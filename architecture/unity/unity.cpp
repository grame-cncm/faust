/*
 c++ -I. -O2 -fPIC -arch i386 -arch x86_64 -bundle audiothrudemo.cpp -o
 audiothrudemo.so
 */

#include <string.h>
#include <iostream>
#include <algorithm>

#include "faust/dsp/dsp.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/misc.h"
#include "faust/dsp/dsp-tools.h"
#include "faust/unity/AudioPluginInterface.h"

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
        
        unitydsp(UInt32 dspbuffersize = 0)
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
        
        void ComputeUnityParameters(UnityAudioEffectDefinition* definition)
        {
            // create the parameter definitions
            int n = fUI.getParamsCount();
            UnityAudioParameterDefinition* pdef = (UnityAudioParameterDefinition*)malloc(n * sizeof(UnityAudioParameterDefinition));
            for (int i = 0; i < n; i++) {
                // fill the parameters definitions
                strncpy(pdef[i].name, fUI.getParamAddress(i), 15);
                pdef[i].name[15] = 0;
                strncpy(pdef[i].unit, fUI.getMetadata("unit", i), 15);
                pdef[i].unit[15] = 0;
                pdef[i].description = strndup(fUI.getMetadata("tooltip", i), 256);
                pdef[i].min = fUI.getParamMin(i);
                pdef[i].max = fUI.getParamMax(i);
                pdef[i].defaultval = fUI.getParamInit(i);
                pdef[i].displayscale = 1;
                pdef[i].displayexponent = 1;
            }
            definition->numparameters = n;
            definition->paramdefs = pdef;
        }
        
        void unityProcess(float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int outchannels)
        {
            fInputs->interleavedRead(inbuffer, length, inchannels);
            compute(length, fInputs->buffers(), fOutputs->buffers());
            fOutputs->interleavedWrite(outbuffer, length, outchannels);
        }
        
        void setParamValue(int pnum, float pval) { fUI.setParamValue(pnum, pval); }
        
        float getParamValue(int pnum) { return fUI.getParamValue(pnum); }
};

//=============================================================================
// The seven Unity callbacks: create(), reset(), release(), process(),
// setParameter, getParameter, getFloatBuffer.
//=============================================================================

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK CreateCallback(UnityAudioEffectState* state)
{
    std::cout << "Create()" << std::endl;
    unitydsp* p = new unitydsp(state->dspbuffersize);
    if (p) {
        state->effectdata = p;
        return UNITY_AUDIODSP_OK;
    } else {
        std::cerr << "Failed to allocate dsp object" << std::endl;
        return UNITY_AUDIODSP_ERR_UNSUPPORTED;
    }
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ResetCallback(UnityAudioEffectState* state)
{
    std::cout << "Reset()" << std::endl;
    unitydsp* p = (unitydsp*)state->effectdata;
    if (p) p->init(state->samplerate);
    
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ReleaseCallback(UnityAudioEffectState* state)
{
    std::cout << "Release()" << std::endl;
    unitydsp* p = (unitydsp*)state->effectdata;
    if (p) {
        delete p;
        state->effectdata = 0;
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ProcessCallback(UnityAudioEffectState* state, float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int outchannels)
{
    if (inchannels != outchannels) return UNITY_AUDIODSP_ERR_UNSUPPORTED;
    unitydsp* p = (unitydsp*)state->effectdata;
    
    if (p) {
        p->unityProcess(inbuffer, outbuffer, length, inchannels, outchannels);
    } else {
        memset(outbuffer, 0, sizeof(float) * length * inchannels);
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK SetFloatParameterCallback(UnityAudioEffectState* state, int pnum, float pval)
{
    unitydsp* p = (unitydsp*)state->effectdata;
    
    if (p) {
        p->setParamValue(pnum, pval);
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK GetFloatParameterCallback(UnityAudioEffectState* state, int pnum, float* pval, char*)
{
    unitydsp* p = (unitydsp*)state->effectdata;
    if (p) {
        *pval = p->getParamValue(pnum);
    }
    return UNITY_AUDIODSP_OK;
}

int UNITY_AUDIODSP_CALLBACK GetFloatBufferCallback(UnityAudioEffectState*, const char*, float*, int) { return UNITY_AUDIODSP_OK; }

//=============================================================================
// UnityGetAudioEffectDefinitions() : the entry point of a unity audio plugin.
// It uses the macro symbol PLUGINAME to create the plugin name. It creates a
// temporary dsp object to decribe the user interface. Potentially more than
// one plugin can be described. But here only one is described.
//=============================================================================

#define xstr(s) str(s)
#define str(s) #s

extern "C" UNITY_AUDIODSP_EXPORT_API int UnityGetAudioEffectDefinitions(UnityAudioEffectDefinition*** definitionptr)
{
    std::cout << "Definition()" << std::endl;
    static UnityAudioEffectDefinition definition;
    static UnityAudioEffectDefinition* definitionp[1];
    
    memset(&definition, 0, sizeof(definition));
    strcpy(definition.name, xstr(PLUGINNAME));
    definition.structsize = sizeof(UnityAudioEffectDefinition);
    definition.paramstructsize = sizeof(UnityAudioParameterDefinition);
    definition.apiversion = UNITY_AUDIO_PLUGIN_API_VERSION;
    definition.pluginversion = 0x010000;
    definition.create = CreateCallback;
    definition.reset = ResetCallback;
    definition.release = ReleaseCallback;
    definition.process = ProcessCallback;
    definition.setfloatparameter = SetFloatParameterCallback;
    definition.getfloatparameter = GetFloatParameterCallback;
    definition.getfloatbuffer = GetFloatBufferCallback;
    
    unitydsp* d = new unitydsp();
    if (d) {
        d->ComputeUnityParameters(&definition);
        // unity plugins are either effects (n->n) or generators (0->n)
        // for effects definition.channels must be 0
        definition.channels = (d->getNumInputs() != 0) ? 0 : d->getNumOutputs();
        delete d;
    }
    
    definitionp[0] = &definition;
    *definitionptr = definitionp;
    return 1;
}
