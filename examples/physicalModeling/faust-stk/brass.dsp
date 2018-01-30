declare name "brass";
declare description "WaveGuide Brass instrument from STK";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple brass instrument waveguide model, a la Cook (TBone, HosePlayer).";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Brasses.html"; 

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

pressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Pressure
[2][tooltip:A value between 0 and 1]",1,0.01,1,0.01);
lipTension = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Lip_Tension
[2][tooltip:A value between 0 and 1]",0.780,0.01,1,0.001);
slideLength = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Slide_Length
[2][tooltip:A value between 0 and 1]",0.041,0.01,1,0.001);

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
[4][unit:Hz]",6,1,15,0.1);
vibratoGain = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Gain
[4][tooltip:A value between 0 and 1]",0.05,0,1,0.01);
vibratoBegin = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.05,0,2,0.01);
vibratoAttack = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.5,0,2,0.01);
vibratoRelease = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Release 
[4][unit:s][tooltip:Vibrato release duration]",0.1,0,2,0.01);

envelopeAttack = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Attack 
[5][unit:s][tooltip:Envelope attack duration]",0.005,0,2,0.01);
envelopeDecay = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Decay 
[5][unit:s][tooltip:Envelope decay duration]",0.001,0,2,0.01);
envelopeRelease = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Release 
[5][unit:s][tooltip:Envelope release duration]",0.07,0,2,0.01);

//==================== SIGNAL PROCESSING ================

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

//lips are simulated by a biquad filter whose output is squared and hard-clipped, bandPassH and saturationPos are declared in instruments.lib
lipFilterFrequency = freq*pow(4,(2*lipTension)-1);
lipFilter = *(0.03) : bandPassH(lipFilterFrequency,0.997) <: * : saturationPos;

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//delay times in number of samples
slideTarget = ((ma.SR/freq)*2 + 3)*(0.5 + slideLength);
boreDelay = de.fdelay(4096,slideTarget);

//----------------------- Algorithm implementation ----------------------------

//vibrato
vibrato = vibratoGain*os.osc(vibratoFreq)*envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate);

//envelope (Attack / Decay / Sustain / Release), breath pressure and vibrato
breathPressure = pressure*en.adsr(envelopeAttack,envelopeDecay,1,envelopeRelease,gate) + vibrato;
mouthPressure = 0.3*breathPressure;

//scale the delay feedback
borePressure = *(0.85);

//differencial presure
deltaPressure = mouthPressure - _;

process = (borePressure <: deltaPressure,_ : 
	  (lipFilter <: *(mouthPressure),(1-_)),_ : _, * :> + :
	  fi.dcblocker) ~ (boreDelay : NLFM) :
	  *(gain)*4 : stereo : instrReverb;

