/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2011 Travis Skare
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

    EXCEPTION : As a special exception, you may create a larger work that 
    contains this FAUST architecture section and distribute  
    that work under terms of your choice, so long as that this FAUST 
    architecture section is not modified. 

 ************************************************************************
 ************************************************************************/

// Faust -> Alchemy -> ActionScript C++ Architecture File

#include "AS3.h"
// math.h is needed for many faust examples, so include it.
// otherwise we have to hand-edit c++.
#include "math.h" 

#ifdef __GNUC__

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }
#else 
#endif
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

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{

public:
	bool fStopped;
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void run() = 0;
	
	void stop()	{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};

////// Implementation of UI

// Faust UI hookup is straightforward
// We subclass from UI and then these methods will get called by compiled
// Faust which assembles controls. We handle all UI as needed, and when
// things changed we need to set *zone=(some value).
// This is a little more complicated when jumping between alchemy/script.
// So rather than deal with marshalling pointers, just cheat and use an int:pointer map.
// NOTE: I should have used an STL map but that wasn't working back when I used gcc.
// I'll investigate since that would clean up the code quite a bit.

// upper bound on number of controls
#define MAX_CONTROLS 25
// map of unique ui control id to a float* where faust reads the corresponding value.
static float* uidToZone[MAX_CONTROLS];
// Counter that assigns control IDs.
static int uiMap_id = 0;

// I wasn't able to properly thunk the UI actionscrpit methods to C.
// Since we know the complete UI at the time of creation, a collection of
// ui creation info is passed back from faust_init, and actionscript
// can read it and create the UI.
// This is a little messy and was done last-minute.
const int TYPE_BUTTON = 0;
const int TYPE_TOGGLE = 1;
const int TYPE_SLIDER = 2;
// max length for a  label - more than 50 chars will get cut.
#define LABEL_LEN 50
struct uiElemInfo {
  int type;
  int id;
  char label[LABEL_LEN+1];
  float min;
  float max;
  float init;
  float step;
};
uiElemInfo uielems[MAX_CONTROLS];
static int uielems_size = 0;

// todo: stdio.h has strncpy, I just got paranoid about extra includes making the code bigger :)
void strcopy(char *src, char *dst) {
  dst[LABEL_LEN] = '\0';
  for (int i = 0; i < LABEL_LEN; ++i) {
    if (0 == (dst[i] = src[i])) return;
  }
}

void BuildUIArray(AS3_Val &array) {
  for (int i = 0; i < uielems_size; ++i) {
    AS3_Val result = AS3_Object( "type:AS3ValType,id:AS3ValType,label:AS3ValType,min:AS3ValType,max:AS3ValType,init:AS3ValType,step:AS3ValType",
		AS3_Int(uielems[i].type),
		AS3_Int(uielems[i].id),
		AS3_String(uielems[i].label),
		AS3_Number(uielems[i].min),
		AS3_Number(uielems[i].max),
		AS3_Number(uielems[i].init),
		AS3_Number(uielems[i].step)
	);
	AS3_Set(array, AS3_Int(i), result);
	// decrease refcount? todo: this may leak memory...
	//AS3_Release(result);
  }
}

class ActionScriptUI : public UI {
 public:
  ActionScriptUI() {
    fStopped = false;
  }
  
  virtual ~ActionScriptUI() {
  }
  
  // Pass in a zone, get back a unique ID.
  int registerControl(float *zone) {
    if (!zone) return 0;
	uiMap_id++;
	uidToZone[uiMap_id] = zone;
	return uiMap_id;
  }
  
  // Called from Flash when any control is updated.
  // Results will take effect on the next dsp callback
  // since everything runs in the same thread.
  void updateControl(int id, float value) {
    *(uidToZone[id]) = value;
  }

	virtual void addButton(char* label, float* zone) {
	  int id = registerControl(zone);
	  uielems[uielems_size].type = TYPE_BUTTON;
	  uielems[uielems_size].id = id;
	  strcopy(label, uielems[uielems_size].label);
	  uielems[uielems_size].min = 0;
	  uielems[uielems_size].max = 0;
	  uielems[uielems_size].init = 0;
	  uielems[uielems_size].step = 0;
      uielems_size++;
	}
	virtual void addToggleButton(char* label, float* zone) {
	  int id = registerControl(zone);
	  uielems[uielems_size].type = TYPE_TOGGLE;
	  uielems[uielems_size].id = id;
	  strcopy(label, uielems[uielems_size].label);
	  uielems[uielems_size].min = 0;
	  uielems[uielems_size].max = 0;
	  uielems[uielems_size].init = 0;
	  uielems[uielems_size].step = 0;
      uielems_size++;
	}
	virtual void addCheckButton(char* label, float* zone) {
	  return addToggleButton(label, zone);
	}
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) {
	  return addHorizontalSlider(label, zone, init, min, max, step);
	}
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) {
	  int id = registerControl(zone);
	  uielems[uielems_size].type = TYPE_SLIDER;
	  uielems[uielems_size].id = id;
	  strcopy(label, uielems[uielems_size].label);
	  uielems[uielems_size].min = min;
	  uielems[uielems_size].max = max;
	  uielems[uielems_size].init = init;
	  uielems[uielems_size].step = step;
      uielems_size++;
	}
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) {
	  return addHorizontalSlider(label, zone, init, min, max, step);
	}
		
	// Not implemented yet - these only affect UI layout and aren't critical.
	// See actionscript comments for details.
	virtual void openFrameBox(char* label) {}
	virtual void openTabBox(char* label) {}
	virtual void openHorizontalBox(char* label) {}
	virtual void openVerticalBox(char* label) {}
	virtual void closeBox() {}
	virtual void run() { }
};

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------
//  abstract definition of a signal processor
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 						= 0;
	virtual int getNumOutputs() 					= 0;
	virtual void buildUserInterface(UI* interface) 	= 0;
	virtual void init(int samplingRate) 			= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/// Alchemy DSP
