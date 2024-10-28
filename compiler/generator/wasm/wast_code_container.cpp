/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "wast_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 WAST backend and module description:

 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are
imported from JS "global.Math", or are externally implemented (fmod and remainder in JS)
 - local variables have to be declared first on the block, before being actually initialized or set:
this is done using MoveVariablesInFront3
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of
generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - memory can be allocated internally in the module and exported, or externally in JS and imported
 - the JSON string is written at offset 0 in a data segment. This string *has* to be converted in a
JS string *before* using the DSP instance
 - memory module size cannot be written while generating the output stream, since DSP size is
computed when inlining subcontainers and waveform. The final memory size is finally written after
module code generation.
 - in Load/Store, check if address is constant, so that to be used as an 'offset'
 - move loop 'i' variable by bytes instead of frames to save index code generation of input/output
accesses (gLoopVarInBytes)
 - offset of inputs/outputs are constant, so can be directly generated

 Code generation, the flags can be:
 - 'wast-i' (internal memory for monophonic DSP)
 - 'wast-e' (external memory for polyphonic DSP)
 - or 'wast' which is equivalent to 'wast-i'

Soundfile management:

 - the Soundfile* pointers are moved first in the DSP struct
 - the pointers are allocated in wasm memory and filled on JS side. The Soundfile structure memory
layout has to be reproduced in a "flat way" in wasm memory. The JSON description is used to know the
number of soundfiles and to fill them.

 struct Soundfile {
     void* fBuffers; // will correspond to a double** or float** pointer chosen at runtime
     int* fLength;   // length of each part (so fLength[P] contains the length in frames of part P)
     int* fSR;       // sample rate of each part (so fSR[P] contains the SR of part P)
     int* fOffset;   // offset of each part in the global buffer (so fOffset[P] contains the offset
in frames of part P) int fChannels;  // max number of channels of all concatenated files int fParts;
// the total number of loaded parts bool fIsDouble; // keep the sample format (float or double)
 }
*/

dsp_factory_base* WASTCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""),
        fHelper.str());
}

WASTCodeContainer::WASTCodeContainer(const string& name, int numInputs, int numOutputs,
                                     ostream* out, bool internal_memory)
    : fOut(out)
{
    initialize(numInputs, numOutputs);
    fKlassName      = name;
    fInternalMemory = internal_memory;
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new WASTScalarCodeContainer(name, 0, 1, &fOutAux, sub_container_type, true);
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type,
                                                        bool internal_memory)
{
    return new WASTScalarCodeContainer(name, 0, 1, &fOutAux, sub_container_type, internal_memory);
}

CodeContainer* WASTCodeContainer::createContainer(const string& name, int numInputs, int numOutputs,
                                                  ostream* dst, bool internal_memory)
{
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for WebAssembly\n");
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
        container = new WASTVectorCodeContainer(name, numInputs, numOutputs, dst, internal_memory);
    } else {
        container =
            new WASTScalarCodeContainer(name, numInputs, numOutputs, dst, kInt, internal_memory);
    }

    return container;
}

// Scalar
WASTScalarCodeContainer::WASTScalarCodeContainer(const string& name, int numInputs, int numOutputs,
                                                 ostream* out, int sub_container_type,
                                                 bool internal_memory)
    : WASTCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    fSubContainerType = sub_container_type;
}

// Special version that uses MoveVariablesInFront3 to inline waveforms...
DeclareFunInst* WASTCodeContainer::generateInstanceInitFun(const string& name, const string& obj,
                                                           bool ismethod, bool isvirtual)
{
    Names args;
    if (!ismethod) {
        args.push_back(IB::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* init_block = IB::genBlockInst();
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fStaticInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fPostInitInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fResetUserInterfaceInstructions));
    init_block->pushBackInst(MoveVariablesInFront3().getCode(fClearInstructions));

    init_block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, init_block, isvirtual);
}

