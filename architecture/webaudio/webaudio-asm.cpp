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

#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dsp.h"

// "mydsp" part will be replaced by the actual '-cn' parameter

// Usage : faust -i -uim -a webaudio/webaudio-asm.cpp -cn karplus karplus.dsp -o karplus.cpp

inline int max(unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int max(int a, int b)	{ return (a>b) ? a : b; }

inline long max(long a, long b) { return (a>b) ? a : b; }
inline long max(int a, long b) 	{ return (a>b) ? a : b; }
inline long max(long a, int b) 	{ return (a>b) ? a : b; }

inline float max(float a, float b) { return (a>b) ? a : b; }
inline float max(int a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, int b) 	{ return (a>b) ? a : b; }
inline float max(long a, float b) 	{ return (a>b) ? a : b; }
inline float max(float a, long b) 	{ return (a>b) ? a : b; }

inline double max(double a, double b) 	{ return (a>b) ? a : b; }
inline double max(int a, double b)      { return (a>b) ? a : b; }
inline double max(double a, int b)      { return (a>b) ? a : b; }
inline double max(long a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, long b) 	{ return (a>b) ? a : b; }
inline double max(float a, double b) 	{ return (a>b) ? a : b; }
inline double max(double a, float b) 	{ return (a>b) ? a : b; }

inline int	min(int a, int b)	{ return (a<b) ? a : b; }

inline long min(long a, long b) { return (a<b) ? a : b; }
inline long min(int a, long b) 	{ return (a<b) ? a : b; }
inline long min(long a, int b) 	{ return (a<b) ? a : b; }

inline float min(float a, float b) { return (a<b) ? a : b; }
inline float min(int a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, int b) 	{ return (a<b) ? a : b; }
inline float min(long a, float b) 	{ return (a<b) ? a : b; }
inline float min(float a, long b) 	{ return (a<b) ? a : b; }

inline double min(double a, double b) 	{ return (a<b) ? a : b; }
inline double min(int a, double b)      { return (a<b) ? a : b; }
inline double min(double a, int b)      { return (a<b) ? a : b; }
inline double min(long a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, long b) 	{ return (a<b) ? a : b; }
inline double min(float a, double b) 	{ return (a<b) ? a : b; }
inline double min(double a, float b) 	{ return (a<b) ? a : b; }

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
            mydsp::metadata(&builder);
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
    
    void mydsp_destructor(mydsp_wrap* n) 
    {
        delete n;
    }

    void mydsp_compute(mydsp_wrap* n, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        n->compute(count, inputs, outputs);
    }
    
    int mydsp_getNumInputs(mydsp_wrap* n)
    {
        return n->getNumInputs();
    }
    
    int mydsp_getNumOutputs(mydsp_wrap* n)
    {
        return n->getNumOutputs();
    }
      
    const char* mydsp_getJSON(mydsp_wrap* n)
    {
        return n->getJSON();
    }
    
    void mydsp_setValue(mydsp_wrap* n, const char* path, float value)
    {
        n->setValue(path, value);
    }
    
    float mydsp_getValue(mydsp_wrap* n, const char* path)
    {
        return n->getValue(path);
    }
    
}