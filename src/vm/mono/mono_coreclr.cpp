#include "common.h"
#include "MonoCoreClr.h"

#include "assembly.hpp"
#include "mscoree.h"
#include "threads.h"
#include "ecall.h"
#include "stringliteralmap.h"
#include "assemblynative.hpp"

#ifdef FEATURE_PAL
#include "pal.h"
#endif // FEATURE_PAL

#ifdef WIN32
#define EXPORT_API __declspec(dllexport)
#define SPLITTER W(";")
#else
#define EXPORT_API __attribute__((visibility("default")))
#define SPLITTER W(":")
#endif

ICLRRuntimeHost2* g_CLRRuntimeHost;
MonoDomain* g_RootDomain;
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

CrstStatic g_gc_handles_lock;

char s_AssemblyDir[MAX_PATH] = { 0 };
char s_EtcDir[MAX_PATH] = { 0 };
char s_AssemblyPaths[4096] = { 0 };

// Import this function manually as it is not defined in a header
extern "C" HRESULT  GetCLRRuntimeHost(REFIID riid, IUnknown **ppUnk);

#define ASSERT_NOT_IMPLEMENTED

struct MonoCustomAttrInfo_clr
{
    OBJECTREF typeInfo;
    MethodDesc* getCustomAttributes;
};

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
typedef Thread MonoThread_clr;
typedef MethodDesc MonoMethodSignature_clr;

static inline MonoType_clr MonoType_clr_from_MonoType(MonoType* type)
{
    return MonoType_clr::FromPtr(type);
}

static inline MonoType* MonoType_clr_to_MonoType(MonoType_clr type)
{
    return (MonoType*)type.AsPtr();
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
    ASSERT_NOT_IMPLEMENTED;
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_thread_pool_cleanup()
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_threads_set_shutting_down()
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" void mono_runtime_set_shutting_down()
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" gboolean mono_runtime_is_shutting_down()
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO not used
    return FALSE;
}

extern "C" gboolean mono_domain_finalize(MonoDomain *domain, int timeout)
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO not used
    return TRUE;
}

extern "C" void mono_runtime_cleanup(MonoDomain *domain)
{
    ASSERT_NOT_IMPLEMENTED;
    //TODO not used
}

extern "C" MonoMethod* mono_object_get_virtual_method(MonoObject *obj, MonoMethod *method)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_verifier_set_mode(MiniVerifierMode)
{
    // NOP
    //TODO used in Runtime\Mono\MonoManager.cpp SetSecurityMode()
}

extern "C" void mono_security_set_mode(MonoSecurityMode)
{
    // NOP
    //TODO used in Runtime\Mono\MonoManager.cpp SetSecurityMode()
}

extern "C" void mono_add_internal_call(const char *name, gconstpointer method)
{
    assert(name != nullptr);
    assert(method != nullptr);

    ECall::RegisterICall(name, (PCODE)method);
}

extern "C" void mono_jit_cleanup(MonoDomain *domain)
{
    //TODO used once in Runtime\Mono\MonoManager.cpp CleanupMono()
}

extern "C" MonoDomain* mono_jit_init(const char *file)
{
    return mono_jit_init_version(file, "4.0");
}

void list_tpa(const wchar_t* searchPath, SString& tpa)
{
    SString searchPattern = searchPath;
    searchPattern += W("/*.dll");
    WIN32_FIND_DATAW findData;
    HANDLE fileHandle = FindFirstFileW(searchPattern.GetUnicode(), &findData);

    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            wchar_t pathToAdd[MAX_PATH];
            wcscpy_s(pathToAdd, MAX_PATH, searchPath);
            wcscat_s(pathToAdd, MAX_PATH, W("/"));
            wcscat_s(pathToAdd, MAX_PATH, findData.cFileName);

            tpa += pathToAdd;
            tpa += SPLITTER;
        } while (FindNextFileW(fileHandle, &findData));
        FindClose(fileHandle);
    }
}

extern "C" MonoDomain* mono_jit_init_version(const char *file, const char* runtime_version)
{
    g_gc_handles_lock.Init(CrstMonoHandles);

    if (!g_CLRRuntimeHost)
    {
#if defined(__APPLE__)
        uint32_t lenActualPath = 0;
        const char* entrypointExecutable = "/dev/null";
        /*if (_NSGetExecutablePath(nullptr, &lenActualPath) == -1)
        {
            // OSX has placed the actual path length in lenActualPath,
            // so re-attempt the operation
            entrypointExecutable = new char[lenActualPath + 1];
            entrypointExecutable[lenActualPath] = '\0';
            if (_NSGetExecutablePath(entrypointExecutable, &lenActualPath) == -1)
            {
                delete [] entrypointExecutable;
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }*/

        DWORD error = PAL_InitializeCoreCLR(entrypointExecutable);

        // If PAL initialization failed, then we should return right away and avoid
        // calling any other APIs because they can end up calling into the PAL layer again.
        if (error != S_OK)
        {
            return nullptr;
        }
#endif
        HRESULT hr;
        hr = GetCLRRuntimeHost(IID_ICLRRuntimeHost2, (IUnknown**)&g_CLRRuntimeHost);

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
            W("NATIVE_DLL_SEARCH_DIRECTORIES")
        };

        wchar_t appPath[MAX_PATH] = { 0 };
        Wsz_mbstowcs(appPath, s_AssemblyDir, MAX_PATH);

        wchar_t etcPath[MAX_PATH] = { 0 };
        Wsz_mbstowcs(etcPath, s_EtcDir, MAX_PATH);

        wchar_t assemblyPaths[4096] = { 0 };
        Wsz_mbstowcs(assemblyPaths, s_AssemblyPaths, 4096);

        SString tpa;
        list_tpa(appPath, tpa);

        SString appPaths;
        appPaths += appPath;
        appPaths += SPLITTER;
        appPaths += assemblyPaths;

        SString appNiPaths;
        appNiPaths += appPath;
        appNiPaths+= SPLITTER;
        appNiPaths += appPath;

        SString nativeDllSearchDirs;
        nativeDllSearchDirs += appPath;
        nativeDllSearchDirs += SPLITTER;
        nativeDllSearchDirs += etcPath;

        const wchar_t *property_values[] = {
                  tpa.GetUnicode(),
                  appPaths,
                  appNiPaths.GetUnicode(),
                  nativeDllSearchDirs.GetUnicode()
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
    ASSERT_NOT_IMPLEMENTED;
    return 0;
}

extern "C" void* mono_jit_info_get_code_start(void* jit)
{
    ASSERT_NOT_IMPLEMENTED;
    // TODO used 1 by instrumentation unity/mono profiler
    // Runtime\Profiler\Instrumentation\InstrumentationProfiler.cpp(292)
    return NULL;
}

extern "C" int mono_jit_info_get_code_size(void* jit)
{
    ASSERT_NOT_IMPLEMENTED;
    // TODO used 1 by instrumentation unity/mono profiler
    // Runtime\Profiler\Instrumentation\InstrumentationProfiler.cpp(292)
    return 0;
}

MonoClass * mono_class_from_name(MonoImage *image, const char* name_space, const char *name, bool ignoreCase)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
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
    SString::Iterator i = className.Begin();
    while (className.Find(i, W('/')))
    {
        className.Replace(i, W('+'));
    }
    SString fullTypeName(nameSpace, dot, className);

    TypeHandle retTypeHandle1 = TypeName::GetTypeFromAssembly(fullTypeName.GetUnicode(), assembly, FALSE);

    if (!retTypeHandle1.IsNull())
    {
        return (MonoClass*)retTypeHandle1.AsMethodTable();
    }

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
        THROWS;
        GC_TRIGGERS;
        // We don't support multiple domains
        PRECONDITION(domain == g_RootDomain);
        PRECONDITION(domain != nullptr);
        PRECONDITION(name != nullptr);
    }
    CONTRACTL_END;

    SString assemblyPath(SString::Utf8, name);
    auto domain_clr = (MonoDomain_clr*)domain;
    auto assembly = AssemblySpec::LoadAssembly(assemblyPath.GetUnicode());
    assembly->EnsureActive();
    //auto domainAssembly = assembly->GetDomainAssembly((MonoDomain_clr*)domain);
    return (MonoAssembly*)assembly;
}

