#ifndef DO_API_NO_RETURN
#define DO_API_NO_RETURN(a, b, c) DO_API(a,b,c)
#endif

// MONO_CORECLR (START)
DO_API(void, mono_gc_push_frame, (MonoGCFrame* frame, void* objRef, UINT32 numRef))
DO_API(void, mono_gc_pop_frame, (MonoGCFrame* frame))
DO_API(void, mono_gc_objectref_new, (const MonoObjectRef* objectref))
DO_API(gboolean, mono_gc_objectref_valid, (const MonoObjectRef* objectref))
DO_API(gboolean, mono_gc_is_heap_pointer, (void* ptr))
DO_API(void, mono_gc_objectref_assign, (const MonoObjectRef* objectref))
DO_API(void, mono_gc_object_validate, (MonoObject* object))
DO_API(void, mono_gc_enable_stress_heap, ())
DO_API(void, mono_debug_assert_dialog, (const char *szFile, int iLine, const char *szExpr))
DO_API(gboolean, mono_gc_preemptive, (gboolean enable))
// MONO_CORECLR (END)

// If you add functions to this file you also need to expose them in MonoBundle.exp
// Otherwise they wont be exported in the web plugin!
DO_API(void, mono_thread_suspend_all_other_threads, ())
DO_API(void, mono_thread_pool_cleanup, ())
DO_API(void, mono_threads_set_shutting_down, ())
DO_API(void, mono_runtime_set_shutting_down, ())
DO_API(gboolean, mono_runtime_is_shutting_down, ())
DO_API(gboolean, mono_domain_finalize, (MonoDomain * domain, int timeout))
DO_API(void, mono_runtime_cleanup, (MonoDomain * domain))
DO_API(MonoMethod*, mono_object_get_virtual_method, (MonoObject * obj, MonoMethod * method))

DO_API(void, mono_verifier_set_mode, (MiniVerifierMode));
DO_API(void, mono_security_set_mode, (MonoSecurityMode));
DO_API(void, mono_add_internal_call, (const char *name, gconstpointer method))
#if USE_CONSOLEBRANCH_MONO
DO_API(void, mono_jit_cleanup, (MonoDomain * domain))
#else
DO_API(void, mono_unity_jit_cleanup, (MonoDomain * domain))
#endif
DO_API(MonoDomain*, mono_jit_init, (const char *file))
DO_API(MonoDomain*, mono_jit_init_version, (const char *file, const char* runtime_version))
DO_API(int, mono_jit_exec, (MonoDomain * domain, MonoAssembly * assembly, int argc, char *argv[]))
DO_API(void*, mono_jit_info_get_code_start, (void* jit))
DO_API(int, mono_jit_info_get_code_size, (void* jit))
DO_API(MonoClass *, mono_class_from_name, (MonoImage * image, const char* name_space, const char *name))
DO_API(MonoClass *, mono_class_from_name_case, (MonoImage * image, const char* name_space, const char *name))
DO_API(MonoAssembly *, mono_domain_assembly_open, (MonoDomain * domain, const char *name))
DO_API(MonoDomain *, mono_domain_create_appdomain, (const char *domainname, const char* configfile))
DO_API(void, mono_domain_unload, (MonoDomain * domain))
DO_API(MonoObject*, mono_object_new, (MonoDomain * domain, MonoClass * klass))
DO_API(void, mono_runtime_object_init, (MonoObject * this_obj))
DO_API(MonoObject*, mono_runtime_invoke, (MonoMethod * method, void *obj, void **params, MonoException **exc))
DO_API(void, mono_field_set_value, (MonoObject * obj, MonoClassField * field, void *value))
DO_API(void, mono_field_get_value, (MonoObject * obj, MonoClassField * field, void *value))
DO_API(int, mono_field_get_offset, (MonoClassField * field))
DO_API(MonoClassField*, mono_class_get_fields, (MonoClass * klass, gpointer * iter))
DO_API(MonoClass*, mono_class_get_nested_types, (MonoClass * klass, gpointer * iter))
DO_API(MonoMethod*, mono_class_get_methods, (MonoClass * klass, gpointer * iter))
DO_API(int, mono_class_get_userdata_offset, ())
DO_API(void*, mono_class_get_userdata, (MonoClass * klass))
DO_API(void, mono_class_set_userdata, (MonoClass * klass, void* userdata))
DO_API(MonoDomain*, mono_domain_get, ())
DO_API(MonoDomain*, mono_get_root_domain, ())
DO_API(gint32, mono_domain_get_id, (MonoDomain * domain))
DO_API(void, mono_assembly_foreach, (GFunc func, gpointer user_data))
DO_API(void, mono_image_close, (MonoImage * image))
DO_API(void, mono_unity_socket_security_enabled_set, (gboolean))
//DO_API(void,mono_set_unhandled_exception_handler,(void* function))
DO_API(const char*, mono_image_get_name, (MonoImage * image))
DO_API(MonoClass*, mono_get_object_class, ())
#if PLATFORM_WIN || PLATFORM_OSX || PLATFORM_ANDROID || PLATFORM_TIZEN || PLATFORM_STV || PLATFORM_LINUX
DO_API(void, mono_set_signal_chaining, (gboolean))
#endif
#if PLATFORM_WIN
DO_API(long, mono_unity_seh_handler, (EXCEPTION_POINTERS*))
DO_API(void, mono_unity_set_unhandled_exception_handler, (void*))
#endif

