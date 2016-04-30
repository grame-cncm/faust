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

#include <string>
#include <libgen.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "interpreter_dsp_aux.hh"
#include "libfaust.h"

using namespace std;

#define VERSION 0.5

std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Heap;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Direct;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2DirectInvert;

std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Heap;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Direct;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2DirectInvert;

void interpreter_dsp_factory::dump(std::ostream* out)
{
    *out << "interpreter_dsp_factory" << endl;
    *out << "version " << VERSION << endl;
    
    *out << "inputs " << fNumInputs << " ouputs " << fNumOutputs << endl;
    *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize << " sr_offet " << fSROffset << endl;
    
    *out << "user_unterface_block" << endl;
    fUserInterfaceBlock->dump(out);
    
    *out << "init_block" << endl;
    fInitBlock->dump(out);
    
    *out << "control_block" << endl;
    fComputeBlock->dump(out);
    
    *out << "dsp_block" << endl;
    fComputeDSPBlock->dump(out);
}

// Factory parser

interpreter_dsp_factory* interpreter_dsp_factory::parse(std::istream* in)
{
    char dummy_line[256];
    
    // Parse version
    char version[256];
    in->getline(dummy_line, 256);
    in->getline(version, 256);
    
    // Parse inputs/outputs
    char ins_outs[256];
    int inputs, outputs;
    in->getline(ins_outs, 256);
    
    // Parse int/real heap size
    char heap_size[256];
    int int_heap_size, real_heap_size, sr_offset;
    in->getline(heap_size, 256);
    
    // Parse User Interface block
    in->getline(dummy_line, 256);
    FIRUserInterfaceBlockInstruction<float>* ui_block = parseUIBlock(in);
    
    // Parse Init block
    in->getline(dummy_line, 256);
    FIRBlockInstruction<float>* init_block = parseCodeBlock(in);
    
    // Parse Control block
    in->getline(dummy_line, 256);
    FIRBlockInstruction<float>* compute_control_block = parseCodeBlock(in);
    
    // Parse DSP block
    in->getline(dummy_line, 256);
    FIRBlockInstruction<float>* compute_dsp_block = parseCodeBlock(in);
    
    return new interpreter_dsp_factory(inputs, outputs,
                                       int_heap_size,
                                       real_heap_size,
                                       sr_offset,
                                       ui_block,
                                       init_block,
                                       compute_control_block,
                                       compute_dsp_block);
}

FIRUserInterfaceBlockInstruction<float>* interpreter_dsp_factory::parseUIBlock(std::istream* in)
{
    char ui_item[256];
    in->getline(ui_item, 256);
    
    /*
    while (ui_item != ) {
        int opcode, offset;
        std::string label, key, value;
        float int, min, max, step;
    }
    */
    
}

FIRBlockInstruction<float>* interpreter_dsp_factory::parseCodeBlock(std::istream* in)
{
    
}

// Instances

interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    return reinterpret_cast<interpreter_dsp*>(new interpreter_dsp_aux<float>(this));
}

EXPORT interpreter_dsp_factory* getDSPInterpreterFactoryFromSHAKey(const std::string& sha_key)
{}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromFile(const std::string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  std::string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createDSPInterpreterFactoryFromString(base.substr(0, pos), path_to_content(filename), argc, argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    } 
}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromString(const std::string& name_app,
                                                                    const std::string& dsp_content,
                                                                    int argc, const char* argv[], 
                                                                    std::string& error_msg)
{
    int argc1 = argc + 3;
    const char* argv1[32];
    char error_msg_aux[512];

    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "interp";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
    }
    
    interpreter_dsp_factory* factory = compile_faust_interpreter(argc1, argv1,
                                                                name_app.c_str(), 
                                                                dsp_content.c_str(), 
                                                                error_msg_aux);
    error_msg = error_msg_aux;
    return factory;
}   

EXPORT bool deleteDSPInterpreterFactory(interpreter_dsp_factory* factory)
{
    delete factory;
    return true;
}

EXPORT std::vector<std::string> getDSPInterpreterFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
}

EXPORT std::vector<std::string> getAllDSPInterpreterFactories()
{}

EXPORT void deleteAllDSPInterpreterFactories()
{}

EXPORT interpreter_dsp* createDSPInterpreterInstance(interpreter_dsp_factory* factory)
{
    return factory->createDSPInstance();
}

EXPORT void deleteDSPInterpreterInstance(interpreter_dsp* dsp)
{
    delete reinterpret_cast<interpreter_dsp_aux<float>*>(dsp);
}

EXPORT interpreter_dsp_factory* readDSPInterpreterFactoryFromMachine(const std::string& machine_code)
{
    std::stringstream reader(machine_code);
    return interpreter_dsp_factory::parse(&reader);
}

EXPORT std::string writeDSPInterpreterFactoryToMachine(interpreter_dsp_factory* factory)
{
    std::stringstream writer;
    factory->dump(&writer);
    return writer.str();
}

EXPORT interpreter_dsp_factory* readDSPInterpreterFactoryFromMachineFile(const std::string& machine_code_path)
{
    std::ifstream reader(machine_code_path);
    return interpreter_dsp_factory::parse(&reader);
}

EXPORT void writeDSPInterpreterFactoryToMachineFile(interpreter_dsp_factory* factory, const std::string& machine_code_path)
{
    std::ofstream writer(machine_code_path);
    factory->dump(&writer);
}

