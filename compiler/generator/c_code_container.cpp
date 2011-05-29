/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "c_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "function_builder.hh"

using namespace std;

extern int gVectorLoopVariant;
extern bool gUIMacroSwitch;
extern bool gDSPStruct;
extern bool gOpenCLSwitch;
extern bool gCUDASwitch;
extern bool gOpenMPSwitch;
extern bool gSchedulerSwitch;
extern bool gVectorSwitch;

extern map<Tree, set<Tree> > gMetaDataSet;
map <string, int> CInstVisitor::gGlobalTable;

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CScalarCodeContainer("", 0, 1, fOut, sub_container_type, name);
}

CodeContainer* CCodeContainer::createContainer(int numInputs, int numOutputs, ostream* dst)
{
    gDSPStruct = true;
    CodeContainer* container;

    if (gOpenCLSwitch) {
        cerr << "ERROR : OpenCL not supported for C" << endl;
        exit(1);
    }
    if (gCUDASwitch) {
        cerr << "ERROR : CUDA not supported for C" << endl;
        exit(1);
    }

    if (gOpenMPSwitch) {
        container = new COpenMPCodeContainer("mydsp", numInputs, numOutputs, dst, "c_");
    } else if (gSchedulerSwitch) {
        container = new CWorkStealingCodeContainer("mydsp", numInputs, numOutputs, dst, "c_");
    } else if (gVectorSwitch) {
        container = new CVectorCodeContainer("mydsp", numInputs, numOutputs, dst, "c_");
    } else {
        container = new CScalarCodeContainer("mydsp", numInputs, numOutputs, dst, kInt, "c_");
    }

    return container;
}

void CCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "struct " << fPrefix << fStructName << " {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "};";

    // Memory methods
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "static " << fPrefix << "* " << " new" << fPrefix << "() { "
                        << "return (" << fPrefix << fStructName  << "*)malloc(sizeof(" << fPrefix << fStructName << "))"
                        << "; }";

    tab(n, *fOut); *fOut << "static void " << "delete" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "free(dsp)"
                        << "; }";

    // Input method
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "static int getNumInputs" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumInputs
                        << "; }";

    // Output method
    tab(n, *fOut); *fOut << "static int getNumOutputs" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumOutputs
                        << "; }";

    // Init
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "static void " << "instanceInit" << fPrefix << "(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateInit(&fCodeProducer);
    tab(n, *fOut); *fOut << "}";

    // Fill
    tab(n, *fOut);
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n, *fOut); *fOut << "static void " << "fill" << fPrefix << "(" << fPrefix << fStructName << subst("* dsp, int $0, int* output) {", counter);
    } else {
        tab(n, *fOut); *fOut << "static void " << "fill" << fPrefix << "(" << fPrefix << fStructName << subst("* dsp, int $0, $1* output) {", counter, ifloat());
    }
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "};\n" << endl;
}

