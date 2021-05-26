/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016-2021 GRAME, Centre National de Creation Musicale
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

#include "faust/audio/jack-dsp.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/OSCUI.h"
#include "faust/gui/SoundUI.h"
#include "faust/misc.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << "item: " << list[i] << "\n";
    }
}

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

struct DynamicDSP {
    
    dsp_factory* fFactory = nullptr;
    dsp* fDSP = nullptr;
    MidiUI* fMIDIInterface = nullptr;
    httpdUI* fHTTPDinterface = nullptr;
    GUI* fInterface = nullptr;
    GUI* fOSCinterface = nullptr;
    FUI* fFInterface = nullptr;
    SoundUI* fSoundinterface = nullptr;
    jackaudio_midi fAudio;
    
    bool is_llvm = false;
    
    DynamicDSP(int argc, char* argv[])
    {
        char name[256];
        char filename[256];
        char rcfilename[256];
        char* home = getenv("HOME");
        int nvoices = 0;
        bool midi_sync = false;
        string error_msg;
        
        snprintf(name, 255, "%s", basename(argv[0]));
        snprintf(filename, 255, "%s", basename(argv[argc-1]));
        snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
        
        is_llvm = isopt(argv, "-llvm");
        bool is_interp = isopt(argv, "-interp");
        bool is_midi = isopt(argv, "-midi");
        bool is_osc = isopt(argv, "-osc");
        bool is_all = isopt(argv, "-all");
        bool is_generic = isopt(argv, "-generic");
        bool is_httpd = isopt(argv, "-httpd");
        bool is_resample = isopt(argv, "-resample");
        bool is_double = isopt(argv, "-double");
        
        if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
            cout << "dynamic-jack-gtk [-llvm|interp] [-edit] [-generic] [-nvoices <num>] [-all] [-midi] [-osc] [-httpd] [-resample] [additional Faust options (-vec -vs 8...)] foo.dsp/foo.fbc/foo.ll/foo.bc/foo.mc" << endl;
            cout << "Use '-llvm' to use LLVM backend\n";
            cout << "Use '-interp' to use Interpreter backend, using either .dsp or .fbc (Faust Byte Code) files\n";
            cout << "Use '-edit' to start an edit/compile/run loop: closing the window will reopen a new one with the new compiled code\n";
            cout << "Use '-generic' to JIT for a generic CPU (otherwise 'native' mode is used)\n";
            cout << "Use '-nvoices <num>' to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC\n";
            cout << "Use '-all' to active the 'all voices always playing' mode\n";
            cout << "Use '-midi' to activate MIDI control\n";
            cout << "Use '-osc' to activate OSC control\n";
            cout << "Use '-httpd' to activate HTTP control\n";
            cout << "Use '-resample' to resample soundfiles to the audio driver sample rate\n";
            exit(EXIT_FAILURE);
        }
        
        cout << "Libfaust version : " << getCLibFaustVersion() << endl;
        
        int argc1 = 0;
        const char* argv1[64];
        
        cout << "Compiled with additional options : ";
        for (int i = 1; i < argc-1; i++) {
            if ((string(argv[i]) == "-llvm")
                || (string(argv[i]) == "-interp")
                || (string(argv[i]) == "-edit")
                || (string(argv[i]) == "-generic")
                || (string(argv[i]) == "-midi")
                || (string(argv[i]) == "-osc")
                || (string(argv[i]) == "-all")
                || (string(argv[i]) == "-httpd")
                || (string(argv[i]) == "-resample")) {
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
            
            string opt_target;
            if (is_generic) {
                string triple, cpu;
                splitTarget(getDSPMachineTarget(), triple, cpu);
                opt_target = triple + ":generic";
                cout << "Using LLVM backend in 'generic' mode\n";
            } else {
                cout << "Using LLVM backend in 'native' mode\n";
            }
            
            // argc : without the filename (last element);
            fFactory = createDSPFactoryFromFile(argv[argc-1], argc1, argv1, opt_target, error_msg, -1);
            
            if (!fFactory) {
                cerr << error_msg;
                return;
            }
            
        } else {
            cout << "Using interpreter backend" << endl;
            // argc : without the filename (last element);
            fFactory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
        }
        
        if (!fFactory) {
            cerr << error_msg;
            return;
        }
        
        cout << "getCompileOptions " << fFactory->getCompileOptions() << endl;
        printList(fFactory->getLibraryList());
        printList(fFactory->getIncludePathnames());
        
        fDSP = fFactory->createDSPInstance();
        if (!fDSP) {
            cerr << "Cannot create instance "<< endl;
            return;
        }
        
        if (is_double) {
            cout << "Running in double..." << endl;
            fDSP = new dsp_sample_adapter<double, float>(fDSP);
        }
        
        cout << "getName " << fFactory->getName() << endl;
        cout << "getSHAKey " << fFactory->getSHAKey() << endl;
        
        // Before reading the -nvoices parameter
        MidiMeta::analyse(fDSP, midi_sync, nvoices);
        nvoices = lopt(argv, "-nvoices", nvoices);
        
        if (nvoices > 0) {
            cout << "Starting polyphonic mode 'nvoices' : " << nvoices << " and 'all' : " << is_all << endl;
            fDSP = new mydsp_poly(fDSP, nvoices, !is_all, true);
        }
        
        fInterface = new GTKUI(filename, &argc, &argv);
        fDSP->buildUserInterface(fInterface);
        
        fFInterface = new FUI();
        fDSP->buildUserInterface(fFInterface);
        
        if (!fAudio.init(filename, fDSP)) {
            return;
        }
        
        // After audio init to get SR
        if (is_resample) {
            fSoundinterface = new SoundUI("", fAudio.getSampleRate(), nullptr, is_double);
        } else {
            fSoundinterface = new SoundUI("", -1, nullptr, is_double);
        }
        fDSP->buildUserInterface(fSoundinterface);
        
        if (is_httpd) {
            fHTTPDinterface = new httpdUI(name, fDSP->getNumInputs(), fDSP->getNumOutputs(), argc, argv);
            fDSP->buildUserInterface(fHTTPDinterface);
        }
        
        if (is_osc) {
            fOSCinterface = new OSCUI(filename, argc, argv);
            fDSP->buildUserInterface(fOSCinterface);
        }
        
        if (is_midi) {
            fMIDIInterface = new MidiUI(&fAudio);
            fDSP->buildUserInterface(fMIDIInterface);
        }
        
        // State (after UI construction)
        fFInterface->recallState(rcfilename);
        fAudio.start();
        
        if (is_httpd) {
            fHTTPDinterface->run();
        }
        
        if (is_osc) {
            fOSCinterface->run();
        }
        
        if (is_midi) {
            fMIDIInterface->run();
        }
        
        fInterface->run();
        
        fAudio.stop();
        fFInterface->saveState(rcfilename);
    }
    
    ~DynamicDSP()
    {
        delete fDSP;
        delete fInterface;
        delete fFInterface;
        delete fMIDIInterface;
        delete fHTTPDinterface;
        delete fOSCinterface;
        delete fSoundinterface;
        
        if (is_llvm) {
            deleteDSPFactory(static_cast<llvm_dsp_factory*>(fFactory));
        } else {
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(fFactory));
        }
    }
        
};

int main(int argc, char* argv[])
{
    if (isopt(argv, "-edit")) {
        // A very harsh way of updating the DSP code...
        while (true) DynamicDSP(argc, argv);
    } else {
        // Run once
        DynamicDSP(argc, argv);
    }
    return 0;
}

