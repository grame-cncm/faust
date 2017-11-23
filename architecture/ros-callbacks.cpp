/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2014-2015 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "faust/misc.h"
#include "faust/gui/RosCI.h"
#include "faust/dsp/dsp.h"

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

/************************************************************************
*************************************************************************
			
							BE CAREFUL :
			
	This architecture file cannot be used to deal with any stream.
	It has been written to be used before an over architecture file :
		- jack-ros.cpp
		- jack-gtk-ros.cpp
		
	It has been written for faust2appls tools like faust2ros or 
	faust2rosgtk
	
*************************************************************************
*************************************************************************/
				
mydsp*	DSP;

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    char appname[256];
	
	snprintf(appname, 255, "%s", basename(argv[0]));
    
	// Create DSP Object
	DSP = new mydsp();
	if (DSP==0) {
        std::cout<<"Unable to allocate Faust DSP object" <<std::endl;
		exit(1);
	}
	
	// Create and build ROS Callbacks Interface
	RosCI* interface = new RosCI();
	DSP->buildUserInterface(interface);
	
	// Gets the number of ROS metadata declared
	int count = interface->getParamsCount();
	
	// Gets the callbacks parameters
	std::vector<RosCI::CallbackParams> parameters = interface->getCallbacksParameters();
	
	std::string name = static_cast<std::string>(appname);
	// Writes the rosCallbacks.h file
	interface->callbacksWriter(count, parameters, name);

	// desallocation
	delete interface;

	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

