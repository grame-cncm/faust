/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
	published by the Free Software Foundation; either version 2.1 of the 
	License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
 	License along with the GNU C Library; if not, write to the Free
  	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  	02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* link with  */
#include <math.h>
/* link with  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h> 
#include <sys/wait.h>

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <map>
#include <libgen.h>
#include <portaudio.h>

#include "faustqt.h"


using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS 
#endif

//#define BENCHMARKMODE


struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }

// g++ -O3 -lm -ljack `gtk-config --cflags --libs` ex2.cpp
 
	

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))


// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }



/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }


<<includeIntrinsic>>


/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/





//----------------------------------------------------------------
//  définition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>
		
				
mydsp	DSP;





/******************************************************************************
*******************************************************************************

							PORT AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------------------
// 	number of physical input and output channels of the PA device
//----------------------------------------------------------------------------

int		gDevNumInChans;
int		gDevNumOutChans;


//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];


//----------------------------------------------------------------------------
// allocated the noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

void allocChannels (int size, int numInChan, int numOutChan) 
{
	
	assert (numInChan < 256);
	assert (numOutChan < 256);
	
	
	for (int i = 0; i < numInChan; i++) {
		gInChannel[i] = (float*) calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gInChannel[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < numOutChan; i++) {
		gOutChannel[i] = (float*) calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gOutChannel[i][j] = 0.0;
		}
	}
}

//----------------------------------------------------------------------------
// Port Audio Callback 
//----------------------------------------------------------------------------

static int audioCallback(const void *ibuf, void *obuf, unsigned long frames, const PaStreamCallbackTimeInfo*,  PaStreamCallbackFlags, void * )
{
	float* fInputBuffer = (float*) ibuf;
	float* fOutputBuffer = (float*) obuf;
		
	// split input samples
	for (unsigned long s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumInChans; c++) {
			gInChannel[c][s] = fInputBuffer[c + s*gDevNumInChans];
		}
	}
	
	// process samples
	DSP.compute(frames, gInChannel, gOutChannel);

	// merge output samples
	for (unsigned long s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumOutChans; c++) {
			fOutputBuffer[c + s*gDevNumOutChans] = gOutChannel[c][s];
		}
	}
			
    return 0;
}

/******************************************************************************
*******************************************************************************

                                GLOBAL VARIABLES

*******************************************************************************
*******************************************************************************/
    
list<UI*>               UI::fGuiList;
map<float*, float>      QTGUI::fGuiSize;       // map widget zone with widget size coef
map<float*, string>     QTGUI::fTooltip;       // map widget zone with tooltip strings
set<float*>             QTGUI::fKnobSet;       // set of widget zone to be knobs
map<float*, string>     QTGUI::fUnit;          // map widget zone with unit strings (i.e. "dB")
set<float*>             QTGUI::fLedSet;        // set of widget zone to be LEDs


		


/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/

long lopt (char *argv[], const char *name, long def) 
{
	int	i;
	for (i=0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

void pa_error(int err)
{
	if (err != paNoError) {
		printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
		exit(1);
	}
}	
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
	UI* interface = new QTGUI(argc, argv);
	char rcfilename[256];
    PaStream* as;
		
    long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 128);
 	
    pa_error(Pa_Initialize());
	
	const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
	const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());
	
	gDevNumInChans = (DSP.getNumInputs() > 0) ? idev->maxInputChannels : 0 ;
	gDevNumOutChans = (DSP.getNumOutputs() > 0) ? odev->maxOutputChannels : 0;
    
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;
    
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.sampleFormat = paFloat32;
    inputParameters.channelCount = gDevNumInChans;
    inputParameters.hostApiSpecificStreamInfo = 0;
    
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.sampleFormat = paFloat32;
    outputParameters.channelCount = gDevNumOutChans;
    outputParameters.hostApiSpecificStreamInfo = 0;
    
    PaError err;
    if ((err = Pa_IsFormatSupported(
        ((gDevNumInChans > 0) ? &inputParameters : 0), 
        ((gDevNumOutChans > 0) ? &outputParameters : 0), srate)) != 0) {
        printf("stream format is not supported err = %d\n", err);
        exit(1);
    }

    printf("inchan = %d, outchan = %d, freq = %ld\n", gDevNumInChans, gDevNumOutChans, srate);
	allocChannels(fpb, max(gDevNumInChans, DSP.getNumInputs()), max(gDevNumOutChans, DSP.getNumOutputs()));
	
	DSP.init(long(srate));
	DSP.buildUserInterface(interface);
	
    const char* home = getenv("HOME");
    if (home == 0) home = ".";
    snprintf(rcfilename, 256, "%s/.%src", home, basename(argv[0]));
    interface->recallState(rcfilename);

	pa_error(Pa_OpenDefaultStream(&as, gDevNumInChans, gDevNumOutChans, paFloat32, srate, fpb, audioCallback, 0));
	Pa_StartStream(as);
	interface->run();
	Pa_StopStream(as);
	Pa_CloseStream(as);

    interface->saveState(rcfilename);
  	return 0;
}

