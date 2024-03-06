#include "lp_filter2.h"


static const float C_6 = 0.000001f;
static const float lp_filter2_extra_0 = (2.0f * 3.141592653589793f);
static const float al_7 = 0.0f;
static const float C_4 = 0.000001f;
static const float al_9 = 0.0f;


void lp_filter2::reset()
{
	firstRun = 1;
}

void lp_filter2::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	Rr_7 = (0.5f / (C_6 * fs));
	Rr_8 = (0.5f / (C_4 * fs));
	Gr_8 = (1.0f / Rr_8);
	
}

void lp_filter2::process(float *x, float *y_out_, int nSamples)
{
	if (firstRun) {
		cutoff_CHANGED = 1;
	}
	else {
		cutoff_CHANGED = cutoff != cutoff_z1;
	}
	
	if (cutoff_CHANGED) {
		const float R = (1.0f / ((lp_filter2_extra_0 * ((0.01f + (0.3f * cutoff)) * fs)) * 0.000001f));
		const float Rl_7 = R;
		lp_filter2_extra_1 = (Rr_7 / (Rl_7 + Rr_7));
		const float Rl_8 = (Rl_7 + Rr_7);
		const float Gl_8 = (1.0f / Rl_8);
		const float R0_8 = ((Rl_8 * Rr_8) / (Rl_8 + Rr_8));
		dl_8 = ((2.0f * Gl_8) / (((1.0f / R0_8) + Gl_8) + Gr_8));
		lp_filter2_extra_2 = (dl_8 - 1.0f);
		dr_8 = (1.0f - dl_8);
		const float Rr_9 = R0_8;
		lp_filter2_extra_3 = (Rr_9 / (R + Rr_9));
		lp_filter2_extra_5 = (dr_8 - 1.0f);
	}
	
	cutoff_CHANGED = 0;

	if (firstRun) {
		
		_delayed_4 = 0.0f;
		_delayed_6 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float bC2 = _delayed_4;
		const float ar_7 = bC2;
		const float al_8 = -((al_7 + ar_7));
		const float ar_8 = _delayed_6;
		const float ar_9 = ((dl_8 * al_8) + (dr_8 * ar_8));
		const float au_8 = (ar_9 - (lp_filter2_extra_3 * ((al_9 + ar_9) + ((2.0f * x[i]) - -((al_9 + ar_9))))));
		const float aC2 = (ar_7 - (lp_filter2_extra_1 * ((al_7 + ar_7) + (((lp_filter2_extra_2 * al_8) + (dr_8 * ar_8)) + au_8))));
		const float y = (0.5f * (aC2 + bC2));
		
		_delayed_4 = aC2;
		_delayed_6 = (((dl_8 * al_8) + (lp_filter2_extra_5 * ar_8)) + au_8);
		
		
		y_out_[i] = y;
	}

	
	cutoff_z1 = cutoff;
	firstRun = 0;
}


float lp_filter2::getcutoff() {
	return cutoff;
}
void lp_filter2::setcutoff(float value) {
	cutoff = value;
}

