import("effect.lib"); 

process = par(i,2, crybaby(wah)) with {
   wah = hslider("[1] AhAh",0.6,0,1,0.01) : automat(360, 10, 0.0);
};
