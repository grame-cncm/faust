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

#include "linen_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 Linen backend implementation with Flax Linen (nn.Module) support:

 ### Core Architecture:
 - Generates a one-sample "tick" method as an instance method
 - Uses jax.lax.scan for efficient loop processing over audio blocks
 - Architecture files (minimal_linen.py, impulse_linen.py) provide the __call__ wrapper
 - Flax Linen modules handle parameter management via self.param() / self.variable()

 ### Key Design Decisions:
 - **Flax Linen Integration**: Uses nn.Module with @nn.compact
 - **Immutable Arrays**: JAX arrays require `.at[index].set(value)` instead of in-place updates
 - **All in state**: Both UI parameters and state variables stored in `state` dict (no params/state split)
 - **Cache Variables**: Soundfile cache variables (ending in "ca") are local vars, not state entries
 - **NumPy Initialization**: Use mutable NumPy arrays during setup, convert to JAX in tick method
*/

dsp_factory_base* LinenCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""),
        "");
}

LinenCodeContainer::LinenCodeContainer(const std::string& name, int numInputs, int numOutputs,
                                       std::ostream* out)
{
    // Mandatory
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut       = out;

    // Allocate one static visitor to be shared by main module and sub containers
    if (!gGlobal->gLinenVisitor) {
        gGlobal->gLinenVisitor = new LinenInstVisitor(out, name);
    }
}

