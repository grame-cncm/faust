/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN alsa-gtk.cpp ****************/

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
#include "faust/gui/PathBuilder.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/misc.h"
#include "faust/gui/GTKUI.h"
#include "faust/audio/alsa-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
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

using namespace std;

dsp* DSP;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static bool hasMIDISync()
{
    JSONUI jsonui;
    mydsp* tmp_dsp = new mydsp();
    tmp_dsp->buildUserInterface(&jsonui);
    string json = jsonui.JSON();
    delete tmp_dsp;
    
    return ((json.find("midi") != string::npos) &&
            ((json.find("start") != string::npos) ||
            (json.find("stop") != string::npos) ||
            (json.find("clock") != string::npos)));
}

//-------------------------------------------------------------------------
//                                     MAIN
//-------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);

#ifdef POLY
    int poly = lopt(argv, "--poly", 4);
    int group = lopt(argv, "--group", 1);
    DSP = new mydsp_poly(new mydsp(), poly, true, group);

#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(DSP);
    }
#endif

#else

#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(new mydsp());
    } else {
        DSP = new mydsp();
    }
#else
    DSP = new mydsp();
#endif

#endif
     
    if (!DSP) {
        cerr << "Unable to allocate Faust DSP object" << endl;
        exit(1);
    }

    GUI* interface = new GTKUI(name, &argc, &argv);
    FUI* finterface = new FUI();
    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(finterface);

#ifdef MIDICTRL
    rt_midi midi_handler(name);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    cout << "MIDI is on" << endl;
#endif

#ifdef HTTPCTRL
    httpdUI* httpdinterface = new httpdUI(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(httpdinterface);
    cout << "HTTPD is on" << endl;
#endif

#ifdef OSCCTRL
    GUI* oscinterface = new OSCUI(name, argc, argv);
    DSP->buildUserInterface(oscinterface);
#endif

    alsaaudio audio(argc, argv, DSP);
    if (!audio.init(name, DSP)) {
        cerr << "Unable to init audio" << endl;
        exit(1);
    }
    
    finterface->recallState(rcfilename);
    
    if (!audio.start()) {
        cerr << "Unable to start audio" << endl;
        exit(1);
    }

#ifdef HTTPCTRL
    httpdinterface->run();
#endif

#ifdef OSCCTRL
    oscinterface->run();
#endif
#ifdef MIDICTRL
    if (!midiinterface.run()) {
        cerr << "MidiUI run error\n";
    }
#endif
    interface->run();

#ifdef MIDICTRL
    midiinterface.stop();
#endif

    audio.stop();
    finterface->saveState(rcfilename);

    // desallocation
    delete interface;
    delete finterface;
#ifdef HTTPCTRL
    delete httpdinterface;
#endif
#ifdef OSCCTRL
    delete oscinterface;
#endif

    return 0;
}

/******************** END alsa-gtk.cpp ****************/

