import("diffable.lib");

process = _*(gain + tremolo)
with {
    gain = .4;
    rate = 8;
    depth = .25;

    modulator = .5*(1+diffableOsc(rate));
    tremolo = depth*modulator; // <: attach(hbargraph("trem", -1, 1));
};