extern "C" MonoDomain * mono_domain_create_appdomain(const char *domainname, const char* configfile)
{
    ASSERT_NOT_IMPLEMENTED;
    // TODO used mostly in Runtime\Mono\MonoManager.cpp   MonoManager::CreateAndSetChildDomain()
    // to load script assemblies
    return NULL;
}

extern "C" void mono_domain_unload(MonoDomain* domain)
{
    ASSERT_NOT_IMPLEMENTED;
    // TODO used mainly in Runtime\Mono\MonoManager.cpp UnloadDomain() to unload from the current domain
}

extern "C" MonoObject* mono_object_new(MonoDomain *domain, MonoClass *klass)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
        PRECONDITION(domain != NULL);
        PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    {
        GCX_COOP();
        OBJECTREF objectRef = AllocateObject((MethodTable*)klass);
        return (MonoObject*)OBJECTREFToObject(objectRef);
    }
}

extern "C" void mono_runtime_object_init(MonoObject *this_obj)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
        PRECONDITION(this_obj != NULL);
    }
    CONTRACTL_END;

    GCX_COOP();

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
    MethodTable* ptable;
    GCX_COOP();
    OBJECTREF objref = ObjectToOBJECTREF((Object*)obj);

    auto method_clr = (MonoMethod_clr*)method;

    MetaSig     methodSig(method_clr);
    DWORD numArgs = methodSig.NumFixedArgs();
    ArgIterator argIt(&methodSig);

    const int MAX_ARG_SLOT = 128;
    ARG_SLOT argslots[MAX_ARG_SLOT];

    DWORD slotIndex = 0;
    if (methodSig.HasThis())
    {
        argslots[0] = ObjToArgSlot(objref);
        slotIndex++;
    }

    PVOID pRetBufStackCopy = NULL;
    auto retTH = methodSig.GetRetTypeHandleNT();
    CorElementType retType = retTH.GetInternalCorElementType();

    auto hasReturnBufferArg = argIt.HasRetBuffArg();
    if (hasReturnBufferArg)
    {
        SIZE_T sz = retTH.GetMethodTable()->GetNumInstanceFieldBytes();
        pRetBufStackCopy = _alloca(sz);
        memset(pRetBufStackCopy, 0, sz);
        argslots[slotIndex] = PtrToArgSlot(pRetBufStackCopy);
        slotIndex++;
    }

    for (DWORD argIndex = 0; argIndex < numArgs; argIndex++, slotIndex++)
    {
        int ofs = argIt.GetNextOffset();
        _ASSERTE(ofs != TransitionBlock::InvalidOffset);
        auto stackSize = argIt.GetArgSize();

        auto argTH = methodSig.GetLastTypeHandleNT();
        auto argType = argTH.GetInternalCorElementType();

        // TODO: Factorize ValueType detection and Managed detection
        switch (argType)
        {
        case ELEMENT_TYPE_VALUETYPE:
        case ELEMENT_TYPE_BOOLEAN:      // boolean
        case ELEMENT_TYPE_I1:           // byte
        case ELEMENT_TYPE_U1:
        case ELEMENT_TYPE_I2:           // short
        case ELEMENT_TYPE_U2:
        case ELEMENT_TYPE_CHAR:         // char
        case ELEMENT_TYPE_I4:           // int
        case ELEMENT_TYPE_U4:
        case ELEMENT_TYPE_I8:           // long
        case ELEMENT_TYPE_U8:
        case ELEMENT_TYPE_R4:           // float
        case ELEMENT_TYPE_R8:           // double
        case ELEMENT_TYPE_I:
        case ELEMENT_TYPE_U:
            switch (stackSize)
            {
            case 1:
            case 2:
            case 4:
                argslots[slotIndex] = *(INT32*)params[argIndex];
                break;

            case 8:
                argslots[slotIndex] = *(INT64*)params[argIndex];
                break;

            default:
                if (stackSize > sizeof(ARG_SLOT))
                {
                    argslots[slotIndex] = PtrToArgSlot(params[argIndex]);
                }
                else
                {
                    CopyMemory(&argslots[slotIndex], params[argIndex], stackSize);
                }
                break;
            }
            break;
        case ELEMENT_TYPE_BYREF:
            argslots[slotIndex] = PtrToArgSlot(params[argIndex]);
            break;
        case ELEMENT_TYPE_PTR:
            argslots[slotIndex] = PtrToArgSlot(*(void**)params[argIndex]);
            break;
        case ELEMENT_TYPE_STRING:
        case ELEMENT_TYPE_OBJECT:
        case ELEMENT_TYPE_CLASS:
        case ELEMENT_TYPE_ARRAY:
        case ELEMENT_TYPE_SZARRAY:
        case ELEMENT_TYPE_VAR:
            argslots[slotIndex] = ObjToArgSlot(ObjectToOBJECTREF((MonoObject_clr*)params[argIndex]));
            break;
        default:
            assert(false && "This argType is not supported");
            break;
        }
    }

    MethodDescCallSite invoker((MonoMethod_clr*)method, &objref);

    // TODO: Convert params to ARG_SLOT
    ARG_SLOT result = invoker.Call_RetArgSlot(argslots);

    methodSig.Reset();
    if (methodSig.IsReturnTypeVoid())
    {
        return nullptr;
    }

    // Check reflectioninvocation.cpp
    // TODO: Handle 
    switch (retType)
    {
        case ELEMENT_TYPE_VALUETYPE:
        case ELEMENT_TYPE_BOOLEAN:      // boolean
        case ELEMENT_TYPE_I1:           // byte
        case ELEMENT_TYPE_U1:
        case ELEMENT_TYPE_I2:           // short
        case ELEMENT_TYPE_U2:
        case ELEMENT_TYPE_CHAR:         // char
        case ELEMENT_TYPE_I4:           // int
        case ELEMENT_TYPE_U4:
        case ELEMENT_TYPE_I8:           // long
        case ELEMENT_TYPE_U8:
        case ELEMENT_TYPE_R4:           // float
        case ELEMENT_TYPE_R8:           // double
        case ELEMENT_TYPE_I:
        case ELEMENT_TYPE_U:
        case ELEMENT_TYPE_PTR:
            if (hasReturnBufferArg)
            {                
                return (MonoObject*)OBJECTREFToObject(retTH.GetMethodTable()->Box(pRetBufStackCopy));
            }
            else 
            {
                return (MonoObject*)OBJECTREFToObject(retTH.GetMethodTable()->Box(&result));
            }
            break;
        case ELEMENT_TYPE_STRING:
        case ELEMENT_TYPE_OBJECT:
        case ELEMENT_TYPE_CLASS:
        case ELEMENT_TYPE_ARRAY:
        case ELEMENT_TYPE_SZARRAY:
        case ELEMENT_TYPE_VAR:
            return (MonoObject*)OBJECTREFToObject(ArgSlotToObj(result));
            break;
        default:
            assert(false && "This retType is not supported");
            break;
    }
    return nullptr;
}

