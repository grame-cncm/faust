// -double, FAUSTFLOAT float: the slider at its maximum reads float(0.3) from its zone, above 0.3,
// so the amount reaches 3.0 while the interval proves it below 3 (a line of 3 values)
process = _ <: @(hslider("x", 0, 0, 0.3, 0.001) * 9 + 0.3);
