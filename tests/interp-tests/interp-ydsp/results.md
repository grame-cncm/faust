# interp-ydsp: phase 0 measurements

Apple M5, Darwin 25.6.0 arm64.

- C++ compiler: Apple clang version 21.0.0 (clang-2100.4.1.1), `-O3` (libraries, bench, translator); the C++ ceiling with `-O3 -ffp-contract=off`
- FBC from `FAUST Version 2.95.3 / Source commit: 0b21bae83`, `-lang interp -single`
- libfaust (`Source commit` compiled in): interp 13cc2e3f9, fpb 13cc2e3f9, mir 13cc2e3f9, ydsp 13cc2e3f9
- YUP 4792e50 2026-11-20 (YDSP module compiled with the flags of YUP's own Release build)
- Sample rate 48000 Hz, blocks of 128 samples, best of 5 runs of 0.2 s each, after a warm-up.
- **interp**: the interpreter; **fpb**, **mir**: the DSP block compiled by interp-fpb, interp-mir (`FAUST_INTERP_MIR_PROMOTE=0`); **mir+promo**: interp-mir with `FAUST_INTERP_MIR_PROMOTE=1`; **ydsp-mem**: interp-ydsp with `FAUST_INTERP_YDSP_PROMOTE=0`; **ydsp**: interp-ydsp (promotion on); **ydsp-strict**: interp-ydsp with `FAUST_INTERP_YDSP_LIBMF32=0` (YDSP's strict mode: float32 transcendentals computed in float64, expected to differ from the interpreter by about one ulp); **cpp**: the C++ class.
- Every engine's outputs are compared with the interpreter's (400 blocks of noise, every parameter moved halfway): **12 DSPs**, 6 engines compared with the interpreter on each, bit for bit.

## ns per sample

| DSP | interp | fpb | mir | mir+promo | ydsp-mem | ydsp | ydsp-strict | cpp | mir / ydsp-mem | mir+promo / ydsp | ydsp / cpp | identical | YDSP code, compile |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|---|
| [compressor](../../../examples/dynamic/compressor.dsp) | 106.31 | 36.72 | 14.76 | 13.51 | 14.88 | 10.18 | 15.71 | 7.04 | ×0.99 | ×1.33 | ×1.45 | yes (ydsp-strict: 560 samples differ, max 1.2e-07) | 848 B, 0.4 ms |
| [crybaby](../../../examples/filtering/cryBaby.dsp) | 43.61 | 19.75 | 8.76 | 4.61 | 9.07 | 4.09 | 4.11 | 4.70 | ×0.97 | ×1.13 | ×0.87 | yes | 680 B, 0.4 ms |
| [echo](../../../examples/delayEcho/echo.dsp) | 11.63 | 5.22 | 4.10 | 1.76 | 4.25 | 4.61 | 4.62 | 2.85 | ×0.96 | ×0.38 | ×1.61 | yes | 160 B, 0.1 ms |
| [flanger](../../../examples/phasing/flanger.dsp) | 125.32 | 50.88 | 17.82 | 10.73 | 11.53 | 4.79 | 4.85 | 4.52 | ×1.55 | ×2.24 | ×1.06 | yes | 1152 B, 0.8 ms |
| [freeverb](../../../examples/reverb/freeverb.dsp) | 266.55 | 78.21 | 113.36 | 50.47 | 37.67 | 24.73 | 24.72 | 19.55 | ×3.01 | ×2.04 | ×1.26 | yes | 5516 B, 1.6 ms |
| [moog_vcf](../../../examples/filtering/moogVCF.dsp) | 283.73 | 139.53 | 42.87 | 47.16 | 54.60 | 29.28 | 37.54 | 18.07 | ×0.79 | ×1.61 | ×1.62 | yes | 3104 B, 1.3 ms |
| [osc](../../../examples/generator/osc.dsp) | 25.42 | 12.88 | 4.60 | 3.16 | 5.71 | 2.42 | 2.42 | 3.55 | ×0.81 | ×1.31 | ×0.68 | yes | 464 B, 0.2 ms |
| [parametric_eq](../../../examples/filtering/parametricEqualizer.dsp) | 233.59 | 107.09 | 36.03 | 22.69 | 58.07 | 26.05 | 24.00 | 18.25 | ×0.62 | ×0.87 | ×1.43 | yes (ydsp-strict: 39997 samples differ, max 4.9e-06) | 2216 B, 0.9 ms |
| [phaser2](../../../examples/phasing/phaser.dsp) | 623.69 | 317.19 | 222.07 | 222.34 | 249.57 | 160.92 | 327.96 | 59.92 | ×0.89 | ×1.38 | ×2.69 | yes (ydsp-strict: 55461 samples differ, max 1.9e-07) | 5320 B, 2.5 ms |
| [virtual_analog_oscillator](../../../examples/generator/virtualAnalog.dsp) | 1319.19 | 862.40 | 310.40 | 339.53 | 238.00 | 163.02 | 224.39 | 39.63 | ×1.30 | ×2.08 | ×4.11 | yes (ydsp-strict: 2819 samples differ, max 4.3e-07) | 21464 B, 30.2 ms |
| [vocoder](../../../examples/filtering/vocoder.dsp) | 1878.96 | 362.27 | 122.81 | 111.03 | 150.44 | 102.02 | 101.98 | 93.78 | ×0.82 | ×1.09 | ×1.09 | yes | 17072 B, 24.2 ms |
| [zita_rev1](../../../examples/reverb/zitaRev.dsp) | 676.54 | 190.95 | 98.25 | 58.02 | 88.12 | 44.13 | 44.40 | 29.91 | ×1.11 | ×1.31 | ×1.48 | yes | 10864 B, 4.9 ms |

## Geometric means

| ratio | value |
|---|---:|
| interp / fpb (speedup over the interpreter) | ×2.49 |
| interp / mir (speedup over the interpreter) | ×5.31 |
| interp / mir+promo (speedup over the interpreter) | ×7.52 |
| interp / ydsp-mem (speedup over the interpreter) | ×5.57 |
| interp / ydsp (speedup over the interpreter) | ×9.64 |
| interp / ydsp-strict (speedup over the interpreter) | ×8.39 |
| interp / cpp (speedup over the interpreter) | ×13.83 |
| mir / ydsp-mem (the code generator, same translation without promotion) | ×1.05 |
| mir+promo / ydsp (the code generator, same translation with promotion) | ×1.28 |
| mir / mir+promo (promotion, MIR) | ×1.42 |
| ydsp-mem / ydsp (promotion, YDSP) | ×1.73 |
| ydsp-strict / ydsp (YDSP's strict float32 transcendentals, in float64) | ×1.15 |
| ydsp / cpp (distance to the C++ ceiling) | ×1.43 |

## Other checks (correctness only)

- `-double`: osc identical for every engine; freeverb identical for every engine; zita_rev1 identical for every engine; vocoder identical for every engine.
- two instances of one factory, computed alternately: osc identical for every engine; zita_rev1 identical for every engine; vocoder identical for every engine.
- `-vec -lv 1`: osc identical for every engine; freeverb identical for every engine.
  - osc, YDSP: interp-ydsp: DSP block not compiled (an int heap access with a computed index), the interpreter runs it
  - freeverb, YDSP: interp-ydsp: DSP block compiled to 13732 bytes of machine code (2142 IR instructions, 3156 before optimisation, 217 blocks), 5 real and 182 int heap cells promoted, 10.32 ms
