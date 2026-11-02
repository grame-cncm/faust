# faust2juce

The **faust2juce** tool transforms a Faust DSP program into a fully working JUCE standalone application or plugin, which can possibly be controlled with MIDI or OSC messages. Polyphonic instruments are automatically created from polyphonic aware Faust DSP code, which contains interface parameters with the following `freq`, `gain` and `gate` names. The metadata **declare nvoices "8";** kind of line with a desired value of voices can be added in the source code. See [Creating polyphonic instruments](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support). 

Polyphonic synthesiser can be created using JUCE Synthesiser model or Faust own polyphonic architecture file (using the `mydsp_poly` class). The `-jsynth` parameter has to be used to choose the JUCE model.

**faust2juce** uses several UI interfaces, subclasses of the base UI class (defined in the architecture/faust/gui/UI.h header) to link to various JUCE components:

 - `JuceGUI.h`: contains the main JuceGUI class (and additional helpers classes) to display Faust UI components (buttons, sliders, bargraphs...) using JUCE widgets. The following `[style:knob]`, `[style:led]`, `[style:numerical]`, `[style:radio]`, `[style:menu]`, `[scale:log]`, `[scale:exp]`, `[tooltip:xx]`, `[hidden:0|1]` metadata are supported.
 - `JuceOSCUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE OSC messaging system, allowing to control them in both directions
 - `JuceParameterUI.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) with the JUCE AudioParameterFloat/AudioParameterBool classes, named after the Faust shortnames and shaped by the widget metadata (see [Host parameters](#host-parameters))
 - `JuceStateUI.h`: allows to save/restore Faust UI components (buttons, sliders, bargraphs...) values using the JUCE state management system (MemoryInputStream/MemoryOutputStream classes)

Some additional files are needed for soundfile and MIDI support:

- `JuceReader.h`: contains code to load audio files using JUCE code, that will be used when the `soundfile` primitive is used in the Faust code
- `juce-midi.h`: allows to link Faust UI components (buttons, sliders, bargraphs...) to the JUCE MIDI messaging system (for inputs and outputs) 

Two different achitecture files will be used to glue the previously described files with the Faust C++ generated class: 
- `juce-plugin.cpp`: is used to create a JUCE plugin
- `juce-standalone.cpp`: is used to create a JUCE stanalone application

## How to use

**faust2juce** is used with the following command: 

`faust2juce [-osc] [-midi] [-soundfile] [-nvoices <num>] [-effect auto|<effect.dsp>] [-presets <file.json>] [-standalone] [-jucemodulesdir <dir>] [-vst2sdkdir <dir>] [-disable-splash-screen] [-jsynth] [-llvm] [-magic] [additional Faust options (-vec -vs 8...)] file.dsp` 

By default it will create a plugin project, with a folder named with the dsp file name, containing a .jucer project with a FaustPluginProcessor.cpp file to be used by JUCE, an `effect.h` file with `-effect`, a `FaustPresets.h` file with `-presets`, and a `CMakeLists.txt` with its `JuceLibraryCode/JuceHeader.h` (see [Building with CMake](#building-with-cmake)).

When using `-standalone` mode, it will create a standalone project, with a folder named with the dsp file name, containing a .jucer project with a FaustAudioApplication.cpp file to be used by JUCE.

The resulting folder has to be moved on the "examples" folder of your JUCE installation, the .jucer file has to be opened, and projects for specific native platforms can be generated. Using the `-jucemodulesdir` allows to generate projects that can be used without moving them in JUCE installation.

The folder is rebuilt from scratch at each run. **faust2juce** only replaces a previous export (a folder containing its `.jucer` project, `FaustPluginProcessor.cpp` or `FaustAudioApplication.cpp`): if a file or another folder has the name of the DSP, for instance a binary compiled from it, it stops with an error and leaves it untouched.

### Building with CMake

Plugin projects (without `-llvm`) also contain a `CMakeLists.txt`, which builds the plugins without Projucer, with the options given to **faust2juce**:

```
cd foo
cmake -B build -DJUCE_DIR=/path/to/JUCE
cmake --build build --config Release
```

The plugins are then in `build/foo_artefacts/Release`. Without `JUCE_DIR`, CMake downloads JUCE (version 8.0.10, which `-DJUCE_GIT_TAG=<tag>` changes). JUCE only builds the AUv3 format with the Xcode generator (`cmake -G Xcode`). `-DFAUST_COPY_PLUGINS=ON` copies the plugins to the user plug-in folders after each build. `-DFAUST_CUSTOM_EDITOR=<file.h>` and `-DFAUST_EXTRA_SOURCES="<a.cpp;b.cpp>"` replace the generic interface with a custom editor (see [Custom editor](#custom-editor)). With `-magic`, `-DFOLEYS_GUI_MAGIC_DIR=<dir>` is required and `-DFAUST_MAGIC_XML=<file.xml>` builds a saved GUI into the plugin (see [Options](#options)).

The CMake build uses the `JuceLibraryCode/JuceHeader.h` file written by **faust2juce**, which only includes the JUCE modules used by the architecture. Projucer replaces it when the .jucer project is saved, so use one of the two builds per exported folder.

## JUCE compatibility

Generated projects use macOS 12.0 as the deployment target for both Debug and Release builds. This setting applies to plugin and standalone projects, including the LLVM variants, and can be changed in Projucer for your target system and Xcode SDK.

The GUI uses shaped text measurement on JUCE 8 and later, including JUCE 9, and retains the older font API on JUCE 7 and earlier. MIDI devices use the identifier-based `getDefaultDevice()` and `openDevice()` APIs. After updating Faust, regenerate the project with `faust2juce` to refresh its embedded architecture headers, then save the `.jucer` project with your JUCE version's Projucer before building in Xcode.

## Options

Here are the available options:

- `-osc` : activates OSC control
- `-midi` : activates MIDI control
- `-soundfile` : when compiling DSP using 'soundfile' primitive, to add needed resources
- `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC
- `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
- `-effect auto` : to produce a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC 
- `-presets <file.json>` : to expose the presets of a JSON file as host programs, plugins only (see [Presets as host programs](#presets-as-host-programs))
- `-standalone` : to produce a standalone project, otherwise a plugin project is generated
- `-jucemodulesdir <folder>` : to set JUCE modules directory to `<folder>`, such as ~/JUCE/modules
- `-vst2sdkdir <folder>` : to set VST 2 Legacy Directory to `<folder>`. This is the directory that contains "plugininterfaces/vst2.x/aeffect.h".
- `-disable-splash-screen` : to disable the JUCE splash screen (license is required).
- `-jsynth` : to use JUCE polyphonic Synthesizer instead of Faust polyphonic code
- `-llvm` : to use the LLVM compilation chain (OSX and Linux for now)
---
- `-magic` : to generate a project using [PluginGuiMagic](https://github.com/ffAudio/foleys_gui_magic) (the `foleys_gui_magic` JUCE module), a GUI builder whose editor runs in the plugin itself: the interface is designed in the running plugin, saved as an XML file, then built into the plugin. The plugin processor is a `foleys::MagicProcessor` and the project defines `PLUGIN_MAGIC`. Without a saved GUI, the plugin shows a default interface generated from the parameters, with one box per Faust group (see [Host parameters](#host-parameters)). Tested with foleys_gui_magic 1.5.0 and JUCE 8.0.10; the 1.3.x versions do not compile with JUCE 8. The [former PluginGuiMagic repository](https://github.com/ffAudio/PluginGuiMagic) is archived: use the module repository.

With the CMake build (see [Building with CMake](#building-with-cmake)), `-DFOLEYS_GUI_MAGIC_DIR=<dir>` gives a checkout of the foleys_gui_magic repository, or its `modules/foleys_gui_magic` folder, and `-DFAUST_MAGIC_XML=<file.xml>` builds a GUI saved by the editor into the plugin (this defines `MAGIC_LOAD_BINARY`, described below):

```
cmake -B build -DJUCE_DIR=/path/to/JUCE -DFOLEYS_GUI_MAGIC_DIR=/path/to/foleys_gui_magic -DFAUST_MAGIC_XML=my-gui.xml
cmake --build build --config Release
```

With the .jucer project, the foleys_gui_magic module has to be added and configured in Projucer:

![image](https://user-images.githubusercontent.com/3178344/126184481-b83ba2ff-46c4-4aa5-b010-2d2e87eb4e14.png)

Two other definitions add code to the plugin:

MAGIC_LOAD_BINARY
- loads the GUI from an XML file built into the plugin, instead of the default interface. The code reads `BinaryData::magic_xml`: with the .jucer project, add the XML file to the project, name it `magic.xml` or change `magic_xml` and `magic_xmlSize` in FaustPluginProcessor.cpp to match its name, and define the variable. The CMake build does all this with `FAUST_MAGIC_XML`.

MAGIC_LEVEL_SOURCE
- adds an output level meter source, named `output`, that a meter of the GUI can display. It shows where in the source code hooks for other visualizers would be added. These are PluginGuiMagic features not represented in Faust, and knowledge of the PluginGuiMagic components is assumed.

With the .jucer project, enter these definitions in the exporter settings page, or add a `#define` line near the top of FaustPluginProcessor.cpp.

Current limitations:
- menus and radio buttons (`[style:menu{...}]`, `[style:radio{...}]`) are discrete parameters with value names, not `juce::AudioParameterChoice`: the default interface shows them as sliders, but a ComboBox placed in the editor and bound to one of them lists its names
- with `-presets`, the programs are listed and selected by the host, but the current program is not saved with the plugin state (the parameter values are)
- `FAUST_CUSTOM_EDITOR` cannot be combined with `-magic`
- the editor is available in every build of the plugin, which the `FOLEYS_SHOW_GUI_EDITOR_PALLETTE` module setting (1 by default) controls: set it to 0 for a plugin that is distributed

---
- `-help or -h` : shows the different options 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2juce**, like `-vec -lv 1` to compile in vector mode.etc.

The generated plugin project also understands the following preprocessor definitions, to add in Projucer (Exporters > Extra Preprocessor Definitions) or with CMake:

- `FAUST_CUSTOM_EDITOR="MyEditor.h"` : replaces the generic interface with a custom editor (see [Custom editor](#custom-editor)); with CMake, use `-DFAUST_CUSTOM_EDITOR=<path/to/MyEditor.h>` and `-DFAUST_EXTRA_SOURCES=...` instead
- `FAUST_JUCE_FULLPATH_IDS` : names the host parameters after their full path, as before Faust 2.92.0, so that automation saved in older host sessions still applies (see [Host parameters](#host-parameters)); with CMake, `-DCMAKE_CXX_FLAGS=-DFAUST_JUCE_FULLPATH_IDS`

## Latency setting

Some plugins add latency in the signal path. A special global metadata can be used in the DSP code to define it, so that the C++ architecture file can extract it and use the JUCE `AudioProcessor::setLatencySamples()` method to have the plugin inform the host about its added latency. The following syntax can be used:

- `declare latency_frames "7000";` (or alternatively `declare latency_samples "7000";`) to express the latency in samples/frames

- `declare latency_sec "0.5";` to express the latency in seconds, to be converted internally in samples/frames using the host sample rate 

## Tail length setting

Some plugins keep producing sound after their input stops, typically with delays or reverbs. A special global metadata can be used in the DSP code to define how long, so that the C++ architecture file can extract it and return it from the JUCE `AudioProcessor::getTailLengthSeconds()` method. The host then knows how long to keep processing the plugin after the last note or input, for instance when bouncing a track. The following syntax can be used:

- `declare tail_sec "12";` to express the tail length in seconds (0 when not declared)

## Presets as host programs

The `-presets <file.json>` option gives a plugin factory presets, which hosts list in their own preset or program menu, without opening the plugin interface. The JSON file maps preset names to control values:

```
{
    "Soft": { "cutoff": 800, "resonance": 0.2 },
    "Bright": { "cutoff": 6000, "drive": 2.5 }
}
```

A control is named by the ID of its host parameter (see [Host parameters](#host-parameters)) or by its label. The plugin then exposes the programs "Default", with the values declared in the DSP, followed by the presets in the order of the file. Selecting a program recalls it completely: the controls it does not name go back to their default value. Selecting the current program again does nothing, because some hosts do so right after restoring a session, which would overwrite the restored values. The current program is saved with the plugin state. A preset naming an unknown control is reported on the standard error when the plugin starts. A label shared by several controls (such as `depth` in `Route 0/depth`, `Route 1/depth`...) sets all of them: name one of them by its shortname (`Route_0_depth`).

The control names can be found in the JSON description of the DSP (`faust -json foo.dsp`, the `shortname` field of each control). Rather than writing a preset by hand, it can also be taken from the plugin: right-click the generic interface and choose "Copy settings as a faust2juce -presets entry", which copies the current settings to the clipboard as `{ "Preset": { ... } }`. Only the controls that differ from their default value are written, as presets list them; rename the entry and paste it into the file. A custom editor can offer the same thing by declaring and calling the function the architecture defines:

```c++
juce::String faustPresetJSON(juce::AudioProcessor& processor, const juce::String& name);
```

The file is embedded in the project (`FaustPresets.h`) and the `FAUST_PRESETS` macro is defined. This option is only available for plugins, not with `-standalone`.

## Host parameters

Each Faust control becomes a host parameter, whose ID is the Faust shortname: the label alone (`cutoff`), or preceded by the enclosing groups when the label is repeated (`Route_0_depth`). These IDs do not depend on the groups added by the architecture for polyphony or for the `-effect` sequencing, so they stay the same when these options change. Previous versions used the full path; define `FAUST_JUCE_FULLPATH_IDS` when compiling the plugin to keep these IDs, so that automation recorded in existing host sessions still applies.

The Faust groups (`vgroup`, `hgroup`, `tgroup`) become JUCE parameter groups (`juce::AudioProcessorParameterGroup`), named after the group labels, with the groups added by the architecture (`Polyphonic`, `Voices`) around them. Hosts that show parameter groups, VST3 units for instance, and GUI builders such as PluginGuiMagic, whose default interface is laid out from these groups, present the parameters the way the DSP organises them. The parameter IDs and their order do not depend on the groups.

With `-effect`, the shortnames are computed separately for the voices and for the effect. A control declared by both, with the same shortname, kind and range (for instance a `bpm` slider used by the voices and by a tempo-synced delay of the effect), becomes a single host parameter that sets both. A control with the same shortname but another kind or range keeps its own parameter, whose ID is numbered (`bpm_2`). The saved plugin state is not affected. With `FAUST_JUCE_FULLPATH_IDS`, controls are not merged.

Widget metadata is passed on to the host:

- `[scale:log]` and `[scale:exp]` shape the parameter range with the same conversions as the other Faust interfaces, so that host knobs and automation curves follow the control (the middle of a logarithmic 30..18000 Hz control is about 735 Hz)
- `[unit:Hz]` becomes the parameter label, displayed by hosts next to the value
- `[style:menu{'Sine':0;'Saw':1}]` and `[style:radio{...}]` make the parameter discrete, show the name of the closest declared value and accept a name typed in the host
- the widget step sets the snapping of values and the number of decimals displayed

`[tooltip:...]` has no equivalent in JUCE parameters and is not passed on.

## Custom editor

A project can replace the generic interface with its own JUCE editor, while still building on the generated processor. Define `FAUST_CUSTOM_EDITOR` as the name of a header, for instance `-DFAUST_CUSTOM_EDITOR='"MyEditor.h"'` (in Projucer, add `FAUST_CUSTOM_EDITOR="MyEditor.h"` to the preprocessor definitions). The architecture includes this header, leaves out the generic interface (`JuceGUI.h`), and expects it to define:

- `FaustEditorBridge`: a class owned by the processor and shared with the editor. The processor calls it on the audio thread:
  - `prepare(double sampleRate, int blockSize, int numVoices)` from `prepareToPlay`, `numVoices` being 0 for a monophonic DSP
  - `processMidi(juce::MidiBuffer& midi, int numSamples)` at the start of each block, before the MIDI events are decoded, so that it can read them or add its own, for instance from a `juce::MidiKeyboardState` displayed by the editor
  - `processAudio(const juce::AudioBuffer<T>& buffer, int activeVoices)` after each block, with `T` being `float`, or `double` when the DSP is compiled in double precision, for meters, scopes or load measurement. `activeVoices` counts the voices still sounding, and is -1 when unknown (with `-jsynth`)
- `juce::AudioProcessorEditor* createFaustEditor(juce::AudioProcessor&, FaustEditorBridge&)`, called by `createEditor()`

Both only depend on JUCE, so the editor can be compiled in its own translation unit and reach the DSP controls through the host parameters (`AudioProcessor::getParameters()`, see above). A minimal header could be:

```c++
#pragma once
#include "MyEditor.h"   // class MyEditor : public juce::AudioProcessorEditor

struct FaustEditorBridge
{
    juce::MidiKeyboardState keyboard;   // played by MyEditor
    void prepare(double, int, int) {}
    void processMidi(juce::MidiBuffer& midi, int numSamples) { keyboard.processNextMidiBuffer(midi, 0, numSamples, true); }
    template <typename T> void processAudio(const juce::AudioBuffer<T>&, int) {}
};

inline juce::AudioProcessorEditor* createFaustEditor(juce::AudioProcessor& p, FaustEditorBridge& bridge)
{
    return new MyEditor(p, bridge);
}
```

`FAUST_CUSTOM_EDITOR` cannot be combined with `-magic`.

## Faust DSP Testbench

As a fork of the [DSP-Testbench](https://github.com/AndrewJJ/DSP-Testbench) project, [Faust DSP Testbench](https://github.com/grame-cncm/Faust-DSP-Testbench) is designed to help developers using the [JUCE framework](https://juce.com) to analyse their Faust DSP by providing a test harness for code inheriting from `juce::dsp::ProcessorBase`. The harness provides signal sources, routing, analysis and monitoring functions.
