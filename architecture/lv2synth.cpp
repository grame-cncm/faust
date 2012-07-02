/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2009-2011 Albert Graef <Dr.Graef@t-online.de>
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

/* LV2 architecture for Faust synths. */

/* NOTE: This requires one of the Boost headers (boost/circular_buffer.hpp),
   so to compile Faust programs created with this architecture you need to
   have at least the Boost headers installed somewhere on your include path
   (the Boost libraries aren't needed). */

#include <stdlib.h>
#include <math.h>
#include <list>
#include <map>

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

struct Meta
{
  list< strpair > data;
  void declare (const char* key, const char* value)
  { data.push_back(strpair(key, value)); }
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
   LV2 UI interface
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

class LV2UI : public UI
{
public:
  int nelems, nports;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  LV2UI();
  virtual ~LV2UI();

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

LV2UI::LV2UI()
{
  nelems = nports = 0;
  elems = NULL;
}

LV2UI::~LV2UI()
{
  if (elems) free(elems);
}

void LV2UI::declare(float* zone, const char* key, const char* value)
{
  map< int, list<strpair> >::iterator it = metadata.find(nelems);
  if (it != metadata.end())
    it->second.push_back(strpair(key, value));
  else
    metadata[nelems] = list<strpair>(1, strpair(key, value));
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label)
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

#define portno(label) (is_voice_ctrl(label)?-1:nports++)

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone)
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
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float init, float min, float max, float step)
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

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float min, float max)
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

void LV2UI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void LV2UI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void LV2UI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void LV2UI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void LV2UI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void LV2UI::openTabBox(const char* label)
{ add_elem(UI_T_GROUP, label); }
void LV2UI::openHorizontalBox(const char* label)
{ add_elem(UI_H_GROUP, label); }
void LV2UI::openVerticalBox(const char* label)
{ add_elem(UI_V_GROUP, label); }
void LV2UI::closeBox()
{ add_elem(UI_END_GROUP); }

void LV2UI::run() {}

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
//  LV2 interface
//----------------------------------------------------------------------------

//#line 400 "lv2synth.cpp"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bitset>
#include <boost/circular_buffer.hpp>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/dynmanifest/dynmanifest.h>
#include <lv2/lv2plug.in/ns/ext/event/event-helpers.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

#ifndef URI_PREFIX
#define URI_PREFIX "http://faust-lv2.googlecode.com"
#endif

#ifndef PLUGIN_URI
#define PLUGIN_URI URI_PREFIX "/mydsp"
#endif

#define MIDI_EVENT_URI "http://lv2plug.in/ns/ext/midi#MidiEvent"

#ifndef NVOICES
#define NVOICES 16
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

struct LV2SynthPlugin {
  bool active;		// activation status
  int rate;		// sampling rate
  int nvoices;		// current number of voices (polyphony; <= NVOICES)
  mydsp *dsp[NVOICES];	// the dsps
  LV2UI *ui[NVOICES];	// their Faust interface descriptions
  int n_in, n_out;	// number of input and output control ports
  int *ctrls;		// Faust ui elements (indices into ui->elems)
  float **ports;	// corresponding LV2 data
  float *portvals;	// cached port data from the last run
  float *midivals[16];	// per-midi channel data
  int *inctrls, *outctrls;	// indices for active and passive controls
  float **inputs, **outputs;	// audio buffers
  int freq, gain, gate;	// indices of voice controls
  unsigned n_samples;	// current block size
  float **outbuf;	// audio buffers for mixing down the voices
  float **inbuf;	// dummy input buffer
  LV2_Event_Buffer* event_port;	// midi input
  float *poly;		// polyphony port
  std::map<uint8_t,int> ctrlmap; // MIDI controller map
  // Needed host features (the uri-map extension is officially deprecated, but
  // still needed for some if not most hosts at the time of this writing).
  LV2_URI_Map_Feature* uri_map;
  LV2_URID_Map* map;	// the new urid extension
  LV2_URID midi_event;	// midi event uri
  LV2_Event_Feature* event_ref;
  // Octave tunings (offsets in semitones) per MIDI channel.
  float tuning[16][12];
  // Allocated voices per MIDI channel and note.
  int8_t notes[16][128];
  // Free and used voices.
  int n_free, n_used;
  boost::circular_buffer<int> free_voices;
  boost::circular_buffer<int> used_voices;
  struct {
    uint8_t ch;
    int8_t note;
  } note_info[NVOICES];
  // Voices queued for note-offs (zero-length notes).
  int n_queued;
  bitset<NVOICES> queued;
  // Last gate value during run() for each voice. We need to keep track of
  // these so that we can force the Faust synth to retrigger a note when
  // needed.
  float lastgate[NVOICES];
  // Current pitch bend and pitch bend range on each MIDI channel, in semitones.
  float bend[16], range[16];
  // Current coarse, fine and total master tuning on each MIDI channel (tuning
  // offset relative to A4 = 440 Hz, in semitones).
  float coarse[16], fine[16], tune[16];
  // Current RPN MSB and LSB numbers, as set with controllers 101 and 100.
  uint8_t rpn_msb[16], rpn_lsb[16];
  // Current data entry MSB and LSB numbers, as set with controllers 6 and 38.
  uint8_t data_msb[16], data_lsb[16];

