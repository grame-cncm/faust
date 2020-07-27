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

#include "esp32.h"

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/esp32-dsp.h"

// MIDI support
#ifdef MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/midi/esp32-midi.h"
#endif

// for polyphonic synths
#ifdef NVOICES
#include "faust/dsp/poly-dsp.h"
#endif

#ifdef HAS_MAIN
#include "WM8978.h"
#endif

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

#ifdef MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

AudioFaust::AudioFaust(int sample_rate, int buffer_size)
{
#ifdef NVOICES
    int nvoices = NVOICES;
    mydsp_poly* dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, true);
    fDSP = dsp_poly;
#else
    fDSP = new mydsp();
#endif
    
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    fAudio = new esp32audio(sample_rate, buffer_size);
    fAudio->init("esp32", fDSP);
    
#ifdef MIDICTRL
    fMIDIHandler = new esp32_midi();
#ifdef NVOICES
    fMIDIHandler->addMidiIn(dsp_poly);
#endif
    fMIDIInterface = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIInterface);
#endif
}

AudioFaust::~AudioFaust()
{
    delete fDSP;
    delete fUI;
    delete fAudio;
#ifdef MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

bool AudioFaust::start()
{
#ifdef MIDICTRL
    if (!fMIDIInterface->run()) return false;
#endif
    return fAudio->start();
}

void AudioFaust::stop()
{
#ifdef MIDICTRL
    fMIDIInterface->stop();
#endif
    fAudio->stop();
}

void AudioFaust::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

float AudioFaust::getParamValue(const std::string& path)
{
    return fUI->getParamValue(path);
}

// Entry point
#ifdef HAS_MAIN
extern "C" void app_main()
{
    // Init audio codec
    WM8978 wm8978;
    wm8978.init();
    wm8978.addaCfg(1,1);
    wm8978.inputCfg(1,0,0);
    wm8978.outputCfg(1,0);
    wm8978.micGain(30);
    wm8978.auxGain(0);
    wm8978.lineinGain(0);

    // Set gain
    wm8978.spkVolSet(60); // [0-63]
    
    wm8978.hpVolSet(40,40);
    wm8978.i2sCfg(2,0);
    
    // Allocate and start Faust DSP
    AudioFaust* DSP = new AudioFaust(48000, 32);
    DSP->start();
    
    // Waiting forever
    vTaskSuspend(nullptr);
}
#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/
