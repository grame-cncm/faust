// The slider is read from a FAUSTFLOAT zone, a float : the float of 0.7 is below 0.7,
// and in -double x < 0.7 is true at the minimum of the slider. The comparison must not
// be decided (and folded) at compile time. In -single, the literal 0.7f is that same
// float : x < 0.7f is false at the minimum, rightly decided.
x = hslider("x", 0.7, 0.7, 1, 0.01);
process = rdtable(3, (+(1)~_), 1 + (x < 0.7));