#if !USE_CONSOLEBRANCH_MONO
DO_API(void, mono_unity_runtime_set_main_args, (int, const char* argv[]))
#endif

#if USE_MONO_AOT
DO_API(void*, mono_aot_get_method, (MonoDomain * domain, MonoMethod * method))
#endif
//DO_API(MonoMethod*, mono_marshal_get_xappdomain_invoke, (MonoMethod*))

// Type-safe way of looking up methods based on method signatures
DO_API(MonoObject*, mono_runtime_invoke_array, (MonoMethod * method, void *obj, MonoArray * params, MonoException **exc))
DO_API(char*, mono_array_addr_with_size, (MonoArray * array, int size, uintptr_t idx));
#define mono_array_addr(array, type, index) ((type*)(void*) mono_array_addr_with_size (array, sizeof (type), index))

#if UNITY_EDITOR
DO_API(MonoMethodDesc*, mono_method_desc_new, (const char *name, gboolean include_namespace))
DO_API(MonoMethod*, mono_method_desc_search_in_class, (MonoMethodDesc * desc, MonoClass * klass))
DO_API(void, mono_method_desc_free, (MonoMethodDesc * desc))
DO_API(char*, mono_type_get_name_full, (MonoType * type, MonoTypeNameFormat format))
DO_API(gboolean, mono_type_generic_inst_is_valuetype, (MonoType*))
#endif

#if PLATFORM_WIN || PLATFORM_XBOXONE
DO_API(gunichar2*, mono_string_to_utf16, (MonoString * string_obj))
#endif

