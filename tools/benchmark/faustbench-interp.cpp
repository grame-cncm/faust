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

#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    string error_msg;
    dsp_factory* factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], error_msg);
    
    if (!factory) {
        cerr << error_msg;
        exit(1);
    }
    
    dsp* DSP = factory->createDSPInstance();
    
    measure_dsp mes(DSP, 512, 5.);  // Buffer_size and duration in sec of measure
    mes.measure();
    pair<double, double> res = mes.getStats();
    cout << argv[argc-1] << " : " << res.first << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << endl;
    FAUSTBENCH_LOG<double>(res.first);
    
    // DSP deleted by mes
    return 0;
}
