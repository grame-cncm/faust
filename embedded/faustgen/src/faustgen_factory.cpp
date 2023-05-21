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

#ifdef WIN32
#pragma warning (disable: 4244 4800 4267)
#define _CRT_SECURE_NO_WARNINGS
#else
#include <Carbon/Carbon.h>
#endif

#include "faustgen_factory.h"
#include "faustgen~.h"

#define LLVM_DSP

#include <faust/dsp/libfaust.h>
#include <faust/dsp/poly-dsp.h>

using namespace std;

const char* TEXT_APPL_LIST[] = {"Visual\\ Studio\\ Code", "Atom", "Smultron", "TextWrangler", "TextExit", "" };

// Globals
int faustgen_factory::gFaustCounter = 0;

//===================
// Faust DSP Factory
//===================

struct MyMeta : public Meta, public map<string, string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    const string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
};

struct FaustPluginMeta : public Meta
{
    FaustPluginMeta(::dsp* dsp)
    {
        dsp->metadata(this);
    }
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};

static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>

#if TARGET_CPU_ARM64
// Content of commonsyms.c, adding this code solves missing symbols issue.
t_common_symbols_table *_common_symbols = NULL;

void common_symbols_init(void)
{
    _common_symbols = common_symbols_gettable();
}
#endif

static string getTarget()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "" : "i386-apple-darwin10.6.0";
}

// Returns the serial number as a CFString.
// It is the caller's responsibility to release the returned CFString when done with it.
static string getSerialNumber()
{
    io_service_t platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice"));
    
    if (platformExpert) {
        CFTypeRef serialNumberAsCFString =
        IORegistryEntryCreateCFProperty(platformExpert,
                                        CFSTR(kIOPlatformSerialNumberKey),
                                        kCFAllocatorDefault, 0);
        if (serialNumberAsCFString) {
            char serial_name[256];
            CFStringGetCString((CFStringRef)serialNumberAsCFString, serial_name, 256, kCFStringEncodingMacRoman);
            string res = string(serial_name) + string(getCodeSize());
            CFRelease(serialNumberAsCFString);
            return res;
        }
        IOObjectRelease(platformExpert);
    }
    return "";
}

#else

static string getTarget() { return ""; }

static int getComputerName(char* computer_name, DWORD* computer_name_lg)
{
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     "SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName",
                     0, KEY_QUERY_VALUE, &hKey ) != ERROR_SUCCESS)
        return FALSE;
    if (RegQueryValueEx(hKey, "ComputerName", NULL, NULL,
                        (LPBYTE) computer_name,
                        (LPDWORD) computer_name_lg) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return FALSE;
    }
    RegCloseKey(hKey);
    return TRUE;
}

static string getSerialNumber()
{
    char serial_name[256] = "Default Windows name";
    DWORD name_lg = 256;
    if (getComputerName(serial_name, &name_lg) == TRUE) {
        return string(serial_name) + string(getCodeSize());
    } else {
        return "Windows";
    }
}

#endif

static string getFolderFromFilename(const string& full_path)
{
    size_t first = full_path.find_first_of(SEPARATOR);
    size_t last = full_path.find_last_of(SEPARATOR);
    return (first != string::npos && last != string::npos) ? full_path.substr(first, last - first) : "";
}

static string getFolderFromPath(const string& full_path)
{
    size_t first = full_path.find_first_of(SEPARATOR);
    return (first != string::npos) ? full_path.substr(first, full_path.size() - first) : "";
}

