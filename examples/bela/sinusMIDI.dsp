import("stdfaust.lib");


phasor(f)   = f/ma.SR : (+,1.0:fmod) ~ _ ;
osc(f)      = phasor(f) * 6.28318530718 : sin;

process = osc(hslider("frequence[midi:ctrl 14]", 440, 20, 10000, 0.1));