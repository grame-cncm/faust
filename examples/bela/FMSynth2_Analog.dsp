import("all.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple FM synthesizer.

///////////////////////////////////////////////////////////////////////////////////////////////////
// ANALOG IMPLEMENTATION:
//
// ANALOG_0	: Modulator frequency ratio
// ANALOG_1	: Attack
// ANALOG_2	: Decay/Release
// ANALOG_3	: Sustain
//
// MIDI:
// CC 1 : FM feedback on modulant oscillator.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// GENERAL, Keyboard
midigate = button("gate");
midifreq = nentry("freq[unit:Hz]", 440, 20, 20000, 1);
midigain = nentry("gain", 1, 0, 1, 0.01);

// modwheel:
feedb = (gFreq-1) * (hslider("feedb[midi:ctrl 1]", 0, 0, 1, 0.001) : si.smoo);
modFreqRatio = hslider("ratio[BELA: ANALOG_0]",2,0,20,0.01) : si.smoo;

// pitchwheel
bend = ba.semi2ratio(hslider("bend [midi:pitchwheel]",0,-2,2,0.01));

gFreq = midifreq * bend;

//=================================== Parameters Mapping =================================
//========================================================================================
// Same for volume & modulation:
volA = hslider("A[BELA: ANALOG_1]",0.01,0.01,4,0.01);
volDR = hslider("DR[BELA: ANALOG_2]",0.6,0.01,8,0.01);
volS = hslider("S[BELA: ANALOG_3]",0.2,0,1,0.01);
envelop = en.adsre(volA,volDR,volS,volDR,midigate);

// modulator frequency
modFreq = gFreq * modFreqRatio;

// modulation index
FMdepth = envelop * 1000 * midigain;

// Out amplitude
vol = envelop;

//============================================ DSP =======================================
//========================================================================================

FMfeedback(frq) = (+(_,frq):os.osci) ~ (*(feedb));
FMall(f) = os.osci(f + (FMdepth*FMfeedback(f*modFreqRatio)));

process = FMall(gFreq) * vol;
