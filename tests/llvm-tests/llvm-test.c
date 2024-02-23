/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2024 GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/llvm-dsp-c.h"
#include "faust/dsp/libfaust-c.h"
#include "faust/gui/PrintCUI.h"

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
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
    
    char* target = getCDSPMachineTarget();
    printf("getDSPMachineTarget %s\n", target);
    freeCMemory(target);
    
    llvm_dsp_factory* factory = createCDSPFactoryFromString("score", code, argc1, argv1, "", error_msg, -1);
    if (!factory) {
        printf("Cannot create factory : %s\n", error_msg);
        exit(EXIT_FAILURE);
    } else {
        llvm_dsp* dsp = createCDSPInstance(factory);
        if (!dsp) {
            printf("Cannot create DSP\n");
            exit(EXIT_FAILURE);
        } else {
            printf("getNumInputs : %d\n", getNumInputsCDSPInstance(dsp));
            printf("getNumOutputs : %d\n", getNumOutputsCDSPInstance(dsp));
            
            // Defined in PrintCUI.h
            metadataCDSPInstance(dsp, &mglue);
            
            buildUserInterfaceCDSPInstance(dsp, &uglue);
            
            // Cleanup
            deleteCDSPInstance(dsp);
            deleteCDSPFactory(factory);
        }
    }
}
