declare name "piano";
declare description "WaveGuide Commuted Piano";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3";
// Synthesis Tool Kit 4.3 (MIT style license);
declare description "A commuted WaveGuide piano.";

import("instruments.lib");

//==================== BREAK-POINT FUNCTIONS ================

// The functions of the note number that shape the piano, interpolated linearly between
// their points and held beyond them (the tables of the STK piano, formerly read from
// piano.h through ffunction) : written as ba.bpf, they are bounded exactly by the
// compiler and run on every backend.

getValueBq4_gEarBalled = ba.bpf.start(100, 0.04)
    : ba.bpf.point(102.477, 0.1)
    : ba.bpf.point(104.518, 0.3)
    : ba.bpf.point(106, 0.5)
    : ba.bpf.point(107, 1)
    : ba.bpf.end(108, 1.5);

getValueDCBa1 = ba.bpf.start(21, -0.999)
    : ba.bpf.point(24, -0.999)
    : ba.bpf.point(30, -0.999)
    : ba.bpf.point(36, -0.999)
    : ba.bpf.point(42, -0.999)
    : ba.bpf.point(48.027, -0.993)
    : ba.bpf.point(60, -0.995)
    : ba.bpf.point(72.335, -0.96)
    : ba.bpf.point(78.412, -0.924)
    : ba.bpf.point(84.329, -0.85)
    : ba.bpf.point(87.688, -0.77)
    : ba.bpf.point(91, -0.7)
    : ba.bpf.point(92, -0.91)
    : ba.bpf.point(96.783, -0.85)
    : ba.bpf.point(99, -0.8)
    : ba.bpf.point(100, -0.85)
    : ba.bpf.point(104.634, -0.7)
    : ba.bpf.end(107.518, -0.5);

getValueDetuningHz = ba.bpf.start(21, 0.003)
    : ba.bpf.point(24, 0.003)
    : ba.bpf.point(28, 0.003)
    : ba.bpf.point(29, 0.06)
    : ba.bpf.point(31, 0.1)
    : ba.bpf.point(36, 0.11)
    : ba.bpf.point(42, 0.12)
    : ba.bpf.point(48, 0.2)
    : ba.bpf.point(54, 0.2)
    : ba.bpf.point(60, 0.25)
    : ba.bpf.point(66, 0.27)
    : ba.bpf.point(72.232, 0.3)
    : ba.bpf.point(78, 0.35)
    : ba.bpf.point(84, 0.5)
    : ba.bpf.point(88.531, 0.582)
    : ba.bpf.point(92.116, 0.664)
    : ba.bpf.point(95.844, 0.793)
    : ba.bpf.end(99, 1);

getValueDryTapAmpT60 = ba.bpf.start(21.001, 0.491)
    : ba.bpf.point(26.587, 0.498)
    : ba.bpf.point(34.249, 0.47)
    : ba.bpf.point(40.794, 0.441)
    : ba.bpf.point(47.977, 0.392)
    : ba.bpf.point(55, 0.37)
    : ba.bpf.point(60, 0.37)
    : ba.bpf.point(66, 0.37)
    : ba.bpf.point(71.934, 0.37)
    : ba.bpf.point(78, 0.37)
    : ba.bpf.point(83.936, 0.39)
    : ba.bpf.point(88.557, 0.387)
    : ba.bpf.point(92.858, 0.4)
    : ba.bpf.point(97.319, 0.469)
    : ba.bpf.point(102.4, 0.5)
    : ba.bpf.end(107.198, 0.494);

getValueEQBandWidthFactor = ba.bpf.start(21, 5)
    : ba.bpf.point(24.112, 5)
    : ba.bpf.point(28, 5)
    : ba.bpf.point(35, 4.956)
    : ba.bpf.point(41, 6)
    : ba.bpf.point(42, 2)
    : ba.bpf.point(48.773, 1.072)
    : ba.bpf.point(57.558, 1.001)
    : ba.bpf.point(63.226, 1.048)
    : ba.bpf.point(69.178, 1.12)
    : ba.bpf.point(72.862, 1.525)
    : ba.bpf.point(80.404, 2.788)
    : ba.bpf.end(97.659, 1.739);

