
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

// Adapted from original Wasmer-based implementation to use Wasmtime C++ API
// (https://github.com/bytecodealliance/wasmtime)

#define JACK 1

#if JACK
#include "faust/audio/jack-dsp.h"
#else
#include "faust/audio/dummy-audio.h"
#endif
#include "faust/gui/httpdUI.h"
#include "faust/misc.h"
#include "faust/dsp/wasm-dsp.h"

#include <iostream>

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap  GUI::gTimedZoneMap;

static bool endsWith(const std::string& str, const std::string& suffix)
{
    if (str.length() >= suffix.length()) {
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faustwasmtime foo.dsp|foo.wasm" << endl;
        cout << "Open the http://127.0.0.1:5510 URL to get an http based control\n";
        exit(EXIT_FAILURE);
    }
    
    string error_msg;
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    std::string file = argv[1];
    wasm_dsp_factory* factory = nullptr;
    if (endsWith(file, ".dsp")) {
        factory = createWasmDSPFactoryFromFile(file, 0, NULL, error_msg, true);
    } else if (endsWith(file, ".wasm")) {
        factory = readWasmDSPFactoryFromMachineFile(file, error_msg);
    }
  
    if (!factory) {
        cerr << "Cannot create factory : " << error_msg;
        exit(EXIT_FAILURE);
    }
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "Cannot create instance " << endl;
        exit(EXIT_FAILURE);
    }

#if JACK
    jackaudio audio;
#else
    dummyaudio audio;
#endif
    if (!audio.init(argv[1], DSP)) {
        return 0;
    }

    httpdUI httpdinterface(argv[1], DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);

    audio.start();

    httpdinterface.run();

    char c;
    while ((c = getchar()) != 'q') {
        usleep(1000000);
    }

    audio.stop();
    
    delete DSP;
    deleteWasmDSPFactory(factory);
    
    return 0;
}
