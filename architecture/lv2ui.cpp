/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2009-2016 Albert Graef <aggraef@gmail.com>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 3 of the
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

/* LV2 UI architecture for Faust synths. */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <list>
#include <map>
#include <set>

// generic Faust dsp and UI classes
#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>

using namespace std;

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

/******************************************************************************
*******************************************************************************

		       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

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
  bool is_instr;
  int nelems, nports;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  LV2UI(int maxvoices = 0);
  virtual ~LV2UI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

  bool have_freq, have_gain, have_gate;
  bool is_voice_ctrl(const char *label);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    
  virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();

  virtual void run();

  virtual void declare(float* zone, const char* key, const char* value);
    
};

LV2UI::LV2UI(int maxvoices)
{
  is_instr = maxvoices>0;
  have_freq = have_gain = have_gate = false;
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
  elems[nelems].max = 1.0;
  elems[nelems].step = 1.0;
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

inline bool LV2UI::is_voice_ctrl(const char *label)
{
  if (!is_instr)
    return false;
  else if (!have_freq && !strcmp(label, "freq"))
    return (have_freq = true);
  else if (!have_gain && !strcmp(label, "gain"))
    return (have_gain = true);
  else if (!have_gate && !strcmp(label, "gate"))
    return (have_gate = true);
  else
    return false;
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

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeclass>>

//----------------------------------------------------------------------------
//  LV2 UI interface
//----------------------------------------------------------------------------

#line 282 "lv2ui.cpp"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

/* Define this to get debugging output from the Qt-related code. Setting this
   to a value >1 will give even more extensive debugging output. Using a zero
   value or commenting the following line makes sure that no qDebug calls are
   included in the code at all. */
//#define FAUSTQT_DEBUG 1

/* Define this to get debugging output from the LV2 UI interface
   (communication between LV2 host and LV2 UI code). Setting this to a value
   >1 will give even more extensive debugging output. */
//#define LV2UI_DEBUG 1

// Set this to the proper shared library extension for your system
#ifndef DLLEXT
#define DLLEXT ".so"
#endif

#ifndef URI_PREFIX
#define URI_PREFIX "https://faustlv2.bitbucket.io"
#endif

#ifndef PLUGIN_URI
#define PLUGIN_URI URI_PREFIX "/mydsp"
#endif

//#define NVOICES 16

#ifndef VOICE_CTRLS
#define VOICE_CTRLS 1
#endif

#ifndef FAUST_MTS
#define FAUST_MTS 1
#endif

#ifndef FAUST_META
#define FAUST_META 1
#endif

#ifndef FAUST_MIDICC
#define FAUST_MIDICC 1
#endif

#if FAUST_MTS

// Helper classes to read and store MTS tunings.

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string>
#include <vector>
#include <algorithm>

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
  if (fread(data, 1, len, fp) < (size_t)len) {
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
      if (t.data) {
#if 1
	// The data isn't currently used anywhere in the GUI, so we get rid of
	// it immediately.
	free(t.data); t.data = 0; t.len = 0;
#endif
	tuning.push_back(t);
      }
    }
  }
  closedir(dp);
  // sort found tunings by name
  sort(tuning.begin(), tuning.end(), compareByName);
}

#endif

/***************************************************************************/

/* LV2 plugin UI data structure. This is a stripped-down version of the
   LV2Plugin struct in lv2.cpp whose sole purpose is to keep track of all the
   parameters of the plugin. Therefore most of the live port data isn't
   actually implemented and we only have to maintain a single dsp and UI
   instance here, no matter how many voices we actually have in the case of an
   instrument plugin. In fact, the dsp instance is mostly used to fill in the
   data of the various UI objects that we use. NOTE: This *must* be kept in
   sync with lv2.cpp so that (at least) the numbering of the control ports
   matches up. */

struct LV2PluginUI {
  const int maxvoices;	// maximum number of voices (zero if not an instrument)
  const int ndsps;	// number of dsp instances (1 if maxvoices==0)
  int nvoices;		// current number of voices (<= maxvoices)
  int tuning_no;	// current tuning number (<= n_tunings)
  mydsp *dsp;		// the dsp
  LV2UI *ui;		// Faust interface description
  int n_in, n_out;	// number of input and output control ports
  int *ctrls;		// Faust ui elements (indices into ui->elems)
  int *inctrls, *outctrls;	// indices for active and passive controls
  int freq, gain, gate;	// indices of voice controls
  int n_params;		// number of param mapping entries
  int *param_no;	// map Qt -> Faust control numbers
  int *control_no;	// map Faust -> Qt control numbers
#if 0
  std::map<uint8_t,int> ctrlmap; // MIDI controller map
#endif
  // LV2 UI tie-ins to send port data from GUI to the host.
  LV2UI_Write_Function write_function;
  LV2UI_Controller controller;

  // Static methods. These all use static data so they can be invoked before
  // instantiating a plugin.