faustgen_factory::faustgen_factory(const string& name)
{
    m_siginlets = 0;
    m_sigoutlets = 0;
    
    fDefaultPath = path_getdefault();
    fName = name;
    fDSPfactory = nullptr;
    fBitCodeSize = 0;
    fBitCode = nullptr;
    fSourceCodeSize = 0;
    fSourceCode = nullptr;
    gFaustCounter++;
    fFaustNumber = gFaustCounter;
    fOptLevel = LLVM_OPTIMIZATION;
    fSoundUI = nullptr;
    fSampleFormat = kNone;
    
#ifdef __APPLE__
    // OSX only : access to the fautgen~ bundle
    CFBundleRef faustgen_bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.grame.faustgen-"));  // - character added since SDK 7.3.3
    CFURLRef faustgen_ref = CFBundleCopyBundleURL(faustgen_bundle);
    UInt8 bundle_path[512];
    Boolean res = CFURLGetFileSystemRepresentation(faustgen_ref, true, bundle_path, 512);
    assert(res);
    
    // Built the complete resource path
    fResourcePath = string((const char*)bundle_path) + string(FAUST_LIBRARY_PATH);
    fLibraryPath.insert(fResourcePath);
    
    // Draw path in temporary folder
    fDrawPath = string(FAUST_DRAW_PATH);
#endif
    
#ifdef WIN32
    HMODULE handle = LoadLibrary("faustgen~.mxe64");
    if (handle) {
        // Get faustgen~.mxe64 path
        char name[512];
        GetModuleFileName(handle, name, 512);
        string str_name = string(name);
        str_name = str_name.substr(0, str_name.find_last_of("\\"));
        // Built the complete resource path
        fResourcePath = string(str_name) + string(FAUST_LIBRARY_PATH);
        fLibraryPath.insert(fResourcePath);
        // Draw path in temporary folder
        TCHAR lpTempPathBuffer[MAX_PATH];
        // Gets the temp path env string (no guarantee it's a valid path).
        DWORD dwRetVal = GetTempPath(MAX_PATH, lpTempPathBuffer);
        if (dwRetVal > MAX_PATH || (dwRetVal == 0)) {
            post("GetTempPath failed...");
            // Try our value instead...
            fDrawPath = string(str_name) + string(FAUST_DRAW_PATH);
        } else {
            fDrawPath = string(lpTempPathBuffer);
        }
        FreeLibrary(handle);
    } else {
        post("Error : cannot locate faustgen~.mxe64...");
        fDrawPath = "";
    }
#endif
}

faustgen_factory::~faustgen_factory()
{
    free_dsp_factory();
    free_sourcecode();
    free_bitcode();
    
    remove_svg();
 
    delete fSoundUI;
    fSoundUI = nullptr;
}

void faustgen_factory::free_sourcecode()
{
    if (fSourceCode) {
        sysmem_freehandle(fSourceCode);
        fSourceCodeSize = 0;
        fSourceCode = nullptr;
    }
}

void faustgen_factory::free_bitcode()
{
    if (fBitCode) {
        sysmem_freehandle(fBitCode);
        fBitCodeSize = 0;
        fBitCode = nullptr;
    }
}

void faustgen_factory::free_dsp_factory()
{
    lock_audio();
    lock_ui();
    {
        // Free all instances
        for (const auto& it : fInstances) {
            it->free_dsp();
        }
        deleteDSPFactory(fDSPfactory);
        fDSPfactory = nullptr;
    }
    unlock_ui();
    unlock_audio();
}

llvm_dsp_factory* faustgen_factory::create_factory_from_bitcode()
{
    // Alternate model using machine code
    string error_msg;
    llvm_dsp_factory* factory = readDSPFactoryFromMachine(*fBitCode, getTarget(), error_msg);
    if (factory) {
        // Reset fSoundUI with the new factory getIncludePathnames
        delete fSoundUI;
        fSoundUI = new SoundUI(factory->getIncludePathnames(), -1, nullptr, true);
        /*
         vector<string> sound_directories = factory->getIncludePathnames();
         for (int i = 0; i < sound_directories.size(); i++) {
            post("sound_directories %d %s", i, sound_directories[i].c_str());
         }
        */
    } else {
        post("%s", error_msg.c_str());
    }
    return factory;
}