  LV2SynthPlugin() : free_voices(NVOICES), used_voices(NVOICES) {
    active = false;
    rate = 44100;
    nvoices = NVOICES;
    n_in = n_out = 0;
    uri_map = NULL; map = NULL;
    midi_event = -1;
    event_ref = NULL;
    event_port = NULL;
    poly = NULL;
    freq = gain = gate = -1;
    n_free = NVOICES;
    for (int i = 0; i < NVOICES; i++) {
      free_voices.push_back(i);
      lastgate[i] = 0.0f;
    }
    for (int i = 0; i < 16; i++) {
      bend[i] = 0.0f;
      range[i] = 2.0f;
      coarse[i] = fine[i] = tune[i] = 0.0f;
      rpn_msb[i] = rpn_lsb[i] = 0x7f;
      data_msb[i] = data_lsb[i] = 0;
      for (int j = 0; j < 12; j++)
	tuning[i][j] = 0.0f;
    }
    n_used = 0;
    n_queued = 0;
    n_samples = 0;
    memset(dsp, 0, sizeof(dsp));
    memset(ui, 0, sizeof(ui));
    memset(notes, 0xff, sizeof(notes));
    ctrls = inctrls = outctrls = NULL;
    ports = inputs = outputs = inbuf = outbuf = NULL;
    portvals = NULL;
    memset(midivals, 0, sizeof(midivals));
  }

  // Voice allocation.

#if DEBUG_VOICE_ALLOC
  void print_voices(const char *msg)
  {
    fprintf(stderr, "%s: notes =", msg);
    for (uint8_t ch = 0; ch < 16; ch++)
      for (int note = 0; note < 128; note++)
	if (notes[ch][note] >= 0)
	  fprintf(stderr, " [%d] %d(#%d)", ch, note, notes[ch][note]);
    fprintf(stderr, "\nqueued (%d):", n_queued);
    for (int i = 0; i < nvoices; i++)
      if (queued[i]) fprintf(stderr, " #%d", i);
    fprintf(stderr, "\nused (%d):", n_used);
    for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	 it != used_voices.end(); it++)
      fprintf(stderr, " #%d->%d", *it, note_info[*it].note);
    fprintf(stderr, "\nfree (%d):", n_free);
    for (boost::circular_buffer<int>::iterator it = free_voices.begin();
	 it != free_voices.end(); it++)
      fprintf(stderr, " #%d", *it);
    fprintf(stderr, "\n");
  }
#endif

  int alloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = notes[ch][note];
    if (i >= 0) {
      // note already playing on same channel, retrigger it
      voice_off(i);
      voice_on(i, note, vel, ch);
      // move this voice to the end of the used list
      for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	   it != used_voices.end(); it++) {
	if (*it == i) {
	  used_voices.erase(it);
	  used_voices.push_back(i);
	  break;
	}
      }
#if DEBUG_VOICE_ALLOC
      print_voices("retrigger");
