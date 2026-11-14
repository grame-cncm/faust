/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public License
 as published by the Free Software Foundation; either version 2.1 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include <algorithm>
#include <assert.h>
#include <map>
#include <vector>

#if JUCE_WINDOWS
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1
#endif

#include "JuceLibraryCode/JuceHeader.h"

#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/juce-dsp-adapter.h"
#include "faust/gui/MidiUI.h"
#include "faust/dsp/poly-dsp.h"
#if !defined(PLUGIN_MAGIC) && !defined(FAUST_CUSTOM_EDITOR)
#include "faust/gui/JuceGUI.h"
#endif
#include "faust/gui/JuceParameterUI.h"
#include "faust/gui/JuceStateUI.h"
#include "faust/gui/LatencyMeta.h"

// Always included otherwise -i mode sometimes fails...
#include "faust/gui/DecoratorUI.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

#if defined(OSCCTRL)
#include "faust/gui/JuceOSCUI.h"
#endif

#if defined(MIDICTRL)
#include "faust/midi/juce-midi.h"
#include "faust/dsp/timed-dsp.h"
#endif

#if defined(POLY2)
#include "faust/dsp/dsp-combiner.h"
#include "effect.h"
#endif 

// Presets given to faust2juce -presets <file.json>, as the gFaustPresets JSON string
#if defined(FAUST_PRESETS)
#include "FaustPresets.h"
#endif

// The current values of a plugin's parameters that differ from their default value, as
// presets list them: { "<parameter ID>": value, ... }, values in the units of the DSP and
// rounded to 7 significant digits (the precision of a float)
static juce::var faustPresetValues(juce::AudioProcessor& processor)
{
    juce::DynamicObject::Ptr values = new juce::DynamicObject();
    for (auto* parameter : processor.getParameters()) {
        if (auto* ranged = dynamic_cast<juce::RangedAudioParameter*>(parameter)) {
            float normalised = ranged->getValue();
            if (std::abs(normalised - ranged->getDefaultValue()) > 1e-6f) {
                juce::String text = juce::String::toDecimalStringWithSignificantFigures(ranged->convertFrom0to1(normalised), 7);
                values->setProperty(ranged->getParameterID(), text.getDoubleValue());
            }
        }
    }
    return juce::var(values.get());
}

/*
 Write the current values of a plugin's parameters as one preset in the faust2juce -presets
 format: { "<name>": { "<parameter ID>": value, ... } }, values in the units of the DSP.
 Only the parameters that differ from their default value are written, as presets list
 them, and values are rounded to 7 significant digits (the precision of a float).

 The generic editor offers it in its context menu. A custom editor, even in another
 translation unit, can declare it and call it:
     juce::String faustPresetJSON(juce::AudioProcessor& processor, const juce::String& name);
*/
juce::String faustPresetJSON(juce::AudioProcessor& processor, const juce::String& name)
{
    juce::DynamicObject::Ptr preset = new juce::DynamicObject();
    preset->setProperty(name, faustPresetValues(processor));
    return juce::JSON::toString(juce::var(preset.get()));
}

// Read a file in the faust2juce -presets format into presets, an object mapping preset names
// to their values. A missing or empty file gives an empty object. Return an error message,
// or an empty string.
static juce::String faustReadPresetsFile(const juce::File& file, juce::var& presets)
{
    presets = juce::var(new juce::DynamicObject());
    if (!file.existsAsFile()) return {};
    juce::String text = file.loadFileAsString();
    if (text.trim().isEmpty()) return {};
    juce::var parsed;
    juce::Result result = juce::JSON::parse(text, parsed);
    if (result.failed()) return file.getFullPathName() + ": " + result.getErrorMessage();
    if (parsed.getDynamicObject() == nullptr) {
        return file.getFullPathName() + " is not a faust2juce -presets file: a JSON object is expected";
    }
    presets = parsed;
    return {};
}

/*
 Add the current values of a plugin's parameters, as written by faustPresetJSON, to a file
 in the faust2juce -presets format, as the preset <name>. A preset of the same name is
 replaced where it is, the others are kept in their order, and a missing file is created.
 Return an error message, or an empty string.

 The generic editor offers it in its context menu, to prepare the file given to -presets
 (in the standalone application of the plugin for instance). A custom editor can declare
 it and call it:
     juce::String faustAddPresetToFile(juce::AudioProcessor& processor, const juce::String& name,
                                       const juce::File& file);
*/
juce::String faustAddPresetToFile(juce::AudioProcessor& processor, const juce::String& name, const juce::File& file)
{
    juce::var presets;
    juce::String error = faustReadPresetsFile(file, presets);
    if (error.isNotEmpty()) return error;
    presets.getDynamicObject()->setProperty(name, faustPresetValues(processor));
    if (!file.replaceWithText(juce::JSON::toString(presets) + "\n")) return "Cannot write " + file.getFullPathName();
    return {};
}

