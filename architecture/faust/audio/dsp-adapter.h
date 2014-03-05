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

#ifndef __dsp_adapter__
#define __dsp_adapter__

#include <string.h>
#include "faust/audio/dsp.h"

class dsp_adapter : public dsp {
    
private:
    
    FAUSTFLOAT** fAdaptedInputs;
    FAUSTFLOAT** fAdaptedOutputs;
    int fHardwareInputs;
    int fHardwareOutputs;
    dsp* fDsp;
    
public:
    
    dsp_adapter(dsp* dsp, int hardware_inputs, int hardware_outputs, int buffer_size)
    {
        fDsp = dsp;
        fHardwareInputs = hardware_inputs;
        fHardwareOutputs = hardware_outputs;
        
        fAdaptedInputs = new FAUSTFLOAT*[dsp->getNumInputs()];
        for (int i = 0; i < dsp->getNumInputs() - hardware_inputs; i++) {
            fAdaptedInputs[i + hardware_inputs] = new FAUSTFLOAT[buffer_size];
            memset(fAdaptedInputs[i + hardware_inputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
        }
        
        fAdaptedOutputs = new FAUSTFLOAT*[dsp->getNumOutputs()];
        for (int i = 0; i < dsp->getNumOutputs() - hardware_outputs; i++) {
            fAdaptedOutputs[i + hardware_outputs] = new FAUSTFLOAT[buffer_size];
            memset(fAdaptedOutputs[i + hardware_outputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
        }
    }
    
    virtual~ dsp_adapter()
    {
        for (int i = 0; i < fDsp->getNumInputs() - fHardwareInputs; i++) {
            delete [] fAdaptedInputs[i + fHardwareInputs];
        }
        delete [] fAdaptedInputs;
        
        for (int i = 0; i < fDsp->getNumOutputs() - fHardwareOutputs; i++) {
            delete [] fAdaptedOutputs[i + fHardwareOutputs];
        }
        delete [] fAdaptedOutputs;
        
        delete fDsp;
    }
    
    int getNumInputs() 	{return fDsp->getNumInputs();}
    int getNumOutputs() {return fDsp->getNumOutputs();}
    void buildUserInterface(UI* ui_interface) {return fDsp->buildUserInterface(ui_interface);}
    void init(int samplingRate) {return fDsp->init(samplingRate);}
   
    virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        for (int i = 0; i < fHardwareInputs; i++) {
            fAdaptedInputs[i] = inputs[i];
        }
        for (int i = 0; i < fHardwareOutputs; i++) {
            fAdaptedOutputs[i] = outputs[i];
        }
        fDsp->compute(len, fAdaptedInputs, fAdaptedOutputs);
    }
};

#endif
