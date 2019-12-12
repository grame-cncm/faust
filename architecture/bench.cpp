/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

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
#include <map>
#include <sys/time.h>

#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/misc.h"

using namespace std;

float* gBuffer = 0;        // a buffer of NV*VSize samples

unsigned int COUNT   = 2000;     // number of measures
unsigned int NV      = 4096;     // number of vectors in BIG buffer (should exceed cache)
unsigned int ITER    = 10;       // number of iterations per measure
unsigned int VSIZE   = 4096;     // size of a vector in samples
unsigned int IDX     = 0;        // current vector number (0 <= VIdx < NV)

bool setRealtimePriority()
{
    struct passwd*          pw;
    int                     err;
    uid_t                   uid;
    int                     policy;
    struct sched_param      param;

    uid = getuid ();
    pw = getpwnam ("root");
    setuid (pw->pw_uid);

    pthread_getschedparam(pthread_self(), &policy, &param);
    policy = SCHED_RR;
    param.sched_priority = 50;
    err = pthread_setschedparam(pthread_self(), policy, &param);

    setuid(uid);
    return (err != -1);
}

double mysecond()
{
    struct timeval tp;
    struct timezone tzp;
    int i = gettimeofday(&tp,&tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

mydsp DSP;

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
    for (int i = 11; i < COUNT; i++) {
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
    gBuffer = (float*)calloc(BSIZE, sizeof(float));
    
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

    assert(numInChan < 256);
    assert(numOutChan < 256);

    float* inChannel[256];
    float* outChannel[256];

    // allocate input buffers (initialized with white noise)
    allocBuffer();

    // allocate output channels (not initialized)
    for (int i = 0; i < numOutChan; i++) outChannel[i] = (float*)calloc(VSIZE, sizeof(float));

    // init the dsp with a resoneable sampling rate)
    DSP.init(48000);
    double* timing = (double*) calloc(COUNT, sizeof(double));

    for (int i = 0; i < COUNT; i++) {
        timing[i] = mysecond();
        for (int k = 0; k < ITER; k++) {
            // allocate new input buffers to avoid L2 cache
            for (int c = 0; c < numInChan; c++) { inChannel[c] = nextVect(); }
            DSP.compute(VSIZE,inChannel,outChannel);
        }
    }

    statistic(name, timing);
}

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

// lopt : Scan Command Line long int Arguments
long lopt(int argc, char* argv[], const char* longname, const char* shortname, long def)
{
	for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
			return atoi(argv[i]);
        }
    }
	return def;
}

int main(int argc, char* argv[])
{
    AVOIDDENORMALS;
    VSIZE = lopt(argc, argv, "--vector-size", "-vec", 4096);
    NV = lopt(argc, argv, "--num-vector", "-n", 20000);
    COUNT = lopt(argc, argv, "--count", "-c", 1000);
    ITER = lopt(argc, argv, "--iteration", "-i", 10);
    //setRealtimePriority();
  	bench(argv[0]);
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
