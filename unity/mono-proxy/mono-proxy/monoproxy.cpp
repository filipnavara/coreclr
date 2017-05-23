// This file is generated automatically DO NOT EDIT
// Generated with MonoProxyCodeGen

#include "monoproxy.h"

typedef void (*type_mono_thread_suspend_all_other_threads)();
type_mono_thread_suspend_all_other_threads __mono_thread_suspend_all_other_threads__;
extern "C" EXPORT_API void mono_thread_suspend_all_other_threads()
{
    log_function_usage("mono_thread_suspend_all_other_threads");
    if (!__mono_thread_suspend_all_other_threads__)
        __mono_thread_suspend_all_other_threads__ = (type_mono_thread_suspend_all_other_threads)load_mono_function("mono_thread_suspend_all_other_threads");
    __mono_thread_suspend_all_other_threads__();
}

typedef void (*type_mono_thread_pool_cleanup)();
type_mono_thread_pool_cleanup __mono_thread_pool_cleanup__;
extern "C" EXPORT_API void mono_thread_pool_cleanup()
{
    log_function_usage("mono_thread_pool_cleanup");
    if (!__mono_thread_pool_cleanup__)
        __mono_thread_pool_cleanup__ = (type_mono_thread_pool_cleanup)load_mono_function("mono_thread_pool_cleanup");
    __mono_thread_pool_cleanup__();
}

typedef void (*type_mono_threads_set_shutting_down)();
type_mono_threads_set_shutting_down __mono_threads_set_shutting_down__;
extern "C" EXPORT_API void mono_threads_set_shutting_down()
{
    log_function_usage("mono_threads_set_shutting_down");
    if (!__mono_threads_set_shutting_down__)
        __mono_threads_set_shutting_down__ = (type_mono_threads_set_shutting_down)load_mono_function("mono_threads_set_shutting_down");
    __mono_threads_set_shutting_down__();
}

typedef void (*type_mono_runtime_set_shutting_down)();
type_mono_runtime_set_shutting_down __mono_runtime_set_shutting_down__;
extern "C" EXPORT_API void mono_runtime_set_shutting_down()
{
    log_function_usage("mono_runtime_set_shutting_down");
    if (!__mono_runtime_set_shutting_down__)
        __mono_runtime_set_shutting_down__ = (type_mono_runtime_set_shutting_down)load_mono_function("mono_runtime_set_shutting_down");
    __mono_runtime_set_shutting_down__();
}

typedef gboolean (*type_mono_runtime_is_shutting_down)();
type_mono_runtime_is_shutting_down __mono_runtime_is_shutting_down__;
extern "C" EXPORT_API gboolean mono_runtime_is_shutting_down()
{
    log_function_usage("mono_runtime_is_shutting_down");
    if (!__mono_runtime_is_shutting_down__)
        __mono_runtime_is_shutting_down__ = (type_mono_runtime_is_shutting_down)load_mono_function("mono_runtime_is_shutting_down");
    return __mono_runtime_is_shutting_down__();
}

typedef gboolean (*type_mono_domain_finalize)(MonoDomain * domain, int timeout);
type_mono_domain_finalize __mono_domain_finalize__;
extern "C" EXPORT_API gboolean mono_domain_finalize(MonoDomain * domain, int timeout)
{
    log_function_usage("mono_domain_finalize");
    if (!__mono_domain_finalize__)
        __mono_domain_finalize__ = (type_mono_domain_finalize)load_mono_function("mono_domain_finalize");
    return __mono_domain_finalize__(domain, timeout);
}

typedef void (*type_mono_runtime_cleanup)(MonoDomain * domain);
type_mono_runtime_cleanup __mono_runtime_cleanup__;
extern "C" EXPORT_API void mono_runtime_cleanup(MonoDomain * domain)
{
    log_function_usage("mono_runtime_cleanup");
    if (!__mono_runtime_cleanup__)
        __mono_runtime_cleanup__ = (type_mono_runtime_cleanup)load_mono_function("mono_runtime_cleanup");
    __mono_runtime_cleanup__(domain);
}

typedef MonoMethod* (*type_mono_object_get_virtual_method)(MonoObject * obj, MonoMethod * method);
type_mono_object_get_virtual_method __mono_object_get_virtual_method__;
extern "C" EXPORT_API MonoMethod* mono_object_get_virtual_method(MonoObject * obj, MonoMethod * method)
{
    log_function_usage("mono_object_get_virtual_method");
    if (!__mono_object_get_virtual_method__)
        __mono_object_get_virtual_method__ = (type_mono_object_get_virtual_method)load_mono_function("mono_object_get_virtual_method");
    return __mono_object_get_virtual_method__(obj, method);
}

typedef void (*type_mono_verifier_set_mode)(MiniVerifierMode mode);
type_mono_verifier_set_mode __mono_verifier_set_mode__;
extern "C" EXPORT_API void mono_verifier_set_mode(MiniVerifierMode mode)
{
    log_function_usage("mono_verifier_set_mode");
    if (!__mono_verifier_set_mode__)
        __mono_verifier_set_mode__ = (type_mono_verifier_set_mode)load_mono_function("mono_verifier_set_mode");
    __mono_verifier_set_mode__(mode);
}

typedef void (*type_mono_security_set_mode)(MonoSecurityMode mode);
type_mono_security_set_mode __mono_security_set_mode__;
extern "C" EXPORT_API void mono_security_set_mode(MonoSecurityMode mode)
{
    log_function_usage("mono_security_set_mode");
    if (!__mono_security_set_mode__)
        __mono_security_set_mode__ = (type_mono_security_set_mode)load_mono_function("mono_security_set_mode");
    __mono_security_set_mode__(mode);
}

typedef void (*type_mono_add_internal_call)(const char *name, gconstpointer method);
type_mono_add_internal_call __mono_add_internal_call__;
extern "C" EXPORT_API void mono_add_internal_call(const char *name, gconstpointer method)
{
    log_function_usage("mono_add_internal_call");
    if (!__mono_add_internal_call__)
        __mono_add_internal_call__ = (type_mono_add_internal_call)load_mono_function("mono_add_internal_call");
    __mono_add_internal_call__(name, method);
}

typedef void (*type_mono_unity_jit_cleanup)(MonoDomain * domain);
type_mono_unity_jit_cleanup __mono_unity_jit_cleanup__;
extern "C" EXPORT_API void mono_unity_jit_cleanup(MonoDomain * domain)
{
    log_function_usage("mono_unity_jit_cleanup");
    if (!__mono_unity_jit_cleanup__)
        __mono_unity_jit_cleanup__ = (type_mono_unity_jit_cleanup)load_mono_function("mono_unity_jit_cleanup");
    __mono_unity_jit_cleanup__(domain);
}

typedef MonoDomain* (*type_mono_jit_init)(const char *file);
type_mono_jit_init __mono_jit_init__;
extern "C" EXPORT_API MonoDomain* mono_jit_init(const char *file)
{
    log_function_usage("mono_jit_init");
    if (!__mono_jit_init__)
        __mono_jit_init__ = (type_mono_jit_init)load_mono_function("mono_jit_init");
    return __mono_jit_init__(file);
}

typedef MonoDomain* (*type_mono_jit_init_version)(const char *file, const char* runtime_version);
type_mono_jit_init_version __mono_jit_init_version__;
extern "C" EXPORT_API MonoDomain* mono_jit_init_version(const char *file, const char* runtime_version)
{
    log_function_usage("mono_jit_init_version");
    if (!__mono_jit_init_version__)
        __mono_jit_init_version__ = (type_mono_jit_init_version)load_mono_function("mono_jit_init_version");
    return __mono_jit_init_version__(file, runtime_version);
}

typedef int (*type_mono_jit_exec)(MonoDomain * domain, MonoAssembly * assembly, int argc, char *argv[]);
type_mono_jit_exec __mono_jit_exec__;
extern "C" EXPORT_API int mono_jit_exec(MonoDomain * domain, MonoAssembly * assembly, int argc, char *argv[])
{
    log_function_usage("mono_jit_exec");
    if (!__mono_jit_exec__)
        __mono_jit_exec__ = (type_mono_jit_exec)load_mono_function("mono_jit_exec");
    return __mono_jit_exec__(domain, assembly, argc, argv);
}

typedef void* (*type_mono_jit_info_get_code_start)(void* jit);
type_mono_jit_info_get_code_start __mono_jit_info_get_code_start__;
extern "C" EXPORT_API void* mono_jit_info_get_code_start(void* jit)
{
    log_function_usage("mono_jit_info_get_code_start");
    if (!__mono_jit_info_get_code_start__)
        __mono_jit_info_get_code_start__ = (type_mono_jit_info_get_code_start)load_mono_function("mono_jit_info_get_code_start");
    return __mono_jit_info_get_code_start__(jit);
}

typedef int (*type_mono_jit_info_get_code_size)(void* jit);
type_mono_jit_info_get_code_size __mono_jit_info_get_code_size__;
extern "C" EXPORT_API int mono_jit_info_get_code_size(void* jit)
{
    log_function_usage("mono_jit_info_get_code_size");
    if (!__mono_jit_info_get_code_size__)
        __mono_jit_info_get_code_size__ = (type_mono_jit_info_get_code_size)load_mono_function("mono_jit_info_get_code_size");
    return __mono_jit_info_get_code_size__(jit);
}

typedef MonoClass * (*type_mono_class_from_name)(MonoImage * image, const char* name_space, const char *name);
type_mono_class_from_name __mono_class_from_name__;
extern "C" EXPORT_API MonoClass * mono_class_from_name(MonoImage * image, const char* name_space, const char *name)
{
    log_function_usage("mono_class_from_name");
    if (!__mono_class_from_name__)
        __mono_class_from_name__ = (type_mono_class_from_name)load_mono_function("mono_class_from_name");
    return __mono_class_from_name__(image, name_space, name);
}

typedef MonoClass * (*type_mono_class_from_name_case)(MonoImage * image, const char* name_space, const char *name);
type_mono_class_from_name_case __mono_class_from_name_case__;
extern "C" EXPORT_API MonoClass * mono_class_from_name_case(MonoImage * image, const char* name_space, const char *name)
{
    log_function_usage("mono_class_from_name_case");
    if (!__mono_class_from_name_case__)
        __mono_class_from_name_case__ = (type_mono_class_from_name_case)load_mono_function("mono_class_from_name_case");
    return __mono_class_from_name_case__(image, name_space, name);
}

typedef MonoAssembly * (*type_mono_domain_assembly_open)(MonoDomain * domain, const char *name);
type_mono_domain_assembly_open __mono_domain_assembly_open__;
extern "C" EXPORT_API MonoAssembly * mono_domain_assembly_open(MonoDomain * domain, const char *name)
{
    log_function_usage("mono_domain_assembly_open");
    if (!__mono_domain_assembly_open__)
        __mono_domain_assembly_open__ = (type_mono_domain_assembly_open)load_mono_function("mono_domain_assembly_open");
    return __mono_domain_assembly_open__(domain, name);
}

typedef MonoDomain * (*type_mono_domain_create_appdomain)(const char *domainname, const char* configfile);
type_mono_domain_create_appdomain __mono_domain_create_appdomain__;
extern "C" EXPORT_API MonoDomain * mono_domain_create_appdomain(const char *domainname, const char* configfile)
{
    log_function_usage("mono_domain_create_appdomain");
    if (!__mono_domain_create_appdomain__)
        __mono_domain_create_appdomain__ = (type_mono_domain_create_appdomain)load_mono_function("mono_domain_create_appdomain");
    return __mono_domain_create_appdomain__(domainname, configfile);
}

typedef void (*type_mono_domain_unload)(MonoDomain * domain);
type_mono_domain_unload __mono_domain_unload__;
extern "C" EXPORT_API void mono_domain_unload(MonoDomain * domain)
{
    log_function_usage("mono_domain_unload");
    if (!__mono_domain_unload__)
        __mono_domain_unload__ = (type_mono_domain_unload)load_mono_function("mono_domain_unload");
    __mono_domain_unload__(domain);
}

typedef MonoObject* (*type_mono_object_new)(MonoDomain * domain, MonoClass * klass);
type_mono_object_new __mono_object_new__;
extern "C" EXPORT_API MonoObject* mono_object_new(MonoDomain * domain, MonoClass * klass)
{
    log_function_usage("mono_object_new");
    if (!__mono_object_new__)
        __mono_object_new__ = (type_mono_object_new)load_mono_function("mono_object_new");
    return __mono_object_new__(domain, klass);
}

typedef void (*type_mono_runtime_object_init)(MonoObject * this_obj);
type_mono_runtime_object_init __mono_runtime_object_init__;
extern "C" EXPORT_API void mono_runtime_object_init(MonoObject * this_obj)
{
    log_function_usage("mono_runtime_object_init");
    if (!__mono_runtime_object_init__)
        __mono_runtime_object_init__ = (type_mono_runtime_object_init)load_mono_function("mono_runtime_object_init");
    __mono_runtime_object_init__(this_obj);
}

typedef MonoObject* (*type_mono_runtime_invoke)(MonoMethod * method, void *obj, void **params, MonoException **exc);
type_mono_runtime_invoke __mono_runtime_invoke__;
extern "C" EXPORT_API MonoObject* mono_runtime_invoke(MonoMethod * method, void *obj, void **params, MonoException **exc)
{
    log_function_usage("mono_runtime_invoke");
    if (!__mono_runtime_invoke__)
        __mono_runtime_invoke__ = (type_mono_runtime_invoke)load_mono_function("mono_runtime_invoke");
    return __mono_runtime_invoke__(method, obj, params, exc);
}

typedef void (*type_mono_field_set_value)(MonoObject * obj, MonoClassField * field, void *value);
type_mono_field_set_value __mono_field_set_value__;
extern "C" EXPORT_API void mono_field_set_value(MonoObject * obj, MonoClassField * field, void *value)
{
    log_function_usage("mono_field_set_value");
    if (!__mono_field_set_value__)
        __mono_field_set_value__ = (type_mono_field_set_value)load_mono_function("mono_field_set_value");
    __mono_field_set_value__(obj, field, value);
}

typedef void (*type_mono_field_get_value)(MonoObject * obj, MonoClassField * field, void *value);
type_mono_field_get_value __mono_field_get_value__;
extern "C" EXPORT_API void mono_field_get_value(MonoObject * obj, MonoClassField * field, void *value)
{
    log_function_usage("mono_field_get_value");
    if (!__mono_field_get_value__)
        __mono_field_get_value__ = (type_mono_field_get_value)load_mono_function("mono_field_get_value");
    __mono_field_get_value__(obj, field, value);
}

typedef int (*type_mono_field_get_offset)(MonoClassField * field);
type_mono_field_get_offset __mono_field_get_offset__;
extern "C" EXPORT_API int mono_field_get_offset(MonoClassField * field)
{
    log_function_usage("mono_field_get_offset");
    if (!__mono_field_get_offset__)
        __mono_field_get_offset__ = (type_mono_field_get_offset)load_mono_function("mono_field_get_offset");
    return __mono_field_get_offset__(field);
}

