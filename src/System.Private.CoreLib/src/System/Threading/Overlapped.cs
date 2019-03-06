// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

//

/*
 * This files defines the following types:
 *  - _IOCompletionCallback
 *  - Overlapped
 */

/*=============================================================================
**
**
**
** Purpose: Class for converting information to and from the native 
**          overlapped structure used in asynchronous file i/o
**
**
=============================================================================*/


using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace System.Threading
{
    #region class _IOCompletionCallback

    internal unsafe class _IOCompletionCallback
    {
        private IOCompletionCallback _ioCompletionCallback;
        private ExecutionContext _executionContext;
        private uint _errorCode; // Error code
        private uint _numBytes; // No. of bytes transferred 
        private NativeOverlapped* _pNativeOverlapped;

        internal _IOCompletionCallback(IOCompletionCallback ioCompletionCallback, ExecutionContext executionContext)
        {
            _ioCompletionCallback = ioCompletionCallback;
            _executionContext = executionContext;
        }

        // Context callback: same sig for SendOrPostCallback and ContextCallback
        private static ContextCallback s_ccb = new ContextCallback(IOCompletionCallback_Context);
        private static void IOCompletionCallback_Context(object state)
        {
            _IOCompletionCallback helper = (_IOCompletionCallback)state;
            Debug.Assert(helper != null, "_IOCompletionCallback cannot be null");
            helper._ioCompletionCallback(helper._errorCode, helper._numBytes, helper._pNativeOverlapped);
        }

        internal static unsafe void PerformIOCompletionCallback(uint errorCode, uint numBytes, NativeOverlapped* pNativeOverlapped)
        {
            Overlapped overlapped = Overlapped.GetOverlappedFromNative(pNativeOverlapped);

            if (overlapped._callback is IOCompletionCallback iocb)
            {
                // We got here because of UnsafePack (or) Pack with EC flow suppressed
                iocb(errorCode, numBytes, pNativeOverlapped);
            }
            else if (overlapped._callback != null)
            {
                // We got here because of Pack
                var helper = (_IOCompletionCallback)overlapped._callback;
                helper._errorCode = errorCode;
                helper._numBytes = numBytes;
                helper._pNativeOverlapped = pNativeOverlapped;
                ExecutionContext.RunInternal(helper._executionContext, s_ccb, helper);
            }
        }
    }

    #endregion class _IOCompletionCallback

    #region class Overlapped

    public unsafe class Overlapped
    {
        internal IAsyncResult _asyncResult;
        internal object _callback; // IOCompletionCallback or _IOCompletionCallback
        private GCHandle[] _pinnedData;
        private NativeOverlapped * _pNativeOverlapped;
        private IntPtr _eventHandle;
        private int _offsetLow;
        private int _offsetHigh;

        public Overlapped()
        {
        }

        public Overlapped(int offsetLo, int offsetHi, IntPtr hEvent, IAsyncResult ar)
        {
            _offsetLow = offsetLo;
            _offsetHigh = offsetHi;
            _eventHandle = hEvent;
            AsyncResult = ar;
        }

        [Obsolete("This constructor is not 64-bit compatible.  Use the constructor that takes an IntPtr for the event handle.  http://go.microsoft.com/fwlink/?linkid=14202")]
        public Overlapped(int offsetLo, int offsetHi, int hEvent, IAsyncResult ar) : this(offsetLo, offsetHi, new IntPtr(hEvent), ar)
        {
        }

        public IAsyncResult AsyncResult { get; set; }

        public int OffsetLow
        {
            get { return _pNativeOverlapped != null ? _pNativeOverlapped->OffsetLow : _offsetLow; }
            set
            {
                if (_pNativeOverlapped != null)
                {
                    _pNativeOverlapped->OffsetLow = value;
                }
                else
                {
                    _offsetLow = value;
                }
            }
        }

        public int OffsetHigh
        {
            get { return _pNativeOverlapped != null ? _pNativeOverlapped->OffsetHigh : _offsetHigh; }
            set
            {
                if (_pNativeOverlapped != null)
                {
                    _pNativeOverlapped->OffsetHigh = value;
                }
                else
                {
                    _offsetHigh = value;
                }
            }
        }

        [Obsolete("This property is not 64-bit compatible.  Use EventHandleIntPtr instead.  http://go.microsoft.com/fwlink/?linkid=14202")]
        public int EventHandle
        {
            get { return EventHandleIntPtr.ToInt32(); }
            set { EventHandleIntPtr = new IntPtr(value); }
        }

        public IntPtr EventHandleIntPtr
        {
            get { return _pNativeOverlapped != null ? _pNativeOverlapped->EventHandle : _eventHandle; }
            set
            {
                if (_pNativeOverlapped != null)
                {
                    _pNativeOverlapped->EventHandle = value;
                }
                else
                {
                    _eventHandle = value;
                }
            }
        }

        /*====================================================================
        *  Packs a managed overlapped class into native Overlapped struct.
        *  Roots the iocb and stores it in the ReservedCOR field of native Overlapped
        *  Pins the native Overlapped struct and returns the pinned index.
        ====================================================================*/
        [Obsolete("This method is not safe.  Use Pack (iocb, userData) instead.  http://go.microsoft.com/fwlink/?linkid=14202")]
        [CLSCompliant(false)]
        public unsafe NativeOverlapped* Pack(IOCompletionCallback iocb)
        {
            return Pack(iocb, null);
        }

        [CLSCompliant(false)]
        public unsafe NativeOverlapped* Pack(IOCompletionCallback iocb, object userData)
        {
            if (_pNativeOverlapped != null)
            {
                throw new InvalidOperationException(SR.InvalidOperation_Overlapped_Pack);
            }

            if (iocb != null)
            {
                ExecutionContext ec = ExecutionContext.Capture();
                _callback = (ec != null && !ec.IsDefault) ? new _IOCompletionCallback(iocb, ec) : (object)iocb;
            }
            else
            {
                _callback = null;
            }
            return AllocateNativeOverlapped(userData);
        }

        [Obsolete("This method is not safe.  Use UnsafePack (iocb, userData) instead.  http://go.microsoft.com/fwlink/?linkid=14202")]
        [CLSCompliant(false)]
        public unsafe NativeOverlapped* UnsafePack(IOCompletionCallback iocb)
        {
            return UnsafePack(iocb, null);
        }

        [CLSCompliant(false)]
        public unsafe NativeOverlapped* UnsafePack(IOCompletionCallback iocb, object userData)
        {
            if (_pNativeOverlapped != null)
            {
                throw new InvalidOperationException(SR.InvalidOperation_Overlapped_Pack);
            }
            _callback = iocb;
            return AllocateNativeOverlapped(userData);
        }

        /*====================================================================
        *  Unpacks an unmanaged native Overlapped struct.
        *  Unpins the native Overlapped struct
        ====================================================================*/
        [CLSCompliant(false)]
        public static unsafe Overlapped Unpack(NativeOverlapped* nativeOverlappedPtr)
        {
            if (nativeOverlappedPtr == null)
                throw new ArgumentNullException(nameof(nativeOverlappedPtr));

            return GetOverlappedFromNative(nativeOverlappedPtr);
        }

        [CLSCompliant(false)]
        public static unsafe void Free(NativeOverlapped* nativeOverlappedPtr)
        {
            if (nativeOverlappedPtr == null)
                throw new ArgumentNullException(nameof(nativeOverlappedPtr));

            GetOverlappedFromNative(nativeOverlappedPtr)._pNativeOverlapped = null;
            FreeNativeOverlapped(nativeOverlappedPtr);
        }

        private unsafe NativeOverlapped* AllocateNativeOverlapped(object userData)
        {
            Debug.Assert(_pinnedData == null);

            bool success = false;
            try
            {
                if (userData != null)
                {
                    try
                    {
                        if (userData is object[] objArray)
                        {
                            _pinnedData = new GCHandle[objArray.Length];
                            for (int i = 0; i < objArray.Length; i++)
                            {
                                _pinnedData[i] = GCHandle.Alloc(objArray[i], GCHandleType.Pinned);
                            }
                        }
                        else
                        {
                            _pinnedData = new GCHandle[1];
                            _pinnedData[0] = GCHandle.Alloc(userData, GCHandleType.Pinned);
                        }
                    }
                    catch (ArgumentException)
                    {
                        // For performance reasons we catch the exception thrown by GCHandle.Alloc
                        // instead of calling Marshal.IsPinnable ourselves. The ParamName of the
                        // ArgumentException has to be fixed up.
                        throw new ArgumentException(SR.ArgumentException_NotIsomorphic, nameof(userData));
                    }
                }

                NativeOverlapped* pNativeOverlapped = (NativeOverlapped*)Marshal.AllocHGlobal(sizeof(NativeOverlapped) + sizeof(GCHandle));
                *(GCHandle*)(pNativeOverlapped + 1) = default(GCHandle);
                _pNativeOverlapped = pNativeOverlapped;

                _pNativeOverlapped->InternalLow = default;
                _pNativeOverlapped->InternalHigh = default;
                _pNativeOverlapped->OffsetLow = _offsetLow;
                _pNativeOverlapped->OffsetHigh = _offsetHigh;
                _pNativeOverlapped->EventHandle = _eventHandle;

                *(GCHandle*)(_pNativeOverlapped + 1) = GCHandle.Alloc(this);

                success = true;
                return _pNativeOverlapped;
            }
            finally
            {
                if (!success)
                    FreeNativeOverlapped();
            }
        }

        internal static unsafe void FreeNativeOverlapped(NativeOverlapped* nativeOverlappedPtr)
        {
            Overlapped overlapped = GetOverlappedFromNative(nativeOverlappedPtr);
            overlapped.FreeNativeOverlapped();
        }

        private void FreeNativeOverlapped()
        {
            if (_pinnedData != null)
            {
                for (int i = 0; i < _pinnedData.Length; i++)
                {
                    if (_pinnedData[i].IsAllocated)
                    {
                        _pinnedData[i].Free();
                    }
                }
                _pinnedData = null;
            }

            if (_pNativeOverlapped != null)
            {
                GCHandle handle = *(GCHandle*)(_pNativeOverlapped + 1);
                if (handle.IsAllocated)
                    handle.Free();

                Marshal.FreeHGlobal((IntPtr)_pNativeOverlapped);
                _pNativeOverlapped = null;
            }
        }

        internal static unsafe Overlapped GetOverlappedFromNative(NativeOverlapped* pNativeOverlapped)
        {
            GCHandle handle = *(GCHandle*)(pNativeOverlapped + 1);
            return (Overlapped)handle.Target;
        }
    }

    #endregion class Overlapped
}
