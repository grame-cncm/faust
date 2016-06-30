
# synth.lib 
This library contains a collection of envelope generators.

It should be used using the `sy` environment:

```
sy = library("synth.lib");
process = sy.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `sy`
environment:

```
import("stdfaust.lib");
process = sy.functionCall;
```

### `popFilterPerc`
A simple percussion instrument based on a "poped" resonant bandpass filter.

#### Usage

```
popFilterDrum(freq,q,gate) : _;
```

Where:

* `freq`: the resonance frequency of the instrument 
* `q`: the q of the res filter (typically, 5 is a good value)
* `gate`: the trigger signal (0 or 1)

---


### `dubDub`
A simple synth based on a sawtooth wave filtered by a resonant lowpass.

#### Usage

```
dubDub(freq,ctFreq,q,gate) : _;
```

Where:

* `freq`: frequency of the sawtooth
* `ctFreq`: cutoff frequency of the filter
* `q`: Q of the filter
* `gate`: the trigger signal (0 or 1)

---


### `sawTrombone`
A simple trombone based on a lowpassed sawtooth wave.

#### Usage

```
sawTrombone(att,freq,gain,gate) : _
```

Where:

* `att`: exponential attack duration in s (typically 0.01)
* `freq`: the frequency
* `gain`: the gain (0-1)
* `gate`: the gate (0 or 1)

---


### `combString`
Simplest string physical model ever based on a comb filter.

#### Usage

```
combString(freq,res,gate) : _;
```

Where:

* `freq`: the frequency of the string
* `res`: string T60 (resonance time) in second
* `gate`: trigger signal (0 or 1)

---


### `additiveDrum`
A simple drum using additive synthesis.

#### Usage

```
additiveDrum(freq,freqRatio,gain,harmDec,att,rel,gate) : _
```

Where:

* `freq`: the resonance frequency of the drum
* `freqRatio`: a list of ratio to choose the frequency of the mode in 
     function of `freq` e.g.(1 1.2 1.5 ...). The first element should always 
     be one (fundamental).
* `gain`: the gain of each mode as a list (1 0.9 0.8 ...). The first element 
     is the gain of the fundamental.
* `harmDec`: harmonic decay ratio (0-1): configure the speed at which 
     higher modes decay compare to lower modes.
* `att`: attack duration in second
* `rel`: release duration in second
* `gate`: trigger signal (0 or 1)

---


### `additiveDrum`
An FM synthesizer with an arbitrary number of modulators connected as a sequence.

#### Usage

```
freqs = (300,400,...);
indices = (20,...);
fm(freqs,indices) : _
```

Where:

* `freqs`: a list of frequencies where the first one is the frequency of the carrier
     and the others, the frequency of the modulator(s)
* `indices`: the indices of modulation (Nfreqs-1)

---

