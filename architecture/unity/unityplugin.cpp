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

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

<<includeIntrinsic>>

<<includeclass>>

//=============================================================================
// unitydsp : a Faust dsp combined with an APIUI and AudioChannels that
// implements the various Unity callbacks.
//=============================================================================

#ifdef POLY

#include "faust/dsp/poly-dsp.h"

template <int INPUTS, int OUTPUTS>
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
            
            if (dspbuffersize > 0) {
                fInputs = (INPUTS > 0) ? new AudioChannels(dspbuffersize, INPUTS) : nullptr;
                fOutputs = (OUTPUTS > 0) ? new AudioChannels(dspbuffersize, OUTPUTS) : nullptr;
            }
        }
    
        ~unitypolydsp()
        {
            delete fInputs;
            delete fOutputs;
        }
    
        void unityProcess(float* inbuffer, float* outbuffer, int length, int inchannels, int outchannels)
        {
            if (INPUTS > 0) fInputs->interleavedRead(inbuffer, length, inchannels);
            fDSP->compute(length, ((INPUTS > 0) ? fInputs->buffers() : nullptr), ((OUTPUTS > 0) ? fOutputs->buffers() : nullptr));
            if (OUTPUTS > 0) fOutputs->interleavedWrite(outbuffer, length, outchannels);
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
#define UNITY_POLY_DSP unitypolydsp<FAUST_INPUTS, FAUST_OUTPUTS>
    
    DllExport UNITY_POLY_DSP* Faust_contextNew(int bufferSize, int nvoices)
    {
        return new UNITY_POLY_DSP(bufferSize, nvoices);
    }
    
    DllExport void Faust_contextInit(UNITY_POLY_DSP* ctx, int sampleRate) { ctx->init(sampleRate); }
    
    DllExport void Faust_process(UNITY_POLY_DSP* ctx, FAUSTFLOAT* inbuffer, FAUSTFLOAT* oubuffer, int nframes, int channels)
    {
        ctx->unityProcess(inbuffer, oubuffer, nframes, channels, channels);
    }
    
    DllExport void Faust_delete(UNITY_POLY_DSP* ctx) { delete ctx; }
    
    DllExport int Faust_getSampleRate(UNITY_POLY_DSP* ctx) { return ctx->getSampleRate(); }
    
    DllExport int Faust_getNumInputChannels(UNITY_POLY_DSP* ctx) { return ctx->getNumInputs(); }
    
    DllExport int Faust_getNumOutputChannels(UNITY_POLY_DSP* ctx) { return ctx->getNumOutputs(); }
    
    DllExport void Faust_setParameterValue(UNITY_POLY_DSP* ctx, int param, float value) { ctx->setParamValue(param, value); }
    
    DllExport float Faust_getParameterValue(UNITY_POLY_DSP* ctx, int param) { return ctx->getParamValue(param); }
    
    DllExport float Faust_getParamMin(UNITY_POLY_DSP* ctx, int param) { return ctx->getParamMin(param); }
    
    DllExport float Faust_getParamMax(UNITY_POLY_DSP* ctx, int param) { return ctx->getParamMax(param); }
    
    // MIDI API
    DllExport void Faust_keyOn(UNITY_POLY_DSP* ctx, int channel, int pitch, int velocity)
    {
        ctx->keyOn(channel, pitch, velocity);
    }
    
    DllExport void Faust_keyOff(UNITY_POLY_DSP* ctx, int channel, int pitch, int velocity = 127)
    {
        ctx->keyOff(channel, pitch, velocity);
    }
    
    DllExport void Faust_ctrlChange(UNITY_POLY_DSP* ctx, int channel, int ctrl, int value)
    {
        ctx->ctrlChange(channel, ctrl, value);
    }
    
    DllExport void Faust_allNotesOff(UNITY_POLY_DSP* ctx, bool hard = false)
    {
        ctx->allNotesOff(hard);
    }
    
}

#else

template <int INPUTS, int OUTPUTS>
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
            if (dspbuffersize > 0) {
                fInputs = (INPUTS > 0) ? new AudioChannels(dspbuffersize, INPUTS) : nullptr;
                fOutputs = (OUTPUTS > 0) ? new AudioChannels(dspbuffersize, OUTPUTS) : nullptr;
            }
        }
    
        ~unitydsp()
        {
            delete fInputs;
            delete fOutputs;
        }
    
        void unityProcess(float* inbuffer, float* outbuffer, int length, int inchannels, int outchannels)
        {
            if (INPUTS > 0 ) fInputs->interleavedRead(inbuffer, length, inchannels);
            compute(length, ((INPUTS > 0 ) ? fInputs->buffers() : nullptr), ((OUTPUTS > 0) ? fOutputs->buffers() : nullptr));
            if (OUTPUTS > 0) fOutputs->interleavedWrite(outbuffer, length, outchannels);
        }
    
        void setParamValue(int pnum, float pval) { fUI.setParamValue(pnum, pval); }
    
        float getParamValue(int pnum) { return fUI.getParamValue(pnum); }
    
        float getParamMin(int pnum) { return fUI.getParamMin(pnum); }
    
        float getParamMax(int pnum) { return fUI.getParamMax(pnum); }
    
};

extern "C"
{
    
    #define UNITY_DSP unitydsp<FAUST_INPUTS, FAUST_OUTPUTS>
    
    DllExport UNITY_DSP* Faust_contextNew(int bufferSize)
    {
        return new UNITY_DSP(bufferSize);
    }
    
    DllExport void Faust_contextInit(UNITY_DSP* ctx, int sampleRate) { ctx->init(sampleRate); }
    
    DllExport void Faust_process(UNITY_DSP* ctx, FAUSTFLOAT* inbuffer, FAUSTFLOAT* oubuffer, int nframes, int channels)
    {
        ctx->unityProcess(inbuffer, oubuffer, nframes, channels, channels);
    }
    
    DllExport void Faust_delete(UNITY_DSP* ctx) { delete ctx; }
    
    DllExport int Faust_getSampleRate(UNITY_DSP* ctx) { return ctx->getSampleRate(); }
    
    DllExport int Faust_getNumInputChannels(UNITY_DSP* ctx) { return ctx->getNumInputs(); }
    
    DllExport int Faust_getNumOutputChannels(UNITY_DSP* ctx) { return ctx->getNumOutputs(); }
    
    DllExport void Faust_setParameterValue(UNITY_DSP* ctx, int param, float value) { ctx->setParamValue(param, value); }
    
    DllExport float Faust_getParameterValue(UNITY_DSP* ctx, int param) { return ctx->getParamValue(param); }
    
    DllExport float Faust_getParamMin(UNITY_DSP* ctx, int param) { return ctx->getParamMin(param); }
    
    DllExport float Faust_getParamMax(UNITY_DSP* ctx, int param) { return ctx->getParamMax(param); }
    
}
#endif


