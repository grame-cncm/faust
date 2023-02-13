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

import std.datetime;
import core.cpuid;
import core.stdc.stdio;
import core.stdc.stdlib;
version (Posix)
{
   import core.sys.posix.pwd;
   import core.sys.posix.unistd;
   import core.sys.posix.pthread;
}
import dplug.core.nogc;

@trusted:
@nogc:
nothrow:

float[] gBuffer = null;  // a buffer of NV*VSize samples

__gshared ulong COUNT   = 2000;     // number of measures
__gshared ulong NV      = 4096;     // number of vectors in BIG buffer (should exceed cache)
__gshared ulong ITER    = 10;       // number of iterations per measure
__gshared ulong VSIZE   = 4096;     // size of a vector in samples
__gshared ulong IDX     = 0;        // current vector number (0 <= VIdx < NV)

bool setRealtimePriority()
{
   version (Posix)
   {
      passwd*      pw;
      int          err;
      uid_t        uid;
      int          policy;
      sched_param  param;

      uid = getuid();
      pw = getpwnam("root");
      setuid(pw.pw_uid);

      pthread_getschedparam(pthread_self(), &policy, &param);
      policy = SCHED_RR;
      param.sched_priority = 50;
      err = pthread_setschedparam(pthread_self(), policy, &param);

      setuid(uid);
      return (err != -1);
   }
   else
   {
      return false;
   }
}

double toSeconds(Duration dur)
{
   return dur.total!"nsecs" / 1e9;
}

version (D_InlineAsm_X86) version = InlineAsm_X86_Any;
else version (D_InlineAsm_X86_64) version = InlineAsm_X86_Any;

void avoidDenormals()
{
   version (InlineAsm_X86_Any)
   {
      uint mxcsr;
      asm nothrow @nogc { stmxcsr mxcsr; }
      if (sse2)
         mxcsr |= 0x8040;
      else
         mxcsr |= 0x8000;
      asm nothrow @nogc { ldmxcsr mxcsr; }
   }
}

/******************************************************************************
 *******************************************************************************

 VECTOR INTRINSICS

 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

class dsp {}
alias FAUSTFLOAT = float;

// dummy implementations
struct Meta { @nogc void opDispatch(string s, A...)(A) nothrow {} }
struct UI { @nogc void opDispatch(string s, A...)(A) nothrow {} }

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

__gshared mydsp DSP;
shared static this() { DSP = mallocNew!mydsp; }
shared static ~this() { DSP.destroyFree; }

/**
 * Bench by calling COUNT times the compute() method for
 * the computation of vsize samples
 */

enum MEGABYTE = 1048576.0;

void statistic(string name, MonoTime[] timing)
{
   double lo, hi, tot;
   double mega =  cast(double)(VSIZE*ITER)/MEGABYTE; // mega samples
   // skip first 10 values to avoid cache bias ???
   lo = hi = tot = mega/(timing[11] - timing[10]).toSeconds;
   for (int i = 11; i < COUNT; i++) {
       double delta = mega/(timing[i] - timing[i-1]).toSeconds;
       if (delta < lo) {
           lo = delta;
       } else if (delta > hi) {
           hi = delta;
       }
       tot += delta;
   }

   printf("\t" ~ "%f" ~
          "\t" ~ "%f" ~ "\t" ~ "MB/s inputs" ~
          "\t" ~ "%f" ~ "\t" ~ "MB/s outputs" ~
          "\t" ~ "%f" ~
          "\t" ~ "%f" ~ "\n",
          hi, hi*4*DSP.getNumInputs(), hi*4*DSP.getNumOutputs(), tot/(COUNT-11), lo);
}

void allocBuffer()
{
   ulong BSIZE = NV * VSIZE;
   gBuffer = mallocSlice!float(BSIZE);

   int R0_0 = 0;
   for (int j = 0; j < BSIZE; j++) {
       int R0temp0 = (12345 + (1103515245 * R0_0));
       gBuffer[j] = 4.656613e-10f*R0temp0;
       R0_0 = R0temp0;
   }
}

void deallocBuffer()
{
   freeSlice(gBuffer);
   gBuffer = null;
}

float* nextVect()
{
   IDX = (1+IDX)%NV;
   return &gBuffer[IDX*VSIZE];
}

void bench(string name)
{
   int numInChan = DSP.getNumInputs();
   int numOutChan = DSP.getNumOutputs();

   assert(numInChan < 256);
   assert(numOutChan < 256);

   float*[256] inChannel;
   float*[256] outChannel;

   // allocate input buffers (initialized with white noise)
   allocBuffer();
   scope(exit) deallocBuffer();

   // allocate output channels (not initialized)
   for (int i = 0; i < numOutChan; i++) outChannel[i] = mallocSlice!float(VSIZE).ptr;
   scope(exit) for (int i = 0; i < numOutChan; i++) freeSlice(outChannel[i][0..VSIZE]);

   // init the dsp with a resoneable sampling rate)
   DSP.initialize(48000);
   MonoTime[] timing = mallocSlice!MonoTime(COUNT);
   scope(exit) freeSlice(timing);

   for (int i = 0; i < COUNT; i++) {
       timing[i] = MonoTime.currTime;
       for (int k = 0; k < ITER; k++) {
           // allocate new input buffers to avoid L2 cache
           for (int c = 0; c < numInChan; c++) { inChannel[c] = nextVect(); }
           DSP.compute(cast(uint)VSIZE,inChannel,outChannel);
       }
   }

   statistic(name, timing);
}

//-------------------------------------------------------------------------
//									MAIN
//-------------------------------------------------------------------------

// lopt : Scan Command Line long int Arguments
long lopt(string[] args, string longname, string shortname, long def)
{
    for (ulong i = 2, n = args.length; i < n; i++) {
        if (args[i-1] == shortname || args[i-1] == longname) {
            return atoi(assumeZeroTerminated(args[i]));
        }
    }
    return def;
}

void main(string[] args)
{
    avoidDenormals();
    VSIZE = lopt(args, "--vector-size", "-vec", 4096);
    NV = lopt(args, "--num-vector", "-n", 20000);
    COUNT = lopt(args, "--count", "-c", 1000);
    ITER = lopt(args, "--iteration", "-i", 10);
    //setRealtimePriority();
    bench(args[0]);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
