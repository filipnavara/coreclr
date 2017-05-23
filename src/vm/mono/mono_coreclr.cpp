#include "common.h"
#include "MonoCoreClr.h"

#include "assembly.hpp"
#include "mscoree.h"
#include "threads.h"

#ifdef WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

ICLRRuntimeHost2* g_CLRRuntimeHost;
MonoDomain* g_RootDomain;
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

char s_AssemblyDir[MAX_PATH] = { 0 };

// Import this function manually as it is not defined in a header
extern "C" HRESULT  GetCLRRuntimeHost(REFIID riid, IUnknown **ppUnk);

typedef Assembly MonoAssembly_clr;
typedef Assembly MonoImage_clr;
typedef Object MonoObject_clr;
typedef FieldDesc MonoClassField_clr; // struct MonoClassField;
typedef MethodTable MonoClass_clr; //struct MonoClass;
typedef AppDomain MonoDomain_clr; //struct MonoDomain;
typedef MethodDesc MonoMethod_clr;
typedef OBJECTREF MonoObjectRef_clr;
typedef TypeHandle MonoType_clr;
typedef ArrayBase MonoArray_clr;
typedef const COR_SIGNATURE MonoMethodSignature_clr;

static inline MonoType_clr MonoType_clr_from_MonoType(MonoType* type)
{
    return MonoType_clr::FromPtr(type);
}


// dummy function just to test that it is exported in coreclr so/dll
extern "C" EXPORT_API void mono_test_export()
{
}

// Functions used by MonoObjectRef
 extern "C" void mono_gc_objectref_new(const MonoObjectRef* objectref)
 {
     Thread::ObjectRefNew((const OBJECTREF*)objectref);
 }
 
 extern "C" gboolean mono_gc_objectref_valid(const MonoObjectRef* objectref)
 {
     return Thread::IsObjRefValid((const OBJECTREF*)objectref);
 }
 
 extern "C" gboolean mono_gc_is_heap_pointer(void* ptr)
 {
     return ((IGCHeap*)GCHeapUtilities::GetGCHeap())->IsHeapPointer(ptr);
 }
 
 extern "C" void mono_gc_objectref_assign(const MonoObjectRef* objectref)
 {
     Thread::ObjectRefAssign((const OBJECTREF*)objectref);
 }

extern "C" void mono_gc_object_validate(MonoObject* object)
{
    ((Object*)object)->Validate();
}

extern "C" void mono_gc_enable_stress_heap()
{
    ENABLESTRESSHEAP();
}

// switch to preemptive (true) or cooperative (false)
// returns the previous state of the GC
// TODO: Write equivalent to GCCoop with this function
extern "C" gboolean mono_gc_preemptive(gboolean enable)
{
    Thread* thread = GetThread();
    gboolean previousState = thread->PreemptiveGCDisabled();
    if (enable)
    {
        if (previousState)
        {
            thread->EnablePreemptiveGC();
            MONO_ASSERTE(!thread->PreemptiveGCDisabled());
        }
    }
    else if (!previousState)
    {
        thread->DisablePreemptiveGC();
        MONO_ASSERTE(thread->PreemptiveGCDisabled());
    }
    return previousState;
}


extern "C" void mono_debug_assert_dialog(const char *szFile, int iLine, const char *szExpr)
{
    DbgAssertDialog(szFile, iLine, szExpr);
}

// Make sure that our MonoGCCookie as the exact same size as the CoreCLR FrameWithCookie<GCFrame>
static_assert(sizeof(FrameWithCookie<GCFrame>) == sizeof(MonoGCCookie), "MonoGCCookie != CLRGCCookie");

extern "C" void mono_thread_suspend_all_other_threads()
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_thread_pool_cleanup()
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_threads_set_shutting_down()
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_runtime_set_shutting_down()
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" gboolean mono_runtime_is_shutting_down()
{
    //TODO not used
    return FALSE;
}

extern "C" gboolean mono_domain_finalize(MonoDomain *domain, int timeout)
{
    //TODO not used
    return TRUE;
}

extern "C" void mono_runtime_cleanup(MonoDomain *domain)
{
    //TODO not used
}

extern "C" MonoMethod* mono_object_get_virtual_method(MonoObject *obj, MonoMethod *method)
{
    //TODO used 2 times
    return NULL;
}

extern "C" void mono_verifier_set_mode(MiniVerifierMode)
{
    //TODO used in Runtime\Mono\MonoManager.cpp SetSecurityMode()
    // NOP for now
}

extern "C" void mono_security_set_mode(MonoSecurityMode)
{
    //TODO used in Runtime\Mono\MonoManager.cpp SetSecurityMode()
    // NOP for now
}

extern "C" void mono_add_internal_call(const char *name, gconstpointer method)
{
    //TODO used for registering all internal functions in mono
}

extern "C" void mono_jit_cleanup(MonoDomain *domain)
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" MonoDomain* mono_jit_init(const char *file)
{
    return mono_jit_init_version(file, "4.0");
}

extern "C" MonoDomain* mono_jit_init_version(const char *file, const char* runtime_version)
{
    if (!g_CLRRuntimeHost)
    {
        HRESULT hr;
        hr = GetCLRRuntimeHost(IID_ICLRRuntimeHost4, (IUnknown**)&g_CLRRuntimeHost);

        if(FAILED(hr))
        {
            return nullptr;
        }

        ICLRRuntimeHost2* host = g_CLRRuntimeHost;

		hr = host->SetStartupFlags(static_cast<STARTUP_FLAGS>(
			STARTUP_FLAGS::STARTUP_CONCURRENT_GC | STARTUP_FLAGS::STARTUP_SINGLE_APPDOMAIN | STARTUP_FLAGS::STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN));
        
        if(FAILED(hr))
        {
            return nullptr;
        }

		hr = host->Start();

        if(FAILED(hr))
        {
            return nullptr;
        }

        const wchar_t *property_keys[] = {
            W("TRUSTED_PLATFORM_ASSEMBLIES"),
            W("APP_PATHS"),
            W("APP_NI_PATHS"),
            W("NATIVE_DLL_SEARCH_DIRECTORIES"),
            W("APP_LOCAL_WINMETADATA")
        };

        wchar_t appPath[MAX_PATH] = { 0 };
        Wsz_mbstowcs(appPath, s_AssemblyDir, MAX_PATH);

        wchar_t* appNiPath = appPath;
        wchar_t* nativeDllSearchDirs = appPath;
        wchar_t* appLocalWinmetadata = appPath;

        const wchar_t *property_values[] = {
            // TRUSTED_PLATFORM_ASSEMBLIES
                  W(""),  // TODO: Add TPA list here
                  // APP_PATHS
                  appPath,
                  // APP_NI_PATHS
                  appNiPath,
                  // NATIVE_DLL_SEARCH_DIRECTORIES
                  nativeDllSearchDirs,
                  // APP_LOCAL_WINMETADATA
                  appLocalWinmetadata
        };

        // TODO: This is not safe
        wchar_t  wfile[MAX_PATH];
        Wsz_mbstowcs(wfile, file, MAX_PATH); // check if null terminated

        DWORD domainId;
        hr = host->CreateAppDomainWithManager(
            wfile,   // The friendly name of the AppDomain
                     // Flags:
                     // APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS
                     // - By default CoreCLR only allows platform neutral assembly to be run. To allow
                     //   assemblies marked as platform specific, include this flag
                     //
                     // APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP
                     // - Allows sandboxed applications to make P/Invoke calls and use COM interop
                     //
                     // APPDOMAIN_SECURITY_SANDBOXED
                     // - Enables sandboxing. If not set, the app is considered full trust
                     //
                     // APPDOMAIN_IGNORE_UNHANDLED_EXCEPTION
                     // - Prevents the application from being torn down if a managed exception is unhandled
                     //
            APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS |
            APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP |
            APPDOMAIN_DISABLE_TRANSPARENCY_ENFORCEMENT,
            NULL,                // Name of the assembly that contains the AppDomainManager implementation
            NULL,                    // The AppDomainManager implementation type name
            sizeof(property_keys) / sizeof(wchar_t*),  // The number of properties
            property_keys,
            property_values,
            &domainId);

        if(FAILED(hr))
        {
            return nullptr;
        }
    }

    AppDomain *pCurDomain = SystemDomain::GetCurrentDomain();
    g_RootDomain = (MonoDomain*)pCurDomain;
    return g_RootDomain;
}