class Faust {
public:
  Faust() { 
    // mydsp will be defined by faust in 'includeclass'
    dsp_ = new mydsp();
	ui_ = new ActionScriptUI();
	dsp_->buildUserInterface(ui_);
    dsp_->init(44100); // 44.1k, 2 channels, @ 32-bit is hardcoded into flash player 10.
  }
  
  ~Faust() {
    if (dsp_) delete dsp_;
	if (ui_) delete ui_;
  }
  
//private:
public: // we're all friends here
	mydsp *dsp_;
	ActionScriptUI *ui_;
};

Faust *faust = NULL;

// Alchemy wrapper interface code
static AS3_Val api_init(void *thisPtr, AS3_Val args) {
  faust = new Faust();
  AS3_Val array = AS3_Array("");
  BuildUIArray(array);
  return array;
}

static AS3_Val api_shutdown(void *thisPtr, AS3_Val args) {
	if (faust)
		delete faust;
	return AS3_Int(0);
}

// args = int id, float value
static AS3_Val api_onControlChange(void *thisPtr, AS3_Val args) {
  if (!faust) return AS3_Int(0);

  // Marshall the arguments in.
  int id = 0;
  AS3_Val controlVal;
  AS3_ArrayValue(args, "IntType, AS3ValType", &id, &controlVal);
  double control_double = AS3_NumberValue(controlVal);

  // loss of precision is ok.
  float value = (float)control_double;

  // Call the actual update function
  faust->ui_->updateControl(id, value);
  return AS3_Int(0);
}

#define MAX_FLASH_BUFFER 8192
// output buffers - L/R channels separate
static float bufferL[MAX_FLASH_BUFFER];
static float bufferR[MAX_FLASH_BUFFER];
// output buffer - construct interleaved output
static float bufferSum[2*MAX_FLASH_BUFFER];

