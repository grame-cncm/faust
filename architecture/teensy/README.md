# faust2teensy

The **faust2teensy** tool can be used to fully program the Teensy microcontroller and to generate DSP objects compatible with the Teensy audio library. In both cases, we strongly recommend to use the Teensy 3.6 which hosts an FPU (i.e., the Teensy 3.2 doesn't have one). 

`faust2teensy [-lib] [-midi] [-nvoices <num>] [Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `-lib`: to generates a package containing an object compatible with the Teensy audio library
- `-midi`: to activate MIDI control
- `-nvoices <num>`: to produce a polyphonic self-contained DSP with <num> voices

So using `faust2teensy -lib foo.dsp` will generate the `foo.h` and `foo.cpp` files. Create a new project in the Arduino/Teensyduino software (e.g., call it foo) and place foo.cpp and foo.h in the same folder (whose name should probably be /foo) than foo.ino. See the [full tutorial](https://faustdoc.grame.fr/tutorials/teensy/).
