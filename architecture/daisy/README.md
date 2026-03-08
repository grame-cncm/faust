# faust2daisy

The **faust2daisy** tool compiles a Faust DSP program in a folder containing the C++ source code and a Makefile to compile it.  
This new version is a partial refactor of the previous tool, aiming to : 
- improve memory footprint
- provide compile time memory footprint
- target Daisy boards (while still providing a way to target platforms)

`faust2daisy [-faust2daisy_options...] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-seed`: target Daisy seed chip
- `-patchsm`: target Daisy patchsm chip
- `-pod`: use Pod configuration file 
- `-patch`: use Patch configuration file (not full feature yet) 
- `-sram`: program will stand on SRAM (512kB)
- `-qspi`: program will stand on QSPIFLASH (8MB)
- `-sdram`: enable SDRAM for large buffers (slow, but big)
- `-mem-thresh <num>`: specify size threshold (in bytes) above which data is stored on SDRAM (default 1024 bytes)
- `-config-file <filepath>`: specify a JSON configuration file made in the same way as "faust/architecture/daisy/pod.json"
- `-midi`: enables MIDI (defaults to USB internal MIDI of chip)
- `-midi-uart`: enables MIDI UART 
- `-rx-pin <Pin>`: RX Pin for MIDI UART
- `-tx-pin <Pin>`: TX Pin for MIDI UART
- `-nvoices <num>`: number of voices, enables polyphony 
- `-poly-mode`: mode for voice management in polyphonic context. Options <stealing> or <blocking> (defaults to stealing)
- `sr <num>`: sample rate of DSP : only 8000, 16000, 32000, 48000, 96000 are allowed
- `bs <num>`: buffer size
- Any other option will be passed to Faust compiler

## Setup 