#endif
      return i;
    } else if (n_free > 0) {
      // take voice from free list
      int i = free_voices.front();
      free_voices.pop_front();
      n_free--;
      used_voices.push_back(i);
      note_info[i].ch = ch;
      note_info[i].note = note;
      n_used++;
      voice_on(i, note, vel, ch);
      notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("alloc");
#endif
      return i;
    } else {
      // steal a voice
      assert(n_used > 0);
      // FIXME: Maybe we should look for the oldest note on the *current*
      // channel here, but this is faster.
      int i = used_voices.front();
      int oldch = note_info[i].ch;
      int oldnote = note_info[i].note;
      voice_off(i);
      notes[oldch][oldnote] = -1;
      if (queued[i]) {
	queued[i] = false;
	n_queued--;
      }
      used_voices.pop_front();
      used_voices.push_back(i);
      note_info[i].ch = ch;
      note_info[i].note = note;
      voice_on(i, note, vel, ch);
      notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("steal");
#endif
      return i;
    }
  }

  int dealloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = notes[ch][note];
    if (i >= 0) {
      if (lastgate[i] == 0.0f && gate >= 0) {
	// zero-length note, queued for later
	if (!queued[i]) {
	  queued[i] = true;
	  n_queued++;
	  notes[ch][note] = -1;
	}
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (queued)");
#endif
	return i;
      }
      assert(n_free < nvoices);
      free_voices.push_back(i);
      n_free++;
      voice_off(i);
      notes[ch][note] = -1;
      // erase this voice from the used list
      for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	   it != used_voices.end(); it++) {
	if (*it == i) {
	  used_voices.erase(it);
	  n_used--;
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
    float pitch = note + tune[chan] + tuning[chan][note%12] + bend[chan];
    return 440.0*pow(2, (pitch-69.0)/12.0);
  }

  void voice_on(int i, int8_t note, int8_t vel, uint8_t ch)
  {
    if (lastgate[i] == 1.0f && gate >= 0) {
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
    for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	 it != used_voices.end(); it++) {
      int i = *it;
      if (note_info[i].ch == chan && freq >= 0) {
	int note = note_info[i].note;
	*ui[i]->elems[freq].zone = midicps(note, chan);
      }
    }
  }

  void all_notes_off()
  {
    for (int i = 0; i < nvoices; i++)
      voice_off(i);
    for (int i = 0; i < 16; i++)
      bend[i] = 0.0f;
    memset(notes, 0xff, sizeof(notes));
    free_voices.clear();
    n_free = nvoices;
    for (int i = 0; i < nvoices; i++)
      free_voices.push_back(i);
    queued.reset();
    n_queued = 0;
    used_voices.clear();
    n_used = 0;
  }

  void all_notes_off(uint8_t chan)
  {
    for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	 it != used_voices.end(); ) {
      int i = *it;
      if (note_info[i].ch == chan) {
	assert(n_free < nvoices);
	free_voices.push_back(i);
	n_free++;
	voice_off(i);
	notes[note_info[i].ch][note_info[i].note] = -1;
	if (queued[i]) {
	  queued[i] = false;
	  n_queued--;
	}
	// erase this voice from the used list
	it = used_voices.erase(it);
	n_used--;
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (all-notes-off)");
#endif
      } else
	it++;
    }
    bend[chan] = 0.0f;
  }

  void queued_notes_off()
  {
    if (n_queued == 0) return;
    for (int i = 0; i < nvoices; i++)
      if (queued[i]) {
	assert(n_free < nvoices);
	free_voices.push_back(i);
	n_free++;
	voice_off(i);
	notes[note_info[i].ch][note_info[i].note] = -1;
	queued[i] = false;
	n_queued--;
	// erase this voice from the used list
	for (boost::circular_buffer<int>::iterator it = used_voices.begin();
	     it != used_voices.end(); it++) {
	  if (*it == i) {
	    used_voices.erase(it);
	    n_used--;
	    break;
	  }
	}
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (unqueued)");
#endif
      }
  }
};

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  LV2SynthPlugin* plugin = new LV2SynthPlugin;
  // Scan host features for URID (or URI) map.
  for (int i = 0; features[i]; i++) {
    if (!strcmp(features[i]->URI, LV2_URID_URI "#map")) {
      plugin->map = (LV2_URID_Map*)features[i]->data;
      plugin->midi_event =
	plugin->map->map(plugin->map->handle, MIDI_EVENT_URI);
    } else if (!strcmp(features[i]->URI, LV2_URI_MAP_URI)) {
      plugin->uri_map = (LV2_URI_Map_Feature*)features[i]->data;
      plugin->midi_event =
	plugin->uri_map->uri_to_id(plugin->uri_map->callback_data,
				   LV2_EVENT_URI, MIDI_EVENT_URI);
    } else if (!strcmp(features[i]->URI, LV2_EVENT_URI)) {
      plugin->event_ref = (LV2_Event_Feature *)features[i]->data;
    }
  }
  if (!plugin->map && !plugin->uri_map) {
    fprintf
      (stderr, "%s: host supports neither uri-map or urid:map, giving up\n",
       PLUGIN_URI);
    delete plugin;
    return 0;
  }
  plugin->rate = rate;
  for (int i = 0; i < NVOICES; i++) {
    plugin->dsp[i] = new mydsp();
    plugin->ui[i] = new LV2UI();
    plugin->dsp[i]->init(plugin->rate);
    plugin->dsp[i]->buildUserInterface(plugin->ui[i]);
  }
  // The LV2 ports are numbered as follows: 0..k-1 are the control ports, then
  // come the n audio input ports, then the m audio output ports, and finally
  // the midi input port and the polyphony control.
  int k = plugin->ui[0]->nports, p = 0, q = 0;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  // Allocate tables for the control elements and their LV2 ports.
  plugin->ctrls = (int*)calloc(k, sizeof(int));
  plugin->inctrls = (int*)calloc(k, sizeof(int));
  plugin->outctrls = (int*)calloc(k, sizeof(int));
  plugin->ports = (float**)calloc(k, sizeof(float*));
  plugin->portvals = (float*)calloc(k, sizeof(float));
  assert(k == 0 || (plugin->ctrls && plugin->inctrls && plugin->outctrls &&
		    plugin->ports && plugin->portvals));
  for (int ch = 0; ch < 16; ch++) {
    plugin->midivals[ch] = (float*)calloc(k, sizeof(float));
    assert(k == 0 || plugin->midivals[ch]);
  }
  // Scan the Faust UI for active and passive controls which become the
  // input and output control ports of the LV2 plugin, respectively.
  for (int i = 0, j = 0; i < plugin->ui[0]->nelems; i++) {
    switch (plugin->ui[0]->elems[i].type) {
    case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
      // control groups
      break;
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
      // passive controls (output ports)
      plugin->ctrls[j++] = i;
      plugin->outctrls[q++] = i;
      break;
    default:
      // active controls (input ports)
      if (plugin->freq == -1 &&
	  !strcmp(plugin->ui[0]->elems[i].label, "freq"))
	plugin->freq = i;
      else if (plugin->gain == -1 &&
	       !strcmp(plugin->ui[0]->elems[i].label, "gain"))
	plugin->gain = i;
      else if (plugin->gate == -1 &&
	       !strcmp(plugin->ui[0]->elems[i].label, "gate"))
	plugin->gate = i;
      else {
#if FAUST_MIDICC
	std::map< int, list<strpair> >::iterator it =
	  plugin->ui[0]->metadata.find(i);
	if (it != plugin->ui[0]->metadata.end()) {
	  // Scan for controller mappings.
	  for (std::list<strpair>::iterator jt = it->second.begin();
	       jt != it->second.end(); jt++) {
	    const char *key = jt->first, *val = jt->second;
#if DEBUG_META
	    fprintf(stderr, "ctrl '%s' meta: '%s' -> '%s'\n",
		    plugin->ui[0]->elems[i].label, key, val);
#endif
	    if (strcmp(key, "midi")) continue;
	    unsigned num;
	    if (sscanf(val, "ctrl %u", &num) < 1) continue;
#if 0 // enable this to get feedback about controller assignments
	    fprintf(stderr, "%s: cc %d -> %s\n", PLUGIN_URI, num,
		    plugin->ui[0]->elems[i].label);
#endif
	    plugin->ctrlmap.insert(std::pair<uint8_t,int>(num, p));
	  }
	}
#endif
	plugin->ctrls[j++] = i;
	plugin->inctrls[p++] = i;
	int p = plugin->ui[0]->elems[i].port;
	float val = plugin->ui[0]->elems[i].init;
	plugin->portvals[p] = val;
	for (int ch = 0; ch < 16; ch++)
	  plugin->midivals[ch][p] = val;
      }
      break;
    }
  }
  // Realloc the inctrls and outctrls vectors to their appropriate sizes.
  plugin->inctrls = (int*)realloc(plugin->inctrls, p*sizeof(int));
  assert(p == 0 || plugin->inctrls);
  plugin->outctrls = (int*)realloc(plugin->outctrls, q*sizeof(int));
  assert(q == 0 || plugin->outctrls);
  plugin->n_in = p; plugin->n_out = q;
  // Allocate vectors for the audio input and output ports. Like
  // plugin->ports, these will be initialized in the connect_port callback.
  plugin->inputs = (float**)calloc(n, sizeof(float*));
  assert(n == 0 || plugin->inputs);
  plugin->outputs = (float**)calloc(m, sizeof(float*));
  assert(m == 0 || plugin->outputs);
  // Initialize the mixdown buffer.
  plugin->outbuf = (float**)calloc(m, sizeof(float*));
  assert(m == 0 || plugin->outbuf);
  // We start out with a blocksize of 512 samples here. Hopefully this is
  // enough for most realtime hosts so that we can avoid reallocations in the
  // event loop where we know what the actual blocksize is.
  plugin->n_samples = 512;
  for (int i = 0; i < m; i++) {
    plugin->outbuf[i] = (float*)malloc(plugin->n_samples*sizeof(float));
    assert(plugin->outbuf[i]);
  }
  // Initialize a 1-sample dummy input buffer used for retriggering notes.
  plugin->inbuf = (float**)calloc(n, sizeof(float*));
  assert(n == 0 || plugin->inbuf);
  for (int i = 0; i < m; i++) {
    plugin->inbuf[i] = (float*)malloc(sizeof(float));
    assert(plugin->inbuf[i]);
    *plugin->inbuf[i] = 0.0f;
  }
  return (LV2_Handle)plugin;
}

