/************************************************************************
 FAUST Architecture File
 Copyright (C) 2023 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 **************************************************************************/

#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <cmath>
// Code for ap_fixed type mode
#include "ap_fixed.h"

typedef ap_fixed<32,8,AP_RND_CONV,AP_SAT> fixpoint_t;

// m: MSB, l: LSB (negative coding)
#define sfx_t(m,l) ap_fixed<(m-l+1),m+1,AP_RND_CONV,AP_SAT>
#define ufx_t(m,l) ap_ufixed<(m-l),m,AP_RND_CONV,AP_SAT>

/*
// fx version
inline fixpoint_t fabsfx(fixpoint_t x)
{
    return fixpoint_t(std::fabs(float(x)));
}
inline fixpoint_t acosfx(fixpoint_t x)
{
    return fixpoint_t(std::acos(float(x)));
}
inline fixpoint_t asinfx(fixpoint_t x)
{
    return fixpoint_t(std::asin(float(x)));
}
inline fixpoint_t atanfx(fixpoint_t x)
{
    return fixpoint_t(std::atan(float(x)));
}
inline fixpoint_t atan2fx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::atan2(float(x), float(y)));
}
inline fixpoint_t ceilfx(fixpoint_t x)
{
    return fixpoint_t(std::ceil(float(x)));
}
inline fixpoint_t cosfx(fixpoint_t x)
{
    return fixpoint_t(std::cos(float(x)));
}
inline fixpoint_t expfx(fixpoint_t x)
{
    return fixpoint_t(std::exp(float(x)));
}
inline fixpoint_t exp2fx(fixpoint_t x)
{
    return fixpoint_t(std::exp2(float(x)));
}
inline fixpoint_t exp10fx(fixpoint_t x)
{
#ifdef __APPLE__
    return fixpoint_t(__exp10f(float(x)));
#else
    return fixpoint_t(std::exp10(float(x)));
#endif
}
inline fixpoint_t floorfx(fixpoint_t x)
{
    return fixpoint_t(std::floor(float(x)));
}
inline fixpoint_t fmodfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::fmod(float(x), float(y)));
}
inline fixpoint_t logfx(fixpoint_t x)
{
    return fixpoint_t(std::log(float(x)));
}
inline fixpoint_t log2fx(fixpoint_t x)
{
    return fixpoint_t(std::log2(float(x)));
}
inline fixpoint_t log10fx(fixpoint_t x)
{
    return fixpoint_t(std::log10(float(x)));
}
inline fixpoint_t powfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::pow(float(x), float(y)));
}
inline fixpoint_t remainderfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::remainder(float(x), float(y)));
}
inline fixpoint_t rintfx(fixpoint_t x)
{
    return fixpoint_t(std::rint(float(x)));
}
inline fixpoint_t roundfx(fixpoint_t x)
{
    return fixpoint_t(std::round(float(x)));
}
inline fixpoint_t sinfx(fixpoint_t x)
{
    return fixpoint_t(std::sin(float(x)));
}
inline fixpoint_t sqrtfx(fixpoint_t x)
{
    return fixpoint_t(std::sqrt(float(x)));
}
inline fixpoint_t tanfx(fixpoint_t x)
{
    return fixpoint_t(std::tan(float(x)));
}
// min/max
inline fixpoint_t fminfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::min(float(x), float(y)));
}
inline fixpoint_t fmaxfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::max(float(x), float(y)));
}
*/

// fx version
inline float fabsfx(float x)
{
    return std::fabs(x);
}
inline float acosfx(float x)
{
    return std::acos(x);
}
inline float asinfx(float x)
{
    return std::asin(x);
}
inline float atanfx(float x)
{
    return std::atan(x);
}
inline float atan2fx(float x, float y)
{
    return std::atan2(x, y);
}
inline float ceilfx(float x)
{
    return std::ceil(x);
}
inline float cosfx(float x)
{
    return std::cos(x);
}
inline float expfx(float x)
{
    return std::exp(x);
}
inline float exp2fx(float x)
{
    return std::exp2(x);
}
inline float exp10fx(float x)
{
#ifdef __APPLE__
    return __exp10f(x);
#else
    return exp10(x);
#endif
}
inline float floorfx(float x)
{
    return std::floor(x);
}
inline float fmodfx(float x, float y)
{
    return std::fmod(x, y);
}
inline float logfx(float x)
{
    return std::log(x);
}
inline float log2fx(float x)
{
    return std::log2(x);
}
inline float log10fx(float x)
{
    return std::log10(x);
}
inline float powfx(float x, float y)
{
    return std::pow(x, y);
}
inline float remainderfx(float x, float y)
{
    return std::remainder(x, y);
}
inline float rintfx(float x)
{
    return std::rint(x);
}
inline float roundfx(float x)
{
    return std::round(x);
}
inline float sinfx(float x)
{
    return std::sin(x);
}
inline float sqrtfx(float x)
{
    return std::sqrt(x);
}
inline float tanfx(float x)
{
    return std::tan(x);
}
// min/max
/*
#define minfx(x, y) { (((x) < (y)) ? (x) : (y)) }
#define maxfx(x, y) { (((x) < (y)) ? (y) : (x)) }
*/

inline float minfx(float x, float y) { return (x < y) ? x : y; }
inline float maxfx(float x, float y) { return (x < y) ? y : x; }

#endif
