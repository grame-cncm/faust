import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
innerGate = checkbox("inner") == 0;
freq = hslider("freq", 440, 100, 2000, 1);
cut = hslider("cutoff", 800, 50, 5000, 1);

process = vgroup("outer", outerGate : ondemand(
  hgroup("inner", innerGate : ondemand(os.osc(freq) : fi.lowpass(2, cut)))
));
