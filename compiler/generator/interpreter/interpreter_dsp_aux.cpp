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

#ifndef LOADER
#include "libfaust.h"
#endif

using namespace std;

#ifdef LOADER
static string path_to_content(const string& path)
{
    ifstream file(path.c_str(), ifstream::binary);
    
    file.seekg(0, file.end);
    int size = file.tellg();
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

dsp* interpreter_dsp_factory::createDSPInstance()
{
    if (dynamic_cast<interpreter_dsp_factory_aux<float>*>(fFactory)) {
        return new interpreter_dsp(new interpreter_dsp_aux<float>(dynamic_cast<interpreter_dsp_factory_aux<float>*>(fFactory)));
    } else if (dynamic_cast<interpreter_dsp_factory_aux<double>*>(fFactory)) {
        return new interpreter_dsp(new interpreter_dsp_aux<double>(dynamic_cast<interpreter_dsp_factory_aux<double>*>(fFactory)));
    } else {
        assert(false);
    }
}

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    // TODO
    return 0;
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
    int argc1 = argc + 3;
    const char* argv1[32];
    char error_msg_aux[512];
    
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "interp";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
    }
    
    interpreter_dsp_factory_aux<float>* factory = compile_faust_interpreter(argc1, argv1,
                                                                         name_app.c_str(),
                                                                         dsp_content.c_str(),
                                                                         error_msg_aux);
    error_msg = error_msg_aux;
    return new interpreter_dsp_factory(factory);
#endif
}

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    // TODO: use of smart pointer
    delete factory;
    return true;
}

EXPORT vector<string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
    vector<string> res;
    return res;
}

EXPORT vector<string> getAllInterpreterDSPFactories()
{
    // TODO
    vector<string> res;
    return res;
}

EXPORT void deleteAllInterpreterDSPFactories()
{}

EXPORT interpreter_dsp* createInterpreterDSPInstance(interpreter_dsp_factory* factory)
{
    return reinterpret_cast<interpreter_dsp*>(factory->createDSPInstance());
}

EXPORT void deleteInterpreterDSPInstance(interpreter_dsp* dsp)
{
    delete dsp;
}

// Read/write

static std::string read_type(std::istream* in)
{
    std::string type_line;
    getline(*in, type_line);
    
    std::stringstream  type_reader(type_line);
    std::string dummy, type;
    type_reader >> dummy;   // Read "interpreter_dsp_factory" token
    type_reader >> type;
    
    return type;
}

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachine(const string& machine_code)
{
    stringstream reader(machine_code);
    std::string type = read_type(&reader);
    
    std::cout << type << std::endl;
    
    if (type == "float") {
        return new interpreter_dsp_factory(interpreter_dsp_factory_aux<float>::read(&reader));
    } else if (type == "double") {
        return new interpreter_dsp_factory(interpreter_dsp_factory_aux<double>::read(&reader));
    } else {
        assert(false);
        return 0;
    }
}

EXPORT string writeInterpreterDSPFactoryToMachine(interpreter_dsp_factory* factory)
{
    stringstream writer;
    factory->fFactory->write(&writer);
    return writer.str();
}

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineFile(const string& machine_code_path)
{
    string base = basename((char*)machine_code_path.c_str());
    size_t pos = machine_code_path.find(".fbc");
    
    if (pos != string::npos) {
        //ifstream reader(machine_code_path);
        ifstream reader(machine_code_path.c_str());
        std::string type = read_type(&reader);
        
        if (type == "float") {
            return new interpreter_dsp_factory(interpreter_dsp_factory_aux<float>::read(&reader));
        } else if (type == "double") {
            return new interpreter_dsp_factory(interpreter_dsp_factory_aux<double>::read(&reader));
        } else {
            assert(false);
            return 0;
        }
    } else {
        std::cerr << "File Extension is not the one expected (.fbc expected)" << std::endl;
        return 0;
    }
}

EXPORT void writeInterpreterDSPFactoryToMachineFile(interpreter_dsp_factory* factory, const string& machine_code_path)
{
    ofstream writer(machine_code_path.c_str());
    factory->fFactory->write(&writer);
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

EXPORT void interpreter_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    BufferGeneric buffers(input, output);
    fDSP->compute(count, buffers);
}

