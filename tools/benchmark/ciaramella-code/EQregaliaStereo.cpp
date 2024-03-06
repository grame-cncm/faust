#include "EQregaliaStereo.h"


static const float EQregaliaStereo_extra_0 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_2 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_4 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_7 = (3.141592653589793f * 200.0f);
static const float EQregaliaStereo_extra_9 = (3.141592653589793f * 5000.0f);
static const float EQregaliaStereo_extra_11 = (3.141592653589793f * 1789.0f);
static const float EQregaliaStereo_extra_12 = (3.141592653589793f * 1789.0f);
static const float EQregaliaStereo_extra_13 = -(0.4643843937958486f);
static const float EQregaliaStereo_extra_14 = ((2.0f * 3.141592653589793f) * 1000.0f);
static const float EQregaliaStereo_extra_17 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_19 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_21 = (40.0f * 0.5f);
static const float EQregaliaStereo_extra_24 = (3.141592653589793f * 200.0f);
static const float EQregaliaStereo_extra_26 = (3.141592653589793f * 5000.0f);
static const float EQregaliaStereo_extra_28 = (3.141592653589793f * 1789.0f);
static const float EQregaliaStereo_extra_29 = (3.141592653589793f * 1789.0f);
static const float EQregaliaStereo_extra_30 = -(0.4643843937958486f);
static const float EQregaliaStereo_extra_31 = ((2.0f * 3.141592653589793f) * 1000.0f);
static const float gain_4_I = ((1 * 40.0f) - (40.0f * 0.5f));
static const float gain_6_I = ((0 * 40.0f) - (40.0f * 0.5f));
static const float gain_11_I = ((1 * 40.0f) - (40.0f * 0.5f));
static const float gain_13_I = ((0 * 40.0f) - (40.0f * 0.5f));


void EQregaliaStereo::reset()
{
	firstRun = 1;
}

void EQregaliaStereo::setSampleRate(float sampleRate)
{
	fs = sampleRate;
	const float z_3 = (EQregaliaStereo_extra_7 / fs);
	a_3 = ((z_3 - 1.0f) / (z_3 + 1.0f));
	const float z_5 = (EQregaliaStereo_extra_9 / fs);
	a_5 = ((z_5 - 1.0f) / (z_5 + 1.0f));
	a_7 = ((1.0f - (EQregaliaStereo_extra_11 / fs)) / (1.0f + (EQregaliaStereo_extra_12 / fs)));
	const float z_7 = (EQregaliaStereo_extra_14 / fs);
	const float b_7 = -(((((EQregaliaStereo_extra_13 * z_7) * z_7) - (0.01348369482970019f * z_7)) + 1.000898384794433f));
	EQregaliaStereo_extra_15 = (b_7 * (1.0f + a_7));
	EQregaliaStereo_extra_16 = (b_7 * (1.0f + a_7));
	const float z_10 = (EQregaliaStereo_extra_24 / fs);
	a_10 = ((z_10 - 1.0f) / (z_10 + 1.0f));
	const float z_12 = (EQregaliaStereo_extra_26 / fs);
	a_12 = ((z_12 - 1.0f) / (z_12 + 1.0f));
	a_14 = ((1.0f - (EQregaliaStereo_extra_28 / fs)) / (1.0f + (EQregaliaStereo_extra_29 / fs)));
	const float z_14 = (EQregaliaStereo_extra_31 / fs);
	const float b_14 = -(((((EQregaliaStereo_extra_30 * z_14) * z_14) - (0.01348369482970019f * z_14)) + 1.000898384794433f));
	EQregaliaStereo_extra_32 = (b_14 * (1.0f + a_14));
	EQregaliaStereo_extra_33 = (b_14 * (1.0f + a_14));
	
}

