
# hoa.lib 
Faust library for high order ambisonic.

It should be used using the `ho` environment:

```
ho = library("ho.lib");
process = ho.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ho`
environment:

```
import("stdfaust.lib");
process = ho.functionCall;
```

### `encoder`
Ambisonic encoder. Encodes a signal in the circular harmonics domain 
depending on an order of decomposition and an angle.

#### Usage

```
encoder(n, x, a) : _
```

Where:

* `n`: the order
* `x`: the signal
* `a`: the angle

---


### `decoder`
Decodes an ambisonics sound field for a circular array of loudspeakers.

#### Usage

```
_ : decoder(n, p) : _
```

Where:

* `n`: the order
* `p`: the number of speakers

#### Note

Number of loudspeakers must be greater or equal to 2n+1. It's preferable 
to use 2n+2 loudspeakers.

---


### `decoderStereo`
Decodes an ambisonic sound field for stereophonic configuration. 
An "home made" ambisonic decoder for stereophonic restitution 
(30° - 330°) : Sound field lose energy around 180°. You should 
use `inPhase` optimization with ponctual sources.
#### Usage

```
_ : decoderStereo(n) : _
```

Where:

* `n`: the order

---


## Optimization Functions
Functions to weight the circular harmonics signals depending to the 
ambisonics optimization. 
It can be `basic` for no optimization, `maxRe` or `inPhase`.

### `optimBasic`
The basic optimization has no effect and should be used for a perfect 
circle of loudspeakers with one listener at the perfect center loudspeakers 
array.

#### Usage

```
_ : optimBasic(n) : _ 
```

Where:

* `n`: the order

---


### `optimMaxRe`
The maxRe optimization optimize energy vector. It should be used for an 
auditory confined in the center of the loudspeakers array.

#### Usage

```
_ : optimMaxRe(n) : _ 
```

Where:

* `n`: the order

---


### `optimInPhase`
The inPhase Optimization optimize energy vector and put all loudspeakers signals 
n phase. It should be used for an auditory

### Usage

``
 : optimInPhase(n) : _ 
``

here:

 `n`: the order

---


### `wider`
Can be used to wide the diffusion of a localized sound. The order 
depending signals are weighted and appear in a logarithmic way to 
have linear changes.

#### Usage

```
_ : wider(n,w) : _ 
```

Where:

* `n`: the order
* `w`: the width value between 0 - 1

---


### `map`
It simulate the distance of the source by applying a gain 
on the signal and a wider processing on the soundfield.

#### Usage

```
map(n, x, r, a)
```

Where:

* `n`: the order
* `x`: the signal
* `r`: the radius
* `a`: the angle in radian

---


### `rotate`
Rotates the sound field.

#### Usage

```
_ : rotate(n, a) : _ 
```

Where:

* `n`: the order
* `a`: the angle in radian

---

