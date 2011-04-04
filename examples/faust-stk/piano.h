//Parameters for piano.dsp
//©Romain Michon (rmichon@ccrma.stanford.edu), 2011
//licence: FAUST-STK

#include "instrument.h"

#define _LOOKUP_TABLE_H_

//**********************************************************************

extern LookupTable noteOffDelayTime;

/* pianoDriverC.sb */
/* Coupling Filter */

extern LookupTable singleStringDecayRate;
extern LookupTable singleStringZero;
extern LookupTable singleStringPole;
extern LookupTable releaseLoopGain;
extern LookupTable detuningHz;
extern LookupTable stiffnessCoefficient;
extern LookupTable strikePosition;
extern LookupTable EQGain;
extern LookupTable EQBandwidthFactor;

/* PianoDriverA */
/* HammerFilter */
extern LookupTable loudPole;
extern LookupTable softPole;
extern LookupTable normalizedVelocity;
extern LookupTable loudGain;
extern LookupTable softGain;


/* Soundboard */
extern LookupTable sustainPedalLevel;
extern LookupTable DryTapAmpT60;
extern double DryTapAmpCurrent;
extern LookupTable DCBa1;


/* pianoDriverB */
/* High Notes */
extern LookupTable secondStageAmpRatio;
extern LookupTable r1_1db;
extern LookupTable r1_2db;
extern LookupTable r2db;
extern LookupTable r3db;
extern LookupTable secondPartialFactor;
extern LookupTable thirdPartialFactor;
extern LookupTable bq4_gEarBalled;

//***************************************************************

/* PianoDriver.sb */
double noteOffDelayTime_points[5*2] = {
	89.000,3.000,
	93.000,2.000,
	95.000,1.500,
	99.782,1.020,
	108.000,0.300,
};
LookupTable noteOffDelayTime(&noteOffDelayTime_points[0], 5);

/* pianoDriverC.sb */
/* Coupling Filter */

double singleStringDecayRate_points[17*2] = {
	21.000,-1.500,
	24.000,-1.500,
	28.000,-1.500,
	29.000,-6.000,
	36.000,-6.000,
	42.000,-6.100,
	48.000,-7.000,
	52.836,-7.000,
	60.000,-7.300,
	66.000,-7.700,
	72.000,-8.000,
	78.000,-8.800,
	84.000,-10.000,
	88.619,-11.215,
	92.368,-12.348,
	95.684,-13.934,
	99.000,-15.000
};
LookupTable singleStringDecayRate(&singleStringDecayRate_points[0], 17);

double singleStringZero_points[17*2] = {
	21.000,-1.000,
	24.000,-1.000,
	28.000,-1.000,
	29.000,-1.000,
	32.534,-1.000,
	36.000,-0.700,
	42.000,-0.400,
	48.000,-0.200,
	54.000,-0.120,
	60.000,-0.080,
	66.000,-0.070,
	72.000,-0.070,
	79.000,-0.065,
	84.000,-0.063,
	88.000,-0.060,
	96.000,-0.050,
	99.000,-0.050	};
LookupTable singleStringZero(&singleStringZero_points[0], 17);

double singleStringPole_points[17*2] = {
	21.000,0.350,
	24.604,0.318,
	26.335,0.279,
	28.000,0.250,
	32.000,0.150,
	36.000,0.000,
	42.000,0.000,
	48.000,0.000,
	54.000,0.000,
	60.000,0.000,
	66.000,0.000,
	72.000,0.000,
	76.000,0.000,
	84.000,0.000,
	88.000,0.000,
	96.000,0.000,
	99.000,0.000	};
LookupTable singleStringPole(&singleStringPole_points[0], 17);

double releaseLoopGain_points[10*2] = {
	21.000,0.865,
	24.000,0.880,
	29.000,0.896,
	36.000,0.910,
	48.000,0.920,
	60.000,0.950,
	72.000,0.965,
	84.000,0.988,
	88.000,0.997,
	99.000,0.988	};
LookupTable releaseLoopGain(&releaseLoopGain_points[0], 10);

