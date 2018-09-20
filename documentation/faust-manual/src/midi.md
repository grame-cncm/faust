# MIDI and Polyphony Support

<!-- TODO: something should be said about MIDI channels -->

Similarly to [OSC](#osc-support), several Faust architectures also provide MIDI 
support. This allows Faust applications to be controlled from any MIDI device 
(or to control MIDI devices). MIDI is also the preferable way to control 
Polyphonic instruments.

<!-- TODO: more about link between MIDI and polyphony in general -->

## Configuring MIDI in Faust

MIDI support can be added to any Faust program (as long as the target 
architecture supports it: see tables below) simply by adding the `[midi:on]` 
metadata to the [standard `option` metadata](#standard-metadata):

```
declare options "[midi:on]";
```

<!-- TODO: the tables indicating which architectures implement MIDI support
should be placed here. -->

MIDI control is configured in Faust using [metadata](#ui-label-metadata) 
in [UI elements](#user-interface-primitives-and-configuration). They are 
decoded by a special architecture that parses incoming MIDI messages and 
updates the appropriate control parameters, or send MIDI messages when the UI 
elements (i.e., sliders, buttons, etc.) are moved.

All MIDI configuration metadata in Faust follow the following format:

```
[midi:xxx yyy...]
```

This section provides a list of the most common metadata that can be used to
configure of the MIDI behavior of a Faust program.

> Below, when a 7-bit MIDI parameter is used to drive a 
[button](#button-primitive) or a [checkbox](#checkbox-primitive), its maximum 
value (127) maps to 1 ("on") while its minimum value (0) maps to 0 ("off").

### `[midi:ctrl num]` Metadata

The `[midi:ctrl num]` metadata assigns MIDI CC (control) to a specific UI 
element. When used in a slider or a bargraph, this metadata will map the UI 
element value to the {0, 127} range. When used with a button or a checkbox, 
1 will be mapped to 127, 0 will be mapped to 0.

**Usage**

```
toto = hslider("toto[midi:ctrl num]",...);
```

Where:

* `num`: the MIDI CC number

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by MIDI CC 11. When CC11=0, then the frequency is 200Hz, when 
CC11=127, then the frequency is 1000Hz.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:ctrl 11]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

### `[midi:keyon midikey]` Metadata

The `[midi:keyon midikey]` metadata assigns the velocity value of a key-on MIDI 
message received on a specific `midikey` to a Faust parameter. When used in a 
slider or a bargraph, this metadata will map the UI element value to the 
{0, 127} range. When used with a button or a checkbox, 1 will be mapped to 127, 
0 will be mapped to 0.

**Usage**

```
toto = hslider("toto[midi:keyon midikey]",...);
```

Where:

* `midikey`: the MIDI key number

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by the velocity value received on key 62 when a key-on message is
sent. Therefore, the frequency will only be updated when MIDI key 62 is pressed.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:keyon 62]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

### `[midi:keyoff midikey]` Metadata

The `[midi:keyoff midikey]` metadata assigns the velocity value of a key-off MIDI 
message received on a specific `midikey` to a Faust parameter. When used in a 
slider or a bargraph, this metadata will map the UI element value to the 
{0, 127} range. When used with a button or a checkbox, 1 will be mapped to 127, 
0 will be mapped to 0.

**Usage**

```
toto = hslider("toto[midi:keyoff midikey]",...);
```

Where:

* `midikey`: the MIDI key number

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by the velocity value received on key 62 when a key-off message is
sent. Therefore, the frequency will only be updated when MIDI key 62 is 
released.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:keyon 62]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

### `[midi:key midikey]` Metadata

The `[midi:key midikey]` metadata assigns the velocity value of key-on and 
key-off MIDI messages received on a specific `midikey` to a Faust parameter. 
When used in a slider or a bargraph, this metadata will map the UI element 
value to the {0, 127} range. When used with a button or a checkbox, 1 will be 
mapped to 127, 0 will be mapped to 0.

**Usage**

```
toto = hslider("toto[midi:key midikey]",...);
```

Where:

* `midikey`: the MIDI key number

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by the velocity value received on key 62 when key-on and key-off 
messages are sent. Therefore, the frequency will only be updated when MIDI key 
62 is pressed and released.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:key 62]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

### `[midi:keypress midikey]` Metadata

The `[midi:keypress midikey]` metadata assigns the pressure (after-touch) value 
of a specific `midikey` to a Faust parameter. When used in a slider or a 
bargraph, this metadata will map the UI element value to the {0, 127} range. 
When used with a button or a checkbox, 1 will be mapped to 127, 0 will be 
mapped to 0.

**Usage**

```
toto = hslider("toto[midi:keypress midikey]",...);
```

Where:

* `midikey`: the MIDI key number

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by the pressure (after-touch) values received on key 62.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:keypress 62]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

