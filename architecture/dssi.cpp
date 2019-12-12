/************************************************************************
	IMPORTANT NOTE : this file contains two clearly delimited
	sections : the ARCHITECTURE section (in two parts) and the
	USER section. Each section is governed by its own copyright
	and license. Please check individually each section for
	license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2011 Michael J. Wilson

    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute
    it and/or modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute that
    work under terms of your choice, so long as this FAUST
    architecture section is not modified.
    ---------------------------------------------------------------------

************************************************************************/

/********************************************************************
 * dssi.cpp - Polyphonic dssi wrapper for the FAUST language.
 *
 * Usage: faust -a dssi.cpp myfaustprog.dsp
 *
 * By Michael J. Wilson (mwilson@alumni.caltech.edu)
 *
 * Made with reference to:
 *   - vsti-mono.cpp by Julius Smith (http://ccrma.stanford.edu/~jos/)
 *   - ladspa.cpp by GRAME, Centre National de Creation Musicale
 *   - karplong.cpp by Chris Cannam, Steve Harris, Sean Bolton
 *
 * Because of the inclusion of code from ladspa.cpp, this architecture
 * file is also released under the GNU General Public Licenses version
 * 3.  Sections which were taken from ladspa.cpp are clearly marked
 * below, in order to trace the GPL dependency.
 * As with faust2pd and vsti-mono.cpp, to obtain MIDI control via
 * NoteOn/Off, Velocity, and KeyNumber, there must be a button named
 * "gate" and sliders (or numeric entries) named "gain" and "freq" in
 * the Faust patch specified in myfaustprog.dsp.
 *
 * FAUST
 * Copyright (C) 2003-2007 GRAME, Centre National de Creation Musicale
 * http://www.grame.fr/
 *
 ********************************************************************/

#include "dssi.h"
#include "ladspa.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <list>

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
    #warning *** dssi.cpp: NO SSE FLAG (denormals may slow things down) ***
    #define AVOIDDENORMALS
#endif

struct Meta : std::map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};


#define sym(name) xsym(name)
#define xsym(name) #name

inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }
inline int int2pow2 (int x) { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************

VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

//---------------------Abstract User Interface--------------------
//
// Abstract definition of a User Interface to be passed to the
// buildUserInterface method of a Faust Signal Processor
//
//----------------------------------------------------------------
class UI
{
    bool fStopped;

public:
    UI() : fStopped(false) {}
    virtual ~UI() {}

    virtual void addButton(const char* label, float* zone) = 0;
    virtual void addToggleButton(const char* label, float* zone) = 0;
    virtual void addCheckButton(const char* label, float* zone) = 0;
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

    // -- passive widgets
    virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

    // -- frames and labels
    virtual void openFrameBox(const char* label) = 0;
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;

    virtual void show() = 0;
    virtual void run() = 0;

    void stop()		{ fStopped = true; }
    bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

//------------------Abstract Signal Processor---------------------
//
//  Abstract definition of a Faust Signal Processor
//
//----------------------------------------------------------------
class dsp
{
protected:
    int fSampleRate;
public:
    dsp() {}
    virtual ~dsp() {}
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void buildUserInterface(UI* interface) = 0;
    virtual void init(int sample_rate) = 0;
    virtual void compute(int len, float** inputs, float** outputs)= 0;
};

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

////////////////////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////////////////////
class Plugin;
class DescriptorUI;
class Voice;

////////////////////////////////////////////////////////////////////////////////
// Global data
////////////////////////////////////////////////////////////////////////////////
// Maximum polyphony, must be at least 1 (TODO make this configurable at compile / runtime?)
const int MAX_POLYPHONY = 64;
// Descriptor
DSSI_Descriptor* g_dssi_descriptor;
// Additional data for descriptor:
LADSPA_Descriptor* g_ladspa_descriptor;
// Program descriptor:
DSSI_Program_Descriptor g_program_descriptor;

// Global data for the descriptor:
std::vector<LADSPA_PortDescriptor> g_port_descriptors;
std::vector<LADSPA_PortRangeHint> g_port_range_hints;
std::vector<const char*> g_port_names;
const char* g_name;

////////////////////////////////////////////////////////////////////////////////
// The enclosed code is from ladspa.cpp 
// TODO groups of port names
static const char* inames[] =
{
    "input00", "input01", "input02", "input03", "input04",
    "input05", "input06", "input07", "input08", "input09",
    "input10", "input11", "input12", "input13", "input14",
    "input15", "input16", "input17", "input18", "input19",
    "input20", "input21", "input22", "input23", "input24",
    "input25", "input26", "input27", "input28", "input29",
    "input30", "input31", "input32", "input33", "input34",
    "input35", "input36", "input37", "input38", "input39"
};
static const char* onames[] =
{
    "output00", "output01", "output02", "output03", "output04",
    "output05", "output06", "output07", "output08", "output09",
    "output10", "output11", "output12", "output13", "output14",
    "output15", "output16", "output17", "output18", "output19",
    "output20", "output21", "output22", "output23", "output24",
    "output25", "output26", "output27", "output28", "output29",
    "output30", "output31", "output32", "output33", "output34",
    "output35", "output36", "output37", "output38", "output39"
};
// END code from ladspa.cpp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global helper functions
////////////////////////////////////////////////////////////////////////////////
char* get_metadata_if_exists(const char* key, const char* default_string)
{
    // TODO probably want to free these somehow.  Currently only used for ladspa descriptor
    Meta meta;
    static mydsp dsp;
    dsp.metadata(&meta);
    if(meta.find(key) != meta.end())
    {
        return strdup(meta[key]);
    }
    else
    {
        return strdup(default_string);
    }
}

////////////////////////////////////////////////////////////////////////////////
// The enclosed code is from ladspa.cpp 
std::string simplify(const std::string& src)
{
    int		i=0;
    int		level=2;
    std::string	dst;

    while (src[i] ) {

        switch (level) {

        case 0 :
        case 1 :
        case 2 :
            // Skip the begin of the label "--foo-"
            // until 3 '-' have been read
            if (src[i]=='-') { level++; }
            break;

        case 3 :
            // copy the content, but skip non alphnum
            // and content in parenthesis
            switch (src[i]) {
            case '(' :
            case '[' :
                level++;
                break;

            case '-' :
                dst += '-';
                break;

            default :
                if (isalnum(src[i])) {
                    dst+= tolower(src[i]);
                }

            }
            break;

        default :
            // here we are inside parenthesis and
            // we skip the content until we are back to
            // level 3
            switch (src[i]) {

            case '(' :
            case '[' :
                level++;
                break;

            case ')' :
            case ']' :
                level--;
                break;

            default :
                break;
            }
        }
        i++;
    }
    return (dst.size() > 0) ? dst :src;
}
// END code from ladspa.cpp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single voice; use multiple for polyphony
////////////////////////////////////////////////////////////////////////////////
class Voice : public UI
{
public:
    Voice(int sampleRate);
    ~Voice();

    // UI methods:
    // TODO don't hardcode these so hard maybe
    void setFreq(float val);
    void setGate(float val);
    void setGain(float val);

    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

    virtual void addNumDisplay(const char* label, float* zone, int precision);
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max);
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

    virtual void openFrameBox(const char* label);
    virtual void openTabBox(const char* label);
    virtual void openHorizontalBox(const char* label);
    virtual void openVerticalBox(const char* label);
    virtual void closeBox();

    virtual void show();
    virtual void run();

    // Internal control (to Faust DSP)
    std::vector<float*> m_controls;

    // TODO maybe don't make this public eventually
    mydsp* m_mydsp;

private:
    // Helpers for UI building:
    // TODO organize this a bit better later...
    bool ckAnyMatch(const char* label, const char* indexName, float **zone, float* newZone);
    bool ckAllMatches(const char* label, float* zone);
    void addZone(float* zone);

    int m_samplerate;

    float* m_freq_zone;
    float* m_gate_zone;
    float* m_gain_zone;
};

////////////////////////////////////////////////////////////////////////////////
// Plugin class to handle DSSI methods:
////////////////////////////////////////////////////////////////////////////////
class Plugin : public UI
{
public:
    // LADSPA methods:
    static LADSPA_Handle instantiate(const LADSPA_Descriptor *, unsigned long);
    static void connectPort(LADSPA_Handle, unsigned long, LADSPA_Data *);
    static void activate(LADSPA_Handle);
    static void run(LADSPA_Handle, unsigned long);
    static void cleanup(LADSPA_Handle);

    // DSSI methods:
    static const DSSI_Program_Descriptor* getProgram(LADSPA_Handle, unsigned long);
    static void selectProgram(LADSPA_Handle, unsigned long, unsigned long);
    static int getMidiController(LADSPA_Handle, unsigned long);
    static void runSynth(LADSPA_Handle, unsigned long, snd_seq_event_t *, unsigned long);

    // UI methods:
    // TODO don't hardcode these so hard maybe
    void setFreq(float val, int voice = 0);
    void setGate(float val, int voice = 0);
    void setGain(float val, int voice = 0);

    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

    virtual void addNumDisplay(const char* label, float* zone, int precision);
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max);
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

    virtual void openFrameBox(const char* label);
    virtual void openTabBox(const char* label);
    virtual void openHorizontalBox(const char* label);
    virtual void openVerticalBox(const char* label);
    virtual void closeBox();

    virtual void show();
    virtual void run();

private:
    Plugin(int sampleRate);
    ~Plugin();

    // Helper methods:
    void updateControlZones();
    void runImpl(unsigned long, snd_seq_event_t *, unsigned long);
    void addSamples(size_t);

    // Helpers for UI building:
    // TODO organize this a bit better later...
    bool ckAnyMatch(const char* label, const char* indexName);
    bool ckAllMatches(const char* label);
    void add_control_with_default(float default_value);

    int m_samplerate;

    // Voice allocation memebers (TODO maybe break voice allocator into separate class later)
    // Note each voice is playing
    std::vector<int> voice_notes;
    // Queue of free voices
    std::list<size_t> voice_free;

    // Voices for polyphony
    std::vector<Voice*> m_voices;

    // Top-level inputs (from DSSI host)
    std::vector<float*> m_inputs;
    // Top-level outputs (to DSSI host)
    std::vector<float*> m_outputs;
    // Temp vector for collecting outputs TODO this is an ugly way to do it...
    std::vector<std::vector<float> > m_temp_outputs;
    // External control (from DSSI host)
    std::vector<float*> m_controls;

    // Control default values
    std::vector<float> m_control_defaults;
};

