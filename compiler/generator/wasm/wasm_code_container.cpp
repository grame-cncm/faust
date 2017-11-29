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
#include "rn_base64.h"

using namespace std;

/*
 WASM backend and module description:
 
 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from JS "global.Math",
   or are externally implemented (fmod and remainder in JS)
 - local variables have to be declared first on the block, before being actually initialized or set : this is done using MoveVariablesInFront3
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - LocalVariableCounter visitor allows to count and create local variables of each types
 - FunAndTypeCounter visitor allows to count and create function types and global variable offset
 - memory can be allocated internally in the module and exported, or externally in JS and imported
 - the JSON string is written at offset 0 in a data segment. This string *has* to be converted in a JS string *before* using the DSP instance
 - memory module size cannot be written while generating the output stream, since DSP size is computed when inlining subcontainers and waveforms.
 The final memory size is finally written after module code generation.
 - in Load/Store, check if address is constant, so that to be used as an 'offset'
 - move loop 'i' variable by bytes instead of frames to save index code generation of input/output accesses (gLoopVarInBytes)
 - offset of inputs/outputs are constant, so can be directly generated

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
        throw faustexception("ERROR : OpenMP not supported for WebAssembly\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for WebAssembly\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for WebAssembly\n");
    } else {
        container = new WASMScalarCodeContainer(name, numInputs, numOutputs, dst, kInt, internal_memory);
    }

    return container;
}

DeclareFunInst* WASMCodeContainer::generateClassInit(const string& name)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt32));
    
    BlockInst* inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
    
    BlockInst* block = MoveVariablesInFront3().getCode(inlined);
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceClear(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    BlockInst* renamed = DspRenamer().getCode(fClearInstructions);
    
    BlockInst* block = MoveVariablesInFront3().getCode(renamed);
    
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceConstants(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("samplingFreq", Typed::kInt32));
    
    BlockInst* inlined = inlineSubcontainersFunCalls(fInitInstructions);
    
    BlockInst* block = MoveVariablesInFront3().getCode(inlined);
  
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceResetUserInterface(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    BlockInst* renamed = DspRenamer().getCode(fResetUserInterfaceInstructions);
    
    BlockInst* block = MoveVariablesInFront3().getCode(renamed);
    
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
DeclareFunInst* WASMCodeContainer::generateInstanceInitFun(const string& name, const string& obj, bool ismethod, bool isvirtual, bool addreturn)
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
    
    // Mathematical functions and global variables are handled in a separated visitor that creates functions types and global variable offset
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
    
    // Keep location of memory generation
    size_t begin_memory = -1;
    if (fInternalMemory) {
        begin_memory = gGlobal->gWASMVisitor->generateInternalMemory();
    }
    
    // Exports
    gGlobal->gWASMVisitor->generateExports(fInternalMemory);
 
    // Functions
    int32_t functions_start = gGlobal->gWASMVisitor->startSection(BinaryConsts::Section::Code);
    fBinaryOut << U32LEB(14); // num functions
    
    // Internal functions in alphabetical order
    
    // 1) classInit
    generateClassInit("classInit")->accept(gGlobal->gWASMVisitor);
    
    // 2) compute
    generateCompute();
    
    // 3) getNumInputs
    generateGetInputs("getNumInputs", "dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 4) getNumOutputs
    generateGetOutputs("getNumOutputs", "dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 5) getParamValue (adhoc generation for now since currently FIR cannot be generated to handle this case)
    gGlobal->gWASMVisitor->generateGetParamValue();
   
    // 6) getSampleRate
    generateGetSampleRate("dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 7) init
    generateInit("dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 8) instanceClear
    generateInstanceClear("instanceClear", "dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 9) instanceConstants
    generateInstanceConstants("instanceConstants", "dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 10) instanceInit
    generateInstanceInit("dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
    // 11) instanceResetUserInterface
    generateInstanceResetUserInterface("instanceResetUserInterface", "dsp", false, false)->accept(gGlobal->gWASMVisitor);
    
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
    
    // JSON generation
    
    // Prepare compilation options
    stringstream options;
    gGlobal->printCompilationOptions(options);
    
    stringstream size;
    size << gGlobal->gWASMVisitor->getStructSize();
    
    JSONInstVisitor json_visitor1;
    generateUserInterface(&json_visitor1);
    
    map <string, string>::iterator it;
    std::map<std::string, int> path_index_table;
    map <string, MemoryDesc>& fieldTable1 = gGlobal->gWASMVisitor->getFieldTable();
    for (it = json_visitor1.fPathTable.begin(); it != json_visitor1.fPathTable.end(); it++) {
        // Get field index
        MemoryDesc tmp = fieldTable1[(*it).first];
        path_index_table[(*it).second] = tmp.fOffset;
    }
    
    JSONInstVisitor json_visitor2("", fNumInputs, fNumOutputs, "", "", FAUSTVERSION, options.str(), size.str(), path_index_table);
    generateUserInterface(&json_visitor2);
    generateMetaData(&json_visitor2);
    
    string json = json_visitor2.JSON(true);
    
    // Memory size can now be written
    if (fInternalMemory) {
        // Since JSON is written in data segment at offset 0, the memory size must be computed taking account JSON size and DSP + audio buffer size
        fBinaryOut.writeAt(begin_memory, U32LEB(genMemSize(gGlobal->gWASMVisitor->getStructSize(), fNumInputs + fNumOutputs, json.size())));
    }
    
    // Data segment contains the JSON string starting at offset 0,
    gGlobal->gWASMVisitor->generateJSON(removeChar(json, '\\'));
    
    // Finally produce output stream
    fBinaryOut.writeTo(*fOut);
    
    // Helper code
    int n = 0;
    
    // Generate JSON and getSize
    tab(n, fHelper); fHelper << "/*\n" << "Code generated with Faust version " << FAUSTVERSION << endl;
    fHelper << "Compilation options: ";
    gGlobal->printCompilationOptions(fHelper);
    fHelper << "\n*/\n";
    
    // Generate JSON
    tab(n, fHelper); fHelper << "function getJSON" << fKlassName << "() {";
        tab(n+1, fHelper);
        fHelper << "return \""; fHelper << json; fHelper << "\";";
        //fHelper << "return `\""; fHelper << json; fHelper << "`\";";
        printlines(n+1, fUICode, fHelper);
    tab(n, fHelper); fHelper << "}\n";
    
    if (gGlobal->gOutputLang == "wasm-ib" || gGlobal->gOutputLang == "wasm-eb") {
        
        /*
        // Write binary as an array
        fHelper << showbase         // show the 0x prefix
                << internal         // fill between the prefix and the number
                << setfill('0');    // fill with 0s
        {
            fHelper << "function getBinaryCode" << fKlassName << "() {";
                tab(n+1, fHelper);
                fHelper << "return new Uint8Array([";
                char sep = ' ';
                for (int i = 0; i < fBinaryOut.size(); i++) {
                    fHelper << sep << hex << int(fBinaryOut[i]);
                    sep = ',';
                }
                fHelper << "]).buffer; }\n";
            tab(n, fHelper);
        }
        
        {
            fHelper << "function getBinaryCodeString" << fKlassName << "() {";
                tab(n+1, fHelper);
                fHelper << "return \"new Uint8Array([";
                char sep = ' ';
                for (int i = 0; i < fBinaryOut.size(); i++) {
                    fHelper << sep << hex << int(fBinaryOut[i]);
                    sep = ',';
                }
                fHelper << "]).buffer\"; }\n";
            tab(n, fHelper);
        }
        */
        
        fHelper << "function getBase64Code" << fKlassName << "() {";
        fHelper << " return \"" << base64_encode(fBinaryOut.toString()) << "\"; }\n";
        tab(n, fHelper);
    }
}

void WASMScalarCodeContainer::generateCompute()
{
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
    
    // Creates function and visit it
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
    args.push_back(InstBuilder::genNamedTyped("inputs", Typed::kVoid_ptr));
    args.push_back(InstBuilder::genNamedTyped("outputs", Typed::kVoid_ptr));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    InstBuilder::genDeclareFunInst("compute", fun_type, block)->accept(gGlobal->gWASMVisitor);
}

// Vector
WASMVectorCodeContainer::WASMVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, bool internal_memory)
    :WASMCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = -1;
}

WASMVectorCodeContainer::~WASMVectorCodeContainer()
{}

void WASMVectorCodeContainer::generateCompute()
{}

