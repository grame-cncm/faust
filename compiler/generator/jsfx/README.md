# JSFX Backend for Faust

Currently has available features : 
* Sliders 
* Buttons and Checkboxes are translated to integer sliders in range 0-1
* MIDI : keyon, keyoff, key, ctrl
* Experimental Polyphonic MIDI (key, freq, gain, veloc or vel, gate)

# TODO

* MIDI Poly > Modes for voices steeling, voice blocking (...)
* Grain3.dsp not passing
* Indent
* Architecture file 
* Bargraph for MIDI output 

** NOw -> To debug, prototype by fixing JSFX directly 
    * Fix MIDI and slider scaling with FAUST MIDI laws
    * Liste de tri des voix (devant la plus récemment allouée, derrière la plus ancienne)
    * Comment on trouve la voix correspondante à éteindre ? 