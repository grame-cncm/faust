// The outputs are what a note wrote: its frequency, its gain, its gate.
freq = hslider("freq", 100, 20, 20000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = button("gate");
process = freq, gain, gate;
