# interp-ydsp against interp-mir: fix-check

Apple M5, Darwin 25.6.0 arm64. Load average at the end: 4.2 3.6 4.4.

- FBC from `FAUST Version 2.95.3 / Source commit: 0b21bae83`, `-lang interp -single`; bench executables built by run-bench.py.
- Corpus: `tests/impulse-tests/dsp`, `examples` (372 DSPs).
- interp-mir and interp-ydsp with their defaults (promotion on in both). Outputs compared with the interpreter's, bit for bit (400 blocks of noise, parameters moved halfway); best of 5 runs of 0.10 s.

## Counts

| status | DSPs |
|---|---:|
| ok | 339 |
| ydsp not compiled | 7 |
| differs | 5 |
| crash | 5 |
| faust failed | 16 |

## Speed, on the 339 DSPs both compile with the interpreter's outputs

| ratio | value |
|---|---:|
| interp / mir, geometric mean | ×7.02 |
| interp / ydsp, geometric mean | ×8.71 |
| **mir / ydsp, geometric mean** | **×1.24** |
| mir / ydsp: min, 10 %, 25 %, median, 75 %, 90 %, max | ×0.42, ×0.93, ×1.01, ×1.19, ×1.43, ×1.84, ×3.34 |
| DSPs where YDSP is faster than MIR (ratio > 1) | 263 of 339 |
| DSPs where YDSP is more than 10 % slower (ratio < 0.9) | 32 |
| YDSP compile time: median, max | 0.7 ms, 1661.0 ms |

### The 10 DSPs where YDSP does worst against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| examples/delayEcho/echo.dsp | 11.54 | 1.70 | 4.00 | ×0.42 |
| examples/delayEcho/stereoEcho.dsp | 19.16 | 1.72 | 3.90 | ×0.44 |
| examples/physicalModeling/faust-stk/tunedBar.dsp | 1006.40 | 110.03 | 172.68 | ×0.64 |
| tests/impulse-tests/dsp/tf_exp.dsp | 64.49 | 5.39 | 7.45 | ×0.72 |
| examples/SAM/volume/volume.dsp | 14.03 | 1.71 | 2.23 | ×0.77 |
| examples/gameaudio/door.dsp | 303.16 | 21.36 | 27.84 | ×0.77 |
| examples/dynamic/volume.dsp | 10.37 | 1.68 | 2.18 | ×0.77 |
| examples/physicalModeling/mi-faust/13_Construction/construction.dsp | 4384.52 | 370.91 | 479.36 | ×0.77 |
| tests/impulse-tests/dsp/norm2.dsp | 41.07 | 4.74 | 6.02 | ×0.79 |
| tests/impulse-tests/dsp/capture.dsp | 20.45 | 1.77 | 2.22 | ×0.79 |

### The 10 DSPs where YDSP does best against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| examples/physicalModeling/fds/2dKirchhoffThinPlate.dsp | 8557.27 | 4621.47 | 1383.14 | ×3.34 |
| tests/impulse-tests/dsp/priority1.dsp | 566.00 | 158.11 | 49.54 | ×3.19 |
| examples/quantizing/quantizedChords.dsp | 961.69 | 239.35 | 78.77 | ×3.04 |
| examples/physicalModeling/fds/StiffString.dsp | 2914.30 | 592.17 | 197.12 | ×3.00 |
| examples/physicalModeling/fds/ControllableNonPhysicalString.dsp | 2782.33 | 609.44 | 204.54 | ×2.98 |
| tests/impulse-tests/dsp/bells.dsp | 2359.30 | 652.29 | 239.52 | ×2.72 |
| examples/physicalModeling/old/karplus.dsp | 23.26 | 4.93 | 1.81 | ×2.72 |
| examples/misc/guitarix.dsp | 765.71 | 154.93 | 57.31 | ×2.70 |
| tests/impulse-tests/dsp/reverb_designer.dsp | 3513.08 | 1674.21 | 662.30 | ×2.53 |
| examples/smartKeyboard/bowed.dsp | 491.72 | 84.49 | 34.72 | ×2.43 |

## Not in the means

| DSP | status | why |
|---|---|---|
| tests/impulse-tests/dsp/math.dsp | crash | mir exit -6 |
| tests/impulse-tests/dsp/osc_enable.dsp | crash | mir exit -6 |
| tests/impulse-tests/dsp/select2.dsp | ydsp not compiled | an int heap access with a computed index |
| tests/impulse-tests/dsp/sound.dsp | crash | mir exit -6 |
| tests/impulse-tests/dsp/table2.dsp | ydsp not compiled | an int heap access with a computed index |
| tests/impulse-tests/dsp/waveform2.dsp | ydsp not compiled | an int heap access with a computed index |
| tests/impulse-tests/dsp/waveform4.dsp | ydsp not compiled | an int heap access with a computed index |
| tests/impulse-tests/dsp/waveform6.dsp | ydsp not compiled | an int heap access with a computed index |
| examples/SAM/16_channel_volume/layout.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/chorus/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/echo/echo.dsp | faust failed | ERROR : calling foreign function 'fastpow2' is not allowed in this compilation mode |
| examples/SAM/echo/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/effects/echo.dsp | faust failed | ERROR : calling foreign function 'fastpow2' is not allowed in this compilation mode |
| examples/SAM/effects/effects.dsp | faust failed | ERROR : calling foreign function 'fastpow2' is not allowed in this compilation mode |
| examples/SAM/effects/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/flanger/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/freeverb/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/SAM/virtualAnalog/layout2.dsp | faust failed | ????:-1 : ERROR : undefined symbol : process |
| examples/bela/granulator.dsp | ydsp not compiled | an int heap access with a computed index |
| examples/gameaudio/bubble.dsp | differs | ydsp: 67004 samples differ, max 6.0e-08 |
| examples/gameaudio/fire.dsp | differs | ydsp: 17511 samples differ, max 7.3e-06 |
| examples/generator/dx7.dsp | ydsp not compiled | an int heap access with a computed index |
| examples/misc/paradigma.dsp | crash | mir exit -6 |
| examples/misc/sflooper.dsp | crash | mir exit -6 |
| examples/physicalModeling/faust-stk/bass.dsp | faust failed | ERROR : calling foreign function 'getValueBassLoopFilterb0' is not allowed in this compilation mode |
| examples/physicalModeling/faust-stk/bowed.dsp | faust failed | has 2 inputs |
| examples/physicalModeling/faust-stk/harpsi.dsp | faust failed | ERROR : calling foreign function 'getValueReleaseLoopGain' is not allowed in this compilation mode |
| examples/physicalModeling/faust-stk/modalBar.dsp | faust failed | ERROR : calling foreign function 'loadPreset' is not allowed in this compilation mode |
| examples/physicalModeling/faust-stk/piano.dsp | faust failed | ERROR : calling foreign function 'getValueStiffnessCoefficient' is not allowed in this compilation mode |
| examples/physicalModeling/faust-stk/voiceForm.dsp | faust failed | ERROR : calling foreign function 'loadPhonemeParameters' is not allowed in this compilation mode |
| examples/physicalModeling/vocalFOF.dsp | differs | ydsp: 79500 samples differ, max 2.4e-06 |
| examples/physicalModeling/vocalFOFMIDI.dsp | differs | ydsp: 30820 samples differ, max 1.9e-06 |
| examples/reverb/vital_rev.dsp | differs | ydsp: 61162 samples differ, max 2.0e-07 |
