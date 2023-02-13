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

#include <libgen.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"

using namespace std;

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

static string replaceChar(string str, char src, char dst)
{
    replace(str.begin(), str.end(), src, dst);
    return str;
}

template <typename REAL>
static vector<string> bench(dsp_optimizer_real<REAL> optimizer, const string& name)
{
    tuple<double, double, double, TOption> res = optimizer.findOptimizedParameters();
    return get<3>(res);
}

int main(int argc, char* argv[])
{
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "dynamic-faust [-target xxx] [-opt native|generic] [-o foo.ll|foo.bc|foo.mc|foo.o] [additional Faust options (-vec -vs 8...)] foo.dsp" << endl;
        cout << "Use '-target xxx' to cross-compile the code for a different architecture (like 'x86_64-apple-darwin15.6.0:haswell')\n";
        cout << "Use '-opt native' to activate the best compilation options for the native CPU\n";
        cout << "Use '-opt generic' to activate the best compilation options for a generic CPU\n";
        cout << "Use '-o foo.ll' to generate an LLVM IR textual file\n";
        cout << "Use '-o foo.bc' to generate an LLVM bitcode file\n";
        cout << "Use '-o foo.mc' to generate an LLVM machine code file\n";
        cout << "Use '-o foo.o' to generate an object code file\n";
        return 0;
    }
    
    string target = lopts(argv, "-target", getDSPMachineTarget().c_str());
    bool is_opt = isopt(argv, "-opt");
    string opt = lopts(argv, "-opt", "generic");
    bool is_double = isopt(argv, "-double");
    
    string in_filename, out_filename, error_msg;
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if ((string(argv[i]) == "-target") || string(argv[i]) == "-opt"){
            i++;
            continue;
        } else if (endWith(string(argv[i]), ".dsp")) {
            in_filename = argv[i];
            continue;
        } else if (string(argv[i]) == "-o") {
            out_filename = argv[i+1];
            i++;
            continue;
        } else if (string(argv[i]) == "-a") {
            cerr << "ERROR : -a parameter cannot be used!\n";
            exit(EXIT_FAILURE);
        }
        argv1[argc1++] = argv[i];
        cout << argv[i] << " ";
    }
    cout << endl;
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    if (out_filename == "") {
        cerr << "ERROR : no output file given...\n";
        exit(EXIT_FAILURE);
    }
    
    string opt_target;
    vector<string> optimal_options;
    
    string triple, cpu;
    splitTarget(getDSPMachineTarget(), triple, cpu);
    cout << "Host : " << triple << ":" << cpu << "\n";
    
    if (is_opt) {
        
        if (opt == "generic") {
            opt_target = triple + ":generic";
            cout << "Using 'generic' mode\n";
        } else {
            cout << "Using 'native' mode\n";
        }
        
        cout << "Looking for optimal parameters... \n";
        int buffer_size = 512;
        try {
            if (is_double) {
                optimal_options = bench(dsp_optimizer_real<double>(in_filename, argc1, argv1, opt_target, buffer_size, 1, -1, false), in_filename);
            } else {
                optimal_options = bench(dsp_optimizer_real<float>(in_filename, argc1, argv1, opt_target, buffer_size, 1, -1, false), in_filename);
            }
        } catch (...) {
            cerr << "libfaust error...\n";
            exit(EXIT_FAILURE);
        }
        
        cout << "Compiled with optimal options : ";
        for (size_t i = 0; i < optimal_options.size(); i++) {
            argv1[argc1++] = optimal_options[i].c_str();
            cout << optimal_options[i] << " ";
        }
        cout << endl;
        
        // Compilation target is the opt_target
        target = opt_target;
    } else {
        splitTarget(target, triple, cpu);
        target = triple + ":" + replaceChar(cpu, '_', '-');
    }
    
    // Create factory
    cout << "Compiled with target : " << target << endl;
    llvm_dsp_factory* factory = createDSPFactoryFromFile(in_filename, argc1, argv1, target, error_msg, -1);
    if (!factory) {
        cerr << error_msg;
        exit(EXIT_FAILURE);
    }
    
    // Save it
    if (endWith(out_filename, ".ll")) {
        if (!writeDSPFactoryToIRFile(factory, out_filename)) {
            cerr << "ERROR : writeDSPFactoryToIRFile...\n";
            exit(EXIT_FAILURE);
        }
    } else if (endWith(out_filename, ".bc")) {
        if (!writeDSPFactoryToBitcodeFile(factory, out_filename)) {
            cerr << "ERROR : writeDSPFactoryToBitcodeFile...\n";
            exit(EXIT_FAILURE);
        }
    } else if (endWith(out_filename, ".mc")) {
        if (!writeDSPFactoryToMachineFile(factory, out_filename, "")) {
            cerr << "ERROR : writeDSPFactoryToMachineFile...\n";
            exit(EXIT_FAILURE);
        }
    } else if (endWith(out_filename, ".o")) {
        if (!writeDSPFactoryToObjectcodeFile(factory, out_filename, "")) {
            cerr << "ERROR : writeDSPFactoryToObjectcodeFile...\n";
            exit(EXIT_FAILURE);
        }
    } else  {
        cerr << "ERROR : unrecognized file extension " << out_filename << "\n";
        exit(EXIT_FAILURE);
    }
    
    deleteDSPFactory(factory);
    return 0;
}

