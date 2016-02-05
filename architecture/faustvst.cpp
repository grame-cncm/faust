/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2014 Albert Graef <aggraef@gmail.com>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2.1 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/* VST architecture for Faust synths. */

/* NOTE: This requires one of the Boost headers (boost/circular_buffer.hpp),
   so to compile Faust programs created with this architecture you need to
   have at least the Boost headers installed somewhere on your include path
   (the Boost libraries aren't needed). */

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <list>
#include <map>
#include <set>

using namespace std;

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

typedef pair<const char*,const char*> strpair;

struct Meta : std::map<const char*, const char*>
{
  void declare(const char *key, const char *value)
  {
    (*this)[key] = value;
  }
  const char* get(const char *key, const char *def)
  {
    if (this->find(key) != this->end())
      return (*this)[key];
    else
      return def;
  }
};

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 	max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 	max (int a, int b)		{ return (a>b) ? a : b; }

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


inline int	min (int a, int b)		{ return (a<b) ? a : b; }

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
//template<typename T> T abs (T a)		{ return (a<T(0)) ? -a : a; }

inline int	lsr (int x, int n)		{ return int(((unsigned int)x) >> n); }

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

  virtual void addButton(const char* label, float* zone) = 0;
  virtual void addCheckButton(const char* label, float* zone) = 0;
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

  virtual void openTabBox(const char* label) = 0;
  virtual void openHorizontalBox(const char* label) = 0;
  virtual void openVerticalBox(const char* label) = 0;
  virtual void closeBox() = 0;

  virtual void run() = 0;

  void stop() { fStopped = true; }
  bool stopped() { return fStopped; }

  virtual void declare(float* zone, const char* key, const char* value) {}
};

/***************************************************************************
   VST UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  const char *label;
  int port;
  float *zone;
  void *ref;
  float init, min, max, step;
};

class PFaustUI : public UI
{
public:
  bool is_instr;
  int nelems, nports;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  PFaustUI(int maxvoices = 0);
  virtual ~PFaustUI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();

  virtual void run();

  virtual void declare(float* zone, const char* key, const char* value);
};

PFaustUI::PFaustUI(int maxvoices)
{
  is_instr = maxvoices>0;
  nelems = nports = 0;
  elems = NULL;
}

PFaustUI::~PFaustUI()
{
  if (elems) free(elems);
}

void PFaustUI::declare(float* zone, const char* key, const char* value)
{
  map< int, list<strpair> >::iterator it = metadata.find(nelems);
  if (it != metadata.end())
    it->second.push_back(strpair(key, value));
  else
    metadata[nelems] = list<strpair>(1, strpair(key, value));
}

inline void PFaustUI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = -1;
  elems[nelems].zone = NULL;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

static bool is_voice_ctrl(const char *label);

#define portno(label) ((is_instr && is_voice_ctrl(label))?-1:nports++)

inline void PFaustUI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 1.0;
  elems[nelems].step = 1.0;
  nelems++;
}

inline void PFaustUI::add_elem(ui_elem_type_t type, const char *label, float *zone, float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void PFaustUI::add_elem(ui_elem_type_t type, const char *label, float *zone, float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void PFaustUI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PFaustUI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PFaustUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PFaustUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PFaustUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PFaustUI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PFaustUI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PFaustUI::openTabBox(const char* label)
{ add_elem(UI_T_GROUP, label); }
void PFaustUI::openHorizontalBox(const char* label)
{ add_elem(UI_H_GROUP, label); }
void PFaustUI::openVerticalBox(const char* label)
{ add_elem(UI_V_GROUP, label); }
void PFaustUI::closeBox()
{ add_elem(UI_END_GROUP); }

void PFaustUI::run() {}

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
  // internal freelist for custom voice allocation
  dsp *prev, *next;
  dsp() {}
  virtual ~dsp() {}
  virtual int getNumInputs() = 0;
  virtual int getNumOutputs() = 0;
  virtual void buildUserInterface(UI* interface) = 0;
  virtual void init(int samplingRate) = 0;
  virtual void compute(int len, float** inputs, float** outputs) = 0;
};

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeclass>>

//----------------------------------------------------------------------------
//  VST interface
//----------------------------------------------------------------------------

#line 398 "faustvst.cpp"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boost/circular_buffer.hpp>

// Some boilerplate code pilfered from the mda Linux vst source code.
#include "pluginterfaces/vst2.x/aeffectx.h"
extern "C" {
#define VST_EXPORT   __attribute__ ((visibility ("default")))
extern VST_EXPORT AEffect * VSTPluginMain(audioMasterCallback audioMaster);
// This is for legacy (<2.4) VST hosts which look for the 'main' entry point.
AEffect *main_plugin (audioMasterCallback audioMaster) asm ("main");
#define main main_plugin
VST_EXPORT AEffect * main(audioMasterCallback audioMaster)
{
  return VSTPluginMain(audioMaster);
}
}

/* Setting NVOICES at compile time overrides meta data in the Faust source. If
   set, this must be an integer value >= 0. A nonzero value indicates an
   instrument (VSTi) plugin with the given maximum number of voices. Use 1 for
   a monophonic synthesizer, and 0 for a simple effect plugin. If NVOICES
   isn't defined at compile time then the number of voices of an instrument
   plugin can also be set with the global "nvoices" meta data key in the Faust
   source. This setting also adds a special "polyphony" control to the plugin
   which can be used to dynamically adjust the actual number of voices in the
   range 1..NVOICES. */
//#define NVOICES 16

/* This enables a special "tuning" control in a VSTi plugin which lets you
   select the MTS tuning to be used for the synth. In order to use this, you
   just drop some sysex (.syx) files with MTS octave-based tunings in 1- or
   2-byte format into the ~/.fautvst/tuning directory (these can be generated
   with the author's sclsyx program, https://bitbucket.org/agraef/sclsyx).
   The control will only be shown if any .syx files were found at startup. 0
   selects the default tuning (standard 12-tone equal temperament), i>0 the
   tuning in the ith sysex file (in alphabetic order). */
#ifndef FAUST_MTS
#define FAUST_MTS 1
#endif

/* This allows various manifest data to be generated from the corresponding
   metadata (author, name, description, license) in the Faust source. */
#ifndef FAUST_META
#define FAUST_META 1
#endif

/* This enables automatic MIDI controller mapping based on the midi:ctrl
   attributes in the Faust source. We have this enabled by default, but you
   may have to disable it if the custom controller mapping gets in the way of
   the automation facilities that the host provides. (But then again if the
   host wants to do its own controller mapping then it probably won't, or at
   least shouldn't, send us the MIDI controllers in the first place.) */
#ifndef FAUST_MIDICC
#define FAUST_MIDICC 1
#endif

// You can define these for various debugging output items.
//#define DEBUG_META 1 // recognized MIDI controller metadata
//#define DEBUG_VOICES 1 // triggering of synth voices
//#define DEBUG_VOICE_ALLOC 1 // voice allocation
//#define DEBUG_MIDI 1 // incoming MIDI messages
//#define DEBUG_NOTES 1 // note messages
//#define DEBUG_MIDICC 1 // controller messages
//#define DEBUG_RPN 1 // RPN messages (pitch bend range, master tuning)
//#define DEBUG_MTS 1 // MTS messages (octave/scale tuning)

static bool is_voice_ctrl(const char *label)
{
  return !strcmp(label, "freq") || !strcmp(label, "gain") ||
    !strcmp(label, "gate");
}

// Note and voice data structures.

struct NoteInfo {
  uint8_t ch;
  int8_t note;
};

struct VoiceData {
  // Octave tunings (offsets in semitones) per MIDI channel.
  float tuning[16][12];
  // Allocated voices per MIDI channel and note.
  int8_t notes[16][128];
  // Free and used voices.
  int n_free, n_used;
  boost::circular_buffer<int> free_voices;
  boost::circular_buffer<int> used_voices;
  NoteInfo *note_info;
  // Voices queued for note-offs (zero-length notes).
  set<int> queued;
  // Last gate value during run() for each voice. We need to keep track of
  // these so that we can force the Faust synth to retrigger a note when
  // needed.
  float *lastgate;
  // Current pitch bend and pitch bend range on each MIDI channel, in semitones.
  float bend[16], range[16];
  // Current coarse, fine and total master tuning on each MIDI channel (tuning
  // offset relative to A4 = 440 Hz, in semitones).
  float coarse[16], fine[16], tune[16];
  VoiceData(int n) : free_voices(n), used_voices(n) { }
};

