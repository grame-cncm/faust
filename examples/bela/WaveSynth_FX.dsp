import("stdfaust.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Simple demo of wavetable synthesis. A LFO modulate the interpolation between 4 tables.
// It's possible to add more tables step.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// MIDI IMPLEMENTATION:
//
// CC 1     : LFO Depth (wave travel modulation)
// CC 14	: LFO Frequency
// CC 70	: Wave travelling
//
// CC 73	: Attack
// CC 76	: Decay
// CC 77	: Sustain
// CC 72	: Release
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// GENERAL
midigate = button("gate");
midifreq = nentry("freq[unit:Hz]", 440, 20, 20000, 1);
midigain = nentry("gain", 0.5, 0, 1, 0.01);

waveTravel = hslider("waveTravel [midi:ctrl ]",0,0,1,0.01);

// pitchwheel
bend = ba.semi2ratio(hslider("bend [midi:pitchwheel]",0,-2,2,0.01));

gFreq = midifreq * bend;

// LFO
lfoDepth = hslider("lfoDepth[midi:ctrl 1]",0,0.,1,0.001):si.smoo;
lfoFreq = hslider("lfoFreq[midi:ctrl 14]",0.1,0.01,10,0.001):si.smoo;
moov = ((os.lf_trianglepos(lfoFreq) * lfoDepth) + waveTravel) : min(1) : max(0);

volA = hslider("A[midi:ctrl 73]",0.01,0.01,4,0.01);
volD = hslider("D[midi:ctrl 76]",0.6,0.01,8,0.01);
volS = hslider("S[midi:ctrl 77]",0.2,0,1,0.01);
volR = hslider("R[midi:ctrl 72]",0.8,0.01,8,0.01);
envelop = en.adsre(volA,volD,volS,volR,midigate);

// Out Amplitude
vol = envelop * midigain;

WF(tablesize, rang) = abs((fmod ((1+(float(ba.time)*rang)/float(tablesize)), 4.0 ))-2) -1.;

// 4 WF maxi with this version:
scanner(nb, position) = -(_,soustraction) : *(_,coef) : cos : max(0)
    with {
        coef = 3.14159 * ((nb-1)*0.5);
        soustraction = select2(position>0, 0, (position/(nb-1)));
    };

wfosc(freq) = (rdtable(tablesize, wt1, faze)*(moov : scanner(4,0)))+(rdtable(tablesize, wt2, faze)*(moov : scanner(4,1)))
				+ (rdtable(tablesize, wt3, faze)*(moov : scanner(4,2)))+(rdtable(tablesize, wt4, faze)*(moov : scanner(4,3)))
    with {
        tablesize = 1024;
        wt1 = WF(tablesize, 16);
        wt2 = WF(tablesize, 8);
        wt3 = WF(tablesize, 6);
        wt4 = WF(tablesize, 4);
        faze = int(os.phasor(tablesize,freq));
    };

//#################################################################################################//
//##################################### EFFECT SECTION ############################################//
//#################################################################################################//
// Simple FX chaine build for a mono synthesizer.
// It control general volume and pan.
// FX Chaine is:
//		Drive
//		Flanger
//		Reverberation
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// MIDI IMPLEMENTATION:
// (All are available by OSC)
//
// CC 7	: Volume
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
volFX = hslider("volume[midi:ctrl 7]",1,0,1,0.001);// Should be 7 according to MIDI CC norm.

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
effect = _ *(volFX) : ef.cubicnl_nodc(drive, 0.1) : flanger : panno : reverb;

process = wfosc(gFreq) * vol;
