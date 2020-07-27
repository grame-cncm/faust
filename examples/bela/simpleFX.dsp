import("stdfaust.lib");
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple FX chaine build for a mono synthesizer.
// It controle general volume and pan.
// FX Chaine is:
//		Drive
//		Flanger
//		Reverberation
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// MIDI IMPLEMENTATION:
// (All are available by OSC)
//
// CC 7  : Volume
// CC 10 : Pan
//
// CC 92 : Distortion Drive
//
// CC 13 : Flanger Delay
// CC 93 : Flanger Dry/Wet
// CC 94 : Flanger Feedback
//
// CC 12 : Reverberation Room size
// CC 91 : Reverberation Dry/Wet
// CC 95 : Reverberation Damp
// CC 90 : Reverberation Stereo Width
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// VOLUME:
vol = hslider("volume[midi:ctrl 7]",1,0,1,0.001);// Should be 7 according to MIDI CC norm.

// EFFECTS /////////////////////////////////////////////
drive = hslider("drive[midi:ctrl 92]",0.3,0,1,0.001);

// Flanger
curdel = hslider("flangDel[midi:ctrl 13]",4,0.001,10,0.001);
fb = hslider("flangFeedback[midi:ctrl 94]",0.7,0,1,0.001);
fldw = hslider("dryWetFlang[midi:ctrl 93]",0.5,0,1,0.001);
flanger = efx
	with {
		fldel = (curdel + (os.lf_triangle(1) * 2) ) : min(10);
		efx = _ <: _, pf.flanger_mono(10,fldel,1,fb,0) : dry_wet(fldw);
	};

// Panoramique:
panno = _ : sp.panner(hslider ("pan[midi:ctrl 10]",0.5,0,1,0.001)) : _,_;

// REVERB (from freeverb_demo)
reverb = _,_ <: (*(g)*fixedgain,*(g)*fixedgain :
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
        combfeed = vslider("RoomSize[midi:ctrl 12]", 0.7, 0, 1, 0.025)*scaleroom*origSR/ma.SR + offsetroom;
        spatSpread = vslider("Stereo[midi:ctrl 90]",0.6,0,1,0.01)*46*ma.SR/origSR;
        g = vslider("dryWetReverb[midi:ctrl 91]", 0.4, 0, 1, 0.001);
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
