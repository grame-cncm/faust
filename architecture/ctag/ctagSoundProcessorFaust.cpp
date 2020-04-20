/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2004-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 MAX MSP SDK : in order to compile a MaxMSP external with this
 architecture file you will need the official MaxMSP SDK from
 cycling'74. Please check the corresponding license.
 
 ************************************************************************
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <atomic>

#include "ctagSoundProcessor.hpp"

#include "faust/dsp/dsp.h"

namespace CTAG::SP{
    class ctagSoundProcessorFaustmydsp : public ctagSoundProcessor{
    public:
        void Process(const ProcessData &);
        ~ctagSoundProcessorFaustmydsp();
        ctagSoundProcessorFaustmydsp();
        const char * GetCStrID() const;
    private:
        void setParamValueInternal(const string &id, const string &key, const int val) override;
        void loadPresetInternal() override;
        // Faust part
        dsp* fDSP;
        FAUSTFLOAT* fInputs[2];
        FAUSTFLOAT* fOutputs[2];
    };
}

using namespace CTAG::SP;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

ctagSoundProcessorFaustmydsp::ctagSoundProcessorFaustmydsp()
{
    // Faust part
    fDSP = new mydsp();
    
    // allocate deinterleaved buffers
    fInputs[0] = new FAUSTFLOAT[bufSz];
    fInputs[1] = new FAUSTFLOAT[bufSz];
    
    fOutputs[0] = new FAUSTFLOAT[bufSz];
    fOutputs[1] = new FAUSTFLOAT[bufSz];
    
    isStereo = (fDSP->getNumInputs() == 2) && (fDSP->getNumOutputs() == 2);
    // acquire model from spiffs json, model auto loads last active preset
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    // take preset values from model
    loadPresetInternal();
}

void ctagSoundProcessorFaustmydsp::Process(const ProcessData &data)
{
    // Deinterleave
    for (size_t frame; frame < bufSz; frame++) {
        fInputs[0][frame] = data.buf[frame*2];
        fInputs[1][frame] = data.buf[frame*2+1];
    }
    
    // Faust processing
    fDSP->compute(bufSz, fInputs, fOutputs);
    
    // Interleave
    for (size_t frame; frame < bufSz; frame++) {
        data.buf[frame*2] = fOutputs[0][frame];
        data.buf[frame*2+1] = fOutputs[1][frame];
    }
}

ctagSoundProcessorFaustmydsp::~ctagSoundProcessorFaustmydsp()
{
    delete [] fInputs[0];
    delete [] fInputs[1];
    delete [] fOutputs[0];
    delete [] fOutputs[1];
    
    delete fDSP;
}

const char * ctagSoundProcessorFaustmydsp::GetCStrID() const
{
    struct MyMeta : public Meta {
        std::string  name;
        virtual void declare(const char* key, const char* value)
        {
            if (strcmp(key, "name") == 0) name = value;
        }
    };
    
    MyMeta meta_data;
    fDSP->metadata(&meta_data);
   
    return "Faust" + meta_data.name;
}

void ctagSoundProcessorFaustmydsp::setParamValueInternal(const string &id, const string &key, const int val)
{
    // TODO
}

void ctagSoundProcessorFaustmydsp::loadPresetInternal()
{
    // TODO
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
