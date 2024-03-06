#include "lowshelffilter.h"


static const float lowshelffilter_extra_2 = (3.141592653589793f * 200.0f);


void lowshelffilter::reset()
{
	firstRun = 1;
}

void lowshelffilter::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	const float z = (lowshelffilter_extra_2 / fs);
	a = ((z - 1.0f) / (z + 1.0f));
	
}

void lowshelffilter::process(float *x, float *y_out_, int nSamples)
{
	if (firstRun) {
		gain_CHANGED = 1;
	}
	else {
		gain_CHANGED = gain != gain_z1;
	}
	
	if (gain_CHANGED) {
		const float K = gain;
		lowshelffilter_extra_0 = ((K + 1.0f) / 2.0f);
		lowshelffilter_extra_1 = ((K - 1.0f) / 2.0f);
	}
	
	gain_CHANGED = 0;

	if (firstRun) {
		
		_delayed_3 = 0;
		_delayed_4 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float u = ((lowshelffilter_extra_1 * ((a * x[i]) + _delayed_3)) - (a * _delayed_4));
		const float y = ((lowshelffilter_extra_0 * x[i]) + u);
		
		_delayed_3 = x[i];
		_delayed_4 = u;
		
		
		y_out_[i] = y;
	}

	
	gain_z1 = gain;
	firstRun = 0;
}


float lowshelffilter::getgain() {
	return gain;
}
void lowshelffilter::setgain(float value) {
	gain = value;
}

