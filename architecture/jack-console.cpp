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
#include <math.h>
#include <iostream>
#include <vector>

#include "faust/gui/console.h"
#include "faust/misc.h"
#include "faust/audio/jack-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif


using namespace std;


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

								USER INTERFACE

*******************************************************************************
/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp		DSP;
list<GUI*>	GUI::fGuiList;
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[] )
{
	char	jackname[256];
	snprintf(jackname, 255, "%s", basename(argv[0]));

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);

#ifdef OSCCTRL
	GUI*	oscinterface = new OSCUI(jackname, argc, argv);
	DSP.buildUserInterface(oscinterface);
#endif

#ifdef HTTPCTRL
	httpdUI*	httpdinterface = new httpdUI(jackname, argc, argv);
	DSP.buildUserInterface(httpdinterface);
#endif

	jackaudio audio;
	audio.init(jackname, &DSP);
	interface->process_command();
	audio.start();

#ifdef HTTPCTRL
	httpdinterface->run();
#endif	
	
#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();
	
	audio.stop();
	return 0;
} 


		
/********************END ARCHITECTURE SECTION (part 2/2)****************/

