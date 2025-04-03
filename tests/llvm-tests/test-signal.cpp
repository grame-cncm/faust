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

#include "faust/dsp/signal-dsp.h"
#include "faust/gui/GTKUI.h"
#include "faust/audio/coreaudio-dsp.h"
#include "faust/dsp/dsp-adapter.h"

#include <iostream>
#include <cstring>
#include <libgen.h>

#define BUFFER_SIZE 64

using namespace std;

//std::string dsp_code = "process = 1,2;";
//std::string dsp_code = "process = 1.5,2.6;";
//std::string dsp_code = "process = _ <: _+1.5, _+2.6;";
//std::string dsp_code = "process = _ <: (_+1.5, _+2.6) : (sin, cos);";
//std::string dsp_code = "process = sin;";
//std::string dsp_code = "process = @(5);";
//std::string dsp_code = "process = _ <: @(5), @(10);";
//std::string dsp_code = "process = _&_;";

std::string dsp_code = "process = 1 : + ~ _;";

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static bool hasCompileOption(const string& compile_options, const string& option)
{
    istringstream iss(compile_options);
    string token;
    while (std::getline(iss, token, ' ')) {
        if (token == option) return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    string error_msg;
    signal_dsp_factory* factory;
    
    if (argc == 1) {
        factory = createSignalDSPFactoryFromString("SignalDSP", dsp_code, 0, nullptr, error_msg);
    } else {
        factory = createSignalDSPFactoryFromFile(argv[1], 0, nullptr, error_msg);
    }
    if (!factory) {
        cerr << error_msg;
        return -1;
    }
     
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "ERROR : cannot allocate DSP\n";
        return -1;
    }
    
    if (hasCompileOption(factory->getCompileOptions(), "-double")) {
        cout << "Running in double..." << endl;
        DSP = new dsp_sample_adapter<double, float>(DSP);
    }
     
    cout << "getNumInputs() " << DSP->getNumInputs() << endl;
    cout << "getNumOutputs() " << DSP->getNumOutputs() << endl;
    
    DSP->init(44100);
     
    /*
    FAUSTFLOAT* inputs[DSP->getNumInputs()];
    for (int chan = 0; chan < DSP->getNumInputs(); chan++) {
        inputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
        memset(inputs[chan], 0, sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    FAUSTFLOAT* outputs[DSP->getNumOutputs()];
    for (int chan = 0; chan < DSP->getNumOutputs(); chan++) {
        outputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    DSP->compute(BUFFER_SIZE, inputs, outputs);
    for (int chan = 0; chan < DSP->getNumOutputs(); chan++) {
        for (int frame = 0; frame < BUFFER_SIZE/2; frame++) {
            cout << "chan[" << chan << "]frame[" << frame << "] = " << outputs[chan][frame] << endl;
        }
    }
    cout << "Type a key\n";
    char c = getchar();
    */
    
    char name[256];
    char filename[256];
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    GUI* gui = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(gui);
    
    coreaudio audio(44100, 512);
    if (!audio.init(name, DSP)) {
        cerr << "Unable to init audio" << endl;
        exit(1);
    }
    
    if (!audio.start()) {
        cerr << "Unable to start audio" << endl;
        exit(1);
    }
    
    gui->run();
    audio.stop();
    
    delete DSP;
    deleteSignalDSPFactory(factory);
     
    return 0;
}
