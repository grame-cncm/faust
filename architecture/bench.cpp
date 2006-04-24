//#include "../bench/lmbench.h"






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




inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }



// g++ -Wall -O3 -lm -lpthread -lasound `gtk-config --cflags --libs` test.cpp -o test

#ifdef __GNUC__

//-------------------------------------------------------------------
// Generic min and max using gcc extensions
//-------------------------------------------------------------------

#define max(x,y) ((x)>?(y))
#define min(x,y) ((x)<?(y))

//abs(x) should be already predefined

#else

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

#endif

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


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

	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;

	// -- passive widgets

	virtual void addNumDisplay(char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;

	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
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
//  d�inition du processeur de signal
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




static __inline__ unsigned long long int rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}


#define CHRONO(title,test)					\
{											\
	unsigned long long int t0, t1, t2;							\
											\
	printf("Test %s... ", title);			\
	test;									\
	t0 = rdtsc ();							\
	t1 = rdtsc ();							\
	test;									\
	t2 = rdtsc ();							\
	printf("elapsed time: %ld cycles\n", long(t2-t1 - (t1-t0)));	\
}




#define BSIZE 1024


void bench()
{

	int numInChan = DSP.getNumInputs();
	int numOutChan = DSP.getNumOutputs();

	assert (numInChan < 256);
	assert (numOutChan < 256);

	float* 	inChannel[256];
	float* 	outChannel[256];

	// allocate input buffers (initialized with white noise)
	float R0_0 = 0;
	for (int i = 0; i < numInChan; i++) {
		inChannel[i] = (float*) aligned_calloc (BSIZE, sizeof(float));
		for (int j = 0; j < BSIZE; j++) {
			int R0temp0 = (12345 + (1103515245 * R0_0));
			inChannel[i][j] = 4.656613e-10f*R0temp0;
			R0_0 = R0temp0;
		}
	}
	// allocate output buffers (not initialized)
	for (int i = 0; i < numOutChan; i++) outChannel[i] = (float*) aligned_calloc (BSIZE, sizeof(float));

	// init the dsp with a resoneable sampling rate)
	DSP.init(48000);

	// compute one block of BSIZE samples
	CHRONO("Faust generated code ", DSP.compute(BSIZE,inChannel,outChannel));

}



//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

// lopt : Scan Command Line long int Arguments

long lopt (int argc, char *argv[], char* longname, char* shortname, long def)
{
	for (int i=2; i<argc; i++)
		if ( strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0 )
			return atoi(argv[i]);
	return def;
}


int main(int argc, char *argv[] )
{
  bool rt = setRealtimePriority();
  printf(rt?"RealTime Set\n":"RealTime Not Set\n");

  bench();
  return 0;
}





