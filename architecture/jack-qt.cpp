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
#include <libgen.h>
#include <jack/jack.h>

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <map>

#include "faustqt.h"


using namespace std;

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

inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }


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
	for (int i = 0; i < gNumInChans; i++) {
	    gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    gOutChannel[i] = (float *)jack_port_get_buffer(output_ports[i], nframes);
	}
	DSP.compute(nframes, gInChannel, gOutChannel);
	return 0;
}


/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
	
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
list<UI*> UI::fGuiList;

int main( int argc, char *argv[] )
{
	//gtk_init (&argc, &argv);
	
	UI* 				interface = new QTGUI(argc, argv);
	jack_client_t*			client;	
	char				jackname[256];
	char				rcfilename[256];
	char**				physicalInPorts;
	char**				physicalOutPorts;
	
	snprintf(jackname, 255, "%s", basename(argv[0]));
	
	char* home = getenv("HOME");
	snprintf(rcfilename, 255, "%s/.%src", home, basename(argv[0]));
	
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
	
	interface->recallState(rcfilename);

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
        }
        
        if (physicalInPorts != NULL) {
            for (int i = 0; i < gNumOutChans && physicalInPorts[i]; i++) {
                    jack_connect(client, jack_port_name(output_ports[i]), physicalInPorts[i]);
            } 		
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
	interface->saveState(rcfilename);
		
  	return 0;
}