typedef MonoClassField* (*type_mono_class_get_fields)(MonoClass * klass, gpointer * iter);
type_mono_class_get_fields __mono_class_get_fields__;
extern "C" EXPORT_API MonoClassField* mono_class_get_fields(MonoClass * klass, gpointer * iter)
{
    log_function_usage("mono_class_get_fields");
    if (!__mono_class_get_fields__)
        __mono_class_get_fields__ = (type_mono_class_get_fields)load_mono_function("mono_class_get_fields");
    return __mono_class_get_fields__(klass, iter);
}

typedef MonoClass* (*type_mono_class_get_nested_types)(MonoClass * klass, gpointer * iter);
type_mono_class_get_nested_types __mono_class_get_nested_types__;
extern "C" EXPORT_API MonoClass* mono_class_get_nested_types(MonoClass * klass, gpointer * iter)
{
    log_function_usage("mono_class_get_nested_types");
    if (!__mono_class_get_nested_types__)
        __mono_class_get_nested_types__ = (type_mono_class_get_nested_types)load_mono_function("mono_class_get_nested_types");
    return __mono_class_get_nested_types__(klass, iter);
}

typedef MonoMethod* (*type_mono_class_get_methods)(MonoClass * klass, gpointer * iter);
type_mono_class_get_methods __mono_class_get_methods__;
extern "C" EXPORT_API MonoMethod* mono_class_get_methods(MonoClass * klass, gpointer * iter)
{
    log_function_usage("mono_class_get_methods");
    if (!__mono_class_get_methods__)
        __mono_class_get_methods__ = (type_mono_class_get_methods)load_mono_function("mono_class_get_methods");
    return __mono_class_get_methods__(klass, iter);
}

typedef int (*type_mono_class_get_userdata_offset)();
type_mono_class_get_userdata_offset __mono_class_get_userdata_offset__;
extern "C" EXPORT_API int mono_class_get_userdata_offset()
{
    log_function_usage("mono_class_get_userdata_offset");
    if (!__mono_class_get_userdata_offset__)
        __mono_class_get_userdata_offset__ = (type_mono_class_get_userdata_offset)load_mono_function("mono_class_get_userdata_offset");
    return __mono_class_get_userdata_offset__();
}

typedef void* (*type_mono_class_get_userdata)(MonoClass * klass);
type_mono_class_get_userdata __mono_class_get_userdata__;
extern "C" EXPORT_API void* mono_class_get_userdata(MonoClass * klass)
{
    log_function_usage("mono_class_get_userdata");
    if (!__mono_class_get_userdata__)
        __mono_class_get_userdata__ = (type_mono_class_get_userdata)load_mono_function("mono_class_get_userdata");
    return __mono_class_get_userdata__(klass);
}

typedef void (*type_mono_class_set_userdata)(MonoClass * klass, void* userdata);
type_mono_class_set_userdata __mono_class_set_userdata__;
extern "C" EXPORT_API void mono_class_set_userdata(MonoClass * klass, void* userdata)
{
    log_function_usage("mono_class_set_userdata");
    if (!__mono_class_set_userdata__)
        __mono_class_set_userdata__ = (type_mono_class_set_userdata)load_mono_function("mono_class_set_userdata");
    __mono_class_set_userdata__(klass, userdata);
}

typedef MonoDomain* (*type_mono_domain_get)();
type_mono_domain_get __mono_domain_get__;
extern "C" EXPORT_API MonoDomain* mono_domain_get()
{
    log_function_usage("mono_domain_get");
    if (!__mono_domain_get__)
        __mono_domain_get__ = (type_mono_domain_get)load_mono_function("mono_domain_get");
    return __mono_domain_get__();
}

typedef MonoDomain* (*type_mono_get_root_domain)();
type_mono_get_root_domain __mono_get_root_domain__;
extern "C" EXPORT_API MonoDomain* mono_get_root_domain()
{
    log_function_usage("mono_get_root_domain");
    if (!__mono_get_root_domain__)
        __mono_get_root_domain__ = (type_mono_get_root_domain)load_mono_function("mono_get_root_domain");
    return __mono_get_root_domain__();
}

typedef gint32 (*type_mono_domain_get_id)(MonoDomain * domain);
type_mono_domain_get_id __mono_domain_get_id__;
extern "C" EXPORT_API gint32 mono_domain_get_id(MonoDomain * domain)
{
    log_function_usage("mono_domain_get_id");
    if (!__mono_domain_get_id__)
        __mono_domain_get_id__ = (type_mono_domain_get_id)load_mono_function("mono_domain_get_id");
    return __mono_domain_get_id__(domain);
}

typedef void (*type_mono_assembly_foreach)(GFunc func, gpointer user_data);
type_mono_assembly_foreach __mono_assembly_foreach__;
extern "C" EXPORT_API void mono_assembly_foreach(GFunc func, gpointer user_data)
{
    log_function_usage("mono_assembly_foreach");
    if (!__mono_assembly_foreach__)
        __mono_assembly_foreach__ = (type_mono_assembly_foreach)load_mono_function("mono_assembly_foreach");
    __mono_assembly_foreach__(func, user_data);
}

typedef void (*type_mono_image_close)(MonoImage * image);
type_mono_image_close __mono_image_close__;
extern "C" EXPORT_API void mono_image_close(MonoImage * image)
{
    log_function_usage("mono_image_close");
    if (!__mono_image_close__)
        __mono_image_close__ = (type_mono_image_close)load_mono_function("mono_image_close");
    __mono_image_close__(image);
}

typedef void (*type_mono_unity_socket_security_enabled_set)(gboolean val);
type_mono_unity_socket_security_enabled_set __mono_unity_socket_security_enabled_set__;
extern "C" EXPORT_API void mono_unity_socket_security_enabled_set(gboolean val)
{
    log_function_usage("mono_unity_socket_security_enabled_set");
    if (!__mono_unity_socket_security_enabled_set__)
        __mono_unity_socket_security_enabled_set__ = (type_mono_unity_socket_security_enabled_set)load_mono_function("mono_unity_socket_security_enabled_set");
    __mono_unity_socket_security_enabled_set__(val);
}

typedef const char* (*type_mono_image_get_name)(MonoImage * image);
type_mono_image_get_name __mono_image_get_name__;
extern "C" EXPORT_API const char* mono_image_get_name(MonoImage * image)
{
    log_function_usage("mono_image_get_name");
    if (!__mono_image_get_name__)
        __mono_image_get_name__ = (type_mono_image_get_name)load_mono_function("mono_image_get_name");
    return __mono_image_get_name__(image);
}

typedef MonoClass* (*type_mono_get_object_class)();
type_mono_get_object_class __mono_get_object_class__;
extern "C" EXPORT_API MonoClass* mono_get_object_class()
{
    log_function_usage("mono_get_object_class");
    if (!__mono_get_object_class__)
        __mono_get_object_class__ = (type_mono_get_object_class)load_mono_function("mono_get_object_class");
    return __mono_get_object_class__();
}

typedef void (*type_mono_set_signal_chaining)(gboolean v);
type_mono_set_signal_chaining __mono_set_signal_chaining__;
extern "C" EXPORT_API void mono_set_signal_chaining(gboolean v)
{
    log_function_usage("mono_set_signal_chaining");
    if (!__mono_set_signal_chaining__)
        __mono_set_signal_chaining__ = (type_mono_set_signal_chaining)load_mono_function("mono_set_signal_chaining");
    __mono_set_signal_chaining__(v);
}

typedef long (*type_mono_unity_seh_handler)(EXCEPTION_POINTERS* p);
type_mono_unity_seh_handler __mono_unity_seh_handler__;
extern "C" EXPORT_API long mono_unity_seh_handler(EXCEPTION_POINTERS* p)
{
    log_function_usage("mono_unity_seh_handler");
    if (!__mono_unity_seh_handler__)
        __mono_unity_seh_handler__ = (type_mono_unity_seh_handler)load_mono_function("mono_unity_seh_handler");
    return __mono_unity_seh_handler__(p);
}

typedef void (*type_mono_unity_set_unhandled_exception_handler)(void* p);
type_mono_unity_set_unhandled_exception_handler __mono_unity_set_unhandled_exception_handler__;
extern "C" EXPORT_API void mono_unity_set_unhandled_exception_handler(void* p)
{
    log_function_usage("mono_unity_set_unhandled_exception_handler");
    if (!__mono_unity_set_unhandled_exception_handler__)
        __mono_unity_set_unhandled_exception_handler__ = (type_mono_unity_set_unhandled_exception_handler)load_mono_function("mono_unity_set_unhandled_exception_handler");
    __mono_unity_set_unhandled_exception_handler__(p);
}

typedef void (*type_mono_unity_runtime_set_main_args)(int argc, const char* argv[]);
type_mono_unity_runtime_set_main_args __mono_unity_runtime_set_main_args__;
extern "C" EXPORT_API void mono_unity_runtime_set_main_args(int argc, const char* argv[])
{
    log_function_usage("mono_unity_runtime_set_main_args");
    if (!__mono_unity_runtime_set_main_args__)
        __mono_unity_runtime_set_main_args__ = (type_mono_unity_runtime_set_main_args)load_mono_function("mono_unity_runtime_set_main_args");
    __mono_unity_runtime_set_main_args__(argc, argv);
}

typedef MonoObject* (*type_mono_runtime_invoke_array)(MonoMethod * method, void *obj, MonoArray * params, MonoException **exc);
type_mono_runtime_invoke_array __mono_runtime_invoke_array__;
extern "C" EXPORT_API MonoObject* mono_runtime_invoke_array(MonoMethod * method, void *obj, MonoArray * params, MonoException **exc)
{
    log_function_usage("mono_runtime_invoke_array");
    if (!__mono_runtime_invoke_array__)
        __mono_runtime_invoke_array__ = (type_mono_runtime_invoke_array)load_mono_function("mono_runtime_invoke_array");
    return __mono_runtime_invoke_array__(method, obj, params, exc);
}

typedef char* (*type_mono_array_addr_with_size)(MonoArray * array, int size, uintptr_t idx);
type_mono_array_addr_with_size __mono_array_addr_with_size__;
extern "C" EXPORT_API char* mono_array_addr_with_size(MonoArray * array, int size, uintptr_t idx)
{
    log_function_usage("mono_array_addr_with_size");
    if (!__mono_array_addr_with_size__)
        __mono_array_addr_with_size__ = (type_mono_array_addr_with_size)load_mono_function("mono_array_addr_with_size");
    return __mono_array_addr_with_size__(array, size, idx);
}

typedef gunichar2* (*type_mono_string_to_utf16)(MonoString * string_obj);
type_mono_string_to_utf16 __mono_string_to_utf16__;
extern "C" EXPORT_API gunichar2* mono_string_to_utf16(MonoString * string_obj)
{
    log_function_usage("mono_string_to_utf16");
    if (!__mono_string_to_utf16__)
        __mono_string_to_utf16__ = (type_mono_string_to_utf16)load_mono_function("mono_string_to_utf16");
    return __mono_string_to_utf16__(string_obj);
}

typedef const char* (*type_mono_field_get_name)(MonoClassField * field);
type_mono_field_get_name __mono_field_get_name__;
extern "C" EXPORT_API const char* mono_field_get_name(MonoClassField * field)
{
    log_function_usage("mono_field_get_name");
    if (!__mono_field_get_name__)
        __mono_field_get_name__ = (type_mono_field_get_name)load_mono_function("mono_field_get_name");
    return __mono_field_get_name__(field);
}

typedef MonoClass* (*type_mono_field_get_parent)(MonoClassField * field);
type_mono_field_get_parent __mono_field_get_parent__;
extern "C" EXPORT_API MonoClass* mono_field_get_parent(MonoClassField * field)
{
    log_function_usage("mono_field_get_parent");
    if (!__mono_field_get_parent__)
        __mono_field_get_parent__ = (type_mono_field_get_parent)load_mono_function("mono_field_get_parent");
    return __mono_field_get_parent__(field);
}

typedef MonoType* (*type_mono_field_get_type)(MonoClassField * field);
type_mono_field_get_type __mono_field_get_type__;
extern "C" EXPORT_API MonoType* mono_field_get_type(MonoClassField * field)
{
    log_function_usage("mono_field_get_type");
    if (!__mono_field_get_type__)
        __mono_field_get_type__ = (type_mono_field_get_type)load_mono_function("mono_field_get_type");
    return __mono_field_get_type__(field);
}

typedef int (*type_mono_type_get_type)(MonoType * type);
type_mono_type_get_type __mono_type_get_type__;
extern "C" EXPORT_API int mono_type_get_type(MonoType * type)
{
    log_function_usage("mono_type_get_type");
    if (!__mono_type_get_type__)
        __mono_type_get_type__ = (type_mono_type_get_type)load_mono_function("mono_type_get_type");
    return __mono_type_get_type__(type);
}

typedef const char* (*type_mono_method_get_name)(MonoMethod * method);
type_mono_method_get_name __mono_method_get_name__;
extern "C" EXPORT_API const char* mono_method_get_name(MonoMethod * method)
{
    log_function_usage("mono_method_get_name");
    if (!__mono_method_get_name__)
        __mono_method_get_name__ = (type_mono_method_get_name)load_mono_function("mono_method_get_name");
    return __mono_method_get_name__(method);
}

typedef char* (*type_mono_method_full_name)(MonoMethod * method, gboolean signature);
type_mono_method_full_name __mono_method_full_name__;
extern "C" EXPORT_API char* mono_method_full_name(MonoMethod * method, gboolean signature)
{
    log_function_usage("mono_method_full_name");
    if (!__mono_method_full_name__)
        __mono_method_full_name__ = (type_mono_method_full_name)load_mono_function("mono_method_full_name");
    return __mono_method_full_name__(method, signature);
}

typedef MonoImage* (*type_mono_assembly_get_image)(MonoAssembly * assembly);
type_mono_assembly_get_image __mono_assembly_get_image__;
extern "C" EXPORT_API MonoImage* mono_assembly_get_image(MonoAssembly * assembly)
{
    log_function_usage("mono_assembly_get_image");
    if (!__mono_assembly_get_image__)
        __mono_assembly_get_image__ = (type_mono_assembly_get_image)load_mono_function("mono_assembly_get_image");
    return __mono_assembly_get_image__(assembly);
}

typedef MonoClass* (*type_mono_method_get_class)(MonoMethod * method);
type_mono_method_get_class __mono_method_get_class__;
extern "C" EXPORT_API MonoClass* mono_method_get_class(MonoMethod * method)
{
    log_function_usage("mono_method_get_class");
    if (!__mono_method_get_class__)
        __mono_method_get_class__ = (type_mono_method_get_class)load_mono_function("mono_method_get_class");
    return __mono_method_get_class__(method);
}

typedef MonoClass* (*type_mono_object_get_class)(MonoObject * obj);
type_mono_object_get_class __mono_object_get_class__;
extern "C" EXPORT_API MonoClass* mono_object_get_class(MonoObject * obj)
{
    log_function_usage("mono_object_get_class");
    if (!__mono_object_get_class__)
        __mono_object_get_class__ = (type_mono_object_get_class)load_mono_function("mono_object_get_class");
    return __mono_object_get_class__(obj);
}

