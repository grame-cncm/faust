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

#include "JuceLibraryCode/JuceHeader.h"

#include "faust/dsp/timed-dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/misc.h"

#include "faust/gui/APIUI.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/JuceGUI.h"
#include "faust/gui/MidiUI.h"

#include <math.h>
#include <algorithm>

using std::max;
using std::min;

#if defined(OSCCTRL)
	#include "faust/gui/JuceOSCUI.h"
#endif //OSCCTRL

#if defined(MIDICTRL)
	#include "faust/midi/juce-midi.h"
#endif //MIDICTRL

#include "faust/dsp/poly-dsp.h"

#if defined(POLY2)
#include "faust/dsp/dsp-combiner.h"
#include "dsp_effect.cpp"
#endif //POLY POLY2

<<includeIntrinsic>>

<<includeclass>>

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

struct MyMeta : public Meta, public std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    const std::string get(const char* key, const char* def)
    {
        if (this->find(key) != this->end()) {
            return (*this)[key];
        } else {
            return def;
        }
    }
};

static void analyseMeta(bool& midi_sync, int& nvoices)
{
    mydsp* tmp_dsp = new mydsp();
    
    JSONUI jsonui;
    tmp_dsp->buildUserInterface(&jsonui);
    std::string json = jsonui.JSON();
    midi_sync = ((json.find("midi") != std::string::npos) &&
                 ((json.find("start") != std::string::npos) ||
                  (json.find("stop") != std::string::npos) ||
                  (json.find("clock") != std::string::npos)));
    
#if defined(NVOICES) && NVOICES!=NUM_VOICES
    nvoices = NVOICES;
#else
    MyMeta meta;
    tmp_dsp->metadata(&meta);
    std::string numVoices = meta.get("nvoices", "0");
    nvoices = atoi(numVoices.c_str());
    if (nvoices < 0) nvoices = 0;
#endif
    
    delete tmp_dsp;
}

class MainContentComponent : public AudioAppComponent, private Timer
{
    public:
   
        MainContentComponent()
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

            addAndMakeVisible(juceGUI);
            
            fDSP->buildUserInterface(&juceGUI);
            
        #if defined(MIDICTRL)
            fMIDIHandler = new juce_midi();
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
            
            recommendedSize = juceGUI.getSize();
            setSize (recommendedSize.getWidth(), recommendedSize.getHeight());

            // specify the number of input and output channels that we want to open
            setAudioChannels (fDSP->getNumInputs(), fDSP->getNumOutputs());
            startTimerHz(25); 
        }

        ~MainContentComponent()
        {
            shutdownAudio();
        }
        
        void timerCallback() override
        {
            GUI::updateAllGuis();
        }
         
        //==============================================================================
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
        {
            AudioIODevice* device = deviceManager.getCurrentAudioDevice();
            const BigInteger activeInputChannels = device->getActiveInputChannels();
            const BigInteger activeOutputChannels = device->getActiveOutputChannels();
            const int maxInputChannels = activeInputChannels.getHighestBit() + 1;
            const int maxOutputChannels = activeOutputChannels.getHighestBit() + 1;
            
            // Possibly adapt DSP...
            if (fDSP->getNumInputs() > maxInputChannels || fDSP->getNumOutputs() > maxOutputChannels) {
                fDSP = new dsp_adapter(fDSP.release(), maxInputChannels, maxOutputChannels, 4096);
            }
            
            fDSP->init(int(sampleRate));
        }

        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
        {
            AVOIDDENORMALS;
            
            const float* inputs[fDSP->getNumInputs()];
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                inputs[i] = bufferToFill.buffer->getReadPointer(i, bufferToFill.startSample);
            }
            
            float* outputs[fDSP->getNumOutputs()];
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputs[i] = bufferToFill.buffer->getWritePointer(i, bufferToFill.startSample);
            }
            
            fDSP->compute(bufferToFill.numSamples, (float**)inputs, outputs);
        }

        void releaseResources() override
        {
            
        }

        void paint (Graphics& g) override
        {
            g.fillAll (Colour (Colours::white));
        }

        void resized() override
        {
            juceGUI.setBounds(getLocalBounds());
        }

        Rectangle<int> getMinSize(){
            return Rectangle<int>(0, 0, jmin(recommendedSize.getWidth(), screenWidth), jmin(recommendedSize.getHeight(), screenHeight));
        }

        Rectangle<int> getRecommendedSize(){
            return recommendedSize;
        }

    private:
    
    #if defined(MIDICTRL)
        ScopedPointer<juce_midi> fMIDIHandler;
        ScopedPointer<MidiUI> fMIDIUI;
    #endif
    
    #if defined(OSCCTRL)
        ScopedPointer<JuceOSCUI> fOSCUI;
    #endif
        
        JuceGUI juceGUI;
        
        ScopedPointer<dsp> fDSP;
    
        Rectangle<int> recommendedSize;
        Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
        int screenWidth = r.getWidth();
        int screenHeight = r.getHeight();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
MainContentComponent* createMainContentComponent()     { return new MainContentComponent(); }