llvm_dsp_factory* faustgen_factory::create_factory_from_sourcecode()
{
    char name_app[64];
    snprintf(name_app, 64, "faustgen-%d", fFaustNumber);
    
    // To be sure we get a correct SVG diagram...
    remove_svg();
    
    default_compile_options();
    print_compile_options();
    
    // Prepare compile options
    string error_msg;
    const char* argv[64];
    
    assert(fCompileOptions.size() < 64);
    int i = 0;
    for (const auto& it : fCompileOptions) {
        argv[i++] = (char*)it.c_str();
    }
    argv[fCompileOptions.size()] = 0;  // NULL terminated argv
    
    // Generate SVG file
    if (!generateAuxFilesFromString(name_app, *fSourceCode, fCompileOptions.size(), argv, error_msg)) {
        post("Generate SVG error : %s", error_msg.c_str());
    }
    
    llvm_dsp_factory* factory = createDSPFactoryFromString(name_app, *fSourceCode, fCompileOptions.size(), argv, getTarget(), error_msg, fOptLevel);
    
    if (factory) {
        // Reset fSoundUI with the new factory getIncludePathnames
        delete fSoundUI;
        fSoundUI = new SoundUI(factory->getIncludePathnames(), -1, nullptr, true);
        /*
         std::vector<std::string> sound_directories = factory->getIncludePathnames();
         for (int i = 0; i < sound_directories.size(); i++) {
            post("sound_directories %d %s", i, sound_directories[i].c_str());
         }
        */
        return factory;
    } else {
        // Update all instances
        for (const auto& it : fInstances) {
            //it->hilight_on();
        }
        if (fInstances.begin() != fInstances.end()) {
            (*fInstances.begin())->hilight_error(error_msg);
        }
        post("Invalid Faust code or compile options : %s", error_msg.c_str());
        return 0;
    }
}

::dsp* faustgen_factory::create_dsp_instance(int nvoices)
{
    ::dsp* dsp = fDSPfactory->createDSPInstance();
    
    // Check 'nvoices' metadata
    if (nvoices == 0) {
        MyMeta meta;
        dsp->metadata(&meta);
        std::string numVoices = meta.get("nvoices", "0");
        nvoices = atoi(numVoices.c_str());
        if (nvoices < 0) nvoices = 0;
    }
    
    // Add the sample size if needed
    if (fSampleFormat == kFloat) {
        dsp = new dsp_sample_adapter<float, double>(dsp);
    }
    
    // Possibly create polyphonic DSP
    if (nvoices > 0) {
        dsp = new mydsp_poly(dsp, nvoices, true);
    }
    
    return dsp;
}

::dsp* faustgen_factory::create_dsp_aux()
{
    ::dsp* dsp = nullptr;
    string error;
    
    // Factory already allocated
    if (fDSPfactory) {
        dsp = create_dsp_instance();
        post("Factory already allocated, %i input(s), %i output(s)", dsp->getNumInputs(), dsp->getNumOutputs());
        goto end;
    }
    
    // Tries to create from bitcode
    if (fBitCodeSize > 0) {
        fDSPfactory = create_factory_from_bitcode();
        if (fDSPfactory) {
            dsp = create_dsp_instance();
            FaustPluginMeta meta(dsp);
            post("Compilation from bitcode succeeded, %i input(s), %i output(s)", dsp->getNumInputs(), dsp->getNumOutputs());
            goto end;
        } else {
            post("Compilation from bitcode failed...");
        }
    }
    
    // Otherwise tries to create from source code
    if (fSourceCodeSize > 0) {
        fDSPfactory = create_factory_from_sourcecode();
        if (fDSPfactory) {
            dsp = create_dsp_instance();
            FaustPluginMeta meta(dsp);
            post("Compilation from source code succeeded, %i input(s), %i output(s)", dsp->getNumInputs(), dsp->getNumOutputs());
            goto end;
        } else {
            post("Compilation from source code failed...");
        }
    }
    
    // Otherwise creates default DSP keeping the same input/output number
    fDSPfactory = createDSPFactoryFromString("default", DEFAULT_CODE, 0, 0, getTarget(), error, 0);
    dsp = create_dsp_instance();
    post("Allocation of default DSP succeeded, %i input(s), %i output(s)", dsp->getNumInputs(), dsp->getNumOutputs());
    
end:
    assert(dsp);
    m_siginlets = dsp->getNumInputs();
    m_sigoutlets = dsp->getNumOutputs();
    
    // Prepare JSON
    make_json(dsp);
    return dsp;
}

