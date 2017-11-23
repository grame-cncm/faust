# faust2nodejs

faust2nodejs can be used to generate Faust-based nodejs native addons. The 
generated addons can embed most of the audio engines supported by Faust: alsa, 
JACK, CoreAudio, RtAudio, PortAudio, etc. Since faust2nodejs essentially acts 
as a wrapper to faust2api, it offers the same features than this system (MIDI 
and OSC suport, polyphony, separate effect file, etc.).

## Requirements

The latest version of [nodejs](https://nodejs.org) should be installed on your
system. Additionally, you should make sure that `node-gyp` is available on
your computer. 

On the mac:

```
sudo npm install node-gyp -g
```

On Linux:

```
sudo apt install node-gyp && npm install node-gyp -g
```

As for other Faust architectures, the various SDKs/development files associated 
with the targeted audio engine should also be installed. For example, if 
creating a nodejs addon with a JACK driver, libjack should be installed, etc.

## Generating a Faust Nodejs Native Addon

In a terminal window, just call:

```
faust2nodejs [DRIVER] [OPTIONS] faustFile.dsp
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

The generated addon will take the DSP name.

## Using the Generated Addon

Generated Faust addons use essentially the same API than 
[faust2api](https://ccrma.stanford.edu/~rmichon/faust2api/) (click on the link
for an exhaustive overview of the API). Typically, the "life cycle" of an 
addon will look like:

First load it:

```
const faust = require('./faustFile');
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

Several addons can possibly be loaded and used at the same time. This is especially interesting when using the JACK driver, since each of them will appear as a separated JACK client.   

## Know Issues

For now, even though Alsa native nodejs and addons can be generated and 
compiled without any issue, they crash during the constructor call with:

```
pcm_misc.c:380: snd_pcm_format_size: Assertion `0' failed.
```

Weirdly, Alsa audio engines generated with faust2api are fine when called from
a test C++ program. It seems that the problem comes from the setting of the
sample format in `alsa-dsp.h`:

```
// search for 32-bits or 16-bits format
err = snd_pcm_hw_params_set_format (stream, params, SND_PCM_FORMAT_S32);
if (err) {
  err = snd_pcm_hw_params_set_format (stream, params, SND_PCM_FORMAT_S16);
  check_error_msg(err, "unable to set format to either 32-bits or 16-bits");
}
snd_pcm_hw_params_get_format(params, &fSampleFormat);
```

For some reasons, even though `snd_pcm_hw_params_set_format` doesn't return an
error, it doesn't seem to set the desired sample format (`fSampleFormat` is
always equal to `S8` while it should be `S32_LE`).