extern "C" void mono_field_set_value(MonoObject *obj, MonoClassField *field, void *value)
{
    // TODO: Add contact
    // TODO: obj not protected?
    GCX_COOP();
    OBJECTREF objectRef = ObjectToOBJECTREF((MonoObject_clr*)obj);
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
    GCX_COOP();
    OBJECTREF objectRef = ObjectToOBJECTREF((MonoObject_clr*)obj);
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
        THROWS;
        GC_NOTRIGGER;
        PRECONDITION(klass != NULL);
    }
    CONTRACTL_END;

    if (!iter)
    {
        return NULL;
    }
    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;

    ApproxFieldDescIterator* iterator = (ApproxFieldDescIterator*)*iter;
    if (iterator == nullptr)
    {
        iterator = new ApproxFieldDescIterator(klass_clr, ApproxFieldDescIterator::INSTANCE_FIELDS | ApproxFieldDescIterator::STATIC_FIELDS);
        *iter = iterator;
    }

    auto nextField = iterator->Next();
    if (nextField == nullptr)
    {
        *iter = nullptr;
        delete iterator;
        return nullptr;
    }

    return (MonoClassField*)nextField;
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
        THROWS;
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
        *iter = iterator;
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
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_image_close(MonoImage *image)
{
    // NOP
}