/*
 A project can replace the generic editor by defining FAUST_CUSTOM_EDITOR as the name
 of a header, for instance -DFAUST_CUSTOM_EDITOR='"MyEditor.h"'. The header is included
 here and must define:

 - FaustEditorBridge: state shared between the processor, which owns it, and the editor.
   The processor calls it on the audio thread:
     prepare(double sampleRate, int blockSize, int numVoices) from prepareToPlay,
       numVoices being 0 for a monophonic DSP;
     processMidi(juce::MidiBuffer& midi, int numSamples) before the MIDI events are
       decoded, so that it can read them or add its own (an on-screen keyboard);
     processAudio(const juce::AudioBuffer<T>& buffer, int activeVoices) after each
       block, with T float or double, activeVoices being -1 when unknown (-jsynth).
 - juce::AudioProcessorEditor* createFaustEditor(juce::AudioProcessor&, FaustEditorBridge&)

 Both only depend on JUCE, so the editor can live in its own translation unit.
*/
#if defined(FAUST_CUSTOM_EDITOR)
#if defined(PLUGIN_MAGIC)
#error "FAUST_CUSTOM_EDITOR cannot be used with PLUGIN_MAGIC"
#endif
#include FAUST_CUSTOM_EDITOR
#endif

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDSOUNDFILE(l,s)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

<<includeIntrinsic>>

<<includeclass>>

#if defined(JUCE_POLY)

struct FaustSound : public juce::SynthesiserSound {
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

// An hybrid JUCE and Faust voice

class FaustVoice : public juce::SynthesiserVoice, public dsp_voice {
    
    private:
        
        static constexpr int kMaxSlice = 8192;   // frames of fBuffer
        
        std::unique_ptr<juce::AudioBuffer<FAUSTFLOAT>> fBuffer;
        
        /*
            Computes the voice and mixes it into 'outputBuffer', in samples of type FloatType
            (float, or double when the host processes in double precision), converting from
            FAUSTFLOAT if needed. Blocks longer than fBuffer are computed in several slices.
        */
        template <typename FloatType>
        void renderVoice (juce::AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
        {
            // Only plays when the voice is active
            if (!isVoiceActive()) {
                return;
            }
            
            const int outputs = std::min(fDSP->getNumOutputs(), outputBuffer.getNumChannels());
            for (int offset = 0; offset < numSamples; offset += kMaxSlice) {
                const int slice = std::min(kMaxSlice, numSamples - offset);
                
                // Play the voice
                compute(slice, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfWritePointers());
                
                // Mix it in outputs
                for (int chan = 0; chan < outputs; chan++) {
                    const FAUSTFLOAT* voice = fBuffer->getReadPointer(chan);
                    FloatType* output = outputBuffer.getWritePointer(chan, startSample + offset);
                    for (int frame = 0; frame < slice; frame++) {
                        output[frame] += FloatType(voice[frame]);
                    }
                }
            }
        }
        
    public:
        
        FaustVoice(dsp* dsp):dsp_voice(dsp)
        {
            // Allocate buffer for mixing
            fBuffer = std::make_unique<juce::AudioBuffer<FAUSTFLOAT>>(dsp->getNumOutputs(), kMaxSlice);
            fDSP->init(juce::SynthesiserVoice::getSampleRate());
        }
        
        bool canPlaySound (juce::SynthesiserSound* sound) override
        {
            return dynamic_cast<FaustSound*> (sound) != nullptr;
        }
        
        // The voice DSP is initialized in the constructor before the host gives the sample rate:
        // its constants are recomputed (keeping its controls) when the sample rate is set
        void setCurrentPlaybackSampleRate (double newRate) override
        {
            juce::SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);
            if (newRate > 0) {
                fDSP->instanceConstants(int(newRate));
                fDSP->instanceClear();
            }
        }
        
        void startNote (int midiNoteNumber,
                        float velocity,
                        juce::SynthesiserSound* s,
                        int currentPitchWheelPosition) override
        {
            // Note is triggered
            keyOn(midiNoteNumber, velocity);
        }
        
        void stopNote (float velocity, bool allowTailOff) override
        {
            keyOff(!allowTailOff);
        }
        
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            // not implemented for now
        }
        
        void controllerMoved (int controllerNumber, int newControllerValue) override
        {
            // not implemented for now
        }
        
        // The host can process in float or in double precision, whatever FAUSTFLOAT is
        void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                              int startSample,
                              int numSamples) override
        {
            renderVoice(outputBuffer, startSample, numSamples);
        }
        
        void renderNextBlock (juce::AudioBuffer<double>& outputBuffer,
                              int startSample,
                              int numSamples) override
        {
            renderVoice(outputBuffer, startSample, numSamples);
        }
    
};

// Decorates the JUCE Synthesiser and adds Faust polyphonic code for GUI handling

class FaustSynthesiser : public juce::Synthesiser, public dsp_voice_group {
    
    private:
        
