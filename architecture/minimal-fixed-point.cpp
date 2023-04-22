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
#include "faust/audio/dummy-audio.h"
#include "faust/dsp/one-sample-dsp.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

#include "ap_fixed.h"

typedef ap_fixed<32, 8, AP_RND_CONV, AP_SAT> fixpoint_t;

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
    return fixpoint_t(exp10(float(x)));
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

using namespace std;

int main(int argc, char* argv[])
{
    mydsp DSP;
    cout << "DSP size: " << sizeof(DSP) << " bytes\n";
    
    // Activate the UI, here that only print the control paths
    PrintUI ui;
    DSP.buildUserInterface(&ui);
    
    // Allocate the audio driver to render 5 buffers of 512 frames
    dummyaudio audio(5);
    audio.init("Test", static_cast<dsp*>(&DSP));
    
    // Render buffers...
    audio.start();
    audio.stop();
}

/******************* END minimal-fixed-point.cpp ****************/