#if FAUST_MTS

// Helper classes to read and store MTS tunings.

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string>
#include <vector>

struct MTSTuning {
  char *name; // name of the tuning
  int len; // length of sysex data in bytes
  unsigned char *data; // sysex data
  MTSTuning() : name(0), len(0), data(0) {}
  MTSTuning& operator=(const MTSTuning &t)
  {
    if (this == &t) return *this;
    if (name) free(name); if (data) free(data);
    name = 0; data = 0; len = t.len;
    if (t.name) {
      name = strdup(t.name); assert(name);
    }
    if (t.data) {
      data = (unsigned char*)malloc(len); assert(data);
      memcpy(data, t.data, len);
    }
    return *this;
  }
  MTSTuning(const MTSTuning& t) : name(0), len(0), data(0)
  { *this = t; }
  MTSTuning(const char *filename);
  ~MTSTuning()
  { if (name) free(name); if (data) free(data); }
};

MTSTuning::MTSTuning(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  name = 0; len = 0; data = 0;
  if (!fp) return;
  struct stat st;
  if (fstat(fileno(fp), &st)) return;
  len = st.st_size;
  data = (unsigned char*)calloc(len, 1);
  if (!data) {
    len = 0; fclose(fp);
    return;
  }
  assert(len > 0);
  if (fread(data, 1, len, fp) < len) {
    free(data); len = 0; data = 0; fclose(fp);
    return;
  }
  fclose(fp);
  // Do some basic sanity checks.
  if (data[0] != 0xf0 || data[len-1] != 0xf7 || // not a sysex message
      (data[1] != 0x7e && data[1] != 0x7f) || data[3] != 8 || // not MTS
      !((len == 21 && data[4] == 8) ||
	(len == 33 && data[4] == 9))) { // no 1- or 2-byte tuning
    free(data); len = 0; data = 0;
    return;
  }
  // Name of the tuning is the basename of the file, without the trailing .syx
  // suffix.
  string nm = filename;
  size_t p = nm.rfind(".syx");
  if (p != string::npos) nm.erase(p);
  p = nm.rfind('/');
  if (p != string::npos) nm.erase(0, p+1);
  name = strdup(nm.c_str());
  assert(name);
}

struct MTSTunings {
  vector<MTSTuning> tuning;
  MTSTunings() {}
  MTSTunings(const char *path);
};

static bool compareByName(const MTSTuning &a, const MTSTuning &b)
{
  return strcmp(a.name, b.name) < 0;
}

MTSTunings::MTSTunings(const char *path)
{
  DIR *dp = opendir(path);
  if (!dp) return;
  struct dirent *d;
  while ((d = readdir(dp))) {
    string nm = d->d_name;
    if (nm.length() > 4 && nm.substr(nm.length()-4) == ".syx") {
      string pathname = path;
      pathname += "/";
      pathname += nm;
      MTSTuning t(pathname.c_str());
      if (t.data) tuning.push_back(t);
    }
  }
  closedir(dp);
  // sort found tunings by name
  sort(tuning.begin(), tuning.end(), compareByName);
}

#endif

#if FAUST_MIDICC
static float ctrlval(const ui_elem_t &el, uint8_t v)
{
  // Translate the given MIDI controller value to the range and stepsize
  // indicated by the Faust control.
  switch (el.type) {
  case UI_BUTTON: case UI_CHECK_BUTTON:
    return (float)(v>=64);
  default:
    /* Continuous controllers. The problem here is that the range 0..127 is
       not symmetric. We'd like to map 64 to the center of the range
       (max-min)/2 and at the same time retain the full control range
       min..max. So let's just pretend that there are 128 controller values
       and map value 127 to the max value anyway. */
    if (v==127)
      return el.max;
    else
      // XXXFIXME: We might want to add proper quantization according to
      // el.step here.
      return el.min+(el.max-el.min)*v/128;
  }
}
#endif

/***************************************************************************/

/* Polyphonic Faust plugin data structure. XXXTODO: At present this is just a
   big struct which exposes all requisite data. Some more work is needed to
   make the interface a bit more abstract and properly encapsulate the
   internal data structures, so that implementation details can be changed
   more easily. */

struct PFaustPlugin {
  const int maxvoices;	// maximum number of voices (zero if not an instrument)
  const int ndsps;	// number of dsp instances (1 if maxvoices==0)
  int nvoices;		// current number of voices (<= maxvoices)
  bool active;		// activation status
  int rate;		// sampling rate
  mydsp **dsp;		// the dsps
  PFaustUI **ui;	// their Faust interface descriptions
  int n_in, n_out;	// number of input and output control ports
  int poly, tuning;	// polyphony and tuning ports
  int *ctrls;		// Faust ui elements (indices into ui->elems)
  float *ports;		// port data (plugin-side control values)
  float *portvals;	// cached port data from the last run
  float *midivals[16];	// per-channel midi data
  int *inctrls, *outctrls;	// indices for active and passive controls
  int freq, gain, gate;	// indices of voice controls
  const char **units;	// unit names (control meta data)
  unsigned n_samples;	// current block size
  float **outbuf;	// audio buffers for mixing down the voices
  float **inbuf;	// dummy input buffer used for retriggering notes
  std::map<uint8_t,int> ctrlmap; // MIDI controller map (control meta data)
  // Current RPN MSB and LSB numbers, as set with controllers 101 and 100.
  uint8_t rpn_msb[16], rpn_lsb[16];
  // Current data entry MSB and LSB numbers, as set with controllers 6 and 38.
  uint8_t data_msb[16], data_lsb[16];
  // Synth voice data (instruments only).
  VoiceData *vd;

  // Static methods. These all use static data so they can be invoked before
  // instantiating a plugin.

  // Global meta data (dsp name, author, etc.).
  static Meta *meta;
  static void init_meta()
  {
    if (!meta) {
      meta = new Meta;
      mydsp::metadata(meta);
    }
  }

  static const char *pluginName()
  {
    init_meta();
    return meta->get("name", "mydsp");
  }

  static const char *pluginAuthor()
  {
    init_meta();
    return meta->get("author", "");
  }

  static const char *pluginDescription()
  {
    init_meta();
    return meta->get("description", "");
  }

  static const char *pluginVersion()
  {
    init_meta();
    return meta->get("version", "0.0");
  }

  // Load a collection of sysex files with MTS tunings in ~/.faust/tuning.
  static int n_tunings;
#if FAUST_MTS
  static MTSTunings *mts;

  static MTSTunings *load_sysex_data()
  {
    if (!mts) {
      string mts_path;
      // Look for FAUST_HOME. If that isn't set, try $HOME/.faust. If HOME
      // isn't set either, just assume a .faust subdir of the cwd.
      const char *home = getenv("FAUST_HOME");
      if (home)
	mts_path = home;
      else {
	home = getenv("HOME");
	if (home) {
	  mts_path = home;
	  mts_path += "/.faust";
	} else
	  mts_path = ".faust";
      }
      // MTS tunings are looked for in this subdir.
      mts_path += "/tuning";
      mts = new MTSTunings(mts_path.c_str());
#ifdef __APPLE__
      if (!mts || mts->tuning.size() == 0) {
	// Also check ~/Library/Faust/Tuning on the Mac.
	home = getenv("HOME");
	if (home) {
	  if (mts) delete mts;
	  mts_path = home;
	  mts_path += "/Library/Faust/Tuning";
	  mts = new MTSTunings(mts_path.c_str());
	}
      }
#endif
      n_tunings = mts->tuning.size();
    }
    return mts;
  }
#endif

  // The number of voices of an instrument plugin. We get this information
  // from the global meta data (nvoices key) of the dsp module if present, and
  // you can also override this setting at compile time by defining the
  // NVOICES macro. If neither is defined or the value is zero then the plugin
  // becomes a simple audio effect instead.
  static int numVoices()
  {
#ifdef NVOICES
    return NVOICES;
#else
    init_meta();
    const char *numVoices = meta->get("nvoices", "0");
    int nvoices = atoi(numVoices);
    if (nvoices < 0 ) nvoices = 0;
    return nvoices;
#endif
  }