void faustgen_factory::make_json(::dsp* dsp)
{
    // Prepare JSON
    JSONUI builder(m_siginlets, m_sigoutlets);
    dsp->buildUserInterface(&builder);
    dsp->metadata(&builder);
    fJSON = builder.JSON();
}

void faustgen_factory::add_library_path(const string& library_path)
{
    fLibraryPath.insert(library_path);
}

void faustgen_factory::add_compile_option(const string& key, const string& value)
{
    if ((key != "") && (value != "")) {
        fCompileOptions.push_back(key);
        fCompileOptions.push_back(value);
    }
}

void faustgen_factory::add_compile_option(const string& value)
{
    if (value != "") {
        fCompileOptions.push_back(value);
    }
}

void faustgen_factory::print_compile_options()
{
    if (fCompileOptions.size() > 0) {
        post("-----------------------------");
        for (const auto& it : fCompileOptions) {
            post("Compile option = %s", it.c_str());
        }
        post("-----------------------------");
    }
}

void faustgen_factory::default_compile_options()
{
    // Clear and set default value
    fCompileOptions.clear();
    fSampleFormat = kNone;
    
    // Add -svg to current compile options
    add_compile_option("-svg");
    
    // All library paths
    for (const auto& it1 : fLibraryPath) {
        add_compile_option("-I", it1);
    }
    
    // Draw path
    add_compile_option("-O", fDrawPath);
    
    // All options set in the 'compileoptions' message
    StringVectorIt it;
    for (it = fOptions.begin(); it != fOptions.end(); it++) {
        // '-opt v' : parsed for LLVM optimization level
        if (*it == "-opt") {
            it++;
            fOptLevel = atoi((*it).c_str());
        } else if (*it == "-single") {
            fSampleFormat = kFloat;
            add_compile_option(*it);
        } else if (*it == "-double") {
            fSampleFormat = kDouble;
            add_compile_option(*it);
        } else {
            add_compile_option(*it);
        }
    }
    
    // By defaut -double is used
    if (fSampleFormat == kNone) {
        fSampleFormat = kDouble;
        add_compile_option("-double");
    }
  
    // Vector mode by default
    /*
     add_compile_option("-vec");
     add_compile_option("-lv");
     add_compile_option("1");
     */
    /*
     Seems not necessary...
     fCompileOptions.push_back("-vs");
     stringstream num;
     num << sys_getblksize();
     add_compile_option(num.str());
     */
}

