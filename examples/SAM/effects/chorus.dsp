import("stdfaust.lib");

import("layout2.dsp");

voices = 8; // MUST BE EVEN
process = ba.bypass1to2(cbp,chorus_mono(dmax,curdel,rate,sigma,do2,voices));

dmax = 8192;
curdel = dmax * ckg(vslider("[0] Delay [midi:ctrl 55] [style:knob]", 0.5, 0, 1, 1)) : si.smooth(0.999);
rateMax = 7.0; // Hz
rateMin = 0.01;
rateT60 = 0.15661;
rate = ckg(vslider("[1] Rate [midi:ctrl 56] [unit:Hz] [style:knob]", 0.5, rateMin, rateMax, 0.0001))
    : si.smooth(ba.tau2pole(rateT60/6.91));

depth = ckg(vslider("[4] Depth [midi:ctrl 57] [style:knob]", 0.5, 0, 1, 0.001)) : si.smooth(ba.tau2pole(depthT60/6.91));

depthT60 = 0.15661;
delayPerVoice = 0.5*curdel/voices;
sigma = delayPerVoice * ckg(vslider("[6] Deviation [midi:ctrl 58] [style:knob]",0.5,0,1,0.001)) : si.smooth(0.999);

periodic = 1;

do2 = depth;   // use when depth=1 means "multivibrato" effect (no original => all are modulated)
cbp = 1-int(csg(vslider("[0] Enable [midi:ctrl 103][style:knob]",0,0,1,1)));

chorus_mono(dmax,curdel,rate,sigma,do2,voices)
	= _ <: (*(1-do2)<:_,_),(*(do2) <: par(i,voices,voice(i)) :> _,_) : ro.interleave(2,2) : +,+
    with {
        angle(i) = 2*ma.PI*(i/2)/voices + (i%2)*ma.PI/2;
        voice(i) = de.fdelay(dmax,min(dmax,del(i))) * cos(angle(i));
        del(i) = curdel*(i+1)/voices + dev(i);
        rates(i) = rate/float(i+1);
        dev(i) = sigma * os.oscp(rates(i),i*2*ma.PI/voices);
    };
