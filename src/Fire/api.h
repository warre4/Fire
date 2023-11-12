#pragma once


// Fire engine API (FAPI)

//#if defined(_WIN32) // Windows
//	#if defined(FBUILD_DLL)
//		#define FAPI __declspec(dllexport)
//	#else
//		#define FAPI _declspec(dllimport)
//	#endif
//#elif defined(__GNUC__) // Linux
//	#if defined(FBUILD_DLL)
//		#define FAPI __attribute__((visibility("default")))
//	#else
//		#define FAPI
//	#endif
//#else // unknown platform
//	#if defined(FBUILD_DLL)
//		#pragma warning WARNING: Fire engine building dynamically for unknown platform, dynamic linking could be broken
//		#define FAPI
//	#else
//		#define FAPI
//	#endif
//#endif

#define FAPI // temporarily disabled, dynamic linking is not implemented yet