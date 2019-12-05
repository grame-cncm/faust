
process = /*button("play") :*/ string(0, hslider("freq", 440, 100, 8000,1), 4, 1) <: _,_;



//----------------------------------String-------------------------------
// A karplus-strong string.
//
// USAGE: string(440Hz, 4s, 1.0, button("play"))
// or	  button("play") : string(440Hz, 4s, 1.0)
//-----------------------------------------------------------------------

string(coef, freq, t60, level, trig) = /*noise*trig :*/ resonator(80, 1)
	with {
		resonator(d,a)	= (+ : @(d-1)) ~ (average : *(a));
		average(x)		= x+x':*(0.5); //(x*(1+coef)+x'*(1-coef))/2;
		trigger(n) 		= upfront : + ~ decay(n) : >(0.0);
		upfront(x) 		= (x-x') > 0.0;
		decay(n,x)		= x - (x>0.0)/n;
		freq2samples(f) = 44100.0/f;
		att 			= pow(0.001,1.0/(freq*t60)); // attenuation coefficient
		random  		= +(12345)~*(1103515245);
		noise   		= random/2147483647.0;
	};

   
