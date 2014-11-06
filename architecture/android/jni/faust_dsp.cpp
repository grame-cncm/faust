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

#include <android/log.h>
#include "opensl_io.h"
#include "faust_dsp.h"
#include "mydsp.cpp"
#include <stdio.h>
#include <string>

#define FAUSTFLOAT float
#define BUFFERFRAMES 1024
#define VECSAMPS 256
#define SR 44100

using namespace std;

OPENSL_STREAM *p;
mydsp* DSP;
GUI* ui_interface;

int inChanNumb, outChanNumb;
float **bufferout,**bufferin;

Para faust::initFaust(){
	DSP = new mydsp();
	ui_interface = new GUI();
	ui_interface->initUI();
	DSP->buildUserInterface(ui_interface);
	DSP->init(SR);
	Para params;
	inChanNumb = DSP->getNumInputs();
	outChanNumb = DSP->getNumOutputs();

	// allocating memory for output channel
	bufferout = new float *[outChanNumb];
	bufferout[0] = new float [VECSAMPS];
	if(outChanNumb == 2) bufferout[1] = new float [VECSAMPS];

	// allocating memory for input channel
	if(inChanNumb == 1){
		bufferin = new float *[1];
		bufferin[0] = new float [VECSAMPS];
	}

	// layout elements initialization
	params.cntLay = ui_interface->params.cntLay;
	params.typeLay = new int [params.cntLay];
	params.labelLayPos = new int [params.cntLay];

	// parameters elements initialization
	params.cnt = ui_interface->params.cnt;
	params.cntEl = ui_interface->params.cntEl;
	params.type = new int [params.cnt];
	params.typeEl = new int [params.cntEl];
	params.labelPos = new int [params.cnt];
	params.zone = new float [params.cnt];
	params.init = new float [params.cnt];
	params.min = new float [params.cnt];
	params.max = new float [params.cnt];
	params.step = new float [params.cnt];

	int oldPos = 0;
	char labelBuf[1024]="",labelBuf2[1024]="",labelOld[1024]="",metadata[1024]="";

	for(int i=0; i<params.cntEl; i++) params.typeEl[i] = ui_interface->params.typeEl[i];

	for(int i=0; i<params.cnt; i++){
		params.type[i] = ui_interface->params.type[i];
		/*
		 * There must be a way to do that in a nicer way with swig, but for now,
		 * it works fine... TODO
		 */
		int currentPos = strlen(ui_interface->params.label[i]);
		params.labelPos[i] = currentPos + oldPos;
		oldPos = currentPos + oldPos;
		strcpy(labelBuf,labelOld);
		strcat(labelBuf,ui_interface->params.label[i]);
		strcpy(labelOld,labelBuf);
		params.label = labelBuf;

		params.init[i] = ui_interface->params.init[i];
		*ui_interface->params.value[0] = params.zone[i];
		params.min[i] = ui_interface->params.min[i];
		params.max[i] = ui_interface->params.max[i];
		params.step[i] = ui_interface->params.step[i];

		strcat(metadata,ui_interface->params.metadata[i]);
	}

	params.metadata = metadata;

	//__android_log_print(ANDROID_LOG_VERBOSE, "Echo", "Foucou: %s", metadata);
	// reset variables
	oldPos = 0;
	strcpy(labelOld,"");

	for(int i=0; i<params.cntLay; i++){
		params.typeLay[i] = ui_interface->params.typeLay[i];
		if(params.typeLay[i] == 0 || params.typeLay[i] == 1){
			int currentPos = strlen(ui_interface->params.labelLay[i]);
			params.labelLayPos[i] = currentPos + oldPos;
			oldPos = currentPos + oldPos;
			strcpy(labelBuf2,labelOld);
			strcat(labelBuf2,ui_interface->params.labelLay[i]);
			strcpy(labelOld,labelBuf2);
			params.labelLay = labelBuf2;
		}
	}
	return params;
}

void faust::startAudio(){
	p = android_OpenAudioDevice(SR,inChanNumb,outChanNumb,BUFFERFRAMES);
}

void faust::stopAudio(){
	android_CloseAudioDevice(p);
	delete [] bufferin;
	delete [] *bufferout;
	delete [] bufferout;
}

void faust::setParam(float *params){
	for(int i = 0; i<ui_interface->params.cnt; i++){
		*ui_interface->params.value[i] = params[i];
	}
}

void faust::processDSP(){
	float out[VECSAMPS*2];

	// getting input signal
	if(inChanNumb>=1) android_AudioIn(p,bufferin[0],VECSAMPS);

	// computing...
	DSP->compute(VECSAMPS,bufferin,bufferout);

	// sending output signal
	if(outChanNumb == 1) android_AudioOut(p,bufferout[0],VECSAMPS);
	else{
		int i,j;
		for(i = 0, j=0; i < VECSAMPS; i++, j+=2){
			out[j] = bufferout[0][i];
			out[j+1] = bufferout[1][i];
		}
		android_AudioOut(p,out,VECSAMPS*2);
	}
}
