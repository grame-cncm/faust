# JSFX Backend for Faust

Currently has available features : 
* Sliders 
* Buttons and Checkboxes are translated to integer sliders in range 0-1
* MIDI : keyon, keyoff, key, ctrl

# TODO

* MIDI -> add nvoices support (with voice stealing)
* MIDI -> currently, slider values are computing in @block section if midi is on. It would be nice to move only the "fSlow" variables corresponding to MIDI to the block section.
* Grain3.dsp not passing
* Indent
* Architecture file 
* Bargraph for MIDI output 
