/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2024 GRAME, Centre National de Creation Musicale
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

//====================
// Faust DSP Instance
//====================

class faustgen_factory;

class faustgen : public MspCpp5<faustgen> {
    
        friend class faustgen_factory;
        
    private:
        
        faustgen_factory* fDSPfactory;
        std::map<std::string, std::vector<t_object*>> fOutputTable;  // Output UI items (like bargraph) in the patcher to be notified
    
        max_midi fMidiHandler;          // Generic MIDI handler
        mspUI* fDSPUI;                  // Control UI
        MidiUI* fMidiUI;                // Midi UI
        OSCUI* fOSCUI;                  // OSC UI
        SaveUI* fSavedUI;               // Save/load current value, reset to init value
    
        ::dsp* fDSP;                    // JIT compiled Faust dsp
        int fNumOutputs = 0;            // Cached getNumOutputs value
        ::dsp* fMCDSP;                  // Multi-channels adapter
        t_object* fEditor;              // Text editor object
        bool fRNBOAttr;                 // RNBO attribute
        bool fMute;                     // DSP mute state
        static t_jrgba gDefaultColor;   // Color of the object to be used when restoring default color
        
        // Display the full DSP source text in a Max window
        void display_dsp_source();
        
        // Display the module parameters alongside their default values
        void display_dsp_params();
        
        // Compile the DSP with -svg and show the rendered control layout
        void display_svg();
        
        // Show the bundled PDF documentation inside Max
        void display_documentation();
        
        // List available Faust libraries in the Max window
        void display_libraries();
        
        // Create the Faust DSP instance (optionally initializing controllers)
        void create_dsp(bool init);
        
        // Release the current DSP and its adapters
        void free_dsp();
        
        // Mark the UI object as dirty so Max persists state
        void set_dirty();
        
        // Post a DSP status message to the Max console
        void dsp_status(const char* mess);
        
        // Ensure the audio chain is connected to the DAC before processing
        t_pxobject* check_dac();
        
        // Create the JSUI companion used for UI rendering
        void create_jsui();
        
        // Get or create the factory matching the requested DSP name
        bool allocate_factory(const std::string& effect_name);
        
        // Initialize controller values in the DSP UI
        void init_controllers();
        
        // Parse JSON text into a Max dictionary
        t_dictionary* json_reader(const char* jsontext);
    
    public:
        
        // Default constructor used when the class is instantiated internally
        faustgen()
        {
            faustgen(gensym("faustgen~"), NULL, NULL);
        }
        
        // Construct a faustgen~ object from a Max patcher instantiation
        faustgen(t_symbol* sym, long ac, t_atom* av);
        
        // Called upon deleting the object inside the patcher
        ~faustgen();
    
        // Replace the current Faust source code and trigger recompilation
        void update_sourcecode(const std::string& codebox = "");
    
        // Highlight compiler errors in the embedded editor
        void hilight_error(const std::string& error);
        
        // Called upon sending the object a message inside the max patcher
        // Allows to set a value to the Faust module's parameter
        void anything(long inlet, t_symbol* s, long ac, t_atom* av);
        
        // Update Faust compiler options from Max messages
        void compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        // Read Faust source from disk
        void read(long inlet, t_symbol* s);
        
        // Write the current Faust source to disk
        void write(long inlet, t_symbol* s);
        
        // Switch polyphony on or off with the requested number of voices
        void polyphony(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        // Initialize the DSP from a Max message
        void init(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        // Dump DSP metadata to the Max console
        void dump(long inlet, t_symbol* s, long argc, t_atom* argv);
    
        // Forward incoming MIDI messages to the Faust MIDI UI
        void midievent(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        // Configure or query OSC support
        void osc(long inlet, t_symbol* s, long argc, t_atom* argv);
    
        // Print input parameter names/types
        void dump_inputs();
        
        // Print output parameter names/types
        void dump_outputs();
        
        // Add a new library lookup path
        void librarypath(long inlet, t_symbol* s);
        
        // Mute or unmute DSP processing
        void mute(long inlet, long mute);
    
        // Return the number of channels exposed on a given outlet
        long multichanneloutputs(long outletindex);
        
        // Called when saving the Max patcher, this function saves the necessary
        // data inside the json file (faust sourcecode)
        void appendtodictionary(t_dictionary* d);
        
        // Restore saved source code and settings from a Max dictionary
        void getfromdictionary(t_dictionary* d);
        
        // Called when the user double-clicks on the faustgen object inside the Max patcher
        void dblclick(long inlet);
    
        // Display inlet/outlet help text in Max
        void assist(void* b, long msg, long a, char* dst);
        
        // Called when closing the text editor, calls for the creation of a new Faust module with the updated sourcecode
        void edclose(long inlet, char** text, long size);
        
        // Process the signal data with the Faust module
        void perform(int vs, t_sample** inputs, long numins, t_sample** outputs, long numouts);
    
        // Callback given to setupIO to set the sampling rate
        void init(double samplerate);
    
};

#endif