<!-- TODO: don't understand what those means: check with Stéphane  -->
<!-- 
- \lstinline'[midi:pgm num]' in a slider or bargraph will map the UI element value to the progchange value, so \emph{progchange} message with the same \emph{num} value will be sent. When used with a button or checkbox, 1 will send the \emph{progchange} message with \emph{num} value, 0 will send nothing,

- \lstinline'[midi:chanpress num]' in a slider or bargraph will map the UI element value to the chanpress value, so \emph{chanpress} message with the same \emph{num} value will be sent. When used with a button or checkbox, 1 will send the \emph{chanpress} message with \emph{num} value, 0 will send nothing,
-->

### `[midi:pitchwheel]` Metadata

The `[midi:pitchwheel]` metadata assigns the pitch-wheel value to a 
Faust parameter. When used in a slider or a bargraph, this metadata will map 
the UI element value to the {0, 16383} range. When used with a button or a 
checkbox, 1 will be mapped to 16383, 0 will be mapped to 0.

**Usage**

```
toto = hslider("toto[midi:pitchwheel]",...);
```

**Example**

In the following example, the frequency of a sawtooth wave oscillator is 
controlled by the pitch-wheel.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("frequency[midi:pitchwheel]",200,50,1000,0.01) : si.smoo;
process = os.sawtooth(freq);
```
<!-- /faust-run -->

### `[midi:start]` Metadata

When used with a button or a checkbox, `[midi:start]` will trigger a value of 
1 when a `start` MIDI message is received. 

**Usage**

```
toto = checkbox("toto[midi:start]");
```

### `[midi:stop]` Metadata

When used with a button or a checkbox, `[midi:stop]` will trigger a value of 
0 when a `stop` MIDI message is received. 

**Usage**

```
toto = checkbox("toto[midi:stop]");
```

### `[midi:clock]` Metadata

When used with a button or a checkbox, `[midi:clock]` will deliver a sequence 
of successive 1 and 0 values each time a `clock` MIDI message is received (seen
by Faust code as a square command signal, to be used to compute higher level
information).

**Usage**

```
toto = checkbox("toto[midi:clock]");
```

### MIDI Sync

MIDI clock-based synchronization can be used to slave a given Faust program
using the metadata presented in the 3 past sections.

A typical Faust program will then use the MIDI clock stream to possibly compute 
the BPM information, or for any synchronization need it may have.  Here is a 
simple example of a sinus generated which a frequency controlled by the MIDI 
clock stream, and starting/stopping when receiving the MIDI start/stop 
messages:

<!-- faust-run -->
```
import("stdfaust.lib");

// square signal (1/0), changing state at each received clock
clocker = checkbox("MIDI clock[midi:clock]");    

// ON/OFF button controlled with MIDI start/stop messages
play = checkbox("ON/OFF [midi:start] [midi:stop]");    

