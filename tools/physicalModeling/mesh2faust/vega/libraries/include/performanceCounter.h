/*

* Copyright (c) 2008, Carnegie Mellon University
* All rights reserved.
*
* Code author: Jernej Barbic
* Research: Jernej Barbic, Doug L. James
* Funding: NSF, Link Foundation
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Carnegie Mellon University, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


=== A counter to measure code execution time. ===

Designed for real-time system (e.g., real-time computer animation, haptics), 
but useful in general. You can time arbitrary segments of your code.
Same interface under Windows, Linux and Mac OS X.

Under Linux/MAC OS X, accuracy is that of gettimeofday function,
which gives time in seconds and microseconds.
In practice, it has been accurate down to microsecond range.

Under Windows, the counter uses the QueryPerformanceCounter Windows API call.
Again, accuracy has been in the microsecond range in practice.

Usage:
Call StartCounter() before your code block.
Call StopCounter() after your code block.
Read the elapsed time using GetElapsedTime().

Version: 1.0

*/

#ifndef _PERFORMANCECOUNTER_H_
#define _PERFORMANCECOUNTER_H_

/**************** LINUX/MAC OS X COUNTER *******************/

#if (defined __unix__) || (defined __APPLE__)

#include "stdlib.h"
#include "sys/time.h"

class PerformanceCounter
{
public:

  PerformanceCounter() { StartCounter(); }

  void StartCounter(); // call this before your code block
  void StopCounter(); // call this after your code block

  // read the elapsed time (units are seconds, accuracy is up to microseconds)
  double GetElapsedTime();

protected:
  long startCountSec,stopCountSec,startCountMicroSec,stopCountMicroSec;
};

inline void PerformanceCounter::StartCounter()
{
  struct timeval tv;

  gettimeofday(&tv,NULL);

  startCountSec = tv.tv_sec;
  startCountMicroSec = tv.tv_usec;
  stopCountSec = startCountSec;
  stopCountMicroSec = startCountMicroSec;
}

inline void PerformanceCounter::StopCounter()
{
  struct timeval tv;

  gettimeofday(&tv,NULL);

  stopCountSec = tv.tv_sec;
  stopCountMicroSec = tv.tv_usec;
}


inline double PerformanceCounter::GetElapsedTime()
{
  double elapsedTime = 1.0 * (stopCountSec-startCountSec) + 1E-6 * (stopCountMicroSec - startCountMicroSec);
  return elapsedTime;
}

#endif

#if defined(_WIN32) || defined(WIN32)

/**************** WINDOWS COUNTER *******************/

#include <windows.h>

class PerformanceCounter
{
public:

  PerformanceCounter() 
  {
    // reset the counter frequency
    QueryPerformanceFrequency(&timerFrequency);
    StartCounter(); 
  }

  void StartCounter(); // call this before your code block
  void StopCounter(); // call this after your code block

  // read elapsed time (units are seconds, accuracy is up to microseconds)
  double GetElapsedTime();

protected:
  LARGE_INTEGER timerFrequency;
  LARGE_INTEGER startCount,stopCount;
};

inline void PerformanceCounter::StartCounter()
{
  QueryPerformanceCounter(&startCount);
}

inline void PerformanceCounter::StopCounter()
{
  QueryPerformanceCounter(&stopCount);
}


inline double PerformanceCounter::GetElapsedTime()
{
  return ((double)(stopCount.QuadPart - startCount.QuadPart))
    / ((double)timerFrequency.QuadPart);
}

#endif
#endif

