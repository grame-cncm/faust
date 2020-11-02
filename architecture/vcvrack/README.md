# faust2vcvrack

The **faust2vcvrack** tool compiles a Faust DSP program in a folder containing the [VCV Rack](https://vcvrack.com) plugin C++ source code and a Makefile to compile it. By default the resulting C++ code is compiled and installed in the VCV Rack application.

`faust2vcvrack [-source] [-nvoices <num>] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-source to only create the source folder`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`

[WIP]: Faust DSP code classically produces audio signals in the [-1..1] range. Since VCV expect audio signals in the [-5..5] range, they are automatically converted in the architecture file. VC control in the [0..10] volts range will be mapped to the controllers [min..max] range.

## Metadate

- `[VC:N]` can be used in input or output controllers to connect them to VC instead of regular GUI parameters.

## DSP examples

Here is a simple example showing how oscillators can be controlled by parameters:

```
import("stdfaust.lib");

// UI controllers connected using metadata
freq = hslider("freq", 200, 50, 5000, 0.01);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = button("gate");
check = checkbox("check");

// DSP processor
process = os.osc(freq) * gain * gate, os.sawtooth(freq) * gain * check;
```
