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

#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

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

#define EXTERNAL_VERSION "0.51"

class mspUI;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
     
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};


/*--------------------------------------------------------------------------*/
typedef struct faust
{
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    short m_where;
    bool m_mute;
    void** args;
    mspUI* dspUI;
    mydsp* dsp;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:

		string fLabel;
		float* fZone;

		float range(float min, float max, float val) {return (val < min) ? min : (val > max) ? max : val;}

	public:

		mspUIObject(const char* label, float* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}

		virtual void SetValue(double f) {*fZone = range(0.0,1.0,f);}
		virtual void toString(char* buffer) {}
		virtual string GetName() {return fLabel;}
};

/*--------------------------------------------------------------------------*/
class mspToggleButton : public mspUIObject {

	public:

		mspToggleButton(const char* label, float* zone):mspUIObject(label,zone) {}
		virtual ~mspToggleButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "ToggleButton(float): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {

	public:

		mspCheckButton(const char* label, float* zone):mspUIObject(label,zone) {}
		virtual ~mspCheckButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "CheckButton(float): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {

	public:

		mspButton(const char* label, float* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Button(float): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject{

	private:

		float fInit;
		float fMin;
		float fMax;
		float fStep;

	public:

		mspSlider(const char* label, float* zone, float init, float min, float max, float step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Slider(float): %s [init=%.1f:min=%.1f:max=%.1f:step=%.1f:cur=%.1f]", fLabel.c_str(), fInit, fMin, fMax, fStep, *fZone);
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

		void addButton(const char* label, float* zone) {fUITable[string(label)] = new mspButton(label, zone);}

		void addToggleButton(const char* label, float* zone) {fUITable[string(label)] = new mspToggleButton(label, zone);}

		void addCheckButton(const char* label, float* zone) {fUITable[string(label)] = new mspCheckButton(label, zone);}

		void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void openFrameBox(const char* label) {}
		void openTabBox(const char* label) {}
		void openHorizontalBox(const char* label) {}
		void openVerticalBox(const char* label) {}
		void closeBox() {}

		bool SetValue(string name, double f)
		{
			if (fUITable.count(name)) {
                fUITable[name]->SetValue(f);
                return true;
            } else {
                return false;
            }
		}
		iterator begin()	{return fUITable.begin();}
		iterator end()		{return fUITable.end();}

		// To be implemented
		void addNumDisplay(const char* label, float* zone, int precision) {}
		void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {}
        void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
		void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
};

//--------------------------------------------------------------------------
static bool check_digit(const string& name)
{
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) return true;
    }
    return false;
}

static int count_digit(const string& name)
{
    int count = 0;
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) count++;
    }
    return count;
}

