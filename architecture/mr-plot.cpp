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
#include <iostream>

// g++ -O3 -lm -lsndfile  myfx.cpp

using namespace std;

#include "gui/GUI.h"
#include "audio/dsp.h"
#include "misc.h"

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }

inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }

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

struct param {
	float* fZone; float fMin; float fMax;
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
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) 	{}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) 			{}

    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
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

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

<<includeclass>>

mydsp DSP;

class channels
{

 protected:

	int 	fNumFrames;
	int		fNumChannels;
    int*    fRates;
	float*	fBuffers[256];

  public:

	channels(int nframes, int nchannels, int* rates)
	{
		fNumFrames		= nframes;
		fNumChannels 	= nchannels;
        fRates = rates;

		// allocate audio  channels
		for (int chan = 0; chan < fNumChannels; chan++) {
			fBuffers[chan] = (float*)calloc(fNumFrames * fRates[chan], sizeof(float));
		}
	}

	~channels()
	{
		// free separate input channels
		for (int i = 0; i < fNumChannels; i++) {
		//	free(fBuffers[i]);
		}
	}

	float**	buffers()		{ return fBuffers; }

};

class input_channels : public channels
{
    public:

	input_channels(int nframes, int nchannels, int* rates)
        :channels(nframes, nchannels, rates)
    {}

    void dirac()
    {
        cout << "dirac: chan " << fNumChannels << " frames: " << fNumFrames << endl;
        for (int chan = 0; chan < fNumChannels; chan++) {
            memset(fBuffers[chan], 0, fNumFrames * fRates[chan] * sizeof(float));
            fBuffers[0][0] = 1.f;
        }
    }

    void step()
    {
        cout << "step: chan " << fNumChannels << " frames: " << fNumFrames << endl;
        for (int chan = 0; chan < fNumChannels; chan++) {
           for (int frame = 0; frame < fNumFrames * fRates[chan]; frame++) {
                fBuffers[chan][frame] = 1.0;
            }
         }
    }

    void ramp()
    {
        cout << "ramp: chan " << fNumChannels << " frames: " << fNumFrames << endl;
        for (int chan = 0; chan < fNumChannels; chan++) {
           for (int frame = 0; frame < fNumFrames * fRates[chan]; frame++) {
                fBuffers[chan][frame] = (float(frame)/float(fNumFrames * fRates[chan]));
            }
        }
    }

};

#define kFrames 128

int main(int argc, char *argv[])
{
	float fnbsamples;
    float signal_test_type;
    FILE* mr_input = NULL;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);
    interface->addOption("-s", &signal_test_type, 1.0, 0.0, 2.0);

    if (DSP.getNumInputs() > 0) {
        mr_input = fopen("mr-plot.in", "r");
        if (!mr_input) {
            fprintf(stderr, "no input file found\n");
        }
    }

	// init signal processor and the user interface values
	DSP.init(44100);

	// modify the UI values according to the command line options
	interface->process_command();

    int nins = DSP.getNumInputs();
    int nins_rate[nins];
    int max_nins_rate = 0;
    for (int chan = 0; chan < nins; chan++) {
        nins_rate[chan] = DSP.getInputRate(chan);
        max_nins_rate = std::max(max_nins_rate, nins_rate[chan]);
    }
	input_channels chan_in(kFrames, nins, nins_rate);

	int nouts = DSP.getNumOutputs();
    int nouts_rate[nins];
    int max_nouts_rate = 0;
    for (int chan = 0; chan < nouts; chan++) {
        nouts_rate[chan] = DSP.getOutputRate(chan);
        max_nouts_rate = std::max(max_nouts_rate, nouts_rate[chan]);
    }
	channels chan_out(kFrames, nouts, nouts_rate);

    switch(int(signal_test_type)) {

        case 0:
            chan_in.dirac();
            break;
        case 1:
            chan_in.step();
            break;
        case 2:
            chan_in.ramp();
            break;
    }

	int nbsamples = int(fnbsamples);
  	while (nbsamples > kFrames) {
        // Read input
        for (int i = 0; i < kFrames; i++) {
            for (int r = 0; r < max_nins_rate; r++) {
                for (int chan = 0; chan < nins; chan++) {
                    /*
                    float sample;
                    if (mr_input) {
                        fscanf(mr_input, "%8f\t", &sample);
                    } else {
                        sample = float(i);
                    }
                    if (r < nins_rate[chan]) {
                        chan_in.buffers()[chan][i * nins_rate[chan] + r] = sample;
                    } else {
                        // Nothing
                    }
                    */
                }
            }
		}
        // Compute
		DSP.compute(kFrames, chan_in.buffers(), chan_out.buffers());
        // Write output
		for (int i = 0; i < kFrames; i++) {
            cout << "--- frame " << i << " ---" << endl;
            for (int r = 0; r < max_nouts_rate; r++) {
                for (int chan = 0; chan < nouts; chan++) {
                    if (r < nouts_rate[chan]) {
                        printf("%8f\t", chan_out.buffers()[chan][i * nouts_rate[chan] + r]);
                    } else {
                        printf("\t");
                    }
                }
                printf("\n");
            }
		}
		nbsamples -= kFrames;
	}

    // Remaining frames

    // Read input
    for (int i = 0; i < kFrames; i++) {
        for (int r = 0; r < max_nins_rate; r++) {
            for (int chan = 0; chan < nins; chan++) {
                /*
                float sample;
                if (mr_input) {
                    fscanf(mr_input, "%8f\t", &sample);
                } else {
                    sample = float(i);
                }
                if (r < nins_rate[chan]) {
                    chan_in.buffers()[chan][i * nins_rate[chan] + r] = sample;
                } else {
                    // Nothing
                }
                */
            }
        }
    }
    // Compute
    DSP.compute(kFrames, chan_in.buffers(), chan_out.buffers());
    // Write output
    for (int i = 0; i < kFrames; i++) {
        cout << "--- frame " << i << " ---" << endl;
        for (int r = 0; r < max_nouts_rate; r++) {
            for (int chan = 0; chan < nouts; chan++) {
                if (r < nouts_rate[chan]) {
                    printf("%8f\t", chan_out.buffers()[chan][i * nouts_rate[chan] + r]);
                } else {
                    printf("\t");
                }
            }
            printf("\n");
        }
    }

	return 0;
}
