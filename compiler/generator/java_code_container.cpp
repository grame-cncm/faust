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

#include "java_code_container.hh"
#include "exception.hh"
#include "Text.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

CodeContainer* JAVACodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAVAScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* JAVACodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Java\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Java\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Java\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Java\n");
    } else if (gGlobal->gVectorSwitch) {
        //container = new JAVAVectorCodeContainer(name, super, numInputs, numOutputs, dst);
        throw faustexception("Vector mode not supported for Java\n");
    } else {
        container = new JAVAScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
JAVAScalarCodeContainer::JAVAScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :JAVACodeContainer(name, super, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

JAVAScalarCodeContainer::~JAVAScalarCodeContainer()
{}

void JAVACodeContainer::produceInternal()
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

        tab(n+1, *fOut);
        tab(n+1, *fOut);
        produceInfoFunctions(n+1, fKlassName, false);
        
        // Inits
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        // Fill
        string counter = "count";
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

    tab(n, *fOut); *fOut << "};" << endl;
    
     // Memory methods (as globals)
    tab(n, *fOut); *fOut << fKlassName << " new" <<  fKlassName << "() { "
                        << "return new "<< fKlassName << "()"
                        << "; }";
    tab(n, *fOut);
}

void JAVACodeContainer::produceClass()
{
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    // Libraries
    printLibrary(*fOut);
   
    tab(n, *fOut); *fOut << "public class " << fKlassName << " extends " << fSuperKlassName << " {";

        tab(n+1, *fOut);
        
        // Global declarations
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateGlobalDeclarations(&fCodeProducer);
        tab(n+1, *fOut);
        
        // Generate polymorphic cast
        *fOut << "private final float castFloat(float val) { return val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float castFloat(double val) { return (float)val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float castFloat(int val) { return (float)val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float castFloat(boolean val) { return (float)((val)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int castInt(double val) { return (int)val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int castInt(float val) { return (int)val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int castInt(int val) { return val; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int castInt(boolean val) { return (val) ? 1 : 0; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final boolean castBoolean(int val) { return (val == 0) ? true : false; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final boolean castBoolean(float val) { return (val == 0.f) ? true : false; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final boolean castBoolean(double val) { return (val == 0) ? true : false; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final boolean castBoolean(boolean val) { return val; }" << endl;
        
        // Generate polymorphic arithemic operations
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(int a, int b) { return a + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(int a, float b) { return (float)a + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(float a, int b) { return a + (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(float a, float b) { return a + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(int a, boolean b) { return a + ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(boolean a, int b) { return ((a)?1:0) + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(boolean a, boolean b) { return ((a)?1:0) + ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(float a, boolean b) { return a + ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(boolean a, float b) { return ((a)?1.f:0.f) + b; }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_minus(int a, int b) { return a - b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_minus(int a, float b) { return (float)a - b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_minus(float a, int b) { return a - (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_minus(float a, float b) { return a - b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_minus(int a, boolean b) { return a - ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_minus(boolean a, int b) { return ((a)?1:0) - b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_minus(boolean a, boolean b) { return ((a)?1:0) - ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_minus(float a, boolean b) { return a - ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_minus(boolean a, float b) { return ((a)?1.f:0.f) - b; }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_mult(int a, int b) { return a * b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_mult(int a, float b) { return (float)a * b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_mult(float a, int b) { return a * (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_mult(float a, float b) { return a * b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_mult(int a, boolean b) { return a * ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_mult(boolean a, int b) { return ((a)?1:0) * b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_mult(boolean a, boolean b) { return ((a)?1:0) * ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_mult(float a, boolean b) { return a * ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_mult(boolean a, float b) { return ((a)?1.f:0.f) * b; }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_div(int a, int b) { return a / b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_div(int a, float b) { return (float)a / b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_div(float a, int b) { return a / (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_div(float a, float b) { return a / b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_div(int a, boolean b) { return a / ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_div(boolean a, int b) { return ((a)?1:0) / b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_div(boolean a, boolean b) { return ((a)?1:0) / ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_div(float a, boolean b) { return a / ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_div(boolean a, float b) { return ((a)?1.f:0.f) / b; }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_rem(int a, int b) { return a % b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_rem(int a, float b) { return (float)a % b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_rem(float a, int b) { return a % (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_rem(float a, float b) { return a % b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_rem(int a, boolean b) { return a % ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_rem(boolean a, int b) { return ((a)?1:0) % b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_rem(boolean a, boolean b) { return ((a)?1:0) % ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_rem(float a, boolean b) { return a % ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_rem(boolean a, float b) { return ((a)?1.f:0.f) % b; }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_and(int a, int b) { return a & b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_and(int a, boolean b) { return a & ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_and(boolean a, int b) { return ((a)?1:0) & b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_and(boolean a, boolean b) { return ((a)?1:0) & ((b)?1:0); }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_or(int a, int b) { return a | b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_or(int a, boolean b) { return a | ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_or(boolean a, int b) { return ((a)?1:0) | b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_or(boolean a, boolean b) { return ((a)?1:0) | ((b)?1:0); }" << endl;
        
        tab(n+1, *fOut);
        *fOut << "private final int java_xor(int a, int b) { return a ^ b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_xor(int a, boolean b) { return a ^ ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_xor(boolean a, int b) { return ((a)?1:0) ^ b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_xor(boolean a, boolean b) { return ((a)?1:0) ^ ((b)?1:0); }" << endl;
        
        /*
        tab(n+1, *fOut);
        *fOut << "private final int java_<<<(int a, int b) { return a << b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_<<<(int a, float b) { return (float)a << b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_<<<(float a, int b) { return a << (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_<<<(int a, boolean b) { return a << ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_<<<(boolean a, int b) { return ((a)?1:0) / b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_<<<(float a, boolean b) { return a +/ ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_<<<(boolean a, float b) { return ((a)?1.f:0.f) / b; }" << endl;
       
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(int a, int b) { return a + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(int a, float b) { return (float)a + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(float a, int b) { return a + (float)b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(int a, boolean b) { return a + ((b)?1:0); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final int java_plus(boolean a, int b) { return ((a)?1:0) + b; }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(float a, boolean b) { return a + ((b)?1.f:0.f); }" << endl;
        tab(n+1, *fOut);
        *fOut << "private final float java_plus(boolean a, float b) { return ((a)?1.f:0.f) + b; }" << endl;
        */

       
        // Sub containers
        generateSubContainers();

        // Fields
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
        
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "void allocate() {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                generateAllocate(&fCodeProducer);
            tab(n+1, *fOut);  *fOut << "}";
            tab(n+1, *fOut);
        }

        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "void destroy() {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                generateDestroy(&fCodeProducer);
            tab(n+1, *fOut);  *fOut << "}";
            tab(n+1, *fOut);
        }

        // Print metadata declaration
        tab(n+1, *fOut); *fOut   << "public void metadata(Meta m) { ";

        for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
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

        tab(n+1, *fOut);
        produceInfoFunctions(n+1, fKlassName, true);
        
        // Inits
        tab(n+1, *fOut); *fOut << "public void classInit(int samplingFreq) {";
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

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void JAVACodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{
    // Input/Output method
    fCodeProducer.Tab(tabs);
    generateGetInputs(subst("$0::getNumInputs", classname), true, isvirtual)->accept(&fCodeProducer);
    generateGetOutputs(subst("$0::getNumOutputs", classname), true,  isvirtual)->accept(&fCodeProducer);

    // Input Rates
    fCodeProducer.Tab(tabs);
    generateGetInputRate(subst("$0::getInputRate", classname), true,  isvirtual)->accept(&fCodeProducer);

    // Output Rates
    fCodeProducer.Tab(tabs);
    generateGetOutputRate(subst("$0::getOutputRate", classname), true,  isvirtual)->accept(&fCodeProducer);
}

void JAVAScalarCodeContainer::generateCompute(int n)
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
JAVAVectorCodeContainer::JAVAVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), JAVACodeContainer(name, super, numInputs, numOutputs, out)
{}

JAVAVectorCodeContainer::~JAVAVectorCodeContainer()
{}

void JAVAVectorCodeContainer::generateCompute(int n)
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

