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

#include "PluginProcessor.h"
#include "PluginEditor.h"

FaustPlugInAudioProcessor::FaustPlugInAudioProcessor() : AudioProcessor()
{
    bool midi_sync = false;
    int nvoices = 1;
    bool group = true;
    
    analyseMeta(midi_sync, nvoices);
    
#ifdef POLY2
    dsp* tmp_dsp = new mydsp();
    std::cout << "Started with " << nvoices << " voices\n";
    
#if MIDICTRL
    if (midi_sync) {
        fDSP = new timed_dsp(new dsp_sequencer(new mydsp_poly(tmp_dsp, nvoices, true, group), new dsp_effect()));
    } else {
        fDSP = new dsp_sequencer(new mydsp_poly(tmp_dsp, nvoices, true, group), new dsp_effect());
    }
#else
    fDSP = new dsp_sequencer(new mydsp_poly(tmp_dsp, nvoices, false, group), new dsp_effect());
#endif
    
#else
    dsp* tmp_dsp = new mydsp();
    if (nvoices > 1) {
        std::cout << "Started with " << nvoices << " voices\n";
#if MIDICTRL
        if (midi_sync) {
            fDSP = new timed_dsp(new mydsp_poly(tmp_dsp, nvoices, true, group));
        } else {
            fDSP = new mydsp_poly(tmp_dsp, nvoices, true, group);
        }
#else
        fDSP = new mydsp_poly(tmp_dsp, nvoices, false, group);
#endif
    } else {
#if MIDICTRL
        if (midi_sync) {
            fDSP = new timed_dsp(new mydsp());
        } else {
            fDSP = new mydsp();
        }
#else
        fDSP = new mydsp();
#endif
    }
    
#endif
    
#if defined(MIDICTRL)
    fMIDIHandler = new juce_midi_handler();
    fMIDIUI = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIUI);
    if (!fMIDIUI->run()) {
        std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
    }
#endif
    
#if defined(OSCCTRL)
    fOSCUI = new JuceOSCUI("127.0.0.1", 5510, 5511);
    fDSP->buildUserInterface(fOSCUI);
    if (!fOSCUI->run()) {
        std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
    }
#endif
       
    startTimerHz(25);
}

FaustPlugInAudioProcessor::~FaustPlugInAudioProcessor()
{
    delete fDSP;
    
#if defined(MIDICTRL)
    delete fMIDIUI;
    delete fMIDIHandler;
#endif
#if defined(OSCCTRL)
    delete fOSCUI;
#endif
}

void FaustPlugInAudioProcessor::timerCallback()
{
    GUI::updateAllGuis();
}

//==============================================================================
const String FaustPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FaustPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FaustPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double FaustPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FaustPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FaustPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FaustPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return String();
}

void FaustPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FaustPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    fDSP->init(int(sampleRate));
}

void FaustPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool FaustPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsSynth
    return (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs());
#else
    return (layouts.getMainInputChannelSet().size() == fDSP->getNumInputs())
    && (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs());
#endif
}

void FaustPlugInAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    AVOIDDENORMALS;
    
#if defined(MIDICTRL)
    fMIDIHandler->decodeBuffer(midiMessages);
    midiMessages.clear();
#endif
       
    fDSP->compute(buffer.getNumSamples(),
                  (FAUSTFLOAT**)buffer.getArrayOfReadPointers(),
                  (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
}

//==============================================================================
bool FaustPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FaustPlugInAudioProcessor::createEditor()
{
    return new FaustPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void FaustPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FaustPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustPlugInAudioProcessor();
}
