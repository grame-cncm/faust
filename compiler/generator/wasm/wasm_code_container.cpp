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

#include "wasm_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"
#include "json_instructions.hh"

using namespace std;

/*
 WASM module description:
 
 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from the from JS "global.Math",
   or are externally implemented (log10 in JS using log, fmod in JS, remainder in JS)
 - local variables have to be declared first on the block, before being actually initialized or set : this is done using MoveVariablesInFront3
 - 'faustpower' function actually fallback to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - LocalVariableCounter visitor allows to count and create local variables of each types
 - FunAndTypeCounter visitor allows to count and create function types and global variable offset
 - memory can be allocated internally in the module and exported, or externally in JS and imported

*/

dsp_factory_base* WASMCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), fHelper.str());
}

WASMCodeContainer::WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory):fOut(out)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    fInternalMemory = internal_memory;
    
    // Allocate one static visitor to be shared by main and sub containers
    if (!gGlobal->gWASMVisitor) {
        gGlobal->gWASMVisitor = new WASMInstVisitor(&fBinaryOut, internal_memory);
    }
}

CodeContainer* WASMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new WASMScalarCodeContainer(name, 0, 1, fOut, sub_container_type, true);
}

CodeContainer* WASMCodeContainer::createScalarContainer(const string& name, int sub_container_type, bool internal_memory)
{
    return new WASMScalarCodeContainer(name, 0, 1, fOut, sub_container_type, internal_memory);
}

CodeContainer* WASMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool internal_memory)
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
        throw faustexception("OpenMP : OpenMP not supported for WebAssembly\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("Scheduler mode not supported for WebAssembly\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("Vector mode not supported for WebAssembly\n");
    } else {
        container = new WASMScalarCodeContainer(name, numInputs, numOutputs, dst, kInt, internal_memory);
    }

    return container;
}

DeclareFunInst* WASMCodeContainer::generateClassInit(const string& name, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt));
    
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    DspRenamer renamer;
    BlockInst* renamed = renamer.getCode(fStaticInitInstructions);
    BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
    
    MoveVariablesInFront3 mover;
    BlockInst* block = mover.getCode(inlined);
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceClear(const string& name, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    DspRenamer renamer;
    BlockInst* renamed = renamer.getCode(fClearInstructions);
    
    MoveVariablesInFront3 mover;
    BlockInst* block = mover.getCode(renamed);
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceConstants(const string& name, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt));
    
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    DspRenamer renamer;
    BlockInst* renamed = renamer.getCode(fInitInstructions);
    BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
    
    MoveVariablesInFront3 mover;
    BlockInst* block = mover.getCode(inlined);
  
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceResetUserInterface(const string& name, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    DspRenamer renamer;
    BlockInst* renamed = renamer.getCode(fResetUserInterfaceInstructions);
    
    MoveVariablesInFront3 mover;
    BlockInst* block = mover.getCode(renamed);
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

// Scalar
WASMScalarCodeContainer::WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type, bool internal_memory)
    :WASMCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
     fSubContainerType = sub_container_type;
}

WASMScalarCodeContainer::~WASMScalarCodeContainer()
{}

// Special version that uses MoveVariablesInFront3 to inline waveforms...
DeclareFunInst* WASMCodeContainer::generateInstanceInitFun(const string& name, bool ismethod, bool isvirtual, bool addreturn)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt));
    BlockInst* init_block = InstBuilder::genBlockInst();
    
    {
        MoveVariablesInFront3 mover;
        init_block->pushBackInst(mover.getCode(fStaticInitInstructions));
    }
    {
        MoveVariablesInFront3 mover;
        init_block->pushBackInst(mover.getCode(fInitInstructions));
    }
    {
        MoveVariablesInFront3 mover;
        init_block->pushBackInst(mover.getCode(fPostInitInstructions));
    }
    {
        MoveVariablesInFront3 mover;
        init_block->pushBackInst(mover.getCode(fResetUserInterfaceInstructions));
    }
    {
        MoveVariablesInFront3 mover;
        init_block->pushBackInst(mover.getCode(fClearInstructions));
    }
    
    if (addreturn) { init_block->pushBackInst(InstBuilder::genRetInst()); }
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, init_block);
}

void WASMCodeContainer::produceInternal()
{
    // Fields generation
    generateGlobalDeclarations(gGlobal->gWASMVisitor);
    generateDeclarations(gGlobal->gWASMVisitor);
}

