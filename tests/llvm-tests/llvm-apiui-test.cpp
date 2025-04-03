/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2024 GRAME, Centre National de Creation Musicale
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
#include <fstream>
#include <sstream>
#include <thread>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/libfaust.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/gui/APIUI.h"
#include "faust/misc.h"

using namespace std;

// To do CPU native compilation
#ifndef JIT_TARGET
#define JIT_TARGET ""
#endif

static void Test(const char* dspFileAux)
{
    string error_msg;
    string dspFile = dspFileAux;
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromFile\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromFile(dspFile, 0, nullptr, JIT_TARGET, error_msg, -1);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
         
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "Test of APIUI" << endl;
        APIUI api_ui;
        DSP->buildUserInterface(&api_ui);
        for (int p = 0; p < api_ui.getParamsCount(); p++) {
            cout << "======================" << endl;
            cout << "getParamLabel " << api_ui.getParamLabel(p) << endl;
            cout << "getParamShortname " << api_ui.getParamShortname(p) << endl;
            cout << "getParamAddress " << api_ui.getParamAddress(p) << endl;
            cout << "getParamMin " << api_ui.getParamMin(p) << endl;
            cout << "getParamMax " << api_ui.getParamMax(p) << endl;
            cout << "getParamInit " << api_ui.getParamInit(p) << endl;
            cout << "getParamStep " << api_ui.getParamStep(p) << endl;
            cout << "getParamRatio " << api_ui.getParamRatio(p) << endl;
            
            for (int step = 0; step < 10; step++) {
                float val = float(step)/9.f;
                cout << "ratio2value " << val << " " << api_ui.ratio2value(p, val) << endl;
            }
            
            api_ui.setParamRatio(p, 0.0);
            cout << "getParamRatio 0.0 " << api_ui.getParamRatio(p) << endl;
            cout << "getParamValue 0.0 " << api_ui.getParamValue(p) << endl;
            
            api_ui.setParamRatio(p, 0.3);
            cout << "getParamRatio 0.3 " << api_ui.getParamRatio(p) << endl;
            cout << "getParamValue 0.3 " << api_ui.getParamValue(p) << endl;
            
            api_ui.setParamRatio(p, 0.5);
            cout << "getParamRatio 0.5 " << api_ui.getParamRatio(p) << endl;
            cout << "getParamValue 0.5 " << api_ui.getParamValue(p) << endl;
            
            api_ui.setParamRatio(p, 0.9);
            cout << "getParamRatio 0.9 " << api_ui.getParamRatio(p) << endl;
            cout << "getParamValue 0.9 " << api_ui.getParamValue(p) << endl;
            
            api_ui.setParamRatio(p, 1.0);
            cout << "getParamRatio 1.0 " << api_ui.getParamRatio(p) << endl;
            cout << "getParamValue 1.0 " << api_ui.getParamValue(p) << endl;
        }
      
        delete DSP;
        deleteDSPFactory(factory);
    }
}

int main(int argc, char* argv[])
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help") || argc < 2) {
        cout << "llvm-apiui-test foo.dsp" << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
   
    Test(argv[1]);
    
    return 0;
}

