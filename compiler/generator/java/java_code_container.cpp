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

map <string, bool> JAVAInstVisitor::gFunctionSymbolTable;
map <string, string> JAVAInstVisitor::gMathLibTable;

dsp_factory_base* JAVACodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* JAVACodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new JAVAScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* JAVACodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for Java\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for Java\n");
    }
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
        throw faustexception("ERROR : Vector mode not supported for Java\n");
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
        // fKlassName used in method naming for subclasses
        produceInfoFunctions(n+1, fKlassName, "dsp", true, false, &fCodeProducer);
    
        // TODO
        //generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);
        
        // Inits
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
            generateResetUserInterface(&fCodeProducer);
            generateClear(&fCodeProducer);
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
    tab(n, *fOut);
    *fOut << fKlassName << " new" <<  fKlassName << "() {"
                        << "return new "<< fKlassName << "()"
                        << "; }";
                        
    tab(n, *fOut);
    *fOut << "void delete" << fKlassName << "(" << fKlassName <<" dsp) {}";
    tab(n, *fOut);
}

void JAVACodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);
   
    tab(n, *fOut); *fOut << "public class " << fKlassName << " extends " << fSuperKlassName << " {";

        // Global declarations
        tab(n+1, *fOut);
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateGlobalDeclarations(&fCodeProducer);
      
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

        for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
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
        // No class name for main class
        produceInfoFunctions(n+1, "", "dsp", true, true, &fCodeProducer);
        
        // Inits
    
        // TODO
        /*
        generateStaticInitFun("classInit", false)->accept(&fCodeProducer);
        generateInstanceInitFun("instanceInit", true, true)->accept(&fCodeProducer);
        */
    
        tab(n+1, *fOut); *fOut << "public void classInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
   
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void instanceConstants(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void instanceResetUserInterface() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateResetUserInterface(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void instanceClear() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
        generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
   
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void init(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "public void instanceInit(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "instanceConstants(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceResetUserInterface();";
            tab(n+2, *fOut); *fOut << "instanceClear();";
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