// input buffers - L/R separate
static float inputL[MAX_FLASH_BUFFER];
static float inputR[MAX_FLASH_BUFFER];
// input buffer scratch space - interleaved
static float bufferInSum[2*MAX_FLASH_BUFFER];

// This is the most 'interesting' function of the file - it takes in flash sound buffers
//  and sends them through Faust DSP code.
// args = int nsamples, float* buffer (byte[] in flash)
static AS3_Val api_tick(void *thisPtr, AS3_Val args) {
  if (!faust) return AS3_Int(0);

  // Marshall arguments in.
  int nsamples = 0;
  int use_input = 0;
  AS3_Val buffer;
  AS3_Val input;
  AS3_ArrayValue(args, "IntType, IntType, AS3ValType, AS3ValType", &nsamples, &use_input, &input, &buffer);
  
  float* outputs[2] = {bufferL, bufferR};
  float* inputs[2] = {inputL, inputR};
  if (use_input) {
    //AS3_ByteArray_seek(input, 0, 0);
	// we need (#samples * sizeof(float) * 2 channels) bytes.
    AS3_ByteArray_readBytes((char*)bufferInSum, input, nsamples * 4 * 2);
	char *src = (char*)bufferInSum;
	char *dl = (char*)inputL, *dr = (char*)inputR;
	for (int i = 0; i < nsamples; ++i) {
	  // fix endianness
	  dl[3] = src[0];
	  dl[2] = src[1];
	  dl[1] = src[2];
	  dl[0] = src[3];
	  dr[3] = src[4];
	  dr[2] = src[5];
	  dr[1] = src[6];
	  dr[0] = src[7];
	  dl += 4;
	  dr += 4;
	  src += 8;
	}
  }

  // magic!
  faust->dsp_->compute(nsamples, inputs, outputs);

  // Post-process: interleave arrays. 
  // Faust outputs to two separate arrays (which are probably contiguous in memory - see above)
  // Flash's sound callback needs this as LRLRLRLR...
  // For added fun, LLVM internal float seems to be the opposite endianness
  // as what Flash uses, so we have to do this byte-by-byte.
  char *copyL = (char*)bufferL;
  char *copyR = (char*)bufferR;
  char *tape_head = (char*)bufferSum;
  for (int i = 0; i < nsamples; ++i) {
    *tape_head++ = copyL[3];
	*tape_head++ = copyL[2];
	*tape_head++ = copyL[1];
	*tape_head++ = copyL[0];
	*tape_head++ = copyR[3];
	*tape_head++ = copyR[2];
	*tape_head++ = copyR[1];
	*tape_head++ = copyR[0];
	copyL+=4;
	copyR+=4;
  }
  AS3_ByteArray_writeBytes(buffer, bufferSum, 4 * nsamples * 2);

  return AS3_Int(0);
}

//Alchemy entry point
// Here we are responsible for contructing an API object to pass back to Flash.
// This must contain pointers to all functions which may be called.
int main()
{
	//define the methods exposed to ActionScript
	//typed as an ActionScript Function instance
	AS3_Val methodInit = AS3_Function( NULL, api_init );
	AS3_Val methodShutdown = AS3_Function( NULL, api_shutdown );
	AS3_Val methodOnControlChange = AS3_Function( NULL, api_onControlChange );
	AS3_Val methodTick = AS3_Function( NULL, api_tick );

	// construct an API lookup table with references to all functions
	// In flash we'll instantiate one of these and call methods on it
	// e.g. faust.api_tick().
	AS3_Val result = AS3_Object(
		"api_init:AS3ValType, api_shutdown:AS3ValType, api_onControlChange:AS3ValType, api_tick:AS3ValType",
		methodInit, methodShutdown, methodOnControlChange, methodTick);

	AS3_Release(methodInit);
	AS3_Release(methodShutdown);
	AS3_Release(methodOnControlChange);
	AS3_Release(methodTick);

	// notify Flash of our functions and run -- this function never returns.
	AS3_LibInit(result);

	return 0;
}
/********************END ARCHITECTURE SECTION (part 2/2)****************/

