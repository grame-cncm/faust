
# demo.lib 
This library contains a set of demo functions based on examples located in the
`/examples` folder.

It should be used using the `dm` environment:

```
dm = library("demo.lib");
process = dm.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `dm`
environment:

```
import("stdfaust.lib");
process = dm.functionCall;
```

## Analyzers

### `mth_octave_spectral_level_demo`
Demonstrate mth_octave_spectral_level in a standalone GUI.

#### Usage
```
_ : mth_octave_spectral_level_demo(BandsPerOctave);
_ : spectral_level_demo : _; // 2/3 octave
```

---


## Filters

### `parametric_eq_demo`
A parametric equalizer application.
Based on examples/filtering/parametricEqualizer.dsp

#### Usage:

```
_ : parametric_eq_demo : _ ;
```

---


### `spectral_tilt_demo`
A spectral tilt application.
Based on examples/filtering/parametricEqualizer.dsp

#### Usage

```
_ : spectral_tilt_demo(N) : _ ;
```

Where:

* `N`: filter order (integer)

All other parameters interactive

---


### `mth_octave_filterbank_demo` and `filterbank_demo`
Graphic Equalizer: Each filter-bank output signal routes through a fader.
Based on examples/filtering/filterBank.dsp

#### Usage

```
_ : mth_octave_filterbank_demo(M) : _
_ : filterbank_demo : _
```

Where: 

* `N`: number of bands per octave

---


## Effects

### `cubicnl_demo`
Distortion demo application.
Based on examples/dynamic/distortion.dsp

#### Usage: 

```
_ : cubicnl_demo : _;
```

---


### `gate_demo`
Gate demo application.
Based on examples/dynamic/noiseGate.dsp

#### Usage

```
_,_ : gate_demo : _,_;
```

---


### `compressor_demo`
Compressor demo application.
Based on examples/dynamic/compressor.dsp

#### Usage

```
_,_ : compressor_demo : _,_;
```

---


### `exciter`
Psychoacoustic harmonic exciter, with GUI.
Based on examples/psychoacoustic/harmonicExciter.dsp

#### Usage

```
_ : exciter : _
```

#### References

* <https://secure.aes.org/forum/pubs/ebriefs/?elib=16939>
* <https://www.researchgate.net/publication/258333577_Modeling_the_Harmonic_Exciter>

---


### `moog_vcf_demo`
Illustrate and compare all three Moog VCF implementations above.
Based on examples/filtering/moogVCF.dsp

#### Usage

```
_ : moog_vcf_demo : _;
```

---


### `wah4_demo`
Wah pedal application.
Based on examples/filtering/wahPedal.dsp

#### Usage

```
_ : wah4_demo : _;
```

---


### `crybaby_demo`
Crybaby effect application.
Based on examples/filtering/cryBaby.dsp

#### Usage

```
_ : crybaby_demo : _ ;
```

---


### `vocoder_demo`
Use example of the vocoder function where an impulse train is used
as excitation.
Based on examples/filtering/vocoder.dsp

#### Usage

```
_ : vocoder_demo : _;
```

---


### `flanger_demo`
Flanger effect application.
Based on examples/phasing/flanger.dsp

#### Usage

```
_,_ : flanger_demo : _,_;
```

---


### `phaser2_demo`
Phaser effect demo application.
Based on examples/phasing/phaser.dsp

#### Usage

```
_,_ : phaser2_demo : _,_;
```

---


### `freeverb_demo`
Freeverb demo application
Based on examples/reverb/freeverb.dsp

#### Usage

```
_,_ : freeverb_demo : _,_;
```

---


### `stereo_reverb_tester`
Handy test inputs for reverberator demos below.
Based on examples/reverb/reverbTester.dsp

#### Usage

```
_ : stereo_reverb_tester : _
```

---


### `fdnrev0_demo`
A reverb application using `fdnrev0`.
Based on examples/reverb/fdnrev.dsp

#### Usage

```
_,_ : fdnrev0_demo(N,NB,BBSO) : _,_
```

Where:

* `n`: Feedback Delay Network (FDN) order / number of delay lines used = 
 order of feedback matrix / 2, 4, 8, or 16 [extend primes array below for 
 32, 64, ...]
* `nb`: Number of frequency bands / Number of (nearly) independent T60 controls
 / Integer 3 or greater
* `bbso` = Butterworth band-split order / order of lowpass/highpass bandsplit 
 used at each crossover freq / odd positive integer

---


### `zita_rev_fdn_demo`
Reverb demo application based on `zita_rev_fdn`.
Based on examples/reverb/zitaRevFDN.dsp

#### Usage

```
si.bus(8) : zita_rev_fdn_demo : si.bus(8)
```

---


### `zita_rev1`
Example GUI for `zita_rev1_stereo` (mostly following the Linux `zita-rev1` GUI).

Only the dry/wet and output level parameters are "dezippered" here.  If
parameters are to be varied in real time, use `smooth(0.999)` or the like
in the same way.

#### Usage

```
_,_ : zita_rev1 : _,_
```

#### Reference

<http://www.kokkinizita.net/linuxaudio/zita-rev1-doc/quickguide.html>

---


## Generators

### `sawtooth_demo`
An application demonstrating the different sawtooth oscillators of Faust.
Based on examples/generator/sawtoothLab.dsp

#### Usage  

```
sawtooth_demo : _
```

---


### `virtual_analog_oscillator_demo`
Virtual analog oscillator demo application.
Based on examples/generator/virtualAnalog.dsp

#### Usage

```
virtual_analog_oscillator_demo : _
```

---


### `oscrs_demo` 
Simple application demoing filter based oscillators.

#### Usage

```
oscrs_demo : _
```

---