void faustgen_factory::getfromdictionary(t_dictionary* d)
{
    // Read machine serial number
    const char* serial_number;
    t_max_err err = dictionary_getstring(d, gensym("serial_number"), &serial_number);
    if ((err != MAX_ERR_NONE) || (strcmp(serial_number, getSerialNumber().c_str()) != 0)) {
        post("Patch compiled on another machine or another CPU architecture, so ignore bitcode, force recompilation and use default compileoptions");
        goto read_sourcecode;
    }
    
    // Read sourcecode "version" key
    const char* faustgen_version;
    err = dictionary_getstring(d, gensym("version"), &faustgen_version);
    
    // Read fSampleFormat version
    err = dictionary_getlong(d, gensym("sample_format"), (t_atom_long*)&fSampleFormat);
    
    if (err != MAX_ERR_NONE) {
        post("Cannot read \"version\" key, so ignore bitcode, force recompilation and use default compileoptions");
        goto read_sourcecode;
    } else if (strcmp(faustgen_version, FAUSTGEN_VERSION) != 0) {
        post("Older version of faustgen~ (%s versus %s), so ignore bitcode, force recompilation and use default compileoptions", FAUSTGEN_VERSION, faustgen_version);
        goto read_sourcecode;
    }
    
    // Read bitcode size key
    err = dictionary_getlong(d, gensym("machinecode_size"), (t_atom_long*)&fBitCodeSize);
    if (err != MAX_ERR_NONE) {
        fBitCodeSize = 0;
        goto read_sourcecode;
    }
    
    // If OK read bitcode
    fBitCode = sysmem_newhandleclear(fBitCodeSize + 1);             // We need to use a size larger by one for the null terminator
    const char* bitcode;
    err = dictionary_getstring(d, gensym("machinecode"), &bitcode); // The retrieved pointer references the string in the dictionary, it is not a copy.
    sysmem_copyptr(bitcode, *fBitCode, fBitCodeSize);
    if (err != MAX_ERR_NONE) {
        fBitCodeSize = 0;
    }
    
read_sourcecode:
    // Load fLibraryPath
    int i = 0;
    const char* read_library_path;
    char library_path[32];
    
loop:
    snprintf(library_path, 32, "library_path%d", i++);
    err = dictionary_getstring(d, gensym(library_path), &read_library_path);
    if (err == MAX_ERR_NONE) {
        fLibraryPath.insert(read_library_path);
        goto loop;
    }
    
    // Read sourcecode size key
    err = dictionary_getlong(d, gensym("sourcecode_size"), (t_atom_long*)&fSourceCodeSize);
    if (err != MAX_ERR_NONE) {
        goto default_sourcecode;
    }
    
    // If OK read sourcecode
    fSourceCode = sysmem_newhandleclear(fSourceCodeSize + 1);           // We need to use a size larger by one for the null terminator
    const char* sourcecode;
    err = dictionary_getstring(d, gensym("sourcecode"), &sourcecode);   // The retrieved pointer references the string in the dictionary, it is not a copy.
    sysmem_copyptr(sourcecode, *fSourceCode, fSourceCodeSize);
    if (err == MAX_ERR_NONE) {
        return;
    }
    
default_sourcecode:
    // Otherwise tries to create from default source code
    fSourceCodeSize = strlen(DEFAULT_SOURCE_CODE);
    fSourceCode = sysmem_newhandleclear(fSourceCodeSize + 1);
    sysmem_copyptr(DEFAULT_SOURCE_CODE, *fSourceCode, fSourceCodeSize);
}

// Called when saving the Max patcher
// This function saves the necessary data inside the JSON file (Faust sourcecode)
void faustgen_factory::appendtodictionary(t_dictionary* d)
{
    post("Saving object version, library_path, sourcecode and bitcode...");
    
    // Write machine serial number
    dictionary_appendstring(d, gensym("serial_number"), getSerialNumber().c_str());
    
    // Write faustgen~ version
    dictionary_appendstring(d, gensym("version"), FAUSTGEN_VERSION);
    
    // Write fSampleFormat version
    dictionary_appendlong(d, gensym("sample_format"), fSampleFormat);
    
    // Write fLibraryPath
    int i = 0;
    for (const auto &it : fLibraryPath) {
        char library_path[32];
        snprintf(library_path, 32, "library_path%d", i++);
        dictionary_appendstring(d, gensym(library_path), it.c_str());
    }
    
    // Write source code
    if (fSourceCodeSize) {
        dictionary_appendlong(d, gensym("sourcecode_size"), fSourceCodeSize);
        dictionary_appendstring(d, gensym("sourcecode"), *fSourceCode);
    }
    
    // Write bitcode
    if (fDSPfactory) {
        // Alternate model using machine code
        string machinecode = writeDSPFactoryToMachine(fDSPfactory, getTarget());
        dictionary_appendlong(d, gensym("machinecode_size"), machinecode.size());
        dictionary_appendstring(d, gensym("machinecode"), machinecode.c_str());
    }
}

bool faustgen_factory::try_open_svg()
{
    // Open the svg diagram file inside a web browser
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "type \"file:///%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    snprintf(command, 512, "open \"file://%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#endif
    return (system(command) == 0);
}

void faustgen_factory::open_svg()
{
    // Open the svg diagram file inside a web browser
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "start \"\" \"file:///%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    snprintf(command, 512, "open \"file://%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#endif
    system(command);
}

void faustgen_factory::remove_svg()
{
    // Possibly done by "compileoptions" or display_svg
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "rmdir /S/Q \"%sfaustgen-%d-svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    snprintf(command, 512, "rm -r \"%sfaustgen-%d-svg\"", fDrawPath.c_str(), fFaustNumber);
#endif
    system(command);
}

