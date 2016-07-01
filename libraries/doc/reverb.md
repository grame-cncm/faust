
# reverb.lib 
A library of reverb effects.

It should be used using the `re` environment:

```
re = library("reverb.lib");
process = re.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `re`
environment:

```
import("stdfaust.lib");
process = re.functionCall;
```

## Functions Reference

### `jcrev` and `satrev`
These artificial reverberators take a mono signal and output stereo
(`satrev`) and quad (`jcrev`).  They were implemented by John Chowning
in the MUS10 computer-music language (descended from Music V by Max
Mathews).  They are Schroeder Reverberators, well tuned for their size.
Nowadays, the more expensive freeverb is more commonly used (see the
Faust examples directory).

`jcrev` reverb below was made from a listing of "RV", dated April 14, 1972,
which was recovered from an old SAIL DART backup tape.
John Chowning thinks this might be the one that became the
well known and often copied JCREV.

`satrev` was made from a listing of "SATREV", dated May 15, 1971,
which was recovered from an old SAIL DART backup tape.
John Chowning thinks this might be the one used on his
often-heard brass canon sound examples, one of which can be found at
<https://ccrma.stanford.edu/~jos/wav/FM_BrassCanon2.wav>

#### Usage

```
_ : jcrev : _,_,_,_
_ : satrev : _,_
```

---


### `mono_freeverb` and `stereo_freeverb`
A simple Schroeder reverberator primarily developed by "Jezar at Dreampoint" that
is extensively used in the free-software world. It uses four Schroeder allpasses in
series and eight parallel Schroeder-Moorer filtered-feedback comb-filters for each
audio channel, and is said to be especially well tuned.

#### Usage

```
_ : mono_freeverb(fb1, fb2, damp, spread) : _;
_,_ : stereo_freeverb(fb1, fb2, damp, spread) : _,_;
```

Where:

* `fb1`: coefficient of the lowpass comb filters (0-1)
* `fb2`: coefficient of the allpass comb filters (0-1)
* `damp`: damping of the lowpass comb filter (0-1)
* `spread`: spatial spread in number of samples (for stereo)

---


### `fdnrev0`
Pure Feedback Delay Network Reverberator (generalized for easy scaling).

#### Usage

```
<1,2,4,...,N signals> <:
fdnrev0(MAXDELAY,delays,BBSO,freqs,durs,loopgainmax,nonl) :>
<1,2,4,...,N signals>
```

Where:

* `N`: 2, 4, 8, ...  (power of 2)
* `MAXDELAY`: power of 2 at least as large as longest delay-line length
* `delays`: N delay lines, N a power of 2, lengths perferably coprime
* `BBSO`: odd positive integer = order of bandsplit desired at freqs
* `freqs`: NB-1 crossover frequencies separating desired frequency bands
* `durs`: NB decay times (t60) desired for the various bands
* `loopgainmax`: scalar gain between 0 and 1 used to "squelch" the reverb
* `nonl`: nonlinearity (0 to 0.999..., 0 being linear)

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/FDN_Reverberation.html>

---


### `zita_rev_fdn`
Internal 8x8 late-reverberation FDN used in the FOSS Linux reverb zita-rev1
by Fons Adriaensen <fons@linuxaudio.org>.  This is an FDN reverb with
allpass comb filters in each feedback delay in addition to the
damping filters.

#### Usage

```
bus(8) : zita_rev_fdn(f1,f2,t60dc,t60m,fsmax) : bus(8)
```

Where:

* `f1`: crossover frequency (Hz) separating dc and midrange frequencies
* `f2`: frequency (Hz) above f1 where T60 = t60m/2 (see below)
* `t60dc`: desired decay time (t60) at frequency 0 (sec)
* `t60m`: desired decay time (t60) at midrange frequencies (sec)
* `fsmax`: maximum sampling rate to be used (Hz)

#### Reference

* <http://www.kokkinizita.net/linuxaudio/zita-rev1-doc/quickguide.html>
* <https://ccrma.stanford.edu/~jos/pasp/Zita_Rev1.html>

---


### `zita_rev1_stereo`
Extend `zita_rev_fdn` to include `zita_rev1` input/output mapping in stereo mode.

#### Usage

```
_,_ : zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax) : _,_
```

Where:

`rdel`  = delay (in ms) before reverberation begins (e.g., 0 to ~100 ms)
(remaining args and refs as for `zita_rev_fdn` above)

---


### `zita_rev1_ambi`
Extend zita_rev_fdn to include zita_rev1 input/output mapping in
"ambisonics mode", as provided in the Linux C++ version.

#### Usage

```
_,_ : zita_rev1_ambi(rgxyz,rdel,f1,f2,t60dc,t60m,fsmax) : _,_,_,_
```

Where:

`rgxyz` = relative gain of lanes 1,4,2 to lane 0 in output (e.g., -9 to 9)
  (remaining args and references as for zita_rev1_stereo above)

---

