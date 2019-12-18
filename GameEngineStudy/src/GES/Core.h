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

typedef char const * cstring;

#ifdef _WIN32
	#ifdef _WIN64
		#define GES_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GES_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define GES_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define GES_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define GES_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown compiler/platform!"
#endif

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

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#include <memory> // std::unique_ptr, std::shared_ptr
namespace GES {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
