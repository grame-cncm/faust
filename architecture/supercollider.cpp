/*  -*- mode: c++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-
    vi: noet sta sw=4 ts=4:

    FAUST architecture file for SuperCollider.
	Copyright (C) 2005 Stefan Kersten.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

// compile with:
// g++ `pkg-config --cflags libscsynth` -O3 -fPIC -shared -lm -o XXX.so XXX.cpp

#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <SC_PlugIn.h>

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }
		
inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }
inline int 		int2pow2 (int x)			{ int r=0; while ((1<<r)<x) r++; return r; }


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

inline void *aligned_calloc(size_t nmemb, size_t size)
{
	return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0);
}

<<includeIntrinsic>>


/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
// Abstract user interface
//----------------------------------------------------------------------------
		
class UI 
{
public:
	virtual ~UI() { }

	// active widgets
	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// passive widgets
	virtual void addNumDisplay(char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;
	
	// layout widgets
	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
	virtual void closeBox() = 0;
};

//----------------------------------------------------------------------------
// Control counter
//----------------------------------------------------------------------------
		
class ControlCounter : public UI
{
public:
	ControlCounter()
		: mNumControls(0)
	{ }

	size_t getNumControls() const { return mNumControls; }

	// active widgets
	virtual void addButton(char* label, float* zone)
	{ addControl(); }
	virtual void addToggleButton(char* label, float* zone)
	{ addControl(); }
	virtual void addCheckButton(char* label, float* zone)
	{ addControl(); }
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step)
	{ addControl(); }
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step)
	{ addControl(); }
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
	{ addControl(); }
	
	// passive widgets
	virtual void addNumDisplay(char* label, float* zone, int precision) { }
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) { }
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) { }
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) { }
	
	// layout widgets
	virtual void openFrameBox(char* label) { }
	virtual void openTabBox(char* label) { }
	virtual void openHorizontalBox(char* label) { }
	virtual void openVerticalBox(char* label) { }
	virtual void closeBox() { }

protected:
	void addControl() { mNumControls++; }

private:
	size_t mNumControls;
};

//----------------------------------------------------------------------------
// UI control
//----------------------------------------------------------------------------
		
struct Control
{
	typedef void (*UpdateFunction)(Control* self, float value);
	
	UpdateFunction updateFunction;
	float min, max, step;
	float* zone;
	
	inline void update(float value)
	{
		(*updateFunction)(this, value);
	}
	
	static void simpleUpdate(Control* self, float value)
	{
		*self->zone = value;
	}
	static void boundedUpdate(Control* self, float value)
	{
		*self->zone = sc_round(sc_clip(value, self->min, self->max), self->step);
	}
};

//----------------------------------------------------------------------------
// Control allocator
//----------------------------------------------------------------------------
		
class ControlAllocator : public UI
{
public:
	ControlAllocator(Control* controls)
		: mControls(controls)
	{ }

	// active widgets
	virtual void addButton(char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addToggleButton(char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addCheckButton(char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }

	// passive widgets
	virtual void addNumDisplay(char* label, float* zone, int precision) { }
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) { }
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) { }
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) { }
	
	// layout widgets
	virtual void openFrameBox(char* label) { }
	virtual void openTabBox(char* label) { }
	virtual void openHorizontalBox(char* label) { }
	virtual void openVerticalBox(char* label) { }
	virtual void closeBox() { }

private:
	void addControl(Control::UpdateFunction updateFunction, float* zone, float min, float max, float step)
	{
		Control* ctrl = mControls++;
		ctrl->updateFunction = updateFunction;
		ctrl->min = min;
		ctrl->max = max;
		ctrl->step = step;
		ctrl->zone = zone;
	}
	void addSimpleControl(float* zone)
	{
		addControl(Control::simpleUpdate, zone, 0.f, 0.f, 0.f);
	}
	void addBoundedControl(float* zone, float min, float max, float step)
	{
		addControl(Control::boundedUpdate, zone, min, max, step);
	}

private:
	Control* mControls;
};


/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
// Abstract DSP interface
//----------------------------------------------------------------------------
		
class dsp
{
public:
	virtual ~dsp();
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;

protected:
	int fSamplingFreq;
};

dsp::~dsp() { }

//----------------------------------------------------------------------------
// FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>


/******************************************************************************
*******************************************************************************

							SUPERCOLLIDER DSP INTERFACE

*******************************************************************************
*******************************************************************************/

