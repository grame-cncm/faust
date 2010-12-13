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

#include "java_code_container.hh"
#include "Text.hh"
#include "floats.hh"

using namespace std;

extern bool gUIMacroSwitch;
extern int gVectorLoopVariant;

extern map<Tree, set<Tree> > gMetaDataSet;

// Scalar
JAVAScalarCodeContainer::JAVAScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :JAVACodeContainer(name, super, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

JAVAScalarCodeContainer::~JAVAScalarCodeContainer()
{}

CodeContainer* JAVACodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAVAScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

void JAVACodeContainer::printIncludeFile(ostream& fout)
{
    set<string> S;
    set<string>::iterator f;

    collectIncludeFile(S);
    for (f = S.begin(); f != S.end(); f++) 	{
        fout << "#import " << *f << "\n";
    }
}

void JAVACodeContainer::produceInternal()
{
    int n = 1;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "final class " << fKlassName << " {";

        tab(n+1, *fOut);

        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "  public:";

         // Memory methods
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fKlassName << "* " << "new" <<  fKlassName << "() { "
                            << "return (" << fKlassName << "*) new "<< fKlassName << "()"
                            << "; }";

        tab(n+1, *fOut); *fOut << "void " << "delete(" << fKlassName << "* dsp) { "
                              << "; }";

        // Input method
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "int getNumInputs() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "int getNumOutputs() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void init(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        if (fSubContainerType == kInt) {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, int* output) {", counter);
        } else {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, $1* output) {", counter, ifloat());
        }
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        generateComputeBlock(&fCodeProducer);
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
        loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

    tab(n, *fOut); *fOut << "};\n" << endl;
}

void JAVACodeContainer::produceClass()
{
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    pushFrontInitMethod(InstBuilder::genStoreGlobalVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "final class " << fKlassName << " extends " << fSuperKlassName << " {";

        tab(n+1, *fOut);

        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut);

        // Sub containers
        generateSubContainers();

        // Fields
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "  public:";

        // Print metadata declaration
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut   << "void metadata(Meta* m) { ";

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
        tab(n+1, *fOut); *fOut << "int getNumInputs() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "int getNumOutputs() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            if (fStaticInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fStaticInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void instanceInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void init(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";

        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void buildUserInterface(UI* interface) {";
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

    // Generate user interface macros if needed
	if (gUIMacroSwitch) {
		tab(n, *fOut); *fOut << "#ifdef FAUST_UIMACROS";
            tab(n+1, *fOut); *fOut << "#define FAUST_INPUTS " << fNumInputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_ACTIVES " << fNumActives;
            tab(n+1, *fOut); *fOut << "#define FAUST_PASSIVES " << fNumPassives;
			printlines(n+1, fUIMacro, *fOut);
		tab(n, *fOut); *fOut << "#endif";
	}
}

void JAVAScalarCodeContainer::generateCompute(int n)
{
    string counter = "count";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("void compute(int $0, $1** inputs, $1** outputs) {", counter,  xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Vector
JAVAVectorCodeContainer::JAVAVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), JAVACodeContainer(name, super, numInputs, numOutputs, out)
{}

JAVAVectorCodeContainer::~JAVAVectorCodeContainer()
{}

void JAVAVectorCodeContainer::generateCompute(int n)
{
    // Compute
    string counter = "fullcount";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", counter, xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate it
    fDAGBlock->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// OpenMP
JAVAOpenMPCodeContainer::JAVAOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :OpenMPCodeContainer( numInputs, numOutputs), JAVACodeContainer(name, super, numInputs, numOutputs, out)
{}

JAVAOpenMPCodeContainer::~JAVAOpenMPCodeContainer()
{}

// Works stealing scheduler
JAVAWorkStealingCodeContainer::JAVAWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :JAVACodeContainer(name, super, numInputs, numOutputs, out)
{}

JAVAWorkStealingCodeContainer::~JAVAWorkStealingCodeContainer()
{}