void CCodeContainer::produceClass()
{
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    if (!fGeneratedSR)
        pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

     // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "struct " << fPrefix << fStructName << " {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "};";

    // Memory methods
    tab(n, *fOut);
    tab(n, *fOut); *fOut << fPrefix << fStructName << "* " << fPrefix << "newDsp() { "
                        << "return (" << fPrefix << fStructName  << "*)malloc(sizeof(" << fPrefix << fStructName << "))"
                        << "; }";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "static void destroyDsp(" << fPrefix << fStructName << "* dsp) {";
                    if (fDestroyInstructions->fCode.size() > 0) {
                        tab(n+1, *fOut);
                        fDestroyInstructions->accept(&fCodeProducer);
                    }
    tab(n, *fOut);  *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "deleteDsp(" << fPrefix << fStructName << "* dsp) { ";
        tab(n+1, *fOut); *fOut << "destroyDsp(dsp);";
        tab(n+1, *fOut); *fOut << "free(dsp);";
    tab(n, *fOut);  *fOut << "}";


    // Print metadata declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "metadata(Meta* m) { ";

    for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(n+1, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(n+1, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                    tab(n+1, *fOut); *fOut << "m->declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }

    tab(n, *fOut); *fOut << "}" << endl;

    // Get sample rate method
    tab(n, *fOut); *fOut << "int " << fPrefix << "getSampleRate(" << fPrefix << fStructName << "* dsp) { "
                        << "return dsp->fSamplingFreq"
                        << "; }";

    // Input method
    tab(n, *fOut); *fOut << "int " << fPrefix << "getNumInputs(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumInputs
                        << "; }";

    // Output method
    tab(n, *fOut); *fOut << "int " << fPrefix << "getNumOutputs(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumOutputs
                        << "; }";

    // Input Rates
    tab(n, *fOut); *fOut << "int " << fPrefix << "getInputRate(" << fPrefix << fStructName << "* dsp, int channel) { ";
        tab(n+1, *fOut); *fOut << "switch (channel) {";
            for (int i = 0; i != fNumInputs; ++i) {
                tab(n+2, *fOut); *fOut << "case " << i << ": return " << fInputRates[i] << ";";
            }
            tab(n+2, *fOut); *fOut << "default: -1;" << endl;
        tab(n+1, *fOut); *fOut << "}";
   tab(n, *fOut); *fOut << "}";

     // Output Rates
    tab(n, *fOut); *fOut << "int " << fPrefix << "getOutputRate(" << fPrefix << fStructName << "* dsp, int channel) { ";
        tab(n+1, *fOut); *fOut << "switch (channel) {";
            for (int i = 0; i != fNumOutputs; ++i) {
                tab(n+2, *fOut); *fOut << "case " << i << ": return " << fOutputRates[i] << ";";
            }
            tab(n+2, *fOut); *fOut << "default: -1;" << endl;
        tab(n+1, *fOut); *fOut << "}";
    tab(n, *fOut); *fOut << "}";

    // Inits
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "classInit(int samplingFreq) {";
        if (fStaticInitInstructions->fCode.size() > 0) {
            tab(n+1, *fOut);
            CInstVisitor codeproducer(fOut, "", "");
            codeproducer.Tab(n+1);
            fStaticInitInstructions->accept(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "instanceInit(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateInit(&fCodeProducer);
    tab(n, *fOut); *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "init(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut); *fOut << fPrefix << "classInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << fPrefix << "instanceInit(dsp, samplingFreq);";
    tab(n, *fOut); *fOut << "}";

    // User interface
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "buildUserInterface(" << fPrefix << fStructName << "* dsp, UIGlue* interface) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateUserInterface(&fCodeProducer);
    tab(n, *fOut); *fOut << "}";

    // Compute
    generateCompute(n);

    // Generate user interface macros if needed
	if (gUIMacroSwitch) {
		tab(n, *fOut); *fOut << "#ifdef FAUST_UIMACROS";
            tab(n+1, *fOut); *fOut << "#define FAUST_INPUTS " << fNumInputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_ACTIVES " << fNumActives;
            tab(n+1, *fOut); *fOut << "#define FAUST_PASSIVES " << fNumPassives;
			printlines(n+1, fUIMacro, *fOut);
		tab(n, *fOut); *fOut << "#endif";
        tab(n, *fOut);
	}
}

// Scalar
CScalarCodeContainer::CScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type, const string& prefix)
    :CCodeContainer(name, numInputs, numOutputs, out, prefix)
{
    fSubContainerType = sub_container_type;
}

CScalarCodeContainer::~CScalarCodeContainer()
{}

void CScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
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
CVectorCodeContainer::CVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :VectorCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

CVectorCodeContainer::~CVectorCodeContainer()
{}

void CVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    fDAGBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// OpenMP
COpenMPCodeContainer::COpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :OpenMPCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

void COpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    fGlobalLoopBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

COpenMPCodeContainer::~COpenMPCodeContainer()
{}

// Works stealing scheduler
CWorkStealingCodeContainer::CWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :WSSCodeContainer(numInputs, numOutputs, "dsp"), CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

CWorkStealingCodeContainer::~CWorkStealingCodeContainer()
{}

void CWorkStealingCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates "computeThread" code
    tab(n, *fOut); *fOut << "void computeThread(" << fPrefix << fStructName << "* dsp, int num_thread) {";
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generate it
    fThreadLoopBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    // Compute "compute" declaration

    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    tab(n, *fOut); *fOut << "void computeThreadExternal(void* dsp, int num_thread) {";
        tab(n+1, *fOut); *fOut << "computeThread((" << fPrefix << fStructName << "*)dsp, num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}
