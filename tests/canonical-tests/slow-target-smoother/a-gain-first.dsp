import("stdfaust.lib");
// a smoother of a slow target t, its pole p : y = (1 - p) t + p y'
p = hslider("p", 0.99, 0.5, 0.999, 0.001);
t = hslider("t", 1, 0, 10, 0.01);
process = t : *(1 - p) : + ~ *(p);
