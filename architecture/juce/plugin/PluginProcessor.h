/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "JuceLibraryCode/JuceHeader.h"

class dsp;
class juce_midi_handler;
class MidiUI;
class JuceOSCUI;
class JuceStateUI;
#ifdef JUCE_POLY
class FaustSynthesiser;
#endif

class FaustPlugInAudioProcessor : public AudioProcessor, private Timer
{
    public:
        FaustPlugInAudioProcessor();
        ~FaustPlugInAudioProcessor();

        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
        void releaseResources() override;

        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    
        void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

        AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;

        const String getName() const override;

        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;

        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const String getProgramName (int index) override;
        void changeProgramName (int index, const String& newName) override;

        void getStateInformation (MemoryBlock& destData) override;
        void setStateInformation (const void* data, int sizeInBytes) override;
    
        void timerCallback() override;
    
        static void panic(float val, void* arg);
    
    #ifdef JUCE_POLY
        FaustSynthesiser* fSynth;
    #else
    #if defined(MIDICTRL)
        juce_midi_handler* fMIDIHandler;
        MidiUI* fMIDIUI;
    #endif
        dsp* fDSP;
    #endif
    
    #if defined(OSCCTRL)
        JuceOSCUI* fOSCUI;
    #endif
    
        JuceStateUI* fStateUI;
    
private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
   
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
