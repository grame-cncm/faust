/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/misc.h"

using namespace std;

int main(int argc, char* argv[])
{
    char name[256];
    char filename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    
    bool is_llvm = isopt(argv, "-llvm");
    bool is_interp = isopt(argv, "-interp");
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
        cout << "dynamic-faust [-llvm/interp] [additional Faust options (-vec -vs 8...)] foo.dsp" << endl;
        cout << "Use '-llvm' to use LLVM backend\n";
        cout << "Use '-interp' to use Interpreter backend\n";
        exit(EXIT_FAILURE);
    }
    
    string error_msg;
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if ((string(argv[i]) == "-llvm")
            || (string(argv[i]) == "-interp")) {
            continue;
        }
        argv1[argc1++] = argv[i];
        cout << argv[i] << " ";
    }
    cout << endl;
    
    argv1[argc1] = 0;  // NULL terminated argv
    
    if (is_llvm) {
        cout << "Using LLVM backend" << endl;
        // argc : without the filename (last element);
        llvm_dsp_factory* factory = createDSPFactoryFromFile(argv[argc-1], argc1, argv1, "", error_msg, -1);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        // Write machine code file
        writeDSPFactoryToMachineFile(factory, string(argv[argc-1]) + ".mc", "");
        
        deleteDSPFactory(factory);
        
    } else {
        cout << "Using interpreter backend" << endl;
        // argc : without the filename (last element);
        interpreter_dsp_factory* factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        // Write byte code file
        writeInterpreterDSPFactoryToBitcodeFile(factory, string(argv[argc-1]) + ".fbc");
        
        deleteInterpreterDSPFactory(factory);
    }
    
    return 0;
}

