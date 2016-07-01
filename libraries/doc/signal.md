
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


### `dot(n)`
Dot product for two vectors of size n.

#### Usage

```
_,_,_,_,_,_ : dot(3) : _
```

Where:

* `n`: size of the vectors (int, must be known at compile time)

---

