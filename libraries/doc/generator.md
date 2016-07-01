
# oscillator.lib 
This library contains a collection of sound generators.

It should be used using the `ge` environment:

```
os = library("oscillator.lib");
process = os.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ge`
environment:

```
import("stdfaust.lib");
process = os.functionCall;
```

## Noises

### `noise()`
White noise generator (outputs random number between -1 and 1).

#### Usage

```
noise : _
```

---


### `multirandom(n)`
Generates multiple decorrelated random numbers 
in parallel. 

#### Usage
```
multirandom(n) : _
```

Where:

* `n`: the number of decorrelated random numbers in parallel

---


### `multinoise(n)`
Generates multiple decorrelated noises
in parallel.

#### Usage

```
multinoise(n) : _
```

Where:

* `n`: the number of decorrelated random numbers in parallel

---


### `noises(n,i)`
TODO: not sure what the point is with this one.

---


### `pink_noise`
Pink noise (1/f noise) generator (third-order approximation)

#### Usage

```
pink_noise : _;
```

#### Reference:

<https://ccrma.stanford.edu/~jos/sasp/Example_Synthesis_1_F_Noise.html>

---


### `pink_noise_vm`
Multi pink noise generator.

#### Usage

```
pink_noise_vm(N) : _;
```

Where: 

* `N`: number of latched white-noise processes to sum,
 not to exceed sizeof(int) in C++ (typically 32).

#### References

* <http://www.dsprelated.com/showarticle/908.php>
* <http://www.firstpr.com.au/dsp/pink-noise/#Voss-McCartney>

---


### `lfnoise`, `lfnoise0` and `lfnoiseN`
Low-frequency noise generators (Butterworth-filtered downsampled white noise)

#### Usage

```
lfnoise0(rate) : _;   // new random number every int(SR/rate) samples or so
lfnoiseN(N,rate) : _; // same as "lfnoise0(rate) : lowpass(N,rate)" [see filter.lib]
lfnoise(rate) : _;    // same as "lfnoise0(rate) : seq(i,5,lowpass(N,rate))" (no overshoot)
```

#### Example 

(view waveforms in faust2octave):

```
rate = SR/100.0; // new random value every 100 samples (SR from music.lib)
process = lfnoise0(rate),   // sampled/held noise (piecewise constant)
          lfnoiseN(3,rate), // lfnoise0 smoothed by 3rd order Butterworth LPF
          lfnoise(rate);    // lfnoise0 smoothed with no overshoot
```

---


## Wave-Table-Based Oscillators

### `sinwaveform(tablesize)`
Sine waveform ready to use with a `rdtable`.

#### Usage

```
sinwaveform(tablesize) : _
```

Where:

* `tablesize`: the table size

---


### `coswaveform(tablesize)`
Cosine waveform ready to use with a `rdtable`.

#### Usage

```
coswaveform(tablesize) : _
```

Where:

* `tablesize`: the table size

---


### `phasor(tablesize,freq)`
A simple phasor to be used with a `rdtable`.

#### Usage

```
phasor(tablesize,freq) : _
```

Where:

* `tablesize`: the table size
* `freq`: the frequency of the wave (Hz)

---


### `oscsin(freq)`
Sine wave oscillator.

#### Usage

```
oscsin(freq) : _
```

Where:

* `freq`: the frequency of the wave (Hz)

---


### `osc(freq)`
Sine wave oscillator (same as `oscsin`).

#### Usage

```
osc(freq) : _
```

Where:

* `freq`: the frequency of the wave (Hz)

---


### `oscos(freq)`
Cosine wave oscillator.

#### Usage

```
osccos(freq) : _
```

Where:

* `freq`: the frequency of the wave (Hz)

---


### `oscp(freq,p)`
A sine wave generator with controllable phase.

#### Usage

```
oscp(freq,p) : _
```

Where:

* `freq`: the frequency of the wave (Hz)
* `p`: the phase in radian

---


### `osci(freq)`
Interpolated phase sine wave oscillator.

#### Usage

```
osci(freq) : _
```

Where:

* `freq`: the frequency of the wave (Hz)

---


## Virtual Analog Oscillators
Mostly elements from old "oscillator.lib".

Virtual analog oscillators and filter-based oscillators.

Low-frequency oscillators have prefix `lf_`
(no aliasing suppression, signal-means not necessarily zero)

### Low Frequency Impulse and Pulse Trains, Square and Triangle Waves 
Low Frequency Impulse and Pulse Trains, Square and Triangle Waves

`lf_imptrain`, `lf_pulsetrainpos`, `lf_squarewavepos`, `lf_squarewave`, 
`lf_trianglepos`

#### Usage

```
lf_imptrain(freq) : _
lf_pulsetrainpos(freq,duty) : _
lf_squarewavepos(freq) : _
lf_squarewave(freq) : _
lf_trianglepos(freq) : _
```

Where:

* `freq`: frequency in Hz
* `duty`: duty cycle between 0 and 1

#### Notes

* Suffix 'pos' means the function is nonnegative, otherwise ~ zero mean
* All impulse and pulse trains jump to 1 at time 0

---


### Low Frequency Sawtooths
Low Frequency Sawtooths

`lf_rawsaw`, `lf_sawpos`, `lf_sawpos_phase`

