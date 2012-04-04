/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2004-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either version 3
	of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.

	MAX MSP SDK : in order to compile a MaxMSP external with this
	architecture file you will need the official MaxMSP SDK from
	cycling'74. Please check the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#define FAUSTFLOAT double

#include "faust/gui/UI.h"
#include "faust/audio/dsp.h"
#include "faust/misc.h"

using namespace std;

// There is a bug with powf() when cross compiling with mingw
// the following macro avoid the problem
#ifdef WIN32
#define powf(x,y) pow(x,y)
#define expf(x) exp(x)
#endif

#ifdef __GNUC__

//-------------------------------------------------------------------
// Generic min and max using gcc extensions
//-------------------------------------------------------------------


#else

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max(unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max(int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max(long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max(int a, long b)          { return (a>b) ? a : b; }
inline long 	max(long a, int b)          { return (a>b) ? a : b; }

inline float 	max(float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max(int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max(float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max(long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max(float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max(double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max(int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max(double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max(long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max(double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max(float a, double b)      { return (a>b) ? a : b; }
inline double 	max(double a, float b)      { return (a>b) ? a : b; }

inline int 		min(int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min(long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min(int a, long b)          { return (a<b) ? a : b; }
inline long 	min(long a, int b)          { return (a<b) ? a : b; }

inline float 	min(float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min(int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min(float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min(long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min(float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min(double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min(int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min(double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min(long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min(double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min(float a, double b)      { return (a<b) ? a : b; }
inline double 	min(double a, float b)      { return (a<b) ? a : b; }

#endif

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


/* Faust code wrapper ------- */

#include "ext.h"
#include "z_dsp.h"
#include <string.h>

#define ASSIST_INLET 	1  		/* should be defined somewhere ?? */
#define ASSIST_OUTLET 	2		/* should be defined somewhere ?? */

class mspUI;

/*--------------------------------------------------------------------------*/
typedef struct faust
{
	t_pxobject m_ob;
	t_atom *m_seen, *m_want;
	short m_where;
	void** args;
	mspUI* dspUI;
	mydsp* dsp;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:

		string fLabel;
		double* fZone;

		double range(double min, double max, double val) {return (val < min) ? min : (val > max) ? max : val;}

	public:

		mspUIObject(const char* label, double* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}

		virtual void SetValue(double f) {*fZone = range(0.0,1.0,f);}
		virtual void toString(char* buffer) {}
		virtual string GetName() {return fLabel;}
};

/*--------------------------------------------------------------------------*/
class mspToggleButton : public mspUIObject {

	public:

		mspToggleButton(const char* label, double* zone):mspUIObject(label,zone) {}
		virtual ~mspToggleButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "ToggleButton(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {

	public:

		mspCheckButton(const char* label, double* zone):mspUIObject(label,zone) {}
		virtual ~mspCheckButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "CheckButton(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {

	public:

		mspButton(const char* label, double* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Button(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject{

	private:

		double fInit;
		double fMin;
		double fMax;
		double fStep;

	public:

		mspSlider(const char* label, double* zone, double init, double min, double max, double step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Slider(double): %s [%.1f:%.1f:%.1f]", fLabel.c_str(), fMin, fInit, fMax);
		}

		void SetValue(double f) {*fZone = range(fMin,fMax,f);}
};

/*--------------------------------------------------------------------------*/
class mspUI : public UI
{
	private:

		map<string,mspUIObject*> fUITable;

	public:
    
		typedef map<string,mspUIObject*>::iterator iterator;

		mspUI() {}
		virtual ~mspUI()
		{
			for (iterator iter = fUITable.begin(); iter != fUITable.end(); iter++) {
                delete (iter->second);
            }
   		}

		void addButton(const char* label, double* zone) {fUITable[string(label)] = new mspButton(label, zone);}

		void addToggleButton(const char* label, double* zone) {fUITable[string(label)] = new mspToggleButton(label, zone);}

		void addCheckButton(const char* label, double* zone) {fUITable[string(label)] = new mspCheckButton(label, zone);}

		void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void openFrameBox(const char* label) {}
		void openTabBox(const char* label) {}
		void openHorizontalBox(const char* label) {}
		void openVerticalBox(const char* label) {}
		void closeBox() {}

		void SetValue(string name, double f)
		{
			if (fUITable.count(name)) {
				fUITable[name]->SetValue(f);
            }
		}
		iterator begin()	{return fUITable.begin();}
		iterator end()		{return fUITable.end();}

		// To be implemented
		void addNumDisplay(const char* label, double* zone, int precision) {}
		void addTextDisplay(const char* label, double* zone, const char* names[], double min, double max) {}
        void addHorizontalBargraph(const char* label, double* zone, double min, double max) {}
		void addVerticalBargraph(const char* label, double* zone, double min, double max) {}
};

//--------------------------------------------------------------------------
void faust_method(t_faust *obj, t_symbol *s, short ac, t_atom *at)
{
	if (ac < 0) return;
    if (at[0].a_type != A_FLOAT) return;

    string name = string((s)->s_name);
    float value = at[0].a_w.w_float;

  	obj->dspUI->SetValue(name, (double)value); // doesn't have any effect if name is unknown
}

/*--------------------------------------------------------------------------*/
void *faust_new(t_symbol *s, short ac, t_atom *av)
{
	t_faust *x = (t_faust *)newobject(faust_class);

	x->dsp = new mydsp();
	x->dspUI = new mspUI();

	x->dsp->init(long(sys_getsr()));
	x->dsp->buildUserInterface(x->dspUI);

	x->args = (void**)calloc((x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2, sizeof(void*));

	/* Multi in */
	dsp_setup((t_pxobject *)x, x->dsp->getNumInputs());

	/* Multi out */
	for (int i = 0; i< x->dsp->getNumOutputs(); i++) {
		outlet_new((t_pxobject *)x, (char*)"signal");
    }

	((t_pxobject *)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
	return x;
}

/*--------------------------------------------------------------------------*/
void faust_assist(t_faust *x, void *b, long msg, long a, char *dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->dsp->getNumInputs() == 0) {
                sprintf(dst, "(signal) : Unused Input");
            } else {
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			}
			post((char*)"------------------");
			for (mspUI::iterator it = x->dspUI->begin(); it != x->dspUI->end(); ++it) {
				char param[64];
				it->second->toString(param);
				post(param);
			}
        } else if (a < x->dsp->getNumInputs()) {
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        sprintf(dst, "(signal) : Audio Output %ld", (a+1));
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust *x)
{
	dsp_free((t_pxobject *)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args) free(x->args);
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    AVOIDDENORMALS;
    x->dsp->compute(sampleframes, ins, outs);
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
int main()
{
	setup((t_messlist **)&faust_class, (method)faust_new, (method)faust_free,
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	dsp *thedsp = new mydsp();
	mspUI *dspUI = new mspUI();
	thedsp->buildUserInterface(dspUI);

	// Add the same method for every parameters and use the symbol as a selector
	// inside this method
	for (mspUI::iterator it = dspUI->begin(); it != dspUI->end(); ++it) {
		char *name = const_cast<char *>(it->second->GetName().c_str());
		addmess((method)faust_method, name, A_GIMME, 0);
	}

    addmess((method)faust_dsp64, (char*)"dsp64", A_CANT, 0);
	addmess((method)faust_assist, (char*)"assist", A_CANT, 0);
	dsp_initclass();

    delete(dspUI);
    delete(thedsp);
	post((char*)"Faust DSP object");
	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/




