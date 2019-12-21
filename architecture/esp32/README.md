# ESP32 Architectures

The ESP32 is a cheap microcontroller developed and distributed by Espressif: <https://www.espressif.com/en/products/hardware/esp32/overview>. It is used at the heart of an increasing number of boards, especially for real-time DSP applications.

## `faust2esp32`

`faust2esp32` can be used to turn a Faust program into an DSP engine for the ESP32. While new options are being added to it, the current (and only) way to use `faust2esp32` is by running:

```
faust2esp32 -lib FaustFile.dsp
```

which will generate a `.zip` package containing: 

* a DSP engine taking the form a C++ class (named after the name of the Faust file, so `FaustFile` here)
* a C++ object to configure the potential audio codec used on your ESP32-based board (currently, only the Wolfson WM8978 used on the [TTGO T-Audio](https://github.com/LilyGO/TTGO-TAudio) board is being supported but we're in the process of adding new ones).

The `architecture/esp32/drivers` folder contains the documentation of each object related to specific audio codecs.

## Tutorial

A series of tutorials demonstrating how to use `faust2esp32` can be found on the Faust website: <https://faust.grame.fr/doc/tutorials#dsp-on-the-esp32-with-faust>.

## Credit

This project is the fruit of a collaboration between Romain Michon (GRAME-CNCM, Lyon, France) and Dan Overholt (Aalborg University, Copenhagen, Denmark).
