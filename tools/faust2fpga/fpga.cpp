
#include <algorithm>
#include <ap_int.h>
#include <cmath>

// The Faust compiler will insert the C code here
<<includeIntrinsic>>

<<includeclass>>

#ifndef SAMPLE_RATE
#define SAMPLE_RATE 48000
#endif

#if FAUST_INPUTS > 2
#warning More than 2 inputs defined. Only the first 2 will be used!
#endif

#if FAUST_OUTPUTS < 1
#error At least one output is required!
#endif

#if FAUST_OUTPUTS > 2
#warning More than 2 outputs defined. Only the first 2 will be used!
#endif

static char initialized = 0;

// DSP struct
static mydsp DSP;

// Control arrays
static int icontrol[FAUST_INT_CONTROLS];
static FAUSTFLOAT fcontrol[FAUST_REAL_CONTROLS];

// DSP arrays
static int izone[FAUST_INT_ZONE];
static FAUSTFLOAT fzone[FAUST_FLOAT_ZONE];

void faust_v4(ap_int<24> in_left, ap_int<24> in_right, ap_int<24> *out_left,
           ap_int<24> *out_right, 
           bool bypass_dsp, bool bypass_faust)
{

	if (initialized == 0) {
		initmydsp(&DSP, SAMPLE_RATE, izone, fzone);
		initialized = 1;
	}

	// Update control
	controlmydsp(&DSP, icontrol, fcontrol, izone, fzone);

	// Allocate 'inputs' and 'outputs' for 'compute' method
	FAUSTFLOAT inputs[FAUST_INPUTS], outputs[FAUST_OUTPUTS];

	const float scaleFactor = 8388608.0f;

	// Prepare inputs for 'compute' method
#if FAUST_INPUTS > 0
	inputs[0] =  in_left.to_float() / scaleFactor;
#endif
#if FAUST_INPUTS > 1
	inputs[1] =  in_right.to_float() / scaleFactor;
#endif

	computemydsp(&DSP, inputs, outputs, icontrol, fcontrol, izone, fzone);

	// Copy produced outputs
	*out_left = ap_int<24>(outputs[0] * scaleFactor);
#if FAUST_OUTPUTS > 1
	*out_right = ap_int<24>(outputs[1] * scaleFactor);
#else
	*out_right = ap_int<24>(outputs[0] * scaleFactor);
#endif
}
