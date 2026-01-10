import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
gateL = checkbox("left") == 0;
gateR = checkbox("right") == 0;

branchL(x) = (gateL, x) : ondemand(fi.lowpass(2, 600));
branchR(x) = (gateR, x) : ondemand(fi.highpass(2, 1200));
mix(x) = branchL(x) + branchR(x);

process = (outerGate, _) : ondemand(mix);