extern "C" int mono_jit_exec(MonoDomain *domain, MonoAssembly *assembly, int argc, char *argv[])
{
    // TODO NOT USED
    return 0;
}

extern "C" void* mono_jit_info_get_code_start(void* jit)
{
    // TODO used 1 by instrumentation unity/mono profiler
    // Runtime\Profiler\Instrumentation\InstrumentationProfiler.cpp(292)
    return NULL;
}

extern "C" int mono_jit_info_get_code_size(void* jit)
{
    // TODO used 1 by instrumentation unity/mono profiler
    // Runtime\Profiler\Instrumentation\InstrumentationProfiler.cpp(292)
    return 0;
}

MonoClass * mono_class_from_name(MonoImage *image, const char* name_space, const char *name, bool ignoreCase)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        // We don't support multiple domains
        PRECONDITION(image != nullptr);
        PRECONDITION(name_space != nullptr);
        PRECONDITION(name != nullptr);
    }
    CONTRACTL_END;

    auto assembly = (MonoAssembly_clr*)image;
    DomainAssembly* domainAssembly = assembly->GetDomainAssembly();

    SString nameSpace(SString::Utf8, name_space);
    SString dot(SString::Utf8, ".");
    SString className(SString::Utf8, name);

    SString fullTypeName(nameSpace, dot, className);

    TypeHandle retTypeHandle = TypeName::GetTypeManaged(fullTypeName.GetUnicode(), domainAssembly, FALSE, ignoreCase, assembly->IsIntrospectionOnly(), TRUE, NULL, FALSE, (OBJECTREF*)NULL); // TODO: We don't pass a keepAlive object. Might be problematic for collectible?

    if (!retTypeHandle.IsNull())
    {
        return (MonoClass*)retTypeHandle.AsMethodTable();
    }

    return NULL;
}

extern "C" MonoClass * mono_class_from_name(MonoImage *image, const char* name_space, const char *name)
{
    return mono_class_from_name(image, name_space, name, false);
}

extern "C" MonoClass * mono_class_from_name_case(MonoImage *image, const char* name_space, const char *name)
{
    return mono_class_from_name(image, name_space, name, true);
}

extern "C" MonoAssembly * mono_domain_assembly_open(MonoDomain *domain, const char *name)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        // We don't support multiple domains
        PRECONDITION(domain == g_RootDomain);
        PRECONDITION(domain != nullptr);
        PRECONDITION(name != nullptr);
    }
    CONTRACTL_END;

    SString assemblyPath(SString::Utf8, name);
    auto assembly = AssemblySpec::LoadAssembly(assemblyPath.GetUnicode());
    assembly->GetDomainAssembly((MonoDomain_clr*)domain);
    return (MonoAssembly*)assembly;
}

extern "C" MonoDomain * mono_domain_create_appdomain(const char *domainname, const char* configfile)
{
    // TODO used mostly in Runtime\Mono\MonoManager.cpp   MonoManager::CreateAndSetChildDomain()
    // to load script assemblies
    return NULL;
}

extern "C" void mono_domain_unload(MonoDomain* domain)
{
    // TODO used mainly in Runtime\Mono\MonoManager.cpp UnloadDomain() to unload from the current domain
}

extern "C" MonoObject* mono_object_new(MonoDomain *domain, MonoClass *klass)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
        MODE_COOPERATIVE;
        INJECT_FAULT(COMPlusThrowOM()); // TODO: Check if this is applicable here
        PRECONDITION(domain != NULL);
        PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    OBJECTREF objectRef = AllocateObject((MethodTable*)klass);
    return NULL;
}

extern "C" void mono_runtime_object_init(MonoObject *this_obj)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
        MODE_COOPERATIVE;
        INJECT_FAULT(COMPlusThrowOM()); // TODO: Check if this is applicable here
        PRECONDITION(this_obj != NULL);
    }
    CONTRACTL_END;

    // TODO check what to do with the exception thrown by CallDefaultConstructor
    OBJECTREF objref = ObjectToOBJECTREF((MonoObject_clr*)this_obj);
    GCPROTECT_BEGIN(objref);
    {
        CallDefaultConstructor(objref);
    }
    GCPROTECT_END();
}

extern "C" MonoObject* mono_runtime_invoke(MonoMethod *method, void *obj, void **params, MonoException **exc)
{
    // TODO: Add contract
    MONO_ASSERTE(params == NULL);  // TODO: Handle params to ARG_SLOT

    MethodTable* ptable;

    OBJECTREF objref = ObjectToOBJECTREF((Object*)obj);

    MethodDescCallSite invoker((MonoMethod_clr*)method, &objref);

    // TODO: Convert params to ARG_SLOT
    OBJECTREF result = invoker.Call_RetOBJECTREF((ARG_SLOT*)NULL);
    return (MonoObject*)OBJECTREFToObject(result);
}

