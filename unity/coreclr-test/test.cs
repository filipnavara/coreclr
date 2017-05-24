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

        public static int StaticTestArg1_float(int a)
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
    }
}
