// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

using System.Runtime.CompilerServices;

namespace System.Threading
{
    public abstract partial class WaitHandle
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern int WaitOneCore(IntPtr waitHandle, int millisecondsTimeout);
 
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern int WaitMultipleIgnoringSyncContext(IntPtr[] waitHandles, bool waitAll, int millisecondsTimeout);

        private static int SignalAndWaitCore(IntPtr waitHandleToSignal, IntPtr waitHandleToWaitOn, int millisecondsTimeout)
        {
            int ret = SignalAndWaitNative(waitHandleToSignal, waitHandleToWaitOn, millisecondsTimeout);

            if (ret == Interop.Errors.ERROR_TOO_MANY_POSTS)
            {
                throw new InvalidOperationException(SR.Threading_WaitHandleTooManyPosts);
            }

            return ret;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern int SignalAndWaitNative(IntPtr waitHandleToSignal, IntPtr waitHandleToWaitOn, int millisecondsTimeout);
    }
}
