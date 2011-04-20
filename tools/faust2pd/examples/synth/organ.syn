
declare name "organ -- a simple additive synth";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

vol	= hslider("vol", 0.3, 0, 10, 0.01);	// %
pan	= hslider("pan", 0.5, 0, 1, 0.01);	// %
attack	= hslider("attack", 0.01, 0, 1, 0.001);	// sec
decay	= hslider("decay", 0.3, 0, 1, 0.001);	// sec
sustain = hslider("sustain", 0.5, 0, 1, 0.01);	// %
release = hslider("release", 0.2, 0, 1, 0.001);	// sec
freq	= nentry("freq", 440, 20, 20000, 1);	// Hz
gain	= nentry("gain", 0.3, 0, 10, 0.01);	// %
gate	= button("gate");			// 0/1

// relative amplitudes of the different partials

amp(1)	= hslider("amp1", 1.0, 0, 3, 0.01);
amp(2)	= hslider("amp2", 0.5, 0, 3, 0.01);
amp(3)	= hslider("amp3", 0.25, 0, 3, 0.01);

// additive synth: 3 sine oscillators with adsr envelop

partial(i) = amp(i+1)*osc((i+1)*freq);

process	= sum(i, 3, partial(i))
  * (gate : vgroup("1-adsr", adsr(attack, decay, sustain, release)))
  * gain : vgroup("2-master", *(vol) : panner(pan));
