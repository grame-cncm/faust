/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

struct Para {
			int cnt;
			int cntLay;
			int cntEl;
			int *typeEl;
			int *typeLay;
			int *labelLayPos;
			char *labelLay;
			char *metadata;
			int *type;
			float *zone;
			int *labelPos;
			char *label;
			float *init;
			float *min;
			float *max;
			float *step;
		} ;

class faust{
public:
	Para initFaust(void);
	void startAudio(void);
	void processDSP(void);
	void setParam(float*);
	void stopAudio(void);
};

