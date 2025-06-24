import("stdfaust.lib");

freq = nentry("freq", 440, 50, 2000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = button("gate");

osc = dm.sawtooth(freq) * gain * gate;
process = osc <: _,_;

