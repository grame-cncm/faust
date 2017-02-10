/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include <string>
#include "faust/dsp/poly-dsp.h"
#include "JuceLibraryCode/JuceHeader.h"

struct FaustSound : public SynthesiserSound {
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

class FaustVoice : public SynthesiserVoice,  public dsp_voice {
    
    private:
        
        std::string fGateLabel;
        std::string fGainLabel;
        std::string fFreqLabel;
        
        ScopedPointer<AudioBuffer<FAUSTFLOAT>> fBuffer;
    
    public:
        
        FaustVoice(dsp* dsp):dsp_voice(dsp)
        {
            // Keep gain, freq and gate labels
            extractLabels(fGateLabel, fFreqLabel, fGainLabel);
            
            fDSP->init(SynthesiserVoice::getSampleRate());
            
            // Allocate buffer for mixing
            fBuffer = new AudioBuffer<FAUSTFLOAT>(dsp->getNumOutputs(), 8192);
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
            setParamValue(fFreqLabel, midiToFreq(midiNoteNumber));
            setParamValue(fGainLabel, velocity);
            fTrigger = true;
        }
    
        void stopNote (float velocity, bool allowTailOff) override
        {
           setParamValue(fGateLabel, 0.0f);
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
            if (fTrigger) {
                setParamValue(fGateLabel, 0.0f);
                computeSlice(0, 1, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfReadPointers());
                setParamValue(fGateLabel, 1.0f);
                computeSlice(1, numSamples - 1, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfReadPointers());
                fTrigger = false;
            } else {
                fDSP->compute(numSamples, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfReadPointers());
            }
            
            // Mix them in outputs
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputBuffer.addFrom(i, startSample, *fBuffer, i, 0, numSamples);
            }
        }
    
};


#endif
