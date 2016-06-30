
# spat.lib 
This library contains a collection of tools for sound spatialization.

It should be used using the `sp` environment:

```
sp = library("spat.lib");
process = sp.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `sp`
environment:

```
import("stdfaust.lib");
process = sp.functionCall;
```

### `panner(g)`
A simple linear gain panner.

### Usage

```
_ : panner(g) : _,_
```

Where:

* `g`: the panning (0-1) 

---


### `spat(n,a,d)`
GMEM SPAT: n-outputs spatializer

### Usage

```
_ : spat(n,r,d) : _,_,...
```

Where:

* `n`: number of outputs
* `r`: rotation (between 0 et 1)
* `d`: distance of the source (between 0 et 1) 

---


### `stereoize(p)`
Transform an arbitrary processor `p` into a stereo processor with 2 inputs
and 2 outputs.

#### Usage

```
_,_ : stereoize(p) : _,_
```

Where:

* `p`: the arbitrary processor

---

