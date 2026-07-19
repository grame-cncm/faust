import("stdfaust.lib");

// Polyphony fixture WITH a shared learnable parameter.
//
// freq/gain/gate are turned into per-voice signal inputs via widget modulation
// (replace = !,_;), while `cutoff` stays an hslider -> a single learnable
// nnx.Param that is shared (broadcast) across all vmapped voices. This gives a
// parameter to differentiate (gradients accumulate over voices) and to persist
// with safetensors.
freq = hslider("freq", 440, 20, 20000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = hslider("gate", 0, 0, 1, 1);
cutoff = hslider("cutoff", 1000, 50, 8000, 1);

synth = os.osc(freq) * en.ar(0.05, 2.0, gate) * gain : fi.lowpass(1, cutoff);

replace = !,_;
process = ["freq": replace, "gain": replace, "gate": replace -> synth];
