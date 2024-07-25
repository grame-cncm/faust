declare name "churchOrgan";
declare author "Remi Chapelle";

import("stdfaust.lib");

// GUI
f = hslider("[00]freq[unit:Hz]",440,50,1000,0.1);
g = hslider("[01]gain",1,0,1,0.01);
t = button("[10]gate") : si.smoo;
p8 = hslider("[03]gain 8ve partial",1,0,1,0.01);
p5 = hslider("[04]gain 5th partial",1,0,1,0.01);
p3 = hslider("[05]gain 3d partial",1,0,1,0.01);
px = hslider("[06]gain other partials",0.05,0,1,0.01);
p0 = hslider("[02]gain fundamental",1,0,1,0.01);
psub = hslider("[07]gain lower octave",1,0,1,0.01);
nog = hslider("[08]noise gain",0.01,0,1,0.001);
pg = hslider("[09]gain preset",1,0,1,0.01);

// Reverb
r = dm.zita_light;

// Instrument
orgue = os.osc(f)       *p0
        + os.osc(f*2)   *p8
        + os.osc(f*0.5) *psub*0.5
        + os.osc(f*1.5) *p5*0.3
        + os.osc(f*3)   *p5*0.9
        + os.osc(f*4)   *p8*0.8
        + os.osc(f*5)   *p3*0.7
        + os.osc(f*6)   *p5*0.6
        + os.osc(f*7)   *px*0.5
        + os.osc(f*8)   *p8*0.6
        + os.osc(f*9)   *px*0.3
        + os.osc(f*10)  *p3*0.2
        + os.osc(f*11)  *px*0.15
        + os.osc(f*12)  *p5*0.1
        + os.osc(f*13)  *px*0.8
        + os.osc(f*14)  *px*0.6
        + os.osc(f*15)  *px*0.5
        + os.osc(f*16)  *p8*0.4
        + no.noise*nog;

process = orgue*g*t <: r;
