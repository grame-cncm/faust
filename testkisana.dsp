declare name  	"myKisana";
declare author  "Yann Orlarey";

//Modifications GRAME July 2015

/* ========= DESCRITPION =============

- Kisana : 3-loops string instrument (based on Karplus-Strong)
- Head = Silence
- Tilt = High frequencies 
- Front = High + Medium frequencies
- Bottom = High + Medium + Low frequencies
- Left = Minimum brightness
- Right = Maximum birghtness
- Front = Long notes
- Back = Short notes

*/

import("stdfaust.lib");

KEY = 60;	// basic midi key
NCY = 15; 	// note cycle length
CCY = 15;	// control cycle length
BPS = 360;	// general tempo (ba.beat per sec)

process = kisana;    

//-------------------------------kisana----------------------------------
// USAGE:  kisana : _,_;
// 		3-loops string instrument
//-----------------------------------------------------------------------

kisana = vgroup("MyKisana", harpe(C,11,48), harpe(C,11,60), (harpe(C,11,72) : *(1.5), *(1.5)) 
	:>*(l),*(l))
	with {
		l = -20 : ba.db2linear;//hslider("[1]Volume",-20, -60, 0, 0.01) : ba.db2linear;
		C = hslider("[2]Brightness[acc:0 1 -10 0 10]", 0.2, 0, 1, 0.01) : ba.automat(BPS, CCY, 0.0);
	};

//----------------------------------Harpe--------------------------------
// USAGE:  harpe(C,10,60) : _,_;
//		C is the filter coefficient 0..1
// 		Build a N (10) strings harpe using a pentatonic scale 
//		based on midi key b (60)
//		Each string is triggered by a specific
//		position of the "hand"
//-----------------------------------------------------------------------
harpe(C,N,b) = 	hand(b) <: par(i, N, position(i+1)
							: string(C,Penta(b).degree2Hz(i), att, lvl)
							: pan((i+0.5)/N) )
				 	:> _,_
	with {
		att  = hslider("[3]Resonance[acc:2 1 -10 0 12]", 4, 0.1, 10, 0.01); 
		hand(48) = vslider("h:[1]Instrument Hands/1 (Note %b)[unit:pk]", 0, 0, N, 1) : int : ba.automat(120, CCY, 0.0);
		hand(60) = vslider("h:[1]Instrument Hands/2 (Note %b)[unit:pk]", 2, 0, N, 1) : int : ba.automat(240, CCY, 0.0);
		hand(72) = vslider("h:[1]Instrument Hands/3 (Note %b)[unit:pk]", 4, 0, N, 1) : int : ba.automat(480, CCY, 0.0);
		//lvl  = vslider("h:loop/level", 0, 0, 6, 1) : int : ba.automat(BPS, CCY, 0.0) : -(6) : ba.db2linear; 
		lvl = 1;
		pan(p) = _ <: *(sqrt(1-p)), *(sqrt(p));
		position(a,x) = abs(x - a) < 0.5;
	};

//----------------------------------Penta-------------------------------
// Pentatonic scale with degree to midi and degree to Hz conversion
// USAGE: Penta(60).degree2midi(3) ==> 67 midikey
//        Penta(60).degree2Hz(4)   ==> 440 Hz
//-----------------------------------------------------------------------

Penta(key) = environment {

	A4Hz = 440; 
	
	degree2midi(0) = key+0;
	degree2midi(1) = key+2;
	degree2midi(2) = key+4;
	degree2midi(3) = key+7;
	degree2midi(4) = key+9;
	degree2midi(d) = degree2midi(d-5)+12;
	
	degree2Hz(d) = A4Hz*semiton(degree2midi(d)-69) with { semiton(n) = 2.0^(n/12.0); };

}; 
 
//----------------------------------String-------------------------------
// A karplus-strong string.
//
// USAGE: string(440Hz, 4s, 1.0, button("play"))
// or	  button("play") : string(440Hz, 4s, 1.0)
//-----------------------------------------------------------------------

string(coef, freq, t60, level, trig) = no.noise*level
							: *(trig : trigger(freq2samples(freq)))
							: resonator(freq2samples(freq), att)
	with {
		resonator(d,a)	= (+ : @(d-1)) ~ (average : *(a));
		average(x)		= (x*(1+coef)+x'*(1-coef))/2;
		trigger(n) 		= upfront : + ~ decay(n) : >(0.0);
		upfront(x) 		= (x-x') > 0.0;
		decay(n,x)		= x - (x>0.0)/n;
		freq2samples(f) = 44100.0/f;
		att 			= pow(0.001,1.0/(freq*t60)); // attenuation coefficient
		random  		= +(12345)~*(1103515245);
		noise   		= random/2147483647.0;
	};

   
