/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 Jean Pierre Cimalando, GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#define FAUST_UIMACROS 1

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

/*
faust -uim -a minimal-static.cpp noise.dsp -o noise.cpp && c++ noise.cpp -o noise && ./noise
faust -uim -a minimal-static.cpp clarinetMIDI.dsp -o clarinetMIDI.cpp && c++ clarinetMIDI.cpp -o clarinetMIDI && ./clarinetMIDI
faust -uim -a minimal-static.cpp vumeter.dsp -o vumeter.cpp && c++ vumeter.cpp -o vumeter && ./vumeter
*/

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

/*
 Example: generate UI information into static metadata
 */
struct ControlDescription {
    const char *type;
    const char *ident;
    const char *name;
    const char *var;
    float def;
    float min;
    float max;
    float step;
};

static const ControlDescription actives[] = {
#define ACTIVE_ELEMENT(type, ident, name, var, def, min, max, step) \
{ #type, #ident, name, #var, def, min, max, step },
    FAUST_LIST_ACTIVES(ACTIVE_ELEMENT)
};
static_assert(FAUST_ACTIVES == sizeof(actives) / sizeof(actives[0]), "incorrect size of result");

static const ControlDescription passives[] = {
#define PASSIVE_ELEMENT(type, ident, name, var, def, min, max, step) \
{ #type, #ident, name, #var, def, min, max, step },
    FAUST_LIST_PASSIVES(PASSIVE_ELEMENT)
};
static_assert(FAUST_PASSIVES == sizeof(passives) / sizeof(passives[0]), "incorrect size of result");

/*
 Example: generate UI actives into an enum
 */
enum {
#define ACTIVE_ENUM_MEMBER(type, ident, name, var, def, min, max, step) \
kActive_##ident,
    FAUST_LIST_ACTIVES(ACTIVE_ENUM_MEMBER)
    //
    kNumActives,
};
static_assert(FAUST_ACTIVES == kNumActives, "incorrect size of result");

int main(int argc, char* argv[])
{
    printf("=============================\n"
           "DSP Static Information (-uim)\n"
           "=============================\n"
           "\n");
    
    printf("Number of actives: %d\n", FAUST_ACTIVES);
    putchar('\n');
    
    for (int i = 0; i < FAUST_ACTIVES; ++i) {
        printf("--- active number %d\n\n", i + 1);
        
        printf("Parameter name:             %s\n", actives[i].name);
        printf("Kind of control:            %s\n", actives[i].type);
        printf("Unique symbol:              %s\n", actives[i].ident);
        printf("Name of instance variable:  %s\n", actives[i].var);
        putchar('\n');
        printf("Value range:                %g to %g\n", actives[i].min, actives[i].max);
        printf("Default value:              %g\n", actives[i].def);
        printf("Step:                       %g\n", actives[i].step);
        putchar('\n');
    }
    
    printf("Number of passives: %d\n", FAUST_PASSIVES);
    putchar('\n');
    
    for (int i = 0; i < FAUST_PASSIVES; ++i) {
        printf("--- passive number %d\n\n", i + 1);
        
        printf("Parameter name:             %s\n", passives[i].name);
        printf("Kind of control:            %s\n", passives[i].type);
        printf("Unique symbol:              %s\n", passives[i].ident);
        printf("Name of instance variable:  %s\n", passives[i].var);
        putchar('\n');
        printf("Value range:                %g to %g\n", passives[i].min, passives[i].max);
        printf("Default value:              %g\n", passives[i].def);
        printf("Step:                       %g\n", passives[i].step);
        putchar('\n');
    }
    
    return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

