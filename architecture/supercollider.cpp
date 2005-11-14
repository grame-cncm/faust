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

#define MAX_NUM_CONTROLS 16

static InterfaceTable *ft;
static char gUnitName[PATH_MAX];

#ifdef __GNUC__

//-------------------------------------------------------------------
// Generic min and max using gcc extensions
//-------------------------------------------------------------------

#define max(x,y) ((x)>?(y))
#define min(x,y) ((x)<?(y))

//abs(x) should be already predefined

#else

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
		
#endif

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


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

struct UI
{
public:
	struct Control
	{
		float*	zone;
		float	min;
		float	max;
		float	step;

		void update(float value)
		{
			*zone = sc_round(sc_clip(value, min, max), step);
		}
	};

	void init()
	{
		mNumControls = 0;
	}

	void addControl(float* zone, float min, float max, float step)
	{
		if (mNumControls < MAX_NUM_CONTROLS) {
			Control* ctrl = &mControls[mNumControls++];
			ctrl->zone = zone;
			ctrl->min = min;
			ctrl->max = max;
			ctrl->step = step;
		} else {
			scprintf("Faust[%s]: control zone storage exceeded\n"
					 "           increase MAX_NUM_CONTROLS in %s\n",
					 gUnitName, __FILE__);
		}
	}

	Control* getControls() { return mControls; }
	size_t getNumControls() const { return mNumControls; }

	// -- active widgets
	
	void addButton(char*, float* zone)
	{ addControl(zone, 0.f, 1.f, 0.f); }
	void addToggleButton(char*, float* zone)
	{ addControl(zone, 0.f, 1.f, 0.f); }
	void addCheckButton(char*, float* zone)
	{ addControl(zone, 0.f, 1.f, 0.f); }
	void addVerticalSlider(char*, float* zone, float init, float min, float max, float step)
	{ addControl(zone, min, max, step); }
	void addHorizontalSlider(char*, float* zone, float init, float min, float max, float step)
	{ addControl(zone, min, max, step); }
	void addNumEntry(char*, float* zone, float init, float min, float max, float step)
	{ addControl(zone, min, max, step); }
	
	// -- passive widgets (unused)
	
	// TODO: might add these as outputs
	void addNumDisplay(char* label, float* zone, int precision) { }
	void addTextDisplay(char* label, float* zone, char* names[], float min, float max) { }
	void addHorizontalBargraph(char* label, float* zone, float min, float max) { }
	void addVerticalBargraph(char* label, float* zone, float min, float max) { }
	
	// -- widget's layouts (unused)
	
	void openFrameBox(char* label) { }
	void openTabBox(char* label) { }
	void openHorizontalBox(char* label) { }
	void openVerticalBox(char* label) { }
	void closeBox() { }

private:
	Control		mControls[MAX_NUM_CONTROLS];
	size_t		mNumControls;
};


/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

class dsp
{
public:
	virtual ~dsp() = 0;
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;

protected:
	int fSamplingFreq;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>

/******************************************************************************
*******************************************************************************

							SUPERCOLLIDER DSP INTERFACE

*******************************************************************************
*******************************************************************************/

struct Faust : public Unit
{
	mydsp	mDSP;
	UI		mUI;
	int		mFirstControlIndex;
	int		mNumControls;
};

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
	UI::Control* ctrls = unit->mUI.getControls();
	int firstControl = unit->mFirstControlIndex;
	int numControls = unit->mNumControls;
	for (int i = 0; i < numControls; ++i) {
		ctrls[i].update(IN0(firstControl + i));
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
	unit->mDSP.init((int)SAMPLERATE);

	// check input/output channels
	bool valid = true;
	valid = ((unit->mNumInputs >= unit->mDSP.getNumInputs()) &&
			 (unit->mNumOutputs >= unit->mDSP.getNumOutputs()));
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
		scprintf("Faust[%s]: input/output channel mismatch, generating silence ...\n",
				 gUnitName);
		SETCALC(Faust_next_clear);
	}

	// init ui
	unit->mUI.init();
	unit->mDSP.buildUserInterface(&unit->mUI);

	// init control zone bounds
	unit->mFirstControlIndex = unit->mDSP.getNumInputs();
	if (unit->mFirstControlIndex > unit->mNumInputs) {
		unit->mFirstControlIndex = unit->mNumInputs;
	}
	unit->mNumControls = unit->mUI.getNumControls();
	if ((unit->mFirstControlIndex + unit->mNumControls) > unit->mNumInputs) {
		unit->mNumControls = unit->mNumInputs - unit->mFirstControlIndex;
	}
}

void load(InterfaceTable* inTable)
{
    ft = inTable;

	// use file name as ugen name
	char* name = gUnitName;
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

	if (name[0]) {
		// upcase name
		name[0] = toupper(name[0]);
	} else {	
		// catch empty name
		snprintf(name, PATH_MAX, "Faust");
	}

	(*ft->fDefineUnit)(name, sizeof(Faust),
					   (UnitCtorFunc)&Faust_Ctor, 0,
					   // FIXME: necessary?
					   kUnitDef_CantAliasInputsToOutputs);

	scprintf("Faust[%s]: loaded\n", name);
}

// EOF
