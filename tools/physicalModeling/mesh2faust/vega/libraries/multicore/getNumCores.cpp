/*
* Copyright (c) 2015, University of Southern California
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of University of Southern California, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY UNIVERSITY OF SOUTHERN CALIFORNIA 
* ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
* IN NO EVENT SHALL UNIVERSITY OF SOUTHERN CALIFORNIA BE 
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  Multicore library.
  Code authors: Jernej Barbic, Yili Zhao, Bohan Wang
*/

#ifdef WIN32
  #include <windows.h>
#elif defined(__APPLE__)
  #include <sys/param.h>
  #include <sys/sysctl.h>
#else
  #include <unistd.h>
#endif

#include "getNumCores.h"

int GetNumCores::Get()
{
  #ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
  #elif defined(__APPLE__)
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) 
    {
      nm[1] = HW_NCPU;
      sysctl(nm, 2, &count, &len, NULL, 0);
      if(count < 1) { count = 1; }
    }
    return count;
  #else
    return sysconf(_SC_NPROCESSORS_ONLN);
  #endif
}

