
declare name 		"zita_rev1";
import("effect.lib");

process = zita_rev1
	with {
		zita_rev1(x,y) = zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax,x,y)
				: out_eq : dry_wet(x,y) : out_level
		with {

		fsmax = 48000.0;  // highest sampling rate that will be used

		fdn_group(x) = hgroup(
			"[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER ALLPASS-COMB REVERBERATOR (8x8). See Faust's effect.lib for documentation and references]", x);

		in_group(x) = fdn_group(hgroup("[1] Input", x));

		rdel = in_group(vslider("[1] In Delay [unit:ms] [style:knob]
						[tooltip: Delay in ms before reverberation begins]",
						60,20,100,1));

		freq_group(x) = fdn_group(hgroup("[2] Decay Times in Bands (see tooltips)", x));

		f1 = freq_group(vslider("[1] LF X [unit:Hz] [style:knob] [scale:log]
			[tooltip: Crossover frequency (Hz) separating low and middle frequencies]",
			200, 50, 1000, 1));

		t60dc = freq_group(vslider("[2] Low RT60 [unit:s] [style:knob] [scale:log]
				[style:knob] [tooltip: T60 = time (in seconds) to decay 60dB in low-frequency band]",
				3, 1, 8, 0.1));

		t60m = freq_group(vslider("[3] Mid RT60 [unit:s] [style:knob] [scale:log]
				[tooltip: T60 = time (in seconds) to decay 60dB in middle band]",
				2, 1, 8, 0.1));

		f2 = freq_group(vslider("[4] HF Damping [unit:Hz] [style:knob] [scale:log]
			[tooltip: Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60]",
			6000, 1500, 0.49*fsmax, 1));

		out_eq = pareq_stereo(eq1f,eq1l,eq1q) : pareq_stereo(eq2f,eq2l,eq2q);
		// Zolzer style peaking eq (not used in zita-rev1) (filter.lib):
		// pareq_stereo(eqf,eql,Q) = peak_eq(eql,eqf,eqf/Q), peak_eq(eql,eqf,eqf/Q);
		// Regalia-Mitra peaking eq with "Q" hard-wired near sqrt(g)/2 (filter.lib):
		pareq_stereo(eqf,eql,Q) = peak_eq_rm(eql,eqf,tpbt), peak_eq_rm(eql,eqf,tpbt)
		with {
			tpbt = wcT/sqrt(max(0,g)); // tan(PI*B/SR), B bw in Hz (Q^2 ~ g/4)
			wcT = 2*PI*eqf/SR;  // peak frequency in rad/sample
			g = db2linear(eql); // peak gain
		};

		eq1_group(x) = fdn_group(hgroup("[3] RM Peaking Equalizer 1", x));

		eq1f = eq1_group(vslider("[1] Eq1 Freq [unit:Hz] [style:knob] [scale:log]
			[tooltip: Center-frequency of second-order Regalia-Mitra peaking equalizer section 1]",
			315, 40, 2500, 1));

		eq1l = eq1_group(vslider("[2] Eq1 Level [unit:dB] [style:knob]
			[tooltip: Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1]",
			0, -15, 15, 0.1));

		eq1q = eq1_group(vslider("[3] Eq1 Q [style:knob]
			[tooltip: Q = centerFrequency/bandwidth of second-order peaking equalizer section 1]",
			3, 0.1, 10, 0.1));

		eq2_group(x) = fdn_group(hgroup("[4] RM Peaking Equalizer 2", x));

		eq2f = eq2_group(vslider("[1] Eq2 Freq [unit:Hz] [style:knob] [scale:log]
			[tooltip: Center-frequency of second-order Regalia-Mitra peaking equalizer section 2]",
			1500, 160, 10000, 1));

		eq2l = eq2_group(vslider("[2] Eq2 Level [unit:dB] [style:knob]
			[tooltip: Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2]",
			0, -15, 15, 0.1));

		eq2q = eq2_group(vslider("[3] Eq2 Q [style:knob]
			[tooltip: Q = centerFrequency/bandwidth of second-order peaking equalizer section 2]",
			3, 0.1, 10, 0.1));

		out_group(x)  = fdn_group(hgroup("[5] Output", x));

		dry_wet(x,y) = *(wet) + dry*x, *(wet) + dry*y with {
			wet = 0.5*(drywet+1.0);
			dry = 1.0-wet;
		};

		drywet = out_group(vslider("[1] Dry/Wet Mix [style:knob]
			[tooltip: -1 = dry, 1 = wet]",
			0.4492, -1.0, 1.0, 0.01)) : smooth(0.999);

		out_level = *(gain),*(gain);

		gain = out_group(vslider("[2] Level [unit:dB] [style:knob]
			[tooltip: Output scale factor]", 16.79, -70, 40, 0.1))
			: db2linear : smooth(0.999);

		};
	};