double detuningHz_points[18*2] = {
	21.000,0.003,
	24.000,0.003,
	28.000,0.003,
	29.000,0.060,
	31.000,0.100,
	36.000,0.110,
	42.000,0.120,
	48.000,0.200,
	54.000,0.200,
	60.000,0.250,
	66.000,0.270,
	72.232,0.300,
	78.000,0.350,
	84.000,0.500,
	88.531,0.582,
	92.116,0.664,
	95.844,0.793,
	99.000,1.000	};
LookupTable detuningHz(&detuningHz_points[0], 18);

double stiffnessCoefficient_points[10*2] = {
	21.000,-0.850,
	23.595,-0.850,
	27.055,-0.830,
	29.000,-0.700,
	37.725,-0.516,
	46.952,-0.352,
	60.000,-0.250,
	73.625,-0.036,
	93.810,-0.006,
	99.000,1.011	};
LookupTable stiffnessCoefficient(&stiffnessCoefficient_points[0], 10);

double strikePosition_points[12*2] = {
	21.000,0.050,
	24.000,0.050,
	28.000,0.050,
	35.000,0.050,
	41.000,0.050,
	42.000,0.125,
	48.000,0.125,
	60.000,0.125,
	72.000,0.125,
	84.000,0.125,
	96.000,0.125,
	99.000,0.125	};
LookupTable strikePosition(&strikePosition_points[0], 12);

double EQGain_points[14*2] = {
	21.000,2.000,
	24.000,2.000,
	28.000,2.000,
	30.000,2.000,
	35.562,1.882,
	41.000,1.200,
	42.000,0.600,
	48.000,0.500,
	54.000,0.500,
	59.928,0.502,
	66.704,0.489,
	74.201,0.477,
	91.791,1.000,
	99.000,1.000	};
LookupTable EQGain(&EQGain_points[0], 14);

double EQBandwidthFactor_points[13*2] = {
	21.000,5.000,
	24.112,5.000,
	28.000,5.000,
	35.000,4.956,
	41.000,6.000,
	42.000,2.000,
	48.773,1.072,
	57.558,1.001,
	63.226,1.048,
	69.178,1.120,
	72.862,1.525,
	80.404,2.788,
	97.659,1.739	};
LookupTable EQBandwidthFactor(&EQBandwidthFactor_points[0], 13);


/* PianoDriverA */
/* HammerFilter */

double loudPole_points[19*2] = {
	21.000,0.875,
	23.719,0.871,
	27.237,0.836,
	28.996,0.828,
	32.355,0.820,
	36.672,0.816,
	40.671,0.820,
	45.788,0.812,
	47.867,0.812,
	54.000,0.810,
	60.000,0.800,
	66.000,0.800,
	72.000,0.810,
	78.839,0.824,
	84.446,0.844,
	89.894,0.844,
	96.463,0.848,
	103.512,0.840,
	107.678,0.840	};
LookupTable loudPole(&loudPole_points[0], 19);

double softPole_points[16*2] = {
	21.000,0.990,
	24.000,0.990,
	28.000,0.990,
	29.000,0.990,
	36.000,0.990,
	42.000,0.990,
	48.000,0.985,
	54.000,0.970,
	60.000,0.960,
	66.000,0.960,
	72.000,0.960,
	78.000,0.970,
	84.673,0.975,
	91.157,0.990,
	100.982,0.970,
	104.205,0.950	};
LookupTable softPole(&softPole_points[0], 16);

double normalizedVelocity_points[8*2] = {
	0.000,0.000,
	0.170,0.318,
	0.316,0.546,
	0.460,0.709,
	0.599,0.825,
	0.717,0.894,
	0.841,0.945,
	1.000,1.000	};
LookupTable normalizedVelocity(&normalizedVelocity_points[0], 8);

double loudGain_points[16*2] = {
	21.873,0.891,
	25.194,0.870,
	30.538,0.848,
	35.448,0.853,
	41.513,0.842,
	47.434,0.826,
	53.644,0.820,
	60.720,0.815,
	65.630,0.820,
	72.995,0.853,
	79.060,0.920,
	85.270,1.028,
	91.624,1.247,
	95.668,1.296,
	99.000,1.300,
	100.000,1.100	};
LookupTable loudGain(&loudGain_points[0], 16);

