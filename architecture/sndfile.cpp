#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sndfile.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream> 

// g++ -O3 -lm -lsndfile  myfx.cpp

using namespace std;


#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

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
			
	int 	files()		{ return fFiles.size(); }
	char* 	file (int n)	{ return fFiles[n]; }
	
	char* input_file ()	{ cout << "input file " << fFiles[0]; return fFiles[0]; }
	char* output_file() 	{  cout << "output file " << fFiles[1]; return fFiles[1]; }
		
	void process_init()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]); 
				if (p == fKeyParam.end()) {
					cout << fArgv[0] << " : unrecognized option " << fArgv[i] << "\n";
					exit(1);
				}
				char*	end;
				*(p->second.fZone) = float(strtod(fArgv[i+1], &end));
				i++;
			}
		}
	}		
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


class Separator
{
	int		fNumFrames; 
	int		fNumInputs; 
	int		fNumOutputs;
	
	float*	fInput;
	float*	fOutputs[256];

  public:
		  
	Separator(int numFrames, int numInputs, int numOutputs) 
	{
		fNumFrames 	= numFrames;
		fNumInputs 	= numInputs;
		fNumOutputs = max(numInputs, numOutputs);
		
		// allocate interleaved input channel
		fInput = (float*) aligned_calloc(fNumFrames*fNumInputs, sizeof(float));
		
		// allocate separate output channels
		for (int i = 0; i < fNumOutputs; i++) {
			fOutputs[i] = (float*) aligned_calloc (fNumFrames, sizeof(float));
		}
		
	}
	
	~Separator() 
	{
		// free interleaved input channel
		free(fInput);
		
		// free separate output channels
		for (int i = 0; i < fNumOutputs; i++) {
			free(fOutputs[i]);
		}		
	}

	float*	input()		{ return fInput; }
	
	float** outputs()	{ return fOutputs; }
	
	void 	separate()	
	{ 	
		for (int s = 0; s < fNumFrames; s++) {
			for (int c = 0; c < fNumInputs; c++) {
				fOutputs[c][s] = fInput[c + s*fNumInputs];
			}
		}
	}	
};
	
	
class Interleaver
{
	int		fNumFrames; 
	int		fNumInputs; 
	int		fNumOutputs;
	
	float*	fInputs[256];
	float*	fOutput;

  public:
		  
	Interleaver(int numFrames, int numInputs, int numOutputs) 
	{
		fNumFrames 	= numFrames;
		fNumInputs 	= max(numInputs, numOutputs);
		fNumOutputs = numOutputs;
		
		// allocate separate input channels
		for (int i = 0; i < fNumInputs; i++) {
			fInputs[i] = (float*) aligned_calloc (fNumFrames, sizeof(float));
		}
		
		// allocate interleaved output channel
		fOutput = (float*) aligned_calloc(fNumFrames*fNumOutputs, sizeof(float));
		
	}
	
	~Interleaver()
	{
		// free separate input channels
		for (int i = 0; i < fNumInputs; i++) {
			free(fInputs[i]);
		}		
		
		// free interleaved output channel
		free(fOutput);
	}
	
	float**	inputs()		{ return fInputs; }
	
	float* 	output()		{ return fOutput; }
	
	void 	interleave()
	{ 	
		for (int s = 0; s < fNumFrames; s++) {
			for (int c = 0; c < fNumOutputs; c++) {
				fOutput[c + s*fNumOutputs] = fInputs[c][s];
			}
		}
	}
};

#define kFrames 512
	
int main(int argc, char *argv[] )
{
	SNDFILE*		in_sf;
	SNDFILE*		out_sf;
	SF_INFO			in_info;
	SF_INFO			out_info;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->process_command();
	
	// open input file
	in_info.format = 0;
	in_sf = sf_open (interface->input_file(), SFM_READ, &in_info);
	if (in_sf == NULL) { sf_perror(in_sf); exit(0); }
	
	// open output file
	out_info = in_info;
    out_info.format = in_info.format;
	out_info.channels = DSP.getNumOutputs();
	out_sf = sf_open(interface->output_file(), SFM_WRITE, &out_info);
	if (out_sf == NULL) { sf_perror(out_sf); exit(0); }

	
	// create separator and interleaver
	Separator 	sep (kFrames, in_info.channels, DSP.getNumInputs());
	Interleaver ilv (kFrames, DSP.getNumOutputs(), DSP.getNumOutputs());
	
	// init signal processor
	DSP.init(in_info.samplerate);
	//DSP.buildUserInterface(interface);
	interface->process_init();

	// process all samples
	int nbf;
	do {
		nbf = sf_readf_float(in_sf, sep.input(), kFrames);
		sep.separate();
		DSP.compute(nbf, sep.outputs(), ilv.inputs());
		ilv.interleave();
		sf_writef_float(out_sf, ilv.output(), nbf);		
		//sf_write_raw(out_sf, ilv.output(), nbf);
	} while (nbf == kFrames);
	
	// close the input and output files
	sf_close(in_sf);
	sf_close(out_sf);
} 
