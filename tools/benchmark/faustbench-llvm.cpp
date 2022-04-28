
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
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

#include <iostream>

#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"

using namespace std;

template <typename REAL>
static void bench(dsp_optimizer_real<REAL> optimizer, const string& in_filename, bool is_trace)
{
    tuple<double, double, TOption> res = optimizer.findOptimizedParameters();
    if (is_trace) cout << "Best value for '" << in_filename << "' is : " << get<0>(res) << " MBytes/sec (DSP CPU % : " << (get<1>(res) * 100) << " at 44100 Hz) with ";
    for (size_t i = 0; i < get<2>(res).size(); i++) {
        cout << get<2>(res)[i] << " ";
    }
    cout << endl;
}

template <typename REAL>
static void bench_single(const string& in_filename, dsp* DSP, int buffer_size, int run, bool is_control, bool is_trace)
{
    cout << "DSP inputs = " << DSP->getNumInputs() << " outputs = " << DSP->getNumOutputs() << endl;
    
    measure_dsp_real<REAL> mes(DSP, buffer_size, 5., true, is_control);  // Buffer_size and duration in sec of measure
    for (int i = 0; i < run; i++) {
        mes.measure();
        if (is_trace) cout << in_filename << " : " << mes.getStats() << " MBytes/sec (DSP CPU % : " << (mes.getCPULoad() * 100) << " at 44100 Hz)" << endl;
        FAUSTBENCH_LOG<REAL>(mes.getStats());
    }
}

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustbench-llvm [-notrace] [-control] [-generic] [-single] [-run <num>] [-bs <frames>] [-opt <level (0..4|-1)>] [-us <factor>] [-ds <factor>] [-filter <filter(0..4)>] [additional Faust options (-vec -vs 8...)] foo.dsp" << endl;
        cout << "Use '-notrace' to only generate the best compilation parameters\n";
        cout << "Use '-control' to update all controllers with random values at each cycle\n";
        cout << "Use '-generic' to compile for a generic processor, otherwise the native CPU will be used\n";
        cout << "Use '-single' to execute only one test (scalar by default)\n";
        cout << "Use '-run <num>' to execute each test <num> times\n";
        cout << "Use '-bs <frames>' to set the buffer-size in frames\n";
        cout << "Use '-opt <level (0..4|-1)>' to pass an optimisation level to LLVM, between 0 and 4 (-1 means 'maximal level' if range changes in the future)\n";
        cout << "Use '-us <factor>' to upsample the DSP by a factor\n";
        cout << "Use '-ds <factor>' to downsample the DSP by a factor\n";
        cout << "Use '-filter <filter>' for upsampling or downsampling [0..4]\n";
        return 0;
    }
    
    bool is_double = isopt(argv, "-double");
    bool is_trace = !isopt(argv, "-notrace");
    bool is_control = isopt(argv, "-control");
    bool is_single = isopt(argv, "-single");
    bool is_generic = isopt(argv, "-generic");
    int run = lopt(argv, "-run", 1);
    int buffer_size = lopt(argv, "-bs", 512);
    int opt = lopt(argv, "-opt", -1);
    int ds = lopt(argv, "-ds", 0);
    int us = lopt(argv, "-us", 0);
    int filter = lopt(argv, "-filter", 0);
    
    if (is_trace) cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    // Possibly activate 'generic' generation mode
    string target;
    if (is_generic) {
        string triple, cpu;
        splitTarget(getDSPMachineTarget(), triple, cpu);
        target = triple + ":generic";
        if (is_trace) cout << "Using 'generic' mode\n";
    } else {
        if (is_trace) cout << "Using 'native' mode\n";
    }
    
    int argc1 = 0;
    const char* argv1[64];
    
    if (is_trace) cout << "Running with 'compute' called with " << buffer_size << " samples" << endl;
    
    if (is_trace) cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-single"
            || string(argv[i]) == "-generic"
            || string(argv[i]) == "-control") {
            continue;
        } else if (string(argv[i]) == "-run"
                   || string(argv[i]) == "-opt"
                   || string(argv[i]) == "-bs"
                   || string(argv[i]) == "-ds"
                   || string(argv[i]) == "-us"
                   || string(argv[i]) == "-filter") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
        if (is_trace) cout << argv[i] << " ";
    }
    if (is_trace) cout << endl;
    
    // Add library
    argv1[argc1++] = "-I";
    argv1[argc1++] = "/usr/local/share/faust";
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    //FAUSTBENCH_LOG<string>("faustbench LLVM");
    
    string in_filename = argv[argc-1];
    
    try {
        if (is_single) {
            string error_msg;
            llvm_dsp_factory* factory = createDSPFactoryFromFile(in_filename, argc1, argv1, target, error_msg, opt);
            if (!factory) {
                cerr << error_msg;
                exit(EXIT_FAILURE);
            }
            
            dsp* DSP = factory->createDSPInstance();
            if (!DSP) {
                cerr << "Cannot create instance\n";
                exit(EXIT_FAILURE);
            }
            
            if (is_double) {
                bench_single<double>(in_filename, DSP, buffer_size, run, is_control, is_trace);
            } else {
                bench_single<float>(in_filename, DSP, buffer_size, run, is_control, is_trace);
            }
            
            deleteDSPFactory(factory);
            
        } else {
            if (is_double) {
                bench(dsp_optimizer_real<double>(in_filename,
                                                argc1, argv1,
                                                target, buffer_size,
                                                run, -1,
                                                is_trace,
                                                is_control,
                                                ds, us, filter),
                                                in_filename,
                                                is_trace);
            } else {
                bench(dsp_optimizer_real<float>(in_filename,
                                               argc1, argv1,
                                               target, buffer_size,
                                               run, -1,
                                               is_trace,
                                               is_control,
                                               ds, us, filter),
                                               in_filename,
                                               is_trace);
            }
        }
    } catch (...) {
        cerr << "libfaust error...\n";
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
