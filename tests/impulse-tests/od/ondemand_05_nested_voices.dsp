import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
innerGateA = checkbox("innerA") == 0;
innerGateB = checkbox("innerB") == 0;

inner(freq, gate) = gate : ondemand(os.osc(freq));

mix = inner(220, innerGateA) + inner(330, innerGateB);

process = outerGate : ondemand(mix);
