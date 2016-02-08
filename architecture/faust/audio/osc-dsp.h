/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
 
#ifndef __osc_dsp__
#define __osc_dsp__

#include <stdio.h>
#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

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
	virtual ~oscdsp() 
    { 
        stop(); 
        for (int i = 0; i < numInputs(); i++) {
            delete [] fInBuffers[i];
        }
        for (int i = 0; i < numOutputs(); i++) {
            delete [] fOutBuffers[i];
        }
        delete [] fInBuffers;
        delete [] fOutBuffers;
    }

	virtual bool init(const char*name, dsp* DSP) 
    {
		fDsp = DSP;
		fDsp->init(44100);
		fInBuffers  = new float*[numInputs()];
		fOutBuffers = new float*[numOutputs()];
		for (int i = 0; i < numInputs(); i++) {
			fInBuffers[i] = new float[kMaxBuffer];
        }
		for (int i = 0; i < numOutputs(); i++) {
			fOutBuffers [i] = new float[kMaxBuffer];
        }
		return true;
	}

	virtual bool start()	{ return true; }
	virtual void stop()		{}

	void compute(int nframes) 
    {
		fDsp->compute(nframes, fInBuffers, fOutBuffers);
		for (int i= 0; i < numOutputs(); i++) {
			send(nframes, fOutBuffers [i], i);
        }
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
	int	numOutputs() const	{ return fDsp ? fDsp->getNumOutputs() : 0; }
	int	numInputs() const	{ return fDsp ? fDsp->getNumInputs() : 0; }
};

#endif
