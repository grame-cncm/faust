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

#include <math.h>
#include <algorithm>

#if JUCE_WINDOWS
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1
#endif

#include "JuceLibraryCode/JuceHeader.h"

#include "faust/gui/MapUI.h"
#include "faust/misc.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/MidiUI.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/JuceGUI.h"
#include "faust/gui/JuceParameterUI.h"
#include "faust/gui/JuceStateUI.h"

#if defined(OSCCTRL)
#include "faust/gui/JuceOSCUI.h"
#endif

#if defined(MIDICTRL)
#include "faust/midi/juce-midi.h"
#endif

#if defined(POLY2)
#include "faust/dsp/dsp-combiner.h"
#include "dsp_effect.cpp"
#endif 

<<includeIntrinsic>>

<<includeclass>>

#if defined(JUCE_POLY)

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
        
        Synthesiser fSynth;
    
        static void panic(float val, void* arg)
        {
            static_cast<FaustSynthesiser*>(arg)->allNotesOff(0, false); // 0 stops all voices
        }
  
    public:
        
        FaustSynthesiser():dsp_voice_group(panic, this, true, true)
        {}
        
        virtual ~FaustSynthesiser()
        {
            // Voices will be deallocated by fSynth
            dsp_voice_group::clearVoices();
        }
        
        void addVoice(FaustVoice* voice)
        {
            fSynth.addVoice(voice);
            dsp_voice_group::addVoice(voice);
        }
        
        void addSound(SynthesiserSound* sound)
        {
            fSynth.addSound(sound);
        }
        
        void allNotesOff(int midiChannel, bool allowTailOff)
        {
            fSynth.allNotesOff(midiChannel, allowTailOff);
        }
        
        void setCurrentPlaybackSampleRate (double newRate)
        {
            fSynth.setCurrentPlaybackSampleRate(newRate);
        }
        
        void renderNextBlock (AudioBuffer<float>& outputAudio,
                              const MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
        
        void renderNextBlock (AudioBuffer<double>& outputAudio,
                              const MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
};

#endif

class FaustPlugInAudioProcessor : public AudioProcessor, private Timer
{

    public:
        
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor();
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        void processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }

    
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
    
        void releaseResources() override
        {}
        
        void timerCallback() override;
    
        AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
    
    #ifdef JUCE_POLY
        ScopedPointer<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        ScopedPointer<juce_midi_handler> fMIDIHandler;
        ScopedPointer<MidiUI> fMIDIUI;
    #endif
        ScopedPointer<dsp> fDSP;
    #endif
        
    #if defined(OSCCTRL)
        ScopedPointer<JuceOSCUI> fOSCUI;
    #endif
        
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
        
    private:
    
        template <typename FloatType>
        void process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages);
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

class FaustPlugInAudioProcessorEditor : public AudioProcessorEditor
{
    
    public:
        
        FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor&);
        virtual ~FaustPlugInAudioProcessorEditor();
        
        void paint (Graphics&) override;
        void resized() override;
        
    private:
        
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        FaustPlugInAudioProcessor& processor;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessorEditor)
        
        JuceGUI fJuceGUI;
    
};

static mydsp gDSP;

FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: AudioProcessor (getBusesProperties()), fParameterUI(this)
{
    bool midi_sync = false;
    int nvoices = 0;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
#ifdef JUCE_POLY
    fSynth = new FaustSynthesiser();
    for (int i = 0; i < nvoices; i++) {
        fSynth->addVoice(new FaustVoice(new mydsp()));
    }
    fSynth->init();
    fSynth->addSound(new FaustSound());
#else
    
    bool group = true;
    mydsp_poly* dsp_poly = nullptr;
    
#ifdef POLY2
    std::cout << "Started with " << nvoices << " voices\n";
    dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
    
#if MIDICTRL
    if (midi_sync) {
        fDSP = new timed_dsp(new dsp_sequencer(dsp_poly, new dsp_effect()));
    } else {
        fDSP = new dsp_sequencer(dsp_poly, new dsp_effect());
    }
#else
    fDSP = new dsp_sequencer(dsp_poly, new dsp_effect());
#endif
    
#else
    if (nvoices > 0) {
        std::cout << "Started with " << nvoices << " voices\n";
        dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
        
#if MIDICTRL
        if (midi_sync) {
            fDSP = new timed_dsp(dsp_poly);
        } else {
            fDSP = dsp_poly;
        }
#else
        fDSP = dsp_poly;
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
    fMIDIHandler->addMidiIn(dsp_poly);
    fMIDIUI = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIUI);
    if (!fMIDIUI->run()) {
        std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
    }
#endif
    
#endif
    
#if defined(OSCCTRL)
    fOSCUI = new JuceOSCUI("127.0.0.1", 5510, 5511);
#ifdef JUCE_POLY
    fSynth->buildUserInterface(fOSCUI);
#else
    fDSP->buildUserInterface(fOSCUI);
#endif
    if (!fOSCUI->run()) {
        std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
    }
#endif
    
#ifdef JUCE_POLY
    fSynth->buildUserInterface(&fStateUI);
    fSynth->buildUserInterface(&fParameterUI);
#else
    fDSP->buildUserInterface(&fStateUI);
    fDSP->buildUserInterface(&fParameterUI);
#endif
    
    startTimerHz(25);
}

