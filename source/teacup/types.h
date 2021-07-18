// MIT License
//
// Copyright (c) 2021 Aaron M. Roller
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef TC_TYPES_HEADER_GUARD
#define TC_TYPES_HEADER_GUARD

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Helper macros

#define TC_STR(X) TC_STR_(X)
#define TC_STR_(X) #X

#define TC_CAT(A, B) TC_CAT_(A, B)
#define TC_CAT_(A, B) A ## B

#define TC_BLOCK_BEGIN(...) for (;__VA_ARGS__;) {
#define TC_BLOCK_END(...) break; }

#define TC_STATEMENT(S) do { S } while (0);

#define TC_MAX(A, B) (((A) > (B)) ? (A) : (B))
#define TC_MIN(A, B) (((A) < (B)) ? (A) : (B))

#define TC_CLAMP(A, LOW, HIGH) (((A) < (LOW)) ? (LOW) : (((A) > (HIGH)) ? (HIGH) : (A)))
#define TC_CLAMP_TOP(A, HIGH) TC_MIN(A, HIGH)
#define TC_CLAMP_BOT(A, LOW) TC_MAX(A, LOW)

////////////////////////////////////////////////////////////////////////////////
// Context cracking

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__64BIT__) || defined(__LP64__)
#   define TC_ARCH_64_BIT 1
#   define TC_ARCH_NAME "64-bit"
#else
#   define TC_ARCH_32_BIT 1
#   define TC_ARCH_NAME "32-bit"
#endif

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#   define TC_ISA_ARM 1
#   define TC_ISA_NAME "Arm"
#   define TC_CACHE_LINE_SIZE 64
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
#   define TC_ISA_X86 1
#   define TC_ISA_NAME "x86"
#   define TC_CACHE_LINE_SIZE 64
#else
#   error "Unknown instruction set"
#endif

#if defined(__clang__)
#   define TC_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#   define TC_COMPILER_NAME "Clang " TC_STR(__clang_major__) "." TC_STR(__clang_minor__) "." TC_STR(__clang_patchlevel__)
#elif defined(__GNUC__)
#   define TC_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#   define TC_COMPILER_NAME "GCC " TC_STR(__GNUC__) "." TC_STR(__GNUC_MINOR__) "." TC_STR(__GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
#   define TC_COMPILER_MSVC _MSC_VER
#   if TC_COMPILER_MSVC >= 1920
#       define TC_COMPILER_NAME "MSVC 16.0"
#   elif TC_COMPILER_MSVC >= 1910
#       define TC_COMPILER_NAME "MSVC 15.0"
#   elif TC_COMPILER_MSVC >= 1900
#       define TC_COMPILER_NAME "MSVC 14.0"
#   elif TC_COMPILER_MSVC >= 1800
#       define TC_COMPILER_NAME "MSVC 12.0"
#   elif TC_COMPILER_MSVC >= 1700
#       define TC_COMPILER_NAME "MSVC 11.0"
#   elif TC_COMPILER_MSVC >= 1600
#       define TC_COMPILER_NAME "MSVC 10.0"
#   elif TC_COMPILER_MSVC >= 1500
#       define TC_COMPILER_NAME "MSVC 9.0"
#   else
#       define TC_COMPILER_NAME "MSVC"
#   endif
#else
#   error "Unknown compiler"
#endif

#if defined(_WIN32) || defined(_WIN64)
#   define TC_OS_WINDOWS 1
#   define TC_OS_NAME "Windows"
#elif defined(__linux__)
#   define TC_OS_LINUX 1
#   define TC_OS_POSIX 1
#   define TC_OS_NAME "Linux"
#elif defined(__APPLE__) || defined(__MACH__)
#   define TC_OS_MACOS 1
#   define TC_OS_POSIX 1
#   define TC_OS_NAME "MacOS"
#else
#   error "Unknown operating system"
#endif

////////////////////////////////////////////////////////////////////////////////
// Compiler traits

