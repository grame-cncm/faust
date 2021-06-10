import("stdfaust.lib");
process = ba.pulsen(1, ba.hz2midikey(freq) * 1000) : pm.marimba(freq, 0, 7000, 0.5, 0.8) * gate * gain with {
  freq = hslider("freq", 440, 40, 8000, 1);
  gain = hslider("gain", 0.5, 0, 1, 0.01);
  gate = button("gate");
};