        juce::Synthesiser fSynth;
    
        static void panic(FAUSTFLOAT val, void* arg)
        {
            static_cast<FaustSynthesiser*>(arg)->allNotesOff(0, false); // 0 stops all voices
        }
  
    public:
        
        FaustSynthesiser():dsp_voice_group(panic, this, true, true)
        {
            setNoteStealingEnabled(true);
        }
        
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
        
        void addSound(juce::SynthesiserSound* sound)
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
        
        void renderNextBlock (juce::AudioBuffer<float>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
        
        void renderNextBlock (juce::AudioBuffer<double>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
};

#endif

// Using the PluginGuiMagic project (https://github.com/ffAudio/foleys_gui_magic)

#if defined(PLUGIN_MAGIC)

class FaustPlugInAudioProcessor : public foleys::MagicProcessor, private juce::Timer
{
    
    public:
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
        
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
    #ifdef MAGIC_LEVEL_SOURCE
            fOutputMeter->pushSamples(buffer);
    #endif
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void releaseResources() override
        {}
        
    #if defined(FAUST_PRESETS)
        // PluginGuiMagic saves its own state (its ValueTree, with the parameter values):
        // the current program is added to it as a property, and read back after a restore
        void getStateInformation (juce::MemoryBlock& destData) override;
        void postSetStateInformation() override;
    #endif
        
        void timerCallback() override;
        
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
      
    #ifdef MAGIC_LEVEL_SOURCE
        foleys::MagicLevelSource* fOutputMeter = nullptr;
    #endif
        juce::AudioProcessorValueTreeState treeState{ *this, nullptr };
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<dsp> fDSP;
        FaustHostAdapter fHostAdapter;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
        
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
        
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
    
        // Number of polyphonic voices (0 for a monophonic DSP)
        int fNumVoices = 0;
    #ifndef JUCE_POLY
        // The polyphonic voices, if any, to count the active ones
        dsp_voice_group* fPolyVoices = nullptr;
    #endif
        // Tail length reported to the host, from [declare tail_sec "<seconds>"]
        double fTailLength = 0.0;
        // Latency reported to the host, from [declare latency_samples "<frames>"] or [declare latency_sec "<seconds>"]
        LatencyMeta fLatency;
    #if defined(FAUST_PRESETS)
        // Host programs: "Default" (the values declared in the DSP), then the presets
        // of gFaustPresets, each mapping control names to values
        struct FaustProgram {
            juce::String fName;
            std::map<juce::String, float> fValues;
        };
        std::vector<FaustProgram> fPrograms;
        int fCurrentProgram = 0;
        void loadPrograms();
        juce::RangedAudioParameter* findParameter(const juce::String& name);
    #endif
    #if defined(POLY2)
        // The voices and the effect, owned by fDSP, visited separately to build the
        // host parameters (see the constructor)
        dsp* fVoiceDSP = nullptr;
        dsp* fEffectDSP = nullptr;
    #endif
    
        // Number of voices currently sounding, -1 when unknown (-jsynth)
        int getNumActiveVoices() const
        {
        #ifdef JUCE_POLY
            return -1;
        #else
            return (fPolyVoices) ? fPolyVoices->getNumActiveVoices() : 0;
        #endif
        }
        
    private:
        
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#else

class FaustPlugInAudioProcessor : public juce::AudioProcessor, private juce::Timer
{

    public:
        
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
    
        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void getStateInformation (juce::MemoryBlock& destData) override;
        void setStateInformation (const void* data, int sizeInBytes) override;
    
        void releaseResources() override
        {}
        
        void timerCallback() override;
    
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<dsp> fDSP;
        FaustHostAdapter fHostAdapter;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
    
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
    
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
    
        // Number of polyphonic voices (0 for a monophonic DSP)
        int fNumVoices = 0;
    #ifndef JUCE_POLY
        // The polyphonic voices, if any, to count the active ones
        dsp_voice_group* fPolyVoices = nullptr;
    #endif
        // Tail length reported to the host, from [declare tail_sec "<seconds>"]
        double fTailLength = 0.0;
        // Latency reported to the host, from [declare latency_samples "<frames>"] or [declare latency_sec "<seconds>"]
        LatencyMeta fLatency;
    #if defined(FAUST_PRESETS)
        // Host programs: "Default" (the values declared in the DSP), then the presets
        // of gFaustPresets, each mapping control names to values
        struct FaustProgram {
            juce::String fName;
            std::map<juce::String, float> fValues;
        };
        std::vector<FaustProgram> fPrograms;
        int fCurrentProgram = 0;
        void loadPrograms();
        juce::RangedAudioParameter* findParameter(const juce::String& name);
    #endif
    #if defined(POLY2)
        // The voices and the effect, owned by fDSP, visited separately to build the
        // host parameters (see the constructor)
        dsp* fVoiceDSP = nullptr;
        dsp* fEffectDSP = nullptr;
    #endif
    
        // Number of voices currently sounding, -1 when unknown (-jsynth)
        int getNumActiveVoices() const
        {
        #ifdef JUCE_POLY
            return -1;
        #else
            return (fPolyVoices) ? fPolyVoices->getNumActiveVoices() : 0;
        #endif
        }
    
    #if defined(FAUST_CUSTOM_EDITOR)
        // Defined by the FAUST_CUSTOM_EDITOR header; it outlives the editor, which can
        // be closed and reopened while the processor keeps running
        FaustEditorBridge fEditorBridge;
    #else
        // The presets file to which the context menu of the generic editor adds the
        // current settings, kept here to survive the editor; not saved with the state
        juce::File fPresetsFile;
    #endif

    private:
    
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#endif

#if !defined(FAUST_CUSTOM_EDITOR)
class FaustPlugInAudioProcessorEditor : public juce::AudioProcessorEditor
{
    
    public:
        
        FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor&);
        virtual ~FaustPlugInAudioProcessorEditor() {}
        
        void paint (juce::Graphics&) override;
        void resized() override;
    #ifndef PLUGIN_MAGIC
        // Context menu: copy the current settings as a faust2juce -presets entry, or add
        // them to a presets file
        void mouseDown (const juce::MouseEvent&) override;
    #endif

    private:

        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        FaustPlugInAudioProcessor& processor;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessorEditor)
#ifndef PLUGIN_MAGIC
        JuceGUI fJuceGUI;

        // The dialogs of the context menu, kept until the next use since they are asynchronous
        std::unique_ptr<juce::FileChooser> fPresetsChooser;
        std::unique_ptr<juce::AlertWindow> fPresetNameDialog;
        std::unique_ptr<juce::AlertWindow> fPresetReplaceDialog;

        void choosePresetsFile(bool create);
        void askPresetName(const juce::File& file, bool create);
        void addPreset(const juce::File& file, const juce::String& name, bool create);
        void showPresetError(const juce::String& message);
#endif
};
#endif

#ifndef PLUGIN_MAGIC
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: juce::AudioProcessor (getBusesProperties()), fParameterUI(this)
#else
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: foleys::MagicProcessor (getBusesProperties()), fParameterUI(this)	
#endif
{
    bool midi_sync = false;
    bool midi = false;
    int nvoices = 0;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi, midi_sync, nvoices);
    
    // Delays and reverbs keep sounding after the input stops: [declare tail_sec "<seconds>"]
    struct TailMeta : public Meta {
        double fSeconds = 0.0;
        void declare(const char* key, const char* value)
        {
            if (std::string(key) == "tail_sec") fSeconds = std::atof(value);
        }
    };
    TailMeta tail_meta;
    tmp_dsp->metadata(&tail_meta);
    fTailLength = tail_meta.fSeconds;
    // Lookaheads and linear phase filters delay the signal: the host compensates it
    tmp_dsp->metadata(&fLatency);
    delete tmp_dsp;
    fNumVoices = nvoices;
	
#ifdef PLUGIN_MAGIC
#ifdef MAGIC_LOAD_BINARY
    // change magic_xml and magic_xmlSize to match the name of your included
    // XML file from Plugin GUI Magic
    magicState.setGuiValueTree(BinaryData::magic_xml, BinaryData::magic_xmlSize);
#endif
// put other GUI Magic sources here, similar to expression below.
#ifdef MAGIC_LEVEL_SOURCE
    fOutputMeter = magicState.createAndAddObject<foleys::MagicLevelSource>("output");
#endif
#endif
   
#ifdef JUCE_POLY
    assert(nvoices > 0);
    fSynth = std::make_unique<FaustSynthesiser>();
    for (int i = 0; i < nvoices; i++) {
        fSynth->addVoice(new FaustVoice(new mydsp()));
    }
    fSynth->init();
    fSynth->addSound(new FaustSound());
#else
    
    bool group = true;
    
#ifdef POLY2
    assert(nvoices > 0);
    std::cout << "Started with " << nvoices << " voices\n";
    dsp* dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
    fPolyVoices = static_cast<mydsp_poly*>(dsp);
    fVoiceDSP = dsp;
    fEffectDSP = new effect();
    
#if MIDICTRL
    if (midi_sync) {
        fDSP = std::make_unique<timed_dsp>(new dsp_sequencer(fVoiceDSP, fEffectDSP));
    } else {
        fDSP = std::make_unique<dsp_sequencer>(fVoiceDSP, fEffectDSP);
    }
#else
    fDSP = std::make_unique<dsp_sequencer>(fVoiceDSP, fEffectDSP);
#endif
    
#else
    if (nvoices > 0) {
        std::cout << "Started with " << nvoices << " voices\n";
        dsp* dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
        fPolyVoices = static_cast<mydsp_poly*>(dsp);
        
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(dsp);
        } else {
            fDSP = std::make_unique<decorator_dsp>(dsp);
        }
#else
        fDSP = std::make_unique<decorator_dsp>(dsp);
#endif
    } else {
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(new mydsp());
        } else {
            fDSP = std::make_unique<mydsp>();
        }
#else
        fDSP = std::make_unique<mydsp>();
#endif
    }
    