To use `faust2daisy`, you need the daisy toolchain installed. 
- [Linux](https://daisy.audio/tutorials/toolchain-linux/)
- [Mac](https://daisy.audio/tutorials/toolchain-mac/)

You will also need [libDaisy](https://github.com/electro-smith/libDaisy) to be built. Latest tool was designed to target version 8.1.0. 
You should specify environment variables. For example, on macOS/Linux:
```bash
export LIBDAISY_DIR=~/GitHub/DaisyExamples/libdaisy
export DAISYSP_DIR=~/GitHub/DaisyExamples/DaisySP
```

If on macOS, consider putting the above text in `~/.zshrc` so that it's always set in Terminal.

The default optimization is for file size: `OPT=-Os`. You can optimize for speed by setting `OPT=-O2` or the even more aggressive setting `OPT=-O3`. This can be set in the Makefile in "faust/architecture/daisy".

## Targetting boards 

This tool is intended to target Daisy boards : 
- Seed 
- PatchSM - currently unimplemented 

The idea is to provide access to all of the Pins that can be useful in an audio context : 
- Audio inputs & outputs (24 bits)
- Control ADCs (16 bits)
- Control DACs (12 bits)
- GPIO (in either on/off mode, or as software PWM for output)

Example : 
``` faust
import("stdfaust.lib");

freq = hslider("freq[adc::A0]", 50, 50, 1000, 0.1) : si.smoo;

// Controls accept scale parameter : either lin (default), log or exp 
amp = hslider("freq[adc:A1][scale:exp]", 0, 0, 1, 0.01) : si.smoo;

// Digital GPIO (1 or 0 only)
gate = button("gate[gpio:D27]); 

// Generate envelop, and map it to DAC A7 (Dac 1) of Seed to control a led, or a scope for example 
env = gate : en.are(0.05, 3) <: attach(_, _ : vbargraph("envelop[dac:A7]));

process = os.sawtooth(freq) * amp * 0.5 * env <: _,_;
```

Then compile with `faust2daisy -seed my.dsp`. 

In order to embrace more fully the potential of Daisy boards, there gpio outputs can be configured as PWM controls, providing more high frequency outputs

``` faust
import("stdfaust.lib");

// Here we get a 0-1 value we put in a bargraph with pwm set to inv (can be off, on or inv). 
// It seems inv gives the actual non-inverted result, while on gives inverted results 
duty = hslider("duty[adc:A0]", 0, 0, 1, 0.001) <: attach(_, _ :   vbargraph("led2[gpio:D17][pwm:inv]", 0, 1)); 

process = os.osc(100) * duty * 0.3;
```

### MIDI 

Midi is implemented for both monophonic controls (control change, keyon, keyoff, key) & polyphonic controls (freq, key, gain, vel, gate). 
Of course, you need to set "nvoices" either as a command line option, or in your DSP metadata. 

MIDI can be passed through the power supply/flash USB interface. This is the MIDI USB mode (default when setting `-midi`) or through serial ports (UART) with `midi-uart` option. In this case, you need to specify which pins are used.

## Targetting platforms 

There is a wide variety of platforms standing on Daisy boards : Pod, Patch, Patch.Init(), Hothouse (...). 
You might as well create your own. 
This is why a JSON configuration file system has been implemented. Two examples (pod and patch) can be found in "faust/architecture/daisy". 

These files provide informations on which board is used (seed or patchsm), which type of MIDI is used, and the current pins used (in case of UART). 
It also provides a mapping of metadata between ADCs/DACs and physical controls : for example [knob:1] = [adc:A4]. 
It doesn't add any feature, but makes it easier to remember than remembering every pin you have on your platform.

For configuration files provided with Faust, they are mapped to a command line option like `-pod` or `-patch`. 
If you are building your own platform, you must set `-config-file <my_path.json>`. 

## Memory Limits (FLASH, SRAM, QSPI, SDRAM)

This new version of *faust2daisy* tool provides an (almost) fully compile time memory footprint, letting you know how storage and memory will be used at build time.

Flash mode defaults to the FLASH (it will use native STM32 bootloader), for program whose binary size can be up to 128 kB.
One of the following options can be used for larger programs (it will propose to install Daisy bootloader first on FLASH first) : 
- `-sram`: to flash program on SRAM - for binary up to 512KB. It will enable `-sdram` option since SRAM won't be usable for RAM anymore. 
- `-qspi`: to flash program on QSPIFLASH - for binary up do 8MB. 
Note that both `-sram` and `-qspi` will propose you to install a specific bootloader (to FLASH) in order to load your DSP when booting.

Since storage is short on embedded platforms, you might want to take benefit from SDRAM for large buffers. 
When building, the compiler will raise an error if your program overflows the location it is supposed to use. 
You can then choose a more appropriate location (SRAM, QSPI), or put large buffers on SDRAM. 
Flash and SRAM are fast, though SRAM option forces you to put buffers to SDRAM (which is slower).
QSPIFLASH is slower than Flash and SRAM. 

## Architecture files

Specific architecture files have been developed:

- [faust/gui/DaisyControlUI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/DaisyControlUI.h): to be used with the DSP `buildUserInterface` method to implement `button`, `checkbox`, `hslider`, `vslider`, `hbargraph`, `vbargraph` controllers, and interpret the specific metadata previously described
- [faust/midi/daisy-midi.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/daisy-midi.h): implements a [midi_handler](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/midi.h) subclass to decode incoming MIDI events.
- [faust/midi/daisy-poly.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/daisy-poly.h): implements a lightweight polyphonic DSP encapsulation

## Python parsing 

This tool uses a combination of interactions between the bash script and two python scripts (generate_config.py & faust_daisy_parser.py). 
The latter is the most important, and will parse JSON representation of you Faust DSP to generate some C++ code to map all UI and metadata informations from Daisy to Faust C++ DSP. 

## New features (08/03/2026)

Daisy support is being refactored to provide a more efficient and memory deterministic support. The idea is to stick as close as possible to Daisy SDK.
It was developed with libDaisy version 8.1.0.
This new development allows the following new features : 
- Near constant memory footprint (almost no dynamic allocation) 
- Chip support (Seed, PatchSM) instead of platforms (Pod, Patch, Patch.Init)
- JSON Configuration files for platforms support (see architecture/daisy/pod.json for example)
- Access to all analog ADCs and DACs of chips (for controls like knobs, sliders, CV etc)
- Access to all GPIO for digital control (useful for buttons, leds) 
- GPIO outputs can be configured with software PWM (dimming led, or additional DAC's)
- MIDI can be passed through internal chip USB, or through UART pins (pod for example).
- MIDI monophonic support for CC, Keyon, Keyoff, Key
- MIDI polyphonic support (algorithms for voice stealing and voice blocking)
- Program can stand on Flash memory (128kB), SRAM (512kB) or QSPIFLASH (8MB)
- Large buffers can be placed on SDRAM with `-sdram`. 
- `-mem-thresh` determines size threshold in bytes above which data is stored on SDRAM  

## Possible future developments 

- Daisy Patch full support (external Audio codec)
- Daisy Patch SM support 
- MIDI external USB peripheral support (Seed)
- OLED screens (Patch, custom platforms)
- DMA for DACs / ADCs : Could provide extended audio inputs & outputs (16 bit for ADC, 12 bits for DAC) or higher time precision for controls 
- Multiplexer for ADCs / DACs (to use with 4051's for example)
- I2C communication (audio and/or control)