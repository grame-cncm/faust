import("stdfaust.lib");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// A complete Stereo FX chain with:
//		CHORUS
//		PHASER
//		DELAY
//		REVERB
//
// Designed to use the Analog Input for parameters controls.
//
// CONTROLES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANALOG IN:
// ANALOG 0	: Chorus Depth
// ANALOG 1	: Chorus Delay
// ANALOG 2	: Phaser Dry/Wet
// ANALOG 3	: Phaser Frequency ratio
// ANALOG 4	: Delay Dry/Wet
// ANALOG 5	: Delay Time
// ANALOG 6	: Reverberation Dry/Wet
// ANALOG 7	: Reverberation Room size
//
// Available by OSC : (see BELA console for precise adress)
// Rate			: Chorus LFO modulation rate (Hz)
// Deviation	: Chorus delay time deviation.
//
// InvertSum	: Phaser inversion of phaser in sum. (On/Off)
// VibratoMode	: Phaser vibrato Mode. (On/Off)
// Speed		: Phaser LFO frequency
// NotchDepth	: Phaser LFO depth
// Feedback		: Phaser Feedback
// NotchWidth	: Phaser Notch Width
// MinNotch1	: Phaser Minimal frequency
// MaxNotch1	: Phaser Maximal Frequency
//
// Damp			: Reverberation Damp
// Stereo		: Reverberation Stereo Width
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

process = chorus_stereo(dmax,curdel,rate,sigma,do2,voices) : phaserSt : xdelay : reverb;

// CHORUS (from SAM demo lib) //////////////////////////////////////////////////////////////////////////////////////////////////////////
voices = 8; // MUST BE EVEN

pi = 4.0*atan(1.0);
periodic  = 1;

dmax = 8192;
curdel = dmax * vslider("Delay[BELA: ANALOG_1]", 0.5, 0, 1, 1) : si.smooth(0.999);
rateMax = 7.0; // Hz
rateMin = 0.01;
rateT60 = 0.15661;

rate = vslider("Rate", 0.5, rateMin, rateMax, 0.0001): si.smooth(ba.tau2pole(rateT60/6.91));
depth = vslider("Depth [BELA: ANALOG_0]", 0.5, 0, 1, 0.001) : si.smooth(ba.tau2pole(depthT60/6.91));
// (dept = dry/wet)

depthT60 = 0.15661;
delayPerVoice = 0.5*curdel/voices;
sigma = delayPerVoice * vslider("Deviation",0.5,0,1,0.001) : si.smooth(0.999);

do2 = depth;   // use when depth=1 means "multivibrato" effect (no original => all are modulated)

chorus_stereo(dmax,curdel,rate,sigma,do2,voices) =
      _,_ <: *(1-do2),*(1-do2),(*(do2),*(do2) <: par(i,voices,voice(i)):>_,_) : ro.interleave(2,2) : +,+;
      voice(i) = de.fdelay(dmax,min(dmax,del(i)))/(i+1)
    with {
       angle(i) = 2*pi*(i/2)/voices + (i%2)*pi/2;
       voice(i) = de.fdelay(dmax,min(dmax,del(i))) * cos(angle(i));

         del(i) = curdel*(i+1)/voices + dev(i);
         rates(i) = rate/float(i+1);
         dev(i) = sigma *
             os.oscp(rates(i),i*2*pi/voices);
    };

// PHASER (from demo lib.) /////////////////////////////////////////////////////////////////////////////////////////////////////////////
phaserSt = _,_ <: _, _, phaser2_stereo : dry_wetST(dwPhaz)
    with {

        invert = checkbox("InvertSum");
        vibr = checkbox("VibratoMode"); // In this mode you can hear any "Doppler"

        phaser2_stereo = pf.phaser2_stereo(Notches,width,frqmin,fratio,frqmax,speed,mdepth,fb,invert);

        Notches = 4; // Compile-time parameter: 2 is typical for analog phaser stomp-boxes

        speed  = hslider("Speed", 0.5, 0, 10, 0.001);
        depth  = hslider("NotchDepth", 1, 0, 1, 0.001);
        fb     = hslider("Feedback", 0.7, -0.999, 0.999, 0.001);

        width  = hslider("NotchWidth",1000, 10, 5000, 1);
        frqmin = hslider("MinNotch1",100, 20, 5000, 1);
        frqmax = hslider("MaxNotch1",800, 20, 10000, 1) : max(frqmin);
        fratio = hslider("NotchFreqRatio[BELA: ANALOG_3]",1.5, 1.1, 4, 0.001);
        dwPhaz = vslider("dryWetPhaser[BELA: ANALOG_2]", 0.5, 0, 1, 0.001); 

        mdepth = select2(vibr,depth,2); // Improve "ease of use"
    };

// DELAY (with feedback and crossfeeback) //////////////////////////////////////////////////////////////////////////////////////////////
delay = ba.sec2samp(hslider("delay[BELA: ANALOG_5]", 1,0,2,0.001));
preDelL	= delay/2;
delL	= delay;
delR	= delay;

crossLF	= 1200;

CrossFeedb = 0.6;
dwDel = vslider("dryWetDelay[BELA: ANALOG_4]", 0.5, 0, 1, 0.001);

routeur(a,b,c,d) = ((a*CrossFeedb):fi.lowpass(2,crossLF))+c,
					((b*CrossFeedb):fi.lowpass(2,crossLF))+d;

xdelay = _,_ <: _,_,((de.sdelay(65536, 512,preDelL),_):
		(routeur : de.sdelay(65536, 512,delL) ,de.sdelay(65536, 512,delR)) ~ (_,_)) : dry_wetST(dwDel);

// REVERB (from freeverb_demo) /////////////////////////////////////////////////////////////////////////////////////////////////////////
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

        damping = vslider("Damp",0.5, 0, 1, 0.025)*scaledamp*origSR/ma.SR;
        combfeed = vslider("RoomSize[BELA: ANALOG_7]", 0.5, 0, 1, 0.001)*scaleroom*origSR/ma.SR + offsetroom;
        spatSpread = vslider("Stereo",0.5,0,1,0.01)*46*ma.SR/origSR;
        g = vslider("dryWetReverb[BELA: ANALOG_6]", 0.2, 0, 1, 0.001);
        // (g = Dry/Wet)
    };

// Dry-Wet (from C. LEBRETON)
dry_wetST(dw,x1,x2,y1,y2) = (wet*y1 + dry*x1),(wet*y2 + dry*x2)
    with {
        wet = 0.5*(dw+1.0);
        dry = 1.0-wet;
    };
