import("stdfaust.lib");
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple FX chain build for a mono synthesizer.
// It control general volume and pan.
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
// CC 7  : Volume
// CC 10 : Pan
//
// CC 13 : Flanger Delay
// CC 13 : Flanger Delay
// CC 94 : Flanger Feedback
//
// CC 95 : Reverberation Damp
// CC 90: Reverberation Stereo Width
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

// VOLUME:
vol = hslider("volume[midi:ctrl 7]",1,0,1,0.001);	// Should be 7 according to MIDI CC norm.

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

// Panoramic:
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
effets = _ *(vol) : ef.cubicnl_nodc(drive, 0.1) : flanger : panno : reverb;

process = effets;
