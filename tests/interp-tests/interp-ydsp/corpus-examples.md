# interp-ydsp against interp-mir: examples

Apple M5, Darwin 25.6.0 arm64. Load average at the end: 4.0 6.5 6.1.

- FBC from `FAUST Version 2.95.3 / Source commit: 0b21bae83`, `-lang interp -single`; bench executables built by run-bench.py.
- Corpus: `examples` (273 DSPs).
- interp-mir and interp-ydsp with their defaults (promotion on in both). Outputs compared with the interpreter's, bit for bit (400 blocks of noise, parameters moved halfway); best of 5 runs of 0.10 s.

## Counts

| status | DSPs |
|---|---:|
| ok | 246 |
| ydsp not compiled | 4 |
| differs | 5 |
| crash | 2 |
| faust failed | 16 |

## Speed, on the 246 DSPs both compile with the interpreter's outputs

| ratio | value |
|---|---:|
| interp / mir, geometric mean | ×7.47 |
| interp / ydsp, geometric mean | ×9.39 |
| **mir / ydsp, geometric mean** | **×1.26** |
| mir / ydsp: min, 10 %, 25 %, median, 75 %, 90 %, max | ×0.41, ×0.90, ×1.00, ×1.24, ×1.47, ×1.82, ×3.51 |
| DSPs where YDSP is faster than MIR (ratio > 1) | 188 of 246 |
| DSPs where YDSP is more than 10 % slower (ratio < 0.9) | 25 |
| YDSP compile time: median, max | 1.1 ms, 381.2 ms |

### The 10 DSPs where YDSP does worst against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| examples/delayEcho/echo.dsp | 13.56 | 1.71 | 4.21 | ×0.41 |
| examples/delayEcho/stereoEcho.dsp | 19.71 | 1.76 | 4.29 | ×0.41 |
| examples/generator/brightOrgan.dsp | 827.87 | 86.77 | 140.30 | ×0.62 |
| examples/SAM/volume/volume.dsp | 14.76 | 1.82 | 2.39 | ×0.76 |
| examples/gameaudio/door.dsp | 300.59 | 21.54 | 28.05 | ×0.77 |
| examples/SAM/effects/freeverb.dsp | 344.08 | 18.40 | 23.44 | ×0.79 |
| examples/dynamic/volume.dsp | 11.77 | 1.88 | 2.39 | ×0.79 |
| examples/physicalModeling/mi-faust/13_Construction/construction.dsp | 4398.45 | 372.60 | 464.53 | ×0.80 |
| examples/delayEcho/quadEcho.dsp | 33.80 | 3.62 | 4.36 | ×0.83 |
| examples/physicalModeling/mi-faust/03_HammerTime/hammerOsc.dsp | 49.26 | 5.84 | 7.03 | ×0.83 |

### The 10 DSPs where YDSP does best against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| examples/physicalModeling/fds/2dKirchhoffThinPlate.dsp | 8973.17 | 4778.72 | 1362.27 | ×3.51 |
| examples/quantizing/quantizedChords.dsp | 983.61 | 251.76 | 81.52 | ×3.09 |
| examples/physicalModeling/fds/ControllableNonPhysicalString.dsp | 2821.44 | 602.53 | 207.68 | ×2.90 |
| examples/physicalModeling/fds/StiffString.dsp | 3527.34 | 651.01 | 225.82 | ×2.88 |
| examples/physicalModeling/old/karplus.dsp | 24.34 | 4.95 | 1.80 | ×2.76 |
| examples/misc/guitarix.dsp | 742.84 | 158.80 | 58.32 | ×2.72 |
| examples/SAM/freeverb/freeverbForBrowser.dsp | 594.30 | 46.30 | 19.91 | ×2.33 |
| examples/smartKeyboard/midiOnly.dsp | 148.56 | 15.15 | 6.74 | ×2.25 |
| examples/SAM/chorus/chorusForBrowser.dsp | 461.99 | 44.22 | 20.31 | ×2.18 |
| examples/SAM/effects/chorus.dsp | 436.43 | 43.89 | 20.19 | ×2.17 |

## Not in the means

| DSP | status | why |
|---|---|---|
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
| examples/reverb/fdnRev.dsp | ydsp not compiled | YDSP code generation: <memory>: error: AsmJit failed to assemble the kernel: InvalidDisplacement (InvalidDisplacement: stur s0, [sp, 16424])

--- AsmJit assembl |
| examples/reverb/reverbDesigner.dsp | ydsp not compiled | YDSP code generation: <memory>: error: AsmJit failed to assemble the kernel: InvalidDisplacement (InvalidDisplacement: stur s0, [sp, 16424])

--- AsmJit assembl |
| examples/reverb/vital_rev.dsp | differs | ydsp: 61162 samples differ, max 2.0e-07 |
