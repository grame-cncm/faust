/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
#include "faust/gui/faustqt.h"
#include "faust/gui/OSCUI.h"
#include "faust/misc.h"
#include "faust/audio/osc-dsp.h"

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/
<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/******************************************************************************
*******************************************************************************

                                MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
int main(int argc, char *argv[])
{
	char name[256], dst[258];
	char rcfilename[256];

	char* home = getenv("HOME");
	snprintf(name, 255, "%s", basename(argv[0]));
	snprintf(dst, 257, "/%s/", name);
	snprintf(rcfilename, 255, "%s/.%src", home, name);

    QApplication myApp(argc, argv);
    
	QTGUI* interface = new QTGUI();
	FUI* finterface = new FUI();
	DSP.buildUserInterface(interface);
	DSP.buildUserInterface(finterface);

	oscdsp osca (dst, argc, argv);
	OSCUI*	oscinterface = new OSCUI(name, argc, argv, &osca);
	DSP.buildUserInterface(oscinterface);
	
	snprintf(dst, 257, "/%s/", oscinterface->getRootName());
	osca.setDest (dst);
	
	osca.init (name, &DSP);	
	finterface->recallState(rcfilename);
	osca.start ();	
	
	oscinterface->run();
	interface->run();	
    
    myApp.setStyleSheet(interface->styleSheet());
    myApp.exec();
    interface->stop();
    
	osca.stop();
	finterface->saveState(rcfilename);
    
	// desallocation
    delete interface;
    delete finterface;
	delete oscinterface;
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
					

