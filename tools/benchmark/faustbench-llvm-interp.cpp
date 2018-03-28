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

#include "faust/dsp/dsp-bench.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustbench-llvm-interp foo.dsp" << endl;
        return 0;
    }
    
    std::cout << "Libfaust version : " << getCLibFaustVersion () << std::endl;
    
    std::string error_msg1;
    std::string error_msg2;
    dsp_factory* factory1 = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "", error_msg1, -1);
    dsp_factory* factory2 = createInterpreterDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], error_msg2);
    
    if (!factory1) {
        std::cout << "Cannot create factory : " << error_msg1;
        exit(1);
    }
    
    if (!factory2) {
        std::cout << "Cannot create factory : " << error_msg2;
        exit(1);
    }
    
    dsp* DSP1 = factory1->createDSPInstance();
    dsp* DSP2 = factory2->createDSPInstance();
    
    if (!DSP1 || !DSP2) {
        std::cout << "Cannot create instances" << std::endl;
        exit(1);
    }
    
    measure_dsp* measure1 = new measure_dsp(DSP1, 1024, 5.0);
    measure_dsp* measure2 = new measure_dsp(DSP2, 1024, 5.0);
    
    measure1->measure();
    measure2->measure();
    
    double res1 = measure1->getStats();
    double res2 = measure2->getStats();
  
    cout << "Result LLVM : " << res1 <<  " Interpreter : " << res2 << " ratio : " << res1/res2 << std::endl;
  
    delete measure1;
    delete measure2;
    
    deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory1));
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory2));
    
    return 0;
}
