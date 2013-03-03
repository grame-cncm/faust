
#ifndef __osc_dsp__
#define __osc_dsp__

#include <stdio.h>
#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"
#include "OSCIO.h"

/******************************************************************************
*******************************************************************************

							OSC AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

#define kMaxBuffer 4096

class oscdsp : public audio, public oscfaust::OSCIO {
	dsp*	 fDsp;
	float ** fInBuffers, **fOutBuffers;

 public:
    oscdsp(const char * dst, int argc, char *argv[]) : OSCIO(dst), fDsp(0), fInBuffers(0), fOutBuffers(0)
    {
        for (int i = 1; i < argc-1; i++) {
            if (!strcmp(argv[i], "-iodst")) setDest (argv[i+1]);
        }
    }
	virtual ~oscdsp() { stop(); }

	virtual bool init(const char*name, dsp* DSP) 
    {
		fDsp = DSP;
		fDsp->init(44100);
		fInBuffers  = new float*[numInputs()];
		fOutBuffers = new float*[numOutputs()];
		for (int i= 0; i < numInputs(); i++)
			fInBuffers[i] = new float[kMaxBuffer];
		for (int i= 0; i < numOutputs(); i++)
			fOutBuffers [i] = new float[kMaxBuffer];
		return true;
	}

	virtual bool start()	{ return true; }
	virtual void stop()		{}

	void compute(int nframes) 
    {
		fDsp->compute(nframes, fInBuffers, fOutBuffers);
		for (int i= 0; i < numOutputs(); i++)
			send( nframes, fOutBuffers [i], i);
	}

	void receive(int nvalues, float* val) 
    {
		int inChans = numInputs();
		if (!inChans) {
			compute(nvalues);
			return;
		}

		for (int i=0; i < nvalues; i++) {
			int c = i % inChans;
			int frame = i / inChans;
			fInBuffers[c][frame] = val[i];
		}
		compute (nvalues / inChans);
	}
	int		numOutputs() const	{ return fDsp ? fDsp->getNumOutputs() : 0; }
	int		numInputs() const	{ return fDsp ? fDsp->getNumInputs() : 0; }
};

#endif
