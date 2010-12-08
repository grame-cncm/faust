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

extern map<Tree, set<Tree> > gMetaDataSet;
map <string, int> CInstVisitor::gGlobalTable;

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CScalarCodeContainer("", 0, 1, fOut, sub_container_type, name);
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
    tab(n, *fOut); *fOut << fPrefix << "* " << " new" << fPrefix << "() { "
                        << "return (" << fPrefix << fStructName  << "*)malloc(sizeof(" << fPrefix << fStructName << "))"
                        << "; }";

    tab(n, *fOut); *fOut << "void " << "delete" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "free(dsp)"
                        << "; }";

    // Input method
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "int getNumInputs" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumInputs
                        << "; }";

    // Output method
    tab(n, *fOut); *fOut << "int getNumOutputs" << fPrefix << "(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumOutputs
                        << "; }";

    // Init
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << "instanceInit" << fPrefix << "(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        if (fInitInstructions->fCode.size() > 0) {
            tab(n+1, *fOut);
            fCodeProducer.Tab(n+1);
            generateInit(&fCodeProducer);
        }
    tab(n, *fOut); *fOut << "}";

    // Fill
    tab(n, *fOut);
    if (fSubContainerType == kInt) {
        tab(n, *fOut); *fOut << "void " << "fill" << fPrefix << "(" << fPrefix << fStructName << "* dsp, int count, int* output) {";
    } else {
        tab(n, *fOut); *fOut << "void " << "fill" << fPrefix << "(" << fPrefix << fStructName << subst("* dsp, int count, $0* output) {", ifloat());
    }
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop();
    loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "};\n" << endl;
}

void CCodeContainer::produceClass()
{
    int n = 0;

    // Generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushGlobalDeclare(InstBuilder::genDecGlobalVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    pushFrontInitMethod(InstBuilder::genStoreGlobalVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

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

    // Input method
    tab(n, *fOut); *fOut << "int " << fPrefix << "getNumInputs(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumInputs
                        << "; }";

    // Output method
    tab(n, *fOut); *fOut << "int " << fPrefix << "getNumOutputs(" << fPrefix << fStructName << "* dsp) { "
                        << "return " << fNumOutputs
                        << "; }";

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
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int count, $0** inputs, $0** outputs) {", xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop();
    loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// Vector
CVectorCodeContainer::CVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

CVectorCodeContainer::~CVectorCodeContainer()
{}

void CVectorCodeContainer::generateCompute(int n)
{
    // Prepare global loop
    StatementInst* block = NULL;
    if (gVectorLoopVariant == 0) {
        block = generateDAGLoopVariant0();
    } else {
        block = generateDAGLoopVariant1();
    }

    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    assert(block);
    block->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// OpenMP
COpenMPCodeContainer::COpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :OpenMPCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

void COpenMPCodeContainer::generateCompute(int n)
{
    // Prepare global loop
    StatementInst* block = generateDAGLoopOMP();

    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Transform stack array variables in struct variables
    //MoveStackArray2Struct();

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    assert(block);
    block->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

COpenMPCodeContainer::~COpenMPCodeContainer()
{}

// Works stealing scheduler
CWorkStealingCodeContainer::CWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, const string& prefix)
    :WSSCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out, prefix)
{}

CWorkStealingCodeContainer::~CWorkStealingCodeContainer()
{}

void CWorkStealingCodeContainer::produceClass()
{
    // Transform some stack variables in struct variables
    MoveStack2Struct();

    // Specific init code
    generateDAGLoopWSSAux3();

    // Inherited method
    CCodeContainer::produceClass();
}

void CWorkStealingCodeContainer::generateCompute(int n)
{
    lclgraph dag;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag);

     // Prepare global loop
    StatementInst* block = generateDAGLoopWSS(dag);

    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates "computeThread" code
    tab(n, *fOut); *fOut << "void computeThread(" << fPrefix << fStructName << "* dsp, int num_thread) {";
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    // Generate it
    block->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    // Compute "compute" declaration
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);

    generateDAGLoopWSSAux2(true);

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    tab(n, *fOut); *fOut << "void computeThreadExternal(void* dsp, int num_thread) {";
        tab(n+1, *fOut); *fOut << "computeThread((" << fPrefix << fStructName << "*)dsp, num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}