FaustPlugInAudioProcessor::~FaustPlugInAudioProcessor()
{}

AudioProcessor::BusesProperties FaustPlugInAudioProcessor::getBusesProperties()
{
    if (PluginHostType::getPluginLoadedAs() == wrapperType_Standalone) {
        if (gDSP.getNumInputs() == 0) {
            return BusesProperties().withOutput("Output", AudioChannelSet::discreteChannels(std::min<int>(2, gDSP.getNumOutputs())), true);
        } else {
            return BusesProperties()
            .withInput("Input", AudioChannelSet::discreteChannels(std::min<int>(2, gDSP.getNumInputs())), true)
            .withOutput("Output", AudioChannelSet::discreteChannels(std::min<int>(2, gDSP.getNumOutputs())), true);
        }
    } else {
        if (gDSP.getNumInputs() == 0) {
            return BusesProperties().withOutput("Output", AudioChannelSet::discreteChannels(gDSP.getNumOutputs()), true);
        } else {
            return BusesProperties()
            .withInput("Input", AudioChannelSet::discreteChannels(gDSP.getNumInputs()), true)
            .withOutput("Output", AudioChannelSet::discreteChannels(gDSP.getNumOutputs()), true);
        }
    }
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
{}

const String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return String();
}

void FaustPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{}

bool FaustPlugInAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return sizeof(FAUSTFLOAT) == 8;
}

//==============================================================================
void FaustPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need...
    
#ifdef JUCE_POLY
    fSynth->setCurrentPlaybackSampleRate (sampleRate);
#else
    
    // Possibly adapt DSP
    if (fDSP->getNumInputs() > getTotalNumInputChannels() || fDSP->getNumOutputs() > getTotalNumOutputChannels()) {
        fDSP = new dsp_adapter(fDSP.release(), getTotalNumInputChannels(), getTotalNumOutputChannels(), 4096);
    }
   
    // Setting the DSP default values has already been done by 'buildUserInterface(&fStateUI)' call
    mydsp::classInit(int(sampleRate));
    fDSP->instanceConstants(int(sampleRate));
    fDSP->instanceClear();
    
#endif
}

bool FaustPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#ifdef JUCE_POLY
    return true;
#else
    
#if JucePlugin_IsSynth
    // Stereo is supported
    return (layouts.getMainOutputChannelSet().size() == 2) || (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs());
#else
    // Stereo is supported
    return
    ((layouts.getMainInputChannelSet().size() == 2) && (layouts.getMainOutputChannelSet().size() == 2))
    ||
    ((layouts.getMainInputChannelSet().size() == fDSP->getNumInputs()) && (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs()));
#endif
    
#endif
}

template <typename FloatType>
void FaustPlugInAudioProcessor::process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages)
{
    AVOIDDENORMALS;
    
#ifdef JUCE_POLY
    fSynth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
#else
#if defined(MIDICTRL)
    // Read MIDI input events from midiMessages
    fMIDIHandler->decodeBuffer(midiMessages);
    // Then write MIDI output events to midiMessages
    fMIDIHandler->encodeBuffer(midiMessages);
#endif
    // MIDI timestamp is expressed in frames
    fDSP->compute(-1, buffer.getNumSamples(),
                  (FAUSTFLOAT**)buffer.getArrayOfReadPointers(),
                  (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
#endif
}

//==============================================================================
bool FaustPlugInAudioProcessor::hasEditor() const
{
    return true;
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
    
    fStateUI.getStateInformation(destData);
}

void FaustPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    fStateUI.setStateInformation(data, sizeInBytes);
 }

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustPlugInAudioProcessor();
}

//==============================================================================
FaustPlugInAudioProcessorEditor::FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), fJuceGUI(false)
{
    addAndMakeVisible(fJuceGUI);
    
#ifdef JUCE_POLY
    p.fSynth->buildUserInterface(&fJuceGUI);
#else
    p.fDSP->buildUserInterface(&fJuceGUI);
#endif
    
    juce::Rectangle<int> recommendedSize = fJuceGUI.getSize();
    setSize (recommendedSize.getWidth(), recommendedSize.getHeight());
}

FaustPlugInAudioProcessorEditor::~FaustPlugInAudioProcessorEditor()
{}

//==============================================================================
void FaustPlugInAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void FaustPlugInAudioProcessorEditor::resized()
{
    fJuceGUI.setBounds(getLocalBounds());
}

// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
