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
 WAST module description :
 
 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from the from JS "global.Math",
   or are externally implemented (log10 in JS using log, fmod in JS)
 - local variables have to be declared first on the block, before being actually initialized or set: this is done using MoveVariablesInFront3
 - 'faustpower' function actualy fallback to regular 'pow' (see powprim.h)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun
 - integer 'min/max' is done in the module in 'min_i/max_i' (using lt/select)
 - memory can be allocated internally in the module and exported, or externally in JS and imported

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
        gGlobal->gWASTVisitor = new WASTInstVisitor(fOut, fInternalMemory);
    }
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new WASTScalarCodeContainer(name, 0, 1, fOut, sub_container_type, true);
}

CodeContainer* WASTCodeContainer::createScalarContainer(const string& name, int sub_container_type, bool internal_memory)
{
    return new WASTScalarCodeContainer(name, 0, 1, fOut, sub_container_type, internal_memory);
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
        throw faustexception("OpenMP : OpenMP not supported for WebAssembly\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("Scheduler mode not supported for WebAssembly\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("Vector mode not supported for WebAssembly\n");
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
DeclareFunInst* WASTCodeContainer::generateInstanceInitFun(const string& name, bool ismethod, bool isvirtual, bool addreturn)
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

void WASTCodeContainer::produceInternal()
{
    // Fields generation
    generateGlobalDeclarations(gGlobal->gWASTVisitor);
    generateDeclarations(gGlobal->gWASTVisitor);
}

void WASTCodeContainer::produceClass()
{
    int n = 0;
  
    tab(n, *fOut);
    gGlobal->gWASTVisitor->Tab(n);
    
    tab(n, *fOut); *fOut << "(module";
    
        // Global declarations (mathematical functions, global variables...)
        gGlobal->gWASTVisitor->Tab(n+1);
    
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first
        generateGlobalDeclarations(gGlobal->gWASTVisitor);
    
        // Imported functions
        /*
        tab(n+1, *fOut); *fOut << "(func $print-i (import \"imports\" \"print\") (param i32))";
        tab(n+1, *fOut); *fOut << "(func $print-f (import \"imports\" \"print\") (param f32))";
        */
    
        // Exported functions
        tab(n+1, *fOut); *fOut << "(export \"getNumInputs\" (func $getNumInputs))";
        tab(n+1, *fOut); *fOut << "(export \"getNumOutputs\" (func $getNumOutputs))";
        tab(n+1, *fOut); *fOut << "(export \"getSampleRate\" (func $getSampleRate))";
        tab(n+1, *fOut); *fOut << "(export \"init\" (func $init))";
        tab(n+1, *fOut); *fOut << "(export \"instanceInit\" (func $instanceInit))";
        tab(n+1, *fOut); *fOut << "(export \"instanceConstants\" (func $instanceConstants))";
        tab(n+1, *fOut); *fOut << "(export \"instanceResetUserInterface\" (func $instanceResetUserInterface))";
        tab(n+1, *fOut); *fOut << "(export \"instanceClear\" (func $instanceClear))";
        tab(n+1, *fOut); *fOut << "(export \"setParamValue\" (func $setParamValue))";
        tab(n+1, *fOut); *fOut << "(export \"getParamValue\" (func $getParamValue))";
        tab(n+1, *fOut); *fOut << "(export \"compute\" (func $compute))";
    
        // Fields : compute the structure size to use in 'new'
        gGlobal->gWASTVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gWASTVisitor);
        
        // After field declaration...
        generateSubContainers();
    
        tab(n+1, *fOut);
        if (fInternalMemory) {
            *fOut << "(memory (export \"memory\") ";
            *fOut << ((pow2limit(gGlobal->gWASTVisitor->getStructSize() + (fNumInputs + fNumOutputs) * (audioMemSize + (8192 * audioMemSize))) / wasmMemSize) + 1) << ")";
        } else {
            *fOut << "(import \"memory\" \"memory\" (memory $0 ";
            *fOut << ((pow2limit(gGlobal->gWASTVisitor->getStructSize() + (fNumInputs + fNumOutputs) * (audioMemSize + (8192 * audioMemSize))) / wasmMemSize) + 1) << "))";
        }
    
        // Always generated mathematical functions
        tab(n+1, *fOut);
        WASInst::generateIntMin()->accept(gGlobal->gWASTVisitor);
        WASInst::generateIntMax()->accept(gGlobal->gWASTVisitor);
        
        /*
        tab(n+1, *fOut); *fOut << "(func $fmod" << isuffix() << " (type $0) (param $value " << realStr << ") (param $1 " << realStr << ") (result " << realStr << ")";
        tab(n+2, *fOut); *fOut << "(return (call $" << realStr << "-rem (get_local $value) (get_local $1)))";
        tab(n+1, *fOut); *fOut << ")";
         
        tab(n+1, *fOut); *fOut <<  "(func $log10" << isuffix() << " (type $2) (param $value " << realStr << ") (result " << realStr << ")";
        tab(n+2, *fOut); *fOut << "(return (" << realStr << ".div (call $log (get_local $value)) (call $log (" << realStr << ".const 10))))";
        tab(n+1, *fOut); *fOut << ")";
        */
    
        // getNumInputs/getNumOutputs
        generateGetInputs("getNumInputs", false, false)->accept(gGlobal->gWASTVisitor);
        generateGetOutputs("getNumOutputs", false, false)->accept(gGlobal->gWASTVisitor);
    
        // Inits
        tab(n+1, *fOut); *fOut << "(func $classInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
                DspRenamer renamer;
                BlockInst* renamed = renamer.getCode(fStaticInitInstructions);
                BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
                generateWASTBlock(inlined);
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceConstants (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
                DspRenamer renamer;
                BlockInst* renamed = renamer.getCode(fInitInstructions);
                BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
                generateWASTBlock(inlined);
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceResetUserInterface (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASTBlock(renamer.getCode(fResetUserInterfaceInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceClear (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASTVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASTBlock(renamer.getCode(fClearInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        gGlobal->gWASTVisitor->Tab(n+1);
    
        // init
        generateInit(false, false)->accept(gGlobal->gWASTVisitor);
    
        // instanceInit
        generateInstanceInit(false, false)->accept(gGlobal->gWASTVisitor);
    
        // getSampleRate
        generateGetSampleRate(false, false)->accept(gGlobal->gWASTVisitor);
    
        // setParamValue
        tab(n+1, *fOut); *fOut << "(func $setParamValue (param $dsp i32) (param $index i32) (param $value " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(" << realStr << ".store ";
                tab(n+3, *fOut); *fOut << "(i32.add (get_local $dsp) (get_local $index))";
                tab(n+3, *fOut); *fOut << "(get_local $value)";
            tab(n+2, *fOut); *fOut << ")";
        tab(n+1, *fOut); *fOut << ")";
    
        // getParamValue
        tab(n+1, *fOut); *fOut << "(func $getParamValue (param $dsp i32) (param $index i32) (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(return (" << realStr << ".load (i32.add (get_local $dsp) (get_local $index))))";
        tab(n+1, *fOut); *fOut << ")";
    
        // compute
        generateCompute(n);
        
        // Possibly generate separated functions
        gGlobal->gWASTVisitor->Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(gGlobal->gWASTVisitor);
    
    tab(n, *fOut); *fOut << ")";
    tab(n, *fOut);
    
    // Helper code
    
    // User interface : prepare the JSON string...
    JSONInstVisitor json_visitor(fNumInputs, fNumOutputs);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);
    
    // Generate JSON and getSize
    tab(n, fHelper); fHelper << "/* Helper code generated with FAUST version " << FAUSTVERSION << " */\n";
    tab(n, fHelper); fHelper << "function getSize" << fKlassName << "() {";
        tab(n+1, fHelper);
        fHelper << "return " << gGlobal->gWASTVisitor->getStructSize() << ";";
        printlines(n+1, fUICode, fHelper);
    tab(n, fHelper); fHelper << "}";
    tab(n, fHelper);
    
    // Fields to path
    tab(n, fHelper); fHelper << "function getPathTable" << fKlassName << "() {";
        tab(n+1, fHelper); fHelper << "var pathTable = [];";
        map <string, string>::iterator it;
        map <string, WASTInstVisitor::MemoryDesc>& fieldTable = gGlobal->gWASTVisitor->getFieldTable();
        for (it = json_visitor.fPathTable.begin(); it != json_visitor.fPathTable.end(); it++) {
            WASTInstVisitor::MemoryDesc tmp = fieldTable[(*it).first];
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

void WASTScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut); *fOut << "(func $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)";
        tab(n+2, *fOut);
        gGlobal->gWASTVisitor->Tab(n+2);
        fComputeBlockInstructions->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
        MoveVariablesInFront2 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions, true);
        block->accept(gGlobal->gWASTVisitor);
    tab(n+1, *fOut); *fOut << ")";
}

DeclareFunInst* WASInst::generateIntMin()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");
    
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(v1, Typed::kInt));
    args.push_back(InstBuilder::genNamedTyped(v2, Typed::kInt));
    
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genSelect2Inst(InstBuilder::genLessThan(InstBuilder::genLoadFunArgsVar(v1),
                                                                                                     InstBuilder::genLoadFunArgsVar(v2)),
                                                                            InstBuilder::genLoadFunArgsVar(v1),
                                                                            InstBuilder::genLoadFunArgsVar(v2))));
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("min_i", fun_type, block);
}

DeclareFunInst* WASInst::generateIntMax()
{
    string v1 = gGlobal->getFreshID("v1");
    string v2 = gGlobal->getFreshID("v2");
    
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(v1, Typed::kInt));
    args.push_back(InstBuilder::genNamedTyped(v2, Typed::kInt));
    
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genSelect2Inst(InstBuilder::genLessThan(InstBuilder::genLoadFunArgsVar(v1),
                                                                                                     InstBuilder::genLoadFunArgsVar(v2)),
                                                                            InstBuilder::genLoadFunArgsVar(v2),
                                                                            InstBuilder::genLoadFunArgsVar(v1))));
    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("max_i", fun_type, block);
}




