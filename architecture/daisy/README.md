# faust2daisy

The **faust2daisy** tool compiles a Faust DSP program in a folder containing the C++ source code and a Makefile to compile it.  

`faust2daisy [-patch] [-midi] [-nvoices <num>] [-sr <num>] [-bs <num>] [-source] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-patch : to compile for 4 ins/outs Patch (TODO)`
- `-midi to activate MIDI control`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI (TODO)`
- `-sr <num> to specify sample rate (default 44100)`
- `-bs <num> to specify buffer size (default 16)`
- `-source to only create the source folder`

The generated folder has to be moved in the *DaisyExamples/DaisySP/examples* folder and compiled from there. 

Only programming the POD can been tested. The 2 *switches* and 2 *knobs* can be connected to UI controllers using metadata:

- `[switch:N]` (with N from 1 to 2) has to be used in a `button` or `checkbox` item to connect it to the POD switch number N.
- `[knob:N]` (with N from 1 to 2) has to be used in a `vslider`, `hslider` or `nentry` item to connect it to the POD knob number N. The knob [0..1] range will be mapped to the slider/nentry [min..max] range.

Other metadata:

- `[scale:lin|log|exp]` metadata is implemented.

## DSP examples

Here is a simple example showing how oscillators can be controlled by physical items and MIDI messages:

```
import("stdfaust.lib");

// UI controllers connected using metadata
freq = hslider("freq [knob:1] [midi:ctrl 1] [scale:log]", 200, 50, 5000, 0.01);
gain = hslider("gain [knob:2] [midi:ctrl 7]", 0.5, 0, 1, 0.01);
gate = button("gate [switch:1]");
check = checkbox("check [switch:2]");

// DSP processor
process = os.osc(freq) * gain * gate, os.sawtooth(freq) * gain * check;
```
