# Simple MIDI Controlled 16 Channel Volume Control

## Description

A 16 channel MIDI volume controller

## Parameters

Function         | MIDI CC # | Function          | MIDI CC #
-----------------|-----------|-------------------|-----------
Channel 1 Volume | `CC-1`    | Channel 9 Volume  | `CC-9`
Channel 2 Volume | `CC-2`    | Channel 10 Volume | `CC-10`
Channel 3 Volume | `CC-3`    | Channel 11 Volume | `CC-11`
Channel 4 Volume | `CC-4`    | Channel 12 Volume | `CC-12`
Channel 5 Volume | `CC-5`    | Channel 13 Volume | `CC-13`
Channel 6 Volume | `CC-6`    | Channel 14 Volume | `CC-14`
Channel 7 Volume | `CC-7`    | Channel 15 Volume | `CC-15`
Channel 8 Volume | `CC-8`    | Channel 16 Volume | `CC-16`

## Building the Example

The faust code (.dsp) in this directory has been compiled using `faust2sam` into `16-channel-volume-sam`

```
% faust2sam -midi 16-channel-volume.dsp
```

The result of this compile is a zip file `16—channel—volume-sam.zip` containing the following three files:

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

These 3 files should be placed into the directory `sam_baremetal_framework_core1/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way. The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

```
#define USE_FAUST_ALGORITHM_CORE1               TRUE
#define USE_FAUST_ALGORITHM_CORE2               TRUE
```