double softGain_points[15*2] = {
	20.865,0.400,
	22.705,0.400,
	25.960,0.400,
	28.224,0.400,
	31.196,0.400,
	36.715,0.400,
	44.499,0.400,
	53.981,0.400,
	60.000,0.350,
	66.000,0.350,
	72.661,0.350,
	81.435,0.430,
	88.311,0.450,
	93.040,0.500,
	96.434,0.500	};
LookupTable softGain(&softGain_points[0], 15);


/* Soundboard */

double sustainPedalLevel_points[13*2] = {
	21.000,0.050,
	24.000,0.050,
	31.000,0.030,
	36.000,0.025,
	48.000,0.010,
	60.000,0.005,
	66.000,0.003,
	72.000,0.002,
	78.000,0.002,
	84.000,0.003,
	90.000,0.003,
	96.000,0.003,
	108.000,0.002	};
LookupTable sustainPedalLevel(&sustainPedalLevel_points[0], 13);

double DryTapAmpT60_points[16*2] = {
	21.001,0.491,
	26.587,0.498,
	34.249,0.470,
	40.794,0.441,
	47.977,0.392,
	55.000,0.370,
	60.000,0.370,
	66.000,0.370,
	71.934,0.370,
	78.000,0.370,
	83.936,0.390,
	88.557,0.387, 
	92.858,0.400,
	97.319,0.469,
	102.400,0.500,
	107.198,0.494	};
LookupTable DryTapAmpT60(&DryTapAmpT60_points[0], 16);

double DryTapAmpCurrent = 0.15;

double DCBa1_points[18*2] = {
	21.000,-0.999,
	24.000,-0.999,
	30.000,-0.999,
	36.000,-0.999,
	42.000,-0.999,
	48.027,-0.993,
	60.000,-0.995,
	72.335,-0.960,
	78.412,-0.924,
	84.329,-0.850,
	87.688,-0.770,
	91.000,-0.700,
	92.000,-0.910,
	96.783,-0.850,
	99.000,-0.800,
	100.000,-0.850,
	104.634,-0.700,
	107.518,-0.500	};
LookupTable DCBa1(&DCBa1_points[0], 18);

/* pianoDriverB */
/* High Notes */

double secondStageAmpRatio_points[6*2] = {
	82.277,-18.508,
	88.000,-30.000,
	90.000,-30.000,
	93.451,-30.488,
	98.891,-30.633,
	107.573,-30.633	};
LookupTable secondStageAmpRatio(&secondStageAmpRatio_points[0], 6);

double r1_1db_points[3*2] = {
	100.000,-75.000,
	103.802,-237.513,
	108.000,-400.000	};
LookupTable r1_1db(&r1_1db_points[0], 3);

double r1_2db_points[4*2] = {
	98.388,-16.562,
	100.743,-75.531,
	103.242,-154.156,
	108.000,-300.000	};
LookupTable r1_2db(&r1_2db_points[0], 4);

double r2db_points[2*2] = {
	100.000,-115.898,
	107.858,-250.000	};
LookupTable r2db(&r2db_points[0], 2);

double r3db_points[2*2] = {
	100.000,-150.000,
	108.000,-400.000	};
LookupTable r3db(&r3db_points[0], 2);

double secondPartialFactor_points[2*2] = {
	88.000,2.000,
	108.000,2.100	};
LookupTable secondPartialFactor(&secondPartialFactor_points[0], 2);

double thirdPartialFactor_points[2*2] = {
	88.000,3.100,
	108.000,3.100	};
LookupTable thirdPartialFactor(&thirdPartialFactor_points[0], 2);

double bq4_gEarBalled_points[6*2] = {
	100.000,0.040,
	102.477,0.100,
	104.518,0.300,
	106.000,0.500,
	107.000,1.000,
	108.000,1.500	};
LookupTable bq4_gEarBalled(&bq4_gEarBalled_points[0], 6);

//************************************************************************

float getValueDryTapAmpT60 (float index){
	return DryTapAmpT60.getValue(index);
}

float getValueSustainPedalLevel (float index){
	return sustainPedalLevel.getValue(index);
}

float getValueLoudPole(float index){
	return loudPole.getValue(index);
}

