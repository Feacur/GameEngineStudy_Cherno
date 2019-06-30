#pragma once

#include <stdint.h> // the following types

typedef int8_t   int8;  // signed char
typedef int16_t  int16; // short
typedef int32_t  int32; // int
typedef int64_t  int64; // long long

typedef uint8_t  uint8;  // unsigned char
typedef uint16_t uint16; // unsigned short
typedef uint32_t uint32; // unsigned int
typedef uint64_t uint64; // unsigned long long

typedef long          int48;  // witty (32 + 64) / 2
typedef unsigned long uint48; // witty (32 + 64) / 2

#ifdef GES_PLATFORM_WINDOWS
	#ifdef GES_SHARED
		#ifdef GES_BUILD_DLL
			#define GES_API __declspec(dllexport)
			#define GES_TEMPLATE
		#else
			#define GES_API __declspec(dllimport)
			#define GES_TEMPLATE extern
		#endif
	#else
		#define GES_API
		#define GES_TEMPLATE
	#endif
#else
	#error supported platforms: Windows
#endif

#ifdef SHIPPING
	#define GES_ASSERT(x, ...)
	#define GES_CORE_ASSERT(x, ...)
#else
	#define GES_ASSERT(x, ...) { if(!(x)) { GES_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GES_CORE_ASSERT(x, ...) { if(!(x)) { GES_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif

#define BIT(T, index) static_cast<T>(static_cast<T>(1) << index)

#define BIND_EVENT_FN(name) std::bind(&name, this, std::placeholders::_1)
