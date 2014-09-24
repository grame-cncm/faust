//-----------------------------------------------------
// name: "karplus32"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2006"
//
// Code generated with Faust 0.9.68 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
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
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fRec1[2];
	int 	iRec2[2];
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	float 	fVec1[4096];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fRec0[3];
	FAUSTFLOAT 	fslider5;
	float 	fVec2[4096];
	float 	fRec3[3];
	float 	fVec3[4096];
	float 	fRec4[3];
	float 	fVec4[4096];
	float 	fRec5[3];
	float 	fVec5[4096];
	float 	fRec6[3];
	float 	fVec6[4096];
	float 	fRec7[3];
	float 	fVec7[4096];
	float 	fRec8[3];
	float 	fVec8[4096];
	float 	fRec9[3];
	float 	fVec9[4096];
	float 	fRec10[3];
	float 	fVec10[4096];
	float 	fRec11[3];
	float 	fVec11[4096];
	float 	fRec12[3];
	float 	fVec12[4096];
	float 	fRec13[3];
	float 	fVec13[4096];
	float 	fRec14[3];
	float 	fVec14[4096];
	float 	fRec15[3];
	float 	fVec15[2048];
	float 	fRec16[3];
	float 	fVec16[512];
	float 	fRec17[3];
	FAUSTFLOAT 	fslider6;
	float 	fVec17[4096];
	float 	fRec18[3];
	float 	fVec18[4096];
	float 	fRec19[3];
	float 	fVec19[4096];
	float 	fRec20[3];
	float 	fVec20[4096];
	float 	fRec21[3];
	float 	fVec21[4096];
	float 	fRec22[3];
	float 	fVec22[4096];
	float 	fRec23[3];
	float 	fVec23[4096];
	float 	fRec24[3];
	float 	fVec24[4096];
	float 	fRec25[3];
	float 	fVec25[4096];
	float 	fRec26[3];
	float 	fVec26[4096];
	float 	fRec27[3];
	float 	fVec27[4096];
	float 	fRec28[3];
	float 	fVec28[4096];
	float 	fRec29[3];
	float 	fVec29[4096];
	float 	fRec30[3];
	float 	fVec30[4096];
	float 	fRec31[3];
	float 	fVec31[2048];
	float 	fRec32[3];
	float 	fVec32[1024];
	float 	fRec33[3];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "karplus32");
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

	virtual int getNumInputs() 	{ return 0; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.1f;
		fslider1 = 128.0f;
		fbutton0 = 0.0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) iRec2[i] = 0;
		fslider2 = 0.5f;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec1[i] = 0;
		fslider3 = 32.0f;
		fslider4 = 128.0f;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		fslider5 = 1.0f;
		for (int i=0; i<4096; i++) fVec2[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<4096; i++) fVec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<4096; i++) fVec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<4096; i++) fVec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<4096; i++) fVec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<4096; i++) fVec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<4096; i++) fVec8[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<4096; i++) fVec9[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<4096; i++) fVec10[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<4096; i++) fVec11[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<4096; i++) fVec12[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<4096; i++) fVec13[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<4096; i++) fVec14[i] = 0;
		for (int i=0; i<3; i++) fRec15[i] = 0;
		for (int i=0; i<2048; i++) fVec15[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<512; i++) fVec16[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		fslider6 = 0.5f;
		for (int i=0; i<4096; i++) fVec17[i] = 0;
		for (int i=0; i<3; i++) fRec18[i] = 0;
		for (int i=0; i<4096; i++) fVec18[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<4096; i++) fVec19[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<4096; i++) fVec20[i] = 0;
		for (int i=0; i<3; i++) fRec21[i] = 0;
		for (int i=0; i<4096; i++) fVec21[i] = 0;
		for (int i=0; i<3; i++) fRec22[i] = 0;
		for (int i=0; i<4096; i++) fVec22[i] = 0;
		for (int i=0; i<3; i++) fRec23[i] = 0;
		for (int i=0; i<4096; i++) fVec23[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<4096; i++) fVec24[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<4096; i++) fVec25[i] = 0;
		for (int i=0; i<3; i++) fRec26[i] = 0;
		for (int i=0; i<4096; i++) fVec26[i] = 0;
		for (int i=0; i<3; i++) fRec27[i] = 0;
		for (int i=0; i<4096; i++) fVec27[i] = 0;
		for (int i=0; i<3; i++) fRec28[i] = 0;
		for (int i=0; i<4096; i++) fVec28[i] = 0;
		for (int i=0; i<3; i++) fRec29[i] = 0;
		for (int i=0; i<4096; i++) fVec29[i] = 0;
		for (int i=0; i<3; i++) fRec30[i] = 0;
		for (int i=0; i<4096; i++) fVec30[i] = 0;
		for (int i=0; i<3; i++) fRec31[i] = 0;
		for (int i=0; i<2048; i++) fVec31[i] = 0;
		for (int i=0; i<3; i++) fRec32[i] = 0;
		for (int i=0; i<1024; i++) fVec32[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("karplus32");
		interface->openVerticalBox("excitator");
		interface->addHorizontalSlider("excitation (samples)", &fslider1, 128.0f, 2.0f, 512.0f, 1.0f);
		interface->addButton("play", &fbutton0);
		interface->closeBox();
		interface->openVerticalBox("noise generator");
		interface->addHorizontalSlider("level", &fslider2, 0.5f, 0.0f, 1.0f, 0.1f);
		interface->closeBox();
		interface->addHorizontalSlider("output volume", &fslider6, 0.5f, 0.0f, 1.0f, 0.1f);
		interface->openVerticalBox("resonator x32");
		interface->addHorizontalSlider("attenuation", &fslider0, 0.1f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("detune", &fslider3, 32.0f, 0.0f, 512.0f, 1.0f);
		interface->addHorizontalSlider("duration (samples)", &fslider4, 128.0f, 2.0f, 512.0f, 1.0f);
		interface->addHorizontalSlider("polyphony", &fslider5, 1.0f, 0.0f, 32.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.5f * (1.0f - float(fslider0)));
		float 	fSlow1 = (1.0f / float(fslider1));
		float 	fSlow2 = float(fbutton0);
		float 	fSlow3 = (4.656612875245797e-10f * float(fslider2));
		float 	fSlow4 = float(fslider3);
		float 	fSlow5 = float(fslider4);
		int 	iSlow6 = int((int(((fSlow5 + (30 * fSlow4)) - 1.5f)) & 4095));
		float 	fSlow7 = float(fslider5);
		int 	iSlow8 = (fSlow7 > 30);
		int 	iSlow9 = int((int(((fSlow5 + (28 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow10 = (fSlow7 > 28);
		int 	iSlow11 = int((int(((fSlow5 + (26 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow12 = (fSlow7 > 26);
		int 	iSlow13 = int((int(((fSlow5 + (24 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow14 = (fSlow7 > 24);
		int 	iSlow15 = int((int(((fSlow5 + (22 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow16 = (fSlow7 > 22);
		int 	iSlow17 = int((int(((fSlow5 + (20 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow18 = (fSlow7 > 20);
		int 	iSlow19 = int((int(((fSlow5 + (18 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow20 = (fSlow7 > 18);
		int 	iSlow21 = int((int(((fSlow5 + (16 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow22 = (fSlow7 > 16);
		int 	iSlow23 = int((int(((fSlow5 + (14 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow24 = (fSlow7 > 14);
		int 	iSlow25 = int((int(((fSlow5 + (12 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow26 = (fSlow7 > 12);
		int 	iSlow27 = int((int(((fSlow5 + (10 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow28 = (fSlow7 > 10);
		int 	iSlow29 = int((int(((fSlow5 + (8 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow30 = (fSlow7 > 8);
		int 	iSlow31 = int((int(((fSlow5 + (6 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow32 = (fSlow7 > 6);
		int 	iSlow33 = int((int(((fSlow5 + (4 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow34 = (fSlow7 > 4);
		int 	iSlow35 = int((int(((fSlow5 + (2 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow36 = (fSlow7 > 2);
		int 	iSlow37 = int((int((fSlow5 - 1.5f)) & 4095));
		int 	iSlow38 = (fSlow7 > 0);
		float 	fSlow39 = float(fslider6);
		int 	iSlow40 = int((int((((31 * fSlow4) + fSlow5) - 1.5f)) & 4095));
		int 	iSlow41 = (fSlow7 > 31);
		int 	iSlow42 = int((int(((fSlow5 + (29 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow43 = (fSlow7 > 29);
		int 	iSlow44 = int((int(((fSlow5 + (27 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow45 = (fSlow7 > 27);
		int 	iSlow46 = int((int(((fSlow5 + (25 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow47 = (fSlow7 > 25);
		int 	iSlow48 = int((int(((fSlow5 + (23 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow49 = (fSlow7 > 23);
		int 	iSlow50 = int((int(((fSlow5 + (21 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow51 = (fSlow7 > 21);
		int 	iSlow52 = int((int(((fSlow5 + (19 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow53 = (fSlow7 > 19);
		int 	iSlow54 = int((int(((fSlow5 + (17 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow55 = (fSlow7 > 17);
		int 	iSlow56 = int((int(((fSlow5 + (15 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow57 = (fSlow7 > 15);
		int 	iSlow58 = int((int(((fSlow5 + (13 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow59 = (fSlow7 > 13);
		int 	iSlow60 = int((int(((fSlow5 + (11 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow61 = (fSlow7 > 11);
		int 	iSlow62 = int((int(((fSlow5 + (9 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow63 = (fSlow7 > 9);
		int 	iSlow64 = int((int(((fSlow5 + (7 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow65 = (fSlow7 > 7);
		int 	iSlow66 = int((int(((fSlow5 + (5 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow67 = (fSlow7 > 5);
		int 	iSlow68 = int((int(((fSlow5 + (3 * fSlow4)) - 1.5f)) & 4095));
		int 	iSlow69 = (fSlow7 > 3);
		int 	iSlow70 = int((int(((fSlow4 + fSlow5) - 1.5f)) & 4095));
		int 	iSlow71 = (fSlow7 > 1);
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fVec0[0] = fSlow2;
			fRec1[0] = ((fRec1[1] + ((fSlow2 - fVec0[1]) > 0.0f)) - (fSlow1 * (fRec1[1] > 0)));
			iRec2[0] = (12345 + (1103515245 * iRec2[1]));
			float fTemp0 = (fSlow3 * (iRec2[0] * ((fRec1[0] > 0.0f) + 1.52587890625e-05f)));
			fVec1[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec0[1] + fRec0[2])));
			fRec0[0] = fVec1[(IOTA-iSlow6)&4095];
			fVec2[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec3[1] + fRec3[2])));
			fRec3[0] = fVec2[(IOTA-iSlow9)&4095];
			fVec3[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec4[1] + fRec4[2])));
			fRec4[0] = fVec3[(IOTA-iSlow11)&4095];
			fVec4[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec5[1] + fRec5[2])));
			fRec5[0] = fVec4[(IOTA-iSlow13)&4095];
			fVec5[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec6[1] + fRec6[2])));
			fRec6[0] = fVec5[(IOTA-iSlow15)&4095];
			fVec6[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec7[2] + fRec7[1])));
			fRec7[0] = fVec6[(IOTA-iSlow17)&4095];
			fVec7[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec8[1] + fRec8[2])));
			fRec8[0] = fVec7[(IOTA-iSlow19)&4095];
			fVec8[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec9[1] + fRec9[2])));
			fRec9[0] = fVec8[(IOTA-iSlow21)&4095];
			fVec9[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec10[1] + fRec10[2])));
			fRec10[0] = fVec9[(IOTA-iSlow23)&4095];
			fVec10[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec11[1] + fRec11[2])));
			fRec11[0] = fVec10[(IOTA-iSlow25)&4095];
			fVec11[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec12[1] + fRec12[2])));
			fRec12[0] = fVec11[(IOTA-iSlow27)&4095];
			fVec12[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec13[1] + fRec13[2])));
			fRec13[0] = fVec12[(IOTA-iSlow29)&4095];
			fVec13[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec14[1] + fRec14[2])));
			fRec14[0] = fVec13[(IOTA-iSlow31)&4095];
			fVec14[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec15[1] + fRec15[2])));
			fRec15[0] = fVec14[(IOTA-iSlow33)&4095];
			fVec15[IOTA&2047] = (fTemp0 + (fSlow0 * (fRec16[1] + fRec16[2])));
			fRec16[0] = fVec15[(IOTA-iSlow35)&2047];
			fVec16[IOTA&511] = ((fSlow0 * (fRec17[1] + fRec17[2])) + fTemp0);
			fRec17[0] = fVec16[(IOTA-iSlow37)&511];
			output0[i] = (FAUSTFLOAT)(fSlow39 * ((((((((((((((((iSlow38 * fRec17[0]) + (iSlow36 * fRec16[0])) + (iSlow34 * fRec15[0])) + (iSlow32 * fRec14[0])) + (iSlow30 * fRec13[0])) + (iSlow28 * fRec12[0])) + (iSlow26 * fRec11[0])) + (iSlow24 * fRec10[0])) + (iSlow22 * fRec9[0])) + (iSlow20 * fRec8[0])) + (iSlow18 * fRec7[0])) + (iSlow16 * fRec6[0])) + (iSlow14 * fRec5[0])) + (iSlow12 * fRec4[0])) + (iSlow10 * fRec3[0])) + (iSlow8 * fRec0[0])));
			fVec17[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec18[1] + fRec18[2])));
			fRec18[0] = fVec17[(IOTA-iSlow40)&4095];
			fVec18[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec19[1] + fRec19[2])));
			fRec19[0] = fVec18[(IOTA-iSlow42)&4095];
			fVec19[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec20[1] + fRec20[2])));
			fRec20[0] = fVec19[(IOTA-iSlow44)&4095];
			fVec20[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec21[1] + fRec21[2])));
			fRec21[0] = fVec20[(IOTA-iSlow46)&4095];
			fVec21[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec22[1] + fRec22[2])));
			fRec22[0] = fVec21[(IOTA-iSlow48)&4095];
			fVec22[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec23[1] + fRec23[2])));
			fRec23[0] = fVec22[(IOTA-iSlow50)&4095];
			fVec23[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec24[1] + fRec24[2])));
			fRec24[0] = fVec23[(IOTA-iSlow52)&4095];
			fVec24[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec25[1] + fRec25[2])));
			fRec25[0] = fVec24[(IOTA-iSlow54)&4095];
			fVec25[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec26[1] + fRec26[2])));
			fRec26[0] = fVec25[(IOTA-iSlow56)&4095];
			fVec26[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec27[1] + fRec27[2])));
			fRec27[0] = fVec26[(IOTA-iSlow58)&4095];
			fVec27[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec28[1] + fRec28[2])));
			fRec28[0] = fVec27[(IOTA-iSlow60)&4095];
			fVec28[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec29[1] + fRec29[2])));
			fRec29[0] = fVec28[(IOTA-iSlow62)&4095];
			fVec29[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec30[1] + fRec30[2])));
			fRec30[0] = fVec29[(IOTA-iSlow64)&4095];
			fVec30[IOTA&4095] = (fTemp0 + (fSlow0 * (fRec31[1] + fRec31[2])));
			fRec31[0] = fVec30[(IOTA-iSlow66)&4095];
			fVec31[IOTA&2047] = (fTemp0 + (fSlow0 * (fRec32[1] + fRec32[2])));
			fRec32[0] = fVec31[(IOTA-iSlow68)&2047];
			fVec32[IOTA&1023] = (fTemp0 + (fSlow0 * (fRec33[1] + fRec33[2])));
			fRec33[0] = fVec32[(IOTA-iSlow70)&1023];
			output1[i] = (FAUSTFLOAT)(fSlow39 * ((((((((((((((((iSlow71 * fRec33[0]) + (iSlow69 * fRec32[0])) + (iSlow67 * fRec31[0])) + (iSlow65 * fRec30[0])) + (iSlow63 * fRec29[0])) + (iSlow61 * fRec28[0])) + (iSlow59 * fRec27[0])) + (iSlow57 * fRec26[0])) + (iSlow55 * fRec25[0])) + (iSlow53 * fRec24[0])) + (iSlow51 * fRec23[0])) + (iSlow49 * fRec22[0])) + (iSlow47 * fRec21[0])) + (iSlow45 * fRec20[0])) + (iSlow43 * fRec19[0])) + (iSlow41 * fRec18[0])));
			// post processing
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
			iRec2[1] = iRec2[0];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
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