typedef MonoObject* (*type_mono_object_isinst)(MonoObject * obj, MonoClass * klass);
type_mono_object_isinst __mono_object_isinst__;
extern "C" EXPORT_API MonoObject* mono_object_isinst(MonoObject * obj, MonoClass * klass)
{
    log_function_usage("mono_object_isinst");
    if (!__mono_object_isinst__)
        __mono_object_isinst__ = (type_mono_object_isinst)load_mono_function("mono_object_isinst");
    return __mono_object_isinst__(obj, klass);
}

typedef gboolean (*type_mono_class_is_valuetype)(MonoClass * klass);
type_mono_class_is_valuetype __mono_class_is_valuetype__;
extern "C" EXPORT_API gboolean mono_class_is_valuetype(MonoClass * klass)
{
    log_function_usage("mono_class_is_valuetype");
    if (!__mono_class_is_valuetype__)
        __mono_class_is_valuetype__ = (type_mono_class_is_valuetype)load_mono_function("mono_class_is_valuetype");
    return __mono_class_is_valuetype__(klass);
}

typedef gboolean (*type_mono_class_is_blittable)(MonoClass * klass);
type_mono_class_is_blittable __mono_class_is_blittable__;
extern "C" EXPORT_API gboolean mono_class_is_blittable(MonoClass * klass)
{
    log_function_usage("mono_class_is_blittable");
    if (!__mono_class_is_blittable__)
        __mono_class_is_blittable__ = (type_mono_class_is_blittable)load_mono_function("mono_class_is_blittable");
    return __mono_class_is_blittable__(klass);
}

typedef guint32 (*type_mono_signature_get_param_count)(MonoMethodSignature * sig);
type_mono_signature_get_param_count __mono_signature_get_param_count__;
extern "C" EXPORT_API guint32 mono_signature_get_param_count(MonoMethodSignature * sig)
{
    log_function_usage("mono_signature_get_param_count");
    if (!__mono_signature_get_param_count__)
        __mono_signature_get_param_count__ = (type_mono_signature_get_param_count)load_mono_function("mono_signature_get_param_count");
    return __mono_signature_get_param_count__(sig);
}

typedef char* (*type_mono_string_to_utf8)(MonoString * string_obj);
type_mono_string_to_utf8 __mono_string_to_utf8__;
extern "C" EXPORT_API char* mono_string_to_utf8(MonoString * string_obj)
{
    log_function_usage("mono_string_to_utf8");
    if (!__mono_string_to_utf8__)
        __mono_string_to_utf8__ = (type_mono_string_to_utf8)load_mono_function("mono_string_to_utf8");
    return __mono_string_to_utf8__(string_obj);
}

typedef MonoString* (*type_mono_unity_string_empty_wrapper)();
type_mono_unity_string_empty_wrapper __mono_unity_string_empty_wrapper__;
extern "C" EXPORT_API MonoString* mono_unity_string_empty_wrapper()
{
    log_function_usage("mono_unity_string_empty_wrapper");
    if (!__mono_unity_string_empty_wrapper__)
        __mono_unity_string_empty_wrapper__ = (type_mono_unity_string_empty_wrapper)load_mono_function("mono_unity_string_empty_wrapper");
    return __mono_unity_string_empty_wrapper__();
}

typedef MonoString* (*type_mono_string_new_wrapper)(const char* text);
type_mono_string_new_wrapper __mono_string_new_wrapper__;
extern "C" EXPORT_API MonoString* mono_string_new_wrapper(const char* text)
{
    log_function_usage("mono_string_new_wrapper");
    if (!__mono_string_new_wrapper__)
        __mono_string_new_wrapper__ = (type_mono_string_new_wrapper)load_mono_function("mono_string_new_wrapper");
    return __mono_string_new_wrapper__(text);
}

typedef MonoString* (*type_mono_string_new_len)(MonoDomain * domain, const char *text, guint32 length);
type_mono_string_new_len __mono_string_new_len__;
extern "C" EXPORT_API MonoString* mono_string_new_len(MonoDomain * domain, const char *text, guint32 length)
{
    log_function_usage("mono_string_new_len");
    if (!__mono_string_new_len__)
        __mono_string_new_len__ = (type_mono_string_new_len)load_mono_function("mono_string_new_len");
    return __mono_string_new_len__(domain, text, length);
}

typedef MonoString* (*type_mono_string_from_utf16)(const gunichar2 * text);
type_mono_string_from_utf16 __mono_string_from_utf16__;
extern "C" EXPORT_API MonoString* mono_string_from_utf16(const gunichar2 * text)
{
    log_function_usage("mono_string_from_utf16");
    if (!__mono_string_from_utf16__)
        __mono_string_from_utf16__ = (type_mono_string_from_utf16)load_mono_function("mono_string_from_utf16");
    return __mono_string_from_utf16__(text);
}

typedef MonoClass* (*type_mono_class_get_parent)(MonoClass * klass);
type_mono_class_get_parent __mono_class_get_parent__;
extern "C" EXPORT_API MonoClass* mono_class_get_parent(MonoClass * klass)
{
    log_function_usage("mono_class_get_parent");
    if (!__mono_class_get_parent__)
        __mono_class_get_parent__ = (type_mono_class_get_parent)load_mono_function("mono_class_get_parent");
    return __mono_class_get_parent__(klass);
}

typedef const char* (*type_mono_class_get_namespace)(MonoClass * klass);
type_mono_class_get_namespace __mono_class_get_namespace__;
extern "C" EXPORT_API const char* mono_class_get_namespace(MonoClass * klass)
{
    log_function_usage("mono_class_get_namespace");
    if (!__mono_class_get_namespace__)
        __mono_class_get_namespace__ = (type_mono_class_get_namespace)load_mono_function("mono_class_get_namespace");
    return __mono_class_get_namespace__(klass);
}

typedef gboolean (*type_mono_class_is_subclass_of)(MonoClass * klass, MonoClass * klassc, gboolean check_interfaces);
type_mono_class_is_subclass_of __mono_class_is_subclass_of__;
extern "C" EXPORT_API gboolean mono_class_is_subclass_of(MonoClass * klass, MonoClass * klassc, gboolean check_interfaces)
{
    log_function_usage("mono_class_is_subclass_of");
    if (!__mono_class_is_subclass_of__)
        __mono_class_is_subclass_of__ = (type_mono_class_is_subclass_of)load_mono_function("mono_class_is_subclass_of");
    return __mono_class_is_subclass_of__(klass, klassc, check_interfaces);
}

typedef const char* (*type_mono_class_get_name)(MonoClass * klass);
type_mono_class_get_name __mono_class_get_name__;
extern "C" EXPORT_API const char* mono_class_get_name(MonoClass * klass)
{
    log_function_usage("mono_class_get_name");
    if (!__mono_class_get_name__)
        __mono_class_get_name__ = (type_mono_class_get_name)load_mono_function("mono_class_get_name");
    return __mono_class_get_name__(klass);
}

typedef char* (*type_mono_type_get_name)(MonoType * type);
type_mono_type_get_name __mono_type_get_name__;
extern "C" EXPORT_API char* mono_type_get_name(MonoType * type)
{
    log_function_usage("mono_type_get_name");
    if (!__mono_type_get_name__)
        __mono_type_get_name__ = (type_mono_type_get_name)load_mono_function("mono_type_get_name");
    return __mono_type_get_name__(type);
}

typedef MonoClass* (*type_mono_type_get_class)(MonoType * type);
type_mono_type_get_class __mono_type_get_class__;
extern "C" EXPORT_API MonoClass* mono_type_get_class(MonoType * type)
{
    log_function_usage("mono_type_get_class");
    if (!__mono_type_get_class__)
        __mono_type_get_class__ = (type_mono_type_get_class)load_mono_function("mono_type_get_class");
    return __mono_type_get_class__(type);
}

typedef MonoException * (*type_mono_exception_from_name_msg)(MonoImage * image, const char *name_space, const char *name, const char *msg);
type_mono_exception_from_name_msg __mono_exception_from_name_msg__;
extern "C" EXPORT_API MonoException * mono_exception_from_name_msg(MonoImage * image, const char *name_space, const char *name, const char *msg)
{
    log_function_usage("mono_exception_from_name_msg");
    if (!__mono_exception_from_name_msg__)
        __mono_exception_from_name_msg__ = (type_mono_exception_from_name_msg)load_mono_function("mono_exception_from_name_msg");
    return __mono_exception_from_name_msg__(image, name_space, name, msg);
}

typedef MonoException * (*type_mono_exception_from_name_two_strings)(MonoImage * image, const char *name_space, const char *name, const char *msg1, const char *msg2);
type_mono_exception_from_name_two_strings __mono_exception_from_name_two_strings__;
extern "C" EXPORT_API MonoException * mono_exception_from_name_two_strings(MonoImage * image, const char *name_space, const char *name, const char *msg1, const char *msg2)
{
    log_function_usage("mono_exception_from_name_two_strings");
    if (!__mono_exception_from_name_two_strings__)
        __mono_exception_from_name_two_strings__ = (type_mono_exception_from_name_two_strings)load_mono_function("mono_exception_from_name_two_strings");
    return __mono_exception_from_name_two_strings__(image, name_space, name, msg1, msg2);
}

typedef MonoException * (*type_mono_get_exception_argument_null)(const char *arg);
type_mono_get_exception_argument_null __mono_get_exception_argument_null__;
extern "C" EXPORT_API MonoException * mono_get_exception_argument_null(const char *arg)
{
    log_function_usage("mono_get_exception_argument_null");
    if (!__mono_get_exception_argument_null__)
        __mono_get_exception_argument_null__ = (type_mono_get_exception_argument_null)load_mono_function("mono_get_exception_argument_null");
    return __mono_get_exception_argument_null__(arg);
}

typedef void (*type_mono_raise_exception)(MonoException * ex);
type_mono_raise_exception __mono_raise_exception__;
extern "C" EXPORT_API void mono_raise_exception(MonoException * ex)
{
    log_function_usage("mono_raise_exception");
    if (!__mono_raise_exception__)
        __mono_raise_exception__ = (type_mono_raise_exception)load_mono_function("mono_raise_exception");
    __mono_raise_exception__(ex);
}

typedef MonoClass* (*type_mono_get_exception_class)();
type_mono_get_exception_class __mono_get_exception_class__;
extern "C" EXPORT_API MonoClass* mono_get_exception_class()
{
    log_function_usage("mono_get_exception_class");
    if (!__mono_get_exception_class__)
        __mono_get_exception_class__ = (type_mono_get_exception_class)load_mono_function("mono_get_exception_class");
    return __mono_get_exception_class__();
}

typedef MonoClass* (*type_mono_get_array_class)();
type_mono_get_array_class __mono_get_array_class__;
extern "C" EXPORT_API MonoClass* mono_get_array_class()
{
    log_function_usage("mono_get_array_class");
    if (!__mono_get_array_class__)
        __mono_get_array_class__ = (type_mono_get_array_class)load_mono_function("mono_get_array_class");
    return __mono_get_array_class__();
}

typedef MonoClass* (*type_mono_get_string_class)();
type_mono_get_string_class __mono_get_string_class__;
extern "C" EXPORT_API MonoClass* mono_get_string_class()
{
    log_function_usage("mono_get_string_class");
    if (!__mono_get_string_class__)
        __mono_get_string_class__ = (type_mono_get_string_class)load_mono_function("mono_get_string_class");
    return __mono_get_string_class__();
}

typedef MonoClass* (*type_mono_get_boolean_class)();
type_mono_get_boolean_class __mono_get_boolean_class__;
extern "C" EXPORT_API MonoClass* mono_get_boolean_class()
{
    log_function_usage("mono_get_boolean_class");
    if (!__mono_get_boolean_class__)
        __mono_get_boolean_class__ = (type_mono_get_boolean_class)load_mono_function("mono_get_boolean_class");
    return __mono_get_boolean_class__();
}

typedef MonoClass* (*type_mono_get_byte_class)();
type_mono_get_byte_class __mono_get_byte_class__;
extern "C" EXPORT_API MonoClass* mono_get_byte_class()
{
    log_function_usage("mono_get_byte_class");
    if (!__mono_get_byte_class__)
        __mono_get_byte_class__ = (type_mono_get_byte_class)load_mono_function("mono_get_byte_class");
    return __mono_get_byte_class__();
}

typedef MonoClass* (*type_mono_get_char_class)();
type_mono_get_char_class __mono_get_char_class__;
extern "C" EXPORT_API MonoClass* mono_get_char_class()
{
    log_function_usage("mono_get_char_class");
    if (!__mono_get_char_class__)
        __mono_get_char_class__ = (type_mono_get_char_class)load_mono_function("mono_get_char_class");
    return __mono_get_char_class__();
}

typedef MonoClass* (*type_mono_get_int16_class)();
type_mono_get_int16_class __mono_get_int16_class__;
extern "C" EXPORT_API MonoClass* mono_get_int16_class()
{
    log_function_usage("mono_get_int16_class");
    if (!__mono_get_int16_class__)
        __mono_get_int16_class__ = (type_mono_get_int16_class)load_mono_function("mono_get_int16_class");
    return __mono_get_int16_class__();
}

typedef MonoClass* (*type_mono_get_int32_class)();
type_mono_get_int32_class __mono_get_int32_class__;
extern "C" EXPORT_API MonoClass* mono_get_int32_class()
{
    log_function_usage("mono_get_int32_class");
    if (!__mono_get_int32_class__)
        __mono_get_int32_class__ = (type_mono_get_int32_class)load_mono_function("mono_get_int32_class");
    return __mono_get_int32_class__();
}

typedef MonoClass* (*type_mono_get_int64_class)();
type_mono_get_int64_class __mono_get_int64_class__;
extern "C" EXPORT_API MonoClass* mono_get_int64_class()
{
    log_function_usage("mono_get_int64_class");
    if (!__mono_get_int64_class__)
        __mono_get_int64_class__ = (type_mono_get_int64_class)load_mono_function("mono_get_int64_class");
    return __mono_get_int64_class__();
}

typedef MonoClass* (*type_mono_get_single_class)();
type_mono_get_single_class __mono_get_single_class__;
extern "C" EXPORT_API MonoClass* mono_get_single_class()
{
    log_function_usage("mono_get_single_class");
    if (!__mono_get_single_class__)
        __mono_get_single_class__ = (type_mono_get_single_class)load_mono_function("mono_get_single_class");
    return __mono_get_single_class__();
}

typedef MonoClass* (*type_mono_get_double_class)();
type_mono_get_double_class __mono_get_double_class__;
extern "C" EXPORT_API MonoClass* mono_get_double_class()
{
    log_function_usage("mono_get_double_class");
    if (!__mono_get_double_class__)
        __mono_get_double_class__ = (type_mono_get_double_class)load_mono_function("mono_get_double_class");
    return __mono_get_double_class__();
}

typedef MonoArray* (*type_mono_array_new)(MonoDomain * domain, MonoClass * eclass, guint32 n);
type_mono_array_new __mono_array_new__;
extern "C" EXPORT_API MonoArray* mono_array_new(MonoDomain * domain, MonoClass * eclass, guint32 n)
{
    log_function_usage("mono_array_new");
    if (!__mono_array_new__)
        __mono_array_new__ = (type_mono_array_new)load_mono_function("mono_array_new");
    return __mono_array_new__(domain, eclass, n);
}

