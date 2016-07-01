
# misceffect.lib 
This library contains a collection of audio effects.

It should be used using the `ef` environment:

```
ef = library("misceffect.lib");
process = ef.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ef`
environment:

```
import("stdfaust.lib");
process = ef.functionCall;
```

## Dynamic

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


### `cubicnl(drive,offset)`
Cubic nonlinearity distortion.

#### Usage:

```
_ : cubicnl(drive,offset) : _
_ : cubicnl_nodc(drive,offset) : _
```

Where:

* `drive`: distortion amount, between 0 and 1
* `offset`: constant added before nonlinearity to give even harmonics. Note: offset 
 can introduce a nonzero mean - feed cubicnl output to dcblocker to remove this.

#### References:

* <https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html>
* <https://ccrma.stanford.edu/~jos/pasp/Nonlinear_Distortion.html>

---


### `gate_mono` and `gate_stereo`
Mono and stereo signal gates.

#### Usage

```
_ : gate_mono(thresh,att,hold,rel) : _
```

or

```
 _,_ : gate_stereo(thresh,att,hold,rel) : _,_
```

Where:

* `thresh`: dB level threshold above which gate opens (e.g., -60 dB)
* `att`: attack time = time constant (sec) for gate to open (e.g., 0.0001 s = 0.1 ms)
* `hold`: hold time = time (sec) gate stays open after signal level < thresh (e.g., 0.1 s)
* `rel`: release time = time constant (sec) for gate to close (e.g., 0.020 s = 20 ms)

#### References

* <http://en.wikipedia.org/wiki/Noise_gate>
* <http://www.soundonsound.com/sos/apr01/articles/advanced.asp>
* <http://en.wikipedia.org/wiki/Gating_(sound_engineering)>

---


### `compressor_mono` and `compressor_stereo`
Mono and stereo dynamic range compressors.

#### Usage

```
_ : compressor_mono(ratio,thresh,att,rel) : _
_,_ : compressor_stereo(ratio,thresh,att,rel) : _,_
```

Where:

* `ratio`: compression ratio (1 = no compression, >1 means compression)
* `thresh`: dB level threshold above which compression kicks in (0 dB = max level)
* `att`: attack time = time constant (sec) when level & compression going up
* `rel`: release time = time constant (sec) coming out of compression

#### References

* <http://en.wikipedia.org/wiki/Dynamic_range_compression>
* <https://ccrma.stanford.edu/~jos/filters/Nonlinear_Filter_Example_Dynamic.html>
* Albert Graef's "faust2pd"/examples/synth/compressor_.dsp
* More features: <https://github.com/magnetophon/faustCompressors>

---


### `limiter_*`
A limiter guards against hard-clipping.  It can be can be
implemented as a compressor having a high threshold (near the
clipping level), fast attack and release, and high ratio.  Since
the ratio is so high, some knee smoothing is
desirable ("soft limiting").  This example is intended
to get you started using compressor_* as a limiter, so all
parameters are hardwired to nominal values here.
Ratios: 4 (moderate compression), 8 (severe compression),
         12 (mild limiting), or 20 to 1 (hard limiting)
  Att: 20-800 MICROseconds (Note: scaled by ratio in the 1176)
  Rel: 50-1100 ms (Note: scaled by ratio in the 1176)
  Mike Shipley likes 4:1 (Grammy-winning mixer for Queen, Tom Petty, etc.)
    Faster attack gives "more bite" (e.g. on vocals)
    He hears a bright, clear eq effect as well (not implemented here)

#### Usage

```
 _ : limiter_1176_R4_mono   : _;
 _,_ : limiter_1176_R4_stereo : _,_;
```

#### Reference:

<http://en.wikipedia.org/wiki/1176_Peak_Limiter>

---


## Filtering

### `speakerbp(f1,f2)`
Dirt-simple speaker simulator (overall bandpass eq with observed
roll-offs above and below the passband).

Low-frequency speaker model = +12 dB/octave slope breaking to
flat near f1. Implemented using two dc blockers in series.

High-frequency model = -24 dB/octave slope implemented using a
fourth-order Butterworth lowpass.

