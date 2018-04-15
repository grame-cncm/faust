/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#include "rust_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "fir_function_builder.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

/*
 Rust backend description:

 - 'usize' type has to be used for all array access: cast index as 'usize' only when using it (load/store arrays)
 - TODO: local stack variables (shared computation) are normally non-mutable 
 - inputN/outputN local buffer variables in 'compute' are not created at all: they are replaced directly in the code with inputs[N]/outputs[N] (done in instructions_compiler.cpp)
 - BoolOpcode BinOps always casted to integer
 - 'delete' for SubcContainers is not generated 
 - add  'fDummy' zone in 'mydsp' struct to publish it (if needed) in 'declare' when nullptr is used 
 - add 'kMutable' and 'kReference' address access type
 
*/

map <string, bool> RustInstVisitor::gFunctionSymbolTable;

dsp_factory_base* RustCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* RustCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new RustScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* RustCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for Rust\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for Rust\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Rust\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Rust\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        //container = new RustOpenMPCodeContainer(name, numInputs, numOutputs, dst);
        throw faustexception("ERROR : OpenMP not supported for Rust\n");
    } else if (gGlobal->gSchedulerSwitch) {
        //container = new RustWorkStealingCodeContainer(name, numInputs, numOutputs, dst);
        throw faustexception("ERROR : Scheduler not supported for Rust\n");
    } else if (gGlobal->gVectorSwitch) {
        //container = new RustVectorCodeContainer(name, numInputs, numOutputs, dst);
        throw faustexception("ERROR : Vector not supported for Rust\n");
    } else {
        container = new RustScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void RustCodeContainer::produceInternal()
{
    int n = 0;
  
    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
  
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "pub struct " << fKlassName << " {";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut);
    
        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "impl " << fKlassName << " {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);
        produceInfoFunctions(n+1, fKlassName, "&mut self", false, false, &fCodeProducer);
        
        // Init
        // TODO
        //generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&fCodeProducer);
        
        tab(n+1, *fOut); *fOut << "pub fn instanceInit" << fKlassName << "(&mut self, samplingFreq: i32) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
            generateResetUserInterface(&fCodeProducer);
            generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
     
        // Fill
        tab(n+1, *fOut);
        string counter = "count";
        if (fSubContainerType == kInt) {
            tab(n+1, *fOut); *fOut << "pub fn fill" << fKlassName << subst("(&mut self, $0: i32, output: &mut[i32]) {", counter);
        } else {
            tab(n+1, *fOut); *fOut << "pub fn fill" << fKlassName << subst("(&mut self, $0: i32, output: &mut[$1]) {", counter, ifloat());
        }
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateComputeBlock(&fCodeProducer);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&fCodeProducer);
       tab(n+1, *fOut); *fOut << "}" << endl;
    
    tab(n, *fOut); *fOut << "}" << endl;
    
    // Memory methods
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "pub fn new" << fKlassName << "() -> " << fKlassName << " { ";
        tab(n+1, *fOut); *fOut << fKlassName << " {";
        RustInitFieldsVisitor initializer(fOut, n+2);
        generateDeclarations(&initializer);
        tab(n+1, *fOut); *fOut << "}";
    tab(n, *fOut); *fOut << "}";
}