  // The number of controls of the dsp. Some plugin interfaces need that
  // information beforehand, so we create a dummy instance of the UI data to
  // retrieve it. For instrument plugins, we also reserve extra ports for the
  // polyphony and tuning controls, if applicable.
  static int numControls()
  {
    const int num_voices = numVoices();
    mydsp dsp;
    PFaustUI ui(num_voices);
    dsp.buildUserInterface(&ui);
    // reserve one extra port for the polyphony control (instruments only)
    int num_extra = (num_voices>0);
#if FAUST_MTS
    // likewise for the tuning control
    if (num_voices>0 && load_sysex_data())
      num_extra += (mts->tuning.size()>0);
#endif
    return ui.nports+num_extra;
  }

  // Instance methods.

  PFaustPlugin(const int num_voices, const int sr)
    : maxvoices(num_voices), ndsps(num_voices<=0?1:num_voices),
      vd(num_voices>0?new VoiceData(num_voices):0)
  {
    // Initialize static data.
    init_meta();
#if FAUST_MTS
    // Synth: load tuning sysex data if present.
    if (num_voices>0) load_sysex_data();
#endif
    // Allocate data structures and set some reasonable defaults.
    dsp = (mydsp**)calloc(ndsps, sizeof(mydsp*));
    ui = (PFaustUI**)calloc(ndsps, sizeof(PFaustUI*));
    assert(dsp && ui);
    if (vd) {
      vd->note_info = (NoteInfo*)calloc(ndsps, sizeof(NoteInfo));
      vd->lastgate = (float*)calloc(ndsps, sizeof(float));
      assert(vd->note_info && vd->lastgate);
    }
    active = false;
    rate = sr;
    nvoices = maxvoices;
    n_in = n_out = 0;
    poly = maxvoices/2;
    tuning = 0;
    freq = gain = gate = -1;
    for (int i = 0; i < 16; i++) {
      rpn_msb[i] = rpn_lsb[i] = 0x7f;
      data_msb[i] = data_lsb[i] = 0;
    }
    if (vd) {
      vd->n_free = maxvoices;
      for (int i = 0; i < maxvoices; i++) {
	vd->free_voices.push_back(i);
	vd->lastgate[i] = 0.0f;
      }
      for (int i = 0; i < 16; i++) {
	vd->bend[i] = 0.0f;
	vd->range[i] = 2.0f;
	vd->coarse[i] = vd->fine[i] = vd->tune[i] = 0.0f;
	for (int j = 0; j < 12; j++)
	  vd->tuning[i][j] = 0.0f;
      }
      vd->n_used = 0;
      memset(vd->notes, 0xff, sizeof(vd->notes));
    }
    n_samples = 0;
    ctrls = inctrls = outctrls = NULL;
    inbuf = outbuf = NULL;
    ports = portvals = NULL;
    units = NULL;
    memset(midivals, 0, sizeof(midivals));
    // Initialize the Faust DSPs.
    for (int i = 0; i < ndsps; i++) {
      dsp[i] = new mydsp();
      ui[i] = new PFaustUI(num_voices);
      dsp[i]->init(rate);
      dsp[i]->buildUserInterface(ui[i]);
    }
    // The ports are numbered as follows: 0..k-1 are the control ports, then
    // come the n audio input ports, then the m audio output ports, and
    // finally the midi input port and the polyphony and tuning controls. This
    // mimics the port layout of faust-lv2, but should work fine with other
    // kinds of plugin architectures as well.
    int k = ui[0]->nports, p = 0, q = 0;
    int n = dsp[0]->getNumInputs(), m = dsp[0]->getNumOutputs();
    // Allocate tables for the built-in control elements and their ports.
    ctrls = (int*)calloc(k, sizeof(int));
    inctrls = (int*)calloc(k, sizeof(int));
    outctrls = (int*)calloc(k, sizeof(int));
    ports = (float*)calloc(k, sizeof(float));
    portvals = (float*)calloc(k, sizeof(float));
    units = (const char**)calloc(k, sizeof(const char*));
    assert(k == 0 || (ctrls && inctrls && outctrls &&
		      ports && portvals && units));
    for (int ch = 0; ch < 16; ch++) {
      midivals[ch] = (float*)calloc(k, sizeof(float));
      assert(k == 0 || midivals[ch]);
    }
    // Scan the Faust UI for active and passive controls which become the
    // input and output control ports of the plugin, respectively.
    for (int i = 0, j = 0; i < ui[0]->nelems; i++) {
      const char *unit = NULL;
      switch (ui[0]->elems[i].type) {
      case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
	// control groups (ignored right now)
	break;
      case UI_H_BARGRAPH: case UI_V_BARGRAPH:
	// passive controls (output ports)
	ctrls[j++] = i;
	outctrls[q++] = i;
	{
	  std::map< int, list<strpair> >::iterator it =
	    ui[0]->metadata.find(i);
	  if (it != ui[0]->metadata.end()) {
	    for (std::list<strpair>::iterator jt = it->second.begin();
		 jt != it->second.end(); jt++) {
	      const char *key = jt->first, *val = jt->second;
#if DEBUG_META
	      fprintf(stderr, "ctrl '%s' meta: '%s' -> '%s'\n",
		      ui[0]->elems[i].label, key, val);
#endif
	      if (strcmp(key, "unit") == 0)
		unit = val;
	    }
	  }
	  int p = ui[0]->elems[i].port;
	  units[p] = unit;
	}
	break;
      default:
	// active controls (input ports)
	if (maxvoices == 0)
	  goto noinstr;
	else if (freq == -1 &&
		 !strcmp(ui[0]->elems[i].label, "freq"))
	  freq = i;
	else if (gain == -1 &&
		 !strcmp(ui[0]->elems[i].label, "gain"))
	  gain = i;
	else if (gate == -1 &&
		 !strcmp(ui[0]->elems[i].label, "gate"))
	  gate = i;
	else {
	noinstr:
	  std::map< int, list<strpair> >::iterator it =
	    ui[0]->metadata.find(i);
	  if (it != ui[0]->metadata.end()) {
	    // Scan for controller mappings and other control meta data.
	    for (std::list<strpair>::iterator jt = it->second.begin();
		 jt != it->second.end(); jt++) {
	      const char *key = jt->first, *val = jt->second;
#if DEBUG_META
	      fprintf(stderr, "ctrl '%s' meta: '%s' -> '%s'\n",
		      ui[0]->elems[i].label, key, val);
#endif
	      if (strcmp(key, "unit") == 0) {
		unit = val;
#if FAUST_MIDICC
	      } else if (strcmp(key, "midi") == 0) {
		unsigned num;
		if (sscanf(val, "ctrl %u", &num) < 1) continue;
#if 0 // enable this to get feedback about controller assignments
		const char *dsp_name = pluginName();
		fprintf(stderr, "%s: cc %d -> %s\n", dsp_name, num,
			ui[0]->elems[i].label);
#endif
		ctrlmap.insert(std::pair<uint8_t,int>(num, p));
#endif
	      }
	    }
	  }
	  ctrls[j++] = i;
	  inctrls[p++] = i;
	  int p = ui[0]->elems[i].port;
	  float val = ui[0]->elems[i].init;
	  portvals[p] = ports[p] = val;
	  units[p] = unit;
	  for (int ch = 0; ch < 16; ch++)
	    midivals[ch][p] = val;
	}
	break;
      }
    }
    // Realloc the inctrls and outctrls vectors to their appropriate sizes.
    inctrls = (int*)realloc(inctrls, p*sizeof(int));
    assert(p == 0 || inctrls);
    outctrls = (int*)realloc(outctrls, q*sizeof(int));
    assert(q == 0 || outctrls);
    n_in = p; n_out = q;
    if (maxvoices > 0) {
      // Initialize the mixdown buffer.
      outbuf = (float**)calloc(m, sizeof(float*));
      assert(m == 0 || outbuf);
      // We start out with a blocksize of 512 samples here. Hopefully this is
      // enough for most realtime hosts so that we can avoid reallocations
      // later when we know what the actual blocksize is.
      n_samples = 512;
      for (int i = 0; i < m; i++) {
	outbuf[i] = (float*)malloc(n_samples*sizeof(float));
	assert(outbuf[i]);
      }
      // Initialize a 1-sample dummy input buffer used for retriggering notes.
      inbuf = (float**)calloc(n, sizeof(float*));
      assert(n == 0 || inbuf);
      for (int i = 0; i < m; i++) {
	inbuf[i] = (float*)malloc(sizeof(float));
	assert(inbuf[i]);
	*inbuf[i] = 0.0f;
      }
    }
  }

