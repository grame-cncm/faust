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

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/
 
#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/dsp/proxy-dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/misc.h"

#include "faust/gui/APIUI.h"
#include "faust/audio/dummy-audio.h"
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

#if defined(POLY) || defined(POLY2)
	#include "faust/dsp/poly-dsp.h"
	#include "faust/dsp/dsp-combiner.h"
#endif //POLY POLY2

<<includeIntrinsic>>

<<includeclass>>

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;


class MainContentComponent   : public AudioAppComponent, private Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible(juceGUI);
        fDSP = new mydsp();
        
        //-----------------------------------------------
        // Polyphonic DSP built using a single DSP voice
        //-----------------------------------------------
        
        #if defined(POLY) || defined(POLY2)
        	fDSP = new mydsp_poly(fDSP.release(), 32, true);
        #endif
        
        fDSP->buildUserInterface(&juceGUI);
        fDSP->buildUserInterface(&fAPIUI);
        
        #if defined(MIDICTRL)
        	fMIDIHandler = new juce_midi();
        	fMIDIUI = new MidiUI(fMIDIHandler);
        	fDSP->buildUserInterface(fMIDIUI);
        	fMIDIUI->run();
        #endif
        
        #if defined(OSCCTRL)
            fOSCUI = new JuceOSCUI("127.0.0.1", 5510, 5511);
        	fDSP->buildUserInterface(fOSCUI);
        	fOSCUI->run();
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
        g.fillAll (Colour (Colours::darkgrey));
    }

    void resized() override
    {
        std::cout<<std::endl<<"RESIZING"<<std::endl<<std::endl;
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
    
    Juce_GUI juceGUI;
    
    ScopedPointer<dsp> fDSP;
    APIUI fAPIUI;
	
    Rectangle<int> recommendedSize;
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    int screenWidth  = r.getWidth();
    int screenHeight = r.getHeight();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
MainContentComponent* createMainContentComponent()     { return new MainContentComponent(); }
