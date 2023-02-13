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

#include <stdio.h>
#include <string.h>

//#define FAUSTFLOAT double

#include "faust/dsp/interpreter-dsp-c.h"
#include "faust/gui/PrintCUI.h"

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

int main(int argc, const char** argv)
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help")) {
        printf("interp-test-c\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Libfaust version : %s\n", getCLibFaustVersion());
    
    char error_msg[4096];
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
    
    interpreter_dsp_factory* factory = createCInterpreterDSPFactoryFromString("score", code, 0, NULL, error_msg);
    if (!factory) {
        printf("Cannot create factory : %s\n", error_msg);
        exit(EXIT_FAILURE);
    } else {
        interpreter_dsp* dsp = createCInterpreterDSPInstance(factory);
        if (!dsp) {
            printf("Cannot create DSP\n");
            exit(EXIT_FAILURE);
        } else {
            printf("getNumInputs : %d\n", getNumInputsCInterpreterDSPInstance(dsp));
            printf("getNumOutputs : %d\n", getNumOutputsCInterpreterDSPInstance(dsp));
            
            // Defined in PrintCUI.h
            metadataCInterpreterDSPInstance(dsp, &mglue);
            
            buildUserInterfaceCInterpreterDSPInstance(dsp, &uglue);
            
            // Cleanup
            deleteCInterpreterDSPInstance(dsp);
            deleteCInterpreterDSPFactory(factory);
        }
    }

    return 0;
}

