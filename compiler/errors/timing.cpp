/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#ifndef _WIN32
#include <sys/time.h>
#endif
#include "Text.hh"
#include "compatibility.hh"
#include "global.hh"
#include "timing.hh"

using namespace std;

// Timing can be used outside of the scope of 'gGlobal'
bool     gTimingSwitch;
int      gTimingIndex;
double   gStartTime[1024];
double   gEndTime[1024];
ostream* gTimingLog = 0;

#ifndef _WIN32
double mysecond()
{
    struct timeval  tp;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

#else
double mysecond()
{
    return 0;
}
#endif

void startTiming(const char* msg)
{
    // timing
    if (gTimingSwitch) {
        gTimingLog = (getenv("FAUST_TIMING")) ? new ofstream("FAUST_TIMING_LOG", ios::app) : NULL;
        if (gTimingLog) {
            *gTimingLog << endl;
        }
    }

    if (gTimingSwitch || (gGlobal->gOutputLang == "fir")) {
        faustassert(gTimingIndex < 1023);
        if (gTimingSwitch) {
            if (gTimingLog) {
                tab(gTimingIndex, *gTimingLog);
                *gTimingLog << "start " << msg << endl;
            } else {
                tab(gTimingIndex, cerr);
                cerr << "start " << msg << endl;
            }
        }
        gStartTime[gTimingIndex++] = mysecond();
    }
}

void endTiming(const char* msg)
{
    if (gTimingSwitch || (gGlobal->gOutputLang == "fir")) {
        faustassert(gTimingIndex > 0);
        gEndTime[--gTimingIndex] = mysecond();
        double duration          = gEndTime[gTimingIndex] - gStartTime[gTimingIndex];
        if (gTimingSwitch) {
            if (gTimingLog) {
                *gTimingLog << msg << "\t" << duration << endl;
                gTimingLog->flush();
            } else {
                tab(gTimingIndex, cerr);
                cerr << "end " << msg << " (duration : " << duration << ")\n";
            }
        }
#ifdef FIR_BUILD
        if ((gGlobal->gOutputLang == "fir")) {
            if (strcmp(msg, "simplifyToNormalForm") == 0) {
                gGlobal->gStats.fNormalizeCalls++;
                gGlobal->gStats.fNormalizeTimeMs += (duration * 1000.0);
            } else if ((strcmp(msg, "prepare") == 0) || (strcmp(msg, "prepare2") == 0)) {
                gGlobal->gStats.fPrepareCalls++;
                gGlobal->gStats.fPrepareTimeMs += (duration * 1000.0);
            } else if (strcmp(msg, "compileMultiSignal") == 0) {
                gGlobal->gStats.fCodegenCalls++;
                gGlobal->gStats.fCodegenTimeMs += (duration * 1000.0);
            } else if (strcmp(msg, "patternMatcherBuild") == 0) {
                gGlobal->gStats.fPatternMatcherBuildCalls++;
                gGlobal->gStats.fPatternMatcherBuildTimeMs += (duration * 1000.0);
            } else if (strcmp(msg, "patternMatcherApply") == 0) {
                gGlobal->gStats.fPatternMatcherApplyCalls++;
                gGlobal->gStats.fPatternMatcherApplyTimeMs += (duration * 1000.0);
            }
        }
#endif
    }
}
