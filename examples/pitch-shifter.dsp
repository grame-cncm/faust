 //---------------------------- 
 // real time pitch shifter
 //---------------------------- 
 
 
transpose (w, x, s, sig)  =
	fdelay1s(d,sig)*fmin(d/x,1) + fdelay1s(d+w,sig)*(1-fmin(d/x,1)) 
	   	with {
			i = 1 - pow(2, s/12);
			d = i : (+ : +(w) : fmod(_,w)) ~ _;
	        };
 
pitchshifter = vgroup("Pitch Shifter", transpose(
									hslider("window (samples)", 1000, 50, 10000, 1),
									hslider("xfade (samples)", 10, 1, 10000, 1),
									hslider("shift (semitones) ", 0, -12, +12, 0.1)
								  )
				);
		

process = _ <: select2(checkbox("activate"), _, pitchshifter) <: _,_;
