# faust2daisy

<<<<<<< HEAD
The **faust2daisy** tool compiles a Faust DSP program in a folder containing the C++ source code and a Makefile to compile it.  
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
This new version is a partial refactor of the previous tool, aiming to : 
- improve memory footprint
- provide compile time memory footprint
- target Daisy boards (while still providing a way to target platforms)
<<<<<<< HEAD
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
=======
The **faust2daisy** tool compiles a Faust DSP program into a C++ program targetting Electrosmith Daisy boards.
It can target both Daisy Seed and Daisy Patch Submodule, as well as used defined platforms built upon (such as Pod, Patch, Patch.Init() etc). 
>>>>>>> f59ca645a (serial communication & hardware PWM implemented, pin conflict guard implemented)

`faust2daisy [-faust2daisy_options...] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
- `-seed`: target Daisy seed chip
- `-patchsm`: target Daisy patchsm chip
- `-pod`: use Pod configuration file 
- `-patch`: use Patch configuration file, as well as Patch audio codec & OLED display
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
- `-sr <num>`: sample rate of DSP : only 8000, 16000, 32000, 48000, 96000 are allowed
- `-bs <num>`: buffer size
- `-sd` to load soundfiles from the SD card at runtime instead of inlining to QSPI
- `-sd-debug` to print loaded soundfile info over USB serial at startup
-  `-upload-sd` to upload soundfiles to the SD card (does not build the DSP, just the uploader)
- Any other option will be passed to Faust compiler
<<<<<<< HEAD


## Features 

This tool tries to provide the most exhaustive control one can give over Daisy boards with Faust DSP programs. 

It features : 
- Audio : High quality, low latency, 2 inputs, 2 outputs
- Audio : Soundfile, either stored in QSPI flash (small files) or in SD card (bigger files)  
- Control : ADC's (up to 12 inputs, 16 bits each) and DAC's (up to 2, 12 bits outputs). 
- Control : MIDI input, either through USB or serial UART
- Control : Digital GPIOs (a large set of on/off switches, or software PWM at ~500/1000Hz)
- Control : Serial communication with other boards 
- Control : hardware PWM output (~29KHz by default)
- Memory : Almost constant, compile-time awareness of memory footprint 
- Memory : control location where program is stored and executed (Flash, SRAM, QSPI flash)
- Memory : control threshold above which memory blocks (delay for example) are stored in SDRAM (64MB) 
- Development : configuration file system, allowing to rename some pins (for example : `knob:1 == adc:A0`)

## Setup 

To use `faust2daisy`, you need the daisy toolchain installed. 
- [Linux](https://daisy.audio/tutorials/toolchain-linux/)
- [Mac](https://daisy.audio/tutorials/toolchain-mac/)

You will also need [libDaisy](https://github.com/electro-smith/libDaisy) to be built. Latest tool was designed to target version 8.1.0. 
You should specify environment variables. For example, on macOS/Linux:
=======
- `-patch`: to compile for 4 ins/outs [Patch](https://electro-smith.com/products/patch)
- `-pod`: to compile for 2 ins/outs [Pod](https://www.electro-smith.com/daisy/pod)
- `-patchsm`: to compile for Patch Submodule and [patch.Init()](https://electro-smith.com/products/patch-init)
- `-sdram`: to compile using SDRAM for long delay lines/tables etc.
- `-midi`: to activate MIDI control
- `-nvoices <num>`: to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
- `-sr <num>`: to specify sample rate (default 44100)
- `-bs <num>`: to specify buffer size (default 16)
- `-source`: to only create the source folder
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))

## Setup 

<<<<<<< HEAD
It is recommended to put your Faust DSP files inside a directory [DaisyExamples](https://github.com/electro-smith/DaisyExamples/)`/DaisySP/faust_examples`. Then execute `faust2daisy code.dsp` with your chosen options. To use `faust2daisy` in an arbitrary directory, you should specify environment variables. For example, on macOS/Linux:
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
To use `faust2daisy`, you need the daisy toolchain installed. 
- [Linux](https://daisy.audio/tutorials/toolchain-linux/)
- [Mac](https://daisy.audio/tutorials/toolchain-mac/)

You will also need [libDaisy](https://github.com/electro-smith/libDaisy) to be built. Latest tool was designed to target version 8.1.0. 
You should specify environment variables. For example, on macOS/Linux:
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
```bash
export LIBDAISY_DIR=~/GitHub/DaisyExamples/libdaisy
export DAISYSP_DIR=~/GitHub/DaisyExamples/DaisySP
```
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======

>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
If on macOS, consider putting the above text in `~/.zshrc` so that it's always set in Terminal.

The default optimization is for file size: `OPT=-Os`. You can optimize for speed by setting `OPT=-O2` or the even more aggressive setting `OPT=-O3`. This can be set in the Makefile in "faust/architecture/daisy".

## Targetting boards 

This tool is intended to target Daisy boards : 
- Seed 
- PatchSM 

The idea is to provide access to all of the Pins that can be useful in an audio context : 
- Audio inputs & outputs (24 bits)
- Control ADCs (16 bits)
- Control DACs (12 bits)
- GPIO (in either on/off mode, or as software PWM for output)
- Serial UART
- MIDI UART 
- PWM 

<<<<<<< HEAD
<<<<<<< HEAD
Example : 
``` faust
=======
Other metadata:

