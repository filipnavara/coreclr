#include <stdio.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>

#ifndef WIN32
#include <unistd.h>
#include <dlfcn.h>
#endif

#define USE_CORECLR

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
#if !defined(USE_CORECLR)
        const char* unityRoot = getenv("UNITY_ROOT");

        if(unityRoot == nullptr)
        {
            printf("UNITY_ROOT is not defined!\n");
            exit(1);
        }

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
#else
#if defined(__APPLE__)
    std::string monoRuntimeFolder = "/Users/sergeyyanchi/development/hackweek2017/coreclr/bin/Product/OSX.x64.Debug/libcoreclr.dylib";
#else
    std::string monoRuntimeFolder = "C:\\Code\\dotnet\\coreclr\\bin\\Product\\Windows_NT.x64.Debug\\coreclr.dll";
#endif
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

void* get_method(const char* functionName)
{
    void* func = dlsym(get_handle(), functionName);
    if(func == nullptr)
    {
        printf("Failed to load function '%s'\n", functionName);
        // Don't hard exit as some functions are not exported while still exposed by MonoFunctions.h
        // So we might get a null access exception if we are using a function
        // that was not found, but we can identify them when it is failing
        // exit(1);
        return nullptr;
    }
    return func;
}

#define DO_API(r,n,p) typedef r (*type_##n)p; type_##n n = (type_##n)get_method(#n);

