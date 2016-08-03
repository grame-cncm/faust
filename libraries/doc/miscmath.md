
# miscmath.lib 
Mathematic library for Faust. Some functions are implemenented as Faust foreign 
functions of `math.h` functions that are not part of Faust's primitives. Defines 
also various constants and several utilities.

It should be used using the `fi` environment:

```
ma = library("miscmath.lib");
process = ma.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ma`
environment:

```
import("stdfaust.lib");
process = ma.functionCall;
```

## Functions Reference

### `SR`
Current sampling rate (between 1Hz and 192000Hz). Constant during
program execution.

#### Usage

```
SR : _
```

---


### `BS`
Current block-size. Can change during the execution.

#### Usage

```
BS : _
```

---


### `PI`
Constant PI in double precisio.n

#### Usage

```
PI : _
```

---


### `FTZ`
Flush to zero: force samples under the "maximum subnormal number"
to be zero. Usually not needed in C++ because the architecture
file take care of this, but can be useful in javascript for instance.

#### Usage

```
_ : ftz : _
```

See : <http://docs.oracle.com/cd/E19957-01/806-3568/ncg_math.html>

---


### `neg`
Invert the sign (-x) of a signal.

#### Usage

```
_ : neg : _
```

---


### `sub(x,y)`
Subtract `x` and `y`.

---


### `inv`
Compute the inverse (1/x) of the input signal.

#### Usage

```
_ : inv : _
```

---


### `cbrt`
Computes the cube root of of the input signal.

#### Usage

```
_ : cbrt : _
```

---


### `hypot(x,y)`
Computes the euclidian distance of the two input signals
sqrt(x*x+y*y) without undue overflow or underflow.

#### Usage

```
_,_ : hypot : _
```

---


### `ldexp`
Takes two input signals: x and n, and multiplies x by 2 to the power n.

#### Usage

```
_,_ : ldexp : _
``` 

---


### `scalb`
Takes two input signals: x and n, and multiplies x by 2 to the power n.

#### Usage

```
_,_ : scalb : _
```

---


### `log1p(x)`
Computes log(1 + x) without undue loss of accuracy when x is nearly zero.

#### Usage

```
_ : log1p : _
```

---


### `logb`
Return exponent of the input signal as a floating-point number.

#### Usage

```
_ : logb : _
```

---


### `ilogb`
Return exponent of the input signal as an integer number.

#### Usage

```
_ : ilogb : _
```

---


### `log2`
Returns the base 2 logarithm of x.

#### Usage

```
_ : log2 : _
```

---


### `expm1`
Return exponent of the input signal minus 1 with better precision.

#### Usage

```
_ : expm1 : _
```

---


### `acosh`
Computes the principle value of the inverse hyperbolic cosine
of the input signal.

#### Usage

```
_ : acosh : _ 
```

---


### `asinh(x)`
Computes the inverse hyperbolic sine of the input signal.

#### Usage

```
_ : asinh : _
```

---


### `atanh(x)`
Computes the inverse hyperbolic tangent of the input signal.

#### Usage

```
_ : atanh : _
```

---


### `sinh`
Computes the hyperbolic sine of the input signal.

#### Usage

```
_ : sinh : _
```

---


### `cosh`
Computes the hyperbolic cosine of the input signal.

#### Usage

```
_ : cosh : _
```

---


### `tanh`
Computes the hyperbolic tangent of the input signal.

#### Usage

```
_ : tanh : _
```

---


### `erf`
Computes the error function of the input signal.

#### Usage

```
_ : erf : _
```

---


### `erfc`
Computes the complementary error function of the input signal.

#### Usage

```
_ : erfc : _
```

---


### `gamma`
Computes the gamma function of the input signal.

#### Usage

```
_ : gamma : _
```

---


### `lgamma`
Calculates the natural logorithm of the absolute value of
the gamma function of the input signal.

#### Usage

```
_ : lgamma : _
```

---


### `J0`
Computes the Bessel function of the first kind of order 0
of the input signal.

#### Usage

```
_ : J0 : _
```

---


### `J1`
Computes the Bessel function of the first kind of order 1
of the input signal.

#### Usage

```
_ : J1 : _
```

---


### `Jn`
Computes the Bessel function of the first kind of order n
(first input signal) of the second input signal.

#### Usage

```
_,_ : Jn : _
```

---


### `Y0`
Computes the linearly independent Bessel function of the second kind
of order 0 of the input signal.

#### Usage

```
_ : Y0 : _
```

---


### `Y1`
Computes the linearly independent Bessel function of the second kind
of order 1 of the input signal.

#### Usage

```
_ : Y0 : _
```

---


### `Yn`
Computes the linearly independent Bessel function of the second kind
of order n (first input signal) of the second input signal.

#### Usage

```
_,_ : Yn : _
```

---


### `fabs`, `fmax`, `fmin`
Just for compatibility... 

```
fabs = abs
fmax = max
fmin = min
```

---


### `np2(n)`
Gives the next power of 2 of x.

#### Usage

```
np2(n) : _
```

Where:

* `n`: an integer

---


### `frac(n)`
Gives the fractional part of n.

#### Usage

```
frac(n) : _
```

Where:

* `n`: a decimal number

---


### `isnan(x)`
Return non-zero if and only if x is a NaN.

#### Usage

```
_ : isnan : _
```

Where:

* `x`: signal to analyse

---


### `chebychev`
Chebychev transformation of order n.

#### Usage

```
_ : chebychev(n) : _
```

Where:

* `n`: the order of the polynomial

#### Semantics

```
T[0](x) = 1,
T[1](x) = x,
T[n](x) = 2x*T[n-1](x) - T[n-2](x)
```

#### Reference

<http://en.wikipedia.org/wiki/Chebyshev_polynomial>

---


### `chebychevpoly`
Linear combination of the first Chebyshev polynomials.

#### Usage

```
_ : chebychevpoly((c0,c1,...,cn)) : _
```

Where:

* `cn`: the different Chebychevs polynomials such that:
 chebychevpoly((c0,c1,...,cn)) = Sum of chebychev(i)*ci

#### Reference

<http://www.csounds.com/manual/html/chebyshevpoly.html>

---


### `diffn(x)`
Negated first-roder difference.

#### Usage

```
_ : diffn : _
```

---

