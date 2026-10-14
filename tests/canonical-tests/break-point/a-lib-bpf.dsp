import("stdfaust.lib");
// the break-point function (0, 0) (10, 5) (20, -3) (30, 1), held outside
x = hslider("x", 15, -5, 40, 0.01);
process = x : ba.bpf.start(0, 0) : ba.bpf.point(10, 5) : ba.bpf.point(20, -3) : ba.bpf.end(30, 1);
