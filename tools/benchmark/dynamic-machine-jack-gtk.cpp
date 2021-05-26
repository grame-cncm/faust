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

#include "faust/audio/jack-dsp.h"
#include "faust/dsp/interpreter-machine-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/OSCUI.h"
#include "faust/misc.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    char name[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    int nvoices = 0;
    bool midi_sync = false;
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
    
    bool is_midi = isopt(argv, "-midi");
    bool is_osc = isopt(argv, "-osc");
    bool is_httpd = isopt(argv, "-httpd");
    
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "dynamic-machine-jack-gtk [-nvoices <num>] [-midi] [-osc] [-httpd] foo.fbc" << endl;
        cout << "Use '-nvoices <num>' to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI or OSC\n";
        cout << "Use '-midi' to activate MIDI control\n";
        cout << "Use '-osc' to activate OSC control\n";
        cout << "Use '-httpd' to activate HTTP control\n";
        exit(EXIT_FAILURE);
    }
    
    dsp_factory* factory = nullptr;
    dsp* DSP = nullptr;
    MidiUI* midiinterface = nullptr;
    httpdUI* httpdinterface = nullptr;
    GUI* oscinterface = nullptr;
    jackaudio_midi audio;
    string error_msg;
    
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    factory = readInterpreterDSPFactoryFromBitcodeFile(argv[argc-1], error_msg);
    if (!factory) {
        cerr << error_msg;
        exit(EXIT_FAILURE);
    }
    
    DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "Cannot create instance "<< endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "getName " << factory->getName() << endl;
    cout << "getSHAKey " << factory->getSHAKey() << endl;
    
    // Before reading the -nvoices parameter
    MidiMeta::analyse(DSP, midi_sync, nvoices);
    nvoices = lopt(argv, "-nvoices", nvoices);
    
    if (nvoices > 0) {
        cout << "Starting polyphonic mode nvoices : " << nvoices << endl;
        DSP = new mydsp_poly(DSP, nvoices, true, true);
    }
    
    if (isopt(argv, "-double")) {
        cout << "Running in double..." << endl;
    }
    
    GUI* interface = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(interface);
    
    FUI* finterface = new FUI();
    DSP->buildUserInterface(finterface);
    
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
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    
    return 0;
}

