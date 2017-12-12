# faust2max6/faust2msp

faust2max6/faust2msp transforms a Faust DSP program into a compiled Max/MSP external and a ready-to-use patch to load and use it. Polyphonic and MIDI controllable synthesisers can be created. 

## How to use

faust2max6/faust2msp is used with the following command: 

`faust2max6 [-nvoices <num>] [-effect <effect.dsp>] [-midi] [-nopatch] <file.dsp>` 

By default it will create *file~.mxo* external along with a *file.maxpat* patch file and a *ui.js* helper file, that will load the external and automatically create a User Interface (with sliders, buttons...) ready to control it. To be fully functional, the object still has to be connected to audio inputs/outputs or other elements in the patch. **Double-click** on the object allow to display its controls with their **label**, **range** and **complete path**. 

## Options

The following options are available: 

  - `-nvoices <num> to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI`
  - `-effect <effect.dsp> to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI`
  - `-midi to activate MIDI control`
  - `-nopatch' to deactivate patch generation`

The *faust2msp* tools has to be used to create old Max5 compatible externals, the *faust2max6* tools hast to be used starting with Max6. 
