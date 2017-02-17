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

class FaustComponent : public AudioAppComponent, private Timer
{
    public:
   
        FaustComponent()
        {
            bool midi_sync = false;
            int nvoices = 1;
            bool group = true;
            
            analyseMeta(midi_sync, nvoices);
            
        #ifdef POLY2
            std::cout << "Started with " << nvoices << " voices\n";
                
        #if MIDICTRL
            if (midi_sync) {
                fDSP = new timed_dsp(new dsp_sequencer(new mydsp_poly(new mydsp(), nvoices, true, group), new dsp_effect()));
            } else {
                fDSP = new dsp_sequencer(new mydsp_poly(new mydsp(), nvoices, true, group), new dsp_effect());
            }
        #else
            fDSP = new dsp_sequencer(new mydsp_poly(new mydsp(), nvoices, false, group), new dsp_effect());
        #endif
                
        #else
            if (nvoices > 1) {
                std::cout << "Started with " << nvoices << " voices\n";
        #if MIDICTRL
                if (midi_sync) {
                    fDSP = new timed_dsp(new mydsp_poly(new mydsp(), nvoices, true, group));
                } else {
                    fDSP = new mydsp_poly(new mydsp(), nvoices, true, group);
                }
        #else
                fDSP = new mydsp_poly(new mydsp(), nvoices, false, group);
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

        ~FaustComponent()
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

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustComponent)
};

// (This function is called by the app startup code to create our main component)
FaustComponent* createFaustComponent()     { return new FaustComponent(); }

//==============================================================================
class FaustAudioApplication : public JUCEApplication
{
    
    public:
        //==============================================================================
        FaustAudioApplication() {}
        
        const String getApplicationName() override       { return ProjectInfo::projectName; }
        const String getApplicationVersion() override    { return ProjectInfo::versionString; }
        bool moreThanOneInstanceAllowed() override       { return true; }
        
        //==============================================================================
        void initialise (const String& commandLine) override
        {
            // This method is where you should put your application's initialisation code..
            mainWindow = new MainWindow (getApplicationName());
        }
        
        void shutdown() override
        {
            // Add your application's shutdown code here..
            
            mainWindow = nullptr; // (deletes our window)
        }
        
        //==============================================================================
        void systemRequestedQuit() override
        {
            // This is called when the app is being asked to quit: you can ignore this
            // request and let the app carry on running, or call quit() to allow the app to close.
            quit();
        }
        
        void anotherInstanceStarted (const String& commandLine) override
        {
            // When another instance of the app is launched while this one is running,
            // this method is invoked, and the commandLine parameter tells you what
            // the other instance's command-line arguments were.
        }
        
        //==============================================================================
        /*
         This class implements the desktop window that contains an instance of
         our FaustComponent class.
         */
        
        class myViewport : public Viewport
        {
        public:
            myViewport(String name, int w, int h, int rW, int rH): Viewport(name), minWidth(w), minHeight(h), recommendedWidth(rW), recommendedHeight(rH)
            {
                addAndMakeVisible(tooltipWindow);
            }
            
            virtual void resized() override {
                Viewport::resized();
                getBounds().getWidth() < minWidth ? ((minWidth < recommendedWidth) ? width = minWidth
                                                     : width = recommendedWidth)
                : width = getBounds().getWidth();
                getBounds().getHeight() < minHeight ? ((minHeight < recommendedHeight) ? height = minHeight
                                                       : height = recommendedHeight)
                : height = getBounds().getHeight();
                
            #if JUCE_IOS || JUCE_ANDROID
                currentAreaChanged(width, height);
            #else
                getViewedComponent()->setBounds(Rectangle<int>(0, 0, width, height));
            #endif
            }
            
            void currentAreaChanged (int w, int h) {
                getViewedComponent()->setBounds(0, 0, jmax(getParentWidth(), w), jmax(getParentHeight(), h));
                setSize(getParentWidth(), getParentHeight());
            }
            
        private:
            int minWidth, minHeight;
            int recommendedWidth, recommendedHeight;
            int width, height;
            TooltipWindow tooltipWindow;
            int j = 0;
        };
        
        class MainWindow : public DocumentWindow
        {
        public:
            MainWindow (String name) : DocumentWindow (name,
                                                       Colours::lightgrey,
                                                       DocumentWindow::allButtons)
            {
                setUsingNativeTitleBar (true);
                
            #if JUCE_IOS || JUCE_ANDROID
                setFullScreen(true);
            #endif
                
                FaustComponent* fWindow = createFaustComponent();
                int minWidth  = fWindow->getMinSize().getWidth();
                int minHeight = fWindow->getMinSize().getHeight();
                int recomWidth = fWindow->getRecommendedSize().getWidth();
                int recomHeight = fWindow->getRecommendedSize().getHeight();
                
                fViewport = new myViewport(name, minWidth, minHeight, recomWidth, recomHeight);
                fViewport->setViewedComponent(fWindow);
                fViewport->setSize(minWidth, minHeight);
                
                setContentOwned(fViewport, true);
                centreWithSize (getWidth(), getHeight());
                setResizable (true, false);
                setVisible(true);
            }
            
            void closeButtonPressed() override
            {
                // This is called when the user tries to close this window. Here, we'll just
                // ask the app to quit when this happens, but you can change this to do
                // whatever you need.
                JUCEApplication::getInstance()->systemRequestedQuit();
            }
            
            /* Note: Be careful if you override any DocumentWindow methods - the base
             class uses a lot of them, so by overriding you might break its functionality.
             It's best to do all your work in your content component instead, but if
             you really have to override any DocumentWindow methods, make sure your
             subclass also calls the superclass's method.
             */
            
        private:
            ScopedPointer<myViewport> fViewport;
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        };
        
    private:
        ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (FaustAudioApplication)

// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

