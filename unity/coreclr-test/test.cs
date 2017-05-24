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
        private int x = 0;
        public test()
        {
            x = 7;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void InternalMethod();

        static int GetNumber()
        {
            Console.WriteLine("Test from C#");
            InternalMethod();
            return 12;
        }

        [TestAttribute]
        static void MethodWithAttribute()
        {

        }

        public static int StaticTestArg1_int(int a)
        {
            return a + 1;
        }

        public static int StaticTestArg2_int(int a, int b)
        {
            return a + b;
        }

        public static float StaticTestArg1_float(float a)
        {
            return a + 1;
        }

        public static float StaticTestArg2_float(float a, float b)
        {
            return a + b;
        }

        public static object StaticTestArg1_obj(object arg1)
        {
            Console.WriteLine(arg1);
            return arg1;
        }

        public int TestArg0()
        {
            return x + 10;
        }

        public int TestArg1_int(int a)
        {
            return x + a + 1;
        }

        public Guid TestGuid()
        {
            return Guid.Parse("81a130d2-502f-4cf1-a376-63edeb000e9f");
        }

        public unsafe void* TestPtr(void* ptr)
        {
            Console.WriteLine(new IntPtr(ptr).ToString("x8"));
            return ptr;
        }
    }
}
