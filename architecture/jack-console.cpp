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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream> 

#include <libgen.h>
#include <jack/jack.h>

// g++ -O3 -lm -lsndfile  myfx.cpp

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

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

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

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	// -- active widgets
	
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	// -- frames and labels
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

struct param {
	float* fZone; float fMin; float fMax;
	param(float* z, float a, float b) : fZone(z), fMin(a), fMax(b) {}
};
	
class CMDUI : public UI
{
	int					fArgc;
	char**				fArgv;
	stack<string>		fPrefix;
	map<string, param>	fKeyParam;
	
	void addOption(const char* label, float* zone, float min, float max)
	{
		string fullname = fPrefix.top() + label;
		fKeyParam.insert(make_pair(fullname, param(zone, min, max)));
	}
	
	void openAnyBox(const char* label)
	{
		string prefix;
		
		if (label && label[0]) {
			prefix = fPrefix.top() + "-" + label;
		} else {
			prefix = fPrefix.top();
		}
		fPrefix.push(prefix);
	}
	
public:
		
	CMDUI(int argc, char *argv[]) : UI(), fArgc(argc), fArgv(argv) { fPrefix.push("--"); }
	virtual ~CMDUI() {}
	
	virtual void addButton(const char* label, float* zone) 		{};
	virtual void addToggleButton(const char* label, float* zone) 	{};
	virtual void addCheckButton(const char* label, float* zone) 	{};
		
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}
		
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}

	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
	{
		addOption(label,zone,min,max);
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) 						{}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) 	{}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) 			{}

	virtual void openFrameBox(const char* label)		{ openAnyBox(label); }
	virtual void openTabBox(const char* label)		{ openAnyBox(label); }
	virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
	virtual void openVerticalBox(const char* label)	{ openAnyBox(label); }
	
	virtual void closeBox() 					{ fPrefix.pop(); }
	
	virtual void show() {}
	virtual void run() 	
	{
		char c;
		printf("Type 'q' to quit\n");
		while ((c = getchar()) != 'q') {
			sleep(1);
		}
	}
	
	void print() 
	{
		map<string, param>::iterator i;
		cout << fArgc << "\n";
		cout << fArgv[0] << " option list : ";
		for (i = fKeyParam.begin(); i != fKeyParam.end(); i++) {
			cout << "[ " << i->first << " " << i->second.fMin << ".." << i->second.fMax <<" ] ";
		}
	}
		
	void process_command()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]); 
				if (p == fKeyParam.end()) {
					cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
					print();
					exit(1);
				}
				char*	end;
				*(p->second.fZone) = float(strtod(fArgv[i+1], &end));
				i++;
			}
		}
	}
		
	void process_init()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]); 
				if (p == fKeyParam.end()) {
					cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
					exit(1);
				}
				char*	end;
				*(p->second.fZone) = float(strtod(fArgv[i+1], &end));
				i++;
			}
		}
	}
};

//----------------------------------------------------------------
//  d�inition du processeur de signal
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
 	virtual void conclude() 										{}
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>
		
				
mydsp	DSP;

/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
// 	number of input and output channels
//----------------------------------------------------------------------------

int		gNumInChans;
int		gNumOutChans;

//----------------------------------------------------------------------------
// Jack ports
//----------------------------------------------------------------------------

jack_port_t *input_ports[256];
jack_port_t *output_ports[256];

//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

//----------------------------------------------------------------------------
// Jack Callbacks 
//----------------------------------------------------------------------------

int srate(jack_nframes_t nframes, void *arg)
{
	printf("the sample rate is now %u/sec\n", nframes);
	return 0;
}

void jack_shutdown(void *arg)
{
	exit(1);
}

int process (jack_nframes_t nframes, void *arg)
{
    AVOIDDENORMALS;
	for (int i = 0; i < gNumInChans; i++) {
	    gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    gOutChannel[i] = (float *)jack_port_get_buffer(output_ports[i], nframes);
	}
	DSP.compute(nframes, gInChannel, gOutChannel);
	return 0;
}
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[] )
{
	char jackname[256];
	char**	physicalInPorts;
	char**	physicalOutPorts;
	jack_client_t*			client;	

    AVOIDDENORMALS;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	
	snprintf(jackname, 255, "%s", basename(argv[0]));
	
	if ((client = jack_client_new(jackname)) == 0) {
	    fprintf(stderr, "jack server not running?\n");
	    return 1;
	}
	
	jack_set_process_callback(client, process, 0);
	jack_set_sample_rate_callback(client, srate, 0);
	jack_on_shutdown(client, jack_shutdown, 0);
	
	gNumInChans = DSP.getNumInputs();
	gNumOutChans = DSP.getNumOutputs();
	
	for (int i = 0; i < gNumInChans; i++) {
	    char buf[256];
	    snprintf(buf, 256, "in_%d", i); 
	    input_ports[i] = jack_port_register(client, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    char buf[256];
	    snprintf(buf, 256, "out_%d", i); 
	    output_ports[i] = jack_port_register(client, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	}
  
    DSP.init(jack_get_sample_rate(client));
	DSP.buildUserInterface(interface);
	
	interface->process_command();
	
	physicalInPorts = (char **)jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
	physicalOutPorts = (char **)jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
		
	if (jack_activate(client)) {
	    fprintf(stderr, "cannot activate client");
	    return 1;
	}
	
	if (physicalOutPorts != NULL) {
		for (int i = 0; i < gNumInChans && physicalOutPorts[i]; i++) {
			jack_connect(client, physicalOutPorts[i], jack_port_name(input_ports[i]));
		}
        free(physicalOutPorts);
	}
	
	if (physicalInPorts != NULL) {
		for (int i = 0; i < gNumOutChans && physicalInPorts[i]; i++) {
			jack_connect(client, jack_port_name(output_ports[i]), physicalInPorts[i]);
		} 	
        free(physicalInPorts);	
	}
	
	interface->run();
	
	jack_deactivate(client);
	
	for (int i = 0; i < gNumInChans; i++) {
	    jack_port_unregister(client, input_ports[i]);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    jack_port_unregister(client, output_ports[i]);
	}

	jack_client_close(client);
	return 0;
} 