typedef MonoArray* (*type_mono_unity_array_new_2d)(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1);
type_mono_unity_array_new_2d __mono_unity_array_new_2d__;
extern "C" EXPORT_API MonoArray* mono_unity_array_new_2d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1)
{
    log_function_usage("mono_unity_array_new_2d");
    if (!__mono_unity_array_new_2d__)
        __mono_unity_array_new_2d__ = (type_mono_unity_array_new_2d)load_mono_function("mono_unity_array_new_2d");
    return __mono_unity_array_new_2d__(domain, eclass, size0, size1);
}

typedef MonoArray* (*type_mono_unity_array_new_3d)(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1, size_t size2);
type_mono_unity_array_new_3d __mono_unity_array_new_3d__;
extern "C" EXPORT_API MonoArray* mono_unity_array_new_3d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1, size_t size2)
{
    log_function_usage("mono_unity_array_new_3d");
    if (!__mono_unity_array_new_3d__)
        __mono_unity_array_new_3d__ = (type_mono_unity_array_new_3d)load_mono_function("mono_unity_array_new_3d");
    return __mono_unity_array_new_3d__(domain, eclass, size0, size1, size2);
}

typedef MonoClass * (*type_mono_array_class_get)(MonoClass * eclass, guint32 rank);
type_mono_array_class_get __mono_array_class_get__;
extern "C" EXPORT_API MonoClass * mono_array_class_get(MonoClass * eclass, guint32 rank)
{
    log_function_usage("mono_array_class_get");
    if (!__mono_array_class_get__)
        __mono_array_class_get__ = (type_mono_array_class_get)load_mono_function("mono_array_class_get");
    return __mono_array_class_get__(eclass, rank);
}

typedef gint32 (*type_mono_class_array_element_size)(MonoClass * ac);
type_mono_class_array_element_size __mono_class_array_element_size__;
extern "C" EXPORT_API gint32 mono_class_array_element_size(MonoClass * ac)
{
    log_function_usage("mono_class_array_element_size");
    if (!__mono_class_array_element_size__)
        __mono_class_array_element_size__ = (type_mono_class_array_element_size)load_mono_function("mono_class_array_element_size");
    return __mono_class_array_element_size__(ac);
}

typedef MonoObject* (*type_mono_type_get_object)(MonoDomain * domain, MonoType * type);
type_mono_type_get_object __mono_type_get_object__;
extern "C" EXPORT_API MonoObject* mono_type_get_object(MonoDomain * domain, MonoType * type)
{
    log_function_usage("mono_type_get_object");
    if (!__mono_type_get_object__)
        __mono_type_get_object__ = (type_mono_type_get_object)load_mono_function("mono_type_get_object");
    return __mono_type_get_object__(domain, type);
}

typedef gboolean (*type_mono_class_is_generic)(MonoClass * klass);
type_mono_class_is_generic __mono_class_is_generic__;
extern "C" EXPORT_API gboolean mono_class_is_generic(MonoClass * klass)
{
    log_function_usage("mono_class_is_generic");
    if (!__mono_class_is_generic__)
        __mono_class_is_generic__ = (type_mono_class_is_generic)load_mono_function("mono_class_is_generic");
    return __mono_class_is_generic__(klass);
}

typedef gboolean (*type_mono_class_is_inflated)(MonoClass * klass);
type_mono_class_is_inflated __mono_class_is_inflated__;
extern "C" EXPORT_API gboolean mono_class_is_inflated(MonoClass * klass)
{
    log_function_usage("mono_class_is_inflated");
    if (!__mono_class_is_inflated__)
        __mono_class_is_inflated__ = (type_mono_class_is_inflated)load_mono_function("mono_class_is_inflated");
    return __mono_class_is_inflated__(klass);
}

typedef gboolean (*type_unity_mono_method_is_generic)(MonoMethod * method);
type_unity_mono_method_is_generic __unity_mono_method_is_generic__;
extern "C" EXPORT_API gboolean unity_mono_method_is_generic(MonoMethod * method)
{
    log_function_usage("unity_mono_method_is_generic");
    if (!__unity_mono_method_is_generic__)
        __unity_mono_method_is_generic__ = (type_unity_mono_method_is_generic)load_mono_function("unity_mono_method_is_generic");
    return __unity_mono_method_is_generic__(method);
}

typedef gboolean (*type_unity_mono_method_is_inflated)(MonoMethod * method);
type_unity_mono_method_is_inflated __unity_mono_method_is_inflated__;
extern "C" EXPORT_API gboolean unity_mono_method_is_inflated(MonoMethod * method)
{
    log_function_usage("unity_mono_method_is_inflated");
    if (!__unity_mono_method_is_inflated__)
        __unity_mono_method_is_inflated__ = (type_unity_mono_method_is_inflated)load_mono_function("unity_mono_method_is_inflated");
    return __unity_mono_method_is_inflated__(method);
}

typedef MonoThread * (*type_mono_thread_attach)(MonoDomain * domain);
type_mono_thread_attach __mono_thread_attach__;
extern "C" EXPORT_API MonoThread * mono_thread_attach(MonoDomain * domain)
{
    log_function_usage("mono_thread_attach");
    if (!__mono_thread_attach__)
        __mono_thread_attach__ = (type_mono_thread_attach)load_mono_function("mono_thread_attach");
    return __mono_thread_attach__(domain);
}

typedef void (*type_mono_thread_detach)(MonoThread * thread);
type_mono_thread_detach __mono_thread_detach__;
extern "C" EXPORT_API void mono_thread_detach(MonoThread * thread)
{
    log_function_usage("mono_thread_detach");
    if (!__mono_thread_detach__)
        __mono_thread_detach__ = (type_mono_thread_detach)load_mono_function("mono_thread_detach");
    __mono_thread_detach__(thread);
}

typedef MonoThread * (*type_mono_thread_exit)();
type_mono_thread_exit __mono_thread_exit__;
extern "C" EXPORT_API MonoThread * mono_thread_exit()
{
    log_function_usage("mono_thread_exit");
    if (!__mono_thread_exit__)
        __mono_thread_exit__ = (type_mono_thread_exit)load_mono_function("mono_thread_exit");
    return __mono_thread_exit__();
}

typedef MonoThread * (*type_mono_thread_current)();
type_mono_thread_current __mono_thread_current__;
extern "C" EXPORT_API MonoThread * mono_thread_current()
{
    log_function_usage("mono_thread_current");
    if (!__mono_thread_current__)
        __mono_thread_current__ = (type_mono_thread_current)load_mono_function("mono_thread_current");
    return __mono_thread_current__();
}

typedef void (*type_mono_thread_set_main)(MonoThread * thread);
type_mono_thread_set_main __mono_thread_set_main__;
extern "C" EXPORT_API void mono_thread_set_main(MonoThread * thread)
{
    log_function_usage("mono_thread_set_main");
    if (!__mono_thread_set_main__)
        __mono_thread_set_main__ = (type_mono_thread_set_main)load_mono_function("mono_thread_set_main");
    __mono_thread_set_main__(thread);
}

typedef void (*type_mono_set_find_plugin_callback)(gconstpointer method);
type_mono_set_find_plugin_callback __mono_set_find_plugin_callback__;
extern "C" EXPORT_API void mono_set_find_plugin_callback(gconstpointer method)
{
    log_function_usage("mono_set_find_plugin_callback");
    if (!__mono_set_find_plugin_callback__)
        __mono_set_find_plugin_callback__ = (type_mono_set_find_plugin_callback)load_mono_function("mono_set_find_plugin_callback");
    __mono_set_find_plugin_callback__(method);
}

typedef void (*type_mono_security_enable_core_clr)();
type_mono_security_enable_core_clr __mono_security_enable_core_clr__;
extern "C" EXPORT_API void mono_security_enable_core_clr()
{
    log_function_usage("mono_security_enable_core_clr");
    if (!__mono_security_enable_core_clr__)
        __mono_security_enable_core_clr__ = (type_mono_security_enable_core_clr)load_mono_function("mono_security_enable_core_clr");
    __mono_security_enable_core_clr__();
}

typedef void (*type_mono_security_set_core_clr_platform_callback)(MonoCoreClrPlatformCB cb);
type_mono_security_set_core_clr_platform_callback __mono_security_set_core_clr_platform_callback__;
extern "C" EXPORT_API void mono_security_set_core_clr_platform_callback(MonoCoreClrPlatformCB cb)
{
    log_function_usage("mono_security_set_core_clr_platform_callback");
    if (!__mono_security_set_core_clr_platform_callback__)
        __mono_security_set_core_clr_platform_callback__ = (type_mono_security_set_core_clr_platform_callback)load_mono_function("mono_security_set_core_clr_platform_callback");
    __mono_security_set_core_clr_platform_callback__(cb);
}

typedef void (*type_mono_runtime_unhandled_exception_policy_set)(MonoRuntimeUnhandledExceptionPolicy policy);
type_mono_runtime_unhandled_exception_policy_set __mono_runtime_unhandled_exception_policy_set__;
extern "C" EXPORT_API void mono_runtime_unhandled_exception_policy_set(MonoRuntimeUnhandledExceptionPolicy policy)
{
    log_function_usage("mono_runtime_unhandled_exception_policy_set");
    if (!__mono_runtime_unhandled_exception_policy_set__)
        __mono_runtime_unhandled_exception_policy_set__ = (type_mono_runtime_unhandled_exception_policy_set)load_mono_function("mono_runtime_unhandled_exception_policy_set");
    __mono_runtime_unhandled_exception_policy_set__(policy);
}

typedef MonoClass* (*type_mono_class_get_nesting_type)(MonoClass * klass);
type_mono_class_get_nesting_type __mono_class_get_nesting_type__;
extern "C" EXPORT_API MonoClass* mono_class_get_nesting_type(MonoClass * klass)
{
    log_function_usage("mono_class_get_nesting_type");
    if (!__mono_class_get_nesting_type__)
        __mono_class_get_nesting_type__ = (type_mono_class_get_nesting_type)load_mono_function("mono_class_get_nesting_type");
    return __mono_class_get_nesting_type__(klass);
}

typedef MonoVTable* (*type_mono_class_vtable)(MonoDomain * domain, MonoClass * klass);
type_mono_class_vtable __mono_class_vtable__;
extern "C" EXPORT_API MonoVTable* mono_class_vtable(MonoDomain * domain, MonoClass * klass)
{
    log_function_usage("mono_class_vtable");
    if (!__mono_class_vtable__)
        __mono_class_vtable__ = (type_mono_class_vtable)load_mono_function("mono_class_vtable");
    return __mono_class_vtable__(domain, klass);
}

typedef MonoReflectionMethod* (*type_mono_method_get_object)(MonoDomain * domain, MonoMethod * method, MonoClass * refclass);
type_mono_method_get_object __mono_method_get_object__;
extern "C" EXPORT_API MonoReflectionMethod* mono_method_get_object(MonoDomain * domain, MonoMethod * method, MonoClass * refclass)
{
    log_function_usage("mono_method_get_object");
    if (!__mono_method_get_object__)
        __mono_method_get_object__ = (type_mono_method_get_object)load_mono_function("mono_method_get_object");
    return __mono_method_get_object__(domain, method, refclass);
}

typedef MonoMethodSignature* (*type_mono_method_signature)(MonoMethod * method);
type_mono_method_signature __mono_method_signature__;
extern "C" EXPORT_API MonoMethodSignature* mono_method_signature(MonoMethod * method)
{
    log_function_usage("mono_method_signature");
    if (!__mono_method_signature__)
        __mono_method_signature__ = (type_mono_method_signature)load_mono_function("mono_method_signature");
    return __mono_method_signature__(method);
}

typedef MonoType* (*type_mono_signature_get_params)(MonoMethodSignature * sig, gpointer * iter);
type_mono_signature_get_params __mono_signature_get_params__;
extern "C" EXPORT_API MonoType* mono_signature_get_params(MonoMethodSignature * sig, gpointer * iter)
{
    log_function_usage("mono_signature_get_params");
    if (!__mono_signature_get_params__)
        __mono_signature_get_params__ = (type_mono_signature_get_params)load_mono_function("mono_signature_get_params");
    return __mono_signature_get_params__(sig, iter);
}

typedef MonoType* (*type_mono_signature_get_return_type)(MonoMethodSignature * sig);
type_mono_signature_get_return_type __mono_signature_get_return_type__;
extern "C" EXPORT_API MonoType* mono_signature_get_return_type(MonoMethodSignature * sig)
{
    log_function_usage("mono_signature_get_return_type");
    if (!__mono_signature_get_return_type__)
        __mono_signature_get_return_type__ = (type_mono_signature_get_return_type)load_mono_function("mono_signature_get_return_type");
    return __mono_signature_get_return_type__(sig);
}

typedef MonoType* (*type_mono_class_get_type)(MonoClass * klass);
type_mono_class_get_type __mono_class_get_type__;
extern "C" EXPORT_API MonoType* mono_class_get_type(MonoClass * klass)
{
    log_function_usage("mono_class_get_type");
    if (!__mono_class_get_type__)
        __mono_class_get_type__ = (type_mono_class_get_type)load_mono_function("mono_class_get_type");
    return __mono_class_get_type__(klass);
}

typedef void (*type_mono_debug_init)(int format);
type_mono_debug_init __mono_debug_init__;
extern "C" EXPORT_API void mono_debug_init(int format)
{
    log_function_usage("mono_debug_init");
    if (!__mono_debug_init__)
        __mono_debug_init__ = (type_mono_debug_init)load_mono_function("mono_debug_init");
    __mono_debug_init__(format);
}

typedef gboolean (*type_mono_is_debugger_attached)();
type_mono_is_debugger_attached __mono_is_debugger_attached__;
extern "C" EXPORT_API gboolean mono_is_debugger_attached()
{
    log_function_usage("mono_is_debugger_attached");
    if (!__mono_is_debugger_attached__)
        __mono_is_debugger_attached__ = (type_mono_is_debugger_attached)load_mono_function("mono_is_debugger_attached");
    return __mono_is_debugger_attached__();
}

typedef void (*type_mono_debug_open_image_from_memory)(MonoImage * image, const char *raw_contents, int size);
type_mono_debug_open_image_from_memory __mono_debug_open_image_from_memory__;
extern "C" EXPORT_API void mono_debug_open_image_from_memory(MonoImage * image, const char *raw_contents, int size)
{
    log_function_usage("mono_debug_open_image_from_memory");
    if (!__mono_debug_open_image_from_memory__)
        __mono_debug_open_image_from_memory__ = (type_mono_debug_open_image_from_memory)load_mono_function("mono_debug_open_image_from_memory");
    __mono_debug_open_image_from_memory__(image, raw_contents, size);
}

typedef guint32 (*type_mono_field_get_flags)(MonoClassField * field);
type_mono_field_get_flags __mono_field_get_flags__;
extern "C" EXPORT_API guint32 mono_field_get_flags(MonoClassField * field)
{
    log_function_usage("mono_field_get_flags");
    if (!__mono_field_get_flags__)
        __mono_field_get_flags__ = (type_mono_field_get_flags)load_mono_function("mono_field_get_flags");
    return __mono_field_get_flags__(field);
}

