
# compressor.lib 
A library of compressor effects.

It should be used using the `co` environment:

```
co = library("compressor.lib");
process = co.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `co`
environment:

```
import("stdfaust.lib");
process = co.functionCall;
```

## Functions Reference

### `compressor_mono` and `compressor_stereo`
Mono and stereo dynamic range compressors.

#### Usage

```
_ : compressor_mono(ratio,thresh,att,rel) : _
_,_ : compressor_stereo(ratio,thresh,att,rel) : _,_
```

Where:

* `ratio`: compression ratio (1 = no compression, >1 means compression)
* `thresh`: dB level threshold above which compression kicks in (0 dB = max level)
* `att`: attack time = time constant (sec) when level & compression going up
* `rel`: release time = time constant (sec) coming out of compression

#### References

* <http://en.wikipedia.org/wiki/Dynamic_range_compression>
* <https://ccrma.stanford.edu/~jos/filters/Nonlinear_Filter_Example_Dynamic.html>
* Albert Graef's "faust2pd"/examples/synth/compressor_.dsp
* More features: <https://github.com/magnetophon/faustCompressors>

---


### `limiter_*`
A limiter guards against hard-clipping.  It can be can be
implemented as a compressor having a high threshold (near the
clipping level), fast attack and release, and high ratio.  Since
the ratio is so high, some knee smoothing is
desirable ("soft limiting").  This example is intended
to get you started using compressor_* as a limiter, so all
parameters are hardwired to nominal values here.
Ratios: 4 (moderate compression), 8 (severe compression),
         12 (mild limiting), or 20 to 1 (hard limiting)
  Att: 20-800 MICROseconds (Note: scaled by ratio in the 1176)
  Rel: 50-1100 ms (Note: scaled by ratio in the 1176)
  Mike Shipley likes 4:1 (Grammy-winning mixer for Queen, Tom Petty, etc.)
    Faster attack gives "more bite" (e.g. on vocals)
    He hears a bright, clear eq effect as well (not implemented here)

#### Usage

```
 _ : limiter_1176_R4_mono   : _;
 _,_ : limiter_1176_R4_stereo : _,_;
```

#### Reference:

<http://en.wikipedia.org/wiki/1176_Peak_Limiter>

---