  // Global meta data (dsp name, author, etc.).
  static Meta *meta;
  static void init_meta()
  {
    if (!meta) {
      meta = new Meta;
      mydsp tmp_dsp;
      tmp_dsp.metadata(meta);
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

  static const char *pluginLicense()
  {
    init_meta();
    return meta->get("license", "");
  }

  static const char *pluginVersion()
  {
    init_meta();
    return meta->get("version", "");
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

  // Instance methods.

  LV2PluginUI(const int num_voices,
	      LV2UI_Write_Function write_function,
	      LV2UI_Controller controller)
    : maxvoices(num_voices), ndsps(num_voices<=0?1:num_voices),
      write_function(write_function), controller(controller)
  {
    // Initialize static data.
    init_meta();
#if FAUST_MTS
    // Synth: load tuning sysex data if present.
    if (num_voices>0) load_sysex_data();
#endif
    // Allocate data structures and set some reasonable defaults.
    nvoices = maxvoices/2;
    if (nvoices <= 0) nvoices = 1;
    tuning_no = 0;
    n_in = n_out = 0;
    freq = gain = gate = -1;
    ctrls = inctrls = outctrls = NULL;
    // Initialize the Faust DSP.
    dsp = new mydsp();
    ui = new LV2UI(num_voices);
    dsp->init(48000);
    dsp->buildUserInterface(ui);
    // The ports are numbered as follows: 0..k-1 are the control ports, then
    // come the n audio input ports, then the m audio output ports, and
    // finally the midi input port and the polyphony and tuning controls.
    int k = ui->nports, p = 0, q = 0;
    // Allocate tables for the built-in control elements and their ports.
    ctrls = (int*)calloc(k, sizeof(int));
    inctrls = (int*)calloc(k, sizeof(int));
    outctrls = (int*)calloc(k, sizeof(int));
    assert(k == 0 || (ctrls && inctrls && outctrls));
    // Scan the Faust UI for active and passive controls which become the
    // input and output control ports of the plugin, respectively.
    for (int i = 0, j = 0; i < ui->nelems; i++) {
      switch (ui->elems[i].type) {
      case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
	// control groups (ignored right now)
	break;
      case UI_H_BARGRAPH: case UI_V_BARGRAPH:
	// passive controls (output ports)
	ctrls[j++] = i;
	outctrls[q++] = i;
	break;
      default:
	// active controls (input ports)
	if (maxvoices == 0)
	  goto noinstr;
	else if (freq == -1 &&
		 !strcmp(ui->elems[i].label, "freq"))
	  freq = i;
	else if (gain == -1 &&
		 !strcmp(ui->elems[i].label, "gain"))
	  gain = i;
	else if (gate == -1 &&
		 !strcmp(ui->elems[i].label, "gate"))
	  gate = i;
	else {
	noinstr:
#if 0 //FAUST_MIDICC
	  // Disabled since the controller mappings aren't currently used
	  // anywhere in the GUI.
	  std::map< int, list<strpair> >::iterator it =
	    ui->metadata.find(i);
	  if (it != ui->metadata.end()) {
	    // Scan for controller mappings.
	    for (std::list<strpair>::iterator jt = it->second.begin();
		 jt != it->second.end(); jt++) {
	      const char *key = jt->first, *val = jt->second;
	      if (strcmp(key, "midi") == 0) {
		unsigned num;
		if (sscanf(val, "ctrl %u", &num) < 1) continue;
		ctrlmap.insert(std::pair<uint8_t,int>(num, p));
	      }
	    }
	  }
#endif
	  ctrls[j++] = i;
	  inctrls[p++] = i;
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
    // Map of GUI parameter numbers to the actual control indices. This is
    // initialized later by LV2QtGUI::open() below.
    n_params = 0;
    param_no = control_no = 0;
  }

  ~LV2PluginUI()
  {
    delete dsp;
    delete ui;
    if (param_no) delete[] param_no;
    if (control_no) delete[] control_no;
    free(ctrls); free(inctrls); free(outctrls);
  }

  // Qt GUI interface. XXXTODO: This should probably be rewritten some
  // time. Currently these methods mostly emulate some methods from the VST
  // API which the Qt GUI implementation was originally written for. Note that
  // these methods work with normalized (0..1) values, like in the VST API.

  double quantize(double x, double d)
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

  float nvoices_val, tuning_no_val;

  // AG: Note that we have to map the GUI parameter numbers to the actual
  // Faust control indices here. This extra level of indirection is necessary
  // because in some cases Qt may enumerate the child widgets in a different
  // order than what we have in the Faust program. The mapping is computed in
  // the QTGUIWrapper class below, please see the comments there for details.

  int map_param(int i)
  {
    return (i < 0 || i >= n_params) ? i : param_no[i];
  }

  int map_control(int i)
  {
    return (i < 0 || i >= n_params) ? i : control_no[i];
  }

  void setParameter(int index, float value)
  {
    index = map_param(index);
    const double eps = 1e-5;
    int k = ui->nports;
    int n = dsp->getNumInputs(), m = dsp->getNumOutputs();
    if (index >= 0 && index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      float min = ui->elems[j].min;
      float max = ui->elems[j].max;
      float step = ui->elems[j].step;
      float val = (min == max)?min:min+quantize(value*(max-min), step);
      if (fabs(val) < fabs(step) || fabs(val)/fabs(max-min) < eps)
	val = 0.0;
      // Make sure to clamp the value in the allowed range, Carla barfs
      // otherwise.
      val = clamp(min, max, val);
      if (*ui->elems[j].zone != val) {
	// update our copy of the control value
	*ui->elems[j].zone = val;
	// also send the data to the LV2 host
#if LV2UI_DEBUG
	fprintf(stderr, "%s: write_function: send value %g on port #%d\n", pluginName(), val, index);
#endif
	write_function(controller, index, sizeof(float), 0,
		       ui->elems[j].zone);
      }
    } else if (index == k && maxvoices > 0) {
      int oldval = nvoices;
      nvoices = (int)quantize((value*maxvoices), 1);
      if (nvoices <= 0) nvoices = 1;
      if (oldval != nvoices) {
	// index is k (#regular control ports) + n (#audio ins) + m (#audio
	// outs) + 1 (#midi ins), next port is polyphony control
	int index = k+n+m+1;
	nvoices_val = (float)nvoices;
#if LV2UI_DEBUG
	fprintf(stderr, "%s: write_function: send nvoices value %g on port #%d\n", pluginName(), nvoices_val, index);
#endif
	write_function(controller, index, sizeof(float), 0, &nvoices_val);
      }
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      int oldval = tuning_no;
      tuning_no = (int)quantize((value*n_tunings), 1);
      if (oldval != tuning_no) {
	// index is k (#regular control ports) + n (#audio ins) + m (#audio
	// outs) + 1 (#midi ins) + 1 (polyphony control), next port is tuning
	// control
	int index = k+n+m+2;
	tuning_no_val = (float)tuning_no;
#if LV2UI_DEBUG
	fprintf(stderr, "%s: write_function: send tuning value %g on port #%d\n", pluginName(), tuning_no_val, index);
#endif
	write_function(controller, index, sizeof(float), 0, &tuning_no_val);
      }
#endif
    }
  }

  // Version of setParameter which is used by the LV2 port_event callback.
  // This just sets the port value directly, without translation, and doesn't
  // send the value.
  void setPortval(int index, float value)
  {
    const double eps = 1e-5;
    int k = ui->nports;
    int n = dsp->getNumInputs(), m = dsp->getNumOutputs();
    if (index >= 0 && index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      // quantize+clamp
      float min = ui->elems[j].min;
      float max = ui->elems[j].max;
      float step = ui->elems[j].step;
      float val = (min == max)?min:min+quantize(value-min, step);
      if (fabs(val) < fabs(step) || fabs(val)/fabs(max-min) < eps)
	val = 0.0;
      val = clamp(min, max, val);
      // update our copy of the control value
      *ui->elems[j].zone = val;
    } else if (index == k && maxvoices > 0) {
      nvoices = (int)value;
      if (nvoices <= 0) nvoices = 1;
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      tuning_no = (int)value;
#endif
    }
  }

  float clamp(float min, float max, float val)
  {
    if (min<=max) {
      if (val < min) val = min;
      if (val > max) val = max;
    } else {
      if (val > min) val = min;
      if (val < max) val = max;
    }
    return val;
  }
  
  float normalize(float min, float max, float val)
  {
    if (min == max)
      return 0.0f;
    else
      return clamp(0.0, 1.0, (val-min)/(max-min));
  }

  float getParameter(int index)
  {
    index = map_param(index);
    int k = ui->nports;
    if (index >= 0 && index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      return normalize(ui->elems[j].min, ui->elems[j].max, *ui->elems[j].zone);
    } else if (index == k && maxvoices > 0) {
      return normalize(0, maxvoices, nvoices);
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      return normalize(0, n_tunings, tuning_no);
#endif
    } else
      return 0.0f;
  }

  void getParameterName(int index, char *label)
  {
    index = map_param(index);
    int k = ui->nports;
    strcpy(label, "");
    if (index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      strncpy(label, ui->elems[j].label, 32);
    } else if (index == k && maxvoices > 0) {
      strcpy(label, "Polyphony");
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      strcpy(label, "Tuning");
#endif
    }
  }

  void getParameterDisplay(int index, char *text)
  {
    index = map_param(index);
    int k = ui->nports;
    strcpy(text, "");
    if (index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      sprintf(text, "%0.5g", *ui->elems[j].zone);
    } else if (index == k && maxvoices > 0) {
      sprintf(text, "%d voices", nvoices);
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      sprintf(text, "%d %s", tuning_no,
	      tuning_no>0?mts->tuning[tuning_no-1].name:
	      "default");
#endif
    }
  }

  float getMinimum(int index)
  {
    index = map_param(index);
    int k = ui->nports;
    if (index < 0)
      return 0.0f;
    else if (index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      float min = ui->elems[j].min;
      return min;
    } else if (index == k && maxvoices > 0) {
      return 0.0f;
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      return 0.0f;
#endif
    } else
      return 0.0f;
  }

  float getMaximum(int index)
  {
    index = map_param(index);
    int k = ui->nports;
    if (index < 0)
      return 0.0f;
    else if (index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      float max = ui->elems[j].max;
      return max;
    } else if (index == k && maxvoices > 0) {
      return (float)maxvoices;
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      return (float)n_tunings;
#endif
    } else
      return 0.0f;
  }

  float getStep(int index)
  {
    index = map_param(index);
    int k = ui->nports;
    if (index < 0)
      return 0.0f;
    else if (index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      float step = ui->elems[j].step;
      return step;
    } else if (index == k && maxvoices > 0) {
      return 1.0f;
#if FAUST_MTS
    } else if (index == k+1 && n_tunings > 0) {
      return 1.0f;
#endif
    } else
      return 0.0f;
  }

  int isPassiveControl(int index)
  {
    index = map_param(index);
    int k = ui->nports;
    if (index >= 0 && index < k) {
      int j = ctrls[index];
      assert(index == ui->elems[j].port);
      switch (ui->elems[j].type) {
      case UI_V_BARGRAPH:
	return 1;         // passive control is of type UI_V_BARGRAPH
      case UI_H_BARGRAPH:
	return 2;         // passive control is of type UI_H_BARGRAPH
      default:
	return 0;         // not a passive control
      }
    } else
      return 0;
  }

};

Meta *LV2PluginUI::meta = 0;
int LV2PluginUI::n_tunings = 0;
#if FAUST_MTS
MTSTunings *LV2PluginUI::mts = 0;
#endif

/* Generic Faust Qt GUI code by Roman Svidler ported from faust-vst-qt. */

// Copyright (c) 2015-2016 by Roman Svidler
// Copyright (c) 2015-2016 by Albert Gräf

// This is based on the generic Qt code provided by QTUI.h in the Faust
// distribution. Here we only add the necessary machinery to interface between
// the GUI and the LV2 host.

// OSCUI.h and httpdUI.h pull in their own definition of the Meta struct,
// prevent name clashes with our version.
#define Meta FaustMeta

#include "lv2qtgui.h"

#include <iostream>
#include <QApplication>
#include <faust/gui/QTUI.h>
#ifdef OSCCTRL
#include <faust/gui/OSCUI.h>
#endif
#ifdef HTTPCTRL
#include <faust/gui/httpdUI.h>
#endif

#include <QWidget>
#include <QList>
#include <QtAlgorithms>

#line 1018 "lv2ui.cpp"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

LV2QtGUI::LV2QtGUI(LV2PluginUI* plugui) :
  widget(NULL), uidsp(NULL), qtinterface(NULL),
#ifdef OSCCTRL
  oscinterface(NULL),
#endif
#ifdef HTTPCTRL
  httpdinterface(NULL),
#endif
  plugui(plugui)
{
  // The host should actually take care of initializing Qt, but we also do
  // that here if needed to be on the safe side.
  static int argc = 0;
  static char* argv[1] = {0};
  if(qApp) {
#if FAUSTQT_DEBUG
    qDebug() << "qApp already exists";
#endif
  } else {
#if FAUSTQT_DEBUG
    qDebug() << "qApp is created!";
#endif
    new QApplication(argc, argv);
  }

#if FAUSTQT_DEBUG
  qDebug() << "qApp=" << qApp;
#endif
}

LV2QtGUI::~LV2QtGUI()
{
}

// This is a little wrapper class around QTGUI which takes care of eliminating
// the freq/gain/gate controls of instruments in the user interface when
// running the dsp's buildUserInterface method. It also adds polyphony and
// tuning controls to instruments as needed, and does some other extra
// bookkeeping and on-the-fly modifications that we need. -ag

// AG XXXFIXME: This is more complicated than we'd like it to be, since for
// some unknown reason, the children of a tab widget are listed in reverse
// order (https://bitbucket.org/agraef/faust-lv2/issues/10). Since the GUI
// code assumes that the widgets are in the same order as the Faust control
// elements, we need to construct a mapping that translates between the two.

struct QTGUIElem {
  int i;
  QList<int> p;
  const char *label;
  QTGUIElem(int _i, QList<int> _p, const char *_label) :
    i(_i), p(_p), label(_label)
  {}
};

bool qtguielem_less(const QTGUIElem &x, const QTGUIElem &y)
{
  // Qt4 doesn't define operator< on QLists, so we need to do the
  // lexicographic comparison manually.
  QList<int>::const_iterator i = x.p.begin(), j = y.p.begin();
  for (; i != x.p.end() && j != y.p.end(); ++i, ++j) {
    if (*i < *j)
      return true;
    else if (*i > *j)
      return false;
  }
  return j != y.p.end();
}

class QTGUIWrapper : public UI
{
protected:
  bool is_instr;
  QTGUI *ui;
  QList<int> path;
  QList<QTGUIElem> elems;
  int level, maxvoices, numtunings;
  float *voices_zone, *tuning_zone;
  bool have_freq, have_gain, have_gate;
  bool is_voice_ctrl(const char *label)
  {
    if (!is_instr)
      return false;
    else if (!have_freq && !strcmp(label, "freq"))
      return (have_freq = true);
    else if (!have_gain && !strcmp(label, "gain"))
      return (have_gain = true);
    else if (!have_gate && !strcmp(label, "gate"))
      return (have_gate = true);
    else
      return false;
  }
public:
  int *elem_no;
  int nelems;
  QTGUIWrapper(QTGUI *_ui, int _maxvoices, int _numtunings,
	       float *_voices_zone, float *_tuning_zone) :
    is_instr(_maxvoices>0), ui(_ui), level(0),
    maxvoices(_maxvoices), numtunings(_numtunings),
    voices_zone(_voices_zone), tuning_zone(_tuning_zone),
    have_freq(false), have_gain(false), have_gate(false),
    elem_no(0), nelems(0)
  {}
  virtual ~QTGUIWrapper() {}

  // -- widget's layouts
  virtual void openTabBox(const char* label)
  { ui->openTabBox(label); level++; path.append(-1); }
  virtual void openHorizontalBox(const char* label)
  { ui->openHorizontalBox(label); level++; path.append(0); }
  virtual void openVerticalBox(const char* label)
  { ui->openVerticalBox(label); level++; path.append(0); }
  virtual void closeBox()
  {
    if (--level == 0) {
#if VOICE_CTRLS
      if (is_instr) {
	// Add polyphony and tuning controls (experimental).
	ui->addHorizontalSlider("Polyphony", voices_zone,
				maxvoices/2, 0, maxvoices, 1);
	addElem("Polyphony");
#if FAUST_MTS
	if (numtunings>0)
	  ui->addHorizontalSlider("Tuning", tuning_zone, 0, 0, numtunings, 1);
	addElem("Tuning");
#endif
      }
#endif
      // AG: Create an index of all the GUI elements in the right order.
      // XXXFIXME: This may need to be revisited if Qt or Faust changes the
      // order for some reason.
      qSort(elems.begin(), elems.end(), qtguielem_less);
      elem_no = new int[nelems];
      nelems = 0;
      for (QList<QTGUIElem>::iterator x = elems.begin(); x != elems.end();
	   ++x, ++nelems) {
	elem_no[nelems] = x->i;
#if 0
	fprintf(stderr, "%s (#%d):", x->label, x->i);
	for (QList<int>::iterator i = x->p.begin(); i != x->p.end(); ++i) {
	  fprintf(stderr, " %d", *i);
	}
	fprintf(stderr, "\n");
#endif
      }
    }
    path.pop_back();
    if (!path.empty()) {
      if (path.last() < 0)
	path.last()--;
      else
	path.last()++;
    }
    ui->closeBox();
  }

  void addElem(const char *label)
  {
    elems.append(QTGUIElem(nelems++, path, label));
    assert(!path.empty());
    if (path.last() < 0)
      path.last()--;
    else
      path.last()++;
  }

  // -- active widgets
  virtual void addButton(const char* label, FAUSTFLOAT* zone)
  {
    if (!is_voice_ctrl(label)) {
      ui->addButton(label, zone);
      addElem(label);
    }
  }
  virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
  {
    if (!is_voice_ctrl(label)) {
      ui->addCheckButton(label, zone);
      addElem(label);
    }
  }
  virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone,
				 FAUSTFLOAT init, FAUSTFLOAT min,
				 FAUSTFLOAT max, FAUSTFLOAT step)
  {
    if (!is_voice_ctrl(label)) {
      ui->addVerticalSlider(label, zone, init, min, max, step);
      addElem(label);
    }
  }
  virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone,
				   FAUSTFLOAT init, FAUSTFLOAT min,
				   FAUSTFLOAT max, FAUSTFLOAT step) 	
  {
    if (!is_voice_ctrl(label)) {
      ui->addHorizontalSlider(label, zone, init, min, max, step);
      addElem(label);
    }
  }
  virtual void addNumEntry(const char* label, FAUSTFLOAT* zone,
			   FAUSTFLOAT init, FAUSTFLOAT min,
			   FAUSTFLOAT max, FAUSTFLOAT step)
  {
    if (!is_voice_ctrl(label)) {
      ui->addNumEntry(label, zone, init, min, max, step);
      addElem(label);
    }
  }
    
  // -- passive widgets
  virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone,
				     FAUSTFLOAT min, FAUSTFLOAT max) 
  {
    ui->addHorizontalBargraph(label, zone, min, max);
    addElem(label);
  }
  virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone,
				   FAUSTFLOAT min, FAUSTFLOAT max)
  {
    ui->addVerticalBargraph(label, zone, min, max);
    addElem(label);
  }
    
  virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
 
  virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
  {
    // XXXFIXME: Faust's Qt GUI implementation handles [scale:log] and similar
    // meta data affecting the scaling of slider data, but this isn't
    // supported in the current faust-lv2 implementation, so we just ignore
    // this meta data for now.
    if (strcmp(key, "scale")) ui->declare(zone, key, val);
  }

};

QWidget* LV2QtGUI::open()
{
  static int argc = 0;
  static char* argv[1] = {0};

  widget = new QScrollArea();
  widget->setWidgetResizable(true);
  qtinterface = new QTGUI(widget);
  widget->setWidget(qtinterface);

  mydsp* dsp = new mydsp();

#if FAUSTQT_DEBUG
  qDebug() << "open interface: " << qtinterface;
#endif
  // We build the QTGUI indirectly through QTGUIWrapper whose sole purpose is
  // to eliminate the voice controls in case of an instrument plugin.
  QTGUIWrapper qtwrapper(qtinterface,
			 plugui->maxvoices, plugui->n_tunings,
			 &voices_zone, &tuning_zone);
  dsp->buildUserInterface(&qtwrapper);

  // AG: Initialize the Qt GUI -> Faust UI mapping (see the explanation under
  // QTGUIWrapper above).
  plugui->n_params = qtwrapper.nelems;
  plugui->param_no = qtwrapper.elem_no;
  plugui->control_no = new int[qtwrapper.nelems];
  for (int i = 0; i < qtwrapper.nelems; i++)
    plugui->control_no[plugui->param_no[i]] = i;
#if 0
  for (int i = 0; i < plugui->n_params; i++)
    fprintf(stderr, "QT->LV2 %d -> %d\n", i, plugui->param_no[i]);
  for (int i = 0; i < plugui->n_params; i++)
    fprintf(stderr, "LV2->QT %d -> %d\n", i, plugui->control_no[i]);
#endif

  // HTTPD and OSC support (experimental)
#ifdef HTTPCTRL
  httpdinterface = new httpdUI(plugui->pluginName(),
			       dsp->getNumInputs(), dsp->getNumOutputs(),
			       argc, argv);
  dsp->buildUserInterface(httpdinterface);
#if FAUSTQT_DEBUG
  qDebug() << "HTTPD is on";
#endif
#endif

#ifdef OSCCTRL
  oscinterface = new OSCUI(plugui->pluginName(), argc, argv);
  dsp->buildUserInterface(oscinterface);
#if FAUSTQT_DEBUG
  qDebug() << "OSC is on";
#endif
#endif

  // update the size of the QTGUI after creating the GUI elements
  qtinterface->adjustSize();

  // the dimensions of the plug-in window must not exceed screenGeometry
  // (-80 pixel tolerance)
  int desktopHeight = QApplication::desktop()->screenGeometry().height()-80;
  int desktopWidth  = QApplication::desktop()->screenGeometry().width()-80;

#if FAUSTQT_DEBUG>1
  qDebug() << "desktop-height: " <<
           QApplication::desktop()->screenGeometry().height();
  qDebug() << "desktop-width: "  <<
           QApplication::desktop()->screenGeometry().width();
#endif

  // determine the window size
  rectangle.top    = 0;
  rectangle.left   = 0;
  // the height of the plug-in GUI must not exceed the desktop resolution
  if(qtinterface->height() > desktopHeight)
    rectangle.bottom = desktopHeight;
  else // add 20 pixels for scroll bars
    rectangle.bottom = qtinterface->height()+20;
  // the width of the plug-in GUI must not exceed the desktop resolution
  if(qtinterface->width() > desktopWidth)
    rectangle.right  = desktopWidth;
  else // add 20 pixels for scroll bars
    rectangle.right  = qtinterface->width()+20;

  // adjust the widget size
  widget->resize(rectangle.right, rectangle.bottom);

  // determine all children of qtinterface of type QObject*
  QList<QObject*> allObjects = qtinterface->findChildren<QObject*>();
#if FAUSTQT_DEBUG>1
  qDebug() << "QObjects total count: " << allObjects.count();
#endif

  int lv2ParamCount = 0;

  bool vBargraphChecked = true; // used in HorizontalBargraph search
  QObject* lastObject;          // used in addNumDisplay check

  for (QList<QObject*>::iterator i = allObjects.begin(); i != allObjects.end();
       ++i) {
#if FAUSTQT_DEBUG>1
    qDebug("");
    // debugging output: class name of found object
    qDebug() << "QObject: " << (*i)->metaObject()->className();
    qDebug() << "LV2 parameter assigned: " << lv2ParamCount;
#endif

    // Slider
    QSlider* slider = qobject_cast<QSlider*>(*i);
    if (slider) {
#if FAUSTQT_DEBUG>1
      qDebug("found slider!");
#endif
      slider->setProperty("lv2Param", lv2ParamCount);
      QList<QObject*> c; c.append(slider);
      controls.append(c);

      connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateUI()),
              Qt::QueuedConnection);
      updateQTGUI(slider, plugui->getParameter(lv2ParamCount));

      lv2ParamCount++;
    }

    // Knob
    QDial* dial = qobject_cast<QDial*>(*i);
    if (dial) {
#if FAUSTQT_DEBUG>1
      qDebug("found knob!");
#endif
      dial->setProperty("lv2Param", lv2ParamCount);
      QList<QObject*> c; c.append(dial);
      controls.append(c);

      connect(dial, SIGNAL(valueChanged(int)), this, SLOT(updateUI()),
              Qt::QueuedConnection);
      updateQTGUI(dial, plugui->getParameter(lv2ParamCount));

      lv2ParamCount++;
    }

    // Button
    QPushButton* button = qobject_cast<QPushButton*>(*i);
    if (button) {
#if FAUSTQT_DEBUG>1
      qDebug("found button!");
#endif
      button->setProperty("lv2Param", lv2ParamCount);
      QList<QObject*> c; c.append(button);
      controls.append(c);

      connect(button, SIGNAL(pressed()), this,
	      SLOT(updateUI_buttonPressed()), Qt::QueuedConnection);
      connect(button, SIGNAL(released()), this,
	      SLOT(updateUI_buttonReleased()), Qt::QueuedConnection);

      // button is released when GUI opens
      plugui->setParameter(lv2ParamCount, 0.0f);

      lv2ParamCount++;
    }

    // NumDisplay (list) / NumEntry / numerical HorizontalBargraph
    QDoubleSpinBox* num = qobject_cast<QDoubleSpinBox*>(*i);
    if (num) {
      // ignore QDoubleSpinBox with NoButtons, as it's not a list but
      // a NumDisplay
      if(num->buttonSymbols() != QAbstractSpinBox::NoButtons) {
#if FAUSTQT_DEBUG>1
        qDebug("found list!");
#endif
        num->setProperty("lv2Param", lv2ParamCount);
	QList<QObject*> c; c.append(num);
        controls.append(c);

        connect(num, SIGNAL(valueChanged(double)), this, SLOT(updateUI()),
                Qt::QueuedConnection);

        updateQTGUI(num, plugui->getParameter(lv2ParamCount));

        lv2ParamCount++;

        // if previous control is passive and vBargraphChecked==false:
        // found NumDisplay of VerticalBargraphs
        // this is always called if we found a vBargraph in the previous
        // iteration
      } else if(plugui->isPassiveControl(lv2ParamCount-1)==1
                && !vBargraphChecked) {
#if FAUSTQT_DEBUG>1
        qDebug("found numDisplay!");
#endif
        num->setProperty("lv2Param", lv2ParamCount-1);
	controls[lv2ParamCount-1].append(num);
        passive_controls.append(num);

        // the corresponding display of the vBargraphs is now set
        vBargraphChecked = true;
      } else if(lv2ParamCount < plugui->n_params &&
		plugui->isPassiveControl(lv2ParamCount)==2
                && vBargraphChecked) {
        QAbstractSlider* sliderOrKnob =
	  qobject_cast<QAbstractSlider*>(lastObject);
        // only if the previously found QObject is neither slider nor
        // knob
        if(!sliderOrKnob) {
#if FAUSTQT_DEBUG>1
          qDebug("found horizontal bargraph with numerical style!");
#endif
          num->setProperty("lv2Param", lv2ParamCount);
	  QList<QObject*> c; c.append(num);
	  controls.append(c);
	  passive_controls.append(num);

          lv2ParamCount++;
        }
      }
    }

    // CheckBox
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(*i);
    if (checkBox) {
#if FAUSTQT_DEBUG>1
      qDebug("found checkbox!");
#endif
      checkBox->setProperty("lv2Param", lv2ParamCount);
      QList<QObject*> c; c.append(checkBox);
      controls.append(c);

      connect(checkBox, SIGNAL(stateChanged(int)), this,
	      SLOT(updateUI_checkBox()), Qt::QueuedConnection);

      // if the LV2 parameter of the checkbox is less than 0.5 then the
      // checkbox is unchecked
      updateQTGUI(checkBox, plugui->getParameter(lv2ParamCount));

      lv2ParamCount++;
    }

    // Bargraph
    AbstractDisplay* bargraph = dynamic_cast<AbstractDisplay*>(*i);
    if (bargraph) {
      if(plugui->isPassiveControl(lv2ParamCount)==1) {
#if FAUSTQT_DEBUG>1
        qDebug("found vertical bargraph!");
#endif
        vBargraphChecked = false;
      }
#if FAUSTQT_DEBUG>1
      else
        qDebug("found horizontal bargraph!");
#endif

      bargraph->setProperty("lv2Param", lv2ParamCount);
      //led->setProperty("elemType", "led");
      QList<QObject*> c; c.append(bargraph);
      controls.append(c);
      passive_controls.append(bargraph);

      lv2ParamCount++;
    }

    // Radiobuttons
    uiRadioButtons* uiRadio = dynamic_cast<uiRadioButtons*>(*i);
    if (uiRadio) {
#if FAUSTQT_DEBUG>1
      qDebug("found radio buttons!");
#endif

      QList<QRadioButton*> radiobuttons =
	uiRadio->findChildren<QRadioButton*>();

      int radioCount = 0;
      QList<QObject*> c;
      // iterate over all radio buttons in this group
      for (QList<QRadioButton*>::iterator r = radiobuttons.begin();
           r != radiobuttons.end(); ++r) {
        float minimum = plugui->getMinimum(lv2ParamCount);
        float maximum = plugui->getMaximum(lv2ParamCount);
	float step = plugui->getStep(lv2ParamCount);
        // set all properties needed for updateUI()
        (*r)->setProperty("value", radioCount);
        (*r)->setProperty("lv2Param", lv2ParamCount);
        (*r)->setProperty("minimum", minimum);
        (*r)->setProperty("maximum", maximum);
        (*r)->setProperty("singleStep", step);
        connect((*r), SIGNAL(clicked(bool)), this, SLOT(updateUI()),
                Qt::QueuedConnection);

        // set the proper radio button as "clicked" when the GUI opens
	updateQTGUI(*r, plugui->getParameter(lv2ParamCount));
	c.append(*r);
        radioCount++;
      }
      controls.append(c);
      lv2ParamCount++;
    }

    // Menu
    uiMenu* menu = dynamic_cast<uiMenu*>(*i);
    if (menu) {
#if FAUSTQT_DEBUG>1
      qDebug("found menu!");
#endif

      float minimum = plugui->getMinimum(lv2ParamCount);
      float maximum = plugui->getMaximum(lv2ParamCount);
      float step = plugui->getStep(lv2ParamCount);

      menu->setProperty("lv2Param", lv2ParamCount);
      menu->setProperty("minimum", minimum);
      menu->setProperty("maximum", maximum);
      menu->setProperty("singleStep", step);
      QList<QObject*> c; c.append(menu);
      controls.append(c);

      connect(menu, SIGNAL(activated(int)), this, SLOT(updateUI()),
              Qt::QueuedConnection);

      updateQTGUI(menu, plugui->getParameter(lv2ParamCount));

      lv2ParamCount++;
    }
    // save the QObject of this iteration
    lastObject = (*i);
  }

#if FAUSTQT_DEBUG>1
  qDebug() << "LV2 parameters assigned: " << lv2ParamCount;
#endif

#ifdef HTTPCTRL
  httpdinterface->run();
#ifdef QRCODECTRL
  // FIXME: This will pop up each time the GUI is opened. We should maybe have
  // a little button in the GUI somewhere so that the user can show the QR
  // code when needed.
  qtinterface->displayQRCode(httpdinterface->getTCPPort());
#endif
#endif

#ifdef OSCCTRL
  oscinterface->run();
#endif

