/* Pure architecture for Faust. This is similar to the Q architecture, but
   uses double precision for the audio buffers and control variables. See
   http://pure-lang.googlecode.com for a Pure module which can load these
   extensions. */

/* Copyright (c) 2009 Albert Graef

   Copying and distribution of this file, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  This file is offered as-is,
   without any warranty. */

#include <stdlib.h>
#include <math.h>

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

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
  bool	fStopped;
public:
		
  UI() : fStopped(false) {}
  virtual ~UI() {}
	
  virtual void addButton(const char* label, double* zone) = 0;
  virtual void addToggleButton(const char* label, double* zone) = 0;
  virtual void addCheckButton(const char* label, double* zone) = 0;
  virtual void addVerticalSlider(const char* label, double* zone, float init, float min, float max, float step) = 0;
  virtual void addHorizontalSlider(const char* label, double* zone, float init, float min, float max, float step) = 0;
  virtual void addNumEntry(const char* label, double* zone, float init, float min, float max, float step) = 0;

  virtual void addNumDisplay(const char* label, double* zone, int precision) = 0;
  virtual void addTextDisplay(const char* label, double* zone, char* names[], float min, float max) = 0;
  virtual void addHorizontalBargraph(const char* label, double* zone, float min, float max) = 0;
  virtual void addVerticalBargraph(const char* label, double* zone, float min, float max) = 0;
	
  virtual void openFrameBox(const char* label) = 0;
  virtual void openTabBox(const char* label) = 0;
  virtual void openHorizontalBox(const char* label) = 0;
  virtual void openVerticalBox(const char* label) = 0;
  virtual void closeBox() = 0;
	
  virtual void run() = 0;
	
  void stop()	{ fStopped = true; }
  bool stopped() 	{ return fStopped; }

  virtual void declare(double* zone, const char* key, const char* value) {}
};

/***************************************************************************
   Pure UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_TOGGLE_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  const char *label;
  double *zone;
  void *ref;
  float init, min, max, step;
};

class PureUI : public UI
{
public:
  int nelems;
  ui_elem_t *elems;
		
  PureUI();
  virtual ~PureUI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, double *zone);
  void add_elem(ui_elem_type_t type, const char *label, double *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, double *zone,
		float min, float max);

public:
  virtual void addButton(const char* label, double* zone);
  virtual void addToggleButton(const char* label, double* zone);
  virtual void addCheckButton(const char* label, double* zone);
  virtual void addVerticalSlider(const char* label, double* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, double* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, double* zone, float init, float min, float max, float step);

  virtual void addNumDisplay(const char* label, double* zone, int precision);
  virtual void addTextDisplay(const char* label, double* zone, char* names[], float min, float max);
  virtual void addHorizontalBargraph(const char* label, double* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, double* zone, float min, float max);
  
  virtual void openFrameBox(const char* label);
  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();
	
  virtual void run();
};

PureUI::PureUI()
{
  nelems = 0;
  elems = NULL;
}

PureUI::~PureUI()
{
  if (elems) free(elems);
}

inline void PureUI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].zone = NULL;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void PureUI::add_elem(ui_elem_type_t type, const char *label, double *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void PureUI::add_elem(ui_elem_type_t type, const char *label, double *zone,
			     float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void PureUI::add_elem(ui_elem_type_t type, const char *label, double *zone,
			     float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void PureUI::addButton(const char* label, double* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PureUI::addToggleButton(const char* label, double* zone)
{ add_elem(UI_TOGGLE_BUTTON, label, zone); }
void PureUI::addCheckButton(const char* label, double* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PureUI::addVerticalSlider(const char* label, double* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PureUI::addHorizontalSlider(const char* label, double* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PureUI::addNumEntry(const char* label, double* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

// FIXME: addNumDisplay and addTextDisplay not implemented in Faust yet?
void PureUI::addNumDisplay(const char* label, double* zone, int precision) {}
void PureUI::addTextDisplay(const char* label, double* zone, char* names[], float min, float max) {}
void PureUI::addHorizontalBargraph(const char* label, double* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PureUI::addVerticalBargraph(const char* label, double* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PureUI::openFrameBox(const char* label) {}
void PureUI::openTabBox(const char* label)
{ add_elem(UI_T_GROUP, label); }
void PureUI::openHorizontalBox(const char* label)
{ add_elem(UI_H_GROUP, label); }
void PureUI::openVerticalBox(const char* label)
{ add_elem(UI_V_GROUP, label); }
void PureUI::closeBox()
{ add_elem(UI_END_GROUP); }

void PureUI::run() {}

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
	virtual int getNumInputs() = 0;
	virtual int getNumOutputs() = 0;
	virtual void buildUserInterface(UI* interface) = 0;
	virtual void init(int samplingRate) = 0;
 	virtual void compute(int len, double** inputs, double** outputs) = 0;
};

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

/* Define FAUSTFLOAT so that audio buffers and control values are always
   represented as double pointers. This probably requires a recent Faust
   version (0.9.9.6 or later should be ok). */

#define FAUSTFLOAT double

<<includeclass>>

/* The class factory, used to create and destroy mydsp objects in the
   client. Implemented using C linkage to facilitate dlopen access. */

extern "C" dsp *newdsp()
{
  mydsp *d = new mydsp();
  return d;
}

extern "C" void deldsp(dsp* d)
{
  delete d;
}
