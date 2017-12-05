/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#include "compatibility.hh"
#include "interpreter_dsp_aux.hh"
#include "dsp_aux.hh"
#include "Text.hh"
#include "libfaust.h"

using namespace std;

typedef class faust_smartptr<interpreter_dsp_factory> SDsp_factory;
static dsp_factory_table<SDsp_factory> gInterpreterFactoryTable;

// External API

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    return reinterpret_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

//#ifndef INTERP_PLUGIN

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createInterpreterDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    } 
}

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const string& name_app,
                                                                    const string& dsp_content,
                                                                    int argc, const char* argv[], 
                                                                    string& error_msg)
{
    string expanded_dsp_content, sha_key;
    
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return NULL;
    } else {
        
        int argc1 = 0;
        const char* argv1[32];
        
        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        argv1[argc1++] = "interp";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "string";
        
        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        
        argv1[argc1] = 0;  // NULL terminated argv
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        interpreter_dsp_factory* factory = 0;
        
        if (gInterpreterFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else  {
            dsp_factory_base* dsp_factory_aux = compileFaustFactory(argc1, argv1,
                                                                    name_app.c_str(),
                                                                    dsp_content.c_str(),
                                                                    error_msg,
                                                                    true);
            if (dsp_factory_aux) {
                dsp_factory_aux->setName(name_app);
                factory = new interpreter_dsp_factory(dsp_factory_aux);
                gInterpreterFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                factory->setDSPCode(expanded_dsp_content);
                return factory;
            } else {
                return NULL;
            }
        }
    }
}

//#endif

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    return (factory) ? gInterpreterFactoryTable.deleteDSPFactory(factory): false;
}

EXPORT vector<string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
    vector<string> res;
    return res;
}

EXPORT vector<string> getAllInterpreterDSPFactories()
{
    return gInterpreterFactoryTable.getAllDSPFactories();
}

EXPORT void deleteAllInterpreterDSPFactories()
{
    gInterpreterFactoryTable.deleteAllDSPFactories();
}

EXPORT interpreter_dsp::~interpreter_dsp()
{
    gInterpreterFactoryTable.removeDSP(fFactory, this);
    
    if (fFactory->getMemoryManager()) {
        fDSP->~interpreter_dsp_base();
        fFactory->getMemoryManager()->destroy(fDSP);
    } else {
        delete fDSP;
    }
}

EXPORT interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    dsp* dsp = fFactory->createDSPInstance(this);
    gInterpreterFactoryTable.addDSP(this, dsp);
    return reinterpret_cast<interpreter_dsp*>(dsp);
}

// Use the memory manager if needed
EXPORT void interpreter_dsp::operator delete(void* ptr)
{
    dsp_memory_manager* manager = static_cast<interpreter_dsp*>(ptr)->fFactory->getMemoryManager();
    if (manager) {
        manager->destroy(ptr);
    } else {
        ::operator delete(ptr);
    }
}

// Read/write

static std::string read_real_type(std::istream* in)
{
    std::string type_line;
    getline(*in, type_line);
    
    std::stringstream  type_reader(type_line);
    std::string dummy, type;
    type_reader >> dummy;   // Read "interpreter_dsp_factory" token
    type_reader >> type;
    
    return type;
}

static interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineAux(std::istream* in)
{
    try {
        std::string type = read_real_type(in);
        interpreter_dsp_factory* factory = 0;
        
        if (type == "float") {
            factory = new interpreter_dsp_factory(interpreter_dsp_factory_aux<float, 0>::read(in));
        } else if (type == "double") {
            factory = new interpreter_dsp_factory(interpreter_dsp_factory_aux<double, 0>::read(in));
        } else {
            faustassert(false);
        }
        
        gInterpreterFactoryTable.setFactory(factory);
        return factory;
    } catch (faustexception& e) {
        std::cerr << "Exception in readInterpreterDSPFactoryFromMachineAux: " << e.Message();
        return NULL;
    }
}

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachine(const string& machine_code)
{
    stringstream reader(machine_code);
    return readInterpreterDSPFactoryFromMachineAux(&reader);
}

EXPORT string writeInterpreterDSPFactoryToMachine(interpreter_dsp_factory* factory)
{
    stringstream writer;
    factory->write(&writer, true);
    return writer.str();
}

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineFile(const string& machine_code_path)
{
    string base = basename((char*)machine_code_path.c_str());
    size_t pos = machine_code_path.find(".fbc");
    
    if (pos != string::npos) {
        //ifstream reader(machine_code_path);
        ifstream reader(machine_code_path.c_str());
        if (reader.is_open()) {
            return readInterpreterDSPFactoryFromMachineAux(&reader);
        } else {
            std::cerr << "Error opening file '" << machine_code_path << "'" << std::endl;
            return NULL;
        }
    } else {
        std::cerr << "File Extension is not the one expected (.fbc expected)" << std::endl;
        return NULL;
    }
}

EXPORT void writeInterpreterDSPFactoryToMachineFile(interpreter_dsp_factory* factory, const string& machine_code_path)
{
    ofstream writer(machine_code_path.c_str());
    factory->write(&writer, true);
}

EXPORT void interpreter_dsp::metadata(Meta* meta)
{
    fDSP->metadata(meta);
}

EXPORT interpreter_dsp* interpreter_dsp::clone()
{
    return fFactory->createDSPInstance();
}

EXPORT int interpreter_dsp::getSampleRate()
{
    return fDSP->getSampleRate();
}

EXPORT int interpreter_dsp::getNumInputs()
{
    return fDSP->getNumInputs();
}

int EXPORT interpreter_dsp::getNumOutputs()
{
    return fDSP->getNumOutputs();
}

EXPORT void interpreter_dsp::init(int samplingRate)
{
    fDSP->init(samplingRate);
}

EXPORT void interpreter_dsp::instanceInit(int samplingRate)
{
    fDSP->instanceInit(samplingRate);
}

EXPORT void interpreter_dsp::instanceConstants(int samplingRate)
{
    fDSP->instanceConstants(samplingRate);
}

EXPORT void interpreter_dsp::instanceResetUserInterface()
{
    fDSP->instanceResetUserInterface();
}

EXPORT void interpreter_dsp::instanceClear()
{
    fDSP->instanceClear();
}

EXPORT void interpreter_dsp::buildUserInterface(UI* ui_interface)
{
    UITemplate glue(ui_interface);
    fDSP->buildUserInterface(&glue);
}

EXPORT void interpreter_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    fDSP->compute(count, input, output);
}

