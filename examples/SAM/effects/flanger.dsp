// Created from flange.dsp 2015/06/21

import("stdfaust.lib");
import("layout2.dsp");

flanger_mono(dmax,curdel,depth,fb,invert,lfoshape)
  = _ <: _, (-:de.fdelay(dmax,curdel)) ~ *(fb) : _,
  *(select2(invert,depth,0-depth))
  : + : *(1/(1+depth));           // ideal for dc and reinforced sinusoids (in-phase summed signals)


process = ba.bypass1(fbp,flanger_mono_gui);

   // Kill the groups to save vertical space:
   meter_group(x) = flsg(x);
   ctl_group(x)  = flkg(x);
   del_group(x)  = flkg(x);
   lvl_group(x)  = flkf(x);

   flangeview = lfo(freq);

   flanger_mono_gui = attach(flangeview) : flanger_mono(dmax,curdel,depth,fb,invert,lfoshape);

   sinlfo(freq) = (1 + os.oscrs(freq))/2;
   trilfo(freq) = 1.0-abs(os.saw1(freq));
   lfo(f) = (lfoshape * trilfo(f)) + ((1-lfoshape) * sinlfo(f));

   dmax = 2048;
   odflange = 44; // ~1 ms at 44.1 kHz = min delay
   dflange  = ((dmax-1)-odflange)*del_group(vslider("[1] Delay [midi:ctrl 50][style:knob]", 0.22, 0, 1, 1));
   freq     = ctl_group(vslider("[1] Rate [midi:ctrl 51] [unit:Hz] [style:knob]", 0.5, 0, 10, 0.01)) : si.smooth(ba.tau2pole(freqT60/6.91));

   freqT60  = 0.15661;
   depth    = ctl_group(vslider("[3] Depth [midi:ctrl 52] [style:knob]", .75, 0, 1, 0.001)) : si.smooth(ba.tau2pole(depthT60/6.91));

   depthT60 = 0.15661;
   fb       = ctl_group(vslider("[5] Feedback [midi:ctrl 53] [style:knob]", 0, -0.995, 0.99, 0.001)) : si.smooth(ba.tau2pole(fbT60/6.91));

   fbT60    = 0.15661;
   lfoshape = ctl_group(vslider("[7] Waveshape [midi:ctrl 54] [style:knob]", 0, 0, 1, 0.001));
   curdel   = odflange+dflange*lfo(freq);

   fbp = 1-int(flsg(vslider("[0] Enable [midi:ctrl 102][style:knob]",0,0,1,1)));

   invert = flsg(vslider("[1] Invert [midi:ctrl 49][style:knob]",0,0,1,1):int);

