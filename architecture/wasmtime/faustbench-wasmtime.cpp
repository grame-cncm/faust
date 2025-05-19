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

#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"
#include "wasmtime_dsp.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustbench-wasmer foo.wasm" << endl;
        exit(EXIT_FAILURE);
    }

    wasmtime_dsp_factory factory(argv[1]);
    dsp*                 DSP = factory.createDSPInstance();

    measure_dsp mes(DSP, 512, 5.);  // Buffer_size and duration in sec of measure
    mes.measure();
    std::pair<double, double> res = mes.getStats();
    cout << argv[argc - 1] << " : " << res.first << " MBytes/sec, SD : " << res.second
         << "% (DSP CPU % : " << (mes.getCPULoad() * 100) << ")" << endl;
    FAUSTBENCH_LOG<double>(res.first);

    // DSP deleted by mes
    return 0;
}
