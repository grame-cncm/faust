/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2022 GRAME, Centre National de Creation Musicale
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
#include <string>

#include "faust/dsp/cmajorpatch-dsp.h"
#include "cmajor-tools.h"
#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"
#include "faust/dsp/interpreter-dsp.h"

#define FAUST_FILE        "faust.cmajor"
#define FAUST_PATCH_FILE  "faust.cmajorpatch"

//#define INTERP

using namespace std;

static int buffer_size = 512;
static bool is_control = false;

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

static double measureDSP(const string& filename, dsp* DSP)
{
    // Buffer_size and duration in sec of measure, no trace and activated control 
    measure_dsp mes(DSP, buffer_size, 5., false, is_control);
    mes.measure();
    pair<double, double> res =  mes.getStats();
    cout << filename << " : " << res.first << " MBytes/sec (DSP CPU % : " << (mes.getCPULoad() * 100) << " at 44100 Hz)" << endl;
    FAUSTBENCH_LOG<double>(res.first);
    return res.first;
}

static double testFaust(const string& filename, int argc1, const char* argv1[])
{
    // Faust compilation and test
    string error_msg;
#ifdef INTERP
    dsp_factory* factory = createInterpreterDSPFactoryFromFile(filename, argc1, argv1, error_msg);
#else
    dsp_factory* factory = createDSPFactoryFromFile(filename, argc1, argv1, "", error_msg, -1);
#endif
    if (!factory) {
        cerr << "ERROR : file '" << filename << "' cannot be opened with " << error_msg << "\n";
        exit(-1);
    }
    double res = measureDSP(filename, factory->createDSPInstance());
#ifdef INTERP
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
#else
    deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
#endif
    return res;
}

static double testCmajorFile(const string& filename, int argc1, const char* argv1[])
{
    // Cmajor compilation and test
    string error_msg;
    cmajor_dsp_factory* factory = createCmajorDSPFactoryFromFile(filename, argc1, argv1, error_msg);
    if (!factory) {
        cerr << "ERROR : file '" << filename << "' : " << error_msg << "\n";
        exit(-1);
    }
    
    double res = measureDSP(filename, factory->createDSPInstance());
    delete factory;
    return res;
}

static double testCmajor(const string& filename, int argc1, const char* argv1[])
{
    // Faust => Cmajor compilation
    faust_cmajor_parser parser;
    if (!parser.generateCmajorFile(filename, FAUST_FILE, argc1, argv1)) {
        cerr << "ERROR : file '" << filename << "' cannot be opened or compiled! \n";
        exit(-1);
    }
    
    // Generate "cmajorpatch" file
    parser.createCmajorPatch(FAUST_FILE);
    return testCmajorFile(FAUST_FILE, argc1, argv1);
}

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "cmajor-faust-tester [-bs <frames>] [-control] [Faust options : any option (e.g. -vec -vs 8...)] foo.dsp|foo.cmajor" << endl;
        cout << "Use '-bs <frames>' to set the maximum buffer-size in frames\n";
        cout << "Use '-control' to update all controllers with random values at each cycle\n";
        exit(-1);
    }
    
    buffer_size = lopt(argv, "-bs", 512);
    is_control = isopt(argv, "-control");
    cout << "buffer_size = " << buffer_size << endl;
    
    char* filename = argv[argc-1];
    int argc1 = 0;
    const char* argv1[64];
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-control") {
            continue;
        } else if (string(argv[i]) == "-bs") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
    }
    
    if (endWith(filename, "cmajor")) {
        testCmajorFile(filename, argc1, argv1);
    } else {
        double r1 = testFaust(filename, argc1, argv1);
        double r2 = testCmajor(filename, argc1, argv1);
        cout << "Ratio : " << r1/r2 << endl;
    }
    
    return 0;
}
