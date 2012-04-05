/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2004-2011 Remy Muller
	All rights reserved.
    ----------------------------BSD License------------------------------
	Redistribution and use in source and binary forms, with or without 
	modification, are permitted provided that the following conditions 
	are met:

    	* Redistributions of source code must retain the above copyright 
		  notice, this list of conditions and the following disclaimer.
    	* Redistributions in binary form must reproduce the above 
		  copyright notice, this list of conditions and the following 
		  disclaimer in the documentation and/or other materials provided 
		  with the distribution.
    	* Neither the name of Remy Muller nor the names of its 
		  contributors may be used to endorse or promote products derived 
		  from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
	COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
	OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------VST SDK----------------------------------
	In order to compile a VST (TM) plugin with this architecture file 
	you will need the proprietary VST SDK from Steinberg. Please check 
	the corresponding license.

 ************************************************************************
 ************************************************************************/


/********************************************************************
 * VST wrapper for the FAUST language. 
 * Author: remy muller remy.muller@ircam.fr           
 * http://www.smartelectronix.com/~mdsp/            
 *
 * FAUST 
 * Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
 * http://www.grame.fr/                      
 * 
 ********************************************************************/

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
//#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <math.h>

using namespace std ;

// There is a bug with powf() when cross compiling with mingw
// the following macro avoid the problem
#ifdef WIN32
#define powf(x,y) pow(x,y)
#define expf(x) exp(x)
#endif

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

struct Meta
{
    void declare (const char* key, const char* value) {  }
};
	
	

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }


/******************************************************************************
*******************************************************************************
*
*							       VECTOR INTRINSICS
*
*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************
*
*								USER INTERFACE
*
*******************************************************************************
*******************************************************************************/

class UI
{
    bool	fStopped;
		
public:
			
    UI() : fStopped(false) {}
    virtual ~UI() {}
		
    virtual void addButton(char* label, float* zone) = 0;
    virtual void addToggleButton(char* label, float* zone) = 0;
    virtual void addCheckButton(char* label, float* zone) = 0;
    virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	virtual void addNumDisplay(char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;
		
    virtual void openFrameBox(char* label) = 0;
    virtual void openTabBox(char* label) = 0;
    virtual void openHorizontalBox(char* label) = 0;
    virtual void openVerticalBox(char* label) = 0;
    virtual void closeBox() = 0;
		
    virtual void run() {};
		
    void stop()		{ fStopped = true; }
    bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};


/******************************************************************************
*******************************************************************************
*
*								FAUST DSP
*
*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------
//  definition du processeur de signal
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
    virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		
/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
/******************************************************************************
 *
 * VST wrapper
 * 
 ******************************************************************************/

#include "audioeffectx.h" 

class vstUI;

class Faust : public AudioEffectX
{
public:
	Faust(audioMasterCallback audioMaster);
	virtual ~Faust();

	virtual void	process(float **inputs, float **outputs, long sampleFrames);
	virtual void	processReplacing(float **inputs, float **outputs, long sampleFrames);

	virtual void	setProgramName(char *name);
	virtual void	setProgram(long index);
	virtual void	getProgramName(char *name);

	virtual void	setParameter(long index, float value);
	virtual float	getParameter(long index);
	virtual void	getParameterLabel(long index, char *label);
	virtual void	getParameterDisplay(long index, char *text);
	virtual void	getParameterName(long index, char *text);

	virtual void	setSampleRate(float sampleRate);

	virtual bool	getEffectName (char* name);
	virtual bool	getVendorString (char* text);
	virtual bool	getProductString (char* text);

	virtual bool	getInputProperties (long index, VstPinProperties* properties);
	virtual bool	getOutputProperties (long index, VstPinProperties* properties);

private:
	mydsp*	dsp;
	vstUI*	dspUI;
};

/*--------------------------------------------------------------------------*/
class vstUIObject {
protected:
    string fLabel;
    float* fZone;
		
    float range(float min, float max, float val) 
		{	// VST parameters are normalized in the range [0;1]
			val = min + val * (max - min);
			return (val < min) ? min : (val > max) ? max : val;
		}
	 
public:			
    vstUIObject(char* label, float* zone):fLabel(label),fZone(zone) {}
    virtual ~vstUIObject() {}

    virtual void  GetName(char *text){std::strcpy(text,fLabel.c_str());}
    virtual void  SetValue(double f) {*fZone = range(0.0f,1.0f,(float)f);}
    virtual float GetValue() {return *fZone;}
    virtual void  GetDisplay(char *text){std::sprintf(text,"%f",*fZone);}
    virtual long  GetID() 
		{	/* returns the sum of all the ASCII characters  contained in the parameter's label */
			int i;
			long acc;
			for(i=0,acc = 0;i<fLabel.length();i++) acc += (fLabel.c_str())[i];
			return acc;
		}
};

/*--------------------------------------------------------------------------*/
class vstToggleButton : public vstUIObject {
	
public:	
	
