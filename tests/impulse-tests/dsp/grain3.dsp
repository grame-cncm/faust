import("stdfaust.lib");

grainsize = hslider("grainsize [unit:msec]", 100, 1, 1000, 1);
rarefaction = hslider("rarefaction", 0.2, 0, 1, 0.01);
delaymax = hslider("delaymax", 1000, 10, 10000, 1);
grainfreq = 1000 / grainsize;
ramp = os.phasor(1, grainfreq);
seuil = (ramp > 0.0001) * (ramp@1 <= 0.0001);
phase = ramp : *(0.5) : *(2) : *(ma.PI);
source = _;

test = (no.noise : +(1) : *(0.5)) > rarefaction;
factor = test : ba.sAndH(seuil);

del = no.noise : +(1) : *(0.5) : *(delaymax) : *(ma.SR) : /(1000) : ba.sAndH(seuil);

process = source : de.fdelay(524288, del) : *(os.oscp(0, phase)) *(factor);
