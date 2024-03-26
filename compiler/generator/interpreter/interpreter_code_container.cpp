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

#include <cstdlib>

#include "Text.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"
#include "interpreter_code_container.hh"
#include "interpreter_instructions.hh"

using namespace std;

/*
Interpreter backend description:

 - FIR code is transpiled in Faust Byte Code (FBC), to be executed in an interpreter or an hybrid interpreter/compiler
 - a single global visitor for main and subcontainers
 - 'fSampleRate' and 'count' variable manually added in the IntHeap to be setup in 'instanceInit' and 'compute'
 - DSP struct and stack variables are actually allocated in the Int32 and REAL heaps
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - subcontainers code is 'inlined': fields declarations (using the global visitor) and code 'classInit', and 'instanceInit' of the main container
 - 'clone' method is implemented in the 'interpreter_dsp' wrapping code
 - the backend exits in 3 versions:
    - pure Interpreter model: the slowest (FBCInterpreter class)
    - hybrid interpreter/MIR compiler (FBCLLVMCompiler class): the 'init' functions done once are interpreted, the hot 'compute' function is compiled to native using MIR machinery, faster
    - hybrid interpreter/LLVM compiler (FBCMIRCompiler class): the 'init' functions done once are interpreted, the hot 'compute' function is compiled to native using LLVM machinery, even faster, but slower that the pure LLVM backend
 - soundfile support:
    - Soundfile* pointers are kept in FBCExecutor::fSoundTable map
    - this fSoundTable is filled in FBCInterpreter::executeBuildUserInterface when excuting FBCInstruction::kAddSoundfile, `
    triggered by 'buildUserInterface', so has to be done at least once before calling DSP 'init'.
    - the FBCInstruction::kLoadSoundFieldInt and FBCInstruction::kLoadSoundFieldReal FPC instructions directly access the
    prepared fSoundTable in Interp mode. In Interp/[LLVM|MIR] they are compiled as access in a module global soundfile table
    built at construction time (see FBCLLVMCompiler/FBCMIRCompiler constructors).

 TODO: in -mem mode, classInit and classDestroy will have to be called once at factory init and destroy time
 (after global memory allocation is implemented)
*/

template <class REAL>
map<string, FBCInstruction::Opcode> InterpreterInstVisitor<REAL>::gMathLibTable;

template <class REAL>
static FBCBlockInstruction<REAL>* getCurrentBlock()
{
    FBCBlockInstruction<REAL>* block =
        static_cast<InterpreterInstVisitor<REAL>*>(gGlobal->gInterpreterVisitor)->fCurrentBlock;
    // Add kReturn in generated block
    block->push(new FBCBasicInstruction<REAL>(FBCInstruction::kReturn));
    return block;
}

template <class REAL>
static InterpreterInstVisitor<REAL>* getInterpreterVisitor()
{
    return static_cast<InterpreterInstVisitor<REAL>*>(gGlobal->gInterpreterVisitor);
}

template <class REAL>
static void setCurrentBlock(FBCBlockInstruction<REAL>* block)
{
    static_cast<InterpreterInstVisitor<REAL>*>(gGlobal->gInterpreterVisitor)->fCurrentBlock = block;
}

template <class REAL>
InterpreterCodeContainer<REAL>::InterpreterCodeContainer(const string& name, int numInputs, int numOutputs)
{
    initialize(numInputs, numOutputs);
    fKlassName = name;

    // Allocate one static visitor to be shared by main module and sub containers
    if (!gGlobal->gInterpreterVisitor) {
        gGlobal->gInterpreterVisitor = new InterpreterInstVisitor<REAL>();
    }
}

template <class REAL>
CodeContainer* InterpreterCodeContainer<REAL>::createScalarContainer(const string& name, int sub_container_type)
{
    return new InterpreterScalarCodeContainer<REAL>(name, 0, 1, sub_container_type);
}

template <class REAL>
CodeContainer* InterpreterCodeContainer<REAL>::createContainer(const string& name, int numInputs, int numOutputs)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Interpreter\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Interpreter\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Interpreter\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for Interpreter\n");
    } else if (gGlobal->gVectorSwitch) {
        // throw faustexception("ERROR : Vector mode not supported for Interpreter\n");
        if (gGlobal->gVectorLoopVariant == 0) {
            throw faustexception("ERROR : Vector mode with -lv 0 not supported for Interpreter\n");
        }
        container = new InterpreterVectorCodeContainer<REAL>(name, numInputs, numOutputs);
    } else {
        container = new InterpreterScalarCodeContainer<REAL>(name, numInputs, numOutputs, kInt);
    }

    return container;
}

// Scalar
template <class REAL>
InterpreterScalarCodeContainer<REAL>::InterpreterScalarCodeContainer(const string& name, int numInputs, int numOutputs,
                                                                  int sub_container_type)
    : InterpreterCodeContainer<REAL>(name, numInputs, numOutputs)
{
    this->fSubContainerType = sub_container_type;
}

template <class REAL>
InterpreterScalarCodeContainer<REAL>::~InterpreterScalarCodeContainer()
{
}