extern "C" void mono_field_set_value(MonoObject *obj, MonoClassField *field, void *value)
{
    // TODO: Add contact
    // TODO: obj not protected?
    FCALL_CONTRACT;

    OBJECTREF objectRef = ObjectToOBJECTREF((MonoObject_clr*)obj);
    GCX_COOP();
    GCPROTECT_BEGIN(objectRef); // Is it really necessary in cooperative mode? for a GetInstanceField?
    {
        ((MonoClassField_clr*)field)->SetInstanceField(objectRef, value);
    }
    GCPROTECT_END();
}

extern "C" void mono_field_get_value(MonoObject *obj, MonoClassField *field, void *value)
{
    // TODO: Add contact
    // TODO: obj not protected?
    FCALL_CONTRACT;

    OBJECTREF objectRef = ObjectToOBJECTREF((MonoObject_clr*)obj);
    GCX_COOP();
    GCPROTECT_BEGIN(objectRef); // Is it really necessary in cooperative mode? for a GetInstanceField?
    {
        auto field_clr = (MonoClassField_clr*)field;
        field_clr->GetInstanceField(objectRef, value);
    }
    GCPROTECT_END();
}

extern "C" int mono_field_get_offset(MonoClassField *field)
{
    return ((MonoClassField_clr*)field)->GetOffset();
}


extern "C" MonoClassField* mono_class_get_fields(MonoClass* klass, gpointer *iter)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    if (!iter)
    {
        return NULL;
    }
    /*
    struct FieldIterator
    {
        MonoClassField_clr *current;
        MonoClassField_clr *end;
    };
    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;

    FieldIterator* iterator = (FieldIterator*)*iter;
    if (iterator == NULL)
    {
        SIZE_T fieldCount = EEClass::FieldDescListSize(klass_clr);
        if (fieldCount > 0)
        {
            iterator = new FieldIterator();
            iterator->current = klass_clr->GetClass()->GetFieldDescList();;
            iterator->end = iterator->current + fieldCount;
            *iter = iterator;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        iterator->current++;
        if (iterator->current >= iterator->end)
        {
            *iter = NULL;
            delete iterator;
            return NULL;
        }
    }

    return (MonoClassField*)iterator->current;
    */
    // TODO:
    return nullptr;
}

extern "C" MonoClass* mono_class_get_nested_types(MonoClass* klass, gpointer *iter)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    if (!iter)
    {
        return NULL;
    }

    struct NestedTypesIterator
    {
        ULONG index;
        ULONG count;
        mdTypeDef tokens[];
    };

    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;

    NestedTypesIterator* nestedIterator = (NestedTypesIterator*)*iter;
    if (nestedIterator == NULL)
    {
        mdTypeDef token = klass_clr->GetCl();
        IMDInternalImport *pImport = klass_clr->GetMDImport();
        ULONG nestedCount;
        pImport->GetCountNestedClasses(token, &nestedCount);
        // Early exit if there is no nested classes
        if (nestedCount == 0)
        {
            return NULL;
        }
        SIZE_T sizeOfIterator = sizeof(NestedTypesIterator) + sizeof(mdTypeDef) * nestedCount;
        nestedIterator = (NestedTypesIterator*)new BYTE[sizeOfIterator];
        nestedIterator->index = 0;
        nestedIterator->count = nestedCount;
        *iter = nestedIterator;
        pImport->GetNestedClasses(token, nestedIterator->tokens, nestedCount, &nestedCount);
    }

    if (nestedIterator->index < nestedIterator->count)
    {
        TypeHandle th = ClassLoader::LoadTypeDefThrowing(klass_clr->GetModule(), nestedIterator->tokens[nestedIterator->index]);
        nestedIterator->index++;
        MONO_ASSERTE(!th.IsNull());
        return (MonoClass*)th.GetMethodTable();
    }
    else
    {
        *iter = NULL;
        delete[](BYTE*)nestedIterator;
    }

    return NULL;
}

extern "C" MonoMethod* mono_class_get_methods(MonoClass* klass, gpointer *iter)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    if (!iter)
    {
        return NULL;
    }

    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;

    MethodTable::MethodIterator* iterator = (MethodTable::MethodIterator*)*iter;
    if (iterator == NULL)
    {
        iterator = new MethodTable::MethodIterator(klass_clr);
    }

    if (!iterator->IsValid())
    {
        *iter = NULL;
        delete iterator;
        return NULL;
    }

    auto method = iterator->GetMethodDesc();
    iterator->Next();
    return (MonoMethod*)method;
}

extern "C" int mono_class_get_userdata_offset()
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    }
    CONTRACTL_END;

    return offsetof(MethodTable, m_pUserData);
}

extern "C" void* mono_class_get_userdata(MonoClass* klass)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    return ((MonoClass_clr*)klass)->m_pUserData;
}

extern "C" void mono_class_set_userdata(MonoClass* klass, void* userdata)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    ((MonoClass_clr*)klass)->m_pUserData = userdata;
}

extern "C" MonoDomain* mono_domain_get()
{
    return g_RootDomain;
}

extern "C" MonoDomain* mono_get_root_domain()
{
    return g_RootDomain;
}

extern "C" gint32 mono_domain_get_id(MonoDomain *domain)
{
    // TODO
    return NULL;
}

extern "C" void mono_assembly_foreach(GFunc func, gpointer user_data)
{
}

extern "C" void mono_image_close(MonoImage *image)
{
}

extern "C" void mono_unity_socket_security_enabled_set(gboolean)
{
}

//DO_API(void,mono_set_unhandled_exception_handler,(void* function))
extern "C" const char* mono_image_get_name(MonoImage *image)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(image != NULL);
    }
    CONTRACTL_END;

    return reinterpret_cast<MonoAssembly_clr*>(image)->GetSimpleName();
}

extern "C" MonoClass* mono_get_object_class()
{
    // TODO
    return NULL;
}

#if UNITY_WIN || UNITY_OSX || UNITY_ANDROID || UNITY_TIZEN || UNITY_STV || UNITY_LINUX
extern "C" void mono_set_signal_chaining(gboolean)
{
}

#endif
#if UNITY_WIN
extern "C" long mono_unity_seh_handler(EXCEPTION_POINTERS*)
{
}

extern "C" void mono_unity_set_unhandled_exception_handler(void*)
{
}

#endif

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" void mono_set_commandline_arguments(int, const char* argv[], const char*)
{
    // TODO (used)
}

#endif

#if USE_MONO_AOT
extern "C" void* mono_aot_get_method(MonoDomain *domain, MonoMethod *method)
{
}

#endif
//DO_API(MonoMethod*, mono_marshal_get_xappdomain_invoke, (MonoMethod*))

// Type-safe way of looking up methods based on method signatures
extern "C" MonoObject* mono_runtime_invoke_array(MonoMethod *method, void *obj, MonoArray *params, MonoException **exc)
{
    // TODO
    return NULL;
}