CodeContainer* LinenCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new LinenScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* LinenCodeContainer::createContainer(const string& name, int numInputs, int numOutputs,
                                                   ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Linen\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Linen\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Linen\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Linen\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector not supported for Linen\n");
    } else {
        container = new LinenScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void LinenCodeContainer::produceClass()
{
    int n = 0;

    // Print header
    *fOut << "\"\"\"" << endl << "Code generated with Faust version " << FAUSTVERSION << endl;
    *fOut << "Compilation options: ";
    stringstream stream;
    gGlobal->printCompilationOptions(stream);
    *fOut << stream.str();
    tab(n, *fOut);
    *fOut << "\"\"\"";
    tab(n, *fOut);

    if (gGlobal->gFloatSize == 2) {
        tab(n, *fOut);
        *fOut << "# enable double precision: "
                 "https://jax.readthedocs.io/en/latest/notebooks/"
                 "Common_Gotchas_in_JAX.html#double-64bit-precision";
        tab(n, *fOut);
        *fOut << "import jax";
        tab(n, *fOut);
        *fOut << "jax.config.update(\"jax_enable_x64\", True)";
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

    // Find the small copy-delay arrays that can live as scalar carry entries.
    // The analysis must cover exactly the blocks emitted below, including the
    // one-sample loop body, which is therefore generated once here and reused
    // by generateCompute().
    fOneSampleBlock                = fCurLoop->generateOneSample();
    BlockInst* init_inlined        = inlineSubcontainersFunCalls(fInitInstructions);
    BlockInst* static_init_inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
    std::map<std::string, int> scalarized = nnxComputeScalarizedArrays(
        {fGlobalDeclarationInstructions, fDeclarationInstructions, init_inlined,
         static_init_inlined, fClearInstructions, fComputeBlockInstructions,
         fPostComputeBlockInstructions, fOneSampleBlock});
    gGlobal->gLinenVisitor->setScalarizedArrays(scalarized);

    // C's remainder() has no jax.numpy equivalent: jnp.remainder is floored
    // modulo (sign of the divisor), whereas C rounds the quotient to nearest
    // (ties to even). Emit a custom implementation rather than jnp.remainder.
    tab(n, *fOut);
    *fOut << "def remainder(x, y):";
    tab(n + 1, *fOut);
    *fOut << "\"\"\"C++ std::remainder (round-to-nearest quotient); NOT jnp.remainder.\"\"\"";
    tab(n + 1, *fOut);
    *fOut << "quo = jnp.round(x/y)";
    tab(n + 1, *fOut);
    *fOut << "return x - quo * y";
    tab(n, *fOut);
    tab(n, *fOut);

    // Functions
    tab(n, *fOut);
    gGlobal->gLinenVisitor->Tab(n);

    *fOut << "class " << fKlassName << "(nn.Module):";

    // Class docstring built from the UI instructions
    {
        NNXUIDocVisitor doc;
        generateUserInterface(&doc);
        nnxEmitClassDocstring(fOut, n, fKlassName, "Flax Linen", fNumInputs, fNumOutputs, doc);
    }
    tab(n + 1, *fOut);
    gGlobal->gLinenVisitor->Tab(n);

    // Flax Linen modules are dataclasses: configure them via dataclass fields and
    // a setup() method, rather than by overriding __init__ (which the dataclass
    // machinery owns). See
    // https://flax-linen.readthedocs.io/en/latest/api_reference/flax.linen/module.html
    tab(n + 1, *fOut);
    *fOut << "sample_rate: int";
    tab(n + 1, *fOut);
    *fOut << "faust_float: Any = FAUSTFLOAT";
    tab(n + 1, *fOut);
    *fOut << "soundfile_dirs: Optional[List[str]] = None";
    tab(n + 1, *fOut);
    *fOut << "use_magic_clamp: bool = True";
    tab(n + 1, *fOut);
    *fOut << "deterministic: bool = False";
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "# Compiled-in constants (class attributes, not dataclass fields).";
    tab(n + 1, *fOut);
    *fOut << "num_inputs = " << fNumInputs;
    tab(n + 1, *fOut);
    *fOut << "num_outputs = " << fNumOutputs;
    tab(n + 1, *fOut);
    *fOut << "# Full Faust JSON metadata (parsed once at import time)";
    {
        string json;
        if (gGlobal->gFloatSize == 1) {
            json = generateJSON<float>();
        } else {
            json = generateJSON<double>();
        }
        tab(n + 1, *fOut);
        *fOut << "json_metadata = json.loads(\"\"\"" << flattenJSONforPython(json) << "\"\"\")";
    }
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    // setup() replaces __init__ for Flax Linen dataclass modules: it registers
    // the learnable parameters (via self.param) and builds the UI metadata.
    *fOut << "def setup(self):";
    tab(n + 2, *fOut);
    *fOut << "self.rng_collection = \"default\"";
    tab(n + 2, *fOut);
    *fOut << "# Use object.__setattr__ for the mutable bookkeeping dicts: Flax Linen";
    tab(n + 2, *fOut);
    *fOut << "# converts dicts assigned via self.x = {} into immutable FrozenDicts.";
    tab(n + 2, *fOut);
    *fOut << "object.__setattr__(self, \"_parameter_metadata\", {})";
    tab(n + 2, *fOut);
    *fOut << "# Build UI interface (registers parameters via self.param)";
    tab(n + 2, *fOut);
    *fOut << "ui_path = []";
    tab(n + 2, *fOut);
    *fOut << "unnorm_funcs = {}";
    tab(n + 2, *fOut);
    *fOut << "self.build_interface(ui_path, unnorm_funcs)";
    tab(n + 2, *fOut);
    *fOut << "object.__setattr__(self, \"_unnorm_funcs\", unnorm_funcs)";
    tab(n + 2, *fOut);
    *fOut << "self._finalize_interface()";
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    *fOut << "def _initialize_carry(self):";
    {
        tab(n + 2, *fOut);
        *fOut << "state = {}";
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
        *fOut << "# global declarations:";
        LinenInitFieldsVisitor initializer(fOut, n + 2);
        initializer.setScalarizedArrays(scalarized);
        generateDeclarations(&initializer);
        // Generate global variables initialisation
        for (const auto& it : fGlobalDeclarationInstructions->fCode) {
            if (dynamic_cast<DeclareVarInst*>(it)) {
                it->accept(&initializer);
            }
        }
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
        *fOut << "# init constants:";
        tab(n + 2, *fOut);
        gGlobal->gLinenVisitor->Tab(n + 2);
        init_inlined->accept(gGlobal->gLinenVisitor);
        tab(n + 2, *fOut);
        *fOut << "# inline subcontainers:";
        tab(n + 2, *fOut);
        gGlobal->gLinenVisitor->Tab(n + 2);
        static_init_inlined->accept(gGlobal->gLinenVisitor);
        tab(n + 2, *fOut);
        *fOut << "# instance clear:";
        tab(n + 2, *fOut);
        generateClear(gGlobal->gLinenVisitor);
        tab(n + 2, *fOut);

        tab(n + 2, *fOut);
        *fOut << "return state";
        tab(n + 1, *fOut);
    }
    back(1, *fOut);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "def build_interface(self, ui_path: List[str], unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:";
    tab(n + 2, *fOut);
    gGlobal->gLinenVisitor->Tab(n + 2);
    generateUserInterface(gGlobal->gLinenVisitor);
    tab(n + 2, *fOut);
    *fOut << "return";

    // Compute
    tab(n + 1, *fOut);
    generateCompute(n + 1);

    // Whether tick() draws random numbers (random_* foreign functions). The
    // architecture skips per-sample RNG key threading when this is False.
    // Emitted after tick() because the flag is discovered while generating it;
    // Python class attributes may be defined anywhere in the class body.
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "# Whether tick() draws random numbers (random_* foreign functions)";
    tab(n + 1, *fOut);
    *fOut << "is_stochastic = " << (gGlobal->gLinenVisitor->fUsesRandom ? "True" : "False");
    tab(n, *fOut);
}

void LinenCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "def tick(self, state: dict, inputs: jnp.ndarray, rng: jax.Array = None):";
    tab(n + 1, *fOut);

    // Generate RNG helper function for random calls
    tab(n + 1, *fOut);
    *fOut << "# Helper function to get RNG keys";
    tab(n + 1, *fOut);
    *fOut << "rngs = nnx.Rngs(rng) if rng is not None else nnx.data(None)";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    gGlobal->gLinenVisitor->Tab(n + 1);

    // Generates local variables declaration and setup
    gGlobal->gLinenVisitor->fUseNumpy = false;
    generateComputeBlock(gGlobal->gLinenVisitor);

    // Reuse the block generated in produceClass so the scalarization analysis
    // and the emitted tick see the same instructions
    faustassert(fOneSampleBlock);
    fOneSampleBlock->accept(gGlobal->gLinenVisitor);

    generatePostComputeBlock(gGlobal->gLinenVisitor);
    gGlobal->gLinenVisitor->fUseNumpy = true;
}

void LinenCodeContainer::generateSR()
{
    if (!fGeneratedSR) {
        pushDeclare(IB::genDecStructVar("fSampleRate", IB::genInt32Typed()));
    }
    pushPreInitMethod(
        IB::genStoreStructVar("fSampleRate", IB::genLoadFunArgsVar("self.sample_rate")));
}

// Scalar
LinenScalarCodeContainer::LinenScalarCodeContainer(const string& name, int numInputs, int numOutputs,
                                                   std::ostream* out, int sub_container_type)
    : LinenCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}
