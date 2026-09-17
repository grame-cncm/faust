declare name "Thru Zero Flanger";
declare description "Stereo Thru Zero Flanger - warning can ZERO the sound!";
declare author "Oli Larkin (contact@olilarkin.co.uk)";
declare copyright "Oliver Larkin";
declare version "0.1";
declare licence "GPL";

import("effect.lib"); 
import("filter.lib"); 
import("math.lib");

lutsize = 1 << 9;
maxdtms = 20;
smooth_time = 0.005;

rate = hslider("Rate [unit:hz] [OWL:PARAMETER_A]", 0.1, 0., 1, 0.001);
dt = hslider("Delay [unit:ms] [OWL:PARAMETER_B]", 10., 0.5, maxdtms, 0.01) : smooth(tau2pole(smooth_time));
lr_offset = hslider("L-R Offset [OWL:PARAMETER_C]", 0, 0., 1, 0.001) *(0.5) : smooth(tau2pole(smooth_time));
depth = hslider("Depth [unit:%] [OWL:PARAMETER_D]", 20., 3., 100., 1) *(0.01): smooth(tau2pole(smooth_time));

tbllookup(phase)=s1+d*(s2-s1)
with {
  i = int(phase * lutsize); 
  d = decimal(phase * lutsize);
  triangle_table = triangle_phasor(float(time)/float(lutsize));
  triangle_phasor(t) = ((0<=t) & (t<=0.5))*((2*t-0.5)/0.5) + ((0.5<t) & (t<=1.))*((1.5-2*t)/0.5);
  s1 = rdtable(lutsize+1, triangle_table, i);
  s2 = rdtable(lutsize+1, triangle_table, i+1);
};

tzflangeunit(x, offset) = staticdelay(x) + moddelay(x)
with {
  dtsamples = dt * (float(SR)/1000.);
  staticdelay = fdelay(4096, dtsamples);
  moddelay = fdelay(4096, modulation) *(-1.); // inverted 
  phasor = fmod((rate/float(SR) : (+ : decimal) ~ _)+offset, 1.);
  modulation = dtsamples + ((tbllookup(phasor)*depth) * dtsamples);
};

process(l,r) = tzflangeunit(l, 0.), tzflangeunit(r, lr_offset);