#include <stdio.h>
#include <cstdint>

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

// TODO: Add char (utf8 for mono)

typedef wchar_t mono_char; // used by CoreCLR

#define DO_API(r,n,p) extern "C" r n p;

#include <MonoTypes.h>
#include <MonoFunctions.h>

int main()
{
    //MonoDomain *domain  = mono_jit_init_version ("myapp", "v4.0.30319");
    
    /*MonoAssembly *assembly;

    printf("Opening assembly...\n");
    assembly = mono_domain_assembly_open (domain, "coreclrtest.dll");

    printf("Getting image...\n");
    MonoImage* image = mono_assembly_get_image(assembly);

    printf("Getting class...\n");
    MonoClass* klass = mono_class_from_name(image, "coreclrtest", "test");

    printf("Getting method description...\n");
    MonoMethodDesc* methodDesc = mono_method_desc_new ("GetNumber", false);

    printf("Getting method...\n");
    MonoMethod* method = mono_method_desc_search_in_class (methodDesc, klass);

    printf("Invoking...\n");
    MonoObject* returnValue = mono_runtime_invoke(method, nullptr, nullptr, nullptr);

    int int_result = *(int*)mono_object_unbox (returnValue);

    printf("Invoke result: %i\n", int_result);

    printf("Cleaning up...\n");*/
    //mono_jit_cleanup (domain);

    return 0;
}