void WASMCodeContainer::produceClass()
{
    // Module definition
    gGlobal->gWASMVisitor->generateModuleHeader();
    
    // Sub containers : before functions generation
    mergeSubContainers();
    
    // After field declaration...
    generateSubContainers();
    
    // Mthematical functions and global variables are handled in a separated visitor that creates functions types and global variable offset
    generateGlobalDeclarations(gGlobal->gWASMVisitor->getFunAndTypeCounter());
    
    // Update struct offset to take account of global variables defined in 'generateGlobalDeclarations' in the separated visitor
    gGlobal->gWASMVisitor->updateStructOffsetAndFieldTable();
    
    // Functions types
    gGlobal->gWASMVisitor->generateFunTypes();
    
    // Imported functions
    gGlobal->gWASMVisitor->generateImports(fNumInputs + fNumOutputs, fInternalMemory);
    
    // Functions signature
    gGlobal->gWASMVisitor->generateFuncSignatures();
    
    // Fields : compute the structure size to use in 'new'
    generateDeclarations(gGlobal->gWASMVisitor);
    
    // Memory
    if (fInternalMemory) {
        gGlobal->gWASMVisitor->generateMemory(fNumInputs + fNumOutputs);
    }
    
    // Exports
    gGlobal->gWASMVisitor->generateExports(fInternalMemory);
 
    // Functions
    int32_t functions_start = gGlobal->gWASMVisitor->startSection(BinaryConsts::Section::Code);
    fBinaryOut << U32LEB(14); // num functions
    
    // Internal functions in alphabetical order
    
    // 1) classInit
    generateClassInit("classInit", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 2) compute
    generateCompute();
    
    // 3) getNumInputs
    generateGetInputs("getNumInputs", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 4) getNumOutputs
    generateGetOutputs("getNumOutputs", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 5) getParamValue (adhoc generation for now since currently FIR cannot be generated to handle this case)
    gGlobal->gWASMVisitor->generateGetParamValue();
   
    // 6) getSampleRate
    generateGetSampleRate(false, false)->accept(gGlobal->gWASMVisitor);
    
    // 7) init
    generateInit(false, false)->accept(gGlobal->gWASMVisitor);
    
    // 8) instanceClear
    generateInstanceClear("instanceClear", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 9) instanceConstants
    generateInstanceConstants("instanceConstants", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 10) instanceInit
     generateInstanceInit(false, false)->accept(gGlobal->gWASMVisitor);
    
    // 11) instanceResetUserInterface
    generateInstanceResetUserInterface("instanceResetUserInterface", false, false)->accept(gGlobal->gWASMVisitor);
    
    // Always generated mathematical functions
    
    // 12) max_i
    WASInst::generateIntMax()->accept(gGlobal->gWASMVisitor);
    // 13) min_i
    WASInst::generateIntMin()->accept(gGlobal->gWASMVisitor);
    
    // 14) setParamValue (adhoc generation for now since currently FIR cannot be generated to handle this case)
    gGlobal->gWASMVisitor->generateSetParamValue();
    
    // Possibly generate separated functions : TO REMOVE ?
    generateComputeFunctions(gGlobal->gWASMVisitor);
    
    gGlobal->gWASMVisitor->finishSection(functions_start);
   
    // Finally produce output stream
    fBinaryOut.writeTo(*fOut);
    
    // Helper code
    int n = 0;
    
    // User interface : prepare the JSON string
    JSONInstVisitor json_visitor(fNumInputs, fNumOutputs);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);
    
    // Generate JSON and getSize
    tab(n, fHelper); fHelper << "/* Helper code generated with FAUST version " << FAUSTVERSION << " */\n";
    tab(n, fHelper); fHelper << "function getSize" << fKlassName << "() {";
        tab(n+1, fHelper);
        fHelper << "return " << gGlobal->gWASMVisitor->getStructSize() << ";";
        printlines(n+1, fUICode, fHelper);
    tab(n, fHelper); fHelper << "}";
    tab(n, fHelper);
    
    // Fields to path
    tab(n, fHelper); fHelper << "function getPathTable" << fKlassName << "() {";
        tab(n+1, fHelper); fHelper << "var pathTable = [];";
        map <string, string>::iterator it;
        map <string, WASMInstVisitor::MemoryDesc>& fieldTable = gGlobal->gWASMVisitor->getFieldTable();
        for (it = json_visitor.fPathTable.begin(); it != json_visitor.fPathTable.end(); it++) {
            WASMInstVisitor::MemoryDesc tmp = fieldTable[(*it).first];
            tab(n+1, fHelper); fHelper << "pathTable[\"" << (*it).second << "\"] = " << tmp.fOffset << ";";
        }
        tab(n+1, fHelper); fHelper << "return pathTable;";
    tab(n, fHelper); fHelper << "}";
    
    // Generate JSON
    tab(n, fHelper);
    tab(n, fHelper); fHelper << "function getJSON" << fKlassName << "() {";
        tab(n+1, fHelper);
        fHelper << "return \""; fHelper << json_visitor.JSON(true); fHelper << "\";";
        printlines(n+1, fUICode, fHelper);
    tab(n, fHelper); fHelper << "}";
    
    // Metadata declaration
    tab(n, fHelper);
    tab(n, fHelper); fHelper << "function metadata" << fKlassName << "(m) {";
    for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(n+1, fHelper); fHelper << "m.declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(n+1, fHelper); fHelper << "m.declare(\"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                    tab(n+1, fHelper); fHelper << "m.declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }
    tab(n, fHelper); fHelper << "}" << endl << endl;
}

void WASMScalarCodeContainer::generateCompute()
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt));
    args.push_back(InstBuilder::genNamedTyped("inputs", Typed::kVoid_ptr));
    args.push_back(InstBuilder::genNamedTyped("outputs", Typed::kVoid_ptr));
    
    fComputeBlockInstructions->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
    MoveVariablesInFront2 mover;
    BlockInst* block = mover.getCode(fComputeBlockInstructions, true);
    
    // Creates function and visit it
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    InstBuilder::genDeclareFunInst("compute", fun_type, block)->accept(gGlobal->gWASMVisitor);
}


