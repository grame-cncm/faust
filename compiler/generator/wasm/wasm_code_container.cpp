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

#include "wasm_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"
#include "rn_base64.h"

using namespace std;

/*
 WASM backend and module description:

 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from JS
 "global.Math", or are externally implemented (fmod and remainder in JS)
 - local variables have to be declared first on the block, before being actually initialized or set : this is done using
 MoveVariablesInFront3
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - LocalVariableCounter visitor allows to count and create local variables of each types
 - FunAndTypeCounter visitor allows to count and create function types and global variable offset
 - memory can be allocated internally in the module and exported, or externally in JS and imported
 - the JSON string is written at offset 0 in a data segment. This string *has* to be converted in a JS string *before*
 using the DSP instance
 - memory module size cannot be written while generating the output stream, since DSP size is computed when inlining
 subcontainers and waveforms. The final memory size is finally written after module code generation.
 - in Load/Store, check if address is constant, so that to be used as an 'offset'
 - move loop 'i' variable by bytes instead of frames to save index code generation of input/output accesses
 (gLoopVarInBytes)
 - offset of inputs/outputs are constant, so can be directly generated

*/

dsp_factory_base* WASMCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), fHelper.str());
}

WASMCodeContainer::WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                     bool internal_memory)
    : fOut(out)
{
    initialize(numInputs, numOutputs);
    fKlassName      = name;
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

CodeContainer* WASMCodeContainer::createScalarContainer(const string& name, int sub_container_type,
                                                        bool internal_memory)
{
    return new WASMScalarCodeContainer(name, 0, 1, fOut, sub_container_type, internal_memory);
}

CodeContainer* WASMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst,
                                                  bool internal_memory)
{
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not supported for WebAssembly\n");
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
        // throw faustexception("ERROR : Vector mode not supported for WebAssembly\n");
        if (gGlobal->gVectorLoopVariant == 0) {
            throw faustexception("ERROR : Vector mode with -lv 0 not supported for WebAssembly\n");
        }
        container = new WASMVectorCodeContainer(name, numInputs, numOutputs, dst, internal_memory);
    } else {
        container = new WASMScalarCodeContainer(name, numInputs, numOutputs, dst, kInt, internal_memory);
    }

    return container;
}

// DSP API generation

