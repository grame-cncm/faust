//-----------------------------------------------------
// name: "tapiir"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2006"
//
// Code generated with Faust 0.9.68 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
#include <math.h>
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
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

/* Pd architecture file, written by Albert Graef <Dr.Graef@t-online.de>.
   This was derived from minimal.cpp included in the Faust distribution.
   Please note that this is to be compiled as a shared library, which is
   then loaded dynamically by Pd as an external. */

#include <stdlib.h>
#include <math.h>
#include <string>

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dsp.h"

//using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/***************************************************************************
   Pd UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  char *label;
  float *zone;
  float init, min, max, step;
};

class PdUI : public UI
{
public:
  const char *name;
  int nelems, level;
  ui_elem_t *elems;
		
  PdUI();
  PdUI(const char *nm, const char *s);
  virtual ~PdUI();

protected:
  std::string path;
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
};

static std::string mangle(const char *name, int level, const char *s)
{
  const char *s0 = s;
  std::string t = "";
  if (!s) return t;
  // Get rid of bogus "0x00" labels in recent Faust revisions. Also, for
  // backward compatibility with old Faust versions, make sure that default
  // toplevel groups and explicit toplevel groups with an empty label are
  // treated alike (these both return "0x00" labels in the latest Faust, but
  // would be treated inconsistently in earlier versions).
  if (!*s || strcmp(s, "0x00") == 0) {
    if (level == 0)
      // toplevel group with empty label, map to dsp name
      s = name;
    else
      // empty label
      s = "";
  }
  while (*s)
    if (isalnum(*s))
      t += *(s++);
    else {
      const char *s1 = s;
      while (*s && !isalnum(*s)) ++s;
      if (s1 != s0 && *s) t += "-";
    }
  return t;
}

static std::string normpath(std::string path)
{
  path = std::string("/")+path;
  int pos = path.find("//");
  while (pos >= 0) {
    path.erase(pos, 1);
    pos = path.find("//");
  }
  size_t len = path.length();
  if (len > 1 && path[len-1] == '/')
    path.erase(len-1, 1);
  return path;
}

static std::string pathcat(std::string path, std::string label)
{
  if (path.empty())
    return normpath(label);
  else if (label.empty())
    return normpath(path);
  else
    return normpath(path+"/"+label);
}

PdUI::PdUI()
{
  nelems = level = 0;
  elems = NULL;
  name = "";
  path = "";
}

PdUI::PdUI(const char *nm, const char *s)
{
  nelems = level = 0;
  elems = NULL;
  name = nm?nm:"";
  path = s?s:"";
}

