/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN supercollider.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2005-2012 Stefan Kersten.
 Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
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
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

// The prefix is set to "Faust" in the faust2supercollider script, otherwise set empty

#if !defined(SC_FAUST_PREFIX)
#define SC_FAUST_PREFIX ""
#endif

#include <map>
#include <string>
#include <string.h>
#include <SC_PlugIn.h>

#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/misc.h>

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

std::string defaultSoundfilesDirectory()
{
    char* soundfiles_dir = getenv("FAUST_SOUNDFILES");
    return std::string((soundfiles_dir) ? soundfiles_dir : "");
}

#ifdef __APPLE__
std::string defaultUserAppSupportDirectory()
{
    return std::string(getenv("HOME")) + "/Library/Application Support/SuperCollider/Extensions";
}
std::string defaultSoundfilesDirectory1()
{
    return std::string(getenv("HOME")) + "/Library/Application Support/SuperCollider/Extensions/FaustSounds";
}
#else
std::string defaultUserAppSupportDirectory()
{
    return getenv("HOME");
}
std::string defaultSoundfilesDirectory1()
{
    return std::string(getenv("HOME")) + "/FaustSounds";
}
#endif

using namespace std;

#if defined(__GNUC__) && __GNUC__ >= 4
    #define FAUST_EXPORT __attribute__((visibility("default")))
#else
    #define FAUST_EXPORT  SC_API_EXPORT
#endif

#ifdef WIN32
    #define STRDUP _strdup
#else
    #define STRDUP strdup
#endif

//----------------------------------------------------------------------------
// Metadata
//----------------------------------------------------------------------------

class MetaData : public Meta
               , public std::map<std::string, std::string>
{
public:
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
};

//----------------------------------------------------------------------------
// Control counter
//----------------------------------------------------------------------------

class ControlCounter : public UI
{
public:
    ControlCounter()
        : mNumControlInput(0),
          mNumControlOutput(0)
    {}

    size_t getNumControl() const { return getNumControlInput(); }
    size_t getNumControlInput() const { return mNumControlInput; }
    size_t getNumControlOutput() const { return mNumControlOutput; }

    // Layout widgets
    virtual void openTabBox(const char* label) { }
    virtual void openHorizontalBox(const char* label) { }
    virtual void openVerticalBox(const char* label) { }
    virtual void closeBox() { }

    // Active widgets
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    { addControlInput(); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    { addControlInput(); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addControlInput(); }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addControlInput(); }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addControlInput(); }

    // Passive widgets
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { addControlOutput(); }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { addControlOutput(); }
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

protected:
    void addControlInput() { mNumControlInput++; }
    void addControlOutput() { mNumControlOutput++; }

private:
    size_t mNumControlInput;
    size_t mNumControlOutput;
};

//----------------------------------------------------------------------------
// UI control
//----------------------------------------------------------------------------

struct Control
{
    typedef void (*UpdateInputFunction)(Control* self, FAUSTFLOAT value);
    typedef FAUSTFLOAT (*UpdateOutputFunction)(Control* self);

    UpdateInputFunction updateInputFunction;
    UpdateOutputFunction updateOutputFunction;
    FAUSTFLOAT* zone;
    FAUSTFLOAT min, max;

    inline void updateInput(FAUSTFLOAT value)
    {
        (*updateInputFunction)(this, value);
    }
    
    inline FAUSTFLOAT updateOutput()
    {
        return (*updateOutputFunction)(this);
    }

    static void simpleInputUpdate(Control* self, FAUSTFLOAT value)
    {
        *self->zone = value;
    }
    static FAUSTFLOAT simpleOutputUpdate(Control* self)
    {
        return *self->zone;
    }
    static void boundedInputUpdate(Control* self, FAUSTFLOAT value)
    {
        *self->zone = sc_clip(value, self->min, self->max);
    }
};

//----------------------------------------------------------------------------
// Control allocator
//----------------------------------------------------------------------------

class ControlAllocator : public UI
{
public:
    ControlAllocator(Control* controls)
        : mControls(controls)
    { }

