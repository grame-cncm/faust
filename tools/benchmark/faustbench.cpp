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
#include <tuple>
#include <iostream>
#include <string>
#include <math.h>

#include "faust/gui/UI.h"
#include "faust/dsp/one-sample-dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"

#include "faust/gui/Soundfile.h"

// To be used by DSP code if no SoundUI is used
Soundfile* defaultsound = nullptr;

#if defined(ALL_TESTS)

#include "dsp_scal.h"
#include "dsp_scal_exp10.h"
#include "dsp_scal_mcd0.h"
#include "dsp_scal_mcd2.h"
#include "dsp_scal_mcd8.h"
#include "dsp_scal_mcd16.h"
#include "dsp_scal_mcd32.h"
#include "dsp_scal_mcd64.h"
#include "dsp_scal_os.h"

#include "dsp_vec0_4.h"
#include "dsp_vec0_8.h"
#include "dsp_vec0_16.h"
#include "dsp_vec0_32.h"
#include "dsp_vec0_64.h"
#include "dsp_vec0_128.h"
#include "dsp_vec0_256.h"
#include "dsp_vec0_512.h"

#include "dsp_vec0_fun_4.h"
#include "dsp_vec0_fun_8.h"
#include "dsp_vec0_fun_16.h"
#include "dsp_vec0_fun_32.h"
#include "dsp_vec0_fun_64.h"
#include "dsp_vec0_fun_128.h"
#include "dsp_vec0_fun_256.h"
#include "dsp_vec0_fun_512.h"

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
#include "dsp_scal_exp10.h"
#include "dsp_scal_mcd0.h"
#include "dsp_scal_mcd8.h"
#include "dsp_scal_mcd32.h"
#include "dsp_scal_os.h"
#include "dsp_vec0_32.h"
#include "dsp_vec1_32.h"
#include "dsp_vec0g_32.h"
#include "dsp_vec1g_32.h"

#elif defined(SINGLE_TESTS)

#include "dsp_scal.h"

#endif

using namespace std;

ofstream* gFaustbenchLog = nullptr;

template <typename REAL>
static tuple<double, double, double> bench(dsp* dsp, int dsp_size, const string& name, int run, int buffer_size, bool is_trace, bool is_control, int ds, int us, int filter)
{
    measure_dsp_real<REAL> mes(dsp, buffer_size, 5., is_trace, is_control, ds, us, filter);  // Buffer_size and duration in sec of measure
    // Keep best values
    std::pair<double, double> best_res(0,0);
    double best_cpu = 0.;
    // Several runs
    for (int i = 0; i < run; i++) {
        mes.measure();
        std::pair<double, double> res = mes.getStats();
        if (is_trace) cout << name << " : " << res.first << " MBytes/sec, SD : " << res.second << "% (DSP CPU : " << (mes.getCPULoad() * 100) << "% at 44100 Hz)" << endl;
        FAUSTBENCH_LOG<REAL>(res.first);
        if (res.first > best_res.first) {
            best_res = res;
            best_cpu = mes.getCPULoad();
        }
    }
    return make_tuple(best_res.first, best_res.second, best_cpu);
}

static bool compareFun(tuple<double, double, double> i, tuple<double, double, double> j)
{
    return (std::get<0>(i) < std::get<0>(j));
}

