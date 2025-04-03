# faust2juce

The **faust2juce** tool transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code, which contains interface parameters with the following `freq`, `gain` and `gate` names. The metadata **declare nvoices "8";** kind of line with a desired value of voices can be added in the source code. See [Creating polyphonic instruments](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support). 

Polyphonic synthesiser can be created using JUCE Synthesiser model or Faust own polyphonic architecture file (using the `mydsp_poly` class). The `-jsynth` parameter has to be used to choose the JUCE model.

**faust2juce** uses several UI interfaces, subclasses of the base UI class (defined in the architecture/faust/gui/UI.h header) to link to various JUCE components:

 - `JuceGUI.h`: contains the main JuceGUI class (and additional helpers classes) to display Faust UI components (buttons, sliders, bargraphs...) using JUCE widgets. The following `[style:knob]`, `[style:led]`, `[style:numerical]`, `[style:radio]`, `[style:menu]`, `[scale:log]`, `[scale:exp]`, `[tooltip:xx]`, `[hidden:0|1]` metadata are supported.
 - `JuceOSCUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE OSC messaging system, allowing to control them in both directions
 - `JuceParameterUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) with the JUCE AudioParameterFloat/AudioParameterBool classes
 - `JuceStateUI.h`: allows to save/restore Faust UI components (buttons, sliders, bargraphs...) values using the JUCE state management system (MemoryInputStream/MemoryOutputStream classes)

Some additional files are needed for soundfile and MIDI support:

- `JuceReader.h`: contains code to load audio files using JUCE code, that will be used when the `soundfile` primitive is used in the Faust code
- `juce-midi.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE MIDI messaging system (for inputs and outputs) 

Two different achitecture files will be used to glue the previously described files with the Faust C++ generated class: 
- `juce-plugin.cpp`: is used to create a JUCE plugin
- `juce-standalone.cpp`: is used to create a JUCE stanalone application

## How to use

**faust2juce** is used with the following command: 

`faust2juce [-osc] [-midi] [-soundfile] [-nvoices <num>] [-effect auto|<effect.dsp>] [-standalone] [-jucemodulesdir <dir>] [-vst2sdkdir <dir>] [-disable-splash-screen] [-jsynth] [-llvm] [-magic] [additional Faust options (-vec -vs 8...)] file.dsp` 

By default it will create a plugin project, with a folder named with the dsp file name, containing a .jucer project with a FaustPluginProcessor.cpp file to be used by JUCE.

When using `-standalone` mode, it will create a standalone project, with a folder named with the dsp file name, containing a .jucer project with a FaustAudioApplication.cpp file to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can be generated. Using the `-jucemodulesdir` allows to generate projects that can be used without moving them in JUCE installation.

## Options

Here are the available options:

- `-osc` : activates OSC control
- `-midi` : activates MIDI control
- `-soundfile` : when compiling DSP using 'soundfile' primitive, to add needed resources
- `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
- `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
- `-effect auto` : to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC 
- `-standalone` : to produce a standalone project, otherwise a plugin project is generated
- `-jucemodulesdir <folder>` : to set JUCE modules directory to `<folder>`, such as ~/JUCE/modules
- `-vst2sdkdir <folder>` : to set VST 2 Legacy Directory to `<folder>`. This is the directory that contains "plugininterfaces/vst2.x/aeffect.h".
- `-disable-splash-screen` : to disable the JUCE splash screen (license is required).
- `-jsynth` : to use JUCE polyphonic Synthesizer instead of Faust polyphonic code
- `-llvm` : to use the LLVM compilation chain (OSX and Linux for now)
---
- `-magic` : to generate a project using the [PluginGuiMagic GUI builder](https://foleysfinest.com/developer/pluginguimagic/)
Tested with PGM version 1.13. Support for Faust components is incomplete. Supporting some features (e.g. visualizers) in PGM requires editing the generated C++ code.

This creates a preprocessor definition "PLUGIN_MAGIC" in the jucer file e.g. using VisualStudio 2019.

![image](https://user-images.githubusercontent.com/3178344/125528513-d8f127a0-a896-4f50-8210-ba7b8dcf0386.png)

There are a couple of other options as well:

MAGIC_LOAD_BINARY 
- adds generated code if defined. By default not defined, lets you "bake in" your XML file by adding it to your Jucer project and then defining this variable.  You'll also need to configure the foleys_gui_magic module in Jucer:

 ![image](https://user-images.githubusercontent.com/3178344/126184481-b83ba2ff-46c4-4aa5-b010-2d2e87eb4e14.png)

 You also have to change the names of the variables magic_xml and magic_xmlSize in the code to match your file name. If you don't you'll get a compilation error, so you'll know where to look.

MAGIC_LEVEL_SOURCE
- adds generated code if defined. By default not defined, just to show you where in the source code you would add hooks for a visualizer. These are PGM specific features not represented in Faust. Knowledge of how to use the PGM components is assumed.

To use either of these options, either enter the option into the JUCER exporter settings page as shown, or add a `#define` line near the top of your FaustPluginProcessor.cpp.

---
- `-help or -h` : shows the different options 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2juce**, like `-vec -lv 1` to compile in vector mode.etc.

## Latency setting

Some plugins add latency in the signal path. A special global metadata can be used in the DSP code to define it, so that the C++ architecture file can extract it and use the JUCE `AudioProcessor::setLatencySamples()` method to have the plugin inform the host about its added latency. The following syntax can be used:

- `declare latency_frames "7000";` (or alternatively `declare latency_samples "7000";`) to express the latency in samples/frames

- `declare latency_sec "0.5";` to express the latency in seconds, to be converted internally in samples/frames using the host sample rate 

## Faust DSP Testbench

As a fork of the [DSP-Testbench](https://github.com/AndrewJJ/DSP-Testbench) project, [Faust DSP Testbench](https://github.com/grame-cncm/Faust-DSP-Testbench) is designed to help developers using the [JUCE framework](https://juce.com) to analyse their Faust DSP by providing a test harness for code inheriting from `juce::dsp::ProcessorBase`. The harness provides signal sources, routing, analysis and monitoring functions.
