import("stdfaust.lib");

// These are now in a separate file ./effects.dsp
// echo = echog(component("echo.dsp")); // ./echo.dsp
// flanger = flg(component("flanger.dsp")); // ./flanger.dsp
// chorus = chg(component("chorus.dsp")); // ./chorus.dsp
// reverb = rg(component("freeverb.dsp"));

process = main <: _,_; // Now separate: : echo : flanger : chorus : reverb;
main = (signal + extInput : filters : *(ampScaling)) ~ _;
signal = oscs + noise * noiseOff * namp;

ampScaling = envelopeAmp * masterVolume; // masterVolume is redundant but easier to find
oscs = par(i,3,(oscamp(i+1)*osc(i+1))) :> _;

controlSelect(1) = osc1(vrockerred); // ("[0] use as LFO"));
octaveSelect(1) = osc1(vslider("[1] Octave1 [midi:ctrl 23] [style:knob]",1,0,5,1):int); // LO, 32', 16', 8', 4', 2'
// Osc1 detunes like Osc2 and Osc3 (unlike in the Minimoog where it would be an expensive extra knob):
detuneOctaves(1) = osc1(vslider("[2] DeTuning1 [units:Octaves] [midi:ctrl 24] [style:knob]",0.0,-1.0,1.0,0.001));
waveSelect(1) = osc1(vslider("[3] Waveform1 [midi:ctrl 25] [style:knob]",5,0,5,1):int);
amp1Enable = mr1(vslider("[1] On [midi:ctrl 12] [style:knob] [color:blue]",1,0,1,1));
oscamp(1) = mr1(vslider("[0] Osc1 Amp [midi:ctrl 26] [style:knob]",0.5,0.0,1.0,0.001)) * amp1Enable;

eei = mr2(vslider("[1] On [midi:ctrl 13] [style:knob] [color:blue]",0,0,1,1)); // External input = MAIN OUTPUT when "off"
sei = mr2(vslider("[0] Ext Input [midi:ctrl 27] [style: knob]",0,0,1.0,0.001));
extInput(fb,extSig) = fb,extSig : select2(eei) : *(sei) : extClipLED;
extClipLED = _ <: _, (abs : >(0.95) : mr2(vbargraph("[2] Ext Input Clip [style:led]",0,1)):!);
keycLED = attach(mr2(vbargraph("[3] Keyboard Ctl [style:led]",0,1)));

controlSelect(2) = osc2(vrockerred); // ("[0] use as LFO"));
octaveSelect(2) = osc2(vslider("[1] Octave2 [midi:ctrl 28] [style:knob]",1,0,5,1):int); // LO, 32', 16', 8', 4', 2'
detuneOctaves(2) = osc2(vslider("[2] DeTuning2 [units:Octaves] [midi:ctrl 29] [style:knob]",0.41667,-1.0,1.0,0.001));
waveSelect(2) = osc2(vslider("[3] Waveform2 [midi:ctrl 30] [style:knob]",5,0,5,1):int);
amp2Enable = mr3(vslider("[1] On [midi:ctrl 14] [style:knob] [color:blue]",1,0,1,1));
oscamp(2) = mr3(vslider("[0] Osc2 Amp [midi:ctrl 31] [style:knob]",0.5,0.0,1.0,0.001)) * amp2Enable;

noise = select2(ntype,no.noise,10.0*no.pink_noise); // pink noise needs some "make-up gain"
namp = mr4(vslider("[0] Noise Amp [midi:ctrl 32] [style: knob]",0.0,0.0,1.0,0.001));
noiseOff = mr4cbg(vslider("[0] On [midi:ctrl 15] [style:knob] [color:blue]",0,0,1,1));
ntype = mr4cbg(vslider("[1] White/Pink [midi:ctrl 16] [tooltip: Choose either White or Pink Noise] [style: knob] [color:blue]",1,0,1,1));

controlSelect(3) = osc3(vrockerred); // ("[0] use as LFO"));
octaveSelect(3) = osc3(vslider("[1] Octave3 [midi:ctrl 33] [style:knob]",0,0,5,1):int); // LO, 32', 16', 8', 4', 2'
detuneOctaves(3) = osc3(vslider("[2] DeTuning3 [units:Octaves] [midi:ctrl 34] [style:knob]",0.3,-1.0,1.0,0.001));
waveSelect(3) = osc3(vslider("[3] Waveform3 [midi:ctrl 35] [style:knob]",0,0,5,1):int);
amp3Enable = mr5(vslider("[1] On [midi:ctrl 17] [style:knob] [color:blue]",0,0,1,1));
oscamp(3) = mr5(vslider("[0] Osc3 Amp [midi:ctrl 36] [style:knob]",0.5,0.0,1.0,0.001)) * amp3Enable;

