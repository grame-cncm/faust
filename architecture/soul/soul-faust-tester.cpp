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

#include <iostream>
#include <string>

#include "faust/dsp/soulpatch-dsp.h"
#include "faust/dsp/dsp-optimizer.h"
#include "faust/misc.h"

#define FAUST_FILE        "faust.soul"
#define FAUST_PATCH_FILE  "faust.soulpatch"

using namespace std;

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

static void measureDSP(const string& filename, dsp* DSP)
{
    measure_dsp mes(DSP, 512, 5.);  // Buffer_size and duration in sec of measure
    mes.measure();
    cout << filename << " : " << mes.getStats() << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << endl;
    FAUSTBENCH_LOG<double>(mes.getStats());
}

static void testFaust(const string& filename, int argc1, const char* argv1[])
{
    // Faust compilation and test
    string error_msg;
    dsp_factory* factory = createDSPFactoryFromFile(filename, argc1, argv1, "", error_msg, -1);
    if (!factory) {
        cerr << "ERROR : file '" << filename << "' cannot be opened or TOTO compiled with " << error_msg << "\n";
        exit(-1);
    }
    
    measureDSP(filename, factory->createDSPInstance());
}

static void testSOULPatch(const string& filename, int argc1, const char* argv1[])
{
    // SOUL compilation and test
    string error_msg;
    dsp_factory* factory = createSOULDSPFactoryFromFile(filename, argc1, argv1, error_msg);
    if (!factory) {
        cerr << "ERROR : file '" << filename << "' cannot be opened or compiled with " << error_msg << "\n";;
        exit(-1);
    }
    
    measureDSP(filename, factory->createDSPInstance());
}

static void testSOUL(const string& filename, int argc1, const char* argv1[])
{
    // Faust => SOUL compilation
    faust_soul_parser parser;
    if (!parser.generateSOULFile(filename, FAUST_FILE)) {
        cerr << "ERROR : file '" << filename << "' cannot be opened or compiled! \n";
        exit(-1);
    }
    
    // Generate "soulpatch" file
    parser.createSOULPatch(FAUST_PATCH_FILE, FAUST_FILE);
    
    testSOULPatch(FAUST_PATCH_FILE, argc1, argv1);
}

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "soul-faust-tester foo.dsp|foo.soulpatch" << endl;
        exit(-1);
    }
    
    char* filename = argv[argc-1];
   
    int argc1 = 0;
    const char* argv1[64];
    for (int i = 1; i < argc-1; i++) {
        argv1[argc1++] = argv[i];
    }
    
    if (endWith(filename, "soulpatch")) {
        testSOULPatch(filename, argc1, argv1);
    } else {
        testFaust(filename, argc1, argv1);
        testSOUL(filename, argc1, argv1);
    }
    
    return 0;
}
