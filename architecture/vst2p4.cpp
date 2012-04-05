/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2007-2011 Remy Muller & Julius Smith
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
    	* Neither the name of Remy Muller or Julius Smith or of its 
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
 * VST-2.4 wrapper for the FAUST language. 
 *
 * Usage: faust -a vst2p4.cpp myfaustprog.dsp
 *
 * By Julius Smith (http://ccrma.stanford.edu/~jos/), based on 
 * vst.cpp by remy muller remy.muller@ircam.fr 
 * http://www.smartelectronix.com/~mdsp/.
 * Essentially, vst.cpp was edited to look more like the "again" 
 * programming sample that comes with the VST-2.4 SDK from Steinberg.
 *
 * NOTES:
 *  Relies on automatically generated slider GUI for VST plugins.
 *   - Horizontal and vertical sliders mapped to "vstSlider"
 *   - Numeric Entries similarly converted to "vstSlider"
 *   - No support for bar graphs or additional numeric and text displays
 *   - Tested on the Muse Receptor Pro 1.0, System Version 1.6.20070717,
 *     using Visual C++ 2008 Express Edition 
 *     (part of the Microsoft Visual Studio 2008, Beta 2)
 *   - Reference: 
 * http://ccrma.stanford.edu/realsimple/faust/Generating_VST_Plugin_Faust.html
 *
 * FAUST 
 * Copyright (C) 2003-2007 GRAME, Centre National de Creation Musicale
 * http://www.grame.fr/			     
 *
 ********************************************************************/

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
#include <map>
#include <cstring>
#include <cmath>

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

struct Meta : std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
};
		
// abs is now predefined
//template<typename T> T abs (T a) { return (a<T(0)) ? -a : a; }

inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x) { int r=0; while ((1<<r)<x) r++; return r; }

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
		
  virtual void addButton(const char* label, float* zone) = 0;
  virtual void addToggleButton(const char* label, float* zone) = 0;
  virtual void addCheckButton(const char* label, float* zone) = 0;
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
  virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
  virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
		
  virtual void openFrameBox(const char* label) = 0;
  virtual void openTabBox(const char* label) = 0;
  virtual void openHorizontalBox(const char* label) = 0;
  virtual void openVerticalBox(const char* label) = 0;
  virtual void closeBox() = 0;
		
  virtual void run() {};
		
  void stop()		{ fStopped = true; }
  bool stopped()	{ return fStopped; }

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
//  Base dsp class for this architecture
//----------------------------------------------------------------
			
class dsp {

protected:
	 
  int fSamplingFreq;
		
public:
	 
  dsp() {}
  virtual ~dsp() {}
  virtual int getNumInputs() = 0;
  virtual int getNumOutputs() = 0;
  virtual void buildUserInterface(UI* interface) = 0;
  virtual void init(int samplingRate) = 0;
  virtual void compute(int len, float** inputs, float** outputs) = 0;
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

private:
  mydsp*    dsp;
  vstUI*    dspUI;
  char      programName[kVstMaxProgNameLen + 1];
  Meta      meta;

public:
  Faust(audioMasterCallback audioMaster, mydsp* dspi, vstUI* dspUIi);
  virtual ~Faust();

  virtual void	processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);

  virtual void	setProgramName(char *name);
  virtual void	getProgramName(char *name);

  virtual void	setParameter(VstInt32 index, float value);
  virtual float	getParameter(VstInt32 index);
  virtual void	getParameterLabel(VstInt32 index, char *label);
  virtual void	getParameterDisplay(VstInt32 index, char *text);
  virtual void	getParameterName(VstInt32 index, char *text);

  virtual void	setSampleRate(float sampleRate);

  virtual bool	getEffectName (char* name);
  virtual bool	getVendorString (char* text);
  virtual bool	getProductString (char* text);
  virtual VstInt32 getVendorVersion ();

  virtual bool	getInputProperties (VstInt32 index, VstPinProperties* properties);
  virtual bool	getOutputProperties (VstInt32 index, VstPinProperties* properties);
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
  vstUIObject(const char* label, float* zone):fLabel(label),fZone(zone) {}
  virtual ~vstUIObject() {}

  virtual void  GetName(char *text){std::strcpy(text,fLabel.c_str());}
  virtual void  SetValue(double f) {*fZone = range(0.0f,1.0f,(float)f);}
  virtual float GetValue() {return *fZone;}
  virtual void  GetDisplay(char *text){std::sprintf(text,"%f",*fZone);}
  virtual long  GetID() 
  {	/* returns the sum of all the ASCII characters  contained in the parameter's label */
    unsigned int i;
    long acc;
    for(i=0,acc = 0;i<fLabel.length();i++) acc += (fLabel.c_str())[i];
    return acc;
  }
};

