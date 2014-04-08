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
#include <cassert>
#ifndef _WIN32
#include <sys/time.h>
#endif
#include "compatibility.hh"
#include "timing.hh"
#include "global.hh"

using namespace std;

bool    gTimingSwitch;
int		gTimingIndex;
double 	gStartTime[1024];
double 	gEndTime[1024];

#ifndef _WIN32
double mysecond()
{
    struct timeval tp;
    struct timezone tzp;
    int i;

    i = gettimeofday(&tp,&tzp);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6);
}
#else
double mysecond() { return 0; }
#endif

/*
static void tab (int n, ostream& fout)
{
    fout << '\n';
    while (n--)     fout << '\t'; 
}
*/

void startTiming (const char* msg)
{
    if (gTimingSwitch) {
        assert(gTimingIndex < 1023);
        tab(gTimingIndex, cerr); cerr << "start " << msg << endl;
        gStartTime[gTimingIndex++] = mysecond();
    }
}

void endTiming (const char* msg)
{
    if (gTimingSwitch) {
        assert(gTimingIndex > 0);
        gEndTime[--gTimingIndex] = mysecond();
        tab(gTimingIndex, cerr); cerr << "end " << msg << " (duration : " << gEndTime[gTimingIndex] - gStartTime[gTimingIndex] << ")" << endl;
    }
}
