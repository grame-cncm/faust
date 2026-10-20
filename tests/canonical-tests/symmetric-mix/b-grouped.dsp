// A + (1 + w) - w A
import("stdfaust.lib");
g = hslider("g", 0, -10, 10, 0.1);
A = pow(10, g/40);
w = cos(hslider("f", 1000, 100, 10000, 1)/ma.SR);
process = A + (1 + w) - w*A;
