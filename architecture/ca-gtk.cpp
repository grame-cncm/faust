/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN ca-gtk.cpp ****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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
#include <string>
#include <list>

#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/PresetUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/misc.h"
#include "faust/audio/coreaudio-dsp.h"
#ifdef FIXED_POINT
#include "faust/dsp/fixed-point.h"
#endif

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#include "faust/dsp/dsp-tools.h"
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

using namespace std;

dsp* DSP;

list<GUI*> GUI::fGuiList;
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
    bool midi = false;
    int nvoices = 0;
    bool control = true;
    
    if (isopt(argv, "-help") || isopt(argv, "-h")) {
        cout << argv[0] << " [--sample-rate <val>] [--buffer <val>] [--nvoices <val>] [--control <0/1>] [--group <0/1>] [--virtual-midi <0/1>]\n";
        exit(1);
    }
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi, midi_sync, nvoices);
    delete tmp_dsp;
    
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
    
    long srate = (long)lopt(argv, "--sample-rate", -1);
    int fpb = lopt(argv, "--buffer", 512);
    bool is_virtual = lopt(argv, "--virtual-midi", false);
    
#ifdef POLY2
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    cout << "Started with " << nvoices << " voices\n";
    DSP = new mydsp_poly(new mydsp(), nvoices, control, group);
    
#if MIDICTRL
    if (midi_sync) {
        DSP = new timed_dsp(new dsp_sequencer(DSP, new effect()));
    } else {
        DSP = new dsp_sequencer(DSP, new effect());
    }
#else
    DSP = new dsp_sequencer(DSP, new effect());
#endif
    
#else
    nvoices = lopt(argv, "--nvoices", nvoices);
    control = lopt(argv, "--control", control);
    int group = lopt(argv, "--group", 1);
    
    if (nvoices > 0) {
        cout << "Started with " << nvoices << " voices\n";
        DSP = new mydsp_poly(new mydsp(), nvoices, control, group);
        
#if MIDICTRL
        if (midi_sync) {
            DSP = new timed_dsp(DSP);
        }
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
        cerr << "Unable to allocate Faust DSP object" << endl;
        exit(1);
    }
    
    GTKUI* interface = new GTKUI(name, &argc, &argv);
    FUI finterface;
    
#ifdef PRESETUI
    string preset_dir = PresetUI::getPresetDir();
    cout << "Final preset_dir: " << preset_dir << endl;
    PresetUI::tryCreateDirectory(preset_dir);
    PresetUI pinterface(interface, preset_dir + "/" + ((nvoices > 0) ? "poly_" : ""));
    DSP->buildUserInterface(&pinterface);
#else
    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(&finterface);
#endif
    
#ifdef MIDICTRL
    rt_midi midi_handler(name, is_virtual);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    cout << "MIDI is on" << endl;
#endif
    
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    cout << "HTTPD is on" << endl;
#endif
    
#ifdef SOUNDFILE
    {
        // Init default DSP to get the SR
        coreaudio audio(srate, fpb);
        default_dsp def_dsp;
        if (!audio.init(name, &def_dsp)) {
            cerr << "Unable to init audio" << endl;
            exit(1);
        }
        // After audio init to get SR
        srate = audio.getSampleRate();
    }
    SoundUI soundinterface("", srate);
    DSP->buildUserInterface(&soundinterface);
#endif
    
    coreaudio audio(srate, fpb);
    if (!audio.init(name, DSP)) {
        cerr << "Unable to init audio" << endl;
        exit(1);
    }
   
#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    cout << "OSC is on" << endl;
#endif
    
    if (!audio.start()) {
        cerr << "Unable to start audio" << endl;
        exit(1);
    }
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
#ifdef HTTPCTRL
    httpdinterface.run();
#ifdef QRCODECTRL
    interface->displayQRCode(httpdinterface.getTCPPort());
#endif
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
    
#ifdef MIDICTRL
    if (!midiinterface.run()) {
        cerr << "MidiUI run error " << endl;
    }
#endif
    
    // After the allocation of controllers
    finterface.recallState(rcfilename);
    
    interface->run();
    
#ifdef MIDICTRL
    midiinterface.stop();
#endif
    interface->stop();
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    delete DSP;
    return 0;
}

/******************** END bench.cpp ****************/

