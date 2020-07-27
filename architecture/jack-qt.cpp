/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <list>

#include "faust/dsp/timed-dsp.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/misc.h"
#include "faust/gui/QTUI.h"
#include "faust/audio/jack-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
static void osc_compute_callback(void* arg)
{
    static_cast<OSCUI*>(arg)->endBundle();
}
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

// Always include this file, otherwise -nvoices only mode does not compile....
#include "faust/gui/MidiUI.h"

#ifdef MIDICTRL
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
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

#include "faust/dsp/poly-dsp.h"

#ifdef POLY2
#include "faust/dsp/dsp-combiner.h"
#include "effect.h"
#endif

dsp* DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/******************************************************************************
 *******************************************************************************
 
 MAIN PLAY THREAD
 
 *******************************************************************************
 *******************************************************************************/

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    bool midi_sync = false;
    int nvoices = 0;
    bool control = true;
    mydsp_poly* dsp_poly = NULL;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
    
    if (isopt(argv, "-h")) {
        std::cout << "prog [--nvoices <val>] [--control <0/1>] [--group <0/1>]\n";
        exit(1);
    }
    
#ifdef POLY2
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    std::cout << "Started with " << nvoices << " voices\n";
    dsp_poly = new mydsp_poly(new mydsp(), nvoices, control, group);
    
#if MIDICTRL
    if (midi_sync) {
        DSP = new timed_dsp(new dsp_sequencer(dsp_poly, new effect()));
    } else {
        DSP = new dsp_sequencer(dsp_poly, new effect());
    }
#else
    DSP = new dsp_sequencer(dsp_poly, new effect());
#endif
    
#else
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    if (nvoices > 0) {
        std::cout << "Started with " << nvoices << " voices\n";
        dsp_poly = new mydsp_poly(new mydsp(), nvoices, control, group);
        
#if MIDICTRL
        if (midi_sync) {
            DSP = new timed_dsp(dsp_poly);
        } else {
            DSP = dsp_poly;
        }
#else
        DSP = dsp_poly;
#endif
    } else {
#if MIDICTRL
        if (midi_sync) {
            DSP = new timed_dsp(new mydsp());
        } else {
            DSP = new mydsp();
        }
#else
        DSP = new mydsp();
#endif
    }
#endif
    
    if (!DSP) {
        std::cerr << "Unable to allocate Faust DSP object" << std::endl;
        exit(1);
    }
    
    QApplication myApp(argc, argv);
    
    QTGUI interface;
    FUI finterface;
    DSP->buildUserInterface(&interface);
    DSP->buildUserInterface(&finterface);
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    std::cout << "HTTPD is on" << std::endl;
#endif
    
#ifdef MIDICTRL
    jackaudio_midi audio;
    audio.init(name, DSP);
#else
    jackaudio audio;
    audio.init(name, DSP);
#endif
    
// After audio init to get SR
#ifdef SOUNDFILE
    // Use bundle path
    SoundUI soundinterface(SoundUI::getBinaryPath() + "/Contents/Resources/", audio.getSampleRate());
    // SoundUI has to be dispatched on all internal voices
    if (dsp_poly) dsp_poly->setGroup(false);
    DSP->buildUserInterface(&soundinterface);
    if (dsp_poly) dsp_poly->setGroup(group);
#endif
    
#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    std::cout << "OSC is on" << std::endl;
    audio.addControlCallback(osc_compute_callback, &oscinterface);
#endif
    
#ifdef MIDICTRL
    bool rtmidi = isopt(argv, "--rtmidi");
    
    MidiUI* midiinterface;
    if (rtmidi) {
        rt_midi midi_handler(name);
        midi_handler.addMidiIn(dsp_poly);
        midiinterface = new MidiUI(&midi_handler);
        printf("RtMidi is used\n");
    } else {
        midiinterface = new MidiUI(&audio);
        audio.addMidiIn(dsp_poly);
        printf("JACK MIDI is used\n");
    }
    
    DSP->buildUserInterface(midiinterface);
    std::cout << "MIDI is on" << std::endl;
#endif
    
    audio.start();
    
    printf("ins %d\n", audio.getNumInputs());
    printf("outs %d\n", audio.getNumOutputs());
    
#ifdef HTTPCTRL
    httpdinterface.run();
#ifdef QRCODECTRL
    interface.displayQRCode(httpdinterface.getTCPPort());
#endif
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
#ifdef MIDICTRL
    if (!midiinterface->run()) {
        std::cerr << "MidiUI run error\n";
    }
#endif
    
    // After the allocation of controllers
    finterface.recallState(rcfilename);
    interface.run();
    
    myApp.setStyleSheet(interface.styleSheet());
    myApp.exec();
    interface.stop();
    
#ifdef MIDICTRL
    midiinterface->stop();
#endif
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    delete DSP;
#ifdef MIDICTRL
    delete midiinterface;
#endif
    
    return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
