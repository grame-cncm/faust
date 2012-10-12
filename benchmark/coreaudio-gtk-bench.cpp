/* link with : "" */
#include <stdlib.h>
#include <libgen.h>
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
#include <sys/time.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h> 
#include <sys/wait.h>
#include <list>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "faust/audio/coreaudio-dsp.h"
#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/gui/faustgtk.h"

using namespace std;

// handle 32/64 bits int size issues
#ifdef __x86_64__

#define uint32	unsigned int
#define uint64	unsigned long int

#define int32	int
#define int64	long int

#else

#define uint32	unsigned int
#define uint64	unsigned long long int

#define int32	int
#define int64	long long int
#endif

// check 32/64 bits issues are correctly handled
#define CHECKINTSIZE \
	assert(sizeof(int32)==4);\
	assert(sizeof(int64)==8);

#define check_error(err) if (err) { printf("%s:%d, alsa error %d : %s\n", __FILE__, __LINE__, err, snd_strerror(err)); exit(1); }
#define check_error_msg(err,msg) if (err) { fprintf(stderr, "%s:%d, %s : %s(%d)\n", __FILE__, __LINE__, msg, snd_strerror(err), err); exit(1); }
#define display_error_msg(err,msg) if (err) { fprintf(stderr, "%s:%d, %s : %s(%d)\n", __FILE__, __LINE__, msg, snd_strerror(err), err); }

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

<<includeIntrinsic>>

#define BENCHMARKMODE
#ifdef BENCHMARKMODE

/**
 * Returns the number of clock cycles elapsed since the last reset
 * of the processor
 */
static __inline__ uint64 rdtsc(void)
{
	union {
		uint32 i32[2];
		uint64 i64;
	} count;
	
	__asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
     return count.i64;
}

#define KSKIP 20
#define KMESURE 600

int mesure = 0;

// these values are used to determine the number of clocks in a second
uint64 firstRDTSC;
uint64 lastRDTSC;

// these tables contains the last KMESURE in clocks
uint64 starts[KMESURE];
uint64 stops [KMESURE];

#define STARTMESURE starts[mesure%KMESURE] = rdtsc();
#define STOPMESURE stops[mesure%KMESURE] = rdtsc(); mesure = mesure+1;

struct timeval 		tv1;
struct timeval 		tv2;

void openMesure()
{
	struct timezone tz;
	gettimeofday(&tv1, &tz);
	firstRDTSC = rdtsc();
}

void closeMesure()
{
	struct timezone tz;
	gettimeofday(&tv2, &tz);
	lastRDTSC = rdtsc();
}
	
/**
 * return the number of RDTSC clocks per seconds
 */
int64 rdtscpersec()
{
	// If the environment variable CLOCKSPERSEC is defined
	// we use it instead of our own measurement
	char* str = getenv("CLOCKSPERSEC");
    if (str) {
	    int64 cps = (int64) atoll(str);
        if (cps > 1000000000) {
		    return cps;
	    } else {
		    return (lastRDTSC-firstRDTSC) / (tv2.tv_sec - tv1.tv_sec) ;
	    }
    } else {
        return (lastRDTSC-firstRDTSC) / (tv2.tv_sec - tv1.tv_sec) ;
    }   
}
    
/**
 * Converts a duration, expressed in RDTSC clocks, into seconds
 */
double rdtsc2sec(uint64 clk)
{
	return double(clk) / double(rdtscpersec());
}

double rdtsc2sec(double clk)
{
	return clk / double(rdtscpersec());
}

/**
 * Converts RDTSC clocks into Megabytes/seconds according to the
 * number of frames processed during the period, the number of channels
 * and 4 bytes samples.
 */
double megapersec(int frames, int chans, uint64 clk)
{
	return double(frames) * double(chans) * 4 / double(1024 * 1024 * rdtsc2sec(clk));
}
    
/**
 * Compute the mean value of a vector of measures
 */
static uint64 meanValue( vector<uint64>::const_iterator a, vector<uint64>::const_iterator b)
{
	uint64 r = 0;
	unsigned int n = 0;
	while (a!=b) { r += *a++; n++; }
	return (n>0) ? r/n : 0;
}   

/**
 * Print the median value (in Megabytes/second) of KMESURE
 * throughputs measurements
 */
