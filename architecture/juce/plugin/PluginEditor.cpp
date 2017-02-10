

#include "PluginProcessor.h"
#include "PluginEditor.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

//==============================================================================
FaustPlugInAudioProcessorEditor::FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (400, 300);
    
    addAndMakeVisible(juceGUI);
    
    p.fDSP->buildUserInterface(&juceGUI);
    
    recommendedSize = juceGUI.getSize();
    setSize (recommendedSize.getWidth(), recommendedSize.getHeight());
}

FaustPlugInAudioProcessorEditor::~FaustPlugInAudioProcessorEditor()
{
}

//==============================================================================
void FaustPlugInAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    /*
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("FaustPlugIn", getLocalBounds(), Justification::centred, 1);
    */
}

void FaustPlugInAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    juceGUI.setBounds(getLocalBounds());
}
