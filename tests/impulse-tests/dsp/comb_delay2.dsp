import("stdfaust.lib");

// 10 samples delay modulation
modulator = @(os.osc(1000) : +(1) : *(5) : min(10) : max(0));
fix = @(100);
source = os.osc(440);

process = source : fix : modulator;