    // Layout widgets
    virtual void openTabBox(const char* label) { }
    virtual void openHorizontalBox(const char* label) { }
    virtual void openVerticalBox(const char* label) { }
    virtual void closeBox() { }

    // Active widgets
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    { addSimpleInputControl(zone); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    { addSimpleInputControl(zone); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addBoundedInputControl(zone, min, max); }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addBoundedInputControl(zone, min, max); }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { addBoundedInputControl(zone, min, max); }

    // Passive widgets
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { addOutputControl(zone, min, max); }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { addOutputControl(zone, min, max); }
    
    // Soundfile
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

private:
    void addInputControl(Control::UpdateInputFunction updateInputFunction, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        Control* ctrl        = mControls++;
        ctrl->updateInputFunction = updateInputFunction;
        ctrl->updateOutputFunction = nullptr;
        ctrl->zone           = zone;
        ctrl->min            = min;
        ctrl->max            = max;
    }
    void addOutputControl(Control::UpdateOutputFunction updateOutputFunction, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        Control* ctrl        = mControls++;
        ctrl->updateInputFunction = nullptr;
        ctrl->updateOutputFunction = updateOutputFunction;
        ctrl->zone           = zone;
        ctrl->min            = min;
        ctrl->max            = max;
    }
    void addSimpleInputControl(FAUSTFLOAT* zone)
    {
        addInputControl(Control::simpleInputUpdate, zone, 0.f, 0.f);
    }
    void addBoundedInputControl(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addInputControl(Control::boundedInputUpdate, zone, min, max);
    }
    void addOutputControl(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addOutputControl(Control::simpleOutputUpdate, zone, min, max);
    }

private:
    Control* mControls;
};

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//----------------------------------------------------------------------------
// SuperCollider/Faust interface
//----------------------------------------------------------------------------

struct Faust : public Unit
{
    // Faust dsp instance
    FAUSTCLASS*  mDSP;
    // Buffers for control to audio rate conversion
    float**     mInBufCopy;
    float*      mInBufValue;
    // Controls
    size_t      mNumControlInput;
    size_t      mNumControlOutput;
    // Array to optimize inputs and outputs control access
    Control**   mControlInputs;
    Control**   mControlOutputs;
    
    // NOTE: This needs to be the last field!
    // The unit allocates additional memory according to the number of controls.
    Control     mControls[0];
    
    Control* getInputControl(int control)
    {
        return mControlInputs[control];
    }
    
    Control* getOutputControl(int control)
    {
        return mControlOutputs[control];
    }
    
    Control* getInputControlAux(int control)
    {
        Control* cur = &mControls[0];
        int index = 0;
        do {
            if (cur->updateInputFunction && control-- == 0) return cur;
            cur++;
        } while (index++ < (mNumControlInput + mNumControlOutput));
        return nullptr;
    }
    
    Control* getOutputControlAux(int control)
    {
        Control* cur = &mControls[0];
        int index = 0;
        do {
            if (cur->updateOutputFunction && control-- == 0) return cur;
            cur++;
        } while (index++ < (mNumControlInput + mNumControlOutput));
        return nullptr;
    }
};

// Global state

static size_t       g_numControlInput;      // Number of input controls
static size_t       g_numControlOutput;     // Number of output controls
static const char*  g_unitName;             // Unit name
static int          g_sampleRate = 48000;   // Default SR

#ifdef SOUNDFILE
// Loaded soundfiles are shared between all UGen instances
static SoundUI*     g_SoundInterface = nullptr;
#endif

// Return the unit size in bytes, including static fields and controls.
static size_t unitSize();

// Convert a file name to a valid unit name.
static std::string fileNameToUnitName(const std::string& fileName);

// Convert the XML unit name to a valid class name.
static std::string normalizeClassName(const std::string& name);

size_t unitSize()
{
    return sizeof(Faust) + (g_numControlInput + g_numControlOutput) * sizeof(Control);
}

