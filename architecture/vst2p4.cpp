/********************************************************************
 * VST-2.4 wrapper for the FAUST language. 
 *
 * Usage: faust -a vst2p4.cpp myfaustprog.dsp
 *
 * By Julius Smith (http://ccrma.stanford.edu/~jos/), based on 
 * vst.cpp by r�y muller remy.muller@ircam.fr 
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

struct Meta
{
    void declare (const char* key, const char* value) {  }
};
	
	
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

inline int	max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int	max (int a, int b)		{ return (a>b) ? a : b; }

inline long	max (long a, long b)		{ return (a>b) ? a : b; }
inline long	max (int a, long b)		{ return (a>b) ? a : b; }
inline long	max (long a, int b)		{ return (a>b) ? a : b; }

inline float	max (float a, float b)		{ return (a>b) ? a : b; }
inline float	max (int a, float b)		{ return (a>b) ? a : b; }
inline float	max (float a, int b)		{ return (a>b) ? a : b; }
inline float	max (long a, float b)		{ return (a>b) ? a : b; }
inline float	max (float a, long b)		{ return (a>b) ? a : b; }

inline double	max (double a, double b)	{ return (a>b) ? a : b; }
inline double	max (int a, double b)		{ return (a>b) ? a : b; }
inline double	max (double a, int b)		{ return (a>b) ? a : b; }
inline double	max (long a, double b)		{ return (a>b) ? a : b; }
inline double	max (double a, long b)		{ return (a>b) ? a : b; }
inline double	max (float a, double b)		{ return (a>b) ? a : b; }
inline double	max (double a, float b)		{ return (a>b) ? a : b; }

inline int	min (int a, int b)		{ return (a<b) ? a : b; }

inline long	min (long a, long b)		{ return (a<b) ? a : b; }
inline long	min (int a, long b)		{ return (a<b) ? a : b; }
inline long	min (long a, int b)		{ return (a<b) ? a : b; }

inline float	min (float a, float b)		{ return (a<b) ? a : b; }
inline float	min (int a, float b)		{ return (a<b) ? a : b; }
inline float	min (float a, int b)		{ return (a<b) ? a : b; }
inline float	min (long a, float b)		{ return (a<b) ? a : b; }
inline float	min (float a, long b)		{ return (a<b) ? a : b; }

inline double	min (double a, double b)	{ return (a<b) ? a : b; }
inline double	min (int a, double b)		{ return (a<b) ? a : b; }
inline double	min (double a, int b)		{ return (a<b) ? a : b; }
inline double	min (long a, double b)		{ return (a<b) ? a : b; }
inline double	min (double a, long b)		{ return (a<b) ? a : b; }
inline double	min (float a, double b)		{ return (a<b) ? a : b; }
inline double	min (double a, float b)		{ return (a<b) ? a : b; }
		
#endif

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
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

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

//----------------------------------------------------------------
//  Faust-generated dsp class 
//----------------------------------------------------------------
			
<<includeclass>>


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

private:
  mydsp*	dsp;
  vstUI*	dspUI;
  char programName[kVstMaxProgNameLen + 1];
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
    unsigned int i;
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
		
  void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
  { /* Number entries converted to horizontal sliders */
    fUITable.push_back(new vstSlider(label, zone, init, min, max, step));
  }
		
  void openFrameBox(char* label) {}
  void openTabBox(char* label) {}
  void openHorizontalBox(char* label) {}
  void openVerticalBox(char* label) {}
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
  void addNumDisplay(char* label, float* zone, int precision){}
  void addTextDisplay(char* label, float* zone, char* names[], float min, float max){}
  void addHorizontalBargraph(char* label, float* zone, float min, float max){}
  void addVerticalBargraph(char* label, float* zone, float min, float max){}
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
  :AudioEffectX(audioMaster, NUM_PROGRAMS,dspUIi->GetNumParams())
{
  // Copy the pointers to dsp and dspUI instances and take them over 
  // (we'll also deallocate):
  dsp = dspi;
  dspUI = dspUIi;
  dsp->init(long(getSampleRate()));
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
bool Faust::getEffectName (char* name)
{
  return false;
}

//-----------------------------------------------------------------------------------------
bool Faust::getVendorString (char* text)
{
  vst_strncpy (text, "Vendor String goes here", kVstMaxVendorStrLen);
  return true;
}

//-----------------------------------------------------------------------------------------
bool Faust::getProductString (char* text)
{
  vst_strncpy (text, "Product String goes here", kVstMaxProductStrLen);
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
