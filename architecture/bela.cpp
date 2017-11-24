#/************************************************************************

  IMPORTANT NOTE : this file contains two clearly delimited sections :
  the ARCHITECTURE section (in two parts) and the USER section. Each section
  is governed by its own copyright and license. Please check individually
  each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************

  Bela FAUST Architecture file
  Oli Larkin 2016
  www.olilarkin.co.uk
  Based on owl.cpp

  FAUST Architecture File
  Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

#ifndef __FaustBela_H__
#define __FaustBela_H__

#include <cstddef>
#include <string>
#include <math.h>
#include <strings.h>
#include <cstdlib>
#include <Bela.h>
#include <Utilities.h>

using namespace std;

#ifndef __FaustCommonInfrastructure__
#define __FaustCommonInfrastructure__

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/MidiUI.h"
#include "faust/midi/bela-midi.h"

const char* const pinNamesStrings[] =
{
  "ANALOG_0",
  "ANALOG_1",
  "ANALOG_2",
  "ANALOG_3",
  "ANALOG_4",
  "ANALOG_5",
  "ANALOG_6",
  "ANALOG_7",
  "ANALOG_8",
  "DIGITAL_0",
  "DIGITAL_1",
  "DIGITAL_2",
  "DIGITAL_3",
  "DIGITAL_4",
  "DIGITAL_5",
  "DIGITAL_6",
  "DIGITAL_7",
  "DIGITAL_8",
  "DIGITAL_9",
  "DIGITAL_10",
  "DIGITAL_11",
  "DIGITAL_12",
  "DIGITAL_13",
  "DIGITAL_14",
  "DIGITAL_15"
 };

enum EInputPin
{
  kNoPin = -1,
  kANALOG_0 = 0,
  kANALOG_1,
  kANALOG_2,
  kANALOG_3,
  kANALOG_4,
  kANALOG_5,
  kANALOG_6,
  kANALOG_7,
  kANALOG_8,
  kDIGITAL_0,
  kDIGITAL_1,
  kDIGITAL_2,
  kDIGITAL_3,
  kDIGITAL_4,
  kDIGITAL_5,
  kDIGITAL_6,
  kDIGITAL_7,
  kDIGITAL_8,
  kDIGITAL_9,
  kDIGITAL_10,
  kDIGITAL_11,
  kDIGITAL_12,
  kDIGITAL_13,
  kDIGITAL_14,
  kDIGITAL_15,
  kNumInputPins
 };

/**************************************************************************************

  BelaWidget : object used by BelaUI to ensures the connection between a Bela parameter
  and a Faust widget

***************************************************************************************/

class BelaWidget
{
protected:
  EInputPin fBelaPin;
  FAUSTFLOAT* fZone;  // Faust widget zone
  const char* fLabel; // Faust widget label
  FAUSTFLOAT fMin;         // Faust widget minimal value
  FAUSTFLOAT fRange;       // Faust widget value range (max-min)

  public:
  BelaWidget()
  : fBelaPin(kNoPin)
  , fZone(0)
  , fLabel("")
  , fMin(0)
  , fRange(1)
  {}

  BelaWidget(const BelaWidget& w)
  : fBelaPin(w.fBelaPin)
  , fZone(w.fZone)
  , fLabel(w.fLabel)
  , fMin(w.fMin)
  , fRange(w.fRange)
  {}

  BelaWidget(EInputPin pin, FAUSTFLOAT* z, const char* l, FAUSTFLOAT lo, FAUSTFLOAT hi)
  : fBelaPin(pin)
  , fZone(z)
  , fLabel(l)
  , fMin(lo)
  , fRange(hi-lo)
  {}

