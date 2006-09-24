declare name 		"karplus32";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// 				karplus-strong
//		with 32 resonators in parallel
//-----------------------------------------------

import("music.lib");


// Excitator
//--------

upfront(x) 	= (x-x') > 0.0;
decay(n,x)	= x - (x>0)/n;
release(n)	= + ~ decay(n);
trigger(n) 	= upfront : release(n) : >(0.0) : +(leak);
leak 		= 1.0/65536.0;

size 		= hslider("excitation (samples)", 128, 2, 512, 1);




// Resonator
//-----------------

dur 		= hslider("duration (samples)", 128, 2, 512, 1);
att 		= hslider("attenuation", 0.1, 0, 1, 0.01);
average(x)	= (x+x')/2;

resonator(d, a) = (+ : delay(4096, d-1.5)) ~ (average : *(1.0-a)) ;


// Polyphony
//-----------------

detune 		= hslider("detune", 32, 0, 512, 1);
polyphony 	= hslider("polyphony", 1, 0, 32, 1);



output 		= hslider("output volume", 0.5, 0, 1, 0.1);


process =  vgroup("karplus32",
	 		   	vgroup("noise generator", noise * hslider("level", 0.5, 0, 1, 0.1))
				 : vgroup("excitator", *(button("play"): trigger(size)))
				<: vgroup("resonator x32", par(i,32, resonator(dur+i*detune, att) * (polyphony > i)))
				:> *(output),*(output)
			);
