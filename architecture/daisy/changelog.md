# 03/07/2026 

## Features 
* Soundfile primitive support: WAV files (PCM 16/24/32 bit, float 32 bit). Two modes:
  * default (`-qspi`): parsed at build time and inlined into QSPI flash, no runtime
    file I/O or dynamic allocation.
  * `-sd`: loaded from the SD card (`/soundfiles`) into SDRAM at startup. Files are
    uploaded with `faust2daisy -upload-sd` (temporary CDC uploader firmware).
  * Daisy Patch supported 
  * Daisy PatchSM supported 
 * Serial control through UART pins (both RX and TX are implemented), passing messages in the format "amp 0.72551" 
 * Hardware PWM output (defaults to 29Khz) wiht `pwm:D1`. 
 * PIN conflict checking on parser side (for example using `[adc:A0]` and `[gpio:D15]` on daisy seed won't work, since it would conflict, same pin)

## Fix 
* Midi input was not initialized 
* Python parser script DAC interpretation was wrong 
* MIDI CC was not working properly for checkboxes and buttons. Now it is working as Faust documentation says : returns 1 if CC is 127, returns 0 if CC is 0
* Python parser crashed on a DSP with UI controls when no configuration file was provided
* Fixed Patch screen bar ordering 

# 08/03/2026

Daisy support is being refactored to provide a more efficient and memory deterministic support. The idea is to stick as close as possible to Daisy SDK. It was developed with libDaisy version 8.1.0. This new development allows the following new features :

* Near constant memory footprint (almost no dynamic allocation)
* Chip support (Seed, PatchSM) instead of platforms (Pod, Patch, Patch.Init)
* JSON Configuration files for platforms support (see architecture/daisy/pod.json for example)
* Access to all analog ADCs and DACs of chips (for controls like knobs, sliders, CV etc)
* Access to all GPIO for digital control (useful for buttons, leds)
* GPIO outputs can be configured with software PWM (dimming led, or additional DAC's)
* MIDI can be passed through internal chip USB, or through UART pins (pod for example).
* MIDI monophonic support for CC, Keyon, Keyoff, Key
* MIDI polyphonic support (algorithms for voice stealing and voice blocking)
* Program can stand on Flash memory (128kB), SRAM (512kB) or QSPIFLASH (8MB)
* Large buffers can be placed on SDRAM with -sdram.
* -mem-thresh determines size threshold in bytes above which data is stored on SDRAM
