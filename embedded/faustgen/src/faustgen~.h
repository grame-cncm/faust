/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2023 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************
 ************************************************************************/

#ifndef faustgen__h
#define faustgen__h

// FAUSTFLOAT is mandatory defined as double
#define FAUSTFLOAT double
#define MSP64 1

/* link with */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <mutex>
#include <map>

#include <faust/gui/JSONUI.h>
#include <faust/gui/MidiUI.h>
#include <faust/gui/OSCUI.h>
#include <faust/gui/SaveUI.h>

#include "maxcpp5.h"

#ifndef WIN32
#include <libgen.h>
#endif

// Here to be able to use 'post'
#include <faust/gui/mspUI.h>

#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_drag.h"

#define FAUSTGEN_VERSION "1.66"

#include "faustgen_factory.h"

//====================
// Faust DSP Instance
//====================

class faustgen : public MspCpp5<faustgen> {
    
        friend class faustgen_factory;
        
    private:
        
        faustgen_factory* fDSPfactory;
        std::map<std::string, std::vector<t_object*> > fOutputTable;  // Output UI items (like bargraph) in the patcher to be notified
    
        max_midi  fMidiHandler;         // Generic MIDI handler
        mspUI* fDSPUI;                  // Control UI
        MidiUI* fMidiUI;                // Midi UI
        OSCUI* fOSCUI;                  // OSC UI
        SaveUI* fSavedUI;               // Save/load current value, reset to init value
    
        ::dsp* fDSP;                    // LLVM Faust dsp
        t_object* fEditor;              // Text editor object
        bool fMute;                     // DSP mute state
        static t_jrgba gDefaultColor;   // Color of the object to be used when restoring default color
        
        // Display DSP text source
        void display_dsp_source();
        
        // Display the Faust module's parameters along with their standard values
        void display_dsp_params();
        
        // Compile DSP with -svg option and display the SVG files
        void display_svg();
        void display_documentation();
        void display_libraries();
        
        // Create the Faust LLVM based DSP
        void create_dsp(bool init);
        
        void free_dsp();
        
        void set_dirty();
        
        void dsp_status(const char* mess);
        t_pxobject* check_dac();
        void create_jsui();
        void update_outputs();
        
        bool allocate_factory(const std::string& effect_name);
        
        void init_controllers();
        
        t_dictionary* json_reader(const char* jsontext);
    
    public:
        
        faustgen()
        {
            faustgen(gensym("faustgen~"), NULL, NULL);
        }
        
        faustgen(t_symbol* sym, long ac, t_atom* av);
        
        void update_sourcecode();
        
        void hilight_on();
        void hilight_off();
        void hilight_error(const std::string& error);
        
        // Called upon deleting the object inside the patcher
        ~faustgen();
        
        // Called upon sending the object a message inside the max patcher
        // Allows to set a value to the Faust module's parameter
        void anything(long inlet, t_symbol* s, long ac, t_atom* av);
        
        void compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        void read(long inlet, t_symbol* s);
        void write(long inlet, t_symbol* s);
        
        void polyphony(long inlet, t_symbol* s, long argc, t_atom* argv);
        void init(long inlet, t_symbol* s, long argc, t_atom* argv);
        void dump(long inlet, t_symbol* s, long argc, t_atom* argv);
    
        void midievent(long inlet, t_symbol* s, long argc, t_atom* argv);
        void osc(long inlet, t_symbol* s, long argc, t_atom* argv);
    
        void dump_inputs();
        void dump_outputs();
        
        void librarypath(long inlet, t_symbol* s);
        
        void mute(long inlet, long mute);
        
        // Called when saving the Max patcher, this function saves the necessary
        // data inside the json file (faust sourcecode)
        void appendtodictionary(t_dictionary* d);
        
        void getfromdictionary(t_dictionary* d);
        
        // Called when the user double-clicks on the faustgen object inside the Max patcher
        void dblclick(long inlet);
    
        void assist(void* b, long msg, long a, char* dst);
        
        // Called when closing the text editor, calls for the creation of a new Faust module with the updated sourcecode
        void edclose(long inlet, char** text, long size);
        
        // Process the signal data with the Faust module
        void perform(int vs, t_sample** inputs, long numins, t_sample** outputs, long numouts);
    
        // Callback given to setupIO
        void init(double samplerate);
    
};

#endif
