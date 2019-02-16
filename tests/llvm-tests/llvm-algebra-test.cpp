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
#include <fstream>
#include <assert.h>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-combiner.h"

using namespace std;

#define printError(dsp, error_msg) if (!dsp) cout << error_msg;

void testDSP(dsp* dsp)
{
    cout << "testDSP\n";
    
    FAUSTFLOAT* inputs[dsp->getNumInputs()];
    for (int chan = 0; chan < dsp->getNumInputs(); chan++) {
        inputs[chan] = new FAUSTFLOAT[10];
        memset(inputs[chan], 0, 10 * sizeof(FAUSTFLOAT));
    }
    
    FAUSTFLOAT* outputs[dsp->getNumOutputs()];
    for (int chan = 0; chan < dsp->getNumOutputs(); chan++) {
        outputs[chan] = new FAUSTFLOAT[10];
    }
    
    cout << "Compute 1\n";
    dsp->compute(10, inputs, outputs);
    
    for (int chan = 0; chan < dsp->getNumInputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            cout << "inputs[" << chan << "]" << "[" << frame << "] = " << inputs[chan][frame] << endl;
        }
    }
    
    for (int chan = 0; chan < dsp->getNumOutputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            cout << "outputs[" << chan << "]" << "[" << frame << "] = " << outputs[chan][frame] << endl;
        }
    }

    cout << "Compute 2\n";
    dsp->compute(10, inputs, outputs);
    
    for (int chan = 0; chan < dsp->getNumInputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            cout << "inputs[" << chan << "]" << "[" << frame << "] = " << inputs[chan][frame] << endl;
        }
    }
    
    for (int chan = 0; chan < dsp->getNumOutputs(); chan++) {
        for (int frame = 0; frame < 10; frame++) {
            cout << "outputs[" << chan << "]" << "[" << frame << "] = " << outputs[chan][frame] << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    dsp_factory* factory1, *factory2, *factory3;
    dsp* dsp1, *dsp2, *dsp3, *combined;
    string error_msg;
    
    cout << "Testing createDSPSequencer\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    if (dsp1->getNumInputs() != combined->getNumInputs()) {
        cout << "Error in createDSPSequencer : dsp1->getNumInputs() != combined->getNumInputs()\n";
    }
    if (dsp2->getNumOutputs() != combined->getNumOutputs()) {
        cout << "Error in createDSPSequencer : dsp2->getNumOutputs() != combined->getNumOutputs()\n";
    }
    
    testDSP(combined);
    
    cout << "\nTesting createDSPParallelizer\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,1);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (2,2);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPParallelize(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    if ((dsp1->getNumInputs() + dsp2->getNumInputs()) != combined->getNumInputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumInputs() + dsp2->getNumInputs()) != combined->getNumInputs()\n";
    }
    if ((dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined->getNumOutputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined->getNumOutputs()\n";
    }
    
    testDSP(combined);
    
    cout << "\nTesting createDSPSpitter\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPSpitter(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPSpitter(dsp1, dsp2, error_msg);
    printError(combined, error_msg);

    testDSP(combined);
    
    cout << "\nTesting createDSPMerger\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,1,2,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    testDSP(combined);
    
    cout << "\nTesting createDSPRecursiver\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined = createDSPRecursiver(dsp1, dsp2, error_msg);
    printError(combined, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (+,+);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory3 = createDSPFactoryFromString("FaustDSP", "process = (1,1);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    dsp3 = factory3->createDSPInstance();
    combined = createDSPSequencer(dsp3, createDSPRecursiver(dsp1, dsp2, error_msg), error_msg);
    printError(combined, error_msg);
    
    testDSP(combined);
    
    return 0;
}