void WASTCodeContainer::produceClass()
{
    int n = 0;

    CheckSoundfilesVisitor check_soundfiles;
    generateUserInterface(&check_soundfiles);

    // If the DSP struct has soundfiles, external memory has to be used
    fInternalMemory = (check_soundfiles.fHasSoundfiles) ? false : fInternalMemory;

    // Allocate one static visitor to be shared by main module and sub containers
    if (!gGlobal->gWASTVisitor) {
        gGlobal->gWASTVisitor = new WASTInstVisitor(&fOutAux, fInternalMemory);
    }

    gGlobal->gWASTVisitor->Tab(n);

    tab(n, fOutAux);
    fOutAux << "(module";

    // Global declarations (mathematical functions, global variables...)
    gGlobal->gWASTVisitor->Tab(n + 1);

    // Sub containers are merged in the main module, before functions generation
    mergeSubContainers();

    // All mathematical functions (got from math library as variables) have to be first
    generateGlobalDeclarations(gGlobal->gWASTVisitor);
    generateExtGlobalDeclarations(gGlobal->gWASTVisitor);

    // Exported functions
    tab(n + 1, fOutAux);
    fOutAux << "(export \"getNumInputs\" (func $getNumInputs))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"getNumOutputs\" (func $getNumOutputs))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"getSampleRate\" (func $getSampleRate))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"init\" (func $init))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"instanceInit\" (func $instanceInit))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"instanceConstants\" (func $instanceConstants))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"instanceResetUserInterface\" (func $instanceResetUserInterface))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"instanceClear\" (func $instanceClear))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"setParamValue\" (func $setParamValue))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"getParamValue\" (func $getParamValue))";
    tab(n + 1, fOutAux);
    fOutAux << "(export \"compute\" (func $compute))";

    // General imports
    tab(n + 1, fOutAux);
    fOutAux << "(import \"env\" \"memoryBase\" (global $memoryBase i32))";
    tab(n + 1, fOutAux);
    fOutAux << "(import \"env\" \"tableBase\" (global $tableBase i32))";

    // Fields : compute the structure size to use in 'new'
    gGlobal->gWASTVisitor->Tab(n + 1);
    generateDeclarations(gGlobal->gWASTVisitor);

    // Keep location of memory generation
    streampos begin_memory = fOutAux.tellp();

    // Always generated mathematical functions
    tab(n + 1, fOutAux);
    WASInst::generateIntMin()->accept(gGlobal->gWASTVisitor);
    WASInst::generateIntMax()->accept(gGlobal->gWASTVisitor);

    // getNumInputs/getNumOutputs
    generateGetInputs("getNumInputs", "dsp", false, FunTyped::kDefault)
        ->accept(gGlobal->gWASTVisitor);
    generateGetOutputs("getNumOutputs", "dsp", false, FunTyped::kDefault)
        ->accept(gGlobal->gWASTVisitor);

    // Inits
    tab(n + 1, fOutAux);
    fOutAux << "(func $classInit (param $dsp i32) (param $sample_rate i32)";
    tab(n + 2, fOutAux);
    gGlobal->gWASTVisitor->Tab(n + 2);
    {
        BlockInst* inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
        generateWASTBlock(inlined);
    }
    back(1, fOutAux);
    fOutAux << ")";

    tab(n + 1, fOutAux);
    fOutAux << "(func $instanceConstants (param $dsp i32) (param $sample_rate i32)";
    tab(n + 2, fOutAux);
    gGlobal->gWASTVisitor->Tab(n + 2);
    {
        BlockInst* inlined = inlineSubcontainersFunCalls(fInitInstructions);
        generateWASTBlock(inlined);
    }
    back(1, fOutAux);
    fOutAux << ")";

    tab(n + 1, fOutAux);
    fOutAux << "(func $instanceResetUserInterface (param $dsp i32)";
    tab(n + 2, fOutAux);
    gGlobal->gWASTVisitor->Tab(n + 2);
    {
        // Rename 'sig' in 'dsp' and remove 'dsp' allocation
        generateWASTBlock(DspRenamer().getCode(fResetUserInterfaceInstructions));
    }
    back(1, fOutAux);
    fOutAux << ")";

    tab(n + 1, fOutAux);
    fOutAux << "(func $instanceClear (param $dsp i32)";
    tab(n + 2, fOutAux);
    gGlobal->gWASTVisitor->Tab(n + 2);
    {
        // Rename 'sig' in 'dsp' and remove 'dsp' allocation
        generateWASTBlock(DspRenamer().getCode(fClearInstructions));
    }
    back(1, fOutAux);
    fOutAux << ")";

    gGlobal->gWASTVisitor->Tab(n + 1);

    // init
    generateInit("init", "dsp", false, false)->accept(gGlobal->gWASTVisitor);

    // instanceInit
    generateInstanceInit("instanceInit", "dsp", false, false)->accept(gGlobal->gWASTVisitor);

    // getSampleRate
    generateGetSampleRate("getSampleRate", "dsp", false, false)->accept(gGlobal->gWASTVisitor);

    // setParamValue
    tab(n + 1, fOutAux);
    fOutAux << "(func $setParamValue (param $dsp i32) (param $index i32) (param $value " << realStr
            << ")";
    tab(n + 2, fOutAux);
    fOutAux << "(" << realStr << ".store ";
    tab(n + 3, fOutAux);
    fOutAux << "(i32.add (local.get $dsp) (local.get $index))";
    tab(n + 3, fOutAux);
    fOutAux << "(local.get $value)";
    tab(n + 2, fOutAux);
    fOutAux << ")";
    tab(n + 1, fOutAux);
    fOutAux << ")";

    // getParamValue
    tab(n + 1, fOutAux);
    fOutAux << "(func $getParamValue (param $dsp i32) (param $index i32) (result " << realStr
            << ")";
    tab(n + 2, fOutAux);
    fOutAux << "(return (" << realStr << ".load (i32.add (local.get $dsp) (local.get $index))))";
    tab(n + 1, fOutAux);
    fOutAux << ")";

    // compute
    generateCompute(n);

    // Possibly generate separated functions
    gGlobal->gWASTVisitor->Tab(n + 1);
    tab(n + 1, fOutAux);
    generateComputeFunctions(gGlobal->gWASTVisitor);

    back(1, fOutAux);
    fOutAux << ")";
    tab(n, fOutAux);

    // JSON generation
    string json;
    if (gGlobal->gFloatSize == 1) {
        json = generateJSON<float>();
    } else {
        json = generateJSON<double>();
    }

    // Now that DSP structure size is known, concatenate stream parts to produce the final stream
    string tmp_aux = fOutAux.str();
    string begin   = tmp_aux.substr(0, begin_memory);
    string end     = tmp_aux.substr(begin_memory);

    // Write begining of code stream on *fOut
    *fOut << begin;

    // Insert memory generation
    string json1 = flattenJSON(json);
    tab(n + 1, *fOut);
    if (fInternalMemory) {
        int memory_size = genMemSize(gGlobal->gWASTVisitor->getStructSize(),
                                     fNumInputs + fNumOutputs, (int)json1.size());
        *fOut << "(memory (export \"memory\") ";
        // Since JSON is written in data segment at offset 0, the memory size
        // must be computed taking account JSON size and DSP + audio buffer size
        *fOut << memory_size                          // initial memory pages
              << " " << (memory_size + 1000) << ")";  // maximum memory pages number, minimum value
                                                      // is to be extended on JS side for soundfiles
    } else {
        // Memory size set by JS code, so use a minimum value that contains
        // the data segment size (shoud be OK for any JSON)
        *fOut << "(import \"env\" \"memory\" (memory $0 1))";
    }

    // Generate one data segment containing the JSON string starting at offset 0
    tab(n + 1, *fOut);
    *fOut << "(data (i32.const 0) \"" << json1 << "\")";

    // And write end of code stream on *fOut
    *fOut << end;

    // Helper code
    fHelper << json;
}

