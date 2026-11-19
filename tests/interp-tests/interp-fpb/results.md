# interp vs interp-fpb

Apple M5, Darwin 25.6.0 arm64.

- C++ compiler: Apple clang version 21.0.0 (clang-2100.4.1.1)  -O3 (the libraries and this bench)
- FAUST Version 2.94.1; FBC from `-lang interp -single`
- Sample rate 48000 Hz, blocks of 128 samples, best of 5 runs of 0.2 s each, after a warm-up.
- **interp**: libfaust built with the INTERP backend; **interp-fpb**: libfaust built with INTERP_COMP and `INTERP_FPB_BUILD` (the DSP block compiled to FPB steps, the other blocks interpreted).
- **diff**: max |interp − interp-fpb| over 400 blocks of noise, with every parameter moved halfway (0 = identical outputs).

| DSP | interp ns / sample | interp-fpb ns / sample | speedup | diff | FPB steps |
|---|---:|---:|---:|---:|---|
| [compressor](../../../examples/dynamic/compressor.dsp) | 98.53 | 34.71 | **×2.84** | 0 | 33 |
| [crybaby](../../../examples/filtering/cryBaby.dsp) | 42.58 | 18.73 | **×2.27** | 0 | 37 |
| [echo](../../../examples/delayEcho/echo.dsp) | 11.16 | 4.98 | **×2.24** | 0 | 6 |
| [flanger](../../../examples/phasing/flanger.dsp) | 79.73 | 49.54 | **×1.61** | 0 | 65 |
| [freeverb](../../../examples/reverb/freeverb.dsp) | 253.37 | 72.81 | **×3.48** | 0 | 113 |
| [moog_vcf](../../../examples/filtering/moogVCF.dsp) | 278.95 | 131.04 | **×2.13** | 0 | 162 |
| [osc](../../../examples/generator/osc.dsp) | 23.50 | 12.52 | **×1.88** | 0 | 28 |
| [parametric_eq](../../../examples/filtering/parametricEqualizer.dsp) | 223.42 | 98.70 | **×2.26** | 0 | 81 |
| [phaser2](../../../examples/phasing/phaser.dsp) | 600.87 | 288.19 | **×2.09** | 0 | 270 |
| [virtual_analog_oscillator](../../../examples/generator/virtualAnalog.dsp) | 1219.59 | 789.17 | **×1.55** | 0 | 951 |
| [vocoder](../../../examples/filtering/vocoder.dsp) | 1875.30 | 350.18 | **×5.36** | 0 | 583 |
| [zita_rev1](../../../examples/reverb/zitaRev.dsp) | 672.45 | 185.96 | **×3.62** | 0 | 297 |
| **geometric mean** | | | **×2.45** | | |

`-double` (correctness only): osc identical, freeverb identical, zita_rev1 identical, vocoder identical.

Two instances of one factory, computed alternately (correctness only): osc identical, zita_rev1 identical, vocoder identical.

`-vec` (not compiled by FPB, the interpreter runs the DSP block): osc identical, freeverb identical.
