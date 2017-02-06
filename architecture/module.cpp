/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

    This is sample code. This file is provided as an example of minimal
    FAUST architecture file. Redistribution and use in source and binary
    forms, with or without modification, in part or in full are permitted.
    In particular you can create a derived work of this FAUST architecture
    and distribute that work under terms of your choice.

    This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include "faust/gui/GUI.h"
#include "faust/misc.h"
#include "faust/dsp/dsp.h"

using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

<<includeclass>>

extern "C" dsp* newDsp() 									{ return new mydsp(); }
extern "C" void deleteDsp(dsp* self) 						{ delete self; }

extern "C" int getNumInputs(dsp* self) 						{ return self->getNumInputs(); }
extern "C" int getNumOutputs(dsp* self) 					{ return self->getNumOutputs(); }
extern "C" void buildUserInterface(dsp* self,UI* interface) { self->buildUserInterface(interface); }
extern "C" void init(dsp* self, int freq) 					{ self->init(freq); }
extern "C" void compute(dsp* self, int len, float** inputs, float** outputs) { self->compute(len, inputs, outputs); }