typedef MonoImage* (*type_mono_image_open_from_data_full)(const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only);
type_mono_image_open_from_data_full __mono_image_open_from_data_full__;
extern "C" EXPORT_API MonoImage* mono_image_open_from_data_full(const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only)
{
    log_function_usage("mono_image_open_from_data_full");
    if (!__mono_image_open_from_data_full__)
        __mono_image_open_from_data_full__ = (type_mono_image_open_from_data_full)load_mono_function("mono_image_open_from_data_full");
    return __mono_image_open_from_data_full__(data, data_len, need_copy, status, ref_only);
}

typedef MonoImage* (*type_mono_image_open_from_data_with_name)(char *data, guint32 data_len, gboolean need_copy, int *status, gboolean refonly, const char *name);
type_mono_image_open_from_data_with_name __mono_image_open_from_data_with_name__;
extern "C" EXPORT_API MonoImage* mono_image_open_from_data_with_name(char *data, guint32 data_len, gboolean need_copy, int *status, gboolean refonly, const char *name)
{
    log_function_usage("mono_image_open_from_data_with_name");
    if (!__mono_image_open_from_data_with_name__)
        __mono_image_open_from_data_with_name__ = (type_mono_image_open_from_data_with_name)load_mono_function("mono_image_open_from_data_with_name");
    return __mono_image_open_from_data_with_name__(data, data_len, need_copy, status, refonly, name);
}

typedef MonoAssembly * (*type_mono_assembly_load_from)(MonoImage * image, const char*fname, int *status);
type_mono_assembly_load_from __mono_assembly_load_from__;
extern "C" EXPORT_API MonoAssembly * mono_assembly_load_from(MonoImage * image, const char*fname, int *status)
{
    log_function_usage("mono_assembly_load_from");
    if (!__mono_assembly_load_from__)
        __mono_assembly_load_from__ = (type_mono_assembly_load_from)load_mono_function("mono_assembly_load_from");
    return __mono_assembly_load_from__(image, fname, status);
}

typedef gboolean (*type_mono_assembly_fill_assembly_name)(MonoImage * image, MonoAssemblyName * aname);
type_mono_assembly_fill_assembly_name __mono_assembly_fill_assembly_name__;
extern "C" EXPORT_API gboolean mono_assembly_fill_assembly_name(MonoImage * image, MonoAssemblyName * aname)
{
    log_function_usage("mono_assembly_fill_assembly_name");
    if (!__mono_assembly_fill_assembly_name__)
        __mono_assembly_fill_assembly_name__ = (type_mono_assembly_fill_assembly_name)load_mono_function("mono_assembly_fill_assembly_name");
    return __mono_assembly_fill_assembly_name__(image, aname);
}

typedef char* (*type_mono_stringify_assembly_name)(MonoAssemblyName * aname);
type_mono_stringify_assembly_name __mono_stringify_assembly_name__;
extern "C" EXPORT_API char* mono_stringify_assembly_name(MonoAssemblyName * aname)
{
    log_function_usage("mono_stringify_assembly_name");
    if (!__mono_stringify_assembly_name__)
        __mono_stringify_assembly_name__ = (type_mono_stringify_assembly_name)load_mono_function("mono_stringify_assembly_name");
    return __mono_stringify_assembly_name__(aname);
}

typedef int (*type_mono_assembly_name_parse)(const char* name, MonoAssemblyName * assembly);
type_mono_assembly_name_parse __mono_assembly_name_parse__;
extern "C" EXPORT_API int mono_assembly_name_parse(const char* name, MonoAssemblyName * assembly)
{
    log_function_usage("mono_assembly_name_parse");
    if (!__mono_assembly_name_parse__)
        __mono_assembly_name_parse__ = (type_mono_assembly_name_parse)load_mono_function("mono_assembly_name_parse");
    return __mono_assembly_name_parse__(name, assembly);
}

typedef MonoAssembly* (*type_mono_assembly_loaded)(MonoAssemblyName * aname);
type_mono_assembly_loaded __mono_assembly_loaded__;
extern "C" EXPORT_API MonoAssembly* mono_assembly_loaded(MonoAssemblyName * aname)
{
    log_function_usage("mono_assembly_loaded");
    if (!__mono_assembly_loaded__)
        __mono_assembly_loaded__ = (type_mono_assembly_loaded)load_mono_function("mono_assembly_loaded");
    return __mono_assembly_loaded__(aname);
}

typedef int (*type_mono_image_get_table_rows)(MonoImage * image, int table_id);
type_mono_image_get_table_rows __mono_image_get_table_rows__;
extern "C" EXPORT_API int mono_image_get_table_rows(MonoImage * image, int table_id)
{
    log_function_usage("mono_image_get_table_rows");
    if (!__mono_image_get_table_rows__)
        __mono_image_get_table_rows__ = (type_mono_image_get_table_rows)load_mono_function("mono_image_get_table_rows");
    return __mono_image_get_table_rows__(image, table_id);
}

typedef MonoClass* (*type_mono_unity_class_get)(MonoImage * image, guint32 type_token);
type_mono_unity_class_get __mono_unity_class_get__;
extern "C" EXPORT_API MonoClass* mono_unity_class_get(MonoImage * image, guint32 type_token)
{
    log_function_usage("mono_unity_class_get");
    if (!__mono_unity_class_get__)
        __mono_unity_class_get__ = (type_mono_unity_class_get)load_mono_function("mono_unity_class_get");
    return __mono_unity_class_get__(image, type_token);
}

typedef gboolean (*type_mono_metadata_signature_equal)(MonoMethodSignature * sig1, MonoMethodSignature * sig2);
type_mono_metadata_signature_equal __mono_metadata_signature_equal__;
extern "C" EXPORT_API gboolean mono_metadata_signature_equal(MonoMethodSignature * sig1, MonoMethodSignature * sig2)
{
    log_function_usage("mono_metadata_signature_equal");
    if (!__mono_metadata_signature_equal__)
        __mono_metadata_signature_equal__ = (type_mono_metadata_signature_equal)load_mono_function("mono_metadata_signature_equal");
    return __mono_metadata_signature_equal__(sig1, sig2);
}

typedef MonoObject * (*type_mono_value_box)(MonoDomain * domain, MonoClass * klass, gpointer val);
type_mono_value_box __mono_value_box__;
extern "C" EXPORT_API MonoObject * mono_value_box(MonoDomain * domain, MonoClass * klass, gpointer val)
{
    log_function_usage("mono_value_box");
    if (!__mono_value_box__)
        __mono_value_box__ = (type_mono_value_box)load_mono_function("mono_value_box");
    return __mono_value_box__(domain, klass, val);
}

typedef MonoImage* (*type_mono_class_get_image)(MonoClass * klass);
type_mono_class_get_image __mono_class_get_image__;
extern "C" EXPORT_API MonoImage* mono_class_get_image(MonoClass * klass)
{
    log_function_usage("mono_class_get_image");
    if (!__mono_class_get_image__)
        __mono_class_get_image__ = (type_mono_class_get_image)load_mono_function("mono_class_get_image");
    return __mono_class_get_image__(klass);
}

typedef char (*type_mono_signature_is_instance)(MonoMethodSignature * signature);
type_mono_signature_is_instance __mono_signature_is_instance__;
extern "C" EXPORT_API char mono_signature_is_instance(MonoMethodSignature * signature)
{
    log_function_usage("mono_signature_is_instance");
    if (!__mono_signature_is_instance__)
        __mono_signature_is_instance__ = (type_mono_signature_is_instance)load_mono_function("mono_signature_is_instance");
    return __mono_signature_is_instance__(signature);
}

typedef MonoMethod* (*type_mono_method_get_last_managed)();
type_mono_method_get_last_managed __mono_method_get_last_managed__;
extern "C" EXPORT_API MonoMethod* mono_method_get_last_managed()
{
    log_function_usage("mono_method_get_last_managed");
    if (!__mono_method_get_last_managed__)
        __mono_method_get_last_managed__ = (type_mono_method_get_last_managed)load_mono_function("mono_method_get_last_managed");
    return __mono_method_get_last_managed__();
}

typedef MonoClass* (*type_mono_get_enum_class)();
type_mono_get_enum_class __mono_get_enum_class__;
extern "C" EXPORT_API MonoClass* mono_get_enum_class()
{
    log_function_usage("mono_get_enum_class");
    if (!__mono_get_enum_class__)
        __mono_get_enum_class__ = (type_mono_get_enum_class)load_mono_function("mono_get_enum_class");
    return __mono_get_enum_class__();
}

typedef MonoType* (*type_mono_class_get_byref_type)(MonoClass * klass);
type_mono_class_get_byref_type __mono_class_get_byref_type__;
extern "C" EXPORT_API MonoType* mono_class_get_byref_type(MonoClass * klass)
{
    log_function_usage("mono_class_get_byref_type");
    if (!__mono_class_get_byref_type__)
        __mono_class_get_byref_type__ = (type_mono_class_get_byref_type)load_mono_function("mono_class_get_byref_type");
    return __mono_class_get_byref_type__(klass);
}

typedef void (*type_mono_field_static_get_value)(MonoVTable * vt, MonoClassField * field, void *value);
type_mono_field_static_get_value __mono_field_static_get_value__;
extern "C" EXPORT_API void mono_field_static_get_value(MonoVTable * vt, MonoClassField * field, void *value)
{
    log_function_usage("mono_field_static_get_value");
    if (!__mono_field_static_get_value__)
        __mono_field_static_get_value__ = (type_mono_field_static_get_value)load_mono_function("mono_field_static_get_value");
    __mono_field_static_get_value__(vt, field, value);
}

typedef void (*type_mono_unity_set_embeddinghostname)(const char* name);
type_mono_unity_set_embeddinghostname __mono_unity_set_embeddinghostname__;
extern "C" EXPORT_API void mono_unity_set_embeddinghostname(const char* name)
{
    log_function_usage("mono_unity_set_embeddinghostname");
    if (!__mono_unity_set_embeddinghostname__)
        __mono_unity_set_embeddinghostname__ = (type_mono_unity_set_embeddinghostname)load_mono_function("mono_unity_set_embeddinghostname");
    __mono_unity_set_embeddinghostname__(name);
}

typedef void (*type_mono_set_assemblies_path)(const char* name);
type_mono_set_assemblies_path __mono_set_assemblies_path__;
extern "C" EXPORT_API void mono_set_assemblies_path(const char* name)
{
    log_function_usage("mono_set_assemblies_path");
    if (!__mono_set_assemblies_path__)
        __mono_set_assemblies_path__ = (type_mono_set_assemblies_path)load_mono_function("mono_set_assemblies_path");
    __mono_set_assemblies_path__(name);
}

typedef guint32 (*type_mono_gchandle_new)(MonoObject * obj, gboolean pinned);
type_mono_gchandle_new __mono_gchandle_new__;
extern "C" EXPORT_API guint32 mono_gchandle_new(MonoObject * obj, gboolean pinned)
{
    log_function_usage("mono_gchandle_new");
    if (!__mono_gchandle_new__)
        __mono_gchandle_new__ = (type_mono_gchandle_new)load_mono_function("mono_gchandle_new");
    return __mono_gchandle_new__(obj, pinned);
}

typedef MonoObject* (*type_mono_gchandle_get_target)(guint32 gchandle);
type_mono_gchandle_get_target __mono_gchandle_get_target__;
extern "C" EXPORT_API MonoObject* mono_gchandle_get_target(guint32 gchandle)
{
    log_function_usage("mono_gchandle_get_target");
    if (!__mono_gchandle_get_target__)
        __mono_gchandle_get_target__ = (type_mono_gchandle_get_target)load_mono_function("mono_gchandle_get_target");
    return __mono_gchandle_get_target__(gchandle);
}

typedef guint32 (*type_mono_gchandle_new_weakref)(MonoObject * obj, gboolean track_resurrection);
type_mono_gchandle_new_weakref __mono_gchandle_new_weakref__;
extern "C" EXPORT_API guint32 mono_gchandle_new_weakref(MonoObject * obj, gboolean track_resurrection)
{
    log_function_usage("mono_gchandle_new_weakref");
    if (!__mono_gchandle_new_weakref__)
        __mono_gchandle_new_weakref__ = (type_mono_gchandle_new_weakref)load_mono_function("mono_gchandle_new_weakref");
    return __mono_gchandle_new_weakref__(obj, track_resurrection);
}

typedef gboolean (*type_mono_gchandle_is_in_domain)(guint32 gchandle, MonoDomain * domain);
type_mono_gchandle_is_in_domain __mono_gchandle_is_in_domain__;
extern "C" EXPORT_API gboolean mono_gchandle_is_in_domain(guint32 gchandle, MonoDomain * domain)
{
    log_function_usage("mono_gchandle_is_in_domain");
    if (!__mono_gchandle_is_in_domain__)
        __mono_gchandle_is_in_domain__ = (type_mono_gchandle_is_in_domain)load_mono_function("mono_gchandle_is_in_domain");
    return __mono_gchandle_is_in_domain__(gchandle, domain);
}

typedef MonoObject* (*type_mono_assembly_get_object)(MonoDomain * domain, MonoAssembly * assembly);
type_mono_assembly_get_object __mono_assembly_get_object__;
extern "C" EXPORT_API MonoObject* mono_assembly_get_object(MonoDomain * domain, MonoAssembly * assembly)
{
    log_function_usage("mono_assembly_get_object");
    if (!__mono_assembly_get_object__)
        __mono_assembly_get_object__ = (type_mono_assembly_get_object)load_mono_function("mono_assembly_get_object");
    return __mono_assembly_get_object__(domain, assembly);
}

typedef void (*type_mono_gchandle_free)(guint32 gchandle);
type_mono_gchandle_free __mono_gchandle_free__;
extern "C" EXPORT_API void mono_gchandle_free(guint32 gchandle)
{
    log_function_usage("mono_gchandle_free");
    if (!__mono_gchandle_free__)
        __mono_gchandle_free__ = (type_mono_gchandle_free)load_mono_function("mono_gchandle_free");
    __mono_gchandle_free__(gchandle);
}

typedef void (*type_mono_stack_walk)(MonoStackWalk func, gpointer user_data);
type_mono_stack_walk __mono_stack_walk__;
extern "C" EXPORT_API void mono_stack_walk(MonoStackWalk func, gpointer user_data)
{
    log_function_usage("mono_stack_walk");
    if (!__mono_stack_walk__)
        __mono_stack_walk__ = (type_mono_stack_walk)load_mono_function("mono_stack_walk");
    __mono_stack_walk__(func, user_data);
}

typedef char* (*type_mono_pmip)(void *ip);
type_mono_pmip __mono_pmip__;
extern "C" EXPORT_API char* mono_pmip(void *ip)
{
    log_function_usage("mono_pmip");
    if (!__mono_pmip__)
        __mono_pmip__ = (type_mono_pmip)load_mono_function("mono_pmip");
    return __mono_pmip__(ip);
}

