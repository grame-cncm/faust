import("stdfaust.lib");

declare name  	"basicString";
declare author  "Grame";

// UI elements
freq = hslider("freq",440,50,1000,0.01);
gate = button("gate");
exPos = hslider("exPos",0.5,0,1,0.01);
p = hslider("pole",0.9,0,1,0.01)*0.1+0.9;

l = 320/freq; // converts a length in meters into a frequency

process = gate : ba.impulsify : pm.idealString(l,p,exPos) <: _,_;