/*--------------------------------------------------------------------------*/
class vstToggleButton : public vstUIObject {
	
public:	
	
  vstToggleButton(const char* label, float* zone):vstUIObject(label,zone) {}
  virtual ~vstToggleButton() {}
  virtual float GetValue() {return *fZone;}
  virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}				
  virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}
};

/*--------------------------------------------------------------------------*/
class vstCheckButton : public vstUIObject {
	
public:
	
  vstCheckButton(const char* label, float* zone):vstUIObject(label,zone) {}
  virtual ~vstCheckButton() {}
  virtual float GetValue() {return *fZone;}
  virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}
  virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}		
};

/*--------------------------------------------------------------------------*/
class vstButton : public vstUIObject {
	
public:
	
  vstButton(const char* label, float* zone):vstUIObject(label,zone) {}
  virtual ~vstButton() {}		
  virtual float GetValue() {return *fZone;}
  virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}		
  virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}
};

/*--------------------------------------------------------------------------*/
class vstSlider : public vstUIObject {

private:
	
  float fInit;
  float fMin;
  float fMax;
  float fStep;
	
public:	
	
  vstSlider(const char* label, float* zone, float init, float min, float max, float step)
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
		
  void addButton(const char* label, float* zone) {fUITable.push_back(new vstButton(label, zone));}
		
  void addToggleButton(const char* label, float* zone) {fUITable.push_back(new vstToggleButton(label, zone));}
		
  void addCheckButton(const char* label, float* zone) {fUITable.push_back(new vstCheckButton(label, zone));}
		
  void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
  { 	
    fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
  }
		
  void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
  {
    fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
  }
		
  void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
  { /* Number entries converted to horizontal sliders */
    fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
  }
		
  void openFrameBox(const char* label) {}
  void openTabBox(const char* label) {}
  void openHorizontalBox(const char* label) {}
  void openVerticalBox(const char* label) {}
  void closeBox() {}
		
  void  SetValue(VstInt32 index, double f) {assert(index<fUITable.size()); fUITable[index]->SetValue(f);}
  float GetValue(VstInt32 index) {assert(index<fUITable.size()); return fUITable[index]->GetValue();}
  void  GetDisplay(VstInt32 index, char *text) {assert(index<fUITable.size()); fUITable[index]->GetDisplay(text);}
  void  GetName(VstInt32 index, char *text) {assert(index<fUITable.size()); fUITable[index]->GetName(text);}
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
  void addNumDisplay(const char* label, float* zone, int precision){}
  void addTextDisplay(const char* label, float* zone, char* names[], float min, float max){}
  void addHorizontalBargraph(const char* label, float* zone, float min, float max){}
  void addVerticalBargraph(const char* label, float* zone, float min, float max){}
};

//-----------------------------------------------------------------------------
#define NUM_PROGRAMS 0

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
// The dsp and its UI need to be allocated now because
// AudioEffectX wants the no. parameters available as an instance argument:
  mydsp* dspi = new mydsp();
  vstUI* dspUIi = new vstUI(); 
  dspi->buildUserInterface(dspUIi);
  return new Faust(audioMaster,dspi,dspUIi);
}