extern "C" int bench_all(const char* name, int run, int buffer_size, bool is_trace, bool is_control, int ds, int us, int filter)
{
    vector<tuple<double, double, double>> measures;
    vector<string> options;
    
    if (is_trace) {
        cout << "DSP bench of " << name << " compiled in C++ running with FAUSTFLOAT = " << ((sizeof(FAUSTFLOAT) == 4) ? "float" : "double") << endl;
        cout << "Running with 'compute' called with " << buffer_size << " samples" << endl;
    }
    
    dsp_scal dsp;
    cout << "DSP inputs = " << dsp.getNumInputs() << " outputs = " << dsp.getNumOutputs() << endl;
    
#if defined(ALL_TESTS)
    
    options.push_back("-scal" + OPTIONS);
    options.push_back("-scal -exp10" + OPTIONS);
    options.push_back("-scal -mcd 0" + OPTIONS);
    options.push_back("-scal -mcd 2" + OPTIONS);
    options.push_back("-scal -mcd 8" + OPTIONS);
    options.push_back("-scal -mcd 16" + OPTIONS);
    options.push_back("-scal -mcd 32" + OPTIONS);
    options.push_back("-scal -mcd 64" + OPTIONS);
    options.push_back("-scal -os" + OPTIONS);
    
    options.push_back("-vec -lv 0 -vs 4" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 8" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 16" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 32" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 64" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 128" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 256" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 512" + OPTIONS);
    
    options.push_back("-vec -fun -lv 0 -vs 4" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 8" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 16" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 32" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 64" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 128" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 256" + OPTIONS);
    options.push_back("-vec -fun -lv 0 -vs 512" + OPTIONS);
    
    options.push_back("-vec -lv 0 -g -vs 4" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 8" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 16" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 32" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 64" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 128" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 256" + OPTIONS);
    options.push_back("-vec -lv 0 -g -vs 512" + OPTIONS);
    
    options.push_back("-vec -lv 1 -vs 4" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 8" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 16" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 32" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 64" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 128" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 256" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 512" + OPTIONS);
    
    options.push_back("-vec -lv 1 -g -vs 4" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 8" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 16" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 32" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 64" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 128" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 256" + OPTIONS);
    options.push_back("-vec -lv 1 -g -vs 512" + OPTIONS);
    
#elif defined(FAST_TESTS)
    
    options.push_back("-scal" + OPTIONS);
    options.push_back("-scal -exp10" + OPTIONS);
    options.push_back("-scal -mcd 0" + OPTIONS);
    options.push_back("-scal -mcd 8" + OPTIONS);
    options.push_back("-scal -mcd 32" + OPTIONS);
    options.push_back("-scal -os" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 32" + OPTIONS);
    options.push_back("-vec -lv 0 -vs 32 -g" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 32" + OPTIONS);
    options.push_back("-vec -lv 1 -vs 32 -g" + OPTIONS);
    
#elif defined(SINGLE_TESTS)
    
    options.push_back("-scal" + OPTIONS);
    
#endif
    
    int ind = 0;
    
#if defined(ALL_TESTS)
    
    // Scalar
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal(), sizeof(dsp_scal), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_exp10(), sizeof(dsp_scal_exp10), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd0(), sizeof(dsp_scal_mcd0), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd2(), sizeof(dsp_scal_mcd2), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd8(), sizeof(dsp_scal_mcd8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd16(), sizeof(dsp_scal_mcd16), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd32(), sizeof(dsp_scal_mcd32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd64(), sizeof(dsp_scal_mcd64), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_os(), sizeof(dsp_scal_os), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
    // Vector -lv 0
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_4(), sizeof(dsp_vec1_4), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_8(), sizeof(dsp_vec0_8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_16(), sizeof(dsp_vec0_16), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_32(), sizeof(dsp_vec0_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_64(), sizeof(dsp_vec0_64), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_128(), sizeof(dsp_vec0_128), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_256(), sizeof(dsp_vec0_256), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_512(), sizeof(dsp_vec0_512), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_4(), sizeof(dsp_vec1_4), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_8(), sizeof(dsp_vec0g_8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_16(), sizeof(dsp_vec0g_16), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_32(), sizeof(dsp_vec0g_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_64(), sizeof(dsp_vec0g_64), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_128(), sizeof(dsp_vec0g_128), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_256(), sizeof(dsp_vec0g_256), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_512(), sizeof(dsp_vec0g_512), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
    // Vector -lv 1
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_4(), sizeof(dsp_vec1_4), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_8(), sizeof(dsp_vec1_8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_16(), sizeof(dsp_vec1_16), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_32(), sizeof(dsp_vec1_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_64(), sizeof(dsp_vec1_64), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_128(), sizeof(dsp_vec1_128), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_256(), sizeof(dsp_vec1_256), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_512(), sizeof(dsp_vec1_512), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_4(), sizeof(dsp_vec1g_4), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_8(), sizeof(dsp_vec1g_8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_16(), sizeof(dsp_vec1g_16), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_32(), sizeof(dsp_vec1g_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_64(), sizeof(dsp_vec1g_64), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_128(), sizeof(dsp_vec1g_128), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_256(), sizeof(dsp_vec1g_256), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_512(), sizeof(dsp_vec1g_512), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
#elif defined(FAST_TESTS)
    
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal(), sizeof(dsp_scal), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_exp10(), sizeof(dsp_scal_exp10), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd0(), sizeof(dsp_scal_mcd0), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd8(), sizeof(dsp_scal_mcd8), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_mcd32(), sizeof(dsp_scal_mcd32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal_os(), sizeof(dsp_scal_os), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0_32(), sizeof(dsp_vec0_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec0g_32(), sizeof(dsp_vec0g_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1_32(), sizeof(dsp_vec1_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    measures.push_back(bench<FAUSTFLOAT>(new dsp_vec1g_32(), sizeof(dsp_vec1g_32), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
#elif defined(SINGLE_TESTS)
    
    measures.push_back(bench<FAUSTFLOAT>(new dsp_scal(), sizeof(dsp_scal), options[ind++], run, buffer_size, is_trace, is_control, ds, us, filter));
    
#endif
    
    vector<tuple<double, double, double>> measures1 = measures;
    sort(measures1.begin(), measures1.end(), compareFun);
    
    vector<tuple<double, double, double>>::iterator it = find(measures.begin(), measures.end(), measures1[measures1.size()-1]);
    long int pos = distance(measures.begin(), it);
    
    if (is_trace) {
        tuple<double, double, double> res = measures1[measures1.size()-1];
        cout << "Best value is : " << get<0>(res) << " MBytes/sec, SD : " << get<1>(res) << "% (DSP CPU : " << (get<2>(res) * 100) << " at 44100 Hz) with " << options[pos] << endl;
    } else {
        cout << options[pos] << endl;
    }
    return 1;
}

#ifndef TARGET_OS_IPHONE

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustbench [-notrace] [-control] [-run <num>] [-bs <frames>] [-us <factor>] [-ds <factor>] [-filter <filter(0..4)>] foo.dsp" << endl;
        return 0;
    }
    
    //FAUSTBENCH_LOG<string>("faustbench C++");
    
    bool is_trace = !isopt(argv, "-notrace");
    bool is_control = isopt(argv, "-control");
    int run = lopt(argv, "-run", 1);
    int buffer_size = lopt(argv, "-bs", 512);
    int ds = lopt(argv, "-ds", 0);
    int us = lopt(argv, "-us", 0);
    int filter = lopt(argv, "-filter", 0);
   
    defaultsound = new Soundfile(MAX_CHAN, 1024, MAX_CHAN, 1, (sizeof(FAUSTFLOAT) == 8));
    int res = bench_all(argv[0], run, buffer_size, is_trace, is_control, ds, us, filter);
    delete defaultsound;
    return res;
}

#endif