DO_API(const char*, mono_field_get_name, (MonoClassField * field))
DO_API(MonoClass*, mono_field_get_parent, (MonoClassField * field))
DO_API(MonoType*, mono_field_get_type, (MonoClassField * field))
DO_API(int, mono_type_get_type, (MonoType * type))
DO_API(const char*, mono_method_get_name, (MonoMethod * method))
DO_API(char*, mono_method_full_name, (MonoMethod * method, gboolean signature))
DO_API(MonoImage*, mono_assembly_get_image, (MonoAssembly * assembly))
DO_API(MonoClass* , mono_method_get_class, (MonoMethod * method))
DO_API(MonoClass*, mono_object_get_class, (MonoObject * obj))
DO_API(MonoObject*, mono_object_isinst, (MonoObject * obj, MonoClass * klass))
DO_API(gboolean, mono_class_is_valuetype, (MonoClass * klass))
DO_API(gboolean, mono_class_is_blittable, (MonoClass * klass))
DO_API(guint32, mono_signature_get_param_count, (MonoMethodSignature * sig))
DO_API(char*, mono_string_to_utf8, (MonoString * string_obj))
#if !USE_CONSOLEBRANCH_MONO
DO_API(MonoString*, mono_unity_string_empty_wrapper, ())
#endif
DO_API(MonoString*, mono_string_new_wrapper, (const char* text))
DO_API(MonoString*, mono_string_new_len, (MonoDomain * domain, const char *text, guint32 length))
DO_API(MonoString*, mono_string_from_utf16, (const gunichar2 * text))
DO_API(MonoClass*, mono_class_get_parent, (MonoClass * klass))
DO_API(const char*, mono_class_get_namespace, (MonoClass * klass))
DO_API(gboolean, mono_class_is_subclass_of, (MonoClass * klass, MonoClass * klassc,  gboolean check_interfaces))
DO_API(const char*, mono_class_get_name, (MonoClass * klass))
DO_API(char*, mono_type_get_name, (MonoType * type))
DO_API(MonoClass*, mono_type_get_class, (MonoType * type))
DO_API(MonoException *, mono_exception_from_name_msg, (MonoImage * image, const char *name_space, const char *name, const char *msg))
DO_API(MonoException *, mono_exception_from_name_two_strings, (MonoImage * image, const char *name_space, const char *name, const char *msg1, const char *msg2))
DO_API(MonoException *, mono_get_exception_argument_null, (const char *arg))
DO_API_NO_RETURN(void, mono_raise_exception, (MonoException * ex))
DO_API(MonoClass*, mono_get_exception_class, ())
DO_API(MonoClass*, mono_get_array_class, ())
DO_API(MonoClass*, mono_get_string_class, ())
DO_API(MonoClass*, mono_get_boolean_class, ())
DO_API(MonoClass*, mono_get_byte_class, ())
DO_API(MonoClass*, mono_get_char_class, ())
DO_API(MonoClass*, mono_get_int16_class, ())
DO_API(MonoClass*, mono_get_int32_class, ())
DO_API(MonoClass*, mono_get_int64_class, ())
DO_API(MonoClass*, mono_get_single_class, ())
DO_API(MonoClass*, mono_get_double_class, ())
DO_API(MonoArray*, mono_array_new, (MonoDomain * domain, MonoClass * eclass, guint32 n))
#if USE_CONSOLEBRANCH_MONO
DO_API(MonoArray*, mono_array_new_full, (MonoDomain * domain, MonoClass * array_class, guint32 * lengths, guint32 * lower_bounds))
#else
DO_API(MonoArray*, mono_unity_array_new_2d, (MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1))
DO_API(MonoArray*, mono_unity_array_new_3d, (MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1, size_t size2))
#endif

DO_API(MonoClass *, mono_array_class_get, (MonoClass * eclass, guint32 rank))

DO_API(gint32, mono_class_array_element_size, (MonoClass * ac))
DO_API(MonoObject*, mono_type_get_object, (MonoDomain * domain, MonoType * type))
DO_API(gboolean, mono_class_is_generic, (MonoClass * klass))
DO_API(gboolean, mono_class_is_inflated, (MonoClass * klass))

#if !USE_CONSOLEBRANCH_MONO
DO_API(gboolean, unity_mono_method_is_generic, (MonoMethod * method))
DO_API(gboolean, unity_mono_method_is_inflated, (MonoMethod * method))
#endif

DO_API(MonoThread *, mono_thread_attach, (MonoDomain * domain))

DO_API(void, mono_thread_detach, (MonoThread * thread))
DO_API(MonoThread *, mono_thread_exit, ())

DO_API(MonoThread *, mono_thread_current, (void))
DO_API(void, mono_thread_set_main, (MonoThread * thread))
DO_API(void, mono_set_find_plugin_callback, (gconstpointer method))
DO_API(void, mono_security_enable_core_clr, ())

typedef gboolean (*MonoCoreClrPlatformCB) (const char *image_name);
DO_API(void, mono_security_set_core_clr_platform_callback, (MonoCoreClrPlatformCB))

DO_API(void, mono_runtime_unhandled_exception_policy_set, (MonoRuntimeUnhandledExceptionPolicy policy))

DO_API(MonoClass*, mono_class_get_nesting_type, (MonoClass * klass))
DO_API(MonoVTable* , mono_class_vtable, (MonoDomain * domain, MonoClass * klass))
DO_API(MonoReflectionMethod* , mono_method_get_object, (MonoDomain * domain, MonoMethod * method, MonoClass * refclass))

DO_API(MonoMethodSignature*, mono_method_signature, (MonoMethod * method))
DO_API(MonoType*, mono_signature_get_params, (MonoMethodSignature * sig, gpointer * iter))
DO_API(MonoType*, mono_signature_get_return_type, (MonoMethodSignature * sig))
DO_API(MonoType*, mono_class_get_type, (MonoClass * klass))

DO_API(void, mono_debug_init , (int format))

#if !USE_CONSOLEBRANCH_MONO
DO_API(gboolean, mono_is_debugger_attached, (void))
#endif