template <class REAL>
dsp_factory_base* InterpreterCodeContainer<REAL>::produceFactory()
{
    // "count" variable added to be setup later by 'compute'
    pushDeclare(InstBuilder::genDecStructVar("count", InstBuilder::genInt32Typed()));
   
    // Sub containers are merged
    mergeSubContainers();

    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);
    generateDeclarations(gGlobal->gInterpreterVisitor);

    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gInterpreterVisitor);
   
    // Keep "init_static_block"
    FBCBlockInstruction<REAL>* init_static_block = getCurrentBlock<REAL>();
    setCurrentBlock<REAL>(new FBCBlockInstruction<REAL>());

    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gInterpreterVisitor);
  
    // Keep "init_block"
    FBCBlockInstruction<REAL>* init_block = getCurrentBlock<REAL>();
    setCurrentBlock<REAL>(new FBCBlockInstruction<REAL>);

    // Keep "resetui_block"
    generateResetUserInterface(gGlobal->gInterpreterVisitor);
    FBCBlockInstruction<REAL>* resetui_block = getCurrentBlock<REAL>();
    setCurrentBlock<REAL>(new FBCBlockInstruction<REAL>);

    // Keep "clear_block"
    generateClear(gGlobal->gInterpreterVisitor);
    FBCBlockInstruction<REAL>* clear_block = getCurrentBlock<REAL>();
    setCurrentBlock<REAL>(new FBCBlockInstruction<REAL>);

    // Generate UI
    generateUserInterface(gGlobal->gInterpreterVisitor);

    // Generate local variables declaration and setup
    generateComputeBlock(gGlobal->gInterpreterVisitor);

    // Keep "compute_control_block"
    FBCBlockInstruction<REAL>* compute_control_block = getCurrentBlock<REAL>();
    setCurrentBlock<REAL>(new FBCBlockInstruction<REAL>);

    // Keep "compute_dsp_block"
    FBCBlockInstruction<REAL>* compute_dsp_block = generateCompute();

    // Generate metadata block and name
    string                   name;
    FIRMetaBlockInstruction* metadata_block = produceMetadata(name);

    // Then create factory depending of the trace mode
    const char* trace = getenv("FAUST_INTERP_TRACE");
    int         mode  = (trace) ? std::atoi(trace) : 0;

    // Prepare compilation options
    stringstream compile_options;
    gGlobal->printCompilationOptions(compile_options);
    
    switch (mode) {
#if defined(INTERP_BUILD)
        case 1:
            return new interpreter_dsp_factory_aux<REAL, 1>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);

        case 2:
            return new interpreter_dsp_factory_aux<REAL, 2>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);

        case 3:
            return new interpreter_dsp_factory_aux<REAL, 3>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);

        case 4:
            return new interpreter_dsp_factory_aux<REAL, 4>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);

        case 5:
            return new interpreter_dsp_factory_aux<REAL, 5>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);

        case 6:
            return new interpreter_dsp_factory_aux<REAL, 6>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
        
        default:
            // Default case, no trace...
            return new interpreter_dsp_factory_aux<REAL, 0>(
                name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
#elif defined(INTERP_COMP_BUILD)
        default:
            // Default case, no trace...
            return new interpreter_comp_dsp_factory_aux<REAL, 0>(
                 name, compile_options.str(), "", INTERP_FILE_VERSION, fNumInputs, fNumOutputs,
                 getInterpreterVisitor<REAL>()->fIntHeapOffset, getInterpreterVisitor<REAL>()->fRealHeapOffset,
                 getInterpreterVisitor<REAL>()->getFieldOffset("fSampleRate"),
                 getInterpreterVisitor<REAL>()->getFieldOffset("count"), getInterpreterVisitor<REAL>()->getFieldOffset("IOTA"),
                 INTER_MAX_OPT_LEVEL, metadata_block, getInterpreterVisitor<REAL>()->fUserInterfaceBlock, init_static_block,
                 init_block, resetui_block, clear_block, compute_control_block, compute_dsp_block);
#endif
    }
}

template <class REAL>
FBCBlockInstruction<REAL>* InterpreterScalarCodeContainer<REAL>::generateCompute()
{
    BlockInst* compute_block = InstBuilder::genBlockInst();
    compute_block->pushBackInst(this->fCurLoop->generateScalarLoop(fFullCount));
                                
    // Generates post DSP loop code
    compute_block->pushBackInst(this->fPostComputeBlockInstructions);
    
    compute_block->accept(gGlobal->gInterpreterVisitor);
    return getCurrentBlock<REAL>();
}

template <class REAL>
FBCBlockInstruction<REAL>* InterpreterVectorCodeContainer<REAL>::generateCompute()
{
    // Rename all loop variables name to avoid name clash
    LoopVariableRenamer loop_renamer;
    loop_renamer.getCode(this->fDAGBlock)->accept(gGlobal->gInterpreterVisitor);

    return getCurrentBlock<REAL>();
}

template <class REAL>
FIRMetaBlockInstruction* InterpreterCodeContainer<REAL>::produceMetadata(string& name)
{
    FIRMetaBlockInstruction* block = new FIRMetaBlockInstruction();

    // Add global metadata
    for (const auto& it : gGlobal->gMetaDataSet) {
        if (it.first != tree("author")) {
            stringstream str1, str2;
            str1 << *(it.first);
            str2 << **(it.second.begin());
            if (str1.str() == "name") name = unquote(str2.str());
            block->push(new FIRMetaInstruction(str1.str(), unquote(str2.str())));
        } else {
            for (set<Tree>::iterator j = it.second.begin(); j != it.second.end(); j++) {
                if (j == it.second.begin()) {
                    stringstream str1, str2;
                    str1 << *(it.first);
                    str2 << **j;
                    if (str1.str() == "name") name = unquote(str2.str());
                    block->push(new FIRMetaInstruction(str1.str(), unquote(str2.str())));
                } else {
                    stringstream str2;
                    str2 << **j;
                    block->push(new FIRMetaInstruction("contributor", unquote(str2.str())));
                }
            }
        }
    }

    return block;
}

