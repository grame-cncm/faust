/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <list>

#include "faust/dsp/timed-dsp.h"
#include "faust/gui/PathBuilder.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/SoundUI.h"
#include "faust/audio/dummy-audio.h"
#include "faust/misc.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

// Always include this file, otherwise -poly only mode does not compile....
#include "faust/gui/MidiUI.h"

#ifdef MIDICTRL
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

<<includeclass>>

using namespace std;

#include "faust/dsp/poly-dsp.h"

#ifdef POLY2
#include "faust/dsp/dsp-combiner.h"
#include "effect.cpp"
#endif

dsp* DSP;

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
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
    int nvoices = 0;
    mydsp_poly* dsp_poly = NULL;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(rcfilename, 255, "%s/.%src", home, name);
    
    if (isopt(argv, "-h")) {
        std::cout << "prog [--frequency <val>] [--buffer <val>] [--nvoices <val>] [--group <0/1>]\n";
        exit(1);
    }
    
#ifdef POLY2
    nvoices = lopt(argv, "--nvoices", nvoices);
    int group = lopt(argv, "--group", 1);
    cout << "Started with " << nvoices << " voices\n";
    dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
    
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
    int group = lopt(argv, "--group", 1);
    
    if (nvoices > 0) {
        cout << "Started with " << nvoices << " voices\n";
        dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
        
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
    
    if (DSP == 0) {
        cerr << "Unable to allocate Faust DSP object" << endl;
        exit(1);
    }
    
    FUI finterface;
    DSP->buildUserInterface(&finterface);
    
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    cout << "HTTPD is on" << endl;
#endif
    
#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    cout << "OSC is on" << endl;
#endif
    
    dummyaudio audio(44100, 128, 5, 128);
    audio.init(name, DSP);
    
#ifdef MIDICTRL
    rt_midi midi_handler(name);
    midi_handler.addMidiIn(dsp_poly);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
#endif
    
    finterface.recallState(rcfilename);
    
    if (dsp_poly) {
        cout << "keyOn 60 67 72 75" << endl;
        dsp_poly->keyOn(0, 60, 127);
        dsp_poly->keyOn(0, 67, 127);
        dsp_poly->keyOn(0, 72, 127);
        dsp_poly->keyOn(0, 75, 127);
    }
    
    // Play notes once
    audio.start();
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
    if (dsp_poly) {
        cout << "allNotesOff" << endl;
        dsp_poly->allNotesOff(true);
    }
    
    // Rendering in now finished...
    
    if (dsp_poly) {
        cout << "keyOn 60 67 72 75" << endl;
        dsp_poly->keyOn(0, 60, 127);
        dsp_poly->keyOn(0, 67, 127);
        dsp_poly->keyOn(0, 72, 127);
        dsp_poly->keyOn(0, 75, 127);
    }
    
    // Play notes a second time
    audio.start();
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
    if (dsp_poly) {
        cout << "allNotesOff" << endl;
        dsp_poly->allNotesOff(true);
    }
    
    // Rendering in now finished...
    
    if (dsp_poly) {
        cout << "keyOn 60 67 72 75" << endl;
        dsp_poly->keyOn(0, 60, 127);
        dsp_poly->keyOn(0, 67, 127);
        dsp_poly->keyOn(0, 72, 127);
        dsp_poly->keyOn(0, 75, 127);
    }
    
    // Play notes a third time
    audio.start();
    
    cout << "ins " << audio.getNumInputs() << endl;
    cout << "outs " << audio.getNumOutputs() << endl;
    
    if (dsp_poly) {
        cout << "allNotesOff" << endl;
        dsp_poly->allNotesOff(true);
    }
    
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
    if (!midiinterface.run()) {
        cerr << "MidiUI run error\n";
    }
#endif
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    delete DSP;
    
    return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

