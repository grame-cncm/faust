declare name "saxophony";
declare description "Nonlinear WaveGuide Saxophone";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "This class implements a hybrid digital waveguide instrument that can generate a variety of wind-like sounds.  It has also been referred to as the blowed string model. The waveguide section is essentially that of a string, with one rigid and one lossy termination.  The non-linear function is a reed table. The string can be blown at any point between the terminations, though just as with strings, it is impossible to excite the system at either end. If the excitation is placed at the string mid-point, the sound is that of a clarinet.  At points closer to the bridge, the sound is closer to that of a saxophone.  See Scavone (2002) for more details.";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Woodwinds.html";  

import("instruments.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

pressure = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Pressure
[2][tooltip:Breath pressure (a value between 0 and 1)]",1,0,1,0.01);
reedStiffness = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Reed_Stiffness
[2][tooltip:A value between 0 and 1]",0.3,0,1,0.01);
blowPosition = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Blow_Position
[2][tooltip:A value between 0 and 1]",0.5,0,1,0.01);
noiseGain = hslider("h:Physical_and_Nonlinearity/v:Physical_Parameters/Noise_Gain",0.05,0,1,0.01);

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
[4][tooltip:A value between 0 and 1]",0.1,0,1,0.01);
vibratoBegin = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.05,0,2,0.01);
vibratoAttack = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.3,0,2,0.01);
vibratoRelease = hslider("h:Envelopes_and_Vibrato/v:Vibrato_Parameters/Vibrato_Release 
[4][unit:s][tooltip:Vibrato release duration]",0.1,0,2,0.01);

envelopeAttack = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Attack 
[5][unit:s][tooltip:Envelope attack duration]",0.05,0,2,0.01);
envelopeRelease = hslider("h:Envelopes_and_Vibrato/v:Envelope_Parameters/Envelope_Release 
[5][unit:s][tooltip:Envelope release duration]",0.01,0,2,0.01);

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

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//reed table parameters
reedTableOffset = 0.7;
reedTableSlope = 0.1 + (0.4*reedStiffness);

//the reed function is declared in instruments.lib
reedTable = reed(reedTableOffset,reedTableSlope);

//Delay lines length in number of samples
fdel1 = (1-blowPosition) * (ma.SR/freq - 3);
fdel2 = (ma.SR/freq - 3)*blowPosition +1 ;

//Delay lines
delay1 = de.fdelay(4096,fdel1);
delay2 = de.fdelay(4096,fdel2);

//Breath pressure is controlled by an attack / sustain / release envelope (asr is declared in instruments.lib)
envelope = (0.55+pressure*0.3)*en.asr(pressure*envelopeAttack,100,pressure*envelopeRelease,gate);
breath = envelope + envelope*noiseGain*no.noise;

//envVibrato is decalred in instruments.lib
vibrato = vibratoGain*envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate)*osc(vibratoFreq);
breathPressure = breath + breath*vibratoGain*os.osc(vibratoFreq);

//Body filter is a one zero filter (declared in instruments.lib)
bodyFilter = *(gain) : oneZero1(b0,b1)
	with{
		gain = -0.95;
		b0 = 0.5;
		b1 = 0.5;	
	};

instrumentBody(delay1FeedBack,breathP) = delay1FeedBack <: -(delay2) <: 
	((breathP - _ <: breathP - _*reedTable) - delay1FeedBack),_;

process =
	(bodyFilter,breathPressure : instrumentBody) ~ 
	(delay1 : NLFM) : !,
	//Scaling Output and stereo
	*(gain) : stereo : instrReverb;

