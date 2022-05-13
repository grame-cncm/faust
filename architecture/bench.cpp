/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN bench.cpp ****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/

#include <iostream>

#include "faust/dsp/dsp-bench.h"
#include "faust/gui/meta.h"
#include "faust/misc.h"

using namespace std;

template <typename REAL>
static pair<double, double> bench(dsp* dsp, const string& name, int run, int buffer_size, bool is_control)
{
    measure_dsp_real<REAL> mes(dsp, buffer_size, 5., is_control);  // Buffer_size and duration in sec of measure
    for (int i = 0; i < run; i++) {
        mes.measure();
        cout << name << " : " << mes.getStats() << " MBytes/sec (DSP CPU % : " << (mes.getCPULoad() * 100) << " at " << BENCH_SAMPLE_RATE << " Hz)" << endl;
        FAUSTBENCH_LOG<double>(mes.getStats());
    }
    return make_pair(mes.getStats(), mes.getCPULoad());
}

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << argv[0] << " [-control] [-run <num>] [-bs <frames>]" << endl;
        return 0;
    }

    bool is_control = isopt(argv, "-control");
    int run = lopt(argv, "-run", 1);
    int buffer_size = lopt(argv, "-bs", 512);
    
    bench<FAUSTFLOAT>(new mydsp(), argv[0], run, buffer_size, is_control);
}

/******************** END bench.cpp ****************/
