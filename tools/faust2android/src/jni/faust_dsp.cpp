/*
TODO Header needed
*/

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
GUI* interface;

int inChanNumb, outChanNumb;

Para faust::initFaust(){
	DSP = new mydsp();
	interface = new GUI();
	interface->initUI();
	DSP->buildUserInterface(interface);
	DSP->init(SR);
	Para params;
	inChanNumb = DSP->getNumInputs();
	outChanNumb = DSP->getNumOutputs();

	// layout elements initialization
	params.cntLay = interface->params.cntLay;
	params.typeLay = new int [params.cntLay];
	params.labelLayPos = new int [params.cntLay];

	// parameters elements initialization
	params.cnt = interface->params.cnt;
	params.type = new int [params.cnt];
	params.layoutEl = new int [params.cnt];
	params.labelPos = new int [params.cnt];
	params.zone = new float [params.cnt];
	params.init = new float [params.cnt];
	params.min = new float [params.cnt];
	params.max = new float [params.cnt];
	params.step = new float [params.cnt];

	int oldPos = 0;
	char labelBuf[1024]="",labelBuf2[1024]="",labelOld[1024]="";

	//__android_log_print(ANDROID_LOG_VERBOSE, "Echo", "Foucou: %i", outChanNumb);

	for(int i=0; i<params.cnt; i++){
		params.type[i] = interface->params.type[i];
		params.layoutEl[i] = interface->params.layoutEl[i];
		/*
		 * I know there must be a way to do that in a nicer way with swig, but for now,
		 * it works fine... XXX
		 */
		int currentPos = strlen(interface->params.label[i]);
		params.labelPos[i] = currentPos + oldPos;
		oldPos = currentPos + oldPos;
		strcpy(labelBuf,labelOld);
		strcat(labelBuf,interface->params.label[i]);
		strcpy(labelOld,labelBuf);
		params.label = labelBuf;

		params.init[i] = interface->params.init[i];
		*interface->params.value[0] = params.zone[i];
		params.min[i] = interface->params.min[i];
		params.max[i] = interface->params.max[i];
		params.step[i] = interface->params.step[i];
	}

	// reset variables
	oldPos = 0;
	strcpy(labelOld,"");

	for(int i=0; i<params.cntLay; i++){
		params.typeLay[i] = interface->params.typeLay[i];
		int currentPos = strlen(interface->params.labelLay[i]);
		params.labelLayPos[i] = currentPos + oldPos;
		strcpy(labelBuf2,labelOld);
		strcat(labelBuf2,interface->params.labelLay[i]);
		strcpy(labelOld,labelBuf2);
		params.labelLay = labelBuf2;
	}
	return params;
}

void faust::startAudio(){
	p = android_OpenAudioDevice(SR,inChanNumb,outChanNumb,BUFFERFRAMES);
}

void faust::stopAudio(){
	android_CloseAudioDevice(p);
}

void faust::setParam(float *params){
	for(int i = 0; i<interface->params.cnt; i++){
		*interface->params.value[i] = params[i];
	}
}

void faust::processDSP(){
	float out[VECSAMPS*2];
	FAUSTFLOAT **bufIn, **bufOut;
	float *bufferin[inChanNumb],*bufferout[outChanNumb];
	bufIn = (FAUSTFLOAT**) bufferin;
	bufOut = (FAUSTFLOAT**) bufferout;

	// allocating memory for input channel
	if(inChanNumb == 1) bufferin[0] = (float*) malloc(VECSAMPS*sizeof(float));

	// allocating memory for output channel(s)
	bufferout[0] = (float*) malloc(VECSAMPS*sizeof(float));
	if(outChanNumb == 2) bufferout[1] = (float*) malloc(VECSAMPS*sizeof(float));

	// getting input signal
	if(inChanNumb>=1) android_AudioIn(p,bufferin[0],VECSAMPS);

	// computing...
	DSP->compute(VECSAMPS,bufIn,bufOut);

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
