/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************/

#include "teensy.h"

// IMPORTANT: in order for MapUI to work, the teensy linker must be g++
#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

// MIDI support
#if MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/gui/UI.h"
#include "faust/midi/teensy-midi.h"
extern usb_midi_class usbMIDI;
#endif

<<includeIntrinsic>>

<<includeclass>>

#define MULT_16 2147483647
#define DIV_16 4.6566129e-10

unsigned __exidx_start;
unsigned __exidx_end;

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

AudioFaust::AudioFaust() : AudioStream((fDSP = new mydsp())->getNumInputs(), new audio_block_t*[fDSP->getNumInputs()])
{
    fUI = new MapUI();
    fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
    fDSP->buildUserInterface(fUI);
    
    // allocating Faust inputs
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    }
    
    // allocating Faust outputs
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    }
    
#if MIDICTRL
    fMIDIHandler = new teensy_midi();
    fMIDIInterface = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIInterface);
    fMIDIInterface->run();
#endif
}

void AudioFaust::update(void)
{
#if MIDICTRL
    // Pass the MIDI messages received by the Teensy
    fMIDIHandler->processMidi(usbMIDI);
    // Synchronize all GUI controllers
    GUI::updateAllGuis();
#endif
    
    audio_block_t *inBlock[fDSP->getNumInputs()], *outBlock[fDSP->getNumOutputs()];
    int32_t val;
    
    if (fDSP->getNumInputs() > 0) {
        for(int channel = 0; channel < fDSP->getNumInputs(); channel++) {
            inBlock[channel] = receiveReadOnly(channel);
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                val = inBlock[channel]->data[i] << 16;
                fInChannel[channel][i] = val*DIV_16;
            }
            release(inBlock[channel]);
        }
    }
    
    fDSP->compute(AUDIO_BLOCK_SAMPLES,fInChannel,fOutChannel);
    
    for (int channel = 0; channel < fDSP->getNumOutputs(); channel++) {
        outBlock[channel] = allocate();
        if (outBlock[channel]) {
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                val = fOutChannel[channel][i]*MULT_16;
                outBlock[channel]->data[i] = val >> 16;
            }
            transmit(outBlock[channel],channel);
            release(outBlock[channel]);
        }
    }
}

AudioFaust::~AudioFaust()
{
    delete fDSP;
    delete fUI;
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
#if MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

void AudioFaust::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}
