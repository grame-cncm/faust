/************************** BEGIN CInterface.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI and Meta classes for C or LLVM generated code.
 ******************************************************************************/

// -- widget's layouts

using openTabBoxFun = void (*)(void *, const char *);
using openHorizontalBoxFun = void (*)(void *, const char *);
using openVerticalBoxFun = void (*)(void *, const char *);
using closeBoxFun = void (*)(void *);

// -- active widgets

using addButtonFun = void (*)(void *, const char *, float *);
using addCheckButtonFun = void (*)(void *, const char *, float *);
using addVerticalSliderFun = void (*)(void *, const char *, float *, float, float, float, float);
using addHorizontalSliderFun = void (*)(void *, const char *, float *, float, float, float, float);
using addNumEntryFun = void (*)(void *, const char *, float *, float, float, float, float);

// -- passive widgets

using addHorizontalBargraphFun = void (*)(void *, const char *, float *, float, float);
using addVerticalBargraphFun = void (*)(void *, const char *, float *, float, float);

// -- soundfiles
    
using addSoundfileFun = void (*)(void *, const char *, const char *, struct Soundfile **);

using declareFun = void (*)(void *, float *, const char *, const char *);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

using metaDeclareFun = void (*)(void *, const char *, const char *);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

using dsp_imp = char;
    
using newDspFun = dsp_imp *(*)();
using deleteDspFun = void (*)(dsp_imp *);
using allocateDspFun = void (*)(dsp_imp *);
using destroyDspFun = void (*)(dsp_imp *);
using getNumInputsFun = int (*)(dsp_imp *);
using getNumOutputsFun = int (*)(dsp_imp *);
using buildUserInterfaceFun = void (*)(dsp_imp *, UIGlue *);
using initFun = void (*)(dsp_imp *, int);
using clearFun = void (*)(dsp_imp *);
using getSampleRateFun = int (*)(dsp_imp *);
using computeFun = void (*)(dsp_imp *, int, float **, float **);
using metadataFun = void (*)(MetaGlue *);
using classInitFun = void (*)(int);
using getJSONFun = const char *(*)();
    
/***************************************
 * DSP memory manager functions
 ***************************************/

using allocateFun = void *(*)(void *, size_t);
using destroyFun = void (*)(void *, void *);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} ManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/
