
# filter.lib 
A library of filters and of more advanced filter-based sound processor organized 
in 18 sections:

* Basic Filters
* Comb Filters
* Direct-Form Digital Filter Sections
* Direct-Form Second-Order Biquad Sections
* Ladder/Lattice Digital Filters
* Useful Special Cases
* Ladder/Lattice Allpass Filters
* Digital Filter Sections Specified as Analog Filter Sections
* Simple Resonator Filters
* Butterworth Lowpass/Highpass Filters
* Special Filter-Bank Delay-Equalizing Allpass Filters
* Elliptic (Cauer) Lowpass Filters
* Elliptic Highpass Filters
* Butterworth Bandpass/Bandstop Filters
* Elliptic Bandpass Filters
* Parametric Equalizers (Shelf, Peaking)
* Mth-Octave Filter-Banks
* Arbritary-Crossover Filter-Banks and Spectrum Analyzers

It should be used using the `fi` environment:

```
fi = library("filter.lib");
process = fi.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `fi`
environment:

```
import("stdfaust.lib");
process = fi.functionCall;
```

## Basic Filters

### `zero(z)`
One zero filter. Difference equation: y(n) = x(n) - z * x(n-1).

#### Usage

```
_ : zero(z) : _
```

Where:

* `z`: location of zero along real axis in z-plane

#### Reference 
<https://ccrma.stanford.edu/~jos/filters/One_Zero.html>

---


### `pole(p)`
One pole filter. Could also be called a "leaky integrator". 
Difference equation: y(n) = x(n) + p * y(n-1).

#### Usage

```
_ : pole(z) : _
```

Where:

* `p`: pole location = feedback coefficient

#### Reference 
<https://ccrma.stanford.edu/~jos/filters/One_Pole.html>

---


### `integrator`
Same as `pole(1)` [implemented separately for block-diagram clarity].

---


### `dcblockerat(fb)`
DC blocker with configurable break frequency. 
The amplitude response is substantially flat above fb,
and sloped at about +6 dB/octave below fb.
Derived from the analog transfer function 
H(s) = s / (s + 2*PI*fb) 
by the low-frequency-matching bilinear transform method
(i.e., the standard frequency-scaling constant 2*SR).

#### Usage

```
_ : dcblockerat(fb) : _
```

Where:

* `fb`: "break frequency" in Hz, i.e., -3 dB gain frequency.

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Bilinear_Transformation.html>

---


### `dcblocker`
DC blocker. Default dc blocker has -3dB point near 35 Hz (at 44.1 kHz)
and high-frequency gain near 1.0025 (due to no scaling).

#### Usage

```
_ : dcblocker : _
```

---


## Comb Filters

### `ff_comb` and `ff_fcomb`
Feed-Forward Comb Filter. Note that `ff_comb` requires integer delays  
(uses `delay()`  internally) while `ff_fcomb` takes floating-point delays 
(uses `fdelay()` internally).

#### Usage

```
_ : ff_comb(maxdel,intdel,b0,bM) : _
_ : ff_fcomb(maxdel,del,b0,bM) : _
```

Where:

* `maxdel`: maximum delay (a power of 2)
* `intdel`: current (integer) comb-filter delay between 0 and maxdel
* `del`: current (float) comb-filter delay between 0 and maxdel
* `b0`: gain applied to delay-line input
* `bM`: gain applied to delay-line output and then summed with input

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Feedforward_Comb_Filters.html>

---


### `ffcombfilter`
Typical special case of `ff_comb()` where: `b0 = 1`.

---


### `fb_comb` and `fb_fcomb`
Feed-Back Comb Filter.

#### Usage 

```
_ : fb_comb(maxdel,intdel,b0,aN) : _
_ : fb_fcomb(maxdel,del,b0,aN) : _
```

Where:

* `maxdel`: maximum delay (a power of 2)
* `intdel`: current (integer) comb-filter delay between 0 and maxdel
* `del`: current (float) comb-filter delay between 0 and maxdel
* `b0`: gain applied to delay-line input and forwarded to output
* `aN`: minus the gain applied to delay-line output before summing with the input 
 and feeding to the delay line

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Feedback_Comb_Filters.html>

---


### `rev1`
Special case of `fb_comb` (`rev1(maxdel,N,g)`).
The "rev1 section" dates back to the 1960s in computer-music reverberation.
See the `jcrev` and `brassrev` in `reverb.lib` for usage examples.

---


### `fbcombfilter` and `ffbcombfilter`
Other special cases of Feed-Back Comb Filter.

#### Usage 

```
_ : fbcombfilter(maxdel,intdel,g) : _
_ : ffbcombfilter(maxdel,del,g) : _
```

Where:

* `maxdel`: maximum delay (a power of 2)
* `intdel`: current (integer) comb-filter delay between 0 and maxdel
* `del`: current (float) comb-filter delay between 0 and maxdel
* `g`: feedback gain

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Feedback_Comb_Filters.html>

---


### `allpass_comb` and `allpass_fcomb`
Schroeder Allpass Comb Filter. Note that 

```
allpass_comb(maxlen,len,aN) = ff_comb(maxlen,len,aN,1) : fb_comb(maxlen,len-1,1,aN);
```

which is a direct-form-1 implementation, requiring two delay lines.
The implementation here is direct-form-2 requiring only one delay line.

#### Usage

``` 
_ : allpass_comb (maxdel,intdel,aN) : _
_ : allpass_fcomb(maxdel,del,aN) : _
```

Where:

* `maxdel`: maximum delay (a power of 2)
* `intdel`: current (integer) comb-filter delay between 0 and maxdel
* `del`: current (float) comb-filter delay between 0 and maxdel
* `aN`: minus the feedback gain

#### References

* <https://ccrma.stanford.edu/~jos/pasp/Allpass_Two_Combs.html>
* <https://ccrma.stanford.edu/~jos/pasp/Schroeder_Allpass_Sections.html>
* <https://ccrma.stanford.edu/~jos/filters/Four_Direct_Forms.html>

---


### `rev2`
Special case of `allpass_comb` (`rev2(maxlen,len,g)`).
The "rev2 section" dates back to the 1960s in computer-music reverberation.
See the `jcrev` and `brassrev` in `reverb.lib` for usage examples.

---


### `allpass_fcomb5` and `allpass_fcomb1a`
Same as `allpass_fcomb` but use `fdelay5` and `fdelay1a` internally 
(Interpolation helps - look at an fft of faust2octave on

```
`1-1' <: allpass_fcomb(1024,10.5,0.95), allpass_fcomb5(1024,10.5,0.95);`).
```

---


## Direct-Form Digital Filter Sections

### `iir(tfN)`
Nth-order Infinite-Impulse-Response (IIR) digital filter,
implemented in terms of the Transfer-Function (TF) coefficients.
Such filter structures are termed "direct form".

#### Usage

```
  _ : iir(bcoeffs,acoeffs) : _
