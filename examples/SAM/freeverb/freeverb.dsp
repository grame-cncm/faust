import("stdfaust.lib");
import("layout2.dsp");

declare name        "freeverb";
declare version     "1.0";
declare author      "Grame";
declare license     "BSD";
declare copyright   "(c) GRAME 2006 and MoForte Inc. 2017";
declare reference   "https://ccrma.stanford.edu/~jos/pasp/Freeverb.html";

//======================================================
//
//                      Freeverb
//        Faster version using fixed delays (20% gain)
//
//======================================================

// Constant Parameters
//--------------------

fixedgain   = 0.015; //value of the gain of fxctrl
scalewet    = 3.0;
scaledry    = 2.0;
scaledamp   = 0.4;
scaleroom   = 0.28;
offsetroom  = 0.7;
initialroom = 0.5;
initialdamp = 0.5;
initialwet  = 1.0/scalewet;
initialdry  = 0;
initialwidth= 1.0;
initialmode = 0.0;
freezemode  = 0.5;
stereospread= 23;
allpassfeed = 0.5; //feedback of the delays used in allpass filters


// Filter Parameters
//------------------

combtuningL1    = 1116;
combtuningL2    = 1188;
combtuningL3    = 1277;
combtuningL4    = 1356;
combtuningL5    = 1422;
combtuningL6    = 1491;
combtuningL7    = 1557;
combtuningL8    = 1617;

allpasstuningL1 = 556;
allpasstuningL2 = 441;
allpasstuningL3 = 341;
allpasstuningL4 = 225;


// Control Sliders
//--------------------
// Damp : filters the high frequencies of the echoes (especially active for great values of RoomSize)
// RoomSize : size of the reverberation room
// Dry : original signal
// Wet : reverberated signal

dampSlider      = rkg(vslider("Damp [midi:ctrl 3] [style:knob]",0.5, 0, 1, 0.025))*scaledamp;
roomsizeSlider  = rkg(vslider("RoomSize [midi:ctrl 4] [style:knob]", 0.5, 0, 1, 0.025))*scaleroom + offsetroom;
wetSlider       = rkg(vslider("Wet [midi:ctrl 2] [style:knob]", 0.3333, 0, 1, 0.025));
combfeed        = roomsizeSlider;


// Comb and Allpass filters
//-------------------------

allpass(dt,fb) = (_,_ <: (*(fb),_:+:@(dt)), -) ~ _ : (!,_);

comb(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));


// Reverb components
//------------------

monoReverb(fb1, fb2, damp, spread)
    = _ <:  comb(combtuningL1+spread, fb1, damp),
            comb(combtuningL2+spread, fb1, damp),
            comb(combtuningL3+spread, fb1, damp),
            comb(combtuningL4+spread, fb1, damp),
            comb(combtuningL5+spread, fb1, damp),
            comb(combtuningL6+spread, fb1, damp),
            comb(combtuningL7+spread, fb1, damp),
            comb(combtuningL8+spread, fb1, damp)
        +>
            allpass (allpasstuningL1+spread, fb2)
        :   allpass (allpasstuningL2+spread, fb2)
        :   allpass (allpasstuningL3+spread, fb2)
        :   allpass (allpasstuningL4+spread, fb2)
        ;

monoReverbToStereo(fb1, fb2, damp, spread)
    = + <: monoReverb(fb1, fb2, damp, 0) <: _,_;
stereoReverb(fb1, fb2, damp, spread)
    = + <:  monoReverb(fb1, fb2, damp, 0), monoReverb(fb1, fb2, damp, spread);
monoToStereoReverb(fb1, fb2, damp, spread)
    = _ <: monoReverb(fb1, fb2, damp, 0), monoReverb(fb1, fb2, damp, spread);

// fxctrl : add an input gain and a wet-dry control to a stereo FX
//----------------------------------------------------------------

fxctrl(g,w,Fx) =  _,_ <: (*(g),*(g) : Fx : *(w),*(w)), *(1-w), *(1-w) +> _,_;

rbp = 1-int(rsg(vslider("[0] Enable [midi:ctrl 105][style:knob]",0,0,1,1)));

// Freeverb
//---------

//JOS:freeverb = fxctrl(fixedgain, wetSlider, stereoReverb(combfeed, allpassfeed, dampSlider, stereospread));
freeverb = fxctrl(fixedgain, wetSlider, monoReverbToStereo(combfeed, allpassfeed, dampSlider, stereospread));

process = ba.bypass2(rbp,freeverb);
