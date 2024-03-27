

This folder contains useful scripts that combines Faust and the C++ compiler to generates executable binary. Use `-h` or `-help` to get more information on each specific script options. Additional  Faust compiler options (like `-vec -lv 0 -I /path/to/lib`) can be given. You can possibly use the  `CXXFLAGS` environment variable to give additional options to the C++ compiler.

You can use 'sudo make install' to install them. 

###  The following scripts generate audio applications

* `faust2alqt <file.dsp>` : create ALSA/QT application for each input file

* `faust2alsa <file.dsp>` : create ALSA/GTKk application for each input file

* `faust2au <file.dsp>` : create Audio Unit Effect for each input file

* `faust2ausynth <file.dsp>` : create Audio Unit Synth for each input file

* `faust2caqt  <file.dsp>` : create a CoreAudio/QT application for each input file

* `faust2csound <file.dsp>` : create a CSOUND plugin for each input file

* `faust2dssi <file.dsp>` : create a DSSI plugin for each input file

* `faust2gen <file.dsp>` : create a wrapping Max/MSP patch that uses faustgen~ for each input file

* `faust2jack <file.dsp>` : create JACK/GTK application for each input file

* `faust2jaqt <file.dsp>` : create JACK/QT application for each input file

* `faust2juce <file.dsp>` : create JUCE Projucer project for each input file

* `faust2ladspa <file.dsp>` : create a LADSPA plugin for each input file

* `faust2lv2 <file.dsp>` : create an LV2 plugin for each input file

* `faust2max6 <file.dsp>` : create a Max/MSP 6 plugin (64 bits samples) for each input file and a wrapping patch

* `faust2msp <file.dsp>` : create a Max/MSP 4 or 5 plugin (32 bits samples) for each input file and a wrapping patch

* `faust2paqt <file.dsp>` : create a PortAudio/QT application for each input file

* `faust2netjackqt <file.dsp>.` : create a NetJack/QT application for each input file

* `faust2netjackconsole <file.dsp>` : create a NetJack/console application for each input file

* `faust2pure <file.dsp>` : create a Pure plugin for each input file

* `faust2puredata <file.dsp>` : create a PureData plugin for each input file

* `faust2raqt <file.dsp>` : create a RTAudio/QT application for each input file

* `faust2sc.py <file.dsp>` : create a SuperCollider plugin including class files and help files for the input file. This is a python rewrite of `faust2supercollider` and `faust2sc`. 

* `faust2supercollider <file.dsp>` : create a SuperCollider plugin for each input file

* `faust2vst <file.dsp>` : create a VST plugin for each input file

* `faust2webaudio <file.dsp>` : create a HTML/WebAudioAPI (with JavaScript code) application for each input file
  
* `faust2wasm <file.dsp>` : using Emscripten compiler or wasm backend, create a WebAudioAPI node for each input file

* `faust2webaudiowasm <file.dsp>` : using Emscripten compiler or wasm backend, create a HTML/WebAudioAPI (with wasm code) application for each input file


NOTE: In the latest Faust versions there's also an alternative VST architecture available, featuring multi-channel MIDI, MIDI CC and MIDI Tuning Standard (MTS) support. It is invoked as follows:

* `faust2faustvst <file.dsp>` : create a VST plugin for each input file


### The following scripts can be used to generate block diagrams

* `faust2svg <file1.dsp>` : create svg block-diagrams for each input file

* `faust2png <file1.dsp>` : create png block-diagrams for each input file

* `faust2eps <file1.dsp>` : create eps block-diagrams for each input file


### The following scripts also integrate a visualization

* `faust2firefox <file1.dsp>` : faust2svg with visualization using firefox

* `faust2feh <file1.dsp>` : faust2svg with visualization using feh

* `faust2octave <file.dsp>` : faust2plot with visualization using octave   


### The following scripts can be used to generate documentation

* `faust2mathdoc <file.dsp>` : generate mathematical documentation 

* `faust2md <file.dsp>` : generate markdown documentation from the comments in the code
