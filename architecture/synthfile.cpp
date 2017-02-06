/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
    as published by the Free Software Foundation; either version 3 of 
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work 
    that contains this FAUST architecture section and distribute  
    that work under terms of your choice, so long as this FAUST 
    architecture section is not modified. 

 ************************************************************************
 ************************************************************************/

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream> 
#include <map>
#include <stack>
#include <string>
#include <time.h>
#include <vector>

// g++ -O3 -lm -lsynthfile  myfx.cpp

using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

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
	float* fZone; float fMin; float fMax;
	param(float* z, float init, float a, float b) : fZone(z), fMin(a), fMax(b) { *z = init; }
};

class CMDUI : public UI
{
	int					fArgc;
	char**				fArgv;
	char*				fOutFile;
	long				fNumframes;
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
		
	CMDUI(int argc, char *argv[]) : UI(), fArgc(argc), fArgv(argv), fNumframes(44100), fOutFile("out.wav")
			{ fPrefix.push("-"); }
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
		cerr << "usage: " << fArgv[0] << " [options]" << endl;
		cerr << "        [options]: " << endl;
		cerr << "              samples: number of samples to generate, default is 44100 (1 second of sound)" << endl;
		cerr << "           -o outfile: name of the output file, default is 'out.wav'" << endl;

		if (fKeyParam.size()) {
			map<string, param>::iterator i;
			cerr << "        [faust module options]: \n";
			for (i = fKeyParam.begin(); i != fKeyParam.end(); i++) {
				cout << "           " << i->first << " [" << i->second.fMin << ".." << i->second.fMax <<" ] \n";
			}
		}
		exit(1);
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
				}

				if (strcmp(fArgv[i], "-o") == 0) {
					fOutFile = fArgv[i+1];
				}
				else {
					p = fKeyParam.find(fArgv[i]); 
					if (p == fKeyParam.end()) {
						cout << fArgv[0] << ": unrecognized option " << fArgv[i] << "\n";
						printhelp();
					}
					*(p->second.fZone) = float(strtod(fArgv[i+1], NULL));
				}
				i++;				
			}
			else  {
				fNumframes = strtol(fArgv[i], NULL, 10);
				if (fNumframes <= 0 ) printhelp();
			}
		}
	}

	char*	output_file() 	{ return fOutFile; }
	long	num_frames() 	{ return fNumframes; }
		
	void process_init()
	{
		map<string, param>::iterator p;
		for (int i = 1; i < fArgc; i++) {
			if (fArgv[i][0] == '-') {
				p = fKeyParam.find(fArgv[i]); 
				if (p != fKeyParam.end()) {
					*(p->second.fZone) = float(strtod(fArgv[i+1], NULL));
					i++;
				}
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
		
/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp	DSP;
		
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
			fInputs[i] = (float*) calloc (fNumFrames, sizeof(float));
		}
		
		// allocate interleaved output channel
		fOutput = (float*) calloc(fNumFrames*fNumOutputs, sizeof(float));
		
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

#define kFrames			512
#define kSampleRate		44100

int main(int argc, char *argv[] )
{
	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->process_command();
		
	// open output file
	SNDFILE*		out_sf;
	SF_INFO			out_info = { interface->num_frames(), kSampleRate, DSP.getNumOutputs(), 
								 SF_FORMAT_WAV|SF_FORMAT_PCM_16|SF_ENDIAN_LITTLE, 0, 0};
	out_sf = sf_open(interface->output_file(), SFM_WRITE, &out_info);
	if (out_sf == NULL) { 
		cerr << "Error: "; 
		sf_perror(out_sf); 
		exit(1); 
	}
	
	// create interleaver
	Interleaver ilv (kFrames, DSP.getNumOutputs(), DSP.getNumOutputs());
	
	// init signal processor
	DSP.init(kSampleRate);
	interface->process_init();

	// process all samples
	int frames = interface->num_frames();
	int nbf;
	do {
		 if (frames > kFrames) {
		 	nbf 	= kFrames;
		 	frames -= kFrames;
		 }
		 else {
		 	nbf 	= frames;
		 	frames 	= 0;
		 }
		DSP.compute(nbf, 0, ilv.inputs());
		ilv.interleave();
		sf_writef_float(out_sf, ilv.output(), nbf);		
	} while (nbf);
	
	sf_close(out_sf);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