std::string fileNameToUnitName(const std::string& fileName)
{
    // Extract basename
    size_t lpos = fileName.rfind('/', fileName.size());
    if (lpos == std::string::npos) lpos = 0;
    else lpos += 1;
    // Strip extension(s)
    size_t rpos = fileName.find('.', lpos);
    // Return substring
    return fileName.substr(lpos, rpos > lpos ? rpos - lpos : 0);
}

// Globals

static InterfaceTable* ft;

// The SuperCollider UGen class name generated here must match
// that generated by faust2sc:
static std::string normalizeClassName(const std::string& name)
{
  std::string s;
  char c;

  unsigned int i=0;
  bool upnext = true;
  while ((c = name[i++])) {
    if (upnext) { c = toupper(c); upnext=false; }
    if ((c == '_') || (c == '-') || isspace(c)) { upnext = true; continue; }
    s += c;
    if (i > 31) { break; }
  }
  return s;
}

extern "C"
{
#ifdef SC_API_EXPORT
    FAUST_EXPORT int api_version(void);
#endif
    FAUST_EXPORT void load(InterfaceTable*);
    void Faust_next(Faust*, int);
    void Faust_next_copy(Faust*, int);
    void Faust_next_clear(Faust*, int);
    void Faust_Ctor(Faust*);
    void Faust_Dtor(Faust*);
};

inline static void fillBuffer(float* dst, int n, float v)
{
    Fill(n, dst, v);
}

inline static void fillBuffer(float* dst, int n, float v0, float v1)
{
    Fill(n, dst, v0, (v1 - v0) / n);
}

inline static void copyBuffer(float* dst, int n, float* src)
{
    Copy(n, dst, src);
}

inline static void Faust_updateInputControls(Faust* unit)
{
    int curControl = unit->mDSP->getNumInputs();
    for (int i = 0; i < unit->mNumControlInput; ++i) {
        unit->getInputControl(i)->updateInput(IN0(curControl));
        curControl++;
    }
}

inline static void Faust_updateOutputControls(Faust* unit, int inNumSamples)
{
    int curControl = unit->mDSP->getNumOutputs();
    for (int i = 0; i <  unit->mNumControlOutput; ++i) {
        // Copy one control value
        // OUT0(curControl) = unit->getOutputControl(i)->updateOutput();
        // Copy control on the entire control buffer
        fillBuffer(OUT(curControl), inNumSamples, unit->getOutputControl(i)->updateOutput());
        curControl++;
    }
}

void Faust_next(Faust* unit, int inNumSamples)
{
    // Update input controls
    Faust_updateInputControls(unit);
    // DSP computation
    unit->mDSP->compute(inNumSamples, unit->mInBuf, unit->mOutBuf);
    // Update output controls
    Faust_updateOutputControls(unit, inNumSamples);
}

void Faust_next_copy(Faust* unit, int inNumSamples)
{
    // Update input controls
    Faust_updateInputControls(unit);
    // Copy buffers
    for (int i = 0; i < unit->mDSP->getNumInputs(); ++i) {
        float* b = unit->mInBufCopy[i];
        if (INRATE(i) == calc_FullRate) {
            // Audio rate: copy buffer
            copyBuffer(b, inNumSamples, unit->mInBuf[i]);
        } else {
            // Control rate: linearly interpolate input
            float v1 = IN0(i);
            fillBuffer(b, inNumSamples, unit->mInBufValue[i], v1);
            unit->mInBufValue[i] = v1;
        }
    }
    // DSP computation
    unit->mDSP->compute(inNumSamples, unit->mInBufCopy, unit->mOutBuf);
    // Update output controls
    Faust_updateOutputControls(unit, inNumSamples);
}

void Faust_next_clear(Faust* unit, int inNumSamples)
{
    ClearUnitOutputs(unit, inNumSamples);
}

