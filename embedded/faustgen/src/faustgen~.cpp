/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2019 GRAME, Centre National de Creation Musicale
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

#include "faustgen~.h"
#include "faust/dsp/libfaust.h"

#define LLVM_DSP
#include "faust/dsp/poly-dsp.h"

int faustgen_factory::gFaustCounter = 0;
map<string, faustgen_factory*> faustgen_factory::gFactoryMap;
t_jrgba faustgen::gDefaultColor = {-1., -1., -1., -1.};

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

//===================
// Faust DSP Factory
//===================

struct MyMeta : public Meta, public std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    const std::string get(const char* key, const char* def)
    {
        if (this->find(key) != this->end()) {
            return (*this)[key];
        } else {
            return def;
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

static string getFolderFromFilename(const string& fullpath)
{
    size_t first = fullpath.find_first_of(SEPARATOR);
    size_t last = fullpath.find_last_of(SEPARATOR);
    return (first != string::npos && last != string::npos) ? fullpath.substr(first, last - first) : "";
}

static string getFolderFromPath(const string& fullpath)
{
    size_t first = fullpath.find_first_of(SEPARATOR);
    return (first != string::npos) ? fullpath.substr(first, fullpath.size() - first) : "";
}

struct Max_Meta : public Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};

faustgen_factory::faustgen_factory(const string& name)
{
    m_siginlets = 0;
    m_sigoutlets = 0;
    
    fDefaultPath = path_getdefault();
    fName = name;
    fDSPfactory = NULL;
    fBitCodeSize = 0;
    fBitCode = NULL;
    fSourceCodeSize = 0;
    fSourceCode = NULL;
    gFaustCounter++;
    fFaustNumber = gFaustCounter;
    fOptLevel = LLVM_OPTIMIZATION;
    fPolyphonic = false;
    fSoundUI = NULL;
    
    fMidiHandler.startMidi();
    
#ifdef __APPLE__
    // OSX only : access to the fautgen~ bundle
    CFBundleRef faustgen_bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.grame.faustgen-"));  // - character added since SDK 7.3.3
    CFURLRef faustgen_ref = CFBundleCopyBundleURL(faustgen_bundle);
    UInt8 bundle_path[512];
    Boolean res = CFURLGetFileSystemRepresentation(faustgen_ref, true, bundle_path, 512);
    assert(res);
    
    // Built the complete resource path
    fLibraryPath.insert(string((const char*)bundle_path) + string(FAUST_LIBRARY_PATH));
    
    // Draw path in temporary folder
    fDrawPath = string(FAUST_DRAW_PATH);
#endif
    
#ifdef WIN32
    HMODULE handle = LoadLibrary("faustgen~.mxe64");
    if (handle) {
        // Get faustgen~.mxe path
        char name[512];
        GetModuleFileName(handle, name, 512);
        string str_name = string(name);
        str_name = str_name.substr(0, str_name.find_last_of("\\"));
        // Built the complete resource path
        fLibraryPath.insert(string(str_name) + string(FAUST_LIBRARY_PATH));
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
    
    t_max_err err = systhread_mutex_new(&fDSPMutex, SYSTHREAD_MUTEX_NORMAL);
    if (err != MAX_ERR_NONE) {
        post("Cannot allocate mutex...");
    }
}

faustgen_factory::~faustgen_factory()
{
    free_dsp_factory();
    free_sourcecode();
    free_bitcode();
    
    fMidiHandler.stopMidi();
    
    remove_svg();
    systhread_mutex_free(fDSPMutex);
    
    delete fSoundUI;
    fSoundUI = NULL;
}

void faustgen_factory::free_sourcecode()
{
    if (fSourceCode) {
        sysmem_freehandle(fSourceCode);
        fSourceCodeSize = 0;
        fSourceCode = NULL;
    }
}

void faustgen_factory::free_bitcode()
{
    if (fBitCode) {
        sysmem_freehandle(fBitCode);
        fBitCodeSize = 0;
        fBitCode = NULL;
    }
}

void faustgen_factory::free_dsp_factory()
{
    if (lock()) {
        // Free all instances
        for (auto& it : fInstances) {
            it->free_dsp();
        }
        
        //deleteDSPFactory(fDSPfactory);
        fDSPfactory = NULL;
        unlock();
    } else {
        post("Mutex lock cannot be taken...");
    }
}

llvm_dsp_factory* faustgen_factory::create_factory_from_bitcode()
{
    // Alternate model using machine code
    string error_msg;
    llvm_dsp_factory* factory = readDSPFactoryFromMachine(*fBitCode, getTarget(), error_msg);
    if (factory) {
        // Reset fSoundUI with the new factory getIncludePathnames
        delete fSoundUI;
        fSoundUI = new SoundUI(factory->getIncludePathnames());
        /*
         std::vector<std::string> sound_directories = factory->getIncludePathnames();
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
    sprintf(name_app, "faustgen-%d", fFaustNumber);
    
    // To be sure we get a correct SVG diagram...
    remove_svg();
    
    default_compile_options();
    print_compile_options();
    
    // Prepare compile options
    string error_msg;
    const char* argv[64];
    
    assert(fCompileOptions.size() < 64);
    StringVectorIt it;
    int i = 0;
    for (it = fCompileOptions.begin(); it != fCompileOptions.end(); it++) {
        argv[i++] = (char*)(*it).c_str();
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
        fSoundUI = new SoundUI(factory->getIncludePathnames());
        /*
         std::vector<std::string> sound_directories = factory->getIncludePathnames();
         for (int i= 0; i < sound_directories.size(); i++) {
            post("sound_directories %d %s", i, sound_directories[i].c_str());
         }
         */
        return factory;
    } else {
        // Update all instances
        for (auto& it : fInstances) {
            it->hilight_on();
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
    ::dsp* mono = fDSPfactory->createDSPInstance();
    
    // Check 'nvoices' metadata
    if (nvoices == 0) {
        MyMeta meta;
        mono->metadata(&meta);
        std::string numVoices = meta.get("nvoices", "0");
        nvoices = atoi(numVoices.c_str());
        if (nvoices < 0) nvoices = 0;
    }
    
    if (nvoices > 0) {
        fPolyphonic = true;
        return new mydsp_poly(mono, nvoices, true);
    } else {
        fPolyphonic = false;
        return mono;
    }
}

::dsp* faustgen_factory::create_dsp_aux()
{
    ::dsp* dsp = 0;
    Max_Meta meta;
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
            dsp->metadata(&meta);
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
            dsp->metadata(&meta);
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
        StringVectorIt it;
        for (it = fCompileOptions.begin(); it != fCompileOptions.end(); it++) {
            post("Compile option = %s", (*it).c_str());
        }
        post("-----------------------------");
    }
}

void faustgen_factory::default_compile_options()
{
    // Clear and set default value
    fCompileOptions.clear();
    
    // By default when double
    if (sizeof(FAUSTFLOAT) == 8) {
        add_compile_option("-double");
    }
    
    // Add -svg to current compile options
    add_compile_option("-svg");
    
    // All library paths
    StringSetIt it1;
    for (it1 = fLibraryPath.begin(); it1 != fLibraryPath.end(); it1++) {
        add_compile_option("-I", *it1);
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
        } else {
            add_compile_option(*it);
        }
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
    if (err != MAX_ERR_NONE || strcmp(serial_number, getSerialNumber().c_str()) != 0) {
        post("Patch compiled on another machine or another CPU architecture, so ignore bitcode, force recompilation and use default compileoptions");
        goto read_sourcecode;
    }
    
    // Read sourcecode "version" key
    const char* faustgen_version;
    err = dictionary_getstring(d, gensym("version"), &faustgen_version);
    
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
    
    // Save machine serial number
    dictionary_appendstring(d, gensym("serial_number"), getSerialNumber().c_str());
    
    // Save faustgen~ version
    dictionary_appendstring(d, gensym("version"), FAUSTGEN_VERSION);
    
    // Save fLibraryPath
    StringSetIt it;
    int i = 0;
    for (it = fLibraryPath.begin(); it != fLibraryPath.end(); it++) {
        char library_path[32];
        snprintf(library_path, 32, "library_path%d", i++);
        dictionary_appendstring(d, gensym(library_path), (*it).c_str());
    }
    
    // Save source code
    if (fSourceCodeSize) {
        dictionary_appendlong(d, gensym("sourcecode_size"), fSourceCodeSize);
        dictionary_appendstring(d, gensym("sourcecode"), *fSourceCode);
    }
    
    // Save bitcode
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
    sprintf(command, "type \"file:///%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    sprintf(command, "open \"file://%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#endif
    return (system(command) == 0);
}

void faustgen_factory::open_svg()
{
    // Open the svg diagram file inside a web browser
    char command[512];
#ifdef WIN32
    sprintf(command, "start \"\" \"file:///%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    sprintf(command, "open \"file://%sfaustgen-%d-svg/process.svg\"", fDrawPath.c_str(), fFaustNumber);
#endif
    system(command);
}

void faustgen_factory::remove_svg()
{
    // Possibly done by "compileoptions" or display_svg
    char command[512];
#ifdef WIN32
    sprintf(command, "rmdir /S/Q \"%sfaustgen-%d-svg\"", fDrawPath.c_str(), fFaustNumber);
#else
    sprintf(command, "rm -r \"%sfaustgen-%d-svg\"", fDrawPath.c_str(), fFaustNumber);
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
        //deleteDSPFactory(factory);
        
        // Open the SVG diagram file inside a web browser
        open_svg();
    }
}

bool faustgen_factory::open_file(const char* file)
{
    char command[512];
#ifdef WIN32
    sprintf(command, "start \"\" \"%s%s\"", (*fLibraryPath.begin()).c_str(), file);
#else
    sprintf(command, "open \"%s%s\"", (*fLibraryPath.begin()).c_str(), file);
#endif
    post(command);
    return (system(command) == 0);
}

bool faustgen_factory::open_file(const char* appl, const char* file)
{
    char command[512];
#ifdef WIN32
    sprintf(command, "start \"\" %s \"%s%s\"", appl, (*fLibraryPath.begin()).c_str(), file);
#else
    sprintf(command, "open -a %s \"%s%s\"", appl, (*fLibraryPath.begin()).c_str(), file);
#endif
    return (system(command) == 0);
}

void faustgen_factory::display_documentation()
{
    // Open the Web documentation
    char command[512];
#ifdef WIN32
    sprintf(command, "start \"\" \"https://faust.grame.fr/doc/manual/index.html\"");
#else
    sprintf(command, "open \"https://faust.grame.fr/doc/manual/index.html\"");
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
    open_file("analyzers.lib");
    open_file("basics.lib");
    open_file("compressors.lib");
    open_file("delays.lib");
    open_file("demos.lib");
    open_file("double.lib");
    open_file("dx7.lib");
    open_file("envelopes.lib");
    open_file("filters.lib");
    open_file("float.lib");
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
#else
    open_file(FAUST_PDF_LIBRARY);
    display_libraries_aux("all.lib");
    display_libraries_aux("analyzers.lib");
    display_libraries_aux("basics.lib");
    display_libraries_aux("compressors.lib");
    display_libraries_aux("delays.lib");
    display_libraries_aux("demos.lib");
    display_libraries_aux("double.lib");
    display_libraries_aux("dx7.lib");
    display_libraries_aux("envelopes.lib");
    display_libraries_aux("filters.lib");
    display_libraries_aux("float.lib");
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
#endif
}

void faustgen_factory::update_sourcecode(int size, char* source_code)
{
    // Recompile only if text has been changed
    if (strcmp(source_code, *fSourceCode) != 0) {
        
        // Update all instances
        for (auto& it : fInstances) {
            it->hilight_off();
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
        for (auto& it : fInstances) {
            it->update_sourcecode();
        }
        
    } else {
        post("DSP code has not been changed...");
    }
}

void faustgen_factory::librarypath(long inlet, t_symbol* s)
{
    if (s != gensym("")) {
        add_library_path(getFolderFromPath(s->s_name));
    }
}

void faustgen_factory::read(long inlet, t_symbol* s)
{
    char filename[MAX_FILENAME_CHARS];
    short path = 0;
    long type = 'TEXT';
    t_max_err err;
    t_filehandle fh;
    
    // No filename, so open load dialog
    if (s == gensym("")) {
        filename[0] = 0;
        if (open_dialog(filename, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file not found");
            return;
        }
        // Otherwise locate the file
    } else {
        strncpy_zero(filename, s->s_name, MAX_FILENAME_CHARS);
        // Set default path with saved value
        path_setdefault(fDefaultPath, 0);
        if (locatefile_extended(filename, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file '%s' not found", filename);
            return;
        }
    }
    
    // File found, open it and recompile DSP
    err = path_opensysfile(filename, path, &fh, READ_PERM);
    if (err) {
        post("Faust DSP file '%s' cannot be opened", filename);
        return;
    }
    
    // Delete the existing Faust module
    free_dsp_factory();
    
    // Free the memory allocated for fBitCode
    free_bitcode();
    
    err = sysfile_readtextfile(fh, fSourceCode, 0, (t_sysfile_text_flags)(TEXT_LB_UNIX | TEXT_NULL_TERMINATE));
    if (err) {
        post("Faust DSP file '%s' cannot be read", filename);
    }
    
    sysfile_close(fh);
    fSourceCodeSize = sysmem_handlesize(fSourceCode);
    
    // Add DSP file enclosing folder pathname in the '-I' list
    char full_path[MAX_FILENAME_CHARS];
    if ((err = path_topathname(path, filename, full_path)) == 0) {
        add_library_path(getFolderFromFilename(full_path));
    } else {
        post("path_topathname err = %d", err);
    }
    
    // Update all instances
    for (auto& it : fInstances) {
        it->update_sourcecode();
    }
}

void faustgen_factory::write(long inlet, t_symbol* s)
{
    char filename[MAX_FILENAME_CHARS];
    short path = 0;
    long type = 'TEXT';
    t_max_err err;
    t_filehandle fh;
    
    // No filename, so open save dialog
    if (s == gensym("")) {
        filename[0] = 0;
        if (saveas_dialog(filename, &path, NULL)) {
            post("Faust DSP file not found");
            return;
        } else {
            err = path_createsysfile(filename, path, type, &fh);
            if (err) {
                post("Faust DSP file '%s' cannot be created", filename);
                return;
            }
        }
        // Otherwise locate or create the file
    } else {
        strncpy_zero(filename, s->s_name, MAX_FILENAME_CHARS);
        // Set default path with saved value
        path_setdefault(fDefaultPath, 0);
        if (locatefile_extended(filename, &path, (t_fourcc*)&type, (t_fourcc*)&type, 1)) {
            post("Faust DSP file '%s' not found, so tries to create it", filename);
            err = path_createsysfile(filename, path, type, &fh);
            if (err) {
                post("Faust DSP file '%s' cannot be created", filename);
                return;
            }
        } else {
            err = path_opensysfile(filename, path, &fh, WRITE_PERM);
            if (err) {
                post("Faust DSP file '%s' cannot be opened", filename);
                return;
            }
        }
    }
    
    err = sysfile_writetextfile(fh, fSourceCode, (t_sysfile_text_flags)(TEXT_LB_UNIX | TEXT_NULL_TERMINATE));
    if (err) {
        post("Faust DSP file '%s' cannot be written", filename);
    }
    sysfile_close(fh);
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
    
    // Increment ap each time to get to the next atom
    for (i = 0, ap = argv; i < argc; i++, ap++) {
        switch (atom_gettype(ap)) {
                
            case A_LONG: {
                stringstream num;
                num << atom_getlong(ap);
                string res = num.str();
                fOptions.push_back(res.c_str());
                break;
            }
                
            case A_FLOAT:
                post("Invalid compiler option argument - float");
                break;
                
            case A_SYM:
                // Add options to default ones
                fOptions.push_back(atom_getsym(ap)->s_name);
                break;
                
            default:
                post("Invalid compiler option argument - unknown");
                break;
        }
    }
    
    /*
     if (optimize) {
     post("Start looking for optimal compilation options...");
     #ifdef __APPLE__
     double best;
     dsp_optimizer optimizer(string(*fSourceCode), (*fLibraryPath.begin()).c_str(), getTarget(), sys_getblksize());
     fOptions = optimizer.findOptimizedParameters(best);
     #endif
     post("Optimal compilation options found");
     }
     */
    
    // Delete the existing Faust module
    free_dsp_factory();
    
    // Free the memory allocated for fBitCode
    free_bitcode();
    
    // Update all instances
    for (auto& it : fInstances) {
        it->update_sourcecode();
    }
}

//====================
// Faust DSP Instance
//====================

bool faustgen::allocate_factory(const string& effect_name)
{
    bool res = false;
    
    if (faustgen_factory::gFactoryMap.find(effect_name) != faustgen_factory::gFactoryMap.end()) {
        fDSPfactory = faustgen_factory::gFactoryMap[effect_name];
    } else {
        fDSPfactory = new faustgen_factory(effect_name);
        faustgen_factory::gFactoryMap[effect_name] = fDSPfactory;
        res = true;
    }
    
    fDSPfactory->add_instance(this);
    return res;
}

faustgen::faustgen(t_symbol* sym, long ac, t_atom* argv)
{
    m_siginlets = 0;
    m_sigoutlets = 0;
    
    fDSP = NULL;
    fDSPUI = NULL;
    fMidiUI = NULL;
    fOSCUI = NULL;
    fDSPfactory = NULL;
    fEditor = NULL;
    fMute = false;
    
    int i;
    t_atom* ap;
    bool res = false;
    
    // Allocate factory with a given "name"
    for (i = 0, ap = argv; i < ac; i++, ap++) {
        if (atom_gettype(ap) == A_SYM) {
            res = allocate_factory(atom_getsym(ap)->s_name);
            break;
        }
    }
    
    // Empty (= no name) faustgen~ will be internally separated as groups with different names
    if (!fDSPfactory) {
        string effect_name;
        stringstream num;
        num << faustgen_factory::gFaustCounter;
        effect_name = "faustgen_factory-" + num.str();
        res = allocate_factory(effect_name);
    }
    
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    if (gDefaultColor.red == -1.) {
        jbox_get_color(box, &gDefaultColor);
    }
    
    // Needed to script objects
    char name[64];
    sprintf(name, "faustgen-%x", this);
    jbox_set_varname(box, gensym(name));
    
    // Fetch the data inside the max patcher using the dictionary
    t_dictionary* d = 0;
    if ((d = (t_dictionary*)gensym("#D")->s_thing) && res) {
        fDSPfactory->getfromdictionary(d);
    }
    
    create_dsp(true);
}

// Called upon deleting the object inside the patcher
faustgen::~faustgen()
{
    free_dsp();
    
    if (fEditor) {
        object_free(fEditor);
        fEditor = NULL;
    }
    
    fDSPfactory->remove_instance(this);
}

void faustgen::free_dsp()
{
    // Save controller state
    fSavedUI.save();
    
    // Has to be done *before* remove_instance that may free fDSPfactory and thus fDSPfactory->fMidiHandler
    remove_midihandler();
    
    delete fMidiUI;
    fMidiUI = NULL;
    
    delete fOSCUI;
    fOSCUI = NULL;
    
    delete fDSPUI;
    fDSPUI = NULL;
    
    delete fDSP;
    fDSP = NULL;
}

t_dictionary* faustgen::json_reader(const char* jsontext)
{
    t_dictionary *d = NULL;
    t_max_err err;
    t_atom result[1];
    t_object *jsonreader = (t_object*)object_new(_sym_nobox, _sym_jsonreader);
    
    err = (t_max_err)object_method(jsonreader, _sym_parse, jsontext, result);
    if (!err) {
        t_object *ro = (t_object*)atom_getobj(result);
        if (ro) {
            if (object_classname_compare(ro, _sym_dictionary)) {
                d = (t_dictionary*)ro;
            } else {
                object_free(ro);
            }
        }
    }
    object_free(jsonreader);
    return d;
}

// Called upon sending the object a message inside the max patcher
// Allows to set a value to the Faust module's parameter, or a list of values
void faustgen::anything(long inlet, t_symbol* s, long ac, t_atom* av)
{
    bool res = false;
    string name = string((s)->s_name);

    // If no argument is there, consider it as a toggle message for a button
    if (ac == 0 && fDSPUI->isValue(name)) {
        
        FAUSTFLOAT off = FAUSTFLOAT(0.0);
        FAUSTFLOAT on = FAUSTFLOAT(1.0);
        fDSPUI->setValue(name, off);
        fDSPUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        anything(inlet, s, 1, av);
        
    } else if (mspUI::checkDigit(name)) { // List of values
        
        int ndigit = 0;
        int pos;
        
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
        
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            FAUSTFLOAT value;
            switch (atom_gettype(ap)) {
                case A_LONG:
                    value = FAUSTFLOAT(ap[0].a_w.w_long);
                    break;
                case A_FLOAT:
                    value = FAUSTFLOAT(ap[0].a_w.w_float);
                    break;
                default:
                    post("Invalid argument in parameter setting");
                    return;
            }
            
            string num_val = to_string(num + i);
            stringstream param_name; param_name << prefix;
            for (int i = 0; i < ndigit - mspUI::countDigit(num_val); i++) {
                param_name << ' ';
            }
            param_name << num_val;
            
            // Try special naming scheme for list of parameters
            res = fDSPUI->setValue(param_name.str(), value);
            
            // Otherwise try standard name
            if (!res) {
                res = fDSPUI->setValue(name, value);
            }
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
        
    } else {
        // Standard parameter name
        FAUSTFLOAT value = (av[0].a_type == A_LONG) ? FAUSTFLOAT(av[0].a_w.w_long) : av[0].a_w.w_float;
        res = fDSPUI->setValue(name, value);
        if (!res) {
            post("Unknown parameter : %s", (s)->s_name);
        }
    }
}

void faustgen::compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv)
{
    fDSPfactory->compileoptions(inlet, s, argc, argv);
}

void faustgen::read(long inlet, t_symbol* s)
{
    fDSPfactory->read(inlet, s);
}

void faustgen::write(long inlet, t_symbol* s)
{
    fDSPfactory->write(inlet, s);
}

void faustgen::polyphony(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (fDSPfactory->lock()) {
        free_dsp();
        fDSP = fDSPfactory->create_dsp_instance(av[0].a_w.w_long);
        assert(fDSP);
        
        // Init all controller (UI, MIDI, Soundfile)
        init_controllers();
        
        // Prepare JSON
        fDSPfactory->make_json(fDSP);
        
        // Send JSON to JS script
        create_jsui();
        
        // Initialize at the system's sampling rate
        fDSP->init(sys_getsr());
        fDSPfactory->unlock();
    } else {
        post("Mutex lock cannot be taken...");
    }
}

// Reset controllers to init value and send [label, init, min, max]
void faustgen::init(long inlet, t_symbol* s, long ac, t_atom* av)
{
    // Reset internal state
    fSavedUI.reset();
    
    // Input controllers
    for (mspUI::iterator it = fDSPUI->begin1(); it != fDSPUI->end1(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
    // Output controllers
    for (mspUI::iterator it = fDSPUI->begin3(); it != fDSPUI->end3(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
}

// Dump controllers as list of: [label, cur, min, max]
void faustgen::dump(long inlet, t_symbol* s, long ac, t_atom* av)
{
    // Input controllers
    for (mspUI::iterator it = fDSPUI->begin1(); it != fDSPUI->end1(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
    // Output controllers
    for (mspUI::iterator it = fDSPUI->begin3(); it != fDSPUI->end3(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
}

// osc 'IP inport outport xmit bundle'
void faustgen::osc(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac == 5) {
        if (fDSPfactory->lock()) {
            
            delete fOSCUI;
            
            const char* argv1[32];
            int argc1 = 0;
            
            argv1[argc1++] = "Faust";
            
            argv1[argc1++]  = "-desthost";
            argv1[argc1++]  = atom_getsym(&av[0])->s_name;
            
            char inport[32];
            snprintf(inport, 32, "%ld", long(av[1].a_w.w_long));
            argv1[argc1++] = "-port";
            argv1[argc1++] = inport;
            
            char outport[32];
            snprintf(outport, 32, "%ld", long(av[2].a_w.w_long));
            argv1[argc1++] = "-outport";
            argv1[argc1++] = outport;
            
            char xmit[32];
            snprintf(xmit, 32, "%ld", long(av[3].a_w.w_long));
            argv1[argc1++] = "-xmit";
            argv1[argc1++] = xmit;
            
            char bundle[32];
            snprintf(bundle, 32, "%ld", long(av[4].a_w.w_long));
            argv1[argc1++] = "-bundle";
            argv1[argc1++] = bundle;
            
            fOSCUI = new OSCUI("Faust", argc1, (char**)argv1);
            fDSP->buildUserInterface(fOSCUI);
            fOSCUI->run();
            
            post(fOSCUI->getInfos().c_str());
            fDSPfactory->unlock();
        } else {
            post("Mutex lock cannot be taken...");
        }
    } else {
        post("Should be : osc 'IP inport outport xmit(0|1|2) bundle(0|1)'");
    }
}

void faustgen::midievent(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac > 0) {
        int type = (int)av[0].a_w.w_long & 0xf0;
        int channel = (int)av[0].a_w.w_long & 0x0f;
        
        if (ac == 1) {
            fDSPfactory->fMidiHandler.handleSync(0.0, av[0].a_w.w_long);
        } else if (ac == 2) {
            fDSPfactory->fMidiHandler.handleData1(0.0, type, channel, av[1].a_w.w_long);
        } else if (ac == 3) {
            fDSPfactory->fMidiHandler.handleData2(0.0, type, channel, av[1].a_w.w_long, av[2].a_w.w_long);
        }
    }
}

void faustgen::librarypath(long inlet, t_symbol* s)
{
    fDSPfactory->librarypath(inlet, s);
}

// Called when saving the Max patcher, this function saves the necessary data inside the json file (faust sourcecode)
void faustgen::appendtodictionary(t_dictionary* d)
{
    fDSPfactory->appendtodictionary(d);
}

void faustgen::getfromdictionary(t_dictionary* d)
{
    fDSPfactory->getfromdictionary(d);
}

// Called when the user double-clicks on the faustgen object inside the Max patcher
void faustgen::dblclick(long inlet)
{
    // Create a popup menu inside the Max patcher
    t_jpopupmenu* popup = jpopupmenu_create();
    jpopupmenu_additem(popup, 1, "Edit DSP code", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 2, "View DSP parameters", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 3, "View compile options", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 4, "View SVG diagram", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 5, "View Web documentation", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 6, "View libraries", NULL, 0, 0, NULL);
    
    // Get mouse position
    int x,y;
    jmouse_getposition_global(&x, &y);
    t_pt coordinate;
    coordinate.x = x;
    coordinate.y = y;
    
    int choice = jpopupmenu_popup(popup, coordinate, 0);
    
    switch (choice) {
            
        case 1:
            // Open the text editor to allow the user to input Faust sourcecode
            display_dsp_source();
            break;
            
        case 2:
            // Display inside the max window the current values of the module's parameters, as well as their ranges
            display_dsp_params();
            break;
            
        case 3:
            // Display compiler options
            fDSPfactory->print_compile_options();
            break;
            
        case 4:
            // Open the SVG diagram file inside a web browser
            display_svg();
            break;
            
        case 5:
            // Open the documentation
            display_documentation();
            break;
            
        case 6:
            // Open the libraries
            display_libraries();
            break;
            
        default:
            break;
    }
    
    // Destroy the popup menu once this is done
    jpopupmenu_destroy(popup);
}

// Called when closing the text editor, calls for the creation of a new Faust module with the updated sourcecode
void faustgen::edclose(long inlet, char** source_code, long size)
{
    // Edclose "may" be called with an already deallocated object (like closing the patcher with a still opened editor)
    if (fDSP && fEditor) {
        fDSPfactory->update_sourcecode(size, *source_code);
        fEditor = NULL;
    }
}

void faustgen::update_sourcecode()
{
    // Create a new DSP instance
    create_dsp(false);
    
    // faustgen~ state is modified...
    set_dirty();
    
    // Send a bang
    outlet_bang(m_control_outlet);
}

// Process the signal data with the Faust module
inline void faustgen::perform(int vs, t_sample** inputs, long numins, t_sample** outputs, long numouts)
{
    if (!fMute && fDSPfactory->try_lock()) {
        // Has to be tested again when the lock has been taken...
        if (fDSP) {
            fDSP->compute(vs, static_cast<FAUSTFLOAT**>(inputs), static_cast<FAUSTFLOAT**>(outputs));
            if (fOSCUI) fOSCUI->endBundle();
            update_outputs();
        }
        // Done for fMIDIUI and fOSCUI
        GUI::updateAllGuis();
        fDSPfactory->unlock();
    } else {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
            memset(outputs[i], 0, sizeof(t_sample) * vs);
        }
    }
}

inline void faustgen::init(double samplerate)
{
    fDSP->init(samplerate);
}

// Display source code
void faustgen::display_dsp_source()
{
    if (fEditor) {
        // Editor already open, set it to to foreground
        object_attr_setchar(fEditor, gensym("visible"), 1);
    } else {
        // Create a text editor object
        fEditor = (t_object*)object_new(CLASS_NOBOX, gensym("jed"), this, 0);
        
        // Set the text inside the text editor to be fSourceCode
        object_method(fEditor, gensym("settext"), fDSPfactory->get_sourcecode(), gensym("utf-8"));
        object_attr_setchar(fEditor, gensym("scratch"), 1);
        char name[256];
        snprintf(name, 256, "DSP code : %s", fDSPfactory->get_name().c_str());
        object_attr_setsym(fEditor, gensym("title"), gensym(name));
    }
}

// Display the Faust module's parameters along with their standard values
void faustgen::display_dsp_params()
{
    fDSPUI->displayControls();
    post("JSON : %s", fDSPfactory->get_json());
}

void faustgen::display_svg()
{
    fDSPfactory->display_svg();
}

void faustgen::display_documentation()
{
    fDSPfactory->display_documentation();
}

void faustgen::display_libraries()
{
    fDSPfactory->display_libraries();
}

void faustgen::hilight_on()
{
    t_jrgba color;
    jrgba_set(&color, 1.0, 0.0, 0.0, 1.0);
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    jbox_set_color(box, &color);
}

void faustgen::hilight_off()
{
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    jbox_set_color(box, &gDefaultColor);
}

void faustgen::hilight_error(const string& error)
{
    object_error_obtrusive((t_object*)&m_ob, (char*)error.c_str());
}

void faustgen::add_midihandler()
{
    // Polyphonic DSP is controlled by MIDI
    if (fDSPfactory->fPolyphonic) {
        mydsp_poly* poly = static_cast<mydsp_poly*>(fDSP);
        fDSPfactory->fMidiHandler.addMidiIn(poly);
    }
}

void faustgen::remove_midihandler()
{
    // Polyphonic DSP is controlled by MIDI
    if (fDSPfactory->fPolyphonic) {
        mydsp_poly* poly = static_cast<mydsp_poly*>(fDSP);
        fDSPfactory->fMidiHandler.removeMidiIn(poly);
    }
}

void faustgen::init_controllers()
{
    // Initialize User Interface (here connnection with controls)
    if (!fDSPUI) {
        fDSPUI = new mspUI();
        fDSP->buildUserInterface(fDSPUI);
    }
    
    // MIDI handling
    if (!fMidiUI) {
        fMidiUI = new MidiUI(&fDSPfactory->fMidiHandler);
        add_midihandler();
        fDSP->buildUserInterface(fMidiUI);
    }
    
    // Soundfile handling
    if (fDSPfactory->fSoundUI) {
        if (fDSPfactory->fPolyphonic) {
            mydsp_poly* poly = static_cast<mydsp_poly*>(fDSP);
            // SoundUI has to be dispatched on all internal voices
            poly->setGroup(false);
            fDSP->buildUserInterface(fDSPfactory->fSoundUI);
            poly->setGroup(true);
        } else {
            fDSP->buildUserInterface(fDSPfactory->fSoundUI);
        }
    }
}

void faustgen::create_dsp(bool init)
{
    if (fDSPfactory->lock()) {
        fDSP = fDSPfactory->create_dsp_aux();
        assert(fDSP);
        
        // Init all controllers (UI, MIDI, Soundfile)
        init_controllers();
        
        // Initialize at the system's sampling rate
        fDSP->init(sys_getsr());
        
        // Setup MAX audio IO
        bool dspstate = false;
        
        if ((m_siginlets != fDSP->getNumInputs()) || (m_sigoutlets != fDSP->getNumOutputs())) {
            // Number of ins/outs have changed... possibly stop IO
            dspstate = sys_getdspobjdspstate((t_object*)&m_ob);
            if (dspstate) {
                dsp_status("stop");
            }
        }
        
        setupIO(&faustgen::perform, &faustgen::init, fDSP->getNumInputs(), fDSP->getNumOutputs(), init);
        
        // Load old controller state
        fDSP->buildUserInterface(&fSavedUI);
        
        // Possibly restart IO
        if (dspstate) {
            dsp_status("start");
        }
        
        // Send JSON to JS script
        create_jsui();
        
        fDSPfactory->unlock();
    } else {
        post("Mutex lock cannot be taken...");
    }
}

void faustgen::set_dirty()
{
    t_object* mypatcher;
    object_obex_lookup(&m_ob, gensym("#P"), &mypatcher);
    jpatcher_set_dirty(mypatcher, 1);
}

t_pxobject* faustgen::check_dac()
{
    t_object *patcher, *box, *obj;
    object_obex_lookup(this, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        if (obj) {
            if ((object_classname(obj) == gensym("dac~"))
                || (object_classname(obj) == gensym("ezdac~"))
                || (object_classname(obj) == gensym("ezadc~"))
                || (object_classname(obj) == gensym("adc~"))) {
                return (t_pxobject*)box;
            }
        }
    }
    
    return NULL;
}

void faustgen::create_jsui()
{
    t_object *patcher, *box, *obj;
    object_obex_lookup(this, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(fDSPfactory->get_json()));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
        }
    }
    
    // Keep all outputs to be notified in update_outputs
    fOutputTable.clear();
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        t_symbol* scriptingname = jbox_get_varname(obj); // scripting name
        // Keep control outputs
        if (scriptingname && fDSPUI->isOutputValue(scriptingname->s_name)) {
            fOutputTable[scriptingname->s_name].push_back(obj);
        }
    }
}

void faustgen::update_outputs()
{
    for (auto& it1 : fOutputTable) {
        bool new_val = false;
        FAUSTFLOAT value = fDSPUI->getOutputValue(it1.first, new_val);
        if (new_val) {
            t_atom at_value;
            atom_setfloat(&at_value, value);
            for (auto& it2 : it1.second) {
                object_method_typed(it2, gensym("float"), 1, &at_value, 0);
            }
        }
    }
}

void faustgen::dsp_status(const char* mess)
{
    t_pxobject* dac = NULL;
    
    if ((dac = check_dac())) {
        t_atom msg[1];
        atom_setsym(msg, gensym(mess));
        object_method_typed(dac, gensym("message"), 1, msg, 0);
    } else { // Global
        object_method(gensym("dsp")->s_thing, gensym(mess));
    }
}

void faustgen::mute(long inlet, long mute)
{
    fMute = mute;
}

/*
 // For Max 6
 #ifdef WIN32
 //extern "C" int main(void)
 extern "C" void ext_main(void* r)
 #else
 int main(void)
 #endif
 */

extern "C" void ext_main(void* r)
{
#ifdef WIN32
    static bool done = false;
    if (done) return;
    done = true;
#endif
    
    // Creates an instance of Faustgen
    t_class * mclass = faustgen::makeMaxClass("faustgen~");
    post("faustgen~ v%s (sample = 64 bits code = %s)", FAUSTGEN_VERSION, getCodeSize());
    post("LLVM powered Faust embedded compiler v%s", getCLibFaustVersion());
    post("Copyright (c) 2012-2019 Grame");
    
    // Start 'libfaust' in multi-thread safe mode
    startMTDSPFactories();
    
    // Process all messages coming to the object using a custom method
    REGISTER_METHOD_GIMME(faustgen, anything);
    
    // Process the "compileoptions" message, to add optional compilation possibilities
    REGISTER_METHOD_GIMME(faustgen, compileoptions);
    
    // Process the "midievent" message
    REGISTER_METHOD_GIMME(faustgen, midievent);
    
    // Process the "polyphony" message
    REGISTER_METHOD_GIMME(faustgen, polyphony);
    
    // Process the "init" message
    REGISTER_METHOD_GIMME(faustgen, init);
    
    // Process the "dump" message
    REGISTER_METHOD_GIMME(faustgen, dump);
    
    // Process the "osc" message
    REGISTER_METHOD_GIMME(faustgen, osc);
    
    // Register inside Max the necessary methods
    REGISTER_METHOD_DEFSYM(faustgen, read);
    REGISTER_METHOD_DEFSYM(faustgen, write);
    REGISTER_METHOD_DEFSYM(faustgen, librarypath);
    REGISTER_METHOD_LONG(faustgen, mute);
    REGISTER_METHOD_CANT(faustgen, dblclick);
    REGISTER_METHOD_EDCLOSE(faustgen, edclose);
    REGISTER_METHOD_JSAVE(faustgen, appendtodictionary);
}

