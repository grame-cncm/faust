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
#ifndef WIN32
#include <sys/time.h>
#endif
#include "timing.hh"

using namespace std;

#if 0
double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int		lIndex=0;
double 	lStartTime[1024];
double 	lEndTime[1024];

static void tab (int n, ostream& fout)
{
        fout << '\n';
        while (n--)     fout << '\t'; 
}

void startTiming (const char* msg)
{
	assert(lIndex < 1023);
	tab(lIndex, cerr); cerr << "start " << msg << endl;
	lStartTime[lIndex++] = mysecond();
}

void endTiming (const char* msg)
{
	assert(lIndex>0);
	lEndTime[--lIndex] = mysecond();
	tab(lIndex, cerr); cerr << "end " << msg << " (duration : " << lEndTime[lIndex] - lStartTime[lIndex] << ")" << endl;
}

#else

void startTiming (const char* msg)
{}

void endTiming (const char* msg)
{}

#endif

