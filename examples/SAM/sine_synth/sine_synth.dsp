// tosc.dsp - test simple oscillator + MIDI bindings
import("stdfaust.lib");
process = g * a * os.oscrs(f*b) <: _,_;
a = hslider("gain [midi:ctrl 7]",1,0,1,0.001);
f = hslider("freq",392.0,200.0,450.0,0.01);
b = hslider("bend [midi:pitchwheel]",1,0.1,10,0.001);
g = button("gate");
