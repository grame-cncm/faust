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
#include "faust/gui/PathBuilder.h"
#include "faust/gui/FUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/QTUI.h"
#include "faust/misc.h"
#include "faust/audio/rtaudio-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

// Always include this file, otherwise -nvoices only mode does not compile...
#include "faust/midi/rt-midi.h"
#include "faust/gui/MidiUI.h"

#ifdef MIDICTRL
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

#ifdef POLY
#include "faust/dsp/poly-dsp.h"
#endif

dsp* DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/******************************************************************************
 *******************************************************************************
 
 MAIN PLAY THREAD
 
 *******************************************************************************
 *******************************************************************************/

static bool hasMIDISync()
{
    JSONUI jsonui;
    mydsp* tmp_dsp = new mydsp();
    tmp_dsp->buildUserInterface(&jsonui);
    std::string json = jsonui.JSON();
    delete tmp_dsp;
    
    return ((json.find("midi") != std::string::npos) &&
            ((json.find("start") != std::string::npos) ||
             (json.find("stop") != std::string::npos) ||
             (json.find("clock") != std::string::npos)));
}

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, basename(argv[0]));
    
    if (isopt(argv, "-h")) {
        std::cout << "prog [--frequency <val>] [--buffer <val>] [--poly] [--group <0/1>] [--virtual-midi <0/1>]\n";
        exit(1);
    }
    
    long srate = (long)lopt(argv, "--frequency", 44100);
    int fpb = lopt(argv, "--buffer", 512);
    bool is_virtual = lopt(argv, "--virtual-midi", false);
    
#ifdef POLY
    int poly = lopt(argv, "--poly", 4);
    int group = lopt(argv, "--group", 1);
    
#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(new mydsp_poly(new mydsp(), poly, true, group));
    } else {
        DSP = new mydsp_poly(new mydsp(), poly, true, group);
    }
#else
    DSP = new mydsp_poly(new mydsp(), poly, false, group);
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
        std::cerr << "Unable to allocate Faust DSP object" << std::endl;
        exit(1);
    }
    
    QApplication myApp(argc, argv);
    
    QTGUI interface;
    FUI finterface;
    DSP->buildUserInterface(&interface);
    DSP->buildUserInterface(&finterface);
    
#ifdef MIDICTRL
    rt_midi midi_handler(name, is_virtual);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    std::cout << "MIDI is on" << std::endl;
#endif
    
#ifdef HTTPCTRL
    httpdUI httpdinterface(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    std::cout << "HTTPD is on" << std::endl;
#endif
    
#ifdef OSCCTRL
    OSCUI oscinterface(name, argc, argv);
    DSP->buildUserInterface(&oscinterface);
    std::cout << "OSC is on" << std::endl;
#endif
    
    rtaudio audio(srate, fpb);
    audio.init(name, DSP);
    audio.start();
    
    std::cout << "ins " << audio.getNumInputs() << std::endl;
    std::cout << "outs " << audio.getNumOutputs() << std::endl;
    
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
    midiinterface.stop();
#endif
    
    audio.stop();
    finterface.saveState(rcfilename);
    
    return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
