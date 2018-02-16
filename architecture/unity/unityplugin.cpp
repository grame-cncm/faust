//
// UnityPLugin.cpp
// 
//
//  Created by Théophile Dupré on 07/06/2017.
//  Copyright © 2017 Théophile Dupré. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <algorithm>

#include "faust/dsp/dsp.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/misc.h"
#include "faust/dsp/dsp-tools.h"

#ifdef _WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport
#endif

<<includeIntrinsic>>

<<includeclass>>

//=============================================================================
// unitydsp : a Faust dsp combined with an APIUI and AudioChannels that
// implements the various Unity callbacks.
//=============================================================================

class unitydsp : public mydsp
{
    
    private:
        
        APIUI fUI;
        AudioChannels* fInputs;
        AudioChannels* fOutputs;
        
    public:
        
        unitydsp(int dspbuffersize = 0)
        {
            buildUserInterface(&fUI);
            fInputs = 0;
            fOutputs = 0;
            if (dspbuffersize > 0) {
                fInputs = new AudioChannels(dspbuffersize, getNumInputs());
                fOutputs = new AudioChannels(dspbuffersize, getNumOutputs());
            }
        }
        
        ~unitydsp()
        {
            delete fInputs;
            delete fOutputs;
        }
        
        void unityProcess(float* inbuffer, float* outbuffer, int length, int inchannels, int outchannels)
        {
            fInputs->interleavedRead(inbuffer, length, inchannels);
            compute(length, fInputs->buffers(), fOutputs->buffers());
            fOutputs->interleavedWrite(outbuffer, length, outchannels);
        }
        
        void setParamValue(int pnum, float pval) { fUI.setParamValue(pnum, pval); }
        
        float getParamValue(int pnum) { return fUI.getParamValue(pnum); }
        
        float getParamMin(int pnum) { return fUI.getParamMin(pnum); }
        
        float getParamMax(int pnum) { return fUI.getParamMax(pnum); }
};

extern "C"
{
    DllExport unitydsp* Faust_contextNew(int bufferSize)
    {
        return new unitydsp(bufferSize);
    }
    
    DllExport void Faust_contextInit(unitydsp* ctx, int sampleRate) { ctx->init(sampleRate); }

    DllExport void Faust_process(unitydsp* ctx, FAUSTFLOAT* inbuffer, FAUSTFLOAT* oubuffer, int nframes, int channels)
    {
        ctx->unityProcess(inbuffer, oubuffer, nframes, channels, channels);
    }
    
    DllExport void Faust_delete(unitydsp* ctx) { delete ctx; }
    
    DllExport int Faust_getSampleRate(unitydsp* ctx) { return ctx->getSampleRate(); }
    
    DllExport int Faust_getNumInputChannels(unitydsp* ctx) { return ctx->getNumInputs(); }
    
    DllExport int Faust_getNumOutputChannels(unitydsp* ctx) { return ctx->getNumOutputs(); }
    
    DllExport void Faust_setParameterValue(unitydsp* ctx, int param, float value) { ctx->setParamValue(param, value); }
    
    DllExport float Faust_getParameterValue(unitydsp* ctx, int param) { return ctx->getParamValue(param); }
    
    DllExport float Faust_getParamMin(unitydsp* ctx, int param) { return ctx->getParamMin(param); }
    
    DllExport float Faust_getParamMax(unitydsp* ctx, int param) { return ctx->getParamMax(param); }
}
