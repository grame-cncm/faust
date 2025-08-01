# `faust2wwise` static compilation tool

`faust2wwise` is a command-line tool that generates AudioKinetic Wwise plugins from Faust DSP code. It bridges the gap between the FAUST functional DSP programming language and Wwise’s audio middleware, supporting both **Source** and **Effect** (in-place and out-of-place) plugins. 

## Description

Following the `faust2xxx` model, Faust-compiled code is integrated into Wwise using the `wp` script and template files provided by the Wwise SDK, along with a patch-based Python method for plugin generation.

Supported platforms include Windows, MSYS2, and macOS (experimental support).

## Supported Features

- Source and Effect (in-place & out-of-place) Wwise plugin generation
- Parameter integration
- Conditional RTPC support
- Naming flexibility via Faust declare statements
- Multichannel audio support for source plugins
- Error handling
- Testing script to validate against all Faust example files

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
- **Wwise SDK (>??)**
  - `WWISEROOT` must also be exposed system-wide. To do that, open the **AudioKinetic Launcher**, click **Install options (tool icon)** and select **Set environment variables**.
- **Python (>??)**
- **Console access with admin rights**

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

To define a Faust parameter as an RTPC (Real-Time Parameter Control) in Wwise, use UI metadata with the [RTPC,rtpcType] syntax.

The available `rtpcType` options:
- Additive
- Multiplicative
- Exclusive
- Boolean

These types specify how the parameter should react to real-time game input — via an RTPC, a State, or both — and how those values interact (e.g., additive, multiplicative). 

**Example:**
```
hslider("volume[RTPC,Additive]", 0, 0, 1, 0.01);
```
This demonstrates how to define the `volume` parameter as an **RTPC** of type **Additive**, meaning its final value in Wwise will be the sum of the base value plus any real-time contributions from RTPCs or States, allowing multiple sources to influence the parameter simultaneously *(Credits to Guido Fazzito)*.

**Hidden Parameters**

Support for hidden Faust parameters is also available via [widget modulation](https://faustdoc.grame.fr/manual/syntax/#widget-modulation), allowing to override internal parameters and redefining them by attaching RTPC-related metadata directly to its label.

## Testing
 <add a section about faust2wwise script after finalizing it.
 
- @TODO: add a `--faust-root` argument. (default something like `../../../faust`) 
 
- @TODO: add a `--clean` argument to delete all installed plugins from the Wwise directory where the plugins are typically stored. 

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
- Older Wwise versions not supported (<??)
- Speaker configuration code has known technical limitations
- macOS support under active testing

If you'd like to help improve any of these, contributions are welcome!
Please follow the [official contribution guideline](https://faustdoc.grame.fr/manual/community/).

## Troubleshooting

A common error occurred is the following: 
`error: {plugin name} is not a valid name (a project already exists with that name)`

> This typically means that the DSP file has already been compiled, and project files exist in the output directory. To fix this, delete the previously generated directory before recompiling.

Found a bug, unexpected behavior, or something unclear? [Open an issue](https://github.com/grame-cncm/faust/issues).

---
