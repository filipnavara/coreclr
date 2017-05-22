#ifndef MONOTYPES_H
#define MONOTYPES_H

//TODO use mono headers directly, so we don't get burned when the struct definitions in this file
//go out of sync with mono's.
//this is not done yet, because it's tricky, as the mono headers define symbols that we also define in UnityFunctions.h,
//so we'd need to find some way to either remove those defines from the mono headers, or somehow mangle them.
#if ENABLE_MONO

struct MonoException;
struct MonoAssembly;
struct MonoObject;
struct MonoClassField;
struct MonoClass;
struct MonoDomain;
struct MonoImage;
struct MonoType;
struct MonoMethodSignature;
struct MonoArray;
struct MonoThread;
struct MonoVTable;
struct MonoProperty;
struct MonoReflectionAssembly;
struct MonoReflectionMethod;
struct MonoAppDomain;
struct MonoCustomAttrInfo;
struct MonoDl;
#if PLATFORM_STANDALONE || UNITY_EDITOR
struct MonoDlFallbackHandler;
#endif

#if UNITY_EDITOR
struct MonoMethodDesc;
#endif

typedef const void* gconstpointer;
typedef void* gpointer;
typedef int gboolean;
typedef unsigned int guint32;
typedef int gint32;
typedef UInt64 guint64;
typedef SInt64 gint64;
typedef unsigned long gulong;
typedef unsigned char   guchar;
typedef UInt16 gunichar2;
struct MonoString
{
    void* monoObjectPart1;
    void* monoObjectPart2;
    gint32 length;
    gunichar2 firstCharacter;
};

struct MonoMethod
{
    UInt16 flags;
    UInt16 iflags;
};

struct GPtrArray
{
    gpointer *pdata;
    guint32 len;
};

typedef enum
{
    MONO_VERIFIER_MODE_OFF,
    MONO_VERIFIER_MODE_VALID,
    MONO_VERIFIER_MODE_VERIFIABLE,
    MONO_VERIFIER_MODE_STRICT
} MiniVerifierMode;

typedef enum
{
    MONO_SECURITY_MODE_NONE,
    MONO_SECURITY_MODE_CORE_CLR,
    MONO_SECURITY_MODE_CAS,
    MONO_SECURITY_MODE_SMCS_HACK
} MonoSecurityMode;

typedef enum
{
    MONO_TYPE_NAME_FORMAT_IL,
    MONO_TYPE_NAME_FORMAT_REFLECTION,
    MONO_TYPE_NAME_FORMAT_FULL_NAME,
    MONO_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED
} MonoTypeNameFormat;

typedef struct
{
    const char *name;
    const char *culture;
    const char *hash_value;
    const UInt8* public_key;
    // string of 16 hex chars + 1 NULL
    guchar public_key_token[17];
    guint32 hash_alg;
    guint32 hash_len;
    guint32 flags;
    UInt16 major, minor, build, revision;
    // only used and populated by newer Mono
    UInt16 arch;
} MonoAssemblyName;

typedef void GFuncRef (void*, void*);
typedef GFuncRef* GFunc;

typedef enum
{
    MONO_UNHANDLED_POLICY_LEGACY,
    MONO_UNHANDLED_POLICY_CURRENT
} MonoRuntimeUnhandledExceptionPolicy;

typedef enum
{
    MONO_DL_LAZY  = 1,
    MONO_DL_LOCAL = 2,
    MONO_DL_MASK  = 3
} MonoDynamicLibraryFlag;

#if ENABLE_MONO_MEMORY_CALLBACKS
struct MonoMemoryCallbacks;
#endif


struct MonoJitInfo
{
    MonoMethod* method;
    void* next_jit_code_hash;
    gpointer code_start;
};

struct MonoDebugSourceLocation
{
    char* source_file;
    UInt32 row;
    UInt32 column;
    UInt32 il_offset;
};

typedef enum
{
    /* the default is to always obey the breakpoint */
    MONO_BREAK_POLICY_ALWAYS,
    /* a nop is inserted instead of a breakpoint */
    MONO_BREAK_POLICY_NEVER,
    /* the breakpoint is executed only if the program has ben started under
     * the debugger (that is if a debugger was attached at the time the method
     * was compiled).
     */
    MONO_BREAK_POLICY_ON_DBG
} MonoBreakPolicy;

typedef MonoBreakPolicy (*MonoBreakPolicyFunc) (MonoMethod *method);

#if UNITY_ANDROID
struct MonoFileMap;

typedef MonoFileMap* (*MonoFileMapOpen)     (const char* name);
typedef guint64      (*MonoFileMapSize)     (MonoFileMap *fmap);
typedef int          (*MonoFileMapFd)       (MonoFileMap *fmap);
typedef int          (*MonoFileMapClose)    (MonoFileMap *fmap);
typedef void *       (*MonoFileMapMap)      (size_t length, int flags, int fd, guint64 offset, void **ret_handle);
typedef int          (*MonoFileMapUnmap)    (void *addr, void *handle);

typedef gboolean (*MonoStackFrameWalk) (MonoDomain *domain, /*MonoContext*/ void *ctx, /*MonoJitInfo*/ void *ji, gpointer data);

#endif

// MONO_CORECLR (START)
// Types introduced for replicating GCBeginFrame behavior outside the CLR
struct MonoGCFrame
{
    // FrameBase
    void* vtable;
    // Frame
    void* frameNext;
    // GCFrame
    void* objRef;
    UInt32 numRef;
    void* pCurrentThread;
    BOOL maybeInteriorPointer;
};

struct MonoGCCookie
{
    SIZE_T cookie;
    MonoGCFrame frame;
};
// MONO_CORECLR (END)

#endif //ENABLE_MONO
#endif