float getValuePoleValue(float index){
	return softPole.getValue(index);
}

float getValueLoudGain(float index){
	return loudGain.getValue(index);
}

float getValueSoftGain(float index){
	return softGain.getValue(index);
}

float getValueDCBa1(float index){
	return DCBa1.getValue(index);
}

float getValuer1_1db(float index){
	return r1_1db.getValue(index);
}

float getValuer1_2db(float index){
	return r1_2db.getValue(index);
}

float getValuer2db(float index){
	return r2db.getValue(index);
}

float getValuer3db(float index){
	return r3db.getValue(index);
}

float getValueSecondStageAmpRatio(float index){
	return secondStageAmpRatio.getValue(index);
}

float getValueSecondPartialFactor(float index){
	return secondPartialFactor.getValue(index);
}

float getValueThirdPartialFactor(float index){
	return thirdPartialFactor.getValue(index);
}

float getValueBq4_gEarBalled(float index){
	return bq4_gEarBalled.getValue(index);
}

float getValueStrikePosition(float index){
	return strikePosition.getValue(index);
}

float getValueEQBandWidthFactor(float index){
	return EQBandwidthFactor.getValue(index);
}

float getValueEQGain(float index){
	return EQGain.getValue(index);
}

float getValueDetuningHz(float index){
	return detuningHz.getValue(index);
}

float getValueSingleStringDecayRate(float index){
	return singleStringDecayRate.getValue(index);
}

float getValueSingleStringZero(float index){
	return singleStringZero.getValue(index);
}

float getValueSingleStringPole(float index){
	return singleStringPole.getValue(index);
}

float getValueStiffnessCoefficient(float index){
	return stiffnessCoefficient.getValue(index);
}

float getValueReleaseLoopGain(float index){
	return releaseLoopGain.getValue(index);
}

//Harpsichord

double loopFilterb0_points[18*2] = {
	35.000,0.94373,
	36.000,0.94731,
	46.000,0.94731,
	47.000,0.96202,
	52.000,0.96202,
	53.000,0.97477,
	58.000,0.97477,
	59.000,0.97733,
	64.000,0.97733,
	65.000,0.97971,
	70.000,0.97971,
	71.000,0.97971,
	76.000,0.97971,
	77.000,0.98698,
	82.000,0.98698,
	83.000,0.98462,
	86.000,0.98462,
	87.000,0.98611,
};
extern LookupTable loopFilterb0;
LookupTable loopFilterb0(&loopFilterb0_points[0], 18);

float getValueLoopFilterb0(float index){
	return loopFilterb0.getValue(index);
}

double loopFilterb1_points[18*2] = {
	35.000,0.60010,
	36.000,-0.59124,
	46.000,-0.59124,
	47.000,-0.21243,
	52.000,-0.21243,
	53.000,-0.39280,
	58.000,-0.39280,
	59.000,-0.48307,
	64.000,-0.48307,
	65.000,0.51965,
	70.000,0.51965,
	71.000,0.51965,
	76.000,0.51965,
	77.000,-0.42463,
	82.000,-0.42463,
	83.000,0.85655,
	86.000,0.85655,
	87.000,0.68851,
};
extern LookupTable loopFilterb1;
LookupTable loopFilterb1(&loopFilterb1_points[0], 18);

float getValueLoopFilterb1(float index){
	return loopFilterb1.getValue(index);
}

double loopFilterb2_points[18*2] = {
	35.000,-0.00360,
	36.000,-0.12249,
	46.000,-0.12249,
	47.000,-0.16044,
	52.000,-0.16044,
	53.000,-0.21680,
	58.000,-0.21680,
	59.000,-0.16346,
	64.000,-0.16346,
	65.000,0.22162,
	70.000,0.22162,
	71.000,0.22162,
	76.000,0.22162,
	77.000,-0.14973,
	82.000,-0.14973,
	83.000,0.24937,
	86.000,0.24937,
	87.000,0.14838,
};
extern LookupTable loopFilterb2;
LookupTable loopFilterb2(&loopFilterb2_points[0], 18);

float getValueLoopFilterb2(float index){
	return loopFilterb2.getValue(index);
}

