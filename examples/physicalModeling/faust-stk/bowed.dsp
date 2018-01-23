declare name "bowed";
declare description "Nonlinear WaveGuide Bowed Instrument";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A bowed string model, a la Smith (1986), after McIntyre, Schumacher, Woodhouse (1983).";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Bowed_Strings.html";

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

bowPosition = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Bow_Position
[2][tooltip:Bow position along the string (value between 0 and 1)]",0.7,0.01,1,0.01);
bowPressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Bow_Pressure
[2][tooltip:Bow pressure on the string (value between 0 and 1)]",0.75,0,1,0.01);

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
[4][tooltip:A value between 0 and 1]",0.01,0,1,0.01);
vibratoBegin = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.05,0,2,0.01);
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

//==================== SIGNAL PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//attack - sustain - release envelope for nonlinearity (declared in instruments.lib)
envelopeMod = en.asr(nonLinAttack,1,envelopeRelease,gate);

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM = nonLinearModulator((nonLinearity : si.smoo),envelopeMod,freq,
     typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//Parameters for the bow table
tableOffset =  0;
tableSlope = 5 - (4*bowPressure);

//the bow table is declared in instruments.lib
bowTable = bow(tableOffset,tableSlope);

//a attack - decay - sustain - release envelope is used 
envelope = en.adsr(gain*envelopeAttack,envelopeDecay,1, (1-gain)*envelopeRelease,gate);
maxVelocity = 0.03 + (0.2 * gain);

//Delay lines declaration and vibrato, the length of the two delay lines are evolving propotionally
betaRatio = 0.027236 + (0.2*bowPosition);
fdelneck = (ma.SR/freq-4)*(1 - betaRatio);
vibratoEnvelope = envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate);
vibrato = fdelneck + ((ma.SR/freq - 4)*vibratoGain*vibratoEnvelope*os.osc(vibratoFreq));
neckDelay = de.fdelay(4096,vibrato);
fdelbridge = (ma.SR/freq - 4)*betaRatio;
bridgeDelay = de.delay(4096,fdelbridge);

//Body Filter: a biquad filter with a normalized pick gain (declared in instruments.lib)
bodyFilter = bandPass(500,0.85);

//String Filter: a lowpass filter (declared in instruments.lib)
stringFilter = *(0.95) : -onePole(b0,a1)
	with{
		pole = 0.6 - (0.1*22050/ma.SR);
		gain = 0.95;
		b0 = 1-pole;
		a1 = -pole;	
	};

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//----------------------- Algorithm implementation ----------------------------

bowVelocity = envelope*maxVelocity;
instrumentBody(feedBckBridge) = (*(-1) <: +(feedBckBridge),_ : (bowVelocity-_ <: *(bowTable) <: _,_),_ : 
	_, + : +(feedBckBridge),_) ~ (neckDelay) : !,_;

process = (stringFilter : instrumentBody) ~ (bridgeDelay : NLFM) : bodyFilter(*(0.2)) : 
	_*gain*8 : stereo : instrReverb;

