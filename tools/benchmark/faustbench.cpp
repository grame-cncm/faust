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

#include "dsp_scal.h"

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

using namespace std;

#define ADD_DOUBLE string((sizeof(FAUSTFLOAT) == 8) ? "-double " : "")

static double bench(dsp* dsp, const string& name)
{
    dsp->init(48000);
    measure_dsp mes(dsp, 1024, 5);
    mes.measure();
    cout << name << " : " << mes.getStats() << endl;
    return mes.getStats();
}

extern "C" int bench_all(const char* name)
{
    vector<double> measures;
    vector<string> options;
    
    cout << "DSP bench of " << name << " compiled in C++ running with FAUSTFLOAT = " << ((sizeof(FAUSTFLOAT) == 4) ? "float" : "double") << endl;
    
    options.push_back(ADD_DOUBLE + "-scal");
    
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
    
    int ind = 0;
    
    // Scalar
    measures.push_back(bench(new dsp_scal(), options[ind++]));
    
    // Vector -lv 0
    measures.push_back(bench(new dsp_vec1_4(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_8(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_16(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_32(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_64(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_128(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_256(), options[ind++]));
    measures.push_back(bench(new dsp_vec0_512(), options[ind++]));
    
    measures.push_back(bench(new dsp_vec1_4(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_8(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_16(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_32(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_64(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_128(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_256(), options[ind++]));
    measures.push_back(bench(new dsp_vec0g_512(), options[ind++]));
    
    // Vector -lv 1
    measures.push_back(bench(new dsp_vec1_4(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_8(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_16(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_32(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_64(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_128(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_256(), options[ind++]));
    measures.push_back(bench(new dsp_vec1_512(), options[ind++]));
    
    measures.push_back(bench(new dsp_vec1g_4(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_8(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_16(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_32(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_64(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_128(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_256(), options[ind++]));
    measures.push_back(bench(new dsp_vec1g_512(), options[ind++]));
    
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
    return bench_all(argv[0]);
}

#endif
