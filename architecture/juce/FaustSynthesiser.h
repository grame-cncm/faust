/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifndef  __FaustSynthesiser_H__
#define  __FaustSynthesiser_H__

#include "faust/dsp/poly-dsp.h"
#include "JuceLibraryCode/JuceHeader.h"

struct FaustSound : public SynthesiserSound {
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

// An hybrid JUCE and Faust voice

class FaustVoice : public SynthesiserVoice, public dsp_voice {
    
    private:
        
        ScopedPointer<AudioBuffer<FAUSTFLOAT>> fBuffer;
    
    public:
        
        FaustVoice(dsp* dsp):dsp_voice(dsp)
        {
            // Allocate buffer for mixing
            fBuffer = new AudioBuffer<FAUSTFLOAT>(dsp->getNumOutputs(), 8192);
            fDSP->init(SynthesiserVoice::getSampleRate());
        }

        bool canPlaySound (SynthesiserSound* sound) override
        {
            return dynamic_cast<FaustSound*> (sound) != nullptr;
        }

        void startNote (int midiNoteNumber,
                        float velocity,
                        SynthesiserSound* s,
                        int currentPitchWheelPosition) override
        {
            keyOn(midiNoteNumber, velocity);
        }
    
        void stopNote (float velocity, bool allowTailOff) override
        {
            keyOff(!allowTailOff);
            clearCurrentNote();
        }
    
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            // not implemented for now
        }
        
        void controllerMoved (int controllerNumber, int newControllerValue) override
        {
            // not implemented for now
        }
        
        void renderNextBlock (AudioBuffer<FAUSTFLOAT>& outputBuffer,
                              int startSample,
                              int numSamples) override
        {
            // Play the voice
            play(numSamples, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfReadPointers());
            
            // Mix it in outputs
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputBuffer.addFrom(i, startSample, *fBuffer, i, 0, numSamples);
            }
        }
    
};

// Decorates the JUCE Synthesiser and adds Faust polyphonic code for GUI handling

class FaustSynthesiser : public Synthesiser, public dsp_voice_group {
    
    private:
    
        Synthesiser* fSynth;
    
    public:
    
        FaustSynthesiser(uiCallback cb, void* arg):dsp_voice_group(cb, arg, true, true), fSynth(new Synthesiser())
        {}
    
        virtual ~FaustSynthesiser()
        {
            // Voices will be deallocated by fSynth
            dsp_voice_group::clearVoices();
            delete fSynth;
        }
    
        void addVoice(FaustVoice* voice)
        {
            fSynth->addVoice(voice);
            dsp_voice_group::addVoice(voice);
        }
    
        void addSound(SynthesiserSound* sound)
        {
            fSynth->addSound(sound);
        }
    
        void allNotesOff(int midiChannel, bool allowTailOff)
        {
            fSynth->allNotesOff(midiChannel, allowTailOff);
        }
    
        void setCurrentPlaybackSampleRate (double newRate)
        {
            fSynth->setCurrentPlaybackSampleRate(newRate);
        }
    
        void renderNextBlock (AudioBuffer<float>& outputAudio,
                                 const MidiBuffer& inputMidi,
                                 int startSample,
                                 int numSamples)
        {
            fSynth->renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
        void renderNextBlock (AudioBuffer<double>& outputAudio,
                                 const MidiBuffer& inputMidi,
                                 int startSample,
                                 int numSamples)
        {
            fSynth->renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
};

#endif
