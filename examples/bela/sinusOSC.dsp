// Pour tester OSC.
import("stdfaust.lib");


phasor(f)   = f/ma.SR : (+,1.0:fmod) ~ _ ;
osc(f)      = phasor(f) * 6.28318530718 : sin;

process = osc(hslider("frequence", 440, 20, 10000, 0.1));