  ~PFaustPlugin()
  {
    const int n = dsp[0]->getNumInputs();
    const int m = dsp[0]->getNumOutputs();
    for (int i = 0; i < ndsps; i++) {
      delete dsp[i];
      delete ui[i];
    }
    free(ctrls);
    free(inctrls);
    free(outctrls);
    free(ports);
    free(portvals);
    free(units);
    for (int ch = 0; ch < 16; ch++)
      free(midivals[ch]);
    if (inbuf) {
      for (int i = 0; i < n; i++)
	free(inbuf[i]);
      free(inbuf);
    }
    if (outbuf) {
      for (int i = 0; i < m; i++)
	free(outbuf[i]);
      free(outbuf);
    }
    free(dsp);
    free(ui);
    if (vd) {
      free(vd->note_info);
      free(vd->lastgate);
      delete vd;
    }
  }

  // Voice allocation.

#if DEBUG_VOICE_ALLOC
  void print_voices(const char *msg)
  {
    fprintf(stderr, "%s: notes =", msg);
    for (uint8_t ch = 0; ch < 16; ch++)
      for (int note = 0; note < 128; note++)
	if (vd->notes[ch][note] >= 0)
	  fprintf(stderr, " [%d] %d(#%d)", ch, note, vd->notes[ch][note]);
    fprintf(stderr, "\nqueued (%d):", vd->queued.size());
    for (int i = 0; i < nvoices; i++)
      if (vd->queued.find(i) != vd->queued.end()) fprintf(stderr, " #%d", i);
    fprintf(stderr, "\nused (%d):", vd->n_used);
    for (boost::circular_buffer<int>::iterator it = vd->used_voices.begin();
	 it != vd->used_voices.end(); it++)
      fprintf(stderr, " #%d->%d", *it, vd->note_info[*it].note);
    fprintf(stderr, "\nfree (%d):", vd->n_free);
    for (boost::circular_buffer<int>::iterator it = vd->free_voices.begin();
	 it != vd->free_voices.end(); it++)
      fprintf(stderr, " #%d", *it);
    fprintf(stderr, "\n");
  }
#endif