void faustgen_factory::display_svg()
{
    // Try to open SVG svg diagram file inside a web browser
    if (!try_open_svg()) {
        
        post("SVG diagram not available, recompile to produce it");
        
        // Force recompilation to produce it
        llvm_dsp_factory* factory = create_factory_from_sourcecode();
        deleteDSPFactory(factory);
        
        // Open the SVG diagram file inside a web browser
        open_svg();
    }
}

bool faustgen_factory::open_file(const char* file)
{
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "start \"\" \"%s%s\"", (*fLibraryPath.begin()).c_str(), file);
#else
    snprintf(command, 512, "open \"%s%s\"", (*fLibraryPath.begin()).c_str(), file);
#endif
    post(command);
    return (system(command) == 0);
}

bool faustgen_factory::open_file(const char* appl, const char* file)
{
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "start \"\" %s \"%s%s\"", appl, (*fLibraryPath.begin()).c_str(), file);
#else
    snprintf(command, 512, "open -a %s \"%s%s\"", appl, (*fLibraryPath.begin()).c_str(), file);
#endif
    return (system(command) == 0);
}

void faustgen_factory::display_documentation()
{
    // Open the Web documentation
    char command[512];
#ifdef WIN32
    snprintf(command, 512, "start \"\" \"https://faustdoc.grame.fr/manual/introduction\"");
#else
    snprintf(command, 512, "open \"https://faustdoc.grame.fr/manual/introduction\"");
#endif
    system(command);
}

void faustgen_factory::display_libraries_aux(const char* lib)
{
    const char* appl;
    int i = 0;
    
    while ((appl = TEXT_APPL_LIST[i++]) && (strcmp(appl, "") != 0)) {
        if (open_file(appl, lib)) {
            break;
        }
    }
}

void faustgen_factory::display_libraries()
{
    // Open the libraries
#ifdef WIN32
    open_file(FAUST_PDF_LIBRARY);
    open_file("all.lib");
    open_file("aanl.lib");
    open_file("analyzers.lib");
    open_file("basics.lib");
    open_file("compressors.lib");
    open_file("delays.lib");
    open_file("demos.lib");
    open_file("double.lib");
    open_file("dx7.lib");
    open_file("envelopes.lib");
    open_file("filters.lib");
    open_file("fds.lib");
    open_file("hoa.lib");
    open_file("instruments.lib");
    open_file("interpolators.lib");
    open_file("maths.lib");
    open_file("maxmsp.lib");
    open_file("mi.lib");
    open_file("misceffects.lib");
    open_file("noises.lib");
    open_file("oscillators.lib");
    open_file("phaflangers.lib");
    open_file("physmodels.lib");
    open_file("platform.lib");
    open_file("quantizers.lib");
    open_file("reducemaps.lib");
    open_file("reverbs.lib");
    open_file("routes.lib");
    open_file("runtime.lib");
    open_file("sf.lib");
    open_file("signals.lib");
    open_file("soundfiles.lib");
    open_file("spats.lib");
    open_file("stdfaust.lib");
    open_file("synths.lib");
    open_file("tonestacks.lib");
    open_file("tubes.lib");
    open_file("vaeffects.lib");
    open_file("version.lib");
    open_file("wdmodels.lib");
    open_file("webaudio.lib");
#else
    display_libraries_aux("all.lib");
    display_libraries_aux("aanl.lib");
    display_libraries_aux("analyzers.lib");
    display_libraries_aux("basics.lib");
    display_libraries_aux("compressors.lib");
    display_libraries_aux("delays.lib");
    display_libraries_aux("demos.lib");
    display_libraries_aux("double.lib");
    display_libraries_aux("dx7.lib");
    display_libraries_aux("envelopes.lib");
    display_libraries_aux("filters.lib");
    display_libraries_aux("fds.lib");
    display_libraries_aux("hoa.lib");
    display_libraries_aux("instruments.lib");
    display_libraries_aux("interpolators.lib");
    display_libraries_aux("maths.lib");
    display_libraries_aux("maxmsp.lib");
    display_libraries_aux("mi.lib");
    display_libraries_aux("misceffects.lib");
    display_libraries_aux("noises.lib");
    display_libraries_aux("oscillators.lib");
    display_libraries_aux("phaflangers.lib");
    display_libraries_aux("physmodels.lib");
    display_libraries_aux("platform.lib");
    display_libraries_aux("quantizers.lib");
    display_libraries_aux("reducemaps.lib");
    display_libraries_aux("reverbs.lib");
    display_libraries_aux("routes.lib");
    display_libraries_aux("runtime.lib");
    display_libraries_aux("sf.lib");
    display_libraries_aux("signals.lib");
    display_libraries_aux("soundfiles.lib");
    display_libraries_aux("spats.lib");
    display_libraries_aux("stdfaust.lib");
    display_libraries_aux("synths.lib");
    display_libraries_aux("tonestacks.lib");
    display_libraries_aux("tubes.lib");
    display_libraries_aux("vaeffects.lib");
    display_libraries_aux("version.lib");
    display_libraries_aux("wdmodels.lib");
    display_libraries_aux("webaudio.lib");
#endif
}