extern "C" char* mono_array_addr_with_size(MonoArray *array, int size, uintptr_t idx)
{
    // TODO
    return NULL;
}

#define mono_array_addr(array,type,index) ((type*)(void*) mono_array_addr_with_size (array, sizeof (type), index))

#if UNITY_EDITOR
extern "C" MonoMethodDesc* mono_method_desc_new(const char *name, gboolean include_namespace)
{
    // TODO
    return NULL;
}

extern "C" MonoMethod* mono_method_desc_search_in_class(MonoMethodDesc* desc, MonoClass* klass)
{
    // TODO
    return NULL;
}

extern "C" void mono_method_desc_free(MonoMethodDesc* desc)
{
}

extern "C" char* mono_type_get_name_full(MonoType *type, MonoTypeNameFormat format)
{
    // TODO
    return NULL;
}

#endif

#if UNITY_WIN || UNITY_XBOXONE
extern "C" gunichar2* mono_string_to_utf16(MonoString *string_obj)
{
}

#endif

extern "C" const char* mono_field_get_name(MonoClassField *field)
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_field_get_parent(MonoClassField *field)
{
    // TODO
    return NULL;
}

extern "C" MonoType* mono_field_get_type(MonoClassField *field)
{
    // TODO
    return NULL;
}

extern "C" int mono_type_get_type(MonoType *type)
{
    // TODO
    return NULL;
}

extern "C" const char* mono_method_get_name(MonoMethod *method)
{
    return reinterpret_cast<MonoMethod_clr*>(method)->GetName();
}

extern "C" char* mono_method_full_name(MonoMethod* method, gboolean signature)
{
    // TODO
    return NULL;
}

extern "C" MonoImage* mono_assembly_get_image(MonoAssembly *assembly)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        PRECONDITION(assembly != NULL);
    }
    CONTRACTL_END;

    // Assume for now that Assembly == Image
    return (MonoImage*)assembly;
}

extern "C" MonoClass* mono_method_get_class(MonoMethod *method)
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_object_get_class(MonoObject *obj)
{
    MonoClass_clr* klass = reinterpret_cast<MonoObject_clr*>(obj)->GetTypeHandle().AsMethodTable();
    return (MonoClass*)klass;
}

extern "C" MonoObject* mono_object_isinst(MonoObject *obj, MonoClass* klass)
{
    MonoClass* clazz = mono_object_get_class(obj);
    if (mono_class_is_subclass_of(clazz, klass, TRUE))
        return obj;
    return NULL;
}

extern "C" gboolean mono_class_is_valuetype(MonoClass *klass)
{
    MonoClass_clr* clazz = (MonoClass_clr*)klass;
    return (gboolean)clazz->IsValueType();
}

extern "C" guint32 mono_signature_get_param_count(MonoMethodSignature *sig)
{
    // TODO
    return NULL;
}

extern "C" char* mono_string_to_utf8(MonoString *string_obj)
{
    // TODO
    return NULL;
}

extern "C" MonoString* mono_string_new_wrapper(const char* text)
{
    // TODO
    return NULL;
}

extern "C" MonoString* mono_string_new_len(MonoDomain *domain, const char *text, guint32 length)
{
    // TODO
    return NULL;
}

extern "C" MonoString* mono_string_from_utf16(const gunichar2* text)
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_class_get_parent(MonoClass *klass)
{
    MonoClass_clr* parent = reinterpret_cast<MonoClass_clr*>(klass)->GetParentMethodTable();
    return (MonoClass*)parent;
}

extern "C" const char* mono_class_get_namespace(MonoClass *klass)
{
	MonoClass_clr* clazz = (MonoClass_clr*)klass;
	LPCUTF8 name, namespaze;
	clazz->GetMDImport()->GetNameOfTypeDef(clazz->GetCl(), &name, &namespaze);
    return namespaze;
}

extern "C" gboolean mono_class_is_subclass_of(MonoClass *klass, MonoClass *klassc, gboolean check_interfaces)
{
    MonoClass_clr* clazz = (MonoClass_clr*)klass;
    do
    {
        if (clazz == (MonoClass_clr*)klassc)
            return TRUE;
        clazz = clazz->GetParentMethodTable();
    }
    while (clazz != NULL);
    return FALSE;
}

extern "C" const char* mono_class_get_name(MonoClass *klass)
{
	MonoClass_clr* clazz = (MonoClass_clr*)klass;
	LPCUTF8 name, namespaze;
	clazz->GetMDImport()->GetNameOfTypeDef(clazz->GetCl(), &name, &namespaze);
	return name;
}

extern "C" char* mono_type_get_name(MonoType *type)
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_type_get_class(MonoType *type)
{
    // TODO
    return NULL;
}

extern "C" MonoException * mono_exception_from_name_msg(MonoImage *image, const char *name_space, const char *name, const char *msg)
{
    // TODO
    return NULL;
}

extern "C" MonoException * mono_exception_from_name_two_strings(MonoImage *image, const char *name_space, const char *name, const char *msg1, const char *msg2)
{
    // TODO
    return NULL;
}

extern "C" MonoException * mono_get_exception_argument_null(const char *arg)
{
    // TODO
    return NULL;
}

extern "C" void mono_raise_exception(MonoException *ex)
{
}

extern "C" MonoClass* mono_get_exception_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_array_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_string_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_boolean_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_byte_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_char_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_int16_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_int32_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_int64_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_single_class()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_double_class()
{
    // TODO
    return NULL;
}

extern "C" MonoArray* mono_array_new(MonoDomain *domain, MonoClass *eclass, guint32 n)
{
    CONTRACTL{
        THROWS;
        GC_TRIGGERS;
        MODE_COOPERATIVE; // returns an objref without pinning it => cooperative
        PRECONDITION(domain != nullptr);
        PRECONDITION(eclass != nullptr);
    } CONTRACTL_END;

    // TODO: handle large heap flag?
    auto arrayRef = AllocateObjectArray(n, (MonoClass_clr*)eclass);
    return (MonoArray*)OBJECTREFToObject(arrayRef);;
}

extern "C" MonoArray* mono_array_new_full(MonoDomain *domain, MonoClass *array_class, guint32 *lengths, guint32 *lower_bounds)
{
    // TODO
    return NULL;
}

extern "C" MonoClass * mono_array_class_get(MonoClass *eclass, guint32 rank)
{
    CONTRACTL{
        STANDARD_VM_CHECK;
        PRECONDITION(eclass != nullptr);
        PRECONDITION(rank > 0);
    } CONTRACTL_END;

    // TODO: We do not make any caching here
    // Might be a problem compare to mono implem that is caching
    // (clients might expect that for a same eclass+rank, we get the same array class pointer)

    auto eclass_clr = (MonoClass_clr*)eclass;
    auto domain_clr = (MonoDomain_clr*)g_RootDomain;

    auto classModule = eclass_clr->GetModule();
    auto kind = rank == 1 ? ELEMENT_TYPE_SZARRAY : ELEMENT_TYPE_ARRAY;

    // TODO: Is it ok to use a tracker like this?
    AllocMemTracker amTracker;
    auto arrayMT = classModule->CreateArrayMethodTable(eclass_clr, kind, rank, &amTracker);

    return (MonoClass*)arrayMT;
}