  qtinterface->run();

  // The STYLE symbol is set during compilation when using the -style option
  // of the faust2lv2 script or the corresponding options in the Makefile. You
  // can also set this manually if needed, but note that the corresponding
  // resource needs to be present in the qmake project (this is taken care of
  // automagically when using the -style option). Otherwise (or if no style
  // was specified) the default style will be used. -ag
#ifdef STYLE
  // set the style sheet for this GUI, if any
  QString styleSheet("");
  // C preprocessor stringify magic to insert the style sheet name
#define __xstr(s) __str(s)
#define __str(s) #s
  QFile file(":/" __xstr(STYLE) ".qss");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    styleSheet = QLatin1String(file.readAll());
    file.close();
  }
  widget->setStyleSheet(styleSheet);
#endif

#if FAUSTQT_DEBUG
  qDebug() << "Number of controls: " << controls.size();
  qDebug() << "Number of passive controls: " << passive_controls.size();
#endif

  uidsp = dsp;
  return widget;
}

void LV2QtGUI::close()
{
#ifdef HTTPCTRL
  httpdinterface->stop();
  delete httpdinterface;
  httpdinterface = NULL;
#endif
#ifdef OSCCTRL
  oscinterface->stop();
  delete oscinterface;
  oscinterface = NULL;
#endif
  qtinterface->stop();
  delete qtinterface;
  qtinterface = NULL;
  delete widget;
  widget = NULL;
  mydsp* dsp = (mydsp*)uidsp;
  delete dsp;
  dsp = NULL;
  controls.clear();
  passive_controls.clear();
}

