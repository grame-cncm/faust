# faust2teensy

The **faust2teensy** tool can be used to fully program the Teensy microcontroller and to generate DSP objects compatible with the Teensy audio library. In both cases, we strongly recommend to use the Teensy 3.6 which hosts an FPU (i.e., the Teensy 3.2 doesn't have one). 

`faust2teensy [-lib] [-midi] [-nvoices <num>] [-mem] [Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-lib`: to generates a package containing an object compatible with the Teensy audio library
- `-midi`: to activate MIDI control
- `-nvoices <num>`: to produce a polyphonic self-contained DSP with <num> voices
- `-mem`: (Teensy 4.x) to place the DSP's memory in the fastest place it fits: small zones on the heap, delay lines and tables up to 32 kB in an arena in DTCM, up to 128 kB in RAM2 (while 64 kB of the heap stay free), the rest in the PSRAM of a Teensy 4.1 (or the heap without PSRAM). Delay lines read from PSRAM on every sample can cost a lot of CPU; see `faust/dsp/teensy-memory.h` for the limits (`FAUST_TEENSY_ARENA`, ...) and `faust/dsp/tiered-memory-manager.h` for the manager

Polyphony uses `faust/dsp/mcu-poly-dsp.h`: no RTTI or `std::map` (Teensy builds have no RTTI, which `poly-dsp.h` needs), silent voices are not computed, a stolen voice fades out and in over 3 ms, and a parameter with `[poly:mode]` chooses the assign mode (rotate, reuse, unison). With `-midi` the voices play the notes of the Teensy's MIDI input.

So using `faust2teensy -lib foo.dsp` will generate the `foo.h` and `foo.cpp` files. Create a new project in the Arduino/Teensyduino software (e.g., call it foo) and place foo.cpp and foo.h in the same folder (whose name should probably be /foo) than foo.ino. See the [full tutorial](https://faustdoc.grame.fr/tutorials/teensy/).
