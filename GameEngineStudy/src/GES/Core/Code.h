#pragma once
// define this before anything

// #include <intrin.h> // __debugbreak(), SIMD
#include <stdint.h> // integer types data
// #include <float.h>  // floating point types data
// #include <stdio.h>  // printf
// #include <string.h> // memset, memcpy
// #include <math.h>   // sqrtf, sinf, cosf
#include <memory>   // std::unique_ptr, std::shared_ptr

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

// macros
// #define STRINGIFY_A_VALUE(VALUE) #VALUE
// #define STRINGIFY_A_MACRO(MACRO) STRINGIFY_A_VALUE(MACRO)
// #define FILE_AND_LINE __FILE__ ":" STRINGIFY_A_MACRO(__LINE__)
// #define C_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define TOKENIZE_A_VALUE(a, b) a ## b
#define TOKENIZE_A_MACRO(a, b) TOKENIZE_A_VALUE(a, b)

// #undef min
// #undef max

// language-specific
#if defined(__cplusplus)
	#define API_C extern "C"
	#define API_C_BLOCK_START extern "C" {
	#define API_C_BLOCK_END }
#else
	#define API_C
	#define API_C_BLOCK_START
	#define API_C_BLOCK_END
	// #define constexpr
	// #define thread_local
#endif

// platform-specific
#if defined(_WIN32)
	#if defined(_WIN64)
		#define GES_PLATFORM_WINDOWS
	#else
		#define GES_PLATFORM_WINDOWS
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#define GES_PLATFORM_IOS_SIMULATOR
	#elif TARGET_OS_IPHONE == 1
		#define GES_PLATFORM_IOS
	#elif TARGET_OS_MAC == 1
		#define GES_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define GES_PLATFORM_ANDROID
#elif defined(__linux__)
	#define GES_PLATFORM_LINUX
#else
	#error "Unknown compiler/platform!"
#endif

// compiler-specific
#if defined(_MSC_VER) || defined(__clang__)
	#define CODE_BREAK() __debugbreak()
	#define FUNCTION_NAME __FUNCTION__
	// __FUNCSIG__
	//
	#define GES_API_EXPORT __declspec(dllexport)
	#define GES_API_IMPORT __declspec(dllimport)
	#define GES_API_LOCAL
#elif defined(__GNUC__)
	#define CODE_BREAK() __asm volatile ("int3")
	#define FUNCTION_NAME __func__
	// __PRETTY_FUNCTION__
	// https://gcc.gnu.org/wiki/Visibility
	#if __GNUC__ >= 4
		#define GES_API_EXPORT __attribute__((visibility("default")))
		#define GES_API_IMPORT __attribute__((visibility("default")))
		#define GES_API_LOCAL __attribute__((visibility("hidden")))
	#else
		#define GES_API_EXPORT
		#define GES_API_IMPORT
		#define GES_API_LOCAL
	#endif
#elif defined(__MINGW32__) || defined(__MINGW64__)
	#define CODE_BREAK() __asm volatile ("int3")
	#define FUNCTION_NAME __FUNCTION__
	// ?
	//
	#define GES_API_EXPORT
	#define GES_API_IMPORT
	#define GES_API_LOCAL
#else
	#error unsupported compiler
#endif

// dll-specific
#if defined(GES_SHARED)
	#if defined(GES_BUILD_DLL)
		#define GES_TEMPLATE
		#define GES_API GES_API_EXPORT
	#else
		#define GES_TEMPLATE extern
		#define GES_API GES_API_IMPORT
	#endif
#else
	#define GES_TEMPLATE
	#define GES_API
#endif

//
#define BIT(T, index) static_cast<T>(static_cast<T>(1) << index)

#define BIND_EVENT_FN(name) std::bind(&name, this, std::placeholders::_1)

//
namespace GES {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
