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

// Usage : faust -i -uim -a webaudio/webaudio-asm.cpp -cn karplus karplus.dsp -o karplus.cpp

<<includeIntrinsic>>

<<includeclass>>

extern "C" {
    
    // Just inherit from both classes...
    struct mydsp_wrap : public mydsp, public MapUI
    {
        std::string fJSON;
        
        mydsp_wrap(int sample_rate) 
        {
            // Init it with sample_rate supplied...
            init(sample_rate);
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
    mydsp_wrap* mydsp_constructor(int sample_rate) 
    {
        return new mydsp_wrap(sample_rate);
    }
    
    void mydsp_destructor(mydsp_wrap* dsp)
    {
        delete dsp;
    }

    void mydsp_compute(mydsp_wrap* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        dsp->compute(count, inputs, outputs);
    }
    
    int mydsp_getNumInputs(mydsp_wrap* dsp)
    {
        return dsp->getNumInputs();
    }
    
    int mydsp_getNumOutputs(mydsp_wrap* dsp)
    {
        return dsp->getNumOutputs();
    }
      
    const char* mydsp_getJSON(mydsp_wrap* dsp)
    {
        return dsp->getJSON();
    }
    
    void mydsp_setParamValue(mydsp_wrap* dsp, const char* path, float value)
    {
        dsp->setParamValue(path, value);
    }
    
    float mydsp_getParamValue(mydsp_wrap* dsp, const char* path)
    {
        return dsp->getParamValue(path);
    }
    
}