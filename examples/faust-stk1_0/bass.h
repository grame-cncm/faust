//Parameters for bass.dsp
//©Romain Michon (rmichon@ccrma.stanford.edu), 2011
//licence: FAUST-STK

#include "instrument.h"

#define _LOOKUP_TABLE_H_

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
