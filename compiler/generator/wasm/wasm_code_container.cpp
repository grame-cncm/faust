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
 WASM module description :
 
 - mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), are imported from the from JS "global.Math",
    or are externally implemented (log10 in JS using log, fmod in JS)
 - local variables have to be declared first on the block, before being actually initialized or set : this is done using MoveVariablesInFront3
 - 'faustpower' function directly inlined in the code (see CodeContainer::pushFunction)
 - subcontainers are inlined in 'classInit' and 'instanceConstants' functions.
 - waveform generation is 'inlined' using MoveVariablesInFront3, done in a special version of generateInstanceInitFun.
 - integer min/max done in the module in min_i/max_i (using lt/select)

*/

dsp_factory_base* WASMCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), fHelper.str());
}

WASMCodeContainer::WASMCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out):fOut(out)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    
    // Allocate one static visitor
    if (!gGlobal->gWASMVisitor) {
        gGlobal->gWASMVisitor = new WASMInstVisitor(&fBinaryOut);
    }
}

CodeContainer* WASMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new WASMScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* WASMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

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
        container = new WASMScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
WASMScalarCodeContainer::WASMScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :WASMCodeContainer(name, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

WASMScalarCodeContainer::~WASMScalarCodeContainer()
{}

// Special version that uses MoveVariablesInFront3 to inline waveforms...
DeclareFunInst* WASMCodeContainer::generateInstanceInitFun(const string& name, bool ismethod, bool isvirtual, bool addreturn)
{
    //cout << "WASMCodeContainer::generateInstanceInitFun" << endl;
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
    fBinaryOut << int32_t(BinaryConsts::Magic) << int32_t(BinaryConsts::Version);
    
    // Sub containers : before functions generation
    mergeSubContainers();
    
    // All mathematical functions (got from math library as variables) have to be first
    generateGlobalDeclarations(gGlobal->gWASMVisitor);
    
    // Functions types
    gGlobal->gWASMVisitor->generateFunTypes();
    
    // Imported functions
    gGlobal->gWASMVisitor->generateImports();
    
    // Functions signature
    gGlobal->gWASMVisitor->generateFuncSignatures();
    
    // Fields : compute the structure size to use in 'new'
    generateDeclarations(gGlobal->gWASMVisitor);
    
    // After field declaration...
    generateSubContainers();
    
    /*
    ; section "MEMORY" (5)
    000006a: 05                                        ; section code
    000006b: 00                                        ; section size (guess)
    000006c: 01                                        ; num memories
    ; memory 0
    000006d: 00                                        ; memory flags
    000006e: 02                                        ; memory initial pages
    000006b: 03                                        ; FIXUP section size
    */
    
    // Memory
    int32_t memory_start = gGlobal->gWASMVisitor->startSection(BinaryConsts::Section::Memory);
    fBinaryOut << U32LEB(1); // num memories
    fBinaryOut << U32LEB(0); // memory flags
    fBinaryOut << U32LEB((pow2limit(gGlobal->gWASMVisitor->getStructSize() + (fNumInputs + fNumOutputs) * (audioMemSize + (8192 * audioMemSize))) / wasmMemSize) + 1); // memory initial pages
    gGlobal->gWASMVisitor->finishSection(memory_start);
    
    // Exports
    int32_t exports_start = gGlobal->gWASMVisitor->startSection(BinaryConsts::Section::Export);
    fBinaryOut << U32LEB(12); // num export = 11 functions + 1 memory
    {
        // Functions in alphabetical order
        exportFunction("compute");
        exportFunction("getNumInputs");
        exportFunction("getNumOutputs");
        exportFunction("getParamValue");
        exportFunction("getSampleRate");
        exportFunction("init");
        exportFunction("instanceClear");
        exportFunction("instanceConstants");
        exportFunction("instanceInit");
        exportFunction("instanceResetUserInterface");
        exportFunction("setParamValue");
        
        // Memory
        fBinaryOut << "memory";
        fBinaryOut << U32LEB(2);  // Memory kind
        fBinaryOut << U32LEB(0);  // Memory index
    }
    gGlobal->gWASMVisitor->finishSection(exports_start);
    
    // Functions
    int32_t functions_start = gGlobal->gWASMVisitor->startSection(BinaryConsts::Section::Code);
    fBinaryOut << U32LEB(14); // num functions
    
    // Functions in alphabetical order
    
    // Inits
    
    // classInit
    std::cout << "classInit" << std::endl;
    {
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        DspRenamer renamer;
        BlockInst* renamed = renamer.getCode(fStaticInitInstructions);
        BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
        generateWASMBody(inlined);
    }
    
    // compute
    std::cout << "compute" << std::endl;
    generateCompute();
    
    // getNumInputs/getNumOutputs
    generateGetInputs("getNumInputs", false, false)->accept(gGlobal->gWASMVisitor);
    generateGetOutputs("getNumOutputs", false, false)->accept(gGlobal->gWASMVisitor);
    
    // getParamValue (adhoc generation since FIR cannot be generated)
    {
        size_t size_pos = fBinaryOut.writeU32LEBPlaceholder();
        size_t start = fBinaryOut.size();
        
        // Describe function argument types
        LocalVariableCounter local_counter;
        local_counter.generate(&fBinaryOut);
        
        // Index in the dsp
        fBinaryOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // 0 = dsp
        fBinaryOut << int8_t(BinaryConsts::GetLocal) << U32LEB(1);  // 1 = index
        fBinaryOut << int8_t(gBinOpTable[kAdd]->fWasmFloat);
         
        // Load value from index
        fBinaryOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32LoadMem) : int8_t(BinaryConsts::F64LoadMem));
        gGlobal->gWASMVisitor->emitMemoryAccess();
        
        // Return value
        fBinaryOut << int8_t(BinaryConsts::Return);
        
        // Generate end
        fBinaryOut << int8_t(BinaryConsts::End);
        size_t size = fBinaryOut.size() - start;
        fBinaryOut.writeAt(size_pos, U32LEB(size));
    }
   
    // getSampleRate
    WASInst::generateGetSampleRate()->accept(gGlobal->gWASMVisitor);
    
    // init
    WASInst::generateInit()->accept(gGlobal->gWASMVisitor);
    
    // instanceClear
    {
        // Rename 'sig' in 'dsp' and remove 'dsp' allocation
        DspRenamer renamer;
        generateWASMBody(renamer.getCode(fClearInstructions));
    }
    
    // instanceConstants
    {
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        DspRenamer renamer;
        BlockInst* renamed = renamer.getCode(fInitInstructions);
        BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
        generateWASMBody(inlined);
    }
    
    // instanceInit
    WASInst::generateInstanceInit()->accept(gGlobal->gWASMVisitor);
    
    // instanceResetUserInterface
    {
        // Rename 'sig' in 'dsp' and remove 'dsp' allocation
        DspRenamer renamer;
        generateWASMBody(renamer.getCode(fResetUserInterfaceInstructions));
    }
    
    // Always generated mathematical functions
    WASInst::generateIntMax()->accept(gGlobal->gWASMVisitor);
    WASInst::generateIntMin()->accept(gGlobal->gWASMVisitor);
    
    // setParamValue (adhoc generation since FIR cannot be generated)
    {
        size_t size_pos = fBinaryOut.writeU32LEBPlaceholder();
        size_t start = fBinaryOut.size();
        
        // Describe function argument types
        LocalVariableCounter local_counter;
        local_counter.generate(&fBinaryOut);
        
        // Index in the dsp
        fBinaryOut << int8_t(BinaryConsts::GetLocal) << U32LEB(0);  // 0 = dsp
        fBinaryOut << int8_t(BinaryConsts::GetLocal) << U32LEB(1);  // 1 = index
        fBinaryOut << int8_t(gBinOpTable[kAdd]->fWasmFloat);
        
        // Value
        fBinaryOut << int8_t(BinaryConsts::GetLocal) << U32LEB(2);  // 2 = value
        
        // Store value at index
        fBinaryOut << ((gGlobal->gFloatSize == 1) ? int8_t(BinaryConsts::F32StoreMem) : int8_t(BinaryConsts::F64StoreMem));
        gGlobal->gWASMVisitor->emitMemoryAccess();
        
        // Generate end
        fBinaryOut << int8_t(BinaryConsts::End);
        size_t size = fBinaryOut.size() - start;
        fBinaryOut.writeAt(size_pos, U32LEB(size));
    }
    
    // Possibly generate separated functions
    generateComputeFunctions(gGlobal->gWASMVisitor);
    
    gGlobal->gWASMVisitor->finishSection(functions_start);
   
    // Finally produce output stream
    fBinaryOut.writeTo(*fOut);
    
    /*
    int n = 0;
  
    tab(n, *fOut);
    gGlobal->gWASMVisitor->Tab(n);
    
    tab(n, *fOut); *fOut << "(module";
    
        // Global declarations (mathematical functions, global variables...)
        gGlobal->gWASMVisitor->Tab(n+1);
    
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first
        generateGlobalDeclarations(gGlobal->gWASMVisitor);
    
        // Imported functions
        tab(n+1, *fOut); *fOut << "(func $print-i (import \"imports\" \"print\") (param i32))";
        tab(n+1, *fOut); *fOut << "(func $print-f (import \"imports\" \"print\") (param f32))";
    
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
        gGlobal->gWASMVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gWASMVisitor);
        
        // After field declaration...
        generateSubContainers();
    
        //*fOut << "(memory (export \"memory\") 16)";
        tab(n+1, *fOut);
        *fOut << "(memory (export \"memory\") "
              << ((pow2limit(gGlobal->gWASMVisitor->getStructSize() + (fNumInputs + fNumOutputs) * (audioMemSize + (8192 * audioMemSize))) / wasmMemSize) + 1) << ")";
    
        // Always generated mathematical functions
        tab(n+1, *fOut);
        
        tab(n+1, *fOut); *fOut << "(func $min_i (param $v1 i32) (param $v2 i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (select (get_local $v1) (get_local $v2) (i32.lt_s (get_local $v1) (get_local $v2))))";
        tab(n+1, *fOut); *fOut << ")";
        
        tab(n+1, *fOut); *fOut << "(func $max_i (param $v1 i32) (param $v2 i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (select (get_local $v2) (get_local $v1) (i32.lt_s (get_local $v1) (get_local $v2))))";
        tab(n+1, *fOut); *fOut << ")";
        
    
        // tab(n+1, *fOut); *fOut << "(func $fmod" << isuffix() << " (type $0) (param $value " << realStr << ") (param $1 " << realStr << ") (result " << realStr << ")";
        // tab(n+2, *fOut); *fOut << "(return (call $" << realStr << "-rem (get_local $value) (get_local $1)))";
        // tab(n+1, *fOut); *fOut << ")";
         
        // tab(n+1, *fOut); *fOut <<  "(func $log10" << isuffix() << " (type $2) (param $value " << realStr << ") (result " << realStr << ")";
        // tab(n+2, *fOut); *fOut << "(return (" << realStr << ".div (call $log (get_local $value)) (call $log (" << realStr << ".const 10))))";
        // tab(n+1, *fOut); *fOut << ")";
    
    
        tab(n+1, *fOut); *fOut << "(func $getNumInputs (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.const " << fNumInputs << "))";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $getNumOutputs (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.const " << fNumOutputs << "))";
        tab(n+1, *fOut); *fOut << ")";
    
        // Inits
        tab(n+1, *fOut); *fOut << "(func $classInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
                DspRenamer renamer;
                BlockInst* renamed = renamer.getCode(fStaticInitInstructions);
                BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
                generateWASMBlock(inlined);
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceConstants (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
                DspRenamer renamer;
                BlockInst* renamed = renamer.getCode(fInitInstructions);
                BlockInst* inlined = inlineSubcontainersFunCalls(renamed);
                generateWASMBlock(inlined);
          }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceResetUserInterface (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fResetUserInterfaceInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceClear (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fClearInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $init (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $classInit (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceInit (get_local $dsp) (get_local $samplingFreq))";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $instanceConstants (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceResetUserInterface (get_local $dsp))";
            tab(n+2, *fOut); *fOut << "(call $instanceClear (get_local $dsp))";
        tab(n+1, *fOut); *fOut << ")";
        
        // getSampleRate
        tab(n+1, *fOut); *fOut << "(func $getSampleRate (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.load (i32.add (get_local $dsp) (i32.const " << gGlobal->gWASMVisitor->getFieldOffset("fSamplingFreq") << "))))";
        tab(n+1, *fOut); *fOut << ")";
    
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
        generateCompute();
        
        // Possibly generate separated functions
        gGlobal->gWASMVisitor->Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(gGlobal->gWASMVisitor);
    
    tab(n, *fOut); *fOut << ")";
    tab(n, *fOut);
    */
    
    // Helper code
    int n = 0;
    
    // User interface : prepare the JSON string...
    JSONInstVisitor json_visitor(fNumInputs, fNumOutputs);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);
    
    // Generate JSON and getDSPSize
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
    /*
    tab(n+1, *fOut); *fOut << "(func $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)";
        tab(n+2, *fOut);
        gGlobal->gWASMVisitor->Tab(n+2);
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        fComputeBlockInstructions->pushBackInst(loop);
        MoveVariablesInFront2 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions, true);
        block->accept(gGlobal->gWASMVisitor);
    tab(n+1, *fOut); *fOut << ")";
    */
    
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    fComputeBlockInstructions->pushBackInst(loop);
    MoveVariablesInFront2 mover;
    BlockInst* block = mover.getCode(fComputeBlockInstructions, true);
    gGlobal->gWASMVisitor->generateFunDefBody(block);
}
