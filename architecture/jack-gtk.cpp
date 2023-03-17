/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN jack-gtk.cpp ****************/
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
#include "faust/dsp/one-sample-dsp.h"
#include "faust/gui/FUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/PresetUI.h"
#include "faust/audio/jack-dsp.h"
#ifdef FIXED_POINT
#include "faust/dsp/fixed-point.h"
#endif

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

#ifdef OCVCTRL
#include "faust/gui/OCVUI.h"
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

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    bool midi_sync = false;
    int nvoices = 0;
    bool control = true;
    
    if (isopt(argv, "-h")) {
        cout << argv[0] << " [--nvoices <val>] [--control <0/1>] [--group <0/1>]\n";
        exit(1);
    }
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
    
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
    PresetUI pinterface(interface, string(PRESETDIR) + string(name) + ((nvoices > 0) ? "_poly" : ""));
    DSP->buildUserInterface(&pinterface);
#else
    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(&finterface);
#endif
    
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    cout << "HTTPD is on" << endl;
#endif
    
#ifdef OCVCTRL
    OCVUI ocvinterface;
    DSP->buildUserInterface(&ocvinterface);
    cout << "OCVCTRL defined" << endl;
#endif
    
#ifdef MIDICTRL
    jackaudio_midi audio;
#else
    jackaudio audio;
#endif
    if (!audio.init(name, DSP)) {
        cerr << "Unable to init audio" << endl;
        exit(1);
    }
    
// After audio init to get SR
#if SOUNDFILE
    SoundUI soundinterface("", audio.getSampleRate());
    DSP->buildUserInterface(&soundinterface);
#endif

#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    cout << "OSC is on" << endl;
    audio.addControlCallback(osc_compute_callback, &oscinterface);
#endif
    
#ifdef MIDICTRL
    MidiUI* midiinterface = new MidiUI(&audio);
    cout << "JACK MIDI is used" << endl;
    DSP->buildUserInterface(midiinterface);
    cout << "MIDI is on" << endl;
#endif
    
    if (!audio.start()) {
        cerr << "Unable to start audio" << endl;
        exit(1);
    }
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
#ifdef HTTPCTRL
    httpdinterface.run();
#endif
    
#ifdef OCVCTRL
    ocvinterface.run();
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
    
#ifdef MIDICTRL
    if (!midiinterface->run()) {
        cerr << "MidiUI run error " << endl;
    }
#endif
    
    // After the allocation of controllers
    finterface.recallState(rcfilename);
 
    interface->run();
  
#ifdef MIDICTRL
    midiinterface->stop();
#endif
    interface->stop();
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    delete DSP;
#ifdef MIDICTRL
    delete midiinterface;
#endif
    
    return 0;
}


/******************* END jack-gtk.cpp ****************/