void faustgen_factory::update_sourcecode(int size, char* source_code)
{
    // Recompile only if text has been changed
    if (strcmp(source_code, *fSourceCode) != 0) {
        
        // Update all instances
        for (const auto& it : fInstances) {
            //it->hilight_off();
        }
        
        // Delete the existing Faust module
        free_dsp_factory();
        
        // Free the memory allocated for fSourceCode
        free_sourcecode();
        
        // Free the memory allocated for fBitCode
        free_bitcode();
        
        // Allocate the right memory for fSourceCode
        fSourceCode = sysmem_newhandleclear(size + 1);
        sysmem_copyptr(source_code, *fSourceCode, size);
        fSourceCodeSize = size;
        
        // Update all instances
        for (const auto& it : fInstances) {
            it->update_sourcecode();
        }
        
    } else {
        post("DSP code has not been changed...");
    }
}

void faustgen_factory::librarypath(long inlet, t_symbol* s)
{
    if (s == gensym("")) {
        fLibraryPath.clear();
        // fResourcePath has to stay
        fLibraryPath.insert(fResourcePath);
    } else {
        add_library_path(getFolderFromPath(s->s_name));
    }
}

bool faustgen_factory::is_new(t_filehandle file_handle, char* file_name)
{
    char** texthandle = sysmem_newhandle(0);
    t_max_err err = sysfile_readtextfile(file_handle, texthandle, 0, (t_sysfile_text_flags)(TEXT_LB_UNIX | TEXT_NULL_TERMINATE));
    
    bool res;
    if (err) {
        post("Faust DSP file '%s' cannot be read", file_name);
        res = false;
    } else {
        res = (generateSHA1(*texthandle) != generateSHA1(get_sourcecode()));
    }
    // Reset file at beginning
    sysfile_setpos(file_handle, SYSFILE_FROMSTART, 0);
    sysmem_freehandle(texthandle);
    return res;
}

void faustgen_factory::compile_file(t_filehandle file_handle, short path, char* file_name)
{
    // Delete the existing Faust module
    free_dsp_factory();
    
    // Free the memory allocated for fBitCode
    free_bitcode();
    
    // Always works here since 'is_new_file' returned true
    sysfile_readtextfile(file_handle, fSourceCode, 0, (t_sysfile_text_flags)(TEXT_LB_UNIX | TEXT_NULL_TERMINATE));
    sysfile_setpos(file_handle, SYSFILE_FROMSTART, 0);
    
    fSourceCodeSize = sysmem_handlesize(fSourceCode);
    
    // Add DSP file enclosing folder pathname in the '-I' list
    char full_path[MAX_FILENAME_CHARS];
    t_max_err err;
    if ((err = path_topathname(path, file_name, full_path)) == 0) {
        add_library_path(getFolderFromFilename(full_path));
    } else {
        post("path_topathname %s err = %d", file_name, err);
    }
    
    // Update all instances
    for (const auto& it : fInstances) {
        it->update_sourcecode();
    }
}

