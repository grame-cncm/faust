declare name "UniBar";
declare description "Nonlinear Banded Waveguide Models";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "This instrument uses banded waveguide. For more information, see Essl, G. and Cook, P. Banded Waveguides: Towards Physical Modelling of Bar Percussion Instruments, Proceedings of the 1999 International Computer Music Conference.";

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",0.8,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

select = nentry("h:Physical_and_Nonlinearity/v:Physical_Parameters/Excitation_Selector
[2][tooltip:0=Bow; 1=Strike]",0,0,1,1);
integrationConstant = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Integration_Constant
[2][tooltip:A value between 0 and 1]",0,0,1,0.01);
baseGain = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Base_Gain
[2][tooltip:A value between 0 and 1]",1,0,1,0.01);
bowPressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Bow_Pressure
[2][tooltip:Bow pressure on the instrument (Value between 0 and 1)]",0.2,0,1,0.01);
bowPosition = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Bow_Position
[2][tooltip:Bow position on the instrument (Value between 0 and 1)]",0,0,1,0.01);

//==================== MODAL PARAMETERS ================

preset = 1;

nMode(1) = 4;

modes(1,0) = 1;
basegains(1,0) = pow(0.9,1);
excitation(1,0) = 1*gain/nMode(1);

modes(1,1) = 2.756;
basegains(1,1) = pow(0.9,2);
excitation(1,1) = 1*gain/nMode(1);

modes(1,2) = 5.404;
basegains(1,2) = pow(0.9,3);
excitation(1,2) = 1*gain/nMode(1);

modes(1,3) = 8.933;
basegains(1,3) = pow(0.9,4);
excitation(1,3) = 1*gain/nMode(1);

//==================== SIGNAL PROCESSING ================

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//the number of modes depends on the preset being used
nModes = nMode(preset);

//bow table parameters
tableOffset = 0;
tableSlope = 10 - (9*bowPressure);

delayLengthBase = ma.SR/freq;

//delay lengths in number of samples
delayLength(x) = delayLengthBase/modes(preset,x);

//delay lines
delayLine(x) = de.delay(4096,delayLength(x));

//Filter bank: bandpass filters (declared in instruments.lib)
radius = 1 - ma.PI*32/ma.SR;
bandPassFilter(x) = bandPass(freq*modes(preset,x),radius);

//Delay lines feedback for bow table lookup control
baseGainApp = 0.8999999999999999 + (0.1*baseGain);
velocityInputApp = integrationConstant;
velocityInput = velocityInputApp + _*baseGainApp,par(i,(nModes-1),(_*baseGainApp)) :> +;

//Bow velocity is controlled by an ADSR envelope
maxVelocity = 0.03 + 0.1*gain;
bowVelocity = maxVelocity*en.adsr(0.02,0.005,0.9,0.01,gate);

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(delayLengthBase);

//----------------------- Algorithm implementation ----------------------------

//Bow table lookup (bow is decalred in instruments.lib)
bowing = bowVelocity - velocityInput <: *(bow(tableOffset,tableSlope)) : /(nModes);

//One resonance
resonance(x) = + : + (excitation(preset,x)*select) : delayLine(x) : *(basegains(preset,x)) : bandPassFilter(x);

process =
		//Bowed Excitation
		(bowing*((select-1)*-1) <:
		//nModes resonances with nModes feedbacks for bow table look-up 
		par(i,nModes,(resonance(i)~_)))~par(i,nModes,_) :> + : 
		//Signal Scaling and stereo
		*(14) : stereo : instrReverb;
