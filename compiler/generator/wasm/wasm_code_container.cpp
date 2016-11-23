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
 
    1) mathematical functions are either part of WebAssembly (like f32.sqrt, f32.main, f32.max), or are imported from the external Math context,
    or implementted manually (like fmod or log10)
    2) local variables have to be declared first on the block, before being actually initialized or set : this is done using MoveVariablesInFront3

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
        gGlobal->gWASMVisitor = new WASMInstVisitor(fOut);
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

void WASMCodeContainer::produceInternal()
{
    // Fields generation
    generateGlobalDeclarations(gGlobal->gWASMVisitor);
    generateDeclarations(gGlobal->gWASMVisitor);
}

void WASMCodeContainer::produceClass()
{
    int n = 0;
  
    tab(n, *fOut);
    gGlobal->gWASMVisitor->Tab(n);
    
    tab(n, *fOut); *fOut << "(module";
    
        // Type definition
        tab(n+1, *fOut); *fOut << "(type $0 (func (param " << realStr << " " << realStr << ") (result " << realStr << ")))";
        tab(n+1, *fOut); *fOut << "(type $1 (func (param " << realStr << ") (result i32)))";
        tab(n+1, *fOut); *fOut << "(type $2 (func (param " << realStr << ") (result " << realStr << ")))";
        tab(n+1, *fOut); *fOut << "(type $3 (func (param i32) (result i32)))";
        tab(n+1, *fOut); *fOut << "(type $4 (func (param i32 i32)))";
        tab(n+1, *fOut); *fOut << "(type $5 (func (param i32)))";
        tab(n+1, *fOut); *fOut << "(type $6 (func (param i32 i32 " << realStr << ")))";
        tab(n+1, *fOut); *fOut << "(type $7 (func (param i32 i32) (result " << realStr << ")))";
        tab(n+1, *fOut); *fOut << "(type $8 (func (param i32 i32 i32 i32)))";
    
        // Global declarations (mathematical functions, global variables...)
        gGlobal->gWASMVisitor->Tab(n+1);
    
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first
        sortDeclareFunctions sorter(gGlobal->gWASMVisitor->getMathLibTable());
        fGlobalDeclarationInstructions->fCode.sort(sorter);
        generateGlobalDeclarations(gGlobal->gWASMVisitor);
    
        // Always generated mathematical functions
        tab(n+1, *fOut); *fOut << "(import $" << realStr << "-rem \"asm2wasm\" \"" << realStr
                               << "-rem\" (param " << realStr <<  " " << realStr << ") (result "<< realStr << "))";
        tab(n+1, *fOut); *fOut << "(import $" << realStr << "-to-int \"asm2wasm\" \""
                               << realStr << "-to-int\" (param " << realStr << ") (result i32))";
        tab(n+1, *fOut); *fOut << "(import $log " << "\"asm2wasm\" \"log\" (param " << realStr << ") (result " << realStr << "))";
    
        // Memory access
        tab(n+1, *fOut); *fOut << "(import \"env\" \"memory\" (memory $0 256 256))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"table\" (table 0 0 anyfunc))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"memoryBase\" (global $memoryBase i32))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"tableBase\" (global $tableBase i32))";
    
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
    
        // Always generated mathematical functions
        tab(n+1, *fOut);
    
        tab(n+1, *fOut); *fOut << "(func $fmod" << isuffix() << " (type $0) (param $0 " << realStr << ") (param $1 " << realStr << ") (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(call_import $" << realStr << "-rem (get_local $0) (get_local $1))";
        tab(n+1, *fOut); *fOut << ")";
        
        tab(n+1, *fOut); *fOut <<  "(func $log10" << isuffix() << "f (type $2) (param $0 " << realStr << ") (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(return (" << realStr << ".div (call_import $log (get_local $0)) (call_import $log (" << realStr << ".const 10))))";
        tab(n+1, *fOut); *fOut << ")";
    
        // Fields : compute the structure size to use in 'new'
        gGlobal->gWASMVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gWASMVisitor);
        
        // After field declaration...
        generateSubContainers();
    
        tab(n+1, *fOut); *fOut << "(func $getNumInputs (type $3) (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.const " << fNumInputs << "))";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $getNumOutputs (type $3) (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.const " << fNumOutputs << "))";
        tab(n+1, *fOut); *fOut << ")";
    
        // Inits
        tab(n+1, *fOut); *fOut << "(func $classInit (type $4) (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fStaticInitInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceConstants (type $4) (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fInitInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceResetUserInterface (type $5) (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fResetUserInterfaceInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceClear (type $5) (param $dsp i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                DspRenamer renamer;
                generateWASMBlock(renamer.getCode(fClearInstructions));
            }
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $init (type $4) (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $classInit (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceInit (get_local $dsp) (get_local $samplingFreq))";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func $instanceInit (type $4) (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $instanceConstants (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceResetUserInterface (get_local $dsp))";
            tab(n+2, *fOut); *fOut << "(call $instanceClear (get_local $dsp))";
        tab(n+1, *fOut); *fOut << ")";
        
        // getSampleRate
        tab(n+1, *fOut); *fOut << "(func $getSampleRate (type $3) (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(return (i32.load (i32.add (i32.const " << gGlobal->gWASMVisitor->getFieldOffset("fSamplingFreq") << ") (get_local $dsp))))";
        tab(n+1, *fOut); *fOut << ")";
    
        // setParamValue
        tab(n+1, *fOut); *fOut << "(func $setParamValue (type $6) (param $dsp i32) (param $index i32) (param $value " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(" << realStr << ".store ";
                tab(n+3, *fOut); *fOut << "(i32.add (get_local $dsp) (get_local $index))";
                tab(n+3, *fOut); *fOut << "(get_local $value)";
            tab(n+2, *fOut); *fOut << ")";
        tab(n+1, *fOut); *fOut << ")";
    
        // getParamValue
        tab(n+1, *fOut); *fOut << "(func $getParamValue (type $7) (param $dsp i32) (param $index i32) (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(return (" << realStr << ".load (i32.add (get_local $dsp) (get_local $index))))";
        tab(n+1, *fOut); *fOut << ")";

        // compute
        generateCompute(n);
        
        // Possibly generate separated functions
        gGlobal->gWASMVisitor->Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(gGlobal->gWASMVisitor);
    
    tab(n, *fOut); *fOut << ")";
    tab(n, *fOut);
    
    /*
    // Helper code
    
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
    */
}

void WASMScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut); *fOut << "(func $compute (type $8) (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)";
        tab(n+2, *fOut);
        gGlobal->gWASMVisitor->Tab(n+2);
    
        /*
        dump2FIR(fComputeBlockInstructions, &cout);

        // Moves all variables declaration at the beginning of the block
        MoveVariablesInFront3 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions);
        block->accept(gGlobal->gWASMVisitor);

        dump2FIR(block, &cout);
        */
        
        // Generates one single scalar loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        fComputeBlockInstructions->pushBackInst(loop);
        generateWASMBlock(fComputeBlockInstructions);

    tab(n+1, *fOut); *fOut << ")";
}
