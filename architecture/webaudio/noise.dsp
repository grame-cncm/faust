import("stdfaust.lib");

process = no.noise * hslider("Volume", 0.5, 0, 1, 0.01);
