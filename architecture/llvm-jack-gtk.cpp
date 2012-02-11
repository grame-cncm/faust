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

using namespace std;

#include "gui/FUI.h"
#include "misc.h"
#include "gui/faustgtk.h"
#include "audio/jack-dsp.h"

#ifdef OSCCTRL
#include "gui/OSCUI.h"
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
//#define IS_DOUBLE 1
#endif

//#define BENCHMARKMODE

#ifdef __APPLE__
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#endif

#ifndef UInt64
typedef long long unsigned int UInt64;
typedef unsigned int UInt32;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

UInt64 DSP_rdtsc(void)
{
	union {
		UInt32 i32[2];
		UInt64 i64;
	} count;

	__asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
     return count.i64;
}

#define LOCK "lock ; "

char CAS1(volatile void* addr, volatile int value, int newvalue)
{
    register char ret;
    __asm__ __volatile__ (
						  "# CAS \n\t"
						  LOCK "cmpxchg %2, (%1) \n\t"
						  "sete %0               \n\t"
						  : "=a" (ret)
						  : "c" (addr), "d" (newvalue), "a" (value)
                          : "memory"
						  );
    return ret;
}

int atomic_xadd(volatile int* atomic, int val)
{
    register int result;
    __asm__ __volatile__ ("# atomic_xadd \n\t"
                          LOCK "xaddl %0,%1 \n\t"
                          : "=r" (result), "=m" (*atomic)
                          : "0" (val), "m" (*atomic));
    return result;
}

#ifdef __cplusplus
}
#endif


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

// -- layout groups

typedef void (* openFrameBoxFun) (void* interface, const char* label);
typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addToggleButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive display widgets

typedef void (* addNumDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, int precision);
typedef void (* addTextDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

typedef void (* declareFun) (void* interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct UIGlue {

    void* uiInterface;

    openFrameBoxFun openFrameBox;
    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addToggleButtonFun addToggleButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addNumDisplayFun addNumDisplay;
    addTextDisplayFun addTextDisplay;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    declareFun declare;

};

typedef struct llvm_dsp {};

llvm_dsp* new_mydsp();
void delete_mydsp(llvm_dsp*);

int getNumInputs_mydsp(llvm_dsp*);
int getNumOutputs_mydsp(llvm_dsp*);

void init_mydsp(llvm_dsp*, int);
void classInit_mydsp(int);
void instanceInit_mydsp(llvm_dsp*, int);
void buildUserInterface_mydsp(llvm_dsp*, UIGlue*);

void compute_mydsp(llvm_dsp*, int, FAUSTFLOAT**, FAUSTFLOAT**);

void openFrameBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openFrameBox(label);
}

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

void addToggleButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addToggleButton(label, zone);
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

void addNumDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, int precision)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumDisplay(label, zone, precision);
}

void addTextDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addTextDisplay(label, zone, names, min, max);
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
        glue.openFrameBox = openFrameBoxGlue;
        glue.openTabBox = openTabBoxGlue;
        glue.openHorizontalBox = openHorizontalBoxGlue;
        glue.openVerticalBox = openVerticalBoxGlue;
        glue.closeBox = closeBoxGlue;
        glue.addButton = addButtonGlue;
        glue.addToggleButton = addToggleButtonGlue;
        glue.addCheckButton = addCheckButtonGlue;
        glue.addVerticalSlider = addVerticalSliderGlue;
        glue.addHorizontalSlider = addHorizontalSliderGlue;
        glue.addNumEntry = addNumEntryGlue;
        glue.addNumDisplay = addNumDisplayGlue;
        glue.addTextDisplay = addTextDisplayGlue;
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

llvmdsp* DSP;

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

	DSP = new llvmdsp();
	if (DSP==0) {
		cerr << "Unable to allocate Faust DSP object" << endl;
		exit(1);
	}
	GUI* interface 	= new GTKUI(appname, &argc, &argv);
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

		
/********************END ARCHITECTURE SECTION (part 2/2)****************/