#define GET_AND_ASSERT(what, code) \
    printf("Quering %s:", #what); \
    auto what = code; \
    if(what == nullptr) \
    { \
        printf(" failed!\n"); \
        assert(false && "Failing computing "#what); \
    } \
    printf(" ok\n");

#define GET_AND_ASSERT_MESSAGE(what, code, message, ...) \
    printf(message, __VA_ARGS__); \
    auto what = code; \
    if(what == nullptr) \
    { \
        printf(" failed!\n"); \
        assert(false && "Failing computing "#what); \
    } \
    printf(" ok\n");

#define ADD_INTERNAL_METHOD(method, namespace) \
    printf("Adding internal method %s", #method); \
    mono_add_internal_call(namespace"::"#method, reinterpret_cast<gconstpointer>(method)); \
    printf(" ok\n");

#include <MonoTypes.h>
#include <MonoFunctions.h>

const char* k_MonoLib = "/External/MonoBleedingEdge/builds/monodistribution/lib";
const char* k_MonoEtc = "/External/MonoBleedingEdge/builds/monodistribution/etc";

void InternalMethod()
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
#if !defined(USE_CORECLR)
    std::string monoLibFolder = monoRuntimeFolder + k_MonoLib;
    std::string monoEtcFolder = monoRuntimeFolder + k_MonoEtc;
#else
#if defined(__APPLE__)
    std::string monoLibFolder = "/usr/local/share/dotnet/shared/Microsoft.NETCore.App/2.0.0-preview1-002111-00";
    std::string monoEtcFolder = "";
#else
    std::string monoLibFolder = "C:\\Program Files\\dotnet\\shared\\Microsoft.NETCore.App\\2.0.0-preview1-002111-00";
    std::string monoEtcFolder = "";
#endif
#endif

    printf("Setting up directories for Mono...\n");
    mono_set_dirs(monoLibFolder.c_str(), monoEtcFolder.c_str());

    GET_AND_ASSERT(domain, mono_jit_init_version ("myapp", "v4.0.30319"));
    GET_AND_ASSERT_MESSAGE(assembly, mono_domain_assembly_open (domain, dllPath.c_str()), "Opening assembly '%s': ", dllPath.c_str());
    
    ADD_INTERNAL_METHOD(InternalMethod, "coreclrtest.test");

    GET_AND_ASSERT(image, mono_assembly_get_image(assembly));
    GET_AND_ASSERT(klass, mono_class_from_name(image, "coreclrtest", "test"));
    GET_AND_ASSERT(method, mono_class_get_method_from_name (klass, "GetNumber", 0));
    
    //GET_AND_ASSERT(returnValue, mono_runtime_invoke(method, nullptr, nullptr, nullptr));
    auto returnValue = mono_runtime_invoke(method, nullptr, nullptr, nullptr);
    {
        int int_result = *(int*)mono_object_unbox(returnValue);
        printf("Invoke result: %i\n", int_result);
    }

    {
        GET_AND_ASSERT(method_StaticTestArg1_int, mono_class_get_method_from_name(klass, "StaticTestArg1_int", 1));
        int param1 = 10;
        void* params[1] = { &param1 };
        auto resultObj = mono_runtime_invoke(method_StaticTestArg1_int, nullptr, params, nullptr);
        int result = *(int*)mono_object_unbox(resultObj);
        assert(result == param1 + 1);
    }
    {
        GET_AND_ASSERT(method, mono_class_get_method_from_name(klass, "StaticTestArg2_int", 2));
        int param1 = 10;
        int param2 = 15;
        void* params[2] = { &param1, &param2 };
        auto resultObj = mono_runtime_invoke(method, nullptr, params, nullptr);
        int result = *(int*)mono_object_unbox(resultObj);
        assert(result == param1 + param2);
    }
    {
        GET_AND_ASSERT(method, mono_class_get_method_from_name(klass, "StaticTestArg2_float", 2));
        float param1 = 10.0f;
        float param2 = 15.0f;
        void* params[2] = { &param1, &param2 };
        auto resultObj = mono_runtime_invoke(method, nullptr, params, nullptr);
        float result = *(float*)mono_object_unbox(resultObj);
        assert(result == param1 + param2);
    }

    // Create Object
    GET_AND_ASSERT(testobj, mono_object_new(domain, klass));

    {
        GET_AND_ASSERT(method, mono_class_get_method_from_name(klass, "StaticTestArg1_obj", 1));
        void* params[1] = { testobj };
        auto resultObj = mono_runtime_invoke(method, nullptr, params, nullptr);
        // GC is conservative, so the object should never move
        assert(resultObj == testobj);
    }


    GET_AND_ASSERT(klassClassWithAttribute, mono_class_from_name(image, "coreclrtest", "ClassWithAttribute"));
    GET_AND_ASSERT(klassTestAttribute, mono_class_from_name(image, "coreclrtest", "TestAttribute"));
    GET_AND_ASSERT(klassAnotherTestAttribute, mono_class_from_name(image, "coreclrtest", "AnotherTestAttribute"));
    GET_AND_ASSERT(customAttrInfo, mono_custom_attrs_from_class(klassClassWithAttribute));

    printf("class ClassWithAttribute with attribute TestAttribute (1): %i\n", mono_custom_attrs_has_attr(customAttrInfo, klassTestAttribute));
    printf("class ClassWithAttribute with attribute AnotherTestAttribute (0): %i\n", mono_custom_attrs_has_attr(customAttrInfo, klassAnotherTestAttribute));

    GET_AND_ASSERT(methodWithAttribute, mono_class_get_method_from_name (klass, "MethodWithAttribute", 0));
    GET_AND_ASSERT(methodCustomAttrInfo, mono_custom_attrs_from_class(klassClassWithAttribute));

    printf("class MethodWithAttribute with attribute TestAttribute (1): %i\n", mono_custom_attrs_has_attr(methodCustomAttrInfo, klassTestAttribute));
    printf("class MethodWithAttribute with attribute AnotherTestAttribute (0): %i\n", mono_custom_attrs_has_attr(methodCustomAttrInfo, klassAnotherTestAttribute));
    
    printf("class test is sub class of ClassWithAttribute (1): %i\n", mono_class_is_subclass_of(klass, klassClassWithAttribute, 1));
    printf("class test is sub class of TestAttribute (0): %i\n", mono_class_is_subclass_of(klass, klassTestAttribute, 1));

    mono_custom_attrs_free(customAttrInfo);
    mono_custom_attrs_free(methodCustomAttrInfo);

    MonoAssemblyName assemblyName;
    mono_assembly_name_parse("coreclr-test", &assemblyName);

    GET_AND_ASSERT(loadedAssembly, mono_assembly_loaded (&assemblyName));

    printf("Assemblies should be the same (1): %i\n", loadedAssembly == assembly);

    GET_AND_ASSERT(corlib, mono_get_corlib());

    GET_AND_ASSERT(enumClass, mono_get_enum_class());

    printf("Cleaning up...\n");
    mono_unity_jit_cleanup(domain);

    dlclose(s_MonoLibrary);

    return 0;
}
