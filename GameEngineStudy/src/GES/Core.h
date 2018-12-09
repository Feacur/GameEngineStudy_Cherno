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
	#ifdef GES_BUILD_DLL
		#define GES_API __declspec(dllexport)
		#define GES_TEMPLATE
	#else
		#define GES_API __declspec(dllimport)
		#define GES_TEMPLATE extern
	#endif
#else
	#error supported platforms: Windows
#endif

#define BIT(T, index) static_cast<T>(static_cast<T>(1) << index)
