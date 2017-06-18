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

/*
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif
*/

#include "faust/audio/jack-dsp.h"

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/poly-dsp.h"

#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/gui/faustgtk.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/OSCUI.h"

#include "faust/misc.h"

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
    
    bool midi_sync = false;
    malloc_memory_manager manager;
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
    #ifdef INTERP_PLUGIN
        cout << "dynamic-jack-gtk-plugin -interp [-nvoices N] [-midi] [-osc] [-httpd] foo.dsp" << endl;
    #else
        cout << "dynamic-jack-gtk [-llvm/interp] [-nvoices N] [-midi] [-osc] [-httpd] <compiler-options> foo.dsp" << endl;
    #endif
        exit(EXIT_FAILURE);
    }
    
    dsp_factory* factory = 0;
    dsp* DSP = 0;
    mydsp_poly* dsp_poly = NULL;
    MidiUI* midiinterface = 0;
    httpdUI* httpdinterface = 0;
    GUI* oscinterface = 0;
    jackaudio_midi audio;
    string error_msg;
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    
    int argc1 = 0;
    const char* argv1[32];
    
    for (int i = 1; i < argc-1; i++) {
        if ((string(argv[i]) == "-llvm")
            || (string(argv[i]) == "-interp")
            || (string(argv[i]) == "-midi")
            || (string(argv[i]) == "-osc")
            || (string(argv[i]) == "-httpd")) {
            continue;
        }
        if (string(argv[i]) == "-nvoices") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
    }
    
#ifdef INTERP_PLUGIN
    cout << "Using interpreter plugin backend" << endl;
    factory = readInterpreterDSPFactoryFromMachineFile(argv[argc-1]);
#else
    if (is_llvm) {
        cout << "Using LLVM backend" << endl;
        // argc : without the filename (last element);
        factory = createDSPFactoryFromFile(argv[argc-1], argc1, argv1, "", error_msg, -1);
        //factory = createDSPFactoryFromString("FaustLLVM", pathToContent(argv[argc-1]), argc-id-1, (const char**)&argv[id], "", error_msg, -1);
    } else {
        cout << "Using interpreter backend" << endl;
        // argc : without the filename (last element);
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
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
  
    if (nvoices > 0) {
        cout << "Starting polyphonic mode nvoices : " << nvoices << endl;
        DSP = dsp_poly = new mydsp_poly(DSP, nvoices, true, false);
    }
    
    if (isopt(argv, "-double")) {
        cout << "Running in double..." << endl;
    }
   
    GUI* interface = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(interface);
    
    FUI* finterface	= new FUI();
    DSP->buildUserInterface(finterface);
    finterface->recallState(rcfilename);
   
    if (!audio.init(filename, DSP, true)) {
        return 0;
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
    
    audio.start();

    if (is_httpd) {
        httpdinterface->run();
    }

    if (is_osc) {
        oscinterface->run();
    }
    
    if (is_osc) {
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

