/* octave.cpp
   Copyright (C) 2009 by Bjoern Anton Erlach. */

// OCTAVE architecture file for faust.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
// 02111-1307 USA
//-------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <vector>
#include <string>
#include <map>
#include <iostream> 
#include <oct.h>


using namespace std;

// TODO: find out what to do with this Meta thing
struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};


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
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }


<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

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
	string fName; float *fVals; float* fZone; float fMin; float fMax;
	param(string name, float* z, float init, float a, float b) : fName(name), fVals(NULL), fZone(z), fMin(a), fMax(b) { *z = init; }
};


class FNUI : public UI
{
	vector<param>	fParam;
	int numOptions;


public:
	FNUI() : UI() { numOptions=0; }
	virtual ~FNUI() {}
	

	void addOption(const char* label, float* zone, float init, float min, float max)
	{
	  string fullname = label;
	  fParam.push_back(param(fullname, zone, init, min, max));
	  numOptions++;
	}

	virtual vector<param> getOpts () { return fParam; }

	virtual void addButton(const char* label, float* zone)
	{
		addOption(label,zone,0,0,1);
	}
	
	virtual int getNumOptions() { return numOptions; }

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
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
	

	virtual void openFrameBox(const char* label)		{ }
	virtual void openTabBox(const char* label)              { }
	virtual void openHorizontalBox(const char* label)	{ }
	virtual void openVerticalBox(const char* label)		{ }
	
	//	virtual void openFrameBox(const char* label)		{ openAnyBox(label); }
	//virtual void openTabBox(const char* label)              { openAnyBox(label); }
	//virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
	//virtual void openVerticalBox(const char* label)		{ openAnyBox(label); }
	
	//virtual void closeBox() { fPrefix.pop(); }
	virtual void closeBox() { }
	virtual void run() 	{}
	virtual void show() 	{}

};



/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------
//  abstract definition of a signal processor
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 						= 0;
	virtual int getNumOutputs() 					= 0;
	virtual void buildUserInterface(UI* interface) 	= 0;
	virtual void init(int samplingRate) 			= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		

<<includeclass>>


//----------------------------------------------------------------------------
//  Octave interface
//----------------------------------------------------------------------------

// Prefered way to allocate memory
#define ALLOC(x) alloca(x)
#define FREE(x) ((void)0)
// if ALLOCA is not available use MALLOC
//#define ALLOC(x) malloc(x)
//#define FREE(x) free(x)

#define QUOTEME(x) #x

#define DEFAULT_SAMPLERATE 44100
#define DEFAULT_BLOCKSIZE 64

// linear interpolation for vector valued control inputs
void
interpolate_ctrlin (float *vals, NDArray in, int n)
{
  int nin = in.length();
  double ratio = (double)(n-1)/(double)(nin-1);
  int irat = (int) ratio;
  double frat = ratio - (double) irat;
  double rest = 0;
  int i = 0;
  float x;

  for (int j=0; j<(nin-1); j++) {
	  float del;
	  int seglength = irat; 
	  rest += frat;
	  if (rest >= 1.0) {
		  seglength ++;
		  rest -= 1.0;
	  }
	  del = (in(j+1) - in(j)) / (float) seglength;
	  x = in(j);
	  for (int k=0; k<seglength; k++) {
		  vals[i++] = x;
		  x += del;
	  }
  }
  for (; i<n; i++) {
	  vals[i] = in(nin-1);
  }
}