extern "C" gint32 mono_class_array_element_size(MonoClass *ac)
{
    // TODO
    return NULL;
}

extern "C" MonoObject* mono_type_get_object(MonoDomain *domain, MonoType *type)
{
    // TODO
    return NULL;
}

extern "C" gboolean mono_class_is_generic(MonoClass* klass)
{
    // TODO
    return FALSE;
}

extern "C" gboolean mono_class_is_inflated(MonoClass* klass)
{
    // TODO
    return FALSE;
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" gboolean unity_mono_method_is_generic(MonoMethod* method)
{
    // TODO
    return FALSE;
}

extern "C" gboolean unity_mono_method_is_inflated(MonoMethod* method)
{
    // TODO
    return FALSE;
}

#endif

extern "C" MonoThread * mono_thread_attach(MonoDomain *domain)
{
    // TODO (used)
    return NULL;
}

extern "C" void mono_thread_detach(MonoThread *thread)
{
}

extern "C" MonoThread * mono_thread_exit()
{
    // TODO (?)
    return NULL;
}

extern "C" MonoThread * mono_thread_current(void)
{
    return (MonoThread*)GetThread();
}

extern "C" void mono_thread_set_main(MonoThread* thread)
{
    // TODO used
}

extern "C" void mono_set_find_plugin_callback(gconstpointer method)
{
}

extern "C" void mono_security_enable_core_clr()
{
}

typedef gboolean(*MonoCoreClrPlatformCB) (const char *image_name);
extern "C" void mono_security_set_core_clr_platform_callback(MonoCoreClrPlatformCB)
{
}

#if MONO_2_12
extern "C" void mono_security_core_clr_set_options(MonoSecurityCoreCLROptions)
{
}

#endif

extern "C" void mono_runtime_unhandled_exception_policy_set(MonoRuntimeUnhandledExceptionPolicy policy)
{
}

#if UNITY_OSX
//DO_API(void,SetNativeSigsegvHandler,(gconstpointer ptr))
#endif
#if UNITY_WIN
//DO_API(void,SetNativeSigsegvHandlerWin,(gconstpointer ptr))
// @TODO: move this out of windows specific
//DO_API(void,unity_mono_redirect_output,(const char* fout, const char* ferr))
//DO_API(void,unity_mono_close_output,())
#endif

extern "C" MonoClass* mono_class_get_nesting_type(MonoClass *klass)
{
    MonoClass_clr* clazz = (MonoClass_clr*)klass;
    MonoClass_clr* ret = ClassLoader::LoadTypeDefOrRefOrSpecThrowing(clazz->GetModule(), clazz->GetEnclosingCl(), NULL).AsMethodTable();
    return (MonoClass*)ret;
}

extern "C" MonoVTable* mono_class_vtable(MonoDomain *domain, MonoClass *klass)
{
    // TODO (?)
    return NULL;
}

extern "C" MonoReflectionMethod* mono_method_get_object(MonoDomain *domain, MonoMethod *method, MonoClass *refclass)
{
    // TODO (?)
    return NULL;
}

extern "C" MonoMethodSignature* mono_method_signature(MonoMethod *method)
{
    MonoMethodSignature_clr* sig = reinterpret_cast<MonoMethod_clr*>(method)->GetSignature().GetRawSig();
    return (MonoMethodSignature*)sig;
}

extern "C" MonoType* mono_signature_get_params(MonoMethodSignature *sig, gpointer *iter)
{
    // TODO (?)
    return NULL;
}

extern "C" MonoType* mono_signature_get_return_type(MonoMethodSignature *sig)
{
    // TODO (?)
    return NULL;
}

extern "C" MonoType* mono_class_get_type(MonoClass *klass)
{
    TypeHandle h(reinterpret_cast<MonoClass_clr*>(klass));
    return (MonoType*)h.AsPtr();
}

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" void mono_set_ignore_version_and_key_when_finding_assemblies_already_loaded(gboolean value)
{
}

#endif
extern "C" void mono_debug_init(int format)
{
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" gboolean mono_is_debugger_attached(void)
{
    // TODO
    return FALSE;
}

#endif

extern "C" void mono_debug_open_image_from_memory(MonoImage *image, const char *raw_contents, int size)
{
}

extern "C" guint32 mono_field_get_flags(MonoClassField *field)
{
    // TODO
    return NULL;
}

extern "C" MonoImage* mono_image_open_from_data_full(const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only)
{
    // TODO
    return NULL;
}

extern "C" MonoImage* mono_image_open_from_data_with_name(char *data, guint32 data_len, gboolean need_copy, int *status, gboolean refonly, const char *name)
{
    // TODO
    return NULL;
}

extern "C" MonoAssembly * mono_assembly_load_from(MonoImage *image, const char*fname, int *status)
{
    // TODO
    return NULL;
}

extern "C" gboolean mono_assembly_fill_assembly_name(MonoImage *image, MonoAssemblyName *aname)
{
    // TODO
    return FALSE;
}

extern "C" char* mono_stringify_assembly_name(MonoAssemblyName *aname)
{
    // TODO
    return NULL;
}

extern "C" int mono_assembly_name_parse(const char* name, MonoAssemblyName *assembly)
{
    // TODO
    return 0;
}

extern "C" MonoAssembly* mono_assembly_loaded(MonoAssemblyName *aname)
{
    // TODO
    return NULL;
}

extern "C" int mono_image_get_table_rows(MonoImage *image, int table_id)
{
    return 0;
}

extern "C" MonoClass* mono_class_get(MonoImage *image, guint32 type_token)
{
    DomainAssembly* domainAssembly = reinterpret_cast<MonoImage_clr*>(image)->GetDomainAssembly();
    MonoClass_clr* klass = ClassLoader::LoadTypeDefOrRefOrSpecThrowing(domainAssembly->GetModule(), (mdToken)type_token, NULL).AsMethodTable();
    return (MonoClass*)klass;
}

extern "C" gboolean mono_metadata_signature_equal(MonoMethodSignature *sig1, MonoMethodSignature *sig2)
{
    // TODO
    return FALSE;
}

extern "C" MonoObject * mono_value_box(MonoDomain *domain, MonoClass *klass, gpointer val)
{
    // TODO
    return NULL;
}

extern "C" MonoImage* mono_class_get_image(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" char mono_signature_is_instance(MonoMethodSignature *signature)
{
    // TODO
    return 0;
}

extern "C" MonoMethod* mono_method_get_last_managed()
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_get_enum_class()
{
    // TODO
    return NULL;
}

extern "C" MonoType* mono_class_get_byref_type(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" void mono_field_static_get_value(MonoVTable *vt, MonoClassField *field, void *value)
{
}

extern "C" void mono_unity_set_embeddinghostname(const char* name)
{
}

extern "C" void mono_set_assemblies_path(const char* name)
{
}

extern "C" guint32 mono_gchandle_new(MonoObject *obj, gboolean pinned)
{
    // TODO
    return NULL;
}

extern "C" MonoObject* mono_gchandle_get_target(guint32 gchandle)
{
    // TODO
    return NULL;
}

extern "C" guint32 mono_gchandle_new_weakref(MonoObject *obj, gboolean track_resurrection)
{
    // TODO
    return NULL;
}

extern "C" gboolean mono_gchandle_is_in_domain(guint32 gchandle, MonoDomain *domain)
{
    // TODO
    return FALSE;
}

extern "C" MonoObject* mono_assembly_get_object(MonoDomain *domain, MonoAssembly *assembly)
{
    // TODO
    return NULL;
}

extern "C" void mono_gchandle_free(guint32 gchandle)
{
}

typedef gboolean(*MonoStackWalk) (MonoMethod *method, gint32 native_offset, gint32 il_offset, gboolean managed, gpointer data);
extern "C" void mono_stack_walk(MonoStackWalk func, gpointer user_data)
{
}

extern "C" char* mono_pmip(void *ip)
{
    // TODO
    return NULL;
}

extern "C" MonoObject* mono_runtime_delegate_invoke(MonoObject *delegate, void **params, MonoException **exc)
{
    // TODO
    return NULL;
}

extern "C" MonoJitInfo* mono_jit_info_table_find(MonoDomain* domain, void* ip)
{
    // TODO
    return NULL;
}

extern "C" MonoDebugSourceLocation* mono_debug_lookup_source_location(MonoMethod* method, guint32 address, MonoDomain* domain)
{
    // TODO
    return NULL;
}

extern "C" void mono_debug_free_source_location(MonoDebugSourceLocation* location)
{
}

//DO_API (void,GC_free,(void* p))
//DO_API(void*,GC_malloc_uncollectable,(int size))
extern "C" MonoProperty* mono_class_get_properties(MonoClass* klass, gpointer *iter)
{
    // TODO
    return NULL;
}

extern "C" MonoMethod* mono_property_get_get_method(MonoProperty *prop)
{
    // TODO
    return NULL;
}

extern "C" MonoObject * mono_object_new_alloc_specific(MonoVTable *vtable)
{
    // TODO
    return NULL;
}

extern "C" MonoObject * mono_object_new_specific(MonoVTable *vtable)
{
    // TODO
    return NULL;
}

extern "C" void mono_gc_collect(int generation)
{
}

extern "C" int mono_gc_max_generation()
{
    // TODO
    return NULL;
}

extern "C" gint64 mono_gc_get_used_size()
{
    // TODO
    return NULL;
}

extern "C" gint64 mono_gc_get_heap_size()
{
    // TODO
    return NULL;
}

extern "C" void mono_gc_wbarrier_generic_store(gpointer ptr, MonoObject* value)
{
}

extern "C" MonoAssembly* mono_image_get_assembly(MonoImage *image)
{
    // TODO
    return NULL;
}

extern "C" MonoAssembly* mono_assembly_open(const char *filename, int *status)
{
    // TODO
    return NULL;
}

extern "C" gboolean mono_class_is_enum(MonoClass *klass)
{
    return (gboolean)reinterpret_cast<MonoClass_clr*>(klass)->IsEnum();
}

extern "C" MonoType* mono_class_enum_basetype(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" gint32 mono_class_instance_size(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" guint32 mono_object_get_size(MonoObject *obj)
{
    return (guint32)reinterpret_cast<MonoObject_clr*>(obj)->GetSize();
}

extern "C" guint32 mono_class_get_type_token(MonoClass *klass)
{
    return (guint32)reinterpret_cast<MonoClass_clr*>(klass)->GetTypeID();
}

extern "C" const char* mono_image_get_filename(MonoImage *image)
{
    // TODO
    return NULL;
}

extern "C" MonoAssembly* mono_assembly_load_from_full(MonoImage *image, const char *fname, int *status, gboolean refonly)
{
    // TODO
    return NULL;
}

extern "C" MonoClass* mono_class_get_interfaces(MonoClass* klass, gpointer *iter)
{
    // TODO
    return NULL;
}

extern "C" void mono_assembly_close(MonoAssembly *assembly)
{
}

extern "C" MonoProperty* mono_class_get_property_from_name(MonoClass *klass, const char *name)
{
    // TODO
    return NULL;
}

extern "C" MonoMethod* mono_class_get_method_from_name(MonoClass *klass, const char *name, int param_count)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        PRECONDITION(klass != NULL);
        PRECONDITION(name != NULL);
    }
    CONTRACTL_END;

    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;

    // TODO: Check if there is an API to perform this more efficiently
    auto iterator = MethodTable::MethodIterator(klass_clr);
    while (iterator.IsValid())
    {
        auto method = iterator.GetMethodDesc();

        // TODO: check how to handle properly UTF8 comparison
        if (strcmp(method->GetName(), name) == 0)
        {
            auto methodInst = method->GetMethodInstantiation();
            if (methodInst.GetNumArgs() == param_count)
            {
                return (MonoMethod*)method;
            }
        }
        iterator.Next();
    }

    return NULL;
}

extern "C" MonoClass* mono_class_from_mono_type(MonoType *image)
{
    MonoClass_clr* klass = MonoType_clr_from_MonoType(image).AsMethodTable();
    return (MonoClass*)klass;
}

extern "C" int mono_class_get_rank(MonoClass *klass)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    return reinterpret_cast<MonoClass_clr*>(klass)->GetRank();
}

extern "C" MonoClass* mono_class_get_element_class(MonoClass *klass)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    return (MonoClass*)reinterpret_cast<MonoClass_clr*>(klass)->GetApproxArrayElementTypeHandle().AsMethodTable();
}

extern "C" gboolean mono_unity_class_is_interface(MonoClass* klass)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    return reinterpret_cast<MonoClass_clr*>(klass)->IsInterface();
}

