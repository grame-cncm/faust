
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


## Meshes

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