DO_API(void, mono_debug_open_image_from_memory, (MonoImage * image, const char *raw_contents, int size))
DO_API(guint32, mono_field_get_flags, (MonoClassField * field))
DO_API(MonoImage*, mono_image_open_from_data_full, (const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only))
DO_API(MonoImage*, mono_image_open_from_data_with_name, (char *data, guint32 data_len, gboolean need_copy, int *status, gboolean refonly, const char *name))
DO_API(MonoAssembly *, mono_assembly_load_from, (MonoImage * image, const char*fname,  int *status))
DO_API(gboolean, mono_assembly_fill_assembly_name, (MonoImage * image, MonoAssemblyName * aname))
DO_API(char* , mono_stringify_assembly_name, (MonoAssemblyName * aname))
DO_API(int, mono_assembly_name_parse, (const char* name, MonoAssemblyName * assembly))
DO_API(MonoAssembly*, mono_assembly_loaded, (MonoAssemblyName * aname))
DO_API(int, mono_image_get_table_rows, (MonoImage * image, int table_id))
#if USE_CONSOLEBRANCH_MONO
DO_API(MonoClass*, mono_class_get, (MonoImage * image, guint32 type_token))
#else
DO_API(MonoClass*, mono_unity_class_get, (MonoImage * image, guint32 type_token))
#endif
DO_API(gboolean, mono_metadata_signature_equal, (MonoMethodSignature * sig1, MonoMethodSignature * sig2))

DO_API(MonoObject *, mono_value_box, (MonoDomain * domain, MonoClass * klass, gpointer val))
DO_API(MonoImage*, mono_class_get_image, (MonoClass * klass))
DO_API(char, mono_signature_is_instance, (MonoMethodSignature * signature))
DO_API(MonoMethod*, mono_method_get_last_managed, ())
DO_API(MonoClass*, mono_get_enum_class, ())
DO_API(MonoType*, mono_class_get_byref_type, (MonoClass * klass))

DO_API(void, mono_field_static_get_value, (MonoVTable * vt, MonoClassField * field, void *value))
DO_API(void, mono_unity_set_embeddinghostname, (const char* name))
DO_API(void, mono_set_assemblies_path, (const char* name))

DO_API(guint32, mono_gchandle_new, (MonoObject * obj, gboolean pinned))
DO_API(MonoObject*, mono_gchandle_get_target, (guint32 gchandle))

DO_API(guint32, mono_gchandle_new_weakref, (MonoObject * obj, gboolean track_resurrection))

DO_API(gboolean, mono_gchandle_is_in_domain, (guint32 gchandle, MonoDomain * domain))
DO_API(MonoObject*, mono_assembly_get_object, (MonoDomain * domain, MonoAssembly * assembly))

DO_API(void, mono_gchandle_free, (guint32 gchandle))

typedef gboolean (*MonoStackWalk) (MonoMethod *method, gint32 native_offset, gint32 il_offset, gboolean managed, gpointer data);
DO_API(void, mono_stack_walk, (MonoStackWalk func, gpointer user_data));
DO_API(char*, mono_pmip, (void *ip));
DO_API(MonoObject*, mono_runtime_delegate_invoke, (MonoObject * delegate, void **params, MonoException **exc))

DO_API(MonoJitInfo*, mono_jit_info_table_find, (MonoDomain * domain, void* ip))

DO_API(MonoDebugSourceLocation*, mono_debug_lookup_source_location, (MonoMethod * method, guint32 address, MonoDomain * domain))
DO_API(void, mono_debug_free_source_location, (MonoDebugSourceLocation * location))

//DO_API (void,GC_free,(void* p))
//DO_API(void*,GC_malloc_uncollectable,(int size))
DO_API(MonoProperty*, mono_class_get_properties, (MonoClass * klass, gpointer * iter))
DO_API(MonoMethod*, mono_property_get_get_method, (MonoProperty * prop))
DO_API(MonoObject *, mono_object_new_alloc_specific, (MonoVTable * vtable))
DO_API(MonoObject *, mono_object_new_specific, (MonoVTable * vtable))

DO_API(void, mono_gc_collect, (int generation))
DO_API(int, mono_gc_max_generation, ())

DO_API(gint64, mono_gc_get_used_size, ())
DO_API(gint64, mono_gc_get_heap_size, ())

DO_API(void, mono_gc_wbarrier_generic_store, (gpointer ptr, MonoObject * value))

