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

#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"
#include <vector>
#include <iostream>

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

using namespace std;

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
    
    cout << "DSP bench of " << name << " compiled in C++" << endl;
    
    options.push_back("-scal");
    
    options.push_back("-vec -lv 0 -vs 4");
    options.push_back("-vec -lv 0 -vs 8");
    options.push_back("-vec -lv 0 -vs 16");
    options.push_back("-vec -lv 0 -vs 32");
    options.push_back("-vec -lv 0 -vs 64");
    options.push_back("-vec -lv 0 -vs 128");
    options.push_back("-vec -lv 0 -vs 256");
    options.push_back("-vec -lv 0 -vs 512");
    
    options.push_back("-vec -lv 1 -vs 4");
    options.push_back("-vec -lv 1 -vs 8");
    options.push_back("-vec -lv 1 -vs 16");
    options.push_back("-vec -lv 1 -vs 32");
    options.push_back("-vec -lv 1 -vs 64");
    options.push_back("-vec -lv 1 -vs 128");
    options.push_back("-vec -lv 1 -vs 256");
    options.push_back("-vec -lv 1 -vs 512");
    
    // Scalar
    measures.push_back(bench(new dsp_scal(), options[0]));
    
    // Vector -lv 0
    measures.push_back(bench(new dsp_vec1_4(), options[1]));
    measures.push_back(bench(new dsp_vec0_8(), options[2]));
    measures.push_back(bench(new dsp_vec0_16(), options[3]));
    measures.push_back(bench(new dsp_vec0_32(), options[4]));
    measures.push_back(bench(new dsp_vec0_64(), options[5]));
    measures.push_back(bench(new dsp_vec0_128(), options[6]));
    measures.push_back(bench(new dsp_vec0_256(), options[7]));
    measures.push_back(bench(new dsp_vec0_512(), options[8]));
    
    // Vector -lv 1
    measures.push_back(bench(new dsp_vec1_4(), options[9]));
    measures.push_back(bench(new dsp_vec1_8(), options[10]));
    measures.push_back(bench(new dsp_vec1_16(), options[11]));
    measures.push_back(bench(new dsp_vec1_32(), options[12]));
    measures.push_back(bench(new dsp_vec1_64(), options[13]));
    measures.push_back(bench(new dsp_vec1_128(), options[14]));
    measures.push_back(bench(new dsp_vec1_256(), options[15]));
    measures.push_back(bench(new dsp_vec1_512(), options[16]));
    
    vector<double> measures1 = measures;
    sort(measures1.begin(), measures1.end());
    
    vector <double>::iterator it = find(measures.begin(), measures.end(), measures1[measures1.size()-1]);
    int pos = distance(measures.begin(), it);
    
    cout << "Best value is : " << measures1[measures1.size()-1] << " " << options[pos] << endl;
  	return 1;
}

#ifndef TARGET_OS_IPHONE

int main(int argc, char* argv[])
{
    return bench_all(argv[0]);
}

#endif
