declare name "blowBottle";
declare description "Blown Bottle Instrument";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "This object implements a helmholtz resonator (biquad filter) with a polynomial jet excitation (a la Cook).";

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

noiseGain = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Noise_Gain 
[2][tooltip:Breath noise gain (value between 0 and 1)]",0.5,0,1,0.01)*2;
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
vibratoBegin = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.05,0,2,0.01);
vibratoAttack = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.5,0,2,0.01);
vibratoRelease = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Release 
[4][unit:s][tooltip:Vibrato release duration]",0.01,0,2,0.01);

envelopeAttack = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Attack 
[5][unit:s][tooltip:Envelope attack duration]",0.01,0,2,0.01);
envelopeDecay = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Decay 
[5][unit:s][tooltip:Envelope decay duration]",0.01,0,2,0.01);
envelopeRelease = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Release 
[5][unit:s][tooltip:Envelope release duration]",0.5,0,2,0.01);


//==================== SIGNAL PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//attack - sustain - release envelope for nonlinearity (declared in instruments.lib)
envelopeMod = en.asr(nonLinAttack,100,envelopeRelease,gate);

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : si.smoo),envelopeMod,freq,
typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//botlle radius
bottleRadius = 0.999;

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

bandPassFilter = bandPass(freq,bottleRadius);

//----------------------- Algorithm implementation ----------------------------

//global envelope is of type attack - decay - sustain - release
envelopeG =  gain*en.adsr(gain*envelopeAttack,envelopeDecay,100,envelopeRelease,gate);

//pressure envelope is also ADSR
envelope = pressure*en.adsr(gain*0.02,0.01,100,gain*0.2,gate);

//vibrato
vibrato = os.osc(vibratoFreq)*vibratoGain*envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate)*os.osc(vibratoFreq);

//breat pressure
breathPressure = envelope + vibrato;

//breath noise
randPressure = noiseGain*no.noise*breathPressure ;

process = 
	//differential pressure
	(-(breathPressure) <: 
	((+(1))*randPressure : +(breathPressure)) - *(jetTable),_ : bandPassFilter,_)~NLFM : !,_ : 
	//signal scaling
	fi.dcblocker*envelopeG*0.5 : stereo : instrReverb;