waveforms(i) = (tri(i), bent(i), saw(i), sq(i), ptm(i), ptn(i));

// compute oscillator frequency scale factor, staying in lg(Hz) as much as possible:
modWheelShift = 1.5*modWheel; // Manual says 0 to 1.5 octaves
modulationCenterShift = 0; // Leave this off until triangle-wave modulation is debugged
modulationShift = select2(oscModEnable, 0.0,
		          modWheelShift * ( modulationCenterShift + (1.0-modulationCenterShift) * oscNoiseModulation ));
octaveShift(i) = -2+int(octaveSelect(i));
osc3FixedFreq = 369.994; // F# a tritone above middle C
keyFreqGlidedMaybe = select2(osc3Control,osc3FixedFreq,keyFreqGlided);
keyFreqModulatedShifted(3) = keyFreqGlidedMaybe; // osc3 not allowed to FM itself
keyFreqModulatedShifted(i) = keyFreqGlided * pow(2.0, modulationShift); // i=1,2

// When disconnected from the keyboard, Osc3 can detune 3 octaves up or down (Pat video):
detuneBoost(3) = select2(osc3Control,3.0,1.0);
detuneBoost(i) = 1.0; // i=1,2
detuneOctavesFinal(i) = detuneOctaves(i)*detuneBoost(i);

fBase(i) = keyFreqModulatedShifted(i) * pow(2.0, (masterTuneOctaves+octaveShift(i)+detuneOctavesFinal(i)))
	       : si.smooth(ba.tau2pole(0.016));
fLFOBase(i) = 3.0 * pow(2.0, detuneOctavesFinal(i)); // used when osc3 (only) is in LFO mode
lfoMode(i) = (octaveSelect(i) == 0);
f(i) = select2(lfoMode(i), fBase(i), fLFOBase(i)); // lowest range setting is LFO mode for any osc

// i is 1-based:
osc(i) = ba.selectn(6, int(waveSelect(i)), tri(i), bent(i), saw(i), sq(i), ptm(i), ptn(i));
tri(i) = select2(lfoMode(i),
          os.triangle(f(i)),
          os.lf_triangle(f(i)));
bent(i) = 0.5*tri(i) + 0.5*saw(i); // from Minimoog manual
saw(i) = select2(lfoMode(i),
          os.sawtooth(f(i)),
          os.lf_saw(f(i)));
sq(i) = select2(lfoMode(i),
          os.square(f(i)),
          os.lf_squarewave(f(i)));
ptm(i) = select2(lfoMode(i), // Note: a Duty knob would be better than these two, or in addition
          os.pulsetrain(f(i),0.25),
          lf_pulsetrain(f(i),0.25));
ptn(i) = select2(lfoMode(i),
          os.pulsetrain(f(i),0.125),
          lf_pulsetrain(f(i),0.125));

// Soon to appear in oscillators.lib:
lf_pulsetrain(freq,duty) = 2.0*os.lf_pulsetrainpos(freq,duty) - 1.0;

import("layout2.dsp"); // follows the Mini Moog front panel: ./layout2.dsp

filters = ba.bypass1(bp,vcf); // BYPASS WILL GO AWAY (I think you just open it up all the way to bypass):
bp = 0; // VCF is always on
fcLgHz = vcf1(vslider("[1] Corner Freq [unit:Log2(Hz)]
		  [tooltip: Corner resonance frequency in Log2(Hertz)]
		  [style: knob]
                  [midi:ctrl 74]", // Frequency Cutoff (aka Brightness )
		  10.6, log(40.0)/log(2), log(20000.0)/log(2), 0.000001)) // 9 octaves (from Minimoog manual)
		  //p: 40, 30, 80, 0.01))
		  //p: : ba.pianokey2hz
		  : si.smooth(ba.tau2pole(0.016));