////////////////////////////////////////////////////////////////////////////////
// UI class to build descriptor, analogous to ladspa.cpp's portCollector
////////////////////////////////////////////////////////////////////////////////
const int ICONTROL = LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;
const int OCONTROL = LADSPA_PORT_OUTPUT|LADSPA_PORT_CONTROL;

class DescriptorUI : public UI
{
public:
    DescriptorUI(int ins, int outs);

    virtual void addButton(const char* label, float* zone) {
        if (!ckAnyMatch(label, "gate"))
        {
            addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
        }
    }
    virtual void addToggleButton(const char* label, float* zone) {
        addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
    }
    virtual void addCheckButton(const char* label, float* zone) {
        addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
    }
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {
        if (!ckAllMatches(label))
        {
            addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
        }
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {
        if (!ckAllMatches(label))
        {
            addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
        }
    }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {
        if (!ckAllMatches(label))
        {
            addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
        }
    }
    virtual void addNumDisplay(const char* label, float* zone, int precision) {
        addPortDescr(OCONTROL, label, 0, -10000, +10000);
    }
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
        addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
    }
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
        addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
    }
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
        addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
    }

    virtual void openFrameBox(const char* label) { openAnyBox(label); }
    virtual void openTabBox(const char* label) { openAnyBox(label); }
    virtual void openHorizontalBox(const char* label) { openAnyBox(label); }
    virtual void openVerticalBox(const char* label) { openAnyBox(label); }

    virtual void closeBox() { fPrefix.pop(); }

    virtual void show() {}
    virtual void run() {}