- `[scale:lin|log|exp]` metadata is implemented for knobs.


Encoder can be used as a real rotary encoder from Faust with this simple utility functions : 
``` faust
a = button("enc_a[encoder:a]");
b = button("enc_b[encoder:b]");
    
// This functions returns +1 when turning clockwise, -1 when turning anti clockwise, 0 otherwise
encoder_increment(a, b) = inc
with {
    // Rising edge of A: was 0, now 1
    a_rise = (a > a');
    // At rising edge of A: if B is low = CW (+1), if B is high = CCW (-1)                                                                                                                                                                   
    inc = a_rise * (1 - 2 * int(b));
};  

// This function accumulates increment, with a user defined step    
encoder(inc, step) = _~+(inc * step);

// Usage, (b & a are reversed on pod)
inc = encoder_increment(b, a);
encoder_val = encoder(inc, 1); 

```

## Daisy Patch

The **faust2daisy** tool can be used to program the [patch.Init()](https://electro-smith.com/products/patch-init).

## Bootloader Configuration:

Setup the board to utilize the manufacturer's bootloader, ensuring that the generated code fits within the board's memory. For detailed instructions on flashing the bootloader, please refer to: [Daisy Bootloader Getting Started Guide](https://electro-smith.github.io/libDaisy/md_doc_2md_2__a7___getting-_started-_daisy-_bootloader.html).

## Memory Limits (SDRAM)

If you're using a Daisy with significant amount of SDRAM such as the Pod or patch.Init, then you may want to use the `-sdram` flag when compiling code involving long delay lines/tables etc. Enabling this will execute a Python script inside `faust2daisy` that modifies the generated C++ code to put large float buffers (e.g., delay lines) in SDRAM. For this to work, you must have `python3` available on the command line.

## DSP Examples

Here is a simple example showing how oscillators can be controlled by physical items and MIDI messages:

```
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
Example : 
``` faust
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
import("stdfaust.lib");

freq = hslider("freq[adc::A0]", 50, 50, 1000, 0.1) : si.smoo;

// Controls accept scale parameter : either lin (default), log or exp 
amp = hslider("amp[adc:A1][scale:exp]", 0, 0, 1, 0.01) : si.smoo;

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
Of course, you need to set "nvoices" either as a command line option, or in your DSP global metadata. 

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

<<<<<<< HEAD
## Architecture files

Specific architecture files have been developed:

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
- [faust/gui/DaisyControlUI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/DaisyControlUI.h): to be used with the DSP `buildUserInterface` method to implement `button`, `checkbox`, `hslider`, `vslider`, `hbargraph`, `vbargraph` controllers, and interpret the specific metadata previously described
- [faust/midi/daisy-midi.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/daisy-midi.h): implements a [midi_handler](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/midi.h) subclass to decode incoming MIDI events.
- [faust/midi/daisy-poly.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/daisy-poly.h): implements a lightweight polyphonic DSP encapsulation

=======
>>>>>>> f59ca645a (serial communication & hardware PWM implemented, pin conflict guard implemented)
## Python parsing 

This tool uses a combination of interactions between the bash script and a set of python scripts, designed to parse and interpret metadata of your Faust DSP program. 

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

## Soundfiles

The Faust `soundfile` primitive is supported. WAV files referenced by the DSP are
parsed **at build time** and inlined into a generated `daisy_soundfile.hpp`, so
there is no runtime file system and no dynamic allocation. Supported formats are
WAV PCM 16/24/32 bit and IEEE float 32 bit; all data is decoded to `float`.

```faust
import("stdfaust.lib");
// 'kick.wav' must sit next to the .dsp file
sample = soundfile("kick[url:{'kick.wav'}]", 2);
process = 0,0 : sample : !,_,_;
```

Multi-part lists are supported too: `soundfile("s[url:{'a.wav';'b.wav'}]", 2)`.
If a referenced file cannot be found, the build stops with an error.

There are two ways to provide the samples, selected by a CLI option:

### QSPI inlining (default)

The samples are inlined as `const` data. **Build with `-qspi`** so they are placed
in QSPI flash and read memory-mapped (never copied to RAM); the program and the
samples are flashed together as a single image, exactly like any other `-qspi`
program. This is required because audio data does not fit in the 128 KB internal
flash, and QSPI can only be programmed through the Daisy bootloader (which `-qspi`
already uses). A very small soundfile may still fit when built in the default
FLASH mode, but anything sizeable needs `-qspi`.

### SD card at runtime (`-sd`)

With `-sd`, the samples are **not** inlined: the DSP loads `/soundfiles/*.wav`
from the SD card into SDRAM at startup. This keeps the program small (it can run
from internal flash) and supports large/long sounds, but requires an SD card
(see *SD card pins*: only boards exposing the Seed SDMMC pins, e.g. Patch). The
SDRAM arena defaults to 32 MB (override with `-DFAUST_SD_SOUNDFILE_BYTES`).

> The card **must be formatted FAT32** — libDaisy's FatFS has exFAT disabled, so
> exFAT cards (the default for ≥ 32 GB cards) will fail to mount. The uploader
> reports the FatFS error code on failure, e.g. `ERR nomount=13` means
> `FR_NO_FILESYSTEM` (wrong format), `=3` means `FR_NOT_READY` (card not detected).

Upload the WAV files referenced by a DSP to the card with:

```
faust2daisy -upload-sd my.dsp
```

This temporarily flashes a small uploader firmware, then streams the files over
USB-serial into a `/soundfiles` folder (clearing that folder first; nothing else
on the card is touched). Then build and flash the DSP itself with `-sd`:

```
faust2daisy -sd my.dsp
```

> Note: the architecture files and tools must be **installed** (so faust2daisy
> picks them up) — building from the repo alone is not enough, faust2daisy reads
> the installed copies under `faust --archdir`.

## PWM 

This tool allows to output bargraph values to hardware PWM outputs. 
To do so, simply add the metadata `vbargraph("outvalue[pwm:D1]", 0, 1)`. All PWM available pins are referenced inside **daisy_pwm_pin.py**, inside Faust daisy architecture folder.
The PWM output is clocked around 29Khz. 

## Serial 

Serial communication is available in the same way as other controls. It can be used to receive or to transmit control data. 
- Receive : `hslider("freq[rx:D1], 100, 20, 1000, 0.1)`  
- Transmit : `vbargraph("outvalue[tx:D2], 0, 1)`

Messages are formatted like this : `freq <value>` where **<value>** is a 4 bytes float, passed as binary representation. 

## Possible future developments 

- MIDI custom USB peripheral support (Seed)
- OLED screens (Patch, custom platforms)
- DMA for DACs / ADCs : Could provide extended audio inputs & outputs (16 bit for ADC, 12 bits for DAC) or higher time precision for controls 
- Multiplexer for ADCs / DACs (to use with 4051's for example)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
- I2C communication (audio and/or control)
=======
- [faust/gui/DaisyControlUI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/DaisyControlUI.h): to be used with the DSP `buildUserInterface` method to implement `button`, `checkbox`, `hslider`, `vslider` controllers, and interpret the specific metadata previously described
- [faust/midi/daisy-midi.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/daisy-midi.h): implements a [midi_handler](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/midi.h) subclass to decode incoming MIDI events.
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
- I2C communication (audio and/or control)
>>>>>>> b375e26ef (daisy seed is almost full featured, added PWM support for digital outputs, added options to commmand line (rx pin, tx pin))
=======
- I2C communication (audio and/or control)
=======
>>>>>>> f59ca645a (serial communication & hardware PWM implemented, pin conflict guard implemented)
- Serial communication for control

## Changelog 

### Features

02/07/2026
- Soundfile primitive support: WAV files (PCM 16/24/32 bit, float 32 bit). Two modes:
  - default (`-qspi`): parsed at build time and inlined into QSPI flash, no runtime
    file I/O or dynamic allocation.
  - `-sd`: loaded from the SD card (`/soundfiles`) into SDRAM at startup. Files are
    uploaded with `faust2daisy -upload-sd` (temporary CDC uploader firmware).
  - Daisy Patch supported 
  - Daisy PatchSM supported 
 - Serial control through UART pins (both RX and TX are implemented), passing messages in the format "amp 0.72551" 
 - Hardware PWM output (defaults to 29Khz) wiht `pwm:D1`. 

### Fixes 

18/06
- Midi input was not initialized 
- Python parser script was not working well with DAC's 
- MIDI CC was not working properly for checkboxes and buttons. Now it is working as Faust documentation says : returns 1 if CC is 127, returns 0 if CC is 0
- Python parser crashed on a DSP with UI controls when no configuration file was provided
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 3028c82cc (implemented QSPI soundfile, fixed issues (midi input initialization, DAC's broken, CC with checkbox or button)
=======
=======
23/06
- Fixed Patch screen bar ordering 
>>>>>>> 6482c2631 (fixed bugs (digi output), patch screen is working properly, patchsm is tested for GPIO, CV, audio out, and MIDI (poly and monophonic))

# TODO 

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 652359c9f (fixed soundfile on SD card, patchsm started with working outputs and DACS/ADCs)
=======
- Test all PatchSM features 
- Check polyphony and shared controls and outputs


- Test : polyphonic (shared input, output,), digi inp outp, shared digi in, shared digi outp
- Tester polyphonie sur le PATCH
- Digi input : le sens n'est pas clair (haut bas) : essayer avec un vrai bouton 
>>>>>>> 6482c2631 (fixed bugs (digi output), patch screen is working properly, patchsm is tested for GPIO, CV, audio out, and MIDI (poly and monophonic))
=======
- Solve conflict between metadata, global metadata, CLI options, and config file 
- Get more relevant error messages from parser 
>>>>>>> f59ca645a (serial communication & hardware PWM implemented, pin conflict guard implemented)
