/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#include "rust_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 Rust backend description:

 - 'usize' type has to be used for all array access: cast index as 'usize' only when using it (load/store arrays)
 - TODO: local stack variables (shared computation) are normally non-mutable
 - inputN/outputN local buffer variables in 'compute' are not created at all: they are replaced directly in the code
 with inputs[N]/outputs[N] (done in instructions_compiler.cpp)
 - BoolOpcode BinOps always casted to integer
 - 'delete' for SubContainers is not generated
 - add 'kMutable' and 'kReference' address access type

*/

map<string, bool> RustInstVisitor::gFunctionSymbolTable;

dsp_factory_base* RustCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* RustCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new RustScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* RustCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

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
        throw faustexception("ERROR : OpenMP not supported for Rust\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Rust\n");
    } else if (gGlobal->gVectorSwitch) {
        // container = new RustVectorCodeContainer(name, numInputs, numOutputs, dst);
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
    *fOut << "pub struct " << fKlassName << " {";
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer.Tab(n + 1);
    generateDeclarations(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "impl " << fKlassName << " {";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    produceInfoFunctions(n + 1, fKlassName, "&self", false, FunTyped::kDefault, &fCodeProducer);

    // Init
    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&fCodeProducer);

    tab(n + 1, *fOut);
    *fOut << "fn instance_init" << fKlassName << "(&mut self, sample_rate: i32) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    generateResetUserInterface(&fCodeProducer);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Fill
    tab(n + 1, *fOut);
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n + 1, *fOut);
        *fOut << "fn fill" << fKlassName << subst("(&mut self, $0: i32, table: &mut[i32]) {", counter);
    } else {
        tab(n + 1, *fOut);
        *fOut << "fn fill" << fKlassName << subst("(&mut self, $0: i32, table: &mut[$1]) {", counter, ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateComputeBlock(&fCodeProducer);
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(counter);
    loop->accept(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;

    tab(n, *fOut);
    *fOut << "}" << endl;

    // Memory methods
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "pub fn new" << fKlassName << "() -> " << fKlassName << " { ";
    tab(n + 1, *fOut);
    *fOut << fKlassName << " {";
    RustInitFieldsVisitor initializer(fOut, n + 2);
    generateDeclarations(&initializer);
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    *fOut << "}";
}

void RustCodeContainer::produceClass()
{
    int n = 0;

    // Generate gub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "#[cfg_attr(feature = \"default-boxed\", derive(default_boxed::DefaultBoxed))]";
    tab(n, *fOut);
    *fOut << "#[repr(C)]";
    tab(n, *fOut);
    *fOut << "pub struct " << fKlassName << " {";
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer.Tab(n + 1);
    generateDeclarations(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);

    tab(n, *fOut);
    *fOut << "impl FaustDsp for " << fKlassName << " {";

    // Associated type
    tab(n + 1, *fOut);
    *fOut << "type T = " << ifloat() << ";";

    // Memory methods
    tab(n + 2, *fOut);
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 2, *fOut);
        *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
        tab(n + 2, *fOut);
        fAllocateInstructions->accept(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    tab(n + 1, *fOut);

    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
        tab(n + 2, *fOut);
        fDestroyInstructions->accept(&fCodeProducer);
         back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    *fOut << "fn new() -> " << fKlassName << " { ";
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 2, *fOut);
        *fOut << "allocate" << fKlassName << "(dsp);";
    }
    tab(n + 2, *fOut);
    *fOut << fKlassName << " {";
    RustInitFieldsVisitor initializer(fOut, n + 3);
    generateDeclarations(&initializer);
    tab(n + 2, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    *fOut << "}";

    // Print metadata declaration
    produceMetadata(n + 1);

    // Get sample rate method
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    generateGetSampleRate("get_sample_rate", "&self", false, false)->accept(&fCodeProducer);

    produceInfoFunctions(n + 1, "", "&self", false, FunTyped::kDefault, &fCodeProducer);

    // Inits

    // TODO
    //
    // CInstVisitor codeproducer1(fOut, "");
    // codeproducer1.Tab(n+2);
    // generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
    // generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);

    tab(n + 1, *fOut);
    *fOut << "fn class_init(sample_rate: i32) {";
    {
        tab(n + 2, *fOut);
        // Local visitor here to avoid DSP object type wrong generation
        RustInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 2);
        generateStaticInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << "fn instance_reset_params(&mut self) {";
    {
        tab(n + 2, *fOut);
        // Local visitor here to avoid DSP object type wrong generation
        RustInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 2);
        generateResetUserInterface(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << "fn instance_clear(&mut self) {";
    {
        tab(n + 2, *fOut);
        // Local visitor here to avoid DSP object type wrong generation
        RustInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 2);
        generateClear(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << "fn instance_constants(&mut self, sample_rate: i32) {";
    {
        tab(n + 2, *fOut);
        // Local visitor here to avoid DSP object type wrong generation
        RustInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 2);
        generateInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << "fn instance_init(&mut self, sample_rate: i32) {";
    tab(n + 2, *fOut);
    *fOut << "self.instance_constants(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "self.instance_reset_params();";
    tab(n + 2, *fOut);
    *fOut << "self.instance_clear();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << "fn init(&mut self, sample_rate: i32) {";
    tab(n + 2, *fOut);
    *fOut << fKlassName << "::class_init(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "self.instance_init(sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "}";

    // Pre-pass of user interface instructions to determine parameter lookup table (field name => index)
    UserInterfaceParameterMapping parameterMappingVisitor;
    fUserInterfaceInstructions->accept(&parameterMappingVisitor);
    auto parameterLookup = parameterMappingVisitor.getParameterLookup();

    // User interface (non-static method)
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "fn build_user_interface(&self, ui_interface: &mut dyn UI<Self::T>) {";
    tab(n + 2, *fOut);
    *fOut << "Self::build_user_interface_static(ui_interface);";
    tab(n + 1, *fOut);
    *fOut << "}";

    // User interface (static method)
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "fn build_user_interface_static(ui_interface: &mut dyn UI<Self::T>) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    RustUIInstVisitor uiCodeproducer(fOut, "", parameterLookup, n + 2);
    generateUserInterface(&uiCodeproducer);
    back(1, *fOut);
    *fOut << "}";

    // Parameter getter/setter
    produceParameterGetterSetter(n + 1, parameterLookup);

    // Compute
    generateCompute(n + 1);

    tab(n, *fOut);
    *fOut << "}" << endl;
    tab(n, *fOut);
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
}

void RustCodeContainer::produceMetadata(int n)
{
    tab(n, *fOut);
    *fOut << "fn metadata(&self, m: &mut dyn Meta) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(n + 1, *fOut);
            *fOut << "m.declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
            // "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(n + 1, *fOut);
                    *fOut << "m.declare(\"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(n + 1, *fOut);
                    *fOut << "m.declare(\""
                          << "contributor"
                          << "\", " << **j << ");";
                }
            }
        }
    }

    tab(n, *fOut);
    *fOut << "}" << endl;
}

void RustCodeContainer::produceInfoFunctions(int tabs, const string& classname, const string& obj, bool ismethod, FunTyped::FunAttribute funtype, TextInstVisitor* producer)
{
    producer->Tab(tabs);
    generateGetInputs(subst("get_num_inputs$0", classname), obj, false, funtype)->accept(&fCodeProducer);
    generateGetOutputs(subst("get_num_outputs$0", classname), obj, false, funtype)->accept(&fCodeProducer);
}

void RustCodeContainer::produceParameterGetterSetter(int tabs, map<string, int> parameterLookup)
{
    // Add `get_param`
    tab(tabs, *fOut);
    tab(tabs, *fOut);
    *fOut << "fn get_param(&self, param: ParamIndex) -> Option<Self::T> {";
    tab(tabs + 1, *fOut);
    *fOut << "match param.0 {";
    for (const auto &paramPair : parameterLookup) {
        const auto fieldName = paramPair.first;
        const auto index = paramPair.second;
        tab(tabs + 2, *fOut);
        *fOut << index << " => Some(self." << fieldName << "),";
    }
    tab(tabs + 2, *fOut);
    *fOut << "_ => None,";
    tab(tabs + 1, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);
    *fOut << "}";

    // Add `set_param`
    tab(tabs, *fOut);
    tab(tabs, *fOut);
    *fOut << "fn set_param(&mut self, param: ParamIndex, value: Self::T) {";
    tab(tabs + 1, *fOut);
    *fOut << "match param.0 {";
    for (const auto &paramPair : parameterLookup) {
        const auto fieldName = paramPair.first;
        const auto index = paramPair.second;
        tab(tabs + 2, *fOut);
        *fOut << index << " => { self." << fieldName << " = value }";
    }
    tab(tabs + 2, *fOut);
    *fOut << "_ => {}";
    tab(tabs + 1, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);
    *fOut << "}";
}

// Scalar
RustScalarCodeContainer::RustScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                 int sub_container_type)
    : RustCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void RustScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "fn compute("
          << subst("&mut self, $0: i32, inputs: &[&[Self::T]], outputs: &mut[&mut[Self::T]]) {", fFullCount);
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates one single scalar loop
    std::vector<std::string> iterators;
    for (int i = 0; i < fNumInputs; ++i) {
        iterators.push_back("inputs" + std::to_string(i));
    }
    for (int i = 0; i < fNumOutputs; ++i) {
        iterators.push_back("outputs" + std::to_string(i));
    }
    IteratorForLoopInst* loop = fCurLoop->generateSimpleScalarLoop(iterators);
    loop->accept(&fCodeProducer);
    
    // Currently for soundfile management
    generatePostComputeBlock(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// Vector
RustVectorCodeContainer::RustVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), RustCodeContainer(name, numInputs, numOutputs, out)
{
}

void RustVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut);
    *fOut << "fn compute("
          << subst("&mut self, $0: i32, inputs: &[&[Self::T]], outputs: &mut[&mut[Self::T]]) {", fFullCount);
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// OpenMP
RustOpenMPCodeContainer::RustOpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : OpenMPCodeContainer(numInputs, numOutputs), RustCodeContainer(name, numInputs, numOutputs, out)
{
}

void RustOpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut);
    *fOut << "fn compute("
          << subst("&mut self, $0: i32, inputs: &[&[Self::T]], outputs: &mut[&mut[Self::T]]) {", fFullCount);
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    fGlobalLoopBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// Works stealing scheduler
RustWorkStealingCodeContainer::RustWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs,
                                                             std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "dsp"), RustCodeContainer(name, numInputs, numOutputs, out)
{
}

void RustWorkStealingCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates "computeThread" code
    // Note that users either have to adjust the trait in their architecture file.
    // Alternatively we would have to attach this method to the impl, not the trait.
    tab(n, *fOut);
    *fOut << "pub fn compute_thread(" << fKlassName << "&mut self, num_thread: i32) {";
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);

    // Generate it
    fThreadLoopBlock->accept(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "}" << endl;

    // Compute "compute" declaration
    tab(n, *fOut);
    *fOut << "fn compute("
          << subst("&mut self, $0: i32, inputs: &[&[Self::T]], outputs: &mut[&mut[Self::T]]) {", fFullCount);
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "}" << endl;

    tab(n, *fOut);
    *fOut << "extern \"C\" void computeThreadExternal(&mut self, num_thread: i32) {";
    tab(n + 1, *fOut);
    *fOut << "compute_thread((" << fKlassName << "*)dsp, num_thread);";
    tab(n, *fOut);
    *fOut << "}" << endl;
}
