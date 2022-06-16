/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "interpreter_dsp.hh"
#include "compatibility.hh"
#include "libfaust.h"
#include "lock_api.hh"

using namespace std;

#ifdef MACHINE
#include "sha_key.hh"
void faustassertaux(bool cond, const string& file, int line)
{
    if (!cond) {
        stringstream str;
        str << "ASSERT : please report this message, the stack trace, and the failing DSP file to Faust developers (";
        str << "file: " << file.substr(file.find_last_of('/') + 1) << ", line: " << line << ", ";
        str << "version: " << FAUSTVERSION;
        str << ")\n";
        stacktrace(str, 20);
        throw faustexception(str.str());
    }
}
#endif

dsp_factory_table<SDsp_factory> gInterpreterFactoryTable;

// External API

LIBFAUST_API interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    LOCK_API
    return static_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

LIBFAUST_API bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    LOCK_API
    return (factory) ? gInterpreterFactoryTable.deleteDSPFactory(factory) : false;
 }

LIBFAUST_API vector<string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
    LOCK_API
    vector<string> res;
    return res;
}

LIBFAUST_API vector<string> getAllInterpreterDSPFactories()
{
    LOCK_API
    return gInterpreterFactoryTable.getAllDSPFactories();
}

LIBFAUST_API void deleteAllInterpreterDSPFactories()
{
    LOCK_API
    gInterpreterFactoryTable.deleteAllDSPFactories();
}

LIBFAUST_API interpreter_dsp::~interpreter_dsp()
{
    LOCK_API
    gInterpreterFactoryTable.removeDSP(fFactory, this);

    if (fFactory->getMemoryManager()) {
        fDSP->~interpreter_dsp_base();
        fFactory->getMemoryManager()->destroy(fDSP);
    } else {
        delete fDSP;
    }
}

LIBFAUST_API interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    LOCK_API
    dsp* dsp = fFactory->createDSPInstance(this);
    gInterpreterFactoryTable.addDSP(this, dsp);
    return static_cast<interpreter_dsp*>(dsp);
}

// Use the memory manager if needed
LIBFAUST_API void interpreter_dsp::operator delete(void* ptr)
{
    if (ptr) {
        dsp_memory_manager* manager = static_cast<interpreter_dsp*>(ptr)->fFactory->getMemoryManager();
        if (manager) {
            manager->destroy(ptr);
        } else {
            ::operator delete(ptr);
        }
    }
}

// Read/write

static string read_real_type(istream* in)
{
    string type_line;
    getline(*in, type_line);

    stringstream type_reader(type_line);
    string       dummy, type;
    type_reader >> dummy;  // Read "interpreter_dsp_factory" token
    checkToken(dummy, "interpreter_dsp_factory");
    type_reader >> type;

    return type;
}

static interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeAux(const string& bitcode, string& error_msg)
{
    try {
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        
        string sha_key = generateSHA1(bitcode);

        if (gInterpreterFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            interpreter_dsp_factory* factory = nullptr;
            stringstream             reader(bitcode);
            string                   type = read_real_type(&reader);

            if (type == "float") {
                factory = new interpreter_dsp_factory(interpreter_dsp_factory_aux<float, 0>::read(&reader));
            } else if (type == "double") {
                factory = new interpreter_dsp_factory(interpreter_dsp_factory_aux<double, 0>::read(&reader));
            } else {
                throw faustexception("ERROR : unrecognized file format\n");
            }

            gInterpreterFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            factory->setDSPCode(bitcode);
            return factory;
        }
    } catch (faustexception& e) {
        error_msg = e.Message();
        return nullptr;
    }
}

LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const string& bitcode, string& error_msg)
{
    LOCK_API
    return readInterpreterDSPFactoryFromBitcodeAux(bitcode, error_msg);
}

LIBFAUST_API string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory)
{
    LOCK_API
    stringstream writer;
    factory->write(&writer, true);
    return writer.str();
}

LIBFAUST_API interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const string& bitcode_path, string& error_msg)
{
    LOCK_API
    string base = basename((char*)bitcode_path.c_str());
    size_t pos  = bitcode_path.find(".fbc");

    if (pos != string::npos) {
        ifstream reader(bitcode_path.c_str());
        if (reader.is_open()) {
            string bitcode(istreambuf_iterator<char>(reader), {});
            return readInterpreterDSPFactoryFromBitcodeAux(bitcode, error_msg);
        } else {
            error_msg = "ERROR opening file '" + bitcode_path + "'\n";
            return nullptr;
        }
    } else {
        error_msg = "ERROR : file Extension is not the one expected (.fbc expected)\n";
        return nullptr;
    }
}