DO_API(MonoAssembly*, mono_image_get_assembly, (MonoImage * image))
DO_API(MonoAssembly*, mono_assembly_open, (const char *filename, int *status))

DO_API(gboolean, mono_class_is_enum, (MonoClass * klass))
DO_API(MonoType* , mono_class_enum_basetype, (MonoClass * klass))
DO_API(gint32, mono_class_instance_size, (MonoClass * klass))
DO_API(guint32, mono_object_get_size, (MonoObject * obj))
DO_API(guint32, mono_class_get_type_token, (MonoClass * klass))
DO_API(const char*, mono_image_get_filename, (MonoImage * image))
DO_API(MonoAssembly*, mono_assembly_load_from_full, (MonoImage * image, const char *fname, int *status, gboolean refonly))
DO_API(MonoClass*, mono_class_get_interfaces, (MonoClass * klass, gpointer * iter))
DO_API(void, mono_assembly_close, (MonoAssembly * assembly))
DO_API(MonoProperty*, mono_class_get_property_from_name, (MonoClass * klass, const char *name))
DO_API(MonoMethod*, mono_class_get_method_from_name, (MonoClass * klass, const char *name, int param_count))
DO_API(MonoClass*, mono_class_from_mono_type, (MonoType * image))
DO_API(int, mono_class_get_rank, (MonoClass * klass));
DO_API(MonoClass*, mono_class_get_element_class, (MonoClass * klass));
DO_API(gboolean, mono_unity_class_is_interface, (MonoClass * klass))
DO_API(gboolean, mono_unity_class_is_abstract, (MonoClass * klass))
DO_API(int, mono_array_element_size, (MonoClass * classOfArray))

DO_API(gboolean, mono_domain_set, (MonoDomain * domain, gboolean force))
#if !USE_CONSOLEBRANCH_MONO
DO_API(void, mono_unity_domain_set_config, (MonoDomain * domain, const char *base_dir, const char *config_file_name))
#endif
DO_API(void, mono_thread_push_appdomain_ref, (MonoDomain * domain))
DO_API(void, mono_thread_pop_appdomain_ref, ())

DO_API(int, mono_runtime_exec_main, (MonoMethod * method, MonoArray * args, MonoObject **exc))

DO_API(MonoImage*, mono_get_corlib, ())
DO_API(MonoClassField*, mono_class_get_field_from_name, (MonoClass * klass, const char *name))
DO_API(guint32, mono_class_get_flags, (MonoClass * klass))

DO_API(int, mono_parse_default_optimizations, (const char* p))
DO_API(void, mono_set_defaults, (int verbose_level, guint32 opts))
DO_API(void, mono_config_parse, (const char *filename))
DO_API(void, mono_set_dirs, (const char *assembly_dir, const char *config_dir))
//DO_API(void,ves_icall_System_AppDomain_InternalUnload,(int domain_id))
//DO_API(MonoObject*,ves_icall_System_AppDomain_createDomain,(MonoString *friendly_name, MonoObject *setup))

#if !PLATFORM_XBOXONE
// Not defined in current mono-consoles,  June 2 2015
DO_API(void, mono_set_break_policy, (MonoBreakPolicyFunc policy_callback))
#endif

DO_API(void, mono_jit_parse_options, (int argc, char * argv[]))
DO_API(gpointer, mono_object_unbox, (MonoObject * o))

DO_API(MonoObject*, mono_custom_attrs_get_attr, (MonoCustomAttrInfo * ainfo, MonoClass * attr_klass))

DO_API(MonoArray*, mono_custom_attrs_construct, (MonoCustomAttrInfo * cinfo))

DO_API(gboolean, mono_custom_attrs_has_attr, (MonoCustomAttrInfo * ainfo, MonoClass * attr_klass))
DO_API(MonoCustomAttrInfo*, mono_custom_attrs_from_field, (MonoClass * klass, MonoClassField * field))
DO_API(MonoCustomAttrInfo*, mono_custom_attrs_from_method, (MonoMethod * method))
DO_API(MonoCustomAttrInfo*, mono_custom_attrs_from_class, (MonoClass * klass))
DO_API(MonoCustomAttrInfo*, mono_custom_attrs_from_assembly, (MonoAssembly * assembly))
DO_API(MonoArray*, mono_reflection_get_custom_attrs_by_type, (MonoObject * object, MonoClass * klass))
DO_API(void, mono_custom_attrs_free, (MonoCustomAttrInfo * attr))

