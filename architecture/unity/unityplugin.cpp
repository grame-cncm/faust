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

#ifdef POLY

#include "faust/dsp/poly-dsp.h"

class unitypolydsp : public decorator_dsp
{
    
    private:
        
        APIUI fUI;
        AudioChannels* fInputs;
        AudioChannels* fOutputs;
    
    public:
        
        unitypolydsp(int dspbuffersize, int nvoices)
        {
            /*
            bool midi_sync = false;
            // Analyse NVOICES
            mydsp* tmp_dsp = new mydsp();
            MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
            delete tmp_dsp;
            */
            
            fDSP = new mydsp_poly(new mydsp(), nvoices, true, true);
            fDSP->buildUserInterface(&fUI);
            
            fInputs = 0;
            fOutputs = 0;
            if (dspbuffersize > 0) {
                fInputs = new AudioChannels(dspbuffersize, fDSP->getNumInputs());
                fOutputs = new AudioChannels(dspbuffersize, fDSP->getNumOutputs());
            }
        }
        
        ~unitypolydsp()
        {
            delete fInputs;
            delete fOutputs;
        }
        
        void unityProcess(float* inbuffer, float* outbuffer, int length, int inchannels, int outchannels)
        {
            fInputs->interleavedRead(inbuffer, length, inchannels);
            fDSP->compute(length, fInputs->buffers(), fOutputs->buffers());
            fOutputs->interleavedWrite(outbuffer, length, outchannels);
        }
        
        void setParamValue(int pnum, float pval) { fUI.setParamValue(pnum, pval); }
        
        float getParamValue(int pnum) { return fUI.getParamValue(pnum); }
        
        float getParamMin(int pnum) { return fUI.getParamMin(pnum); }
        
        float getParamMax(int pnum) { return fUI.getParamMax(pnum); }
    
        void keyOn(int channel, int pitch, int velocity)
        {
            static_cast<mydsp_poly*>(fDSP)->keyOn(channel, pitch, velocity);
        }
        
        void keyOff(int channel, int pitch, int velocity = 127)
        {
            static_cast<mydsp_poly*>(fDSP)->keyOff(channel, pitch, velocity);
        }
        
        void ctrlChange(int channel, int ctrl, int value)
        {
            static_cast<mydsp_poly*>(fDSP)->ctrlChange(channel, ctrl, value);
        }
        
        void allNotesOff(bool hard = false)
        {
            static_cast<mydsp_poly*>(fDSP)->allNotesOff(hard);
        }

};

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

extern "C"
{
    DllExport unitypolydsp* Faust_contextNew(int bufferSize, int nvoices)
    {
        return new unitypolydsp(bufferSize, nvoices);
    }
    
    DllExport void Faust_contextInit(unitypolydsp* ctx, int sampleRate) { ctx->init(sampleRate); }
    
    DllExport void Faust_process(unitypolydsp* ctx, FAUSTFLOAT* inbuffer, FAUSTFLOAT* oubuffer, int nframes, int channels)
    {
        ctx->unityProcess(inbuffer, oubuffer, nframes, channels, channels);
    }
    
    DllExport void Faust_delete(unitypolydsp* ctx) { delete ctx; }
    
    DllExport int Faust_getSampleRate(unitypolydsp* ctx) { return ctx->getSampleRate(); }
    
    DllExport int Faust_getNumInputChannels(unitypolydsp* ctx) { return ctx->getNumInputs(); }
    
    DllExport int Faust_getNumOutputChannels(unitypolydsp* ctx) { return ctx->getNumOutputs(); }
    
    DllExport void Faust_setParameterValue(unitypolydsp* ctx, int param, float value) { ctx->setParamValue(param, value); }
    
    DllExport float Faust_getParameterValue(unitypolydsp* ctx, int param) { return ctx->getParamValue(param); }
    
    DllExport float Faust_getParamMin(unitypolydsp* ctx, int param) { return ctx->getParamMin(param); }
    
    DllExport float Faust_getParamMax(unitypolydsp* ctx, int param) { return ctx->getParamMax(param); }
    
    // MIDI API
    DllExport void Faust_keyOn(unitypolydsp* ctx, int channel, int pitch, int velocity)
    {
        ctx->keyOn(channel, pitch, velocity);
    }
    
    DllExport void Faust_keyOff(unitypolydsp* ctx, int channel, int pitch, int velocity = 127)
    {
        ctx->keyOff(channel, pitch, velocity);
    }
    
    DllExport void Faust_ctrlChange(unitypolydsp* ctx, int channel, int ctrl, int value)
    {
        ctx->ctrlChange(channel, ctrl, value);
    }
    
    DllExport void Faust_allNotesOff(unitypolydsp* ctx, bool hard = false)
    {
        ctx->allNotesOff(hard);
    }

}

#else

class unitydsp : public mydsp
{
    
    private:
    
        APIUI fUI;
        AudioChannels* fInputs;
        AudioChannels* fOutputs;
        
    public:
        
        unitydsp(int dspbuffersize)
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
#endif


