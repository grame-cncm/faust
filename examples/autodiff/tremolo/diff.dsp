declare name "Differentiable tremolo";
declare description "A differentiable tremolo effect.";

import("diffable.lib");

process = _*(gain + tremolo)
with {
    gain = hslider("gain [diff:1]", .25, 0, .5, .001);
    rate = hslider("rate [diff:1] [unit:Hz]", 5, .1, 100, .1);
    depth = .25;

    modulator = .5*(1+diffableOsc(rate));
    tremolo = depth*modulator;
};
