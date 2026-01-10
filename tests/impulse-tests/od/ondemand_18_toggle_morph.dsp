import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
gateA = checkbox("a") == 0;
gateB = checkbox("b") == 0;
blend = hslider("blend", 0, 0, 1, 0.01);

base = os.osc(220);

pathA = gateA : ondemand(base : fi.lowpass(2, 600));
pathB = gateB : ondemand(base : fi.highpass(2, 1200));

mix = pathA * (1.0 - blend) + pathB * blend;

process = outerGate : ondemand(mix);
