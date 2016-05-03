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
#include <stdlib.h>

#include "interpreter_dsp_aux.hh"

#ifndef LOADER
#include "libfaust.h"
#endif

using namespace std;

map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Heap;
map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Stack;
map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Direct;
map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2DirectInvert;

map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Heap;
map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Direct;
map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2DirectInvert;

static inline string unquote(const string& str)
{
    return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
}

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

void interpreter_dsp_factory::write(ostream* out)
{
    *out << "interpreter_dsp_factory" << endl;
    *out << "version " << INTERP_FILE_VERSION << endl;
    
    *out << "name " << fName << endl;
    
    *out << "inputs " << fNumInputs << " outputs " << fNumOutputs << endl;
    *out << "int_heap_size " << fIntHeapSize << " real_heap_size " << fRealHeapSize
         << " sr_offset " << fSROffset << " count_offset " << fCountOffset << endl;
    
    *out << "user_unterface_block" << endl;
    fUserInterfaceBlock->write(out);
    
    *out << "init_block" << endl;
    fInitBlock->write(out);
    
    *out << "control_block" << endl;
    fComputeBlock->write(out);
    
    *out << "dsp_block" << endl;
    fComputeDSPBlock->write(out);
}

// Factory reader

interpreter_dsp_factory* interpreter_dsp_factory::read(istream* in)
{
    string dummy, value;
    
    // Read "interpreter_dsp_factory" line
    getline(*in, dummy);
    
    // Read "version" line
    string version;
    float version_num;
    getline(*in, version);
    
    stringstream version_reader(version);
    version_reader >> dummy;   // Read "version" token
    version_reader >> value; version_num = strtof(value.c_str(), 0);
    
    if (INTERP_FILE_VERSION != version_num) {
        cerr << "Interpreter file format version '" << version_num << "' different from compiled one '" << INTERP_FILE_VERSION << "'" << endl;
        return 0;
    }
    
    // Read name
    string name, factory_name;
    getline(*in, name);
    
    stringstream name_reader(name);
    name_reader >> dummy;   // Read "name" token
    name_reader >> factory_name;
    
    // Read inputs/outputs
    string ins_outs;
    int inputs, outputs;
    getline(*in, ins_outs);
    
    stringstream in_out_reader(ins_outs);
    
    in_out_reader >> dummy; // Read "inputs" token
    in_out_reader >> value; inputs = strtol(value.c_str(), 0, 10);
    
    in_out_reader >> dummy; // Read "outputs" token
    in_out_reader >> value; outputs = strtol(value.c_str(), 0, 10);
    
    // Read int/real heap size and sr offset
    string heap_size;
    int int_heap_size, real_heap_size, sr_offset, count_offset;
    getline(*in, heap_size);
    
    stringstream heap_size_reader(heap_size);
    
    heap_size_reader >> dummy; // Read "int_heap_size" token
    heap_size_reader >> value; int_heap_size = strtol(value.c_str(), 0, 10);
    
    heap_size_reader >> dummy; // Read "real_heap_size" token
    heap_size_reader >> value; real_heap_size = strtol(value.c_str(), 0, 10);
    
    heap_size_reader >> dummy; // Read "sr_offet" token
    heap_size_reader >> value; sr_offset = strtol(value.c_str(), 0, 10);
    
    heap_size_reader >> dummy; // Read "count_offset" token
    heap_size_reader >> value; count_offset = strtol(value.c_str(), 0, 10);
    
    // Read user interface block
    getline(*in, dummy);    // Read "user_unterface_block" line
    FIRUserInterfaceBlockInstruction<float>* ui_block = readUIBlock(in);
    
    // Read init block
    getline(*in, dummy);    // Read "init_block" line
    FIRBlockInstruction<float>* init_block = readCodeBlock(in);
    
    // Read control block
    getline(*in, dummy);    // Read "control_block" line
    FIRBlockInstruction<float>* compute_control_block = readCodeBlock(in);
    
    // Read DSP block
    getline(*in, dummy);    // Read "dsp_block" line
    FIRBlockInstruction<float>* compute_dsp_block = readCodeBlock(in);
    
    return new interpreter_dsp_factory(factory_name,
                                       version_num,
                                       inputs, outputs,
                                       int_heap_size,
                                       real_heap_size,
                                       sr_offset,
                                       count_offset,
                                       ui_block,
                                       init_block,
                                       compute_control_block,
                                       compute_dsp_block);
}

