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
to the next section.

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
from 2016 demonstrate how this can be done.
 
Fortunately, things are simpler than ever nowadays and `faust2api` greatly
simplifies this process.

## Simple Synth Plug-In

In this section, we demonstrate how to use a Faust synth to build a plug-in
in JUCE with a custom UI from scratch.

> This tutorial only demonstrates how to make a JUCE plug-in. Making a JUCE
standalone application following the same method is perfectly possible with 
some adjustments.

### Generating the DSP Engine

First, let's implement a basic subtractive synthesizer in Faust based on a
filtered sawtooth wave ([`filteredSawtooth.dsp`](TODO)):

<!-- faust-run -->
```
import("stdfaust.lib");
freq = nentry("freq",50,200,1000,0.01) : si.smoo;
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
plug-in to be clean!). Even `gate` is smoothed which will apply a gently
exponential envelope when the trigger signal is sent, etc.

Since Faust will not build its own UI here, the type of UI element used in this
code doesn't really matter. They just serve as a point of entry to control the
parameters of the audio engine we're about to generate. So `nentry`, could be
replaced by `hslider` or `vslider`, it would not make any difference.

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

In this section, we'll assume that your a bit familiar with 
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

The `resize` must be implemented so that the various UI elements that we
created actually have a size:

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

The goal of this section was just to show you how to integrate a Faust DSP
engine into a JUCE plug-in project and how to control it with a simple UI. 
Once again, JUCE is a powerful tool to implement sophisticated UI in a very
simple way. You'll find all the documentation you need on 
[their website](https://juce.com/) to start making beautiful plug-ins!

## Creating and Using a Polyphonic Faust DSP Object
