/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#include <stdio.h>
#include <string.h>

#include "faust/dsp/llvm-c-dsp.h"

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

static void meta_declare(void *iface __unused, const char *key, const char *val)
{
    printf("meta_declare %s, %s\n", key, val);
}

static void ui_open_tab_box(void* iface __unused, const char* label)
{
    printf("ui_open_tab_box %s \n", label);
}

static void ui_open_horizontal_box(void* iface __unused, const char* label)
{
    printf("ui_open_horizontal_box %s \n", label);
}

static void ui_open_vertical_box(void* iface __unused, const char* label)
{
    printf("ui_open_vertical_box %s \n", label);
}

static void ui_close_box(void* iface __unused)
{
    printf("ui_close_box\n");
}

static void ui_add_button(void* iface __unused, const char* label, FAUSTFLOAT* zone)
{
     printf("ui_add_button %s \n", label);
}

static void ui_add_check_button(void* iface __unused, const char* label, FAUSTFLOAT* zone)
{
    printf("ui_add_check_button %s \n", label);
}

static void ui_add_vertical_slider(void* iface __unused, const char* label,
                                   FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                   FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_vertical_slider %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_horizontal_slider(void *iface __unused, const char *label,
                                     FAUSTFLOAT *zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                     FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_vertical_slider %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_num_entry(void* iface __unused, const char* label,
                             FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT step)
{
    printf("ui_add_num_entry %s %f %f %f %f\n", label, init, min, max, step);
}

static void ui_add_horizontal_bargraph(void* iface __unused, const char* label,
                                       FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    printf("ui_add_horizontal_bargraph %s %f %f\n", label, min, max);
}

static void ui_add_vertical_bargraph(void* iface __unused, const char* label,
                                     FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    printf("ui_add_horizontal_bargraph %s %f %f\n", label, min, max);
}

static void ui_add_sound_file(void* iface __unused, const char* label __unused,
                              const char* filename __unused, struct Soundfile** sf_zone __unused)
{
}

static void ui_declare(void *iface, FAUSTFLOAT *zone __unused,
                       const char *key, const char *val)
{
    printf("ui_declare %s, %s\n", key, val);
}

int main(int argc, const char** argv)
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help")) {
        printf("llvm-test-c\n");
        exit(EXIT_FAILURE);
    }
    
    int argc1 = 0;
    const char* argv1[2];
    argv1[argc1++] = "-vec";
    argv1[argc1] = 0;
    
    char err[4096];
    const char* code =
        "import(\"stdfaust.lib\");\n"
        "\n"
        "f0 = hslider(\"[foo:bar]f0\", 110, 110, 880, 1);\n"
        "\n"
        "n = 2;\n"
        "\n"
        "inst = par(i, n, os.oscs(f0 * (n+i) / n)) :> /(n);\n"
        "\n"
        "process = inst, inst;\n";
    
    llvm_dsp_factory* factory = createCDSPFactoryFromString("score", code, argc1, argv1, "", err, -1);
    if (!factory) {
        printf("Cannot create factory : %s\n", err);
        exit(EXIT_FAILURE);
    } else {
        llvm_dsp* dsp = createCDSPInstance(factory);
        if (!dsp) {
            printf("Cannot create DSP\n");
            exit(EXIT_FAILURE);
        } else {
            printf("getNumInputs : %d\n", getNumInputsCDSPInstance(dsp));
            printf("getNumOutputs : %d\n", getNumOutputsCDSPInstance(dsp));
            
            MetaGlue mglue = {
                .metaInterface = NULL,
                .declare = meta_declare
            };
            
            metadataCDSPInstance(dsp, &mglue);
            
            UIGlue uglue = {
                .uiInterface = NULL,
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
            
            buildUserInterfaceCDSPInstance(dsp, &uglue);
            
            // Cleanup
            deleteCDSPInstance(dsp);
            deleteCDSPFactory(factory);
        }
    }
}
