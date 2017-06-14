# faust2juce

faust2juce transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code, which contains interface parameters with the following `freq`, `gain` and `gate` names. The metadata **declare nvoices "8";** kind of line with a desired value of voices can be added in the source code. See [Creating polyphonic instruments](http://faust.grame.fr/news/2016/01/13/polyphonic-instruments.html). 

Polyphonic synthesiser can be created using JUCE Synthesiser model or Faust own polyphonic architecture file (using the 'mydsp_poly' class). The `-jsynth` parameter has to be used to choose the JUCE model.

faust2juce uses several UI interfaces, subclasses of the base UI class (defined in architecture/faust/gui/UI.h header) to link to various JUCE components:

 - `JuceGUI.h` : contains the main JuceGUI class (and additional helpers classes) to display Faust UI components (buttons, sliders, bargraphs...) using JUCE widgets
 - `JuceOSCUI.h` : allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE OSC messaging system, allowing to control them in both directions
 - `JuceParameterUI.h` : allows to link Faust UI components (buttons, sliders, bargraphs...) with the JUCE AudioParameterFloat/AudioParameterFloat classes
 - `JuceStateUI.h` : allows to save/restore Faust UI components (buttons, sliders, bargraphs...) values using the JUCE state management system (MemoryInputStream/MemoryOutputStream classes)


## How to use

faust2juce is used with the following command: 

`faust2juce [-standalone] [-nvoices <num>] [-effect <effect.dsp>] [-jsynth]  [-midi] [-osc] file.dsp` 

By default it will create a plugin project, with a folder named with the dsp file name, containing a .jucer project with a FaustPluginProcessor.cpp file to be used by JUCE.

When using `-standalone` mode, it will create a standalone project, with a folder named with the dsp file name, containing a .jucer project with a FaustAudioApplication.cpp file to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can be generated. 

## Options

The following options are available: 

 - `-standalone`            : to produce a standalone project, otherwise a plugin project is generated
 - `-nvoices <num>`         : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
 - `-effect <effect.dsp>`   : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC (available in Faust polyphonic model) 
 - `-jsynth`                : to use JUCE polyphonic Synthesizer instead of Faust polyphonic code
 - `-midi`                  : activates MIDI control
 - `-osc`                   : activates OSC control
 - `-help or -h`            : shows the different options 

Some others options will be added later, still in development...

