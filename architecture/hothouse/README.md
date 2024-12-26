# faust2hothouse

The **faust2hothouse** tool compiles a Faust DSP program for the [Cleveland Hothouse DIY Pedal](https://clevelandmusicco.com/hothouse-diy-digital-signal-processing-platform-kit/). The script produces a folder containing the C++ source code and a Makefile to compile it.  

`faust2hothouse [-midi] [-nvoices <num>] [-sr <num>] [-bs <num>] [-source] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-midi`: to activate MIDI control
- `-nvoices <num>`: to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI over micro-USB.
- `-sr <num>`: to specify sample rate (default 48000, or 96000, not 44100)
- `-bs <num>`: to specify buffer size (default 48)
- `-source`: to only create the source folder

The default optimization is for file size: `OPT=-Os`. You can optimize for speed by setting `OPT=-O2` or the even more aggressive setting `OPT=-O3`.

Before running the script, you should clone the [Hothouse Examples](https://github.com/clevelandmusicco/HothouseExamples/) ([instructions](https://github.com/clevelandmusicco/HothouseExamples/wiki/10%E2%80%90Minute-Quick-Start#getting-and-initializing-the-code)):
```bash
cd ~/GitHub # where we'll keep HothouseExamples
git clone https://github.com/clevelandmusicco/HothouseExamples
cd HothouseExamples
git submodule update --init --recursive
make -C libDaisy
make -C DaisySP
```

Then proceed with the other [instructions](https://github.com/clevelandmusicco/HothouseExamples/wiki/10%E2%80%90Minute-Quick-Start#build-a-hothouse-example) for a Hothouse example. Once you've deployed a Hothouse example such as the `BasicTremolo`, we can try to use Faust code.

```bash
cd ~/GitHub/HothouseExamples
# Make our project directory and DSP
mkdir faust_projects && cd faust_projects
touch passthrough.dsp
echo "process = _,_;" > passthrough.dsp

# Build our stereo passthrough example.
# When it asks if the device is in DFU/bootloader mode,
# hold the left footswitch until you see a blinking pattern.
faust2hothouse passthrough.dsp
```

In the above snippet, if you want `faust_projects` to be anywhere, not necessarily inside `HothouseExamples`, then you must set the environment variable `HOTHOUSE_DIR` to the location of the [Hothouse Examples](https://github.com/clevelandmusicco/HothouseExamples/). For example, on macOS/Linux:
```bash
export HOTHOUSE_DIR=~/GitHub/HothouseExamples
```

If on macOS, consider putting the above text in `~/.zshrc` so that it's always set in Terminal.

## Hothouse Pedal

On the Hothouse pedal, the 6 knobs, 3 *toggle*-switches, and 2 *foot*-switches can be connected to UI controllers using metadata:

- `[knob:N]` (with `N` from 1 to 6) must be used in a `vslider`, `hslider` or `nentry` item to connect it to the knob number `N`. The knob's range can be anything, so you don't need to use `hslider("param1 [knob:1]", 0, 0, 1, .01)`.
- `[toggle:N]` (with `N` from 1 to 3) must be used in an `nentry` item to connect it to the *toggle*-switch number `N`. You can use toggles in two ways:
- - "0 to 2": `nentry("param1 [toggle:1]", 0, 0, 2, 1)` where 0 is when the toggle is pointing down.
- - "custom menu with 3 choices": `nentry("param1 [toggle:1][style:menu{'low':110;'mid':330;'high':770}]",0,0,770,1)`
- `[foot:N]` (with `N` from 1 to 2) must be used in a `button` or `checkbox` item to connect it to the *foot*-switch number `N`.
- - `foot:1` should only be a `checkbox` (not a `button`) because holding down the left footswitch is meant to activate bootloader mode.

Other metadata:

- `[scale:lin|log|exp]` metadata is implemented for knobs.

## Memory Limits (SDRAM)

The Hothouse should be used with a Daisy Seed with 65MB memory. Inside `faust2hothouse`, we execute a Python script that modifies the generated C++ code to put large float buffers (e.g., delay lines) in SDRAM. For this to work, you must have `python3` available on the command line.

## DSP Examples

### basic_gain.dsp
```faust
// Use the first knob to adjust gain.
import("stdfaust.lib");
gain = hslider("Gain [knob:1][unit:dB]", -80, -80, 0, .01) : ba.db2linear;
process = _*gain, _*gain;
```

### tapestop.dsp

This is a tapestop example that uses [Widget Modulation](https://faustdoc.grame.fr/manual/syntax/#widget-modulation) and whose appearance in the online [IDE](https://faustide.grame.fr/) mimics the Hothouse.
```faust
import("stdfaust.lib");

row1(x) = vgroup("Pedal", hgroup("[0] row1", x));
row2(x) = vgroup("Pedal", hgroup("[1] row2", x));
toggle(x) = vgroup("Pedal", hgroup("[2] toggle", x));
foot(x) = vgroup("Pedal", hgroup("[3] foot", x));

process = [
    "Stop Time": row1(hslider("h:Knob 1/Stop Time [knob:1][unit:ms][style:knob]", 50, 10, 4000, 1)),
    "Stop Alpha": row1(hslider("h:Knob 2/Stop Alpha [knob:2][style:knob]", 1, .01, 2, .01)),
    "Gain Alpha": row1(hslider("h:Knob 3/Gain Alpha [knob:3][style:knob]", 1, .01, 2, .01)),
    "Crossfade": row2(hslider("h:Knob 4/Crossfade [knob:4][unit:ms][style:knob]", 3, 0, 125, 1)),
    "Stop": foot(button("h:Foot 2/Stop [foot:2]"))
    -> dm.tapeStop_demo
];
```

## Architecture files

Specific architecture files have been developed:

- [faust/gui/HothouseControlUI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/HothouseControlUI.h): to be used with the DSP `buildUserInterface` method to implement `button`, `checkbox`, `hslider`, `vslider`, `nentry` controllers, and interpret the specific metadata previously described.
- [faust/midi/daisy-midi.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/daisy-midi.h): implements a [midi_handler](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/midi.h) subclass to decode incoming MIDI events.
