# `faust2wwise` static compilation tool

`faust2wwise` is a command-line tool that generates AudioKinetic Wwise plugins from Faust DSP code. It bridges the gap between the FAUST functional DSP programming language and Wwise’s audio middleware, supporting both **Source** and **Effect** (in-place and out-of-place) plugins. 

## Description

Following the `faust2xxx` model, Faust-compiled code is integrated into Wwise using the `wp` script and template files provided by the Wwise SDK, along with a patch-based Python method for plugin generation.

Supported platforms include Windows, MSYS2, and macOS (via implicit support for the Sound Engine portion only).

## Supported Features

- Source and Effect (in-place & out-of-place) Wwise plugin generation
- Parameter integration
- Conditional RTPC support
- Naming flexibility via Faust declare statements
- Multichannel audio support for source plugins
- Error handling
- Testing script to validate against all Faust example files
- Support for channel mask selection for explicit speaker configuration

## Pipeline overview

The way this work is orchestrated follows a multi-step process, where each phase plays a specific role in preparing, building, and integrating the plugin into the Wwise environment.

**Preliminary Step: Setup and Validation**

- Initialize the configuration.
- Set up and validate the environment,including required checks and dependency validation.

**Step 1: Faust DSP Compilation**
- Compile the Faust DSP (.dsp) file and extract the resulting DSP JSON description
- Process the JSON configuration to initialize the plugin’s setup.

**Step 2: Wwise Plugin Project Generation**
- Use the Wwise wp.py script to generate the base plugin project structure and template files.

**Step 3: Integration**
- Copy the generated Faust DSP file into the Wwise plugin’s SoundEngine directory.
- Replace Wwise template files with those generated during the project setup.
- Apply patch-based integration to enable Faust functionality within the Wwise plugin.
- Update the Lua build script (PremakePlugin.lua) to include required Faust headers.

**Step 4: Project Configuration**
- Run Wwise wp.py premake to configure the project files in preparation for compilation.

**Step 5: Plugin Compilation**
- Build the plugin using the Wwise wp.py build command.

**Outro Step: Cleanup**
  - Remove temporary files and intermediate artifacts to finalize the build.

## Prerequisites
`faust2wwise` comes with the following requirements: 
- **FAUST**
  - The `Faust` compiler must be available in your system **PATH**.
- **Wwise SDK (>=2024.1.0)**
  - `WWISEROOT` must also be exposed system-wide.
- **Python (>=3.9)**
- **Console access with admin rights**

> **HINNT:** `WWISEROOT` must also be exposed system-wide. 

- On **Windows**, open the **AudioKinetic Launcher**, click **Install options (tool icon)** and select **Set environment variables**.

- On **macOS**, set manually the Wwise installation path in your terminal.For instance, assuming a 2024.1.4.8780 Wwise installation, type:

  `export WWISEROOT="/Applications/Audiokinetic/Wwise2024.1.4.8780"`

  To make it permanent, add the line above to your shell config file (e.g., ~/.zshrc or ~/.bash_profile depending on your shell).
Check it's set with: `echo $WWISEROOT`

## Usage

### Basic Syntax

```
faust2wwise path/to/dspfile.dsp [faust options] [wwise options]
```

Upon successful compilation, a Wwise plugin will be automatically generated and registered within the Wwise SDK. It will be placed in the appropriate directory inside the Wwise installation, where plugins are typically stored. The plugin will then be immediately available for use in Wwise.

> Important: Because `faust2wwise` installs plugins into system-level Wwise directories, it must be run from a console with **administrative rights**.

### Example

*A simple example that generates an `out-of-place` Wwise effect plugin named `myfilter` using 64 bit quantization:*

```
faust2wwise myfilter.dsp -double --out-of-place
```

*Type `faust2wwise --help` to view all the available command-line options.*

### Plugin Naming

By default, the plugin name is derived from the file name of the dsp file. If the filename begins with a number, the prefix `Dsp_` is automatically added.

You can override the name via global Faust UI metadata:
```faust
declare name "MyCustomPluginName";
```

### Parameter Integration

**Supported Faust UI Elements**

The following Faust UI elements are supported by faust2wwise:
- hslider
- vslider
- nentry
- checkbox
- button

**RTPC Integration**

To define a Faust parameter as an RTPC (Real-Time Parameter Control) in Wwise, use UI metadata with the [RTPC:rtpcType] syntax.

The available `rtpcType` options:
- Additive
- Multiplicative
- Exclusive
- Boolean

These types specify how the parameter should react to real-time game input — via an RTPC, a State, or both — and how those values interact (e.g., additive, multiplicative). 

> Note: RTPC types are case-insensitive. For example, `multiplicative` is also considered as a valid input and will be interpreted correctly.

**Example:**
```
hslider("volume[RTPC:Additive]", 0, 0, 1, 0.01);
```
This demonstrates how to define the `volume` parameter as an **RTPC** of type **Additive**, meaning its final value in Wwise will be the sum of the base value plus any real-time contributions from RTPCs or States, allowing multiple sources to influence the parameter simultaneously *(Credits to Guido Fazzito)*.

**Hidden Parameters**

