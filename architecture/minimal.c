/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal.c ****************/

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

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "faust/gui/CInterface.h"

#define max(a, b) ((a < b) ? b : a)
#define min(a, b) ((a < b) ? a : b)

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

#define BUFFER_SIZE 64
#define SAMPLE_RATE 44100

// Minimal UI management
static void printHGroup(void* ui_interface, const char* label)
{
    printf("HGroup [label %s]\n", label);
}

static void printVGroup(void* ui_interface, const char* label)
{
    printf("VGroup [label %s]\n", label);
}

static void printOpenTabBox(void* ui_interface, const char* label)
{
    printf("OpenTabBox [label %s]\n", label);
}

static void printCloseBox(void* ui_interface)
{
    printf("CloseBox\n");
}

static void printDeclare(void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{
    printf("Declare [key %s value %s]\n", key, value);
}

static void printVerticalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                         FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("VerticalSlider [label %s init: %f min: %f, max: %f step: %f]\n", label, init, min, max,
           step);
}

static void printHorizontalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                           FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("HorizontalSlider [label %s init: %f min: %f max: %f step: %f]\n", label, init, min, max,
           step);
}

static void printNumEntry(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                   FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("NumEntry [label %s init: %f min: %f max: %f step: %f]\n", label, init, min, max, step);
}

static void printButton(void* ui_interface, const char* label, FAUSTFLOAT* zone)
{
    printf("Button [label %s]\n", label);
}

static void printCheckButton(void* ui_interface, const char* label, FAUSTFLOAT* zone)
{
    printf("CheckButton [label %s]\n", label);
}

static void printHorizontalBargraph(void* ui_interface, const char* label, FAUSTFLOAT* zone,
                                   FAUSTFLOAT min, FAUSTFLOAT max)
{
    printf("HorizontalBargraph [label %s, min: %f, max: %f]\n", label, min, max);
}

static void printVerticalBargraph(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min,
                                 FAUSTFLOAT max)
{
    printf("VerticalBargraph [label %s, min: %f, max: %f]\n", label, min, max);
}

// Minimal management using zone

// Keep a control and lik to the next one
typedef struct ControlZone {
    const char* fLabel;
    FAUSTFLOAT* fZone;
    FAUSTFLOAT fInit;
    FAUSTFLOAT fMin;
    FAUSTFLOAT fMax;
    FAUSTFLOAT fStep;
    struct ControlZone* fNext;
} ControlZone;

static ControlZone* newControl(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                               FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    ControlZone* ctrl = (ControlZone*)calloc(1, sizeof(ControlZone));
    ctrl->fLabel = label;
    ctrl->fZone = zone;
    ctrl->fInit = init;
    ctrl->fMin = min;
    ctrl->fMax = max;
    ctrl->fStep = step;
    ctrl->fNext = NULL;
    return ctrl;
}

static void initControl(ControlZone* ctrl)
{
    ctrl->fLabel = NULL;
    ctrl->fZone = NULL;
    ctrl->fInit = 0;
    ctrl->fMin = 0;
    ctrl->fMax = 0;
    ctrl->fStep = 0;
    ctrl->fNext = NULL;
}

static void printControl(ControlZone* ctrl)
{
    if (ctrl != NULL) {
        if (ctrl->fLabel != NULL) printf("Label %s ", ctrl->fLabel);
        if (ctrl->fZone != NULL) printf("Zone %p ", ctrl->fZone);
        printf("Init %f ", ctrl->fInit);
        printf("Min %f ", ctrl->fMin);
        printf("Max %f ", ctrl->fMax);
        printf("Step %f \n", ctrl->fStep);
    }
}

static void printControls(ControlZone* ctrl)
{
    while (ctrl != NULL) {
        printControl(ctrl);
        ctrl = ctrl->fNext;
    }
}

static void freeControls(ControlZone* ctrl)
{
    while (ctrl != NULL) {
        ControlZone* tmp = ctrl;
        ctrl = ctrl->fNext;
        free(tmp);
    }
}

static void setParamValue(ControlZone* ctrl, const char* label, FAUSTFLOAT value)
{
    while (ctrl != NULL) {
        if (ctrl->fLabel && strcmp(ctrl->fLabel, label) == 0) {
            *ctrl->fZone = value;
            return;
        }
        ctrl = ctrl->fNext;
    }
}

static FAUSTFLOAT getParamValue(ControlZone* ctrl, const char* label)
{
    while (ctrl != NULL) {
        if (ctrl->fLabel && strcmp(ctrl->fLabel, label) == 0) {
            return *ctrl->fZone;
        }
        ctrl = ctrl->fNext;
    }
    return 0;
}

static void ignoreHGroup(void* ui_interface, const char* label)
{}

static void ignoreVGroup(void* ui_interface, const char* label)
{}

static void ignoreOpenTabBox(void* ui_interface, const char* label)
{}

