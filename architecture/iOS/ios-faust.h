//----------------------------------------------------------
// name: "volume"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2006"
//
// Dummmy code
//----------------------------------------------------------

/* link with  */
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

#import "FICocoaUI.h"

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
    private:
        int fSampleRate;
        
    public:
        virtual void metadata(Meta* m) 	{}
        
        virtual int getNumInputs() { return -1; }
        virtual int getNumOutputs() { return -1; }
        static void classInit(int sample_rate) {}
        virtual void instanceInit(int sample_rate) {}
        virtual void init(int sample_rate)
        {
            classInit(sample_rate);
            instanceInit(sample_rate);
        }
        virtual dsp* clone()
        {
            return new mydsp();
        }
        virtual int getSampleRate()
        {
            return fSampleRate;
        }
        virtual void buildUserInterface(UI* interface) {}
        virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {}
};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

dsp* DSP;

/********************END ARCHITECTURE SECTION (part 2/2)****************/
