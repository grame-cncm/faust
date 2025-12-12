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

#ifndef faustgen_factory__h
#define faustgen_factory__h

//===================
// Faust DSP Factory
//===================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <mutex>
#include <map>

// FAUSTFLOAT is mandatory defined as double 
#define FAUSTFLOAT double

#define FAUSTGEN_VERSION "1.79"

// Possibly compile with Interp backend
// #define INTERP_BACKEND

#ifdef INTERP_BACKEND
#include <faust/dsp/interpreter-dsp.h>
#else
#include <faust/dsp/llvm-dsp.h>
#endif
#include <faust/dsp/dsp-adapter.h>
#include <faust/gui/SoundUI.h>

#include "maxcpp5.h"

#ifndef WIN32
#include <libgen.h>
#endif

#define DEFAULT_SOURCE_CODE "import(\"stdfaust.lib\");\nprocess=_,_;"
#define FAUST_PDF_DOCUMENTATION "faust-quick-reference.pdf"
#define FAUST_PDF_LIBRARY "library.pdf"

#ifdef __APPLE__
#include <faust/dsp/dsp-optimizer.h>
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
#define DEFAULT_CODE "process = 0,0;"

class faustgen;

class faustgen_factory {
    
        typedef std::vector<std::string>::const_iterator StringVectorIt;
        typedef std::set<std::string>::const_iterator StringSetIt;
        
        friend class faustgen;
        
    private:
    
        enum sampleFormat { kFloat, kDouble, kNone };
        
        std::set<faustgen*> fInstances; // Set of all DSP
        dsp_factory* fDSPfactory;       // Pointer to the LLVM Faust factory
        SoundUI* fSoundUI;              // Generic Soundfile interface
        
        long fSourceCodeSize;           // Length of source code string
        char** fSourceCode;             // Source code string
        
        long fBitCodeSize;              // Length of the bitcode string
        char** fBitCode;                // Bitcode string
        
        std::set<std::string> fLibraryPath;  // Path towards the Faust libraries
        std::string fResourcePath;           // Path of the resource folder
        std::string fDrawPath;               // Path where to put SVG files
        
        std::vector<std::string> fOptions;   // Options set in the 'compileoptions' message
        
        int fFaustNumber;               // faustgen object's number inside the patcher
        
        std::string fName;              // Name of the DSP group
        std::string fJSON;              // JSON
        
        std::recursive_mutex fAudioMutex;    // Mutex to protect RT audio thread when recompiling DSP
        std::recursive_mutex fUIMutex;       // Mutex to protect UI thread when recompiling DSP
    
        std::vector<std::string> fCompileOptions;   // Faust compiler options
        
        int fOptLevel;                  // LLVM optimization level
        sampleFormat fSampleFormat;     // Sample format in the LLVM module
        
        short fDefaultPath;             // Default path to be saved in factory constructor (using path_getdefault)
                                        // and explicitly set in 'read' and 'write' (using path_setdefault)
    
        int m_siginlets;
        int m_sigoutlets;
        
        // Open a resource from the default path list
        bool open_file(const char* file);
        
        // Open a resource relative to a given application bundle
        bool open_file(const char* appl, const char* file);
        
        // Add a new search path for Faust libraries
        void add_library_path(const std::string& library_path);
        
        // Add a named Faust compiler option
        void add_compile_option(const std::string& key, const std::string& value);
        
        // Add a standalone Faust compiler option
        void add_compile_option(const std::string& value);
        
        // Recursively print the content of a Faust library folder
        void display_libraries_aux(const char* lib);
        
        // Build the JSON UI description from a compiled DSP
        void make_json(::dsp* dsp);
    
        // Check whether a file has changed since last compilation
        bool is_new(t_filehandle file_handle, char* file_name);
        
        // Compile a Faust file located at the given Max path
        void compile_file(t_filehandle file_handle, short path, char* file_name);
    
        // Load library paths in the dictionary
        void load_library_paths(t_dictionary* d);
    