typedef MonoObject* (*type_mono_runtime_delegate_invoke)(MonoObject * delegate, void **params, MonoException **exc);
type_mono_runtime_delegate_invoke __mono_runtime_delegate_invoke__;
extern "C" EXPORT_API MonoObject* mono_runtime_delegate_invoke(MonoObject * delegate, void **params, MonoException **exc)
{
    log_function_usage("mono_runtime_delegate_invoke");
    if (!__mono_runtime_delegate_invoke__)
        __mono_runtime_delegate_invoke__ = (type_mono_runtime_delegate_invoke)load_mono_function("mono_runtime_delegate_invoke");
    return __mono_runtime_delegate_invoke__(delegate, params, exc);
}

typedef MonoJitInfo* (*type_mono_jit_info_table_find)(MonoDomain * domain, void* ip);
type_mono_jit_info_table_find __mono_jit_info_table_find__;
extern "C" EXPORT_API MonoJitInfo* mono_jit_info_table_find(MonoDomain * domain, void* ip)
{
    log_function_usage("mono_jit_info_table_find");
    if (!__mono_jit_info_table_find__)
        __mono_jit_info_table_find__ = (type_mono_jit_info_table_find)load_mono_function("mono_jit_info_table_find");
    return __mono_jit_info_table_find__(domain, ip);
}

typedef MonoDebugSourceLocation* (*type_mono_debug_lookup_source_location)(MonoMethod * method, guint32 address, MonoDomain * domain);
type_mono_debug_lookup_source_location __mono_debug_lookup_source_location__;
extern "C" EXPORT_API MonoDebugSourceLocation* mono_debug_lookup_source_location(MonoMethod * method, guint32 address, MonoDomain * domain)
{
    log_function_usage("mono_debug_lookup_source_location");
    if (!__mono_debug_lookup_source_location__)
        __mono_debug_lookup_source_location__ = (type_mono_debug_lookup_source_location)load_mono_function("mono_debug_lookup_source_location");
    return __mono_debug_lookup_source_location__(method, address, domain);
}

typedef void (*type_mono_debug_free_source_location)(MonoDebugSourceLocation * location);
type_mono_debug_free_source_location __mono_debug_free_source_location__;
extern "C" EXPORT_API void mono_debug_free_source_location(MonoDebugSourceLocation * location)
{
    log_function_usage("mono_debug_free_source_location");
    if (!__mono_debug_free_source_location__)
        __mono_debug_free_source_location__ = (type_mono_debug_free_source_location)load_mono_function("mono_debug_free_source_location");
    __mono_debug_free_source_location__(location);
}

typedef MonoProperty* (*type_mono_class_get_properties)(MonoClass * klass, gpointer * iter);
type_mono_class_get_properties __mono_class_get_properties__;
extern "C" EXPORT_API MonoProperty* mono_class_get_properties(MonoClass * klass, gpointer * iter)
{
    log_function_usage("mono_class_get_properties");
    if (!__mono_class_get_properties__)
        __mono_class_get_properties__ = (type_mono_class_get_properties)load_mono_function("mono_class_get_properties");
    return __mono_class_get_properties__(klass, iter);
}

typedef MonoMethod* (*type_mono_property_get_get_method)(MonoProperty * prop);
type_mono_property_get_get_method __mono_property_get_get_method__;
extern "C" EXPORT_API MonoMethod* mono_property_get_get_method(MonoProperty * prop)
{
    log_function_usage("mono_property_get_get_method");
    if (!__mono_property_get_get_method__)
        __mono_property_get_get_method__ = (type_mono_property_get_get_method)load_mono_function("mono_property_get_get_method");
    return __mono_property_get_get_method__(prop);
}

typedef MonoObject * (*type_mono_object_new_alloc_specific)(MonoVTable * vtable);
type_mono_object_new_alloc_specific __mono_object_new_alloc_specific__;
extern "C" EXPORT_API MonoObject * mono_object_new_alloc_specific(MonoVTable * vtable)
{
    log_function_usage("mono_object_new_alloc_specific");
    if (!__mono_object_new_alloc_specific__)
        __mono_object_new_alloc_specific__ = (type_mono_object_new_alloc_specific)load_mono_function("mono_object_new_alloc_specific");
    return __mono_object_new_alloc_specific__(vtable);
}

typedef MonoObject * (*type_mono_object_new_specific)(MonoVTable * vtable);
type_mono_object_new_specific __mono_object_new_specific__;
extern "C" EXPORT_API MonoObject * mono_object_new_specific(MonoVTable * vtable)
{
    log_function_usage("mono_object_new_specific");
    if (!__mono_object_new_specific__)
        __mono_object_new_specific__ = (type_mono_object_new_specific)load_mono_function("mono_object_new_specific");
    return __mono_object_new_specific__(vtable);
}

typedef void (*type_mono_gc_collect)(int generation);
type_mono_gc_collect __mono_gc_collect__;
extern "C" EXPORT_API void mono_gc_collect(int generation)
{
    log_function_usage("mono_gc_collect");
    if (!__mono_gc_collect__)
        __mono_gc_collect__ = (type_mono_gc_collect)load_mono_function("mono_gc_collect");
    __mono_gc_collect__(generation);
}

typedef int (*type_mono_gc_max_generation)();
type_mono_gc_max_generation __mono_gc_max_generation__;
extern "C" EXPORT_API int mono_gc_max_generation()
{
    log_function_usage("mono_gc_max_generation");
    if (!__mono_gc_max_generation__)
        __mono_gc_max_generation__ = (type_mono_gc_max_generation)load_mono_function("mono_gc_max_generation");
    return __mono_gc_max_generation__();
}

typedef gint64 (*type_mono_gc_get_used_size)();
type_mono_gc_get_used_size __mono_gc_get_used_size__;
extern "C" EXPORT_API gint64 mono_gc_get_used_size()
{
    log_function_usage("mono_gc_get_used_size");
    if (!__mono_gc_get_used_size__)
        __mono_gc_get_used_size__ = (type_mono_gc_get_used_size)load_mono_function("mono_gc_get_used_size");
    return __mono_gc_get_used_size__();
}

typedef gint64 (*type_mono_gc_get_heap_size)();
type_mono_gc_get_heap_size __mono_gc_get_heap_size__;
extern "C" EXPORT_API gint64 mono_gc_get_heap_size()
{
    log_function_usage("mono_gc_get_heap_size");
    if (!__mono_gc_get_heap_size__)
        __mono_gc_get_heap_size__ = (type_mono_gc_get_heap_size)load_mono_function("mono_gc_get_heap_size");
    return __mono_gc_get_heap_size__();
}

typedef void (*type_mono_gc_wbarrier_generic_store)(gpointer ptr, MonoObject * value);
type_mono_gc_wbarrier_generic_store __mono_gc_wbarrier_generic_store__;
extern "C" EXPORT_API void mono_gc_wbarrier_generic_store(gpointer ptr, MonoObject * value)
{
    log_function_usage("mono_gc_wbarrier_generic_store");
    if (!__mono_gc_wbarrier_generic_store__)
        __mono_gc_wbarrier_generic_store__ = (type_mono_gc_wbarrier_generic_store)load_mono_function("mono_gc_wbarrier_generic_store");
    __mono_gc_wbarrier_generic_store__(ptr, value);
}

typedef MonoAssembly* (*type_mono_image_get_assembly)(MonoImage * image);
type_mono_image_get_assembly __mono_image_get_assembly__;
extern "C" EXPORT_API MonoAssembly* mono_image_get_assembly(MonoImage * image)
{
    log_function_usage("mono_image_get_assembly");
    if (!__mono_image_get_assembly__)
        __mono_image_get_assembly__ = (type_mono_image_get_assembly)load_mono_function("mono_image_get_assembly");
    return __mono_image_get_assembly__(image);
}

typedef MonoAssembly* (*type_mono_assembly_open)(const char *filename, int *status);
type_mono_assembly_open __mono_assembly_open__;
extern "C" EXPORT_API MonoAssembly* mono_assembly_open(const char *filename, int *status)
{
    log_function_usage("mono_assembly_open");
    if (!__mono_assembly_open__)
        __mono_assembly_open__ = (type_mono_assembly_open)load_mono_function("mono_assembly_open");
    return __mono_assembly_open__(filename, status);
}

typedef gboolean (*type_mono_class_is_enum)(MonoClass * klass);
type_mono_class_is_enum __mono_class_is_enum__;
extern "C" EXPORT_API gboolean mono_class_is_enum(MonoClass * klass)
{
    log_function_usage("mono_class_is_enum");
    if (!__mono_class_is_enum__)
        __mono_class_is_enum__ = (type_mono_class_is_enum)load_mono_function("mono_class_is_enum");
    return __mono_class_is_enum__(klass);
}

typedef MonoType* (*type_mono_class_enum_basetype)(MonoClass * klass);
type_mono_class_enum_basetype __mono_class_enum_basetype__;
extern "C" EXPORT_API MonoType* mono_class_enum_basetype(MonoClass * klass)
{
    log_function_usage("mono_class_enum_basetype");
    if (!__mono_class_enum_basetype__)
        __mono_class_enum_basetype__ = (type_mono_class_enum_basetype)load_mono_function("mono_class_enum_basetype");
    return __mono_class_enum_basetype__(klass);
}

typedef gint32 (*type_mono_class_instance_size)(MonoClass * klass);
type_mono_class_instance_size __mono_class_instance_size__;
extern "C" EXPORT_API gint32 mono_class_instance_size(MonoClass * klass)
{
    log_function_usage("mono_class_instance_size");
    if (!__mono_class_instance_size__)
        __mono_class_instance_size__ = (type_mono_class_instance_size)load_mono_function("mono_class_instance_size");
    return __mono_class_instance_size__(klass);
}

typedef guint32 (*type_mono_object_get_size)(MonoObject * obj);
type_mono_object_get_size __mono_object_get_size__;
extern "C" EXPORT_API guint32 mono_object_get_size(MonoObject * obj)
{
    log_function_usage("mono_object_get_size");
    if (!__mono_object_get_size__)
        __mono_object_get_size__ = (type_mono_object_get_size)load_mono_function("mono_object_get_size");
    return __mono_object_get_size__(obj);
}

typedef guint32 (*type_mono_class_get_type_token)(MonoClass * klass);
type_mono_class_get_type_token __mono_class_get_type_token__;
extern "C" EXPORT_API guint32 mono_class_get_type_token(MonoClass * klass)
{
    log_function_usage("mono_class_get_type_token");
    if (!__mono_class_get_type_token__)
        __mono_class_get_type_token__ = (type_mono_class_get_type_token)load_mono_function("mono_class_get_type_token");
    return __mono_class_get_type_token__(klass);
}

typedef const char* (*type_mono_image_get_filename)(MonoImage * image);
type_mono_image_get_filename __mono_image_get_filename__;
extern "C" EXPORT_API const char* mono_image_get_filename(MonoImage * image)
{
    log_function_usage("mono_image_get_filename");
    if (!__mono_image_get_filename__)
        __mono_image_get_filename__ = (type_mono_image_get_filename)load_mono_function("mono_image_get_filename");
    return __mono_image_get_filename__(image);
}

typedef MonoAssembly* (*type_mono_assembly_load_from_full)(MonoImage * image, const char *fname, int *status, gboolean refonly);
type_mono_assembly_load_from_full __mono_assembly_load_from_full__;
extern "C" EXPORT_API MonoAssembly* mono_assembly_load_from_full(MonoImage * image, const char *fname, int *status, gboolean refonly)
{
    log_function_usage("mono_assembly_load_from_full");
    if (!__mono_assembly_load_from_full__)
        __mono_assembly_load_from_full__ = (type_mono_assembly_load_from_full)load_mono_function("mono_assembly_load_from_full");
    return __mono_assembly_load_from_full__(image, fname, status, refonly);
}

typedef MonoClass* (*type_mono_class_get_interfaces)(MonoClass * klass, gpointer * iter);
type_mono_class_get_interfaces __mono_class_get_interfaces__;
extern "C" EXPORT_API MonoClass* mono_class_get_interfaces(MonoClass * klass, gpointer * iter)
{
    log_function_usage("mono_class_get_interfaces");
    if (!__mono_class_get_interfaces__)
        __mono_class_get_interfaces__ = (type_mono_class_get_interfaces)load_mono_function("mono_class_get_interfaces");
    return __mono_class_get_interfaces__(klass, iter);
}

typedef void (*type_mono_assembly_close)(MonoAssembly * assembly);
type_mono_assembly_close __mono_assembly_close__;
extern "C" EXPORT_API void mono_assembly_close(MonoAssembly * assembly)
{
    log_function_usage("mono_assembly_close");
    if (!__mono_assembly_close__)
        __mono_assembly_close__ = (type_mono_assembly_close)load_mono_function("mono_assembly_close");
    __mono_assembly_close__(assembly);
}

typedef MonoProperty* (*type_mono_class_get_property_from_name)(MonoClass * klass, const char *name);
type_mono_class_get_property_from_name __mono_class_get_property_from_name__;
extern "C" EXPORT_API MonoProperty* mono_class_get_property_from_name(MonoClass * klass, const char *name)
{
    log_function_usage("mono_class_get_property_from_name");
    if (!__mono_class_get_property_from_name__)
        __mono_class_get_property_from_name__ = (type_mono_class_get_property_from_name)load_mono_function("mono_class_get_property_from_name");
    return __mono_class_get_property_from_name__(klass, name);
}

typedef MonoMethod* (*type_mono_class_get_method_from_name)(MonoClass * klass, const char *name, int param_count);
type_mono_class_get_method_from_name __mono_class_get_method_from_name__;
extern "C" EXPORT_API MonoMethod* mono_class_get_method_from_name(MonoClass * klass, const char *name, int param_count)
{
    log_function_usage("mono_class_get_method_from_name");
    if (!__mono_class_get_method_from_name__)
        __mono_class_get_method_from_name__ = (type_mono_class_get_method_from_name)load_mono_function("mono_class_get_method_from_name");
    return __mono_class_get_method_from_name__(klass, name, param_count);
}

typedef MonoClass* (*type_mono_class_from_mono_type)(MonoType * image);
type_mono_class_from_mono_type __mono_class_from_mono_type__;
extern "C" EXPORT_API MonoClass* mono_class_from_mono_type(MonoType * image)
{
    log_function_usage("mono_class_from_mono_type");
    if (!__mono_class_from_mono_type__)
        __mono_class_from_mono_type__ = (type_mono_class_from_mono_type)load_mono_function("mono_class_from_mono_type");
    return __mono_class_from_mono_type__(image);
}

typedef int (*type_mono_class_get_rank)(MonoClass * klass);
type_mono_class_get_rank __mono_class_get_rank__;
extern "C" EXPORT_API int mono_class_get_rank(MonoClass * klass)
{
    log_function_usage("mono_class_get_rank");
    if (!__mono_class_get_rank__)
        __mono_class_get_rank__ = (type_mono_class_get_rank)load_mono_function("mono_class_get_rank");
    return __mono_class_get_rank__(klass);
}

