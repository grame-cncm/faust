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

using namespace std;

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/FUI.h"
#include "faust/gui/CUI.h"
#include "faust/gui/faustgtk.h"
#include "faust/misc.h"
#include "faust/audio/jack-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

struct llvm_dsp {};

llvm_dsp* new_mydsp();
void delete_mydsp(llvm_dsp*);

int getNumInputs_mydsp(llvm_dsp*);
int getNumOutputs_mydsp(llvm_dsp*);

void init_mydsp(llvm_dsp*, int);
void classInit_mydsp(int);
void instanceInit_mydsp(llvm_dsp*, int);
void buildUserInterface_mydsp(llvm_dsp*, UIGlue*);

void compute_mydsp(llvm_dsp*, int, FAUSTFLOAT**, FAUSTFLOAT**);

#ifdef __cplusplus
}
#endif

class llvmdsp : public dsp {

  private:

	llvm_dsp* fDsp;

  public:

	llvmdsp()
	{
        fDsp = new_mydsp();
    }

	virtual ~llvmdsp()
	{
		delete_mydsp(fDsp);
	}

	virtual int getNumInputs() 	{ return getNumInputs_mydsp(fDsp); }
	virtual int getNumOutputs() { return getNumOutputs_mydsp(fDsp); }

	static void classInit(int samplingFreq)
    {
        classInit_mydsp(samplingFreq);
    }

	virtual void instanceInit(int samplingFreq)
    {
		instanceInit_mydsp(fDsp, samplingFreq);
	}

	virtual void init(int samplingFreq) {
		init_mydsp(fDsp, samplingFreq);
	}

	virtual void buildUserInterface(UI* interface)
    {
        UIGlue glue;
        glue.uiInterface = interface;
        glue.openTabBox = openTabBoxGlue;
        glue.openHorizontalBox = openHorizontalBoxGlue;
        glue.openVerticalBox = openVerticalBoxGlue;
        glue.closeBox = closeBoxGlue;
        glue.addButton = addButtonGlue;
        glue.addCheckButton = addCheckButtonGlue;
        glue.addVerticalSlider = addVerticalSliderGlue;
        glue.addHorizontalSlider = addHorizontalSliderGlue;
        glue.addNumEntry = addNumEntryGlue;
        glue.addHorizontalBargraph = addHorizontalBargraphGlue;
        glue.addVerticalBargraph = addVerticalBargraphGlue;
        glue.declare = declareGlue;
        buildUserInterface_mydsp(fDsp, &glue);
 	}

	virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
    {
        AVOIDDENORMALS;
		compute_mydsp(fDsp, count, input, output);
	}
};

list<GUI*> GUI::fGuiList;

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	char	appname[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");
	
	snprintf(appname, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, appname);

	llvmdsp* DSP = new llvmdsp();
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

		
/********************END ARCHITECTURE SECTION (part 2/2)****************/

