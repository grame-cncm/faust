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

#include "wast_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"
#include "json_instructions.hh"

using namespace std;

/*
 WAST backend and module description:
 
 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from JS "global.Math",
   or are externally implemented (fmod and remainder in JS)
 - local variables have to be declared first on the block, before being actually initialized or set: this is done using MoveVariablesInFront3
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - memory can be allocated internally in the module and exported, or externally in JS and imported
 - the JSON string is written at offset 0 in a data segment. This string *has* to be converted in a JS string *before* using the DSP instance
 - memory module size cannot be written while generating the output stream, since DSP size is computed when inlining subcontainers and waveform. 
 The final memory size is finally written after module code generation.
 - in Load/Store, check if address is constant, so that to be used as an 'offset'
 - move loop 'i' variable by bytes instead of frames to save index code generation of input/output accesses (gLoopVarInBytes)
 - offset of inputs/outputs are constant, so can be directly generated

*/

dsp_factory_base* WASTCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), fHelper.str());
}

WASTCodeContainer::WASTCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory):fOut(out)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    fInternalMemory = internal_memory;
    
    // Allocate one static visitor to be shared by main and sub containers
    if (!gGlobal->gWASTVisitor) {
        gGlobal->gWASTVisitor = new WASTInstVisitor(&fOutAux, fInternalMemory);
    }
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new WASTScalarCodeContainer(name, 0, 1, &fOutAux, sub_container_type, true);
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type, bool internal_memory)
{
    return new WASTScalarCodeContainer(name, 0, 1, &fOutAux, sub_container_type, internal_memory);
}

CodeContainer* WASTCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool internal_memory)
{
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for WebAssembly\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for WebAssembly\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for WebAssembly\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for WebAssembly\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for WebAssembly\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for WebAssembly\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for WebAssembly\n");
    } else {
        container = new WASTScalarCodeContainer(name, numInputs, numOutputs, dst, kInt, internal_memory);
    }

    return container;
}

// Scalar
WASTScalarCodeContainer::WASTScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type, bool internal_memory)
    :WASTCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
     fSubContainerType = sub_container_type;
}

WASTScalarCodeContainer::~WASTScalarCodeContainer()
{}

// Special version that uses MoveVariablesInFront3 to inline waveforms...
DeclareFunInst* WASTCodeContainer::generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt32));
    BlockInst* init_block = InstBuilder::genBlockInst();
    
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fStaticInitInstructions));
  
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fInitInstructions));
    
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fPostInitInstructions));
    
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fResetUserInterfaceInstructions));
    
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fClearInstructions));
    
    if (addreturn) { init_block->pushBackInst(InstBuilder::genRetInst()); }
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, init_block);
}

void WASTCodeContainer::produceInternal()
{
    // Fields generation
    generateGlobalDeclarations(gGlobal->gWASTVisitor);
    generateDeclarations(gGlobal->gWASTVisitor);
}

