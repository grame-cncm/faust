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
#include "interpreter_dsp_aux.hh"
#include "libfaust.h"

using namespace std;

std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Heap;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2Direct;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRMath2DirectInvert;

std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Heap;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2Direct;
std::map<FIRInstruction::Opcode, FIRInstruction::Opcode> FIRInstruction::gFIRExtendedMath2DirectInvert;

void interpreter_dsp_factory::dump()
{
    cout << "------interpreter_dsp_factory------" << endl;
    cout << "fNumInputs = " << fNumInputs << " fNumOutputs = " << fNumOutputs << endl;
    cout << "fRealHeapSize = " << fRealHeapSize << " fIntHeapSize = " << fIntHeapSize << endl;
    cout << "------Init block------" << endl;
    fInitBlock->dump();
    cout << "------control block------" << endl;
    fComputeBlock->dump();
    cout << "------DSP block------" << endl;
    fComputeDSPBlock->dump();
}

interpreter_dsp* interpreter_dsp_factory::createDSPInstance()
{
     return reinterpret_cast<interpreter_dsp*>(new interpreter_dsp_aux<float>(fNumInputs, 
                                                                            fNumOutputs, 
                                                                            fRealHeapSize, 
                                                                            fIntHeapSize,
                                                                            fSROffset,
                                                                            fUserInterfaceBlock, 
                                                                            fInitBlock, 
                                                                            fComputeBlock, 
                                                                            fComputeDSPBlock));
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
    
    interpreter_dsp_factory* factory  = compile_faust_interpreter(argc1, argv1, 
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

