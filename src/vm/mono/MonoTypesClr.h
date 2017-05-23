#ifndef MONOTYPES_CLR_H
#define MONOTYPES_CLR_H
#ifdef ENABLE_MONO

// Include regular Unity MonoTypes.h header
#include "MonoTypes.h"

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

#endif //ENABLE_MONO
#endif