Sawtooth waveform oscillators for virtual analog synthesis et al.
The 'simple' versions (`lf_rawsaw`, `lf_sawpos` and `saw1`), are mere samplings of
the ideal continuous-time ("analog") waveforms.  While simple, the
aliasing due to sampling is quite audible.  The differentiated
polynomial waveform family (`saw2`, `sawN`, and derived functions)
do some extra processing to suppress aliasing (not audible for
very low fundamental frequencies).  According to Lehtonen et al.
(JASA 2012), the aliasing of `saw2` should be inaudible at fundamental
frequencies below 2 kHz or so, for a 44.1 kHz sampling rate and 60 dB SPL
presentation level;  fundamentals 415 and below required no aliasing
suppression (i.e., `saw1` is ok).

#### Usage

```
lf_rawsaw(periodsamps) : _
lf_sawpos(freq) : _
lf_sawpos_phase(phase,freq) : _
saw1(freq) : _
```

---


### Bandlimited Sawtooth
Bandlimited Sawtooth

`sawN(N,freq)`, `sawNp`, `saw2dpw(freq)`, `saw2(freq)`, `saw3(freq)`,
`saw4(freq)`, `saw5(freq)`, `saw6(freq)`, `sawtooth(freq)`, `saw2f2(freq)`
`saw2f4(freq)`

#### Method 1 (`saw2`)

Polynomial Transition Regions (PTR) (for aliasing suppression)

##### Reference

* Kleimola, J.; Valimaki, V., "Reducing Aliasing from Synthetic Audio
 Signals Using Polynomial Transition Regions," in Signal Processing
 Letters, IEEE , vol.19, no.2, pp.67-70, Feb. 2012
* <https://aaltodoc.aalto.fi/bitstream/handle/123456789/7747/publication6.pdf?sequence=9>
* <http://research.spa.aalto.fi/publications/papers/spl-ptr/>

#### Method 2 (`sawN`)

Differentiated Polynomial Waves (DPW) (for aliasing suppression)

##### Reference

"Alias-Suppressed Oscillators based on Differentiated Polynomial Waveforms",
Vesa Valimaki, Juhan Nam, Julius Smith, and Jonathan Abel,
IEEE Tr. Acoustics, Speech, and Language Processing (IEEE-ASLP),
Vol. 18, no. 5, May 2010.

#### Other Cases

Correction-filtered versions of `saw2`: `saw2f2`, `saw2f4`
The correction filter compensates "droop" near half the sampling rate.
See reference for sawN. 

#### Usage

```
sawN(N,freq) : _
sawNp(N,freq,phase) : _
saw2dpw(freq) : _
saw2(freq) : _
saw3(freq) : _ // based on sawN
saw4(freq) : _ // based on sawN
saw5(freq) : _ // based on sawN
saw6(freq) : _ // based on sawN
sawtooth(freq) : _ // = saw2
saw2f2(freq) : _
saw2f4(freq) : _
```

Where:

* `N`: polynomial order
* `freq`: frequency in Hz
* `phase`: phase

---


### Bandlimited Pulse, Square, and Impulse Trains
Bandlimited Pulse, Square, and Impulse Trains

`pulsetrainN`, `pulsetrain`, `squareN`, `square`, `imptrain`, `imptrainN`,
`triangle`, `triangleN`

All are zero-mean and meant to oscillate in the audio frequency range.
Use simpler sample-rounded lf_* versions above for LFOs.

#### Usage

```
pulsetrainN(N,freq,duty) : _ 
pulsetrain(freq, duty) : _ // = pulsetrainN(2) 
squareN(N, freq) : _
square : _ // = squareN(2)
imptrainN(N,freq) : _
imptrain : _ // = imptrainN(2)
triangleN(N,freq) : _
triangle : _ // = triangleN(2)
```

Where:

* `N`: polynomial order
* `freq`: frequency in Hz

---


## Filter-Based Oscillators
Filter-Based Oscillators

#### Usage 

```
osc[b|r|rs|rc|s|w](f), where f = frequency in Hz.
```

#### References

* <http://lac.linuxaudio.org/2012/download/lac12-slides-jos.pdf>
* <https://ccrma.stanford.edu/~jos/pdf/lac12-paper-jos.pdf>

### `oscb`
Sinusoidal oscillator based on the biquad

---


### `oscr`,`oscrs` and `oscs`
Sinusoidal oscillator based on 2D vector rotation,
 = undamped "coupled-form" resonator
 = lossless 2nd-order normalized ladder filter.

`oscr` = `oscrs`, `oscrs` generates a sine wave and `oscs` a cosine.

#### Reference:

<https://ccrma.stanford.edu/~jos/pasp/Normalized_Scattering_Junctions.html>

---


### `oscs`
Sinusoidal oscillator based on the state variable filter
= undamped "modified-coupled-form" resonator
= "magic circle" algorithm used in graphics

---


### `oscw`, `oscwq`, `oscwc` and `oscws`
Sinusoidal oscillator based on the waveguide resonator wgr.

`oscwc` - unit-amplitude cosine oscillator

`oscws` - unit-amplitude sine oscillator

`oscq`  - unit-amplitude cosine and sine (quadrature) oscillator

`oscw`  - default = `oscwc` for maximum speed

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Digital_Waveguide_Oscillator.html>

---

