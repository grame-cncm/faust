declare name "Sitar";
declare description "WaveGuide Sitar";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "This instrument implements a sitar plucked string physical model based on the Karplus-Strong algorithm using a randomly modulated delay line.";

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

resonance = hslider("v:Physical_Parameters/Resonance
[2][tooltip:A value between 0 and 1]",0.7,0,1,0.01)*0.1;

//==================== SIGNAL PROCESSING ================

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//excitation envelope (adsr)
envelope = en.adsr(0.001,0.04,1,0.5,gate);

//the delay length is randomly modulated
targetDelay = ma.SR/freq;
delayLength = targetDelay*((1+(0.5*no.noise)) : si.smooth(0.9992));
delayLine = de.delay(4096,delayLength);

//the loop gain control the resonance duration
loopGain = 0.895 + resonance + (freq*0.0000005);
amGain = 0.1*gain;

//feedback filter is a one zero (declared in instruments.lib)
filter = oneZero1(b0,b1)
	with{
		zero = 0.01;
		b0 = 1/(1 + zero);
		b1 = -zero*b0;
	};

process = (*(loopGain) : filter + (envelope*no.noise*amGain))~delayLine : *(8) : 
stereo : instrReverb;