  int alloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = vd->notes[ch][note];
    if (i >= 0) {
      // note already playing on same channel, retrigger it
      voice_off(i);
      voice_on(i, note, vel, ch);
      // move this voice to the end of the used list
      for (boost::circular_buffer<int>::iterator it =
	     vd->used_voices.begin();
	   it != vd->used_voices.end(); it++) {
	if (*it == i) {
	  vd->used_voices.erase(it);
	  vd->used_voices.push_back(i);
	  break;
	}
      }
#if DEBUG_VOICE_ALLOC
      print_voices("retrigger");
#endif
      return i;
    } else if (vd->n_free > 0) {
      // take voice from free list
      int i = vd->free_voices.front();
      vd->free_voices.pop_front();
      vd->n_free--;
      vd->used_voices.push_back(i);
      vd->note_info[i].ch = ch;
      vd->note_info[i].note = note;
      vd->n_used++;
      voice_on(i, note, vel, ch);
      vd->notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("alloc");
#endif
      return i;
    } else {
      // steal a voice
      assert(vd->n_used > 0);
      // FIXME: Maybe we should look for the oldest note on the *current*
      // channel here, but this is faster.
      int i = vd->used_voices.front();
      int oldch = vd->note_info[i].ch;
      int oldnote = vd->note_info[i].note;
      voice_off(i);
      vd->notes[oldch][oldnote] = -1;
      vd->queued.erase(i);
      vd->used_voices.pop_front();
      vd->used_voices.push_back(i);
      vd->note_info[i].ch = ch;
      vd->note_info[i].note = note;
      voice_on(i, note, vel, ch);
      vd->notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("steal");
#endif
      return i;
    }
  }

  int dealloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = vd->notes[ch][note];
    if (i >= 0) {
      if (vd->lastgate[i] == 0.0f && gate >= 0) {
	// zero-length note, queued for later
	vd->queued.insert(i);
	vd->notes[ch][note] = -1;
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (queued)");
#endif
	return i;
      }
      assert(vd->n_free < nvoices);
      vd->free_voices.push_back(i);
      vd->n_free++;
      voice_off(i);
      vd->notes[ch][note] = -1;
      // erase this voice from the used list
      for (boost::circular_buffer<int>::iterator it =
	     vd->used_voices.begin();
	   it != vd->used_voices.end(); it++) {
	if (*it == i) {
	  vd->used_voices.erase(it);
	  vd->n_used--;
	  break;
	}
      }
#if DEBUG_VOICE_ALLOC
      print_voices("dealloc");
#endif
      return i;
    }
    return -1;
  }


  float midicps(int8_t note, uint8_t chan)
  {
    float pitch = note + vd->tune[chan] +
      vd->tuning[chan][note%12] + vd->bend[chan];
    return 440.0*pow(2, (pitch-69.0)/12.0);
  }

  void voice_on(int i, int8_t note, int8_t vel, uint8_t ch)
  {
    if (vd->lastgate[i] == 1.0f && gate >= 0) {
      // Make sure that the synth sees the 0.0f gate so that the voice is
      // properly retriggered.
      *ui[i]->elems[gate].zone = 0.0f;
      dsp[i]->compute(1, inbuf, outbuf);
    }
#if DEBUG_VOICES
    fprintf(stderr, "voice on: %d %d (%g Hz) %d (%g)\n", i,
	    note, midicps(note, ch), vel, vel/127.0);
#endif
    if (freq >= 0)
      *ui[i]->elems[freq].zone = midicps(note, ch);
    if (gate >= 0)
      *ui[i]->elems[gate].zone = 1.0f;
    if (gain >= 0)
      *ui[i]->elems[gain].zone = vel/127.0;
    // reinitialize the per-channel control data for this voice
    for (int idx = 0; idx < n_in; idx++) {
      int j = inctrls[idx], k = ui[0]->elems[j].port;
      *ui[i]->elems[j].zone = midivals[ch][k];
    }
  }

  void voice_off(int i)
  {
#if DEBUG_VOICES
    fprintf(stderr, "voice off: %d\n", i);
#endif
    if (gate >= 0)
      *ui[i]->elems[gate].zone = 0.0f;
  }

  void update_voices(uint8_t chan)
  {
    // update running voices on the given channel after tuning or pitch bend
    // changes
    for (boost::circular_buffer<int>::iterator it =
	   vd->used_voices.begin();
	 it != vd->used_voices.end(); it++) {
      int i = *it;
      if (vd->note_info[i].ch == chan && freq >= 0) {
	int note = vd->note_info[i].note;
	*ui[i]->elems[freq].zone = midicps(note, chan);
      }
    }
  }

  void all_notes_off()
  {
    for (int i = 0; i < nvoices; i++)
      voice_off(i);
    for (int i = 0; i < 16; i++)
      vd->bend[i] = 0.0f;
    memset(vd->notes, 0xff, sizeof(vd->notes));
    vd->free_voices.clear();
    vd->n_free = nvoices;
    for (int i = 0; i < nvoices; i++)
      vd->free_voices.push_back(i);
    vd->queued.clear();
    vd->used_voices.clear();
    vd->n_used = 0;
  }

  void all_notes_off(uint8_t chan)
  {
    for (boost::circular_buffer<int>::iterator it =
	   vd->used_voices.begin();
	 it != vd->used_voices.end(); ) {
      int i = *it;
      if (vd->note_info[i].ch == chan) {
	assert(vd->n_free < nvoices);
	vd->free_voices.push_back(i);
	vd->n_free++;
	voice_off(i);
	vd->notes[vd->note_info[i].ch][vd->note_info[i].note] = -1;
	vd->queued.erase(i);
	// erase this voice from the used list
	it = vd->used_voices.erase(it);
	vd->n_used--;
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (all-notes-off)");
#endif
      } else
	it++;
    }
    vd->bend[chan] = 0.0f;
  }

  void queued_notes_off()
  {
    if (vd->queued.empty()) return;
    for (int i = 0; i < nvoices; i++)
      if (vd->queued.find(i) != vd->queued.end()) {
	assert(vd->n_free < nvoices);
	vd->free_voices.push_back(i);
	vd->n_free++;
	voice_off(i);
	vd->notes[vd->note_info[i].ch][vd->note_info[i].note] = -1;
	vd->queued.erase(i);
	// erase this voice from the used list
	for (boost::circular_buffer<int>::iterator it =
	       vd->used_voices.begin();
	     it != vd->used_voices.end(); it++) {
	  if (*it == i) {
	    vd->used_voices.erase(it);
	    vd->n_used--;
	    break;
	  }
	}
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (unqueued)");
#endif
      }
  }

  // Plugin activation status. suspend() deactivates a plugin (disables audio
  // processing), resume() reactivates it. Also, set_rate() changes the sample
  // rate. Note that the audio and MIDI process functions (see below) can
  // still be called in deactivated state, but this is optional. The plugin
  // tries to do some reasonable processing in either case, no matter whether
  // the host plugin architecture actually executes callbacks in suspended
  // state or not.

  void suspend()
  {
    active = false;
    if (maxvoices > 0) all_notes_off();
  }

  void resume()
  {
    for (int i = 0; i < ndsps; i++)
      dsp[i]->init(rate);
    for (int i = 0, j = 0; i < ui[0]->nelems; i++) {
      int p = ui[0]->elems[i].port;
      if (p >= 0) {
	float val = ui[0]->elems[i].init;
	portvals[p] = val;
      }
    }
    active = true;
  }

  void set_rate(int sr)
  {
    rate = sr;
    for (int i = 0; i < ndsps; i++)
      dsp[i]->init(rate);
  }

  // Audio and MIDI process functions. The plugin should run these in the
  // appropriate real-time callbacks.

  void process_audio(int blocksz, float **inputs, float **outputs)
  {
    int n = dsp[0]->getNumInputs(), m = dsp[0]->getNumOutputs();
    AVOIDDENORMALS;
    if (maxvoices > 0) queued_notes_off();
    if (!active) {
      // Depending on the plugin architecture, this code might never be
      // invoked, since the plugin is deactivitated at this point. But let's
      // do something reasonable here anyway.
      if (n == m) {
	// copy inputs to outputs
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < blocksz; j++)
	    outputs[i][j] = inputs[i][j];
      } else {
	// silence
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < blocksz; j++)
	    outputs[i][j] = 0.0f;
      }
      return;
    }
    // Handle changes in the polyphony control.
    if (nvoices != poly && poly > 0 && poly <= maxvoices) {
      for (int i = 0; i < nvoices; i++)
	voice_off(i);
      nvoices = poly;
      // Reset the voice allocation.
      memset(vd->notes, 0xff, sizeof(vd->notes));
      vd->free_voices.clear();
      vd->n_free = nvoices;
      for (int i = 0; i < nvoices; i++)
	vd->free_voices.push_back(i);
      vd->used_voices.clear();
      vd->n_used = 0;
    } else
      poly = nvoices;
    // Only update the controls (of all voices simultaneously) if a port value
    // actually changed. This is necessary to allow MIDI controllers to modify
    // the values for individual MIDI channels (see processEvents below). Also
    // note that this will be done *after* processing the MIDI controller data
    // for the current audio block, so manual inputs can still override these.
    bool is_instr = maxvoices > 0;
    for (int i = 0; i < n_in; i++) {
      int j = inctrls[i], k = ui[0]->elems[j].port;
      float &oldval = portvals[k], newval = ports[k];
      if (newval != oldval) {
	if (is_instr) {
	  // instrument: update running voices
	  for (boost::circular_buffer<int>::iterator it =
		 vd->used_voices.begin();
	       it != vd->used_voices.end(); it++) {
	    int i = *it;
	    *ui[i]->elems[j].zone = newval;
	  }
	} else {
	  // simple effect: here we only have a single dsp instance
	  *ui[0]->elems[j].zone = newval;
	}
	// also update the MIDI controller data for all channels (manual
	// control input is always omni)
	for (int ch = 0; ch < 16; ch++)
	  midivals[ch][k] = newval;
	// record the new value
	oldval = newval;
      }
    }
    // Initialize the output buffers.
    if (n_samples < blocksz) {
      // We need to enlarge the buffers. We're not officially allowed to do
      // this here (presumably in the realtime thread), but since we usually
      // don't know the hosts's block size beforehand, there's really nothing
      // else that we can do. Let's just hope that doing this once suffices,
      // then hopefully noone will notice.
      if (outbuf) {
	for (int i = 0; i < m; i++) {
	  outbuf[i] = (float*)realloc(outbuf[i],
				      blocksz*sizeof(float));
	  assert(outbuf[i]);
	}
      }
      n_samples = blocksz;
    }
    if (outbuf) {
      // Pphonic instrument: Mix the voices down to one signal.
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < n_samples; j++)
	  outputs[i][j] = 0.0f;
      for (int l = 0; l < nvoices; l++) {
	// Let Faust do all the hard work.
	dsp[l]->compute(n_samples, inputs, outbuf);
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < n_samples; j++)
	    outputs[i][j] += outbuf[i][j];
      }
    } else {
      // Simple effect: We can write directly to the output buffer.
      dsp[0]->compute(n_samples, inputs, outputs);
    }
    // Finally grab the passive controls and write them back to the
    // corresponding control ports. NOTE: Depending on the plugin
    // architecture, this might require a host call to get the control GUI
    // updated in real-time (if the host supports this at all).
    // FIXME: It's not clear how to aggregate the data of the different
    // voices. We compute the maximum of each control for now.
    for (int i = 0; i < n_out; i++) {
      int j = outctrls[i], k = ui[0]->elems[j].port;
      float *z = ui[0]->elems[j].zone;
      ports[k] = *z;
      for (int l = 1; l < nvoices; l++) {
	float *z = ui[l]->elems[j].zone;
	if (ports[k] < *z)
	  ports[k] = *z;
      }
    }
    // Keep track of the last gates set for each voice, so that voices can be
    // forcibly retriggered if needed.
    if (gate >= 0)
      for (int i = 0; i < nvoices; i++)
	vd->lastgate[i] =
	  *ui[i]->elems[gate].zone;
  }

  // This processes just a single MIDI message, so to process an entire series
  // of MIDI events you'll have to loop over the event data in the plugin's
  // MIDI callback. XXXTODO: Sample-accurate processing of MIDI events.
  
  void process_midi(unsigned char *data, int sz)
  {
#if DEBUG_MIDI
    fprintf(stderr, "midi ev (%d bytes):", sz);
    for (int i = 0; i < sz; i++)
      fprintf(stderr, " 0x%0x", data[i]);
    fprintf(stderr, "\n");
#endif
    uint8_t status = data[0] & 0xf0, chan = data[0] & 0x0f;
    bool is_instr = maxvoices > 0;
    switch (status) {
    case 0x90: {
      if (!is_instr) break;
      // note on
#if DEBUG_NOTES
      fprintf(stderr, "note-on  chan %d, note %d, vel %d\n", chan+1,
	      data[1], data[2]);
#endif
      if (data[2] == 0) goto note_off;
      alloc_voice(chan, data[1], data[2]);
      break;
    }
    case 0x80: {
      if (!is_instr) break;
      // note off
#if DEBUG_NOTES
      fprintf(stderr, "note-off chan %d, note %d, vel %d\n", chan+1,
	      data[1], data[2]);
#endif
      note_off:
      dealloc_voice(chan, data[1], data[2]);
      break;
    }
    case 0xe0: {
      if (!is_instr) break;
      // pitch bend
      // data[1] is LSB, data[2] MSB, range is 0..0x3fff (which maps to
      // -2..+2 semitones by default), center point is 0x2000 = 8192
      int val = data[1] | (data[2]<<7);
      vd->bend[chan] =
	(val-0x2000)/8192.0f*vd->range[chan];
#if DEBUG_MIDICC
      fprintf(stderr, "pitch-bend (chan %d): %g cent\n", chan+1,
	      vd->bend[chan]*100.0);
#endif
      update_voices(chan);
      break;
    }
    case 0xb0: {
      // controller change
      switch (data[1]) {
      case 120: case 123:
	if (!is_instr) break;
	// all-sound-off and all-notes-off controllers (these are treated
	// the same in the current implementation)
	all_notes_off(chan);
#if DEBUG_MIDICC
	fprintf(stderr, "all-notes-off (chan %d)\n", chan+1);
#endif
	break;
      case 121:
	// all-controllers-off (in the current implementation, this just
	// resets the RPN-related controllers)
	data_msb[chan] = data_lsb[chan] = 0;
	rpn_msb[chan] = rpn_lsb[chan] = 0x7f;
#if DEBUG_MIDICC
	fprintf(stderr, "all-controllers-off (chan %d)\n", chan+1);
#endif
	break;
      case 101: case 100:
	// RPN MSB/LSB
	if (data[1] == 101)
	  rpn_msb[chan] = data[2];
	else
	  rpn_lsb[chan] = data[2];
	break;
      case 6: case 38:
	// data entry coarse/fine
	if (data[1] == 6)
	  data_msb[chan] = data[2];
	else
	  data_lsb[chan] = data[2];
	goto rpn;
      case 96: case 97:
	// data increment/decrement
	/* NOTE: The specification of these controllers is a complete
	   mess. Originally, the MIDI specification didn't have anything
	   to say about their exact behaviour at all. Nowadays, the
	   behaviour depends on which RPN or NRPN is being modified, which
	   is also rather confusing. Fortunately, as we only handle RPNs
	   0..2 here anyway, it's sufficient to assume the MSB for RPN #2
	   (channel coarse tuning) and the LSB otherwise. */
	if (rpn_msb[chan] == 0 && rpn_lsb[chan] == 2) {
	  // modify the MSB
	  if (data[1] == 96 && data_msb[chan] < 0x7f)
	    data_msb[chan]++;
	  else if (data[1] == 97 && data_msb[chan] > 0)
	    data_msb[chan]--;
	} else {
	  // modify the LSB
	  if (data[1] == 96 && data_lsb[chan] < 0x7f)
	    data_lsb[chan]++;
	  else if (data[1] == 97 && data_lsb[chan] > 0)
	    data_lsb[chan]--;
	}
      rpn:
	if (!is_instr) break;
	if (rpn_msb[chan] == 0) {
	  switch (rpn_lsb[chan]) {
	  case 0:
	    // pitch bend range, coarse value is in semitones, fine value
	    // in cents
	    vd->range[chan] = data_msb[chan]+
	      data_lsb[chan]/100.0;
#if DEBUG_RPN
	    fprintf(stderr, "pitch-bend-range (chan %d): %g cent\n", chan+1,
		    vd->range[chan]*100.0);
#endif
	    break;
	  case 1:
	    {
	      // channel fine tuning (14 bit value, range -100..+100 cents)
	      int value = (data_msb[chan]<<7) |
		data_lsb[chan];
	      vd->fine[chan] = (value-8192)/8192.0f;
	    }
	    goto master_tune;
	  case 2:
	    // channel coarse tuning (only msb is used, range -64..+63
	    // semitones)
	    vd->coarse[chan] = data_msb[chan]-64;
	  master_tune:
	    vd->tune[chan] = vd->coarse[chan]+
	      vd->fine[chan];
#if DEBUG_RPN
	    fprintf(stderr, "master-tuning (chan %d): %g cent\n", chan+1,
		    vd->tune[chan]*100.0);
#endif
	    update_voices(chan);
	    break;
	  default:
	    break;
	  }
	}
	break;
      default: {
#if FAUST_MIDICC
	// interpret all other controller changes according to the MIDI
	// controller map defined in the Faust plugin itself
	std::map<uint8_t,int>::iterator it = ctrlmap.find(data[1]);
	if (it != ctrlmap.end()) {
	  // defined MIDI controller
	  int j = inctrls[it->second],
	    k = ui[0]->elems[j].port;
	  float val = ctrlval(ui[0]->elems[j], data[2]);
	  midivals[chan][k] = val;
	  if (is_instr) {
	    // instrument: update running voices on this channel
	    for (boost::circular_buffer<int>::iterator it =
		   vd->used_voices.begin();
		 it != vd->used_voices.end(); it++) {
	      int i = *it;
	      if (vd->note_info[i].ch == chan)
		*ui[i]->elems[j].zone = val;
	    }
	  } else {
	    // simple effect: here we only have a single dsp instance and
	    // we're operating in omni mode, so we just update the control no
	    // matter what the midi channel is
	    *ui[0]->elems[j].zone = val;
	  }
#if DEBUG_MIDICC
	  fprintf(stderr, "ctrl-change chan %d, ctrl %d, val %d\n", chan+1,
		  data[1], data[2]);
#endif
	}
#endif
	break;
      }
      }
      break;
    }
    default:
      break;
    }
  }

  // Process an MTS sysex message and update the control values accordingly.

  void process_sysex(uint8_t *data, int sz)
  {
    if (!data || sz < 2) return;
#if DEBUG_MIDI
    fprintf(stderr, "midi sysex (%d bytes):", sz);
    for (int i = 0; i < sz; i++)
      fprintf(stderr, " 0x%0x", data[i]);
    fprintf(stderr, "\n");
#endif
    if (data[0] == 0xf0) {
      // Skip over the f0 and f7 status bytes in case they are included in the
      // dump.
      data++; sz--;
      if (data[sz-1] == 0xf7) sz--;
    }
    if ((data[0] == 0x7e || data[0] == 0x7f) && data[2] == 8) {
      // MIDI tuning standard
      bool realtime = data[0] == 0x7f;
      if ((sz == 19 && data[3] == 8) ||
	  (sz == 31 && data[3] == 9)) {
	// MTS scale/octave tuning 1- or 2-byte form
	bool onebyte = data[3] == 8;
	unsigned chanmsk = (data[4]<<14) | (data[5]<<7) | data[6];
	for (int i = 0; i < 12; i++) {
	  float t;
	  if (onebyte)
	    t = (data[i+7]-64)/100.0;
	  else
	    t = (((data[2*i+7]<<7)|data[2*i+8])-8192)/8192.0;
	  for (uint8_t ch = 0; ch < 16; ch++)
	    if (chanmsk & (1<<ch))
	      vd->tuning[ch][i] = t;
	}
	if (realtime) {
	  for (uint8_t ch = 0; ch < 16; ch++)
	    if (chanmsk & (1<<ch)) {
	      // update running voices on this channel
	      update_voices(ch);
	    }
	}
#if DEBUG_MTS
	fprintf(stderr, "octave-tuning-%s (chan ",
		realtime?"realtime":"non-realtime");
	bool first = true;
	for (uint8_t i = 0; i < 16; )
	  if (chanmsk & (1<<i)) {
	    uint8_t j;
	    for (j = i+1; j < 16 && (chanmsk&(1<<j)); )
	      j++;
	    if (first)
	      first = false;
	    else
	      fprintf(stderr, ",");
	    if (j > i+1)
	      fprintf(stderr, "%u-%u", i+1, j);
	    else
	      fprintf(stderr, "%u", i+1);
	    i = j;
	  } else
	    i++;
	fprintf(stderr, "):");
	if (onebyte) {
	  for (int i = 7; i < 19; i++) {
	    int val = data[i];
	    fprintf(stderr, " %d", val-64);
	  }
	} else {
	  for (int i = 7; i < 31; i++) {
	    int val = data[i++] << 7;
	    val |= data[i];
	    fprintf(stderr, " %g", ((double)val-8192.0)/8192.0*100.0);
	  }
	}
	fprintf(stderr, "\n");
#endif
      }
    }
  }

  // Change to a given preloaded tuning. The given tuning number may be in the
  // range 1..PFaustPlugin::n_tunings, zero denotes the default tuning (equal
  // temperament). This is only supported if FAUST_MTS is defined at compile
  // time.

  void change_tuning(int num)
  {
#if FAUST_MTS
    if (!mts || num == tuning) return;
    if (num < 0) num = 0;
    if (num > mts->tuning.size())
      num = mts->tuning.size();
    tuning = num;
    if (tuning > 0) {
      process_sysex(mts->tuning[tuning-1].data,
		    mts->tuning[tuning-1].len);
    } else {
      memset(vd->tuning, 0, sizeof(vd->tuning));
#if DEBUG_MTS
      fprintf(stderr,
	      "octave-tuning-default (chan 1-16): equal temperament\n");
#endif
#endif
    }
  }

};

