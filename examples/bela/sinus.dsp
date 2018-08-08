import("stdfaust.lib");


phasor(f)   = f/ma.SR : (+,1.0:fmod) ~ _ ;
osc(f)      = phasor(f) * 6.28318530718 : sin;

process = osc(hslider("frequence[BELA: ANALOG_0]", 440, 20, 10000, 0.1));
//hslider("frequence[midi:ctrl 14]", 0, 0, 1, 0.01);