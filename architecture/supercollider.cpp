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

struct Meta 
{
    void declare (const char* key, const char* value) { }
};

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

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

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
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// passive widgets
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	// layout widgets
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;

    virtual void declare(float* zone, const char* key, const char* value) {}
};

//----------------------------------------------------------------------------
// Control counter
//----------------------------------------------------------------------------
		
class ControlCounter : public UI
{
public:
	ControlCounter()
		: mNumControlInputs(0),
		  mNumControlOutputs(0)
	{ }

	size_t getNumControls() const { return getNumControlInputs(); }
	size_t getNumControlInputs() const { return mNumControlInputs; }
	size_t getNumControlOutputs() const { return mNumControlOutputs; }
	
	// active widgets
	virtual void addButton(const char* label, float* zone)
	{ addControlInput(); }
	virtual void addToggleButton(const char* label, float* zone)
	{ addControlInput(); }
	virtual void addCheckButton(const char* label, float* zone)
	{ addControlInput(); }
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{ addControlInput(); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{ addControlInput(); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
	{ addControlInput(); }
	
	// passive widgets
	virtual void addNumDisplay(const char* label, float* zone, int precision) { addControlOutput(); }
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) { addControlOutput(); }
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) { addControlOutput(); }
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) { addControlOutput(); }
	
	// layout widgets
	virtual void openFrameBox(const char* label) { }
	virtual void openTabBox(const char* label) { }
	virtual void openHorizontalBox(const char* label) { }
	virtual void openVerticalBox(const char* label) { }
	virtual void closeBox() { }

protected:
	void addControlInput() {
		printf("addControlInput %d\n", mNumControlInputs);
		mNumControlInputs++; }
	void addControlOutput() { }

private:
	size_t mNumControlInputs;
	size_t mNumControlOutputs;
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
	virtual void addButton(const char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addToggleButton(const char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addCheckButton(const char* label, float* zone)
	{ addSimpleControl(zone); }
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
	{ addBoundedControl(zone, min, max, step); }

	// passive widgets
	virtual void addNumDisplay(const char* label, float* zone, int precision) { }
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) { }
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) { }
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) { }
	
	// layout widgets
	virtual void openFrameBox(const char* label) { }
	virtual void openTabBox(const char* label) { }
	virtual void openHorizontalBox(const char* label) { }
	virtual void openVerticalBox(const char* label) { }
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

// Global state
struct State
{
	mydsp	dsp;
	size_t	numControls;
	char	unitName[PATH_MAX];
	
	void init(int sampleRate);
	size_t unitSize() const;
};

void State::init(int sampleRate)
{
	ControlCounter cc;
	dsp.classInit(sampleRate); // TODO: use real sample rate
	dsp.buildUserInterface(&cc);
	numControls = cc.getNumControls();
}

size_t State::unitSize() const
{
	return sizeof(Faust) + numControls * sizeof(Control);
}

// Globals
static State gState;
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
	unit->mNumControls = gState.numControls;
	ControlAllocator ca(unit->mControls);
	unit->mDSP.buildUserInterface(&ca);

	// check input/output channel configuration
	const size_t numInputs  = unit->mDSP.getNumInputs() + unit->mNumControls;
	const size_t numOutputs = unit->mDSP.getNumOutputs();
	
	bool channelsValid =   (numInputs  == unit->mNumInputs)
						&& (numOutputs == unit->mNumOutputs);
	bool rateValid = true;
	int rateOffender = -1;
	
	if (channelsValid) {
		for (int i = 0; i < unit->mDSP.getNumInputs(); ++i) {
			if (INRATE(i) != calc_FullRate) {
				rateValid = false;
				rateOffender = i;
				break;
			}
		}
	}

	if (channelsValid && rateValid) {
		SETCALC(Faust_next);
	} else {
		Print("Faust[%s]:\n", gState.unitName);
		if (!channelsValid) {
			Print("    Input/Output channel mismatch\n"
				  "        Inputs:  faust %d, unit %d\n"
				  "        Outputs: faust %d, unit %d\n",
				  numInputs, unit->mNumInputs,
				  numOutputs, unit->mNumOutputs);
		}
		if (!rateValid) {
			Print("    Input rate mismatch\n"
				  "        Input %d not audio rate\n");
		}
		Print("    Generating silence ...\n",
			  "    Did you recompile the class library?\n");
		SETCALC(Faust_next_clear);
	}
}

void load(InterfaceTable* inTable)
{
    ft = inTable;

	// initialize unit name
	char* name = gState.unitName;

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

 	// TODO: use real sample rate
	gState.init(48000);
	
	// register ugen
	(*ft->fDefineUnit)(
		name,
		gState.unitSize(),
		(UnitCtorFunc)&Faust_Ctor, 0,
		kUnitDef_CantAliasInputsToOutputs
		);
		
	Print("Faust: %s numControls=%d\n", gState.unitName, gState.numControls);
}

// EOF
