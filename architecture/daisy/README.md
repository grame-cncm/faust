# faust2daisy

The **faust2daisy** tool compiles a Faust DSP program for Electrosmith Daisy boards. It will generate appropriate code for inputs, outputs, and controls, build it and flash it on the daisy board. 

`faust2daisy [-patch] [-pod] [-sdram] [-midi] [-nvoices <num>] [-sr <num>] [-bs <num>] [-source] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-patch`: to compile for 4 ins/outs [Patch](https://electro-smith.com/products/patch)
- `-pod`: to compile for 2 ins/outs [Pod](https://www.electro-smith.com/daisy/pod)
- `-patchsm`: to compile for Patch Submodule and [patch.Init()](https://electro-smith.com/products/patch-init)
- `-sdram`: to compile using SDRAM for long delay lines/tables etc.
- `-mem-thresh <num>`: with sdram option, will define the size threshold above which data is stored on SDRAM.
- `-midi`: to activate MIDI control
- `-nvoices <num>`: to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
- `-sr <num>`: to specify sample rate (default 44100)
- `-bs <num>`: to specify buffer size (default 16)
- `-source`: to only create the source folder

Flash mode options: 
Flash mode defaults to FLASH (the Faust DSP will be stored and executed from Flash memory), for program whose binary can be up to 128KB.
One of the following options can be used for larger programs (it will propose to install Daisy bootloader first on FLASH first) : 
- `-sram`: to flash program on SRAM - for binary up to 512KB. It will enable `-sdram` option since SRAM won't be usable for RAM anymore. 
- `-qspi`: to flash program on QSPIFLASH - for binary up do 8MB : this may slow down execution. 

The `faust2daisy` script requires the following environment variables : 

```bash
export LIBDAISY_DIR=~/GitHub/DaisyExamples/libdaisy
export DAISYSP_DIR=~/GitHub/DaisyExamples/DaisySP
```

If on macOS, consider putting the above text in `~/.zshrc` so that it's always set in Terminal. On Linux `~/.bashrc`. 

The default optimization is for file size: `OPT=-Os`. You can optimize for speed by setting `OPT=-O2` or the even more aggressive setting `OPT=-O3`.

## Daisy Pod

The **faust2daisy** tool can be used to program the [Pod](https://www.electro-smith.com/daisy/pod). On this board, the 2 *switches* and 2 *knobs* can be connected to UI controllers using metadata:

- `[switch:N]` (with N from 1 to 2) has to be used in a `button` or `checkbox` item to connect it to the Pod switch number N.
- `[knob:N]` (with N from 1 to 2) has to be used in a `vslider`, `hslider` or `nentry` item to connect it to the Pod knob number N. The knob [0..1] range will be mapped to the slider/nentry [min..max] range.

Other metadata:

- `[scale:lin|log|exp]` metadata is implemented for knobs.

## Daisy Patch.Init()

The **faust2daisy** tool can be used to program the [patch.Init()](https://electro-smith.com/products/patch-init).

## Bootloader Configuration:

Setup the board to utilize the manufacturer's bootloader, ensuring that the generated code fits within the board's memory. For detailed instructions on flashing the bootloader, please refer to: [Daisy Bootloader Getting Started Guide](https://electro-smith.github.io/libDaisy/md_doc_2md_2__a7___getting-_started-_daisy-_bootloader.html).

## Memory Limits (SDRAM)

If you're using a Daisy with significant amount of SDRAM such as the Pod or patch.Init, then you may want to use the `-sdram` flag when compiling code involving long delay lines/tables etc. Enabling this will execute a Python script inside `faust2daisy` that modifies the generated C++ code to put large float buffers (e.g., delay lines) in SDRAM. For this to work, you must have `python3` available on the command line. The `-mem-thresh` option allows you to define a size threshold, above which data will be stored on SDRAM. 

## DSP Examples

Here is a simple example showing how oscillators can be controlled by physical items and MIDI messages:

```
import("stdfaust.lib");

// UI controllers connected using metadata
freq = hslider("freq [knob:1] [midi:ctrl 1] [scale:log]", 200, 50, 5000, 0.01);
gain = hslider("gain [knob:2] [midi:ctrl 7]", 0.5, 0, 1, 0.01);
gate = button("gate [switch:1]");
check = checkbox("check [switch:2]");

// DSP processor
process = os.osc(freq) * gain * gate, os.sawtooth(freq) * gain * check;
```

## Architecture files

Specific architecture files have been developed:

- [faust/gui/DaisyControlUI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/DaisyControlUI.h): to be used with the DSP `buildUserInterface` method to implement `button`, `checkbox`, `hslider`, `vslider` controllers, and interpret the specific metadata previously described
- [faust/midi/daisy-midi.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/daisy-midi.h): implements a [midi_handler](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/midi/midi.h) subclass to decode incoming MIDI events.

# Limitations 

Currently, MIDI polyphonic DSP's will likely cause crash, and should not be considered as an option. 
Tests involved Daisy POD and Daisy SEED. No tests involved Daisy Patch interface and Patch SM board.

## Refactoring 

The `faust2daisy` utility is currently being refactored. The following features may appear in the future : 
- More direct access to boards (seed and patch_sm) providing all ADC's and DAC's
- More compact code (lighter binaries)
- Static memory for data : removing most dynamic memory allocation to predict accurately binary size
- MIDI Polyphonic support 