void LV2QtGUI::updateQTGUI(QObject* object, float value)
{
  const double eps = 1e-5;
  double minimum, maximum, step, newValue;
  const char* valueChar;

  // checkboxes and radio buttons need special treatment
  QCheckBox* checkBox = qobject_cast<QCheckBox*>(object);
  if (checkBox) {
    if (value < 0.5f)
      checkBox->setChecked(false);
    else
      checkBox->setChecked(true);
    return;
  }

  minimum = object->property("minimum").toDouble();
  maximum = object->property("maximum").toDouble();
  step    = object->property("singleStep").toDouble();

  QRadioButton* radioBut = qobject_cast<QRadioButton*>(object);
  if (radioBut) {
    int radioVal = radioBut->property("value").toInt();
    float val = plugui->normalize(minimum, maximum, radioVal);
    if (fabs(val-value)/(1+fabs(maximum-minimum)) < eps)
      radioBut->click();
    return;
  }

  if (QString(object->metaObject()->className())=="uiMenu")
    valueChar = "currentIndex";
  else
    valueChar = "value";

#if FAUSTQT_DEBUG>1
  int lv2Param = object->property("lv2Param").toInt();
  qDebug() << "QTGUI: lv2Param: " << lv2Param;
  qDebug() << "QTGUI: LV2 value: " << value;
  qDebug() << "QTGUI: old Qt value: "
	   << object->property(valueChar).toDouble();
#endif

  newValue = (minimum==maximum)?minimum : minimum+plugui->quantize(value*
             (maximum-minimum), step);

  if (fabs(newValue) < fabs(step) ||
      fabs(newValue)/fabs(maximum-minimum) < eps)
    newValue = 0.0;

  // set new value with setProperty("value",..), as setValue() is not
  // defined for QObject
  object->setProperty(valueChar, newValue);
#if FAUSTQT_DEBUG>1
  qDebug() << "QTGUI: new Qt value: "
	   << object->property(valueChar).toDouble();
#endif
  uiMenu* menu = dynamic_cast<uiMenu*>(object);
  if (menu) menu->updateZone(0); // updates the currentIndex
}

