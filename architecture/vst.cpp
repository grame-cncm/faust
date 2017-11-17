/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 ************************************************************************
    FAUST VSTi Architecture File
    Copyright (C) 2013 by Yan Michalevsy
    All rights reserved.
    ----------------------------BSD License------------------------------
    Redistribution and use in source and binary forms, with or without 
    modification, are permitted provided that the following conditions 
    are met:

    * Redistributions of source code must retain the above copyright 
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above 
      copyright notice, this list of conditions and the following 
      disclaimer in the documentation and/or other materials provided 
      with the distribution.
    * Neither the name of Julius Smith nor the names of its 
      contributors may be used to endorse or promote products derived 
      from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
    OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------VST SDK----------------------------------
    In order to compile a VST (TM) plugin with this architecture file 
    you will need the proprietary VST SDK from Steinberg. Please check 
    the corresponding license.

 ************************************************************************
 ************************************************************************/

/********************************************************************
 * vsti-poly.cpp - Polyphonic VSTi-2.4 wrapper for the FAUST language. 
 *
 * Usage: faust -a vst.cpp myfaustprog.dsp
 *
 * By Yan Michalevsky (http://www.stanford.edu/~yanm2/)
 * based on vsti-mono.cpp by
 * Julius Smith (http://ccrma.stanford.edu/~jos/), based on vst.cpp
 * by Remy Muller <remy.muller at ircam.fr>
 * (http://www.smartelectronix.com/~mdsp/).  Essentially, vst.cpp was
 * first edited to look more like the "again" programming sample that
 * comes with the VST-2.4 SDK from Steinberg. Next, features from the
 * "vstxsynth" program sample were added to give simple MIDI synth
 * support analogous to that of faust2pd, except that only one voice
 * is supported.  (If the Faust patch has any input signals, this
 * architecture file should reduce to vst2p4.cpp --- i.e., basic VST
 * plugin support.)  As with faust2pd, to obtain MIDI control via
 * NoteOn/Off, Velocity, and KeyNumber, there must be a button named
 * "gate" and sliders (or numeric entries) named "gain" and "freq" in
 * the Faust patch specified in myfaustprog.dsp.
 *
 * NOTES:
 *  Relies on automatically generated slider GUI for VST plugins.
 *   - Horizontal and vertical sliders mapped to "vstSlider"
 *   - Numeric Entries similarly converted to "vstSlider"
 *   - No support for bar graphs or additional numeric and text displays
 *   - Tested on the Muse Receptor Pro 1.0, System Version 1.6.20070717,
 *     using Visual C++ 2008 Express Edition 
 *     (part of the Microsoft Visual Studio 2008, Beta 2)
 *   - Reference: 
 * http://ccrma.stanford.edu/realsimple/faust/Generating_VST_Plugin_Faust.html
 *
 * Initial work on the polyphonic VSTi architecture was done as part
 * of Music 420B class in Stanford University and in summarized in
 * http://stanford.edu/~yanm2/files/mus420b.pdf
 *
 * FAUST 
 * Copyright (C) 2003-2007 GRAME, Centre National de Creation Musicale
 * http://www.grame.fr/			     
 *
 ********************************************************************/

// Suggestion: Faust could replace all leading comments in this file
// by the following shorter comment:

/********************************************************************
 * C++ source generated by the following command line:
 *
 *   faust -a vsti-poly.cpp name.dsp -o name-vsti.cpp
 *
 ********************************************************************/

// (where the filenames could be really right, and the path to vsti-poly.cpp
// could be included as well.)

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <assert.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

// #define DEBUG

#ifdef DEBUG
#define TRACE(x) x
#else
#define TRACE(x)
#endif

using namespace std ;

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

struct Meta : std::map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key] = value; }
		
		const char* get(const char* key, const char* defaultString)
        {
			if (this->find(key) != this->end()) {
				return (*this)[key];
			} else {
				return defaultString;
			}
		}
};

// abs is now predefined
//template<typename T> T abs (T a) { return (a<T(0)) ? -a : a; }

inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x) { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************
*
*							       VECTOR INTRINSICS
*
*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************
*
*								USER INTERFACE
*
*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************
*
*								FAUST DSP
*
*******************************************************************************
*****************************************************************************/

#include "faust/vst/vstui.h"
#include "faust/dsp/dsp.h"

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

#include "faust/vst/voice.h"

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
/*****************************************************************************
 *
 * VST wrapper
 * 
 ****************************************************************************/

#include "audioeffectx.h" 

///////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////

#define MAX_NOUTS (2)

//----------------------------------------------------------------------------
// Faust class prototype
//----------------------------------------------------------------------------
#include "faust/vst/faust.h"
/*--------------------------------------------------------------------------*/

//----------------------------------------------------------------------------
// Class Implementations 
//----------------------------------------------------------------------------

#define kNumPrograms (1)

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	TRACE( fprintf(stderr, "Faust VSTi: Creating VST instance\n") );
	
  // The dsp and its UI need to be allocated now because
  // AudioEffectX wants the no. parameters available as an instance argument:
	mydsp* dspi = new mydsp();
	vstUI* dspUIi = new vstUI();
  dspi->buildUserInterface(dspUIi);

  TRACE( fprintf(stderr,"=== Faust vsti: created\n") ); // look for this in the system log

  return new Faust(audioMaster, dspi, dspUIi);
}

//-----------------------------------------------------------------------------
// Faust
//-----------------------------------------------------------------------------
Faust::Faust(audioMasterCallback audioMaster, dsp* dspi, vstUI* dspUIi)
  : AudioEffectX(audioMaster, kNumPrograms, dspUIi->GetNumParams()),
		m_dsp(dspi), m_dspUI(dspUIi), 
		m_voices(MAX_POLYPHONY, (Voice*)NULL),
		m_playingVoices(),
		m_freeVoices(),
		m_prevVoice(-1),
		m_tempOutputs(NULL),
		m_tempOutputSize(INITIAL_TEMP_OUTPUT_SIZE),
		m_currentNotes(),
		m_currentVelocities(),
		m_currentDeltas()
{
#ifdef DEBUG
  fprintf(stderr,"=== Faust vsti: classInit:\n");
#endif

  mydsp::classInit((int)getSampleRate()); // Ask AudioEffect for sample-rate

  setProgram(0);
  setProgramName("Default");

  if (audioMaster) {
    setNumInputs(m_dsp->getNumInputs());
    setNumOutputs(m_dsp->getNumOutputs());		
    canProcessReplacing();
    if (m_dsp->getNumInputs() == 0) {
      isSynth(); // at least let's hope so!
      if (m_dsp->getNumOutputs() < 1) {
				fprintf(stderr,"*** faust: vsti: No signal inputs or outputs, "
						"and Faust has no MIDI outputs!\n");
			}
    }
    setUniqueID(m_dspUI->makeID());					
  }

	// Initialize all members related to polyphonic performance
	TRACE( fprintf(stderr, "Faust VSTi: Initializing voices and temporary output buffers\n") );
	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		m_voices[i] = new Voice((int)getSampleRate());
		m_freeVoices.push_back(i);
	}

	TRACE( fprintf(stderr, "Faust VSTi: Allocating %d temporary output "
								 "buffers\n", m_dsp->getNumOutputs()) );
	m_tempOutputs = (FAUSTFLOAT**) malloc(sizeof(FAUSTFLOAT*) * m_dsp->getNumOutputs());
	for (int i = 0; i < m_dsp->getNumOutputs(); ++i) {
		m_tempOutputs[i] = (FAUSTFLOAT*) malloc(sizeof(FAUSTFLOAT) * m_tempOutputSize);
	}

  initProcess();
  if (m_dsp->getNumInputs() == 0) {
    suspend(); //  Synths start out quiet
  }
} // end of Faust constructor

//----------------------------------------------------------------------------
Faust::~Faust()
{
	TRACE( fprintf(stderr, "Calling Faust VST destructor\n") );
	
	for (int i = 0; i < m_dsp->getNumOutputs(); ++i) {
		free(m_tempOutputs[i]);
		m_tempOutputs[i] = NULL;
	}

	free(m_tempOutputs);

	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		if (NULL != m_voices[i]) {
			delete m_voices[i];
			m_voices[i] = NULL;
		}
	}

  if (m_dspUI) {
		delete m_dspUI;
	}

  if (m_dsp) {
		delete m_dsp;
	}

} // end of Faust destructor