#if USE_CONSOLEBRANCH_MONO
DO_API(void*, mono_loader_get_last_error, (void))
DO_API(MonoException*, mono_loader_error_prepare_exception, (void *error))
#else
DO_API(MonoException*, mono_unity_loader_get_last_error_and_error_prepare_exception, (void))
#endif

#if PLATFORM_STANDALONE || UNITY_EDITOR
// DllImport fallback handling to load native libraries from custom locations
typedef void* (*MonoDlFallbackLoad) (const char *name, int flags, char **err, void *user_data);
typedef void* (*MonoDlFallbackSymbol) (void *handle, const char *name, char **err, void *user_data);
typedef void* (*MonoDlFallbackClose) (void *handle, void *user_data);

#   if !PLATFORM_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
DO_API(MonoDlFallbackHandler*, mono_dl_fallback_register, (MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data))
DO_API(void, mono_dl_fallback_unregister, (MonoDlFallbackHandler * handler))
#   endif

#endif

typedef void (*vprintf_func)(const char* msg, va_list args);
DO_API(void, mono_unity_set_vprintf_func, (vprintf_func func))

DO_API(void, mono_unity_liveness_stop_gc_world, ())
DO_API(void, mono_unity_liveness_finalize, (void* state))
DO_API(void, mono_unity_liveness_start_gc_world, ())
DO_API(void, mono_unity_liveness_free_struct, (void* state))
#if USE_CONSOLEBRANCH_MONO
DO_API(void*, mono_unity_liveness_calculation_begin, (MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata))
#else
DO_API(void*, mono_unity_liveness_calculation_begin, (MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata, mono_liveness_world_state_callback world_started_callback, mono_liveness_world_state_callback world_stopped_callback))
#endif
DO_API(void, mono_unity_liveness_calculation_end, (void* state))
DO_API(void, mono_unity_liveness_calculation_from_root, (MonoObject * root, void* state))
DO_API(void, mono_unity_liveness_calculation_from_statics, (void* state))

#if !USE_CONSOLEBRANCH_MONO
DO_API(MonoMethod*, unity_mono_reflection_method_get_method, (MonoReflectionMethod * mrf))
#endif


///@TODO add this as an optimization when upgrading mono, used by MonoStringNewLength:
/// mono_string_new_len      (MonoDomain *domain, const char *text, guint length);

// Profiler
#if ENABLE_MONO_MEMORY_PROFILER
typedef void (*MonoProfileFunc) (void *prof);
typedef void (*MonoProfileMethodFunc)   (void *prof, MonoMethod   *method);
typedef void (*MonoProfileExceptionFunc) (void *prof, MonoObject *object);
typedef void (*MonoProfileExceptionClauseFunc) (void *prof, MonoMethod *method, int clause_type, int clause_num);
typedef void (*MonoProfileGCFunc)         (void *prof, int event, int generation);
typedef void (*MonoProfileGCResizeFunc)   (void *prof, SInt64 new_size);
typedef void (*MonoProfileAllocFunc)      (void *prof, MonoObject* obj, MonoClass* klass);
typedef void (*MonoProfileStatCallChainFunc) (void *prof, int call_chain_depth, guchar **ip, void *context);
typedef void (*MonoProfileStatFunc)       (void *prof, guchar *ip, void *context);
typedef void (*MonoProfileJitResult)    (void *prof, MonoMethod *method, void* jinfo, int result);
typedef void (*MonoProfileThreadFunc)     (void *prof, unsigned long tid);


DO_API(void, mono_profiler_install, (void *prof, MonoProfileFunc shutdown_callback))
DO_API(void, mono_profiler_set_events, (int events))
DO_API(void, mono_profiler_install_enter_leave, (MonoProfileMethodFunc enter, MonoProfileMethodFunc fleave))
DO_API(void, mono_profiler_install_gc, (MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback))
DO_API(void, mono_profiler_install_allocation, (MonoProfileAllocFunc callback))
DO_API(void, mono_profiler_install_jit_end, (MonoProfileJitResult jit_end))
DO_API(void, mono_profiler_install_thread, (MonoProfileThreadFunc start, MonoProfileThreadFunc end))
//DO_API(void, mono_gc_base_init, ())
//DO_API(void, mono_profiler_install_statistical, (MonoProfileStatFunc callback))
//DO_API(void, mono_profiler_install_statistical_call_chain, (MonoProfileStatCallChainFunc callback, int call_chain_depth))
DO_API(void, mono_profiler_install_exception, (MonoProfileExceptionFunc throw_callback, MonoProfileMethodFunc exc_method_leave, MonoProfileExceptionClauseFunc clause_callback))