FIRUserInterfaceBlockInstruction<float>* interpreter_dsp_factory::readUIBlock(istream* in)
{
    string dummy, value, line;
    int size;
    
    // Read "block_size" line
    getline(*in, line);
    stringstream line_reader(line);
    
    line_reader >> dummy; // Read "block_size" token
    line_reader >> value; size = strtol(value.c_str(), 0, 10);
    
    FIRUserInterfaceBlockInstruction<float>* ui_block = new FIRUserInterfaceBlockInstruction<float>();
    
    for (int i = 0; i < size; i++) {
        getline(*in, line);
        stringstream item_line_reader(line);
        ui_block->push(readUIInstruction(&item_line_reader));
    }
    
    return ui_block;
}

FIRUserInterfaceInstruction<float>* interpreter_dsp_factory::readUIInstruction(stringstream* inst)
{
    FIRBlockInstruction<float>::Opcode opcode;
    int offset;
    float init, min, max, step;
    string dummy, value, label, key, val;
    
    *inst >> dummy;  // Read "opcode" token
    *inst >> value; opcode = FIRBlockInstruction<float>::Opcode(strtol(value.c_str(), 0, 10));
    *inst >> dummy;  // Read opcode string representation (that is not used)
    
    *inst >> dummy;  // Read "offset" token
    *inst >> value; offset = strtol(value.c_str(), 0, 10);
    
    *inst >> dummy;  // Read "label" token
    *inst >> label;  // Read "label" content
    
    *inst >> dummy;  // Read "key" token
    *inst >> key;    // Read "key" content
    
    *inst >> dummy;  // Read "value" token
    *inst >> val;    // Read "value" conent
    
    *inst >> dummy;  // Read "init" token
    *inst >> value; init = strtof(value.c_str(), 0);
    
    *inst >> dummy;  // Read "min" token
    *inst >> value; min = strtof(value.c_str(), 0);
    
    *inst >> dummy;  // Read "max" token
    *inst >> value; max = strtof(value.c_str(), 0);
    
    *inst >> dummy;  // Read "step" token
    *inst >> value; step = strtof(value.c_str(), 0);

    return new FIRUserInterfaceInstruction<float>(opcode, offset, unquote(label), unquote(key), unquote(val), init, min, max, step);
}

FIRBlockInstruction<float>* interpreter_dsp_factory::readCodeBlock(istream* in)
{
    string dummy, value, line;
    int size;
    
    // Read "block_size" line
    getline(*in, line);
    stringstream line_reader(line);
    
    line_reader >> dummy; // Read "block_size" token
    line_reader >> value; size = strtol(value.c_str(), 0, 10);
    
    FIRBlockInstruction<float>* code_block = new FIRBlockInstruction<float>();
    
    for (int i = 0; i < size; i++) {
        getline(*in, line);
        stringstream inst_line_reader(line);
        FIRBasicInstruction<float>* inst = readCodeInstruction(&inst_line_reader, in);
        if (inst->fOpcode == FIRInstruction::kCondBranch) {   // Special case for loops
            inst->fBranch1 = code_block;
        }
        code_block->push(inst);
    }
    
    return code_block;
}

