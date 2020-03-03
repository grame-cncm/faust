import("all.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple FM synthesizer.
// 2 oscillators and FM feedback on modulant oscillator
//
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

FMfeedback(frq) = (+(_,frq):os.osci) ~ (* (feedb));
FMall(f) = os.osci(f + (FMdepth*FMfeedback(f*modFreqRatio)));

//#################################################################################################//
//##################################### EFFECT SECTION ############################################//
//#################################################################################################//
//
// Simple FX chaine build for a mono synthesizer.
// It controle general volume and pan.
// FX Chaine is:
//		Drive
//		Flanger
//		Reverberation
//
// This version use ANALOG IN to controle some of the parameters.
// Other parameters continue to be available by MIDI or OSC.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// ANALOG IMPLEMENTATION:
//
// ANALOG_4	: Distortion Drive
// ANALOG_5	: Flanger Dry/Wet
// ANALOG_6	: Reverberation Dry/Wet
// ANALOG_7	: Reverberation Room size
//
// MIDI:
// CC 7	: Volume
// CC 10 : Pan
//
// CC 13 : Flanger Delay
// CC 13 : Flanger Delay
// CC 94 : Flanger Feedback
//
// CC 95 : Reverberation Damp
// CC 90 : Reverberation Stereo Width
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

// VOLUME:
volFX = hslider("volume[midi:ctrl 7]",1,0,1,0.001);	// Should be 7 according to MIDI CC norm.

// EFFECTS /////////////////////////////////////////////
drive = hslider("drive[BELA: ANALOG_4]",0.3,0,1,0.001);

// Flanger
curdel = hslider("flangDel[midi:ctrl 13]",4,0.001,10,0.001);
fb = hslider("flangFeedback[midi:ctrl 94]",0.7,0,1,0.001);
fldw = hslider("dryWetFlang[BELA: ANALOG_5]",0.5,0,1,0.001);
flanger = efx
	with {
		fldel = (curdel + (os.lf_triangle(1) * 2) ) : min(10);
		efx = _ <: _, pf.flanger_mono(10,fldel,1,fb,0) : dry_wet(fldw);
	};

// Pannoramique:
panno = _ : sp.panner(hslider("pan[midi:ctrl 10]",0.5,0,1,0.001)) : _,_;

// REVERB (from freeverb_demo)
reverb = _,_ <: (*(g)*fixedgain, *(g)*fixedgain :
	re.stereo_freeverb(combfeed, allpassfeed, damping, spatSpread)),
	*(1-g), *(1-g) :> _,_
    with {
        scaleroom   = 0.28;
        offsetroom  = 0.7;
        allpassfeed = 0.5;
        scaledamp   = 0.4;
        fixedgain   = 0.1;
        origSR = 44100;

        damping = vslider("Damp[midi:ctrl 95]",0.5, 0, 1, 0.025)*scaledamp*origSR/ma.SR;
        combfeed = vslider("RoomSize[BELA: ANALOG_7]", 0.7, 0, 1, 0.025)*scaleroom*origSR/ma.SR + offsetroom;
        spatSpread = vslider("Stereo[midi:ctrl 90]",0.6,0,1,0.01)*46*ma.SR/origSR;
        g = vslider("dryWetReverb[BELA: ANALOG_6]", 0.4, 0, 1, 0.001);
        // (g = Dry/Wet)
    };

// Dry-Wet (from C. LEBRETON)
dry_wet(dw,x,y) = wet*y + dry*x
    with {
        wet = 0.5*(dw+1.0);
        dry = 1.0-wet;
    };

// ALL
effect = _ *(volFX) : ef.cubicnl_nodc(drive, 0.1) : flanger : panno : reverb;

process = FMall(gFreq) * vol;