#endif
    
#if defined(MIDICTRL)
    fMIDIHandler = std::make_unique<juce_midi_handler>();
    fMIDIUI = std::make_unique<MidiUI>(fMIDIHandler.get());
    fDSP->buildUserInterface(fMIDIUI.get());
    if (!fMIDIUI->run()) {
        std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
    }
#endif
    
#endif
    
#if defined(OSCCTRL)
    fOSCUI = std::make_unique<JuceOSCUI>("127.0.0.1", 5510, 5511);
#ifdef JUCE_POLY
    fSynth->buildUserInterface(fOSCUI.get());
#else
    fDSP->buildUserInterface(fOSCUI.get());
#endif
    if (!fOSCUI->run()) {
        std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
    }
#endif
    
#if defined(SOUNDFILE)
    // Use bundle path
    auto file = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
        .getParentDirectory().getParentDirectory().getChildFile("Resources");
    fSoundUI = std::make_unique<SoundUI>(file.getFullPathName().toStdString(), -1, nullptr, sizeof(FAUSTFLOAT) == 8);
    fDSP->buildUserInterface(fSoundUI.get());
#endif
    
#ifdef JUCE_POLY
    fSynth->buildUserInterface(&fStateUI);
    fSynth->buildUserInterface(&fParameterUI);
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fSynth->instanceResetUserInterface();
    }
