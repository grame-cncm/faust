# faust2soul

**faust2soul** tool compiles a Faust DSP program to SOUL source code and patch as a monophonic DSP or possibly a MIDI controllable polyphonic one (when the DSP describes an instrument, following the `freq, gain, gate` [parameter naming convention](https://faust.grame.fr/doc/manual/index.html#midi-polyphony-support)). The resulting SOUL code can be played using the 'soul' runtime  (only available for early developers for now, ask Cesare or Jules...), or by pasting and compiling the code in the [SOUL Playground](https://soul.dev/playground):

`faust2soul [-nvoices <num>] [-effect auto|<effect.dsp>] [-midi] [-play] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`
- `-effect <effect.dsp> to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI`
- `-effect auto to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI`
- `-midi to activate MIDI control`
- `-play to start the 'soul' runtime with the generated SOUL file`

So for instance:

- `faust2soul noise.dsp` to produce two noise.soul and noise.soulpatch files
- `faust2soul -play osc.dsp` to produce two osc.soul  and osc.soulpatch files and play the osc.soulpatch
- `faust2soul -midi -nvoices 16 -play clarinetMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument as two clarinetMIDI.soul and clarinetMIDI.soulpatch files and play the clarinetMIDI.soulpatch
- `faust2soul -midi -nvoices 16 -effect freeverb.dsp -play violinMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument with a global effect as two violinMIDI.soul and violinMIDI.soulpatch files and play the violinMIDI.soulpatch


# soul-faust-player 

**soul-faust-player** tool loads a SOUL patch or an hybrid Faust/SOUL code file, wraps it as a Faust DSP object, and runs it in the Faust runtime audio/control machinery. 

Here are the available options:

- `-hybrid to load and execute an hybrid Faust/SOUL file`

So for instance:

- `faust2soul clarinetMIDI.dsp` to produce two clarinetMIDI.soul and clarinetMIDI.soulpatch files
- `soul-faust-player clarinetMIDI.soulpatch` to run the clarinetMIDI.soulpatch

Or:

- `soul-faust-player -hybrid hybrid-test1.soul` to run an hybrid `hybrid-test1.soul` file containing both Faust and SOUL sections. Two `hybrid.soul` (containing the original SOUL sections and the Faust => SOUL generated sections) and an `hybrid.soulpatch` files will be generated in the process.