void WASTCodeContainer::produceClass()
{
    int n = 0;
  
    gGlobal->gWASTVisitor->Tab(n);
    
    tab(n, fOutAux); fOutAux << "(module";
    
        // Global declarations (mathematical functions, global variables...)
        gGlobal->gWASTVisitor->Tab(n+1);
    
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first
        generateGlobalDeclarations(gGlobal->gWASTVisitor);
    
        // Exported functions
        tab(n+1, fOutAux); fOutAux << "(export \"getNumInputs\" (func $getNumInputs))";
        tab(n+1, fOutAux); fOutAux << "(export \"getNumOutputs\" (func $getNumOutputs))";
        tab(n+1, fOutAux); fOutAux << "(export \"getSampleRate\" (func $getSampleRate))";
        tab(n+1, fOutAux); fOutAux << "(export \"init\" (func $init))";
        tab(n+1, fOutAux); fOutAux << "(export \"instanceInit\" (func $instanceInit))";
        tab(n+1, fOutAux); fOutAux << "(export \"instanceConstants\" (func $instanceConstants))";
        tab(n+1, fOutAux); fOutAux << "(export \"instanceResetUserInterface\" (func $instanceResetUserInterface))";
        tab(n+1, fOutAux); fOutAux << "(export \"instanceClear\" (func $instanceClear))";
        tab(n+1, fOutAux); fOutAux << "(export \"setParamValue\" (func $setParamValue))";
        tab(n+1, fOutAux); fOutAux << "(export \"getParamValue\" (func $getParamValue))";
        tab(n+1, fOutAux); fOutAux << "(export \"compute\" (func $compute))";
    
        // General imports
        tab(n+1, fOutAux); fOutAux << "(import \"env\" \"memoryBase\" (global $memoryBase i32))";
        tab(n+1, fOutAux); fOutAux << "(import \"env\" \"tableBase\" (global $tableBase i32))";
    
        // Fields : compute the structure size to use in 'new'
        gGlobal->gWASTVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gWASTVisitor);
        
        // After field declaration
        generateSubContainers();
    
        // Keep location of memory generation
        streampos begin_memory = fOutAux.tellp();
    
        // Always generated mathematical functions
        tab(n+1, fOutAux);
        WASInst::generateIntMin()->accept(gGlobal->gWASTVisitor);
        WASInst::generateIntMax()->accept(gGlobal->gWASTVisitor);
    
        // getNumInputs/getNumOutputs
        generateGetInputs("getNumInputs", "dsp", false, false)->accept(gGlobal->gWASTVisitor);
        generateGetOutputs("getNumOutputs", "dsp", false, false)->accept(gGlobal->gWASTVisitor);
    
        // Inits
        tab(n+1, fOutAux); fOutAux << "(func $classInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, fOutAux); gGlobal->gWASTVisitor->Tab(n+2);
            {
                BlockInst* inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
                generateWASTBlock(inlined);
            }
        tab(n+1, fOutAux); fOutAux << ")";
    
        tab(n+1, fOutAux); fOutAux << "(func $instanceConstants (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, fOutAux); gGlobal->gWASTVisitor->Tab(n+2);
            {
                BlockInst* inlined = inlineSubcontainersFunCalls(fInitInstructions);
                generateWASTBlock(inlined);
            }
        tab(n+1, fOutAux); fOutAux << ")";
    
        tab(n+1, fOutAux); fOutAux << "(func $instanceResetUserInterface (param $dsp i32)";
            tab(n+2, fOutAux); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateWASTBlock(DspRenamer().getCode(fResetUserInterfaceInstructions));
            }
        tab(n+1, fOutAux); fOutAux << ")";
    
        tab(n+1, fOutAux); fOutAux << "(func $instanceClear (param $dsp i32)";
            tab(n+2, fOutAux); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateWASTBlock(DspRenamer().getCode(fClearInstructions));
            }
        tab(n+1, fOutAux); fOutAux << ")";
    
        gGlobal->gWASTVisitor->Tab(n+1);
    
        // init
        generateInit("dsp", false, false)->accept(gGlobal->gWASTVisitor);
    
        // instanceInit
        generateInstanceInit("dsp", false, false)->accept(gGlobal->gWASTVisitor);
    
        // getSampleRate
        generateGetSampleRate("dsp", false, false)->accept(gGlobal->gWASTVisitor);
    
        // setParamValue
        tab(n+1, fOutAux); fOutAux << "(func $setParamValue (param $dsp i32) (param $index i32) (param $value " << realStr << ")";
            tab(n+2, fOutAux); fOutAux << "(" << realStr << ".store ";
                tab(n+3, fOutAux); fOutAux << "(i32.add (get_local $dsp) (get_local $index))";
                tab(n+3, fOutAux); fOutAux << "(get_local $value)";
            tab(n+2, fOutAux); fOutAux << ")";
        tab(n+1, fOutAux); fOutAux << ")";
    
        // getParamValue
        tab(n+1, fOutAux); fOutAux << "(func $getParamValue (param $dsp i32) (param $index i32) (result " << realStr << ")";
            tab(n+2, fOutAux); fOutAux << "(return (" << realStr << ".load (i32.add (get_local $dsp) (get_local $index))))";
        tab(n+1, fOutAux); fOutAux << ")";
    
        // compute
        generateCompute(n);
        
        // Possibly generate separated functions
        gGlobal->gWASTVisitor->Tab(n+1);
        tab(n+1, fOutAux);
        generateComputeFunctions(gGlobal->gWASTVisitor);
    
    tab(n, fOutAux); fOutAux << ")";
    tab(n, fOutAux);
    
    // JSON generation
    
    // Prepare compilation options
    stringstream options;
    gGlobal->printCompilationOptions(options);
    
    stringstream size;
    size << gGlobal->gWASTVisitor->getStructSize();
    
    JSONInstVisitor json_visitor1;
    generateUserInterface(&json_visitor1);
    
    map <string, string>::iterator it;
    std::map<std::string, int> path_index_table;
    map <string, MemoryDesc>& fieldTable1 = gGlobal->gWASTVisitor->getFieldTable();
    for (it = json_visitor1.fPathTable.begin(); it != json_visitor1.fPathTable.end(); it++) {
        // Get field index
        MemoryDesc tmp = fieldTable1[(*it).first];
        path_index_table[(*it).second] = tmp.fOffset;
    }
    
    // "name", "filename" found in medata
    JSONInstVisitor json_visitor2("", "", fNumInputs, fNumOutputs, "", "", FAUSTVERSION, options.str(), size.str(), path_index_table);
    generateUserInterface(&json_visitor2);
    generateMetaData(&json_visitor2);
    
    string json = json_visitor2.JSON(true);
    
    // Now that DSP structure size is known, concatenate stream parts to produce the final stream
    string tmp_aux = fOutAux.str();
    string begin = tmp_aux.substr(0, begin_memory);
    string end = tmp_aux.substr(begin_memory);
    
    // Write begining of code stream on *fOut
    *fOut << begin;
    
    // Insert memory generation
    tab(n+1, *fOut);
    if (fInternalMemory) {
        *fOut << "(memory (export \"memory\") ";
        // Since JSON is written in data segment at offset 0, the memory size must be computed taking account JSON size and DSP + audio buffer size
        *fOut << genMemSize(gGlobal->gWASTVisitor->getStructSize(), fNumInputs + fNumOutputs, json.size()) << ")"; // memory initial pages
    } else {
        // Memory size set by JS code, so use a minimum value that contains the data segment size (shoud be OK for any JSON)
        *fOut << "(import \"env\" \"memory\" (memory $0 1))";
    }
    
    // Generate one data segment containing the JSON string starting at offset 0
    tab(n+1, *fOut);
    *fOut << "(data (i32.const 0) \"" << json << "\")";
    
    // And write end of code stream on *fOut
    *fOut << end;
    
    // Helper code
    
    // Generate JSON and getSize
    tab(n, fHelper); fHelper << "/*\n" << "Code generated with Faust version " << FAUSTVERSION << endl;
    fHelper << "Compilation options: ";
    gGlobal->printCompilationOptions(fHelper);
    fHelper << "\n*/\n";
    
    // Generate JSON
    tab(n, fHelper); fHelper << "function getJSON" << fKlassName << "() {";
        tab(n+1, fHelper);
        fHelper << "return \""; fHelper << json; fHelper << "\";";
        printlines(n+1, fUICode, fHelper);
    tab(n, fHelper); fHelper << "}\n";
}

