
# analyzer.lib 
This library contains a collection of tools to analyze signals.

It should be used using the `an` environment:

```
an = library("analyzer.lib");
process = an.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `an`
environment:

```
import("stdfaust.lib");
process = an.functionCall;
```

## Amplitude Tracking

### `amp_follower`
Classic analog audio envelope follower with infinitely fast rise and
exponential decay.  The amplitude envelope instantaneously follows
the absolute value going up, but then floats down exponentially.

#### Usage

```
_ : amp_follower(rel) : _
```

Where:

* `rel`: release time = amplitude-envelope time-constant (sec) going down

#### Reference

* Musical Engineer's Handbook, Bernie Hutchins, Ithaca NY, 1975 Electronotes 
Newsletter, Bernie Hutchins

---


### `amp_follower_ud`
Envelope follower with different up and down time-constants
(also called a "peak detector").

#### Usage

```
   _ : amp_follower_ud(att,rel) : _
```

Where:

* `att`: attack time = amplitude-envelope time constant (sec) going up
* `rel`: release time = amplitude-envelope time constant (sec) going down

#### Note

We assume rel >> att.  Otherwise, consider rel ~ max(rel,att).
For audio, att is normally faster (smaller) than rel (e.g., 0.001 and 0.01).
Use `amp_follower_ar` below to remove this restriction.

#### Reference

* "Digital Dynamic Range Compressor Design --- A Tutorial and Analysis", by
  Dimitrios Giannoulis, Michael Massberg, and Joshua D. Reiss
  <http://www.eecs.qmul.ac.uk/~josh/documents/GiannoulisMassbergReiss-dynamicrangecompression-JAES2012.pdf>

---


### `amp_follower_ar(att,rel)`
Envelope follower with independent attack and release times. The
release can be shorter than the attack (unlike in `amp_follower_ud`
above).

#### Usage

```
_ : amp_follower_ar(att,rel) : _;
```

---


## Spectrum-Analyzers
Spectrum-analyzers split the input signal into a bank of parallel signals, one for 
each spectral band. They are related to the Mth-Octave Filter-Banks in `filter.lib`.
The documentation of this library contains more details about the implementation. 
The parameters are:

* `M`: number of band-slices per octave (>1)
* `N`: total number of bands (>2)
* `ftop` = upper bandlimit of the Mth-octave bands (<SR/2)

In addition to the Mth-octave output signals, there is a highpass signal
containing frequencies from ftop to SR/2, and a "dc band" lowpass signal 
containing frequencies from 0 (dc) up to the start of the Mth-octave bands.
Thus, the N output signals are
```
highpass(ftop), MthOctaveBands(M,N-2,ftop), dcBand(ftop*2^(-M*(N-1)))
```

A Spectrum-Analyzer is defined here as any band-split whose bands span
the relevant spectrum, but whose band-signals do not
necessarily sum to the original signal, either exactly or to within an
allpass filtering. Spectrum analyzer outputs are normally at least nearly
"power complementary", i.e., the power spectra of the individual bands
sum to the original power spectrum (to within some negligible tolerance).

#### Increasing Channel Isolation

Go to higher filter orders - see Regalia et al. or Vaidyanathan (cited 
below) regarding the construction of more aggressive recursive 
filter-banks using elliptic or Chebyshev prototype filters.
  
#### References

* "Tree-structured complementary filter banks using all-pass sections",
  Regalia et al., IEEE Trans. Circuits & Systems, CAS-34:1470-1484, Dec. 1987
* "Multirate Systems and Filter Banks", P. Vaidyanathan, Prentice-Hall, 1993
* Elementary filter theory: https://ccrma.stanford.edu/~jos/filters/

### `mth_octave_analyzer[N]`
Octave analyzer.

#### Usage
```
_ : mth_octave_analyzer(O,M,ftop,N) : par(i,N,_); // Oth-order Butterworth
_ : mth_octave_analyzer6e(M,ftop,N) : par(i,N,_); // 6th-order elliptic
```

Also for convenience:

```
_ : mth_octave_analyzer3(M,ftop,N) : par(i,N,_); // 3d-order Butterworth
_ : mth_octave_analyzer5(M,ftop,N) : par(i,N,_); // 5th-roder Butterworth
mth_octave_analyzer_default = mth_octave_analyzer6e;
```

Where: 

* `O`: order of filter used to split each frequency band into two
* `M`: number of band-slices per octave
* `ftop`: highest band-split crossover frequency (e.g., 20 kHz)
* `N`: total number of bands (including dc and Nyquist)

---


## Mth-Octave Spectral Level
Spectral Level: Display (in bar graphs) the average signal level in each spectral band.

### `mth_octave_spectral_level6e`
Spectral level display.

#### Usage:

```
_ : mth_octave_spectral_level6e(M,ftop,NBands,tau,dB_offset);
```

Where: 

* `M`: bands per octave
* `ftop`: lower edge frequency of top band
* `NBands`: number of passbands (including highpass and dc bands),
* `tau`: spectral display averaging-time (time constant) in seconds,
* `dB_offset`: constant dB offset in all band level meters.

Also for convenience:

```
mth_octave_spectral_level_default = mth_octave_spectral_level6e;
spectral_level = mth_octave_spectral_level(2,10000,20);
``` 

---


### `[third|half]_octave_[analyzer|filterbank]`
A bunch of special cases based on the different analyzer functions described above:

```
third_octave_analyzer(N) = mth_octave_analyzer_default(3,10000,N);
third_octave_filterbank(N) = mth_octave_filterbank_default(3,10000,N);
half_octave_analyzer(N) = mth_octave_analyzer_default(2,10000,N);
half_octave_filterbank(N) = mth_octave_filterbank_default(2,10000,N);
octave_filterbank(N) = mth_octave_filterbank_default(1,10000,N);
octave_analyzer(N) = mth_octave_analyzer_default(1,10000,N);
```

#### Usage

See `mth_octave_spectral_level_demo`.

---


## Arbritary-Crossover Filter-Banks and Spectrum Analyzers
These are similar to the Mth-octave analyzers above, except that the
band-split frequencies are passed explicitly as arguments. 

### `analyzer`
Analyzer.

#### Usage

```
_ : analyzer   (O,freqs) : par(i,N,_); // No delay equalizer
```

Where: 

* `O`: band-split filter order (ODD integer required for filterbank[i])
* `freqs`: (fc1,fc2,...,fcNs) [in numerically ascending order], where
          Ns=N-1 is the number of octave band-splits 
          (total number of bands N=Ns+1). 

If frequencies are listed explicitly as arguments, enclose them in parens:

```
_ : analyzer(3,(fc1,fc2)) : _,_,_
```

---

