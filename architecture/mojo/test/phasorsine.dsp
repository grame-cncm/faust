declare name "phasorsine";

rate = max(1, fconstant(int fSamplingFreq, <math.h>));
freq = hslider("freq[unit:Hz]", 220, 20, 2000, 1);
gain = hslider("gain", 0.1, 0, 0.5, 0.005);
mute = checkbox("mute");

phase = (+ : %(1.0)) ~ _;
osc(f) = f / rate : phase : *(6.283185307179586) : sin;

process = osc(freq) * gain * (1 - mute) <: _, _;
