/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-fixed-point.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/
 
#include <algorithm>
#include <cmath>

#include "faust/gui/PrintUI.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

#include "ap_fixed.h"

typedef ap_fixed<32,8,AP_RND_CONV,AP_SAT> fixpoint_t;

// m: position of the most significant bit of the value, without taking the sign bit into account
// l: LSB with negative coding
#define sfx_t(m,l) ap_fixed<((m+1)-l+1),(m+1)+1,AP_RND_CONV,AP_SAT>
#define ufx_t(m,l) ap_ufixed<((m+1)-l),(m+1),AP_RND_CONV,AP_SAT>

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

inline float minfx(float x, float y) { return (x < y) ? x : y; }
inline float maxfx(float x, float y) { return (x < y) ? y : x; }

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/******************* END minimal-fixed-point.cpp ****************/
