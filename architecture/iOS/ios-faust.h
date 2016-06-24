//----------------------------------------------------------
// name: "volume"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2006"
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
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
    float 	fConst0;
    float 	fTempPerm0;
    float 	fRec0[2];
    FAUSTFLOAT 	fbargraph0;
    float 	fTempPerm1;
    float 	fRec1[2];
    FAUSTFLOAT 	fbargraph1;
    int fSamplingFreq;
    
public:
    virtual void metadata(Meta* m) 	{
        m->declare("name", "vumeter");
        m->declare("version", "1.0");
        m->declare("author", "Grame");
        m->declare("license", "BSD");
        m->declare("copyright", "(c)GRAME 2006");
        m->declare("math.lib/name", "Math Library");
        m->declare("math.lib/author", "GRAME");
        m->declare("math.lib/copyright", "GRAME");
        m->declare("math.lib/version", "1.0");
        m->declare("math.lib/license", "LGPL with exception");
        m->declare("music.lib/name", "Music Library");
        m->declare("music.lib/author", "GRAME");
        m->declare("music.lib/copyright", "GRAME");
        m->declare("music.lib/version", "1.0");
        m->declare("music.lib/license", "LGPL with exception");
    }
    
    virtual int getNumInputs() 	{ return 2; }
    virtual int getNumOutputs() 	{ return 2; }
    static void classInit(int samplingFreq) {
    }
    virtual void instanceInit(int samplingFreq) {
        fSamplingFreq = samplingFreq;
        fConst0 = (1.0f / min(1.92e+05f, max(1.0f, (float)fSamplingFreq)));
        fTempPerm0 = 0;
        for (int i=0; i<2; i++) fRec0[i] = 0;
        fTempPerm1 = 0;
        for (int i=0; i<2; i++) fRec1[i] = 0;
    }
    virtual void init(int samplingFreq) {
        classInit(samplingFreq);
        instanceInit(samplingFreq);
    }
    virtual dsp* clone() {
        return new mydsp();
    }
    virtual int getSampleRate() {
        return fSamplingFreq;
    }
    virtual void buildUserInterface(UI* interface) {
        interface->openVerticalBox("0x00");
        interface->declare(&fbargraph0, "2", "");
        interface->declare(&fbargraph0, "unit", "dB");
        interface->addHorizontalBargraph("0x7fdd89d68530", &fbargraph0, -7e+01f, 5.0f);
        interface->declare(&fbargraph1, "2", "");
        interface->declare(&fbargraph1, "unit", "dB");
        interface->addHorizontalBargraph("0x7fdd89d69520", &fbargraph1, -7e+01f, 5.0f);
        interface->closeBox();
    }
    virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
        //zone1
        //zone2
        //zone2b
        //zone3
        FAUSTFLOAT* input0 = input[0];
        FAUSTFLOAT* input1 = input[1];
        FAUSTFLOAT* output0 = output[0];
        FAUSTFLOAT* output1 = output[1];
        //LoopGraphScalar
        for (int i=0; i<count; i++) {
            fTempPerm0 = (float)input0[i];
            fRec0[0] = max((fRec0[1] - fConst0), fabsf(fTempPerm0));
            fbargraph0 = (20 * log10f(max(0.00031622776f, fRec0[0])));
            output0[i] = (FAUSTFLOAT)fTempPerm0;
            fTempPerm1 = (float)input1[i];
            fRec1[0] = max((fRec1[1] - fConst0), fabsf(fTempPerm1));
            fbargraph1 = (20 * log10f(max(0.00031622776f, fRec1[0])));
            output1[i] = (FAUSTFLOAT)fTempPerm1;
            // post processing
            fRec1[1] = fRec1[0];
            fRec0[1] = fRec0[0];
        }
    }
};


/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

dsp* DSP;

/********************END ARCHITECTURE SECTION (part 2/2)****************/