extern "C" void mono_unity_socket_security_enabled_set(gboolean)
{
    // NOP
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

#if PLATFORM_WIN || PLATFORM_OSX || PLATFORM_ANDROID || PLATFORM_TIZEN || PLATFORM_STV || PLATFORM_LINUX
extern "C" void mono_set_signal_chaining(gboolean)
{
    // NOP
}

#endif
#if PLATFORM_WIN
extern "C" long mono_unity_seh_handler(EXCEPTION_POINTERS*)
{
    ASSERT_NOT_IMPLEMENTED;
    return 0;
}

extern "C" void mono_unity_set_unhandled_exception_handler(void*)
{
    ASSERT_NOT_IMPLEMENTED;
}

#endif

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" void mono_set_commandline_arguments(int, const char* argv[], const char*)
{
    ASSERT_NOT_IMPLEMENTED;
    // TODO (used)
}

#endif

#if USE_MONO_AOT
extern "C" void* mono_aot_get_method(MonoDomain *domain, MonoMethod *method)
{
    ASSERT_NOT_IMPLEMENTED;
}

#endif
//DO_API(MonoMethod*, mono_marshal_get_xappdomain_invoke, (MonoMethod*))

// Type-safe way of looking up methods based on method signatures
extern "C" MonoObject* mono_runtime_invoke_array(MonoMethod *method, void *obj, MonoArray *params, MonoException **exc)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" char* mono_array_addr_with_size(MonoArray *array, int size, uintptr_t idx)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

#define mono_array_addr(array,type,index) ((type*)(void*) mono_array_addr_with_size (array, sizeof (type), index))

#if UNITY_EDITOR
extern "C" MonoMethodDesc* mono_method_desc_new(const char *name, gboolean include_namespace)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoMethod* mono_method_desc_search_in_class(MonoMethodDesc* desc, MonoClass* klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_method_desc_free(MonoMethodDesc* desc)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" char* mono_type_get_name_full(MonoType *type, MonoTypeNameFormat format)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

#endif

#if PLATFORM_WIN || PLATFORM_XBOXONE
extern "C" gunichar2* mono_string_to_utf16(MonoString *string_obj)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

#endif

extern "C" const char* mono_field_get_name(MonoClassField *field)
{
    CONTRACTL
    {
        THROWS;
        GC_NOTRIGGER;
        MODE_ANY;
    }
    CONTRACTL_END
    auto field_clr = (MonoClassField_clr*)field;
    return field_clr->GetName();
}

extern "C" MonoClass* mono_field_get_parent(MonoClassField *field)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoType* mono_field_get_type(MonoClassField *field)
{
    CONTRACTL
    {
        PRECONDITION(field != NULL);
    }
    CONTRACTL_END;
             
    auto field_clr = (MonoClassField_clr*)field;

    MonoType_clr typeHandle = field_clr->GetFieldTypeHandleThrowing();

    return MonoType_clr_to_MonoType(typeHandle);
}

extern "C" int mono_type_get_type(MonoType *type)
{
    TypeHandle typeHandle = TypeHandle::FromPtr((PTR_VOID)type);
    auto elementType = typeHandle.GetMethodTable()->GetVerifierCorElementType();

    switch(elementType)
    {
        case ELEMENT_TYPE_VOID:
            return MONO_TYPE_VOID;
        case ELEMENT_TYPE_END:
            return MONO_TYPE_END;
        case ELEMENT_TYPE_PTR:
            return MONO_TYPE_PTR;
        case ELEMENT_TYPE_BYREF:
            return MONO_TYPE_BYREF;
        case ELEMENT_TYPE_STRING:
            return MONO_TYPE_STRING;
        case ELEMENT_TYPE_R4:
            return MONO_TYPE_R4;
        case ELEMENT_TYPE_R8:
            return MONO_TYPE_R8;
        case ELEMENT_TYPE_I8:
            return MONO_TYPE_I8;
        case ELEMENT_TYPE_I4:
            return MONO_TYPE_I4;
        case ELEMENT_TYPE_I2:
            return MONO_TYPE_I2;
        case ELEMENT_TYPE_I1:
            return MONO_TYPE_I1;
        case ELEMENT_TYPE_U8:
            return MONO_TYPE_U8;
        case ELEMENT_TYPE_U4:
            return MONO_TYPE_U4;
        case ELEMENT_TYPE_U2:
            return MONO_TYPE_U2;
        case ELEMENT_TYPE_U1:
            return MONO_TYPE_U1;
        case ELEMENT_TYPE_CLASS:
            return MONO_TYPE_CLASS;
        case ELEMENT_TYPE_BOOLEAN:
            return MONO_TYPE_BOOLEAN;
        case ELEMENT_TYPE_CHAR:
            return MONO_TYPE_CHAR;
        case ELEMENT_TYPE_VALUETYPE:
            return MONO_TYPE_VALUETYPE;
        case ELEMENT_TYPE_VAR:
            return MONO_TYPE_VAR;
        case ELEMENT_TYPE_ARRAY:
            return MONO_TYPE_ARRAY;
        case ELEMENT_TYPE_GENERICINST:
            return MONO_TYPE_GENERICINST;
        case ELEMENT_TYPE_TYPEDBYREF:
            return MONO_TYPE_TYPEDBYREF;
        case ELEMENT_TYPE_I:
            return MONO_TYPE_I;
        case ELEMENT_TYPE_U:
            return MONO_TYPE_U;
        case ELEMENT_TYPE_FNPTR:
            return MONO_TYPE_FNPTR;
        case ELEMENT_TYPE_OBJECT:
            return MONO_TYPE_OBJECT;
        case ELEMENT_TYPE_SZARRAY:
            return MONO_TYPE_SZARRAY;
        case ELEMENT_TYPE_MVAR:
            return MONO_TYPE_MVAR;
        case ELEMENT_TYPE_CMOD_REQD:
            return MONO_TYPE_CMOD_REQD;
        case ELEMENT_TYPE_CMOD_OPT:
            return MONO_TYPE_CMOD_OPT;
        case ELEMENT_TYPE_INTERNAL:
            return MONO_TYPE_INTERNAL;
        case ELEMENT_TYPE_MODIFIER:
            return MONO_TYPE_MODIFIER;
        case ELEMENT_TYPE_SENTINEL:
            return MONO_TYPE_SENTINEL;
        case ELEMENT_TYPE_PINNED:
            return MONO_TYPE_PINNED;
        default:
            return 0;
    }
}

extern "C" const char* mono_method_get_name(MonoMethod *method)
{
    return reinterpret_cast<MonoMethod_clr*>(method)->GetName();
}

extern "C" char* mono_method_full_name(MonoMethod* method, gboolean signature)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
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
    MonoMethodSignature_clr* msig = (MonoMethodSignature_clr*)sig;
    MetaSig metasig(msig);
    return metasig.NumFixedArgs();
}

extern "C" char* mono_string_to_utf8(MonoString *string_obj)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoString* mono_string_new_wrapper(const char* text)
{
    assert(text != nullptr);
    SString sstr(SString::Utf8, text);
    GCX_COOP();
    return (MonoString*)OBJECTREFToObject(AllocateString(sstr));
}

extern "C" MonoString* mono_string_new_len(MonoDomain *domain, const char *text, guint32 length)
{
    assert(text != nullptr);
    SString sstr(SString::Utf8, text);
    GCX_COOP();
    STRINGREF strObj = AllocateString(length);
    memcpyNoGCRefs(strObj->GetBuffer(), sstr.GetUnicode(), sstr.GetCount() * sizeof(WCHAR));
    return (MonoString*)OBJECTREFToObject(strObj);
}

extern "C" MonoString* mono_string_from_utf16(const gunichar2* text)
{
    assert(text != nullptr);
    SString sstr((const WCHAR*)text);
    GCX_COOP();
    return (MonoString*)OBJECTREFToObject(AllocateString(sstr));
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
        if (check_interfaces)
        {
            auto ifaceIter = clazz->IterateInterfaceMap();
            while (ifaceIter.Next())
                if (ifaceIter.GetInterface() == (MonoClass_clr*)klassc)
                    return TRUE;
        }
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
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_type_get_class(MonoType *type)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoException * mono_exception_from_name_msg(MonoImage *image, const char *name_space, const char *name, const char *msg)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoException * mono_exception_from_name_two_strings(MonoImage *image, const char *name_space, const char *name, const char *msg1, const char *msg2)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoException * mono_get_exception_argument_null(const char *arg)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_raise_exception(MonoException *ex)
{
}

extern "C" MonoClass* mono_get_exception_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_array_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_string_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_boolean_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_byte_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_char_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_int16_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_int32_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_int64_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_single_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoClass* mono_get_double_class()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoArray* mono_array_new(MonoDomain *domain, MonoClass *eclass, guint32 n)
{
    CONTRACTL{
        THROWS;
        GC_TRIGGERS;
        PRECONDITION(domain != nullptr);
        PRECONDITION(eclass != nullptr);
    } CONTRACTL_END;

    GCX_COOP();
    // TODO: handle large heap flag?
    auto arrayRef = AllocateObjectArray(n, (MonoClass_clr*)eclass);
    return (MonoArray*)OBJECTREFToObject(arrayRef);;
}

extern "C" MonoArray* mono_array_new_full(MonoDomain *domain, MonoClass *array_class, guint32 *lengths, guint32 *lower_bounds)
{
    ASSERT_NOT_IMPLEMENTED;
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

    TypeHandle typeHandle(reinterpret_cast<MonoClass_clr*>(eclass));
    auto arrayMT = typeHandle.MakeArray(rank);

    return (MonoClass*)arrayMT.GetMethodTable();
}

extern "C" gint32 mono_class_array_element_size(MonoClass *ac)
{
    CONTRACTL{
        STANDARD_VM_CHECK;
        PRECONDITION(ac != nullptr);
    } CONTRACTL_END;
    auto ac_clr = (MonoClass_clr*)ac;

    // TODO: Is it really the method to use?
    DWORD s = ac_clr->GetBaseSize();
    return s;
}

extern "C" MonoObject* mono_type_get_object(MonoDomain *domain, MonoType *type)
{
    MonoType_clr* clrType = reinterpret_cast<MonoType_clr*>(type);
    return (MonoObject*) OBJECTREFToObject(clrType->GetManagedClassObject());
}

extern "C" gboolean mono_class_is_generic(MonoClass* klass)
{
    CONTRACTL{
        PRECONDITION(klass != nullptr);
    } CONTRACTL_END;
    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;
    return klass_clr->IsGenericTypeDefinition();
}

extern "C" gboolean mono_class_is_inflated(MonoClass* klass)
{
    CONTRACTL{
        PRECONDITION(klass != nullptr);
    } CONTRACTL_END;
    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;
    // TODO: is it really the concept behind inflated? (generic instance?)
    return klass_clr->HasInstantiation();
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" gboolean unity_mono_method_is_generic(MonoMethod* method)
{
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

extern "C" gboolean unity_mono_method_is_inflated(MonoMethod* method)
{
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

#endif

extern "C" MonoThread * mono_thread_attach(MonoDomain *domain)
{
    CONTRACTL{
        PRECONDITION(domain == g_RootDomain);
    } CONTRACTL_END;
    auto domain_clr = (MonoDomain_clr*)domain;
    MonoThread_clr* currentThread = GetThread();

    assert(domain_clr->CanThreadEnter(currentThread));

    return (MonoThread*)currentThread;
}

extern "C" void mono_thread_detach(MonoThread *thread)
{
    CONTRACTL{
        PRECONDITION(thread != nullptr);
    } CONTRACTL_END;
    auto thread_clr = (MonoThread_clr*)thread;
    // TODO: FALSE or TRUE there?
    thread_clr->DetachThread(FALSE);
}

extern "C" MonoThread * mono_thread_exit()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoThread * mono_thread_current(void)
{
    return (MonoThread*)GetThread();
}

extern "C" void mono_thread_set_main(MonoThread* thread)
{
    CONTRACTL{
        PRECONDITION(thread != nullptr);
    } CONTRACTL_END;
    auto thread_clr = (MonoThread_clr*)thread;
    // almost NOP
    assert(AppDomain::GetCurrentDomain()->CanThreadEnter(thread_clr));
}

extern "C" void mono_set_find_plugin_callback(gconstpointer method)
{
    // NOP
}

extern "C" void mono_security_enable_core_clr()
{
    ASSERT_NOT_IMPLEMENTED;
}

typedef gboolean(*MonoCoreClrPlatformCB) (const char *image_name);
extern "C" void mono_security_set_core_clr_platform_callback(MonoCoreClrPlatformCB)
{
    // NOP
}

#if MONO_2_12
extern "C" void mono_security_core_clr_set_options(MonoSecurityCoreCLROptions)
{
    ASSERT_NOT_IMPLEMENTED;
}

#endif

extern "C" void mono_runtime_unhandled_exception_policy_set(MonoRuntimeUnhandledExceptionPolicy policy)
{
    // NOP
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
    MonoClass_clr* klass_clr = (MonoClass_clr*)klass;
    if (!klass_clr->GetClass()->IsNested())
    {
        return nullptr;
    }
    MonoClass_clr* ret = ClassLoader::LoadTypeDefOrRefOrSpecThrowing(klass_clr->GetModule(), klass_clr->GetEnclosingCl(), NULL).AsMethodTable();
    return (MonoClass*)ret;
}

extern "C" MonoVTable* mono_class_vtable(MonoDomain *domain, MonoClass *klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoReflectionMethod* mono_method_get_object(MonoDomain *domain, MonoMethod *method, MonoClass *refclass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoMethodSignature* mono_method_signature(MonoMethod *method)
{
    return (MonoMethodSignature*)method;
}

extern "C" MonoType* mono_signature_get_params(MonoMethodSignature *sig, gpointer *iter)
{
    MonoMethodSignature_clr* signature = (MonoMethodSignature_clr*)sig;
    MetaSig* metasig = (MetaSig*)*iter;
    if (metasig == NULL)
    {
        metasig = new MetaSig(signature);
        *iter = metasig;
    }

    CorElementType argType = metasig->NextArg();
    if (argType == ELEMENT_TYPE_END)
    {
        delete metasig;
        *iter = NULL;
        return NULL;
    }

    TypeHandle typeHandle = metasig->GetLastTypeHandleThrowing();
    return (MonoType*)typeHandle.AsPtr();
}

extern "C" MonoType* mono_signature_get_return_type(MonoMethodSignature *sig)
{
    MonoMethodSignature_clr* signature = (MonoMethodSignature_clr*)sig;
    MetaSig msig(signature);
    TypeHandle reth = msig.GetRetTypeHandleThrowing();
    return (MonoType*)reth.AsPtr();
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
    ASSERT_NOT_IMPLEMENTED;
}

#endif
extern "C" void mono_debug_init(int format)
{
    // NOP
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" gboolean mono_is_debugger_attached(void)
{
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

#endif

extern "C" void mono_debug_open_image_from_memory(MonoImage *image, const char *raw_contents, int size)
{
    // NOP
}

extern "C" guint32 mono_field_get_flags(MonoClassField *field)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoImage* mono_image_open_from_data_full(const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoImage* mono_image_open_from_data_with_name(char *data, guint32 data_len, gboolean need_copy, int *status, gboolean refonly, const char *name)
{
    // TODO: not sure this is the correct way
    MonoImage_clr* assembly = AssemblyNative::LoadFromBuffer(FALSE, (const BYTE*)data, data_len, nullptr, 0, nullptr, nullptr, kCurrentAppDomain);
    return (MonoImage*)assembly;
}

extern "C" MonoAssembly * mono_assembly_load_from(MonoImage *image, const char*fname, int *status)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" gboolean mono_assembly_fill_assembly_name(MonoImage *image, MonoAssemblyName *aname)
{
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

extern "C" char* mono_stringify_assembly_name(MonoAssemblyName *aname)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" int mono_assembly_name_parse(const char* name, MonoAssemblyName *assembly)
{
    assembly->name = name;
    return 1;
}

extern "C" MonoAssembly* mono_assembly_loaded(MonoAssemblyName *aname)
{
    AppDomain::AssemblyIterator assemblyIterator = SystemDomain::GetCurrentDomain()->IterateAssembliesEx((AssemblyIterationFlags)(
            kIncludeExecution | kIncludeLoaded | kIncludeCollected));

    CollectibleAssemblyHolder<DomainAssembly *> pDomainAssembly;
    while (assemblyIterator.Next(pDomainAssembly.This()))
    {
        auto simpleName = pDomainAssembly->GetSimpleName();
        if (strcmp(simpleName, aname->name) == 0)
        {
            return (MonoAssembly*)pDomainAssembly->GetAssembly();
        }
    }
    return NULL;
}

extern "C" int mono_image_get_table_rows(MonoImage *image, int table_id)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

extern "C" MonoObject * mono_value_box(MonoDomain *domain, MonoClass *klass, gpointer val)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoImage* mono_class_get_image(MonoClass *klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" char mono_signature_is_instance(MonoMethodSignature *sig)
{
    MonoMethodSignature_clr* sig_clr = (MonoMethodSignature_clr*)sig;
    MetaSig msig(sig_clr);
    return msig.HasThis();
}

extern "C" MonoMethod* mono_method_get_last_managed()
{
    // NOP
    return NULL;
}

extern "C" MonoClass* mono_get_enum_class()
{
    MonoImage* img = mono_get_corlib();
    return mono_class_from_name(img, "System", "Enum");
}

extern "C" MonoType* mono_class_get_byref_type(MonoClass *klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_field_static_get_value(MonoVTable *vt, MonoClassField *field, void *value)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_set_embeddinghostname(const char* name)
{
    // NOP
}

extern "C" void mono_set_assemblies_path(const char* name)
{
    strcpy(s_AssemblyPaths, name);
}


guint32 handleId = 0;
struct MonoHandleInfo
{
    MonoHandleInfo() : Handle(nullptr), Pinned(0)
    {
    }
    MonoHandleInfo(const MonoHandleInfo& copy) : Handle(copy.Handle), Pinned(copy.Pinned)
    {
    }
    OBJECTHANDLE Handle;
    gboolean Pinned;
};
MapSHashWithRemove<guint32, MonoHandleInfo> g_gc_map_id_to_handle;

extern "C" guint32 mono_gchandle_new(MonoObject *obj, gboolean pinned)
{
    CONTRACTL
    {
        PRECONDITION(obj != NULL);
    }
    CONTRACTL_END;

    GCX_COOP();
    // TODO: This method is not accurate with Cooperative/Preemptive mode

    // NOTE
    // mono is using a guint32 to identify an GCHandle
    // while coreclr is using a OBJECTHANDLE which is a pointer
    // so we are maintaining a map here between an generated identifier
    // and the OBJECTHANDLE
    CrstHolder lock(&g_gc_handles_lock);

    auto objref = ObjectToOBJECTREF((MonoObject_clr*)obj);
    OBJECTHANDLE rawHandle = pinned ?
        GetAppDomain()->CreatePinningHandle(objref) :
        GetAppDomain()->CreateHandle(objref);
    MonoHandleInfo objhandle;
    objhandle.Handle = rawHandle;
    objhandle.Pinned = pinned;

    auto id = ++handleId;
    g_gc_map_id_to_handle.Add(id, objhandle);
    
    return id;
}

extern "C" void mono_gchandle_free(guint32 gchandle)
{
    CrstHolder lock(&g_gc_handles_lock);

    MonoHandleInfo handle;
    if (g_gc_map_id_to_handle.Lookup(gchandle, &handle))
    {
        if (handle.Pinned)
        {
            DestroyPinningHandle(handle.Handle);
        }
        else
        {
            DestroyHandle(handle.Handle);
        }
        g_gc_map_id_to_handle.Remove(gchandle);
    }
}


extern "C" MonoObject* mono_gchandle_get_target(guint32 gchandle)
{
    GCX_COOP();
    // TODO: This method is not accurate with Cooperative/Preemptive mode

    CrstHolder lock(&g_gc_handles_lock);

    MonoHandleInfo handle;
    if (g_gc_map_id_to_handle.Lookup(gchandle, &handle))
    {
        OBJECTREF objref = ObjectFromHandle(handle.Handle);
        return (MonoObject*)OBJECTREFToObject(objref);
    }

    // throw an error?
    return NULL;
}

extern "C" guint32 mono_gchandle_new_weakref(MonoObject *obj, gboolean track_resurrection)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" gboolean mono_gchandle_is_in_domain(guint32 gchandle, MonoDomain *domain)
{
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

extern "C" MonoObject* mono_assembly_get_object(MonoDomain *domain, MonoAssembly *assembly)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

typedef gboolean(*MonoStackWalk) (MonoMethod *method, gint32 native_offset, gint32 il_offset, gboolean managed, gpointer data);
extern "C" void mono_stack_walk(MonoStackWalk func, gpointer user_data)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" char* mono_pmip(void *ip)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoObject* mono_runtime_delegate_invoke(MonoObject *delegate, void **params, MonoException **exc)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoJitInfo* mono_jit_info_table_find(MonoDomain* domain, void* ip)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoDebugSourceLocation* mono_debug_lookup_source_location(MonoMethod* method, guint32 address, MonoDomain* domain)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_debug_free_source_location(MonoDebugSourceLocation* location)
{
}

//DO_API (void,GC_free,(void* p))
//DO_API(void*,GC_malloc_uncollectable,(int size))
extern "C" MonoProperty* mono_class_get_properties(MonoClass* klass, gpointer *iter)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoMethod* mono_property_get_get_method(MonoProperty *prop)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoObject * mono_object_new_alloc_specific(MonoVTable *vtable)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoObject * mono_object_new_specific(MonoVTable *vtable)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_gc_collect(int generation)
{
    FCALL_CONTRACT;
    _ASSERTE(generation >= -1);
    GCHeapUtilities::GetGCHeap()->GarbageCollect(generation, false, collection_blocking);
}

extern "C" int mono_gc_max_generation()
{
    FCALL_CONTRACT;
    return GCHeapUtilities::GetGCHeap()->GetMaxGeneration();
}

extern "C" gint64 mono_gc_get_used_size()
{
    FCALL_CONTRACT;
    return GCHeapUtilities::GetGCHeap()->GetTotalBytesInUse();
}

extern "C" gint64 mono_gc_get_heap_size()
{
    FCALL_CONTRACT;
    // NOT CORRECT
    return GCHeapUtilities::GetGCHeap()->GetTotalBytesInUse();
}

extern "C" void mono_gc_wbarrier_generic_store(gpointer ptr, MonoObject* value)
{
}

extern "C" MonoAssembly* mono_image_get_assembly(MonoImage *image)
{
    return (MonoAssembly*)image;
}

extern "C" MonoAssembly* mono_assembly_open(const char *filename, int *status)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" gboolean mono_class_is_enum(MonoClass *klass)
{
    return (gboolean)reinterpret_cast<MonoClass_clr*>(klass)->IsEnum();
}

extern "C" MonoType* mono_class_enum_basetype(MonoClass *klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" gint32 mono_class_instance_size(MonoClass *klass)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoAssembly* mono_assembly_load_from_full(MonoImage *image, const char *fname, int *status, gboolean refonly)
{
    // TODO: As we are making MonoImage == MonoAssembly, return it as-is
    return (MonoAssembly*)image;
}

extern "C" MonoClass* mono_class_get_interfaces(MonoClass* klass, gpointer *iter)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_assembly_close(MonoAssembly *assembly)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" MonoProperty* mono_class_get_property_from_name(MonoClass *klass, const char *name)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoMethod* mono_class_get_method_from_name(MonoClass *klass, const char *name, int param_count)
{
    CONTRACTL
    {
        THROWS;
        GC_TRIGGERS;
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
            MetaSig     methodSig(method);

            DWORD numArgs = methodSig.NumFixedArgs();
            if (numArgs == param_count)
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
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_thread_push_appdomain_ref(MonoDomain *domain)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_thread_pop_appdomain_ref()
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" int mono_runtime_exec_main(MonoMethod *method, MonoArray *args, MonoObject **exc)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoImage* mono_get_corlib()
{
    char buf[MAX_PATH] = { 0 };
    sprintf_s(buf, COUNTOF(buf), "%s/%s", s_AssemblyDir, "mscorlib.dll");

    return (MonoImage*)mono_domain_assembly_open(g_RootDomain, buf);
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
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" int mono_parse_default_optimizations(const char* p)
{
    // NOP
    return 0;
}

extern "C" void mono_set_defaults(int verbose_level, guint32 opts)
{
    // NOP
}

extern "C" void mono_config_parse(const char *filename)
{
    // NOP
}

extern "C" void mono_set_dirs(const char *assembly_dir, const char *config_dir)
{
    strcpy(s_AssemblyDir, assembly_dir);
    strcpy(s_EtcDir, assembly_dir);
}

//DO_API(void,ves_icall_System_AppDomain_InternalUnload,(int domain_id))
//DO_API(MonoObject*,ves_icall_System_AppDomain_createDomain,(MonoString *friendly_name, MonoObject *setup))

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  June 2 2015
extern "C" void mono_set_break_policy(MonoBreakPolicyFunc policy_callback)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

extern "C" void mono_jit_parse_options(int argc, char * argv[])
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoArray* mono_custom_attrs_construct(MonoCustomAttrInfo *cinfo)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" gboolean mono_custom_attrs_has_attr(MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    MonoClass_clr* clrClass = reinterpret_cast<MonoClass_clr*>(ainfo);
    MonoClass_clr* attributeClass = reinterpret_cast<MonoClass_clr*>(attr_klass);

    LPCUTF8 name, namespaze;
	attributeClass->GetMDImport()->GetNameOfTypeDef(attributeClass->GetCl(), &name, &namespaze);

    char buf[512] = {0};
    sprintf_s(buf, COUNTOF(buf), "%s.%s", namespaze, name);

    return S_OK == clrClass->GetMDImport()->GetCustomAttributeByName(clrClass->GetCl(), buf, NULL, NULL);
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_field(MonoClass *klass, MonoClassField *field)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_method(MonoMethod *method)
{
    MonoMethod_clr* clrMethod = reinterpret_cast<MonoMethod_clr*>(method);

    return (MonoCustomAttrInfo*)clrMethod->GetMethodTable();
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_class(MonoClass *klass)
{
    MonoClass_clr* clrClass = reinterpret_cast<MonoClass_clr*>(klass);

    return (MonoCustomAttrInfo*)clrClass;
}

extern "C" MonoCustomAttrInfo* mono_custom_attrs_from_assembly(MonoAssembly *assembly)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoArray* mono_reflection_get_custom_attrs_by_type(MonoObject* object, MonoClass* klass)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_custom_attrs_free(MonoCustomAttrInfo* attr)
{
   
}

extern "C" void* mono_loader_get_last_error(void)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" MonoException* mono_loader_error_prepare_exception(void *error)
{
    ASSERT_NOT_IMPLEMENTED;
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
    return NULL;
}

extern "C" void mono_dl_fallback_unregister(MonoDlFallbackHandler *handler)
{
    ASSERT_NOT_IMPLEMENTED;
}

#	endif

#endif

typedef void(*vprintf_func)(const char* msg, va_list args);
extern "C" void mono_unity_set_vprintf_func(vprintf_func func)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void* mono_unity_liveness_allocate_struct(MonoClass* filter, int max_object_count, mono_register_object_callback callback, void* userdata)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

extern "C" void mono_unity_liveness_stop_gc_world()
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_liveness_finalize(void* state)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_liveness_start_gc_world()
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_liveness_free_struct(void* state)
{
    ASSERT_NOT_IMPLEMENTED;
}

#if USE_CONSOLEBRANCH_MONO
extern "C" void* mono_unity_liveness_calculation_begin(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
#else
extern "C" void* mono_unity_liveness_calculation_begin(MonoClass * filter, int max_object_count, mono_register_object_callback callback, void* userdata, mono_liveness_world_state_callback world_started_callback, mono_liveness_world_state_callback world_stopped_callback)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
#endif

extern "C" void mono_unity_liveness_calculation_end(void* state)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_liveness_calculation_from_root(MonoObject* root, void* state)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_unity_liveness_calculation_from_statics(void* state)
{
    ASSERT_NOT_IMPLEMENTED;
}

#if !USE_CONSOLEBRANCH_MONO
extern "C" MonoMethod* unity_mono_reflection_method_get_method(MonoReflectionMethod* mrf)
{
    ASSERT_NOT_IMPLEMENTED;
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
    // NOP
}

extern "C" void mono_profiler_set_events(int events)
{
    // NOP
}

extern "C" void mono_profiler_install_enter_leave(MonoProfileMethodFunc enter, MonoProfileMethodFunc fleave)
{
    // NOP
}

extern "C" void mono_profiler_install_gc(MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback)
{
    // NOP
}

extern "C" void mono_profiler_install_allocation(MonoProfileAllocFunc callback)
{
    // NOP
}

extern "C" void mono_profiler_install_jit_end(MonoProfileJitResult jit_end)
{
    // NOP
}

extern "C" void mono_profiler_install_thread(MonoProfileThreadFunc start, MonoProfileThreadFunc end)
{
    // NOP
}

//DO_API(void, mono_gc_base_init, ())
//DO_API(void, mono_profiler_install_statistical, (MonoProfileStatFunc callback))
//DO_API(void, mono_profiler_install_statistical_call_chain, (MonoProfileStatCallChainFunc callback, int call_chain_depth))
extern "C" void mono_profiler_install_exception(MonoProfileExceptionFunc throw_callback, MonoProfileMethodFunc exc_method_leave, MonoProfileExceptionClauseFunc clause_callback)
{
    // NOP
}

#endif

#if UNITY_IPHONE || UNITY_TVOS
extern "C" void mono_aot_register_module(void *aot_info)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
}
#else
extern "C" void g_free(void* p)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_trace_set_mask_string(const char *value)
{
    ASSERT_NOT_IMPLEMENTED;
}

#if UNITY_XBOXONE
extern "C" void mono_trace_set_level(GLogLevelFlags level)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_WIIU
extern "C" char* g_strdup_d(char const* str)
{
    ASSERT_NOT_IMPLEMENTED;
}

// specific allocations
#define g_free				console_g_free
#define g_free_d(x)			console_g_free(x)
#define g_strdup_d(x)		g_strdup(x)

extern "C" void* g_memdup(void const* mem, unsigned int byte_size)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" char* g_strdup(const char *str)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" gboolean mono_jit_set_trace_options(const char* options)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_PSP2 || UNITY_WIIU
// memory and string functions
extern "C" void* console_g_malloc(size_t size)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void* console_g_calloc(size_t size, size_t elemSize)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void* console_g_realloc(void *memblock, size_t size)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void console_g_free(void* p)
{
    ASSERT_NOT_IMPLEMENTED;
}
#define g_free console_g_free
#endif

#if UNITY_XBOXONE
extern "C" void mono_trace_enable(gboolean enable)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_PSP2 || UNITY_XBOXONE

#if !UNITY_XBOXONE
// Not defined in current mono-consoles,  Nov 25 2013
extern "C" void mono_set_corlib_data(void *data, size_t size)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

extern "C" void mono_runtime_set_no_exec(gboolean val)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void mono_jit_set_aot_only(gboolean val)
{
    ASSERT_NOT_IMPLEMENTED;
}

typedef MonoAssembly *(*MonoAssemblySearchFunc)         (char **aname, void* user_data);

extern "C" void mono_install_assembly_postload_search_hook(MonoAssemblySearchFunc func, gpointer user_data)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_WIIU || UNITY_XBOXONE
extern "C" void mono_runtime_set_main_args(const char** args, int num_args)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_OSX
extern "C" int mono_backtrace_from_context(void* context, void* array[], int count)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if ENABLE_MONO_MEMORY_CALLBACKS
extern "C" void unity_mono_install_memory_callbacks(MonoMemoryCallbacks* callbacks)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif

#if UNITY_PS4
extern "C" void unity_mono_set_thread_affinity(int aff)
{
    ASSERT_NOT_IMPLEMENTED;
}

extern "C" void unity_mono_set_thread_policy(int type, int policy)
{
    ASSERT_NOT_IMPLEMENTED;
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
    ASSERT_NOT_IMPLEMENTED;
    return FALSE;
}

#if PLATFORM_STANDALONE || UNITY_EDITOR
#if !PLATFORM_XBOXONE
extern "C" MonoDlFallbackHandler* mono_dl_fallback_register(MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
extern "C" void mono_dl_fallback_unregister(MonoDlFallbackHandler * handler)
{
    ASSERT_NOT_IMPLEMENTED;
}
#endif
#endif 

extern "C" MonoArray* mono_unity_array_new_2d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
extern "C" MonoArray* mono_unity_array_new_3d(MonoDomain * domain, MonoClass * eclass, size_t size0, size_t size1, size_t size2)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
extern "C" MonoClass* mono_unity_class_get(MonoImage * image, guint32 type_token)
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
extern "C" void mono_unity_domain_set_config(MonoDomain * domain, const char *base_dir, const char *config_file_name)
{
    ASSERT_NOT_IMPLEMENTED;
}
extern "C" MonoException* mono_unity_loader_get_last_error_and_error_prepare_exception()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}
extern "C" void mono_unity_runtime_set_main_args(int, const char* argv[])
{
    ASSERT_NOT_IMPLEMENTED;
}
extern "C" MonoString* mono_unity_string_empty_wrapper()
{
    ASSERT_NOT_IMPLEMENTED;
    return NULL;
}

#if PLATFORM_OSX
extern "C" int mono_unity_backtrace_from_context(void* context, void* array[], int count)
{
    ASSERT_NOT_IMPLEMENTED;
    return 0;
}
#endif
