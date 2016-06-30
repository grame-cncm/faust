
# envelope.lib 
This library contains a collection of envelope generators.

It should be used using the `en` environment:

```
en = library("envelope.lib");
process = en.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `en`
environment:

```
import("stdfaust.lib");
process = en.functionCall;
```

## Functions Reference

### `smoothEnvelope`
An envelope with an exponential attack and release.

#### Usage

```
smoothEnvelope(ar,t) : _
```

* `ar`: attack and release duration (s)
* `t`: trigger signal (0-1)

---


### `ar`
AR (Attack, Release) envelope generator (useful to create percussion envelopes).

#### Usage

```
ar(a,r,t) : _
```

Where:

* `a`: attack (sec)
* `r`: release (sec)
* `t`: trigger signal (0 or 1)

---


### `asr`
ASR (Attack, Sustain, Release) envelope generator.

#### Usage

```
asr(a,s,r,t) : _
```

Where:

* `a`, `s`, `r`: attack (sec), sustain (percentage of t), release (sec)
* `t`: trigger signal ( >0 for attack, then release is when t back to 0)

---


### `adsr`
ADSR (Attack, Decay, Sustain, Release) envelope generator.

#### Usage

```
adsr(a,d,s,r,t) : _
```

Where:

* `a`, `d`, `s`, `r`: attack (sec), decay (sec), sustain (percentage of t), release (sec)
* `t`: trigger signal ( >0 for attack, then release is when t back to 0)

---

