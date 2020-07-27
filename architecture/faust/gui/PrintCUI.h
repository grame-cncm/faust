/************************** BEGIN PrintCUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_PRINTCUI_H
#define FAUST_PRINTCUI_H

#include <stdio.h>
#include "faust/gui/CInterface.h"

/*******************************************************************************
 * PrintCUI : Faust User Interface
 * This class print arguments given to calls to UI methods and shows how
 * a struct can be used inside functions.
 ******************************************************************************/

// Example of UI with a state
typedef struct PRINTCUI {
    int fVar1;
    float fVar2;
    // Some structure to keep [zone, init, min, max, step] parameters...
} PRINTCUI;

static void ui_open_tab_box(void* iface, const char* label)
{
    printf("ui_open_tab_box %s \n", label);
}

static void ui_open_horizontal_box(void* iface, const char* label)
{
    printf("ui_open_horizontal_box %s \n", label);
}

static void ui_open_vertical_box(void* iface, const char* label)
{
    // Using the 'iface' state
    PRINTCUI* cui = (PRINTCUI*)iface;
    printf("ui_open_horizontal_box %s %d %f\n", label, cui->fVar1, cui->fVar2);
}

static void ui_close_box(void* iface)
{
    printf("ui_close_box\n");
}

static void ui_add_button(void* iface, const char* label, FAUSTFLOAT* zone)
{
    printf("ui_add_button %s \n", label);
}

static void ui_add_check_button(void* iface, const char* label, FAUSTFLOAT* zone)
{
    printf("ui_add_check_button %s \n", label);
}

static void ui_add_vertical_slider(void* iface, const char* label,
                                   FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                   FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_vertical_slider %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_horizontal_slider(void *iface, const char *label,
                                     FAUSTFLOAT *zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                     FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_vertical_slider %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_num_entry(void* iface, const char* label,
                             FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_num_entry %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_horizontal_bargraph(void* iface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    printf("ui_add_horizontal_bargraph %s %f %f\n", label, min, max);
}

static void ui_add_vertical_bargraph(void* iface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    printf("ui_add_horizontal_bargraph %s %f %f\n", label, min, max);
}

static void ui_add_sound_file(void* iface, const char* label, const char* filename, struct Soundfile** sf_zone)
{
    printf("ui_add_sound_file %s %s\n", label, filename);
}

static void ui_declare(void* iface, FAUSTFLOAT *zone, const char *key, const char *val)
{
    printf("ui_declare %s, %s\n", key, val);
}

// Example of a structure to be given as 'iface' in functions
PRINTCUI cui = {
    .fVar1 = 1,
    .fVar2 = 0.5
};

UIGlue uglue = {
    .uiInterface = &cui,
    .openTabBox = ui_open_tab_box,
    .openHorizontalBox = ui_open_horizontal_box,
    .openVerticalBox = ui_open_vertical_box,
    .closeBox = ui_close_box,
    .addButton = ui_add_button,
    .addCheckButton = ui_add_check_button,
    .addVerticalSlider = ui_add_vertical_slider,
    .addHorizontalSlider = ui_add_horizontal_slider,
    .addNumEntry = ui_add_num_entry,
    .addHorizontalBargraph = ui_add_horizontal_bargraph,
    .addVerticalBargraph = ui_add_vertical_bargraph,
    .addSoundfile = ui_add_sound_file,
    .declare = ui_declare
};

static void meta_declare(void* iface, const char *key, const char *val)
{
    printf("meta_declare %s, %s\n", key, val);
}

MetaGlue mglue = {
    .metaInterface = NULL,
    .declare = meta_declare
};

#endif // FAUST_PRINTCUI_H
/**************************  END  PrintCUI.h **************************/
