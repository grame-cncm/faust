
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"

using namespace std;

template <typename T>
static void bench(dsp_optimizer<T> optimizer, const string& name, bool trace)
{
    pair<double, vector<std::string> > res = optimizer.findOptimizedParameters();
    if (trace) cout << "Best value is for '" << name << "' is : " << res.first << " with ";
    for (int i = 0; i < res.second.size(); i++) {
        cout << res.second[i] << " ";
    }
    cout << endl;
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
        cout << "faustbench-llvm [-notrace] [-generic] [-single] [-run <num>] [additional Faust options (-vec -vs 8...)] foo.dsp" << endl;
        cout << "Use '-notrace' to only generate the best compilation parameters\n";
        cout << "Use '-generic' to compile for a generic processor, otherwise the native CPU will be used\n";
        cout << "Use '-single' to execute only scalar test\n";
        cout << "Use '-run <num>' to execute each test <num> times\n";
        return 0;
    }
    
    bool is_double = isopt(argv, "-double");
    bool is_trace = !isopt(argv, "-notrace");
    bool is_single = isopt(argv, "-single");
    bool is_generic = isopt(argv, "-generic");
    
    int run = lopt(argv, "-run", 1);
    
    int buffer_size = 1024;
    
    if (is_trace) cout << "Libfaust version : " << getCLibFaustVersion () << std::endl;
    
    // Possiby activate 'generic' generation mode
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
    
    if (is_trace) cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-single" || string(argv[i]) == "-generic") {
            continue;
        } else if (string(argv[i]) == "-run") {
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
 
    argv1[argc1] = 0;  // NULL terminated argv
    
    //FAUSTBENCH_LOG<string>("faustbench LLVM");
   
    try {
        if (is_single) {
            string error_msg;
            
            dsp_factory* factory = createDSPFactoryFromFile(argv[argc-1], argc1, argv1, "", error_msg, -1);
            if (!factory) {
                cerr << "Cannot create factory : " << error_msg;
                exit(EXIT_FAILURE);
            }
            
            dsp* DSP = factory->createDSPInstance();
            if (!DSP) {
                cerr << "Cannot create instance " << endl;
                exit(EXIT_FAILURE);
            }
            
            measure_dsp mes(DSP, 512, 5.);  // Buffer_size and duration in sec of  measure
            for (int i = 0; i < run; i++) {
                mes.measure();
                if (is_trace) cout << argv[argc-1] << " : " << mes.getStats() << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << endl;
                FAUSTBENCH_LOG<double>(mes.getStats());
            }

        } else {
            if (is_double) {
                bench(dsp_optimizer<double>(argv[argc-1], argc1, argv1, target, buffer_size, run, -1, is_trace), argv[argc-1], is_trace);
            } else {
                bench(dsp_optimizer<float>(argv[argc-1], argc1, argv1, target, buffer_size, run, -1, is_trace), argv[argc-1], is_trace);
            }
        }
    } catch (...) {}
    
  	return 0;
}