typedef MonoClass* (*type_mono_class_get_element_class)(MonoClass * klass);
type_mono_class_get_element_class __mono_class_get_element_class__;
extern "C" EXPORT_API MonoClass* mono_class_get_element_class(MonoClass * klass)
{
    log_function_usage("mono_class_get_element_class");
    if (!__mono_class_get_element_class__)
        __mono_class_get_element_class__ = (type_mono_class_get_element_class)load_mono_function("mono_class_get_element_class");
    return __mono_class_get_element_class__(klass);
}

typedef gboolean (*type_mono_unity_class_is_interface)(MonoClass * klass);
type_mono_unity_class_is_interface __mono_unity_class_is_interface__;
extern "C" EXPORT_API gboolean mono_unity_class_is_interface(MonoClass * klass)
{
    log_function_usage("mono_unity_class_is_interface");
    if (!__mono_unity_class_is_interface__)
        __mono_unity_class_is_interface__ = (type_mono_unity_class_is_interface)load_mono_function("mono_unity_class_is_interface");
    return __mono_unity_class_is_interface__(klass);
}

typedef gboolean (*type_mono_unity_class_is_abstract)(MonoClass * klass);
type_mono_unity_class_is_abstract __mono_unity_class_is_abstract__;
extern "C" EXPORT_API gboolean mono_unity_class_is_abstract(MonoClass * klass)
{
    log_function_usage("mono_unity_class_is_abstract");
    if (!__mono_unity_class_is_abstract__)
        __mono_unity_class_is_abstract__ = (type_mono_unity_class_is_abstract)load_mono_function("mono_unity_class_is_abstract");
    return __mono_unity_class_is_abstract__(klass);
}

typedef int (*type_mono_array_element_size)(MonoClass * classOfArray);
type_mono_array_element_size __mono_array_element_size__;
extern "C" EXPORT_API int mono_array_element_size(MonoClass * classOfArray)
{
    log_function_usage("mono_array_element_size");
    if (!__mono_array_element_size__)
        __mono_array_element_size__ = (type_mono_array_element_size)load_mono_function("mono_array_element_size");
    return __mono_array_element_size__(classOfArray);
}

typedef gboolean (*type_mono_domain_set)(MonoDomain * domain, gboolean force);
type_mono_domain_set __mono_domain_set__;
extern "C" EXPORT_API gboolean mono_domain_set(MonoDomain * domain, gboolean force)
{
    log_function_usage("mono_domain_set");
    if (!__mono_domain_set__)
        __mono_domain_set__ = (type_mono_domain_set)load_mono_function("mono_domain_set");
    return __mono_domain_set__(domain, force);
}

typedef void (*type_mono_unity_domain_set_config)(MonoDomain * domain, const char *base_dir, const char *config_file_name);
type_mono_unity_domain_set_config __mono_unity_domain_set_config__;
extern "C" EXPORT_API void mono_unity_domain_set_config(MonoDomain * domain, const char *base_dir, const char *config_file_name)
{
    log_function_usage("mono_unity_domain_set_config");
    if (!__mono_unity_domain_set_config__)
        __mono_unity_domain_set_config__ = (type_mono_unity_domain_set_config)load_mono_function("mono_unity_domain_set_config");
    __mono_unity_domain_set_config__(domain, base_dir, config_file_name);
}

typedef void (*type_mono_thread_push_appdomain_ref)(MonoDomain * domain);
type_mono_thread_push_appdomain_ref __mono_thread_push_appdomain_ref__;
extern "C" EXPORT_API void mono_thread_push_appdomain_ref(MonoDomain * domain)
{
    log_function_usage("mono_thread_push_appdomain_ref");
    if (!__mono_thread_push_appdomain_ref__)
        __mono_thread_push_appdomain_ref__ = (type_mono_thread_push_appdomain_ref)load_mono_function("mono_thread_push_appdomain_ref");
    __mono_thread_push_appdomain_ref__(domain);
}

typedef void (*type_mono_thread_pop_appdomain_ref)();
type_mono_thread_pop_appdomain_ref __mono_thread_pop_appdomain_ref__;
extern "C" EXPORT_API void mono_thread_pop_appdomain_ref()
{
    log_function_usage("mono_thread_pop_appdomain_ref");
    if (!__mono_thread_pop_appdomain_ref__)
        __mono_thread_pop_appdomain_ref__ = (type_mono_thread_pop_appdomain_ref)load_mono_function("mono_thread_pop_appdomain_ref");
    __mono_thread_pop_appdomain_ref__();
}

typedef int (*type_mono_runtime_exec_main)(MonoMethod * method, MonoArray * args, MonoObject **exc);
type_mono_runtime_exec_main __mono_runtime_exec_main__;
extern "C" EXPORT_API int mono_runtime_exec_main(MonoMethod * method, MonoArray * args, MonoObject **exc)
{
    log_function_usage("mono_runtime_exec_main");
    if (!__mono_runtime_exec_main__)
        __mono_runtime_exec_main__ = (type_mono_runtime_exec_main)load_mono_function("mono_runtime_exec_main");
    return __mono_runtime_exec_main__(method, args, exc);
}

typedef MonoImage* (*type_mono_get_corlib)();
type_mono_get_corlib __mono_get_corlib__;
extern "C" EXPORT_API MonoImage* mono_get_corlib()
{
    log_function_usage("mono_get_corlib");
    if (!__mono_get_corlib__)
        __mono_get_corlib__ = (type_mono_get_corlib)load_mono_function("mono_get_corlib");
    return __mono_get_corlib__();
}

typedef MonoClassField* (*type_mono_class_get_field_from_name)(MonoClass * klass, const char *name);
type_mono_class_get_field_from_name __mono_class_get_field_from_name__;
extern "C" EXPORT_API MonoClassField* mono_class_get_field_from_name(MonoClass * klass, const char *name)
{
    log_function_usage("mono_class_get_field_from_name");
    if (!__mono_class_get_field_from_name__)
        __mono_class_get_field_from_name__ = (type_mono_class_get_field_from_name)load_mono_function("mono_class_get_field_from_name");
    return __mono_class_get_field_from_name__(klass, name);
}

typedef guint32 (*type_mono_class_get_flags)(MonoClass * klass);
type_mono_class_get_flags __mono_class_get_flags__;
extern "C" EXPORT_API guint32 mono_class_get_flags(MonoClass * klass)
{
    log_function_usage("mono_class_get_flags");
    if (!__mono_class_get_flags__)
        __mono_class_get_flags__ = (type_mono_class_get_flags)load_mono_function("mono_class_get_flags");
    return __mono_class_get_flags__(klass);
}

typedef int (*type_mono_parse_default_optimizations)(const char* p);
type_mono_parse_default_optimizations __mono_parse_default_optimizations__;
extern "C" EXPORT_API int mono_parse_default_optimizations(const char* p)
{
    log_function_usage("mono_parse_default_optimizations");
    if (!__mono_parse_default_optimizations__)
        __mono_parse_default_optimizations__ = (type_mono_parse_default_optimizations)load_mono_function("mono_parse_default_optimizations");
    return __mono_parse_default_optimizations__(p);
}

typedef void (*type_mono_set_defaults)(int verbose_level, guint32 opts);
type_mono_set_defaults __mono_set_defaults__;
extern "C" EXPORT_API void mono_set_defaults(int verbose_level, guint32 opts)
{
    log_function_usage("mono_set_defaults");
    if (!__mono_set_defaults__)
        __mono_set_defaults__ = (type_mono_set_defaults)load_mono_function("mono_set_defaults");
    __mono_set_defaults__(verbose_level, opts);
}

typedef void (*type_mono_config_parse)(const char *filename);
type_mono_config_parse __mono_config_parse__;
extern "C" EXPORT_API void mono_config_parse(const char *filename)
{
    log_function_usage("mono_config_parse");
    if (!__mono_config_parse__)
        __mono_config_parse__ = (type_mono_config_parse)load_mono_function("mono_config_parse");
    __mono_config_parse__(filename);
}

typedef void (*type_mono_set_dirs)(const char *assembly_dir, const char *config_dir);
type_mono_set_dirs __mono_set_dirs__;
extern "C" EXPORT_API void mono_set_dirs(const char *assembly_dir, const char *config_dir)
{
    log_function_usage("mono_set_dirs");
    if (!__mono_set_dirs__)
        __mono_set_dirs__ = (type_mono_set_dirs)load_mono_function("mono_set_dirs");
    __mono_set_dirs__(assembly_dir, config_dir);
}

typedef void (*type_mono_set_break_policy)(MonoBreakPolicyFunc policy_callback);
type_mono_set_break_policy __mono_set_break_policy__;
extern "C" EXPORT_API void mono_set_break_policy(MonoBreakPolicyFunc policy_callback)
{
    log_function_usage("mono_set_break_policy");
    if (!__mono_set_break_policy__)
        __mono_set_break_policy__ = (type_mono_set_break_policy)load_mono_function("mono_set_break_policy");
    __mono_set_break_policy__(policy_callback);
}

typedef void (*type_mono_jit_parse_options)(int argc, char * argv[]);
type_mono_jit_parse_options __mono_jit_parse_options__;
extern "C" EXPORT_API void mono_jit_parse_options(int argc, char * argv[])
{
    log_function_usage("mono_jit_parse_options");
    if (!__mono_jit_parse_options__)
        __mono_jit_parse_options__ = (type_mono_jit_parse_options)load_mono_function("mono_jit_parse_options");
    __mono_jit_parse_options__(argc, argv);
}

typedef gpointer (*type_mono_object_unbox)(MonoObject * o);
type_mono_object_unbox __mono_object_unbox__;
extern "C" EXPORT_API gpointer mono_object_unbox(MonoObject * o)
{
    log_function_usage("mono_object_unbox");
    if (!__mono_object_unbox__)
        __mono_object_unbox__ = (type_mono_object_unbox)load_mono_function("mono_object_unbox");
    return __mono_object_unbox__(o);
}

typedef MonoObject* (*type_mono_custom_attrs_get_attr)(MonoCustomAttrInfo * ainfo, MonoClass * attr_klass);
type_mono_custom_attrs_get_attr __mono_custom_attrs_get_attr__;
extern "C" EXPORT_API MonoObject* mono_custom_attrs_get_attr(MonoCustomAttrInfo * ainfo, MonoClass * attr_klass)
{
    log_function_usage("mono_custom_attrs_get_attr");
    if (!__mono_custom_attrs_get_attr__)
        __mono_custom_attrs_get_attr__ = (type_mono_custom_attrs_get_attr)load_mono_function("mono_custom_attrs_get_attr");
    return __mono_custom_attrs_get_attr__(ainfo, attr_klass);
}

typedef MonoArray* (*type_mono_custom_attrs_construct)(MonoCustomAttrInfo * cinfo);
type_mono_custom_attrs_construct __mono_custom_attrs_construct__;
extern "C" EXPORT_API MonoArray* mono_custom_attrs_construct(MonoCustomAttrInfo * cinfo)
{
    log_function_usage("mono_custom_attrs_construct");
    if (!__mono_custom_attrs_construct__)
        __mono_custom_attrs_construct__ = (type_mono_custom_attrs_construct)load_mono_function("mono_custom_attrs_construct");
    return __mono_custom_attrs_construct__(cinfo);
}

typedef gboolean (*type_mono_custom_attrs_has_attr)(MonoCustomAttrInfo * ainfo, MonoClass * attr_klass);
type_mono_custom_attrs_has_attr __mono_custom_attrs_has_attr__;
extern "C" EXPORT_API gboolean mono_custom_attrs_has_attr(MonoCustomAttrInfo * ainfo, MonoClass * attr_klass)
{
    log_function_usage("mono_custom_attrs_has_attr");
    if (!__mono_custom_attrs_has_attr__)
        __mono_custom_attrs_has_attr__ = (type_mono_custom_attrs_has_attr)load_mono_function("mono_custom_attrs_has_attr");
    return __mono_custom_attrs_has_attr__(ainfo, attr_klass);
}

typedef MonoCustomAttrInfo* (*type_mono_custom_attrs_from_field)(MonoClass * klass, MonoClassField * field);
type_mono_custom_attrs_from_field __mono_custom_attrs_from_field__;
extern "C" EXPORT_API MonoCustomAttrInfo* mono_custom_attrs_from_field(MonoClass * klass, MonoClassField * field)
{
    log_function_usage("mono_custom_attrs_from_field");
    if (!__mono_custom_attrs_from_field__)
        __mono_custom_attrs_from_field__ = (type_mono_custom_attrs_from_field)load_mono_function("mono_custom_attrs_from_field");
    return __mono_custom_attrs_from_field__(klass, field);
}

typedef MonoCustomAttrInfo* (*type_mono_custom_attrs_from_method)(MonoMethod * method);
type_mono_custom_attrs_from_method __mono_custom_attrs_from_method__;
extern "C" EXPORT_API MonoCustomAttrInfo* mono_custom_attrs_from_method(MonoMethod * method)
{
    log_function_usage("mono_custom_attrs_from_method");
    if (!__mono_custom_attrs_from_method__)
        __mono_custom_attrs_from_method__ = (type_mono_custom_attrs_from_method)load_mono_function("mono_custom_attrs_from_method");
    return __mono_custom_attrs_from_method__(method);
}

typedef MonoCustomAttrInfo* (*type_mono_custom_attrs_from_class)(MonoClass * klass);
type_mono_custom_attrs_from_class __mono_custom_attrs_from_class__;
extern "C" EXPORT_API MonoCustomAttrInfo* mono_custom_attrs_from_class(MonoClass * klass)
{
    log_function_usage("mono_custom_attrs_from_class");
    if (!__mono_custom_attrs_from_class__)
        __mono_custom_attrs_from_class__ = (type_mono_custom_attrs_from_class)load_mono_function("mono_custom_attrs_from_class");
    return __mono_custom_attrs_from_class__(klass);
}

typedef MonoCustomAttrInfo* (*type_mono_custom_attrs_from_assembly)(MonoAssembly * assembly);
type_mono_custom_attrs_from_assembly __mono_custom_attrs_from_assembly__;
extern "C" EXPORT_API MonoCustomAttrInfo* mono_custom_attrs_from_assembly(MonoAssembly * assembly)
{
    log_function_usage("mono_custom_attrs_from_assembly");
    if (!__mono_custom_attrs_from_assembly__)
        __mono_custom_attrs_from_assembly__ = (type_mono_custom_attrs_from_assembly)load_mono_function("mono_custom_attrs_from_assembly");
    return __mono_custom_attrs_from_assembly__(assembly);
}

typedef MonoArray* (*type_mono_reflection_get_custom_attrs_by_type)(MonoObject * object, MonoClass * klass);
type_mono_reflection_get_custom_attrs_by_type __mono_reflection_get_custom_attrs_by_type__;
extern "C" EXPORT_API MonoArray* mono_reflection_get_custom_attrs_by_type(MonoObject * object, MonoClass * klass)
{
    log_function_usage("mono_reflection_get_custom_attrs_by_type");
    if (!__mono_reflection_get_custom_attrs_by_type__)
        __mono_reflection_get_custom_attrs_by_type__ = (type_mono_reflection_get_custom_attrs_by_type)load_mono_function("mono_reflection_get_custom_attrs_by_type");
    return __mono_reflection_get_custom_attrs_by_type__(object, klass);
}

