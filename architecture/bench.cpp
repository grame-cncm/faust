//#include "../bench/lmbench.h"
// derived from bench.cpp to test parallel processing


/* link with  */
/* link with : "" */
#include <stdlib.h>
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

#include <iostream>


using namespace std;



float*          gBuffer = 0;        // a buffer of NV*VSize samples

unsigned int    COUNT   = 2000;     // number of measures
unsigned int    NV      = 4096;     // number of vectors in BIG buffer (should exceed cache)
unsigned int    ITER    = 10;       // number of iterations per measure
unsigned int    VSIZE   = 4096;     // size of a vector in samples
unsigned int    IDX     = 0;        // current vector number (0 <= VIdx < NV)


//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }



// g++ -Wall -O3 -lm -lpthread -lasound `gtk-config --cflags --libs` test.cpp -o test


//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }




bool setRealtimePriority ()
{
    struct passwd *         pw;
    int                     err;
    uid_t                   uid;
    struct sched_param      param;

    uid = getuid ();
    pw = getpwnam ("root");
    setuid (pw->pw_uid);
    param.sched_priority = 50; /* 0 to 99  */
    err = sched_setscheduler(0, SCHED_RR, &param);
    setuid (uid);
    return (err != -1);
}

#include <sys/time.h>

double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/



<<includeIntrinsic>>



/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
	bool	fStopped;
public:

	UI() : fStopped(false) {}
	virtual ~UI() {}

	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

	// -- passive widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;

	virtual void run() = 0;

	void stop()	{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};




/******************************************************************************
*******************************************************************************

								DSP

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------
//  definition du processeur de signal
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


<<includeclass>>

mydsp	DSP;


#if 0

static __inline__ unsigned long long int rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}

#endif

/**
 * Bench by calling COUNT times the compute() method for
 * the computation of vsize samples
 */

#define MEGABYTE 1048576.0

void statistic(const char* name, double* timing)
{
    double lo, hi, tot;
    double mega =  double(VSIZE*ITER)/MEGABYTE; // mega samples
    // skip first 10 values to avoid cache bias ???
    lo = hi = tot = mega/(timing[11] - timing[10]);
    for (int i = 11; i<COUNT; i++) {
        double delta = mega/(timing[i] - timing[i-1]);
        if (delta < lo) {
            lo = delta;
        } else if (delta > hi) {
            hi = delta;
        }
        tot += delta;
    }

    cout << '\t' << hi
         << '\t' << hi*4*DSP.getNumInputs() << '\t' << "MB/s inputs"
         << '\t' << hi*4*DSP.getNumOutputs() << '\t' << "MB/s outputs"
         << '\t' << tot/(COUNT-11)
         << '\t' << lo
         << endl; 
} 

void allocBuffer()
{
    unsigned int BSIZE = NV * VSIZE;
    gBuffer = (float*) aligned_calloc (BSIZE, sizeof(float));
    
    int R0_0 = 0;
    for (int j = 0; j < BSIZE; j++) {
        int R0temp0 = (12345 + (1103515245 * R0_0));
        gBuffer[j] = 4.656613e-10f*R0temp0;
        R0_0 = R0temp0;
    }
}

float* nextVect()
{
    IDX = (1+IDX)%NV;
    return &gBuffer[IDX*VSIZE];
}

void bench(const char* name)
{

    int numInChan = DSP.getNumInputs();
    int numOutChan = DSP.getNumOutputs();

    assert (numInChan < 256);
    assert (numOutChan < 256);

    float*  inChannel[256];
    float*  outChannel[256];

    // allocate input buffers (initialized with white noise)
    allocBuffer();

    // allocate output channels (not initialized)
    for (int i = 0; i < numOutChan; i++) outChannel[i] = (float*) aligned_calloc (VSIZE, sizeof(float));

    // init the dsp with a resoneable sampling rate)
    DSP.init(48000);
    double* timing = (double*) aligned_calloc (COUNT, sizeof(double));

    for (int i = 0; i<COUNT; i++) {
        timing[i] = mysecond();
        for (int k = 0; k<ITER; k++) {
            // allocate new input buffers to avoid L2 cache
            for (int c=0; c<numInChan; c++) { inChannel[c] = nextVect(); }
            DSP.compute(VSIZE,inChannel,outChannel);
        }
    }

    statistic(name, timing);
}

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

// lopt : Scan Command Line long int Arguments

long lopt (int argc, char *argv[], const char* longname, const char* shortname, long def)
{
	for (int i=2; i<argc; i++)
		if ( strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0 )
			return atoi(argv[i]);
	return def;
}


int main(int argc, char *argv[] )
{
    VSIZE = lopt(argc, argv, "--vector-size", "-vec", 4096);
    NV = lopt(argc, argv, "--num-vector", "-n", 20000);
    COUNT = lopt(argc, argv, "--count", "-c", 1000);
    ITER = lopt(argc, argv, "--iteration", "-i", 10);
    //setRealtimePriority();
  	bench(argv[0]);
  	return 0;
}





