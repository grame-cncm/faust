import("pm.lib");

// UI elements
freq = hslider("freq",440,50,1000,0.01);
gate = button("gate");
exPos = hslider("exPos",0.5,0,1,0.01);
p = hslider("pole",0.9,0,1,0.01)*0.1+0.9;

l = 320/freq; // coverts a length in meters into a frequency
impulsify = _ <: _,mem : - : >(0); // creates an impulse from a button

process = gate : impulsify : idealString(l,p,exPos) <: _,_;