void LV2QtGUI::updatePassiveControl(QObject* object, float value)
{
  int lv2Param = object->property("lv2Param").toInt();
  float minimum  = plugui->getMinimum(lv2Param);
  float maximum  = plugui->getMaximum(lv2Param);

  float fValue = value*maximum - value*minimum + minimum;

  AbstractDisplay* bargraph  = dynamic_cast<AbstractDisplay*>(object);
  QDoubleSpinBox* numDisplay = dynamic_cast<QDoubleSpinBox*>(object);

  if(bargraph)
    bargraph->setValue(fValue);
  else if(numDisplay)
    numDisplay->setValue(fValue);
}


/***********************
 *******  Slots ********
 ***********************/

// The slots are called in response to interactive changes of a GUI element
// (e.g., slider movements). Here we update the corresponding LV2 parameters.

void LV2QtGUI::updateUI_buttonPressed()
{
  int lv2Param = QObject::sender()->property("lv2Param").toInt();
#if FAUSTQT_DEBUG>1
  qDebug() << "LV2: lv2Param: " << lv2Param;
  qDebug() << "LV2: button pressed";
#endif
  plugui->setParameter(lv2Param, 1.0f);
}

void LV2QtGUI::updateUI_buttonReleased()
{
  int lv2Param = QObject::sender()->property("lv2Param").toInt();
#if FAUSTQT_DEBUG>1
  qDebug() << "LV2: lv2Param: " << lv2Param;
  qDebug() << "LV2: button released";
#endif
  plugui->setParameter(lv2Param, 0.0f);
}

