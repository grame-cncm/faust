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

#import "DSPBase.h"
#import <algorithm>
#import <vector>
#import <assert.h>

#include "faust/dsp/dsp.h"
#include "faust/misc.h"
#include "faust/gui/DecoratorUI.h"

#ifdef MIDICTRL
#include "faust/gui/MidiUI.h"
#endif

#ifdef POLY
#include "faust/dsp/poly-dsp.h"
#endif

#define FAUST_UIMACROS 1

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

class Faustmydsp : public DSPBase, public GenericUI {
    
    private:
        mydsp* fDSP;
        size_t inputChannelCount = 0;
        size_t outputChannelCount = 0;
        std::vector<FAUSTFLOAT*> fZones;
    #ifdef MIDICTRL
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    #endif
    
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone) override { fZones.push_back(zone); }
        void addCheckButton(const char* label, FAUSTFLOAT* zone) override { fZones.push_back(zone); }
        void addVerticalSlider(const char*
                               label,
                               FAUSTFLOAT* zone,
                               FAUSTFLOAT init,
                               FAUSTFLOAT min,
                               FAUSTFLOAT max,
                               FAUSTFLOAT step) override
        {
            fZones.push_back(zone);
        }
        void addHorizontalSlider(const char*
                                 label,
                                 FAUSTFLOAT* zone,
                                 FAUSTFLOAT init,
                                 FAUSTFLOAT min,
                                 FAUSTFLOAT max,
                                 FAUSTFLOAT step) override
        {
            fZones.push_back(zone);
        }
        void addNumEntry(const char*
                         label,
                         FAUSTFLOAT* zone,
                         FAUSTFLOAT init,
                         FAUSTFLOAT min,
                         FAUSTFLOAT max,
                         FAUSTFLOAT step) override
        {
            fZones.push_back(zone);
        }
    
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override {}
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override {}
    
    public:
    
    #ifdef MIDICTRL
        Faustmydsp():fMidiUI(&fMidiHandler)
    #else
        Faustmydsp()
    #endif
        {
        #ifdef POLY
            int nvoices = 0;
            bool midi_sync = false;
            fDSP = new mydsp();
            MidiMeta::analyse(DSP, midi_sync, nvoices);
            fDSP = new mydsp_poly(DSP, nvoices, true, true);
        #else
            fDSP = new mydsp();
        #endif
            inputChannelCount = fDSP->getNumInputs();
            outputChannelCount = fDSP->getNumOutputs();
        #ifdef MIDICTRL
            fDSP->buildUserInterface(&fMidiUI);
        #endif
            fDSP->buildUserInterface(this);
            //assert(fDSP->getNumInputs() == (fDSP->getNumOutputs()));
        }
    
        ~Faustmydsp()
        {
            delete fDSP;
        }
    
        void setParameter(AUParameterAddress address, float value, bool immediate) override
        {
             if (address < fZones.size()) {
                *fZones[address] = value;
             }
        }
    
        void init(int channelCount, double sampleRate) override
        {
            fDSP->init(int(sampleRate));
        }
    
        void reset() override
        {
            fDSP->instanceResetUserInterface();
            fDSP->instanceClear();
        }
    
    #ifdef MIDICTRL
        void handleMIDIEvent(AUMIDIEvent const& ev) override
        {
            if (ev.length == 1) {
                fMidiHandler.handleData1(ev.eventSampleTime, ev.eventType, ev.data[0]);
            } else if (ev.length == 2) {
                fMidiHandler.handleData2(ev.eventSampleTime, ev.eventType, ev.data[0], ev.data[1]);
            }
        }
    #endif
    
        void startRamp(const AUParameterEvent &event) override
        {
            auto address = event.parameterAddress;
            if (address < fZones.size()) {
                *fZones[address] = event.value;
            }
        }
    
        // Need to override this since it's pure virtual.
        void process(AUAudioFrameCount frameCount, AUAudioFrameCount bufferOffset) override
        {
            float* inputs[inputChannelCount];
            float* outputs[outputChannelCount];

            for (int channel = 0; channel < inputChannelCount; ++channel) {
                inputs[channel] = (float*)inputBufferLists[0]->mBuffers[channel].mData + bufferOffset;
            }
            for (int channel = 0; channel < outputChannelCount; ++channel) {
                outputs[channel] = (float*)outputBufferList->mBuffers[channel].mData + bufferOffset;
            }
            fDSP->compute(int(frameCount), inputs, outputs);
        }
    
};

// Register AK class and parameters

enum mydspParameter : AUParameterAddress {
#define ACTIVE_ENUM_MEMBER(type, ident, name, var, def, min, max, step) \
mydsp_##ident,
    FAUST_LIST_ACTIVES(ACTIVE_ENUM_MEMBER)
    kNumActives,
};

AK_REGISTER_DSP(Faustmydsp)

#define REGISTER_PARAMETER(type, ident, name, var, def, min, max, step) \
    AK_REGISTER_PARAMETER(mydsp_##ident)
FAUST_LIST_ACTIVES(REGISTER_PARAMETER);

/********************END ARCHITECTURE SECTION (part 2/2)****************/