getValueEQGain = ba.bpf.start(21, 2)
    : ba.bpf.point(24, 2)
    : ba.bpf.point(28, 2)
    : ba.bpf.point(30, 2)
    : ba.bpf.point(35.562, 1.882)
    : ba.bpf.point(41, 1.2)
    : ba.bpf.point(42, 0.6)
    : ba.bpf.point(48, 0.5)
    : ba.bpf.point(54, 0.5)
    : ba.bpf.point(59.928, 0.502)
    : ba.bpf.point(66.704, 0.489)
    : ba.bpf.point(74.201, 0.477)
    : ba.bpf.point(91.791, 1)
    : ba.bpf.end(99, 1);

getValueLoudGain = ba.bpf.start(21.873, 0.891)
    : ba.bpf.point(25.194, 0.87)
    : ba.bpf.point(30.538, 0.848)
    : ba.bpf.point(35.448, 0.853)
    : ba.bpf.point(41.513, 0.842)
    : ba.bpf.point(47.434, 0.826)
    : ba.bpf.point(53.644, 0.82)
    : ba.bpf.point(60.72, 0.815)
    : ba.bpf.point(65.63, 0.82)
    : ba.bpf.point(72.995, 0.853)
    : ba.bpf.point(79.06, 0.92)
    : ba.bpf.point(85.27, 1.028)
    : ba.bpf.point(91.624, 1.247)
    : ba.bpf.point(95.668, 1.296)
    : ba.bpf.point(99, 1.3)
    : ba.bpf.end(100, 1.1);

getValueLoudPole = ba.bpf.start(21, 0.875)
    : ba.bpf.point(23.719, 0.871)
    : ba.bpf.point(27.237, 0.836)
    : ba.bpf.point(28.996, 0.828)
    : ba.bpf.point(32.355, 0.82)
    : ba.bpf.point(36.672, 0.816)
    : ba.bpf.point(40.671, 0.82)
    : ba.bpf.point(45.788, 0.812)
    : ba.bpf.point(47.867, 0.812)
    : ba.bpf.point(54, 0.81)
    : ba.bpf.point(60, 0.8)
    : ba.bpf.point(66, 0.8)
    : ba.bpf.point(72, 0.81)
    : ba.bpf.point(78.839, 0.824)
    : ba.bpf.point(84.446, 0.844)
    : ba.bpf.point(89.894, 0.844)
    : ba.bpf.point(96.463, 0.848)
    : ba.bpf.point(103.512, 0.84)
    : ba.bpf.end(107.678, 0.84);

getValuePoleValue = ba.bpf.start(21, 0.99)
    : ba.bpf.point(24, 0.99)
    : ba.bpf.point(28, 0.99)
    : ba.bpf.point(29, 0.99)
    : ba.bpf.point(36, 0.99)
    : ba.bpf.point(42, 0.99)
    : ba.bpf.point(48, 0.985)
    : ba.bpf.point(54, 0.97)
    : ba.bpf.point(60, 0.96)
    : ba.bpf.point(66, 0.96)
    : ba.bpf.point(72, 0.96)
    : ba.bpf.point(78, 0.97)
    : ba.bpf.point(84.673, 0.975)
    : ba.bpf.point(91.157, 0.99)
    : ba.bpf.point(100.982, 0.97)
    : ba.bpf.end(104.205, 0.95);

getValueReleaseLoopGain = ba.bpf.start(21, 0.865)
    : ba.bpf.point(24, 0.88)
    : ba.bpf.point(29, 0.896)
    : ba.bpf.point(36, 0.91)
    : ba.bpf.point(48, 0.92)
    : ba.bpf.point(60, 0.95)
    : ba.bpf.point(72, 0.965)
    : ba.bpf.point(84, 0.988)
    : ba.bpf.point(88, 0.997)
    : ba.bpf.end(99, 0.988);

getValueSecondPartialFactor = ba.bpf.start(88, 2)
    : ba.bpf.end(108, 2.1);

getValueSecondStageAmpRatio = ba.bpf.start(82.277, -18.508)
    : ba.bpf.point(88, -30)
    : ba.bpf.point(90, -30)
    : ba.bpf.point(93.451, -30.488)
    : ba.bpf.point(98.891, -30.633)
    : ba.bpf.end(107.573, -30.633);

