
# noise.lib 
A library of noise generators.

It should be used using the `no` environment:

```
no = library("noise.lib");
process = no.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `no`
environment:

```
import("stdfaust.lib");
process = no.functionCall;
```

## Functions Reference

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