    vstToggleButton(char* label, float* zone):vstUIObject(label,zone) {}
    virtual ~vstToggleButton() {}
    virtual float GetValue() {return *fZone;}
    virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}				
    virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}
};

/*--------------------------------------------------------------------------*/
class vstCheckButton : public vstUIObject {
	
public:
	
    vstCheckButton(char* label, float* zone):vstUIObject(label,zone) {}	
    virtual ~vstCheckButton() {}
    virtual float GetValue() {return *fZone;}
    virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}
    virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}		
};

/*--------------------------------------------------------------------------*/
class vstButton : public vstUIObject {
	
public:
	
    vstButton(char* label, float* zone):vstUIObject(label,zone) {}
    virtual ~vstButton() {}		
    virtual float GetValue() {return *fZone;}
    virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}		
    virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}
};

/*--------------------------------------------------------------------------*/
class vstSlider : public vstUIObject{

private:
	
    float fInit;
    float fMin;
    float fMax;
    float fStep;
	
public:	
	
    vstSlider(char* label, float* zone, float init, float min, float max, float step)
        :vstUIObject(label,zone), fInit(init), fMin(min), fMax(max),fStep(step) {}
    virtual ~vstSlider() {}	

    virtual float GetValue() {return (*fZone-fMin)/(fMax-fMin);}	// normalize
    virtual void SetValue(double f) {*fZone = range(fMin,fMax,(float)f);} // expand
};

/*--------------------------------------------------------------------------*/
class vstUI : public UI
{
private:
	
    vector<vstUIObject*> fUITable;
		
public:
			
    vstUI(){}
    virtual ~vstUI() 
		{
			for (vector<vstUIObject*>::iterator iter = fUITable.begin(); iter != fUITable.end(); iter++) delete *iter;
   		}
		
    void addButton(char* label, float* zone) {fUITable.push_back(new vstButton(label, zone));}
		
    void addToggleButton(char* label, float* zone) {fUITable.push_back(new vstToggleButton(label, zone));}
		
    void addCheckButton(char* label, float* zone) {fUITable.push_back(new vstCheckButton(label, zone));}
		
    void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) 
		{ 	
			fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
		}
		
    void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) 
		{
			fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
		}
		
    void addNumEntry(char* label, float* zone, float init, float min, float max, float step) {}
		
    void openFrameBox(char* label) {}
    void openTabBox(char* label) {}
    void openHorizontalBox(char* label) {}
    void openVerticalBox(char* label) {}
    void closeBox() {}
		
    void  SetValue(int index, double f) {assert(index<fUITable.size()); fUITable[index]->SetValue(f);}
    float GetValue(long index)	{assert(index<fUITable.size()); return fUITable[index]->GetValue();}
    void  GetDisplay(long index, char *text) {assert(index<fUITable.size()); fUITable[index]->GetDisplay(text);}
    void  GetName(long index, char *text) {assert(index<fUITable.size()); fUITable[index]->GetName(text);}
    long  GetNumParams() {return fUITable.size();}

    long  makeID()
        /* Creates a (unique?)id by summing all the parameter's labels, 
         * then wrapping it in the range [0;maxNumberOfId] and adding 
         * this number to the offset made by the Four Character ID: 'FAUS'
         */
		{   
			const long maxNumberOfId = 128;
			long baseid = 'FAUS';
            long id=0;
			for(int i=0;i<fUITable.size();i++) id += fUITable[i]->GetID();
			return baseid + id % maxNumberOfId;
		}
		
	// To be implemented
	void addNumDisplay(char* label, float* zone, int precision){}
	void addTextDisplay(char* label, float* zone, char* names[], float min, float max){}
	void addHorizontalBargraph(char* label, float* zone, float min, float max){}
	void addVerticalBargraph(char* label, float* zone, float min, float max){}
};

//-----------------------------------------------------------------------------
#define NUM_PROGRAMS 0
#define FAKE_NUM_PARAMS 16

Faust::Faust(audioMasterCallback audioMaster)
    :AudioEffectX(audioMaster, NUM_PROGRAMS,FAKE_NUM_PARAMS)
{
	dsp = new mydsp();
	dspUI= new vstUI();
	dsp->buildUserInterface(dspUI);
	dsp->init(long(getSampleRate()));
	
	/* we override here the fake number of parameters with the real one*/
	this->cEffect.numParams = this->numParams = dspUI->GetNumParams();
	  
	setNumInputs(dsp->getNumInputs());		
	setNumOutputs(dsp->getNumOutputs());		
	setUniqueID(dspUI->makeID());					
	canProcessReplacing();//?
}