typedef void (*type_mono_custom_attrs_free)(MonoCustomAttrInfo * attr);
type_mono_custom_attrs_free __mono_custom_attrs_free__;
extern "C" EXPORT_API void mono_custom_attrs_free(MonoCustomAttrInfo * attr)
{
    log_function_usage("mono_custom_attrs_free");
    if (!__mono_custom_attrs_free__)
        __mono_custom_attrs_free__ = (type_mono_custom_attrs_free)load_mono_function("mono_custom_attrs_free");
    __mono_custom_attrs_free__(attr);
}

typedef MonoException* (*type_mono_unity_loader_get_last_error_and_error_prepare_exception)();
type_mono_unity_loader_get_last_error_and_error_prepare_exception __mono_unity_loader_get_last_error_and_error_prepare_exception__;
extern "C" EXPORT_API MonoException* mono_unity_loader_get_last_error_and_error_prepare_exception()
{
    log_function_usage("mono_unity_loader_get_last_error_and_error_prepare_exception");
    if (!__mono_unity_loader_get_last_error_and_error_prepare_exception__)
        __mono_unity_loader_get_last_error_and_error_prepare_exception__ = (type_mono_unity_loader_get_last_error_and_error_prepare_exception)load_mono_function("mono_unity_loader_get_last_error_and_error_prepare_exception");
    return __mono_unity_loader_get_last_error_and_error_prepare_exception__();
}

typedef MonoDlFallbackHandler* (*type_mono_dl_fallback_register)(MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data);
type_mono_dl_fallback_register __mono_dl_fallback_register__;
extern "C" EXPORT_API MonoDlFallbackHandler* mono_dl_fallback_register(MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    log_function_usage("mono_dl_fallback_register");
    if (!__mono_dl_fallback_register__)
        __mono_dl_fallback_register__ = (type_mono_dl_fallback_register)load_mono_function("mono_dl_fallback_register");
    return __mono_dl_fallback_register__(load_func, symbol_func, close_func, user_data);
}

typedef void (*type_mono_dl_fallback_unregister)(MonoDlFallbackHandler * handler);
type_mono_dl_fallback_unregister __mono_dl_fallback_unregister__;
extern "C" EXPORT_API void mono_dl_fallback_unregister(MonoDlFallbackHandler * handler)
{
    log_function_usage("mono_dl_fallback_unregister");
    if (!__mono_dl_fallback_unregister__)
        __mono_dl_fallback_unregister__ = (type_mono_dl_fallback_unregister)load_mono_function("mono_dl_fallback_unregister");
    __mono_dl_fallback_unregister__(handler);
}

typedef void (*type_mono_unity_set_vprintf_func)(vprintf_func func);
type_mono_unity_set_vprintf_func __mono_unity_set_vprintf_func__;
extern "C" EXPORT_API void mono_unity_set_vprintf_func(vprintf_func func)
{
    log_function_usage("mono_unity_set_vprintf_func");
    if (!__mono_unity_set_vprintf_func__)
        __mono_unity_set_vprintf_func__ = (type_mono_unity_set_vprintf_func)load_mono_function("mono_unity_set_vprintf_func");
    __mono_unity_set_vprintf_func__(func);
}

typedef void (*type_mono_unity_liveness_stop_gc_world)();
type_mono_unity_liveness_stop_gc_world __mono_unity_liveness_stop_gc_world__;
extern "C" EXPORT_API void mono_unity_liveness_stop_gc_world()
{
    log_function_usage("mono_unity_liveness_stop_gc_world");
    if (!__mono_unity_liveness_stop_gc_world__)
        __mono_unity_liveness_stop_gc_world__ = (type_mono_unity_liveness_stop_gc_world)load_mono_function("mono_unity_liveness_stop_gc_world");
    __mono_unity_liveness_stop_gc_world__();
}

typedef void (*type_mono_unity_liveness_finalize)(void* state);
type_mono_unity_liveness_finalize __mono_unity_liveness_finalize__;
extern "C" EXPORT_API void mono_unity_liveness_finalize(void* state)
{
    log_function_usage("mono_unity_liveness_finalize");
    if (!__mono_unity_liveness_finalize__)
        __mono_unity_liveness_finalize__ = (type_mono_unity_liveness_finalize)load_mono_function("mono_unity_liveness_finalize");
    __mono_unity_liveness_finalize__(state);
}

typedef void (*type_mono_unity_liveness_start_gc_world)();
type_mono_unity_liveness_start_gc_world __mono_unity_liveness_start_gc_world__;
extern "C" EXPORT_API void mono_unity_liveness_start_gc_world()
{
    log_function_usage("mono_unity_liveness_start_gc_world");
    if (!__mono_unity_liveness_start_gc_world__)
        __mono_unity_liveness_start_gc_world__ = (type_mono_unity_liveness_start_gc_world)load_mono_function("mono_unity_liveness_start_gc_world");
    __mono_unity_liveness_start_gc_world__();
}

typedef void (*type_mono_unity_liveness_free_struct)(void* state);
type_mono_unity_liveness_free_struct __mono_unity_liveness_free_struct__;
extern "C" EXPORT_API void mono_unity_liveness_free_struct(void* state)
{
    log_function_usage("mono_unity_liveness_free_struct");
    if (!__mono_unity_liveness_free_struct__)
        __mono_unity_liveness_free_struct__ = (type_mono_unity_liveness_free_struct)load_mono_function("mono_unity_liveness_free_struct");
    __mono_unity_liveness_free_struct__(state);
}

typedef void* (*type_mono_unity_liveness_calculation_begin)(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata, mono_liveness_world_state_callback world_started_callback, mono_liveness_world_state_callback world_stopped_callback);
type_mono_unity_liveness_calculation_begin __mono_unity_liveness_calculation_begin__;
extern "C" EXPORT_API void* mono_unity_liveness_calculation_begin(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata, mono_liveness_world_state_callback world_started_callback, mono_liveness_world_state_callback world_stopped_callback)
{
    log_function_usage("mono_unity_liveness_calculation_begin");
    if (!__mono_unity_liveness_calculation_begin__)
        __mono_unity_liveness_calculation_begin__ = (type_mono_unity_liveness_calculation_begin)load_mono_function("mono_unity_liveness_calculation_begin");
    return __mono_unity_liveness_calculation_begin__(filter, max_object_count, callback, userdata, world_started_callback, world_stopped_callback);
}

typedef void (*type_mono_unity_liveness_calculation_end)(void* state);
type_mono_unity_liveness_calculation_end __mono_unity_liveness_calculation_end__;
extern "C" EXPORT_API void mono_unity_liveness_calculation_end(void* state)
{
    log_function_usage("mono_unity_liveness_calculation_end");
    if (!__mono_unity_liveness_calculation_end__)
        __mono_unity_liveness_calculation_end__ = (type_mono_unity_liveness_calculation_end)load_mono_function("mono_unity_liveness_calculation_end");
    __mono_unity_liveness_calculation_end__(state);
}

typedef void (*type_mono_unity_liveness_calculation_from_root)(MonoObject * root, void* state);
type_mono_unity_liveness_calculation_from_root __mono_unity_liveness_calculation_from_root__;
extern "C" EXPORT_API void mono_unity_liveness_calculation_from_root(MonoObject * root, void* state)
{
    log_function_usage("mono_unity_liveness_calculation_from_root");
    if (!__mono_unity_liveness_calculation_from_root__)
        __mono_unity_liveness_calculation_from_root__ = (type_mono_unity_liveness_calculation_from_root)load_mono_function("mono_unity_liveness_calculation_from_root");
    __mono_unity_liveness_calculation_from_root__(root, state);
}

typedef void (*type_mono_unity_liveness_calculation_from_statics)(void* state);
type_mono_unity_liveness_calculation_from_statics __mono_unity_liveness_calculation_from_statics__;
extern "C" EXPORT_API void mono_unity_liveness_calculation_from_statics(void* state)
{
    log_function_usage("mono_unity_liveness_calculation_from_statics");
    if (!__mono_unity_liveness_calculation_from_statics__)
        __mono_unity_liveness_calculation_from_statics__ = (type_mono_unity_liveness_calculation_from_statics)load_mono_function("mono_unity_liveness_calculation_from_statics");
    __mono_unity_liveness_calculation_from_statics__(state);
}

typedef MonoMethod* (*type_unity_mono_reflection_method_get_method)(MonoReflectionMethod * mrf);
type_unity_mono_reflection_method_get_method __unity_mono_reflection_method_get_method__;
extern "C" EXPORT_API MonoMethod* unity_mono_reflection_method_get_method(MonoReflectionMethod * mrf)
{
    log_function_usage("unity_mono_reflection_method_get_method");
    if (!__unity_mono_reflection_method_get_method__)
        __unity_mono_reflection_method_get_method__ = (type_unity_mono_reflection_method_get_method)load_mono_function("unity_mono_reflection_method_get_method");
    return __unity_mono_reflection_method_get_method__(mrf);
}

typedef void (*type_mono_profiler_install)(void *prof, MonoProfileFunc shutdown_callback);
type_mono_profiler_install __mono_profiler_install__;
extern "C" EXPORT_API void mono_profiler_install(void *prof, MonoProfileFunc shutdown_callback)
{
    log_function_usage("mono_profiler_install");
    if (!__mono_profiler_install__)
        __mono_profiler_install__ = (type_mono_profiler_install)load_mono_function("mono_profiler_install");
    __mono_profiler_install__(prof, shutdown_callback);
}

typedef void (*type_mono_profiler_set_events)(int events);
type_mono_profiler_set_events __mono_profiler_set_events__;
extern "C" EXPORT_API void mono_profiler_set_events(int events)
{
    log_function_usage("mono_profiler_set_events");
    if (!__mono_profiler_set_events__)
        __mono_profiler_set_events__ = (type_mono_profiler_set_events)load_mono_function("mono_profiler_set_events");
    __mono_profiler_set_events__(events);
}

typedef void (*type_mono_profiler_install_enter_leave)(MonoProfileMethodFunc enter, MonoProfileMethodFunc fleave);
type_mono_profiler_install_enter_leave __mono_profiler_install_enter_leave__;
extern "C" EXPORT_API void mono_profiler_install_enter_leave(MonoProfileMethodFunc enter, MonoProfileMethodFunc fleave)
{
    log_function_usage("mono_profiler_install_enter_leave");
    if (!__mono_profiler_install_enter_leave__)
        __mono_profiler_install_enter_leave__ = (type_mono_profiler_install_enter_leave)load_mono_function("mono_profiler_install_enter_leave");
    __mono_profiler_install_enter_leave__(enter, fleave);
}

typedef void (*type_mono_profiler_install_gc)(MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback);
type_mono_profiler_install_gc __mono_profiler_install_gc__;
extern "C" EXPORT_API void mono_profiler_install_gc(MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback)
{
    log_function_usage("mono_profiler_install_gc");
    if (!__mono_profiler_install_gc__)
        __mono_profiler_install_gc__ = (type_mono_profiler_install_gc)load_mono_function("mono_profiler_install_gc");
    __mono_profiler_install_gc__(callback, heap_resize_callback);
}

typedef void (*type_mono_profiler_install_allocation)(MonoProfileAllocFunc callback);
type_mono_profiler_install_allocation __mono_profiler_install_allocation__;
extern "C" EXPORT_API void mono_profiler_install_allocation(MonoProfileAllocFunc callback)
{
    log_function_usage("mono_profiler_install_allocation");
    if (!__mono_profiler_install_allocation__)
        __mono_profiler_install_allocation__ = (type_mono_profiler_install_allocation)load_mono_function("mono_profiler_install_allocation");
    __mono_profiler_install_allocation__(callback);
}

typedef void (*type_mono_profiler_install_jit_end)(MonoProfileJitResult jit_end);
type_mono_profiler_install_jit_end __mono_profiler_install_jit_end__;
extern "C" EXPORT_API void mono_profiler_install_jit_end(MonoProfileJitResult jit_end)
{
    log_function_usage("mono_profiler_install_jit_end");
    if (!__mono_profiler_install_jit_end__)
        __mono_profiler_install_jit_end__ = (type_mono_profiler_install_jit_end)load_mono_function("mono_profiler_install_jit_end");
    __mono_profiler_install_jit_end__(jit_end);
}

typedef void (*type_mono_profiler_install_thread)(MonoProfileThreadFunc start, MonoProfileThreadFunc end);
type_mono_profiler_install_thread __mono_profiler_install_thread__;
extern "C" EXPORT_API void mono_profiler_install_thread(MonoProfileThreadFunc start, MonoProfileThreadFunc end)
{
    log_function_usage("mono_profiler_install_thread");
    if (!__mono_profiler_install_thread__)
        __mono_profiler_install_thread__ = (type_mono_profiler_install_thread)load_mono_function("mono_profiler_install_thread");
    __mono_profiler_install_thread__(start, end);
}

typedef void (*type_mono_profiler_install_exception)(MonoProfileExceptionFunc throw_callback, MonoProfileMethodFunc exc_method_leave, MonoProfileExceptionClauseFunc clause_callback);
type_mono_profiler_install_exception __mono_profiler_install_exception__;
extern "C" EXPORT_API void mono_profiler_install_exception(MonoProfileExceptionFunc throw_callback, MonoProfileMethodFunc exc_method_leave, MonoProfileExceptionClauseFunc clause_callback)
{
    log_function_usage("mono_profiler_install_exception");
    if (!__mono_profiler_install_exception__)
        __mono_profiler_install_exception__ = (type_mono_profiler_install_exception)load_mono_function("mono_profiler_install_exception");
    __mono_profiler_install_exception__(throw_callback, exc_method_leave, clause_callback);
}

typedef void (*type_mono_unity_g_free)(void* p);
type_mono_unity_g_free __mono_unity_g_free__;
extern "C" EXPORT_API void mono_unity_g_free(void* p)
{
    log_function_usage("mono_unity_g_free");
    if (!__mono_unity_g_free__)
        __mono_unity_g_free__ = (type_mono_unity_g_free)load_mono_function("mono_unity_g_free");
    __mono_unity_g_free__(p);
}

typedef void (*type_mono_trace_set_level_string)(const char *value);
type_mono_trace_set_level_string __mono_trace_set_level_string__;
extern "C" EXPORT_API void mono_trace_set_level_string(const char *value)
{
    log_function_usage("mono_trace_set_level_string");
    if (!__mono_trace_set_level_string__)
        __mono_trace_set_level_string__ = (type_mono_trace_set_level_string)load_mono_function("mono_trace_set_level_string");
    __mono_trace_set_level_string__(value);
}

typedef void (*type_mono_trace_set_mask_string)(const char *value);
type_mono_trace_set_mask_string __mono_trace_set_mask_string__;
extern "C" EXPORT_API void mono_trace_set_mask_string(const char *value)
{
    log_function_usage("mono_trace_set_mask_string");
    if (!__mono_trace_set_mask_string__)
        __mono_trace_set_mask_string__ = (type_mono_trace_set_mask_string)load_mono_function("mono_trace_set_mask_string");
    __mono_trace_set_mask_string__(value);
}
