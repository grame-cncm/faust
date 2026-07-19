import("stdfaust.lib");

freq = hslider("freq", 440, 20, 20000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = hslider("gate", 0, 0, 1, 1);

// Widget modulation: naming process args the same as hslider variables
// replaces those widgets with signal inputs.
synth = os.osc(freq) * en.ar(0.05, 2.0, gate) * gain;

// process = synth; // if using inside the Faust IDE;

replace = !,_;
process = ["freq": replace, "gain": replace, "gate": replace -> synth];
