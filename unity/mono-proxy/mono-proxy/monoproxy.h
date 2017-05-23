#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>
#include <set>
#include <mutex>

#ifndef WIN32
#include <unistd.h>
#include <dlfcn.h>
#endif

#ifdef WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
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
typedef void* MonoStackWalk;
typedef void* MonoCoreClrPlatformCB;
typedef void* vprintf_func;
typedef void* MonoDlFallbackLoad;
typedef void* MonoDlFallbackSymbol;
typedef void* MonoDlFallbackClose;
typedef void* MonoProfileFunc;
typedef void* MonoProfileMethodFunc;
typedef void* MonoProfileGCFunc;
typedef void* MonoProfileGCResizeFunc;
typedef void* MonoProfileAllocFunc;
typedef void* MonoProfileJitResult;
typedef void* MonoProfileThreadFunc;
typedef void* MonoProfileExceptionFunc;
typedef void* MonoProfileExceptionClauseFunc;

#include <MonoTypes.h>

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

FILE* logFile;
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

std::string get_directory_from_this_dll()
{
    char appPath[MAX_PATH] = { 0 };
    GetModuleFileNameA((HINSTANCE)&__ImageBase, appPath, _countof(appPath));
    for (size_t i = strlen(appPath) - 1; i >= 0; i--)
    {
        if (appPath[i] == '\\')
        {
            appPath[i + 1] = 0;
            break;
        }
    }
    std::string dllPath = appPath;
    return dllPath;
}

std::mutex mtx;
std::set<std::string> FunctionsUsed;

void log_function_usage(const char* funcname)
{
    mtx.lock();
    if (!logFile)
    {
        std::string logPath = get_directory_from_this_dll();
        logPath += "monoproxy.log";
        logFile = fopen(logPath.c_str(), "w");
    }
    if (FunctionsUsed.find(funcname) == FunctionsUsed.end())
    {
        FunctionsUsed.insert(funcname);
        fprintf(logFile, "%s\n", funcname);
        fflush(logFile);
    }
    mtx.unlock();
}


void* mono_dll_handle;
void* load_mono_function(const char* funcname)
{
    if (!mono_dll_handle)
    {
        std::string dllPath = get_directory_from_this_dll();
        dllPath += "mono-2.0-bdwgc_original.dll";

        mono_dll_handle = dlopen(dllPath.c_str(), RTLD_LAZY);
        assert(mono_dll_handle);
    }

    auto p = dlsym(mono_dll_handle, funcname);
    assert(p);
    return p;
}