PdUI::~PdUI()
{
  if (elems) {
    for (int i = 0; i < nelems; i++)
      if (elems[i].label)
	free(elems[i].label);
    free(elems);
  }
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 1.0;
  elems[nelems].step = 1.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void PdUI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PdUI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PdUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PdUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PdUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PdUI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PdUI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PdUI::openTabBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openHorizontalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openVerticalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::closeBox()
{
  int pos = path.rfind("/");
  if (pos < 0) pos = 0;
  path.erase(pos);
  level--;
}

void PdUI::run() {}

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	int 	IOTA;
	float 	fVec0[524288];
	FAUSTFLOAT 	fslider11;
	int 	iConst0;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	float 	fVec1[524288];
	FAUSTFLOAT 	fslider21;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	float 	fVec2[524288];
	FAUSTFLOAT 	fslider31;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fslider37;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	float 	fVec3[524288];
	FAUSTFLOAT 	fslider41;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	FAUSTFLOAT 	fslider47;
	FAUSTFLOAT 	fslider48;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	float 	fVec4[524288];
	FAUSTFLOAT 	fslider51;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	FAUSTFLOAT 	fslider54;
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	FAUSTFLOAT 	fslider58;
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fslider60;
	float 	fVec5[524288];
	FAUSTFLOAT 	fslider61;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider62;
	FAUSTFLOAT 	fslider63;
	FAUSTFLOAT 	fslider64;
	FAUSTFLOAT 	fslider65;
	FAUSTFLOAT 	fslider66;
	FAUSTFLOAT 	fslider67;
	FAUSTFLOAT 	fslider68;
	FAUSTFLOAT 	fslider69;
	FAUSTFLOAT 	fslider70;
	FAUSTFLOAT 	fslider71;
	FAUSTFLOAT 	fslider72;
	FAUSTFLOAT 	fslider73;
	FAUSTFLOAT 	fslider74;
	FAUSTFLOAT 	fslider75;
	FAUSTFLOAT 	fslider76;
	FAUSTFLOAT 	fslider77;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "tapiir");
		m->declare("version", "1.0");
		m->declare("author", "Grame");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL with exception");
	}

	virtual int getNumInputs() 	{ return 2; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 1.0f;
		fslider1 = 1.0f;
		fslider2 = 1.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 1.0f;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		fslider9 = 0.0f;
		fslider10 = 1.0f;
		IOTA = 0;
		for (int i=0; i<524288; i++) fVec0[i] = 0;
		fslider11 = 0.0f;
		iConst0 = min(192000, max(1, fSamplingFreq));
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fslider12 = 1.0f;
		fslider13 = 1.0f;
		fslider14 = 0.0f;
		fslider15 = 0.0f;
		fslider16 = 0.0f;
		fslider17 = 0.0f;
		fslider18 = 0.0f;
		fslider19 = 0.0f;
		fslider20 = 1.0f;
		for (int i=0; i<524288; i++) fVec1[i] = 0;
		fslider21 = 0.0f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider22 = 1.0f;
		fslider23 = 1.0f;
		fslider24 = 0.0f;
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		fslider27 = 0.0f;
		fslider28 = 0.0f;
		fslider29 = 0.0f;
		fslider30 = 1.0f;
		for (int i=0; i<524288; i++) fVec2[i] = 0;
		fslider31 = 0.0f;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider32 = 1.0f;
		fslider33 = 1.0f;
		fslider34 = 0.0f;
		fslider35 = 0.0f;
		fslider36 = 0.0f;
		fslider37 = 0.0f;
		fslider38 = 0.0f;
		fslider39 = 0.0f;
		fslider40 = 1.0f;
		for (int i=0; i<524288; i++) fVec3[i] = 0;
		fslider41 = 0.0f;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fslider42 = 1.0f;
		fslider43 = 1.0f;
		fslider44 = 0.0f;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 0.0f;
		fslider49 = 0.0f;
		fslider50 = 1.0f;
		for (int i=0; i<524288; i++) fVec4[i] = 0;
		fslider51 = 0.0f;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider52 = 1.0f;
		fslider53 = 1.0f;
		fslider54 = 0.0f;
		fslider55 = 0.0f;
		fslider56 = 0.0f;
		fslider57 = 0.0f;
		fslider58 = 0.0f;
		fslider59 = 0.0f;
		fslider60 = 1.0f;
		for (int i=0; i<524288; i++) fVec5[i] = 0;
		fslider61 = 0.0f;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider62 = 0.0f;
		fslider63 = 0.0f;
		fslider64 = 0.0f;
		fslider65 = 0.0f;
		fslider66 = 0.0f;
		fslider67 = 0.0f;
		fslider68 = 1.0f;
		fslider69 = 1.0f;
		fslider70 = 1.0f;
		fslider71 = 0.0f;
		fslider72 = 0.0f;
		fslider73 = 0.0f;
		fslider74 = 0.0f;
		fslider75 = 0.0f;
		fslider76 = 0.0f;
		fslider77 = 1.0f;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("Tapiir");
		interface->openTabBox("0x00");
		interface->openHorizontalBox("Tap 0");
		interface->addVerticalSlider("delay (sec)", &fslider11, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider10, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider6, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider2, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider5, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider4, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider3, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider7, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider8, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider9, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("Tap 1");
		interface->addVerticalSlider("delay (sec)", &fslider21, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider20, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider13, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider12, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider19, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider18, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider17, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider16, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider15, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider14, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("Tap 2");
		interface->addVerticalSlider("delay (sec)", &fslider31, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider30, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider23, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider22, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider29, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider28, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider27, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider26, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider25, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider24, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("Tap 3");
		interface->addVerticalSlider("delay (sec)", &fslider41, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider40, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider33, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider32, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider39, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider38, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider37, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider36, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider35, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider34, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("Tap 4");
		interface->addVerticalSlider("delay (sec)", &fslider51, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider50, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider43, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider42, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider49, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider48, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider47, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider46, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider45, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider44, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("Tap 5");
		interface->addVerticalSlider("delay (sec)", &fslider61, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addVerticalSlider("gain", &fslider60, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider53, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider52, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider59, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider58, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider57, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider56, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider55, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider54, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("outputs");
		interface->openHorizontalBox("output 0");
		interface->addVerticalSlider("gain", &fslider68, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider1, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider0, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider67, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider66, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider65, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider64, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider63, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider62, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->openHorizontalBox("output 1");
		interface->addVerticalSlider("gain", &fslider77, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 0", &fslider70, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("input 1", &fslider69, 1.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 0", &fslider76, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 1", &fslider75, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 2", &fslider74, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 3", &fslider73, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 4", &fslider72, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->addVerticalSlider("tap 5", &fslider71, 0.0f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = float(fslider4);
		float 	fSlow5 = float(fslider5);
		float 	fSlow6 = float(fslider6);
		float 	fSlow7 = float(fslider7);
		float 	fSlow8 = float(fslider8);
		float 	fSlow9 = float(fslider9);
		float 	fSlow10 = float(fslider10);
		int 	iSlow11 = int((int((iConst0 * float(fslider11))) & 524287));
		float 	fSlow12 = float(fslider12);
		float 	fSlow13 = float(fslider13);
		float 	fSlow14 = float(fslider14);
		float 	fSlow15 = float(fslider15);
		float 	fSlow16 = float(fslider16);
		float 	fSlow17 = float(fslider17);
		float 	fSlow18 = float(fslider18);
		float 	fSlow19 = float(fslider19);
		float 	fSlow20 = float(fslider20);
		int 	iSlow21 = int((int((iConst0 * float(fslider21))) & 524287));
		float 	fSlow22 = float(fslider22);
		float 	fSlow23 = float(fslider23);
		float 	fSlow24 = float(fslider24);
		float 	fSlow25 = float(fslider25);
		float 	fSlow26 = float(fslider26);
		float 	fSlow27 = float(fslider27);
		float 	fSlow28 = float(fslider28);
		float 	fSlow29 = float(fslider29);
		float 	fSlow30 = float(fslider30);
		int 	iSlow31 = int((int((iConst0 * float(fslider31))) & 524287));
		float 	fSlow32 = float(fslider32);
		float 	fSlow33 = float(fslider33);
		float 	fSlow34 = float(fslider34);
		float 	fSlow35 = float(fslider35);
		float 	fSlow36 = float(fslider36);
		float 	fSlow37 = float(fslider37);
		float 	fSlow38 = float(fslider38);
		float 	fSlow39 = float(fslider39);
		float 	fSlow40 = float(fslider40);
		int 	iSlow41 = int((int((iConst0 * float(fslider41))) & 524287));
		float 	fSlow42 = float(fslider42);
		float 	fSlow43 = float(fslider43);
		float 	fSlow44 = float(fslider44);
		float 	fSlow45 = float(fslider45);
		float 	fSlow46 = float(fslider46);
		float 	fSlow47 = float(fslider47);
		float 	fSlow48 = float(fslider48);
		float 	fSlow49 = float(fslider49);
		float 	fSlow50 = float(fslider50);
		int 	iSlow51 = int((int((iConst0 * float(fslider51))) & 524287));
		float 	fSlow52 = float(fslider52);
		float 	fSlow53 = float(fslider53);
		float 	fSlow54 = float(fslider54);
		float 	fSlow55 = float(fslider55);
		float 	fSlow56 = float(fslider56);
		float 	fSlow57 = float(fslider57);
		float 	fSlow58 = float(fslider58);
		float 	fSlow59 = float(fslider59);
		float 	fSlow60 = float(fslider60);
		int 	iSlow61 = int((int((iConst0 * float(fslider61))) & 524287));
		float 	fSlow62 = float(fslider62);
		float 	fSlow63 = float(fslider63);
		float 	fSlow64 = float(fslider64);
		float 	fSlow65 = float(fslider65);
		float 	fSlow66 = float(fslider66);
		float 	fSlow67 = float(fslider67);
		float 	fSlow68 = float(fslider68);
		float 	fSlow69 = float(fslider69);
		float 	fSlow70 = float(fslider70);
		float 	fSlow71 = float(fslider71);
		float 	fSlow72 = float(fslider72);
		float 	fSlow73 = float(fslider73);
		float 	fSlow74 = float(fslider74);
		float 	fSlow75 = float(fslider75);
		float 	fSlow76 = float(fslider76);
		float 	fSlow77 = float(fslider77);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			float fTemp0 = (float)input1[i];
			float fTemp1 = (float)input0[i];
			fVec0[IOTA&524287] = (fSlow10 * (((fSlow9 * fRec5[1]) + ((fSlow8 * fRec4[1]) + ((fSlow7 * fRec3[1]) + ((fSlow6 * fTemp1) + (((fSlow5 * fRec0[1]) + (fSlow4 * fRec1[1])) + (fSlow3 * fRec2[1])))))) + (fSlow2 * fTemp0)));
			fRec0[0] = fVec0[(IOTA-iSlow11)&524287];
			fVec1[IOTA&524287] = (fSlow20 * ((((((((fSlow19 * fRec0[1]) + (fSlow18 * fRec1[1])) + (fSlow17 * fRec2[1])) + (fSlow16 * fRec3[1])) + (fSlow15 * fRec4[1])) + (fSlow14 * fRec5[1])) + (fSlow13 * fTemp1)) + (fSlow12 * fTemp0)));
			fRec1[0] = fVec1[(IOTA-iSlow21)&524287];
			fVec2[IOTA&524287] = (fSlow30 * ((((((((fSlow29 * fRec0[1]) + (fSlow28 * fRec1[1])) + (fSlow27 * fRec2[1])) + (fSlow26 * fRec3[1])) + (fSlow25 * fRec4[1])) + (fSlow24 * fRec5[1])) + (fSlow23 * fTemp1)) + (fSlow22 * fTemp0)));
			fRec2[0] = fVec2[(IOTA-iSlow31)&524287];
			fVec3[IOTA&524287] = (fSlow40 * ((((((((fSlow39 * fRec0[1]) + (fSlow38 * fRec1[1])) + (fSlow37 * fRec2[1])) + (fSlow36 * fRec3[1])) + (fSlow35 * fRec4[1])) + (fSlow34 * fRec5[1])) + (fSlow33 * fTemp1)) + (fSlow32 * fTemp0)));
			fRec3[0] = fVec3[(IOTA-iSlow41)&524287];
			fVec4[IOTA&524287] = (fSlow50 * ((((((((fSlow49 * fRec0[1]) + (fSlow48 * fRec1[1])) + (fSlow47 * fRec2[1])) + (fSlow46 * fRec3[1])) + (fSlow45 * fRec4[1])) + (fSlow44 * fRec5[1])) + (fSlow43 * fTemp1)) + (fSlow42 * fTemp0)));
			fRec4[0] = fVec4[(IOTA-iSlow51)&524287];
			fVec5[IOTA&524287] = (fSlow60 * ((((((((fSlow59 * fRec0[1]) + (fSlow58 * fRec1[1])) + (fSlow57 * fRec2[1])) + (fSlow56 * fRec3[1])) + (fSlow55 * fRec4[1])) + (fSlow54 * fRec5[1])) + (fSlow53 * fTemp1)) + (fSlow52 * fTemp0)));
			fRec5[0] = fVec5[(IOTA-iSlow61)&524287];
			output0[i] = (FAUSTFLOAT)(fSlow68 * ((((((((fSlow67 * fRec0[0]) + (fSlow66 * fRec1[0])) + (fSlow65 * fRec2[0])) + (fSlow64 * fRec3[0])) + (fSlow63 * fRec4[0])) + (fSlow62 * fRec5[0])) + (fSlow1 * fTemp1)) + (fSlow0 * fTemp0)));
			output1[i] = (FAUSTFLOAT)(fSlow77 * ((((((((fSlow76 * fRec0[0]) + (fSlow75 * fRec1[0])) + (fSlow74 * fRec2[0])) + (fSlow73 * fRec3[0])) + (fSlow72 * fRec4[0])) + (fSlow71 * fRec5[0])) + (fSlow70 * fTemp1)) + (fSlow69 * fTemp0)));
			// post processing
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
		}
	}
};



#include <stdio.h>
#include <string>
#include "m_pd.h"

#define sym(name) xsym(name)
#define xsym(name) #name
#define faust_setup(name) xfaust_setup(name)
#define xfaust_setup(name) name ## _tilde_setup(void)

// time for "active" toggle xfades in secs
#define XFADE_TIME 0.1f

static t_class *faust_class;

struct t_faust {
  t_object x_obj;
#ifdef __MINGW32__
  /* This seems to be necessary as some as yet undetermined Pd routine seems
     to write past the end of x_obj on Windows. */
  int fence; /* dummy field (not used) */
#endif
  mydsp *dsp;
  PdUI *ui;
  std::string *label;
  int active, xfade, n_xfade, rate, n_in, n_out;
  t_sample **inputs, **outputs, **buf;
  t_outlet *out;
  t_sample f;
};

static t_symbol *s_button, *s_checkbox, *s_vslider, *s_hslider, *s_nentry,
  *s_vbargraph, *s_hbargraph;

static inline void zero_samples(int k, int n, t_sample **out)
{
  for (int i = 0; i < k; i++)
#ifdef __STDC_IEC_559__
    /* IEC 559 a.k.a. IEEE 754 floats can be initialized faster like this */
    memset(out[i], 0, n*sizeof(t_sample));
#else
    for (int j = 0; j < n; j++)
      out[i][j] = 0.0f;
#endif
}

static inline void copy_samples(int k, int n, t_sample **out, t_sample **in)
{
  for (int i = 0; i < k; i++)
    memcpy(out[i], in[i], n*sizeof(t_sample));
}

static t_int *faust_perform(t_int *w)
{
  t_faust *x = (t_faust *)(w[1]);
  int n = (int)(w[2]);
  if (!x->dsp || !x->buf) return (w+3);
  AVOIDDENORMALS;
  if (x->xfade > 0) {
    float d = 1.0f/x->n_xfade, f = (x->xfade--)*d;
    d = d/n;
    x->dsp->compute(n, x->inputs, x->buf);
    if (x->active)
      if (x->n_in == x->n_out)
	/* xfade inputs -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->inputs[i][j]+(1.0f-f)*x->buf[i][j];
      else
	/* xfade 0 -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = (1.0f-f)*x->buf[i][j];
    else
      if (x->n_in == x->n_out)
	/* xfade buf -> inputs */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j]+(1.0f-f)*x->inputs[i][j];
      else
	/* xfade buf -> 0 */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j];
  } else if (x->active) {
    x->dsp->compute(n, x->inputs, x->buf);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else if (x->n_in == x->n_out) {
    copy_samples(x->n_out, n, x->buf, x->inputs);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else
    zero_samples(x->n_out, n, x->outputs);
  return (w+3);
}

static void faust_dsp(t_faust *x, t_signal **sp)
{
  int n = sp[0]->s_n, sr = (int)sp[0]->s_sr;
  if (x->rate <= 0) {
    /* default sample rate is whatever Pd tells us */
    PdUI *ui = x->ui;
    float *z = NULL;
    if (ui->nelems > 0 &&
	(z = (float*)malloc(ui->nelems*sizeof(float)))) {
      /* save the current control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  z[i] = *ui->elems[i].zone;
    }
    /* set the proper sample rate; this requires reinitializing the dsp */
    x->rate = sr;
    x->dsp->init(sr);
    if (z) {
      /* restore previous control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  *ui->elems[i].zone = z[i];
      free(z);
    }
  }
  if (n > 0)
    x->n_xfade = (int)(x->rate*XFADE_TIME/n);
  dsp_add(faust_perform, 2, x, n);
  for (int i = 0; i < x->n_in; i++)
    x->inputs[i] = sp[i+1]->s_vec;
  for (int i = 0; i < x->n_out; i++)
    x->outputs[i] = sp[x->n_in+i+1]->s_vec;
  if (x->buf != NULL)
    for (int i = 0; i < x->n_out; i++) {
      x->buf[i] = (t_sample*)malloc(n*sizeof(t_sample));
      if (x->buf[i] == NULL) {
	for (int j = 0; j < i; j++)
	  free(x->buf[j]);
	free(x->buf);
	x->buf = NULL;
	break;
      }
    }
}

static int pathcmp(const char *s, const char *t)
{
  int n = strlen(s), m = strlen(t);
  if (n == 0 || m == 0)
    return 0;
  else if (t[0] == '/')
    return strcmp(s, t);
  else if (n <= m || s[n-m-1] != '/')
    return strcmp(s+1, t);
  else
    return strcmp(s+n-m, t);
}

static void faust_any(t_faust *x, t_symbol *s, int argc, t_atom *argv)
{
  if (!x->dsp) return;
  PdUI *ui = x->ui;
  if (s == &s_bang) {
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label && ui->elems[i].zone) {
	t_atom args[6];
	t_symbol *_s;
	switch (ui->elems[i].type) {
	case UI_BUTTON:
	  _s = s_button;
	  break;
	case UI_CHECK_BUTTON:
	  _s = s_checkbox;
	  break;
	case UI_V_SLIDER:
	  _s = s_vslider;
	  break;
	case UI_H_SLIDER:
	  _s = s_hslider;
	  break;
	case UI_NUM_ENTRY:
	  _s = s_nentry;
	  break;
	case UI_V_BARGRAPH:
	  _s = s_vbargraph;
	  break;
	case UI_H_BARGRAPH:
	  _s = s_hbargraph;
	  break;
	default:
	  continue;
	}
	SETSYMBOL(&args[0], gensym(ui->elems[i].label));
	SETFLOAT(&args[1], *ui->elems[i].zone);
	SETFLOAT(&args[2], ui->elems[i].init);
	SETFLOAT(&args[3], ui->elems[i].min);
	SETFLOAT(&args[4], ui->elems[i].max);
	SETFLOAT(&args[5], ui->elems[i].step);
	outlet_anything(x->out, _s, 6, args);
      }
  } else {
    const char *label = s->s_name;
    int count = 0;
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label &&
	  pathcmp(ui->elems[i].label, label) == 0) {
	if (argc == 0) {
	  if (ui->elems[i].zone) {
	    t_atom arg;
	    SETFLOAT(&arg, *ui->elems[i].zone);
	    outlet_anything(x->out, gensym(ui->elems[i].label), 1, &arg);
	  }
	  ++count;
	} else if (argc == 1 &&
		   (argv[0].a_type == A_FLOAT ||
		    argv[0].a_type == A_DEFFLOAT) &&
		   ui->elems[i].zone) {
	  float f = atom_getfloat(argv);
	  *ui->elems[i].zone = f;
	  ++count;
	} else
	  pd_error(x, "[faust] %s: bad control argument: %s",
		   x->label->c_str(), label);
      }
    if (count == 0 && strcmp(label, "active") == 0) {
      if (argc == 0) {
	t_atom arg;
	SETFLOAT(&arg, (float)x->active);
	outlet_anything(x->out, gensym((char*)"active"), 1, &arg);
      } else if (argc == 1 &&
		 (argv[0].a_type == A_FLOAT ||
		  argv[0].a_type == A_DEFFLOAT)) {
	float f = atom_getfloat(argv);
	x->active = (int)f;
	x->xfade = x->n_xfade;
      }
    }
  }
}

static void faust_free(t_faust *x)
{
  if (x->label) delete x->label;
  if (x->dsp) delete x->dsp;
  if (x->ui) delete x->ui;
  if (x->inputs) free(x->inputs);
  if (x->outputs) free(x->outputs);
  if (x->buf) {
    for (int i = 0; i < x->n_out; i++)
      if (x->buf[i]) free(x->buf[i]);
    free(x->buf);
  }
}

static void *faust_new(t_symbol *s, int argc, t_atom *argv)
{
  t_faust *x = (t_faust*)pd_new(faust_class);
  int sr = -1;
  t_symbol *id = NULL;
  x->active = 1;
  for (int i = 0; i < argc; i++)
    if (argv[i].a_type == A_FLOAT || argv[i].a_type == A_DEFFLOAT)
      sr = (int)argv[i].a_w.w_float;
    else if (argv[i].a_type == A_SYMBOL || argv[i].a_type == A_DEFSYMBOL)
      id = argv[i].a_w.w_symbol;
  x->rate = sr;
  if (sr <= 0) sr = 44100;
  x->xfade = 0; x->n_xfade = (int)(sr*XFADE_TIME/64);
  x->inputs = x->outputs = x->buf = NULL;
    x->label = new std::string(sym(mydsp) "~");
  x->dsp = new mydsp();
  x->ui = new PdUI(sym(mydsp), id?id->s_name:NULL);
  if (!x->dsp || !x->ui || !x->label) goto error;
  if (id) {
    *x->label += " ";
    *x->label += id->s_name;
  }
  x->n_in = x->dsp->getNumInputs();
  x->n_out = x->dsp->getNumOutputs();
  if (x->n_in > 0)
    x->inputs = (t_sample**)malloc(x->n_in*sizeof(t_sample*));
  if (x->n_out > 0) {
    x->outputs = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
    x->buf = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
  }
  if ((x->n_in > 0 && x->inputs == NULL) ||
      (x->n_out > 0 && (x->outputs == NULL || x->buf == NULL)))
    goto error;
  for (int i = 0; i < x->n_out; i++)
    x->buf[i] = NULL;
  x->dsp->init(sr);
  x->dsp->buildUserInterface(x->ui);
  for (int i = 0; i < x->n_in; i++)
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  x->out = outlet_new(&x->x_obj, 0);
  for (int i = 0; i < x->n_out; i++)
    outlet_new(&x->x_obj, &s_signal);
  return (void *)x;
 error:
  faust_free(x);
  x->dsp = NULL; x->ui = NULL;
  x->inputs = x->outputs = x->buf = NULL;
  return (void *)x;
}

extern "C" void faust_setup(mydsp)
{
  t_symbol *s = gensym(sym(mydsp) "~");
  faust_class =
    class_new(s, (t_newmethod)faust_new, (t_method)faust_free,
	      sizeof(t_faust), CLASS_DEFAULT,
	      A_GIMME, A_NULL);
  class_addmethod(faust_class, (t_method)faust_dsp, gensym((char*)"dsp"), A_NULL);
  class_addanything(faust_class, faust_any);
  class_addmethod(faust_class, nullfn, &s_signal, A_NULL);
  s_button = gensym((char*)"button");
  s_checkbox = gensym((char*)"checkbox");
  s_vslider = gensym((char*)"vslider");
  s_hslider = gensym((char*)"hslider");
  s_nentry = gensym((char*)"nentry");
  s_vbargraph = gensym((char*)"vbargraph");
  s_hbargraph = gensym((char*)"hbargraph");
  /* give some indication that we're loaded and ready to go */
  mydsp dsp = mydsp();
  post("[faust] %s: %d inputs, %d outputs", sym(mydsp) "~",
       dsp.getNumInputs(), dsp.getNumOutputs());
}