private:
    std::stack<std::string> fPrefix;

    void addPortDescr(int type, const char* label, int hint, float min=0.0, float max=0.0);

    void openAnyBox(const char* label);

    bool ckAnyMatch(const char* label, const char* indexName)
        {
            // TODO do case-insensitive here...
            if (strcmp(label,indexName)==0)
            {
                // Don't set values in the DescriptorUI
                // TODO consolidate this later
                return true;
            }
            return false;
        }
    bool ckAllMatches(const char* label)
        {
            bool result = false;
            result = result || ckAnyMatch(label,"gain");
            result = result || ckAnyMatch(label,"gate");
            result = result || ckAnyMatch(label,"freq");
            return result;
        }
};

////////////////////////////////////////////////////////////////////////////////
// DescriptorUI methods
////////////////////////////////////////////////////////////////////////////////
DescriptorUI::DescriptorUI(int ins, int outs)
{
    // Note inputs and outputs
    for (int i = 0; i < ins; i++)
    {
        g_port_descriptors.push_back(LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO);
        LADSPA_PortRangeHint temp;
        temp.HintDescriptor = 0;
        temp.LowerBound = 0;
        temp.UpperBound = 0;
        g_port_range_hints.push_back(temp);
        g_port_names.push_back(inames[i]);
    }
    for (int j = 0; j < outs; j++)
    {
        g_port_descriptors.push_back(LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO);
        LADSPA_PortRangeHint temp;
        temp.HintDescriptor = 0;
        temp.LowerBound = 0;
        temp.UpperBound = 0;
        g_port_range_hints.push_back(temp);
        g_port_names.push_back(onames[j]);
    }
}

void DescriptorUI::addPortDescr(int type, const char* label, int hint, float min, float max)
{
////////////////////////////////////////////////////////////////////////////////
// The enclosed code is derived from ladspa.cpp 
    std::string fullname = simplify(fPrefix.top() + "-" + label);
    // TODO for debugging, I'm just using the label for now instead of the full name (since fullname can get long)
//    char * str = strdup(fullname.c_str());
    char * str = strdup(label);
// END code from ladspa.cpp
////////////////////////////////////////////////////////////////////////////////

    g_port_descriptors.push_back(type);
    LADSPA_PortRangeHint temp;
    temp.HintDescriptor = hint;
    temp.LowerBound = min;
    temp.UpperBound = max;
    g_port_range_hints.push_back(temp);
    g_port_names.push_back(str); // TODO memory leak; need to free
}