void faust_method(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    /*
	if (ac < 0) return;
    if (at[0].a_type != A_FLOAT) return;

    string name = string((s)->s_name);
    float value = at[0].a_w.w_float;

  	obj->dspUI->SetValue(name, value); // doesn't have any effect if name is unknown
    */
    
    bool res = false;
    
    if (ac < 0) return;
    
    // Check if no argument is there, consider it is a toggle message for a button
    if (ac == 0) {
        
        string name = string((s)->s_name);
        float off = 0.0f;
        float on = 1.0f;
        obj->dspUI->SetValue(name, off);
        obj->dspUI->SetValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_method(obj, s, 1, av);
        
        return;
    }

    string name = string((s)->s_name);
    //printf("param_name name = %s  ac = %d\n", (s)->s_name, ac);
    
    // List of values
    if (check_digit(name)) {
        
        int ndigit = 0;
        int pos;
        
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
       
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            float value;
            switch (atom_gettype(ap)) {
                case A_LONG: {
                    value = (float)ap[0].a_w.w_long;
                    break;
                }
                case A_FLOAT:
                    value = ap[0].a_w.w_float;
                    break;
                    
                default:
                    post("Invalid argument in parameter setting"); 
                    return;         
            }
            
            stringstream num_val;
            num_val << num + i;
            char param_name[256];
            
            switch (ndigit - count_digit(num_val.str())) {
                case 0: 
                    sprintf(param_name, "%s%s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 1: 
                    sprintf(param_name, "%s %s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 2: 
                    sprintf(param_name, "%s  %s", prefix.c_str(), num_val.str().c_str());
                    break;
            }
            
            //printf("param_name = %s value = %f\n", param_name, value);
            res = obj->dspUI->SetValue(param_name, value); // Doesn't have any effect if name is unknown
        }
    // Standard parameter
    } else {
        float value = (av[0].a_type == A_LONG) ? (float)av[0].a_w.w_long : av[0].a_w.w_float;
        res = obj->dspUI->SetValue(name, value); // Doesn't have any effect if name is unknown
    }
    
    if (!res) {
        post("Unknown parameter : %s", (s)->s_name);
    }
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    t_faust* x = (t_faust*)newobject(faust_class);

    x->m_mute = false;

    x->dsp = new mydsp();
    x->dspUI = new mspUI();

    x->dsp->init(long(sys_getsr()));
    x->dsp->buildUserInterface(x->dspUI);

    x->args = (void**)calloc((x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2, sizeof(void*));

    /* Multi in */
    dsp_setup((t_pxobject*)x, x->dsp->getNumInputs());

    /* Multi out */
    for (int i = 0; i< x->dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }

    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
    return x;
}

/*--------------------------------------------------------------------------*/
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
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
				char param[256];
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
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
	dsp_free((t_pxobject*)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args) free(x->args);
}

/*--------------------------------------------------------------------------*/
t_int *faust_perform(t_int *w)
{
	t_faust* x = (t_faust*) (w[1]);
	long n = w[2];
	int offset = 3;
	AVOIDDENORMALS;
    if (x->m_mute) {
        float** outputs = ((float**)&w[offset+x->dsp->getNumInputs()]);
        // Write null buffers to outs
        for (int i = 0; i < x->dsp->getNumOutputs(); i++) {
             memset(outputs[i], 0, sizeof(float) * n);
        }
    } else {
        x->dsp->compute(n, ((float**)&w[offset]), ((float**)&w[offset+x->dsp->getNumInputs()]));
    }
	return (w + (x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2+1);
}

/*--------------------------------------------------------------------------*/
void  faust_dsp(t_faust* x, t_signal **sp, short* count)
{
	x->args[0] = x;
	x->args[1] = (void*)sp[0]->s_n;
	for (int i = 0; i<(x->dsp->getNumInputs()+x->dsp->getNumOutputs()); i++) {
		x->args[i+2] = sp[i]->s_vec;
    }
	dsp_addv(faust_perform, (x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2, x->args);
}

/*--------------------------------------------------------------------------*/
int main()
{
	setup((t_messlist**)&faust_class, (method)faust_new, (method)faust_free,
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	dsp* thedsp = new mydsp();
	mspUI dspUI;
 	thedsp->buildUserInterface(&dspUI);
  
	// Add the same method for every parameters and use the symbol as a selector
	// inside this method
	for (mspUI::iterator it = dspUI.begin(); it != dspUI.end(); ++it) {
		char* name = const_cast<char*>(it->second->GetName().c_str());
		addmess((method)faust_method, name, A_GIMME, 0);
	}

	addmess((method)faust_dsp, (char*)"dsp", A_CANT, 0);
	addmess((method)faust_assist, (char*)"assist", A_CANT, 0);
    addmess((method)faust_mute, (char*)"mute", A_GIMME, 0);
	dsp_initclass();
    
    post((char*)"Faust DSP object 32 bits v%s", EXTERNAL_VERSION);
    post((char*)"Copyright (c) 2012 Grame");
    Max_Meta1 meta1;
    mydsp::metadata(&meta1);
    if (meta1.fCount > 0) {
        Max_Meta2 meta2;
        post("------------------------------");
        mydsp::metadata(&meta2);
        post("------------------------------");
    }

    delete(thedsp);
	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/




