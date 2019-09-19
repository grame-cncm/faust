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

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define HYBRID_FILE      "hybrid.soul"
#define HYBRID_PATH_FILE "hybrid.soulpatch"

int main(int argc, char* argv[])
{
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "soul-faust-player foo.soulpatch (pure SOUL patch) or foo.soul (pure SOUL code or Faust/SOUL hybrid)" << endl;
        exit(-1);
    }
    
    char* filename = argv[argc-1];
    string real_file;
    
    if (endWith(filename, ".soul")) {
        
        // We have a pure SOUL file or a Faust/SOUL file. Parse it, compile the Faust part to SOUL, generate the SOUL result
        faust_soul_parser parser;
        if (!parser.parse(filename, HYBRID_FILE)) {
            cerr << "ERROR : file '" << filename << "' cannot be opened!\n";
            exit(-1);
        }
        
        // Generate "soulpatch" file
        std::ofstream patch_file(HYBRID_PATH_FILE);
        patch_file << "{";
        patch_file << "\"soulPatchV1\":" << endl;
            patch_file << "\t{" << endl;
                patch_file << "\t\t\"ID\": \"grame.soul.hybrid\"," << endl;
                patch_file << "\t\t\"version\": \"1.0\"," << endl;
                patch_file << "\t\t\"name\": \"hybrid\"," << endl;
                patch_file << "\t\t\"description\": \"SOUL example\"," << endl;
                patch_file << "\t\t\"category\": \"synth\"," << endl;
                patch_file << "\t\t\"manufacturer\": \"GRAME\"," << endl;
                patch_file << "\t\t\"website\": \"https://faust.grame.fr\"," << endl;
                patch_file << "\t\t\"isInstrument\": true," << endl;
                patch_file << "\t\t\"source\": "; patch_file << "\"" << HYBRID_FILE << "\"" << endl;
            patch_file << "\t}" << endl;
        patch_file << "}";
        patch_file.close();
        
        real_file = HYBRID_PATH_FILE;
    } else {
        real_file = filename;
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
        audio.init(filename, DSP);
        
        // Has to be done after init
        GTKUI interface(filename, &argc, &argv);
        DSP->buildUserInterface(&interface);
        
        // MIDI handling
        rt_midi midi_handler(filename, false, true);
        DSP->setMidiHandler(&midi_handler);
        
        midi_handler.startMidi();
        audio.start();
        
        // Call run all GUI instances
        GUI::runAllGuis();
        
        midi_handler.stopMidi();
        audio.stop();
        
        // Cleanup
        delete DSP;
        delete factory;
    } catch (...) {
        cerr << "ERROR : cannot allocate soulpatch_dsp\n";
        exit(-1);
    }
    
    return 0;
}
