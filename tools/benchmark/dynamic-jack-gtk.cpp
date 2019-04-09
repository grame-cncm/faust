/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/*
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif
*/

#include "faust/dsp/dsp-optimizer.h"
#include "faust/audio/jack-dsp.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/OSCUI.h"
#include "faust/gui/SoundUI.h"
#include "faust/misc.h"

#include "faust/dsp/llvm-dsp-adapter.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

struct malloc_memory_manager : public dsp_memory_manager {
    
    void* allocate(size_t size)
    {
        void* res = malloc(size);
        //cout << "malloc_manager : " << size << " " << res << endl;
        return res;
    }
    virtual void destroy(void* ptr)
    {
        //cout << "free_manager : " << ptr << endl;
        free(ptr);
    }
    
};

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        std::cout << "item: " << list[i] << "\n";
    }
}

int main(int argc, char* argv[])
{
    char name[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
    
    bool is_llvm = isopt(argv, "-llvm");
    bool is_interp = isopt(argv, "-interp");
    bool is_midi = isopt(argv, "-midi");
    bool is_osc = isopt(argv, "-osc");
    bool is_httpd = isopt(argv, "-httpd");
    int nvoices = lopt(argv, "-nvoices", -1);
    
    malloc_memory_manager manager;
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
        cout << "dynamic-jack-gtk [-llvm|interp] [-nvoices <num>] [-midi] [-osc] [-httpd] [additional Faust options (-vec -vs 8...)] foo.dsp/foo.fbc/foo.ll/foo.bc/foo.mc" << endl;
        cout << "Use '-llvm' to use LLVM backend\n";
        cout << "Use '-interp' to use Interpreter backend (using either .dsp or .fbc (Faust Byte Code) files\n";
        cout << "Use '-nvoices <num>' to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC\n";
        cout << "Use '-midi' to activate MIDI control\n";
        cout << "Use '-osc' to activate OSC control\n";
        cout << "Use '-httpd' to activate HTTP control\n";
        exit(EXIT_FAILURE);
    }
    
    dsp_factory* factory = nullptr;
    dsp* DSP = nullptr;
    mydsp_poly* dsp_poly = nullptr;
    MidiUI* midiinterface = nullptr;
    httpdUI* httpdinterface = nullptr;
    GUI* oscinterface = nullptr;
    jackaudio_midi audio;
    string error_msg;
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if ((string(argv[i]) == "-llvm")
            || (string(argv[i]) == "-interp")
            || (string(argv[i]) == "-midi")
            || (string(argv[i]) == "-osc")
            || (string(argv[i]) == "-httpd")) {
            continue;
        } else if (string(argv[i]) == "-nvoices") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
        cout << argv[i] << " ";
    }
    cout << endl;
    
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    if (is_llvm) {
        cout << "Using LLVM backend" << endl;
        // argc : without the filename (last element);
        factory = createDSPFactoryFromFile(argv[argc-1], argc1, argv1, "", error_msg, -1);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            cout << "Trying to use readDSPFactoryFromIRFile..." << endl;
            factory = readDSPFactoryFromIRFile(argv[argc-1], "", error_msg, -1);
        }
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            cout << "Trying to use readDSPFactoryFromIRFile..." << endl;
            factory = readDSPFactoryFromBitcodeFile(argv[argc-1], "", error_msg, -1);
        }
        
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            cout << "Trying to use readDSPFactoryFromMachineFile..." << endl;
            factory = readDSPFactoryFromMachineFile(argv[argc-1], "", error_msg);
        }
  
        //cout << "getDSPMachineTarget " << getDSPMachineTarget() << endl;
        
        /*
        // Test Write/Read
        string path_name = factory->getName();
        
        cout << "Test writeDSPFactoryToBitcodeFile/readDSPFactoryFromBitcodeFile" << endl;
        writeDSPFactoryToBitcodeFile(static_cast<llvm_dsp_factory*>(factory), path_name);
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromBitcodeFile(path_name, "", -1);
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());
        */
        
    } else {
        cout << "Using interpreter backend" << endl;
        // argc : without the filename (last element);
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            cout << "Trying to use createInterpreterDSPFactoryFromFile..." << endl;
            factory = readInterpreterDSPFactoryFromBitcodeFile(argv[argc-1], error_msg);
        }
    }
    
    if (!factory) {
        cerr << "Cannot create factory : " << error_msg;
        exit(EXIT_FAILURE);
    }
    
    cout << "getCompileOptions " << factory->getCompileOptions() << endl;
    printList(factory->getLibraryList());
    printList(factory->getIncludePathnames());    
    
    //factory->setMemoryManager(&manager);  causes crash in -fm mode
    DSP = factory->createDSPInstance();
    
    // For test
    //DSP = new mydsp();
    
    /*
    measure_dsp* mes = new measure_dsp(DSP->clone(), 512, 5.);  // Buffer_size and duration in sec of measure
    for (int i = 0; i < 2; i++) {
        mes->measure();
        cout << argv[argc-1] << " : " << mes->getStats() << " " << "(DSP CPU % : " << (mes->getCPULoad() * 100) << ")" << endl;
    }
    */
    
    // To test compiled block reuse
    //DSP = factory->createDSPInstance();
    
    if (!DSP) {
        cerr << "Cannot create instance "<< endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "getName " << factory->getName() << endl;
    cout << "getSHAKey " << factory->getSHAKey() << endl;
    
    //exit(1);
  
    if (nvoices > 0) {
        cout << "Starting polyphonic mode nvoices : " << nvoices << endl;
        DSP = dsp_poly = new mydsp_poly(DSP, nvoices, true, true);
    }
    
    if (isopt(argv, "-double")) {
        cout << "Running in double..." << endl;
    }
   
    GUI* interface = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(interface);
    
    FUI* finterface = new FUI();
    DSP->buildUserInterface(finterface);
    
    SoundUI* soundinterface = new SoundUI();
    // SoundUI has to be dispatched on all internal voices
    if (dsp_poly) dsp_poly->setGroup(false);
    DSP->buildUserInterface(soundinterface);
    if (dsp_poly) dsp_poly->setGroup(true);
    
    if (!audio.init(filename, DSP)) {
        exit(EXIT_FAILURE);
    }
   
    if (is_httpd) {
        httpdinterface = new httpdUI(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
        DSP->buildUserInterface(httpdinterface);
    }
    
    if (is_osc) {
        oscinterface = new OSCUI(filename, argc, argv);
        DSP->buildUserInterface(oscinterface);
    }
    
    if (is_midi) {
        midiinterface = new MidiUI(&audio);
        DSP->buildUserInterface(midiinterface);
    }
    
    if (nvoices > 0) {
        audio.addMidiIn(dsp_poly);
    }
    
    // State (after UI construction)
    finterface->recallState(rcfilename);
    audio.start();

    if (is_httpd) {
        httpdinterface->run();
    }

    if (is_osc) {
        oscinterface->run();
    }
    
    if (is_midi) {
        midiinterface->run();
    }
    
    interface->run();

    audio.stop();
    
    finterface->saveState(rcfilename);
    
    delete DSP;
    delete interface;
    delete finterface;
    delete midiinterface;
    delete httpdinterface;
    delete oscinterface;
    delete soundinterface;
    
    //delete mes;
  
    if (is_llvm) {
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
    } else {
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    }
    
    return 0;
}