#else
    fDSP->buildUserInterface(&fStateUI);
#if defined(POLY2) && !defined(FAUST_JUCE_FULLPATH_IDS)
    // Visit the voices and the effect one after the other rather than the sequencer
    // that combines them: JuceParameterUI then computes the shortnames of each DSP
    // without the groups added by the sequencer, and a control declared by both
    // (e.g. a tempo used by the voices and by a delay) gets a single host parameter
    // driving both zones. The saved state (fStateUI) keeps the combined paths.
    fVoiceDSP->buildUserInterface(&fParameterUI);
    fEffectDSP->buildUserInterface(&fParameterUI);
#else
    fDSP->buildUserInterface(&fParameterUI);
#endif
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fDSP->instanceResetUserInterface();
    }
#endif
    
#if defined(FAUST_PRESETS)
    // Once the host parameters exist, so that preset names can be checked against them
    loadPrograms();
#endif
    
    startTimerHz(25);
}

juce::AudioProcessor::BusesProperties FaustPlugInAudioProcessor::getBusesProperties()
{
    if (juce::PluginHostType::getPluginLoadedAs() == wrapperType_Standalone) {
        if (FAUST_INPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::canonicalChannelSet(std::min<int>(2, FAUST_OUTPUTS)), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::canonicalChannelSet(std::min<int>(2, FAUST_INPUTS)), true)
            .withOutput("Output", juce::AudioChannelSet::canonicalChannelSet(std::min<int>(2, FAUST_OUTPUTS)), true);
        }
    } else {
        if (FAUST_INPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::canonicalChannelSet(FAUST_OUTPUTS), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::canonicalChannelSet(FAUST_INPUTS), true)
            .withOutput("Output", juce::AudioChannelSet::canonicalChannelSet(FAUST_OUTPUTS), true);
        }
    }
}

void FaustPlugInAudioProcessor::timerCallback()
{
    GUI::updateAllGuis();
}

//==============================================================================
const juce::String FaustPlugInAudioProcessor::getName() const
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
    return fTailLength;
}

#if defined(FAUST_PRESETS)

// Parse gFaustPresets: { "name": { "control": value, ... }, ... }. A control is named by
// the ID of its host parameter (the Faust shortname) or by its label.
void FaustPlugInAudioProcessor::loadPrograms()
{
    fPrograms.push_back({ "Default", {} });
    juce::var presets = juce::JSON::parse(juce::String::fromUTF8(gFaustPresets));
    juce::DynamicObject* object = presets.getDynamicObject();
    if (!object) {
        std::cerr << "ERROR : the presets given to faust2juce -presets are not a JSON object" << std::endl;
        return;
    }
    for (const auto& preset : object->getProperties()) {
        FaustProgram program { preset.name.toString(), {} };
        if (juce::DynamicObject* values = preset.value.getDynamicObject()) {
            for (const auto& value : values->getProperties()) {
                if (!findParameter(value.name.toString())) {
                    std::cerr << "WARNING : preset '" << program.fName << "' sets '" << value.name.toString()
                              << "', which is not a control" << std::endl;
                }
                program.fValues[value.name.toString()] = float(value.value);
            }
        }
        fPrograms.push_back(program);
    }
}