getValueSingleStringDecayRate = ba.bpf.start(21, -1.5)
    : ba.bpf.point(24, -1.5)
    : ba.bpf.point(28, -1.5)
    : ba.bpf.point(29, -6)
    : ba.bpf.point(36, -6)
    : ba.bpf.point(42, -6.1)
    : ba.bpf.point(48, -7)
    : ba.bpf.point(52.836, -7)
    : ba.bpf.point(60, -7.3)
    : ba.bpf.point(66, -7.7)
    : ba.bpf.point(72, -8)
    : ba.bpf.point(78, -8.8)
    : ba.bpf.point(84, -10)
    : ba.bpf.point(88.619, -11.215)
    : ba.bpf.point(92.368, -12.348)
    : ba.bpf.point(95.684, -13.934)
    : ba.bpf.end(99, -15);

getValueSingleStringPole = ba.bpf.start(21, 0.35)
    : ba.bpf.point(24.604, 0.318)
    : ba.bpf.point(26.335, 0.279)
    : ba.bpf.point(28, 0.25)
    : ba.bpf.point(32, 0.15)
    : ba.bpf.point(36, 0)
    : ba.bpf.point(42, 0)
    : ba.bpf.point(48, 0)
    : ba.bpf.point(54, 0)
    : ba.bpf.point(60, 0)
    : ba.bpf.point(66, 0)
    : ba.bpf.point(72, 0)
    : ba.bpf.point(76, 0)
    : ba.bpf.point(84, 0)
    : ba.bpf.point(88, 0)
    : ba.bpf.point(96, 0)
    : ba.bpf.end(99, 0);

getValueSingleStringZero = ba.bpf.start(21, -1)
    : ba.bpf.point(24, -1)
    : ba.bpf.point(28, -1)
    : ba.bpf.point(29, -1)
    : ba.bpf.point(32.534, -1)
    : ba.bpf.point(36, -0.7)
    : ba.bpf.point(42, -0.4)
    : ba.bpf.point(48, -0.2)
    : ba.bpf.point(54, -0.12)
    : ba.bpf.point(60, -0.08)
    : ba.bpf.point(66, -0.07)
    : ba.bpf.point(72, -0.07)
    : ba.bpf.point(79, -0.065)
    : ba.bpf.point(84, -0.063)
    : ba.bpf.point(88, -0.06)
    : ba.bpf.point(96, -0.05)
    : ba.bpf.end(99, -0.05);

getValueSoftGain = ba.bpf.start(20.865, 0.4)
    : ba.bpf.point(22.705, 0.4)
    : ba.bpf.point(25.96, 0.4)
    : ba.bpf.point(28.224, 0.4)
    : ba.bpf.point(31.196, 0.4)
    : ba.bpf.point(36.715, 0.4)
    : ba.bpf.point(44.499, 0.4)
    : ba.bpf.point(53.981, 0.4)
    : ba.bpf.point(60, 0.35)
    : ba.bpf.point(66, 0.35)
    : ba.bpf.point(72.661, 0.35)
    : ba.bpf.point(81.435, 0.43)
    : ba.bpf.point(88.311, 0.45)
    : ba.bpf.point(93.04, 0.5)
    : ba.bpf.end(96.434, 0.5);

getValueStiffnessCoefficient = ba.bpf.start(21, -0.85)
    : ba.bpf.point(23.595, -0.85)
    : ba.bpf.point(27.055, -0.83)
    : ba.bpf.point(29, -0.7)
    : ba.bpf.point(37.725, -0.516)
    : ba.bpf.point(46.952, -0.352)
    : ba.bpf.point(60, -0.25)
    : ba.bpf.point(73.625, -0.036)
    : ba.bpf.point(93.81, -0.006)
    : ba.bpf.end(99, 1.011);

getValueStrikePosition = ba.bpf.start(21, 0.05)
    : ba.bpf.point(24, 0.05)
    : ba.bpf.point(28, 0.05)
    : ba.bpf.point(35, 0.05)
    : ba.bpf.point(41, 0.05)
    : ba.bpf.point(42, 0.125)
    : ba.bpf.point(48, 0.125)
    : ba.bpf.point(60, 0.125)
    : ba.bpf.point(72, 0.125)
    : ba.bpf.point(84, 0.125)
    : ba.bpf.point(96, 0.125)
    : ba.bpf.end(99, 0.125);