Meta *PFaustPlugin::meta = 0;
int PFaustPlugin::n_tunings = 0;
#if FAUST_MTS
MTSTunings *PFaustPlugin::mts = 0;
#endif

/* VST-specific part starts here. ********************************************/

#include "audioeffectx.h"

class VSTWrapper : public AudioEffectX
{
public:
  VSTWrapper(audioMasterCallback audioMaster);
  ~VSTWrapper();

  virtual void processReplacing(float **inputs, float **outputs,
				VstInt32 sampleframes);
  virtual VstInt32 processEvents(VstEvents* events);

  virtual void suspend();
  virtual void resume();
  virtual void setSampleRate(float sampleRate);

  virtual void setProgram(VstInt32 program);
  virtual void setProgramName(const char *name);
  virtual void getProgramName(char *name);
  virtual bool getProgramNameIndexed(VstInt32 category,
				     VstInt32 index, char* text);

  virtual void setParameter(VstInt32 index, float value);
  virtual float getParameter(VstInt32 index);
  virtual bool string2parameter(VstInt32 index, char *text);
  virtual void getParameterLabel(VstInt32 index, char *label);
  virtual void getParameterDisplay(VstInt32 index, char *text);
  virtual void getParameterName(VstInt32 index, char *text);

  virtual bool getInputProperties(VstInt32 index,
				  VstPinProperties *properties);
  virtual bool getOutputProperties(VstInt32 index,
				   VstPinProperties* properties);

