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

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

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

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

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
//  signal processor definition
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
    int*    fRates;
	float*	fBuffers[256];

  public:

	channels(int nframes, int nchannels, int* rates)
	{
		fNumFrames		= nframes;
		fNumChannels 	= nchannels;
        fRates = rates;

		// allocate audio  channels
		for (int i = 0; i < fNumChannels; i++) {
			fBuffers[i] = (float*)calloc(fNumFrames * fRates[i], sizeof(float));
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

#define kFrames 512

int main(int argc, char *argv[])
{
	float fnbsamples;
    FILE* mr_input;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);

    if (DSP.getNumInputs() > 0) {
        mr_input = fopen("mr-plot.in", "r");
        if (!mr_input) {
            fprintf(stderr, "no input file found\n");
            exit(1);
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
	channels chan_in(kFrames, nins, nins_rate);

	int nouts = DSP.getNumOutputs();
    int nouts_rate[nins];
    int max_nouts_rate = 0;
    for (int chan = 0; chan < nouts; chan++) {
        nouts_rate[chan] = DSP.getOutputRate(chan);
        max_nouts_rate = std::max(max_nouts_rate, nouts_rate[chan]);
    }
	channels chan_out(kFrames, nouts, nouts_rate);

	int nbsamples = int(fnbsamples);
	while (nbsamples > kFrames) {
        // Read input
        for (int i = 0; i < kFrames; i++) {
            for (int r = 0; r < max_nins_rate; r++) {
                for (int chan = 0; chan < nins; chan++) {
                    float sample;
                    fscanf(mr_input, "%8f\t", &sample);
                    if (r < nins_rate[chan]) {
                        chan_in.buffers()[chan][i * nins_rate[chan] + r] = sample;
                    } else {
                        // Nothing
                    }
                }
            }
		}
        // Compute
		DSP.compute(kFrames, chan_in.buffers(), chan_out.buffers());
        // Write output
		for (int i = 0; i < kFrames * max_nouts_rate; i++) {
            for (int r = 0; r < max_nouts_rate; r++) {
                for (int chan = 0; chan < nouts; chan++) {
                    if (r < nouts_rate[chan]) {
                        printf("%8f\t", chan_out.buffers()[chan][i * nouts_rate[chan] + r]);
                    } else {
                        printf("\t");
                    }
                }
            }
			cout << endl;
		}
		nbsamples -= kFrames;
	}

    // Remaining frames

    // Read input
    for (int i = 0; i < kFrames; i++) {
        for (int r = 0; r < max_nins_rate; r++) {
            for (int chan = 0; chan < nins; chan++) {
                float sample;
                fscanf(mr_input, "%8f\t", &sample);
                if (r < nins_rate[chan]) {
                    chan_in.buffers()[chan][i * nins_rate[chan] + r] = sample;
                } else {
                    // Nothing
                }
            }
        }
    }
    // Compute
    DSP.compute(kFrames, chan_in.buffers(), chan_out.buffers());
    // Write output
    for (int i = 0; i < kFrames * max_nouts_rate; i++) {
        for (int r = 0; r < max_nouts_rate; r++) {
            for (int chan = 0; chan < nouts; chan++) {
                if (r < nouts_rate[chan]) {
                    printf("%8f\t", chan_out.buffers()[chan][i * nouts_rate[chan] + r]);
                } else {
                    printf("\t");
                }
            }
        }
        cout << endl;
    }

	return 0;
}
