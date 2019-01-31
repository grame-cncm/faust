# Flange

## Description

The flanger effect impresses uniformly spaced sweeping notches on the sound spectrum. It accomplishes this using a variable comb filter, which works by mixing the input sound with a variably delayed-and-scaled copy of the input. Unlike the phaser, the flanger notches are uniformly spaced on a linear frequency scale, and there can be many more of them at low cost.

## Parameters

Parameter     | MIDI CC # | Description | Physical Control |
|---|---|---|---|
**Enable**    | `CC-105` | Turn the effect on/off| switch`SW-4` |
**Rate**      | `CC-2`   | The Flanger Rate parameter sets the frequency of its LFO in Hz | knob`HADC-0` |
**Depth**     | `CC-3`   | Depth of spectral notches - performable - Depth = 0 means no effect, Depth = 1 means maximum effect (spectral-notch gains go all the way down to zero).  | knob`HADC-1` |
**Feedback**  | `CC-4`   | Gain applied to the output signal and then summed with the input signal - performable  | knob`HADC-2` |
**Delay**     | `CC-50`  | Maximum Delay (in ms) used by the flanger - the actual delay at any given time is between this value and zero.
**Waveshape** | `CC-54`  | Various waveshapes, triangle, square ...
**Invert**    | `CC-49`  | Invert the phase

## Building the Example

The faust code (.dsp) in this directory has been compiled using `faust2sam` into `flanger-sam`

```
% faust2sam -midi flanger.dsp
```

The result of this compile is a zip file `flanger-sam.zip` which contains the following three files:

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

These 3 files should be placed into the directory `sam_baremetal_framework_core1/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way. The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

```
#define USE_FAUST_ALGORITHM_CORE1           TRUE
#define USE_FAUST_ALGORITHM_CORE2           FALSE
```
