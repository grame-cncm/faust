declare name "Nonlinear WaveGuide Flute from STK";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple flute physical model, as discussed by Karjalainen, Smith, Waryznyk, etc.  The jet model uses a polynomial, a la Cook.";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Flutes_Recorders_Pipe_Organs.html"; 

import("music.lib");
import("instrument.lib");

//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = nentry("h:Basic Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",1,0,1,0.01); 
gate = button("h:Basic Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

embouchureAjust = hslider("h:Physical and Nonlinearity/v:Physical Parameters/Embouchure Ajust
[2][tooltip:A value between 0 and 1]",0.5,0,1,0.01);
noiseGain = hslider("h:Physical and Nonlinearity/v:Physical Parameters/Noise Gain
[2][tooltip:A value between 0 and 1]",0.03,0,1,0.01);
pressure = hslider("h:Physical and Nonlinearity/v:Physical Parameters/Pressure
[2][tooltip:Breath pressure (value between 0 and 1)]",1,0,1,0.01);

typeModulation = nentry("h:Physical and Nonlinearity/v:Nonlinear Filter Parameters/Modulation Type 
[3][tooltip: 0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal;
2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod;
4=theta is modulated by a sine wave of frequency freq;]",0,0,4,1);
nonLinearity = hslider("h:Physical and Nonlinearity/v:Nonlinear Filter Parameters/Nonlinearity 
[3][tooltip:Nonlinearity factor (value between 0 and 1)]",0,0,1,0.01);
frequencyMod = hslider("h:Physical and Nonlinearity/v:Nonlinear Filter Parameters/Modulation Frequency 
[3][unit:Hz][tooltip:Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)]",220,20,1000,0.1);
nonLinAttack = hslider("h:Physical and Nonlinearity/v:Nonlinear Filter Parameters/Nonlinearity Attack
[3][unit:s][Attack duration of the nonlinearity]",0.1,0,2,0.01);

vibratoFreq = hslider("h:Envelopes and Vibrato/v:Vibrato Parameters/Vibrato Freq 
[4][unit:Hz]",6,1,15,0.1);
vibratoGain = hslider("h:Envelopes and Vibrato/v:Vibrato Parameters/Vibrato Gain
[4][tooltip:A value between 0 and 1]",0.05,0,1,0.01);
vibratoBegin = hslider("h:Envelopes and Vibrato/v:Vibrato Parameters/Vibrato Begin
[4][unit:s][tooltip:Vibrato silence duration before attack]",0.05,0,2,0.01);
vibratoAttack = hslider("h:Envelopes and Vibrato/v:Vibrato Parameters/Vibrato Attack 
[4][unit:s][tooltip:Vibrato attack duration]",0.5,0,2,0.01);
vibratoRelease = hslider("h:Envelopes and Vibrato/v:Vibrato Parameters/Vibrato Release 
[4][unit:s][tooltip:Vibrato release duration]",0.1,0,2,0.01);

envelopeAttack = hslider("h:Envelopes and Vibrato/v:Envelope Parameters/Envelope Attack 
[5][unit:s][tooltip:Envelope attack duration]",0.03,0,2,0.01);
envelopeDecay = hslider("h:Envelopes and Vibrato/v:Envelope Parameters/Envelope Decay 
[5][unit:s][tooltip:Envelope decay duration]",0.01,0,2,0.01);
envelopeRelease = hslider("h:Envelopes and Vibrato/v:Envelope Parameters/Envelope Release 
[5][unit:s][tooltip:Envelope release duration]",0.3,0,2,0.01);

//==================== SIGNAL PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in filter.lib

//nonlinear filter order
nlfOrder = 6; 

//attack - sustain - release envelope for nonlinearity (declared in instrument.lib)
envelopeMod = asr(nonLinAttack,100,envelopeRelease,gate);

//nonLinearModultor is declared in instrument.lib, it adapts allpassnn from filter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : smooth(0.999)),envelopeMod,freq,
     typeModulation,(frequencyMod : smooth(0.999)),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

jetReflexion = 0.5;
jetRatio = 0.08 + (0.48*embouchureAjust);
endReflexion = 0.5;

//Delay lines lengths in number of samples
jetDelayLength = (SR/freq)*jetRatio;
boreDelayLength = SR/freq;
filterPole = 0.7 - (0.1*22050/SR);

//One Pole Filter (declared in instrument.lib)
onePoleFilter = _*gain : onePole(b0,a1)
	with{
		gain = -1;
		pole = 0.7 - (0.1*22050/SR);
		b0 = 1 - pole;
		a1 = -pole;
	};

//stereoizer is declared in instrument.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(SR/freq);

//----------------------- Algorithm implementation ----------------------------

//the vibrato amplitude is controled by an envelope generator (declared in instrument.lib)
vibrato = vibratoGain*envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate)*osc(vibratoFreq);

//Breath pressure is controlled by an Attack / Decay / Sustain / Release envelope
envelopeBreath = pressure*adsr(pressure*envelopeAttack,envelopeDecay,80,envelopeRelease,gate);
breathPressure = envelopeBreath + envelopeBreath*(noiseGain*noise + vibrato);

//delay lines
jetDelay = fdelay(4096,jetDelayLength);
boreDelay = fdelay(4096,boreDelayLength);

//reflexion filter is a one pole and a dcblocker
reflexionFilters = onePoleFilter : dcblocker;

process =
	(reflexionFilters <: 
	//Differential Pressure
	((breathPressure - _*jetReflexion) : 
	jetDelay : jetTable) + (_*endReflexion)) ~ (boreDelay : NLFM) : 
	//output scaling and stereo signal
	*(0.3*gain) : stereo : hgroup("Reverb[6]",component("freeverb.dsp")); 