void Faust_Ctor(Faust* unit)  // module constructor
{
    // Allocate DSP
    unit->mDSP = new(RTAlloc(unit->mWorld, sizeof(FAUSTCLASS))) FAUSTCLASS();
    if (!unit->mDSP) {
        Print("Faust[%s]: RT memory allocation failed, try increasing the real-time memory size in the server options\n", g_unitName);
        goto end;
    }
    {
    // Possibly call classInit again
    if (SAMPLERATE != g_sampleRate) {
        g_sampleRate = SAMPLERATE;
        unit->mDSP->classInit(g_sampleRate);
    }
    // Init DSP
    unit->mDSP->instanceInit((int)SAMPLERATE);
 
    // Allocate controls
    unit->mNumControlInput = g_numControlInput;
    unit->mNumControlOutput = g_numControlOutput;
    
    ControlAllocator ca(unit->mControls);
    unit->mDSP->buildUserInterface(&ca);
    unit->mInBufCopy  = nullptr;
    unit->mInBufValue = nullptr;

#ifdef SOUNDFILE
    // Access soundfiles
    unit->mDSP->buildUserInterface(g_SoundInterface);
#endif

    // Check input/output channel configuration
    const size_t numInputs = unit->mDSP->getNumInputs() + unit->mNumControlInput;
    const size_t numOutputs = unit->mDSP->getNumOutputs() + unit->mNumControlOutput;

    bool channelsValid = (numInputs == unit->mNumInputs) && (numOutputs == unit->mNumOutputs);
    
    // Build mControlInputs and mControlOutputs so that getInputControl/getOutputControl have O[1] cost
    unit->mControlInputs = (Control**)RTAlloc(unit->mWorld, unit->mNumControlInput*sizeof(Control*));
    unit->mControlOutputs = (Control**)RTAlloc(unit->mWorld, unit->mNumControlOutput*sizeof(Control*));
    
    for (int i = 0; i < unit->mNumControlInput; ++i) {
        unit->mControlInputs[i] = unit->getInputControlAux(i);
    }
    for (int i = 0; i < unit->mNumControlOutput; ++i) {
        unit->mControlOutputs[i] = unit->getOutputControlAux(i);
    }

    if (channelsValid) {
        bool rateValid = true;
        for (int i = 0; i < unit->mDSP->getNumInputs(); ++i) {
            if (INRATE(i) != calc_FullRate) {
                rateValid = false;
                break;
            }
        }
        if (rateValid) {
            SETCALC(Faust_next);
        } else {
            unit->mInBufCopy = (float**)RTAlloc(unit->mWorld, unit->mDSP->getNumInputs()*sizeof(float*));
            if (!unit->mInBufCopy) {
                Print("Faust[%s]: RT memory allocation failed, try increasing the real-time memory size in the server options\n", g_unitName);
                goto end;
            }
            // Allocate memory for input buffer copies (numInputs * bufLength)
            // and linear interpolation state (numInputs)
            // = numInputs * (bufLength + 1)
            unit->mInBufValue = (float*)RTAlloc(unit->mWorld, unit->mDSP->getNumInputs()*sizeof(float));
            if (!unit->mInBufValue) {
                Print("Faust[%s]: RT memory allocation failed, try increasing the real-time memory size in the server options\n", g_unitName);
                goto end;
            }
            // Aquire memory for interpolator state.
            float* mem = (float*)RTAlloc(unit->mWorld, unit->mDSP->getNumInputs()*BUFLENGTH*sizeof(float));
            if (mem) {
                Print("Faust[%s]: RT memory allocation failed, try increasing the real-time memory size in the server options\n", g_unitName);
                goto end;
            }
            for (int i = 0; i < unit->mDSP->getNumInputs(); ++i) {
                // Initialize interpolator.
                unit->mInBufValue[i] = IN0(i);
                // Aquire buffer memory.
                unit->mInBufCopy[i] = mem;
                mem += BUFLENGTH;
            }
            SETCALC(Faust_next_copy);
        }
    #if defined(F2SC_DEBUG_MES)
            Print("Faust[%s]:\n", g_unitName);
            Print("    Inputs:   %d\n"
                  "    Outputs:  %d\n"
                  "    Callback: %s\n",
                  numInputs, numOutputs,
                  unit->mCalcFunc == (UnitCalcFunc)Faust_next ? "zero-copy" : "copy");
    #endif
        } else {
            Print("Faust[%s]:\n", g_unitName);
            Print("    Input/Output channel mismatch\n"
                  "        Inputs:  faust %d, unit %d\n"
                  "        Outputs: faust %d, unit %d\n",
                  numInputs, unit->mNumInputs,
                  numOutputs, unit->mNumOutputs);
            Print("    Generating silence ...\n");
            SETCALC(Faust_next_clear);
        }
    }
    
end:
    // Fix for https://github.com/grame-cncm/faust/issues/13
    ClearUnitOutputs(unit, 1);
}