void RustCodeContainer::produceClass()
{
    int n = 0;
        
    // Ignore the following warning
    /*
    tab(n, *fOut); *fOut << "#![allow(unused_parens)]";
    tab(n, *fOut); *fOut << "#![allow(non_snake_case)]";
    tab(n, *fOut); *fOut << "#![allow(non_camel_case_types)]";
    */
    //tab(n, *fOut); *fOut << "#[derive(Copy, Clone, Default)] // 'Default' needed for struct default initialisation" ;

    // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
    
    // TODO
    //tab(n, *fOut); *fOut << "impl dsp<" << ifloat() <<"> for " << fKlassName << " {";
    tab(n, *fOut); *fOut << "pub struct " << fKlassName << " {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Dummy field used for 'declare'
        *fOut << "fDummy: " << ifloat() << ",";
        tab(n+1, *fOut);
    
        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "}";
    tab(n, *fOut);
    
    tab(n, *fOut); *fOut << "impl " << fKlassName << " {";

        // Memory methods
        tab(n+2, *fOut);
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n+2, *fOut); *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
                tab(n+2, *fOut);
                fAllocateInstructions->accept(&fCodeProducer);
            tab(n+2, *fOut); *fOut << "}";
        }
        
        tab(n+1, *fOut);
        
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
                tab(n+2, *fOut);
                fDestroyInstructions->accept(&fCodeProducer);
            tab(n+1, *fOut);  *fOut << "}";
            tab(n+1, *fOut);
            tab(n+1, *fOut);
        }
        
        *fOut << "pub fn new() -> " << fKlassName << " { ";
            if (fAllocateInstructions->fCode.size() > 0) {
                tab(n+2, *fOut); *fOut << "allocate" << fKlassName << "(dsp);";
            }
            tab(n+2, *fOut); *fOut << fKlassName << " {";
                tab(n+3, *fOut);
                *fOut << "fDummy: 0 as " << ifloat() << ",";
                RustInitFieldsVisitor initializer(fOut, n+3);
                generateDeclarations(&initializer);
            tab(n+2, *fOut); *fOut << "}";
        tab(n+1, *fOut); *fOut << "}";

        // Print metadata declaration
        tab(n+1, *fOut);
        produceMetadata(n+1);
  
        // Get sample rate method
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateGetSampleRate("&mut self", false, false)->accept(&fCodeProducer);
    
        produceInfoFunctions(n+1, "", "&mut self", false, false, &fCodeProducer);

        // Inits
        
        // TODO
        //
        // CInstVisitor codeproducer1(fOut, "");
        // codeproducer1.Tab(n+2);
        // generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
        // generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);
        
        tab(n+1, *fOut); *fOut << "pub fn classInit(samplingFreq: i32) {";
            {
                tab(n+2, *fOut);
                // Local visitor here to avoid DSP object type wrong generation  
                RustInstVisitor codeproducer(fOut, "");
                codeproducer.Tab(n+2);
                generateStaticInit(&codeproducer);
            }
        tab(n+1, *fOut); *fOut << "}";
        
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn instanceResetUserInterface(&mut self) {";
            {
                tab(n+2, *fOut);
                // Local visitor here to avoid DSP object type wrong generation
                RustInstVisitor codeproducer(fOut, "");
                codeproducer.Tab(n+2);
                generateResetUserInterface(&codeproducer);
            }
        tab(n+1, *fOut); *fOut << "}";
        
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn instanceClear(&mut self) {";
            {
                tab(n+2, *fOut);
                // Local visitor here to avoid DSP object type wrong generation
                RustInstVisitor codeproducer(fOut, "");
                codeproducer.Tab(n+2);
                generateClear(&codeproducer);
            }
        tab(n+1, *fOut); *fOut << "}";
        
      
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn instanceConstants(&mut self, samplingFreq: i32) {";
            {
                tab(n+2, *fOut);
                // Local visitor here to avoid DSP object type wrong generation
                RustInstVisitor codeproducer(fOut, "");
                codeproducer.Tab(n+2);
                generateInit(&codeproducer);
            }
        tab(n+1, *fOut); *fOut << "}";
       
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn instanceInit(&mut self, samplingFreq: i32) {";
            tab(n+2, *fOut); *fOut << "self.instanceConstants(samplingFreq);";
            tab(n+2, *fOut); *fOut << "self.instanceResetUserInterface();";
            tab(n+2, *fOut); *fOut << "self.instanceClear();";
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn init(&mut self, samplingFreq: i32) {";
            tab(n+2, *fOut); *fOut << fKlassName << "::classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "self.instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
    
        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "pub fn buildUserInterface(&mut self, ui_interface: &mut UI<" << ifloat() << ">) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateUserInterface(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        // Compute
        generateCompute(n+1);
    
    tab(n, *fOut);
    *fOut << "}" << endl;
    tab(n, *fOut);
}

void RustCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut); *fOut << "pub fn metadata(&mut self, m: &mut Meta) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(tabs+1, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become "contributor"
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(tabs+1, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                    tab(tabs+1, *fOut); *fOut << "m.declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }
 
    tab(tabs, *fOut); *fOut << "}" << endl;
}

// Scalar
RustScalarCodeContainer::RustScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :RustCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

RustScalarCodeContainer::~RustScalarCodeContainer()
{}

void RustScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "pub fn compute(" << subst("&mut self, $0: i32, inputs: &[&[$1]], outputs: &mut[&mut[$1]]) {", fFullCount, ifloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates one single scalar loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// Vector
RustVectorCodeContainer::RustVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), RustCodeContainer(name, numInputs, numOutputs, out)
{}

RustVectorCodeContainer::~RustVectorCodeContainer()
{}

void RustVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "pub fn compute(" << subst("&mut self, $0: i32, inputs: &[&[$1]], outputs: &mut[&mut[$1]]) {", fFullCount, ifloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates DSP loop
        fDAGBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// OpenMP
RustOpenMPCodeContainer::RustOpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :OpenMPCodeContainer(numInputs, numOutputs), RustCodeContainer(name, numInputs, numOutputs, out)
{}

void RustOpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "pub fn compute(" << subst("&mut self, $0: i32, inputs: &[&[$1]], outputs: &mut[&mut[$1]]) {", fFullCount, ifloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generate it
        fGlobalLoopBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

RustOpenMPCodeContainer::~RustOpenMPCodeContainer()
{}

// Works stealing scheduler
RustWorkStealingCodeContainer::RustWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :WSSCodeContainer(numInputs, numOutputs, "dsp"), RustCodeContainer(name, numInputs, numOutputs, out)
{}

RustWorkStealingCodeContainer::~RustWorkStealingCodeContainer()
{}

void RustWorkStealingCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates "computeThread" code
    tab(n, *fOut); *fOut << "pub fn computeThread(" << fKlassName << "&mut self, num_thread: i32) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generate it
        fThreadLoopBlock->accept(&fCodeProducer);

        tab(n, *fOut); *fOut << "}" << endl;

        // Compute "compute" declaration
        tab(n, *fOut); *fOut << "pub fn compute(" << subst("&mut self, $0: i32, inputs: &[&[$1]], outputs: &mut[&mut[$1]]) {", fFullCount, ifloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    tab(n, *fOut); *fOut << "extern \"C\" void computeThreadExternal(&mut self, num_thread: i32) {";
        tab(n+1, *fOut); *fOut << "computeThread((" << fKlassName << "*)dsp, num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}
