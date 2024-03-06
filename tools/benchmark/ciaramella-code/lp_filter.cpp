#include "lp_filter.h"


static const float C_3 = 0.000001f;
static const float lp_filter_extra_0 = (2.0f * 3.141592653589793f);
static const float al_5 = 0.0f;


void lp_filter::reset()
{
	firstRun = 1;
}

void lp_filter::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	Rr_5 = (0.5f / (C_3 * fs));
}

void lp_filter::process(float *x, float *y_out_, int nSamples)
{
	if (firstRun) {
		cutoff_CHANGED = 1;
	}
	else {
		cutoff_CHANGED = cutoff != cutoff_z1;
	}
	
	if (cutoff_CHANGED) {
		lp_filter_extra_1 = (Rr_5 / ((1.0f / ((lp_filter_extra_0 * ((0.1f + (0.3f * cutoff)) * fs)) * 0.000001f)) + Rr_5));
    }
	
	cutoff_CHANGED = 0;

	if (firstRun) {
		
		_delayed_2 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float bC = _delayed_2;
		const float ar_5 = bC;
		const float aC = (ar_5 - (lp_filter_extra_1 *(ar_5 + ((2.0f * x[i]) + ar_5))));
		const float y = (0.5f * (aC + bC));
		
		_delayed_2 = aC;
		
		
		y_out_[i] = y;
	}

	
	cutoff_z1 = cutoff;
	firstRun = 0;
}


float lp_filter::getcutoff() {
	return cutoff;
}
void lp_filter::setcutoff(float value) {
	cutoff = value;
}