void DescriptorUI::openAnyBox(const char* label)
{
////////////////////////////////////////////////////////////////////////////////
// The enclosed code is from ladspa.cpp 
    if (fPrefix.size() == 0)
    {
        // top level label is used as plugin name
        g_name = label;
        fPrefix.push(label);
    }
    else
    {
        std::string s;
        if (label && label[0])
        {
            s = fPrefix.top() + "-" + label;
        }
        else
        {
            s = fPrefix.top();
        }
        fPrefix.push(s);
    }
// END code from ladspa.cpp
////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
// Plugin methods
////////////////////////////////////////////////////////////////////////////////
Plugin::Plugin(int sampleRate) :
    m_samplerate(sampleRate)
{
    int i;

    mydsp temp_mydsp;

    for (i = 0; i < MAX_POLYPHONY; i++)
    {
        m_voices.push_back(new Voice(m_samplerate));

        // Voice parameters:
        voice_free.push_back(i);
        // TODO using -1 to represent nothing; think of a more clear way to do this
        voice_notes.push_back(-1);
    }
    for (i = 0; i < temp_mydsp.getNumInputs(); i++)
    {
        m_inputs.push_back(0);
    }
    for (i = 0; i < temp_mydsp.getNumOutputs(); i++)
    {
        m_outputs.push_back(0);
        std::vector<float> temp;
        temp.push_back(0.0);
        m_temp_outputs.push_back(temp);
    }
}

Plugin::~Plugin()
{
    size_t i;
    for (i = 0; i < m_voices.size(); i++)
    {
        delete m_voices[i];
    }
}

LADSPA_Handle Plugin::instantiate(const LADSPA_Descriptor *, unsigned long rate)
{
    Plugin *plugin = new Plugin(rate);
    size_t i;

    mydsp* temp_mydsp = new mydsp();
    temp_mydsp->buildUserInterface(plugin);
    delete temp_mydsp;

    for (i = 0; i < plugin->m_voices.size(); i++)
    {
        plugin->m_voices[i]->m_mydsp->buildUserInterface(plugin->m_voices[i]);
    }
    return plugin;
}

void Plugin::connectPort(LADSPA_Handle handle, unsigned long port, LADSPA_Data *location)
{
    Plugin *plugin = (Plugin *)handle;

    // Map inputs, then outputs, then controls:
    if (port < plugin->m_inputs.size())
    {
        *(&plugin->m_inputs[port]) = (float *)location;
    }
    else if (port < plugin->m_inputs.size() + plugin->m_outputs.size())
    {
        *(&plugin->m_outputs[port - plugin->m_inputs.size()]) = (float *)location;
    }
    else
    {
        plugin->m_controls[port - plugin->m_inputs.size() - plugin->m_outputs.size()] = (float *)location;
    }
}

void Plugin::activate(LADSPA_Handle handle)
{
    Plugin *plugin = (Plugin *)handle;
    for (size_t i = 0; i < plugin->m_voices.size(); i++)
    {
        plugin->m_voices[i]->m_mydsp->init(plugin->m_samplerate);
    }
}

void Plugin::run(LADSPA_Handle handle, unsigned long samples)
{
    runSynth(handle, samples, 0, 0);
}

void Plugin::cleanup(LADSPA_Handle handle)
{
    delete (Plugin *)handle;
}

const DSSI_Program_Descriptor* Plugin::getProgram(LADSPA_Handle handle, unsigned long index)
{
    if (index == 0)
    {
        return &g_program_descriptor;
    }
    else
    {
        return NULL;
    }
}

void Plugin::selectProgram(LADSPA_Handle handle, unsigned long bank, unsigned long program)
{
    Plugin *plugin = (Plugin *)handle;
    for (size_t i = 0; i < plugin->m_controls.size(); i++)
    {
        *(plugin->m_controls[i]) = plugin->m_control_defaults[i];
    }
}

int Plugin::getMidiController(LADSPA_Handle, unsigned long port)
{
    // TODO this is where we need to map MIDI controllers to ports
    return DSSI_NONE;
}

void Plugin::updateControlZones()
{
    for (size_t i = 0; i < m_controls.size(); i++)
    {
        for (size_t j = 0; j < m_voices.size(); j++)
        {
            *(m_voices[j]->m_controls[i]) = *(m_controls[i]);
        }
    }
}

void Plugin::runSynth(LADSPA_Handle handle, unsigned long samples, snd_seq_event_t *events, unsigned long eventCount)
{
    Plugin *plugin = (Plugin *)handle;
    plugin->updateControlZones();
    plugin->runImpl(samples, events, eventCount);
}

void Plugin::runImpl(unsigned long sampleCount, snd_seq_event_t *events, unsigned long eventCount)
{
    unsigned long pos;
    unsigned long count;
    unsigned long eventPos;
    snd_seq_ev_note_t n;

    size_t voice_index;

    pos = 0;
    eventPos = 0;
    while (pos < sampleCount)
    {
	while ((eventPos < eventCount) &&
	       (pos >= events[eventPos].time.tick))
        {
            switch (events[eventPos].type)
            {
	    case SND_SEQ_EVENT_NOTEON:
		n = events[eventPos].data.note;
		if (n.velocity > 0)
                {
                    // Look for the next free voice:
                    if (!voice_free.empty())
                    {
                        // Get the index of the first free string and remove it from the list
                        voice_index = voice_free.front();
                        voice_free.pop_front();

                        // Play the note on that voice
                        voice_notes[voice_index] = n.note;
                        float freq = 440.0f * powf(2.0f,(((float)n.note)-69.0f)/12.0f);
                        float gain = n.velocity/127.0f;
                        setFreq(freq, voice_index); // Hz - requires Faust control-signal "freq"
                        setGain(gain, voice_index); // 0-1 - requires Faust control-signal "gain"
                        setGate(1.0f, voice_index); // 0 or 1 - requires Faust button-signal "gate"
                    }
		}
		break;
	    case SND_SEQ_EVENT_NOTEOFF:
                for (voice_index = 0; voice_index < voice_notes.size(); voice_index++)
                {
                    if (voice_notes[voice_index] == events[eventPos].data.note.note)
                    {
                        setGate(0, voice_index);
                        // TODO using -1 to represent nothing; think of a more clear way to do this
                        voice_notes[voice_index] = -1;
                        voice_free.push_back(voice_index);
                    }
                }
		break;
	    default:
		break;
	    }
	    ++eventPos;
	}

	if ((eventPos < eventCount) && (events[eventPos].time.tick < sampleCount))
        {
	    count = events[eventPos].time.tick - pos;
	}
        else
        {
            count = sampleCount - pos;
        }

        addSamples(count);
	pos += count;
    }
}

void Plugin::addSamples(size_t samples)
{
    size_t i;
    size_t j;
    size_t v;

    // TODO this isn't very efficient right now...

    // Grow temp buffers to appropriate size / zero them:
    for (i = 0; i < m_temp_outputs.size(); i++)
    {
        for (j = 0; j < samples; j++)
        {
            if (m_temp_outputs[i].size() < (j+1))
            {
                m_temp_outputs[i].push_back(0.0);
            }
            else
            {
                m_temp_outputs[i][j] = 0.0;
            }
        }
    }

    AVOIDDENORMALS;

    // Add all voices together
    for (v = 0; v < m_voices.size(); v++)
    {
        m_voices[v]->m_mydsp->compute(samples, &m_inputs[0], &m_outputs[0]);

        // Accumulate in temp buffer
        for (i = 0; i < m_outputs.size(); i++)
        {
            for (j = 0; j < samples; j++)
            {
                m_temp_outputs[i][j] += m_outputs[i][j];
            }
        }
    }

    // Transfer accumulator to actual outputs
    for (i = 0; i < m_outputs.size(); i++)
    {
        for (j = 0; j < samples; j++)
        {
            // TODO find a better way to protect against clipping.
            m_outputs[i][j] = m_temp_outputs[i][j] / (float)MAX_POLYPHONY;
        }
    }
}

void Plugin::setFreq(float val, int voice)
{
    m_voices[voice]->setFreq(val);
}

void Plugin::setGate(float val, int voice)
{
    m_voices[voice]->setGate(val);
}

void Plugin::setGain(float val, int voice)
{
    m_voices[voice]->setGain(val);
}

void Plugin::addButton(const char* label, float* zone)
{
    if (!ckAnyMatch(label, "gate"))
    {
        add_control_with_default(0);
    }
}

void Plugin::addToggleButton(const char* label, float* zone)
{
    add_control_with_default(0);
}

void Plugin::addCheckButton(const char* label, float* zone)
{
    add_control_with_default(0);
}

void Plugin::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label))
    {
        add_control_with_default(init);
    }
}
void Plugin::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label))
    {
        add_control_with_default(init);
    }
}
void Plugin::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label))
    {
        add_control_with_default(init);
    }
}