res = vcf1(vslider("[2] Corner Resonance [midi:ctrl 37] [tooltip: Resonance Q at VCF corner frequency (0 to 1)]
		  [style: knob]",
		  0.7, 0, 1, 0.01));

vcfKeyRange = vcf1cbg(vslider("[2] Kbd Ctl [midi:ctrl 38] [tooltip: Keyboard tracking of VCF corner-frequency (0=none, 1=full)]
		  [style: knob]",
		  1, 0, 1, 0.001)); // was in mr2
vcfModEnable = vcf1cbg(vslider("[1] Filter Mod. [midi:ctrl 19] [color:red] [style:knob] [tooltip: Filter Modulation => Route Modulation Mix output to VCF frequency]",1,0,1,1));
// Note that VCF has three sources of corner-frequency setting that are added together:
// - Corner Freq knob (40 Hz to 20 kHz)
// - VCF Contour envelope (0 to 4 octaves)
// - Injection 32 of Modulation Mix (0 to 1.5 octaves)
// Manual says maximum vcf sweep spans 0 to 4 octaves:
// Original Knob went to 10, but we're going to 4 so we can say the knob is in "octaves" units:
vcfContourAmountOctaves = vcf1(vslider("[3] Amount of Contour (octaves) [midi:ctrl 39] [style: knob]", 1.2, 0, 4.0, 0.001));
vcfContourOctaves = vcfContourAmountOctaves * envelopeVCF; // in octaves
// We are assuming that the modulation-mix range for the VCF freq is 1.5 octaves like it is for oscs 1 and 2:
vcfModMixModulationOctaves = select2(vcfModEnable, 0, (1.5 * oscNoiseModulation * modWheel)); // octaves
vcfModulationOctaves = vcfModMixModulationOctaves + vcfContourOctaves;
keyFreqLogHzGlided = log(keyFreqGlided)/log(2.0); // FIXME: Start w freqLogHz not freq so we don't need exp(log()) here
keyShiftOctaves = keyFreqLogHzGlided - log(261.625565)/log(2.0); // FIXME: ARBITRARILY centering on middle C - check device
vcfKeyShiftOctaves = vcfKeyRange * keyShiftOctaves;
modulatedFcLgHz = fcLgHz + vcfModulationOctaves + vcfKeyShiftOctaves;

fc = min((0.5*ma.SR), pow(2.0,modulatedFcLgHz));
vcf = ve.moog_vcf_2bn(res,fc);

// Attack, Decay, and Sustain ranges are set according to the Minimoog manual:
attT60VCF = 0.001 * vcf2(vslider("[0] AttackF [midi:ctrl 40] [tooltip: Attack Time] [unit:ms] [style: knob]",1400,10,10000,1));
decT60VCF = 0.001 * vcf2(vslider("[0] DecayF [midi:ctrl 41] [tooltip: Decay-to-Sustain Time] [unit:ms] [style: knob]",10,10,10000,1));
susLvlVCF = 0.01 * vcf2(vslider("[0] SustainF [midi:ctrl 42] [tooltip: Sustain level as percent of max] [style: knob]",80,0,100,0.1));
decayButton = wg(vslider("Decay [midi:ctrl 20] [tooltip:Envelope Release either Decay value or 0][style:knob]",1,0,1,1):int); // was Staccato
legatoButton = wg(vslider("Glide [midi:ctrl 65] [tooltip: Glide from note to note][style:knob]",1,0,1,1)); // was Legato
relT60VCF = select2(decayButton,0.010,decT60VCF);
envelopeVCF = en.adsre(attT60VCF,decT60VCF,susLvlVCF,relT60VCF,gate);

// --- Smart Keyboard interface ---

declare interface "SmartKeyboard{
    'Number of Keyboards':'2',
    'Keyboard 0 - Number of Keys':'13',
    'Keyboard 1 - Number of Keys':'13',
    'Keyboard 0 - Lowest Key':'72',
    'Keyboard 1 - Lowest Key':'60'
}";

// --- functions ---

// Signal controls:

keyDownHold = gg(vslider("[0] gateHold [tooltip: lock sustain pedal on (hold gate set at 1)][style:knob]",0,0,1,1));

