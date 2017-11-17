# faust2nodejs

faust2nodejs can be used to generate Faust-based nodejs native addons. The 
generated addons can embed most of the audio engines supported by Faust: alsa, 
JACK, coreaudio, rtaudio, portaudio, etc. Since faust2nodejs essentially acts 
as a wrapper to faust2api, it offers the same features than this system (MIDI 
and OSC suport, polyphony, separate effect file, etc.).

## Requirements

The latest version of [nodejs](https://nodejs.org) should be installed on your
system. Additionally, you should make sure that `node-gyp` is available on
your computer. If it's not the case, typical installation steps on Linux would
be: `sudo apt install node-gyp && npm install node-gyp -g`.

As for other Faust architectures, the various SDKs/development files associated 
with the targeted audio engine should also be installed. For example, if 
creating a nodejs addon with a JACK driver, libjack should be installed, etc.

## Generating a Faust Nodejs Native Addon

In a terminal window, just call:

```
faust2nodjs [DRIVER] [OPTIONS] faustFile.dsp
```

With [DRIVER]:

* `-coreaudio`: coreaudio audio engine
* `-alsa`: alsa audio engine
* `-jack`: JACK audio engine
* `-portaudio`: portaudio audio engine
* `-rtaudio`: rtaudio audio engine
* `-dummy`: dummy audio engine

and with [OPTION] (mostly inherited from [faust2api](https://ccrma.stanford.edu/~rmichon/faust2api/)):

* `-nvoices N`: creates a polyphonic object with N voices.
* `-effect <effect.dsp>`: adds an effect to the polyphonic synth (this option 
  is ignored if `-nvoices` is not specified).
* `-midi`: add built-in RtMidi support to the API.
* `-osc`: add built-in OSC support to the API.
* `-source`: generates the source of the addon without compiling it.
* `-electronv <VERSION>`: allows to specify the current version of electron if
generating an addon for this framework.
* `-debug`: prints compilation output.

## Using the Generated Addon

Generated Faust addons use essentially the same API than 
[faust2api](https://ccrma.stanford.edu/~rmichon/faust2api/) (click on the link
for an exhaustive overview of the API). Typically, the "life cycle" of an 
addon will look like:

First load it:

```
const faust = require('./faust');
```

instantiate it:

```
var dspFaustNode = new faust.DspFaustNode(); // for audio engines where the sampling rate and the buffer length are imposed (e.g., JACK, etc.) 
var dspFaustNode = new faust.DspFaustNode(44100,512); // for audio engines where the sampling rate and the buffer length are chosen by the user (e.g., Alsa, CoreAudio, etc.)
```

start it:

```
dspFaustNode.start();
```

change some parameters:

```
dspFaustNode.setParamValue("paramAddress",value);
// or
dspFaustNode.setParamValue(paramID,value);
```

Parameters address and ID can be easily with:

```
for(i=0;i<dspFaustNode.getParamsCount();i++){
  console.log("ID: " + i + " Address: " + dspFaustNode.getParamAddress(i));
}
``` 

stop it:

```
dspFaustNode.stop();
```

destroy it (forces garbage collection - necessary in most cases):

```
dspFaustNode.destroy();
```
