# interp-ydsp against interp-mir: impulse-tests

Apple M5, Darwin 25.6.0 arm64. Load average at the end: 6.3 7.5 5.3.

- FBC from `FAUST Version 2.95.3 / Source commit: 0b21bae83`, `-lang interp -single`; bench executables built by run-bench.py.
- Corpus: `tests/impulse-tests/dsp` (99 DSPs).
- interp-mir and interp-ydsp with their defaults (promotion on in both). Outputs compared with the interpreter's, bit for bit (400 blocks of noise, parameters moved halfway); best of 5 runs of 0.10 s.

## Counts

| status | DSPs |
|---|---:|
| ok | 91 |
| ydsp not compiled | 5 |
| differs | 0 |
| crash | 3 |
| faust failed | 0 |

## Speed, on the 91 DSPs both compile with the interpreter's outputs

| ratio | value |
|---|---:|
| interp / mir, geometric mean | ×6.22 |
| interp / ydsp, geometric mean | ×7.34 |
| **mir / ydsp, geometric mean** | **×1.18** |
| mir / ydsp: min, 10 %, 25 %, median, 75 %, 90 %, max | ×0.64, ×0.93, ×0.99, ×1.15, ×1.33, ×1.68, ×3.26 |
| DSPs where YDSP is faster than MIR (ratio > 1) | 64 of 91 |
| DSPs where YDSP is more than 10 % slower (ratio < 0.9) | 8 |
| YDSP compile time: median, max | 0.3 ms, 210.9 ms |

### The 10 DSPs where YDSP does worst against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| tests/impulse-tests/dsp/norm2.dsp | 41.56 | 4.84 | 7.55 | ×0.64 |
| tests/impulse-tests/dsp/tf_exp.dsp | 114.44 | 9.26 | 13.38 | ×0.69 |
| tests/impulse-tests/dsp/volume.dsp | 8.07 | 1.77 | 2.30 | ×0.77 |
| tests/impulse-tests/dsp/capture.dsp | 21.39 | 1.82 | 2.30 | ×0.79 |
| tests/impulse-tests/dsp/tapiir.dsp | 115.67 | 9.45 | 11.53 | ×0.82 |
| tests/impulse-tests/dsp/osc.dsp | 13.33 | 3.03 | 3.62 | ×0.84 |
| tests/impulse-tests/dsp/table.dsp | 12.66 | 2.96 | 3.48 | ×0.85 |
| tests/impulse-tests/dsp/APF.dsp | 18.62 | 4.27 | 4.78 | ×0.89 |
| tests/impulse-tests/dsp/smoothdelay.dsp | 55.52 | 5.01 | 5.45 | ×0.92 |
| tests/impulse-tests/dsp/waveform3.dsp | 8.21 | 3.45 | 3.71 | ×0.93 |

### The 10 DSPs where YDSP does best against MIR

| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |
|---|---:|---:|---:|---:|
| tests/impulse-tests/dsp/priority1.dsp | 574.89 | 164.94 | 50.53 | ×3.26 |
| tests/impulse-tests/dsp/karplus.dsp | 23.31 | 5.02 | 2.12 | ×2.37 |
| tests/impulse-tests/dsp/freeverb.dsp | 352.35 | 44.39 | 19.27 | ×2.30 |
| tests/impulse-tests/dsp/modulations.dsp | 2376.06 | 228.52 | 103.93 | ×2.20 |
| tests/impulse-tests/dsp/echo_bug.dsp | 27.10 | 3.86 | 1.83 | ×2.10 |
| tests/impulse-tests/dsp/reverb_designer.dsp | 4115.71 | 1765.36 | 866.91 | ×2.04 |
| tests/impulse-tests/dsp/long_convolution.dsp | 159.52 | 17.68 | 9.52 | ×1.86 |
| tests/impulse-tests/dsp/comb_bug_exp.dsp | 68.72 | 8.22 | 4.44 | ×1.85 |
| tests/impulse-tests/dsp/karplus32.dsp | 315.08 | 63.80 | 35.68 | ×1.79 |
| tests/impulse-tests/dsp/vumeter.dsp | 24.47 | 5.87 | 3.49 | ×1.68 |

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