keyDown = gg(button("[1] gate [tooltip: The gate signal is 1 during a
	note and 0 otherwise. For MIDI, NoteOn occurs when the gate
	transitions from 0 to 1, and NoteOff is an event corresponding
	to the gate transition from 1 to 0. The name of this Faust
	button must be 'gate'.]"));

sustain = gg(button("[1] sustain [midi:ctrl 64]
	[tooltip: extends the gate (keeps it set to 1)]")); // MIDI only (see smartkeyb doc)

gate = keyDown + keyDownHold + sustain : min(1);

attT60 = 0.001 * ng(vslider("[0] AttackA [midi:ctrl 43] [tooltip: Attack Time] [unit:ms] [style: knob]",2,0,5000,0.1));
decT60 = 0.001 * ng(vslider("[0] DecayA [midi:ctrl 44] [tooltip: Decay-to-Sustain Time] [unit:ms] [style: knob]",10,0,10000,0.1));
susLvl = 0.01 * ng(vslider("[0] SustainA [midi:ctrl 45] [tooltip: Sustain level as percent of max] [style: knob]",80,0,100,0.1));
relT60 = select2(decayButton,0.010,decT60); // right?
envelopeAmpNoAM = en.adsre(attT60,decT60,susLvl,relT60,gate);
AMDepth = 0.5;
envelopeAmp = select2(oscModEnable, envelopeAmpNoAM,
	    envelopeAmpNoAM * (1.0 + AMDepth*modWheel * 0.5 * (1.0+oscNoiseModulation)));

// Signal Parameters
ampL = volg(vslider("[1] gain [style:knob] [tooltip: Amplitude]",0.2,0,1.0,0.001));
amp = ampL : si.smoo; // envelopeAmp is multiplied once on entire signal sum
//elecGuitar.dsp values used:
bend = wg(ba.semi2ratio(hslider("[0] bend [style:knob] [midi:pitchwheel]",0,-2,2,0.01))) : si.polySmooth(gate,0.999,1);
//Previous guess:
modWheel = wg(vslider("[1] mod [midi:ctrl 1] [style:knob] [tooltip: PitchModulation amplitude in octaves]",
	       0,0,1.0,0.01)) : si.polySmooth(gate,0.999,1);
//p: MIDI requires frequency in Hz, not piano-keys as we had before
// Frequency Range is 0.1 Hz to 20 kHz according to the Minimoog manual:
// MIDI REQUIRES THE FOLLOWING PARAMETER TO BE NAMED 'freq':
keyFreqBent = bend * kg(hslider("[2] freq [unit:Hz] [style:knob]",220,0.1,20000,0.1));
masterVolume = vg(vslider("MasterVolume [style:knob] [midi:ctrl 7] [tooltip: master volume, MIDI controlled]",
	     0.7,0,1,0.001))
	       : si.smooth(ba.tau2pole(0.16));
masterTuneOctaves = dg(vslider("[0] Tune [midi:ctrl 47] [unit:Octaves] [style:knob]
    [tooltip: Frequency-shift up or down for all oscillators in Octaves]", 0.0,-1.0,1.0,0.001));
    // Oscillator Modulation HrockerRed => apply Modulation Mix output osc1&2 pitches
glide = gmmg(vslider("[0] Glide [midi:ctrl 5] [unit:sec/octave] [style:knob] [scale:log]
    [tooltip: Portamento (frequency-glide) in seconds per octave]",
		    0.008,0.001,1.0,0.001));
legatoPole = select2(legatoButton,0.5,ba.tau2pole(glide*exp(1.0f)/2.0f)); // convert 1/e to 1/2 by slowing down exp
keyFreqGlided = keyFreqBent : si.smooth(legatoPole);

mmix = gmmg(vslider("[1] Mod. Mix [midi:ctrl 48] [style:knob] [tooltip: Modulation Mix: Osc3 (0) to Noise (1)]",
            0.0,0.0,1.0,0.001));
oscNoiseModulation = (mmix * noise) + ((1.0-mmix) * osc(3)); // noise amplitude and off-switch ignored here
oscModEnable = dsg(vslider("[0] Osc. Mod. [midi:ctrl 22] [color:red] [style:knob] [tooltip:Oscillator Modulation adds Modulation Mix output to osc1&2 frequencies",1,0,1,1)); // any offset?
osc3Control = dsg(vslider("[1] Osc. 3 Ctl [midi:ctrl 9] [color:red] [style:knob] [tooltip:Oscillator 3 frequency tracks the keyboard if on, else not",0,0,1,1):int);
