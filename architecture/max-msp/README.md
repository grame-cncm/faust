# faust2max6/faust2msp

faust2max6/faust2msp transform a Faust DSP program into a compiled Max/MSP external, and a ready-to-use patch to load and use it. Polyphonic and MIDI controllable synthesisers can be created. 

## How to use

faust2max6/faust2msp are used with the following command: 

`faust2max6 [-opt native|generic] [-native] [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-osc] [-universal] [-nopatch] [-soundfile/-soundfile-static] [additional Faust options (-vec -vs 8...)] <file.dsp>` 

By default it will create *file~.mxo* external along with a *file.maxpat* patch file and a *ui.js* helper file, that will load the external and automatically create a User Interface (with sliders, buttons...) ready to control it. To be fully functional, the object still has to be connected to audio inputs/outputs or other elements in the patch. **Double-click** on the object allow to display its controls with their **label**, **range** and **complete path**. 

## Options

The following options are available: 

  - `-opt native` : to activate the best compilation options for the native CPU
  - `-opt generic` : to activate the best compilation options for a generic CPU 
  - `-native` to compile for the native CPU (otherwise the 'generic' mode is used by default)
  - `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
  - `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI
  - `-midi` : to activate MIDI control
  - `-osc` : to activate OSC control
  - `-universal` : to generate a 64/32 bits external
  - `-nopatch` : to deactivate patch generation
  - `-soundfile` : when compiling DSP using 'soundfile' primitive, to add needed resources
  - `-soundfile-static` when compiling DSP using 'soundfile' primitive, to add needed resources in static mode
  - `-help or -h` : shows the different options 
 
The *faust2msp* tools has to be used to create old Max5 compatible externals, the *faust2max6* tools has to be used starting with Max6. 

## Configuration

If you plan to use faust2max6/faust2msp on your own machine, you will have to:

- install [Max/MSP SDK](https://cycling74.com/downloads/sdk)
- edit the `faust/tools/faust2appls/faustpath` script to properly setup the $MAXSDK variable
- install Faust again using `sudo make install`