static void
cleanup(LV2_Handle instance)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)instance;
  int m = plugin->dsp[0]->getNumOutputs();
  for (int i = 0; i < NVOICES; i++) {
    delete plugin->dsp[i];
    delete plugin->ui[i];
  }
  free(plugin->ctrls);
  free(plugin->inctrls);
  free(plugin->outctrls);
  free(plugin->ports);
  free(plugin->portvals);
  free(plugin->inputs);
  free(plugin->outputs);
  for (int ch = 0; ch < 16; ch++)
    free(plugin->midivals[ch]);
  for (int i = 0; i < m; i++)
    free(plugin->outbuf[i]);
  free(plugin->outbuf);
  delete plugin;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)instance;
  int i = port, k = plugin->ui[0]->nports;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  if (i < k)
    plugin->ports[i] = (float*)data;
  else {
    i -= k;
    if (i < n)
      plugin->inputs[i] = (float*)data;
    else {
      i -= n;
      if (i < m)
	plugin->outputs[i] = (float*)data;
      else if (i == m)
	plugin->event_port = (LV2_Event_Buffer*)data;
      else if (i == m+1)
	plugin->poly = (float*)data;
      else
	fprintf(stderr, "%s: bad port number %u\n", PLUGIN_URI, port);
    }
  }
}

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

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)instance;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  AVOIDDENORMALS;
  plugin->queued_notes_off();
  if (!plugin->active) {
    if (n == m) {
      // copy inputs to outputs
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < n_samples; j++)
	  plugin->outputs[i][j] = plugin->inputs[i][j];
    } else {
      // silence
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < n_samples; j++)
	  plugin->outputs[i][j] = 0.0f;
    }
    return;
  }
  // Handle changes in the polyphony control.
  if (plugin->poly) {
    int nvoices = *plugin->poly;
    if (plugin->nvoices != nvoices && nvoices > 0 && nvoices <= NVOICES) {
      for (int i = 0; i < plugin->nvoices; i++)
	plugin->voice_off(i);
      plugin->nvoices = nvoices;
      // Reset the voice allocation.
      memset(plugin->notes, 0xff, sizeof(plugin->notes));
      plugin->free_voices.clear();
      plugin->n_free = nvoices;
      for (int i = 0; i < nvoices; i++)
	plugin->free_voices.push_back(i);
      plugin->used_voices.clear();
      plugin->n_used = 0;
    } else
      *plugin->poly = plugin->nvoices;
  }
  int nvoices = plugin->nvoices;
  // Process incoming MIDI events.
  if (plugin->event_port) {
    LV2_Event_Iterator i;
    for (lv2_event_begin(&i, plugin->event_port);
	 lv2_event_is_valid(&i);
	 lv2_event_increment(&i)) {
      LV2_Event* ev = lv2_event_get(&i, NULL);
      if (ev->type == 0) {
	if (plugin->event_ref) {
	  plugin->event_ref->lv2_event_unref
	    (plugin->event_ref->callback_data, ev);
	}
      } else if (ev->type == plugin->midi_event) {
	uint8_t *data = (uint8_t*)(ev+1);
#if 0
	// FIXME: Consider doing sample-accurate note onsets here. LV2 keeps
	// track of the exact onset in the frames and subframes fields
	// (http://lv2plug.in/ns/doc/html/structLV2__Atom__Event.html), but we
	// can't use that information at present, since our gate parameter is
	// a control variable which can only change at block boundaries. In
	// the future, the gate could be implemented as an audio signal to get
	// sample-accurate note onsets.
	uint32_t frames = ev->frames;
#endif
#if DEBUG_MIDI
	fprintf(stderr, "midi ev (%u bytes):", ev->size);
	for (unsigned i = 0; i < ev->size; i++)
	  fprintf(stderr, " 0x%0x", data[i]);
	fprintf(stderr, "\n");
#endif
	uint8_t status = data[0] & 0xf0, chan = data[0] & 0x0f;
	switch (status) {
	case 0x90: {
	  // note on
#if DEBUG_NOTES
	  fprintf(stderr, "note-on  chan %d, note %d, vel %d\n", chan+1,
		  data[1], data[2]);
#endif
	  // LV2 actually forbids zero velocities here, but we never know how
	  // broken the host is, so we handle this case anyway to be on the safe
	  // side.
	  if (data[2] == 0) goto note_off;
	  plugin->alloc_voice(chan, data[1], data[2]);
	  break;
	}
	case 0x80: {
	  // note off
#if DEBUG_NOTES
	  fprintf(stderr, "note-off chan %d, note %d, vel %d\n", chan+1,
		  data[1], data[2]);
#endif
	  note_off:
	  plugin->dealloc_voice(chan, data[1], data[2]);
	  break;
	}
	case 0xe0: {
	  // pitch bend
	  // data[1] is LSB, data[2] MSB, range is 0..0x3fff (which maps to
	  // -2..+2 semitones by default), center point is 0x2000 = 8192
	  int val = data[1] | (data[2]<<7);
	  plugin->bend[chan] = (val-0x2000)/8192.0f*plugin->range[chan];
#if DEBUG_MIDICC
	  fprintf(stderr, "pitch-bend (chan %d): %g cent\n", chan+1,
		  plugin->bend[chan]*100.0);
#endif
	  plugin->update_voices(chan);
	  break;
	}
	case 0xb0: {
	  // controller change
	  switch (data[1]) {
	  case 120: case 123:
	    // all-sound-off and all-notes-off controllers (these are treated
	    // the same in the current implementation)
	    plugin->all_notes_off(chan);
#if DEBUG_MIDICC
	    fprintf(stderr, "all-notes-off (chan %d)\n", chan+1);
#endif
	    break;
	  case 121:
	    // all-controllers-off (in the current implementation, this just
	    // resets the RPN-related controllers)
	    plugin->data_msb[chan] = plugin->data_lsb[chan] = 0;
	    plugin->rpn_msb[chan] = plugin->rpn_lsb[chan] = 0x7f;
#if DEBUG_MIDICC
	    fprintf(stderr, "all-controllers-off (chan %d)\n", chan+1);
#endif
	    break;
	  case 101: case 100:
	    // RPN MSB/LSB
	    if (data[1] == 101)
	      plugin->rpn_msb[chan] = data[2];
	    else
	      plugin->rpn_lsb[chan] = data[2];
	    break;
	  case 6: case 38:
	    // data entry coarse/fine
	    if (data[1] == 6)
	      plugin->data_msb[chan] = data[2];
	    else
	      plugin->data_lsb[chan] = data[2];
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
	    if (plugin->rpn_msb[chan] == 0 && plugin->rpn_lsb[chan] == 2) {
	      // modify the MSB
	      if (data[1] == 96 && plugin->data_msb[chan] < 0x7f)
		plugin->data_msb[chan]++;
	      else if (data[1] == 97 && plugin->data_msb[chan] > 0)
		plugin->data_msb[chan]--;
	    } else {
	      // modify the LSB
	      if (data[1] == 96 && plugin->data_lsb[chan] < 0x7f)
		plugin->data_lsb[chan]++;
	      else if (data[1] == 97 && plugin->data_lsb[chan] > 0)
		plugin->data_lsb[chan]--;
	    }
	  rpn:
	    if (plugin->rpn_msb[chan] == 0) {
	      switch (plugin->rpn_lsb[chan]) {
	      case 0:
		// pitch bend range, coarse value is in semitones, fine value
		// in cents
		plugin->range[chan] = plugin->data_msb[chan]+
		  plugin->data_lsb[chan]/100.0;
#if DEBUG_RPN
		fprintf(stderr, "pitch-bend-range (chan %d): %g cent\n", chan+1,
			plugin->range[chan]*100.0);
#endif
		break;
	      case 1:
		{
		  // channel fine tuning (14 bit value, range -100..+100 cents)
		  int value = (plugin->data_msb[chan]<<7) |
		    plugin->data_lsb[chan];
		  plugin->fine[chan] = (value-8192)/8192.0f;
		}
		goto master_tune;
	      case 2:
		// channel coarse tuning (only msb is used, range -64..+63
		// semitones)
		plugin->coarse[chan] = plugin->data_msb[chan]-64;
	      master_tune:
		plugin->tune[chan] = plugin->coarse[chan]+plugin->fine[chan];
#if DEBUG_RPN
		fprintf(stderr, "master-tuning (chan %d): %g cent\n", chan+1,
			plugin->tune[chan]*100.0);
#endif
		plugin->update_voices(chan);
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
	    std::map<uint8_t,int>::iterator it = plugin->ctrlmap.find(data[1]);
	    if (it != plugin->ctrlmap.end()) {
	      // defined MIDI controller
	      int j = plugin->inctrls[it->second],
		k = plugin->ui[0]->elems[j].port;
	      float val = ctrlval(plugin->ui[0]->elems[j], data[2]);
	      plugin->midivals[chan][k] = val;
	      // update running voices on this channel
	      for (boost::circular_buffer<int>::iterator it =
		     plugin->used_voices.begin();
		   it != plugin->used_voices.end(); it++) {
		int i = *it;
		if (plugin->note_info[i].ch == chan)
		  *plugin->ui[i]->elems[j].zone = val;
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
	case 0xf0:
	  if (data[0] == 0xf0 && data[ev->size-1] == 0xf7) {
	    // sysex
	    if ((data[1] == 0x7e || data[1] == 0x7f) && data[3] == 8) {
	      // MIDI tuning standard
	      bool realtime = data[1] == 0x7f;
	      if ((ev->size == 21 && data[4] == 8) ||
		  (ev->size == 33 && data[4] == 9)) {
		// MTS scale/octave tuning 1- or 2-byte form
		bool onebyte = data[4] == 8;
		unsigned chanmsk = (data[5]<<14) | (data[6]<<7) | data[7];
		for (int i = 0; i < 12; i++) {
		  float t;
		  if (onebyte)
		    t = (data[i+8]-64)/100.0;
		  else
		    t = (((data[2*i+8]<<7)|data[2*i+9])-8192)/8192.0;
		  for (uint8_t ch = 0; ch < 16; ch++)
		    if (chanmsk & (1<<ch))
		      plugin->tuning[ch][i] = t;
		}
		if (realtime) {
		  for (uint8_t ch = 0; ch < 16; ch++)
		    if (chanmsk & (1<<ch)) {
		      // update running voices on this channel
		      plugin->update_voices(ch);
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
		  for (int i = 8; i < 20; i++) {
		    int val = data[i];
		    fprintf(stderr, " %d", val-64);
		  }
		} else {
		  for (int i = 8; i < 32; i++) {
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
	  break;
	default:
	  break;
	}
      } else {
	fprintf(stderr, "%s: unknown event type %d\n", PLUGIN_URI, ev->type);
      }
    }
  }
  // Only update the controls (of all voices simultaneously) if the port value
  // actually changed. This is necessary to allow MIDI controllers to modify
  // the values for individual MIDI channels (see above). Also note that we do
  // this *after* processing the MIDI controller data so that manual inputs
  // can override these.
  for (int i = 0; i < plugin->n_in; i++) {
    int j = plugin->inctrls[i], k = plugin->ui[0]->elems[j].port;
    float &oldval = plugin->portvals[k], newval = *plugin->ports[k];
    if (newval != oldval) {
      // update running voices
      for (boost::circular_buffer<int>::iterator it =
	     plugin->used_voices.begin();
	   it != plugin->used_voices.end(); it++) {
	int i = *it;
	*plugin->ui[i]->elems[j].zone = newval;
      }
      // also update the MIDI controller data for all channels (manual control
      // input is always omni)
      for (int ch = 0; ch < 16; ch++)
	plugin->midivals[ch][k] = newval;
      // record the new value
      oldval = newval;
    }
  }
  // Initialize the output buffers.
  if (plugin->n_samples < n_samples) {
    // We need to enlarge the buffers. We're not officially allowed to do this
    // here (presumably in the realtime thread), but since we can't know the
    // hosts's block size beforehand, there's really nothing else that we can
    // do. Let's just hope that doing this once suffices, then hopefully
    // noone will notice.
    for (int i = 0; i < m; i++) {
      plugin->outbuf[i] = (float*)realloc(plugin->outbuf[i],
					  n_samples*sizeof(float));
      assert(plugin->outbuf[i]);
    }
    plugin->n_samples = n_samples;
  }
  for (int i = 0; i < m; i++)
    for (unsigned j = 0; j < n_samples; j++)
      plugin->outputs[i][j] = 0.0f;
  // Mix the voices down to one signal.
  for (int l = 0; l < nvoices; l++) {
    // Let Faust do all the hard work.
    plugin->dsp[l]->compute(n_samples, plugin->inputs, plugin->outbuf);
    for (int i = 0; i < m; i++)
      for (unsigned j = 0; j < n_samples; j++)
	plugin->outputs[i][j] += plugin->outbuf[i][j];
  }
  // Finally grab the passive controls and write them back to the
  // corresponding LV2 ports. FIXME: It's not clear how to aggregate the data
  // of the different voices. We compute the maximum of each control for now.
  for (int i = 0; i < plugin->n_out; i++) {
    int j = plugin->outctrls[i], k = plugin->ui[0]->elems[j].port;
    float *z = plugin->ui[0]->elems[j].zone;
    *plugin->ports[k] = *z;
    for (int l = 1; l < nvoices; l++) {
      float *z = plugin->ui[l]->elems[j].zone;
      if (*plugin->ports[k] < *z)
	*plugin->ports[k] = *z;
    }
  }
  // Keep track of the last gates set for each voice, so that voices can be
  // forcibly retriggered if needed.
  if (plugin->gate >= 0)
    for (int i = 0; i < nvoices; i++)
      plugin->lastgate[i] = *plugin->ui[i]->elems[plugin->gate].zone;
}

static void
activate(LV2_Handle instance)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)instance;
  for (int i = 0; i < NVOICES; i++)
    plugin->dsp[i]->init(plugin->rate);
  for (int i = 0, j = 0; i < plugin->ui[0]->nelems; i++) {
    int p = plugin->ui[0]->elems[i].port;
    float val = plugin->ui[0]->elems[i].init;
    plugin->portvals[p] = val;
  }
  plugin->active = true;
}

static void
deactivate(LV2_Handle instance)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)instance;
  plugin->active = false;
  plugin->all_notes_off();
}

const void*
extension_data(const char* uri)
{
  return NULL;
}

static const LV2_Descriptor descriptor = {
  PLUGIN_URI,
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index) {
  case 0:
    return &descriptor;
  default:
    return NULL;
  }
}

//----------------------------------------------------------------------------
//  Dynamic manifest
//----------------------------------------------------------------------------

// NOTE: If your LV2 host doesn't offer this extension then you'll have to
// create a static ttl file with the descriptions of the ports yourself. You
// can also do this by compiling this code to a standalone executable while
// defining the __MAIN__ symbol. Running the executable then prints the
// manifest on stdout.

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_open(LV2_Dyn_Manifest_Handle *handle,
			  const LV2_Feature *const *features)
{
  LV2SynthPlugin* plugin = new LV2SynthPlugin;
  plugin->dsp[0] = new mydsp();
  plugin->ui[0] = new LV2UI();
  plugin->dsp[0]->init(48000);
  plugin->dsp[0]->buildUserInterface(plugin->ui[0]);
  int k = plugin->ui[0]->nports;
  plugin->ctrls = (int*)calloc(k, sizeof(int));
  assert(k == 0 || plugin->ctrls);
  plugin->freq = plugin->gain = plugin->gate = -1;
  for (int i = 0, j = 0; i < plugin->ui[0]->nelems; i++) {
    switch (plugin->ui[0]->elems[i].type) {
    case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
      // control groups
      break;
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
      // passive controls (output ports)
      plugin->ctrls[j++] = i;
      break;
    default:
      // active controls (input ports)
      if (plugin->freq == -1 &&
	  !strcmp(plugin->ui[0]->elems[i].label, "freq"))
	plugin->freq = i;
      else if (plugin->gain == -1 &&
	       !strcmp(plugin->ui[0]->elems[i].label, "gain"))
	plugin->gain = i;
      else if (plugin->gate == -1 &&
	       !strcmp(plugin->ui[0]->elems[i].label, "gate"))
	plugin->gate = i;
      else
	plugin->ctrls[j++] = i;
      break;
    }
  }
  *handle = (LV2_Dyn_Manifest_Handle)plugin;
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_subjects(LV2_Dyn_Manifest_Handle handle,
				  FILE *fp)
{
  fprintf(fp, "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n\
<%s> a lv2:Plugin .\n", PLUGIN_URI);
  return 0;
}

#include <string>
#include <ctype.h>

static string mangle(const string &s)
{
  string t = s;
  size_t n = s.size();
  for (size_t i = 0; i < n; i++)
    if ((i == 0 && !isalpha(t[i]) && t[i] != '_') ||
	(!isalnum(t[i]) && t[i] != '_'))
      t[i] = '_';
  return t;
}

static unsigned steps(float min, float max, float step)
{
  if (step == 0.0) return 1;
  int n = (max-min)/step;
  if (n < 0) n = -n;
  if (n == 0) n = 1;
  return n;
}

#if FAUST_META
static bool is_xmlstring(const char *s)
{
  // This is just a basic sanity check. The string must not contain any
  // (unescaped) newlines, carriage returns or double quotes.
  return !strchr(s, '\n') && !strchr(s, '\r') && !strchr(s, '"');
}
#endif

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_data(LV2_Dyn_Manifest_Handle handle,
			      FILE *fp,
			      const char *uri)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)handle;
  int k = plugin->ui[0]->nports;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  // Scan the global metadata for plugin name, description, license etc.
  const char *plugin_name = NULL, *plugin_author = NULL, *plugin_descr = NULL,
    *plugin_license = NULL;
#if FAUST_META
  Meta meta;
  plugin->dsp[0]->metadata(&meta);
  for (std::list<strpair>::iterator it = meta.data.begin();
       it != meta.data.end(); it++) {
    const char *key = it->first, *val = it->second;
    if (!val || !is_xmlstring(val)) continue;
    if (!strcmp(key, "name")) {
      if (!plugin_name)
	plugin_name = val;
    } else if (!strcmp(key, "description")) {
      if (!plugin_descr)
	plugin_descr = val;
    } else if (!strcmp(key, "author")) {
      if (!plugin_author)
	plugin_author = val;
    } else if (!strcmp(key, "license")) {
      if (!plugin_license)
	plugin_license = val;
    }
  }
#endif
  if (!plugin_name) plugin_name = "mydsp";
  fprintf(fp, "@prefix doap: <http://usefulinc.com/ns/doap#> .\n\
@prefix foaf:  <http://xmlns.com/foaf/0.1/> .\n\
@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n\
@prefix epp:   <http://lv2plug.in/ns/ext/port-props#> .\n\
@prefix ev:    <http://lv2plug.in/ns/ext/event#> .\n\
@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n\
@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n\
@prefix units: <http://lv2plug.in/ns/extensions/units#> .\n\
<%s>\n\
       a lv2:Plugin, lv2:InstrumentPlugin ;\n\
       doap:name \"%s\" ;\n\
       lv2:binary <mydsp.so> ;\n\
       lv2:optionalFeature epp:supportsStrictBounds ;\n\
       lv2:optionalFeature lv2:hardRtCapable ;\n", PLUGIN_URI, plugin_name);
  if (plugin_author)
    fprintf(fp, "\
       doap:maintainer [ foaf:name \"%s\" ] ;\n", plugin_author);
  if (plugin_descr)
    fprintf(fp, "\
       doap:description \"%s\" ;\n", plugin_descr);
  if (plugin_license)
    fprintf(fp, "\
       doap:license \"%s\" ;\n", plugin_license);
  int idx = 0;
  // control ports
  for (int i = 0; i < k; i++, idx++) {
    int j = plugin->ctrls[i];
    assert(idx == plugin->ui[0]->elems[j].port);
    fprintf(fp, "%s [\n", idx==0?"    lv2:port":" ,");
    const char *label = plugin->ui[0]->elems[j].label;
    assert(label);
    string sym = mangle(plugin->ui[0]->elems[j].label);
    switch (plugin->ui[0]->elems[j].type) {
    // active controls (input ports)
    case UI_BUTTON: case UI_CHECK_BUTTON:
    fprintf(fp, "\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        lv2:portProperty lv2:toggled ;\n\
	lv2:default 0.00000 ;\n\
	lv2:minimum 0.00000 ;\n\
	lv2:maximum 1.00000 ;\n", idx, sym.c_str(), label);
      break;
    case UI_NUM_ENTRY: case UI_H_SLIDER: case UI_V_SLIDER:
    fprintf(fp, "\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        epp:rangeSteps %u ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), label,
	    steps(plugin->ui[0]->elems[j].min,
		  plugin->ui[0]->elems[j].max,
		  plugin->ui[0]->elems[j].step),
	    plugin->ui[0]->elems[j].init,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].max);
      break;
    // passive controls (output ports)
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
    fprintf(fp, "\
	a lv2:OutputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), label,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].max);
      break;
    default:
      assert(0 && "this can't happen");
      break;
    }
    // Scan for Faust control metadata we understand and add corresponding
    // hints to the LV2 description of the port.
    std::map< int, list<strpair> >::iterator it =
      plugin->ui[0]->metadata.find(j);
    if (it != plugin->ui[0]->metadata.end()) {
      for (std::list<strpair>::iterator jt = it->second.begin();
	   jt != it->second.end(); jt++) {
	const char *key = jt->first, *val = jt->second;
	if (!strcmp(key, "unit"))
	  fprintf(fp, "\
	units:unit [\n\
            a            units:Unit ;\n\
            units:name   \"%s\" ;\n\
            units:symbol \"%s\" ;\n\
            units:render \"%%f %s\"\n\
	] ;\n", val, val, val);
	if (strcmp(key, "lv2")) continue;
	if (!strcmp(val, "integer"))
	  fprintf(fp, "\
	lv2:portProperty lv2:integer ;\n");
	else if (!strcmp(val, "hidden") || !strcmp(val, "notOnGUI"))
	  fprintf(fp, "\
	lv2:portProperty epp:notOnGUI ;\n");
	else if (!strncmp(val, "scalepoint", 10) ||
		 !strncmp(val, "scalePoint", 10)) {
	  val += 10;
	  if (!isspace(*val)) continue;
	  char *label = (char*)malloc(strlen(val)+1);
	  float point;
	  int pos;
	  while (sscanf(val, "%s %g%n", label, &point, &pos) == 2) {
	    fprintf(fp, "\
	lv2:scalePoint [ rdfs:label \"%s\"; rdf:value %g ] ;\n",
		    label, point);
	    val += pos;
	  }
	  free(label);
	} else
	  fprintf(stderr, "%s: bad port property '%s:%s'\n", PLUGIN_URI,
		  key, val);
      }
    }
    fprintf(fp, "    ]");
  }
  // audio inputs
  for (int i = 0; i < n; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a lv2:AudioPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"in%d\" ;\n\
	lv2:name \"in%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  // audio outputs
  for (int i = 0; i < m; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:OutputPort ;\n\
	a lv2:AudioPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"out%d\" ;\n\
	lv2:name \"out%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  // midi input
  fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a ev:EventPort ;\n\
	ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"midiin\" ;\n\
	lv2:name \"midiin\"\n\
    ]", idx==0?"    lv2:port":" ,", idx);
  idx++;
  // polyphony control
  fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"nvoices\" ;\n\
	lv2:name \"Polyphony\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
#       lv2:portProperty epp:expensive ;\n\
        lv2:portProperty lv2:integer ;\n\
        epp:rangeSteps %d ;\n\
	lv2:default %d ;\n\
	lv2:minimum 1 ;\n\
	lv2:maximum %d ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, NVOICES,
	  NVOICES>1?NVOICES/2:1,
	  NVOICES);
  idx++;
  fprintf(fp, "\n.\n");
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
void lv2_dyn_manifest_close(LV2_Dyn_Manifest_Handle handle)
{
  LV2SynthPlugin* plugin = (LV2SynthPlugin*)handle;
  delete plugin->dsp[0];
  delete plugin->ui[0];
  delete plugin;
}

int main()
{
  LV2_Dyn_Manifest_Handle handle;
  LV2_Feature **features = { NULL };
  int res = lv2_dyn_manifest_open(&handle, features);
  if (res) return res;
  res = lv2_dyn_manifest_get_data(handle, stdout, PLUGIN_URI);
  return res;
}