void Plugin::addNumDisplay(const char* label, float* zone, int precision)
{
    add_control_with_default(0);
}
void Plugin::addTextDisplay(const char* label, float* zone, char* names[], float min, float max)
{
    add_control_with_default(0);
}
void Plugin::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{
    add_control_with_default(min);
}
void Plugin::addVerticalBargraph(const char* label, float* zone, float min, float max)
{
    add_control_with_default(min);
}

void Plugin::openFrameBox(const char* label)
{
}
void Plugin::openTabBox(const char* label)
{
}
void Plugin::openHorizontalBox(const char* label)
{
}
void Plugin::openVerticalBox(const char* label)
{
}
void Plugin::closeBox()
{
}

void Plugin::show()
{
}
void Plugin::run()
{
}

bool Plugin::ckAnyMatch(const char* label, const char* indexName)
{
    // TODO do case-insensitive here...
    if (strcmp(label,indexName)==0)
    {
        return true;
    }
    return false;
}
bool Plugin::ckAllMatches(const char* label)
{
    bool result = false;
    result = result || ckAnyMatch(label,"gain");
    result = result || ckAnyMatch(label,"gate");
    result = result || ckAnyMatch(label,"freq");
    return result;
}
void Plugin::add_control_with_default(float default_value)
{
    // TODO may need to consider different things for input and output controls...
    m_controls.push_back(0);
    m_control_defaults.push_back(default_value);
}


