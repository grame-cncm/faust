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
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "faust/gui/GTKUI.h"
#include "faust/audio/jack-dsp.h"
#include "faust/dsp/soulpatch-dsp.h"
#include "faust/dsp/libfaust.h"
#include "faust/misc.h"
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define HYBRID_FILE      "hybrid.soul"
#define HYBRID_PATH_FILE "hybrid.soulpatch"

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "soul-faust-player [-hybrid] foo.soul" << endl;
        cout << "Use '-hybrid' to load and execute an hybrid Faust/SOUL file\n";
        exit(-1);
    }
    
    string real_file;
    bool is_hybrid = isopt(argv, "-hybrid");
    
    if (is_hybrid) {
        
        // Parse te Faust/SOUL file to create a SOUL one
        faust_soul_parser parser;
        if (!parser.parse(argv[argc-1], HYBRID_FILE)) {
            cerr << "ERROR : file '" << argv[1] << "' cannot be opened!\n";
            exit(-1);
        }
        
        // Create "soulpatch"
        std::ofstream patch_file(HYBRID_PATH_FILE);
        patch_file << "{";
        patch_file << "\"soulPatchV1\":" << endl;
            patch_file << "{" << endl;
            patch_file << "\"ID\": \"grame.soul.hybrid\"," << endl;
            patch_file << "\"version\": \"1.0\"," << endl;
            patch_file << "\"name\": \"hybrid\"," << endl;
            patch_file << "\"description\": \"SOUL example\"," << endl;
            patch_file << "\"category\": \"synth\"," << endl;
            patch_file << "\"manufacturer\": \"GRAME\"," << endl;
            patch_file << "\"website\": \"https://faust.grame.fr\"," << endl;
            patch_file << "\"isInstrument\": true," << endl;
            patch_file << "\"source\": "; patch_file << "\"" << HYBRID_FILE << "\"" << endl;
            patch_file << "}" << endl;
        patch_file << "}";
        patch_file.close();
        
        real_file = HYBRID_PATH_FILE;
    } else {
        real_file = argv[argc-1];
    }
    
    try {
        string error_msg;
        soul_dsp_factory* factory = createSOULDSPFactoryFromFile(real_file, argc, (const char**)argv, error_msg);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(1);
        }
        soulpatch_dsp* DSP = factory->createDSPInstance();
        
        cout << "getNumInputs " << DSP->getNumInputs() << endl;
        cout << "getNumOutputs " << DSP->getNumOutputs() << endl;
        
        jackaudio audio;
        audio.init(argv[1], DSP);
        
        // Has to be done after init
        GTKUI interface(argv[1], &argc, &argv);
        DSP->buildUserInterface(&interface);
        
        // MIDI handling
        rt_midi midi_handler(argv[1], false, true);
        DSP->setMidiHandler(&midi_handler);
        
        midi_handler.startMidi();
        audio.start();
        
        // Call run all GUI instances
        GUI::runAllGuis();
        
        midi_handler.stopMidi();
        audio.stop();
        
        // Cleanup
        delete DSP;
        //delete factory;
    } catch (...) {
        cerr << "ERROR : cannot allocate soulpatch_dsp\n";
        exit(-1);
    }
    
    return 0;
}
