# faust2vcvrack

The **faust2vcvrack** tool compiles a Faust DSP program in a folder containing the [VCV Rack](https://vcvrack.com) plugin C++ source code and a Makefile to compile it. By default the resulting C++ code is compiled and installed in the VCV Rack application.

`faust2vcvrack [-source] [-nvoices <num>] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-source to only create the source folder`
- `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`

[WIP]: Faust DSP code classically produces audio signals in the [-1..1] range. Since VCV expect audio signals in the [-5..5] range, they are automatically converted in the architecture file. VC control in the [0..10] volts range will be mapped to the controllers [min..max] range.

## Polyphony support

Polyphonic modules can be created using the  `-nvoices <num>` parameter up to 16 voices. The  `freq/gate/gain` convention can be used in the DSP code. VCV Rack follows the 1V/octave convention for MIDI pitch values, so the MIDI signals are automatically converted to `freq` using this convention. Gain and gates signals (using the [0..10v] range) are converted to [0..1] values.

Note that creating polyphonic effects also make sense in VCV Rack. For instance a reverb connected to a polyphonic instrument would need to be polyphonic. Thus the  `-nvoices <num>` parameter can also be used in this case.

## Metadata

- `[CV:N]` can be used in input or output controllers to connect them to VC instead of regular GUI parameters.

## DSP examples

Here is a simple example showing how oscillators can be controlled by parameters:

```
import("stdfaust.lib");

freq = hslider("freq", 200, 50, 5000, 0.01);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = button("gate");
check = checkbox("check");

// DSP processor
process = os.osc(freq) * gain * gate, os.sawtooth(freq) * gain * check;
```

A polyphonic instrument with `freq/gate/gain` controllers associated with VC MIDI inputs, using the `[VC:N]` metadata, to be compiled with the `-nvoices <num>` option:

```
import("stdfaust.lib");

// control variables
master = hslider("master", 0.3, 0, 2, 0.01);    
pan = hslider("pan", 0.5, 0, 1, 0.01);    

freq = nentry("freq [CV:1]", 440, 20, 20000, 1);    
gain = nentry("gain [CV:3]", 0.3, 0, 10, 0.01);    
gate = button("gate [CV:2]");            

// relative amplitudes of the different partials
amp(1) = hslider("amp1", 1.0, 0, 3, 0.01);
amp(2) = hslider("amp2", 0.5, 0, 3, 0.01);
amp(3) = hslider("amp3", 0.25, 0, 3, 0.01);

// panner function
panner(pan, x) = x*sqrt(1-pan), x*sqrt(pan);

// additive synth: 3 sine oscillators with adsr envelop
partial(i) = amp(i+1)*os.osc((i+1)*freq);

process = sum(i, 3, partial(i))
* (gate : vgroup("1-adsr", en.adsr(0.05, 0.1, 0.1, 0.1)))
* gain : vgroup("2-master", *(master) : panner(pan));
```