////////////////////////////////////////////////////////////////////////////////
// Voice methods
////////////////////////////////////////////////////////////////////////////////
Voice::Voice(int sampleRate) :
    m_samplerate(sampleRate),
    m_freq_zone(0),
    m_gate_zone(0),
    m_gain_zone(0)
{
    m_mydsp = new mydsp();
}

Voice::~Voice()
{
    delete m_mydsp;
}

void Voice::setFreq(float val)
{
    if (m_freq_zone)
    {
        *m_freq_zone = val;
    }
}

void Voice::setGate(float val)
{
    if (m_gate_zone)
    {
        *m_gate_zone = val;
    }
}

void Voice::setGain(float val)
{
    if (m_gain_zone)
    {
        *m_gain_zone = val;
    }
}

void Voice::addButton(const char* label, float* zone)
{
    if (!ckAnyMatch(label, "gate", &m_gate_zone, zone))
    {
        addZone(zone);
    }
}

void Voice::addToggleButton(const char* label, float* zone)
{
    addZone(zone);
}

void Voice::addCheckButton(const char* label, float* zone)
{
    addZone(zone);
}

void Voice::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label, zone))
    {
        addZone(zone);
    }
}
void Voice::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label, zone))
    {
        addZone(zone);
    }
}
void Voice::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
    if (!ckAllMatches(label, zone))
    {
        addZone(zone);
    }
}

void Voice::addNumDisplay(const char* label, float* zone, int precision)
{
    addZone(zone);
}
void Voice::addTextDisplay(const char* label, float* zone, char* names[], float min, float max)
{
    addZone(zone);
}
void Voice::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{
    addZone(zone);
}
void Voice::addVerticalBargraph(const char* label, float* zone, float min, float max)
{
    addZone(zone);
}

void Voice::openFrameBox(const char* label)
{
}
void Voice::openTabBox(const char* label)
{
}
void Voice::openHorizontalBox(const char* label)
{
}
void Voice::openVerticalBox(const char* label)
{
}
void Voice::closeBox()
{
}

void Voice::show()
{
}
void Voice::run()
{
}

bool Voice::ckAnyMatch(const char* label, const char* indexName, float **zone, float* newZone)
{
    // TODO do case-insensitive here...
    if (strcmp(label,indexName)==0)
    {
        *zone = newZone;
        return true;
    }
    return false;
}
bool Voice::ckAllMatches(const char* label, float* zone)
{
    bool result = false;
    result = result || ckAnyMatch(label,"gain", &m_gain_zone, zone);
    result = result || ckAnyMatch(label,"gate", &m_gate_zone, zone);
    result = result || ckAnyMatch(label,"freq", &m_freq_zone, zone);
    return result;
}
void Voice::addZone(float* zone)
{
    m_controls.push_back(zone);
}


