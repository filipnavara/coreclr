#include <stdio.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef WIN32
#include <unistd.h>
#include <dlfcn.h>
#endif

typedef signed short SInt16;

typedef unsigned short UInt16;
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef signed int SInt32;
typedef unsigned int UInt32;
typedef signed long long SInt64;
typedef unsigned long long UInt64;

typedef void* mono_register_object_callback;
typedef void* mono_liveness_world_state_callback;

void* s_MonoLibrary = nullptr;

#ifdef WIN32
#include <Windows.h>
const int RTLD_LAZY = 0; // not used
void* dlopen(const char* path, int flags)
{
    return ::LoadLibraryA(path);
}
void dlclose(void* handle)
{
    ::FreeLibrary((HMODULE)handle);
}
void* dlsym(void* handle, const char* funcname)
{
    auto sym = ::GetProcAddress((HMODULE)handle, funcname);
    if (!sym)
    {
        printf("Failing to dlsym '%s'\n", funcname);
        //exit(1);
    }
    return sym;
}
#endif

void* get_handle()
{
    if(s_MonoLibrary == nullptr)
    {
        std::string monoRuntimeFolder = getenv("UNITY_ROOT");
#if defined(__APPLE__)
        monoRuntimeFolder += "/External/MonoBleedingEdge/builds/embedruntimes/osx/libmonosgen-2.0.dylib";
#elif defined(_WIN64)
        monoRuntimeFolder += "/External/MonoBleedingEdge/builds/embedruntimes/win64/mono-2.0-sgen.dll";
#elif defined(_WIN32)
        monoRuntimeFolder += "/External/MonoBleedingEdge/builds/embedruntimes/win32/mono-2.0-sgen.dll";
#else
#error("Not supported");
#endif

        printf("Loading Mono from '%s'...\n", monoRuntimeFolder.c_str());
        s_MonoLibrary = dlopen(monoRuntimeFolder.c_str(), RTLD_LAZY);

        if(s_MonoLibrary == nullptr)
        {
            printf("Failed to load mono\n");
            exit(1);
        }
    }
    return s_MonoLibrary;
}

typedef wchar_t mono_char; // used by CoreCLR

#define DO_API(r,n,p) typedef r (*type_##n)p; type_##n n = (type_##n)dlsym(get_handle(), #n);

#include <MonoTypes.h>
#include <MonoFunctions.h>

const char* k_MonoLib = "/External/MonoBleedingEdge/builds/monodistribution/lib";
const char* k_MonoEtc = "/External/MonoBleedingEdge/builds/monodistribution/etc";

extern "C" void InternalMethod()
{
    printf("Internal method was called\n");
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Provide path to dll!\n");
        return 1;
    }

    std::string dllPath = argv[1];

    std::string monoRuntimeFolder = getenv("UNITY_ROOT");
    std::string monoLibFolder = monoRuntimeFolder + k_MonoLib;
    std::string monoEtcFolder = monoRuntimeFolder + k_MonoEtc;

    printf("Setting up directories for Mono...\n");
    mono_set_dirs(monoLibFolder.c_str(), monoEtcFolder.c_str());

    printf("Creating domain...\n");
    MonoDomain *domain  = mono_jit_init_version ("myapp", "v4.0.30319");

    if(domain == nullptr)
    {
        printf("Failed to create domain!\n");
        return 1;
    }
    
    printf("Opening assembly '%s'...\n", dllPath.c_str());
    MonoAssembly* assembly = mono_domain_assembly_open (domain, dllPath.c_str());

    if(assembly == nullptr)
    {
        printf("Failed to load assembly!\n");
        return 1;
    }

    printf("Adding internal method 'coreclrtest.test::InternalMethod'...\n");
    mono_add_internal_call ("coreclrtest.test::InternalMethod", reinterpret_cast<gconstpointer>(InternalMethod));

    printf("Getting image...\n");
    MonoImage* image = mono_assembly_get_image(assembly);

    if(image == nullptr)
    {
        printf("Failed to get image!\n");
        return 1;
    }

    printf("Getting class...\n");
    MonoClass* klass = mono_class_from_name(image, "coreclrtest", "test");

    if(klass == nullptr)
    {
        printf("Failed to get class!\n");
        return 1;
    }

    printf("Getting method...\n");
    MonoMethod* method = mono_class_get_method_from_name (klass, "GetNumber", 0);

    if(method == nullptr)
    {
        printf("Failed to get method!\n");
        return 1;
    }

    printf("Invoking...\n");
    MonoObject* returnValue = mono_runtime_invoke(method, nullptr, nullptr, nullptr);

    if(returnValue == nullptr)
    {
        printf("Failed to invoke!\n");
        return 1;
    }

    int int_result = *(int*)mono_object_unbox (returnValue);

    printf("Invoke result: %i\n", int_result);

    printf("Cleaning up...\n");

#ifdef USE_CONSOLEBRANCH_MONO
    mono_jit_cleanup(domain);
#else
    mono_unity_jit_cleanup(domain);
#endif

    dlclose(s_MonoLibrary);

    return 0;
}