//-----------------------------------------------------------------------------
void Faust::setProgram (VstInt32 program)
// Override this method of AudioEffect in order to set 
// local instance variables corresponding to the current MIDI program.
// Here there is only one program.
{
  if (program < 0 || program >= kNumPrograms) {
		fprintf(stderr,
						"*** Faust vsti: setting program to %d is OUT OF RANGE\n",
						program);
    return;
  }  

#ifdef DEBUG
  fprintf(stderr,"=== Faust vsti: setting program to %d\n",program);
#endif

  curProgram = program; // curProgram defined in audioeffect.h
} // end of setProgram

//----------------------------------------------------------------------------
void Faust::setProgramName (const char* name)
{
  vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//----------------------------------------------------------------------------
void Faust::getProgramName(char *name)
{
  vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//----------------------------------------------------------------------------
void Faust::getParameterLabel(VstInt32 index, char *label)
{	
	const char* unit = "";
	if (index < numParams) {
		 unit = m_dspUI->getControlMetadata(index, "unit", "");
	}

	vst_strncpy (label, unit, kVstMaxParamStrLen); // parameter units in Name

	TRACE( fprintf(stderr, "Called getParameterLabel for parameter %d, returning %s\n",
								 index, label) );
} // end of getParameterLabel

//----------------------------------------------------------------------------
void Faust::getParameterDisplay(VstInt32 index, char *text)
{
  if(index < numParams) {
    m_dspUI->GetDisplay(index,text); // get displayed float value as text
	}
  else {
    vst_strncpy (text, "IndexOutOfRange", kVstMaxParamStrLen);
	}
}

//----------------------------------------------------------------------------
void Faust::getParameterName(VstInt32 index, char *label)
{
  if(index < numParams) {
    m_dspUI->GetName(index,label); // parameter name, including units
	} else {
    vst_strncpy (label, "IndexOutOfRange", kVstMaxParamStrLen);
	}
} // end of getParamterName

//--------------------

bool Faust::getParameterProperties(VstInt32 index, VstParameterProperties* properties)
{
	if (index < 0 || index >= m_dspUI->GetNumParams()) {
		TRACE( fprintf(stderr, "Faust VSTi: Invalid parameter index %d\n",
									 index) );
		return false;
	}

	TRACE( fprintf(stderr, "Faust VSTi: getParameterProperties called with index %d\n",
								 index) );

	if ( index == m_dspUI->gateIndex ) {
		properties->flags |= kVstParameterIsSwitch;
	}

	getParameterName(index, properties->label);
	
	// TODO: set parameter range
	const vstSlider* slider = dynamic_cast<const vstSlider*>(m_dspUI);
	if (NULL != slider) {
		// has min-max range
		properties->minInteger = slider->getMinValue();
		properties->maxInteger = slider->getMaxValue();
		properties->stepInteger = slider->getStep();
	}

	return true;
} // end of getParameterProperties

//----------------------------------------------------------------------------
void Faust::setParameter(VstInt32 index, float value)
{
	if (index >= numParams || index < 0) {
		TRACE( fprintf(stderr, "Faust VSTi: Invalid parameter index %d\n",
									 index) );
		return;
	}

  m_dspUI->SetValue(index, value);

	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		TRACE( fprintf(stderr, "Setting parameter %d for voice %d to value %f\n",
									 index, i, value) );
		m_voices[i]->SetValue(index, value);
	}
} // end of setParameter

//----------------------------------------------------------------------------
float Faust::getParameter(VstInt32 index)
{
	return (index >= 0 && index < numParams) ? m_dspUI->GetValue(index) : 0.0f;
}

//-----------------------------------------------------------------------------
bool Faust::getInputProperties (VstInt32 index, VstPinProperties* properties)
{
  if(index < 0 || index >= m_dsp->getNumInputs()) {
		return false;
	}

	sprintf (properties->label, "Grame Faust DSP input: %d",index);
	sprintf (properties->shortLabel, "In %d",index);
	properties->flags = kVstPinIsActive;
	if (m_dsp->getNumInputs() == 2) {
		properties->flags |= kVstPinIsStereo;
	}
	
	return true;
}

//-----------------------------------------------------------------------------
bool Faust::getOutputProperties (VstInt32 index, VstPinProperties* properties)
{
  if(index < 0 || m_dsp->getNumOutputs() < 1) {
		return false;
	}

	sprintf (properties->label, "Grame Faust DSP output: %d",index);
	sprintf (properties->shortLabel, "Out %d",index);
	properties->flags = kVstPinIsActive;
	if (m_dsp->getNumOutputs() == 2) {
		properties->flags |= kVstPinIsStereo;
	}
	return true;
}

//----------------------------------------------------------------------------
bool Faust::getProgramNameIndexed (VstInt32 category, VstInt32 index, 
																	 char* text)
{
  if (index < kNumPrograms) {
      vst_strncpy (text, programName, kVstMaxProgNameLen);
      return true;
  }
  return false;
}

const char* Faust::getMetadata(const char* key, const char* defaultString)
{
    Meta meta;
    mydsp tmp_dsp;
    tmp_dsp.metadata(&meta);
    return meta.get(key, defaultString);
} // end of getMetadata

//-----------------------------------------------------------------------------
bool Faust::getEffectName (char* name)
{
  const char* effectName = getMetadata("name", "Effect Name goes here");
  vst_strncpy (name, effectName, kVstMaxEffectNameLen);
  return true;
}

//-----------------------------------------------------------------------------
bool Faust::getVendorString (char* text)
{
  const char* vendorString = getMetadata("author", "Vendor String goes here");
  vst_strncpy (text, vendorString, kVstMaxVendorStrLen);
  return true;
}

//-----------------------------------------------------------------------------
bool Faust::getProductString (char* text)
{
  const char* productString = getMetadata("name", "Product String goes here");
  vst_strncpy (text, productString, kVstMaxProductStrLen);
  return true;
}

//-----------------------------------------------------------------------------
VstInt32 Faust::getVendorVersion ()
{ 
	const char* versionString = getMetadata("version", "0.0");
  return (VstInt32)atof(versionString);
}

//-----------------------------------------------------------------------------
VstInt32 Faust::canDo (const char* text)
{
  if (!strcmp (text, "receiveVstEvents")) {
    return 1;
	}
  
	if (!strcmp (text, "receiveVstMidiEvent")) {
    return 1;
	}

  if (!strcmp (text, "midiProgramNames")) {
    return 1;
	}

  return -1;	// explicitly can't do; 0 => don't know
} // end of canDo

//----------------------------------------------------------------------------
VstInt32 Faust::getNumMidiInputChannels ()
{
  return 1; // one MIDI-in channel
}

//----------------------------------------------------------------------------
VstInt32 Faust::getNumMidiOutputChannels ()
{
  return 0; // no MIDI-outs
}

//----------------------------------------------------------------------------
VstInt32 Faust::getMidiProgramName (VstInt32 channel, MidiProgramName* mpn)
{
  VstInt32 prg = mpn->thisProgramIndex;
  if (prg < 0 || prg > 0) return 0;
  fillProgram (channel, prg, mpn);
  return 1; // we have only 1 "MIDI program"
}

//------------------------------------------------------------------------
VstInt32 Faust::getCurrentMidiProgram (VstInt32 channel, MidiProgramName* mpn)
{
  // There is only one MIDI program here, so return it regardless of MIDI channel:
  if (channel < 0 || channel >= 16 || !mpn) return -1;
  VstInt32 prg = 0;
  mpn->thisProgramIndex = prg;
  fillProgram (channel, prg, mpn);
  return prg;
}

//------------------------------------------------------------------------
void Faust::fillProgram (VstInt32 channel, VstInt32 prg, MidiProgramName* mpn)
// Fill mpn struct for given channel.  Here there should be only one.
{
  mpn->midiBankMsb = mpn->midiBankLsb = -1;
  mpn->reserved = 0;
  mpn->flags = 0;
  vst_strncpy (mpn->name, programName, kVstMaxProgNameLen);
  mpn->midiProgram = (char)prg; // prg should only be 0
  mpn->parentCategoryIndex = -1;
}

//------------------------------------------------------------------------
VstInt32 Faust::getMidiProgramCategory (VstInt32 channel, MidiProgramCategory* cat)
// VST host wants to fill cat struct for given channel.  We have only one category.
{
  cat->parentCategoryIndex = -1;	// -1:no parent category
  cat->flags = 0;			// reserved, none defined yet, zero.
  VstInt32 category = cat->thisCategoryIndex;
  vst_strncpy (cat->name, "Faust Patch", kVstMaxProgNameLen);
  return 1; // one category
}

//***********************************************************************

//----------------------------------------------------------------------------
void Faust::setSampleRate(float sampleRate)
{
  AudioEffect::setSampleRate(sampleRate);
  m_dsp->init((int)getSampleRate()); // in case AudioEffect altered it

	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		m_voices[i]->m_dsp.init((int)getSampleRate());
	}
}