Support for hidden Faust parameters is also available via [widget modulation](https://faustdoc.grame.fr/manual/syntax/#widget-modulation), allowing to override internal parameters and redefining them by attaching RTPC-related metadata directly to its label.

## Explicit Speaker Configuration (Source plugins only)

You can specify a speaker layout explicitly using the `--spkcfg` option. This allows to define the channel configuration by referencing one of the standard Wwise speaker setup macros, as defined in the `AkSpeakerConfig.h` of the Wwise SDK. This is useful when your plugin or project targets a specific speaker configuration(i.e. 5.1, 7.1.4, Auro, or Dolby Atmos). Available options are listed in [spkcfg.py](spkcfg.py) file, and are based on the official [Wwise channel mask definitions](https://www.audiokinetic.com/en/public-library/2024.1.7_8863/?source=SDK&id=_ak_speaker_config_8h_source.html). if `--spkcfg` option is not provided, the speaker configuration is automatically inferred based on the number of audio outputs declared in the Faust DSP file.

> Important: The number of audio outputs defined in your Faust DSP file must match the number of channels implied by the selected configuration. 

### Example:

```
faust2wwise myGenerator.dsp --spkcfg AK_SPEAKER_SETUP_5POINT1
```
This example shows of how explicit speaker configuration can be provided for a Faust DSP file that generates audio output for 6 channels.

## Testing

To test `faust2wwise`, a Python test script is provided that runs the conversion script on all `.dsp` files in a given directory. To use it, run `faust2wwise` in test mode using the `test` command-line parameter:

```
faust2wwise test --testdir /path/to/dir_containing_dsp_files
```

*Type `faust2wwise test --help` to view all the available command-line options.*
>Note: the`--clean` option is currently not supported.

Test results are stored in the current working directory under the `myF2Wtests/` folder:
 - a summary is saved in the `testResults.json` file
 - each `dsp` file gets a separate `build.log` in its distinct output directory.

> Important: Because `faust2wwise test` installs plugins into system-level Wwise directories, it must be run from a console with **administrative rights**.

**Compiling Faust examples from the official Faust repo**

Use `faust2wwise test --testdir path/to/faust/examples` to compile all the tests (or a random portion of them using the `--limit <N>` option) of the official Faust dsp `examples`. This allows to either test `faust2wwise` at scale or compile a large suite of Faust examples into Wwise plugins making them accessible for use directly within the Wwise SDK. 
 
> Note: Some .dsp files are automatically excluded since they require special handling (see EXCLUDE_FILES in the [test script](test.py)).

## Error Codes

The following exit codes are used to indicate specific failure points during the conversion pipeline:

Code | Name | Description
:--- | :--- | ---:
2 | ERR_INVALID_INPUT | Invalid input arguments or missing required files.
3 | ERR_ENVIRONMENT | Environment setup failed or required tools are missing.
4 | ERR_FAUST_COMPILE | Faust DSP compilation failed.
5 | ERR_JSON_PARSE | Failed to parse the generated DSP JSON description.
6 | ERR_GENERATION | Wwise plugin project generation failed.
7 | ERR_INTEGRATION | Error during file integration or patching phase.
8 | ERR_CONFIGURATION | Project configuration via premake failed.
9 | ERR_BUILD | Plugin build process failed.

## Limitations

The following features are currently limited or under development:
- support multiple dsps
  - multiple instances of the same DSP class
  - and/or instances from different DSP classes
- Bargraphs parameter support. Potential approaches are:
  - [Wwise Plug-in Dialog](https://www.audiokinetic.com/en/public-library/2024.1.6_8842/?source=SDK&id=wwiseplugin_dialog_guide.html), though note this is currently platform-dependent and only supported on Windows.
  - `hbargraphs` which behave like sliders visually, but they do not output values, limiting their usefulness for feedback or monitoring. 
- Older Wwise versions not supported (<=2023.1.15)
- macOS support for Wwise Authoring plug-ins is indirect because the Authoring application runs as a Windows binary through an adaptation layer, and therefore requires plug-ins to be built as Windows DLLs. To achieve this on macOs, you must build the Authoring plug-in on a Windows machine or VM with Visual Studio, while the Sound Engine plug-in can be built natively on macOS. (For more details, see the official documentation on [macOs Plug-in Considerations](https://www.audiokinetic.com/en/public-library/2024.1.7_8863/?source=SDK&id=authoringplugin_macos.html))
- `faust2wwise test` currently does not support the `--clean` option.

If you'd like to help improve any of these, contributions are welcome!
Please follow the [official contribution guideline](https://faustdoc.grame.fr/manual/community/).

## Troubleshooting

### `error: {plugin name} is not a valid name (a project already exists with that name)`

> This is a common error and it typically means that the DSP file has already been compiled, and project files exist in the output directory. To fix this, delete the previously generated directory before recompiling.

### Build error:`fatal error: 'faust/dsp/dsp.h' file not found`

> This error is observed on macOs platform and usually occurs when the Faust include path is misconfigured—most often, the leading `/` is missing  (e.g., `usr/local/include` instead of `/usr/local/include`), causing the compiler to fail. To fix this, open the project in Xcode, go to **Build Settings -> Search Paths -> Header Search Paths**, and manually correct the path by ensuring it begins with a `/`.

### Build error: `Cannot use 'throw' with exceptions disabled`

> This error occurs on macOS when building with Xcode and using `throw` in the code, while C++ exceptions are disabled. To fix this, open the project in Xcode, navigate to **Build Settings -> Apple Clang -> Language - C++ -> Enable C++ Exceptions**, and set to **Yes**.

### Speaker configuration provided does not match with number of outputs supported by the Faust program.

> This error occurs when the number of outputs in your Faust program doesn't match the number of speakers implied by the selected `--spkcfg` option. Ensure that your Faust file uses the correct number of outputs to match the speaker layout, or omit the `--spkcfg` option to use the default speaker configuration to let the channel mask be selected automatically from default mappings based on the number of DSP outputs.

Found a bug, unexpected behavior, or something unclear? [Open an issue](https://github.com/grame-cncm/faust/issues).

---