juce::RangedAudioParameter* FaustPlugInAudioProcessor::findParameter(const juce::String& name)
{
    for (auto* parameter : getParameters()) {
        if (auto* ranged = dynamic_cast<juce::RangedAudioParameter*>(parameter)) {
            if (ranged->getParameterID() == name || ranged->getName(1024) == name) return ranged;
        }
    }
    return nullptr;
}

int FaustPlugInAudioProcessor::getNumPrograms()
{
    return int(fPrograms.size());
}

int FaustPlugInAudioProcessor::getCurrentProgram()
{
    return fCurrentProgram;
}

// Recall a program completely: the controls it does not name go back to their default
// value, so that nothing is left over from the previous sound. Selecting the current
// program again does nothing, since some hosts do so right after restoring a session,
// which would overwrite the restored values.
void FaustPlugInAudioProcessor::setCurrentProgram (int index)
{
    if (index < 0 || index >= int(fPrograms.size()) || index == fCurrentProgram) return;
    fCurrentProgram = index;
    const auto& values = fPrograms[size_t(index)].fValues;
    for (auto* parameter : getParameters()) {
        if (auto* ranged = dynamic_cast<juce::RangedAudioParameter*>(parameter)) {
            auto it = values.find(ranged->getParameterID());
            if (it == values.end()) it = values.find(ranged->getName(1024));
            ranged->setValueNotifyingHost((it != values.end()) ? ranged->convertTo0to1(it->second) : ranged->getDefaultValue());
        }
    }
    updateHostDisplay(juce::AudioProcessor::ChangeDetails().withProgramChanged(true));
}

const juce::String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return (index >= 0 && index < int(fPrograms.size())) ? fPrograms[size_t(index)].fName : juce::String();
}

#else

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

const juce::String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return juce::String();
}

#endif

void FaustPlugInAudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

bool FaustPlugInAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return sizeof(FAUSTFLOAT) == 8;
}

//==============================================================================
void FaustPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if (fLatency.isDeclared()) {
        setLatencySamples(fLatency.getFrames(sampleRate));
    }

#ifdef JUCE_POLY
    mydsp::classInit(int(sampleRate));
    fSynth->setCurrentPlaybackSampleRate (sampleRate);
#else
    
    // Setting the DSP control values has already been done
    // by 'buildUserInterface(&fStateUI)', using the saved values or the default ones.
    // What has to be done to finish the DSP initialization is done now.
    mydsp::classInit(int(sampleRate));
#ifdef POLY2
    // The effect has its own static tables, initialized before instance constants.
    effect::classInit(int(sampleRate));
#endif
    fDSP->instanceConstants(int(sampleRate));
    fDSP->instanceClear();
    
    // Builds the DSP adapters outside the audio thread for the expected configuration;
    // process rebuilds them if the host finally uses another one
    if (isUsingDoublePrecision()) {
        fHostAdapter.prepare<double>(fDSP.get(), getTotalNumInputChannels(), getTotalNumOutputChannels());
    } else {
        fHostAdapter.prepare<float>(fDSP.get(), getTotalNumInputChannels(), getTotalNumOutputChannels());
    }
    
#endif
#ifdef MAGIC_LEVEL_SOURCE
    magicState.prepareToPlay(sampleRate, samplesPerBlock);
    fOutputMeter->setupSource(getMainBusNumOutputChannels(), sampleRate, 500, 200);
#endif
#if defined(FAUST_CUSTOM_EDITOR)
    // The custom editor bridge can size its buffers and reset its measurements
    fEditorBridge.prepare(sampleRate, samplesPerBlock, fNumVoices);
#endif
}

bool FaustPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    /*
        Any number of input channels, and any number of output channels up to the DSP outputs:
        the DSP adapts to fewer channels with a dsp_adapter (see FaustHostAdapter). More output
        channels are refused, since the DSP would leave them unwritten: the host then routes
        the DSP outputs itself, as it does for the CLAP plugin. FaustHostAdapter still clears
        such channels, should a host use them anyway (and the standalone, whose channels are
        those of the audio device).
        See https://github.com/grame-cncm/faust/issues/1392
    */
#ifdef JUCE_POLY
    const int dsp_outputs = FAUST_OUTPUTS;
#else
    // The DSP actually computed: with -effect, the outputs of the effect
    const int dsp_outputs = fDSP ? fDSP->getNumOutputs() : FAUST_OUTPUTS;
#endif
    return layouts.getMainOutputChannels() <= dsp_outputs;
}

template <typename FloatType>
void FaustPlugInAudioProcessor::process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
#if defined(FAUST_CUSTOM_EDITOR)
    // Before the DSP sees the MIDI events: the bridge can add notes from the editor
    fEditorBridge.processMidi(midiMessages, buffer.getNumSamples());
#endif
    
#ifdef JUCE_POLY
    // The voices are added to the output channels: clear those that do not carry an input,
    // since the host does not guarantee their content
    for (int chan = getTotalNumInputChannels(); chan < getTotalNumOutputChannels(); chan++) {
        buffer.clear(chan, 0, buffer.getNumSamples());
    }
    fSynth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
