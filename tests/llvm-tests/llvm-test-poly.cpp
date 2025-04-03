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
#include <sstream>
#include <thread>
#include <unistd.h>

#include "faust/dsp/poly-llvm-dsp.h"
#include "faust/gui/PrintUI.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/misc.h"

using namespace std;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help") || argc < 2) {
        cout << "llvm-test-poly organ.dsp" << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
   
    string error_msg;
    cout << "=============================\n";
    cout << "Test createPolyDSPFactoryFromFile\n";
    {
        llvm_dsp_poly_factory* factory = createPolyDSPFactoryFromFile(argv[1], 0, nullptr, "", error_msg, -1);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        dsp_poly* DSP = factory->createPolyDSPInstance(16, true, true);
        if (!DSP) {
            cerr << "Cannot create polyphonic instance "<< endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "Print UI parameters" << endl;
        PrintUI print_ui;
        DSP->buildUserInterface(&print_ui);
        
        // Allocate MIDI/audio driver
        jackaudio_midi audio;
        audio.init("FaustDSP", DSP);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"FaustDSP", &argc, (char***)&argv);
        DSP->buildUserInterface(&gtk_ui);
        
        // Create MIDI controller
        MidiUI midi_ui = MidiUI(&audio);
        DSP->buildUserInterface(&midi_ui);
        
        // Start real-time processing
        audio.start();
        
        // Start MIDI
        midi_ui.run();
        
        // Start GUI
        gtk_ui.run();
        
        // Cleanup
        audio.stop();
        delete DSP;
        delete factory;
    }
    
    return 0;
}

