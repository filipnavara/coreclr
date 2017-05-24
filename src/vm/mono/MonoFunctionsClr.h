// Mono CoreCLR specifics
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

#define ENABLE_MONO_MEMORY_PROFILER 1

// Include regular Unity Mono functions
#include <MonoFunctions.h>