void printstats(const char* applname, int bsize, int ichans, int ochans)
{
    assert(mesure > KMESURE);
    vector<uint64> V(KMESURE);

    for (int i = 0; i<KMESURE; i++) {
        V[i] = stops[i] - starts[i];
    }

    sort(V.begin(), V.end());
  
    // Mean of 10 best values (gives relatively stable results)
    uint64 meaval00 = meanValue(V.begin(), V.begin()+ 5);			
    uint64 meaval25 = meanValue(V.begin()+KMESURE/4 - 2, V.begin()+KMESURE/4 + 3);			
    uint64 meaval50 = meanValue(V.begin()+KMESURE/2 - 2, V.begin()+KMESURE/2 + 3);			
    uint64 meaval75 = meanValue(V.begin()+3*KMESURE/4 - 2, V.begin()+3*KMESURE/4 + 3);			
    uint64 meaval100 = meanValue(V.end() - 5, V.end());			
  
    //printing
    cout << applname
         << '\t' << megapersec(bsize, ichans+ochans, meaval00) 
         << '\t' << megapersec(bsize, ichans+ochans, meaval25) 
         << '\t' << megapersec(bsize, ichans+ochans, meaval50) 
         << '\t' << megapersec(bsize, ichans+ochans, meaval75) 
         << '\t' << megapersec(bsize, ichans+ochans, meaval100) 
         << endl;
}

#else

#define STARTMESURE
#define STOPMESURE

#endif
		
<<includeclass>>

bool running = true;

class TMeasureTCoreAudioRenderer : public TCoreAudioRenderer {

    protected:

        virtual void compute(int inNumberFrames)
        {
            STARTMESURE
            fDSP->compute(inNumberFrames, fInChannel, fOutChannel);
            STOPMESURE
            running = mesure <= (KMESURE + KSKIP);
        }
};
                    
class measure_coreaudio : public audio {
    
    TMeasureTCoreAudioRenderer audio_device;
	long fSampleRate, fFramesPerBuf;

 public:
			 measure_coreaudio(long srate, long fpb) : fSampleRate(srate), fFramesPerBuf(fpb) {}
	virtual ~measure_coreaudio() {}

	virtual bool init(const char* /*name*/, dsp* DSP) {
		DSP->init(fSampleRate);
		if (audio_device.OpenDefault(DSP, DSP->getNumInputs(), DSP->getNumOutputs(), fFramesPerBuf, fSampleRate) < 0) {
			printf("Cannot open CoreAudio device\n");
			return false;
		}
        return true;
    }

	virtual bool start() {
		if (audio_device.Start() < 0) {
			printf("Cannot start CoreAudio device\n");
			return false;
		}
 		return true;
	}

	virtual void stop() {
		audio_device.Stop();
		audio_device.Close();
	}

};

mydsp DSP;

list<GUI*> GUI::fGuiList;

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
		
// sopt : Scan Command Line string Arguments
const char* sopt(int argc, char *argv[], const char* longname, const char* shortname, const char* def) 
{
	for (int i=2; i<argc; i++) 
		if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) 
			return argv[i];
	return def;
}
	
// fopt : Scan Command Line flag option (without argument), return true if the flag
bool fopt(int argc, char *argv[], const char* longname, const char* shortname) 
{
	for (int i=1; i<argc; i++) 
		if (strcmp(argv[i], shortname) == 0 || strcmp(argv[i], longname) == 0) 
			return true;
	return false;
}
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

pthread_t guithread;
	
void* run_ui(void* ptr)
{
	GUI* interface = (GUI*)ptr;
	interface->run();
	pthread_exit(0);
	return 0;
}

int main(int argc, char *argv[])
{
	CHECKINTSIZE;
	
	// compute rcfilename to (re)store application state
    char name[256];
	char rcfilename[256];
	char* home = getenv("HOME");
    snprintf(name, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, basename(argv[0]));
    
	long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 512);
    
    UI* interface = new GTKUI(argv[0], &argc, &argv);
 	
    DSP.init(srate);
    DSP.buildUserInterface(interface);
    
    pthread_create(&guithread, NULL, run_ui, interface);
	
    openMesure();
    
    measure_coreaudio audio(srate, fpb);
    audio.init(name, &DSP);
    audio.start();
    
    while(running) {
        usleep(100000);
    }
	closeMesure();

#ifdef BENCHMARKMODE
    printstats(argv[0], fpb, DSP.getNumInputs(), DSP.getNumOutputs());
#endif       

    audio.stop();
  	return 0;
}
