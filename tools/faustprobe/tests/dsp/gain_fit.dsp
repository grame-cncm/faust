// The host loop of a hand-derived gradient: the two gains of y = g1 x + g2 x'
// fitted to 0.5 and -0.25 under white noise.
g1 = hslider("g1", 0.0, -2, 2, 0.001);
g2 = hslider("g2", 0.0, -2, 2, 0.001);
e(x) = (g1 - 0.5) * x + (g2 + 0.25) * x';
process = _ <: (e(_) <: _ * _), (_ <: (e(_) * _ : *(2)), (e(_) * _' : *(2)));