```

Where:

* `order`: filter order (int) = max(#poles,#zeros)
* `bcoeffs`: (b0,b1,...,b_order) = TF numerator coefficients
* `acoeffs`: (a1,...,a_order) = TF denominator coeffs (a0=1)

#### Reference

<https://ccrma.stanford.edu/~jos/filters/Four_Direct_Forms.html>

---


### `fir` 
FIR filter (convolution of FIR filter coefficients with a signal)

#### Usage

``` 
_ : fir(bv) : _
```

Where: 

* `bv` = b0,b1,...,bn is a parallel bank of coefficient signals.

#### Note 

`bv` is processed using pattern-matching at compile time,
      so it must have this normal form (parallel signals).

#### Example

Smoothing white noise with a five-point moving average:

```
bv = .2,.2,.2,.2,.2;
process = noise : fir(bv);
```

Equivalent (note double parens):

```
process = noise : fir((.2,.2,.2,.2,.2));
```

---


### `conv` and `convN`
Convolution of input signal with given coefficients.

#### Usage

```
_ : conv((k1,k2,k3,...,kN)) : _; // Argument = one signal bank
_ : convN(N,(k1,k2,k3,...)) : _; // Useful when N < count((k1,...))
```

---


### `tf1`, `tf2` and `tf3`
tfN = N'th-order direct-form digital filter.

#### Usage

```
_ : tf1(b0,b1,a1) : _
_ : tf2(b0,b1,b2,a1,a2) : _
_ : tf3(b0,b1,b2,b3,a1,a2,a3) : _
```

Where:

* `a`: the poles
* `b`: the zeros

#### Reference
<https://ccrma.stanford.edu/~jos/fp/Direct_Form_I.html>

---


### `notchw(width,freq)`
Simple notch filter based on a biquad (`tf2`).

#### Usage:

```
_ : notchw(width,freq) : _
```

Where:

* `width`: "notch width" in Hz (approximate)
* `freq`: "notch frequency" in Hz

#### Reference
<https://ccrma.stanford.edu/~jos/pasp/Phasing_2nd_Order_Allpass_Filters.html>

---


## Direct-Form Second-Order Biquad Sections
Direct-Form Second-Order Biquad Sections

#### Reference

<https://ccrma.stanford.edu/~jos/filters/Four_Direct_Forms.html>

### `tf21`, `tf22`, `tf22t` and `tf21t`
tfN = N'th-order direct-form digital filter where: 

* `tf21` is tf2, direct-form 1
* `tf22` is tf2, direct-form 2
* `tf22t` is tf2, direct-form 2 transposed
* `tf21t` is tf2, direct-form 1 transposed

#### Usage

```
_ : tf21(b0,b1,b2,a1,a2) : _
_ : tf22(b0,b1,b2,a1,a2) : _
_ : tf22t(b0,b1,b2,a1,a2) : _
_ : tf21t(b0,b1,b2,a1,a2) : _
```

Where:

* `a`: the poles
* `b`: the zeros

#### Reference
<https://ccrma.stanford.edu/~jos/fp/Direct_Form_I.html>

---


## Ladder/Lattice Digital Filters 
Ladder and lattice digital filters generally have superior numerical
properties relative to direct-form digital filters.  They can be derived
from digital waveguide filters, which gives them a physical interpretation.


### `av2sv`
Compute reflection coefficients sv from transfer-function denominator av.

#### Usage

```
sv = av2sv(av)
```

Where:

* `av`: parallel signal bank `a1,...,aN`
* `sv`: parallel signal bank `s1,...,sN`

where `ro = ith` reflection coefficient, and
      `ai` = coefficient of `z^(-i)` in the filter
         transfer-function denominator `A(z)`.

#### Reference

  <https://ccrma.stanford.edu/~jos/filters/Step_Down_Procedure.html> 
  (where reflection coefficients are denoted by k rather than s).

---


### `bvav2nuv`
Compute lattice tap coefficients from transfer-function coefficients.

#### Usage

```
nuv = bvav2nuv(bv,av)
```

Where:

* `av`: parallel signal bank `a1,...,aN`
* `bv`: parallel signal bank `b0,b1,...,aN`
* `nuv`: parallel signal bank  `nu1,...,nuN`

where `nui` is the i'th tap coefficient,
      `bi` is the coefficient of `z^(-i)` in the filter numerator,
      `ai` is the coefficient of `z^(-i)` in the filter denominator

---


### `iir_lat2(bc,av)`
Two-multiply latice IIR filter or arbitrary order.

#### Usage

```
_ : iir_lat2(bv,av) : _
```

Where:

* bv: zeros as a bank of parallel signals
* av: poles as a bank of parallel signals

---


### `allpassnt(n,sv)`
Two-multiply lattice allpass (nested order-1 direct-form-ii allpasses).

#### Usage

```
_ : allpassnt(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

---


### `iir_kl(bc,av)`
Kelly-Lochbaum ladder IIR filter or arbitrary order.

#### Usage

```
_ : iir_kl(bv,av) : _
```

Where:

* bv: zeros as a bank of parallel signals
* av: poles as a bank of parallel signals

---


### `allpassnklt(n,sv)`
Kelly-Lochbaum ladder allpass.

#### Usage:

```
_ : allpassklt(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

---


### `iir_lat1(bc,av)`
One-multiply latice IIR filter or arbitrary order.

#### Usage

```
_ : iir_lat1(bv,av) : _
```

Where:

* bv: zeros as a bank of parallel signals
* av: poles as a bank of parallel signals

---


### `allpassn1mt(n,sv)`
One-multiply lattice allpass with tap lines.

#### Usage

```
_ : allpassn1mt(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

---


### `iir_nl(bv,av)`
Normalized ladder filter of arbitrary order.

#### Usage

```
_ : iir_nl(bv,av) : _
```

Where:

* bv: zeros as a bank of parallel signals
* av: poles as a bank of parallel signals

#### References

* J. D. Markel and A. H. Gray, Linear Prediction of Speech, New York: Springer Verlag, 1976.
* <https://ccrma.stanford.edu/~jos/pasp/Normalized_Scattering_Junctions.html>

---


### `allpassnnlt(n,sv)`
Normalized ladder allpass filter of arbitrary order.

#### Usage:

```
_ : allpassnnlt(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1,1)

#### References

* J. D. Markel and A. H. Gray, Linear Prediction of Speech, New York: Springer Verlag, 1976.
* <https://ccrma.stanford.edu/~jos/pasp/Normalized_Scattering_Junctions.html>

---


## Useful Special Cases

### `tf2np`
Biquad based on a stable second-order Normalized Ladder Filter
(more robust to modulation than `tf2` and protected against instability).

#### Usage

```
_ : tf2np(b0,b1,b2,a1,a2) : _
```

Where:

* `a`: the poles
* `b`: the zeros

---


### `wgr(f,r,x)`
Second-order transformer-normalized digital waveguide resonator.

#### Usage

``` 
_ : wgr(f,r) : _
```

Where:

* `f`: resonance frequency (Hz)
* `r`: loss factor for exponential decay (set to 1 to make a numerically stable oscillator)

#### References

* <https://ccrma.stanford.edu/~jos/pasp/Power_Normalized_Waveguide_Filters.html>
* <https://ccrma.stanford.edu/~jos/pasp/Digital_Waveguide_Oscillator.html>

---


### `nlf2`
Second order normalized digital waveguide resonator.

#### Usage 

```
_ : nlf2(f,r) : _
```

Where:

* `f`: resonance frequency (Hz)
* `r`: loss factor for exponential decay (set to 1 to make a sinusoidal oscillator)

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Power_Normalized_Waveguide_Filters.html>

---


### `apnl(a1,a2)`
Passive Nonlinear Allpass based on Pierce switching springs idea.
Switch between allpass coefficient `a1` and `a2` at signal zero crossings.

#### Usage

```
_ : apnl(a1,a2) : _
```

Where:

* `a1` and `a2`: allpass coefficients

#### Reference

* "A Passive Nonlinear Digital Filter Design ..." by John R. Pierce and Scott 
A. Van Duyne, JASA, vol. 101, no. 2, pp. 1120-1126, 1997

---


## Ladder/Lattice Allpass Filters
An allpass filter has gain 1 at every frequency, but variable phase.
Ladder/lattice allpass filters are specified by reflection coefficients.
They are defined here as nested allpass filters, hence the names allpassn*.

#### References

* <https://ccrma.stanford.edu/~jos/pasp/Conventional_Ladder_Filters.html>
* <https://ccrma.stanford.edu/~jos/pasp/Nested_Allpass_Filters.html>
* Linear Prediction of Speech, Markel and Gray, Springer Verlag, 1976

### `allpassn(n,sv)`
Two-multiply lattice - each section is two multiply-adds.

#### Usage:

```
_ : allpassn(n,sv) : _
```
#### Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

#### References

* J. O. Smith and R. Michon, "Nonlinear Allpass Ladder Filters in FAUST", in 
Proceedings of the 14th International Conference on Digital Audio Effects 
(DAFx-11), Paris, France, September 19-23, 2011.

---


### `allpassnn(n,tv)`
Normalized form - four multiplies and two adds per section,
but coefficients can be time varying and nonlinear without
"parametric amplification" (modulation of signal energy).

#### Usage:

```
_ : allpassnn(n,tv) : _
```

Where:

* `n`: the order of the filter
* `tv`: the reflexion coefficients (-PI PI)

---


### `allpasskl(n,sv)`
Kelly-Lochbaum form - four multiplies and two adds per
section, but all signals have an immediate physical
interpretation as traveling pressure waves, etc.

#### Usage:

```
_ : allpassnkl(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

---


### `allpass1m(n,sv)`
One-multiply form - one multiply and three adds per section.
Normally the most efficient in special-purpose hardware.

#### Usage:

```
_ : allpassn1m(n,sv) : _
```

Where:

* `n`: the order of the filter
* `sv`: the reflexion coefficients (-1 1)

---


## Digital Filter Sections Specified as Analog Filter Sections

### `tf2s` and `tf2snp`
Second-order direct-form digital filter,
specified by ANALOG transfer-function polynomials B(s)/A(s),
and a frequency-scaling parameter.  Digitization via the
bilinear transform is built in.

#### Usage 

```
_ : tf2s(b2,b1,b0,a1,a0,w1) : _
```
Where: 

```
        b2 s^2 + b1 s + b0
H(s) = --------------------
           s^2 + a1 s + a0
```

and `w1` is the desired digital frequency (in radians/second)
corresponding to analog frequency 1 rad/sec (i.e., `s = j`).

#### Example

A second-order ANALOG Butterworth lowpass filter,
         normalized to have cutoff frequency at 1 rad/sec,
         has transfer function

```
             1
H(s) = -----------------
        s^2 + a1 s + 1
```

where `a1 = sqrt(2)`.  Therefore, a DIGITAL Butterworth lowpass 
cutting off at `SR/4` is specified as `tf2s(0,0,1,sqrt(2),1,PI*SR/2);`

#### Method 

Bilinear transform scaled for exact mapping of w1.

#### Reference 

<https://ccrma.stanford.edu/~jos/pasp/Bilinear_Transformation.html>

---


### `tf3slf`
Analogous to tf2s above, but third order, and using the typical
low-frequency-matching bilinear-transform constant 2/T ("lf" series)
instead of the specific-frequency-matching value used in tf2s and tf1s.
Note the lack of a "w1" argument.

#### Usage

```
_ : tf3slf(b3,b2,b1,b0,a3,a2,a1,a0) : _
```

---


### `tf1s`
First-order direct-form digital filter,
specified by ANALOG transfer-function polynomials B(s)/A(s),
and a frequency-scaling parameter.

#### Usage

```
tf1s(b1,b0,a0,w1)
```
Where: 

       b1 s + b0
H(s) = ----------
          s + a0

and `w1` is the desired digital frequency (in radians/second)
corresponding to analog frequency 1 rad/sec (i.e., `s = j`).

#### Example
A first-order ANALOG Butterworth lowpass filter,
         normalized to have cutoff frequency at 1 rad/sec,
         has transfer function

          1
H(s) = -------
        s + 1

so `b0 = a0 = 1` and `b1 = 0`.  Therefore, a DIGITAL first-order 
Butterworth lowpass with gain -3dB at `SR/4` is specified as 

```
tf1s(0,1,1,PI*SR/2); // digital half-band order 1 Butterworth
```

#### Method

Bilinear transform scaled for exact mapping of w1.

#### Reference 
<https://ccrma.stanford.edu/~jos/pasp/Bilinear_Transformation.html>

---


### `tf2sb`
Bandpass mapping of `tf2s`: In addition to a frequency-scaling parameter
`w1` (set to HALF the desired passband width in rad/sec),
there is a desired center-frequency parameter wc (also in rad/s).
Thus, `tf2sb` implements a fourth-order digital bandpass filter section
specified by the coefficients of a second-order analog lowpass prototpe
section.  Such sections can be combined in series for higher orders.
The order of mappings is (1) frequency scaling (to set lowpass cutoff w1),
(2) bandpass mapping to wc, then (3) the bilinear transform, with the 
usual scale parameter `2*SR`.  Algebra carried out in maxima and pasted here.

#### Usage

```
_ : tf2sb(b2,b1,b0,a1,a0,w1,wc) : _
```

---


### `tf1sb`
First-to-second-order lowpass-to-bandpass section mapping,
analogous to tf2sb above.

#### Usage

```
_ : tf1sb(b1,b0,a0,w1,wc) : _
```

---


## Simple Resonator Filters

### `resonlp`, `resonhp` and `resonbp`
Simple resonant lowpass, highpass and bandpass filters based on `tf2s`.

#### Usage

```
_ : resonlp(fc,Q,gain) : _
_ : resonhp(fc,Q,gain) : _
_ : resonbp(fc,Q,gain) : _

```

Where:

* `fc`: center frequency (Hz)
* `Q`: q
* `gain`: gain (0-1)

---


## Butterworth Lowpass/Highpass Filters

### `lowpass` and `highpass`
Nth-order Butterworth lowpass or highpass filters.

#### Usage

```
_ : lowpass(N,fc) : _
_ : highpass(N,fc) : _
```

Where:

* `N`: filter order (number of poles) [nonnegative constant integer]
* `fc`: desired cut-off frequency (-3dB frequency) in Hz

#### References

* <https://ccrma.stanford.edu/~jos/filters/Butterworth_Lowpass_Design.html>
* `butter` function in Octave `("[z,p,g] = butter(N,1,'s');")`

---


### `lowpass0_highpass1(s,N,fc)`
TODO

---


## Special Filter-Bank Delay-Equalizing Allpass Filters
These special allpass filters are needed by filterbank et al. below.
They are equivalent to (`lowpass(N,fc)` +|- `highpass(N,fc))/2`, but with 
canceling pole-zero pairs removed (which occurs for odd N).

### `lowpass_plus`|`minus_highpass`
TODO

---


## Elliptic (Cauer) Lowpass Filters
Elliptic (Cauer) Lowpass Filters

#### References

* <http://en.wikipedia.org/wiki/Elliptic_filter
* functions `ncauer` and `ellip` in Octave

### `lowpass3e(fc)`
Third-order Elliptic (Cauer) lowpass filter.

#### Usage

```
_ : lowpass3e(fc) : _
```

Where: 

* `fc`: -3dB frequency in Hz

#### Design

For spectral band-slice level display (see `octave_analyzer3e`):

```
[z,p,g] = ncauer(Rp,Rs,3);  % analog zeros, poles, and gain, where
Rp = 60  % dB ripple in stopband
Rs = 0.2 % dB ripple in passband
```

---


### `lowpass6e(fc)`
Sixth-order Elliptic/Cauer lowpass filter.

#### Usage

```
_ : lowpass6e(fc) : _
```

Where: 

* `fc`: -3dB frequency in Hz

#### Design 

For spectral band-slice level display (see octave_analyzer6e):

```
[z,p,g] = ncauer(Rp,Rs,6);  % analog zeros, poles, and gain, where
 Rp = 80  % dB ripple in stopband
 Rs = 0.2 % dB ripple in passband
```

---


## Elliptic Highpass Filters

### `highpass3e(fc)`
Third-order Elliptic (Cauer) highpass filter. Inversion of `lowpass3e` wrt unit 
circle in s plane (s <- 1/s)

#### Usage

```
_ : highpass3e(fc) : _
```

Where: 

* `fc`: -3dB frequency in Hz

---


### `highpass6e(fc)`
Sixth-order Elliptic/Cauer highpass filter. Inversion of lowpass3e wrt unit 
circle in s plane (s <- 1/s)

#### Usage

```
_ : highpass6e(fc) : _
```

Where: 

* `fc`: -3dB frequency in Hz

---


## Butterworth Bandpass/Bandstop Filters

### `bandpass` and `bandstop`
Order 2*Nh Butterworth bandpass filter made using the transformation
`s <- s + wc^2/s` on `lowpass(Nh)`, where `wc` is the desired bandpass center 
frequency.  The `lowpass(Nh)` cutoff `w1` is half the desired bandpass width.
A notch-like "bandstop" filter is similarly made from `highpass(Nh)`.

#### Usage

```
_ : bandpass(Nh,fl,fu) : _
_ : bandstop(Nh,fl,fu) : _
```
Where:

* `Nh`: HALF the desired bandpass/bandstop order (which is therefore even)
* `fl`: lower -3dB frequency in Hz
* `fu`: upper -3dB frequency in Hz
Thus, the passband (stopband) width is `fu-fl`, 
      and its center frequency is `(fl+fu)/2`.

#### Reference

<http://cnx.org/content/m16913/latest/>

---


## Elliptic Bandpass Filters

### `bandpass6e`
Order 12 elliptic bandpass filter analogous to `bandpass(6)`.

---


### `bandpass12e`
Order 24 elliptic bandpass filter analogous to `bandpass(6)`.

---


## Parametric Equalizers (Shelf, Peaking)
Parametric Equalizers (Shelf, Peaking)

#### References

* <http://en.wikipedia.org/wiki/Equalization>
* <http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt>
* Digital Audio Signal Processing, Udo Zolzer, Wiley, 1999, p. 124
* https://ccrma.stanford.edu/~jos/filters/Low_High_Shelving_Filters.html>
* https://ccrma.stanford.edu/~jos/filters/Peaking_Equalizers.html>
* maxmsp.lib in the Faust distribution
* bandfilter.dsp in the faust2pd distribution 

### `low_shelf` and `lowshelf_other_freq`
First-order "low shelf" filter (gain boost|cut between dc and some frequency)

#### Usage

``` 
_ : lowshelf(N,L0,fx) : _
_ : lowshelf_other_freq(N,L0,fx) : _
```

Where:
* `N`: filter order 1, 3, 5, ... (odd only).
* `L0`: desired level (dB) between dc and fx (boost `L0>0` or cut `L0<0`)
* `fx`: -3dB frequency of lowpass band (`L0>0`) or upper band (`L0<0`)
      (see "SHELF SHAPE" below).

The gain at SR/2 is constrained to be 1.
The generalization to arbitrary odd orders is based on the well known
fact that odd-order Butterworth band-splits are allpass-complementary
(see filterbank documentation below for references).

#### Shelf Shape
The magnitude frequency response is approximately piecewise-linear
on a log-log plot ("BODE PLOT").  The Bode "stick diagram" approximation
L(lf) is easy to state in dB versus dB-frequency lf = dB(f):

* L0 > 0:
 * L(lf) = L0, f between 0 and fx = 1st corner frequency;
 * L(lf) = L0 - N * (lf - lfx), f between fx and f2 = 2nd corner frequency;
 * L(lf) = 0, lf > lf2.
 * lf2 = lfx + L0/N = dB-frequency at which level gets back to 0 dB.
* L0 < 0:
 * L(lf) = L0, f between 0 and f1 = 1st corner frequency;
 * L(lf) = - N * (lfx - lf), f between f1 and lfx = 2nd corner frequency;
 * L(lf) = 0, lf > lfx.
 * lf1 = lfx + L0/N = dB-frequency at which level goes up from L0.

 See `lowshelf_other_freq`.

---


### `high_shelf` and `highshelf_other_freq`
First-order "high shelf" filter (gain boost|cut above some frequency).

#### Usage

```
_ : highshelf(N,Lpi,fx) : _
_ : highshelf_other_freq(N,Lpi,fx) : _
```

Where:

* `N`: filter order 1, 3, 5, ... (odd only).
* `Lpi`: desired level (dB) between fx and SR/2 (boost Lpi>0 or cut Lpi<0)
* `fx`: -3dB frequency of highpass band (L0>0) or lower band (L0<0)
       (Use highshelf_other_freq() below to find the other one.)

The gain at dc is constrained to be 1.
See `lowshelf` documentation above for more details on shelf shape.

---


### `peak_eq`
Second order "peaking equalizer" section (gain boost or cut near some frequency)
Also called a "parametric equalizer" section.

#### Usage 

```
_ : peak_eq(Lfx,fx,B) : _;
```

Where:

* `Lfx`: level (dB) at fx (boost Lfx>0 or cut Lfx<0)
* `fx`: peak frequency (Hz)
* `B`: bandwidth (B) of peak in Hz

---


### `peak_eq_cq`
Constant-Q second order peaking equalizer section. 

#### Usage

```
_ : peak_eq_cq(Lfx,fx,Q) : _;
```

Where:

* `Lfx`: level (dB) at fx
* `fx`: boost or cut frequency (Hz)
* `Q`: "Quality factor" = fx/B where B = bandwidth of peak in Hz

---


### `peak_eq_rm`
Regalia-Mitra second order peaking equalizer section

#### Usage

```
_ : peak_eq_rm(Lfx,fx,tanPiBT) : _;
```

Where:

* `Lfx`: level (dB) at fx
* `fx`: boost or cut frequency (Hz)
* `tanPiBT`: `tan(PI*B/SR)`, where B = -3dB bandwidth (Hz) when 10^(Lfx/20) = 0
        ~ PI*B/SR for narrow bandwidths B

#### Reference 

P.A. Regalia, S.K. Mitra, and P.P. Vaidyanathan,
"The Digital All-Pass Filter: A Versatile Signal Processing Building Block"
Proceedings of the IEEE, 76(1):19-37, Jan. 1988.  (See pp. 29-30.)

---


### `spectral_tilt`
Spectral tilt filter, providing an arbitrary spectral rolloff factor
alpha in (-1,1), where
 -1 corresponds to one pole (-6 dB per octave), and
 +1 corresponds to one zero (+6 dB per octave).
In other words, alpha is the slope of the ln magnitude versus ln frequency.
For a "pinking filter" (e.g., to generate 1/f noise from white noise),
set alpha to -1/2.

#### Usage

```
_ : spectral_tilt(N,f0,bw,alpha) : _
```
Where:

* `N`: desired integer filter order (fixed at compile time)
* `f0`: lower frequency limit for desired roll-off band
* `bw`: bandwidth of desired roll-off band
* `alpha`: slope of roll-off desired in nepers per neper
        (ln mag / ln radian freq)

#### Examples
See `spectral_tilt_demo`.

#### Reference
Link to appear here when write up is done

---


### `levelfilter` and `levelfilterN`
Dynamic level lowpass filter.

#### Usage

```
_ : levelfilter(L,freq) : _
_ : levelfilterN(N,freq,L) : _
```

Where:

* `L`: desired level (in dB) at Nyquist limit (SR/2), e.g., -60
* `freq`: corner frequency (-3dB point) usually set to fundamental freq
* `N`: Number of filters in series where L = L/N

#### Reference

<https://ccrma.stanford.edu/realsimple/faust_strings/Dynamic_Level_Lowpass_Filter.html>

---


## Mth-Octave Filter-Banks
Mth-octave filter-banks split the input signal into a bank of parallel signals, one 
for each spectral band. They are related to the Mth-Octave Spectrum-Analyzers in 
`analysis.lib`.
The documentation of this library contains more details about the implementation.
The parameters are:

* `M`: number of band-slices per octave (>1)
* `N`: total number of bands (>2)
* `ftop`: upper bandlimit of the Mth-octave bands (<SR/2)

In addition to the Mth-octave output signals, there is a highpass signal
containing frequencies from ftop to SR/2, and a "dc band" lowpass signal 
containing frequencies from 0 (dc) up to the start of the Mth-octave bands.
Thus, the N output signals are

```
highpass(ftop), MthOctaveBands(M,N-2,ftop), dcBand(ftop*2^(-M*(N-1)))
```

A Filter-Bank is defined here as a signal bandsplitter having the
property that summing its output signals gives an allpass-filtered
version of the filter-bank input signal.  A more conventional term for
this is an "allpass-complementary filter bank".  If the allpass filter
is a pure delay (and possible scaling), the filter bank is said to be
a "perfect-reconstruction filter bank" (see Vaidyanathan-1993 cited
below for details).  A "graphic equalizer", in which band signals
are scaled by gains and summed, should be based on a filter bank.

The filter-banks below are implemented as Butterworth or Elliptic
spectrum-analyzers followed by delay equalizers that make them 
allpass-complementary.

#### Increasing Channel Isolation

Go to higher filter orders - see Regalia et al. or Vaidyanathan (cited 
below) regarding the construction of more aggressive recursive 
filter-banks using elliptic or Chebyshev prototype filters.
  
#### References

* "Tree-structured complementary filter banks using all-pass sections",
  Regalia et al., IEEE Trans. Circuits & Systems, CAS-34:1470-1484, Dec. 1987
* "Multirate Systems and Filter Banks", P. Vaidyanathan, Prentice-Hall, 1993
* Elementary filter theory: https://ccrma.stanford.edu/~jos/filters/

### `mth_octave_filterbank[n]`
Allpass-complementary filter banks based on Butterworth band-splitting.
For Butterworth band-splits, the needed delay equalizer is easily found.

#### Usage

```
_ : mth_octave_filterbank(O,M,ftop,N) : par(i,N,_); // Oth-order
_ : mth_octave_filterbank_alt(O,M,ftop,N) : par(i,N,_); // dc-inverted version
```

Also for convenience:

```
_ : mth_octave_filterbank3(M,ftop,N) : par(i,N,_); // 3d-order Butterworth
_ : mth_octave_filterbank5(M,ftop,N) : par(i,N,_); // 5th-roder Butterworth
mth_octave_filterbank_default = mth_octave_analyzer6e;
```

Where: 

* `O`: order of filter used to split each frequency band into two
* `M`: number of band-slices per octave
* `ftop`: highest band-split crossover frequency (e.g., 20 kHz)
* `N`: total number of bands (including dc and Nyquist)

---


## Arbritary-Crossover Filter-Banks and Spectrum Analyzers
These are similar to the Mth-octave analyzers above, except that the
band-split frequencies are passed explicitly as arguments. 

### `filterbank`
Filter bank.

#### Usage

```
_ : filterbank (O,freqs) : par(i,N,_); // Butterworth band-splits
```
Where: 

* `O`: band-split filter order (ODD integer required for filterbank[i])
* `freqs`: (fc1,fc2,...,fcNs) [in numerically ascending order], where
          Ns=N-1 is the number of octave band-splits 
          (total number of bands N=Ns+1). 

If frequencies are listed explicitly as arguments, enclose them in parens:

```
_ : filterbank(3,(fc1,fc2)) : _,_,_
```

---


### `filterbanki`
Inverted-dc filter bank.

#### Usage

```
_ : filterbanki(O,freqs) : par(i,N,_); // Inverted-dc version 
```

Where: 

* `O`: band-split filter order (ODD integer required for `filterbank[i]`)
* `freqs`: (fc1,fc2,...,fcNs) [in numerically ascending order], where
          Ns=N-1 is the number of octave band-splits 
          (total number of bands N=Ns+1). 

If frequencies are listed explicitly as arguments, enclose them in parens:

```
_ : filterbanki(3,(fc1,fc2)) : _,_,_
```

---

