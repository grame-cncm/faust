import("effect.lib");

process = par(i, 8, crybaby(hslider("freq", 100, 10, 1000, 1)));