void WASTScalarCodeContainer::generateCompute(int n)
{
   tab(n+1, fOutAux); fOutAux << "(func $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)";
        tab(n+2, fOutAux);
        gGlobal->gWASTVisitor->Tab(n+2);
    
        // Loop 'i' variable is moved by bytes
        BlockInst* compute_block = InstBuilder::genBlockInst();
        compute_block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount, gGlobal->gLoopVarInBytes));
    
        // Remove unecessary cast
        compute_block = CastRemover().getCode(compute_block);
    
        // Inline "max_i" call
        compute_block = FunctionCallInliner(WASInst::generateIntMax()).getCode(compute_block);
    
        // Inline "min_i" call
        compute_block = FunctionCallInliner(WASInst::generateIntMin()).getCode(compute_block);
    
        // Push the loop in compute block
        fComputeBlockInstructions->pushBackInst(compute_block);
    
        // Put local variables at the begining
        BlockInst* block = MoveVariablesInFront2().getCode(fComputeBlockInstructions, true);
    
        block->accept(gGlobal->gWASTVisitor);
    tab(n+1, fOutAux); fOutAux << ")";
}

DeclareFunInst* WASInst::generateIntMin()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");
    
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(v1, Typed::kInt32));
    args.push_back(InstBuilder::genNamedTyped(v2, Typed::kInt32));
    
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genSelect2Inst(InstBuilder::genLessThan(InstBuilder::genLoadFunArgsVar(v1),
                                                                                                     InstBuilder::genLoadFunArgsVar(v2)),
                                                                            InstBuilder::genLoadFunArgsVar(v1),
                                                                            InstBuilder::genLoadFunArgsVar(v2))));
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt32), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("min_i", fun_type, block);
}

DeclareFunInst* WASInst::generateIntMax()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");
    
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(v1, Typed::kInt32));
    args.push_back(InstBuilder::genNamedTyped(v2, Typed::kInt32));
    
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genSelect2Inst(InstBuilder::genLessThan(InstBuilder::genLoadFunArgsVar(v1),
                                                                                                     InstBuilder::genLoadFunArgsVar(v2)),
                                                                            InstBuilder::genLoadFunArgsVar(v2),
                                                                            InstBuilder::genLoadFunArgsVar(v1))));
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt32), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("max_i", fun_type, block);
}

// Vector
WASTVectorCodeContainer::WASTVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory)
    :WASTCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = -1;
}

WASTVectorCodeContainer::~WASTVectorCodeContainer()
{}

void WASTVectorCodeContainer::generateCompute(int n)
{}
