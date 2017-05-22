#ifdef WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

// dummy function just to test that it is exported in coreclr so/dll
extern "C" EXPORT_API void mono_test_export()
{
}

