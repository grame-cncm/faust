#include "lp_filter3.h"


static const float al_C_4 = 0.000001f;
static const float lp_filter3_extra_0 = (2.0f * 3.141592653589793f);
static const float al_6 = 0.0f;
static const float C_9 = 0.000001f;
static const float lp_filter3_extra_2 = (2.0f * 3.141592653589793f);
static const float al_11 = 0.0f;
static const float C_14 = 0.000001f;
static const float lp_filter3_extra_4 = (2.0f * 3.141592653589793f);
static const float al_16 = 0.0f;


void lp_filter3::reset()
{
	firstRun = 1;
}

void lp_filter3::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	Rr_6 = (0.5f / (al_C_4 * fs));
	Rr_11 = (0.5f / (C_9 * fs));
	Rr_16 = (0.5f / (C_14 * fs));
	
}

void lp_filter3::process(float *x, float *y_out_, int nSamples)
{
	if (firstRun) {
		cutoff_CHANGED = 1;
		vol_CHANGED = 1;
	}
	else {
		cutoff_CHANGED = cutoff != cutoff_z1;
		vol_CHANGED = vol != vol_z1;
	}
	
	if (cutoff_CHANGED) {
		lp_filter3_extra_1 = (Rr_6 / ((1.0f / ((lp_filter3_extra_0 * ((0.1f + (0.3f * cutoff)) * fs)) * 0.000001f)) + Rr_6));
		lp_filter3_extra_3 = (Rr_11 / ((1.0f / ((lp_filter3_extra_2 * ((0.1f + (0.3f * cutoff)) * fs)) * 0.000001f)) + Rr_11));
		lp_filter3_extra_5 = (Rr_16 / ((1.0f / ((lp_filter3_extra_4 * ((0.1f + (0.3f * cutoff)) * fs)) * 0.000001f)) + Rr_16));
	}
	
	cutoff_CHANGED = 0;
	vol_CHANGED = 0;

	if (firstRun) {
		
		_delayed_6 = 0.0f;
		_delayed_7 = 0.0f;
		_delayed_8 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float bC_2 = _delayed_6;
		const float ar_6 = bC_2;
		const float bC_7 = _delayed_7;
		const float ar_11 = bC_7;
		const float bC_12 = _delayed_8;
		const float ar_16 = bC_12;
		const float aC_12 = (ar_16 - (lp_filter3_extra_5 * ((al_16 + ar_16) + ((2.0f * x[i]) - -((al_16 + ar_16))))));
		const float aC_7 = (ar_11 - (lp_filter3_extra_3 * ((al_11 + ar_11) + ((2.0f * (0.5f * (aC_12 + bC_12))) - -((al_11 + ar_11))))));
		const float aC_2 = (ar_6 - (lp_filter3_extra_1 * ((al_6 + ar_6) + ((2.0f * (0.5f * (aC_7 + bC_7))) - -((al_6 + ar_6))))));
		const float y = ((0.5f * (aC_2 + bC_2)) * vol);
		
		_delayed_6 = aC_2;
		_delayed_7 = aC_7;
		_delayed_8 = aC_12;
		
		
		y_out_[i] = y;
	}

	
	cutoff_z1 = cutoff;
	vol_z1 = vol;
	firstRun = 0;
}


float lp_filter3::getcutoff() {
	return cutoff;
}
void lp_filter3::setcutoff(float value) {
	cutoff = value;
}

float lp_filter3::getvol() {
	return vol;
}
void lp_filter3::setvol(float value) {
	vol = value;
}

