/************************** BEGIN osc-dsp.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
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
    
    private:

        ::dsp* fDSP;
        float **fInBuffers, **fOutBuffers;

    public:
    
        oscdsp(const char* dst, int argc, char* argv[])
        : OSCIO(dst), fDSP(nullptr), fInBuffers(nullptr), fOutBuffers(nullptr)
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

        virtual bool init(const char* name, ::dsp* DSP)
        {
            fDSP = DSP;
            fDSP->init(44100);
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
            fDSP->compute(nframes, fInBuffers, fOutBuffers);
            for (int i = 0; i < numOutputs(); i++) {
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

            for (int i = 0; i < nvalues; i++) {
                int c = i % inChans;
                int frame = i / inChans;
                fInBuffers[c][frame] = val[i];
            }
            compute(nvalues / inChans);
        }

        int	getNumInputs() const	{ return fDSP ? fDSP->getNumInputs() : 0; }
        int	getNumOutputs() const	{ return fDSP ? fDSP->getNumOutputs() : 0; }
	
};

#endif
/**************************  END  osc-dsp.h **************************/
