#pragma once

#ifdef GES_PLATFORM_WINDOWS
	#ifdef GES_BUILD_DLL
		#define GES_API __declspec(dllexport)
	#else
		#define GES_API __declspec(dllimport)
	#endif
#else
	#error supported platforms: Windows
#endif