void LV2QtGUI::updateUI_checkBox()
{
  int lv2Param = QObject::sender()->property("lv2Param").toInt();
#if FAUSTQT_DEBUG>1
  qDebug() << "LV2: lv2Param: " << lv2Param;
#endif

  // if CheckBox == checked
  if(QObject::sender()->property("checked").toBool()) {
#if FAUSTQT_DEBUG>1
    qDebug("checkbox checked");
#endif
    plugui->setParameter(lv2Param, 1.0f);
  } else {
#if FAUSTQT_DEBUG>1
    qDebug("checkbox unchecked");
#endif
    plugui->setParameter(lv2Param, 0.0f);
  }
}

void LV2QtGUI::updateUI()
{
  double value, minimum, maximum, step;
  int lv2Param;

  // for uiMenu we have the property "currentIndex" instead of the property
  // "value"
  if (QString(QObject::sender()->metaObject()->className())=="uiMenu")
    value = QObject::sender()->property("currentIndex").toDouble();
  else
    value = QObject::sender()->property("value").toDouble();
  lv2Param  = QObject::sender()->property("lv2Param").toInt();
  minimum   = QObject::sender()->property("minimum").toDouble();
  maximum   = QObject::sender()->property("maximum").toDouble();
  step      = QObject::sender()->property("singleStep").toDouble();

#if FAUSTQT_DEBUG>1
  qDebug() << "LV2: lv2Param: "       << lv2Param;
  char text[32];
  plugui->getParameterName(lv2Param, text);
  qDebug() << "LV2: label: "          << text;
  qDebug() << "LV2: min: "            << minimum;
  qDebug() << "LV2: max: "            << maximum;
  qDebug() << "LV2: step: "           << step;
  qDebug() << "LV2: new Qt value: "   << value;
  qDebug() << "LV2: old LV2 value: "  << plugui->getParameter(lv2Param);
#endif

  float newFloat = plugui->normalize(minimum, maximum, value);
  plugui->setParameter(lv2Param, newFloat);
#if FAUSTQT_DEBUG>1
  qDebug() << "LV2: new LV2 value: " << plugui->getParameter(lv2Param);
#endif
#if VOICE_CTRLS
  if (lv2Param >= plugui->ui->nports) {
    // Extra polyphony and tuning controls. Generate some informative tooltips
    // for these so that the user understands the meaning of these values.
    QWidget *widget = qobject_cast<QWidget*>(QObject::sender());
    char text[32];
    plugui->getParameterDisplay(lv2Param, text);
    widget->setToolTip(text);
  }
#endif
}

