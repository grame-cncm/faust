# faust2audiokit

The **faust2audiokit** tool transforms a Faust DSP program into a fully working [AudioKit](https://audiokit.io) plugin. The result can be a monophonic DSP or a MIDI controllable polyphonic one (when the DSP describes an instrument, following the `freq, gain, gate` [parameter naming convention](https://faust.grame.fr/doc/manual/index.html#midi-polyphony-support)). 

## How to use

**faust2audiokit** is used with the following command:

`faust2audiokit [-midi] [-nvoices <num>] [additional Faust options (-vec -vs 8...)] <file.dsp>` 

Here are the available options:

- `-midi` : activates MIDI control
- `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI

The result is a folder containing `FaustDSP.hpp` and `FaustDSP.mm` files including the Faust generated C++ class for the DSP, to be added and compiled in the AudioKit framework. Note that the generated C++ class takes the name of the compiled DSP, so that several different DSP can be generated and used in a same project. 
