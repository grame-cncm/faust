# Chorus

## Description

The Chorus effect makes copies of its input sound and remixes them to the stereo field using differently modulated delays, thus simulating a chorus of nearly identical sound sources.

The Chorus output is always stereo, while its input may be either mono or stereo. To minimize CPU usage, place the Chorus at the point in your effects chain where the effects are mono to the left and stereo to the right.

## Parameters

Parameter     | MIDI CC # | Description | Physical Control |
|---|---|---|---|
**Enable**    | `CC-105`  | Turn on/off the effect | switch`SW-4` |
**Rate**      | `CC-2`    | The Chorus Rate (performable) sets the highest frequency used in its LFOs for modulating the delay-line lengths |knob`HADC-0` |
**Depth**     | `CC-3`    | The Depth parameter (performable) controls the mixture of the input sound with the delayed-and-scaled copies of itself: 0 means input only (no chorus effect), 1/2 means equal balance (maximum incidental "flanging" effects), and 1 means modulated delay-line outputs only (pure chorus effect containing only scaling, onset spreading, and decorrelated Doppler shift). | knob`HADC-1` |
**Delay**     | `CC-4`    | The variable delays range between zero and this value |knob`HADC-2` |
**Deviation** | `CC-58`   | The Chorus Deviation sets the amplitude of its LFOs and therefore the range of delay-line length variation. The Deviation and Rate together determine the maximum Doppler shift applied to the sound. | |

## Building the Example

The faust code (.dsp) in this directory has been compiled using faust2sam into chorus-sam

```
% faust2sam -midi chorus.dsp
```

The result of this compile is a zip file `chorus-sam.zip` containing the following three files:

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

These 3 files should be placed into the directory `sam_baremetal_framework_core1/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way. The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

```
#define USE_FAUST_ALGORITHM_CORE1           TRUE
#define USE_FAUST_ALGORITHM_CORE2           FALSE
```
