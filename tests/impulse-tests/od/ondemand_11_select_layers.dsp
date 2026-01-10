import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
gateA = checkbox("a") == 0;
gateB = checkbox("b") == 0;
sel = hslider("select", 0, 0, 1, 1);

sigA = gateA : ondemand(os.osc(300) : fi.lowpass(2, 800));
sigB = gateB : ondemand(os.square(400) : fi.highpass(2, 200));

process = outerGate : ondemand(select2(sel, sigA, sigB));