/* LV2-specific part starts here. ********************************************/

// Thanks are due to Harry van Haaren and Spencer Jackson for figuring out how
// this magic works. -ag

static LV2UI_Handle
instantiate(const LV2UI_Descriptor * descriptor,
	    const char * plugin_uri,
	    const char * bundle_path,
	    LV2UI_Write_Function write_function,
	    LV2UI_Controller controller,
	    LV2UI_Widget * widget,
	    const LV2_Feature * const * features)
{
  if (strcmp(plugin_uri, PLUGIN_URI)) {
    fprintf(stderr,
	    "%s: ERROR: this GUI does not support plugin with URI %s\n",
	    PLUGIN_URI, plugin_uri);
    return NULL;
  }

  LV2PluginUI* plugui = new LV2PluginUI(LV2PluginUI::numVoices(),
					write_function, controller);
  LV2QtGUI* self = new LV2QtGUI(plugui);

  if (self == NULL) return NULL;

  *widget = (LV2UI_Widget)self->open();
  
  return (LV2UI_Handle)self;
}

static void
cleanup(LV2UI_Handle ui)
{
  LV2QtGUI* self = (LV2QtGUI*)ui;
  self->close();
  delete self->plugui;
  delete self;
}

static void update_portval(LV2QtGUI* self, int i)
{
  // Map the port (Faust control) number to the Qt control number.
  LV2PluginUI* plugui = (LV2PluginUI*)self->plugui;
  i = plugui->map_control(i);
  if (i >= 0 && i < self->controls.size() && !self->controls[i].empty()) {
    float val = plugui->getParameter(i);
    if (plugui->isPassiveControl(i)) {
      for (QList<QObject*>::iterator it = self->controls[i].begin();
	   it != self->controls[i].end(); ++it)
	self->updatePassiveControl(*it, val);
    } else {
      for (QList<QObject*>::iterator it = self->controls[i].begin();
	   it != self->controls[i].end(); ++it)
	self->updateQTGUI(*it, val);
    }
  }
}

