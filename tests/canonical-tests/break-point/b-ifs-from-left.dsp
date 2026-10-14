import("stdfaust.lib");
// the break-point function (0, 0) (10, 5) (20, -3) (30, 1), held outside
x = hslider("x", 15, -5, 40, 0.01);
process = ba.if(x < 0, 0, ba.if(x < 10, x*0.5, ba.if(x < 20, 5 + (x - 10)*(-0.8), ba.if(x < 30, -3 + (x - 20)*0.4, 1))));