  void update(BelaContext *context)
  {
    switch(fBelaPin)
    {
      case kANALOG_0:
      case kANALOG_1:
      case kANALOG_2:
      case kANALOG_3:
      case kANALOG_4:
      case kANALOG_5:
      case kANALOG_6:
      case kANALOG_7:
        *fZone = fMin + fRange * analogRead(context, 0 /* TODO: average frame?*/, (int) fBelaPin);
        break;
      case kDIGITAL_0:
      case kDIGITAL_1:
      case kDIGITAL_2:
      case kDIGITAL_3:
      case kDIGITAL_4:
      case kDIGITAL_5:
      case kDIGITAL_6:
      case kDIGITAL_7:
      case kDIGITAL_8:
      case kDIGITAL_9:
      case kDIGITAL_10:
      case kDIGITAL_11:
      case kDIGITAL_12:
      case kDIGITAL_13:
      case kDIGITAL_14:
      case kDIGITAL_15:
        *fZone = digitalRead(context, 0 /* TODO: average frame?*/, ((int) fBelaPin - kDIGITAL_0)) > 0 ? fMin : fMin+fRange;
        break;
      default:
      break;
    };
  }

};

/**************************************************************************************

  BelaUI : Faust User Interface builder. Passed to buildUserInterface BelaUI allows
  the mapping between BELA pins and Faust widgets. It relies on specific
  metadata "...[BELA:DIGITAL_0]..." in the widget's label for that. For example any
  Faust widget with metadata [BELA:DIGITAL_0] will be controlled by DIGITAL_0
  (the second knob).

***************************************************************************************/

// The maximum number of mappings between Bela parameters and Faust widgets
#define MAXBELAWIDGETS 8

class BelaUI : public UI
{
  int fIndex;                           // number of BelaWidgets collected so far
  EInputPin fBelaPin;                   // current pin id
  BelaWidget fTable[MAXBELAWIDGETS];    // kind of static list of BelaWidgets

  // check if the widget is linked to a Bela parameter and, if so, add the corresponding BelaWidget
  void addBelaWidget(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
  {
    if (fBelaPin != kNoPin && (fIndex < MAXBELAWIDGETS))
    {
      fTable[fIndex] = BelaWidget(fBelaPin, zone, label, lo, hi);
      fIndex++;
    }
    fBelaPin = kNoPin;
  }

  // we dont want to create a widget but we clear fBelaPin just in case
  void skip() {
    fBelaPin = kNoPin;
  }

 public:

  BelaUI()
  : fIndex(0)
  , fBelaPin(kNoPin)
  {}

  virtual ~BelaUI() {}

  // should be called before compute() to update widget's zones registered as Bela parameters
  void update(BelaContext *context)
  {
    for (int i=0; i<fIndex; i++)
      fTable[i].update(context);
  }

  //---------------------- virtual methods called by buildUserInterface ----------------

  // -- widget's layouts
  virtual void openTabBox(const char* label) {}
  virtual void openHorizontalBox(const char* label) {}
  virtual void openVerticalBox(const char* label) {}
  virtual void closeBox() {}

  // -- active widgets
  virtual void addButton(const char* label, FAUSTFLOAT* zone) { skip(); }
  virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { skip(); }
  virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step) { addBelaWidget(label, zone, lo, hi); }
  virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step) { addBelaWidget(label, zone, lo, hi); }
  virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step) { addBelaWidget(label, zone, lo, hi); }

  // -- passive widgets
  virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi) { skip(); }
  virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi) { skip(); }
    
  // -- soundfiles
  virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

  // -- metadata declarations
  virtual void declare(FAUSTFLOAT* z, const char* k, const char* id) {
    if (strcasecmp(k,"BELA") == 0) {
      for(int i=0;i<kNumInputPins;i++) {
        if (strcasecmp(id, pinNamesStrings[i]) == 0) {
          fBelaPin = (EInputPin)i;
        }
      }
    }
  }
};

#endif // __FaustCommonInfrastructure__

/**************************BEGIN USER SECTION **************************/

<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/**************************************************************************************

  Bela render.cpp that calls FAUST generated code

***************************************************************************************/

unsigned int gNumBuffers = 0;   // the number of de-interleaved buffers for audio and analog i/o
FAUSTFLOAT *gInputBuffers = NULL, *gOutputBuffers = NULL; //de-interleaved input/output buffers for the audio and analog inputs
FAUSTFLOAT* gFaustIns[10];      // array of pointers to gInputBuffer data
FAUSTFLOAT* gFaustOuts[10];     // array of pointers to gOutputBuffers data
mydsp fDSP;
BelaUI fUI;
bela_midi fMIDI;
MidiUI* fMidiUI;

