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
    
    struct mydsp_poly_wrap : public mydsp_poly, public MapUI {
        
        std::string fJSON;
    
        mydsp_poly_wrap(dsp* dsp, int max_polyphony)
            :mydsp_poly(dsp, max_polyphony, true, true)
        {
            // Creates paths
            buildUserInterface(this);
            
            // Creates JSON
            JSONUI builder(getNumInputs(), getNumOutputs());
            metadata(&builder);
            buildUserInterface(&builder);
            fJSON = builder.JSON();
        }
        
        const char* getJSON()
        {
            return fJSON.c_str();
        }
    };
    
    // C like API
    mydsp_poly_wrap* mydsp_poly_constructor(int max_polyphony)
    {
        return new mydsp_poly_wrap(new mydsp(), max_polyphony);
    }

    void mydsp_poly_destructor(mydsp_poly_wrap* poly)
    {
        delete poly;
    }
    
    int mydsp_poly_getSampleRate(mydsp_wrap* dsp)
    {
        return dsp->getSampleRate();
    }
    
    void mydsp_poly_init(mydsp_poly_wrap* dsp, int sample_rate)
    {
        dsp->init(sample_rate);
    }
    
    void mydsp_poly_instanceInit(mydsp_poly_wrap* dsp, int sample_rate)
    {
        dsp->instanceInit(sample_rate);
    }
    
    void mydsp_poly_instanceConstants(mydsp_poly_wrap* dsp, int sample_rate)
    {
        dsp->instanceConstants(sample_rate);
    }
    
    void mydsp_poly_instanceResetUserInterface(mydsp_wrap* dsp)
    {
        dsp->instanceResetUserInterface();
    }
    
    void mydsp_poly_instanceClear(mydsp_poly_wrap* dsp)
    {
        dsp->instanceClear();
    }
   
    const char* mydsp_poly_getJSON(mydsp_poly_wrap* poly)
    {
        return poly->getJSON();
    }
  
    void mydsp_poly_compute(mydsp_poly_wrap* poly, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        poly->compute(count, inputs, outputs);
    }

    int mydsp_poly_getNumInputs(mydsp_poly_wrap* poly)
    {
        return poly->getNumInputs();
    }

    int mydsp_poly_getNumOutputs(mydsp_poly_wrap* poly)
    {
        return poly->getNumOutputs();
    }

    MapUI* mydsp_poly_keyOn(mydsp_poly_wrap* poly, int channel, int pitch, int velocity)
    {
        return poly->keyOn(channel, pitch, velocity);
    }

    void mydsp_poly_keyOff(mydsp_poly_wrap* poly, int channel, int pitch, int velocity)
    {
        poly->keyOff(channel, pitch, velocity);
    }
    
    void mydsp_poly_allNotesOff(mydsp_poly_wrap* poly)
    {
        poly->allNotesOff();
    }
    
    void mydsp_poly_ctrlChange(mydsp_poly_wrap* poly, int channel, int ctrl, int value)
    {
        poly->ctrlChange(channel, ctrl, value);
    }
    
    void mydsp_poly_pitchWheel(mydsp_poly_wrap* poly, int channel, int wheel)
    {
        poly->pitchWheel(channel, wheel);
    }
    
    void mydsp_poly_setParamValue(mydsp_poly_wrap* poly, const char* path, float value)
    {
        poly->setParamValue(path, value);
    }

    float mydsp_poly_getParamValue(mydsp_poly_wrap* poly, const char* path)
    {
        return poly->getParamValue(path);
    }
    
};

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

