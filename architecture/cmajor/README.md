# faust2cmajor

The **faust2cmajor** tool compiles a Faust DSP program in a folder containing the Cmajor source code and Cmajor patch. The result can be a monophonic DSP or a MIDI controllable polyphonic one (when the DSP describes an instrument, following the `freq, gain, gate` [parameter naming convention](https://faust.grame.fr/doc/manual/index.html#midi-polyphony-support)). The resulting Cmajor code can be played using the **cmaj** runtime:

`faust2cmajor [-midi] [-nvoices <num>] [-effect auto|<effect.dsp>] [-juce] [-dsp] [-play] [additional Faust options (-cn foo -double...)] <file.dsp>`

Here are the available options:

- `-midi to activate MIDI control`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`
- `-effect <effect.dsp> to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI`
- `-effect auto to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI`
- `-juce to create a JUCE project`
- `-dsp to create a 'dsp' compatible subclass`
- `-test to test the resulting patch with 'cmaj render'`
- `-play to start the 'cmaj' runtime with the generated Cmajor patch`

So for instance:

- `faust2cmajor noise.dsp` to produce two noise.cmajor and noise.cmajorpatch files
- `faust2cmajor -play osc.dsp` to produce two osc.cmajor  and osc.cmajorpatch files and play the osc.cmajorpatch
- `faust2cmajor -midi -nvoices 16 -play clarinetMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument as two clarinetMIDI.cmajor and clarinetMIDI.cmajorpatch files and play the clarinetMIDI.cmajorpatch
- `faust2cmajor -midi -nvoices 16 -effect freeverb.dsp -play violinMIDI.dsp` to produce a 16 voices polyphonic MIDI aware intrument with a global effect as two violinMIDI.cmajor and violinMIDI.cmajorpatch files and play the violinMIDI.cmajorpatch

# cmajor-faust-player 

The **cmajor-faust-player** tool loads a Faust DSP file, a Cmajor patch or an hybrid Faust/Cmajor code file, wraps it as a Faust DSP object, and runs it in the Faust runtime audio/control machinery. 

`cmajor-faust-player <foo.dsp> (pure Faust code), <foo.cmajorpatch> (pure Cmajor patch) or <foo.cmajor> (pure Cmajor code or Faust/Cmajor hybrid code)`

So for instance:

- `faust2cmajor clarinetMIDI.dsp` to produce the two `clarinetMIDI.cmajor` and `clarinetMIDI.cmajorpatch` files

Then:

- `cmajor-faust-player clarinetMIDI.dsp` to run the `clarinetMIDI.dsp` file (only containing Faust code)
- `cmajor-faust-player clarinetMIDI.cmajorpatch` to run the `clarinetMIDI.cmajorpatch` file

Or:

- `cmajor-faust-player clarinetMIDI.cmajor` to run the `clarinetMIDI.cmajor` file (only containing the Cmajor code)
- `cmajor-faust-player hybrid-test1.cmajor` to run an hybrid `hybrid-test1.cmajor` file containing both Faust and Cmajor sections. Two `hybrid.cmajor` (containing the original Cmajor sections and the Faust => Cmajor generated sections) and an `hybrid.cmajorpatch` files will be generated in the process.

# cmajor-faust-tester 

The **cmajor-faust-tester** tool allows to test DSP CPU usage of Faust and Cmajor programs, dynamically compiling them, and running them in the Faust runtime or **cmajor** runtime. It measures the DSP CPU usage as MBytes/sec and % of audio bandwidth at 44.1 kHz.

`cmajor-faust-tester [-bs <frames>] [-control] [Faust options : any option (e.g. -vec -vs 8...)] <foo.dsp|foo.cmajorpatch>`

Here are the available options:

- `-bs <frames> to set the maximum buffer-size in frames`
- `-control to update all controllers with random values at each cycle`

So for instance:

- `cmajor-faust-tester foo.dsp` to test 1) the Faust DSP code compiled to LLVM-IR and JITted to native code, then running in the Faust runtime, 2) the Faust DSP code compiled to Cmajor, then compiled to LLVM-IR and JITted to native code, and running in the **cmajor** runtime.

- `cmajor-faust-tester foo.cmajorpatch` to test a Cmajor patch compiled to LLVM-IR and JITted to native code, and running in the **cmajor** runtime.

# cmajor-faust-editor

The **cmajor-faust-editor** tool loads an hybrid Faust/Cmajor code file and compiles it in a Cmajor patch each time the source file content changes. It can be used together with the **cmajor** runtime or any Cmajor aware plugin to create a *Faust/Cmajor => Cmajor => executable code* edit loop. The Cmajor generated files can be set using the`-o <output.cmajor>` option and are named `hybrid.cmajor` and  `hybrid.cmajorpatch` by default.

`cmajor-faust-editor [Faust options : any option (e.g. -ftz 1...)] <foo.cmajor> -o <output.cmajor>`

So for instance to setup a Faust/Cmajor hybrid file edition session:

- `cmajor-faust-editor hybrid-test2.cmajor` to start editing an hybrid Faust/Cmajor code
- `cmaj play hybrid.cmajorpatch` to play the Cmajor dynamically generated `hybrid.cmajorpatch`

## Hybrid Faust/Cmajor Syntax

A Faust block uses the following syntax:

 ```
faust Name
{
  ... Faust code...
}
 ```

It will be compiled in Cmajor code as a `processor Name { ...Cmajor code... } ` and inserted back in the resulting Cmajor file. Here is a real example:

 ```
faust Osc
{
    import("stdfaust.lib");
    freq = hslider("freq [cmajor:osc_freq]", 300, 200, 2000, 0.1);
    vol = hslider("vol", 0.5, 0, 1, 0.01);
    process = os.osc(freq) * vol <: (_,_);  
}
 ```

 By convention, Faust processors audio inputs are numbered `input0/input1..inputN` and audio outputs  `output0/output1..outputN`. So a given `faust Foo {...}` block can be used in the graph section with: `Foo.input0`,  `Foo.input1`, `Foo.ouput0`,  `Foo.output1` for instance.

Control parameters (button, slider, nentry) are using their label name, or a possible *alias* if the `[cmajor:alias]` metadata appears in the label string.

## Example of an hybrid file

The following example combines:

- an `Osc` Faust block with *freq (using an 'osc_freq' alias)* and *vol* controllers
- a `Gain` Cmajor processor with a *volume* controller
- a `Sequence` graph connecting the Faust osc in the Cmajor gain and exposing the three controllers

 ```
faust Osc
{
    import("stdfaust.lib");
    freq = hslider("freq [cmajor:osc_freq]", 300, 200, 2000, 0.1);
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

    void main() 
    {
        loop
        {
            output0 <- input0 * volume;
            output1 <- input1 * volume;
            advance();
        }
    }
}

graph Sequence [[main]]
{
    // Used in 'hslider' label with [cmajor:osc_freq] metadata in 'Faust Osc {...}' block
    input Osc.osc_freq;
    // Used as 'hslider' label in 'Faust Osc {...}' block
    input Osc.vol;
    // Using in Cmajor 'processor Gain {...}' block
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

