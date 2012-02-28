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

#include "js_code_container.hh"
#include "Text.hh"
#include "floats.hh"

using namespace std;

extern bool gUIMacroSwitch;
extern int gVectorLoopVariant;
extern bool gVectorSwitch;
extern bool gOpenCLSwitch;
extern bool gCUDASwitch;
extern bool gOpenMPSwitch;
extern bool gSchedulerSwitch;
extern bool gVectorSwitch;
extern bool gFunTaskSwitch;
extern map<Tree, set<Tree> > gMetaDataSet;

CodeContainer* JAVAScriptCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAVAScriptScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* JAVAScriptCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gOpenCLSwitch) {
        cerr << "ERROR : OpenCL not supported for JavaScript" << endl;
        exit(1);
    }
    if (gCUDASwitch) {
        cerr << "ERROR : CUDA not supported for JavaScript" << endl;
        exit(1);
    }

    if (gOpenMPSwitch) {
        cerr << "ERROR : OpenMP not supported for JavaScript" << endl;
        exit(1);
    } else if (gSchedulerSwitch) {
        cerr << "ERROR : Scheduler mode not supported for JavaScript" << endl;
        exit(1);
    } else if (gVectorSwitch) {
        container = new JAVAScriptVectorCodeContainer(name, super, numInputs, numOutputs, dst);
    } else {
        container = new JAVAScriptScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
JAVAScriptScalarCodeContainer::JAVAScriptScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :JAVAScriptCodeContainer(name, super, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

JAVAScriptScalarCodeContainer::~JAVAScriptScalarCodeContainer()
{}

/*
void JAVAScriptCodeContainer::printIncludeFile(ostream& fout)
{
    set<string> S;
    set<string>::iterator f;

    collectIncludeFile(S);
    for (f = S.begin(); f != S.end(); f++) 	{
        fout << "#import " << *f << "\n";
    }
}
*/

void JAVAScriptCodeContainer::produceInternal()
{
    int n = 1;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    //generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "final class " << fKlassName << " {";

        tab(n+1, *fOut);

        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

        tab(n, *fOut);

         // Memory methods
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fKlassName << "[] " << "new" <<  fKlassName << "() { "
                            << "return (" << fKlassName << "[]) new "<< fKlassName << "()"
                            << "; }";

        tab(n+1, *fOut); *fOut << "void " << "delete(" << fKlassName << "[] dsp) { "
                              << "; }";

        // Input method
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public int getNumInputs() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "public int getNumOutputs() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void init(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        if (fSubContainerType == kInt) {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, int[] output) {", counter);
        } else {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, $1[] output) {", counter, ifloat());
        }
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        generateComputeBlock(&fCodeProducer);
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
        loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

    tab(n, *fOut); *fOut << "};\n" << endl;
}

void JAVAScriptCodeContainer::produceClass()
{
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    // Libraries
    printLibrary(*fOut);
    //printIncludeFile(*fOut);

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    //generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "public class " << fKlassName << " extends " << fSuperKlassName << " {";

        tab(n+1, *fOut);

        // Sub containers
        generateSubContainers();

        // Fields
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

        tab(n, *fOut); // *fOut << "  public:";

        // Print metadata declaration
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut   << "public void metadata(Meta m) { ";

        for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
            if (i->first != tree("author")) {
                tab(n+2, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
            } else {
                for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                    if (j == i->second.begin()) {
                        tab(n+2, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **j << ");" ;
                    } else {
                        tab(n+2, *fOut); *fOut << "m.declare(\"" << "contributor" << "\", " << **j << ");";
                    }
                }
            }
        }

        tab(n+1, *fOut); *fOut << "}" << endl;

        // Input method
        tab(n+1, *fOut); *fOut << "public int getNumInputs() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "public int getNumOutputs() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "static public void classInit(int samplingFreq) {";
            if (fStaticInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fStaticInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void instanceInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void init(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";

        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void buildUserInterface(UI ui_interface) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateUserInterface(&fCodeProducer);
            printlines(n+2, fUICode, *fOut);
        tab(n+1, *fOut); *fOut << "}";

        // Compute
        generateCompute(n);

        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(&fCodeProducer);

    tab(n, *fOut); *fOut << "};\n" << endl;

}

void JAVAScriptScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("public void compute(int $0, $1[][] inputs, $1[][] outputs) {", fFullCount,  ifloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Vector
JAVAScriptVectorCodeContainer::JAVAScriptVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), JAVAScriptCodeContainer(name, super, numInputs, numOutputs, out)
{}

JAVAScriptVectorCodeContainer::~JAVAScriptVectorCodeContainer()
{}

void JAVAScriptVectorCodeContainer::generateCompute(int n)
{
    // Compute
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1[][] inputs, $1[][] outputs) {", fFullCount, ifloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    fDAGBlock->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}