getValueSustainPedalLevel = ba.bpf.start(21, 0.05)
    : ba.bpf.point(24, 0.05)
    : ba.bpf.point(31, 0.03)
    : ba.bpf.point(36, 0.025)
    : ba.bpf.point(48, 0.01)
    : ba.bpf.point(60, 0.005)
    : ba.bpf.point(66, 0.003)
    : ba.bpf.point(72, 0.002)
    : ba.bpf.point(78, 0.002)
    : ba.bpf.point(84, 0.003)
    : ba.bpf.point(90, 0.003)
    : ba.bpf.point(96, 0.003)
    : ba.bpf.end(108, 0.002);

getValueThirdPartialFactor = ba.bpf.start(88, 3.1)
    : ba.bpf.end(108, 3.1);

getValuer1_1db = ba.bpf.start(100, -75)
    : ba.bpf.point(103.802, -237.513)
    : ba.bpf.end(108, -400);

getValuer1_2db = ba.bpf.start(98.388, -16.562)
    : ba.bpf.point(100.743, -75.531)
    : ba.bpf.point(103.242, -154.156)
    : ba.bpf.end(108, -300);

getValuer2db = ba.bpf.start(100, -115.898)
    : ba.bpf.end(107.858, -250);

getValuer3db = ba.bpf.start(100, -150)
    : ba.bpf.end(108, -400);


//==================== GUI SPECIFICATION ================

freq = nentry("h:Basic_Parameters/freq [1][unit:Hz] [tooltip:Tone frequency]", 440, 20, 20000, 1);
gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]", 1, 0, 1, 0.01);
gate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