#endif

#if PLATFORM_IPHONE || PLATFORM_TVOS
DO_API(void, mono_aot_register_module, (void *aot_info))
#endif

// GLib functions
#if !USE_CONSOLEBRANCH_MONO
#define g_free mono_unity_g_free
DO_API(void, mono_unity_g_free, (void* p))
#elif PLATFORM_XBOXONE
#define g_free free
#else
#define g_free console_g_free
DO_API(void, console_g_free, (void* p))
#endif
/*
#if PLATFORM_ANDROID
static inline char   *g_strdup (const char *str) { if (str) {return strdup (str);} return NULL; }
#define g_mem_set_vtable(x)
#else
DO_API(char*,g_strdup,(const char *image))
DO_API(void,g_mem_set_vtable,(gpointer vtable))
#endif*/


//DO_API(void,macosx_register_exception_handler,())

DO_API(void, mono_trace_set_level_string, (const char *value))
DO_API(void, mono_trace_set_mask_string, (const char *value))
#if PLATFORM_XBOXONE
DO_API(void, mono_trace_set_level, (GLogLevelFlags level));
#endif

#if PLATFORM_WIIU
DO_API(char*, g_strdup_d, (char const* str))

// specific allocations
#define g_free_d(x)         console_g_free(x)
#define g_strdup_d(x)       g_strdup(x)

DO_API(void*, g_memdup, (void const* mem, unsigned int byte_size))
DO_API(char*, g_strdup, (const char *str))

DO_API(gboolean, mono_jit_set_trace_options, (const char* options))
#endif

#if PLATFORM_PSVITA || PLATFORM_WIIU
// memory and string functions
DO_API(void*, console_g_malloc, (size_t size))
DO_API(void*, console_g_calloc, (size_t size, size_t elemSize))
DO_API(void*, console_g_realloc, (void *memblock, size_t size))
#endif

#if PLATFORM_XBOXONE
DO_API(void, mono_trace_enable,    (gboolean enable));
#endif

#if PLATFORM_PSVITA || PLATFORM_XBOXONE

#   if !PLATFORM_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
DO_API(void, mono_set_corlib_data, (void *data, size_t size))
#   endif

DO_API(void, mono_runtime_set_no_exec, (gboolean val))
DO_API(void, mono_jit_set_aot_only, (gboolean val))
typedef MonoAssembly *(*MonoAssemblySearchFunc)         (char **aname, void* user_data);

DO_API(void, mono_install_assembly_postload_search_hook, (MonoAssemblySearchFunc func, gpointer user_data))
#endif

#if PLATFORM_WIIU || PLATFORM_XBOXONE
DO_API(void, mono_runtime_set_main_args, (const char** args, int num_args))
#endif

#if PLATFORM_OSX
DO_API(int, mono_unity_backtrace_from_context, (void* context, void* array[], int count))
#endif

#if UNITY_ANDROID
DO_API(void, mono_file_map_override, (MonoFileMapOpen open_func, MonoFileMapSize size_func, MonoFileMapFd fd_func, MonoFileMapClose close_func, MonoFileMapMap map_func, MonoFileMapUnmap unmap_func))
DO_API(void, mono_register_machine_config, (const char *config_xml))

DO_API(char *, mono_debug_print_stack_frame, (MonoMethod * method, guint32 native_offset, MonoDomain * domain))

DO_API(void, mono_walk_stack, (MonoDomain * domain, /*MonoJitTlsData*/ void *jit_tls, /*MonoContext*/ void *start_ctx, MonoStackFrameWalk func, gpointer user_data))
#endif

#if ENABLE_MONO_MEMORY_CALLBACKS
#if USE_CONSOLEBRANCH_MONO
DO_API(void, unity_mono_install_memory_callbacks, (MonoMemoryCallbacks * callbacks))
#else
DO_API(void, mono_unity_install_memory_callbacks, (MonoMemoryCallbacks * callbacks))
#endif
#endif

#if PLATFORM_PS4
DO_API(void, unity_mono_set_thread_affinity, (int aff))
DO_API(void, unity_mono_set_thread_policy, (int type, int policy))
#endif

#undef DO_API
#undef DO_API_NO_RETURN
