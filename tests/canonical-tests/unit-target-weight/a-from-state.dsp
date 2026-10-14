import("stdfaust.lib");
// a smoother of the constant 1 given by the weight w of its target : y = w + (1 - w) y'
w = hslider("w", 0.01, 0.001, 0.5, 0.001);
process = loop ~ _ with { loop(y) = y + w*(1 - y); };