//----------------------------------------------------------------------------
void Faust::initProcess ()
{
  currentVelocity = currentNote = currentDelta = 0;
  m_dsp->init((int)getSampleRate());

	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		m_voices[i]->m_dsp.init((int)getSampleRate());
	}
}

//----------------------------------------------------------------------------
void Faust::processReplacing(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, VstInt32 sampleFrames)
{
    AVOIDDENORMALS;
#ifdef DEBUG
    // fprintf(stderr,"=== Faust vsti: processReplacing . . .\n");
#endif

  if (m_dsp->getNumInputs() > 0) {
		// We're an effect . . . keep going:
    m_dsp->compute(sampleFrames, inputs, outputs);
  }
	else { 
		// We're a synth . . . 
		synthProcessReplacing(inputs, outputs, sampleFrames);
	}
} // end of processReplacing

inline float midiToFreq(int note) {
	return 440.0f*powf(2.0f,(((float)note)-69.0f)/12.0f);
}

void Faust::synthProcessReplacing(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, 
																	VstInt32 sampleFrames)
{
	float* outptr[MAX_NOUTS] = {NULL,};
	int i;
	int nouts = m_dsp->getNumOutputs();

	if (nouts > MAX_NOUTS) {
		TRACE( fprintf(stderr, "VSTi: nouts > MAX_NOUTS. Number of outputs (%d) exceeds limit. "
									 "Truncated to maximum.\n", nouts) );
		nouts = MAX_NOUTS;
	}

	// we're synthesizing . . .
	if (m_currentNotes.size() > 0) {
		int previousDelta = 0;
		while (m_currentNotes.size() > 0) { // a new note
			currentDelta = m_currentDeltas.front();
			// but waiting out a timestamp delay . . .
			if (currentDelta >= sampleFrames) { 
				// start time is after this chunk
				for(std::list<VstInt32>::iterator it = m_currentDeltas.begin(); it != m_currentDeltas.end(); ++it) {
					*it -= sampleFrames;
				}
				compute(inputs, outputs, sampleFrames);
				return;
			}
			else {
				m_currentDeltas.pop_front();
				currentNote = m_currentNotes.front();
				m_currentNotes.pop_front();
				currentVelocity = m_currentVelocities.front();
				m_currentVelocities.pop_front();
				if (currentVelocity > 0) { // Note on
					// Reserve a free voice for the played 
					int currentVoice;
					if (m_freeVoices.size() > 0) {
						currentVoice = m_freeVoices.front();
						m_freeVoices.pop_front();
						struct voice_node *n = new voice_node;
						n->note = currentNote;
						n->voice = currentVoice;
						m_playingVoices.push_back(n);
					}
					else {
						voice_node *front = m_playingVoices.front();
						currentVoice = front->voice;
						float freq = midiToFreq(front->note);
						m_voices[currentVoice]->setPrevFreq(freq);
						front->note = currentNote;
						m_playingVoices.pop_front();
						m_playingVoices.push_back(front);
					}
					memset(outptr, 0, sizeof(outptr));
					// Before the note starts
					assert(nouts <= MAX_NOUTS);
					for (i = 0; i < nouts; i++) {
						outptr[i] = outputs[i] + previousDelta; // leaving caller's pointers alone
					}
					compute(inputs, outptr, currentDelta - previousDelta);
					// Note start
					float freq = midiToFreq(currentNote);
					m_voices[currentVoice]->setFreq(freq); // Hz - requires Faust control-signal "freq"
					float gain = currentVelocity/127.0f;
					m_voices[currentVoice]->setGain(gain); // 0-1 - requires Faust control-signal "gain"
					m_voices[currentVoice]->setGate(1.0f); // 0 or 1 - requires Faust control-signal "gate"
				}
				else { // Note off
					// Find the voice to be turned off
					int currentVoice;
					bool voiceFound = false;
					std::list<voice_node*>::iterator voice_iter = m_playingVoices.begin();
					for (; voice_iter != m_playingVoices.end(); voice_iter++) {
						if (currentNote == (*voice_iter)->note) {
							currentVoice = (*voice_iter)->voice;
							TRACE( fprintf(stderr, "=== Faust VSTi: Found matching voice for note %d: %d\n", currentNote, currentVoice) );
							if (std::find(m_releasedVoices.begin(), m_releasedVoices.end(), currentVoice) == m_releasedVoices.end()) {
								m_releasedVoices.push_back(currentVoice);
								voiceFound = true;
							}
						}
					}
					memset(outptr, 0, sizeof(outptr));
					// Before the note ends
					for (i = 0; i < nouts; i++) {
						outptr[i] = outputs[i] + previousDelta; // leaving caller's pointers alone
					}
					compute(inputs, outptr, currentDelta - previousDelta);
					// Note end
					if (voiceFound) {
						m_voices[currentVoice]->setGate(0);
					}
				}
				previousDelta = currentDelta;
			}
		}
		memset(outptr, 0, sizeof(outptr));
		// Compute the left over time
		int count = sampleFrames - currentDelta;
		// Left over time in chunk
		for (i = 0; i < nouts; i++) {
			outptr[i] = outputs[i] + currentDelta; // leaving caller's pointers alone
		}
		compute(inputs, outptr, count);
	}
	else {
		compute(inputs, outputs, sampleFrames);
	}

} // end of synthProcessReplacing

