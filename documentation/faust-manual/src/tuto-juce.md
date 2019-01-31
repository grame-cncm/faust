# Tutorial: Adding Faust DSP Support to Your JUCE Plug-ins

> This tutorial doesn't belong to the Faust manual. It will eventually
live in its own page. It has been placed here for now for convenience and
rapid prototyping.

[JUCE](https://juce.com/) is a well known framework for creating audio plug-ins
(i.e., VST, AU, AAX, etc.) and applications for a wide range of platforms. 
Faust can be used to generate ready-to-use JUCE applications and plug-ins
implementing the standard user interface (UI) described in the Faust code using
[faust2juce](TODO). However, it is sooo easy to make professional looking UIs 
from scratch in JUCE that you might want to use Faust to implement the DSP
portion of your plug-in and build your own UI.

In this tutorial, we demonstrate how to use [`faust2api`](TODO) to generate 
a JUCE audio engine from Faust and how to interface it with your JUCE
plug-in/UI. We'll cover basic examples as well as more advanced applications
involving polyphony, etc.

## "The Old Way": Brut-Force Method 

> If you're not interested by this brief page of history, you can jump directly 
to the [next section](#simple-synth-plug-in).

Before `faust2api` existed, it was already possible to use Faust to implement
the DSP portion of a JUCE plug-in. Indeed, the most basic way to use Faust is
to generate C++ code with the Faust compiler. Running:

```
faust someCode.dsp -o someCode.cpp
```

will output a C++ file (`someCode.cpp`) containing a class implementing a
ready-to-use audio callback (see [this tutorial](TODO)). Hence, it was just
a matter of using this class in your JUCE project, pass it the input buffers, 
retrieve the output buffers, and change potential parameters, etc. 
[This short (and potentially outdated) tutorial](https://ccrma.stanford.edu/courses/256a-fall-2016/lectures/faust/)
from 2016 demonstrates how this can be done.
 
Fortunately, things are simpler than ever nowadays and `faust2api` greatly
simplifies this process.

## Simple Synth Plug-In

[<< Download the source of this tutorial >>](misc/juce/SawtoothSynth.zip)

In this section, we demonstrate how to use a Faust synth to build a plug-in
in JUCE with a custom UI from scratch.

> This tutorial only demonstrates how to make a JUCE plug-in. Making a JUCE
standalone application following the same method is perfhttp://faust.grame.fr/manual/ectly possible with 
some adjustments.

### Generating the DSP Engine

First, let's implement a basic subtractive synthesizer in Faust based on a
filtered sawtooth wave ([`filteredSawtooth.dsp`](misc/juce/filteredSawtooth.dsp)):

<!-- faust-run -->
```
import("stdfaust.lib");
freq = nentry("freq",50,200,1000,0.01);
gain = nentry("gain",0.5,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;
cutoff = nentry("cutoff",10000,50,10000,0.01) : si.smoo;
process = os.sawtooth(freq)*gain*gate : fi.lowpass(3,cutoff) <: _,_;
```
<!-- /faust-run -->

Feel free to run it in the web editor to see how it sounds!

> The output of the lowpass is split into 2 signals to create a stereo
object.

Note that all the parameters are smoothed to prevent clicking (we want our
plug-in to be clean!). Even `gate` is smoothed, which will apply a gentle
exponential envelope when the trigger signal is sent, etc.

Since Faust will not build its own UI here, the type of UI element used in this
code doesn't really matter. They just serve as a point of entry to control the
parameters of the audio engine we're about to generate. So `nentry`, could be
replaced by `hslider` or `vslider`, it would not make any difference.
However, we encourage you to always write "coherent" interfaces in case
someone would like to use your Faust code "as such" at some point.

This Faust program can be turned into an audio engine for JUCE simply by
running the following command (assuming that Faust is properly installed on
your system):

```
faust2api -juce filterSawtooth.dsp
```

Alternatively (i.e., if you're an unfortunate Windows user), you can use the
Faust web editor to carry out the same task by choosing `source/juce` in the
export function.

In both cases, you'll end up with with a zip file containing a C++ file and
its companion header file as well as some automatically generated markdown
documentation. 

### Creating an Empty JUCE Plug-In Project

In this section, we'll assume that you're a bit familiar with 
[JUCE](https://juce.com/). If that's not your case, don't panic and just read
their [Getting started with the Projucer](https://docs.juce.com/master/tutorial_new_projucer_project.html)
tutorial. We also recommend you to have a look a the next few following 
tutorials to have a sense of how things work. They're nice and easy to read!

In the Projucer, create a new Audio Plug-In, add the targets that you want,
in the settings, make sure that "Plugin is a Synth" is enabled. In our case,
we named it "SawtoothSynth" (choose this name wisely as it will impact the
class names of your program).

<img src="img/juce/newPlugin.jpg" class="mx-auto d-block" width="70%">

Now, place `DspFaust.cpp` and `DspFaust.h` generated in the previous step in
the `Source` folder of your JUCE plug-in project. Then select these 2 files
in `Source` and drag them in the Projucer so that they become visible in the
`Source` tab:

<img src="img/juce/juceProject.jpg" class="mx-auto d-block" width="70%">

At this point, try to compile your plug-in and see if it runs. Remember that
JUCE now generates a "standalone plug-in" by default which is super convenient
to test things without having to open the plug-in in a third party application.

Let's now add our DspFaust object to the `PluginProcessor`. In 
`PluginProcessor.h`, include `DspFaust.h`:

```
#include "../JuceLibraryCode/JuceHeader.h"
#include "DspFaust.h"
```

and implement `DspFaust` in the private section of the `AudioProcessor` class:

```
private:
    DspFaust dspFaust;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawtoothSynthAudioProcessor)
``` 

In `PluginProcessor.cpp`, all we have to do is to call `dspFaust.start()` when
we want to start the Faust audio engine and `dspFaust.stop()` when we want to
stop it. No need to set the sampling rate or the buffer length, `dspFaust` takes
care of that for ya.

> Remember that the package generated by `faust2api` contains a documentation
of the generated API. Feel free to have a look at it to get a sense of what 
methods are available.

`dspFaust.start()` and `dspFaust.stop()` can be conveniently placed in the
constructor and destructor (respectively) of `SawtoothSynthAudioProcessor`:

```
SawtoothSynthAudioProcessor::SawtoothSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
  dspFaust.start();
}

SawtoothSynthAudioProcessor::~SawtoothSynthAudioProcessor()
{
  dspFaust.stop();
}
```

The default JUCE plug-in copies the input buffer in the output buffer. 
Therefore, make sure that the implementation of the `processBlock` method looks
like:

```
void SawtoothSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
```

(empty).

We now want to control the parameters of our `dspFaust` object. For that, the 
`setParamValue` method can be used. Since we want to control the parameters
of our synth from the `PluginEditor`, we create a series of public methods
in `PluginProcessor` to control each parameter of our synth. In 
`PluginProcessor.h` this will look like:

```
public:
  void setFreq(float freq);
  void setGain(float gain);
  void setCutoff(float cutoff);
  void setGate(bool gate);
```

and the corresponding implementation in `PluginProcessor.cpp` will be:

```
void SawtoothSynthAudioProcessor::setFreq(float freq)
{
  dspFaust.setParamValue("/synth/freq",freq);
}

void SawtoothSynthAudioProcessor::setGain(float gain)
{
  dspFaust.setParamValue("/synth/gain",gain);
}

void SawtoothSynthAudioProcessor::setGate(bool gate)
{
  if(gate){
    dspFaust.setParamValue("/synth/gate",1);
  }
  else{
    dspFaust.setParamValue("/synth/gate",0);
  }
}

void SawtoothSynthAudioProcessor::setCutoff(float cutoff)
{
  dspFaust.setParamValue("/synth/cutoff",cutoff);
}
```
 
Hence, `setParamValue` has 2 arguments: the path of the parameter in the Faust
code, and its value. Note that a list of all the available parameters of the
Faust object of their corresponding path can be found in the markdown 
documentation of the package generated with `faust2api`.

That's it for the `PluginProcessor`! Easy isn't it ;)? Now, let's add a basic
interface to control this synth.

We add a series of sliders, button, and labels to the private section of
`SawtoothSynthAudioProcessorEditor` in `PluginEditor.h`:

```
private:
  Slider frequencySlider;
  Slider gainSlider;
  Slider cutoffSlider;
  ToggleButton onOffButton;
    
  Label frequencyLabel;
  Label gainLabel;
  Label cutoffLabel;
  Label onOffLabel;
``` 

and their corresponding implementation in `PluginEditor.cpp`:

```
SawtoothSynthAudioProcessorEditor::SawtoothSynthAudioProcessorEditor (SawtoothSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
  setSize (800, 130);
  
  addAndMakeVisible (frequencySlider);
  frequencySlider.setRange (50.0, 5000.0);
  frequencySlider.setSkewFactorFromMidPoint (500.0);
  frequencySlider.setValue(300);
  frequencySlider.onValueChange = [this] {
    processor.setFreq(frequencySlider.getValue());  
  };

  addAndMakeVisible(frequencyLabel);
  frequencyLabel.setText ("Frequency", dontSendNotification);
  frequencyLabel.attachToComponent (&frequencySlider, true);
    
  addAndMakeVisible (gainSlider);
  gainSlider.setRange (0.0, 1.0);
  gainSlider.setValue(0.5);
  gainSlider.onValueChange = [this] { 
    processor.setGain(gainSlider.getValue()); 
  };
    
  addAndMakeVisible(gainLabel);
  gainLabel.setText ("Gain", dontSendNotification);
  gainLabel.attachToComponent (&gainSlider, true);
    
  addAndMakeVisible (cutoffSlider);
  cutoffSlider.setRange (50.0, 10000.0);
  cutoffSlider.setValue(5000.0);
  cutoffSlider.onValueChange = [this] { 
    processor.setCutoff(cutoffSlider.getValue()); 
  };
    
  addAndMakeVisible(cutoffLabel);
  cutoffLabel.setText ("Cutoff", dontSendNotification);
  cutoffLabel.attachToComponent (&cutoffSlider, true);
  
  addAndMakeVisible(onOffButton);
  onOffButton.onClick = [this] { 
    processor.setGate(onOffButton.getToggleState());
  };
    
  addAndMakeVisible(onOffLabel);
  onOffLabel.setText ("On/Off", dontSendNotification);
  onOffLabel.attachToComponent (&onOffButton, true);
}
```

The methods that we declared in the previous step are basically called to set
the value of the parameters of our DSP engine thanks to the `processor`
object.

The `resized` method must be implemented so that the various UI elements that 
we created actually have a size:

```
void SawtoothSynthAudioProcessorEditor::resized()
{
  const int sliderLeft = 80;
  frequencySlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
  gainSlider.setBounds (sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
  cutoffSlider.setBounds (sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
  onOffButton.setBounds (sliderLeft, 100, getWidth() - sliderLeft - 20, 20);
}
``` 

Finally, make sure that you clean the implementation of the `paint` method
to get rid of the default ugly "Hello World":

```
void SawtoothSynthAudioProcessorEditor::paint (Graphics& g)
{
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}
```

Note that the same approach can be used to create an audio effect: `DspFaust`
will take care of instantiating the input buffers, etc. so it should just
work right away as for this synth example.

Compile your plug-in and run it, it should look like this:

<img src="img/juce/plugin.jpg" class="mx-auto d-block" width="60%">

The goal of this section was just to show you how to integrate a Faust DSP
engine into a JUCE plug-in project and how to control it with a simple UI. 
Once again, JUCE is a powerful tool to implement sophisticated UI in a very
simple way. You'll find all the documentation you need on 
[their website](https://juce.com/) to start making beautiful plug-ins!

## Creating and Using a Polyphonic Faust DSP Object

[<< Download the source of this tutorial >>](misc/juce/SawtoothSynthPoly.zip)

In the second part of this tutorial, we demonstrate how to generate a polyphonic
DSP engine with `faust2api` and how to control it with the "standard" JUCE 
keyboard.

The following code is almost the same as the one used in the previous section,
except that [we declared a global effect using the `effect` standard variable](TODO)
([`filteredSawtoothPoly.dsp`](TODO)): 

<!-- faust-run -->
```
import("stdfaust.lib");
freq = nentry("freq",50,200,1000,0.01) : si.smoo;
gain = nentry("gain",0.5,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;
cutoff = nentry("cutoff",10000,50,10000,0.01) : si.smoo;
process = os.sawtooth(freq)*gain*gate : fi.lowpass(3,cutoff) <: _,_ ;
effect = dm.zita_light;
```
<!-- /faust-run -->

Note that the `freq`, `gain`, and `gate` parameters are declared, which means
that this Faust program can be turned into a polyphonic synth (see the
[MIDI polyphonic documentation](TODO)). Hence, in the current configuration
multiple instances (voices) of `process` will be created and connected to a
single instance of `effect`.

A polyphonic DSP engine for JUCE can be generated from this code by running:

```
faust2api -juce -nvoices 12 filteredSawtoothPoly.dsp
``` 

where 12 is the maximum number of polyphonic voices (which can be changed
from the generated C++ code as well by changing the value of the `NVOICES` 
macro at the beginning of `DspFaust.cpp`). The same result can be achieved
using the [Faust web editor](https://faust.grame.fr/editor) and by choosing
`source/juce-poly` in the export function.

Create a new JUCE audio plug-in project with the same configuration than in
the previous section. Import the `DspFaust` files, create an instance of the
`DspFaust` object and call the `dspFaust.start()` and `dspFaust.stop()` methods
as we did before.

Our goal is to create a simple plug-in with the following interface:

<img src="img/juce/polyPlugin.jpg" class="mx-auto d-block" width="60%">

where the keyboard can be used to play several notes at the same time and
the "cutoff" slider can be used to change the cutoff frequency of the lowpass
filter of all active voices. This is an extremely primitive implementation
where only the messages from the UI keyboard are processed: we're just
doing this for the sake of the example. If you've never worked with keyboards 
and MIDI in JUCE, we strongly recommend you to read [this tutorial](https://docs.juce.com/master/tutorial_handling_midi_events.html).

In `PluginEditor.h`, let's first add the following inheritance to the 
`SawtoothSynthAudioProcessorEditor` class:

```
class SawtoothSynthAudioProcessorEditor  : 
  public AudioProcessorEditor, 
  private MidiInputCallback, 
  private MidiKeyboardStateListener
{
```

This is necessary to implement the MIDI callback and the keyboard (UI) listener.
This inheritance requires us to implement the following methods in the
private section of `PluginEditor.h`. We also add an instance of a UI keyboard
and its associated state as well as a slider and its label to control the
cutoff frequency of the lowpass:

```
private:
  void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
  void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
  void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
  
  MidiKeyboardState keyboardState;   
  MidiKeyboardComponent keyboardComponent; 
    
  Slider cutoffSlider;
  Label cutoffLabel;
``` 

In `PluginEditor.cpp`, we can add the keyboard and the slider to the constructor:

```
SawtoothSynthAudioProcessorEditor::SawtoothSynthAudioProcessorEditor (SawtoothSynthAudioProcessor& p)
  : AudioProcessorEditor (&p), processor (p), keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
  setSize (800, 150);
    
  addAndMakeVisible (keyboardComponent);
  keyboardState.addListener (this);
    
  addAndMakeVisible (cutoffSlider);
  cutoffSlider.setRange (50.0, 10000.0);
  cutoffSlider.setValue(5000.0);
  cutoffSlider.onValueChange = [this] { 
    processor.setCutoff(cutoffSlider.getValue()); 
  };
    
  addAndMakeVisible(cutoffLabel);
  cutoffLabel.setText ("Cutoff", dontSendNotification);
  cutoffLabel.attachToComponent (&cutoffSlider, true);
}
```

and we must de-allocate the keyboard state listener in the destructor:

```
SawtoothSynthAudioProcessorEditor::~SawtoothSynthAudioProcessorEditor()
{
  keyboardState.removeListener(this);
}
``` 

The implementation of the `setCutoff` method is detailed later in this tutorial
and is very similar to the one described in the previous section.

We also need to define the size of the various elements in the interface
(as we did before):

```
void SawtoothSynthAudioProcessorEditor::resized()
{
  const int sliderLeft = 80;
  keyboardComponent.setBounds (10,10,getWidth()-30,100);
  cutoffSlider.setBounds (sliderLeft, 120, getWidth() - sliderLeft - 20, 20);
}
```

MIDI messages are retrieved from the keyboard simply by implementing the
following inherited methods:

```
void SawtoothSynthAudioProcessorEditor::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) {}

void SawtoothSynthAudioProcessorEditor::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
  processor.keyOn(midiNoteNumber,int(127*velocity));
}

void SawtoothSynthAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
  processor.keyOff(midiNoteNumber);
}
```

The implementation of the `keyOn` and `keyOff` methods is detailed below.

On the `PluginProcessor` side, the following methods must be declared in 
`PluginProcessor.h`:

```
void keyOn(int pitch, int  velocity);
void keyOff(int pitch);
void setCutoff(float cutoff);
```

They are the ones that were used in the previous steps.

Their corresponding implementation in `PluginProcessor.cpp` is very straight
forward:

```
void SawtoothSynthAudioProcessor::keyOn(int pitch, int velocity)
{
  dspFaust.keyOn(pitch,velocity);
}

void SawtoothSynthAudioProcessor::keyOff(int pitch)
{
  dspFaust.keyOff(pitch);
}

void SawtoothSynthAudioProcessor::setCutoff(float cutoff)
{
  dspFaust.setParamValue("/Sequencer/DSP1/Polyphonic/Voices/synth/cutoff",cutoff);
}
```

`keyOn` and `keyOff` are methods from `DspFaust` that can be used to trigger
and stop a note. `keyOn` will allocate a new voice, convert its `pitch` 
parameter into a frequency that will be sent automatically to the Faust `freq` 
parameter, `velocity` is converted to a level that will be sent to the `gain` 
parameter, and the `gate` parameter is set to 1. Inversely, `keyOff` sets 
`gate` to 0 and waits for t60 to be reached to de-allocate the current voice.

`keyOn` returns a voice ID whose type is `unsigned long`. This ID can then
be used to change the parameter of a specific voice. We're not using this
functionality in the example presented in this tutorial but here is how this
would work:

```
unsigned long voiceID = dspFaust.keyOn(60,110);
dspFaust.setVoiceParamValue("/synth/cutoff",voiceID,378);
```

Note that voices can also be allocated directly without using `keyOn` and 
`keyOff` with the `newVoice` and the `deleteVoice` methods:

```
unsigned long voiceID = dspFaust.newVoice();
dspFaust.setVoiceParamValue("/synth/gate",voiceID,1);
// do something...
dspFaust.deleteVoice(voiceID);
```

Using `setParamValue` as we're doing in the current example, we can set the
value of a parameter for all the voices of the DSP engine. Unlike
`setVoiceParamValue`, the parameter path must be the complete path provided
in the README of the DSP package generated with `faust2api`. So once again,
for `setVoiceParamValue`, the short path is enough but for `setParamValue`,
the complete path is needed.

You might wonder why the path is much more complex with a polyphonic DSP
engine than with a regular one. `Sequencer` is the full object (poly synth + 
effect), `DSP1` is the synth (`DSP2` is the effect), `Polyphonic` is the 
polyphonic layer of the object, and finally `Voices` addresses all the voices 
at once.

That's it folks! Try to compile and run your plug-in, it should just work. Of
course, things could be significantly improved here but at this point, you
should be able to sail on your own.  
