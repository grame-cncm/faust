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

#include "faust/misc.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/RosUI.h"

#include <ros/ros.h>

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

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
        ROS_ERROR("Unable to allocate Faust DSP object" );
		exit(1);
	}

	// Get name from file name to name the namespace
		//This is a lot of names !
	ros::init(argc, argv, (std::string)appname);
	ros::NodeHandle n;
	
	// Create and build ROS interface
	RosUI* interface = new RosUI(n, (std::string)appname);
	DSP->buildUserInterface(interface);
	
	// Is there any declared ROS metadata ?
	bool meta = interface->isTrue();
	
	if (meta) // If there is any, then we subscribe to the specific subscriber(s)
	{
		RosCallbacks* subscriber = new RosCallbacks(n); 
		std::vector<FAUSTFLOAT*> my_zones = interface->getZones();
		subscriber->subscribe(my_zones);
	}
	
	// Launching jack audio API
	jackaudio audio;
	audio.init(appname, DSP);

	audio.start();
		
	// Call ROS Callbacks
	ros::spin();
	
	// Once Ctrl + C, everything stops
	audio.stop();
	
    // desallocation
    delete interface;
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

