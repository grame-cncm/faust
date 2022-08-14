/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#include "jax_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
* the notes directly below are copied from julia_code_container.cpp
 Julia backend and module description:
 
 - 'delete' for SubContainers is not generated
 - add the ! character to the name of functions that modify their arguments
  (see https://docs.julialang.org/en/v1/manual/style-guide/#bang-convention)
 - in order to simplify global array typing, subcontainers are actually merged in the main DSP structure:
    - so 'mergeSubContainers' is used
    - global variables are added in the DSP structure
    - the JuliaInitFieldsVisitor class does initialisation for waveforms
    - the fGlobalDeclarationInstructions contains global functions and variables. It is "manually" used
    to generate global functions and move global variables declaration at DSP structure level.
*/

map<string, bool> JAXInstVisitor::gFunctionSymbolTable;

dsp_factory_base* JAXCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

JAXCodeContainer::JAXCodeContainer(const std::string& name, int numInputs, int numOutputs, std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut = out;
    
    // Allocate one static visitor
    if (!gGlobal->gJAXVisitor) {
        gGlobal->gJAXVisitor = new JAXInstVisitor(out, name);
    }
}

CodeContainer* JAXCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAXScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* JAXCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for JAX\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for JAX\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for JAX\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for JAX\n");
    } else if (gGlobal->gVectorSwitch) {
        //container = new JAXVectorCodeContainer(name, numInputs, numOutputs, dst);
        throw faustexception("ERROR : Vector not supported for JAX\n");
    } else {
        container = new JAXScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void JAXCodeContainer::produceClass()
{
    int n = 0;
    
    // Print header
    *fOut << "\"\"\"" << endl
          << "Code generated with Faust version " << FAUSTVERSION << endl;
    *fOut << "Compilation options: ";
    stringstream stream;
    gGlobal->printCompilationOptions(stream);
    *fOut << stream.str();
    tab(n, *fOut);
    *fOut << "\"\"\"";
    tab(n, *fOut);
    
    // dtype
    tab(n, *fOut);
    *fOut << "import jax.numpy as jnp";
    tab(n, *fOut);
    *fOut << "from flax import linen as nn";
    //tab(n, *fOut);
    //*fOut << "FAUSTFLOAT = float";
    // tab(n, *fOut);
    // *fOut << "dtype = " << ifloat();  // jnp.float32
    tab(n, *fOut);
        
    // Merge sub containers
    mergeSubContainers();

    // Functions
    tab(n, *fOut);
    gGlobal->gJAXVisitor->Tab(n);
    
    // Only generate globals functions
    //for (const auto& it : fGlobalDeclarationInstructions->fCode) {
    //    if (dynamic_cast<DeclareFunInst*>(it)) {
    //        it->accept(gGlobal->gJAXVisitor);
    //    }
    //}
   
    tab(n, *fOut);
    *fOut << "class " << fKlassName << "(nn.Module):";
    tab(n + 1, *fOut);

    // Fields
    gGlobal->gJAXVisitor->Tab(n + 1);
    //generateDeclarations(gGlobal->gJAXVisitor);
    // Generate global variables definition
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(gGlobal->gJAXVisitor);
        }
    }
    tab(n + 1, *fOut);
    *fOut << "sample_rate: int";
    //*fOut << "def __init__(self, sample_rate: int):";
    //tab(n + 2, *fOut);
    //*fOut << "super(" << fKlassName << ", self).__init__()";
    tab(n + 2, *fOut);
    //tab(n + 2, *fOut);
    //*fOut << "self.classInit(sample_rate)";
    //tab(n + 2, *fOut);
    //*fOut << "self.init_constants(sample_rate)";
    //tab(n + 2, *fOut);
    // *fOut << "self.instanceClear()";
    // tab(n + 2, *fOut);
    //*fOut << "self.instanceResetUserInterface()";
    //tab(n + 2, *fOut);
    //
    // Print metadata declaration
    //produceMetadata(n+1);

    // Get sample rate method
    tab(n, *fOut);
    gGlobal->gJAXVisitor->Tab(n);

    // todo: enable generateGetSampleRate
    //generateGetSampleRate("getSampleRate", "dsp", false, false)->accept(gGlobal->gJAXVisitor);

    tab(n+1, *fOut);
    produceInfoFunctions(n+1, "", "self", false, false, gGlobal->gJAXVisitor);
    
    //tab(n+1, *fOut);
    *fOut << "def classInit(self, sample_rate: int):";
    {
        tab(n + 2, *fOut);
        *fOut << "pass";
        tab(n + 2, *fOut);
        gGlobal->gJAXVisitor->Tab(n + 2);
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gJAXVisitor);
    }
    back(1, *fOut);

    tab(n + 1, *fOut);
    //*fOut << "def instanceResetUserInterface(self):";
    //{
    //    tab(n + 2, *fOut);
    //    *fOut << "state = {}";
    //    tab(n + 2, *fOut);
    //    generateResetUserInterface(gGlobal->gJAXVisitor);
    //    *fOut << "return state";
    //    tab(n + 2, *fOut);
    //}
    back(1, *fOut);

    // tab(n + 1, *fOut);
    // *fOut << "def instanceClear(self):";
    // {
    //     tab(n + 2, *fOut);
    //     generateClear(gGlobal->gJAXVisitor);
    // }
    // back(1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "def init_constants(self, state, sample_rate):";
    {
        tab(n + 2, *fOut);
        inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gJAXVisitor);
        tab(n + 2, *fOut);
        *fOut << "return state";
    }
    tab(n+1, *fOut);
   
    tab(n, *fOut);
    //tab(n + 1, *fOut);
    //*fOut << "def instanceInit(self, sample_rate: int):";
    //tab(n + 2, *fOut);
    //*fOut << "init_constants(dsp, sample_rate):";
    //tab(n + 2, *fOut);
    //*fOut << "instanceResetUserInterface(dsp):";
    //tab(n + 2, *fOut);
    //*fOut << "instanceClear(dsp):";
    //tab(n, *fOut);

    //tab(n, *fOut);
    //tab(n, *fOut);
    //*fOut << "def function init(self, sample_rate: int):";
    //tab(n + 1, *fOut);
    //*fOut << "def classInit(dsp, sample_rate: int)";
    //tab(n + 1, *fOut);
    //*fOut << "instanceInit(dsp, sample_rate: int)";
    //tab(n, *fOut);
    
    // JSON generation
    //tab(n+1, *fOut);
    //*fOut << "def getJSON(self):";
    //{
    //    string json;
    //    if (gGlobal->gFloatSize == 1) {
    //        json = generateJSON<float>();
    //    } else {
    //        json = generateJSON<double>();
    //    }
    //    tab(n + 2, *fOut);
    //    *fOut << "return \"\"\"" << flattenJSON(json) << "\"\"\"" << endl;
    //    tab(n + 1, *fOut);
    //}

    // User interface
    tab(n + 1, *fOut);
    *fOut << "def build_interface(self, state, T: int):";
    tab(n + 2, *fOut);
    gGlobal->gJAXVisitor->Tab(n + 2);
    generateUserInterface(gGlobal->gJAXVisitor);


    JAXInitFieldsVisitor initializer(fOut, n + 2);
    generateDeclarations(&initializer);
    // Generate global variables initialisation
    for (const auto& it : fGlobalDeclarationInstructions->fCode) {
        if (dynamic_cast<DeclareVarInst*>(it)) {
            it->accept(&initializer);
        }
    }
    tab(n + 2, *fOut);
    *fOut << "return state";
    
    //// Compute
    tab(n + 1, *fOut);
    generateCompute(n+1);
}

void JAXCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    // fFullCount is the number of samples
    // xfloat() is FAUSTFLOAT
    // *fOut << "def forward(self, " << fFullCount << subst(": int, inputs::Matrix{$0}, outputs::Matrix{$0}):", xfloat());
    *fOut << "@staticmethod";
    tab(n, *fOut);

	*fOut << "def tick(state: dict, inputs: jnp.array):";
    tab(n + 1, *fOut);
	//*fOut << "params, state = carry";

    //tab(n + 1, *fOut);
    //*fOut << "# todo: use jax.vmap to allow batch sizes greater than 1";
    //tab(n + 1, *fOut);
    //*fOut << "outputs = jax.zeros_like(inputs, requires_grad=True)";
    //tab(n + 1, *fOut);
    //*fOut << "count = inputs.shape[-1]";
    tab(n + 1, *fOut);
    gGlobal->gJAXVisitor->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gJAXVisitor);

    // 
    auto loop = fCurLoop->generateOneSample();
    loop->accept(gGlobal->gJAXVisitor);

    /*
    // TODO : atomic switch
    // Currently for soundfile management
    */
    generatePostComputeBlock(gGlobal->gJAXVisitor);

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "@nn.compact";
    tab(n, *fOut);
    *fOut << "def __call__(self, x, T: int) -> jnp.array:";
    tab(n + 1, *fOut);
    *fOut << "state = {}";
    tab(n + 1, *fOut);
    *fOut << "state = self.init_constants(state, self.sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "state = self.build_interface(state, T)";
    tab(n + 1, *fOut);
    //*fOut << "return vscan(self.tick, state, inputs)";
    //*fOut << "return jax.lax.scan(self.tick, state, inputs)";
    *fOut << "return jnp.transpose(jax.lax.scan(self.tick, state, jnp.transpose(x, axes=(1, 0)))[1], axes=(1,0))";
	tab(n, *fOut);
}

void JAXCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "def metadata(self):";
    
        // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "print(\"" << *(i.first) << "\", " << **(i.second.begin()) << ")";
        } else {
                // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
                // "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "print(\"" << *(i.first) << "\", " << **j << ")";
                } else {
                    tab(tabs + 1, *fOut);
                    *fOut << "print(\""
                    << "contributor"
                    << "\", " << **j << ")";
                }
            }
        }
    }
    
    tab(tabs, *fOut);
}

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void JAXCodeContainer::produceInfoFunctions(int tabs, const string& classname, const string& obj, bool ismethod,
                                         bool isvirtual, TextInstVisitor* producer)
{
    // Input/Output method
    producer->Tab(tabs);
    generateGetInputs("getNumInputs", obj, ismethod, isvirtual)->accept(producer);
    tab(tabs, *fOut);
    generateGetOutputs("getNumOutputs", obj, ismethod, isvirtual)->accept(producer);
}

BlockInst* JAXCodeContainer::inlineSubcontainersFunCalls(BlockInst* block)
{
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    block = DspRenamer().getCode(block);
    //dump2FIR(block);

    // Inline subcontainers 'instanceInit' and 'fill' function call
    for (const auto& it : fSubContainers) {
        // Build the function to be inlined (prototype and code)
        DeclareFunInst* inst_init_fun = it->generateInstanceInitFun("instanceInit" + it->getClassName(), "dsp", true, false);
        //dump2FIR(inst_init_fun);
        block = FunctionCallInliner(inst_init_fun).getCode(block);
        //dump2FIR(block);
    
        // Build the function to be inlined (prototype and code)
        DeclareFunInst* fill_fun = it->generateFillFun("fill" + it->getClassName(), "dsp", true, false);
        //dump2FIR(fill_fun);
        block = FunctionCallInliner(fill_fun).getCode(block);
        //dump2FIR(block);
    }
    // dump2FIR(block);
    
    // Rename all loop variables name to avoid name clash
    // LoopVariableRenamer loop_renamer;
    // block = loop_renamer.getCode(block);
    return block;
}

// Scalar
JAXScalarCodeContainer::JAXScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                   int sub_container_type)
    : JAXCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

// Vector
JAXVectorCodeContainer::JAXVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), JAXCodeContainer(name, numInputs, numOutputs, out)
{
}

// todo: this is not tested. see libcode.cpp
void JAXVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    gGlobal->gJAXVisitor->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(gGlobal->gJAXVisitor);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << "def __call__(self, inputs: jnp.array) -> jnp.array:";
    tab(n + 2, *fOut);
    gGlobal->gJAXVisitor->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gJAXVisitor);

    // Generates the DSP loop
    fDAGBlock->accept(gGlobal->gJAXVisitor);

    back(1, *fOut);
}
