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

#define FAUSTGEN_VERSION "1.72"

// Possibly compile with Interp backend
//#define INTERP_BACKEND

#include <faust/dsp/llvm-dsp.h>
#ifdef INTERP_BACKEND
#include <faust/dsp/interpreter-dsp.h>
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
        
        bool open_file(const char* file);
        bool open_file(const char* appl, const char* file);
        
        void add_library_path(const std::string& library_path);
        void add_compile_option(const std::string& key, const std::string& value);
        void add_compile_option(const std::string& value);
        void display_libraries_aux(const char* lib);
        void make_json(::dsp* dsp);
    
        bool is_new(t_filehandle file_handle, char* file_name);
        void compile_file(t_filehandle file_handle, short path, char* file_name);
        
    public:
        
        faustgen_factory(const std::string& name);
        ~faustgen_factory();
        
        dsp_factory* create_factory_from_bitcode();
        dsp_factory* create_factory_from_sourcecode();
        ::dsp* create_dsp_aux();
        
        void free_dsp_factory();
        void free_sourcecode();
        void free_bitcode();
    
        void default_compile_options();
        void print_compile_options();
        
        void getfromdictionary(t_dictionary* d);
        void appendtodictionary(t_dictionary* d);
        
        int get_number() { return fFaustNumber; }
        std::string get_name() { return fName; }
    
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
        void display_documentation();
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
    
        // Mutex between the audio thread and the DSP creation thread
        bool try_lock_audio() { return fAudioMutex.try_lock(); }
        void lock_audio() { fAudioMutex.lock(); }
        void unlock_audio() { fAudioMutex.unlock(); }
    
        // Mutex between the UI thread and the DSP creation thread
        void lock_ui() { fUIMutex.lock(); }
        void unlock_ui() { fUIMutex.unlock(); }
    
        static int gFaustCounter; // Global variable to count the number of faustgen objects inside the patcher
        
        static std::map<std::string, faustgen_factory*> gFactoryMap;
};

inline const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

#endif
