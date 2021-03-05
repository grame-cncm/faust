# faust2soul

The **faust2soul** tool compiles a Faust DSP program in a folder containing the SOUL source code and SOUL patch. The result can be a monophonic DSP or a MIDI controllable polyphonic one (when the DSP describes an instrument, following the `freq, gain, gate` [parameter naming convention](https://faust.grame.fr/doc/manual/index.html#midi-polyphony-support)). The resulting SOUL code can be played using the **soul** runtime, or by pasting and compiling the code in the [SOUL Playground](https://soul.dev/playground):

`faust2soul [-midi] [-nvoices <num>] [-effect auto|<effect.dsp>] [-juce] [-dsp] [-play] [additional Faust options (-cn foo -double...)] <file.dsp>`

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

`soul-faust-player <foo.dsp> (pure Faust code), <foo.soulpatch> (pure SOUL patch) or <foo.soul> (pure SOUL code or Faust/SOUL hybrid code)`

So for instance:

- `faust2soul clarinetMIDI.dsp` to produce the two `clarinetMIDI.soul` and `clarinetMIDI.soulpatch` files

Then:

- `soul-faust-player clarinetMIDI.dsp` to run the `clarinetMIDI.dsp` file (only containing Faust code)
- `soul-faust-player clarinetMIDI.soulpatch` to run the `clarinetMIDI.soulpatch` file

Or:

- `soul-faust-player clarinetMIDI.soul` to run the `clarinetMIDI.soul` file (only containing the SOUL code)
- `soul-faust-player hybrid-test1.soul` to run an hybrid `hybrid-test1.soul` file containing both Faust and SOUL sections. Two `hybrid.soul` (containing the original SOUL sections and the Faust => SOUL generated sections) and an `hybrid.soulpatch` files will be generated in the process.

# soul-faust-tester 

The **soul-faust-tester** tool allows to test DSP CPU usage of Faust and SOUL programs, dynamically compiling them, and running them in the Faust runtime or **soul** runtime. It measures the DSP CPU usage as MBytes/sec and % of audio bandwidth at 44.1 kHz.

`soul-faust-tester [-bs <frames>] [-control] [Faust options : any option (e.g. -vec -vs 8...)] <foo.dsp|foo.soulpatch>`

Here are the available options:

- `-bs <frames> to set the maximum buffer-size in frames`
- `-control to update all controllers with random values at each cycle`

So for instance:

- `soul-faust-tester foo.dsp` to test 1) the Faust DSP code compiled to LLVM-IR and JITted to native code, then running in the Faust runtime, 2) the Faust DSP code compiled to SOUL, then compiled to LLVM-IR and JITted to native code, and running in the **soul** runtime.

- `soul-faust-tester foo.soulpatch` to test a SOUL patch compiled to LLVM-IR and JITted to native code, and running in the **soul** runtime.

# soul-faust-editor

The **soul-faust-editor** tool loads an hybrid Faust/SOUL code file and compiles it in a SOUL patch each time the source file content changes. It can be used together with the **soul** runtime or any SOUL aware plugin to create a *Faust/SOUL => SOUL => executable code* edit loop. The SOUL generated files can be set using the`-o <output.soul>` option and are named `hybrid.soul` and  `hybrid.soulpatch` by default.

`soul-faust-editor [Faust options : any option (e.g. -ftz 1...)] <foo.soul> -o <output.soul>`

So for instance to setup a Faust/SOUL hybrid file edition session:

- `soul-faust-editor hybrid-test2.soul` to start editing an hybrid Faust/SOUL code
- `soul play hybrid.soulpatch` to play the SOUL dynamically generated `hybrid.soulpatch`

## Hybrid Faust/SOUL Syntax

A Faust block uses the following syntax:

 ```
faust Name
{
  ... Faust code...
}
 ```

It will be compiled in SOUL code as a `processor Name { ...SOUL code... } ` and inserted back in the resulting SOUL file. Here is a real example:

 ```
faust Osc
{
    import("stdfaust.lib");
    freq = hslider("freq [soul:osc_freq]", 300, 200, 2000, 0.1);
    vol = hslider("vol", 0.5, 0, 1, 0.01);
    process = os.osc(freq) * vol <: (_,_);  
}
 ```

 By convention, Faust processors audio inputs are numbered `input0/input1..inputN` and audio outputs  `output0/output1..outputN`. So a given `faust Foo {...}` block can be used in the graph section with: `Foo.input0`,  `Foo.input1`, `Foo.ouput0`,  `Foo.output1` for instance.

Control parameters (button, slider, nentry) are using their label name, or a possible *alias* if the `[soul:alias]` metadata appears in the label string.

## Example of an hybrid file

The following example combines:

- an `Osc` Faust block with *freq (using an 'osc_freq' alias)* and *vol* controllers
- a `Gain` SOUL processor with a *volume* controller
- a `Sequence` graph connecting the Faust osc in the SOUL gain and exposing the three controllers

 ```
faust Osc
{
    import("stdfaust.lib");
    freq = hslider("freq [soul:osc_freq]", 300, 200, 2000, 0.1);
    vol = hslider("vol", 0.5, 0, 1, 0.01);
    process = os.osc(freq) * vol <: (_,_);  
}

processor Gain
{
    input stream float volume [[ name: "Gain", min: 0, max: 1, init: 0.1, step: 0.01 ]]; 

    input stream float input0;
    input stream float input1;

    output stream float output0;
    output stream float output1;

    void run() 
    {
        loop {
            output0 << input0 * volume;
            output1 << input1 * volume;
            advance();
        }
    }
}

graph Sequence [[main]]
{
    // Used in 'hslider' label with [soul:osc_freq] metadata in 'Faust Osc {...}' block
    input Osc.osc_freq;
    // Used as 'hslider' label in 'Faust Osc {...}' block
    input Osc.vol;
    // Using in SOUL 'processor Gain {...}' block
    input Gain.volume;

    output stream float audioOut0;
    output stream float audioOut1;

    connection 
    {
        // Faust Osc {...} audio outputs are output0/output1...outputN
        Osc.output0 -> Gain.input0;
        Osc.output1 -> Gain.input1;

        Gain.output0 -> audioOut0;
        Gain.output1 -> audioOut1;
    }
}
 ```
 
**Note**: the code has a dependency with the [efsw](https://github.com/havoc-io/efsw) library which has to be installed before compilation.