bool setup(BelaContext* context, void* userData)
{
  gNumBuffers = context->audioInChannels
                + context->audioOutChannels
                + context->analogInChannels
                + context->analogOutChannels;
//   rt_printf("context->audioFrames %i\n", context->audioFrames);
//   rt_printf("context->audioChannels %i\n", context->audioChannels);
//   rt_printf("context->analogChannels %i\n", context->analogChannels);
//   rt_printf("context->analogFrames %i\n", context->analogFrames);

  fDSP.init(context->audioSampleRate);
  fDSP.buildUserInterface(&fUI); // Maps Bela Analog/Digital IO and faust widgets

  gInputBuffers = (FAUSTFLOAT *) malloc(gNumBuffers * context->audioFrames * sizeof(FAUSTFLOAT));
  gOutputBuffers = (FAUSTFLOAT *) malloc(gNumBuffers * context->audioFrames * sizeof(FAUSTFLOAT));

  if(gInputBuffers == NULL || gOutputBuffers == NULL)
  {
    rt_printf("setup() failed: couldn't allocated buffers");
    return false;
  }

  if(fDSP.getNumInputs() > 10 || fDSP.getNumOutputs() > 10)
  {
    rt_printf("setup() failed: FAUST DSP has too many i/o");
    return false;
  }
  // create the table of input channels
  for(int ch=0; ch<fDSP.getNumInputs(); ++ch)
    gFaustIns[ch] = gInputBuffers + (ch * context->audioFrames);

  // create the table of output channels
  for(int ch=0; ch<fDSP.getNumOutputs(); ++ch)
    gFaustOuts[ch] = gOutputBuffers + (ch * context->audioFrames);

  fMidiUI = new MidiUI(&fMIDI);
  fDSP.buildUserInterface(fMidiUI);
  fMidiUI->run();

  return true;
}

void render(BelaContext* context, void* userData)
{
  // De-interleave the input data
  for(unsigned int frame = 0; frame < context->audioFrames; frame++)
  {
    for(unsigned int ch = 0; ch < gNumBuffers; ch++)
    {
      if(ch >= context->audioInChannels+context->analogInChannels)
        break;
      if(ch >= context->audioInChannels) // handle analogChannels
      {
        unsigned int m = frame/2;
        FAUSTFLOAT mIn = (FAUSTFLOAT) context->analogIn[m * context->analogInChannels + (ch-context->audioInChannels)];
        gInputBuffers[ch * context->audioFrames + frame] = mIn;
      }
      else // handle audioInChannels
      {
        gInputBuffers[ch * context->audioFrames + frame] = context->audioIn[frame * context->audioInChannels + ch];
      }
    }
  }

  // reads Bela pins and updates corresponding Faust Widgets zones
  fUI.update(context);
  // Process FAUST DSP
  fDSP.compute(context->audioFrames, gFaustIns, gFaustOuts);

  // Interleave the output data
  for(unsigned int frame = 0; frame < context->audioFrames; frame++)
  {
    for(unsigned int ch = 0; ch < gNumBuffers; ch++)
    {
      if(ch >= context->audioOutChannels+context->analogOutChannels)
        break;
      else
      {
        if(ch >= context->audioOutChannels) // handle analogChannels
        {
          unsigned int m = frame/2;
          context->analogOut[m * context->analogFrames + (ch-context->audioOutChannels)] = gOutputBuffers[ch*context->audioFrames + frame];
        }
        else // handle audioChannels
        {
          context->audioOut[frame * context->audioOutChannels + ch] = gOutputBuffers[ch * context->audioFrames + frame];
        }
      }
    }
  }
}

void cleanup(BelaContext* context, void* userData)
{
  if(gInputBuffers != NULL)
    free(gInputBuffers);
  if(gOutputBuffers != NULL)
    free(gOutputBuffers);

  delete fMidiUI;
}

#endif // __FaustBela_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
