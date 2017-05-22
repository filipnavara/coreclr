using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace coreclrtest
{
    class test
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void InternalMethod();

        static int GetNumber()
        {
            InternalMethod();
            return 12;
        }
    }
}