void Faust :: compute(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, 
											VstInt32 sampleFrames)
{
	const unsigned int output_buffer_size = sizeof(FAUSTFLOAT) * sampleFrames;

	// Clear the buffers
	for (int i = 0; i < m_dsp->getNumOutputs(); ++i) {
		for (int frame = 0; frame < sampleFrames; ++frame) {
			outputs[i][frame] = 0;
		}
	}

	if (sampleFrames > (VstInt32)m_tempOutputSize) {
		// if requested number of samples to synthesize exceeds current temporary buffer
		TRACE( fprintf(stderr, "Faust VSTi: Increasing temporary buffer to %d frames\n",
									 sampleFrames) );
		for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
			m_tempOutputs[i] = (FAUSTFLOAT*) realloc(m_tempOutputs[i], output_buffer_size * m_dsp->getNumOutputs());
			m_tempOutputSize = sampleFrames;
		}
	}
	
	std::list<voice_node*> removed;
	std::list<voice_node*>::iterator voice_iter = m_playingVoices.begin();
	for(;voice_iter != m_playingVoices.end(); voice_iter++) {
		int voice = (*voice_iter)->voice;
		m_voices[voice]->m_dsp.compute(sampleFrames, inputs, m_tempOutputs);

		bool silent = true;
		// mix current voice into output
		for (int i = 0; i < m_dsp->getNumOutputs(); ++i) {
			for (int frame = 0; frame < sampleFrames; ++frame) {
				outputs[i][frame] += m_tempOutputs[i][frame];
				if (fabs(m_tempOutputs[i][frame]) > 1e-6) {
					silent = false;
				}
			}
		}
		if (silent) {
			std::vector<VstInt32>::iterator it;
			it = std::find(m_releasedVoices.begin(), m_releasedVoices.end(), voice);
			if (it != m_releasedVoices.end()) {
				m_freeVoices.push_back(voice);
				m_releasedVoices.erase(it);
				removed.push_back(*voice_iter);
			}
		}
	} // end of signal computation and mixdown
	while (removed.size() > 0) {
		std::list<voice_node*>::iterator it;
		it = std::find(m_playingVoices.begin(), m_playingVoices.end(), removed.front());
		float freq = midiToFreq((*it)->note);
		m_voices[(*it)->voice]->setPrevFreq(freq);
		free(*it);
		m_playingVoices.erase(it);
		removed.pop_front();
	}

	// normalize sample by the max polyphony
	for (int i = 0; i < m_dsp->getNumOutputs(); ++i) {
		for (int frame = 0; frame < sampleFrames; ++frame) {
			outputs[i][frame] /= (FAUSTFLOAT)sqrt(MAX_POLYPHONY);
		}
	}
} // end of compute

