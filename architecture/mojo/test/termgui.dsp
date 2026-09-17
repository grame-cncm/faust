declare name "termgui";
declare description "Terminal GUI integration test";

rate = max(1, fconstant(int fSamplingFreq, <math.h>));

freq = hslider("freq[unit:Hz]", 220, 20, 2000, 1);
gain = vslider("gain[unit:dB]", -36, -80, 0, 1);
det = nentry("det[unit:Hz]", 0, -20, 20, 0.1);
mute = checkbox("mute");
trig = button("trig");

phase = (+ : %(1.0)) ~ _;
osc(f) = f / rate : phase : *(6.283185307179586) : sin;
amp = pow(10, gain / 20);
sig = (osc(freq + det) + trig * 0.25 * osc((freq + det) * 2)) * amp * (1 - mute);

fall = exp(-1 / (0.05 * rate));
level = abs : max ~ *(fall) : max(0.0001) : log10 : *(20);
out1 = _ <: _, (level : hbargraph("out1[unit:dB]", -80, 0)) : attach;
out2 = _ <: _, (level : vbargraph("out2[unit:dB]", -80, 0)) : attach;

process = tgroup("term", hgroup("ctrl", sig) <: vgroup("out", (out1, out2)));
