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
#include <assert.h>

#include "faust/gui/GTKUI.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/dsp/dsp-optimizer.h"
#include "faust/audio/dummy-audio.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static llvm_dsp_factory* gFactory = nullptr;

#define printError(dsp, error_msg) if (!dsp) cout << error_msg;

static void testDSP(dsp* dsp)
{
    cout << "testDSP\n";
    assert(dsp);
    
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

// Note: no memory management done here...
static dsp* createDSP(const string& code)
{
    string error_msg;
    gFactory = createDSPFactoryFromString("FaustDSP", code, 0, nullptr, "", error_msg);
    if (!gFactory) {
        cout << error_msg;
    }
    assert(gFactory);
    return gFactory->createDSPInstance();
}

static void benchDSP(const string& title, const string& code, dsp* combined)
{
    cout << title << endl;
    
    dsp* dsp = createDSP(code);
    assert(dsp);
  
    measure_dsp* mes1 = new measure_dsp(dsp, 512, 5.);       // Buffer_size and duration in sec of measure
    mes1->measure();
    pair<double, double> res1 = mes1->getStats();
    cout << res1.first << " " << "(DSP CPU % : " << (mes1->getCPULoad() * 100) << ")" << endl;
    
    measure_dsp* mes2 = new measure_dsp(combined, 512, 5.);  // Buffer_size and duration in sec of measure
    mes2->measure();
    pair<double, double> res2 = mes2->getStats();
    cout << res2.first << " " << "(DSP CPU % : " << (mes2->getCPULoad() * 100) << ")" << endl;
    
    cout << "Ratio = " << (res1.first/res2.first) << endl;
    
    delete mes1;
    delete mes2;
    deleteDSPFactory(gFactory);
}

int main(int argc, char* argv[])
{
    dsp* dsp1, *dsp2, *dsp3, *combined1, *combined2;
    string error_msg;
      
    cout << "Testing createDSPSequencer\n";
    
    dsp1 = createDSP("process = (_);");
    dsp2 = createDSP("process = (_,_);");
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    dsp1 = createDSP("process = (_,_);");
    dsp2 = createDSP("process = (_);");
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    dsp1 = createDSP("process = (1,2);");
    dsp2 = createDSP("process = (_,_);");
    combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPSequencer : dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPSequencer : dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    testDSP(createDSP("process = (1,2):(_,_);"));
    
    benchDSP("\ncreateDSPSequencer CPU test\n", "process = (1,2):(_,_);", combined1);
    
    cout << "\nTesting createDSPParallelizer\n";
    
    dsp1 = createDSP("process = (1,1);");
    dsp2 = createDSP("process = (2,2);");
    combined1 = createDSPParallelizer(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if ((dsp1->getNumInputs() + dsp2->getNumInputs()) != combined1->getNumInputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumInputs() + dsp2->getNumInputs()) != combined1->getNumInputs()\n";
    }
    if ((dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined1->getNumOutputs()) {
        cout << "Error in createDSPParallelizer : (dsp1->getNumOutputs() + dsp2->getNumOutputs()) != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    testDSP(createDSP("process = (1,1),(2,2);"));
    
    benchDSP("\ncreateDSPParallelizer CPU test\n", "process = (1,1),(2,2);", combined1);
    
    cout << "\nTesting createDSPSplitter\n";
    
    dsp1 = createDSP("process = (_,_);");
    dsp2 = createDSP("process = (_,_,_);");
    combined1 = createDSPSplitter(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    dsp1 = createDSP("process = (1,2);");
    dsp2 = createDSP("process = (_,_,_,_);");
    combined1 = createDSPSplitter(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPSplitter : (dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPSplitter : (dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }

    testDSP(combined1);
    testDSP(createDSP("process = (1,2)<:(_,_,_,_);"));
    
    benchDSP("\ncreateDSPSplitter CPU test\n", "process = (1,2)<:(_,_,_,_);", combined1);
   
    cout << "\nTesting createDSPMerger\n";
    
    dsp1 = createDSP("process = (_,_,_);");
    dsp2 = createDSP("process = (_,_);");
    combined1 = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    dsp1 = createDSP("process = (1,1,2,2);");
    dsp2 = createDSP("process = (_,_);");
    combined1 = createDSPMerger(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    if (dsp1->getNumInputs() != combined1->getNumInputs()) {
        cout << "Error in createDSPMerger : (dsp1->getNumInputs() != combined1->getNumInputs()\n";
    }
    
    if (dsp2->getNumOutputs() != combined1->getNumOutputs()) {
        cout << "Error in createDSPMerger : (dsp2->getNumOutputs() != combined1->getNumOutputs()\n";
    }
    
    testDSP(combined1);
    testDSP(createDSP("process = (1,1,2,2):>(_,_);"));
    
    benchDSP("\ncreateDSPMerger CPU test\n", "process = (1,1,2,2):>(_,_);", combined1);
    
    cout << "\nTesting createDSPRecursiver\n";
    
    dsp1 = createDSP("process = (_);");
    dsp2 = createDSP("process = (_,_);");
    combined1 = createDSPRecursiver(dsp1, dsp2, error_msg);
    printError(combined1, error_msg);
    
    dsp1 = createDSP("process = (+,+);");
    dsp2 = createDSP("process = (_,_);");
    dsp3 = createDSP("process = (1,1);");
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
    testDSP(createDSP("process = (1,1):(+,+)~(_,_);"));
    
    benchDSP("\ncreateDSPRecursiver CPU test\n", "process = (+,+)~(_,_);", combined1);
    
    {
        dsp1 = createDSP("process = *(hslider(\"vol1\", 0.5, 0, 1, 0.01)),*(hslider(\"vol2\", 0.5, 0, 1, 0.01));");
        dsp2 = createDSP("process = *(vslider(\"vol1\", 0.5, 0, 1, 0.01)),*(vslider(\"vol2\", 0.5, 0, 1, 0.01));");
        combined1 = createDSPSequencer(dsp1, dsp2, error_msg, Layout::kVerticalGroup);
        GTKUI gui((char*)"GTKUI", &argc, &argv);
        combined1->buildUserInterface(&gui);
        printError(combined1, error_msg);
        gui.run();
    }
    
    {
        dsp1 = createDSP("process = *(hslider(\"vol1\", 0.5, 0, 1, 0.01)),*(hslider(\"vol2\", 0.5, 0, 1, 0.01));");
        dsp2 = createDSP("process = *(vslider(\"vol1\", 0.5, 0, 1, 0.01)),*(vslider(\"vol2\", 0.5, 0, 1, 0.01));");
        combined1 = createDSPSequencer(dsp1, dsp2, error_msg, Layout::kHorizontalGroup);
        GTKUI gui((char*)"GTKUI", &argc, &argv);
        combined1->buildUserInterface(&gui);
        printError(combined1, error_msg);
        gui.run();
    }
    
    {
        dsp1 = createDSP("process = *(hslider(\"vol1\", 0.5, 0, 1, 0.01)),*(hslider(\"vol2\", 0.5, 0, 1, 0.01));");
        dsp2 = createDSP("process = *(vslider(\"vol1\", 0.5, 0, 1, 0.01)),*(vslider(\"vol2\", 0.5, 0, 1, 0.01));");
        combined1 = createDSPSequencer(dsp1, dsp2, error_msg);
        GTKUI gui((char*)"GTKUI", &argc, &argv);
        combined1->buildUserInterface(&gui);
        printError(combined1, error_msg);
        gui.run();
    }
    
    {
        dsp1 = createDSP("process = *(hslider(\"vol1\", 0.5, 0, 1, 0.01)),*(hslider(\"vol2\", 0.5, 0, 1, 0.01));");
        dsp2 = createDSP("process = *(vslider(\"vol1\", 0.5, 0, 1, 0.01)),*(vslider(\"vol2\", 0.5, 0, 1, 0.01));");
        combined1 = createDSPSequencer(dsp1, dsp2, error_msg, Layout::kVerticalGroup, "FOO");
        GTKUI gui((char*)"GTKUI", &argc, &argv);
        combined1->buildUserInterface(&gui);
        printError(combined1, error_msg);
        gui.run();
    }
    
    {
        dsp1 = createDSP("import(\"stdfaust.lib\"); process = os.osc(500);");
        dsp2 = createDSP("import(\"stdfaust.lib\"); process = os.square(700);");
        combined1 = createDSPCrossfader(dsp1, dsp2, error_msg, Layout::kVerticalGroup);
        GTKUI gui((char*)"GTKUI", &argc, &argv);
        combined1->buildUserInterface(&gui);
        printError(combined1, error_msg);
        
        dummyaudio audio(1);
        if (!audio.init("FaustDSP", combined1)) {
            return 0;
        }
        
        audio.start();
        audio.stop();
        
        gui.run();
    }
    
    // Finally delete all factories that will themselves delete all attached DSP.
    deleteAllDSPFactories();
    
    return 0;
}

