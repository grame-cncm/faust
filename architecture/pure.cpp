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

/* Pure architecture for Faust. This is similar to the Q architecture, but
   uses double precision for the audio buffers and control variables. See
   http://purelang.bitbucket.org for a Pure module which can load these
   extensions. */

#include <stdlib.h>
#include <math.h>
#include <list>
#include <map>

using namespace std;

typedef pair<const char*,const char*> strpair;

struct Meta
{
  list< strpair > data;
  void declare(const char* key, const char* value)
  { data.push_back(strpair(key, value)); }
};

inline int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

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
  virtual void addCheckButton(const char* label, double* zone) = 0;
  virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
  virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
  virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

  virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
  virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;

  virtual void openTabBox(const char* label) = 0;
  virtual void openHorizontalBox(const char* label) = 0;
  virtual void openVerticalBox(const char* label) = 0;
  virtual void closeBox() = 0;

  virtual void run() = 0;

  void stop() { fStopped = true; }
  bool stopped() { return fStopped; }

  virtual void declare(double* zone, const char* key, const char* value) {}
};

/***************************************************************************
   Pure UI interface
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
  double *zone;
  void *ref;
  double init, min, max, step;
};

class PureUI : public UI
{
public:
  int nelems;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  PureUI();
  virtual ~PureUI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, double *zone);
  void add_elem(ui_elem_type_t type, const char *label, double *zone,
		double init, double min, double max, double step);
  void add_elem(ui_elem_type_t type, const char *label, double *zone,
		double min, double max);

public:
  virtual void addButton(const char* label, double* zone);
  virtual void addCheckButton(const char* label, double* zone);
  virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step);
  virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step);
  virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step);

  virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max);
  virtual void addVerticalBargraph(const char* label, double* zone, double min, double max);

  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();

  virtual void run();

  virtual void declare(double* zone, const char* key, const char* value);
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

void PureUI::declare(double* zone, const char* key, const char* value)
{
  map< int, list<strpair> >::iterator it = metadata.find(nelems);
  if (it != metadata.end())
    it->second.push_back(strpair(key, value));
  else
    metadata[nelems] = list<strpair>(1, strpair(key, value));
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
			     double init, double min, double max, double step)
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
			     double min, double max)
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
void PureUI::addCheckButton(const char* label, double* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PureUI::addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PureUI::addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PureUI::addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PureUI::addHorizontalBargraph(const char* label, double* zone, double min, double max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PureUI::addVerticalBargraph(const char* label, double* zone, double min, double max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

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
  int fSampleRate;
 public:
  // internal freelist for custom voice allocation
  dsp *prev, *next;
  dsp() {}
  virtual ~dsp() {}
  virtual int getNumInputs() = 0;
  virtual int getNumOutputs() = 0;
  virtual void buildUserInterface(UI* interface) = 0;
  virtual void init(int sample_date) = 0;
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

#include <assert.h>

// Define this to get some debugging output.
//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#define FAUST_CN "mydsp"
#endif

/* Dynamic voice allocation. We go to some lengths here to make this as
   realtime-friendly as possible. The idea is that we keep a pool of allocated
   mydsp instances. When a dsp is freed with deldsp(), it's in fact never
   deleted, but put at the end of a freelist from where it may eventually be
   reused by a subsequent call to newdsp(). By these means, the number of
   actual calls to malloc() can be kept to a minimum. In addition, a small
   number of voices are preallocated in static memory (1 by default in the
   present implementation, but you can set this at compile time by redefining
   the NVOICES constant accordingly). If you choose a suitable NVOICES value,
   chances are that your application may never need to allocate dsp instances
   on the heap at all. Also, even if dsp instances have to be created
   dynamically, they are allocated in chunks of NVOICES units, in order to
   reduce the calls to malloc(). Thus we generally recommend to set NVOICES to
   a value >1 which best suits your application. */

#ifndef NVOICES
#define NVOICES 1
#endif

// Make sure that NVOICES is at least 1.
#if NVOICES<1
#undefine NVOICES
#define NVOICES 1
#endif

struct dspmem_t {
  char x[sizeof(mydsp)];
};

struct mem_t {
  dspmem_t mem[NVOICES];
  mem_t *next;
};

// statically and dynamically allocated dsp instances
static mem_t mem0, *mem;
// beginning and end of the freelist
static mydsp *first, *last;

/* This is supposed to be executed when the module gets unloaded. You'll need
   a recent gcc version (or compatible) to make this work. */

void __attribute__ ((destructor)) mydsp_fini(void)
{
  if (!mem) return;
  mem = mem->next;
  while (mem) {
    mem_t *mem1 = mem->next;
    free(mem); mem = mem1;
  }
}

/* The class factory, used to create and destroy mydsp objects in the client.
   This is implemented using C linkage to facilitate dlopen access. */

#include <new>

extern "C" mydsp *newdsp()
{
  if (!mem) {
    mem = &mem0; mem->next = 0;
    // initialize the freelist with the statically allocated voices
    mydsp *prev = 0, *next = (mydsp*)&mem->mem[0];
    first = next;
    for (int i = 0; i < NVOICES; i++) {
      void *p = &mem->mem[i];
      mydsp *d = new(p) mydsp;
      d->prev = prev; prev = d;
      d->next = ++next;
    }
    last = prev; last->next = 0;
#ifdef DEBUG
    fprintf(stderr, ">>> %s: preallocated %d voices\n", FAUST_CN, NVOICES);
#endif
  }
  assert(mem);
  if (!first) {
    // allocate a new chunk of voices and add them to the freelist
    mem_t *block = (mem_t*)calloc(1, sizeof(mem_t));
    block->next = mem->next; mem->next = block;
    mydsp *prev = 0, *next = (mydsp*)&block->mem[0];
    first = next;
    for (int i = 0; i < NVOICES; i++) {
      void *p = &block->mem[i];;
      mydsp *d = new(p) mydsp;
      d->prev = prev; prev = d;
      d->next = ++next;
    }
    last = prev; last->next = 0;
#ifdef DEBUG
    fprintf(stderr, ">>> %s: allocated %d voices\n", FAUST_CN, NVOICES);
#endif
  }
  assert(first && last);
  mydsp *d = first;
  if (first == last) {
    // freelist is now empty
    first = last = 0;
  } else {
    // remove d from the freelist
    first = (mydsp*)first->next;
  }
  d->prev = d->next = 0;
#ifdef DEBUG
  fprintf(stderr, ">>> %s: allocating instance %p\n", FAUST_CN, d);
#endif
  return d;
}

extern "C" void deldsp(mydsp* d)
{
#ifdef DEBUG
  fprintf(stderr, ">>> %s: freeing instance %p\n", FAUST_CN, d);
#endif
  // add d to the freelist
  assert(!d->prev && !d->next);
  if (last) {
    last->next = d; d->prev = last; last = d;
  } else
    first = last = d;
}

extern "C" Meta *newmeta()
{
  Meta *m = new Meta;
  mydsp tmp_dsp;
  tmp_dsp.metadata(m);
  return m;
}

extern "C" void delmeta(Meta* m)
{
  delete m;
}
