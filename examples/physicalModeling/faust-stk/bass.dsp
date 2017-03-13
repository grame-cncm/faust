declare name "Bass";
declare description "Nonlinear WaveGuide Acoustic Bass";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",120,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

touchLength = hslider("v:Physical_Parameters/Touch_Length
[2][tooltip:A value between 0 and 1]",0.15,0,1,0.01)*2;

typeModulation = nentry("v:Nonlinear_Filter_Parameters/Modulation_Type 
[3][tooltip: 0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal;
2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod;
4=theta is modulated by a sine wave of frequency freq;]",0,0,4,1);
nonLinearity = hslider("v:Nonlinear_Filter_Parameters/Nonlinearity 
[3][tooltip:Nonlinearity factor (value between 0 and 1)]",0,0,1,0.01);
frequencyMod = hslider("v:Nonlinear_Filter_Parameters/Modulation_Frequency 
[3][unit:Hz][tooltip:Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)]",220,20,1000,0.1);

//==================== SIGNAL PROCESSING ======================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : si.smoo),1,freq,
     typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//delay length in number of samples
delayLength = float(ma.SR)/freq;

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(delayLength);

//string excitation
excitation = asympT60(-0.5,-0.985,0.02,gate),no.noise*asympT60(gain,0,touchLength,gate) : 
	   onePoleSwep : excitationFilter : excitationFilter
	   with{
		//the exitation filter is a one pole filter (declared in instruments.lib)
		excitationFilter = onePole(0.035,-0.965);
	   };

//the bodyfilter is a bandpass filter (declared in instruments.lib)
bodyFilter = bandPass(108,0.997);

//the reflexion filter is pole zero filter (declared in instruments.lib) whose coefficients are 
//modulated in function of the tone being played
reflexionFilter = poleZero(b0,b1,a1)
	   with{
		//filter coefficients are stored in a C++ function
		loopFilterb0 = ffunction(float getValueBassLoopFilterb0(float), <bass.h>,"");
		loopFilterb1 = ffunction(float getValueBassLoopFilterb1(float), <bass.h>,"");
		loopFiltera1 = ffunction(float getValueBassLoopFiltera1(float), <bass.h>,"");
		freqToNoteNumber = (log - log(440))/log(2)*12 + 69 + 0.5 : int;
		freqn = freq : freqToNoteNumber;
		b0 = loopFilterb0(freqn);
		b1 = loopFilterb1(freqn);
		a1 = loopFiltera1(freqn);
	   };

delayLine = asympT60(0,delayLength,0.01,gate),_ : de.fdelay(4096);

//the resonance duration is different whether a note-on signal is sent or not 
resonanceGain = gate + (gate < 1 <: *(asympT60(1,0.9,0.05)));

process = excitation : 
	(+)~(delayLine : NLFM : reflexionFilter*resonanceGain) <: 
	bodyFilter*1.5 + *(0.5) : *(4) : stereo : instrReverb;

