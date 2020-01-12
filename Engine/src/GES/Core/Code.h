#pragma once
// define this before anything

#include <intrin.h> // debug intrinsics, SIMD
#include <stdint.h> // integer data types
#include <float.h>  // floating point data types
#include <stdio.h>  // file operations, printing functions
#include <string.h> // raw memory operations
#include <math.h>   // non-trivial math functions

typedef int8_t   s8;  // signed char
typedef int16_t  s16; // short
typedef int32_t  s32; // int
typedef int64_t  s64; // long long

typedef uint8_t  u8;  // unsigned char
typedef uint16_t u16; // unsigned short
typedef uint32_t u32; // unsigned int
typedef uint64_t u64; // unsigned long long

typedef long          s48; // witty (32 + 64) / 2
typedef unsigned long u48; // witty (32 + 64) / 2

typedef float  r32;
typedef double r64;

typedef char const * cstring;

// macros
#define GES_STRINGIFY_A_VALUE(v) #v
#define GES_STRINGIFY_A_MACRO(m) GES_STRINGIFY_A_VALUE(m)
#define GES_TOKENIZE_A_VALUE(v1, v2) v1 ## v2
#define GES_TOKENIZE_A_MACRO(m1, m2) GES_TOKENIZE_A_VALUE(m1, m2)

#define GES_FILE_AND_LINE __FILE__ ":" GES_STRINGIFY_A_MACRO(__LINE__)
#define C_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

#undef min
#undef max

// OS detection
#if defined(_WIN64) || defined(_WIN32)
	#define GES_OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define GES_OS_IOS_SIMULATOR
	#elif TARGET_OS_IPHONE == 1
		#define GES_OS_IOS
	#elif TARGET_OS_MAC == 1
		#define GES_OS_MACOS
	#else
		#error "unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define GES_OS_ANDROID
#elif defined(__linux__)
	#define GES_OS_LINUX
#else
	#error "unknown platform"
#endif

// shared library interface
#if defined(_MSC_VER)
	#define GES_DLL_EXPORT __declspec(dllexport)
	#define GES_DLL_IMPORT __declspec(dllimport)
#else
	#define GES_DLL_EXPORT
	#define GES_DLL_IMPORT
#endif

#if defined(GES_SHARED)
	#if defined(GES_IS_DLL)
		#define GES_TEMPLATE
		#define GES_DLL GES_DLL_EXPORT
	#else
		#define GES_TEMPLATE extern
		#define GES_DLL GES_DLL_IMPORT
	#endif
#else
	#define GES_TEMPLATE
	#define GES_DLL
#endif

// c++ meta and operators for enum structs
#if defined(__cplusplus)
namespace meta {
	template<size_t S> struct uint_for_size;
	template<> struct uint_for_size<1> { typedef u8  type; };
	template<> struct uint_for_size<2> { typedef u16 type; };
	template<> struct uint_for_size<4> { typedef u32 type; };
	template<> struct uint_for_size<8> { typedef u64 type; };

	template<typename T>
	struct uint_for_type {
		typedef typename uint_for_size<sizeof(T)>::type type;
	};
}

#if defined(_MSC_VER)
	namespace meta {
		template<typename T>
		struct underlying_type {
			typedef typename __underlying_type(T) type;
		};

		template<typename T>
		struct is_enum {
			static bool const value = __is_enum(T);
		};
	}
	#define UNDERLYING_TYPE_META(T, U)
	#define IS_ENUM_META(T)
#else
	namespace meta {
		template<typename T> struct underlying_type;
		template<typename T> struct is_enum;
	}
	#define UNDERLYING_TYPE_META(T, U)\
	namespace meta { template<> struct underlying_type<T> { typedef typename U type; }; }

	#define IS_ENUM_META(T)\
	namespace meta { template<> struct is_enum<T> { static bool const value = true; }; }
#endif

#define ENUM_FLAG_OPERATORS_IMPL(T)\
constexpr inline T operator&(T a, T b) {\
	using U = meta::uint_for_type<T>::type;\
	return static_cast<T>(static_cast<U>(a) & static_cast<U>(b));\
}\
constexpr inline T operator|(T a, T b) {\
	using U = meta::uint_for_type<T>::type;\
	return static_cast<T>(static_cast<U>(a) | static_cast<U>(b));\
}\
constexpr inline T operator^(T a, T b) {\
	using U = meta::uint_for_type<T>::type;\
	return static_cast<T>(static_cast<U>(a) ^ static_cast<U>(b));\
}\
constexpr inline T operator~(T v) {\
	using U = meta::uint_for_type<T>::type;\
	return static_cast<T>(~static_cast<U>(v));\
}\
constexpr inline bool bits_are_set(T container, T bits) { return (container & bits) == bits; }\
constexpr inline T bits_to_zero(T container, T bits) { return container & ~bits; }
#endif // defined(__cplusplus)

#if defined(__cplusplus)
	#define BIT(T, index) static_cast<T>(static_cast<T>(1) << index)
#else
	#define BIT(T, index) (T)((T)1 << index)
#endif

// memory management
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

//
//
//

#define BIND_EVENT_FN(name) std::bind(&name, this, std::placeholders::_1)
