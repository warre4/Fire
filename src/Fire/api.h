#pragma once


// Fire engine API (FAPI)

#if defined(_WIN32) // Windows
	#if defined(FIRE_ENGINE_COMPILING)
		#define FAPI __declspec(dllexport)
	#else
		#define FAPI _declspec(dllimport)
	#endif
#elif defined(__GNUC__) // Linux
	#if defined(FIRE_ENGINE_COMPILING)
		#define FAPI __attribute__((visibility("default")))
	#else
		#define FAPI
	#endif
#else // unknown platform
	#if defined(FIRE_ENGINE_COMPILING)
		#pragma warning WARNING: Fire engine building dynamically for unknown platform, dynamic linking could be broken
		#define FAPI
	#else
		#define FAPI
	#endif
#endif


#if defined(FIRE_ENGINE_COMPILING)
	#define FIRE_EXPIMP_TEMPLATE
#else
	#define FIRE_EXPIMP_TEMPLATE extern
#endif