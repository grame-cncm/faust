# JSFX Backend for Faust

Currently has available features : 
* Sliders 
* Buttons and Checkboxes are translated to integer sliders in range 0-1
* MIDI : keyon, keyoff, key, ctrl
* Experimental Polyphonic MIDI (key, freq, gain, veloc or vel, gate)

# TODO

* MIDI Poly > Modes for voices steeling, voice blocking (...)
* 7 tests not passing
* Indent
* Architecture file 
* Bargraph for MIDI output 

*   Now 
    * Fix MIDI and slider scaling with FAUST MIDI laws (steps)

* Current fix : 
    - move fTemp2 etc inside class definition
    - find a way to process post compute > probably before the control() > this way we can achieve the proper operation order
