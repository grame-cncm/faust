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

#ifdef _WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

<<includeIntrinsic>>

<<includeclass>>

//=============================================================================
// An AudioChannels is a group of non-interleved buffers that knows how to read
// from or write to an interleaved buffer. The interleaved buffer may have a
// different number of channels than the AudioChannels internal channels.

class AudioChannels
{
    
    protected:
        
        const unsigned int  fNumFrames;
        const unsigned int  fNumChannels;
        FAUSTFLOAT**        fChannels;
        
    public:
        
        AudioChannels(int nframes, int nchannels) : fNumFrames(nframes), fNumChannels(nchannels)
        {
            fChannels    = new FAUSTFLOAT*[nchannels];
            
            // allocate audio channels
            for (unsigned int i = 0; i < fNumChannels; i++) {
                fChannels[i] = new FAUSTFLOAT[fNumFrames];
                for (unsigned int j = 0; j < fNumFrames; j++) {
                    fChannels[i][j] = 0;
                }
            }
        }
        
        virtual ~AudioChannels()
        {
            // free separate input channels
            for (int i = 0; i < fNumChannels; i++) {
                delete[] fChannels[i];
            }
            delete[] fChannels;
        }
        
        //---------------------------------------------------------------------------------------
        // interleavedRead: read, from the interleaved buffer <inbuffer>, <length> frames on
        // <inchannels> channels. The samples are written to the <fNumChannels> internal
        // <fChannels>.
        void interleavedRead(float* inbuffer, unsigned int length, unsigned int inchannels)
        {
            assert(length <= fNumFrames);
            unsigned int C = std::min(inchannels, fNumChannels);
            unsigned int L = std::min(length, fNumFrames);
            
            for (unsigned int f = 0; f < L; f++) {
                unsigned int p = f * inchannels;
                for (unsigned int c = 0; c < C; c++) {
                    fChannels[c][f] = inbuffer[p++];
                }
                for (unsigned int c = C; c < fNumChannels; c++) {
                    fChannels[c][f] = 0;
                }
            }
        }
        
        //----------------------------------------------------------------------------------------
        // interleavedWrite: write to the interleaved buffer <inbuffer>, <length> frames on
        // <outchannels> channels. The samples are read from <fNumChannels> internal
        // <fChannels>.
        void interleavedWrite(float* outbuffer, unsigned int length, unsigned int outchannels)
        {
            assert(length <= fNumFrames);
            unsigned int C = std::min(outchannels, fNumChannels);
            unsigned int F = std::min(length, fNumFrames);
            
            for (unsigned int f = 0; f < F; f++) {
                int p = f * outchannels;
                for (unsigned int c = 0; c < C; c++) {
                    outbuffer[p++] = fChannels[c][f];
                }
                for (unsigned int c = C; c < outchannels; c++) {
                    outbuffer[p++] = 0;
                }
            }
        }
    
        //----------------------------------------------------------------------------------------
        // buffers: the internal buffers ready to use in the compute() method of a faust dsp
        
        FAUSTFLOAT** buffers() { return fChannels; }
};

//=============================================================================
// unitydsp : a Faust dsp combined with an APIUI and AudioChannels that
// implements the various Unity callbacks.

class unitydsp : public mydsp
{
    
    private:
        
        APIUI           fUI;
        AudioChannels*  fInputs;
        AudioChannels*  fOutputs;
        
    public:
        
        unitydsp(int dspbuffersize = 0)
        {
            buildUserInterface(&fUI);
            fInputs = 0;
            fOutputs = 0;
            if (dspbuffersize > 0) {
                fInputs  = new AudioChannels(dspbuffersize, getNumInputs());
                fOutputs = new AudioChannels(dspbuffersize, getNumOutputs());
            }
        }
        
        ~unitydsp()
        {
            if (fInputs) delete fInputs;
            if (fOutputs) delete fOutputs;
        }
        
         void unityProcess(float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int outchannels)
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
        unitydsp* ctx = new unitydsp(bufferSize);
        return ctx;
    }
    
    DllExport void Faust_contextInit(unitydsp* ctx, int sampleRate){ ctx->init(sampleRate); }

    DllExport void Faust_process(unitydsp* ctx, FAUSTFLOAT* inbuffer, FAUSTFLOAT* oubuffer, int nframes)
    {
        ctx->unityProcess(inbuffer, oubuffer, (unsigned int) nframes, ctx->getNumInputs(), ctx->getNumOutputs());
    }
    
    DllExport void Faust_delete(unitydsp* ctx){ delete ctx; }
    
    DllExport int Faust_getSampleRate(unitydsp* ctx){ return ctx->getSampleRate(); }
    
    DllExport int Faust_getNumInputChannels(unitydsp* ctx){ return ctx->getNumInputs(); }
    
    DllExport int Faust_getNumOutputChannels(unitydsp* ctx) { return ctx->getNumOutputs(); }
    
    DllExport void Faust_setParameterValue(unitydsp* ctx, int param, float value){ ctx->setParamValue(param, value); }
    
    DllExport float Faust_getParameterValue(unitydsp* ctx, int param){ return ctx->getParamValue(param); }
    
    DllExport float Faust_getParamMin(unitydsp* ctx, int param) { return ctx->getParamMin(param); }
    
    DllExport float Faust_getParamMax(unitydsp* ctx, int param) { return ctx->getParamMax(param); }
}
