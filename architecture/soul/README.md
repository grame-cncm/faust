# faust2soul

The **faust2soul** tool compiles a Faust DSP program in a folder containing the SOUL source code and SOUL patch.  The result can be a monophonic DSP or a MIDI controllable polyphonic one (when the DSP describes an instrument, following the `freq, gain, gate` [parameter naming convention](https://faust.grame.fr/doc/manual/index.html#midi-polyphony-support)). The resulting SOUL code can be played using the *soul* program, or by pasting and compiling the code in the [SOUL Playground](https://soul.dev/playground):

`faust2soul [-nvoices <num>] [-effect auto|<effect.dsp>] [-midi] [-play] [additional Faust options (-cn foo -double...)] <file.dsp>`

Here are the available options:

- `-midi to activate MIDI control`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`
- `-effect <effect.dsp> to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI`
- `-effect auto to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI`
- `-juce to create a JUCE project`
- `-dsp to create a 'dsp' compatible subclass`
- `-play to start the 'soul' runtime with the generated SOUL patch`

So for instance:

- `faust2soul noise.dsp` to produce two noise.soul and noise.soulpatch files
- `faust2soul -play osc.dsp` to produce two osc.soul  and osc.soulpatch files and play the osc.soulpatch
- `faust2soul -midi -nvoices 16 -play clarinetMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument as two clarinetMIDI.soul and clarinetMIDI.soulpatch files and play the clarinetMIDI.soulpatch
- `faust2soul -midi -nvoices 16 -effect freeverb.dsp -play violinMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument with a global effect as two violinMIDI.soul and violinMIDI.soulpatch files and play the violinMIDI.soulpatch

# soul-faust-player 

The **soul-faust-player** tool loads a Faust DSP file, a SOUL patch or an hybrid Faust/SOUL code file, wraps it as a Faust DSP object, and runs it in the Faust runtime audio/control machinery. 

So for instance:

- `faust2soul clarinetMIDI.dsp` to produce the two `clarinetMIDI.soul` and `clarinetMIDI.soulpatch` files

Then:

- `soul-faust-player clarinetMIDI.dsp` to run the `clarinetMIDI.dsp` file (only containing Faust code)
- `soul-faust-player clarinetMIDI.soulpatch` to run the `clarinetMIDI.soulpatch` file

Or:

- `soul-faust-player clarinetMIDI.soul` to run the `clarinetMIDI.soul` file (only containing the SOUL code)
- `soul-faust-player hybrid-test1.soul` to run an hybrid `hybrid-test1.soul` file containing both Faust and SOUL sections. Two `hybrid.soul` (containing the original SOUL sections and the Faust => SOUL generated sections) and an `hybrid.soulpatch` files will be generated in the process.

# soul-faust-tester 

The **soul-faust-tester** tool allows to test DSP CPU usage of Faust and SOUL programs, dynamically compiling them, and running them in the Faust runtime or SOUL runtime. It measures the DSP CPU usage as MBytes/sec and % of audio bandwidth at 44.1 kHz.

`soul-faust-tester [-bs <frames>] [-control] [Faust options : any option (e.g. -vec -vs 8...)] foo.dsp|foo.soulpatch`

Here are the available options:

- `-bs <frames> to set the maximum buffer-size in frames`
- `control to update all controllers with random values at each cycle`

So for instance:

- `soul-faust-tester foo.dsp` to test 1) the Faust DSP code compiled to LLVM-IR and JITted to native code, then running in the Faust runtime, 2) the Faust DSP code compiled to SOUL, then compiled to LLVM-IR and JITted to native code, and running in the SOUL runtime.

- `soul-faust-tester foo.soulpatch` to test a SOUL patch compiled to LLVM-IR and JITted to native code, and running in the SOUL runtime.

