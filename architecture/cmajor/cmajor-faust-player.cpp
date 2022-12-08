/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2022 GRAME, Centre National de Creation Musicale
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
#include <string>

#include "faust/gui/GTKUI.h"
#include "faust/audio/jack-dsp.h"
#include "faust/dsp/cmajorpatch-dsp.h"
#include "cmajor-tools.h"
#include "faust/dsp/libfaust.h"
#include "faust/misc.h"
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#include <cmajor/helpers/cmaj_PatchUtilities.h>

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define FAUST_FILE        "faust.cmajor"
#define FAUST_PATCH_FILE  "faust.cmajorpatch"

#define HYBRID_FILE       "hybrid.cmajor"
#define HYBRID_PATCH_FILE "hybrid.cmajorpatch"

inline bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "cmajor-faust-player <foo.dsp> (pure Faust code), <foo.cmajorpatch> (pure Cmajor patch) or <foo.cmajor> (pure Cmajor code or Faust/Cmajor hybrid code)" << endl;
        exit(-1);
    }
    
    char* filename = argv[argc-1];
    string real_file;
    
    int argc1 = 0;
    const char* argv1[64];
    for (int i = 1; i < argc-1; i++) {
        argv1[argc1++] = argv[i];
    }
    
    if (endWith(filename, ".dsp")) {
        
        // We have a pure Faust file, compile it to Cmajor
        faust_cmajor_parser parser;
        if (!parser.generateCmajorFile(filename, FAUST_FILE, argc1, argv1)) {
            cerr << "ERROR : file '" << filename << "' cannot be opened or compiled!\n";
            exit(-1);
        }
        
        // Generate "cmajorpatch" file
        parser.createCmajorPatch(FAUST_FILE);
        real_file = FAUST_FILE;
        
    } else if (endWith(filename, ".cmajor")) {
        
        // We have a pure Cmajor file or a Faust/Cmajor file, parse it, compile the Faust part to Cmajor, generate the Cmajor result
        faust_cmajor_parser parser;
        if (!parser.parseCmajorFile(filename, HYBRID_FILE, argc1, argv1)) {
            cerr << "ERROR : file '" << filename << "' cannot be opened or compiled!\n";
            exit(-1);
        }
        
        // Generate "cmajorpatch" file
        parser.createCmajorPatch(HYBRID_FILE);
        real_file = HYBRID_FILE;
        
    } else {
        cerr << "Unsupported file extension" << endl;
        exit(1);
    }
    
    try {
        string error_msg;
        cmajor_dsp_factory* factory = createCmajorDSPFactoryFromFile(real_file, argc, (const char**)argv, error_msg);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(1);
        }
        cmajorpatch_dsp* DSP = factory->createDSPInstance();
        
        cout << "getNumInputs " << DSP->getNumInputs() << endl;
        cout << "getNumOutputs " << DSP->getNumOutputs() << endl;
        
        jackaudio audio;
        audio.init(filename, DSP);
        
        // Has to be done after init
        GTKUI interface(filename, &argc, &argv);
        DSP->buildUserInterface(&interface);
        
        // MIDI handling
        rt_midi midi_handler(filename, false, true);
        DSP->setMidiHandler(&midi_handler);
        
        midi_handler.startMidi();
        audio.start();
        
        interface.run();
        
        midi_handler.stopMidi();
        audio.stop();
        
        // Cleanup
        delete DSP;
        delete factory;
    } catch (...) {
        cerr << "ERROR : cannot allocate cmajorpatch_dsp\n";
        exit(-1);
    }
    
    return 0;
}
