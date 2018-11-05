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

#include "interpreter_dsp_aux.hh"
#include "compatibility.hh"

using namespace std;

dsp_factory_table<SDsp_factory> gInterpreterFactoryTable;

// External API

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    return static_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    return (factory) ? gInterpreterFactoryTable.deleteDSPFactory(factory) : false;
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
    return static_cast<interpreter_dsp*>(dsp);
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

    std::stringstream type_reader(type_line);
    std::string       dummy, type;
    type_reader >> dummy;  // Read "interpreter_dsp_factory" token
    type_reader >> type;

    return type;
}

static interpreter_dsp_factory* readInterpreterDSPFactoryFromMachineAux(std::istream* in)
{
    try {
        std::string              type    = read_real_type(in);
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
        std::cerr << "ERROR in readInterpreterDSPFactoryFromMachineAux: " << e.Message();
        return nullptr;
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
    size_t pos  = machine_code_path.find(".fbc");

    if (pos != string::npos) {
        // ifstream reader(machine_code_path);
        ifstream reader(machine_code_path.c_str());
        if (reader.is_open()) {
            return readInterpreterDSPFactoryFromMachineAux(&reader);
        } else {
            std::cerr << "Error opening file '" << machine_code_path << "'" << std::endl;
            return nullptr;
        }
    } else {
        std::cerr << "File Extension is not the one expected (.fbc expected)" << std::endl;
        return nullptr;
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