void EQregaliaStereo::process(float *xL, float *xR, float *yL_out_, float *yR_out_, int nSamples)
{
	if (firstRun) {
		low_CHANGED = 1;
		high_CHANGED = 1;
		peak_CHANGED = 1;
	}
	else {
		low_CHANGED = low != low_z1;
		high_CHANGED = high != high_z1;
		peak_CHANGED = peak != peak_z1;
	}
	
	if (peak_CHANGED) {
		const float gain_8 = ((peak * 40.0f) - EQregaliaStereo_extra_0);
		const float K_7 = (1.005216266655582f + (gain_8 * (0.1154462118686094f + (gain_8 * (0.006357962473527189f + (gain_8 * (0.0002473043497433871f + (gain_8 * (0.000009275409030059003f + (gain_8 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_1 = ((1.0f + K_7) / 2.0f);
		EQregaliaStereo_extra_10 = ((1.0f - K_7) / 2.0f);
		const float gain_15 = ((peak * 40.0f) - EQregaliaStereo_extra_17);
		const float K_14 = (1.005216266655582f + (gain_15 * (0.1154462118686094f + (gain_15 * (0.006357962473527189f + (gain_15 * (0.0002473043497433871f + (gain_15 * (0.000009275409030059003f + (gain_15 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_18 = ((1.0f + K_14) / 2.0f);
		EQregaliaStereo_extra_27 = ((1.0f - K_14) / 2.0f);
	}
	if (high_CHANGED) {
		const float gain_6 = ((high * 40.0f) - EQregaliaStereo_extra_2);
		const float K_5 = (1.005216266655582f + (gain_6 * (0.1154462118686094f + (gain_6 * (0.006357962473527189f + (gain_6 * (0.0002473043497433871f + (gain_6 * (0.000009275409030059003f + (gain_6 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_3 = ((1.0f + K_5) / 2.0f);
		EQregaliaStereo_extra_8 = ((1.0f - K_5) / 2.0f);
		const float gain_13 = ((high * 40.0f) - EQregaliaStereo_extra_19);
		const float K_12 = (1.005216266655582f + (gain_13 * (0.1154462118686094f + (gain_13 * (0.006357962473527189f + (gain_13 * (0.0002473043497433871f + (gain_13 * (0.000009275409030059003f + (gain_13 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_20 = ((1.0f + K_12) / 2.0f);
		EQregaliaStereo_extra_25 = ((1.0f - K_12) / 2.0f);
	}
	if (low_CHANGED) {
		const float gain_4 = ((low * 40.0f) - EQregaliaStereo_extra_4);
		const float K_3 = (1.005216266655582f + (gain_4 * (0.1154462118686094f + (gain_4 * (0.006357962473527189f + (gain_4 * (0.0002473043497433871f + (gain_4 * (0.000009275409030059003f + (gain_4 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_5 = ((K_3 + 1.0f) / 2.0f);
		EQregaliaStereo_extra_6 = ((K_3 - 1.0f) / 2.0f);
		const float gain_11 = ((low * 40.0f) - EQregaliaStereo_extra_21);
		const float K_10 = (1.005216266655582f + (gain_11 * (0.1154462118686094f + (gain_11 * (0.006357962473527189f + (gain_11 * (0.0002473043497433871f + (gain_11 * (0.000009275409030059003f + (gain_11 * 2.061300092186973e-7f))))))))));
		EQregaliaStereo_extra_22 = ((K_10 + 1.0f) / 2.0f);
		EQregaliaStereo_extra_23 = ((K_10 - 1.0f) / 2.0f);
	}
	
	low_CHANGED = 0;
	high_CHANGED = 0;
	peak_CHANGED = 0;

	if (firstRun) {
		
		_delayed_34 = 0;
		_delayed_35 = 0.0f;
		_delayed_36 = (((((1.005216266655582f + (gain_4_I * (0.1154462118686094f + (gain_4_I * (0.006357962473527189f + (gain_4_I * (0.0002473043497433871f + (gain_4_I * (0.000009275409030059003f + (gain_4_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f);
		_delayed_37 = 0.0f;
		_delayed_38 = ((((1.0f + (1.005216266655582f + (gain_6_I * (0.1154462118686094f + (gain_6_I * (0.006357962473527189f + (gain_6_I * (0.0002473043497433871f + (gain_6_I * (0.000009275409030059003f + (gain_6_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_4_I * (0.1154462118686094f + (gain_4_I * (0.006357962473527189f + (gain_4_I * (0.0002473043497433871f + (gain_4_I * (0.000009275409030059003f + (gain_4_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_39 = ((((1.0f + (1.005216266655582f + (gain_6_I * (0.1154462118686094f + (gain_6_I * (0.006357962473527189f + (gain_6_I * (0.0002473043497433871f + (gain_6_I * (0.000009275409030059003f + (gain_6_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_4_I * (0.1154462118686094f + (gain_4_I * (0.006357962473527189f + (gain_4_I * (0.0002473043497433871f + (gain_4_I * (0.000009275409030059003f + (gain_4_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_40 = ((((1.0f + (1.005216266655582f + (gain_6_I * (0.1154462118686094f + (gain_6_I * (0.006357962473527189f + (gain_6_I * (0.0002473043497433871f + (gain_6_I * (0.000009275409030059003f + (gain_6_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_4_I * (0.1154462118686094f + (gain_4_I * (0.006357962473527189f + (gain_4_I * (0.0002473043497433871f + (gain_4_I * (0.000009275409030059003f + (gain_4_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_41 = 0.0f;
		_delayed_42 = 0.0f;
		_delayed_43 = 0.0f;
		_delayed_44 = 0;
		_delayed_45 = 0.0f;
		_delayed_46 = (((((1.005216266655582f + (gain_11_I * (0.1154462118686094f + (gain_11_I * (0.006357962473527189f + (gain_11_I * (0.0002473043497433871f + (gain_11_I * (0.000009275409030059003f + (gain_11_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f);
		_delayed_47 = 0.0f;
		_delayed_48 = ((((1.0f + (1.005216266655582f + (gain_13_I * (0.1154462118686094f + (gain_13_I * (0.006357962473527189f + (gain_13_I * (0.0002473043497433871f + (gain_13_I * (0.000009275409030059003f + (gain_13_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_11_I * (0.1154462118686094f + (gain_11_I * (0.006357962473527189f + (gain_11_I * (0.0002473043497433871f + (gain_11_I * (0.000009275409030059003f + (gain_11_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_49 = ((((1.0f + (1.005216266655582f + (gain_13_I * (0.1154462118686094f + (gain_13_I * (0.006357962473527189f + (gain_13_I * (0.0002473043497433871f + (gain_13_I * (0.000009275409030059003f + (gain_13_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_11_I * (0.1154462118686094f + (gain_11_I * (0.006357962473527189f + (gain_11_I * (0.0002473043497433871f + (gain_11_I * (0.000009275409030059003f + (gain_11_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_50 = ((((1.0f + (1.005216266655582f + (gain_13_I * (0.1154462118686094f + (gain_13_I * (0.006357962473527189f + (gain_13_I * (0.0002473043497433871f + (gain_13_I * (0.000009275409030059003f + (gain_13_I * 2.061300092186973e-7f))))))))))) / 2.0f) * (((((1.005216266655582f + (gain_11_I * (0.1154462118686094f + (gain_11_I * (0.006357962473527189f + (gain_11_I * (0.0002473043497433871f + (gain_11_I * (0.000009275409030059003f + (gain_11_I * 2.061300092186973e-7f)))))))))) + 1.0f) / 2.0f) * 0) + 0.0f)) + 0.0f);
		_delayed_51 = 0.0f;
		_delayed_52 = 0.0f;
		_delayed_53 = 0.0f;
	}

	for (int i = 0; i < nSamples; i++) {
		
		const float x_3 = xL[i];
		const float u_3 = ((EQregaliaStereo_extra_6 * ((a_3 * x_3) + _delayed_34)) - (a_3 * _delayed_35));
		const float x_5 = ((EQregaliaStereo_extra_5 * x_3) + u_3);
		const float u_5 = ((EQregaliaStereo_extra_8 * ((a_5 * x_5) + _delayed_36)) - (a_5 * _delayed_37));
		const float x_7 = ((EQregaliaStereo_extra_3 * x_5) + u_5);
		const float u_7 = (((EQregaliaStereo_extra_10 * (((a_7 * x_7) + (EQregaliaStereo_extra_15 * _delayed_38)) + _delayed_40)) - (EQregaliaStereo_extra_16 * _delayed_41)) - (a_7 * _delayed_43));
		const float yL = ((EQregaliaStereo_extra_1 * x_7) + u_7);
		const float x_10 = xR[i];
		const float u_10 = ((EQregaliaStereo_extra_23 * ((a_10 * x_10) + _delayed_44)) - (a_10 * _delayed_45));
		const float x_12 = ((EQregaliaStereo_extra_22 * x_10) + u_10);
		const float u_12 = ((EQregaliaStereo_extra_25 * ((a_12 * x_12) + _delayed_46)) - (a_12 * _delayed_47));
		const float x_14 = ((EQregaliaStereo_extra_20 * x_12) + u_12);
		const float u_14 = (((EQregaliaStereo_extra_27 * (((a_14 * x_14) + (EQregaliaStereo_extra_32 * _delayed_48)) + _delayed_50)) - (EQregaliaStereo_extra_33 * _delayed_51)) - (a_14 * _delayed_53));
		const float yR = ((EQregaliaStereo_extra_18 * x_14) + u_14);
		
		_delayed_34 = x_3;
		_delayed_35 = u_3;
		_delayed_36 = x_5;
		_delayed_37 = u_5;
		_delayed_38 = x_7;
		_delayed_39 = x_7;
		_delayed_40 = _delayed_39;
		_delayed_41 = u_7;
		_delayed_42 = u_7;
		_delayed_43 = _delayed_42;
		_delayed_44 = x_10;
		_delayed_45 = u_10;
		_delayed_46 = x_12;
		_delayed_47 = u_12;
		_delayed_48 = x_14;
		_delayed_49 = x_14;
		_delayed_50 = _delayed_49;
		_delayed_51 = u_14;
		_delayed_52 = u_14;
		_delayed_53 = _delayed_52;
		
		
		yL_out_[i] = yL;
		yR_out_[i] = yR;
	}

	
	low_z1 = low;
	high_z1 = high;
	peak_z1 = peak;
	firstRun = 0;
}


float EQregaliaStereo::getlow() {
	return low;
}
void EQregaliaStereo::setlow(float value) {
	low = value;
}

float EQregaliaStereo::gethigh() {
	return high;
}
void EQregaliaStereo::sethigh(float value) {
	high = value;
}

float EQregaliaStereo::getpeak() {
	return peak;
}
void EQregaliaStereo::setpeak(float value) {
	peak = value;
}

