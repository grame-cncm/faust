import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
innerGate = checkbox("inner") == 0;

inner = ondemand(fi.lowpass(2, 800));
outer = ondemand((_, _) : inner : fi.highpass(2, 200));

process = (outerGate, innerGate, _) : outer;