DeclareFunInst* WASMCodeContainer::generateClassInit(const string& name)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
    BlockInst* block   = MoveVariablesInFront3().getCode(inlined);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceClear(const string& name, const string& obj, bool ismethod,
                                                         bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    BlockInst* renamed = DspRenamer().getCode(fClearInstructions);
    BlockInst* block   = MoveVariablesInFront3().getCode(renamed);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceConstants(const string& name, const string& obj, bool ismethod,
                                                             bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* inlined = inlineSubcontainersFunCalls(fInitInstructions);
    BlockInst* block   = MoveVariablesInFront3().getCode(inlined);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* WASMCodeContainer::generateInstanceResetUserInterface(const string& name, const string& obj,
                                                                      bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    BlockInst* renamed = DspRenamer().getCode(fResetUserInterfaceInstructions);
    BlockInst* block   = MoveVariablesInFront3().getCode(renamed);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

// Scalar
WASMScalarCodeContainer::WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                 int sub_container_type, bool internal_memory)
    : WASMCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    fSubContainerType = sub_container_type;
}

// Special version that uses MoveVariablesInFront3 to inline waveforms...
DeclareFunInst* WASMCodeContainer::generateInstanceInitFun(const string& name, const string& obj, bool ismethod,
                                                           bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* init_block = InstBuilder::genBlockInst();
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fStaticInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fPostInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fResetUserInterfaceInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fClearInstructions));

    init_block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, init_block, isvirtual);
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

    // Mathematical functions and global variables are handled in a separated visitor that creates functions types and
    // global variable offset
    generateGlobalDeclarations(gGlobal->gWASMVisitor->getFunAndTypeCounter());
    generateExtGlobalDeclarations(gGlobal->gWASMVisitor->getFunAndTypeCounter());

    // Update struct offset to take account of global variables defined in 'generateGlobalDeclarations' in the separated
    // visitor
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
    fBinaryOut << U32LEB(14);  // num functions

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
    generateGetSampleRate("getSampleRate", "dsp", false, false)->accept(gGlobal->gWASMVisitor);

    // 7) init
    generateInit("init", "dsp", false, false)->accept(gGlobal->gWASMVisitor);

    // 8) instanceClear
    generateInstanceClear("instanceClear", "dsp", false, false)->accept(gGlobal->gWASMVisitor);

    // 9) instanceConstants
    generateInstanceConstants("instanceConstants", "dsp", false, false)->accept(gGlobal->gWASMVisitor);

    // 10) instanceInit
    generateInstanceInit("instanceInit", "dsp", false, false)->accept(gGlobal->gWASMVisitor);

    // 11) instanceResetUserInterface
    generateInstanceResetUserInterface("instanceResetUserInterface", "dsp", false, false)
        ->accept(gGlobal->gWASMVisitor);

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

    // TO REMOVE when 'soundfile' is implemented
    {
        // Generate UI: only to trigger exception when using 'soundfile' primitive
        generateUserInterface(gGlobal->gWASMVisitor);
    }

    // JSON generation
    string json;
    if (gGlobal->gFloatSize == 1) {
        json = generateJSON<float>();
    } else {
        json = generateJSON<double>();
    }
  
    // Memory size can now be written
    if (fInternalMemory) {
        int memory_size = genMemSize(gGlobal->gWASMVisitor->getStructSize(), fNumInputs + fNumOutputs, (int)json.size());
        // Since JSON is written in data segment at offset 0, the memory size
        // must be computed taking account JSON size and DSP + audio buffer size
        fBinaryOut.writeAt(begin_memory, U32LEB(memory_size));
        // maximum memory pages number, minimum value is to be extended on JS side for soundfiles
        fBinaryOut.writeAt(begin_memory + 5, U32LEB(memory_size+1000));
    }

    // Data segment contains the JSON string starting at offset 0,
    gGlobal->gWASMVisitor->generateJSON(json);

    // Finally produce output stream
    fBinaryOut.writeTo(*fOut);

    // Helper code
    int n = 0;

    // Generate JSON and getSize
    tab(n, fHelper);
    fHelper << "/*\n"
            << "Code generated with Faust version " << FAUSTVERSION << endl;
    fHelper << "Compilation options: ";
    gGlobal->printCompilationOptions(fHelper);
    fHelper << "\n*/\n";

    // Generate JSON
    tab(n, fHelper);
    string json2 = flattenJSON1(json);
    fHelper << "function getJSON" << fKlassName << "() {";
    tab(n + 1, fHelper);
    fHelper << "return '";
    fHelper << json2;
    fHelper << "';";
    printlines(n + 1, fUICode, fHelper);
    tab(n, fHelper);
    fHelper << "}\n";

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

// Auxiliary function for shared code in generateCompute
void WASMCodeContainer::generateComputeAux(BlockInst* compute_block)
{
    DeclareFunInst* int_max_fun = WASInst::generateIntMax();
    DeclareFunInst* int_min_fun = WASInst::generateIntMin();

    // Inline "max_i" call
    compute_block = FunctionCallInliner(int_max_fun).getCode(compute_block);

    // Inline "min_i" call
    compute_block = FunctionCallInliner(int_min_fun).getCode(compute_block);

    // Push the loop in compute block
    fComputeBlockInstructions->pushBackInst(compute_block);

    // Put local variables at the begining
    BlockInst* block = MoveVariablesInFront2().getCode(fComputeBlockInstructions, true);
    
    // Remove unecessary cast
    block = CastRemover().getCode(block);
    
    // Creates function and visit it
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("dsp", Typed::kObj_ptr));
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
    args.push_back(InstBuilder::genNamedTyped("inputs", Typed::kVoid_ptr));
    args.push_back(InstBuilder::genNamedTyped("outputs", Typed::kVoid_ptr));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(), FunTyped::kDefault);
    
    InstBuilder::genDeclareFunInst("compute", fun_type, block)->accept(gGlobal->gWASMVisitor);
}

void WASMScalarCodeContainer::generateCompute()
{
    // Loop 'i' variable is moved by bytes
    BlockInst* compute_block = InstBuilder::genBlockInst();
    compute_block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount, gGlobal->gLoopVarInBytes));

    generateComputeAux(compute_block);
}

// Vector
WASMVectorCodeContainer::WASMVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                 bool internal_memory)
    : VectorCodeContainer(numInputs, numOutputs), WASMCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = -1;
}

void WASMVectorCodeContainer::generateCompute()
{
    // Rename all loop variables name to avoid name clash
    LoopVariableRenamer loop_renamer;
    generateComputeAux(loop_renamer.getCode(fDAGBlock));
}
