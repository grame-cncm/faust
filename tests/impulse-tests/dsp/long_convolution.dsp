declare name "long_convolution";
// Long FIR convolution in DEFAULT mode : the witness the impulse suite
// lacked. A 48-tap irregular kernel reads its source at every delay
// 0..47 through a ring buffer -- the adjacent-read chains of the
// emission (carried scalars, refresh order) are exercised end to end.
// An inverted refresh chain floods every carried value and the response
// is massively wrong from the first taps (the guitarix lesson :
// coverage holes have the exact shape of their witness).

import("stdfaust.lib");

conv48 = fi.conv((
    0.000488281, -0.0020752, 0.000561523, -0.00231934, 0.000634766, -0.00247803,
    0.000512695, -0.00247803, 0.000146484, -0.00219727, -0.000622559, -0.00145264,
    -0.00202637, -2.44141e-05, -0.00438232, 0.00247803, -0.00822754, 0.00706787,
    -0.0159546, 0.0202148, -0.0471558, 0.0953003, -0.208582, 0.312427,
    0.75, -0.26803, 0.399963, 0.200696, -0.146655, -0.29303,
    -0.222168, -0.113098, 0.0267334, 0.0312134, 0.164685, 0.0443481,
    0.186621, 0.0540039, 0.123303, 0.0805054, 0.0739868, 0.0591797,
    0.0661743, 0.0400391, 0.0429932, 0.0339844, 0.0320557, 0.02323
));

// the impulse decays through a one-pole, and a steady sine keeps every
// tap exercised over the whole 60000-sample run (a witness that goes
// silent after 130 samples would miss any steady-state miscompilation)
process = (_ : fi.pole(0.5)) + 0.25 * os.osc(440.0) : conv48;