static
void port_event(LV2UI_Handle ui,
		uint32_t port_index,
		uint32_t buffer_size,
		uint32_t format,
		const void * buffer)
{
  if(!format) {
    float val = *(float*)buffer;
    LV2QtGUI* self = (LV2QtGUI*)ui;
    LV2PluginUI* plugui = (LV2PluginUI*)self->plugui;
    int i = port_index, k = plugui->ui->nports;
    int n = plugui->dsp->getNumInputs(), m = plugui->dsp->getNumOutputs();
#if LV2UI_DEBUG
    {
#if LV2UI_DEBUG<2
      int j = plugui->map_control(i);
      if (!plugui->isPassiveControl(j))
#endif
      fprintf(stderr, "%s: port_event: got value %g on port #%d\n", plugui->pluginName(), val, i);
    }
#endif
    if (i < k) { // regular dsp control
      plugui->setPortval(i, val);
      update_portval(self, i);
    } else {
      i -= k;
      if (i < n) // audio input
	goto err;
      else {
	i -= n;
	if (i < m) // audio output
	  goto err;
	else if (i == m) // midi input
	  goto err;
	else if (i == m+1) { // polyphony control (instruments only)
	  plugui->setPortval(k, val);
	  update_portval(self, k);
	} else if (i == m+2) { // tuning control (instruments only)
	  plugui->setPortval(k+1, val);
	  update_portval(self, k+1);
	} else {
	err:
	  fprintf(stderr, "%s: bad port number %u\n", PLUGIN_URI, port_index);
	}
      }
    }
  }
}

static const void*
extension_data(const char* uri)
{
  return NULL;
}

static const LV2UI_Descriptor descriptor = {
  PLUGIN_URI "ui",
  instantiate,
  cleanup,
  port_event,
  extension_data
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2UI_Descriptor*
lv2ui_descriptor(uint32_t index)
{
  switch (index) {
  case 0:
    return &descriptor;
  default:
    return NULL;
  }
}