brightnessFactor = hslider("v:Physical_Parameters/Brightness_Factor
[2][tooltip:A value between 0 and 1]", 0, 0, 1, 0.01);
detuningFactor = hslider("v:Physical_Parameters/Detuning_Factor
[2][tooltip:A value between 0 and 1]", 0.1, 0, 1, 0.01)*10;
stiffnessFactor = hslider("v:Physical_Parameters/Stiffness_Factor
[2][tooltip:A value between 0 and 1]", 0.28, 0, 1, 0.01)*3.7;
hammerHardness = hslider("v:Physical_Parameters/Hammer_Hardness
[2][tooltip:A value between 0 and 1]", 0.1, 0, 1, 0.01)*0.1;

//==================== COMMUTED PIANO PARAMETERS ================

//variables to set keybord splitting zone
DCB2_TURNOFF_KEYNUM = 92;
FIRST_HIGH_NOTE = 88;
PEDAL_ENVELOPE_T60 = 7;

//convert an amplitude in db
dbinv(x) = pow(10, 0.05*x);

//convert a frequency in a midi note number
freqToNoteNumber = (log-log(440))/log(2)*12+69+0.5:int;
freqn = freq:freqToNoteNumber;

//a counter that restart a every note-on
cntSample = *(gate)+1~_:-(1);

//==================== PIANO SOUND BOARD ================

//exponential envelope with 3 phases for the pedal excitation	
asympT60pedal(value, T60) = (*(factor)+constant)~_
    with {
        attDur = hammerHardness*float(ma.SR);
        target = value*((cntSample<attDur)&(gate>0));
        factorAtt = exp(-1/(attDur));
        factorG = exp(-1/(2*float(ma.SR)));
        factorT60 = exp(-7/(T60*float(ma.SR)));
        factor = factorAtt*gate*(cntSample<attDur)+(cntSample>=attDur)*gate*factorG+((gate-1)*-1)*factorT60;
        constant = (1-factor)*target;
    };

//the sound of the piano sound board is generated by noise generator whose output gain is shaped by
//an exponential envelope
soundBoard = dryTapAmp*no.noise+pedalEnv*no.noise:*(0.5)
    with {
        //the values of the envelope cut-off time are stored in an external C++ function 
        dryTapAmpT60 = getValueDryTapAmpT60;
        sustainPedalLevel = getValueSustainPedalLevel;

        pedalEnvCutOffTime = 1.4;
        noteCutOffTime = freqn:dryTapAmpT60*gain;
        pedalEnvValue = freqn:sustainPedalLevel*0.2;
        noteEnvValue = 0.15;
        dryTapAmp = asympT60(noteEnvValue, 0, noteCutOffTime, gate);
        pedalEnv = asympT60pedal(pedalEnvValue, pedalEnvCutOffTime);
    };

//==================== HAMMER MODELING ================

//To model the exitation hammer, we filter the sound from the soundboard with a serie of 4 one pole filters
//connected in serie  

//onePole is declared in instruments.lib
calcHammer = onePole((1-hammerPole)*hammerGain, -hammerPole)
    with {
        //filter gains and coefficients are stored in external C++ files
        loudPole = getValueLoudPole;
        softPole = getValuePoleValue;
        loudGain = getValueLoudGain;
        softGain = getValueSoftGain;

        loudPoleValue = loudPole(freqn)+(brightnessFactor*-0.25)+0.02;
        softPoleValue = softPole(freqn);
        normalizedVelocityValue = 1;
        loudGainValue = loudGain(freqn);
        softGainValue = softGain(freqn);
        overallGain = 1;
        hammerPole = softPoleValue+(loudPoleValue-softPoleValue)*normalizedVelocityValue;
        hammerGain = overallGain*(softGainValue+(loudGainValue-softGainValue)*normalizedVelocityValue);
    };

hammer = seq(i, 4, calcHammer);

//==================== DC BLOCKERS ================

//the values for the dcblockers a1 are stored in an external C++ file
DCBa1 = getValueDCBa1;
dCBa1Value = freqn:DCBa1;
dCBb0Value = 1-dCBa1Value;

dcBlock1 = poleZero((dCBb0Value*0.5), (dCBb0Value*-0.5), dCBa1Value);

dcBlock2a = oneZero1(0.5, -0.5);

dcBlock2b = onePole(dCBb0Value, dCBa1Value);

//==================== HIGH TUNING CALCULATION ================

//high tones are not generated with the waveguide technique but with a serie of biquad filters

r1_1 = getValuer1_1db;
r1_2 = getValuer1_2db;
r2 = getValuer2db;
r3 = getValuer3db;
e = getValueSecondStageAmpRatio;
second_partial_factor = getValueSecondPartialFactor;
third_partial_factor = getValueThirdPartialFactor;
bq4_gEarBalled = getValueBq4_gEarBalled;

r1_1Value = r1_1(freqn)/ma.SR:dbinv;
r1_2Value = r1_2(freqn)/ma.SR:dbinv;
r2Value = r2(freqn)/ma.SR:dbinv;
r3Value = r3(freqn)/ma.SR:dbinv;
eValue = e(freqn):dbinv;
second_partial_factorValue = second_partial_factor(freqn);
third_partial_factorValue = third_partial_factor(freqn);

//set biquad gains and coeffs
gainHighBq(0) = bq4_gEarBalled(freqn)/0.5;
gainHighBq(1) = bq4_gEarBalled(freqn)/0.5;
gainHighBq(2) = 1;
gainHighBq(3) = 1;

b0HighBq(0) = 1;
b0HighBq(1) = 1;
b0HighBq(2) = 1;
b0HighBq(3) = 1;

b1HighBq(0) = 0;
b1HighBq(1) = 0;
b1HighBq(2) = -2*(eValue*r1_1Value+(1-eValue)*r1_2Value)*cos(2*ma.PI*freq/ma.SR);
b1HighBq(3) = 0;

b2HighBq(0) = 0;
b2HighBq(1) = 0;
b2HighBq(2) = eValue*r1_1Value*r1_1Value+(1-eValue)*r1_2Value*r1_2Value;
b2HighBq(3) = 0;

a1HighBq(0) = -2*r3Value*cos(2*ma.PI*freq*third_partial_factorValue/ma.SR);
a1HighBq(1) = -2*r2Value*cos(2*ma.PI*freq*second_partial_factorValue/ma.SR);
a1HighBq(2) = -2*r1_1Value*cos(2*ma.PI*freq/ma.SR);
a1HighBq(3) = -2*r1_2Value*cos(2*ma.PI*freq/ma.SR);

a2HighBq(0) = r3Value*r3Value;
a2HighBq(1) = r2Value*r2Value;
a2HighBq(2) = r1_1Value*r1_1Value;
a2HighBq(3) = r1_2Value*r1_2Value;

highBqs = seq(i, 4, *(gainHighBq(i)):fi.TF2(b0HighBq(i), b1HighBq(i), b2HighBq(i), a1HighBq(i), a2HighBq(i)));

hiPass = oneZero1(b0, b1)
    with {
        b0 = -0.5;
        b1 = -0.5;
    };

//==================== STRIKE POSITION COMB FILTER EQ ================

eq = _*filterGain:fi.TF2(b0, b1, b2, a1, a2)
    with {
        strikePosition = getValueStrikePosition;
        bandwidthFactors = getValueEQBandWidthFactor;
        eq_gain = getValueEQGain;
        eq_tuning = freq/strikePosition(freqn);
        eq_bandwidth = bandwidthFactors(freqn)*freq;
        filterGain = eq_gain(freqn);
        a2 = (eq_bandwidth/ma.SR)*(eq_bandwidth/ma.SR);
        a1 = -2*(eq_bandwidth/ma.SR)*cos(2*ma.PI*eq_tuning/ma.SR);
        b0 = 0.5-0.5*a2;
        b1 = 0;
        b2 = -b0;
    };

//==================== PIANO COUPLED STRINGS ================

//values for the couple strings are stored in externals C++ functions
singleStringDecRate = getValueSingleStringDecayRate;
singleStringZero = getValueSingleStringZero;
singleStringPole = getValueSingleStringPole;
stiffnessCoefficient = getValueStiffnessCoefficient;

//coupling filter parameters
g = pow(10, ((singleStringDecRate(freqn)/freq)/20));
//attenuation per period
b = singleStringZero(freqn);
a = singleStringPole(freqn);
tempd = 3*(1-b)-g*(1-a);
b0Coupling = 2*(g*(1-a)-(1-b))/tempd;
b1Coupling = 2*(a*(1-b)-g*(1-a)*b)/tempd;
a1Coupling = (g*(1-a)*b-3*a*(1-b))/tempd;

//string stiffness
stiffness = stiffnessFactor*stiffnessCoefficient(freqn);

stiffnessAP = poleZero(b0s, b1s, a1s)
    with {
        b0s = stiffness;
        b1s = 1;
        a1s = stiffness;
    };

delayG(frequency, stiffnessCoefficient) = de.fdelay(4096, delayLength)
    with {
        allPassPhase(a1, WT) = atan2((a1*a1-1.0)*sin(WT), (2.0*a1+(a1*a1+1.0)*cos(WT)));
        poleZeroPhase(b0, b1, a1, WT) = atan2(-b1*sin(WT)*(1+a1*cos(WT))+a1*sin(WT)*(b0+b1*cos(WT)),
            (b0+b1*cos(WT))*(1+a1*cos(WT))+b1*sin(WT)*a1*sin(WT));
        wT = frequency*2*ma.PI/ma.SR;
        delayLength = (2*ma.PI+3*allPassPhase(stiffnessCoefficient, wT)+poleZeroPhase((1+2*b0Coupling),
            a1Coupling+2*b1Coupling,
            a1Coupling,
            wT))/wT;
    };

coupledStrings = (parallelStrings<:(_, (_+_<:_, _), _:_, _, (_:couplingFilter), _:adder))~(_, _):!, !, _
    with {
        releaseLoopGain = getValueReleaseLoopGain;
        hz = getValueDetuningHz;
        coupledStringLoopGain = gate*0.9996+((gate-1)*-1)*releaseLoopGain(freqn)*0.9:si.smoo;
        couplingFilter = poleZero(b0Coupling, b1Coupling, a1Coupling);
        hzValue = hz(freqn);
        freq1 = freq+0.5*hzValue*detuningFactor;
        freq2 = freq-0.5*hzValue*detuningFactor;
        delay1 = delayG(freq1, stiffness);
        delay2 = delayG(freq2, stiffness);
        parallelStrings(x, y) = _<:(+(x)*coupledStringLoopGain:seq(i, 3, stiffnessAP):delay1), (_+y*coupledStringLoopGain:seq(i, 3, stiffnessAP):delay2);
        adder(w, x, y, z) = (y<:+(w), +(z)), x;
    };

//stereoizer is declared in instruments.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
stereo = stereoizer(ma.SR/freq);

//==================== PROCESSING ================

conditionLowNote = freqn<FIRST_HIGH_NOTE;
conditionHighNote = freqn>=FIRST_HIGH_NOTE;

process = soundBoard<:(*(conditionLowNote)*6:hammer:dcBlock1:coupledStrings<:+(eq)), (*(conditionHighNote):hiPass:dcBlock1:hammer:dcBlock2a:highBqs:dcBlock2b):>+:*(12):stereo:instrReverb;
