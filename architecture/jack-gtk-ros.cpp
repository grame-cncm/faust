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

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <list>

#include "faust/misc.h"
#include "faust/gui/faustgtk.h"
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

std::list<GUI*>               GUI::fGuiList;

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
	char	appname[256];
	char* 	home = getenv("HOME");
	
	snprintf(appname, 255, "%s", basename(argv[0]));
	
	// create DSP object
	DSP = new mydsp();
	if (DSP==0) {
        ROS_ERROR("Unable to allocate Faust DSP object" );
		exit(1);
	}

	// Get name from file name to name the namespace.
	ros::init(argc, argv, (std::string)appname);
	ros::NodeHandle n((std::string)appname);
		
	// create and build graphic and ROS interfaces
	GUI* interface 	= new GTKUI (appname, &argc, &argv);
	RosUI* rosinterface = new RosUI (n);
	
	DSP->buildUserInterface(rosinterface);
	DSP->buildUserInterface(interface);
	
#ifdef HTTPCTRL
	httpdUI*	httpdinterface = new httpdUI(appname, argc, argv);
	DSP->buildUserInterface(httpdinterface);
    ROS_INFO("HTTPD is on");
#endif

#ifdef OSCCTRL
	GUI*	oscinterface = new OSCUI(appname, argc, argv);
	DSP->buildUserInterface(oscinterface);
#endif
	
	jackaudio audio;
	audio.init(appname, DSP);
	
	audio.start();
	
#ifdef HTTPCTRL
	httpdinterface->run();
#ifdef QRCODECTRL
    interface->displayQRCode( httpdinterface->getTCPPort() );
#endif
#endif
	
#ifdef OSCCTRL
	oscinterface->run();
#endif

	// ROS Callbacks are called by AsyncSpinner spinner
	ros::AsyncSpinner spinner(rosinterface->getParamsCount());
	spinner.start();
	
	// GTK interface is launched
	interface->run();
		
    	interface->stop();
    
	audio.stop();
	
    
    // desallocation
    delete interface;
    delete rosinterface;
    
#ifdef HTTPCTRL
	 delete httpdinterface;
#endif
#ifdef OSCCTRL
	 delete oscinterface;
#endif

  	return 0;
}


/********************END ARCHITECTURE SECTION (part 2/2)****************/