double loopFiltera1_points[18*2] = {
	35.000,0.5941,
	36.000,-0.65928,
	46.000,-0.65928,
	47.000,-0.24222,
	52.000,-0.24222,
	53.000,-0.41402,
	58.000,-0.41402,
	59.000,-0.50837,
	64.000,-0.50837,
	65.000,0.51263,
	70.000,0.51263,
	71.000,0.51263,
	76.000,0.51263,
	77.000,-0.43976,
	82.000,-0.43976,
	83.000,0.85396,
	86.000,0.85396,
	87.000,0.68332,
};
extern LookupTable loopFiltera1;
LookupTable loopFiltera1(&loopFiltera1_points[0], 18);

float getValueLoopFiltera1(float index){
	return loopFiltera1.getValue(index);
}

double loopFiltera2_points[18*2] = {
	35.000,-0.02641,
	36.000,-0.10275,
	46.000,-0.10275,
	47.000,-0.15842,
	52.000,-0.15842,
	53.000,-0.21653,
	58.000,-0.21653,
	59.000,-0.15833,
	64.000,-0.15833,
	65.000,0.22025,
	70.000,0.22025,
	71.000,0.22025,
	76.000,0.22025,
	77.000,-0.14583,
	82.000,-0.14583,
	83.000,0.24405,
	86.000,0.24405,
	87.000,0.14370,
};
extern LookupTable loopFiltera2;
LookupTable loopFiltera2(&loopFiltera2_points[0], 18);

float getValueLoopFiltera2(float index){
	return loopFiltera2.getValue(index);
}

//bass

double bassLoopFilterb0_points[19*2] = {
	24.000,0.54355,
	26.000,0.54355,
	27.000,0.55677,
	29.000,0.55677,
	32.000,0.55677,
	33.000,0.83598,
	36.000,0.83598,
	43.000,0.83598,
	44.000,0.88292,
	48.000,0.88292,
	51.000,0.88292,
	52.000,0.77805,
	54.000,0.77805,
	57.000,0.77805,
	58.000,0.91820,
	60.000,0.91820,
	61.000,0.91820,
	63.000,0.94594,
	65.000,0.91820,
};
extern LookupTable bassLoopFilterb0;
LookupTable bassLoopFilterb0(&bassLoopFilterb0_points[0], 18);

float getValueBassLoopFilterb0(float index){
	return bassLoopFilterb0.getValue(index);
}

double bassLoopFilterb1_points[19*2] = {
	24.000,-0.36586,
	26.000,-0.36586,
	27.000,-0.37628,
	29.000,-0.37628,
	32.000,-0.37628,
	33.000,-0.60228,
	36.000,-0.60228,
	43.000,-0.60228,
	44.000,-0.65721,
	48.000,-0.65721,
	51.000,-0.65721,
	52.000,-0.51902,
	54.000,-0.51902,
	57.000,-0.51902,
	58.000,-0.80765,
	60.000,-0.80765,
	61.000,-0.80765,
	63.000,-0.83230,
	65.000,-0.83230,
};
extern LookupTable bassLoopFilterb1;
LookupTable bassLoopFilterb1(&bassLoopFilterb1_points[0], 18);

float getValueBassLoopFilterb1(float index){
	return bassLoopFilterb1.getValue(index);
}

double bassLoopFiltera1_points[19*2] = {
	24.000,-0.81486,
	26.000,-0.81486,
	27.000,-0.81147,
	29.000,-0.81147,
	32.000,-0.81147,
	33.000,-0.76078,
	36.000,-0.76078,
	43.000,-0.76078,
	44.000,-0.77075,
	48.000,-0.77075,
	51.000,-0.77075,
	52.000,-0.73548,
	54.000,-0.73548,
	57.000,-0.73548,
	58.000,-0.88810,
	60.000,-0.88810,
	61.000,-0.88810,
	63.000,-0.88537,
	65.000,-0.88537,
};
extern LookupTable bassLoopFiltera1;
LookupTable bassLoopFiltera1(&bassLoopFiltera1_points[0], 18);

float getValueBassLoopFiltera1(float index){
	return bassLoopFiltera1.getValue(index);
}