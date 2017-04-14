/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 Allen Weng
 Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************/

#ifndef __juce_dsp__
#define __juce_dsp__

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-adapter.h"

class juceaudio : public audio, private AudioAppComponent {
    
    private:
        
        dsp* fDSP;
    
        void prepareToPlay (int, double) override
        {
            const BigInteger activeInputChannels =  deviceManager.getCurrentAudioDevice()->getActiveInputChannels();
            const BigInteger activeOutputChannels =  deviceManager.getCurrentAudioDevice()->getActiveOutputChannels();
            const int maxInputChannels = activeInputChannels.getHighestBit() + 1;
            const int maxOutputChannels = activeOutputChannels.getHighestBit() + 1;
            
            // Possibly adapt DSP...
            if (fDSP->getNumInputs() > maxInputChannels || fDSP->getNumOutputs() > maxOutputChannels) {
                fDSP = new dsp_adapter(fDSP, maxInputChannels, maxOutputChannels, 4096);
            }
            
            fDSP->init(int(deviceManager.getCurrentAudioDevice()->getCurrentSampleRate()));
        }
        
        void releaseResources() override
        {}
        
        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
        {
            AVOIDDENORMALS;
            
            const float** inputs = (const float**)alloca(fDSP->getNumInputs() * sizeof(float));
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                inputs[i] = bufferToFill.buffer->getReadPointer(i, bufferToFill.startSample);
            }
            
            float** outputs = (float**)alloca(fDSP->getNumOutputs() * sizeof(float));
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputs[i] = bufferToFill.buffer->getWritePointer(i, bufferToFill.startSample);
            }
            
            // MIDI timestamp is expressed in frames
            fDSP->compute(-1, bufferToFill.numSamples, (float**)inputs, outputs);
        }
    
    public:
    
        juceaudio() {}
        virtual ~juceaudio()
        {
            shutdownAudio();
        }
        
        bool init(const char* name, dsp* dsp) override
        {
            fDSP = dsp;
            return true;
        }
        
        bool start() override
        {
            setAudioChannels (fDSP->getNumInputs(), fDSP->getNumOutputs());
            prepareToPlay(0, 0); // Unused samplerate and buffersize, taken from deviceManager
            return true;
        }
        
        void stop() override
        {
            shutdownAudio();
        }
        
        int get_buffer_size() override
        {
            return int(deviceManager.getCurrentAudioDevice()->getCurrentBufferSizeSamples());
        }
        
        int get_sample_rate() override
        {
            return int(deviceManager.getCurrentAudioDevice()->getCurrentSampleRate());
        }
        
        int get_num_inputs() override { return deviceManager.getCurrentAudioDevice()->getActiveInputChannels().toInteger(); }
        int get_num_outputs() override { return deviceManager.getCurrentAudioDevice()->getActiveOutputChannels().toInteger(); }
        
        float get_cpu_load() override { return float(deviceManager.getCpuUsage()); }
};

#endif