#if TC_COMPILER_GCC || TC_COMPILER_CLANG
#   define TC_FORCE_INLINE inline __attribute__((__always_inline__))
#   define TC_FUNCTION __PRETTY_FUNCTION__
#   define TC_LIKELY(_x) __builtin_expect(!!(_x), 1)
#   define TC_UNLIKELY(_x) __builtin_expect(!!(_x), 0)
#   define TC_NO_INLINE __attribute__((noinline))
#   define TC_NO_RETURN __attribute__((noreturn))
#   define TC_CONST_FUNC __attribute__((const))
#   define TC_UNREACHABLE(...) __builtin_unreachable()
#elif TC_COMPILER_MSVC
#   define TC_FORCE_INLINE __forceinline
#   define TC_FUNCTION __FUNCTION__
#   define TC_LIKELY(_x) (_x)
#   define TC_UNLIKELY(_x) (_x)
#   define TC_NO_INLINE __declspec(noinline)
#   define TC_NO_RETURN __declspec(noreturn)
#   define TC_CONST_FUNC __declspec(noalias)
#   define TC_UNREACHABLE(...) __assume(0);
#else
#   error "Unknown TC_COMPILER"
#endif

#define TC_C_LINKAGE_BEGIN extern "C" {
#define TC_C_LINKAGE_END }
#define TC_C_LINKAGE extern "C"

#define TC_GLOBAL static
#define TC_LOCAL static

#define TC_IS_DEF(_macro) TC_IS_DEF_(_macro)
#define TC_IS_DEF_(_macro) (#_macro[0] == '1' && #_macro[1] == 0)

////////////////////////////////////////////////////////////////////////////////
// Debugging

#define TC_PING(...) printf("PING: %s:%d (%s)\n", __FILE__, __LINE__, LT_FUNCTION);

#define TC_STATIC_ASSERT(_condition, ...) static_assert(_condition, "" __VA_ARGS__)

#define TC_ASSERT(_cond, ...) \
    TC_BLOCK_BEGIN(!(_cond)) \
    printf("Assert failed: %s:%d %s\n", __FILE__, __LINE__, "" __VA_ARGS__); \
    fflush(stdout); \
    TC_BREAK_POINT(); \
    TC_BLOCK_END()

#define TC_FAILURE(...) \
    TC_BLOCK_BEGIN(true) \
    printf("Something went terribly wrong: %s:%d %s\n", __FILE__, __LINE__, "" __VA_ARGS__); \
    fflush(stdout); \
    TC_BREAK_POINT(); \
    TC_BLOCK_END()

#if TC_COMPILER_MSVC
#   define TC_BREAK_POINT(...) __debugbreak();
#elif TC_ISA_ARM
    define TC_BREAK_POINT(...) __builtin_trap();
#elif TC_ISA_X86 && (TC_COMPILER_GCC || TC_COMPILER_CLANG)
#   define TC_BREAK_POINT(...) __asm__ ("int $3");
#else
#   define TC_BREAK_POINT(...) TC_STATEMENT(int* int3 = (int*)3L; *int3 = 3;)
#endif

////////////////////////////////////////////////////////////////////////////////
// Fixed sized constants

#define TC_S64_MAX ((S64) 0x7fffffffffffffffllu)
#define TC_S32_MAX ((S32) 0x7fffffff)
#define TC_S16_MAX ((S16) 0x7fff)
#define TC_S8_MAX  ((S8)  0x7f)

#define TC_S64_MIN ((S64) 0x8000000000000000llu)
#define TC_S32_MIN ((S32) 0x80000000)
#define TC_S16_MIN ((S16) 0x8000)
#define TC_S8_MIN  ((S8)  0x80)

#define TC_U64_MAX ((U64) 0xfffffffffffffffllu)
#define TC_U32_MAX ((U32) 0xffffffff)
#define TC_U16_MAX ((U16) 0xffff)
#define TC_U8_MAX  ((U8)  0xff)

////////////////////////////////////////////////////////////////////////////////
// Primitive types

typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t  U8;

typedef int64_t S64;
typedef int32_t S32;
typedef int16_t S16;
typedef int8_t  S8;

typedef double F64;
typedef float  F32;

typedef S64 B64;
typedef S32 B32;
typedef S16 B16;
typedef S8  B8;

typedef void VoidFunc(void);

////////////////////////////////////////////////////////////////////////////////
// Debug types

struct SrcLocation {
    char* file;
    U32 line;
};

////////////////////////////////////////////////////////////////////////////////
// Common functions

inline F32 F32Infinity() {
    union { F32 f; U32 u; } un;
    un.u = 0x7f800000;
    return(un.f);
}

inline F32 F32NegInfinity() {
    union { F32 f; U32 u; } un;
    un.u = 0xff800000;
    return(un.f);
}

#endif // TC_TYPES_HEADER_GUARD
