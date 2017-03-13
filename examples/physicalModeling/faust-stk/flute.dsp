declare name "flute";
declare description "Nonlinear WaveGuide Flute";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple flute based on Smith algorythm: https://ccrma.stanford.edu/~jos/pasp/Flutes_Recorders_Pipe_Organs.html"; 

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01);
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]") : int;

pressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Pressure 
[2][tooltip:Breath pressure (value bewteen 0 and 1)]",0.9,0,1.5,0.01) : si.smoo;
breathAmp = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Noise Gain 
[2][tooltip:Breath noise gain (value between 0 and 1)]",0.1,0,1,0.01)/10;

typeModulation = nentry("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Modulation_Type 
[3][tooltip: 0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal;
2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod;
4=theta is modulated by a sine wave of frequency freq;]",0,0,4,1);
nonLinearity = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Nonlinearity 
[3][tooltip:Nonlinearity factor (value between 0 and 1)]",0,0,1,0.01);
frequencyMod = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Modulation_Frequency 
[3][unit:Hz][tooltip:Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)]",220,20,1000,0.1);
nonLinAttack = hslider("h:Physical_and_Nonlinearity/v:Nonlinear_Filter_Parameters/Nonlinearity Attack
[3][unit:s][Attack duration of the nonlinearity]",0.1,0,2,0.01);

vibratoFreq = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Freq 
[4][unit:Hz]",5,1,15,0.1);
vibratoGain = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Gain
[4][tooltip:A value between 0 and 1]",0.1,0,1,0.01);
vibratoBegin = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.1,0,2,0.01);
vibratoAttack = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.5,0,2,0.01);
vibratoRelease = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Release 
[4][unit:s][tooltip:Vibrato release duration]",0.2,0,2,0.01);

pressureEnvelope = checkbox("h:Envelopes_and_Vibrato/v:Pressure_Envelope_Parameters/Pressure_Env 
[5][unit:s][tooltip:Activate Pressure envelope]") : int;
env1Attack = hslider("h:Envelopes_and_Vibrato/v:Pressure_Envelope_Parameters/Press_Env_Attack 
[5][unit:s][tooltip:Pressure envelope attack duration]",0.05,0,2,0.01);
env1Decay = hslider("h:Envelopes_and_Vibrato/v:Pressure_Envelope_Parameters/Press_Env_Decay 
[5][unit:s][tooltip:Pressure envelope decay duration]",0.2,0,2,0.01);
env1Release = hslider("h:Envelopes_and_Vibrato/v:Pressure_Envelope_Parameters/Press_Env_Release 
[5][unit:s][tooltip:Pressure envelope release duration]",1,0,2,0.01);

env2Attack = hslider("h:Envelopes_and_Vibrato/v:Global_Envelope_Parameters/Glob_Env_Attack 
[6][unit:s][tooltip:Global envelope attack duration]",0.1,0,2,0.01);
env2Release = hslider("h:Envelopes_and_Vibrato/v:Global_Envelope_Parameters/Glob_Env_Release 
[6][unit:s][tooltip:Global envelope release duration]",0.1,0,2,0.01);

//==================== SIGNAL PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//attack - sustain - release envelope for nonlinearity (declared in instruments.lib)
envelopeMod = en.asr(nonLinAttack,100,0.1,gate);

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : si.smoo),envelopeMod,freq,
     typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//Loops feedbacks gains
feedBack1 = 0.4;
feedBack2 = 0.4;

//Delay Lines
embouchureDelayLength = (ma.SR/freq)/2-2;
boreDelayLength = ma.SR/freq-2;
embouchureDelay = de.fdelay(4096,embouchureDelayLength);
boreDelay = de.fdelay(4096,boreDelayLength);

//Polinomial
poly = _ <: _ - _*_*_;

//jet filter is a lowpass filter (declared in miscfilter.lib)
reflexionFilter = fi.lowpass(1,2000);

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//----------------------- Algorithm implementation ----------------------------

//Pressure envelope
env1 = en.adsr(env1Attack,env1Decay,90,env1Release,(gate | pressureEnvelope))*pressure*1.1; 

//Global envelope
env2 = en.asr(env2Attack,100,env2Release,gate)*0.5;

//Vibrato Envelope
vibratoEnvelope = envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate)*vibratoGain; 

vibrato = os.osc(vibratoFreq)*vibratoEnvelope;

breath = no.noise*env1;

flow = env1 + breath*breathAmp + vibrato;

//instrReverb is declared in instruments.lib
process = (_ <: (flow + *(feedBack1) : embouchureDelay : poly) + *(feedBack2) : reflexionFilter)~(boreDelay : NLFM) : *(env2)*gain : 
stereo : instrReverb;