  virtual bool getEffectName(char* name);
  virtual bool getVendorString(char* text);
  virtual bool getProductString(char* text);
  virtual VstInt32 getVendorVersion();
  virtual VstInt32 canDo(char* text);

  // We process all MIDI channels on input.
  virtual VstInt32 getNumMidiInputChannels()  { return 16; }
  // No MIDI output for now. XXXTODO: We might want to do MIDI controller
  // output for passive Faust controls in the future.
  virtual VstInt32 getNumMidiOutputChannels()  { return 0; }

private:
  PFaustPlugin *plugin;
  char progname[kVstMaxProgNameLen+1];
  float *defprog;
};

// Create a "unique" VST plugin ID using Murmur2 hashes. This can't possibly
// avoid all collisions, but will hopefully be good enough.

// Code pilfered from http://code.google.com/p/smhasher/.
static uint32_t MurmurHash2(const void *key, int len, uint32_t seed)
{
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.

  const uint32_t m = 0x5bd1e995;
  const int r = 24;

  // Initialize the hash to a 'random' value

  uint32_t h = seed ^ len;

  // Mix 4 bytes at a time into the hash

  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
  {
    uint32_t k = *(uint32_t*)data;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array

  switch(len)
  {
  case 3: h ^= data[2] << 16;
  case 2: h ^= data[1] << 8;
  case 1: h ^= data[0];
      h *= m;
  };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

static uint32_t idhash(const char *s)
{
  // Arbitrary seed value (should be the same for all instances).
  const uint32_t seed = 4711;
  // XXXFIXME: The rules for valid-formed VST ids don't seem to be very
  // clear. Can it be just any 32 bit number? But it looks like at least the
  // most significant bit should be 0 here, so we enforce that. (Some VST
  // hosts such as Carla display the id as zero otherwise.)
  return MurmurHash2(s, strlen(s), seed) & 0x7fffffff;
}

// initialization and finalization

// This interface function is used by the code in vstplugmain.cpp to create an
// instance of the plugin. It simply invokes the constructor of our VSTWrapper
// class here.
AudioEffect *createEffectInstance(audioMasterCallback audioMaster)
{
  return new VSTWrapper(audioMaster);
}

VSTWrapper::VSTWrapper(audioMasterCallback audioMaster)
  : AudioEffectX(audioMaster, 1, PFaustPlugin::numControls())
{
  const char *dsp_name = PFaustPlugin::pluginName();
  const int num_voices = PFaustPlugin::numVoices();
  // Get the initial sample rate from the VST host.
  const int rate = getSampleRate();
  plugin = new PFaustPlugin(num_voices, rate);
  // VST-specific initialization:
  if (audioMaster) {
    setNumInputs(plugin->dsp[0]->getNumInputs());
    setNumOutputs(plugin->dsp[0]->getNumOutputs());		
    canProcessReplacing();
    if (plugin->maxvoices > 0) isSynth();
    // XXXFIXME: Maybe do something more clever for the unique id.
    setUniqueID((VstInt32)idhash(dsp_name));
  }
  // We only provide one "program" (a.k.a. built-in control preset), which
  // corresponds to the initial input control values in the Faust UI. Faust
  // has no built-in support for presets and we don't try to emulate that here
  // either. Most VST hosts will provide you with a way to save and restore
  // presets in a number of different formats, such as fxb and fxp files.
  curProgram = 0;
  setProgramName("Default");
  // Initialize the program storage.
  defprog = (float*)calloc(plugin->n_in, sizeof(float));
  assert(plugin->n_in == 0 || defprog);
  // At this point, the first n_in elements of plugin->ports should already be
  // filled with the initial input control values, copy them over to the
  // default program.
  memcpy(defprog, plugin->ports, plugin->n_in*sizeof(float));
}

VSTWrapper::~VSTWrapper()
{
  delete plugin;
  if (defprog) free(defprog);
}

// plugin activation and deactivation

void VSTWrapper::suspend()
{
  plugin->suspend();
}

void VSTWrapper::resume()
{
  plugin->rate = getSampleRate();
  plugin->resume();
}

void VSTWrapper::setSampleRate(float sampleRate)
{
  AudioEffect::setSampleRate(sampleRate);
  plugin->set_rate(sampleRate);
}

// programs a.k.a. built-in presets (see above)

void VSTWrapper::setProgram(VstInt32 prog)
{
  if (prog < 0 || prog >= 1) return;
  curProgram = prog;
  memcpy(plugin->ports, defprog, plugin->n_in*sizeof(float));
  // Also reset the polyphony and tuning controls to their default values.
  plugin->poly = plugin->maxvoices/2;
  plugin->change_tuning(0);
  // Some hosts may require this to force a GUI update of the parameters.
  updateDisplay();
}

void VSTWrapper::setProgramName(const char* name)
{
  vst_strncpy(progname, name, kVstMaxProgNameLen);
}

void VSTWrapper::getProgramName(char *name)
{
  vst_strncpy(name, progname, kVstMaxProgNameLen);
}

bool VSTWrapper::getProgramNameIndexed(VstInt32 category, VstInt32 index, 
				       char* text)
{
  if (index < 1) {
    vst_strncpy(text, progname, kVstMaxProgNameLen);
    return true;
  } else
    return false;
}

// control values (setters, getters, meta data)

void VSTWrapper::getParameterName(VstInt32 index, char *label)
{
  int k = plugin->ui[0]->nports;
  strcpy(label, "");
  if (index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    // Note that the VST spec mandates a maximum size of kVstMaxParamStrLen
    // for the label string, which is a rather small constant. This seems
    // overly restrictive, however, given that virtually all VST hosts provide
    // for much longer names. We allow 32 characters here which is hopefully
    // on the safe side.
    vst_strncpy(label, plugin->ui[0]->elems[j].label, 32);
  } else if (index == k && plugin->maxvoices > 0) {
    strcpy(label, "polyphony");
#if FAUST_MTS
  } else if (index == k+1 && plugin->n_tunings > 0) {
    strcpy(label, "tuning");
#endif
  }
}

void VSTWrapper::getParameterLabel(VstInt32 index, char *label)
{
  int k = plugin->ui[0]->nports;
  strcpy(label, "");
  if (index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    if (plugin->units[index])
      // Allow for up to 32 characters; see the remarks concerning
      // kVstMaxParamStrLen above.
      vst_strncpy(label, plugin->units[index], 32);
  }
}

// NOTE: VST parameters are always floats with unit range (0..1). So we need
// to convert between Faust control values with given range/stepsize and the
// VST range here. We use the following quantization algorithm for mapping VST
// to Faust control values.

static double quantize(double x, double d)
{
  if (d == 0.0) return x;
  // Round off x to the nearest increment of d. Note that this may produce
  // rounding artifacts if d is some power of 10 less than 0, since these
  // can't be represented exactly in binary.
  double i;
  if (x*d < 0.0)
    modf(x/d-0.5, &i);
  else
    modf(x/d+0.5, &i);
  return i*d;
}

void VSTWrapper::getParameterDisplay(VstInt32 index, char *text)
{
  int k = plugin->ui[0]->nports;
  strcpy(text, "");
  if (index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    sprintf(text, "%0.5g", plugin->ports[index]);
  } else if (index == k && plugin->maxvoices > 0) {
    sprintf(text, "%d voices", plugin->poly);
#if FAUST_MTS
  } else if (index == k+1 && plugin->n_tunings > 0) {
    sprintf(text, "%d %s", plugin->tuning,
	    plugin->tuning>0?plugin->mts->tuning[plugin->tuning-1].name:
	    "default");
#endif
  }
}

float VSTWrapper::getParameter(VstInt32 index)
{
  int k = plugin->ui[0]->nports;
  if (index >= 0 && index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    float min = plugin->ui[0]->elems[j].min;
    float max = plugin->ui[0]->elems[j].max;
    if (min == max)
      return 0.0f;
    else
      return (plugin->ports[index]-min)/(max-min);
  } else if (index == k && plugin->maxvoices > 0) {
    return (float)plugin->poly/(float)plugin->maxvoices;
#if FAUST_MTS
  } else if (index == k+1 && plugin->n_tunings > 0) {
    return (float)plugin->tuning/(float)plugin->mts->tuning.size();
#endif
  } else
    return 0.0f;
}

void VSTWrapper::setParameter(VstInt32 index, float value)
{
  const double eps = 1e-5;
  int k = plugin->ui[0]->nports;
  if (index >= 0 && index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    // XXXTODO: We use a rather simple-minded quantization algorithm here, do
    // something more comprehensive in the future.
    float min = plugin->ui[0]->elems[j].min;
    float max = plugin->ui[0]->elems[j].max;
    float step = plugin->ui[0]->elems[j].step;
    float val = (min == max)?min:min+quantize(value*(max-min), step);
    if (fabs(val) < fabs(step) || fabs(val)/fabs(max-min) < eps)
      val = 0.0;
    // We only need to update the port value here, the ui values are then
    // updated automatically as needed in the process_audio() callback.
    plugin->ports[index] = val;
  } else if (index == k && plugin->maxvoices > 0) {
    plugin->poly = (int)quantize((value*plugin->maxvoices), 1);
    if (plugin->poly <= 0) plugin->poly = 1;
#if FAUST_MTS
  } else if (index == k+1 && plugin->n_tunings > 0) {
    int tuning = (int)quantize((value*plugin->mts->tuning.size()), 1);
    plugin->change_tuning(tuning);
#endif
  }
}

bool VSTWrapper::string2parameter(VstInt32 index, char *text)
{
  if (!text) return true;
  int k = plugin->ui[0]->nports;
  if (index >= 0 && index < k) {
    int j = plugin->ctrls[index];
    assert(index == plugin->ui[0]->elems[j].port);
    float min = plugin->ui[0]->elems[j].min;
    float max = plugin->ui[0]->elems[j].max;
    float step = plugin->ui[0]->elems[j].step;
    double val = atof(text);
    if (min == max)
      val = min;
    else
      val = min+quantize(val-min, step);
    if (min > max) {
      float m = max;
      max = min; min = m;
    }
    if (val < min)
      val = min;
    else if (val > max)
      val = max;
    plugin->ports[index] = val;
  } else if (index == k && plugin->maxvoices > 0) {
    int val = atoi(text);
    if (val <= 0) val = 1;
    if (val > plugin->maxvoices) val = plugin->maxvoices;
    plugin->poly = val;
#if FAUST_MTS
  } else if (index == k+1 && plugin->mts &&
	     plugin->mts->tuning.size() > 0) {
    plugin->change_tuning(atoi(text));
#endif
  } else
    return false;
  return true;
}

// audio inputs and outputs

bool VSTWrapper::getInputProperties(VstInt32 index,
				    VstPinProperties* properties)
{
  const char *dsp_name = PFaustPlugin::pluginName();
  const int n = plugin->dsp[0]->getNumInputs();
  if (index < 0 || index >= n)
    return false;
  snprintf(properties->label, kVstMaxLabelLen,
	   "%s input #%d", dsp_name, index);
  sprintf(properties->shortLabel, "In%d", index);
  properties->flags = kVstPinIsActive;
  // XXXTODO: deal with multi-channel setups (>2) here
  if (n == 2)
    properties->flags |= kVstPinIsStereo;
  return true;
}

bool VSTWrapper::getOutputProperties(VstInt32 index,
				     VstPinProperties* properties)
{
  const char *dsp_name = PFaustPlugin::pluginName();
  const int n = plugin->dsp[0]->getNumOutputs();
  if (index < 0 || index >= n)
    return false;
  snprintf(properties->label, kVstMaxLabelLen,
	   "%s output #%d", dsp_name, index);
  sprintf(properties->shortLabel, "Out%d", index);
  properties->flags = kVstPinIsActive;
  // XXXTODO: deal with multi-channel setups (>2) here
  if (n == 2)
    properties->flags |= kVstPinIsStereo;
  return true;
}

// global meta data

bool VSTWrapper::getEffectName(char *name)
{
  const char *dsp_name = PFaustPlugin::pluginName();
  vst_strncpy(name, dsp_name, kVstMaxEffectNameLen);
  return true;
}

bool VSTWrapper::getVendorString(char *text)
{
  const char *vendorString = PFaustPlugin::pluginAuthor();
  vst_strncpy(text, vendorString, kVstMaxVendorStrLen);
  return true;
}

bool VSTWrapper::getProductString(char *text)
{
  const char *productString = PFaustPlugin::pluginDescription();
  vst_strncpy(text, productString, kVstMaxProductStrLen);
  return true;
}

VstInt32 VSTWrapper::getVendorVersion()
{ 
  const char *versionString = PFaustPlugin::pluginVersion();
  return (VstInt32)(atof(versionString)*1000.0);
}

VstInt32 VSTWrapper::canDo(char *text)
{
  if (strcmp(text, "receiveVstEvents") == 0) return 1;
  if (strcmp(text, "receiveVstMidiEvent") == 0) return 1;
  // This may convince some VST hosts to send us sysex events (seems to be
  // supported by some Bitwig versions at least).
  if (strcmp(text, "receiveVstSysexEvent") == 0) return 1;
  return -1;
}

// audio and MIDI process functions

void VSTWrapper::processReplacing(float **inputs, float **outputs,
				  VstInt32 n_samples)
{
  plugin->process_audio(n_samples, inputs, outputs);
  // Some hosts may require this to force a GUI update of the passive
  // controls. XXXFIXME: Alas, some hosts don't seem to handle output
  // parameters at all (e.g., Tracktion).
  if (plugin->n_out > 0) updateDisplay();
}

VstInt32 VSTWrapper::processEvents(VstEvents* events)
{
  // Process incoming MIDI events.
  for (VstInt32 i = 0; i < events->numEvents; i++) {
    if (events->events[i]->type == kVstMidiType) {
      VstMidiEvent* ev = (VstMidiEvent*)events->events[i];
      uint8_t *data = (uint8_t*)ev->midiData;
#if 0
      // FIXME: Consider doing sample-accurate note onsets here. VST keeps
      // track of the exact onset in the deltaFrames field, but we can't use
      // that information at present, since our gate parameter is a control
      // variable which can only change at block boundaries. In the future,
      // the gate could be implemented as an audio signal to get
      // sample-accurate note onsets.
      VstInt32 frames = ev->deltaFrames;
#endif
#if 0
      fprintf(stderr, "ev length = %d, offset = %d, detune = %d, off velocity = %d\n", ev->noteLength, ev->noteOffset, (int)(signed char)ev->detune, (int)ev->noteOffVelocity);
#endif
      plugin->process_midi(data, 4);
    } else if (events->events[i]->type == kVstSysExType) {
      VstMidiSysexEvent* ev = (VstMidiSysexEvent*)events->events[i];
      int sz = ev->dumpBytes;
      uint8_t *data = (uint8_t*)ev->sysexDump;
      bool is_instr = plugin->maxvoices > 0;
      if (!is_instr) continue;
      plugin->process_sysex(data, sz);
    } else {
      fprintf(stderr, "%s: unknown event type %d\n",
	      PFaustPlugin::pluginName(), events->events[i]->type);
    }
  }
  return 1;
}
