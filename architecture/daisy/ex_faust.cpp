/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020-2021 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/

#include "daisysp.h"

#ifdef PATCH
#include "daisy_patch.h"
#elif defined POD
#include "daisy_pod.h"
#elif defined PATCHSM
#include "daisy_patch_sm.h"
#else
#include "daisy_seed.h"
#endif

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#if defined PATCHSM
#include "faust/gui/DaisyPatchInitControlUI.h"
#else
#include "faust/gui/DaisyControlUI.h"
#endif
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#include "faust/gui/MidiUI.h"
#endif

using namespace daisysp;
using namespace std;

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

#ifdef POLY
#include "faust/dsp/poly-dsp.h"
#endif

#ifdef PATCH
static daisy::DaisyPatch hw;
#elif defined POD
static daisy::DaisyPod hw; 
#elif defined PATCHSM
static daisy::patch_sm::DaisyPatchSM hw; 
#else
static daisy::DaisySeed hw;
#endif

#if defined PATCHSM
static DaisyPatchInitControlUI* control_UI = nullptr;
#else
static DaisyControlUI* control_UI = nullptr;
#endif
static dsp* DSP = nullptr;

#ifdef MIDICTRL
list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

static void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t count)
{
    // Update controllers
    control_UI->update();
    
    // DSP processing
    DSP->compute(count, const_cast<float**>(in), out);
}

int main(void)
{
    // initialize seed hardware and daisysp modules
    hw.Init();
    
    // allocate DSP
#ifdef POLY
    int nvoices = 0;
    bool midi_sync = false;
    DSP = new mydsp();
    MidiMeta::analyse(DSP, midi_sync, nvoices);
    DSP = new mydsp_poly(DSP, nvoices, true, true);
#else
    DSP = new mydsp();
#endif
    
    // set buffer-size
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);
    
    // init Faust DSP
    DSP->init(MY_SAMPLE_RATE);
    
    // setup controllers
#if (defined PATCH) || (defined POD)
    control_UI = new DaisyControlUI(&hw.seed, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
    hw.StartAdc();
#elif defined (PATCHSM)
    control_UI = new DaisyPatchInitControlUI(&hw, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
    hw.StartAdc();
#else
    //initialize UI for seed
    control_UI = new DaisyControlUI(&hw, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
    // start ADC
    hw.adc.Start();
#endif
    // define and start callback
    hw.StartAudio(AudioCallback);
#ifdef MIDICTRL
    daisy_midi midi_handler;
    MidiUI midi_interface(&midi_handler);
    DSP->buildUserInterface(&midi_interface);
    midi_handler.startMidi();
#endif
    
    // MIDI handling loop
    while(1) {
    #ifdef MIDICTRL
        midi_handler.processMidi();
    #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
