//-----------------------------------------------
// 				karplus-strong
//-----------------------------------------------



// Excitator
//--------

upfront 	= _ <: -(mem) > 0.0; 
release(n) 	= + ~ (_ <: _, (_>0.0)/n : -) ;
trigger(n) 	= upfront : release(n) : >(0.0);

size 		= hslider("excitation (samples)", 128, 2, 512, 1);




// resonator
//-----------------

dur 		= hslider("duration (samples)", 128, 2, 512, 1); // : smooth(0.999);
att 		= hslider("attenuation", 0.1, 0, 1, 0.01);

resonator(d, a) = (+ <: (delay(4096, d-1) + delay(4096, d))/2.0) ~ *(1.0-a) ;

process =  
	  vgroup("noise generator", noise * hslider("level", 0.5, 0, 1, 0.1))
	: vgroup("excitator", *(button("play"): trigger(size)))
	: vgroup("resonator", resonator(dur, att));
