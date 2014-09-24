//-----------------------------------------------------
// name: "mixer"
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
	float 	fConst0;
	FAUSTFLOAT 	fslider0;
	float 	fRec1[2];
	FAUSTFLOAT 	fcheckbox0;
	float 	fRec0[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	FAUSTFLOAT 	fcheckbox1;
	float 	fRec2[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	FAUSTFLOAT 	fcheckbox2;
	float 	fRec4[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT 	fslider3;
	float 	fRec7[2];
	FAUSTFLOAT 	fcheckbox3;
	float 	fRec6[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fentry3;
	FAUSTFLOAT 	fslider4;
	float 	fRec9[2];
	FAUSTFLOAT 	fcheckbox4;
	float 	fRec8[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fentry4;
	FAUSTFLOAT 	fslider5;
	float 	fRec11[2];
	FAUSTFLOAT 	fcheckbox5;
	float 	fRec10[2];
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT 	fentry5;
	FAUSTFLOAT 	fslider6;
	float 	fRec13[2];
	FAUSTFLOAT 	fcheckbox6;
	float 	fRec12[2];
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT 	fentry6;
	FAUSTFLOAT 	fslider7;
	float 	fRec15[2];
	FAUSTFLOAT 	fcheckbox7;
	float 	fRec14[2];
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT 	fentry7;
	FAUSTFLOAT 	fslider8;
	float 	fRec16[2];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "mixer");
		m->declare("version", "1.0");
		m->declare("author", "Grame");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("volume.dsp/name", "volume");
		m->declare("volume.dsp/version", "1.0");
		m->declare("volume.dsp/author", "Grame");
		m->declare("volume.dsp/license", "BSD");
		m->declare("volume.dsp/copyright", "(c)GRAME 2006");
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
		m->declare("panpot.dsp/name", "panpot");
		m->declare("panpot.dsp/version", "1.0");
		m->declare("panpot.dsp/author", "Grame");
		m->declare("panpot.dsp/license", "BSD");
		m->declare("panpot.dsp/copyright", "(c)GRAME 2006");
		m->declare("vumeter.dsp/name", "vumeter");
		m->declare("vumeter.dsp/version", "1.0");
		m->declare("vumeter.dsp/author", "Grame");
		m->declare("vumeter.dsp/license", "BSD");
		m->declare("vumeter.dsp/copyright", "(c)GRAME 2006");
	}

	virtual int getNumInputs() 	{ return 8; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / float(min(192000, max(1, fSamplingFreq))));
		fslider0 = 0.0f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fcheckbox0 = 0.0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fentry0 = 0.0f;
		fslider1 = 0.0f;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fcheckbox1 = 0.0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fentry1 = 0.0f;
		fslider2 = 0.0f;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fcheckbox2 = 0.0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fentry2 = 0.0f;
		fslider3 = 0.0f;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		fcheckbox3 = 0.0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		fentry3 = 0.0f;
		fslider4 = 0.0f;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fcheckbox4 = 0.0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		fentry4 = 0.0f;
		fslider5 = 0.0f;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		fcheckbox5 = 0.0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		fentry5 = 0.0f;
		fslider6 = 0.0f;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		fcheckbox6 = 0.0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		fentry6 = 0.0f;
		fslider7 = 0.0f;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		fcheckbox7 = 0.0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		fentry7 = 0.0f;
		fslider8 = 0.0f;
		for (int i=0; i<2; i++) fRec16[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("mixer");
		interface->openHorizontalBox("stereo out");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider8, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 0");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider7, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph7, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox7);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry7, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 1");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider6, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph6, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox6);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry6, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 2");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider5, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph5, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox5);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry5, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 3");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider4, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph4, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox4);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry4, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 4");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider3, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph3, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox3);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry3, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 5");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider2, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph2, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox2);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry2, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 6");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider1, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph1, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox1);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry1, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->openVerticalBox("voice 7");
		interface->openHorizontalBox("0x00");
		interface->openVerticalBox("fader");
		interface->addVerticalSlider("dB", &fslider0, 0.0f, -96.0f, 4.0f, 0.1f);
		interface->closeBox();
		interface->addVerticalBargraph("meter", &fbargraph0, 0.0f, 1.0f);
		interface->closeBox();
		interface->addCheckButton("mute", &fcheckbox0);
		interface->openVerticalBox("panpot");
		interface->addNumEntry("0x00", &fentry0, 0.0f, -8.0f, 8.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider0))));
		float 	fSlow1 = (1 - float(fcheckbox0));
		float 	fSlow2 = (0.0625f * (float(fentry0) - 8));
		float 	fSlow3 = (1 + fSlow2);
		float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider1))));
		float 	fSlow5 = (1 - float(fcheckbox1));
		float 	fSlow6 = (0.0625f * (float(fentry1) - 8));
		float 	fSlow7 = (1 + fSlow6);
		float 	fSlow8 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider2))));
		float 	fSlow9 = (1 - float(fcheckbox2));
		float 	fSlow10 = (0.0625f * (float(fentry2) - 8));
		float 	fSlow11 = (1 + fSlow10);
		float 	fSlow12 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider3))));
		float 	fSlow13 = (1 - float(fcheckbox3));
		float 	fSlow14 = (0.0625f * (float(fentry3) - 8));
		float 	fSlow15 = (1 + fSlow14);
		float 	fSlow16 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider4))));
		float 	fSlow17 = (1 - float(fcheckbox4));
		float 	fSlow18 = (0.0625f * (float(fentry4) - 8));
		float 	fSlow19 = (1 + fSlow18);
		float 	fSlow20 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider5))));
		float 	fSlow21 = (1 - float(fcheckbox5));
		float 	fSlow22 = (0.0625f * (float(fentry5) - 8));
		float 	fSlow23 = (1 + fSlow22);
		float 	fSlow24 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider6))));
		float 	fSlow25 = (1 - float(fcheckbox6));
		float 	fSlow26 = (0.0625f * (float(fentry6) - 8));
		float 	fSlow27 = (1 + fSlow26);
		float 	fSlow28 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider7))));
		float 	fSlow29 = (1 - float(fcheckbox7));
		float 	fSlow30 = (0.0625f * (float(fentry7) - 8));
		float 	fSlow31 = (1 + fSlow30);
		float 	fSlow32 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider8))));
		float 	fSlow33 = (0 - fSlow2);
		float 	fSlow34 = (0 - fSlow6);
		float 	fSlow35 = (0 - fSlow10);
		float 	fSlow36 = (0 - fSlow14);
		float 	fSlow37 = (0 - fSlow18);
		float 	fSlow38 = (0 - fSlow22);
		float 	fSlow39 = (0 - fSlow26);
		float 	fSlow40 = (0 - fSlow30);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* input6 = input[6];
		FAUSTFLOAT* input7 = input[7];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec1[0] = ((0.999f * fRec1[1]) + fSlow0);
			float fTemp0 = (fSlow1 * ((float)input7[i] * fRec1[0]));
			fRec0[0] = max((fRec0[1] - fConst0), min(0.99f, fabsf(fTemp0)));
			fbargraph0 = fRec0[0];
			float fTemp1 = fTemp0;
			fRec3[0] = ((0.999f * fRec3[1]) + fSlow4);
			float fTemp2 = (fSlow5 * ((float)input6[i] * fRec3[0]));
			fRec2[0] = max((fRec2[1] - fConst0), min(0.99f, fabsf(fTemp2)));
			fbargraph1 = fRec2[0];
			float fTemp3 = fTemp2;
			fRec5[0] = ((0.999f * fRec5[1]) + fSlow8);
			float fTemp4 = (fSlow9 * ((float)input5[i] * fRec5[0]));
			fRec4[0] = max((fRec4[1] - fConst0), min(0.99f, fabsf(fTemp4)));
			fbargraph2 = fRec4[0];
			float fTemp5 = fTemp4;
			fRec7[0] = ((0.999f * fRec7[1]) + fSlow12);
			float fTemp6 = (fSlow13 * ((float)input4[i] * fRec7[0]));
			fRec6[0] = max((fRec6[1] - fConst0), min(0.99f, fabsf(fTemp6)));
			fbargraph3 = fRec6[0];
			float fTemp7 = fTemp6;
			fRec9[0] = ((0.999f * fRec9[1]) + fSlow16);
			float fTemp8 = (fSlow17 * ((float)input3[i] * fRec9[0]));
			fRec8[0] = max((fRec8[1] - fConst0), min(0.99f, fabsf(fTemp8)));
			fbargraph4 = fRec8[0];
			float fTemp9 = fTemp8;
			fRec11[0] = ((0.999f * fRec11[1]) + fSlow20);
			float fTemp10 = (fSlow21 * ((float)input2[i] * fRec11[0]));
			fRec10[0] = max((fRec10[1] - fConst0), min(0.99f, fabsf(fTemp10)));
			fbargraph5 = fRec10[0];
			float fTemp11 = fTemp10;
			fRec13[0] = ((0.999f * fRec13[1]) + fSlow24);
			float fTemp12 = (fSlow25 * ((float)input1[i] * fRec13[0]));
			fRec12[0] = max((fRec12[1] - fConst0), min(0.99f, fabsf(fTemp12)));
			fbargraph6 = fRec12[0];
			float fTemp13 = fTemp12;
			fRec15[0] = ((0.999f * fRec15[1]) + fSlow28);
			float fTemp14 = (fSlow29 * ((float)input0[i] * fRec15[0]));
			fRec14[0] = max((fRec14[1] - fConst0), min(0.99f, fabsf(fTemp14)));
			fbargraph7 = fRec14[0];
			float fTemp15 = fTemp14;
			fRec16[0] = ((0.999f * fRec16[1]) + fSlow32);
			output0[i] = (FAUSTFLOAT)(fRec16[0] * ((((((((fSlow31 * fTemp15) + (fSlow27 * fTemp13)) + (fSlow23 * fTemp11)) + (fSlow19 * fTemp9)) + (fSlow15 * fTemp7)) + (fSlow11 * fTemp5)) + (fSlow7 * fTemp3)) + (fSlow3 * fTemp1)));
			output1[i] = (FAUSTFLOAT)(fRec16[0] * ((((((((fSlow40 * fTemp15) + (fSlow39 * fTemp13)) + (fSlow38 * fTemp11)) + (fSlow37 * fTemp9)) + (fSlow36 * fTemp7)) + (fSlow35 * fTemp5)) + (fSlow34 * fTemp3)) + (fSlow33 * fTemp1)));
			// post processing
			fRec16[1] = fRec16[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
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
