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
 JAX backend and module description:

 - Whereas a normal code container would generate a "compute" method, we generate
   a one-sample loop "tick" method. Our hard-coded "compute" method __call__ is implemented
   in an architecture file. It uses JAX's scan function in conjunction with the generated tick function.
 - Inside "__call__" and before using "scan", we setup the arrays, soundfiles, user interface parameters,
   and other state variables.
 - One tricky part of JAX is modifying arrays in-place:
   https://jax.readthedocs.io/en/latest/_autosummary/jax.numpy.ndarray.at.html
   Whereas C++ would look like
   `fRec1[0] = fTemp0`
   in JAX we have to do
   `state["fRec1"] = state["fRec1"].at[0].set(fTemp0)`
   Also, this at-and-set operation is slow, so we only use it inside the tick method.
   This is why in all other places (like initializing sound files which are arrays),
   we use numpy arrays instead of jnp arrays. It's best to just look at the generated code and notice
   how the jnp prefix is used differently than the np prefix.
 - In order to simplify global array typing, subcontainers are actually merged in the main DSP structure:
    - so 'mergeSubContainers' is used
    - global variables are added in the DSP structure
    - the JAXInitFieldsVisitor class does initialisation for waveforms. This makes it easy to use numpy
      instead of jax when initializing arrays (good for speed). We also use fUseNumpy in this decision making.
      We convert the numpy arrays to jax numpy before they're used in the tick method.
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
    
    // Allocate one static visitor to be shared by main module and sub containers
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
        throw faustexception("ERROR : Vector not supported for JAX\n");
    } else {
        container = new JAXScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

inline string flattenJSONforPython(const string& src)
{
    string dst;
    for (size_t i = 0; i < src.size(); i++) {
        switch (src[i]) {
            case '"':
                dst += "\\\"";
                break;
            case '\\':
                dst += "/";
                break;
            case '\'':
                dst += "'";
                break;
            default:
                dst += src[i];
                break;
        }
    }
    return dst;
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

    if (gGlobal->gFloatSize == 2) {
        tab(n, *fOut);
        *fOut << "# enable double precision: https://jax.readthedocs.io/en/latest/notebooks/Common_Gotchas_in_JAX.html#double-64bit-precision";
        tab(n, *fOut);
        *fOut << "from jax.config import config";
        tab(n, *fOut);
        *fOut << "config.update(\"jax_enable_x64\", True)";
        tab(n, *fOut);
        *fOut << "FAUSTFLOAT = jnp.float64";
        tab(n, *fOut);
    } else {
        tab(n, *fOut);
        *fOut << "# enable single precision";
        tab(n, *fOut);
        *fOut << "FAUSTFLOAT = jnp.float32";
        tab(n, *fOut);
    }

    // Merge sub containers
    mergeSubContainers();

    // Missing math function
    tab(n, *fOut);
    *fOut << "def remainder(x, y):";
    tab(n + 1, *fOut);
    *fOut << "\"\"\"C++ std::remainder implemented with jax numpy\"\"\"";
    tab(n + 1, *fOut);
    *fOut << "quo = jnp.round(x/y)";
    tab(n + 1, *fOut);
    *fOut << "return x - quo * y";
    tab(n + 1, *fOut);

    // Functions
    tab(n, *fOut);
    gGlobal->gJAXVisitor->Tab(n);
 
    *fOut << "class " << fKlassName << "(nn.Module):";
    tab(n + 1, *fOut);

    // Fields
    gGlobal->gJAXVisitor->Tab(n + 1);

    tab(n + 1, *fOut);
    *fOut << "sample_rate: int";
    tab(n + 1, *fOut);
    *fOut << "soundfile_dirs: list[str] = dataclasses.field(default_factory=list)";

    tab(n + 1, *fOut);
    gGlobal->gJAXVisitor->Tab(n);

    tab(n + 1, *fOut);
    produceInfoFunctions(n + 1, "", "self", false, FunTyped::kDefault, gGlobal->gJAXVisitor);
    
    *fOut << "def initialize(self, x, T):";
    {
        tab(n + 2, *fOut);
        *fOut << "state = {}";
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
        *fOut << "# global declarations:";
        JAXInitFieldsVisitor initializer(fOut, n + 2);
        generateDeclarations(&initializer);
        // Generate global variables initialisation
        for (const auto& it : fGlobalDeclarationInstructions->fCode) {
            if (dynamic_cast<DeclareVarInst*>(it)) {
                it->accept(&initializer);
            }
        }
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
        *fOut << "# inline subcontainers:";
        tab(n + 2, *fOut);
        gGlobal->gJAXVisitor->Tab(n + 2);
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gJAXVisitor);
        tab(n + 2, *fOut);
        *fOut << "# init constants:";
        tab(n + 2, *fOut);
        gGlobal->gJAXVisitor->Tab(n + 2);
        inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gJAXVisitor);
        tab(n + 2, *fOut);
        *fOut << "# instance clear:";
        tab(n + 2, *fOut);
        generateClear(gGlobal->gJAXVisitor);
        tab(n + 2, *fOut);
        *fOut << "return state";
        tab(n + 1, *fOut);
    }
    back(1, *fOut);
    
    // JSON generation
    tab(n+1, *fOut);
    *fOut << "def getJSON(self):";
    {
        string json;
        if (gGlobal->gFloatSize == 1) {
            json = generateJSON<float>();
        } else {
            json = generateJSON<double>();
        }
        tab(n + 2, *fOut);
        *fOut << "json_str = \"\"\"" << flattenJSONforPython(json) << "\"\"\"";
        tab(n + 2, *fOut);
        *fOut << "return json.loads(json_str)";
        tab(n + 1, *fOut);
    }

    // User interface
    tab(n + 1, *fOut);
    *fOut << "def build_interface(self, state, x, T: int):";
    tab(n + 2, *fOut);
    *fOut << "ui_path = []";
    tab(n + 2, *fOut);
    gGlobal->gJAXVisitor->Tab(n + 2);
    generateUserInterface(gGlobal->gJAXVisitor);
    tab(n + 2, *fOut);
    *fOut << "return state";
    
    // Compute
    tab(n + 1, *fOut);
    generateCompute(n+1);
    tab(n, *fOut);
}

void JAXCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "@staticmethod";
    tab(n, *fOut);
    *fOut << "def tick(state: dict, inputs: jnp.array):";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    gGlobal->gJAXVisitor->Tab(n + 1);

    // Generates local variables declaration and setup
    gGlobal->gJAXVisitor->fUseNumpy = false;
    generateComputeBlock(gGlobal->gJAXVisitor);

    auto loop = fCurLoop->generateOneSample();
    loop->accept(gGlobal->gJAXVisitor);

    generatePostComputeBlock(gGlobal->gJAXVisitor);
    gGlobal->gJAXVisitor->fUseNumpy = true;
}

void JAXCodeContainer::generateSR()
{
    if (!fGeneratedSR) {
        pushDeclare(InstBuilder::genDecStructVar("fSampleRate", InstBuilder::genInt32Typed()));
    }
    pushPreInitMethod(
        InstBuilder::genStoreStructVar("fSampleRate", InstBuilder::genLoadFunArgsVar("self.sample_rate")));
}

// Scalar
JAXScalarCodeContainer::JAXScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                                   int sub_container_type)
    : JAXCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}
