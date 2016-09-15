
# basic.lib 
A library of basic elements for Faust organized in 5 sections: 

* Conversion Tools
* Counters and Time/Tempo Tools
* Array Processing/Pattern Matching
* Selectors (Conditions)
* Other Tools (Misc)

It should be used using the `ba` environment:

```
ba = library("basic.lib");
process = ba.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `ba`
environment:

```
import("stdfaust.lib");
process = ba.functionCall;
```

## Conversion Tools

### `samp2sec`
Converts a number of samples to a duration in seconds.

#### Usage

```
samp2sec(n) : _
```

Where:

* `n`: number of samples

---


### `sec2samp`
Converts a duration in seconds to a number of samples.

#### Usage

```
sec2samp(d) : _
```

Where:

* `d`: duration in seconds

---


### `db2linear`
Converts a loudness in dB to a linear gain (0-1).

#### Usage

```
db2linear(l) : _
```

Where:

* `l`: loudness in dB

---


### `linear2db`
Converts a linear gain (0-1) to a loudness in dB.

#### Usage

```
linear2db(g) : _
```

Where:

* `g`: a linear gain

---


### `lin2LogGain`
Converts a linear gain (0-1) to a log gain (0-1).

#### Usage

```
_ : lin2LogGain : _
```

---


### `log2LinGain`
Converts a log gain (0-1) to a linear gain (0-1).

#### Usage

```
_ : log2LinGain : _
```

---


### `tau2pole`
Returns a real pole giving exponential decay.
Note that t60 (time to decay 60 dB) is ~6.91 time constants.

#### Usage

```
_ : smooth(tau2pole(tau)) : _
```

Where:

* `tau`: time-constant in seconds

---


### `pole2tau`
Returns the time-constant, in seconds, corresponding to the given real, 
positive pole in (0,1).

#### Usage

```
pole2tau(pole) : _
```

Where:

* `pole`: the pole

---


### `midikey2hz`
Converts a MIDI key number to a frequency in Hz (MIDI key 69 = A440).

#### Usage

```
midikey2hz(mk) : _
```

Where:

* `mk`: the MIDI key number

---


### `pianokey2hz`
Converts a piano key number to a frequency in Hz (piano key 49 = A440).

#### Usage

```
pianokey2hz(pk) : _
```

Where:

* `pk`: the piano key number

---


### `hz2pianokey`
Converts a frequency in Hz to a piano key number (piano key 49 = A440).

#### Usage

```
hz2pianokey(f) : _
```

Where:

* `f`: frequency in Hz

---


## Counters and Time/Tempo Tools

### `countdown`
Starts counting down from n included to 0. While trig is 1 the output is n.
The countdown starts with the transition of trig from 1 to 0. At the end
of the countdown the output value will remain at 0 until the next trig.

#### Usage

```
countdown(n,trig) : _
```

Where:

* `n`: the starting point of the countdown
* `trig`: the trigger signal (1: start at `n`; 0: decrease until 0)

---


### `countup`
Starts counting up from 0 to n included. While trig is 1 the output is 0.
The countup starts with the transition of trig from 1 to 0. At the end
of the countup the output value will remain at n until the next trig.

#### Usage

```
countup(n,trig) : _
```

Where:

* `n`: the starting point of the countup
* `trig`: the trigger signal (1: start at 0; 0: increase until `n`)

---


### `sweep`
Counts from 0 to 'period' samples repeatedly, while 'run' is 1.
Outsputs zero while 'run' is 0.

#### Usage

```
sweep(period,run) : _
```

---


### `time`
A simple timer that counts every samples from the beginning of the process.

#### Usage

```
time : _
```

---


### `tempo`
Converts a tempo in BPM into a number of samples.

#### Usage

```
tempo(t) : _
```

Where:

* `t`: tempo in BPM

---


### `period`
Basic sawtooth wave of period `p`.

#### Usage

```
period(p) : _
```

Where:

* `p`: period as a number of samples

---


### `pulse`
Pulses (10000) generated at period `p`.

#### Usage

```
pulse(p) : _
```

Where:

* `p`: period as a number of samples

---


### `pulsen`
Pulses (11110000) of length `n` generated at period `p`.

#### Usage

```
pulsen(n,p) : _
```

Where:

* `n`: the length of the pulse as a number of samples
* `p`: period as a number of samples

---


### `beat`
Pulses at tempo `t`.

#### Usage

```
beat(t) : _
```

Where:

* `t`: tempo in BPM

---


## Array Processing/Pattern Matching

### `count`
Count the number of elements of list l.

#### Usage

```
count(l)
count ((10,20,30,40)) -> 4
```

Where:

* `l`: list of elements

---


### `take`
Take an element from a list.

#### Usage

```
take(e,l)
take(3,(10,20,30,40)) -> 30
```

Where:

* `p`: position (starting at 1)
* `l`: list of elements

---


### `subseq`
Extract a part of a list.

#### Usage

```
subseq(l, p, n)
subseq((10,20,30,40,50,60), 1, 3) -> (20,30,40)
subseq((10,20,30,40,50,60), 4, 1) -> 50
```

Where:

* `l`: list
* `p`: start point (0: begin of list)
* `n`: number of elements

#### Note:

Faust doesn't have proper lists. Lists are simulated with parallel
compositions and there is no empty list

---


## Selectors (Conditions)

### `if`
if-then-else implemented with a select2.

#### Usage

*   `if(c, t, e) : _`

Where:

* `c`: condition
* `t`: signal selected while c is true
* `e`: signal selected while c is false

---


### `selector`
Selects the ith input among n at compile time.

#### Usage

```
selector(i,n)
_,_,_,_ : selector(2,4) : _  // selects the 3rd input among 4
```

Where:

* `i`: input to select (`int`, numbered from 0, known at compile time)
* `n`: number of inputs (`int`, known at compile time, `n > i`)


---


### `selectn`
Selects the ith input among N at run time.

#### Usage

```
selectn(N,i)
_,_,_,_ : selectn(4,2) : _  // selects the 3rd input among 4
```

Where:

* `N`: number of inputs (int, known at compile time, N > 0)
* `i`: input to select (int, numbered from 0)

#### Example test program

```
N=64; 
process = par(n,N, (par(i,N,i) : selectn(N,n)));
```

---


### `select2stereo`
Select between 2 stereo signals.

#### Usage

```
_,_,_,_ : select2stereo(bpc) : _,_,_,_
```

Where:

* `bpc`: the selector switch (0/1)

---


## Other

### `latch`
Latch input on positive-going transition of "clock" ("sample-and-hold").

#### Usage

```
_ : latch(clocksig) : _
```

Where:

* `clocksig`: hold trigger (0 for hold, 1 for bypass)

---


### `sAndH`
Sample And Hold.

#### Usage

```
_ : sAndH(t) : _
``` 

Where:

* `t`: hold trigger (0 for hold, 1 for bypass)

---


### `peakhold`
Outputs current max value above zero. 

#### Usage

```
_ : peakhold(mode) : _;
```

Where:

`mode` means: 0 - Pass through. A single sample 0 trigger will work as a reset.
   1 - Track and hold max value.

---


### `peakholder`
Tracks abs peak and holds peak for 'holdtime' samples.

#### Usage 

```
_ : peakholder(holdtime) : _;
```

---


### `impulsify`
Turns the signal from a button into an impulse (1,0,0,... when
button turns on).

#### Usage

```
button("gate") : impulsify ;
```

---


### `automat`
Record and replay to the values the input signal in a loop.

#### Usage

```
hslider(...) : automat(bps, size, init) : _
```

---


### Break Point Functions
bpf is an environment (a group of related definitions) that can be used to 
create break-point functions. It contains three functions : 

* `start(x,y)` to start a break-point function
* `end(x,y)` to end a break-point function
* `point(x,y)` to add intermediate points to a break-point function

A minimal break-point function must contain at least a start and an end point :

```
f = bpf.start(x0,y0) : bpf.end(x1,y1);
```

A more involved break-point function can contains any number of intermediate 
points:

```
f = bpf.start(x0,y0) : bpf.point(x1,y1) : bpf.point(x2,y2) : bpf.end(x3,y3);
```

In any case the `x_{i}` must be in increasing order (for all `i`, `x_{i} < x_{i+1}`).
For example the following definition :

```
f = bpf.start(x0,y0) : ... : bpf.point(xi,yi) : ... : bpf.end(xn,yn);
```

implements a break-point function f such that :

* `f(x) = y_{0}` when `x < x_{0}`
* `f(x) = y_{n}` when `x > x_{n}`
* `f(x) = y_{i} + (y_{i+1}-y_{i})*(x-x_{i})/(x_{i+1}-x_{i})` when `x_{i} <= x` 
and `x < x_{i+1}`

---


### `bypass1`
Takes a mono input signal, route it to `e` and bypass it if `bpc = 1`.

#### Usage

```
_ : bypass1(bpc,e) : _
```

Where:

* `bpc`: bypass switch (0/1)
* `e`: a mono effect

---


### `bypass2`
Takes a stereo input signal, route it to `e` and bypass it if `bpc = 1`.

#### Usage

```
_,_ : bypass2(bpc,e) : _,_
```

Where:

* `bpc`: bypass switch (0/1)
* `e`: a stereo effect

---

