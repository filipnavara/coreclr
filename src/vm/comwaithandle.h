// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.


/*============================================================
**
** Header: COMWaitHandle.h
**
** Purpose: Native methods on System.WaitHandle
**
**
===========================================================*/

#ifndef _COM_WAITABLE_HANDLE_H
#define _COM_WAITABLE_HANDLE_H


class WaitHandleNative
{
public:
    static FCDECL2(INT32, CorWaitOneNative, SafeHandle* safeWaitHandleUNSAFE, INT32 timeout);
    static FCDECL3(INT32, CorWaitMultipleNative, Object* waitObjectsUNSAFE, INT32 timeout, CLR_BOOL waitForAll);
    static FCDECL3(INT32, CorSignalAndWaitOneNative, SafeHandle* safeWaitHandleSignalUNSAFE, SafeHandle* safeWaitHandleWaitUNSAFE, INT32 timeout);
    static FCDECL3(DWORD, WaitHelper, PTRArray *handleArrayUNSAFE, CLR_BOOL waitAll, DWORD millis);
};
#endif
