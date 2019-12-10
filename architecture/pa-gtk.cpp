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
#include <iostream>

#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/audio/portaudio-dsp.h"
#include "faust/gui/GTKUI.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
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

mydsp DSP;
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	char appname[256];
	char rcfilename[256];
	char* home = getenv("HOME");

	snprintf(appname, 256, "%s", basename(argv[0]));
	snprintf(rcfilename, 256, "%s/.%src", home, appname);

	GUI* interface = new GTKUI (appname, &argc, &argv);
	FUI* finterface	= new FUI();
	DSP.buildUserInterface(interface);
	DSP.buildUserInterface(finterface);

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(appname, argc, argv);
	DSP.buildUserInterface(oscinterface);
#endif

    long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 128);

	portaudio audio (srate, fpb);
	audio.init(appname, &DSP);
	finterface->recallState(rcfilename);
	audio.start();

#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();

	audio.stop();
	finterface->saveState(rcfilename);
    
   // desallocation
    delete interface;
    delete finterface;
#ifdef OSCCTRL
	 delete oscinterface;
#endif

  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

