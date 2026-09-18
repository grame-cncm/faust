declare name "phasor_sine";

import("stdfaust.lib");

freq = hslider("freq[unit:Hz]", 440, 20, 20000, 1);

phase(f) = (+(f / ma.SR) : ma.frac) ~ _;
sine(f) = sin(2.0 * ma.PI * phase(f));

process = sine(freq);
