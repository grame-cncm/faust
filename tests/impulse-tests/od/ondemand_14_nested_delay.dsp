import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
innerGate = checkbox("inner") == 0;
delaySamps = int(ma.SR / 200);

process = outerGate : ondemand(innerGate : ondemand(os.osc(440) : @(delaySamps)));
