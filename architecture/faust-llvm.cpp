
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2013 GRAME, Centre National de Creation Musicale
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

#ifndef  __mydsp_H__
#define  __mydsp_H__

#include <unistd.h> 

#include <libgen.h>
#include <math.h>
#include <iostream>
#include <vector>
 
#ifndef __misc__
#define __misc__

#include <map>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
};

#endif

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int	lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }
inline int 	int2pow2(int x)		{ int r=0; while ((1<<r)<x) r++; return r; }

long lopt(char *argv[], const char *name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

char* lopts(char *argv[], const char *name, char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}
#endif

#ifndef FAUST_PUI_H
#define FAUST_PUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

 public:

	UI() {}

	virtual ~UI() {}

    // -- widget's layouts

    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

	// -- metadata declarations

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
};

#endif

/*******************************************************************************
 * PUI : Faust User Interface
 * This class print argurments given to calls to UI methods.
 ******************************************************************************/

class PrintUI : public UI
{

 public:

	PrintUI() {}

	virtual ~PrintUI() {}

    // -- widget's layouts

    virtual void openTabBox(const char* label)
    {
        printf("openTabBox label : %s\n", label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        printf("openHorizontalBox label : %s\n", label);
    }
    virtual void openVerticalBox(const char* label)
    {
        printf("openVerticalBox label : %s\n", label);
    }
    virtual void closeBox()
    {
        printf("closeBox\n");
    }

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        printf("addButton label : %s\n", label);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        printf("addCheckButton label : %s\n", label);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printf("addVerticalSlider label : %s init : %f min : %f max : %f step : %f\n", label, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printf("addHorizontalSlider label : %s init : %f min : %f max : %f step : %f\n", label, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        printf("addNumEntry label : %s init : %f min : %f max : %f step : %f\n", label, init, min, max, step);
    }

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
    {
        printf("addHorizontalBargraph label : %s min : %f max : %f\n", label, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        printf("addVerticalBargraph label : %s min : %f max : %f\n", label, min, max);
    }

	// -- metadata declarations

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        printf("declare key : %s val : %s\n", key, val);
    }
    
};

#endif

/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;

//----------------------------------------------------------------
//  signal processor definition
//----------------------------------------------------------------

class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
};

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

/******************************************************************************
*******************************************************************************

						An abstraction layer over audio layer

*******************************************************************************
*******************************************************************************/

#ifndef __audio__
#define __audio__
			
class dsp;
class audio {
 public:
			 audio() {}
	virtual ~audio() {}
	
	virtual bool init(const char* name, dsp*)	= 0;
	virtual bool start()						= 0;
	virtual void stop()							= 0;
};
					
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class audio_simulator : public audio {

 private:
 
    dsp* fDSP;
    
    long fSampleRate;
    long fBufferSize; 
    
    FAUSTFLOAT** fInChannel;
    FAUSTFLOAT** fOutChannel;  
    
    int fCount;
    
 public:
			 audio_simulator(int count = 10):fCount(count) {}
	virtual ~audio_simulator() 
    {
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            delete[] fInChannel[i];
        }
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
           delete[] fOutChannel[i];
        }
        
        delete [] fInChannel;
        delete [] fOutChannel;
    }
	
	virtual bool init(const char* name, dsp* dsp)
    {
        fDSP = dsp;
        fBufferSize = 512;
        fSampleRate = 48000;
        
        fDSP->init(fSampleRate);
        
        fInChannel = new FAUSTFLOAT*[fDSP->getNumInputs()];
        fOutChannel = new FAUSTFLOAT*[fDSP->getNumOutputs()];
        
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new FAUSTFLOAT[fBufferSize];
            memset(fInChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
        }
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new FAUSTFLOAT[fBufferSize];
            memset(fOutChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
        }
        return true;
    }
    virtual bool start()
    {
        while (--fCount > 0) {
            printf("Render one buffer\n");
            render();
            usleep(100000);
        }
        return true;
    }
	virtual void stop()
    {}
    
    void render()
    {
        fDSP->compute(fBufferSize, fInChannel, fOutChannel);
        if (fDSP->getNumInputs() > 0) {
            printf("First in = %f \n", fInChannel[0][0]);
        }
        if (fDSP->getNumOutputs() > 0) {
            printf("First out = %f \n", fOutChannel[0][0]);
        }
    }
    
};
					
#include "faust/dsp/llvm-dsp.h"
#include <string>

#define BUFFER_TO_RENDER 10
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    char jackname[256];
	snprintf(jackname, 255, "%s", basename(argv[0]));
    std::string error_msg;
    
    if (argc < 2) {
        printf("faust-llvm 'foo.dsp'\n");
        exit(-1);
    }
    
    //printf("argv[1]%
    
    // Error check to add....
    llvm_dsp_factory* factory = createDSPFactoryFromFile(argv[1], argc-2, (const char**)&argv[2], "", error_msg, 3);
     
    /*
    // Another possibility by directly giving the Faust program as a string
    
    // Additional parameters given to the compiler
    int argc1 = 3;
    const char* argv1[argc];
    argv1[0] = "-vec";
    argv1[1] = "-lv";
    argv1[2] = " 1";
    
    // Faust program
    std::string faust_program = "process = +;";
    
    llvm_dsp_factory* factory = createDSPFactoryFromString(argc1, argv1, "test", faust_program, "", error_msg, 3);
    */
    
    dsp* DSP = createDSPInstance(factory);
  
	PrintUI interface;
	DSP->buildUserInterface(&interface);

	audio_simulator audio(BUFFER_TO_RENDER);
	audio.init(jackname, DSP);
	audio.start();
    // Render BUFFER_TO_RENDER buffers...
	audio.stop();
	return 0;
} 

#endif

/*
Compilation :

g++ faust-llvm.cpp /usr/local/lib/libfaust.a `llvm-config --ldflags --libs all` -lcrypto -lz -lcurses -o faust-llvm-static
g++ faust-llvm.cpp -lfaust -L /usr/local/lib/faust `llvm-config --ldflags --libs all` -lcrypto -lz -lcurses -o faust-llvm-shared

Usage (possibly with explicit parameters given to the compiler) : 

./faust-llvm-static karplus.dsp
./faust-llvm-static -vec -lv 1 karplus.dsp
./faust-llvm-static -double -vec -lv 0 -vs 64 karplus.dsp
*/

