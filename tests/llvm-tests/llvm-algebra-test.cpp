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

static void testDSP(dsp* dsp)
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
    dsp* dsp1, *dsp2, *dsp3, *combined1, *combined2;
    string error_msg;
    
    cout << "Testing createDSPSequencer\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPSequencer : dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPSequencer : dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    
    cout << "\nTesting createDSPParallelizer\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,1);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (2,2);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPParallelize(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if ((dsp1->getNumInputs() + dsp2->getNumInputs()) != combined1->getNumInputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumInputs() + dsp2->getNumInputs()) != combined1->getNumInputs()\n";
    }
    if ((dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined1->getNumOutputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    
    cout << "\nTesting createDSPSplitter\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPSplitter(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPSplitter(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPSplitter : (dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPSplitter : (dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }

    testDSP(combined1);
    
    cout << "\nTesting createDSPMerger\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_,_,_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (1,1,2,2);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPMerger : (dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPMerger : (dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    
    cout << "\nTesting createDSPRecursiver\n";
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (_);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    combined1 = createDSPRecursiver(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    factory1 = createDSPFactoryFromString("FaustDSP", "process = (+,+);", 0, nullptr, "", error_msg);
    factory2 = createDSPFactoryFromString("FaustDSP", "process = (_,_);", 0, nullptr, "", error_msg);
    factory3 = createDSPFactoryFromString("FaustDSP", "process = (1,1);", 0, nullptr, "", error_msg);
    dsp1 = factory1->createDSPInstance();
    dsp2 = factory2->createDSPInstance();
    dsp3 = factory3->createDSPInstance();
    combined1 = createDSPRecursiver(dsp1, dsp2, error_msg);
    combined2 = createDSPSequencer(dsp3, combined1, error_msg);
    printError(combined2, error_msg);
    
    if ((dsp1->getNumInputs() - dsp2->getNumOutputs()) != combined1->getNumInputs()) {
        cout << "Error in createDSPRecursiver : (dsp1->getNumInputs() - dsp2->getNumOutputs()) != combined->getNumInputs()\n";
    }
    
    if (dsp1->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPRecursiver : (dsp1->getNumOutputs() != combined->getNumOutputs()\n";
    }
    
    testDSP(combined2);
    
    return 0;
}

