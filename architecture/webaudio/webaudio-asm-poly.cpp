/*
 faust2webaudio
 
 Primarily written by Myles Borins
 During the Spring 2013 offering of Music 420b with Julius Smith
 A bit during the Summer of 2013 with the help of Joshua Kit Clayton
 And finally a sprint during the late fall of 2013 to get everything working
 A Special thanks to Yann Orlarey and Stéphane Letz
 
 faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
 Choose the license that best suits your project. The text of the MIT and GPL
 licenses are at the root directory.
 
 Additional code : GRAME 2014

*/

// Adapted From https://gist.github.com/camupod/5640386
// compile using "C" linkage to avoid name obfuscation

#include <emscripten.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>

#include "faust/misc.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp.h"

// "mydsp" part will be replaced by the actual '-cn' parameter

// Usage : faust -i -uim -a webaudio/webaudio-asm-poly.cpp -cn karplus karplus.dsp -o karplus.cpp

<<includeIntrinsic>>

<<includeclass>>

#include "faust/dsp/poly-dsp.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

