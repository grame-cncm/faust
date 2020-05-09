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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <sys/wait.h>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <libgen.h>
#include <jack/jack.h>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/gui/GTKUI.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/UIGlue.h"

using namespace std;

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

// Wrapping C++ class for the C object

class Cdsp : public dsp {

  private:

	mydsp* fDSP;

  public:

	Cdsp()
	{
        fDSP = newmydsp();
	}

	virtual ~Cdsp()
	{
		deletemydsp(fDSP);
	}
	virtual int getNumInputs() 	{ return getNumInputsmydsp(fDSP); }
    
	virtual int getNumOutputs() { return getNumOutputsmydsp(fDSP); }
    
    virtual void buildUserInterface(UI* interface)
    {
        UIGlue glue;
        glue.uiInterface = interface;
        glue.openTabBox = openTabBoxGlueFloat;
        glue.openHorizontalBox = openHorizontalBoxGlueFloat;
        glue.openVerticalBox = openVerticalBoxGlueFloat;
        glue.closeBox = closeBoxGlueFloat;
        glue.addButton = addButtonGlueFloat;
        glue.addCheckButton = addCheckButtonGlueFloat;
        glue.addVerticalSlider = addVerticalSliderGlueFloat;
        glue.addHorizontalSlider = addHorizontalSliderGlueFloat;
        glue.addNumEntry = addNumEntryGlueFloat;
        glue.addHorizontalBargraph = addHorizontalBargraphGlueFloat;
        glue.addVerticalBargraph = addVerticalBargraphGlueFloat;
        glue.addSoundFile = addSoundFileGlueFloat;
        glue.declare = declareGlueFloat;
        
        buildUserInterfacemydsp(fDSP, &glue);
    }

    virtual int getSampleRate()
    {
        return getSampleRatemydsp(fDSP);
    }
    
    virtual void init(int samplingRate)
    {
        initmydsp(fDSP, samplingRate);
    }

	static void classInit(int samplingRate)
    {
        classInitmydsp(samplingRate);
    }

	virtual void instanceInit(int samplingRate)
    {
		instanceInitmydsp(fDSP, samplingRate);
	}
    
    virtual void instanceConstants(int samplingRate)
    {
        instanceConstantsmydsp(fDSP, samplingRate);
    }
    
    virtual void instanceResetUserInterface()
    {
        instanceResetUserInterfacemydsp(fDSP);
    }
    
    virtual void instanceClear()
    {
        instanceClearmydsp(fDSP);
    }
  
    virtual dsp* clone()
    {
        return new Cdsp();
    }
    
    virtual void metadata(Meta* m)
    {
        MetaGlue glue;
        buildMetaGlue(&glue, m);
        metadatamydsp(&glue);
    }
  
	virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
    {
		computemydsp(fDSP, count, input, output);
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

list<GUI*> GUI::fGuiList;
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

	Cdsp* DSP = new Cdsp();
	if (!DSP) {
		cerr << "Unable to allocate Faust DSP object" << endl;
		exit(1);
	}
	GUI* interface 	= new GTKUI(appname, &argc, &argv);
	FUI* finterface	= new FUI();
	DSP->buildUserInterface(interface);
	DSP->buildUserInterface(finterface);

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(appname, argc, argv);
	DSP->buildUserInterface(oscinterface);
#endif

	jackaudio audio;
	audio.init(appname, DSP);
	finterface->recallState(rcfilename);
	audio.start();

#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();

	audio.stop();
	finterface->saveState(rcfilename);
	delete DSP;
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

