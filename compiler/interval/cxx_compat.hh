/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>
#if __cplusplus >= 202002L
#include <bit>
#endif

// The library is compiled as C++17 by its hosts (the Faust compiler among them).
// The two C++20 bit utilities it needs are provided here, and resolve to the
// standard ones when the host compiles in C++20.
namespace itv::compat {

// The object representation of from, read as a To of the same size.
template <class To, class From>
inline To bit_cast(const From& from) noexcept
{
    static_assert(sizeof(To) == sizeof(From), "bit_cast needs types of the same size");
    static_assert(std::is_trivially_copyable_v<To> && std::is_trivially_copyable_v<From>,
                  "bit_cast needs trivially copyable types");
#if defined(__cpp_lib_bit_cast) && __cpp_lib_bit_cast >= 201806L
    return std::bit_cast<To>(from);
#else
    To to;
    std::memcpy(&to, &from, sizeof(To));
    return to;
#endif
}

// The number of leading zero bits of x, 64 for x == 0.
inline int countl_zero(uint64_t x) noexcept
{
#if defined(__cpp_lib_bitops) && __cpp_lib_bitops >= 201907L
    return std::countl_zero(x);
#else
    int n = 0;
    for (uint64_t bit = UINT64_C(1) << 63; bit != 0 && (x & bit) == 0; bit >>= 1) ++n;
    return n;
#endif
}

}  // namespace itv::compat
