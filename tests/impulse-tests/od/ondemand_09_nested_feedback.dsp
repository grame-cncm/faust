import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
innerGate = checkbox("inner") == 0;

process = outerGate : ondemand(innerGate : ondemand(os.osc(220) : +~*(0.4)));
