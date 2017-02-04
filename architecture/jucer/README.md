# faust2juce

## How to use

faust2juce is used with the following command : 

`faust2juce [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-osc] file.dsp` 

It will create a folder named with the dsp file name, containing a .jucer file and a Source folder, with the Main.cpp and the MainComponent.h that Juce uses
In order for it to be ready to use, without changing the Juce modules path, you should put it into the "examples" folder of the Juce git folder.

## Options

There are those options available at this moment for faust2juce : 

 - `-nvoices <num>`         : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
 - `-effect <effect.dsp>`   : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
 - `-midi`                  : activate MIDI control
 - `-osc`                   : activate OSC control
 - `-help`                  : show the different options 

Some others options will be added later, still in development...

