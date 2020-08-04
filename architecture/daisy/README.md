# faust2daisy

The **faust2daisy** tool compiles a Faust DSP program in a folder containing the C++ source code and a Makefile to compile it.  

`faust2daisy [-patch] [-midi] [-nvoices <num>] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-patch : to compile for 4 ins/outs Patch`
- `-midi to activate MIDI control`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`

The generated folder has to be moved in the *DaisyExamples/seed* folder and compiled from there.