////////////////////////////////////////////////////////////////////////////////
// Shared object hooks
////////////////////////////////////////////////////////////////////////////////
extern "C"
{

#ifdef __GNUC__
    __attribute__((constructor)) void init(void)
#else
    void _init(void)
#endif
    {
        AVOIDDENORMALS;

        if (g_dssi_descriptor == 0)
        {
            g_ladspa_descriptor = new LADSPA_Descriptor();
            g_dssi_descriptor = new DSSI_Descriptor();

            mydsp* temp_mydsp = new mydsp();
            DescriptorUI* temp_descriptor_ui = new DescriptorUI(temp_mydsp->getNumInputs(), temp_mydsp->getNumOutputs());
            temp_mydsp->buildUserInterface(temp_descriptor_ui);

            // Fill the descriptors:
            // TODO figure out strdup with const strings
            g_ladspa_descriptor->UniqueID = 0;
            g_ladspa_descriptor->Label = get_metadata_if_exists("name", g_name);
            g_ladspa_descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
            g_ladspa_descriptor->Name = get_metadata_if_exists("name", g_name);
            g_ladspa_descriptor->Maker = get_metadata_if_exists("author", "Maker");
            g_ladspa_descriptor->Copyright = get_metadata_if_exists("copyright", "Copyright");
            g_ladspa_descriptor->PortCount = g_port_descriptors.size();
            g_ladspa_descriptor->PortDescriptors = &g_port_descriptors[0];
            g_ladspa_descriptor->PortNames = &g_port_names[0];
            g_ladspa_descriptor->PortRangeHints = &g_port_range_hints[0];
            g_ladspa_descriptor->ImplementationData = 0;
            g_ladspa_descriptor->instantiate = Plugin::instantiate;
            g_ladspa_descriptor->connect_port = Plugin::connectPort;
            g_ladspa_descriptor->activate = Plugin::activate;
            g_ladspa_descriptor->run = Plugin::run;
            g_ladspa_descriptor->run_adding = 0;
            g_ladspa_descriptor->set_run_adding_gain = 0;
            g_ladspa_descriptor->deactivate = 0;
            g_ladspa_descriptor->cleanup = Plugin::cleanup;

            g_dssi_descriptor->DSSI_API_Version = 1;
            g_dssi_descriptor->LADSPA_Plugin = g_ladspa_descriptor;
            g_dssi_descriptor->configure = 0;
            g_dssi_descriptor->get_program = Plugin::getProgram;
            g_dssi_descriptor->select_program = Plugin::selectProgram;
            g_dssi_descriptor->get_midi_controller_for_port = Plugin::getMidiController;
            g_dssi_descriptor->run_synth = Plugin::runSynth;
            g_dssi_descriptor->run_synth_adding = 0;
            g_dssi_descriptor->run_multiple_synths = 0;
            g_dssi_descriptor->run_multiple_synths_adding = 0;

            // Program description (TODO if we eventually support multiple programs we will need to handle this differently)
            g_program_descriptor.Bank = 0;
            g_program_descriptor.Program = 0;
            g_program_descriptor.Name = get_metadata_if_exists("name", g_name);

            delete temp_mydsp;
            delete temp_descriptor_ui;
        }
    }

#ifdef __GNUC__
    __attribute__((destructor)) void fini(void)
#else
    void _fini()
#endif
    {
        if (g_ladspa_descriptor)
        {
            delete g_ladspa_descriptor;
        }
        if (g_dssi_descriptor)
        {
            delete g_dssi_descriptor;
        }
    }

    const LADSPA_Descriptor *ladspa_descriptor(unsigned long index)
    {
        return 0;
    }

    const DSSI_Descriptor *dssi_descriptor(unsigned long index)
    {
        if (index == 0)
        {
            return g_dssi_descriptor;
        }
        else
        {
            return NULL;
        }
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
