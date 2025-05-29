/************************************************************************
    FAUST Architecture File
    Copyright (C) 2025 GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/wasm-machine-dsp.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"

using namespace std;

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << "item: " << list[i] << "\n";
    }
}

int main(int argc, const char** argv)
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help") || argc < 2) {
        cout << "interp-machine-test foo.fbc" << endl;
        exit(EXIT_FAILURE);
    }
    
    string error_msg;
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    string fbcFile = argv[1];
    
    cout << "=============================\n";
    cout << "Test readWasmDSPFactoryFromBitcodeFile\n";
    {
        // Read precompiled bitcode file
        wasm_dsp_factory* factory = readWasmDSPFactoryFromBitcodeFile(fbcFile, error_msg);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());
        
        cout << "getName " << factory->getName() << endl;
        cout << "getSHAKey " << factory->getSHAKey() << endl;
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance " << endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "Print UI parameters" << endl;
        PrintUI print_ui;
        DSP->buildUserInterface(&print_ui);
        
        dummyaudio audio(1);
        if (!audio.init("FaustDSP", DSP)) {
            return 0;
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteWasmDSPFactory(factory);
    }

    return 0;
}

