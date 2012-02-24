/* link with  */
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

#include "gui/FUI.h"
#include "misc.h"
#include "gui/faustgtk.h"
#include "audio/jack-dsp.h"
#include "gui/CUI.h"

using namespace std;

/*******************************************************************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
//#define IS_DOUBLE 1
#endif


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

void openTabBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openTabBox(label);
}

void openHorizontalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openHorizontalBox(label);
}

void openVerticalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openVerticalBox(label);
}

void closeBoxGlue(void* cpp_interface)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->closeBox();
}

void addButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addButton(label, zone);
}

void addCheckButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addCheckButton(label, zone);
}

void addVerticalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalSlider(label, zone, init, min, max, step);
}

void addHorizontalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalSlider(label, zone, init, min, max, step);
}

void addNumEntryGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumEntry(label, zone, init, min, max, step);
}

void addHorizontalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalBargraph(label, zone, min, max);
}

void addVerticalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalBargraph(label, zone, min, max);
}

void declareGlue(void* cpp_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->declare(zone, key, value);
}


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

	virtual void init(int samplingFreq) {
		initmydsp(fDsp, samplingFreq);
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

        buildUserInterfacemydsp(fDsp, &glue);
  	}

	virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
    {
		computemydsp(fDsp, count, input, output);
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

Cdsp*	DSP;

list<GUI*>                   GUI::fGuiList;

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

	DSP = new Cdsp();
	if (DSP == 0) {
		cerr << "Unable to allocate Faust DSP object" << endl;
		exit(1);
	}
	GUI* interface 	= new GTKUI (appname, &argc, &argv);
	FUI* finterface	= new FUI();
	DSP->buildUserInterface(interface);
	DSP->buildUserInterface(finterface);

#ifdef OSCCTRL
	GUI*	oscinterface = new OSCUI(appname, argc, argv);
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