extern "C" gboolean mono_unity_class_is_abstract(MonoClass* klass)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    return reinterpret_cast<MonoClass_clr*>(klass)->IsAbstract();
}

extern "C" int mono_array_element_size(MonoClass* classOfArray)
{
    CONTRACTL
    {
        NOTHROW;
        GC_NOTRIGGER;
        PRECONDITION(classOfArray != NULL);
    }
    CONTRACTL_END;

    return reinterpret_cast<MonoClass_clr*>(classOfArray)->GetApproxArrayElementTypeHandle().GetSize();
}

extern "C" gboolean mono_domain_set(MonoDomain *domain, gboolean force)
{
    // TODO
    return NULL;
}

extern "C" void mono_thread_push_appdomain_ref(MonoDomain *domain)
{
}

extern "C" void mono_thread_pop_appdomain_ref()
{
}

extern "C" int mono_runtime_exec_main(MonoMethod *method, MonoArray *args, MonoObject **exc)
{
    // TODO
    return NULL;
}

extern "C" MonoImage* mono_get_corlib()
{
    // TODO
    return NULL;
}

extern "C" MonoClassField* mono_class_get_field_from_name(MonoClass *klass, const char *name)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    MonoClass_clr* mt = reinterpret_cast<MonoClass_clr*>(klass);

    ApproxFieldDescIterator fieldDescIterator(mt, ApproxFieldDescIterator::ALL_FIELDS);
    FieldDesc* pField;

    while ((pField = fieldDescIterator.Next()) != NULL)
    {
        if(strcmp(pField->GetName(), name) == 0)
        {
            return (MonoClassField*)pField;
        }
    }

    return NULL;
}