Faust::Faust(audioMasterCallback audioMaster, mydsp* dspi, vstUI* dspUIi)
  : AudioEffectX(audioMaster, NUM_PROGRAMS, dspUIi->GetNumParams())
{
  // Copy the pointers to dsp and dspUI instances and take them over 
  // (we'll also deallocate):
  dsp = dspi;
  dspUI = dspUIi;
  dsp->init(long(getSampleRate()));
  meta["name"] = "FaustFx";
  mydsp::metadata(&meta);
  setNumInputs(dsp->getNumInputs());		
  setNumOutputs(dsp->getNumOutputs());		
  setUniqueID(dspUI->makeID());					
  canProcessReplacing();

  vst_strncpy(programName, "Default", kVstMaxProgNameLen); // default program name
}

//----------------------------------------------------------------------------
Faust::~Faust()
{
  if (dsp) delete dsp;
  if (dspUI) delete dspUI;
}

//-------------------------------------------------------------------------------------------------------
void Faust::setProgramName (char* name)
{
  // this template does not use programs yet - just say "Default":
  vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------
void Faust::getProgramName(char *name)
{
  vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------
void Faust::setParameter(VstInt32 index, float value)
{
  if(index<numParams)
    dspUI->SetValue(index,value);
}

//-----------------------------------------------------------------------------
float Faust::getParameter(VstInt32 index)
{
  if(index<numParams)
    return dspUI->GetValue(index);
  else
    return 0.0f;
}
//-----------------------------------------------------------------------------
void Faust::getParameterName(VstInt32 index, char *label)
{
  if(index<numParams)
    dspUI->GetName(index,label); // parameter name, including units
  else
    vst_strncpy (label, "IndexOutOfRange", kVstMaxParamStrLen);
}
//-----------------------------------------------------------------------------
void Faust::getParameterDisplay(VstInt32 index, char *text)
{
  if(index<numParams)
    dspUI->GetDisplay(index,text); // displayed float value as text
  else
    vst_strncpy (text, "IndexOutOfRange", kVstMaxParamStrLen);
}
//-----------------------------------------------------------------------------
void Faust::getParameterLabel(VstInt32 index, char *label)
{
  vst_strncpy (label, "", kVstMaxParamStrLen); // parameter units in Name
}

//-----------------------------------------------------------------------------
void Faust::setSampleRate(float sampleRate)
{
  // allways call this
  AudioEffect::setSampleRate(sampleRate);
  dsp->init(long(getSampleRate()));
}

//-----------------------------------------------------------------------------------------
bool Faust::getEffectName (char* text)
{
  vst_strncpy (text, meta["name"].c_str(), kVstMaxProductStrLen);
  return true;
}

//-----------------------------------------------------------------------------------------
bool Faust::getVendorString (char* text)
{
  if (meta.count("author") > 0) {
    vst_strncpy (text, meta["author"].c_str(), kVstMaxVendorStrLen);
    return true;
  } else {
    return false;
  }
}

//-----------------------------------------------------------------------------------------
bool Faust::getProductString (char* text)
{
  vst_strncpy (text, meta["name"].c_str(), kVstMaxProductStrLen);
  return true;
}

//-----------------------------------------------------------------------------------------
VstInt32 Faust::getVendorVersion ()
{ 
	return 1000; 
}

//-----------------------------------------------------------------------------
void Faust::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames)
{
    AVOIDDENORMALS;
    dsp->compute(sampleFrames, inputs, outputs);
}

//-----------------------------------------------------------------------------------------
bool Faust::getInputProperties (VstInt32 index, VstPinProperties* properties)
{
  if(index>=0 && index<dsp->getNumInputs())
  {
    sprintf (properties->label, "Grame Faust DSP input: %d",index);
    sprintf (properties->shortLabel, "In %d",index);
    properties->flags = kVstPinIsActive;
    if (dsp->getNumInputs() == 2) {
      properties->flags |= kVstPinIsStereo;
    }
    return true;
  }
  else
    return false;
}

//-----------------------------------------------------------------------------------------
bool Faust::getOutputProperties (VstInt32 index, VstPinProperties* properties)
{
  if(index>=0 && index<dsp->getNumOutputs())
  {
    sprintf (properties->label, "Grame Faust DSP output: %d",index);
    sprintf (properties->shortLabel, "Out %d",index);
    properties->flags = kVstPinIsActive;
    if (dsp->getNumOutputs() == 2) {
      properties->flags |= kVstPinIsStereo;
    }
    return true;
  }
  else
    return false;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/