static void ignoreCloseBox(void* ui_interface)
{}

static void ignoreDeclare(void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{}

static void addVerticalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                              FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, init, min, max, step);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addHorizontalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                                FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, init, min, max, step);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addNumEntry(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                        FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, init, min, max, step);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addButton(void* ui_interface, const char* label, FAUSTFLOAT* zone)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, 0, 0, 1, 1);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addCheckButton(void* ui_interface, const char* label, FAUSTFLOAT* zone)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, 0, 0, 1, 1);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addHorizontalBargraph(void* ui_interface, const char* label, FAUSTFLOAT* zone,
                                 FAUSTFLOAT min, FAUSTFLOAT max)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, 0, min, max, 0);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

static void addVerticalBargraph(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min,
                                FAUSTFLOAT max)
{
    ControlZone* ctrl_list = (ControlZone*)ui_interface;
    ControlZone* ctrl = newControl(label, zone, 0, min, max, 0);
    ctrl->fNext = ctrl_list->fNext;
    ctrl_list->fNext = ctrl;
}

int main(int argc, char* argv[])
{
    mydsp* dsp = newmydsp();

    printf("DSP inputs: %d\n", getNumInputsmydsp(dsp));
    printf("DSP outputs: %d\n", getNumOutputsmydsp(dsp));

    // Init with audio driver SR
    initmydsp(dsp, SAMPLE_RATE);

    // Add controls print methods
    UIGlue ui_glue;
    ui_glue.openHorizontalBox     = printHGroup;
    ui_glue.openVerticalBox       = printVGroup;
    ui_glue.openTabBox            = printOpenTabBox;
    ui_glue.closeBox              = printCloseBox;
    ui_glue.addButton             = printButton;
    ui_glue.addCheckButton        = printCheckButton;
    ui_glue.addVerticalSlider     = printVerticalSlider;
    ui_glue.addHorizontalSlider   = printHorizontalSlider;
    ui_glue.addNumEntry           = printNumEntry;
    ui_glue.addHorizontalBargraph = printHorizontalBargraph;
    ui_glue.addVerticalBargraph   = printVerticalBargraph;
    ui_glue.declare               = printDeclare;

    // Print all controls
    buildUserInterfacemydsp(dsp, &ui_glue);
    
    // Add controls handling methods
    UIGlue ctrl_glue;
    ControlZone* ctrl_list = newControl(NULL, NULL, 0, 0, 0, 0);
    initControl(ctrl_list);
    
    ctrl_glue.uiInterface           = ctrl_list;
    ctrl_glue.openHorizontalBox     = ignoreHGroup;
    ctrl_glue.openVerticalBox       = ignoreVGroup;
    ctrl_glue.openTabBox            = ignoreOpenTabBox;
    ctrl_glue.closeBox              = ignoreCloseBox;
    ctrl_glue.addButton             = addButton;
    ctrl_glue.addCheckButton        = addCheckButton;
    ctrl_glue.addVerticalSlider     = addVerticalSlider;
    ctrl_glue.addHorizontalSlider   = addHorizontalSlider;
    ctrl_glue.addNumEntry           = addNumEntry;
    ctrl_glue.addHorizontalBargraph = addHorizontalBargraph;
    ctrl_glue.addVerticalBargraph   = addVerticalBargraph;
    ctrl_glue.declare               = ignoreDeclare;
    
    // Get all controls
    buildUserInterfacemydsp(dsp, &ctrl_glue);
    
    // Print all labels
    printControls(ctrl_list);
    
    // Set a control using its label
    setParamValue(ctrl_list, "Foo", 0.0);
    setParamValue(ctrl_list, "Bar", 20);

    // Compute one buffer
    FAUSTFLOAT* inputs[getNumInputsmydsp(dsp)];
    FAUSTFLOAT* outputs[getNumOutputsmydsp(dsp)];
    for (int chan = 0; chan < getNumInputsmydsp(dsp); ++chan) {
        inputs[chan] = (FAUSTFLOAT*)malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    for (int chan = 0; chan < getNumOutputsmydsp(dsp); ++chan) {
        outputs[chan] = (FAUSTFLOAT*)malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    computemydsp(dsp, BUFFER_SIZE, inputs, outputs);

    // Print output buffers
    for (int frame = 0; frame < BUFFER_SIZE; ++frame) {
        for (int chan = 0; chan < getNumOutputsmydsp(dsp); ++chan) {
            printf("Audio output chan: %d sample: %f\n", chan, outputs[chan][frame]);
        }
    }
    
    // Deallocation
    freeControls(ctrl_list);

    for (int chan = 0; chan < getNumInputsmydsp(dsp); ++chan) {
        free(inputs[chan]);
    }
    for (int chan = 0; chan < getNumOutputsmydsp(dsp); ++chan) {
        free(outputs[chan]);
    }
    deletemydsp(dsp);
}

/******************** END minimal.c ****************/
