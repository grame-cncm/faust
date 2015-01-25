/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#ifndef _WIN32
#include <sys/time.h>
#endif
#include "compatibility.hh"
#include "timing.hh"
#include "global.hh"

#ifndef _WIN32
double mysecond()
{
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp,&tzp);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6);
}

#else
double mysecond() { return 0; }
#endif

void startTiming(const char* msg)
{
    if (gGlobal->gTimingSwitch) {
        assert(gGlobal->gTimingIndex < 1023);
        if (gGlobal->gTimingLog) {
            tab(gGlobal->gTimingIndex, *gGlobal->gTimingLog);
            *gGlobal->gTimingLog << "start " << msg << endl;
        } else {
            tab(gGlobal->gTimingIndex, cerr);
            cerr << "start " << msg << endl;
        }
        gGlobal->gStartTime[gGlobal->gTimingIndex++] = mysecond();
    }
}

void endTiming(const char* msg)
{
    if (gGlobal->gTimingSwitch) {
        assert(gGlobal->gTimingIndex > 0);
        gGlobal->gEndTime[--gGlobal->gTimingIndex] = mysecond();
        if (gGlobal->gTimingLog) {
            *gGlobal->gTimingLog << msg << "\t" << gGlobal->gEndTime[gGlobal->gTimingIndex] - gGlobal->gStartTime[gGlobal->gTimingIndex] << endl;
            gGlobal->gTimingLog->flush();
        } else {
            tab(gGlobal->gTimingIndex, cerr);
            cerr << "end " << msg << " (duration : " << gGlobal->gEndTime[gGlobal->gTimingIndex] - gGlobal->gStartTime[gGlobal->gTimingIndex] << ")" << endl;
        }
    }
}
