# faust2juce

faust2juce transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code, which contains interface parameters with the following `freq`, `gain` and `gate` names. The metadata **declare nvoices "8";** kind of line with a desired value of voices can be added in the source code. See [Creating polyphonic instruments] (http://faust.grame.fr/news/2016/01/13/polyphonic-instruments.html).

## How to use

faust2juce is used with the following command: 

`faust2juce [-standalone] [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-osc] file.dsp` 

By default it will create a plugin model project, with a folder named with the dsp file name, containing a .jucer project file with PluginProcessor.h,cpp and PluginEditor.h,cpp files to be used by JUCE.

When used `-standalone` mode, it will create a standalone model project, with a folder named with the dsp file name, containing a .jucer project file with Main.cpp and a MainComponent.h files to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can be generated. 

## Options

The following options are available: 

 - `-standalone`            : to produce a standalone project, otherwise a plugin project is generated
 - `-nvoices <num>`         : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
 - `-effect <effect.dsp>`   : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
 - `-midi`                  : activates MIDI control
 - `-osc`                   : activates OSC control
 - `-help or h`             : shows the different options 

Some others options will be added later, still in development...

