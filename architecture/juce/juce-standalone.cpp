/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016-2020 GRAME, Centre National de Creation Musicale
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

#include <algorithm>
#include <assert.h>

#if JUCE_WINDOWS
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1
#endif

#include "JuceLibraryCode/JuceHeader.h"

#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/MidiUI.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/JuceGUI.h"

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

<<includeIntrinsic>>

<<includeclass>>

class FaustComponent : public AudioAppComponent, private Timer
{
    public:
   
        FaustComponent()
        {
            bool midi_sync = false;
            int nvoices = 0;
            bool group = true;
            mydsp_poly* dsp_poly = nullptr;
            
            mydsp* tmp_dsp = new mydsp();
            MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
            delete tmp_dsp;
            
        #ifdef POLY2
            assert(nvoices > 0);
            std::cout << "Started with " << nvoices << " voices\n";
            dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
                
        #if MIDICTRL
            if (midi_sync) {
                fDSP = std::make_unique<timed_dsp>(new dsp_sequencer(dsp_poly, new effect()));
            } else {
                fDSP = std::make_unique<dsp_sequencer>(dsp_poly, new effect());
            }
        #else
            fDSP = std::make_unique<dsp_sequencer>(dsp_poly, new effect());
        #endif
                
        #else
            if (nvoices > 0) {
                std::cout << "Started with " << nvoices << " voices\n";
                dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, group);
                
        #if MIDICTRL
                if (midi_sync) {
                    fDSP = std::make_unique<timed_dsp>(dsp_poly);
                } else {
                    fDSP = std::make_unique<decorator_dsp>(dsp_poly);
                }
        #else
                fDSP = std::make_unique<decorator_dsp>(dsp_poly);
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

            addAndMakeVisible(fJuceGUI);
            fDSP->buildUserInterface(&fJuceGUI);
            
        #if defined(MIDICTRL)
            fMIDIHandler = std::make_unique<juce_midi>();
            fMIDIHandler->addMidiIn(dsp_poly);
            fMIDIUI = std::make_unique<MidiUI>(fMIDIHandler.get());
            fDSP->buildUserInterface(fMIDIUI.get());
            if (!fMIDIUI->run()) {
                std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
            }
        #endif
        
        #if defined(OSCCTRL)
            fOSCUI = std::make_unique<JuceOSCUI>("127.0.0.1", 5510, 5511);
            fDSP->buildUserInterface(fOSCUI.get());
            if (!fOSCUI->run()) {
                std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
            }
        #endif
            
        #if defined(SOUNDFILE)
            auto file = File::getSpecialLocation(File::currentExecutableFile)
                .getParentDirectory().getParentDirectory().getChildFile("Resources");
            fSoundUI = new SoundUI(file.getFullPathName().toStdString());
            // SoundUI has to be dispatched on all internal voices
            if (dsp_poly) dsp_poly->setGroup(false);
            fDSP->buildUserInterface(fSoundUI.get());
            if (dsp_poly) dsp_poly->setGroup(group);
        #endif
            
            recommendedSize = fJuceGUI.getSize();
            setSize (recommendedSize.getWidth(), recommendedSize.getHeight());

            // specify the number of input and output channels that we want to open
            setAudioChannels (fDSP->getNumInputs(), fDSP->getNumOutputs());
            startTimerHz(25); 
        }

        virtual ~FaustComponent()
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
                fDSP = std::make_unique<dsp_adapter>(fDSP.release(), maxInputChannels, maxOutputChannels, 4096);
            }
            
            fDSP->init(int(sampleRate));
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

        void paint (Graphics& g) override
        {
            g.fillAll (Colour (Colours::white));
        }

        void resized() override
        {
            fJuceGUI.setBounds(getLocalBounds());
        }

        juce::Rectangle<int> getMinSize()
        {
            return juce::Rectangle<int>(0, 0, jmin(recommendedSize.getWidth(), screenWidth), jmin(recommendedSize.getHeight(), screenHeight));
        }

        juce::Rectangle<int> getRecommendedSize()
        {
            return recommendedSize;
        }

    private:
    
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
    
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
    
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
        
        JuceGUI fJuceGUI;
        
        std::unique_ptr<dsp> fDSP;
    
        juce::Rectangle<int> recommendedSize;
        juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
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
            mainWindow = std::make_unique<MainWindow>(getApplicationName());
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
            
                myViewport(String name, int w, int h, int rW, int rH):
                Viewport(name),
                minWidth(w),
                minHeight(h),
                recommendedWidth(rW),
                recommendedHeight(rH)
                {}
                
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
                    getViewedComponent()->setBounds(juce::Rectangle<int>(0, 0, width, height));
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
                    
                    fViewport = std::make_unique<myViewport>(name, minWidth, minHeight, recomWidth, recomHeight);
                    fViewport->setViewedComponent(fWindow);
                    fViewport->setSize(minWidth, minHeight);
                    
                    setContentOwned(fViewport.get(), true);
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
            
                std::unique_ptr<myViewport> fViewport;
                JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        };
        
    private:
    
        std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (FaustAudioApplication)

// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

