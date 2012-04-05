/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2007-2011 Julius O. Smith III
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
	published by the Free Software Foundation; either version 2.1 of the 
	License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
 	License along with the GNU C Library; if not, write to the Free
  	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  	02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* matlabplot.cpp = simple variation of plot.cpp */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

#include <vector>
#include <stack>
#include <string>
#include <map>
#include <list>
#include <iostream>

// g++ -O3 -lm -lsndfile  myfx.cpp

using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};



inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>




/******************************************************************************
*******************************************************************************

  							USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
    bool	fStopped;
public:

    UI() : fStopped(false) {}
    virtual ~UI() {}

    // -- active widgets

    virtual void addButton(const char* label, float* zone) = 0;
    virtual void addToggleButton(const char* label, float* zone) = 0;
    virtual void addCheckButton(const char* label, float* zone) = 0;
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

    // -- passive widgets

    virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

    // -- frames and labels

    virtual void openFrameBox(const char* label) = 0;
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;

    virtual void show() = 0;
    virtual void run() = 0;

    void stop()		{ fStopped = true; }
    bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

struct param {
    float* fZone;
    float fMin;
    float fMax;
    param(float* z, float init, float a, float b) : fZone(z), fMin(a), fMax(b) { *z = init; }
};


class CMDUI : public UI
{
    int					fArgc;
    char**				fArgv;
    vector<char*>		fFiles;
    stack<string>		fPrefix;
    map<string, param>	fKeyParam;

    void openAnyBox(const char* label)
    {
        string prefix;

        if (label && label[0]) {
            prefix = fPrefix.top() + "-" + label;
        } else {
            prefix = fPrefix.top();
        }
        fPrefix.push(prefix);
    }

    string simplify(const string& src)
    {
        int		i=0;
        int		level=0;
        string	dst;

        while (src[i] ) {

            switch (level) {

                case 0 :
                case 1 :
                case 2 :
                    // Skip the begin of the label "--foo-"
                    // until 3 '-' have been read
                    if (src[i]=='-') { level++; }
                    break;

                case 3 :
                    // copy the content, but skip non alphnum
                    // and content in parenthesis
                    switch (src[i]) {
                        case '(' :
                        case '[' :
                            level++;
                            break;

                        case '-' :
                            dst += '-';
                            break;

                        default :
                            if (isalnum(src[i])) {
                                dst+= tolower(src[i]);
                            }

                    }
                    break;

                default :
                    // here we are inside parenthesis and
                    // we skip the content until we are back to
                    // level 3
                    switch (src[i]) {

                        case '(' :
                        case '[' :
                            level++;
                            break;

                        case ')' :
                        case ']' :
                            level--;
                            break;

                        default :
                            break;
                    }

            }
            i++;
        }
        return dst;
    }


public:

    CMDUI(int argc, char *argv[]) : UI(), fArgc(argc), fArgv(argv) { fPrefix.push("-"); }
    virtual ~CMDUI() {}


    void addOption(const char* label, float* zone, float init, float min, float max)
    {
        string fullname = "-" + simplify(fPrefix.top() + "-" + label);
        fKeyParam.insert(make_pair(fullname, param(zone, init, min, max)));
    }


    virtual void addButton(const char* label, float* zone)
    {
        addOption(label,zone,0,0,1);
    }

    virtual void addToggleButton(const char* label, float* zone)
    {
        addOption(label,zone,0,0,1);
    }

    virtual void addCheckButton(const char* label, float* zone)
    {
        addOption(label,zone,0,0,1);
    }

    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addOption(label,zone,init,min,max);
    }

    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addOption(label,zone,init,min,max);
    }

    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        addOption(label,zone,init,min,max);
    }

    // -- passive widgets

    virtual void addNumDisplay(const char* label, float* zone, int precision) 						{}
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) 	{}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{}
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) 			{}

    virtual void openFrameBox(const char* label)		{ openAnyBox(label); }
    virtual void openTabBox(const char* label)			{ openAnyBox(label); }
    virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
    virtual void openVerticalBox(const char* label)		{ openAnyBox(label); }

    virtual void closeBox() 							{ fPrefix.pop(); }

    virtual void show() {}
    virtual void run() 	{}

    void printhelp()
    {
        map<string, param>::iterator i;
        cout << fArgc << "\n";
        cout << fArgv[0] << " option list : ";
        for (i = fKeyParam.begin(); i != fKeyParam.end(); i++) {
            cout << "[ " << i->first << " " << i->second.fMin << ".." << i->second.fMax <<" ] ";
        }
        cout << " infile outfile\n";
    }

    void process_command()
    {
        map<string, param>::iterator p;
        for (int i = 1; i < fArgc; i++) {
            if (fArgv[i][0] == '-') {
                if (	(strcmp(fArgv[i], "-help") == 0)
                        || (strcmp(fArgv[i], "-h") == 0)
                        || (strcmp(fArgv[i], "--help") == 0) ) 	{
                    printhelp();
                    exit(1);
                }
                p = fKeyParam.find(fArgv[i]);
                if (p == fKeyParam.end()) {
                    cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
                    printhelp();
                    exit(1);
                }
                char*	end;
                *(p->second.fZone) = float(strtod(fArgv[i+1], &end));
                i++;
            } else {
                fFiles.push_back(fArgv[i]);
            }
        }
    }

    int 	files()			{ return fFiles.size(); }
    char* 	file (int n)	{ return fFiles[n]; }

};

//----------------------------------------------------------------
//  d�inition du processeur de signal
//----------------------------------------------------------------

class dsp {
protected:
    int fSamplingFreq;
public:
    dsp() {}
    virtual ~dsp() {}

    virtual int getNumInputs() 										= 0;
    virtual int getNumOutputs() 									= 0;
    virtual void buildUserInterface(UI* interface) 					= 0;
    virtual void init(int samplingRate) 							= 0;
    virtual void compute(int len, float** inputs, float** outputs) 	= 0;
    virtual void conclude() 										{}
};


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

<<includeclass>>


mydsp	DSP;


class channels
{
    int 	fNumFrames;
    int		fNumChannels;
    float*	fBuffers[256];

public:

    channels(int nframes, int nchannels)
    {
		assert(nchannels < 256);
		
        fNumFrames		= nframes;
        fNumChannels 	= nchannels;

        // allocate audio  channels
        for (int i = 0; i < fNumChannels; i++) {
            fBuffers[i] = (float*) calloc (fNumFrames, sizeof(float));
        }
    }

    void zero()
    {
        // allocate audio  channels
        for (int i = 0; i < fNumChannels; i++) {
			for (int f = 0; f < fNumFrames; f++) {
				fBuffers[i][f] = 0.0;
			}
        }
    }

    void impulse()
    {
        // allocate audio  channels
        for (int i = 0; i < fNumChannels; i++) {
			fBuffers[i][0] = 1.0;
			for (int f = 1; f < fNumFrames; f++) {
				fBuffers[i][f] = 0.0;
			}
        }
    }

    ~channels()
    {
        // free separate input channels
        for (int i = 0; i < fNumChannels; i++) {
            free(fBuffers[i]);
        }
    }

    float**	buffers()		{ return fBuffers; }
};



#define kFrames 512

int main(int argc, char *argv[] )
{
    float			fStartAtSample;
	float			fnbsamples;


    CMDUI* interface = new CMDUI(argc, argv);
    DSP.buildUserInterface(interface);
	
    interface->addOption("-s", &fStartAtSample, 0, 0.0, 100000000.0);
	interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);

//     if (DSP.getNumInputs() > 0) {
//         fprintf(stderr,
//                 "*** input signals not supported by architecture file matlab.cpp\n");
//         exit(1);
//     }

    // init signal processor and the user interface values:
    DSP.init(44100);

    // modify the UI values according to the command-line options:
    interface->process_command();

	// prepare input channels (if any) with an impulse
    int nins = DSP.getNumInputs();
    channels inchan (kFrames, nins);
	inchan.impulse(); // after each compute we will zero them

	// prepare output channels
    int nouts = DSP.getNumOutputs();
    channels outchan (kFrames, nouts);

    // print usage info:
    printf("%% Usage: octave --persist thisfile.m\n\n");

    // print matlab-compatible matrix syntax followed by a plot command:
    printf("faustout = [ ...\n");

    
	// skip <start> samples
	int start = int(fStartAtSample);
	while (start > kFrames) {
		DSP.compute(kFrames, inchan.buffers(), outchan.buffers());
		inchan.zero();
		start -= kFrames;
	}
	if (start > 0) {
		DSP.compute(start, inchan.buffers(), outchan.buffers());
	}
	// end skip
	
	
	int nbsamples = int(fnbsamples);
    while (nbsamples > kFrames) {

        DSP.compute(kFrames, inchan.buffers(), outchan.buffers());
		inchan.zero();
        for (int i = 0; i < kFrames; i++) {
            for (int c = 0; c < nouts; c++) {
                printf(" %g", outchan.buffers()[c][i]);
            }
            if (i < kFrames-1) {
                printf("; ...\n");
            } else {
                printf("; ...\n%%---- Chunk Boundary ----\n");
            }
        }
        nbsamples -= kFrames;
    }

    if (nbsamples) { // Write out partial-chunk buffer:

        DSP.compute(nbsamples, inchan.buffers(), outchan.buffers());
		inchan.zero();
        for (int i = 0; i < nbsamples; i++) {
            for (int c = 0; c < nouts; c++) {
                printf(" %g", outchan.buffers()[c][i]);
            }
            printf("; ...\n");
        }
    }
    printf("];\n\n");
    printf("plot(faustout);\n");
    printf("title('Plot generated by %s made using ''faust -a matlabplot.cpp ...''');\n",argv[0]);
    printf("xlabel('Time (samples)');\n");
    printf("ylabel('Amplitude');\n");
    if (nouts>1) {
        printf("legend(");
        for (int c = 0; c < nouts; c++) {
            printf("'channel %d'", c+1);
            if (c<nouts-1) { printf(","); }
        }
        printf(");");
    }
    return 0;
}
