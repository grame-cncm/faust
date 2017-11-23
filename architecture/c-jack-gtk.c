/************************************************************************
 ************************************************************************
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
#include "faust/gui/faustgtk.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/UIGlue.h"

using namespace std;

/*******************************************************************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

class Cdsp : public dsp {

  private:

	mydsp* fDsp;

  public:

	Cdsp()
	{
        fDsp = newmydsp();
	}

	virtual ~Cdsp()
	{
		deletemydsp(fDsp);
	}
	virtual int getNumInputs() 	{ return getNumInputsmydsp(fDsp); }
    
	virtual int getNumOutputs() { return getNumOutputsmydsp(fDsp); }

	static void classInit(int samplingFreq)
    {
        classInitmydsp(samplingFreq);
    }

	virtual void instanceInit(int samplingFreq)
    {
		instanceInitmydsp(fDsp, samplingFreq);
	}
    
    virtual void instanceConstants(int samplingFreq)
    {
        instanceConstantsmydsp(fDsp, samplingFreq);
    }
    
    virtual void instanceResetUserInterface()
    {
        instanceResetUserInterfacemydsp(fDsp);
    }
    
    virtual void instanceClear()
    {
        instanceClearmydsp(fDsp);
    }
  
    virtual void metadata(Meta* m)
    {
        MetaGlue glue;
        buildMetaGlue(&glue, m);
        metadatamydsp(&glue);
    }
    
    virtual dsp* clone()
    {
       return (dsp*)newmydsp();
    }
    
    virtual int getSampleRate()
    {
        return getSampleRatemydsp(fDsp);
    }

	virtual void init(int samplingFreq)
    {
		initmydsp(fDsp, samplingFreq);
	}

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

        buildUserInterfacemydsp(fDsp, &glue);
  	}

	virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
    {
		computemydsp(fDsp, count, input, output);
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

	snprintf(appname, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, appname);

	Cdsp* DSP = new Cdsp();
	if (DSP == 0) {
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