#else
#if defined(MIDICTRL)
    // Read MIDI input events from midiMessages
    fMIDIHandler->decodeBuffer(midiMessages);
    // Then write MIDI output events to midiMessages
    fMIDIHandler->encodeBuffer(midiMessages);
#endif
    // Adapts the DSP to the sample format and the channel counts of 'buffer'
    fHostAdapter.compute(fDSP.get(), buffer, 0, buffer.getNumSamples(), getTotalNumInputChannels(), getTotalNumOutputChannels());
#endif
    
#if defined(FAUST_CUSTOM_EDITOR)
    // Once the block is computed: the bridge can analyse the output for the editor
    fEditorBridge.processAudio(buffer, getNumActiveVoices());
#endif
}

//==============================================================================
#ifndef PLUGIN_MAGIC
bool FaustPlugInAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FaustPlugInAudioProcessor::createEditor()
{
#if defined(FAUST_CUSTOM_EDITOR)
    return createFaustEditor(*this, fEditorBridge);
#else
    return new FaustPlugInAudioProcessorEditor (*this);
#endif
}

//==============================================================================
void FaustPlugInAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    fStateUI.getStateInformation(destData);
#if defined(FAUST_PRESETS)
    // The current program follows an empty path, where the JuceStateUI reader stops:
    // states written with presets can still be read by plugins built without them
    juce::MemoryOutputStream stream(destData, true);
    stream.writeString("");
    stream.writeString("program");
    stream.writeInt(fCurrentProgram);
#endif
}

void FaustPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    fStateUI.setStateInformation(data, sizeInBytes);
#if defined(FAUST_PRESETS)
    // Skip the (path, value) pairs written by JuceStateUI up to the empty path, then read
    // the current program, absent from states written without presets
    juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    while (!stream.isExhausted() && stream.readString().isNotEmpty()) {
        stream.skipNextBytes(sizeof(FAUSTFLOAT));
    }
    if (!stream.isExhausted() && stream.readString() == "program") {
        fCurrentProgram = juce::jlimit(0, int(fPrograms.size()) - 1, stream.readInt());
    }
#endif
}
#elif defined(FAUST_PRESETS)
// Property of the PluginGuiMagic ValueTree that holds the current program
static const juce::Identifier gFaustProgramID("faustProgram");

void FaustPlugInAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Set just before saving, as PluginGuiMagic does for the parameter values
    magicState.getValueTree().setProperty(gFaustProgramID, fCurrentProgram, nullptr);
    foleys::MagicProcessor::getStateInformation(destData);
}

void FaustPlugInAudioProcessor::postSetStateInformation()
{
    // The restore has replaced the properties of the ValueTree: the program is absent
    // from states written without presets, which then keep the current program
    const juce::var program = magicState.getValueTree().getProperty(gFaustProgramID);
    if (!program.isVoid()) {
        fCurrentProgram = juce::jlimit(0, int(fPrograms.size()) - 1, int(program));
    }
}
#endif
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustPlugInAudioProcessor();
}

//==============================================================================
#if !defined(PLUGIN_MAGIC) && !defined(FAUST_CUSTOM_EDITOR)
FaustPlugInAudioProcessorEditor::FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor& p)
: juce::AudioProcessorEditor (&p), processor (p)
{
#ifdef JUCE_POLY
    p.fSynth->buildUserInterface(&fJuceGUI);
#else
    p.fDSP->buildUserInterface(&fJuceGUI);
#endif
    
    addAndMakeVisible(fJuceGUI);
    // Receive the clicks made on the widgets too, for the context menu
    fJuceGUI.addMouseListener(this, true);
    
    juce::Rectangle<int> recommendedSize = fJuceGUI.getSize();
    setSize (recommendedSize.getWidth(), recommendedSize.getHeight());
}

void FaustPlugInAudioProcessorEditor::mouseDown (const juce::MouseEvent& e)
{
    if (!e.mods.isPopupMenu()) return;
    juce::PopupMenu menu;
    menu.addItem(1, "Copy settings as a faust2juce -presets entry");
    menu.addSeparator();
    // The file used last, to add a series of presets without choosing it again
    const juce::File file = processor.fPresetsFile;
    if (file != juce::File()) {
        menu.addItem(2, "Add settings to " + file.getFileName() + "...");
    }
    menu.addItem(3, "Add settings to a new presets file...");
    menu.addItem(4, "Add settings to an existing presets file...");
    juce::Component::SafePointer<FaustPlugInAudioProcessorEditor> editor(this);
    menu.showMenuAsync(juce::PopupMenu::Options(), [editor, file](int result) {
        if (editor == nullptr) return;
        switch (result) {
            case 1: juce::SystemClipboard::copyTextToClipboard(faustPresetJSON(editor->processor, "Preset")); break;
            case 2: editor->askPresetName(file, false); break;
            case 3: editor->choosePresetsFile(true); break;
            case 4: editor->choosePresetsFile(false); break;
            default: break;
        }
    });
}

