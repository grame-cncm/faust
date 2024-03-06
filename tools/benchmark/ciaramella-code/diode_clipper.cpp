#include "diode_clipper.h"


static const float diode_clipper_extra_0 = (1e-8f * 2200.0f);
static const float k1 = (1.0f / (2200.0f * 1e-8f));
static const float diode_clipper_extra_1 = (1e-16f * 2200.0f);
static const float k4 = (1.0f / 0.026f);
static const float diode_clipper_extra_2 = (1e-16f * 2200.0f);


void diode_clipper::reset()
{
	firstRun = 1;
}

void diode_clipper::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	const float B0 = (2.0f * fs);
	k2 = (diode_clipper_extra_0 / (((B0 * 1e-8f) * 2200.0f) + 1.0f));
	k3 = (diode_clipper_extra_1 / (((B0 * 1e-8f) * 2200.0f) + 1.0f));
	k5 = log((diode_clipper_extra_2 / ((((B0 * 1e-8f) * 2200.0f) + 1.0f) * 0.026f)));
	k6 = (-(B0) - (1.0f * B0));
	
}

void diode_clipper::process(float *x, float *y_out_, int nSamples)
{
	if (firstRun) {
	}
	else {
	}
	
	

	if (firstRun) {
		
		_delayed_3 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float p_z1 = _delayed_3;
		const float q = ((k1 * x[i]) - p_z1);
		const float r = sign(q);
		const float w = ((k2 * q) + (k3 * r));
		const float y = (w - ((0.026f * r) * omega((((k4 * r) * w) + k5))));
		
		_delayed_3 = ((k6 * x[i]) - (1.0f * p_z1));
		
		
		y_out_[i] = y;
	}

	
	firstRun = 0;
}


