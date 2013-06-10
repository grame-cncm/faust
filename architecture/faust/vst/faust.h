#ifndef __VST_FAUST_H__
#define __VST_FAUST_H__

#include <list>
#include <map>
#include <vector>

#include "audioeffectx.h"
#include "dsp.h"

// Increasing MAX_POLYPHONY can increase processing time a lot
// which can as well distort the sound making it sound like noise
const int MAX_POLYPHONY = 10;

const int INITIAL_TEMP_OUTPUT_SIZE = 1024;

//////////////////////////////////////////////////////////////////
// Faust class definition
// This class implements the abstract methods of AudioEffectX
// that define the VST instrument behavior.
//////////////////////////////////////////////////////////////////
class Faust : public AudioEffectX {
public:
	// Constructor
  Faust(audioMasterCallback audioMaster, dsp* dspi, vstUI* dspUIi);

	// Destructor
  virtual ~Faust();

  virtual void processReplacing (FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, VstInt32 sampleFrames);
  virtual VstInt32 processEvents (VstEvents* events);

  virtual void setProgram (VstInt32 program);
  virtual void setProgramName (const char *name);
  virtual void getProgramName (char *name);
  virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char *text);

  virtual void setParameter (VstInt32 index, float value);
  virtual float getParameter (VstInt32 index);
  virtual void getParameterLabel (VstInt32 index, char *label);
  virtual void getParameterDisplay (VstInt32 index, char *text);
  virtual void getParameterName (VstInt32 index, char *text);
	virtual bool getParameterProperties(VstInt32 index, VstParameterProperties* properties);

  virtual void setSampleRate (float sampleRate);

  virtual bool getInputProperties (VstInt32 index, VstPinProperties *properties);
  virtual bool getOutputProperties (VstInt32 index, VstPinProperties *properties);

  virtual bool getEffectName (char *name);
  virtual bool getVendorString (char *text);
  virtual bool getProductString (char *text);
  virtual VstInt32 getVendorVersion ();
  virtual VstInt32 canDo (char *text);

  virtual VstInt32 getNumMidiInputChannels ();
  virtual VstInt32 getNumMidiOutputChannels ();

  virtual VstInt32 getMidiProgramName (VstInt32 channel, MidiProgramName *midiProgramName);
  virtual VstInt32 getCurrentMidiProgram (VstInt32 channel, MidiProgramName *currentProgram);
  virtual VstInt32 getMidiProgramCategory (VstInt32 channel, MidiProgramCategory *category);

private:
  // Get metadata supplied by Faust compiler
  const char* getMetadata(const char* key, const char* defaultString);

  void initProcess ();
  void noteOn (VstInt32 note, VstInt32 velocity, VstInt32 delta);
  void noteOff (VstInt32 note);
	void allNotesOff( void );
  void fillProgram (VstInt32 channel, VstInt32 prg, MidiProgramName* mpn);

	void synthProcessReplacing(float **inputs, float **outputs, 
														 VstInt32 sampleFrames);

	void compute(float** inputs, float** outputs, VstInt32 sampleFrames);
	void bendPitch(float bend);

  dsp* m_dsp;
  vstUI*	m_dspUI;

  // For synths:
  bool noteIsOn;
  VstInt32 currentNote;
  VstInt32 currentVelocity;
  VstInt32 currentDelta;

  char programName[kVstMaxProgNameLen + 1];

  // Polyphony
	std::vector<Voice*> m_voices;

	// Occupied voices - map note to voice index
	std::map<VstInt32, int> m_playingVoices;

	// Free voices - currently rot playing
	std :: list< int > m_freeVoices;

	// Previously played voice
	int m_prevVoice;

	FAUSTFLOAT** m_tempOutputs;
	size_t m_tempOutputSize; // in float frames
}; // end of Faust class

#endif