//-----------------------------------------------------------------------------
VstInt32 Faust::processEvents (VstEvents* ev)
{
  if (ev->numEvents > 0) {
	  TRACE( fprintf(stderr,"=== Faust vsti: processEvents processing %d "
									 "events\n", ev->numEvents) );
  }

  for (VstInt32 i = 0; i < ev->numEvents; i++) {
		TRACE( fprintf(stderr,"=== Faust vsti: event type = %d\n", 
					(ev->events[i])->type) );
		if ((ev->events[i])->type != kVstMidiType) {
			TRACE( fprintf(stderr,"=== Faust vsti: EVENT IGNORED!\n") );
			continue;
		}

		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;
		VstInt32 chan = midiData[0] & 0xf;
		VstInt32 status = midiData[0] & 0xf0;

#ifdef DEBUG
		fprintf(stderr,"\n=== Faust vsti: event->midiData[0] = 0x%x\n", 
				event->midiData[0]);
		fprintf(stderr,"=== Faust vsti: midi channel = 0x%x\n", chan);
		fprintf(stderr,"=== Faust vsti: midi status = 0x%x\n", status);
		fprintf(stderr,"=== Faust vsti: event->midiData[1] = 0x%x\n", 
				event->midiData[1]);
		fprintf(stderr,"=== Faust vsti: event->midiData[2] = 0x%x\n", 
				event->midiData[2]);
#endif

		VstInt32 note = midiData[1] & 0x7f;

		if (status == 0x90) { // note on
			VstInt32 velocity = midiData[2] & 0x7f;
			TRACE( fprintf(stderr,
						"=== Faust vsti: note = %d, velocity = %d, delay = %d\n",
						note,velocity,event->deltaFrames) );
			if (velocity > 0) {
				noteOn(note, velocity, event->deltaFrames);
			} 
			else {
				noteOff(note, event->deltaFrames);
			}
		} 
		else if (status == 0x80) { // note off
			noteOff(note, event->deltaFrames);
			//      } else if (status == 0xA0) { // poly aftertouch
		} else if (status == 0xB0) { // control change
			/* DO SOMETHING WITH THE CONTROLLER DATA */
			fprintf(stderr,"=== Faust vsti: CONTROL CHANGE (status 0xB0)!\n");
			if (midiData[1] == 0x7e || midiData[1] == 0x7b) { // all notes off
				fprintf(stderr,"=== Faust vsti: ALL NOTES OFF!\n");

				//TODO: figure out how to signal all notes off
				// why is all-notes-off inside a "control change" event?
				allNotesOff(); 
			}
		}
		else if (status == 0xE0) { // pitch change
			int val = midiData[1] | (midiData[2] << 7);
			float bend = (val - 0x2000) / 8192.0f;
			bendPitch(bend);
		}
		//      } else if (status == 0xF0) { // SYSX ...
		//      } else if (status == 0xC0) { // program change
		//      } else if (status == 0xD0) { // mono aftertouch
		// For a list, see 
		// http://www.alfred-j-faust.de/rft/midi%20status%20types.html

		TRACE( fprintf(stderr,"=== Faust vsti: Going to next event\n") );

		event++;
	}

	return 1;
}

