# faust2juce

## How to use

faust2juce is used with the following command : 

`faust2juce [-poly] [-midi] [-osc] file.dsp` 

It will create a folder named with the dsp file name, containing a .jucer file and a Source folder, with the Main.cpp and the MainComponent.h that Juce uses
In order for it to be ready to use, without changing the Juce modules path, you should put it into the "examples" folder of the Juce git folder.

## Options

There are those options available at this moment for faust2juce : 

`-poly` 	: Produce a polyphonic self-contained DSP, ready to be used with MIDI events
`-midi`	: Activate MIDI control
`-osc`   	: Activate OSC control
`-help` 	: Show the different options available

Some others options will be added later, still in development...

