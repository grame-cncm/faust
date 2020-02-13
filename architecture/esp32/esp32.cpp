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

// MIDI support
#if MIDICTRL
#include "faust/gui/MidiUI.h"
#include "faust/midi/esp32-midi.h"
#endif

// for polyphonic synths
#ifdef NVOICES
#include "faust/dsp/poly-dsp.h"
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

// After generated C++ class to that FAUST_INPUTS and FAUST_OUTPUTS are defined
#include "faust/audio/esp32-dsp.h"

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

AudioFaust::AudioFaust(int sample_rate, int buffer_size)
{
    fUI = new MapUI();
    fAudio = new esp32audio(sample_rate, buffer_size);
#ifdef NVOICES
    int nvoices = NVOICES;
    dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, true);
    dsp_poly->buildUserInterface(fUI);
    fAudio->init("esp32", dsp_poly);
#else
    fDSP = new mydsp();
    fDSP->buildUserInterface(fUI);
    fAudio->init("esp32", fDSP);
#endif
#if MIDICTRL
    fMIDIHandler = new esp32_midi();
#ifdef NVOICES
    fMIDIHandler->addMidiIn(dsp_poly);
#endif
    fMIDIInterface = new MidiUI(fMIDIHandler);
#ifdef NVOICES
    dsp_poly->buildUserInterface(fMIDIInterface);
#else
    fDSP->buildUserInterface(fMIDIInterface);
#endif
#endif
}

AudioFaust::~AudioFaust()
{
#ifdef NVOICES
    delete dsp_poly;
#else
    delete fDSP;
#endif

    delete fUI;
    delete fAudio;
    
#if MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

bool AudioFaust::start()
{
#if MIDICTRL
    if (!fMIDIInterface->run()) return false;
#endif
    return fAudio->start();
}

void AudioFaust::stop()
{
#if MIDICTRL
    fMIDIInterface->stop();
#endif
    fAudio->stop();
}

void AudioFaust::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
