# JSFX Backend for Faust

Currently has available features :

* Sliders
* Buttons and Checkboxes are translated to integer sliders in range 0-1
* MIDI : keyon, keyoff, key, ctrl
* Polyphonic MIDI (key, freq, gain, veloc or vel, gate)

# TODO

* Add sustain (CC 64) - with metadata like `sustain[midi:ctrl 64]`
* Add aftertouch and missing MIDI messages 
* Bargraph for MIDI output

# Possible improvements 

* GFX (graphics) section described by user and compiled with an architecture file or similar mechanism
* Or a GFX library accessible by sliders metadata