//----------------------------------------------------------------------------

void Faust::bendPitch(float bend)
{
	TRACE( fprintf(stderr, "Bending pitch by %f\n", bend) );
	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		m_voices[i]->setPitchBend(bend);
	}
} // end of Faust::bendPitch

void Faust::noteOn (VstInt32 note, VstInt32 velocity, VstInt32 delta)
{
#ifdef DEBUG
    fprintf(stderr,"=== Faust vsti: noteOn: note = %d, vel = %d, del = %d\n",note,velocity,delta);
#endif
	m_currentNotes.push_back(note);
	m_currentVelocities.push_back(velocity);
	m_currentDeltas.push_back(delta);
} // end of noteOn

//-----------------------------------------------------------------------------
void Faust::noteOff (VstInt32 note, VstInt32 delta)
{
	TRACE( fprintf(stderr,"=== Faust vsti: noteOff\n") );
	m_currentNotes.push_back(note);
	m_currentVelocities.push_back(0);
	m_currentDeltas.push_back(delta);
} // end of nToteOff

void Faust::allNotesOff( void )
{
	TRACE( fprintf(stderr, "All notes off\n") );
	
	for (unsigned int i = 0; i < MAX_POLYPHONY; ++i) {
		m_voices[i]->setGate(0);
	}

	std::list<voice_node*>::iterator voice_iter = m_playingVoices.begin();
	for (; voice_iter != m_playingVoices.end(); voice_iter++) {
		int voice = (*voice_iter)->voice;
		if (std::find(m_releasedVoices.begin(), m_releasedVoices.end(), voice) == m_releasedVoices.end()) {
			m_releasedVoices.push_back(voice);
		}
	}
} // end of Faust::allNotesOff

/********************END ARCHITECTURE SECTION (part 2/2)****************/

