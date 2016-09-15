
# delay.lib 
This library contains a collection of delay functions.

It should be used using the `de` environment:

```
de = library("delay.lib");
process = de.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `de`
environment:

```
import("stdfaust.lib");
process = de.functionCall;
```

## Basic Delay Functions

### `delay`
Simple `d` samples delay where `n` is the maximum delay length as a number of 
samples (it needs to be a power of 2). Unlike the `@` delay operator, this
function allows to preallocate memory which means that `d` can be changed dynamically
at run time as long as it remains smaller than `n`.

#### Usage

```
_ : delay(n,d) : _
``` 

Where:

* `n`: the max delay length as a power of 2
* `d`: the delay length as a number of samples (integer)

---


### `fdelay`
Simple `d` samples fractional delay based on 2 interpolated delay lines where `n` is 
the maximum delay length as a number of samples (it needs to be a power of 2 - see 
`delay()`). 

#### Usage

```
_ : fdelay(n,d) : _
```

Where:

* `n`: the max delay length as a power of 2
* `d`: the delay length as a number of samples (float)

---


### `sdelay`
s(mooth)delay: a mono delay that doesn't click and doesn't 
transpose when the delay time is changed.

#### Usage

```
_ : sdelay(N,it,dt) : _
```

Where :

* `N`: maximal delay in samples (must be a constant power of 2, for example 65536)
* `it`: interpolation time (in samples) for example 1024
* `dt`: delay time (in samples)

---


## Lagrange Interpolation

### `fdelaylti` and `fdelayltv`
Fractional delay line using Lagrange interpolation.

#### Usage

```
_ : fdelaylt[i|v](order, maxdelay, delay, inputsignal) : _
```

Where `order=1,2,3,...` is the order of the Lagrange interpolation polynomial.

`fdelaylti` is most efficient, but designed for constant/slowly-varying delay.
`fdelayltv` is more expensive and more robust when the delay varies rapidly.

NOTE: The requested delay should not be less than `(N-1)/2`.

#### References

* <https://ccrma.stanford.edu/~jos/pasp/Lagrange_Interpolation.html>
* Timo I. Laakso et al., "Splitting the Unit Delay - Tools for Fractional
        Delay Filter Design", IEEE Signal Processing Magazine,
        vol. 13, no. 1, pp. 30-60, Jan 1996.
* Philippe Depalle and Stephan Tassart, "Fractional Delay Lines using
        Lagrange Interpolators", ICMC Proceedings, pp. 341-343, 1996.

---


### `fdelay[n]`
For convenience, `fdelay1`, `fdelay2`, `fdelay3`, `fdelay4`, `fdelay5`
are also available where n is the order of the interpolation.

---


## Thiran Allpass Interpolation
Thiran Allpass Interpolation

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Thiran_Allpass_Interpolators.html>

### `fdelay[n]a`
Delay lines interpolated using Thiran allpass interpolation.

#### Usage 

```
_ : fdelay[N]a(maxdelay, delay, inputsignal) : _
```

(exactly like `fdelay`)

Where: 

* `N`=1,2,3, or 4 is the order of the Thiran interpolation filter,
and the delay argument is at least N - 1/2.

#### Note

The interpolated delay should not be less than `N - 1/2`.
(The allpass delay ranges from `N - 1/2` to `N + 1/2`.)
This constraint can be alleviated by altering the code,
but be aware that allpass filters approach zero delay
by means of pole-zero cancellations.
The delay range `[N-1/2`,`N+1/2]` is not optimal. What is?

Delay arguments too small will produce an UNSTABLE allpass!

Because allpass interpolation is recursive, it is not as robust
as Lagrange interpolation under time-varying conditions.
(You may hear clicks when changing the delay rapidly.)

First-order allpass interpolation, delay d in [0.5,1.5]

---

