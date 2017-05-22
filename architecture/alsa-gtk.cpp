/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
#include "faust/gui/faustgtk.h"
#include "faust/audio/alsa-dsp.h"

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

#include "faust/dsp/poly-dsp.h"

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
dsp* DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

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

int main(int argc, char *argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    mydsp_poly* dsp_poly = NULL;

    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(rcfilename, 255, "%s/.%src", home, name);

#ifdef POLY
    int poly = lopt(argv, "--poly", 4);
    int group = lopt(argv, "--group", 1);
    dsp_poly = new mydsp_poly(new mydsp(), poly, true, group);

#if MIDICTRL
    if (hasMIDISync()) {
        DSP = new timed_dsp(dsp_poly);
    } else {
        DSP = dsp_poly;
    }
#else
    DSP = dsp_poly;
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
     
    if (DSP == 0) {
        std::cerr << "Unable to allocate Faust DSP object" << std::endl;
        exit(1);
    }

    GUI* interface = new GTKUI(name, &argc, &argv);
    FUI* finterface = new FUI();
    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(finterface);

#ifdef MIDICTRL
    rt_midi midi_handler(name);
    midi_handler.addMidiIn(dsp_poly);
    MidiUI midiinterface(&midi_handler);
    DSP->buildUserInterface(&midiinterface);
    std::cout << "MIDI is on" << std::endl;
#endif

#ifdef HTTPCTRL
    httpdUI* httpdinterface = new httpdUI(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(httpdinterface);
    std::cout << "HTTPD is on" << std::endl;
#endif

#ifdef OSCCTRL
    GUI* oscinterface = new OSCUI(name, argc, argv);
    DSP->buildUserInterface(oscinterface);
#endif

    alsaaudio audio (argc, argv, DSP);
    audio.init(name, DSP);
    finterface->recallState(rcfilename);	
    audio.start();

#ifdef HTTPCTRL
    httpdinterface->run();
#endif

#ifdef OSCCTRL
    oscinterface->run();
#endif
#ifdef MIDICTRL
    if (!midiinterface.run()) {
        std::cerr << "MidiUI run error\n";
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

/********************END ARCHITECTURE SECTION (part 2/2)****************/