        // Load source code
        void load_source_code(t_dictionary* d);
    
        // Setup default Faust DSP code
        void default_source_code();
        
    public:
        
        // Create a factory bound to a named DSP group
        faustgen_factory(const std::string& name);
        
        // Destroy the factory and release its resources
        ~faustgen_factory();
        
        // Build an LLVM factory from stored bitcode
        dsp_factory* create_factory_from_bitcode();
        
        // Build an LLVM factory from stored source code
        dsp_factory* create_factory_from_sourcecode();
        
        // Create a DSP instance without applying multi-channel adapters
        ::dsp* create_dsp_aux();
        
        // Free the underlying LLVM factory
        void free_dsp_factory();
        
        // Release the stored source code buffer
        void free_sourcecode();
        
        // Release the stored bitcode buffer
        void free_bitcode();
    
        // Populate default Faust compiler options
        void default_compile_options();
        
        // Post current compile options to the Max console
        void print_compile_options();
        
        // Restore factory state from a Max dictionary
        void getfromdictionary(t_dictionary* d);
        
        // Save factory state into a Max dictionary
        void appendtodictionary(t_dictionary* d);
        
        // Return the instance number of this factory
        int get_number() { return fFaustNumber; }
        
        // Return the registered name of the DSP group
        std::string get_name() { return fName; }
    
        // Load source code from disk
        void read(long inlet, t_symbol* s);
        
        // Save source code to disk
        void write(long inlet, t_symbol* s);
    
        // Add a library path from a Max message
        void librarypath(long inlet, t_symbol* s);
        
        // Return the currently loaded source code (or an empty string)
        char* get_sourcecode()
        {
            static char empty = 0;
            return (fSourceCode) ? *fSourceCode : &empty;
        }
        
        // Return the cached JSON UI description
        const char* get_json() { return fJSON.c_str(); }
        
        // Replace the stored source code buffer
        void update_sourcecode(int size, char* source_code);
        
        // Update compile options received from Max
        void compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv);
        
        // Attempt to open an existing SVG rendering of the DSP
        bool try_open_svg();
        
        // Generate SVG files for the current DSP
        void open_svg();
        
        // Remove generated SVG files
        void remove_svg();
        
        // Compile DSP with -svg option and display the SVG files
        void display_svg();
        
        // Display the bundled Faust documentation
        void display_documentation();
        
        // List available Faust libraries
        void display_libraries();
        
        // Create a DSP instance, optionally polyphonic
        ::dsp* create_dsp_instance(int nvoices = 0);
        
        // Track a new faustgen instance using this factory
        void add_instance(faustgen* dsp) { fInstances.insert(dsp); }
        
        // Remove a faustgen instance and delete the factory if last one
        void remove_instance(faustgen* dsp)
        {
            fInstances.erase(dsp);
            
            // Last instance : remove factory from global table and commit suicide...
            if (fInstances.size() == 0) {
                gFactoryMap.erase(fName);
                delete this;
            }
        }
        // WARNING: remove_instance may delete the factory when the last client goes away.
        // Callers must not dereference the factory pointer after invoking it.
    
        // Mutex between the audio thread and the DSP creation thread
        // Attempt to grab the audio mutex without blocking
        bool try_lock_audio() { return fAudioMutex.try_lock(); }
        
        // Block until the audio mutex is acquired
        void lock_audio() { fAudioMutex.lock(); }
        
        // Release the audio mutex
        void unlock_audio() { fAudioMutex.unlock(); }
    
        // Mutex between the UI thread and the DSP creation thread
        // Block until the UI mutex is acquired
        void lock_ui() { fUIMutex.lock(); }
        
        // Release the UI mutex
        void unlock_ui() { fUIMutex.unlock(); }
    
        static int gFaustCounter; // Global variable to count the number of faustgen objects inside the patcher
        
        static std::map<std::string, faustgen_factory*> gFactoryMap;
};

// Report whether the build targets 32 or 64 bit pointers
inline const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

#endif