DEFUN_DLD (FAUST_FUNC_NAME, args, nargout,    
	   "type " QUOTEME(FAUST_FUNC_NAME) "() to see the arguments.\n")
{
  int nargin = args.length();
  int numIn;
  int numOut;
  int numOpts;
  int maxInputLength = 0;
  mydsp DSP;
  int ngivenctrls;
  float **finputs;
  float **foutputs;
  float **controlinputs;
  int ctrllength;
  int ctrlargoff;
  int allscalarctrls = 1;
  // TODO: float **controloutputs;
  int i;
  vector<param> opts;
  int bsize;
  int srate;
  octave_value_list retval;
  octave_value tmp;

  FNUI* interface = new FNUI(); 
  DSP.buildUserInterface(interface);

  // check if global variable FAUST_BLOCKSIZE is set.
  tmp = get_global_value ("FAUST_BLOCKSIZE", true);
  if (tmp.is_defined ()) 
	  bsize = (int) tmp.scalar_value();  
  else {
	  bsize = DEFAULT_BLOCKSIZE;
  }

  // check if global variable FAUST_SAMPLERATE is set.
  tmp = get_global_value ("FAUST_SAMPLERATE", true);
  if (tmp.is_defined ())
	  srate = (int) tmp.scalar_value();
  else {
	  srate = DEFAULT_SAMPLERATE;
  }

  DSP.init(srate);
  opts = interface->getOpts();

  numIn = DSP.getNumInputs();
  numOut = DSP.getNumOutputs();
  numOpts = interface->getNumOptions();

  // print a usage message in case the function is called with too few arguments
  if (nargin < numIn || nargin == 0) {
	  if (numOut>1) {
		  octave_stdout << "[out1";
		  for (i=2; i<=numOut; i++) 
			  octave_stdout << ",out" << i;
		  octave_stdout << "] = " << QUOTEME(FAUST_FUNC_NAME) << "(";
	  } else {
		  octave_stdout << "out = " << QUOTEME(FAUST_FUNC_NAME) << "(";
	  }
	  if (numIn == 0) 
		  octave_stdout << "numsamps";
	  else
		  octave_stdout << "in1";
	  for (i=2; i<=numIn; i++) 
		  octave_stdout << ", in" << i;
	  for (i=0; i<numOpts; i++) 
		  octave_stdout << ", " << opts[i].fName;
	  octave_stdout << ")\n";
	  delete interface;
	  return retval;
 }

  // If we have inputs we use the length of the longest input vector
  // as length of the output to be produced.
  // If we don't have inputs, the first argument specifies the number of
  // samples to be produced.
  if (numIn == 0) {
	  maxInputLength = args(0).scalar_value();
	  ctrlargoff = 1;
  } else {
	  ctrlargoff = numIn;
	  for (i=0; i<numIn; i++) {
		  octave_idx_type nr = args(i).matrix_value().rows();
		  octave_idx_type nc = args(i).matrix_value().columns();
		  if (nr == 1) {
			  if (nc > maxInputLength) 
				  maxInputLength = nc;
		  } else if (nc == 1) {
			  if (nr > maxInputLength) 
				  maxInputLength = nr;
		  } else {
			  maxInputLength = nc;
			  octave_stdout << "Argument " << i << " has wrong dimensions " << nr << "x" << nc << "\n";
		  }
	  }
  }


  ctrllength = (maxInputLength+bsize-1)/bsize;

  // check for arguments that should serve as control inputs 
  for (i=ctrlargoff; i<nargin; i++) {
	  if ((i-ctrlargoff) < numOpts) {
		  NDArray v = args(i).array_value(); 
		  if (v.length() > 1) {
			  allscalarctrls = 0;
			  opts[i-ctrlargoff].fVals = (float*) ALLOC(sizeof(float)*ctrllength);
			  interpolate_ctrlin(opts[i-ctrlargoff].fVals, v, ctrllength);
			  *opts[i-ctrlargoff].fZone = (float) v(0);
		  } else {
			  *opts[i-ctrlargoff].fZone = (float) args(i).scalar_value();
		  }
	  }
  }
	  
  for (i=0; i<numOpts; i++) {
	  octave_stdout << "Parameter " << opts[i].fName << ": " << *opts[i].fZone << "\n";
  }

  finputs = (float**) ALLOC(sizeof(float*) * numIn);
  foutputs = (float**) ALLOC(sizeof(float*) * numOut);  

  // Copy the matrix and convert to floats - This is a real slowdown!
  for (i=0; i<numIn; i++) {
	  Matrix m = args(i).matrix_value();
	  float *p;
	  finputs[i] = (float*) ALLOC(maxInputLength * sizeof(float));
	  memset(finputs[i], 0, sizeof(float)*maxInputLength);
	  p = finputs[i];
	  if (m.rows() > m.columns()) {
		  for (int j=0; j<m.rows(); j++) {
			  *p++ = (float) m(j,0); 
		  }
	  } else {
		  for (int j=0; j<m.columns(); j++) {
			  *p++ = (float) m(0,j); 
		  }
	  }
  }

  // allocate output vectors
  for (i=0; i<numOut; i++) {
	  foutputs[i] = (float*) ALLOC(maxInputLength * sizeof(float));
	  memset(foutputs[i], 0, sizeof(float)*maxInputLength);
  }

  if (allscalarctrls) {
	  DSP.compute(maxInputLength, finputs, foutputs);
  } else {
	  int nleft = maxInputLength;
	  int k = 0;
	  float **fins;
	  float **fouts;
	  fins = (float**) ALLOC(sizeof(float*) * numIn);
	  fouts = (float**) ALLOC(sizeof(float*) * numOut);
	  memcpy(fins, finputs, sizeof(float*)*numIn);	  
	  memcpy(fouts, foutputs, sizeof(float*)*numOut);
	  while (nleft > 0) {
		  int n = min(bsize, nleft);
		  for (i=0; i<numOpts; i++) {
			  if (opts[i].fVals) {
				  *opts[i].fZone = opts[i].fVals[k];
			  }
		  }
		  DSP.compute(n, fins, fouts);
		  nleft -= n;
		  k++;
		  for (i=0; i<numIn; i++) 
			  fins[i] += n;
		  for (i=0; i<numOut; i++) 
			  fouts[i] += n;
	  }
	  FREE(fins);
	  FREE(fouts);
  }

  // copy the output from the float arrays (and free all tmp memory if malloc is used)
  for (i=0; i<numOut; i++) {
	  Matrix output = Matrix(1, maxInputLength);
	  for (int j=0; j<maxInputLength; j++) 
		  output(0, j) = (double) foutputs[i][j];
	  FREE(foutputs[i]);
	  retval(i) = output;
  }
  for (i=0; i<numOpts; i++) {
	  if (opts[i].fVals) {
		  FREE(opts[i].fVals);
	  }
  }
  for (i=0; i<numIn; i++) {
	  FREE(finputs[i]);
  }
  FREE(foutputs);
  FREE(finputs);

  delete interface;
  return retval;
} 
