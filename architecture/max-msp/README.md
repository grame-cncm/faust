# faust2max6/faust2msp

The **faust2max6/faust2msp** tools transform a Faust DSP program into a compiled Max/MSP external, and a ready-to-use patch to load and use it. Polyphonic and MIDI controllable instruments can be created. Note that **faust2msp** is the old version compiling 32 bits external for Max5, and **faust2max6** compiles 64 bits for Max6 and newer versions, and should be preferably used. 

## How to use

**faust2max6** is used with the following options: 

`faust2max6 [-opt native|generic] [-native] [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-osc] [-us <factor>] [-ds <factor>] [-filter <filter>] [-universal] [-nopatch] [-nopost] [-soundfile/-soundfile-static] [additional Faust options (-vec -vs 8...)] <file.dsp>` 

By default it will create the *file~.mxo* external along with a *file.maxpat* patch file and a *ui.js* helper file, that will load the external and automatically create a User Interface (with sliders, buttons...) ready to control it. To be fully functional, the object still has to be connected to audio inputs/outputs or other elements in the patch. **Double-click** on the object allow to display its controls with their **range**, **label**, **shortname** and **complete path**. Note that  *-double* compilation mode is used by default in **faust2max6**.

Attributes can be used at object creation time, for instance the following DSP code:

```
import("stdfaust.lib");
freq = hslider("freq", 200, 50, 1000, 0.01);
gain = hslider("gain", 0.5, 0, 1, 0.01);
process = os.sawtooth(freq) * gain;
```
can be started with the following `@freq 700` and `@gain 0.6` attributes to configure parameters at creation time. Note that labels containing whitespace (like "freq Hz") cannot be used as attributes, they will have to be renamed.

Depending of the number of audio inputs and outputs described in the DSP source code, the compiled .xmo/.xme object has:
- N inlets, the first one being the message control one and a regular audio inlet, an all other audio inlets
- M outlets, audio outs from 1 to M-1 (or 2 if MIDI outlet is created)
- an output messages outlet 
- the right most outlet is used to send MIDI messages if MIDI metadata are used in the DSP UI items, and is only created when the `-midi` option is used

### Controlling

The compiled .xmo/.xme object can be controlled with the following messages, which can be used depending of the parameters used at compilation time:

- `polyphony <nvoices>` : to set the DSP in polyphonic mode with *nvoices* (note that the DSP code has to follow the [polyphonic convention](https://faustdoc.grame.fr/manual/midi/))
- `osc <IP inport outport xmit[0|1] bundle[0|1]>`: to activate OSC control in input and output mode, possibly generating messages when *xmit = 1*, and in bundle mode when *bundle = 1* 
- `midievent <midi message>`: to receive and decode MIDI messages
- `init`: to generate all inputs and outputs control messages as a message list *[path, init, min, max]* that will be sent on the output messages outlet
- `dump`: to generate all inputs and outputs control messages as a message list *[path, cur, min, max]* that will be sent on the output messages outlet 
- `mute`: to mute audio rendering

When the object has bargraphs, their values are sent in the right most outlet as a message list *[path, cur, min, max]*.

#### Input controllers 

All control messages are received in the left most inlet (the signal + message inlet) with the `<label|shortname|path> <number>` syntax. Their number and exact syntax obviously depend of the actual Faust DSP code. `Label` is the simple name of the controller (like `freq` of `gain`), the `shortname` is the smallest unique name that can be used, and `path` is the complete path following the OSC convention (like `osc/freq` of `osc/gain` kind of path). The `shortname` or `path` syntax has to be used to be sure all controllers are distincts. The `number` parameter is the actual float value for the controller. 

#### Output controllers

When the object has bargraphs, their values are sent on the output messages outlet as a message list *[path, cur, min, max]*.

## Options:

Here are the available options:

  - `-opt native` : to activate the best compilation options for the native CPU
  - `-opt generic` : to activate the best compilation options for a generic CPU 
  - `-native` to compile for the native CPU (otherwise the 'generic' mode is used by default)
  - `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
  - `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI
  - `-midi` : to activate MIDI control
  - `-osc` : to activate OSC control
  - `-us <factor>` : upsample the DSP by a factor
  - `-ds <factor>` : downsample the DSP by a factor
  - `-filter <filter>` : use a filter for upsampling or downsampling [0..4]
  - `-universal` : to generate a 64 bits x86/ARM universal external on macOS 
  - `-nopatch` : to deactivate patch generation
  - `-nopost` : to disable Faust messages to Max console
  - `-soundfile`: when compiling DSP using 'soundfile' primitive, to add the needed resources (soundfiles) in the produced .mxo file, and have the required libsndfile library statically linked
  - `-soundfile-dynamic` : when compiling DSP using 'soundfile' primitive, to add the needed resources (soundfiles) in the produced .mxo file, and use the installed libsndfile library (so possibly using dynamic link)
  - `-help or -h` : shows the different options 
 
The *faust2msp* tools has to be used to create old Max5 compatible externals, the **faust2max6** tools has to be used starting with Max6. 

## Configuration:

If you plan to use **faust2max6/faust2msp** on your own machine, you will have to:

- install [Max/MSP SDK](https://cycling74.com/downloads/sdk)
- edit the `faust/tools/faust2appls/faustpath` script to properly setup the $MAXSDK variable, then re-install the scripts again using `sudo make install`
- alternatively you can locally change the $MAXSDK variable in a terminal using `export MAXSDK=/your/alternate/path`, then use **faust2max6/faust2msp** in this terminal.

## Misc:

- the original DSP file as well as the compiled self-contained C++ file are kept in the compiled `.mxo` external, to be accessed using the *Show Package Contents* option. 

# faust2rnbo

The **faust2rnbo** tool transforms a Faust DSP program into a RNBO patch including the generated codebox code.

## How to use

**faust2rnbo** is used with the following options: 

`faust2rnbo [options] [additional Faust options (-vec -vs 8...)] <file.dsp>` 

## Options:

Here are the available options:

  - `-compile` : to trigger C++ compilation at load time

By default it will create the *file.maxpat* patch file.
