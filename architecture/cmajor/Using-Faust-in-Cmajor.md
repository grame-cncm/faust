

# Using Faust in Cmajor

In this tutorial, we present how [Faust](https://faust.grame.fr) can be used with [Cmajor](https://cmajor.dev), a C like procedural high-performance language especially designed for audio processing, and with dynamic JIT based compilation. Compiling Faust DSP to cmajor code will allow to take profit of hundreds of DSP building blocks implemented in the [Faust Libraries](https://faustlibraries.grame.fr), ready to use [Examples](https://faustdoc.grame.fr/examples/ambisonics/), any DSP program developed in more than 120 projects listed in the [Powered By Faust](https://faust.grame.fr/community/made-with-faust/) page, or Faust DSP programs found on the net.

#### Who is this tutorial for?

The [first section](#using-command-line-tools) assumes a working [Faust](https://github.com/grame-cncm/faust) compiler installed on the machine, so is more designed for regular Faust users. The [second section](#using-the-faust-web-ide) is better suited for Cmajor users who want to discover Faust.  

#### Installing the required packages

Download the [**cmaj** package](https://github.com/SoundStacks/cmajor/releases) and install to have it in your PATH. 

## Using command line tools

### Generating Cmajor code

Assuming you've [compiled and installed the **faust** compiler](https://github.com/grame-cncm/faust/wiki/BuildingSimple), starting from the following DSP **osc.dsp** program:

<!-- faust-run -->
```
import("stdfaust.lib");

vol = hslider("volume [unit:dB]", 0, -96, 0, 0.1) : ba.db2linear : si.smoo;
freq1 = hslider("freq1 [unit:Hz]", 1000, 20, 3000, 1);
freq2 = hslider("freq2 [unit:Hz]", 200, 20, 3000, 1);

process = vgroup("Oscillator", os.osc(freq1) * vol, os.osc(freq2) * vol);
```
<!-- /faust-run -->

The Cmajor code can be generated using:

```bash
faust -lang cmajor osc.dsp -o osc.cmajor
```

This will generate a `mydsp` processor with a set of methods to manipulate it. This API basically mimics the [one defined for the C++ backend](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/dsp.h). 

### Looking at the generated code

The generated code contains `input event` definition for the three sliders defined in the DSP source code:

```
input event float32 eventfHslider1 [[ name: "freq1", group: "/v:Oscillator/freq1", min: 20.0f, max: 3000.0f, init: 1000.0f, step: 1.0f, meta_unit0: "Hz" ]];
input event float32 eventfHslider2 [[ name: "freq2", group: "/v:Oscillator/freq2", min: 20.0f, max: 3000.0f, init: 200.0f, step: 1.0f, meta_unit1: "Hz" ]];
input event float32 eventfHslider0 [[ name: "volume", group: "/v:Oscillator/volume", min: 0.0f, max: 1.0f, init: 0.5f, step: 0.01f ]];
```

The needed `main` function executes the DSP sample generation code:

```
void main()
{
    // DSP loop running forever...
    loop
    {
        if (fUpdated) { fUpdated = false; control(); }
        
        // Computes one sample
        fRec1[0] = fControl[1] + fRec1[1] - floor (fControl[1] + fRec1[1]);
        output0 <- float32 (fControl[0] * ftbl0mydspSIG0.at (int32 (65536.0f * fRec1[0])));
        fRec2[0] = fControl[2] + fRec2[1] - floor (fControl[2] + fRec2[1]);
        output1 <- float32 (fControl[0] * ftbl0mydspSIG0.at (int32 (65536.0f * fRec2[0])));
        fRec1[1] = fRec1[0];
        fRec2[1] = fRec2[0];
        
        // Moves all streams forward by one 'tick'
        advance();
    }
}
```

Note that the generated code uses the so-called [scalar code generation model](https://faustdoc.grame.fr/manual/compiler/#structure-of-the-generated-code), the default one, where the compiled sample generation code is inlined on the Cmajor `loop` block. 

The resulting file is self-contained and so can directly be compiled and executed using the **cmaj** program:

```bash
cmaj play osc.cmajor
```

The three declared sliders are automatically created and can be used to change the two channels frequencies and their volume.

The Cmajor processor code can directly be used in a more complex Cmajor program, possibly connected to other Faust generated or Cmajor hand-written processors. Note that the generated processor name can simply be changed using the Faust compiler `-cn <name>` option, so that several Faust generated processors can be distinguished by their names:

```bash
faust -lang cmajor -cn osc osc.dsp -o osc.cmajor
```

### Using the faust2cmajor tool

The [faust2cmajor](https://github.com/SoundStacks/faust/tree/cmajor/architecture/cmajor#faust2cmajor) tool allows to automate calling the Faust compiler with the right options and interacting with the **cmaj** program:

```bash
faust2cmajor -h
Usage: faust2cmajor [options] [Faust options] <file.dsp>
Compiles Faust programs to Cmajor
Options:
   -midi : activates MIDI control
   -nvoices <num> : produces a polyphonic DSP with <num> voices, ready to be used with MIDI events
   -effect <effect.dsp> : generates a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
   -effect auto : generates a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC
   -juce : to create a JUCE project
   -dsp : to create a 'dsp' compatible subclass
   -play : to start the 'cmaj' runtime with the generated Cmajor file
   Faust options : any option (e.g. -vec -vs 8...). See the Faust compiler documentation.
```

So the following command:
```bash
faust2cmajor -play osc.dsp 
```

Will directly compile the `osc.dsp` file, generate the `osc.cmajor` and `osc.cmajorpatch` files:

```
{
	"CmajorVersion": 1,
	"ID": "grame.cmajor.osc",
	"version": "1.0",
	"name": "osc",
	"description": "Cmajor example",
	"category": "synth",
	"manufacturer": "GRAME",
	"website": "https://faust.grame.fr",
	"isInstrument": false,
	"source": "osc.cmajor"
}
```

And activate the **cmaj** program to run the processor. 

The following [polyphonic ready instrument](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support) DSP can be converted to a MIDI ready cmajor instrument:

<!-- faust-run -->
```
import("stdfaust.lib");
process = organ, organ
with {
    decimalpart(x) = x-int(x);
    phasor(f) = f/ma.SR : (+ : decimalpart) ~ _;
    osc(f) = sin(2 * ma.PI * phasor(f));
    freq = nentry("freq", 100, 100, 3000, 0.01);
    gate = button("gate");
    gain = nentry("gain", 0.5, 0, 1, 0.01);
    organ = gate * (osc(freq) * gain + osc(2 * freq) * gain);
};
```
<!-- /faust-run -->

The following command then opens the **cmaj** program and MDI events can be sent to control the instrument:
```bash
faust2cmajor -play -midi -nvoices 16 organ.dsp 
```

Note that the generated GUI is empty, since the generated processor cannot automatically reflects its controls in the main graph.

The following [polyphonic ready instrument](https://faustdoc.grame.fr/manual/midi/#audio-effects-and-polyphonic-synthesizer) DSP, with an integrated effect, can be converted to a MIDI ready cmajor instrument:

<!-- faust-run -->
```
import("stdfaust.lib");
process = pm.clarinet_ui_MIDI <: _,_;
effect = dm.freeverb_demo;
```
<!-- /faust-run -->

The following command then opens the **cmaj** program and MDI events can be sent to control the instrument:
```bash
faust2cmajor -play -midi -nvoices 16 -effect auto clarinet.dsp 
```

Here again the generated GUI is empty.

## Using the Faust Web IDE

Faust DSP program can be written, tested in the [Faust Web IDE](https://faustide.grame.fr/) and generated as embeddable Cmajor code.

### Generating the Cmajor output

The output as a Cmajor program can directly be generated using the *Platform = source* and *Architecture = cmajor* export options. The resulting *foo* folder is self-contained, containing the `foo.cmajor` and `foo.cmajorpatch` files. The program can be executed using `cmaj play foo/foo.cmajorpatch` command or possibly [converted as a JUCE plugin](https://github.com/SoundStacks/cmajor/blob/main/docs/Getting%20Started.md#generating-c-and-wasm-code).

<img src="img/export.png" class="mx-auto d-block" width="40%">
<center>*Exporting the code*</center>

### Generating the Cmajor output in polyphonic mode

DSP programs following the polyphonic [freq/gate/gain convention](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support) can be generated using the *Platform = source* and *Architecture = cmajor-poly* export options. The resulting *foo* folder is self-contained, containing the `foo.cmajor` and `foo.cmajorpatch` files. The instrument can be executed using `cmaj play foo/foo.cmajorpatch` command and played with a MIDI device or possibly [converted as a JUCE plugin](https://github.com/SoundStacks/cmajor/blob/main/docs/Getting%20Started.md#generating-c-and-wasm-code).

### Generating the Cmajor output in polyphonic mode with a global effect

DSP programs following the polyphonic [freq/gate/gain convention](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support) with and an [integrated effect](https://faustdoc.grame.fr/manual/midi/#audio-effects-and-polyphonic-synthesizer) can be generated using the *Platform = source* and *Architecture = cmajor-poly-effect* export options. The resulting *foo* folder is self-contained, containing the `foo.cmajor` and `foo.cmajorpatch` files. The instrument can be executed using `cmaj play foo/foo.cmajorpatch` command and played with a MIDI device or possibly [converted as a JUCE plugin](https://github.com/SoundStacks/cmajor/blob/main/docs/Getting%20Started.md#generating-c-and-wasm-code).

