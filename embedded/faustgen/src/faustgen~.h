/************************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2015 GRAME, Centre National de Creation Musicale
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


 ************************************************************************
 ************************************************************************/

#ifndef faustgen__h
#define faustgen__h

#define FAUSTFLOAT double
#define MSP64 1

/* link with  */
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <set> 
#include <vector> 
#include <map> 

#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MidiUI.h"
#include "maxcpp5.h"

#ifndef WIN32
#include <libgen.h>
#endif

#include "mspUI.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_drag.h"

#define DEFAULT_SOURCE_CODE "import(\"stdfaust.lib\");\nprocess=_,_;"
#define FAUSTGEN_VERSION "1.22"
#define FAUST_PDF_DOCUMENTATION "faust-quick-reference.pdf"
#define FAUST_PDF_LIBRARY "library.pdf"

#ifdef __APPLE__
    #include "faust/dsp/dsp-optimizer.h"
    #define FAUST_LIBRARY_PATH "/Contents/Resources/"
    #define FAUST_DRAW_PATH "/var/tmp/"
    #define SEPARATOR '/'
#endif

#ifdef WIN32
    #define FAUST_LIBRARY_PATH "\\faustgen-resources\\"
    #define FAUST_DRAW_PATH "\\faustgen-resources\\"
    #define SEPARATOR '\\'
#endif

#define LLVM_OPTIMIZATION -1  // means 'maximum'
#define DEFAULT_CODE "process = _,_;"

const char* TEXT_APPL_LIST[] = {"Atom", "Smultron", "TextWrangler", "TextExit", "" };

//===================
// Faust DSP Factory
//===================

class faustgen;

class faustgen_factory {

    typedef vector<string>::const_iterator StringVectorIt;
    friend class faustgen;

    private:
      
        set<faustgen*> fInstances;      // set of all DSP 
        llvm_dsp_factory* fDSPfactory;  // pointer to the LLVM Faust factory
        midi_handler fMidiHandler;      // Generic MIDI handler          
   
        long fSourceCodeSize;           // length of source code string
        char** fSourceCode;             // source code string
        
        long fBitCodeSize;              // length of the bitcode string
        char** fBitCode;                // bitcode string
        
        vector<string> fLibraryPath;    // path towards the Faust libraries
        string fDrawPath;               // path where to put SVG files
        
        vector<string> fOptions;        // options set in the 'compileoptions' message
                 
        int fFaustNumber;               // faustgen object's number inside the patcher
        
        string fName;                   // name of the DSP group
        string fJSON;                   // JSON
           
        t_systhread_mutex fDSPMutex;    // mutex to protect RT audio thread when recompiling DSP
     
        vector<string> fCompileOptions; // Faust compiler options
    
        int fOptLevel;                  // the LLVM optimization level
        bool fPolyphonic;               // Whether the created DSP is polyphonic
    
        short fDefaultPath;             // Default path to be saved in factory constructor (using path_getdefault)
                                        // and explicitely set in 'read' and 'write' (using path_setdefault)
    
        int m_siginlets;
        int m_sigoutlets;
        
        bool open_file(const char* file);
        bool open_file(const char* appl, const char* file);
        
        void add_library_path(const string& library_path);
        void add_compile_option(const string& key, const string& value);
        void add_compile_option(const string& value);
        void display_libraries_aux(const char* lib);
        void make_json(::dsp* dsp);
        
    public:
    
        faustgen_factory(const string& name);
        
        ~faustgen_factory();
            
        llvm_dsp_factory* create_factory_from_bitcode();
        llvm_dsp_factory* create_factory_from_sourcecode();
        ::dsp* create_dsp_aux();
     
        void free_dsp_factory();
        void free_sourcecode();
        void free_bitcode();
        
        void default_compile_options();
        void print_compile_options();
     
        void getfromdictionary(t_dictionary* d);
        void appendtodictionary(t_dictionary* d);
        
        int get_number() { return fFaustNumber; }
        string get_name() { return fName; }
        
        void read(long inlet, t_symbol* s);
        void write(long inlet, t_symbol* s);
        void librarypath(long inlet, t_symbol* s);
        
        char* get_sourcecode() { return *fSourceCode; }
        
        const char* get_json() { return fJSON.c_str(); }
        
        void update_sourcecode(int size, char* source_code);
        
        void compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv);
           
        // Compile DSP with -svg option and display the SVG files
        bool try_open_svg();
        void open_svg();
        void remove_svg();
        void display_svg();
        void display_pdf();
        void display_libraries();
        
        ::dsp* create_dsp_instance(int nvoices = 0);
        void add_instance(faustgen* dsp) { fInstances.insert(dsp); }
        void remove_instance(faustgen* dsp)  
        { 
            fInstances.erase(dsp); 
            
            // Last instance : remove factory from global table and commit suicide...
            if (fInstances.size() == 0) {
                gFactoryMap.erase(fName);
                delete this;
            }
        }
        
        bool try_lock() { return systhread_mutex_trylock(fDSPMutex) == MAX_ERR_NONE; }
        bool lock() { return systhread_mutex_lock(fDSPMutex) == MAX_ERR_NONE; }
        void unlock() { systhread_mutex_unlock(fDSPMutex); }
      
        static int gFaustCounter;       // global variable to count the number of faustgen objects inside the patcher
      
        static map<string, faustgen_factory*> gFactoryMap;
};

//====================
// Faust DSP Instance
//====================

class faustgen : public MspCpp5<faustgen> {

    friend class faustgen_factory;
    
    private:
    
        faustgen_factory* fDSPfactory;
        map<string, vector <t_object*> > fOutputTable;
        
        mspUI fDSPUI;               // DSP UI
        MidiUI* fMidiUI;            // Midi UI
        ::dsp* fDSP;                // pointer to the LLVM Faust dsp
        t_object* fEditor;          // text editor object
        bool fMute;                 // DSP mute state
        static t_jrgba gDefaultColor;  // Color of the object to be used when restoring default color
         
        // Display DSP text source
        void display_dsp_source();
         
        // Display the Faust module's parameters along with their standard values
        void display_dsp_params();
        
        // Compile DSP with -svg option and display the SVG files
        void display_svg();
        void display_pdf();
        void display_libraries();
         
        // Create the Faust LLVM based DSP
        void create_dsp(bool init);
        
        void free_dsp();
         
        void set_dirty();
        
        void dsp_status(const char* mess);
        t_pxobject* check_dac();
        void create_jsui();
        void update_outputs();
        
        bool allocate_factory(const string& effect_name);
        
        t_dictionary* json_reader(const char* jsontext);
    
        void add_midihandler();
        void remove_midihandler();
    
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
        void midievent(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        void librarypath(long inlet, t_symbol* s);
   
        void mute(long inlet, long mute);
         
        // Called when saving the Max patcher, this function saves the necessary 
        // data inside the json file (faust sourcecode)
        void appendtodictionary(t_dictionary* d);
        
        void getfromdictionary(t_dictionary* d);
     
        // Called when the user double-clicks on the faustgen object inside the Max patcher
        void dblclick(long inlet);
        
        // Called when closing the text editor, calls for the creation of a new Faust module with the updated sourcecode
        void edclose(long inlet, char** text, long size);
          
        // Process the signal data with the Faust module
        void perform(int vs, t_sample** inputs, long numins, t_sample** outputs, long numouts);
        
        void init(double samplerate);
       
};

#endif
