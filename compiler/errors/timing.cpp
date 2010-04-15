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

