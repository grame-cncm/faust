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

EXPORT interpreter_dsp_factory* getInterpreterDSPFactoryFromSHAKey(const string& sha_key)
{
    LOCK_API
    return static_cast<interpreter_dsp_factory*>(gInterpreterFactoryTable.getDSPFactoryFromSHAKey(sha_key));
}

EXPORT bool deleteInterpreterDSPFactory(interpreter_dsp_factory* factory)
{
    LOCK_API
    return (factory) ? gInterpreterFactoryTable.deleteDSPFactory(factory) : false;
 }

EXPORT vector<string> getInterpreterDSPFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
    LOCK_API
    vector<string> res;
    return res;
}

EXPORT vector<string> getAllInterpreterDSPFactories()
{
    LOCK_API
    return gInterpreterFactoryTable.getAllDSPFactories();
}

EXPORT void deleteAllInterpreterDSPFactories()
{
    LOCK_API
    gInterpreterFactoryTable.deleteAllDSPFactories();
}

EXPORT interpreter_dsp::~interpreter_dsp()
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

EXPORT interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    LOCK_API
    dsp* dsp = fFactory->createDSPInstance(this);
    gInterpreterFactoryTable.addDSP(this, dsp);
    return static_cast<interpreter_dsp*>(dsp);
}

// Use the memory manager if needed
EXPORT void interpreter_dsp::operator delete(void* ptr)
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

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcode(const string& bitcode, string& error_msg)
{
    LOCK_API
    return readInterpreterDSPFactoryFromBitcodeAux(bitcode, error_msg);
}

EXPORT string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory)
{
    LOCK_API
    stringstream writer;
    factory->write(&writer, true);
    return writer.str();
}

EXPORT interpreter_dsp_factory* readInterpreterDSPFactoryFromBitcodeFile(const string& bitcode_path, string& error_msg)
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

EXPORT bool writeInterpreterDSPFactoryToBitcodeFile(interpreter_dsp_factory* factory, const string& bitcode_path)
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

EXPORT void interpreter_dsp::init(int sample_rate)
{
    fDSP->init(sample_rate);
}

EXPORT void interpreter_dsp::instanceInit(int sample_rate)
{
    fDSP->instanceInit(sample_rate);
}

EXPORT void interpreter_dsp::instanceConstants(int sample_rate)
{
    fDSP->instanceConstants(sample_rate);
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