// detect front
front(x) = (x-x') != 0.0;      

// count number of peaks during one second
freq(x) = (x-x@ma.SR) : + ~ _;   
   
process = os.osc(8*freq(front(clocker))) * play;
```
<!-- /faust-run -->

## MIDI Polyphony Support

Polyphony is conveniently handled in Faust directly by 
[Faust Architectures](TODO). Note that programming polyphonic instrument 
completely from scratch in Faust and without relying on architectures is also 
possible. In fact, this feature is indispensable if complex signal interactions 
between the different voices have to be described (like sympathetic strings 
resonance in a physical model, etc.). However, since all voices would always be 
computed, this approach could be too CPU costly for simpler or more limited 
needs. In this case describing a single voice in a Faust DSP program and 
externally combining several of them with a special *polyphonic instrument 
aware* architecture file is a better solution. Moreover, this special 
architecture file takes care of dynamic voice allocation and control MIDI 
messages decoding and mapping. 

Polyphony support can be added to any Faust program (as long as the target 
architecture supports it) simply by adding the `[nvoices:n]` metadata
to the [standard `option` metadata](#standard-metadata) where `n` is the
maximum number of voices of polyphony to be allocated:

```
declare options "[nvoices:12]";
```

### Standard Polyphony Parameters

Most Faust architectures allow for the implementation of polyphonic instruments
simply by using a set of "standard user interface names." Hence, any Faust
program declaring the `freq`, `gain`, and `gate` parameter is 
polyphony-compatible. These 3 parameters are directly associated to key-on 
and key-off events and have the following behavior: 

* When a key-on event is received, `gate` will be set to 1. Inversely, when a 
key-off event is received, `gate` will be set to 0. Therefore, `gate` is 
typically used to trigger an envelope, etc.
* `freq` is a frequency in Hz computed automatically in function of the value 
of the pitch contained in a key-on or a key-off message. 
* `gain` is a linear gain (value between 0-1) computed in function of the
velocity value contained in a key-on or a key-off message.

**Example: Simple Polyphonic Synthesizer**

In the following example, the standard `freq`, `gain`, and `gate` parameters
are used to implement a simple polyphonic synth.

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("freq",200,50,1000,0.01);
gain = hslider("gain",0.5,0,1,0.01);
gate = button("gate");
process = os.sawtooth(freq)*gain*gate;
```
<!-- /faust-run -->

> Note that if you execute this code in the 
[Faust online editor](https://faust.grame.fr/editor) with polyphony
mode activated, you should be able to control this simple synth with any MIDI
keyboard connected to your computer. This will only work if you're using
Google Chrome (most other browsers are not MIDI-compatible).

The previous example can be slightly improved by adding an envelope generator
and controlling it with `gain` and `gate`: 

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("freq",200,50,1000,0.01);
gain = hslider("gain",0.5,0,1,0.01);
gate = button("gate");
envelope = en.adsr(0.01,0.01,0.8,0.1,gate)*gain;
process = os.sawtooth(freq)*envelope;
```
<!-- /faust-run -->

**Warning:** Note that all the active voices of polyphony are added together 
without scaling! This means that the previous example will likely click if
several voices are played at the same time. It is the Faust programmer's
responsibility to take this into account in his code. For example, 
assuming that the number of active voices will always be smaller or equal to
4, the following safeguard could be added to the previous example:

```
process = os.sawtooth(freq)*envelope : /(4);
``` 

### Configuring and Activating Polyphony

Polyphony can be activated "manually" in some Faust architectures using an 
option/flag during compilation (e.g., typically `-poly` or `-nvoices` in the 
[faust2...](TODO) scripts). That's also how the 
[Faust online editor](https://faust.grame.fr/editor) works where a button can
be used to turn polyphony on or off.

However, the most standard way to activate polyphony in Faust is to declare
the `[nvoices:n]` metadata which allows us to specify the maximum number of 
voices of polyphony (`n`) that will be allocated in the generated program.

For example, the Faust program from the previous section could be modified such
that: 

<!-- faust-run -->
```
declare options "[midi:on][nvoices:12]";
import("stdfaust.lib");
freq = hslider("freq",200,50,1000,0.01);
gain = hslider("gain",0.5,0,1,0.01);
gate = button("gate");
envelope = en.adsr(0.01,0.01,0.8,0.1,gate)*gain;
process = os.sawtooth(freq)*envelope;
```
<!-- /faust-run -->

> Note that the `[midi:on]` metadata must also be declared in order to be able
to control this program with an external MIDI keyboard.

which when compiled running (for example):

```
faust2jaqt faustProgram.dsp
```

will generate a MIDI-controllable polyphonic synthesizer.

### Audio Effects and Polyphonic Synthesizer

While audio audio effects can be added directly to the `process` line of a
Faust synthesizer, for example:

```
process = os.sawtooth(freq)*envelope : reverb;
```

it is not a good practice since a new instance of that effect will be created
for each active voice of polyphony. The main consequence of this would be an
increased CPU cost.

Similarly to `process`, Faust allows for the declaration of an `effect` line,
which identifies an audio effect to be connected to the output of the 
polyphonic synthesizer. `effect` is a standard variable in Faust (just like
`process`).

For example, a simple reverb can be added to the previous example simply by
writing:

<!-- faust-run -->
```
declare options "[midi:on][nvoices:12]";
import("stdfaust.lib");
freq = hslider("freq",200,50,1000,0.01);
gain = hslider("gain",0.5,0,1,0.01);
gate = button("gate");
envelope = en.adsr(0.01,0.01,0.8,0.1,gate)*gain;
process = os.sawtooth(freq)*envelope <: _,_;
effect = dm.zita_light;
```
<!-- /faust-run -->

In this case, the polyphonic part is based on `process` and a single instance
of the effect defined in `effect` will be created and shared by all voices.

Note that since [`dm.zita_light`](TODO) is a stereo effect, the output of
`process` must be split into 2 signals. Also, be aware that this type of
construction wont be visible in the corresponding block diagram that will only
show what's implemented in the `process` line.

<!-- TODO: in poly mode, effect should automatically activated -->

### Polyphony and Continuous Pitch

Key-on and key-off MIDI messages only send the "base pitch" of the instance of
a note. Hence, if only the `freq` standard parameter is used to control the
frequency of the synthesizer, its pitch will always be "quantized" to the 
nearest semitone. In order to be able to do glissandi, vibrato, etc., a
variable associated to the pitch-wheel needs to be declared and must interact
with the "base frequency" value retrieved from `freq` as such:

```
f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01);
freq = f*bend; // the "final" freq parameter to be used
```

The `bend` variable is controlled by the pitch-wheel thanks to 
[`[midi:pitchwheel]` metadata](#midipitchwheel-metadata). `bend` is used as a
factor multiplied to the base frequency retrieved from `freq`. Therefore, the
default value of `bend` should always be 1 which corresponds to the central
position of the pitch wheel (MIDI value 64). A value smaller than 1 will
decrease the pitch and a value greater than 1 will increase it. 

While the above example will have the expected behavior, it is likely that 
clicking will happen when changing the value of `bend` since this parameter is
not smoothed. Unfortunately, regular smoothing (through the use of 
[`si.smoo`](TODO), for example) is not a good option here. This is due to the
fact that instances of polyphonic voices are frozen when a voice is not being
used. Since the value of `bend` might jump from one value to another when a
voice is being reactivated/reused, continuous smoothing would probably create
an "ugly sweep" in that case. Hence, [`si.polySmooth`](TODO) should be used in
this context instead of [`si.smoo`](TODO). This function shuts down smoothing
for a given number of samples when a trigger is activated.

Reusing the example from the previous section, we can implement a click-free 
polyphonic synthesizer with continuous pitch control:

<!-- faust-run -->
```
declare options "[midi:on][nvoices:12]";
import("stdfaust.lib");
f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",0.5,0,1,0.01);
gate = button("gate");
freq = f*bend; 
envelope = en.adsr(0.01,0.01,0.8,0.1,gate)*gain;
process = os.sawtooth(freq)*envelope <: _,_;
effect = dm.zita_light;
```
<!-- /faust-run -->

Observe the usage of [`si.polySmooth`](TODO) here: when `gate=0` the signal is
not smoothed, when `gate=1` the signal is smoothed with a factor of 0.999 after
one sample.

### Complete Example: Sustain Pedal and Additional Parameters

Just for fun ;), we improve in this section the example from the previous one
by implementing sustain pedal control as well as some modulation controlled by 
the modulation wheel of the MIDI keyboard. 

Sustain pedal control can be easily added simply by declaring a sustain
parameter controlled by MIDI CC 64 (which is directly linked to the sustain
pedal) and interacting with the standard `gate` parameter:

```
s = hslider("sustain[midi:ctrl 64]",0,0,1,1);
t = button("gate");
gate = t+s : min(1);
```

Hence, `gate` will remain equal to 1 as long as the sustain pedal is pressed.

The simple synthesizer from the previous section (which is literally just a
sawtooth oscillator) can be slightly improved by processing it with a 
dynamically-controlled lowpass filter:

<!-- faust-run -->
```
declare options "[midi:on][nvoices:12]";
import("stdfaust.lib");
f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",0.5,0,1,0.01);
s = hslider("sustain[midi:ctrl 64]",0,0,1,1);
cutoff = hslider("cutoff[midi:ctrl 1]",1000,50,4000,0.01) : si.smoo;
t = button("gate");
freq = f*bend; 
gate = t+s : min(1);
envelope = en.adsr(0.01,0.01,0.8,0.1,gate)*gain;
process = os.sawtooth(freq)*envelope : fi.lowpass(3,cutoff) <: _,_;
effect = dm.zita_light;
```
<!-- /faust-run -->

MIDI CC 1 corresponds to the modulation wheel which is used here to control
the cut-off frequency of the lowpass filter.

<!-- Note: the original documentation of polyphony support from the quick 
reference hasn't been integrated to this new doc. We believe that it scares
people more than it helps them. We do think that it would be nice to have a
proper description of the C++ implementation of poly-dsp, but this is the
wrong place for it. -->