FIRBasicInstruction<float>* interpreter_dsp_factory::readCodeInstruction(std::istream* inst, std::istream* in)
{
    FIRBlockInstruction<float>::Opcode opcode;
    int offset1, offset2, val_int;
    float val_real;
    string dummy, value;
    
    *inst >> dummy;  // Read "opcode" token
    *inst >> value; opcode = FIRBlockInstruction<float>::Opcode(strtol(value.c_str(), 0, 10));
    
    *inst >> dummy;  // Read opcode string representation (that is not used)
    
    *inst >> dummy;  // Read "int" token
    *inst >> value; val_int = strtol(value.c_str(), 0, 10);
    
    *inst >> dummy;  // Read "real" token
    *inst >> value; val_real = strtof(value.c_str(), 0);
    
    *inst >> dummy;  // Read "offset1" token
    *inst >> value; offset1 = strtol(value.c_str(), 0, 10);
    
    *inst >> dummy;  // Read "offset2" token
    *inst >> value; offset2 = strtol(value.c_str(), 0, 10);
    
    FIRBlockInstruction<float>* branch1 = 0;
    FIRBlockInstruction<float>* branch2 = 0;
    
    // Possibly read sub-blocks
    if (opcode == FIRInstruction::kIf) {
        branch1 = readCodeBlock(in);  // consume 'in'
        branch2 = readCodeBlock(in);  // consume 'in'
    } else if (opcode == FIRInstruction::kLoop) {
        branch1 = readCodeBlock(in);  // consume 'in'
    }
    
    return new FIRBasicInstruction<float>(opcode, val_int, val_real, offset1, offset2, branch1, branch2);
}

// Instances

interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
    return reinterpret_cast<interpreter_dsp*>(new interpreter_dsp_aux<float>(this));
}

EXPORT interpreter_dsp_factory* getDSPInterpreterFactoryFromSHAKey(const string& sha_key)
{
    // TODO
    return 0;
}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromFile(const string& filename, 
                                                                  int argc, const char* argv[], 
                                                                  string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createDSPInterpreterFactoryFromString(base.substr(0, pos), path_to_content(filename), argc, argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return 0;
    } 
}

EXPORT interpreter_dsp_factory* createDSPInterpreterFactoryFromString(const string& name_app,
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
    
    interpreter_dsp_factory* factory = compile_faust_interpreter(argc1, argv1,
                                                                 name_app.c_str(),
                                                                 dsp_content.c_str(),
                                                                 error_msg_aux);
    error_msg = error_msg_aux;
    return factory;
#endif
}

EXPORT bool deleteDSPInterpreterFactory(interpreter_dsp_factory* factory)
{
    delete factory;
    return true;
}

EXPORT vector<string> getDSPInterpreterFactoryLibraryList(interpreter_dsp_factory* factory)
{
    // TODO
    vector<string> res;
    return res;
}

EXPORT vector<string> getAllDSPInterpreterFactories()
{
    // TODO
    vector<string> res;
    return res;
}

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

EXPORT interpreter_dsp_factory* readDSPInterpreterFactoryFromMachine(const string& machine_code)
{
    stringstream reader(machine_code);
    return interpreter_dsp_factory::read(&reader);
}

EXPORT string writeDSPInterpreterFactoryToMachine(interpreter_dsp_factory* factory)
{
    stringstream writer;
    factory->write(&writer);
    return writer.str();
}

EXPORT interpreter_dsp_factory* readDSPInterpreterFactoryFromMachineFile(const string& machine_code_path)
{
    string base = basename((char*)machine_code_path.c_str());
    size_t pos = machine_code_path.find(".fbc");
    
    if (pos != string::npos) {
        ifstream reader(machine_code_path);
        return interpreter_dsp_factory::read(&reader);
    } else {
        std::cerr << "File Extension is not the one expected (.fbc expected)" << std::endl;
        return 0;
    }
}

EXPORT void writeDSPInterpreterFactoryToMachineFile(interpreter_dsp_factory* factory, const string& machine_code_path)
{
    ofstream writer(machine_code_path);
    factory->write(&writer);
}

