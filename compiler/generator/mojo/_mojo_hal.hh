/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/** @file compiler/generator/mojo/_mojo_hal.hh **/

#ifndef _MOJO_HAL_HH
#define _MOJO_HAL_HH

////////////////////////////////////////////////////////////////
// Operating System

#if !defined(MJ_SYSTEM)
    #define MJ_SYSTEM 0
    #define MJ_SYSTEM_WIN 0
    #define MJ_SYSTEM_OSX 0
    #define MJ_SYSTEM_UNIX 0
    #define MJ_SYSTEM_LINUX 0
#endif

#if defined(_WIN32) || defined(_WIN64)
    #undef MJ_SYSTEM_WIN
    #define MJ_SYSTEM_WIN 1
#elif defined(__APPLE__) && defined(__MACH__)
    #undef MJ_SYSTEM_OSX
    #define MJ_SYSTEM_OSX 1
#elif defined(__unix__)
    #undef MJ_SYSTEM_UNIX
    #define MJ_SYSTEM_UNIX 1
    #if defined(__linux__)
        #undef MJ_SYSTEM_LINUX
        #define MJ_SYSTEM_LINUX 1
    #endif
#else
    #error "This operating system is not supported."
#endif


////////////////////////////////////////////////////////////////
// Compiler
// Supported: MSVC, GCC, clang

#if !defined(MJ_COMPILER)
    #define MJ_COMPILER 0
    #define MJ_COMPILER_MSVC 0
    #define MJ_COMPILER_CLANG 0
    #define MJ_COMPILER_GCC 0
    #define MJ_COMPILER_APPLE 0
#endif

#if defined(_MSC_VER)
    #undef MJ_COMPILER_MSVC
    #define MJ_COMPILER_MSVC 1
#elif defined(__clang__)
    #undef MJ_COMPILER_CLANG
    #define MJ_COMPILER_CLANG 1
    #if defined(__apple_build_version__)
        #undef MJ_COMPILER_APPLE
        #define MJ_COMPILER_APPLE 1
    #endif
#elif defined(__GNUC__)
    #define MJ_COMPILER_GCC 1
#else
    #error "This compiler is not supported."
#endif


////////////////////////////////////////////////////////////////
// Endianness

#if !defined(MJ_IS_BIG_ENDIAN)
    #if MJ_COMPILER_MSVC
        #define MJ_IS_BIG_ENDIAN 0
    #elif defined(__BYTE_ORDER__)
        #define MJ_IS_BIG_ENDIAN (__BYTE_ORDER__ == 4321)
    #else
        #error "Cannot determine endianness at compile time."
    #endif
#endif


////////////////////////////////////////////////////////////////
// CPU, CACHE, SIMD

#if !defined(MJ_CPU)
    #define MJ_CPU 1
    #define MJ_CPU_X86 0
    #define MJ_CPU_ARM 0
    #define MJ_SSE2 0
    #define MJ_NEON 0
    #define MJ_CACHE_LINE_SIZE 0
#endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
    #undef MJ_CPU_X86
    #define MJ_CPU_X86 1
    #if defined(__SSE2__)
        #undef MJ_SSE2
        #define MJ_SSE2 1
    #endif
    #undef MJ_CACHE_LINE_SIZE
    #define MJ_CACHE_LINE_SIZE 64

#elif defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
    #undef MJ_CPU_ARM
    #define MJ_CPU_ARM 1
    #if defined(__ARM_NEON)
        #undef MJ_NEON
        #define MJ_NEON 1
    #endif

    #if defined(__APPLE__)
        #undef MJ_CACHE_LINE_SIZE
        #define MJ_CACHE_LINE_SIZE 128
    #else
        #undef MJ_CACHE_LINE_SIZE
        #define MJ_CACHE_LINE_SIZE 64
    #endif

#else
    #error "Unknown CPU"
#endif


////////////////////////////////////////////////////////////////
// Primitive types

inline namespace mojo {

#if MJ_COMPILER_MSVC
    using u8  = unsigned __int8;
    using u16 = unsigned __int16;
    using u32 = unsigned __int32;
    using u64 = unsigned __int64;
    using s8  = signed __int8;
    using s16 = signed __int16;
    using s32 = signed __int32;
    using s64 = signed __int64;
#else
    #include <stdint.h>
    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using s8  = int8_t;
    using s16 = int16_t;
    using s32 = int32_t;
    using s64 = int64_t;
    using u128 = unsigned __int128;
    using s128 = __int128;
#endif

using usize = size_t;
using ssize = ptrdiff_t;

#if MJ_SYSTEM_WIN
    using sptr = signed __int64;
    using uptr = unsigned __int64;
#else
    using uptr = uintptr_t;
    using sptr = intptr_t;
#endif

using anyptr  = void*;

using f32 = float;
using f64 = double;
using f32_ptr = f32*;
using f64_ptr = f64*;

using b8 = s8 ;
using b16 = s16;
using b32 = s32;


////////////////////////////////////////////////////////////////
// Limits

#if !defined(MJ_LIMIT)
    #define MJ_LIMIT 1

    inline constexpr u8 U8_MIN = 0u;
    inline constexpr u8 U8_MAX = 0xffu;
    inline constexpr s8 I8_MIN = (-0x7f - 1);
    inline constexpr s8 I8_MAX = 0x7f;
    
    inline constexpr u16 U16_MIN = 0u;
    inline constexpr u16 U16_MAX = 0xffffu;
    inline constexpr s16 I16_MIN = (-0x7fff - 1);
    inline constexpr s16 I16_MAX = 0x7fff;
    
    inline constexpr u32 U32_MIN = 0u;
    inline constexpr u32 U32_MAX = 0xffffffffu;
    inline constexpr s32 I32_MIN = (-0x7fffffff - 1);
    inline constexpr s32 I32_MAX = 0x7fffffff;

    inline constexpr u64 U64_MIN = 0ull;
    inline constexpr u64 U64_MAX = 0xffffffffffffffffull;
    inline constexpr s64 I64_MIN = (-0x7fffffffffffffffll - 1);
    inline constexpr s64 I64_MAX = 0x7fffffffffffffffll;
    
    inline constexpr usize USZ_MIN = 0ull;
    inline constexpr usize USZ_MAX = 0xffffffffffffffffull;
    inline constexpr ssize ISZ_MIN = (-0x7fffffffffffffffll - 1);
    inline constexpr ssize ISZ_MAX = 0x7fffffffffffffffll;
#endif
 
}  // namespace mojo

#ifndef mj_debug_trap
    #if MJ_COMPILER_MSVC
        #if _MSC_VER < 1300
            #define mj_debug_trap() __asm int 3
        #else
            #define mj_debug_trap() __debugbreak()
        #endif
    #elif MJ_COMPILER_CLANG
        #define mj_debug_trap() __builtin_debugtrap()
    #elif MJ_COMPILER_GCC
        #define mj_debug_trap() __builtin_trap()
    #endif
#endif
 
#ifndef mj_unreachable
    #if MJ_COMPILER_MSVC
        #define mj_unreachable()     \
            do {                     \
                mj_debug_trap();     \
                __assume(0);         \
            } while (0)
    #else
        #define mj_unreachable()         \
            do {                         \
                mj_debug_trap();         \
                __builtin_unreachable(); \
            } while (0)
    #endif
#endif

////////////////////////////////////////////////////////////////
// Attributes and decroators

#if MJ_COMPILER_MSVC
    #if !defined(mj_restrict)
        #define mj_restrict __restrict
    #endif
#else
    #define mj_restrict __restrict__
#endif

#endif  // _MOJO_HAL_HH
