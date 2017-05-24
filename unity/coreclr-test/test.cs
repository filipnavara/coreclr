using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace coreclrtest
{
    class TestAttribute : Attribute
    {

    }

    class AnotherTestAttribute : Attribute
    {

    }

    [TestAttribute]
    class ClassWithAttribute
    {

    }

    class test : ClassWithAttribute
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void InternalMethod();

        static object GetNumber()
        {
            Console.WriteLine("Test from C#");
            InternalMethod();
            return 12;
        }

        [TestAttribute]
        static void MethodWithAttribute()
        {

        }
    }
}