Example based on measured Celestion G12 (12" speaker):
speakerbp(130,5000);

#### Usage

```
_ : speakerbp(130,5000) : _
```

---


### `moog_vcf(res,fr)`
Moog "Voltage Controlled Filter" (VCF) in "analog" form. Moog VCF 
implemented using the same logical block diagram as the classic 
analog circuit.  As such, it neglects the one-sample delay associated 
with the feedback path around the four one-poles.
This extra delay alters the response, especially at high frequencies
(see reference [1] for details).
See `moog_vcf_2b` below for a more accurate implementation.

#### Usage

```
moog_vcf(res,fr)
```
Where:

* `fr`: corner-resonance frequency in Hz ( less than SR/6.3 or so )
* `res`: Normalized amount of corner-resonance between 0 and 1 (0 is no 
 resonance, 1 is maximum)

#### References
* <https://ccrma.stanford.edu/~stilti/papers/moogvcf.pdf>
* <https://ccrma.stanford.edu/~jos/pasp/vegf.html>

---


### `moog_vcf_2b[n]`
Moog "Voltage Controlled Filter" (VCF) as two biquads. Implementation 
of the ideal Moog VCF transfer function factored into second-order 
sections. As a result, it is more accurate than moog_vcf above, but 
its coefficient formulas are more complex when one or both parameters 
are varied.  Here, res is the fourth root of that in moog_vcf, so, as 
the sampling rate approaches infinity, moog_vcf(res,fr) becomes equivalent
to moog_vcf_2b[n](res^4,fr) (when res and fr are constant).
`moog_vcf_2b` uses two direct-form biquads (`tf2`).
`moog_vcf_2bn` uses two protected normalized-ladder biquads (`tf2np`).

#### Usage

```
moog_vcf_2b(res,fr)
moog_vcf_2bn(res,fr)
```

Where:

* `fr`: corner-resonance frequency in Hz
* `res`: Normalized amount of corner-resonance between 0 and 1
 (0 is min resonance, 1 is maximum)

---


### `wah4(fr)`
Wah effect, 4th order.

#### Usage

```
_ : wah4(fr) : _
```

Where: 

* `fr`: resonance frequency in Hz

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/vegf.html>

---


### `autowah(level)`
Auto-wah effect.

#### Usage

```
_ : autowah(level) : _;
```

Where: 

* `level`: amount of effect desired (0 to 1).

---


### `crybaby(wah)`
Digitized CryBaby wah pedal.

#### Usage

```
_ : crybaby(wah) : _
```

Where: 

* `wah`: "pedal angle" from 0 to 1

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/vegf.html>

---


### `piano_dispersion_filter(M,B,f0)`
Piano dispersion allpass filter in closed form.

#### Usage

```
_ : piano_dispersion_filter(1,B,f0) : +(totalDelay),_ : fdelay(maxDelay) : _
```

Where:

* `M`: number of first-order allpass sections (compile-time only)
     Keep below 20. 8 is typical for medium-sized piano strings.
* `B`: string inharmonicity coefficient (0.0001 is typical)
* `f0`: fundamental frequency in Hz

#### Outputs

* MINUS the estimated delay at `f0` of allpass chain in samples,
    provided in negative form to facilitate subtraction
    from delay-line length.
* Output signal from allpass chain


### `vocoder`
A very simple vocoder where the spectrum of the modulation signal
is analyzed using a filter bank.

#### Usage

```
_ : vocoder(nBands,att,rel,BWRatio,source,excitation) : _;
```

Where:

* `nBands`: Number of vocoder bands
* `att`: Attack time in seconds
* `rel`: Release time in seconds
* `BWRatio`: Coefficient to adjust the bandwidth of each band (0.1 - 2)
* `source`: Modulation signal
* `excitation`: Excitation/Carrier signal

---


### `stereo_width(w)`
Stereo Width effect using the Blumlein Shuffler technique.

#### Usage

```
_,_ : stereo_width(w) : _,_
```

Where:

* `w`: stereo width between 0 and 1

At `w=0`, the output signal is mono ((left+right)/2 in both channels).
At `w=1`, there is no effect (original stereo image).
Thus, w between 0 and 1 varies stereo width from 0 to "original".

#### Reference

* "Applications of Blumlein Shuffling to Stereo Microphone Techniques"
Michael A. Gerzon, JAES vol. 42, no. 6, June 1994

---


## Phasing and Flanging

### `flanger_mono` and `flanger_stereo`
Flanging effect.

#### Usage:

```
_ : flanger_mono(dmax,curdel,depth,fb,invert) : _;
_,_ : flanger_stereo(dmax,curdel1,curdel2,depth,fb,invert) : _,_;
_,_ : flanger_demo : _,_;
```

Where:

* `dmax`: maximum delay-line length (power of 2) - 10 ms typical
* `curdel`: current dynamic delay (not to exceed dmax)
* `depth`: effect strength between 0 and 1 (1 typical)
* `fb`: feedback gain between 0 and 1 (0 typical)
* `invert`: 0 for normal, 1 to invert sign of flanging sum

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Flanging.html>

---


### `phaser2_mono` and `phaser2_stereo`
Phasing effect.

#### Phaser

```
_ : phaser2_mono(Notches,phase,width,frqmin,fratio,frqmax,speed,depth,fb,invert) : _;
_,_ : phaser2_stereo(") : _,_;
_,_ : phaser2_demo : _,_;
```

Where:

* `Notches`: number of spectral notches (MACRO ARGUMENT - not a signal)
* `phase`: phase of the oscillator (0-1)
* `width`: approximate width of spectral notches in Hz
* `frqmin`: approximate minimum frequency of first spectral notch in Hz
* `fratio`: ratio of adjacent notch frequencies
* `frqmax`: approximate maximum frequency of first spectral notch in Hz
* `speed`: LFO frequency in Hz (rate of periodic notch sweep cycles)
* `depth`: effect strength between 0 and 1 (1 typical) (aka "intensity")
           when depth=2, "vibrato mode" is obtained (pure allpass chain)
* `fb`: feedback gain between -1 and 1 (0 typical)
* `invert`: 0 for normal, 1 to invert sign of flanging sum

Reference:

* <https://ccrma.stanford.edu/~jos/pasp/Phasing.html>
* <http://www.geofex.com/Article_Folders/phasers/phase.html>
* 'An Allpass Approach to Digital Phasing and Flanging', Julius O. Smith III,
     Proc. Int. Computer Music Conf. (ICMC-84), pp. 103-109, Paris, 1984.
* CCRMA Tech. Report STAN-M-21: <https://ccrma.stanford.edu/STANM/stanms/stanm21/>

---


## Time Based

### `echo(maxDuration,duration,feedback)`
A simple echo effect.

#### Usage

```
echo(maxDuration,duration,feedback)
```

Where:

* `maxDuration`: the max echo duration in seconds
* `duration`: the echo duration in seconds
* `feedback`: the feedback coefficient

---


## Pitch Shifting

### `transpose`
A simple pitch shifter based on 2 delay lines.

#### Usage

```
_ : transpose(w, x, s) : _
```

Where:

* `w`: the window length (samples)
* `x`: crossfade duration duration (samples)
* `s`: shift (semitones)

---


## Reverbs

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


### `mesh_square`
Square Rectangular Digital Waveguide Mesh.

#### Usage

```
bus(4*N) : mesh_square(N) : bus(4*N);
```

Where:

* `N`: number of nodes along each edge - a power of two (1,2,4,8,...)

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Digital_Waveguide_Mesh.html>

#### Signal Order In and Out

The mesh is constructed recursively using 2x2 embeddings.  Thus,
the top level of `mesh_square(M)` is a block 2x2 mesh, where each
block is a `mesh(M/2)`.  Let these blocks be numbered 1,2,3,4 in the
geometry NW,NE,SW,SE, i.e., as
        1 2
        3 4
Each block has four vector inputs and four vector outputs, where the
length of each vector is `M/2`.  Label the input vectors as Ni,Ei,Wi,Si,
i.e., as the inputs from the North, East South, and West,
and similarly for the outputs.  Then, for example, the upper
left input block of M/2 signals is labeled 1Ni.  Most of the
connections are internal, such as 1Eo -> 2Wi.  The `8*(M/2)` input
signals are grouped in the order
       1Ni 2Ni
       3Si 4Si
       1Wi 3Wi
       2Ei 4Ei
and the output signals are
       1No 1Wo
       2No 2Eo
       3So 3Wo
       4So 4Eo
or

In: 1No 1Wo 2No 2Eo 3So 3Wo 4So 4Eo

Out: 1Ni 2Ni 3Si 4Si 1Wi 3Wi 2Ei 4Ei

Thus, the inputs are grouped by direction N,S,W,E, while the
outputs are grouped by block number 1,2,3,4, which can also be
interpreted as directions NW, NE, SW, SE.  A simple program
illustrating these orderings is `process = mesh_square(2);`.

#### Example

Reflectively terminated mesh impulsed at one corner:

```
mesh_square_test(N,x) = mesh_square(N)~(busi(4*N,x)) // input to corner
with { busi(N,x) = bus(N) : par(i,N,*(-1)) : par(i,N-1,_), +(x); };
process = 1-1' : mesh_square_test(4); // all modes excited forever
```

In this simple example, the mesh edges are connected as follows:

1No -> 1Ni, 1Wo -> 2Ni, 2No -> 3Si, 2Eo -> 4Si,

3So -> 1Wi, 3Wo -> 3Wi, 4So -> 2Ei, 4Eo -> 4Ei

A routing matrix can be used to obtain other connection geometries.

---

