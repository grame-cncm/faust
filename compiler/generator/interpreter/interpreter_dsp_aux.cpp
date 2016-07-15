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

#include "interpreter_dsp_aux.hh"
#include "dsp_aux.hh"

#ifndef LOADER
#include "libfaust.h"
#endif

using namespace std;

typedef class faust_smartptr<interpreter_dsp_factory> SDsp_factory;

dsp_factory_table<SDsp_factory> gInterpreterFactoryTable;


#ifdef LOADER
static string path_to_content(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}
#endif

// External API

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    return reinterpret_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromFile(const string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createInterpreterDSPFactoryFromString(base.substr(0, pos), path_to_content(filename), argc, argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return 0;
    } 
}

EXPORT interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const string& name_app,
                                                                    const string& dsp_content,
                                                                    int argc, const char* argv[], 
                                                                    string& error_msg)
{
#ifdef LOADER
   return 0;
#else
   
    string expanded_dsp_content, sha_key;
    
    if ((expanded_dsp_content = expandDSPFromString(name_app, dsp_content, argc, argv, sha_key, error_msg)) == "") {
        return 0;
    } else {
        
        int argc1 = argc + 3;
        const char* argv1[32];
        
        argv1[0] = "faust";
        argv1[1] = "-lang";
        argv1[2] = "interp";
        for (int i = 0; i < argc; i++) {
            argv1[i+3] = argv[i];
        }
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        interpreter_dsp_factory* factory = 0;
        
        if (gInterpreterFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else if ((factory = new interpreter_dsp_factory(compile_faust_interpreter(argc1, argv1,
                                                                                    name_app.c_str(),
                                                                                    dsp_content.c_str(),
                                                                                    error_msg))) != 0) {
            gInterpreterFactoryTable.setFactory(factory);
            factory->setSHAKey(sha_key);
            factory->setDSPCode(expanded_dsp_content);
            return factory;
        } else {
            return 0;
        }
    }
 #endif
}

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
    delete fDSP;
}

EXPORT interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    dsp* dsp = fFactory->createDSPInstance(this);
    gInterpreterFactoryTable.addDSP(this, dsp);
    return reinterpret_cast<interpreter_dsp*>(dsp);
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
    std::string type = read_real_type(in);
    interpreter_dsp_factory* factory = 0;
    
    if (type == "float") {
        factory =  new interpreter_dsp_factory(interpreter_dsp_factory_aux<float>::read(in));
    } else if (type == "double") {
        factory = new interpreter_dsp_factory(interpreter_dsp_factory_aux<double>::read(in));
    } else {
        assert(false);
    }
    
    gInterpreterFactoryTable.setFactory(factory);
    return factory;
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
        return readInterpreterDSPFactoryFromMachineAux(&reader);
    } else {
        std::cerr << "File Extension is not the one expected (.fbc expected)" << std::endl;
        return 0;
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
    return reinterpret_cast<interpreter_dsp*>(fFactory->createDSPInstance());
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

EXPORT void interpreter_dsp::buildUserInterface(UI* ui_interface)
{
    UIGeneric glue(ui_interface);
    fDSP->buildUserInterface(&glue);
}

EXPORT void interpreter_dsp::compute(int count, float** input, float** output)
{
    RealBuffers buffers(input, output);
    fDSP->compute(count, buffers);
}

EXPORT void interpreter_dsp::compute(int count, double** input, double** output)
{
    RealBuffers buffers(input, output);
    fDSP->compute(count, buffers);
}

