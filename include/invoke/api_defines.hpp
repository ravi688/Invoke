
#pragma once

#if (defined _WIN32 || defined __CYGWIN__) && defined(__GNUC__)
#	define INVOKE_IMPORT_API __declspec(dllimport)
#	define INVOKE_EXPORT_API __declspec(dllexport)
#else
#	define INVOKE_IMPORT_API __attribute__((visibility("default")))
#	define INVOKE_EXPORT_API __attribute__((visibility("default")))
#endif

#ifdef INVOKE_BUILD_STATIC_LIBRARY
#	define INVOKE_API
#elif defined(INVOKE_BUILD_DYNAMIC_LIBRARY)
#	define INVOKE_API INVOKE_EXPORT_API
#elif defined(INVOKE_USE_DYNAMIC_LIBRARY)
#	define INVOKE_API INVOKE_IMPORT_API
#elif defined(INVOKE_USE_STATIC_LIBRARY)
#	define INVOKE_API
#else
#	define INVOKE_API
#endif

