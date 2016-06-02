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
 
 Additional code : GRAME 2014-2016

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

extern "C" {
    
    // C like API
    mydsp_poly* mydsp_poly_constructor(int sample_rate, int max_polyphony) 
    {
        mydsp_poly* poly = new mydsp_poly(max_polyphony, true, true);
        if (poly) poly->init(sample_rate);
        return poly;
    }

    void mydsp_poly_destructor(mydsp_poly* poly) 
    {
        delete poly;
    }

    const char* mydsp_poly_getJSON(mydsp_poly* poly)
    {
        return poly->getJSON();
    }
  
    void mydsp_poly_compute(mydsp_poly* poly, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        poly->compute(count, inputs, outputs);
    }

    int mydsp_poly_getNumInputs(mydsp_poly* poly)
    {
        return poly->getNumInputs();
    }

    int mydsp_poly_getNumOutputs(mydsp_poly* poly)
    {
        return poly->getNumOutputs();
    }

    int mydsp_poly_keyOn(mydsp_poly* poly, int channel, int pitch, int velocity)
    {
        return poly->keyOn(channel, pitch, velocity);
    }

    void mydsp_poly_keyOff(mydsp_poly* poly, int channel, int pitch, int velocity)
    {
        poly->keyOff(channel, pitch, velocity);
    }
    
    void mydsp_poly_allNotesOff(mydsp_poly* poly)
    {
        poly->allNotesOff();
    }
    
    void mydsp_poly_ctrlChange(mydsp_poly* poly, int channel, int ctrl, int value)
    {
        poly->ctrlChange(channel, ctrl, value);
    }
    
    void mydsp_poly_pitchWheel(mydsp_poly* poly, int channel, int wheel)
    {
        poly->pitchWheel(channel, wheel);
    }
    
    void mydsp_poly_setParamValue(mydsp_poly* poly, const char* path, float value)
    {
        poly->setParamValue(path, value);
    }

    float mydsp_poly_getParamValue(mydsp_poly* poly, const char* path)
    {
        return poly->getParamValue(path);
    }
    
    void mydsp_poly_setVoiceParamValue(mydsp_poly* poly, const char* path, int voice, float value)
    {
        poly->setVoiceParamValue(path, voice, value);
    }
    
    float mydsp_poly_getVoiceParamValue(mydsp_poly* poly, const char* path, int voice)
    {
        return poly->getVoiceParamValue(path, voice);
    }
        
};

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

