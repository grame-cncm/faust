/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-effect.c ****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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
 
#include <algorithm>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/gui/CGlue.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

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

class Cdsp : public dsp {
    
    private:
    
        mydsp* fDSP;
    
    public:
    
        Cdsp():fDSP(newmydsp())
        {}
    
        virtual ~Cdsp()
        {
            deletemydsp(fDSP);
        }
    
        virtual int getNumInputs() { return getNumInputsmydsp(fDSP); }
    
        virtual int getNumOutputs() { return getNumOutputsmydsp(fDSP); }
    
        virtual void buildUserInterface(UI* interface)
        {
            UIGlue glue;
            buildUIGlue(&glue, interface, sizeof(FAUSTFLOAT) == 8);
            buildUserInterfacemydsp(fDSP, &glue);
        }
    
        virtual int getSampleRate()
        {
            return getSampleRatemydsp(fDSP);
        }
    
        virtual void init(int samplingRate)
        {
            initmydsp(fDSP, samplingRate);
        }
    
        static void classInit(int samplingRate)
        {
            classInitmydsp(samplingRate);
        }
    
        virtual void instanceInit(int samplingRate)
        {
            instanceInitmydsp(fDSP, samplingRate);
        }
    
        virtual void instanceConstants(int samplingRate)
        {
            instanceConstantsmydsp(fDSP, samplingRate);
        }
    
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
    
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP);
        }
    
        virtual Cdsp* clone()
        {
            return new Cdsp();
        }
    
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
        }
    
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            computemydsp(fDSP, count, input, output);
        }
    
};

// Factory API
dsp* createmydsp() { return new Cdsp(); }

/******************** END minimal-effect.c ****************/
