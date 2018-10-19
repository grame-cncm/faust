# Multi-effect Example

## Description

This effect makes copies of its input sound and remixes them to the stereo field using differently modulated delays, thus simulating a effects of nearly identical sound sources. The included effects are:

  - Flanger
  - Chorus
  - Echo/Delay
  - Reverb

The effects output is always stereo, while its input may be either mono or stereo. To minimize CPU usage, place the effects at the point in your effects chain where the effects are mono to the left and stereo to the right.

## Parameters

Effect  | Parameter           | MIDI CC # | Type   | Description
|---|---|---|---|---|
Echo    | **Enable**          | `CC-105`  | switch`SW-4` | Turn the effect on/off
Echo    | **Feedback**        | `CC-2 `   | knob `HDAC-0`| Controls the number of echo repetitions between 1 and infinity. - performable
Echo    | **Delay Portament** | `CC-60`   | knob   | DelayT60 controls the speed of Delay, Warp. It gives the time to DelayT60 to the next knob setting in seconds. contents. - performable
Echo    | **Delay**           | `CC-61`   | knob   | Time between echoes in seconds - performable. Under Expert there is a Delay Glide which is a portamento for changing the delay time, and is also performable.
Echo    | **Warp**            | `CC-62`   | knob   | Warp moves the output delay-line tap at a rate controlled by Glide. It can create temporary "glitching" (low Glide) or Doppler shifts (high Glide) - performable (thanks to Glide)
Echo    | **Amp**             | `CC-75`   | knob   | Amplitude level of echoes relative to the direct signal - performable
Echo    | **FeedbackSm**      | `CC-76`   | knob   | When an echo is fed back to echo again, it is also lowpass filtered according to this parameter. Tone = 0 ("Digital") corresponds to no filtering, while Tone = 1 ("Tape") gives maximum lowpass filtering, like an old magnetic tape.
||||||
Reverb  | **Enable**          | `CC-104`  | switch`SW-3` | Turn on/off the effect
Reverb  | **Damp**            | `CC-3 `   | knob `HDAC-1`   | Increasing the damping decreases the reverberation time.
Reverb  | **Room Size**       | `CC-4 `   | knob `HDAC-2`   | Increasing the Room Size parameter lengthens the delay lines used in the reverberator, corresponding to longer path lengths between reflections in an acoustic space.
Reverb  | **Wet Dry**         | `CC-79`   | knob   | Level is the "dry/wet mix": 0 for "dry" (no reverb), and 1 for "wet" (pure reverberator output). Note that stereo imaging is normally reduced by reverberation, because the reverberated sound is supposed sound like it's coming from all directions. Reduce the Reverb Level to better preserve stereo imaging.
||||||
Chorus  |**Enable**    | `CC-103`  | switch`SW-2`   | Turn on/off the effect
Chorus  | **Delay**     | `CC-55`    | knob   | The variable delays range between zero and this value
Chorus  |**Rate**      | `CC-56`    | knob   | The Chorus Rate (performable) sets the highest frequency used in its LFOs for modulating the delay-line lengths
Chorus  |**Depth**     | `CC-57`    | knob   | The Depth parameter (performable) controls the mixture of the input sound with the delayed-and-scaled copies of itself: 0 means input only (no chorus effect), 1/2 means equal balance (maximum incidental "flanging" effects), and 1 means modulated delay-line outputs only (pure chorus effect containing only scaling, onset spreading, and decorrelated Doppler shift).
Chorus  |**Deviation** | `CC-58`   | knob   | The Chorus Deviation sets the amplitude of its LFOs and therefore the range of delay-line length variation. The Deviation and Rate together determine the maximum Doppler shift applied to the sound.
||||||
Flanger | **Enable**          | `CC-102`  | switch`SW-1` | Turn on/off the effect
Flanger | **Invert**          | `CC-49`   | knob   |
Flanger | **Delay**           | `CC-50`   | knob   | Maximum Delay (in ms) used by the flanger - the actual delay at any given time is between this value and zero.
Flanger | **Rate**            | `CC-51`   | knob   | The Flanger Rate parameter sets the frequency of its LFO in Hz - performable
Flanger | **Depth**           | `CC-52`   | knob   | Depth of spectral notches - performable - Depth = 0 means no effect, Depth = 1 means maximum effect (spectral-notch gains go all the way down to zero).
Flanger | **Feedback**        | `CC-53`   | knob   | Gain applied to the output signal and then summed with the input signal - performable
Flanger | **Wave Shape**      | `CC-54`   | knob   |



# Building the Example

The faust code (.dsp) in this directory has been compiled using `faust2sam` into `effects-sam`

```
% faust2sam -midi effects.dsp
```

The result of this compile is a zip file `effects-sam.zuo` which contains the following three files:

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

These 3 files should be placed into the directory `sam_baremetal_framework_core1/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way. The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec.

```
#define USE_FAUST_ALGORITHM_CORE1           TRUE
#define USE_FAUST_ALGORITHM_CORE2           FALSE
```
