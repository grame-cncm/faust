
# signal.lib 
A library of basic elements to handle signals in Faust.

It should be used using the `si` environment:

```
si = library("signal.lib");
process = si.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `si`
environment:

```
import("stdfaust.lib");
process = si.functionCall;
```

## Functions Reference

### `bus(n)`
n parallel cables

#### Usage

```
bus(4) -> _,_,_,_
```

Where:

* `n`: is an integer known at compile time that indicates the number of parallel cables.

---


### `block(n)`
Block - terminate n signals.

#### Usage

```
_,_,... : block(n) : _,...
```

Where:

* `n`: the number of signals to be blocked

---


### `cross(n)`
Cross n signals: `(x1,x2,..,xn) -> (xn,..,x2,x1)`.

#### Usage

```
_,_,_ : cross(3) : _,_,_
```

Where:

* `n`: number of signals (int, must be known at compile time)

#### Note

Special case: `cross2`:

```
cross2 = _,cross(2),_;
```

---


### `crossnn(n)`
Cross two `bus(n)`s.

#### Usage

```
_,_,... : crossmm(n) : _,_,...
```

Where:

* `n`: the number of signals in the `bus`

---


### `crossn1(n)`
Cross bus(n) and bus(1).

#### Usage

```
_,_,... : crossn1(n) : _,_,...
```

Where:

* `n`: the number of signals in the first `bus`

---


### `interpolate(i)`
Linear interpolation between two signals.

#### Usage

```
_,_ : interpolate(i) : _
```

Where:

* `i`: interpolation control between 0 and 1 (0: first input; 1: second input)

---


### `smooth(s)`
Exponential smoothing by a unity-dc-gain one-pole lowpass.

#### Usage: 

```
_ : smooth(tau2pole(tau)) : _
```

Where: 

* `tau`: desired smoothing time constant in seconds, or

```
hslider(...) : smooth(s) : _ 
```

Where: 

* `s`: smoothness between 0 and 1. s=0 for no smoothing, s=0.999 is "very smooth",
s>1 is unstable, and s=1 yields the zero signal for all inputs.
The exponential time-constant is approximately 1/(1-s) samples, when s is close to 
(but less than) 1.

#### Reference: 

<https://ccrma.stanford.edu/~jos/mdft/Convolution_Example_2_ADSR.html>

---


### `smoo`
Smoothing function based on `smooth` ideal to smooth UI signals 
(sliders, etc.) down. 

#### Usage

```
hslider(...) : smoo;
```

---


### `polySmooth`
A smoothing function based on `smooth` that doesn't smooth when a
trigger signal is given. This is very useful when making 
polyphonic synthesizer to make sure that the value of the parameter
is the right one when the note is started.

#### Usage

```
hslider(...) : polysmooth(g,s,d) : _
```

Where:

* `g`: the gate/trigger signal used when making polyphonic synths
* `s`: the smoothness (see `smooth`)
* `d`: the number of samples to wait before the signal start being
     smoothed after `g` switched to 1

---


### `bsmooth`
Block smooth linear interpolation during a block of samples.

#### Usage

```
hslider(...) : bsmooth : _
```

---


### `lag_ud(up, dn, signal)`
Lag filter with separate times for up and down.

#### Usage

```
_ : lag_ud(up, dn, signal) : _;
```

---


### `interleave(row,col)`
Interleave row*col cables from column order to row order.
input : x(0), x(1), x(2) ..., x(row*col-1)
output: x(0+0*row), x(0+1*row), x(0+2*row), ..., x(1+0*row), x(1+1*row), x(1+2*row), ...

#### Usage

```
_,_,_,_,_,_ : interleave(3,2) : _,_,_,_,_,_
```

Where:

* `row`: the number of row (int, known at compile time)
* `column`: the number of column (int, known at compile time)

---


### `butterfly(n)`
Addition (first half) then substraction (second half) of interleaved signals.

#### Usage

```
_,_,_,_ : butterfly(4) : _,_,_,_
```

Where:

* `n`: size of the butterfly (n is int, even and known at compile time)

---


### `hadamard(n)`
Hadamard matrix function of size `n = 2^k`.

#### Usage

```
_,_,_,_ : hadamard(4) : _,_,_,_
```

Where:

* `n`: `2^k`, size of the matrix (int, must be known at compile time)

#### Note:

Implementation contributed by Remy Muller.

---


### `dot(n)`
Dot product for two vectors of size n.

#### Usage

```
_,_,_,_,_,_ : dot(3) : _
```

Where:

* `n`: size of the vectors (int, must be known at compile time)

---


### peakhold(mode,sig)
Outputs current max value above zero. 

#### Usage

```
_ : peakhold(mode,sig) : _;
```

Where:

`mode` means: 0 - Pass through. A single sample 0 trigger will work as a reset.
   1 - Track and hold max value.

---


### peakholder(holdtime)
Tracks abs peak and holds peak for 'holdtime' samples.

#### Usage 

```
peakholder(holdtime, sig);
```

---


### `diffn(x)`
Negated first-roder difference.

#### Usage

```
_ : diffn : _
```

---


### `recursivize(p,q)`
Create a recursion from two arbitrary processors p and q.

#### Usage

```
_,_ : stereoize(p,q) : _,_

```

Where:

* `p`: the forward arbitrary processor
* `q`: the feedback arbitrary processor

---

