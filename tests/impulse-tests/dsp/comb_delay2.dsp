import("music.lib");

// 10 samples delay modulation
modulator = @(osc(1000) : +(1) : *(5) : min(10) : max(0));
fix = @(100);
source = osc(440);

process = source : fix : modulator;
