
# phafla.lib 
A library of compressor effects.

It should be used using the `pf` environment:

```
pf = library("phafla.lib");
process = pf.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `pf`
environment:

```
import("stdfaust.lib");
process = pf.functionCall;
```

## Functions Reference

### `flanger_mono` and `flanger_stereo`
Flanging effect.

#### Usage:

```
_ : flanger_mono(dmax,curdel,depth,fb,invert) : _;
_,_ : flanger_stereo(dmax,curdel1,curdel2,depth,fb,invert) : _,_;
_,_ : flanger_demo : _,_;
```

Where:

* `dmax`: maximum delay-line length (power of 2) - 10 ms typical
* `curdel`: current dynamic delay (not to exceed dmax)
* `depth`: effect strength between 0 and 1 (1 typical)
* `fb`: feedback gain between 0 and 1 (0 typical)
* `invert`: 0 for normal, 1 to invert sign of flanging sum

#### Reference

<https://ccrma.stanford.edu/~jos/pasp/Flanging.html>

---


### `phaser2_mono` and `phaser2_stereo`
Phasing effect.

#### Phaser

```
_ : phaser2_mono(Notches,phase,width,frqmin,fratio,frqmax,speed,depth,fb,invert) : _;
_,_ : phaser2_stereo(") : _,_;
_,_ : phaser2_demo : _,_;
```

Where:

* `Notches`: number of spectral notches (MACRO ARGUMENT - not a signal)
* `phase`: phase of the oscillator (0-1)
* `width`: approximate width of spectral notches in Hz
* `frqmin`: approximate minimum frequency of first spectral notch in Hz
* `fratio`: ratio of adjacent notch frequencies
* `frqmax`: approximate maximum frequency of first spectral notch in Hz
* `speed`: LFO frequency in Hz (rate of periodic notch sweep cycles)
* `depth`: effect strength between 0 and 1 (1 typical) (aka "intensity")
           when depth=2, "vibrato mode" is obtained (pure allpass chain)
* `fb`: feedback gain between -1 and 1 (0 typical)
* `invert`: 0 for normal, 1 to invert sign of flanging sum

Reference:

* <https://ccrma.stanford.edu/~jos/pasp/Phasing.html>
* <http://www.geofex.com/Article_Folders/phasers/phase.html>
* 'An Allpass Approach to Digital Phasing and Flanging', Julius O. Smith III,
     Proc. Int. Computer Music Conf. (ICMC-84), pp. 103-109, Paris, 1984.
* CCRMA Tech. Report STAN-M-21: <https://ccrma.stanford.edu/STANM/stanms/stanm21/>

---

