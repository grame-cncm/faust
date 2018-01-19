declare name "clarinet";
declare description "Nonlinear WaveGuide Clarinet";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple clarinet physical model, as discussed by Smith (1986), McIntyre, Schumacher, Woodhouse (1983), and others.";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Woodwinds.html";

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

reedStiffness = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Reed_Stiffness 
[2][tooltip:Reed stiffness (value between 0 and 1)]",0.5,0,1,0.01);
noiseGain = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Noise_Gain 
[2][tooltip:Breath noise gain (value between 0 and 1)]",0,0,1,0.01);
pressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Pressure 
[2][tooltip:Breath pressure (value bewteen 0 and 1)]",1,0,1,0.01);

typeModulation = nentry("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Modulation_Type 
[3][tooltip: 0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal;
2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod;
4=theta is modulated by a sine wave of frequency freq;]",0,0,4,1);
nonLinearity = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Nonlinearity 
[3][tooltip:Nonlinearity factor (value between 0 and 1)]",0,0,1,0.01);
frequencyMod = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Modulation_Frequency 
[3][unit:Hz][tooltip:Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)]",220,20,1000,0.1);
nonLinAttack = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Nonlinearity_Attack
[3][unit:s][Attack duration of the nonlinearity]",0.1,0,2,0.01);

vibratoFreq = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Freq 
[4][unit:Hz]",5,1,15,0.1);
vibratoGain = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Gain
[4][tooltip:A value between 0 and 1]",0.1,0,1,0.01);
vibratoAttack = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.5,0,2,0.01);
vibratoRelease = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Release 
[4][unit:s][tooltip:Vibrato release duration]",0.01,0,2,0.01);

envelopeAttack = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Attack 
[5][unit:s][tooltip:Envelope attack duration]",0.01,0,2,0.01);
envelopeDecay = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Decay 
[5][unit:s][tooltip:Envelope decay duration]",0.05,0,2,0.01);
envelopeRelease = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Release 
[5][unit:s][tooltip:Envelope release duration]",0.1,0,2,0.01);

//==================== SIGNAL PROCESSING ======================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//attack - sustain - release envelope for nonlinearity (declared in instruments.lib)
envelopeMod = en.asr(nonLinAttack,1,envelopeRelease,gate);

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : si.smoo),envelopeMod,freq,
     typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//reed table parameters
reedTableOffset = 0.7;
reedTableSlope = -0.44 + (0.26*reedStiffness);

//the reed function is declared in instruments.lib
reedTable = reed(reedTableOffset,reedTableSlope);

//delay line with a length adapted in function of the order of nonlinear filter
delayLength = ma.SR/freq*0.5 - 1.5 - (nlfOrder*nonLinearity)*(typeModulation < 2);
delayLine = de.fdelay(4096,delayLength);

//one zero filter used as a allpass: pole is set to -1
filter = oneZero0(0.5,0.5);

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//----------------------- Algorithm implementation ----------------------------

//Breath pressure + vibrato + breath noise + envelope (Attack / Decay / Sustain / Release)
envelope = en.adsr(envelopeAttack,envelopeDecay,1,envelopeRelease,gate)*pressure*0.9;

vibrato = os.osc(vibratoFreq)*vibratoGain*
	envVibrato(0.1*2*vibratoAttack,0.9*2*vibratoAttack,100,vibratoRelease,gate);
breath = envelope + envelope*no.noise*noiseGain;
breathPressure = breath + breath*vibrato;

process =
	//Commuted Loss Filtering
	(_,(breathPressure <: _,_) : (filter*-0.95 - _ <: 
	
	//Non-Linear Scattering
	*(reedTable)) + _) ~ 
	
	//Delay with Feedback
	(delayLine : NLFM) : 
	
	//scaling and stereo
	*(gain)*1.5 : stereo : instrReverb; 