// Choose the presets file: a new one (create), whose previous content will be replaced,
// or an existing one, to which the preset will be added
void FaustPlugInAudioProcessorEditor::choosePresetsFile(bool create)
{
    juce::File folder = (processor.fPresetsFile != juce::File())
        ? processor.fPresetsFile.getParentDirectory()
        : juce::File::getSpecialLocation(juce::File::userDocumentsDirectory);
    juce::File start = create ? folder.getChildFile(processor.getName() + "-presets.json") : folder;
    fPresetsChooser = std::make_unique<juce::FileChooser>(create ? "New presets file" : "Presets file to add to",
                                                          start, "*.json");
    int flags = juce::FileBrowserComponent::canSelectFiles;
    flags |= create ? (juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting)
                    : juce::FileBrowserComponent::openMode;
    juce::Component::SafePointer<FaustPlugInAudioProcessorEditor> editor(this);
    fPresetsChooser->launchAsync(flags, [editor, create](const juce::FileChooser& chooser) {
        juce::File file = chooser.getResult();
        if (editor != nullptr && file != juce::File()) {
            editor->askPresetName(file, create);
        }
    });
}

// Ask the name of the preset, "Preset <n>" by default, n following the presets of the file,
// and confirm before replacing a preset of the same name
void FaustPlugInAudioProcessorEditor::askPresetName(const juce::File& file, bool create)
{
    juce::var presets = juce::var(new juce::DynamicObject());
    if (!create) {
        juce::String error = faustReadPresetsFile(file, presets);
        if (error.isNotEmpty()) {
            showPresetError(error);
            return;
        }
    }
    int count = presets.getDynamicObject()->getProperties().size();
    fPresetNameDialog = std::make_unique<juce::AlertWindow>("Add preset", "Name of the preset in " + file.getFileName() + ":",
                                                            juce::MessageBoxIconType::NoIcon, this);
    fPresetNameDialog->addTextEditor("name", "Preset " + juce::String(count + 1));
    fPresetNameDialog->addButton("Add", 1, juce::KeyPress(juce::KeyPress::returnKey));
    fPresetNameDialog->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));
    juce::Component::SafePointer<FaustPlugInAudioProcessorEditor> editor(this);
    fPresetNameDialog->enterModalState(true, juce::ModalCallbackFunction::create([editor, file, create, presets](int result) {
        if (editor == nullptr) return;
        // The dialog is kept until the next use: it is still running this callback
        editor->fPresetNameDialog->setVisible(false);
        if (result != 1) return;
        juce::String name = editor->fPresetNameDialog->getTextEditorContents("name").trim();
        if (name.isEmpty()) {
            editor->showPresetError("A preset needs a name.");
        } else if (presets.getDynamicObject()->hasProperty(name)) {
            editor->fPresetReplaceDialog = std::make_unique<juce::AlertWindow>("Replace preset",
                file.getFileName() + " already has a preset named \"" + name + "\". Replace it?",
                juce::MessageBoxIconType::QuestionIcon, editor.getComponent());
            editor->fPresetReplaceDialog->addButton("Replace", 1, juce::KeyPress(juce::KeyPress::returnKey));
            editor->fPresetReplaceDialog->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));
            editor->fPresetReplaceDialog->enterModalState(true, juce::ModalCallbackFunction::create([editor, file, name](int answer) {
                if (editor == nullptr) return;
                editor->fPresetReplaceDialog->setVisible(false);
                if (answer == 1) editor->addPreset(file, name, false);
            }));
        } else {
            editor->addPreset(file, name, create);
        }
    }));
}

// Write the current settings as the preset name of file, emptied first if it is a new file,
// which then becomes the file of the "Add settings to <file>" menu item
void FaustPlugInAudioProcessorEditor::addPreset(const juce::File& file, const juce::String& name, bool create)
{
    if (create && !file.replaceWithText("")) {
        showPresetError("Cannot write " + file.getFullPathName());
        return;
    }
    juce::String error = faustAddPresetToFile(processor, name, file);
    if (error.isNotEmpty()) {
        showPresetError(error);
        return;
    }
    processor.fPresetsFile = file;
}

void FaustPlugInAudioProcessorEditor::showPresetError(const juce::String& message)
{
    juce::AlertWindow::showAsync(juce::MessageBoxOptions()
                                 .withIconType(juce::MessageBoxIconType::WarningIcon)
                                 .withTitle("Presets file")
                                 .withMessage(message)
                                 .withButton("OK")
                                 .withAssociatedComponent(this),
                                 std::function<void (int)>());
}

//==============================================================================
void FaustPlugInAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
}

void FaustPlugInAudioProcessorEditor::resized()
{
    fJuceGUI.setBounds(getLocalBounds());
}

#endif
// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
