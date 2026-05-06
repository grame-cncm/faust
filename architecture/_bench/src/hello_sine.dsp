import("stdfaust.lib");

decimalpart(x) = x - int(x);
phase(f) = f / ma.SR : (+ : decimalpart) ~ _;
osc(f) = sin(phase(f) * 2 * ma.PI);

freq = hslider("freq", 440, 20, 2000, 1);

process = osc(freq);