extern "C" guint32 mono_class_get_flags(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" int mono_parse_default_optimizations(const char* p)
{
    // TODO (used)
    return 0;
}

extern "C" void mono_set_defaults(int verbose_level, guint32 opts)
{
    // TODO (used)
}

extern "C" void mono_config_parse(const char *filename)
{
    // TODO (used)
}

extern "C" void mono_set_dirs(const char *assembly_dir, const char *config_dir)
{
    strcpy(s_AssemblyDir, assembly_dir);
}

//DO_API(void,ves_icall_System_AppDomain_InternalUnload,(int domain_id))
//DO_API(MonoObject*,ves_icall_System_AppDomain_createDomain,(MonoString *friendly_name, MonoObject *setup))

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  June 2 2015
extern "C" void mono_set_break_policy(MonoBreakPolicyFunc policy_callback)
{
}
#endif

extern "C" void mono_jit_parse_options(int argc, char * argv[])
{
}

extern "C" gpointer mono_object_unbox(MonoObject* o)
{
    CONTRACTL
    {
        NOTHROW;
    GC_NOTRIGGER;
    PRECONDITION(o != NULL);
    }
    CONTRACTL_END;

    return (gpointer)reinterpret_cast<MonoObject_clr*>(o)-> UnBox();
}

extern "C" MonoObject* mono_custom_attrs_get_attr(MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    // TODO
    return NULL;
}

extern "C" MonoArray* mono_custom_attrs_construct(MonoCustomAttrInfo *cinfo)
{
    // TODO
    return NULL;
}

extern "C" gboolean mono_custom_attrs_has_attr(MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    // TODO
    return NULL;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_field(MonoClass *klass, MonoClassField *field)
{
    // TODO
    return NULL;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_method(MonoMethod *method)
{
    // TODO
    return NULL;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_class(MonoClass *klass)
{
    // TODO
    return NULL;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_assembly(MonoAssembly *assembly)
{
    // TODO
    return NULL;
}

extern "C" MonoArray* mono_reflection_get_custom_attrs_by_type(MonoObject* object, MonoClass* klass)
{
    // TODO
    return NULL;
}

extern "C" void mono_custom_attrs_free(MonoCustomAttrInfo* attr)
{
}

extern "C" void* mono_loader_get_last_error(void)
{
    // TODO
    return NULL;
}

extern "C" MonoException* mono_loader_error_prepare_exception(void *error)
{
    // TODO
    return NULL;
}

#if UNITY_STANDALONE || UNITY_EDITOR
// DllImport fallback handling to load native libraries from custom locations
typedef void* (*MonoDlFallbackLoad) (const char *name, int flags, char **err, void *user_data);
typedef void* (*MonoDlFallbackSymbol) (void *handle, const char *name, char **err, void *user_data);
typedef void* (*MonoDlFallbackClose) (void *handle, void *user_data);

#	if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" MonoDlFallbackHandler* mono_dl_fallback_register(MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    // TODO
    return NULL;
}

extern "C" void mono_dl_fallback_unregister(MonoDlFallbackHandler *handler)
{
}

#	endif

#endif

typedef void(*vprintf_func)(const char* msg, va_list args);
extern "C" void mono_unity_set_vprintf_func(vprintf_func func)
{
}

extern "C" void* mono_unity_liveness_allocate_struct(MonoClass* filter, int max_object_count, mono_register_object_callback callback, void* userdata)
{
    // TODO
    return NULL;
}

extern "C" void mono_unity_liveness_stop_gc_world()
{
}

extern "C" void mono_unity_liveness_finalize(void* state)
{
}

extern "C" void mono_unity_liveness_start_gc_world()
{
}

extern "C" void mono_unity_liveness_free_struct(void* state)
{
}

#if USE_CONSOLEBRANCH_MONO
extern "C" void* mono_unity_liveness_calculation_begin(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata)
{
    // TODO
    return NULL;
}
#else
extern "C" void* mono_unity_liveness_calculation_begin(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata, mono_liveness_world_state_callback world_started_callback, mono_liveness_world_state_callback world_stopped_callback)
{
    // TODO
    return NULL;
}
#endif

extern "C" void mono_unity_liveness_calculation_end(void* state)
{
}

extern "C" void mono_unity_liveness_calculation_from_root(MonoObject* root, void* state)
{
}

extern "C" void mono_unity_liveness_calculation_from_statics(void* state)
{
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" MonoMethod* unity_mono_reflection_method_get_method(MonoReflectionMethod* mrf)
{
    // TODO
    return NULL;
}
#endif

///@TODO add this as an optimization when upgrading mono, used by MonoStringNewLength:
/// mono_string_new_len      (MonoDomain *domain, const char *text, guint length);

// Profiler
#if ENABLE_MONO_MEMORY_PROFILER
typedef void(*MonoProfileFunc) (void *prof);
typedef void(*MonoProfileMethodFunc)   (void *prof, MonoMethod   *method);
typedef void(*MonoProfileExceptionFunc) (void *prof, MonoObject *object);
typedef void(*MonoProfileExceptionClauseFunc) (void *prof, MonoMethod *method, int clause_type, int clause_num);
typedef void(*MonoProfileGCFunc)         (void *prof, int event, int generation);
typedef void(*MonoProfileGCResizeFunc)   (void *prof, SInt64 new_size);
typedef void(*MonoProfileAllocFunc)      (void *prof, MonoObject* obj, MonoClass* klass);
typedef void(*MonoProfileStatCallChainFunc) (void *prof, int call_chain_depth, guchar **ip, void *context);
typedef void(*MonoProfileStatFunc)       (void *prof, guchar *ip, void *context);
typedef void(*MonoProfileJitResult)    (void *prof, MonoMethod *method, void* jinfo, int result);
typedef void(*MonoProfileThreadFunc)     (void *prof, unsigned long tid);

extern "C" void mono_profiler_install(void *prof, MonoProfileFunc shutdown_callback)
{
}

extern "C" void mono_profiler_set_events(int events)
{
}

extern "C" void mono_profiler_install_enter_leave(MonoProfileMethodFunc enter, MonoProfileMethodFunc fleave)
{
}

extern "C" void mono_profiler_install_gc(MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback)
{
}

extern "C" void mono_profiler_install_allocation(MonoProfileAllocFunc callback)
{
}

extern "C" void mono_profiler_install_jit_end(MonoProfileJitResult jit_end)
{
}

extern "C" void mono_profiler_install_thread(MonoProfileThreadFunc start, MonoProfileThreadFunc end)
{
}

//DO_API(void, mono_gc_base_init, ())
//DO_API(void, mono_profiler_install_statistical, (MonoProfileStatFunc callback))
//DO_API(void, mono_profiler_install_statistical_call_chain, (MonoProfileStatCallChainFunc callback, int call_chain_depth))
extern "C" void mono_profiler_install_exception(MonoProfileExceptionFunc throw_callback, MonoProfileMethodFunc exc_method_leave, MonoProfileExceptionClauseFunc clause_callback)
{
}

#endif

#if UNITY_IPHONE || UNITY_TVOS
extern "C" void mono_aot_register_module(void *aot_info)
{
}
#endif

// GLib functions

// iPhone uses eglib which just calls free
// Same for XboxOne.  It could probably be pulled from the DLL, however there is
// currently no out-of-line definition of it
#if UNITY_IPHONE || UNITY_TVOS || UNITY_XBOXONE
#define g_free free
#elif MONO_2_12
#define g_free mono_unity_g_free
extern "C" void mono_unity_g_free(void* p)
{
}
#else
extern "C" void g_free(void* p)
{
}
#endif
/*
#if UNITY_ANDROID
static inline char   *g_strdup (const char *str) { if (str) {return strdup (str);} return NULL; }
#define g_mem_set_vtable(x)
#else
extern "C" char* g_strdup(const char *image)
{
}

extern "C" void g_mem_set_vtable(gpointer vtable)
{
}

#endif*/

//DO_API(void,macosx_register_exception_handler,())

extern "C" void mono_trace_set_level_string(const char *value)
{
    // TODO (used)
}

extern "C" void mono_trace_set_mask_string(const char *value)
{
    // TODO (used)
}

#if UNITY_XBOXONE
extern "C" void mono_trace_set_level(GLogLevelFlags level)
{
}
#endif

#if UNITY_WIIU
extern "C" char* g_strdup_d(char const* str)
{
}

// specific allocations
#define g_free				console_g_free
#define g_free_d(x)			console_g_free(x)
#define g_strdup_d(x)		g_strdup(x)

extern "C" void* g_memdup(void const* mem, unsigned int byte_size)
{
}

extern "C" char* g_strdup(const char *str)
{
}

extern "C" gboolean mono_jit_set_trace_options(const char* options)
{
}
#endif

#if UNITY_PSP2 || UNITY_WIIU
// memory and string functions
extern "C" void* console_g_malloc(size_t size)
{
}

extern "C" void* console_g_calloc(size_t size, size_t elemSize)
{
}

extern "C" void* console_g_realloc(void *memblock, size_t size)
{
}

extern "C" void console_g_free(void* p)
{
}
#define g_free console_g_free
#endif

#if UNITY_XBOXONE
extern "C" void mono_trace_enable(gboolean enable)
{
}
#endif

#if UNITY_PSP2 || UNITY_XBOXONE

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" void mono_set_corlib_data(void *data, size_t size)
{
}
#endif

extern "C" void mono_runtime_set_no_exec(gboolean val)
{
}

extern "C" void mono_jit_set_aot_only(gboolean val)
{
}

typedef MonoAssembly *(*MonoAssemblySearchFunc)         (char **aname, void* user_data);

extern "C" void mono_install_assembly_postload_search_hook(MonoAssemblySearchFunc func, gpointer user_data)
{
}
#endif

#if UNITY_WIIU || UNITY_XBOXONE
extern "C" void mono_runtime_set_main_args(const char** args, int num_args)
{
}
#endif

#if UNITY_OSX
extern "C" int mono_backtrace_from_context(void* context, void* array[], int count)
{
}
#endif

#if ENABLE_MONO_MEMORY_CALLBACKS
extern "C" void unity_mono_install_memory_callbacks(MonoMemoryCallbacks* callbacks)
{
}
#endif

#if UNITY_PS4
extern "C" void unity_mono_set_thread_affinity(int aff)
{
}

extern "C" void unity_mono_set_thread_policy(int type, int policy)
{
}
#endif

extern "C" void mono_gc_push_frame(MonoGCFrame* frame, void* objRef, UINT32 numRef)
{
    new (frame) FrameWithCookie<GCFrame>((OBJECTREF*)objRef, numRef, FALSE);
}

extern "C" void mono_gc_pop_frame(MonoGCFrame* frame)
{
    ((FrameWithCookie<GCFrame>*)frame)->Pop();
}

extern "C" void mono_unity_jit_cleanup(MonoDomain *domain)
{
    mono_jit_cleanup(domain);
}

extern "C" gboolean mono_class_is_blittable(MonoClass * klass)
{
    return FALSE;
}

extern "C" MonoDlFallbackHandler* mono_dl_fallback_register(MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    return NULL;
}
extern "C" void mono_dl_fallback_unregister(MonoDlFallbackHandler * handler)
{

}
extern "C" MonoArray* mono_unity_array_new_2d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1)
{
    return NULL;
}
extern "C" MonoArray* mono_unity_array_new_3d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1, size_t size2)
{
    return NULL;
}
extern "C" MonoClass* mono_unity_class_get(MonoImage * image, guint32 type_token)
{
    return NULL;
}
extern "C" void mono_unity_domain_set_config(MonoDomain * domain, const char *base_dir, const char *config_file_name)
{

}
extern "C" MonoException* mono_unity_loader_get_last_error_and_error_prepare_exception()
{
    return NULL;
}
extern "C" void mono_unity_runtime_set_main_args(int, const char* argv[])
{

}
extern "C" MonoString* mono_unity_string_empty_wrapper()
{
    return NULL;
}