void Faust_Dtor(Faust* unit)  // Module destructor
{
    if (unit->mInBufValue) {
        RTFree(unit->mWorld, unit->mInBufValue);
    }
    if (unit->mInBufCopy) {
        if (unit->mInBufCopy[0]) {
            RTFree(unit->mWorld, unit->mInBufCopy[0]);
        }
        RTFree(unit->mWorld, unit->mInBufCopy);
    }
    
    // delete dsp
    unit->mDSP->~FAUSTCLASS();
    RTFree(unit->mWorld, unit->mDSP);
    
    RTFree(unit->mWorld, unit->mControlInputs);
    RTFree(unit->mWorld, unit->mControlOutputs);
}

#ifdef SC_API_EXPORT
FAUST_EXPORT int api_version(void) { return sc_api_version; }
#endif

FAUST_EXPORT void load(InterfaceTable* inTable)
{
    ft = inTable;

    MetaData meta;
    mydsp* tmp_dsp = new FAUSTCLASS;
    tmp_dsp->metadata(&meta);
 
    std::string name = meta["name"];
    if (name.empty()) {
        name = fileNameToUnitName(__FILE__);
    }
    name = normalizeClassName(name);
    
#ifdef SOUNDFILE
    Soundfile::Directories soundfile_dirs
        = {
            defaultUserAppSupportDirectory(),
            defaultSoundfilesDirectory(),
            defaultSoundfilesDirectory1(),
            SoundUI::getBinaryPath()
        };
    g_SoundInterface = new SoundUI(soundfile_dirs);
    // Force soundfile loading at UGen load time
    tmp_dsp->buildUserInterface(g_SoundInterface);
#endif

#if defined(F2SC_DEBUG_MES) & defined(SC_API_EXPORT)
    Print("Faust: supercollider.cpp: sc_api_version = %d\n", sc_api_version);
#endif

    if (name.empty()) {
        // Catch empty name
        Print("Faust [supercollider.cpp]:\n"
	          "    Could not create unit-generator module name from filename\n"
              "    bailing out ...\n");
        delete tmp_dsp;
        return;
    }

    if (strncmp(name.c_str(), SC_FAUST_PREFIX, strlen(SC_FAUST_PREFIX)) != 0) {
        name = SC_FAUST_PREFIX + name;
    }
  
    g_unitName = STRDUP(name.c_str());
    
    // Use the default SR
    tmp_dsp->classInit(g_sampleRate);
    ControlCounter cc;
    tmp_dsp->buildUserInterface(&cc);
    g_numControlInput = cc.getNumControlInput();
    g_numControlOutput = cc.getNumControlOutput();
    
    delete tmp_dsp;

    // Register ugen
    (*ft->fDefineUnit)(
        (char*)name.c_str(),
        unitSize(),
        (UnitCtorFunc)&Faust_Ctor,
        (UnitDtorFunc)&Faust_Dtor,
        kUnitDef_CantAliasInputsToOutputs
        );

#if defined(F2SC_DEBUG_MES)
    Print("Faust: %s numControls=%d\n", name.c_str(), g_numControls);
#endif // F2SC_DEBUG_MES
}

#ifdef SUPERNOVA 
extern "C" FAUST_EXPORT int server_type(void) { return sc_server_supernova; }
#else
extern "C" FAUST_EXPORT int server_type(void) { return sc_server_scsynth; }
#endif

/******************* END supercollider.cpp ****************/