struct Faust : public Unit
{
	mydsp		mDSP;
	size_t		mNumControls;
	Control		mControls[0];
};

// globals
static char gUnitName[PATH_MAX];
static size_t gNumControls;
static InterfaceTable *ft;

extern "C"
{
    void load(InterfaceTable*);
    void Faust_next(Faust*, int);
    void Faust_next_clear(Faust*, int);
    void Faust_Ctor(Faust*);
};

void Faust_next(Faust* unit, int inNumSamples)
{
	// update controls
	Control* controls = unit->mControls;
	int numControls = unit->mNumControls;
	int curControl = unit->mDSP.getNumInputs();
	while (numControls--) {
		(controls++)->update(IN0(curControl++));
	}
	// dsp computation
	unit->mDSP.compute(inNumSamples, unit->mInBuf, unit->mOutBuf);
}

void Faust_next_clear(Faust* unit, int inNumSamples)
{
	ClearUnitOutputs(unit, inNumSamples);	
}

void Faust_Ctor(Faust* unit)
{
	// init dsp
	unit->mDSP.instanceInit((int)SAMPLERATE);

	// allocate controls
	ControlAllocator ca(unit->mControls);
	unit->mDSP.buildUserInterface(&ca);
	unit->mNumControls = gNumControls;

	// check input/output channel configuration
	bool valid =
		((unit->mNumInputs == (unit->mDSP.getNumInputs() + unit->mNumControls)) &&
		 (unit->mNumOutputs == unit->mDSP.getNumOutputs()));

	if (valid) {
		for (int i = 0; i < unit->mDSP.getNumInputs(); ++i) {
			if (INRATE(i) != calc_FullRate) {
				valid = false;
				break;
			}
		}
	}

	if (valid) {
		SETCALC(Faust_next);
	} else {
		Print("Faust[%s]: Input/Output channel/rate mismatch\n"
			  "           Generating silence ...\n",
			  "           Did you recompile the class library?\n",
			  gUnitName);
		SETCALC(Faust_next_clear);
	}
}

void load(InterfaceTable* inTable)
{
    ft = inTable;

	// initialize unit name
	char* name = gUnitName;

	// use file name as ugen name
	const char* fileName = strrchr(__FILE__, '/');
	if (fileName) {
		fileName++;
	} else {
		fileName = __FILE__;
	}
	strncpy(name, fileName, PATH_MAX);

	// strip extension(s)
	char* ext = strchr(name, '.');
	if (ext) *ext = 0;

	if (!name[0]) {
		// catch empty name
		Print("Faust: empty unit generator name\n"
			  "       bailing out ...\n");
		return;
	}

	// get number of controls and compute resulting unit size
	mydsp* dsp = new mydsp; // avoid stack overflow!
	ControlCounter cc;
	dsp->classInit(48000); // TODO: use real sample rate
	dsp->buildUserInterface(&cc);
	size_t numControls = gNumControls = cc.getNumControls();
	size_t sizeofFaust = sizeof(Faust) + numControls * sizeof(Control);
	delete dsp;

	// register ugen
	(*ft->fDefineUnit)(
		name, sizeofFaust,
		(UnitCtorFunc)&Faust_Ctor, 0,
		kUnitDef_CantAliasInputsToOutputs
		);

#if 0
	Print(
		"Faust[%s]: inputs: %d outputs: %d controls: %d size: %d\n",
		name, numInputs, numOutputs, numControls, sizeofFaust
		);
#endif
}

// EOF
