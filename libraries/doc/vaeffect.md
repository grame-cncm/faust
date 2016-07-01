
# vaeffect.lib 
A library of virtual analog filter effects.

It should be used using the `ve` environment:

```
ve = library("vaeffect.lib");
process = ve.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ve`
environment:

```
import("stdfaust.lib");
process = ve.functionCall;
```

## Functions Reference

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

