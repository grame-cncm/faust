# faust2juce

faust2juce transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can be possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code.

## How to use

faust2juce is used with the following command: 

`faust2juce [-plugin] [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-osc] file.dsp` 

When used in `-plugin` mode, it will create a folder named with the dsp file name, containing a .jucer file with a PluginProcessor.h,cpp and PluginEditor.h,cpp files to be used by JUCE.

When used without `-plugin` mode (= standalone mode), it will create a folder named with the dsp file name, containing a .jucer file with a Main.cpp and a MainComponent.h files to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can then be generated. 

## Options

The following options are available: 

 - `-plugin`                : to produce a plugin, otherwise a standalone application is generated
 - `-nvoices <num>`         : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
 - `-effect <effect.dsp>`   : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
 - `-midi`                  : activates MIDI control
 - `-osc`                   : activates OSC control
 - `-help or h`             : shows the different options 

Some others options will be added later, still in development...

