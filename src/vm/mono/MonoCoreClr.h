#ifndef MONOCORECLR_H
#define MONOCORECLR_H

#include <stdlib.h>

// Builtin types used by MonoFunctions.h
typedef signed short SInt16;
typedef unsigned short UInt16;
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef signed int SInt32;
typedef unsigned int UInt32;
typedef signed long long SInt64;
typedef unsigned long long UInt64;

// TODO: Add char (utf8 for mono)
typedef wchar_t mono_char; // used by CoreCLR

// TODO: Temp def
typedef void* mono_register_object_callback;
typedef void* mono_liveness_world_state_callback;

#define DO_API(r,n,p)	extern "C" r n p;

// TODO: Move this to CMake
#define ENABLE_MONO 1

#include "MonoTypes.h"
#include "MonoFunctions.h"

#endif //MONOCORECLR_H
