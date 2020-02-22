# faust2juce

**faust2juce** transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code, which contains interface parameters with the following `freq`, `gain` and `gate` names. The metadata **declare nvoices "8";** kind of line with a desired value of voices can be added in the source code. See [Creating polyphonic instruments](http://faust.grame.fr/news/2016/01/13/polyphonic-instruments.html). 

Polyphonic synthesiser can be created using JUCE Synthesiser model or Faust own polyphonic architecture file (using the 'mydsp_poly' class). The `-jsynth` parameter has to be used to choose the JUCE model.

**faust2juce** uses several UI interfaces, subclasses of the base UI class (defined in the architecture/faust/gui/UI.h header) to link to various JUCE components:

 - `JuceGUI.h`: contains the main JuceGUI class (and additional helpers classes) to display Faust UI components (buttons, sliders, bargraphs...) using JUCE widgets
 - `JuceOSCUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE OSC messaging system, allowing to control them in both directions
 - `JuceParameterUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) with the JUCE AudioParameterFloat/AudioParameterFloat classes
 - `JuceStateUI.h`: allows to save/restore Faust UI components (buttons, sliders, bargraphs...) values using the JUCE state management system (MemoryInputStream/MemoryOutputStream classes)

Some additional files are needed for soundfile and MIDI support:

- `JuceReader.h`: contains code to load audio files using JUCE code, that will be used when the `soundfile` primitive is used in the Faust code
- `juce-midi.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE MIDI messaging system (for inputs and outputs) 

Two different achitecture files will be used to glue the previously described files with the Faust C++ generated class: 
- `juce-plugin.cpp`: is used to create a JUCE plugin
- `juce-standalone.cpp`: is used to create a JUCE stanalone application

## How to use

**faust2juce** is used with the following command: 

`faust2juce [-standalone] [-nvoices <num>] [-effect auto|<effect.dsp>] [-jucemodulesdir <dir>] [-jsynth] [-midi] [-osc] [-llvm] [-soundfile] [additional Faust options (-vec -vs 8...)] file.dsp` 

By default it will create a plugin project, with a folder named with the dsp file name, containing a .jucer project with a FaustPluginProcessor.cpp file to be used by JUCE.

When using `-standalone` mode, it will create a standalone project, with a folder named with the dsp file name, containing a .jucer project with a FaustAudioApplication.cpp file to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can be generated. 

## Options

The following options are available: 

 - `-standalone` : to produce a standalone project, otherwise a plugin project is generated
 - `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
 - `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
 - `-effect auto` : to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC 
 - `-jucemodulesdir <folder>` : to set JUCE modules directory to `<folder>`, such as ~/JUCE/modules
 - `-jsynth` : to use JUCE polyphonic Synthesizer instead of Faust polyphonic code
 - `-midi` : activates MIDI control
 - `-osc` : activates OSC control
 - `-llvm` : to use the LLVM compilation chain (OSX and Linux for now)
 - `-soundfile` : when compiling DSP using 'soundfile' primitive, to add needed resources
 - `-help or -h` : shows the different options 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2juce**, like `-cn name` to give a name to the generated DSP class, or `-vec -lv 1 -lv 1` to compile in vector mode...