DeclareFunInst* WASInst::generateIntMin()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");

    Names args;
    args.push_back(IB::genNamedTyped(v1, Typed::kInt32));
    args.push_back(IB::genNamedTyped(v2, Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(IB::genRetInst(
        IB::genSelect2Inst(IB::genLessThan(IB::genLoadFunArgsVar(v1), IB::genLoadFunArgsVar(v2)),
                           IB::genLoadFunArgsVar(v1), IB::genLoadFunArgsVar(v2))));
    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genInt32Typed(), FunTyped::kDefault);
    return IB::genDeclareFunInst("min_i", fun_type, block);
}

DeclareFunInst* WASInst::generateIntMax()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");

    Names args;
    args.push_back(IB::genNamedTyped(v1, Typed::kInt32));
    args.push_back(IB::genNamedTyped(v2, Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(IB::genRetInst(
        IB::genSelect2Inst(IB::genLessThan(IB::genLoadFunArgsVar(v1), IB::genLoadFunArgsVar(v2)),
                           IB::genLoadFunArgsVar(v2), IB::genLoadFunArgsVar(v1))));
    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genInt32Typed(), FunTyped::kDefault);
    return IB::genDeclareFunInst("max_i", fun_type, block);
}

// Auxiliary functions for shared code in generateCompute
void WASTCodeContainer::generateComputeAux1(int n)
{
    tab(n + 1, fOutAux);
    fOutAux << "(func $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param "
               "$outputs i32)";
    tab(n + 2, fOutAux);
    gGlobal->gWASTVisitor->Tab(n + 2);
}

void WASTCodeContainer::generateComputeAux2(BlockInst* compute_block, int n)
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

    block->accept(gGlobal->gWASTVisitor);
    back(1, fOutAux);
    fOutAux << ")";
}

void WASTScalarCodeContainer::generateCompute(int n)
{
    generateComputeAux1(n);

    // Loop 'i' variable is moved by bytes
    BlockInst* compute_block = IB::genBlockInst();
    compute_block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount, gGlobal->gLoopVarInBytes));

    // Generates post DSP loop code
    compute_block->pushBackInst(fPostComputeBlockInstructions);

    generateComputeAux2(compute_block, n);
}

// Vector
WASTVectorCodeContainer::WASTVectorCodeContainer(const string& name, int numInputs, int numOutputs,
                                                 ostream* out, bool internal_memory)
    : VectorCodeContainer(numInputs, numOutputs),
      WASTCodeContainer(name, numInputs, numOutputs, out, internal_memory)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = -1;
}

void WASTVectorCodeContainer::generateCompute(int n)
{
    generateComputeAux1(n);

    // Rename all loop variables name to avoid name clash
    LoopVariableRenamer loop_renamer;
    generateComputeAux2(loop_renamer.getCode(fDAGBlock), n);
}