//----------------------------------------------------------------------------
Faust::~Faust()
{
	if (dsp) delete dsp;
	if (dspUI) delete dspUI;
}

//-----------------------------------------------------------------------------
void Faust::setParameter(long index, float value)
{
    if(index<numParams)
        dspUI->SetValue(index,value);
}
//-----------------------------------------------------------------------------
float Faust::getParameter(long index)
{
    if(index<numParams)
        return dspUI->GetValue(index);
    else
        return 0.0f;
}
//-----------------------------------------------------------------------------
void Faust::getParameterName(long index, char *label)
{
    if(index<numParams)
        dspUI->GetName(index,label);
    else
        strcpy(label,"");
}
//-----------------------------------------------------------------------------
void Faust::getParameterDisplay(long index, char *text)
{
    if(index<numParams)
        dspUI->GetDisplay(index,text);
    else
        strcpy(text,"");
}
//-----------------------------------------------------------------------------
void Faust::getParameterLabel(long index, char *label)
{
	strcpy(label,"");
}

//-----------------------------------------------------------------------------
void Faust::setProgramName(char *name)
{
	// this template does not use programs yet
}
//-----------------------------------------------------------------------------
void Faust::setProgram(long index)
{
	// this template does not use programs yet
};
//-----------------------------------------------------------------------------
void Faust::getProgramName(char *name)
{
	// this template does not use programs yet
	strcpy(name, "");
}
//-----------------------------------------------------------------------------
void Faust::process(float **inputs, float **outputs, long sampleFrames)
{
	AVOIDDENORMALS;
    dsp->compute(sampleFrames, inputs, outputs);
}
//-----------------------------------------------------------------------------
void Faust::processReplacing(float **inputs, float **outputs, long sampleFrames)
{
	AVOIDDENORMALS;
    dsp->compute(sampleFrames, inputs, outputs);
}
//-----------------------------------------------------------------------------
void Faust::setSampleRate(float sampleRate)
{
	// allways call this
	AudioEffect::setSampleRate(sampleRate);
	dsp->init(long(getSampleRate()));
}
//-----------------------------------------------------------------------------------------
bool Faust::getEffectName (char* name)
{
	return false;
}
//-----------------------------------------------------------------------------------------
bool Faust::getVendorString (char* text)
{
	strcpy (text, "Grame");
	return true;
}
//-----------------------------------------------------------------------------------------
bool Faust::getProductString (char* text)
{
	strcpy (text, "Faust DSP");
	return true;
}
//-----------------------------------------------------------------------------------------
bool Faust::getInputProperties (long index, VstPinProperties* properties)
{
    if(index>=0 && index<dsp->getNumOutputs())
    {
        sprintf (properties->label	  , "Grame Faust DSP: %d",index);
        sprintf (properties->shortLabel, "Faust: %d",index);
        properties->flags = kVstPinIsActive;			
        return true;
    }
    else
        return false;
}
//-----------------------------------------------------------------------------------------
bool Faust::getOutputProperties (long index, VstPinProperties* properties)
{
    if(index>=0 && index<dsp->getNumInputs())
    {
        sprintf (properties->label	  , "Grame Faust DSP: %d",index);
        sprintf (properties->shortLabel, "Faust: %d",index);
        properties->flags = kVstPinIsActive;			
        return true;
    }
    else
        return false;
}

/*****************************************************************************
 *
 * DLL Entry Point
 *
 ******************************************************************************/
bool oome = false;

#if MAC
#pragma export on
#endif

// prototype of the export function main
#if BEOS
#define main main_plugin
extern "C" __declspec(dllexport) AEffect *main_plugin (audioMasterCallback audioMaster);

#elif MACX
#define main main_macho
extern "C" AEffect *main_macho (audioMasterCallback audioMaster);

#else
AEffect *main (audioMasterCallback audioMaster);
#endif

AEffect *main (audioMasterCallback audioMaster)
{
	// get vst version
	if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
		return 0;  // old version

	AudioEffect* effect = new Faust(audioMaster);
	if (!effect)
		return 0;
	if (oome)
	{
		delete effect;
		return 0;
	}
	return effect->getAeffect ();
}

#if MAC
#pragma export off
#endif

#if WIN32
#include <windows.h>
void* hInstance;
BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	hInstance = hInst;
	return 1;
}
#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/


