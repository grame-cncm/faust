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

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/HothouseControlUI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#include "faust/gui/MidiUI.h"
#endif

using namespace daisysp;
using namespace std;
using clevelandmusicco::Hothouse;

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

static Hothouse hw;
Led led1;
Led led2;

bool led1IsOn = false;
bool led2IsOn = false;

static HothouseControlUI* control_UI = nullptr;
static dsp* DSP = nullptr;

#ifdef MIDICTRL
list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

static void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t count)
{
    hw.ProcessAllControls();

    // todo: this only makes sense if the footswtiches are checkboxes.
    led1IsOn ^= hw.switches[Hothouse::Switches::FOOTSWITCH_1].RisingEdge();
    led2IsOn ^= hw.switches[Hothouse::Switches::FOOTSWITCH_2].RisingEdge();

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
    bool midi = false;
    DSP = new mydsp();
    MidiMeta::analyse(DSP, midi, midi_sync, nvoices);
    DSP = new mydsp_poly(DSP, nvoices, true, true);
#else
    DSP = new mydsp();
#endif
    
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);
    hw.SetAudioSampleRate(MY_SAMPLE_RATE);
    float sample_rate = hw.AudioSampleRate();
    
    // init Faust DSP
    DSP->init(int(sample_rate));
    
    // initialize UI
    control_UI = new HothouseControlUI(&hw);
    DSP->buildUserInterface(control_UI);

    // The right footswitch LED
    led1.Init(hw.seed.GetPin(Hothouse::Led::LED_1), led1IsOn);
    led2.Init(hw.seed.GetPin(Hothouse::Led::LED_2), led2IsOn);

    hw.StartAdc();
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
        hw.DelayMs(6);
        led1.Set(led1IsOn ? 1.0f : 0.0f);
        led2.Set(led2IsOn ? 1.0f : 0.0f);
        led1.Update();
        led2.Update();
        hw.CheckResetToBootloader();
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
