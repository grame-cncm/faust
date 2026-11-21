/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public License
 as published by the Free Software Foundation; either version 2.1 of
 the License, or (at your option) any later version.
 
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

#include <string.h> // for memset

#include "teensy.h"

// IMPORTANT: in order for MapUI to work, the teensy linker must be g++
#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

// MIDI support
#if MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/midi/teensy-midi.h"
#endif

// for polyphonic synths (poly-dsp.h needs RTTI, Teensy builds have none)
#ifdef NVOICES
#include "faust/dsp/mcu-poly-dsp.h"
#endif

// -mem: the program's memory in the fastest place it fits (DTCM, RAM2, PSRAM)
#ifdef FAUST_TEENSY_MEM
#include "faust/dsp/teensy-memory.h"
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

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#define MULT_16 32767
#define DIV_16 0.0000305185

// Not needed
// unsigned __exidx_start;
// unsigned __exidx_end;

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

// the DSP (or a voice): through the memory manager with -mem
#ifdef FAUST_TEENSY_MEM
static dsp* newVoice() { return mydsp::create(); }
static void deleteVoice(dsp* d) { mydsp::destroy(d); }
#else
static dsp* newVoice() { return new mydsp(); }
static void deleteVoice(dsp* d) { delete d; }
#endif

AudioFaust::AudioFaust() : AudioStream(FAUST_INPUTS, new audio_block_t*[FAUST_INPUTS])
{
#ifdef FAUST_TEENSY_MEM
    // allocated through the tiers (DTCM, RAM2, PSRAM)
    mydsp::fManager = &teensy_memory::manager();
#endif
    // init() = classInit() + instanceInit(); with -mem init() does nothing
    mydsp::classInit(AUDIO_SAMPLE_RATE_EXACT);
#ifdef NVOICES
    dsp* voices[NVOICES];
    for (int i = 0; i < NVOICES; i++) {
        voices[i] = newVoice();
    }
    fPoly = new mcu_dsp_poly(voices, NVOICES, deleteVoice, nullptr, nullptr, AUDIO_BLOCK_SAMPLES);
    fDSP = fPoly;
#else
    fDSP = newVoice();
#endif
    fDSP->instanceInit(AUDIO_SAMPLE_RATE_EXACT);
    
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    // allocating Faust inputs
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fInChannel = NULL;
    }
    
    // allocating Faust outputs
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fOutChannel = NULL;
    }
    
#if MIDICTRL
    // started on the first update(), see startMidi()
    fMIDIHandler = nullptr;
    fMIDIInterface = nullptr;
#endif
}

#if MIDICTRL
// The object is usually a global of the sketch, so its constructor runs
// during static initialization, possibly before the GUI lists above are
// constructed (the order across files is undefined): a MidiUI made there
// registered in an unconstructed list and crashed before setup(). The
// first update() runs after all of that.
void AudioFaust::startMidi()
{
    fMIDIHandler = new teensy_midi();
    fMIDIInterface = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIInterface);
#ifdef NVOICES
    fPoly->setMidiHandler(fMIDIHandler);  // notes to the voices (Teensy builds have no RTTI)
#endif
    fMIDIInterface->run();
}
#endif

AudioFaust::~AudioFaust()
{
    int inputs = fDSP->getNumInputs();
    int outputs = fDSP->getNumOutputs();
#ifdef NVOICES
    delete fPoly;  // destroys the voices
#else
    deleteVoice(fDSP);
#endif
#ifdef FAUST_TEENSY_MEM
    teensy_memory::reset();  // the DTCM arena is freed as a whole
#endif
    delete fUI;
    for (int i = 0; i < inputs; i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    for (int i = 0; i < outputs; i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
#if MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

template <int INPUTS, int OUTPUTS>
void AudioFaust::updateImp(void)
{
#if MIDICTRL
    if (!fMIDIInterface) {
        startMidi();
    }
    // Process the MIDI messages received by the Teensy
    fMIDIHandler->processMidi();
    // Synchronize all GUI controllers
    GUI::updateAllGuis();
#endif
    
    if (INPUTS > 0) {
        audio_block_t* inBlock[INPUTS];
        for (int channel = 0; channel < INPUTS; channel++) {
            inBlock[channel] = receiveReadOnly(channel);
            if (inBlock[channel]) {
                for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                    int16_t val = inBlock[channel]->data[i];
                    fInChannel[channel][i] = val*DIV_16;
                }
                release(inBlock[channel]);
            } else {
                memset(fInChannel[channel], 0, AUDIO_BLOCK_SAMPLES * sizeof(float));
            }
        }
    }
    
    fDSP->compute(AUDIO_BLOCK_SAMPLES, fInChannel, fOutChannel);
    
    audio_block_t* outBlock[OUTPUTS];
    for (int channel = 0; channel < OUTPUTS; channel++) {
        outBlock[channel] = allocate();
        if (outBlock[channel]) {
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                int16_t val = fOutChannel[channel][i]*MULT_16;
                outBlock[channel]->data[i] = val;
            }
            transmit(outBlock[channel], channel);
            release(outBlock[channel]);
        }
    }
}

void AudioFaust::update(void) { updateImp<FAUST_INPUTS, FAUST_OUTPUTS>(); }

void AudioFaust::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

float AudioFaust::getParamValue(const std::string& path)
{
    return fUI->getParamValue(path);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
