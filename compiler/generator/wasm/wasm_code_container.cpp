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

using namespace std;

dsp_factory_base* WASMCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    (dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : "");
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
{}

void WASMCodeContainer::produceClass()
{
    int n = 0;
  
    tab(n, *fOut);
    gGlobal->gWASMVisitor->Tab(n);
    
    tab(n, *fOut); *fOut << "(module";
    
        // Type definition
        tab(n+1, *fOut); *fOut << "(type $0 (func (param f64 f64) (result f64)))";
        tab(n+1, *fOut); *fOut << "(type $1 (func (param f64) (result i32)))";
        tab(n+1, *fOut); *fOut << "(type $2 (func (param f64) (result f64)))";
        tab(n+1, *fOut); *fOut << "(type $3 (func (param i32) (result i32)))";
        tab(n+1, *fOut); *fOut << "(type $4 (func (param i32 i32)))";
        tab(n+1, *fOut); *fOut << "(type $5 (func (param i32)))";
        tab(n+1, *fOut); *fOut << "(type $6 (func (param i32 i32 f64)))";
        tab(n+1, *fOut); *fOut << "(type $7 (func (param i32 i32) (result f64)))";
        tab(n+1, *fOut); *fOut << "(type $8 (func (param i32 i32 i32 i32)))";

        // Imported functions : TO 64/32 support
        tab(n+1, *fOut); *fOut << "(import $log \"global.Math\" \"log\" (param " << realStr << ") (result " << realStr << "))";
        tab(n+1, *fOut); *fOut << "(import $f64-rem \"asm2wasm\" \"f64-rem\" (param " << realStr <<  " " << realStr << ") (result "<< realStr << "))";
        tab(n+1, *fOut); *fOut << "(import $f64-to-int \"asm2wasm\" \"f64-to-int\" (param " << realStr << ") (result i32))";
    
        // Memory access
        tab(n+1, *fOut); *fOut << "(import \"env\" \"memory\" (memory $0 256 256))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"table\" (table 0 0 anyfunc))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"memoryBase\" (global $memoryBase i32))";
        tab(n+1, *fOut); *fOut << "(import \"env\" \"tableBase\" (global $tableBase i32))";
    
        // Exported functions
        tab(n+1, *fOut); *fOut << "(export \"getNumInputs\" (func $getNumInputs))";
        tab(n+1, *fOut); *fOut << "(export \"getNumOutputs\" (func $getNumOutputs))";
        tab(n+1, *fOut); *fOut << "(export \"classInit\" (func $classInit))";
        tab(n+1, *fOut); *fOut << "(export \"instanceInit\" (func $instanceInit))";
        tab(n+1, *fOut); *fOut << "(export \"init\" (func $init))";
        tab(n+1, *fOut); *fOut << "(export \"getSampleRate\" (func $getSampleRate))";
        tab(n+1, *fOut); *fOut << "(export \"setParamValue\" (func $setParamValue))";
        tab(n+1, *fOut); *fOut << "(export \"getParamValue\" (func $getParamValue))";
        tab(n+1, *fOut); *fOut << "(export \"compute\" (func $compute))";
    
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first...
        gGlobal->gWASMVisitor->Tab(n+1);
        generateGlobalDeclarations(gGlobal->gWASMVisitor);
    
        // Always generated mathematical functions
        tab(n+1, *fOut);
        
        tab(n+1, *fOut); *fOut << "(func (type $0) $fmodf (param $0 " << realStr << ") (param $1 " << realStr << ") (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(call_import $" << realStr << "-rem (get_local $0) (get_local $1))";
        tab(n+1, *fOut); *fOut << ")";
        
        tab(n+1, *fOut); *fOut <<  "(func (type $2) $log10f (param $0 " << realStr << ") (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(" << realStr << ".div (call_import $log (get_local $0)) (call_import $log (" << realStr << ".const 10)))";
        tab(n+1, *fOut); *fOut << ")";
    
        // Fields : compute the structure size to use in 'new'
        gGlobal->gWASMVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gWASMVisitor);
        
        // After field declaration...
        generateSubContainers();
    
        tab(n+1, *fOut); *fOut << "(func (type $3) $getNumInputs (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(i32.const " << fNumInputs << ")";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func (type $3) $getNumOutputs (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(i32.const " << fNumOutputs << ")";
        tab(n+1, *fOut); *fOut << ")";
    
        // Inits
        tab(n+1, *fOut); *fOut << "(func (type $4) $classInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
        // TODO
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func (type $4) $instanceConstants (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
        // TODO
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func (type $5) $instanceResetUserInterface (param $dsp i32)";
        tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
        // TODO
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func (type $5) $instanceClear (param $dsp i32)";
        tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
        // TODO
        tab(n+1, *fOut); *fOut << ")";
        
        tab(n+1, *fOut); *fOut << "(func (type $4) $instanceInit (param $dsp i32) (param $samplingFreq i32)";
        tab(n+2, *fOut); gGlobal->gWASMVisitor->Tab(n+2);
        // TODO
        tab(n+1, *fOut); *fOut << ")";
        
        tab(n+1, *fOut); *fOut << "(func (type $4) $init (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $classInit (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceInit (get_local $dsp) (get_local $samplingFreq))";
        tab(n+1, *fOut); *fOut << ")";
    
        tab(n+1, *fOut); *fOut << "(func (type $4) $instanceInit (param $dsp i32) (param $samplingFreq i32)";
            tab(n+2, *fOut); *fOut << "(call $instanceConstants (get_local $dsp) (get_local $samplingFreq))";
            tab(n+2, *fOut); *fOut << "(call $instanceResetUserInterface (get_local $dsp))";
            tab(n+2, *fOut); *fOut << "(call $instanceClear (get_local $dsp))";
        tab(n+1, *fOut); *fOut << ")";
        
        // getSampleRate
        tab(n+1, *fOut); *fOut << "(func (type $3) $getSampleRate (param $dsp i32) (result i32)";
            tab(n+2, *fOut); *fOut << "(i32.load offset=" << gGlobal->gWASMVisitor->getFieldOffset("fSamplingFreq") << " (get_local $dsp))";
        tab(n+1, *fOut); *fOut << ")";
    
        // setParamValue : TO 64/32 support
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "(func (type $6) $setParamValue (param $dsp i32) (param $index i32) (param $value " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(f32.store ";
                tab(n+3, *fOut); *fOut << "(i32.add (get_local $dsp) (get_local $index))";
                tab(n+3, *fOut); *fOut << "(f32.demote/f64 (get_local $value))";
            tab(n+2, *fOut); *fOut << ")";
        tab(n+1, *fOut); *fOut << ")";
    
        // getParamValue : TO 64/32 support
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "(func (type $7) $getParamValue (param $dsp i32) (param $index i32) (result " << realStr << ")";
            tab(n+2, *fOut); *fOut << "(f64.promote/f32 (f32.load (i32.add (get_local $dsp) (get_local $index))))";
        tab(n+1, *fOut); *fOut << ")";

        // compute
        generateCompute(n);
        
        // Possibly generate separated functions
        gGlobal->gWASMVisitor->Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(gGlobal->gWASMVisitor);
    
    tab(n, *fOut); *fOut << ")";
    tab(n, *fOut);
}

void WASMCodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{}

void WASMScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut); *fOut << "(func (type $8) $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)";
    tab(n+2, *fOut);
    gGlobal->gWASMVisitor->Tab(n+2);
    
    // Generates one single scalar loop and put is the the block
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    fComputeBlockInstructions->pushBackInst(loop);
    
    loop->accept(gGlobal->gWASMVisitor);

    tab(n+1, *fOut); *fOut << ")";
}
