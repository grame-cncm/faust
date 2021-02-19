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

// Copyright AudioKit. All Rights Reserved. Revision History at http://github.com/AudioKit/AudioKit/

#ifndef Faustmydsp_hpp
#define Faustmydsp_hpp

#import "DSPBase.h"
#import <cmath>
#import <assert.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#include "faust/gui/MidiUI.h"
#endif

#ifdef POLY
#include "faust/dsp/poly-dsp.h"
#endif

<<includeIntrinsic>>
<<includeclass>>

class Faustmydsp : public DSPBase {

    private:
        mydsp* fDSP;
    #ifdef MIDICTRL
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    #endif
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
            channelCount = std::max(fDSP->getNumInputs(), fDSP->getNumOutputs());
        #ifdef MIDICTRL
            fDSP->buildUserInterface(&fMidiUI);
        #endif
            //assert(fDSP->getNumInputs() == (fDSP->getNumOutputs()));
        }
    
        ~Faustmydsp()
        {
            delete fDSP;
        }
    
        void setParameter(AUParameterAddress address, float value, bool immediate) override
        {
            // TODO
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
            // TODO
        }
    
        // Need to override this since it's pure virtual.
        void process(AUAudioFrameCount frameCount, AUAudioFrameCount bufferOffset) override
        {
            float* inputs[channelCount];
            float* outputs[channelCount];
            for (int channel = 0; channel < channelCount; ++channel) {
                inputs[channel] = (float *)inputBufferLists[0]->mBuffers[channel].mData + frameOffset;
                outputs[channel] = (float *)outputBufferList->mBuffers[channel].mData + frameOffset;
            }
            fDSP->compute(int(frameCount), inputs, outputs);
        }
    
};

#endif /* Faustmydsp_hpp */

/********************END ARCHITECTURE SECTION (part 2/2)****************/