LIBFAUST_API bool writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const string& bitcode_path)
{
    LOCK_API
    ofstream writer(bitcode_path.c_str());
    if (writer.is_open()) {
        factory->write(&writer, true);
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API void interpreter_dsp::metadata(Meta* meta)
{
    fDSP->metadata(meta);
}

LIBFAUST_API void interpreter_dsp::metadata(MetaGlue* meta)
{
    fDSP->metadata(meta);
}

LIBFAUST_API interpreter_dsp* interpreter_dsp::clone()
{
    return fFactory->createDSPInstance();
}

LIBFAUST_API int interpreter_dsp::getSampleRate()
{
    return fDSP->getSampleRate();
}

LIBFAUST_API int interpreter_dsp::getNumInputs()
{
    return fDSP->getNumInputs();
}

LIBFAUST_API int interpreter_dsp::getNumOutputs()
{
    return fDSP->getNumOutputs();
}

LIBFAUST_API void interpreter_dsp::init(int sample_rate)
{
    fDSP->init(sample_rate);
}

LIBFAUST_API void interpreter_dsp::instanceInit(int sample_rate)
{
    fDSP->instanceInit(sample_rate);
}

LIBFAUST_API void interpreter_dsp::instanceConstants(int sample_rate)
{
    fDSP->instanceConstants(sample_rate);
}

LIBFAUST_API void interpreter_dsp::instanceResetUserInterface()
{
    fDSP->instanceResetUserInterface();
}

LIBFAUST_API void interpreter_dsp::instanceClear()
{
    fDSP->instanceClear();
}

LIBFAUST_API void interpreter_dsp::buildUserInterface(UI* ui_interface)
{
    UITemplate glue(ui_interface);
    fDSP->buildUserInterface(&glue);
}

LIBFAUST_API void interpreter_dsp::buildUserInterface(UIGlue* ui_glue)
{
    UIGlueTemplate glue(ui_glue);
    fDSP->buildUserInterface(&glue);
}

LIBFAUST_API void interpreter_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    fDSP->compute(count, input, output);
}

// Public C interface : lock management is done by called C++ API

#ifdef __cplusplus
extern "C" {
#endif
    
LIBFAUST_API interpreter_dsp_factory* getCInterpreterDSPFactoryFromSHAKey(const char* sha_key)
{
    LOCK_API
    return static_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

LIBFAUST_API bool deleteCInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    return deleteInterpreterDSPFactory(factory);
}

LIBFAUST_API const char** getCInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory)
{
    if (factory) {
        vector<string> library_list1 = factory->getLibraryList();
        const char**   library_list2 = (const char**)malloc(sizeof(char*) * (library_list1.size() + 1));
        
        size_t i;
        for (i = 0; i < library_list1.size(); i++) {
            library_list2[i] = strdup(library_list1[i].c_str());
        }
        
        // Last element is NULL
        library_list2[i] = nullptr;
        return library_list2;
    } else {
        return nullptr;
    }
}

LIBFAUST_API const char** getAllCInterpreterDSPFactories()
{
    vector<string> sha_key_list1 = getAllInterpreterDSPFactories();
    const char**   sha_key_list2 = (const char**)malloc(sizeof(char*) * (sha_key_list1.size() + 1));
    
    size_t i;
    for (i = 0; i < sha_key_list1.size(); i++) {
        sha_key_list2[i] = strdup(sha_key_list1[i].c_str());
    }
    
    // Last element is NULL
    sha_key_list2[i] = nullptr;
    return sha_key_list2;
}

LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcode(const char* bitcode, char* error_msg)
{
    string error_msg_aux;
    interpreter_dsp_factory* factory = readInterpreterDSPFactoryFromBitcode(bitcode, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}
    
LIBFAUST_API char* writeCInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory)
{
    return (factory) ? strdup(writeInterpreterDSPFactoryToBitcode(factory).c_str()) : nullptr;
}

LIBFAUST_API interpreter_dsp_factory* readCInterpreterDSPFactoryFromBitcodeFile(const char* bitcode_path, char* error_msg)
{
    string error_msg_aux;
    interpreter_dsp_factory* factory = readInterpreterDSPFactoryFromBitcodeFile(bitcode_path, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API bool writeCInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const char* bitcode_path)
{
    return (factory) ? writeInterpreterDSPFactoryToBitcodeFile(factory, bitcode_path) : false;
}

LIBFAUST_API void deleteAllCInterpreterDSPFactories()
{
    deleteAllInterpreterDSPFactories();
}
    
LIBFAUST_API void metadataCInterpreterDSPInstance(interpreter_dsp* dsp, MetaGlue* glue)
{
    if (dsp) {
        dsp->metadata(glue);
    }
}

LIBFAUST_API int getNumInputsCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    return (dsp) ? dsp->getNumInputs() : -1;
}

LIBFAUST_API int getNumOutputsCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    return (dsp) ? dsp->getNumOutputs() : -1;
}

LIBFAUST_API void initCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->init(sample_rate);
    }
}

LIBFAUST_API void instanceInitCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->instanceInit(sample_rate);
    }
}

LIBFAUST_API void instanceConstantsCInterpreterDSPInstance(interpreter_dsp* dsp, int sample_rate)
{
    if (dsp) {
        dsp->instanceConstants(sample_rate);
    }
}

LIBFAUST_API void instanceResetUserInterfaceCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    if (dsp) {
        dsp->instanceResetUserInterface();
    }
}

LIBFAUST_API void instanceClearCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    if (dsp) {
        dsp->instanceClear();
    }
}

LIBFAUST_API int getSampleRateCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    return (dsp) ? dsp->getSampleRate() : 0;
}

LIBFAUST_API void buildUserInterfaceCInterpreterDSPInstance(interpreter_dsp* dsp, UIGlue* glue)
{
    if (dsp) {
        dsp->buildUserInterface(glue);
    }
}

LIBFAUST_API void computeCInterpreterDSPInstance(interpreter_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    if (dsp) {
        dsp->compute(count, input, output);
    }
}

LIBFAUST_API interpreter_dsp* cloneCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    return (dsp) ? dsp->clone() : nullptr;
}

LIBFAUST_API interpreter_dsp* createCInterpreterDSPInstance(interpreter_dsp_factory* factory)
{
    return (factory) ? factory->createDSPInstance() : nullptr;
}

LIBFAUST_API void deleteCInterpreterDSPInstance(interpreter_dsp* dsp)
{
    delete dsp;
}
    
#ifdef __cplusplus
}
#endif
