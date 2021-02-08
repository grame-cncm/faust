/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2004-2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

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

template <int INPUTS, int OUTPUTS>
class unitydsp : public mydsp
{
    
    private:
        
        APIUI fUI;
        AudioChannels* fInputs;
        AudioChannels* fOutputs;
        
    public:
        
        unitydsp(UInt32 buffer_size = 0)
        {
            buildUserInterface(&fUI);
            if (buffer_size > 0) {
                fInputs = (INPUTS > 0) ? new AudioChannels(buffer_size, INPUTS) : nullptr;
                fOutputs = (OUTPUTS > 0) ? new AudioChannels(buffer_size, OUTPUTS) : nullptr;
            } else {
                fInputs = nullptr;
                fOutputs = nullptr;
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
            if (INPUTS > 0) fInputs->interleavedRead(inbuffer, length, inchannels);
            compute(length, ((INPUTS > 0) ? fInputs->buffers() : nullptr), ((OUTPUTS > 0) ? fOutputs->buffers() : nullptr));
            if (OUTPUTS > 0) fOutputs->interleavedWrite(outbuffer, length, outchannels);
        }
        
        void setParamValue(int pnum, float pval) { fUI.setParamValue(pnum, pval); }
        
        float getParamValue(int pnum) { return fUI.getParamValue(pnum); }
};

//=============================================================================
// The seven Unity callbacks: create(), reset(), release(), process(),
// setParameter, getParameter, getFloatBuffer.
//=============================================================================

#define UNITY_DSP unitydsp<FAUST_INPUTS, FAUST_OUTPUTS>

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK CreateCallback(UnityAudioEffectState* state)
{
    std::cout << "Create()" << std::endl;
    UNITY_DSP* p = new UNITY_DSP(state->dspbuffersize);
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
    UNITY_DSP* p = (UNITY_DSP*)state->effectdata;
    if (p) p->init(state->samplerate);
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ReleaseCallback(UnityAudioEffectState* state)
{
    std::cout << "Release()" << std::endl;
    UNITY_DSP* p = (UNITY_DSP*)state->effectdata;
    if (p) {
        delete p;
        state->effectdata = 0;
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ProcessCallback(UnityAudioEffectState* state, float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int outchannels)
{
    if (inchannels != outchannels) return UNITY_AUDIODSP_ERR_UNSUPPORTED;
    UNITY_DSP* p = (UNITY_DSP*)state->effectdata;
    if (p) {
        p->unityProcess(inbuffer, outbuffer, length, inchannels, outchannels);
    } else {
        memset(outbuffer, 0, sizeof(float) * length * inchannels);
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK SetFloatParameterCallback(UnityAudioEffectState* state, int pnum, float pval)
{
    UNITY_DSP* p = (UNITY_DSP*)state->effectdata;
    if (p) {
        p->setParamValue(pnum, pval);
    }
    return UNITY_AUDIODSP_OK;
}

UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK GetFloatParameterCallback(UnityAudioEffectState* state, int pnum, float* pval, char*)
{
    UNITY_DSP* p = (UNITY_DSP*)state->effectdata;
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
    
    UNITY_DSP* d = new UNITY_DSP();
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

/********************END ARCHITECTURE SECTION (part 2/2)****************/
