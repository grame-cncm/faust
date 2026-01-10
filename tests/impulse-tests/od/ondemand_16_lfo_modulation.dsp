import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
lfoGate = checkbox("lfo") == 0;
base = hslider("base", 440, 100, 1000, 1);
depth = hslider("depth", 100, 0, 400, 1);

lfo = lfoGate : ondemand(os.osc(0.5) * depth);

process = outerGate : ondemand(os.osc(base + lfo));
