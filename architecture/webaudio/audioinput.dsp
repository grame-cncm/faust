import("stdfaust.lib");

vol = hslider("volume [unit:dB]", 0, -96, 0, 0.1) : ba.db2linear : si.smoo;
freq = hslider("freq [unit:Hz]", 1000, 20, 24000, 1) : si.smoo;

flanger(p,wet,depth) = _ <: de.delay(256,d)*wet,_ :> /(2)
with{
    d = (os.osc(p) + 1)*127*depth;
};

tremolo(fr,dep) = _*(1-(os.osc(fr)*0.5 + 0.5)*dep);
f = hslider("ffreq [unit:Hz]",10,0.1,100,0.01);
w = hslider("fwet",0.5,0,1,0.01);
d = hslider("fdepth",0.5,0,1,0.01);

tf = hslider("tfreq [unit:Hz]",10,0.1,100,0.01);
td = hslider("tdepth",0.5,0,1,0.01);

gain = hslider("gain [knob:2] [midi:ctrl 7]", 0.5, 0, 1, 0.01);
gate = button("gate [switch:1]");

process = + :  flanger(f,w,d) : tremolo(tf,td) <: _,_;