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

#define NVOICES 8

/*
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif
*/

#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/faustgtk.h"
#include "faust/gui/MidiUI.h"
#include "faust/audio/jack-dsp.h"

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

inline string pathToContent(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

struct malloc_memory_manager : public dsp_memory_manager {
    
    void* allocate(size_t size)
    {
        void* res = malloc(size);
        cout << "malloc_manager : " << size << " " << res << endl;
        return res;
    }
    virtual void destroy(void* ptr)
    {
        cout << "free_manager : " << ptr << endl;
        free(ptr);
    }
    
};

int main(int argc, char* argv[])
{
    bool is_llvm = isopt(argv, "-llvm");
    bool is_interp = isopt(argv, "-interp");
    bool is_poly = isopt(argv, "-poly");
    
    bool midi_sync = false;
    int nvoices = 0;
    malloc_memory_manager manager;
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
    #ifdef INTERP_PLUGIN
        cout << "dynamic-jack-gtk-plugin -interp [-poly] foo.dsp" << endl;
    #else
        cout << "dynamic-jack-gtk [-llvm/interp] [-poly] <compiler-options> foo.dsp" << endl;
    #endif
        exit(EXIT_FAILURE);
    }
    
    // Index of first parameter after -llvm/interp and -poly
    int id = 0;
    for (id = 1; id < argc; id++) {
        if ((string(argv[id]) != "-llvm")
            && (string(argv[id]) != "-interp")
            && (string(argv[id]) != "-poly")) {
            break;
        }
    }
    
    dsp_factory* factory = 0;
    dsp* DSP = 0;
    mydsp_poly* dsp_poly = NULL;
    MidiUI* midiinterface = 0;
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
   
    string error_msg;
    
#ifdef INTERP_PLUGIN
    cout << "Using interpreter plugin backend" << endl;
    factory = readInterpreterDSPFactoryFromMachineFile(argv[argc-1]);
#else
    if (is_llvm) {
        cout << "Using LLVM backend" << endl;
        // argc : without the filename (last element);
        factory = createDSPFactoryFromFile(argv[argc-1], argc-id-1, (const char**)&argv[id], "", error_msg, -1);
        //factory = createDSPFactoryFromString("FaustLLVM", pathToContent(argv[argc-1]), argc-id-1, (const char**)&argv[id], "", error_msg, -1);
    } else {
        cout << "Using interpreter backend" << endl;
        // argc : without the filename (last element);
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc-id-1, (const char**)&argv[id], error_msg);
        //factory = createInterpreterDSPFactoryFromString("FaustInterp", pathToContent(argv[argc-1]), argc-id-1, (const char**)&argv[id], error_msg);
    }
#endif
    
    if (factory) {
        factory->setMemoryManager(&manager);
        DSP = factory->createDSPInstance();
        assert(DSP);
    } else {
        cout << "Cannot create factory : " << error_msg << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "getName " << factory->getName() << endl;
  
    if (is_poly) {
        MidiMeta::analyse(DSP, midi_sync, nvoices);
        cout << "Starting polyphonic mode nvoices : " << nvoices << endl;
        DSP = dsp_poly = new mydsp_poly(DSP, nvoices, true, false);
    }
    
    if (isopt(argv, "-double")) {
        cout << "Running in double..." << endl;
    }
   
    char name[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
   
    GUI* interface 	= new GTKUI(filename, &argc, &argv);
    FUI* finterface	= new FUI();

    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(finterface);

#ifdef HTTPCTRL
    httpdUI* httpdinterface = new httpdUI(name, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(httpdinterface);
#endif

#ifdef OSCCTRL
    GUI* oscinterface = new OSCUI(filename, argc, argv);
    DSP->buildUserInterface(oscinterface);
#endif

    jackaudio_midi audio;
    if (!audio.init(filename, DSP, true)) {
        return 0;
    }
    
    if (is_poly) {
        midiinterface = new MidiUI(&audio);
        audio.addMidiIn(dsp_poly);
        DSP->buildUserInterface(midiinterface);
        midiinterface->run();
    }
    
    finterface->recallState(rcfilename);
    audio.start();

#ifdef HTTPCTRL
    httpdinterface->run();
#endif

#ifdef OSCCTRL
    oscinterface->run();
#endif
    interface->run();

    audio.stop();
    finterface->saveState(rcfilename);
    
    delete DSP;
    delete interface;
    delete finterface;
    delete midiinterface;
  
#ifdef INTERP_PLUGIN
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
#else
    if (is_llvm) {
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
    } else {
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    }
#endif
    
    return 0;
}

