// Reverse the output order of pow_int_float.dsp so the floating-point
// helper is declared first. The integer helper must still wrap on overflow.
n = int(hslider("n", 50000, 0, 50000, 1));
x = hslider("x", 0.6, 0, 1, 0.01);

process = x * x, float(n * n);
