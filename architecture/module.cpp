/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include "faust/gui/GUI.h"
#include "faust/misc.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

using namespace std;

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

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" EXPORT dsp* newDsp() { return new mydsp(); }
extern "C" EXPORT void deleteDsp(dsp* self) { delete self; }

extern "C" EXPORT int getNumInputs(dsp* self) { return self->getNumInputs(); }
extern "C" EXPORT int getNumOutputs(dsp* self) { return self->getNumOutputs(); }
extern "C" EXPORT void buildUserInterface(dsp* self, UI* interface) { self->buildUserInterface(interface); }
extern "C" EXPORT void getSampleRate(dsp* self) { self->getSampleRate(self); }
extern "C" EXPORT void init(dsp* self, int sample_rate) { self->init(sample_rate); }
extern "C" EXPORT void instanceInit(dsp* self, int sample_rate) { self->instanceInit(sample_rate); }
extern "C" EXPORT void instanceConstants(dsp* self, int sample_rate) { self->instanceConstants(sample_rate); }
extern "C" EXPORT void instanceResetUserInterface(dsp* self) { self->instanceResetUserInterface(); }
extern "C" EXPORT dsp*  clone(dsp* self) { return self->clone(); }
extern "C" EXPORT void metadata(dsp* self, Meta* m) { self->metadata(m); }
extern "C" EXPORT void compute(dsp* self, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { self->compute(count, inputs, outputs); }

/********************END ARCHITECTURE SECTION (part 2/2)****************/