void faustgen_factory::read(long inlet, t_symbol* s)
{
    long type = 'TEXT';
    t_filehandle file_handle;
    char file_name[MAX_FILENAME_CHARS];
    short path;
    
    // No filename, so open load dialog
    if (s == gensym("")) {
        file_name[0] = 0;
        if (open_dialog(file_name, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file not found");
            return;
        }
        // Otherwise locate the file
    } else {
        strncpy_zero(file_name, s->s_name, MAX_FILENAME_CHARS);
        // Set default path with saved value
        path_setdefault(fDefaultPath, 0);
        if (locatefile_extended(file_name, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file '%s' not found", file_name);
            return;
        }
    }
    
    // File found, open it and recompile DSP
    t_max_err err = path_opensysfile(file_name, path, &file_handle, READ_PERM);
    if (err) {
        post("Faust DSP file '%s' cannot be opened", file_name);
    } else if (is_new(file_handle, file_name)) {
        compile_file(file_handle, path, file_name);
    }
    
    sysfile_close(file_handle);
}

void faustgen_factory::write(long inlet, t_symbol* s)
{
    char file_name[MAX_FILENAME_CHARS];
    short path = 0;
    long type = 'TEXT';
    t_max_err err;
    t_filehandle file_handle;
    
    // No filename, so open save dialog
    if (s == gensym("")) {
        file_name[0] = 0;
        if (saveas_dialog(file_name, &path, NULL)) {
            post("Faust DSP file not found");
            return;
        } else {
            err = path_createsysfile(file_name, path, type, &file_handle);
            if (err) {
                post("Faust DSP file '%s' cannot be created", file_name);
                return;
            }
        }
        // Otherwise locate or create the file
    } else {
        strncpy_zero(file_name, s->s_name, MAX_FILENAME_CHARS);
        // Set default path with saved value
        path_setdefault(fDefaultPath, 0);
        if (locatefile_extended(file_name, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file '%s' not found, so tries to create it", file_name);
            err = path_createsysfile(file_name, path, type, &file_handle);
            if (err) {
                post("Faust DSP file '%s' cannot be created", file_name);
                return;
            }
        } else {
            err = path_opensysfile(file_name, path, &file_handle, WRITE_PERM);
            if (err) {
                post("Faust DSP file '%s' cannot be opened", file_name);
                return;
            }
        }
    }
    
    err = sysfile_writetextfile(file_handle, fSourceCode, (t_sysfile_text_flags)(TEXT_LB_UNIX | TEXT_NULL_TERMINATE));
    if (err) {
        post("Faust DSP file '%s' cannot be written", file_name);
    }
    sysfile_close(file_handle);
}

void faustgen_factory::compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv)
{
    post("Compiler options modified for faustgen");
    
    if (argc == 0) {
        post("No argument entered, no additional compilation option will be used");
    }
    
    // Clear options
    fOptions.clear();
    int i;
    t_atom* ap;
    bool compilation = true;
    
    // Increment ap each time to get to the next atom
    for (i = 0, ap = argv; i < argc; i++, ap++) {
        switch (atom_gettype(ap)) {
                
            case A_LONG: {
                fOptions.push_back(to_string(atom_getlong(ap)).c_str());
                break;
            }
                
            case A_FLOAT:
                post("Invalid compiler option argument - float");
                break;
                
            case A_SYM:
                // Check compilation mode
                if (strcmp(atom_getsym(ap)->s_name, "nc") == 0) {
                    compilation = false;
                } else {
                    // Add options to default ones
                    fOptions.push_back(atom_getsym(ap)->s_name);
                }
                break;
                
            default:
                post("Invalid compiler option argument - unknown");
                break;
        }
    }
   
    if (compilation) {
        // Delete the existing Faust module
        free_dsp_factory();
        
        // Free the memory allocated for fBitCode
        free_bitcode();
        
        // Update all instances
        for (const auto& it : fInstances) {
            it->update_sourcecode();
        }
    }
}