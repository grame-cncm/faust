import("stdfaust.lib");
// a smoother of the constant 1, its pole p : y = (1 - p) + p y', the ramp of an envelope
p = hslider("p", 0.99, 0.5, 0.999, 0.001);
process = loop ~ _ with { loop(y) = (1 - p) + y*p; };
