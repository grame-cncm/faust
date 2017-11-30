/************************************************************************
    FAUST Architecture File
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#include <vector>
#include <iostream>
#include <string>
#include <math.h>

#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"

#if defined(ALL_TESTS)

#include "dsp_scal.h"
#include "dsp_scal_exp10.h"

#include "dsp_vec0_4.h"
#include "dsp_vec0_8.h"
#include "dsp_vec0_16.h"
#include "dsp_vec0_32.h"
#include "dsp_vec0_64.h"
#include "dsp_vec0_128.h"
#include "dsp_vec0_256.h"
#include "dsp_vec0_512.h"

#include "dsp_vec1_4.h"
#include "dsp_vec1_8.h"
#include "dsp_vec1_16.h"
#include "dsp_vec1_32.h"
#include "dsp_vec1_64.h"
#include "dsp_vec1_128.h"
#include "dsp_vec1_256.h"
#include "dsp_vec1_512.h"

#include "dsp_vec0g_4.h"
#include "dsp_vec0g_8.h"
#include "dsp_vec0g_16.h"
#include "dsp_vec0g_32.h"
#include "dsp_vec0g_64.h"
#include "dsp_vec0g_128.h"
#include "dsp_vec0g_256.h"
#include "dsp_vec0g_512.h"

#include "dsp_vec1g_4.h"
#include "dsp_vec1g_8.h"
#include "dsp_vec1g_16.h"
#include "dsp_vec1g_32.h"
#include "dsp_vec1g_64.h"
#include "dsp_vec1g_128.h"
#include "dsp_vec1g_256.h"
#include "dsp_vec1g_512.h"

#elif defined(FAST_TESTS)

#include "dsp_scal.h"
#include "dsp_vec0_32.h"
#include "dsp_vec1_32.h"
#include "dsp_vec0g_32.h"
#include "dsp_vec1g_32.h"

#elif defined(SINGLE_TESTS)

#include "dsp_scal.h"

#endif

using namespace std;

#define ADD_DOUBLE string((sizeof(FAUSTFLOAT) == 8) ? "-double " : "")

ofstream* gFaustbenchLog = nullptr;

static double bench(dsp* dsp, const string& name, int run)
{
    measure_dsp mes(dsp, 1024, 5.);  // Buffer_size and duration in sec of  measure
    for (int i = 0; i < run; i++) {
        mes.measure();
        cout << name << " : " << mes.getStats() << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << endl;
        FAUSTBENCH_LOG<double>(mes.getStats());
    }
    return mes.getStats();
}

extern "C" int bench_all(const char* name, int run)
{
    vector<double> measures;
    vector<string> options;
    
    cout << "DSP bench of " << name << " compiled in C++ running with FAUSTFLOAT = " << ((sizeof(FAUSTFLOAT) == 4) ? "float" : "double") << endl;
    
#if defined(ALL_TESTS)
    
    options.push_back(ADD_DOUBLE + "-scal");
    options.push_back(ADD_DOUBLE + "-scal -exp10");
    
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 4");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 8");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 16");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 32");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 64");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 128");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 256");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 512");
    
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 4 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 8 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 16 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 32 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 64 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 128 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 256 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 512 -g");
    
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 4");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 8");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 16");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 32");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 64");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 128");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 256");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 512");
    
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 4 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 8 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 16 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 32 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 64 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 128 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 256 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 512 -g");
    
#elif defined(FAST_TESTS)
    
    options.push_back(ADD_DOUBLE + "-scal");
    options.push_back(ADD_DOUBLE + "-scal -exp10");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 32");
    options.push_back(ADD_DOUBLE + "-vec -lv 0 -vs 32 -g");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 32");
    options.push_back(ADD_DOUBLE + "-vec -lv 1 -vs 32 -g");
    
#elif defined(SINGLE_TESTS)
    
    options.push_back(ADD_DOUBLE + "-scal");
    
#endif
    
    int ind = 0;
    
#if defined(ALL_TESTS)
    
    // Scalar
    measures.push_back(bench(new dsp_scal(), options[ind++], run));
    measures.push_back(bench(new dsp_scal_exp10(), options[ind++], run));
    
    // Vector -lv 0
    measures.push_back(bench(new dsp_vec1_4(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_8(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_16(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_64(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_128(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_256(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0_512(), options[ind++], run));
    
    measures.push_back(bench(new dsp_vec1_4(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_8(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_16(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_64(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_128(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_256(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_512(), options[ind++], run));
    
    // Vector -lv 1
    measures.push_back(bench(new dsp_vec1_4(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_8(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_16(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_64(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_128(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_256(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_512(), options[ind++], run));
    
    measures.push_back(bench(new dsp_vec1g_4(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_8(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_16(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_64(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_128(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_256(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_512(), options[ind++], run));
    
#elif defined(FAST_TESTS)
    
    measures.push_back(bench(new dsp_scal(), options[ind++], run));
    measures.push_back(bench(new dsp_scal_exp10(), options[ind++], run));
    
    measures.push_back(bench(new dsp_vec0_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec0g_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1_32(), options[ind++], run));
    measures.push_back(bench(new dsp_vec1g_32(), options[ind++], run));
    
#elif defined(SINGLE_TESTS)
    
    measures.push_back(bench(new dsp_scal(), options[ind++], run));
    
#endif
    
    vector<double> measures1 = measures;
    sort(measures1.begin(), measures1.end());
    
    vector <double>::iterator it = find(measures.begin(), measures.end(), measures1[measures1.size()-1]);
    long int pos = distance(measures.begin(), it);
    
    cout << "Best value is : " << measures1[measures1.size()-1] << " with " << options[pos] << endl;
  	return 1;
}

#ifndef TARGET_OS_IPHONE

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustbench [-run <num>] foo.dsp" << endl;
        return 0;
    }
    
    //FAUSTBENCH_LOG<string>("faustbench C++");
    
    int run = lopt(argv, "-run", 1);
    return bench_all(argv[0], run);
}

#endif
