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

#include "c_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "fir_function_builder.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

map <string, bool> CInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* CCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;
    
    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for C\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for C\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for C\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        container = new COpenMPCodeContainer(name, numInputs, numOutputs, dst);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new CWorkStealingCodeContainer(name, numInputs, numOutputs, dst);
    } else if (gGlobal->gVectorSwitch) {
        container = new CVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new CScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
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
  
    tab(n, *fOut); *fOut << "typedef struct {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "} "<<  fKlassName << ";";

    if (!gGlobal->gLightMode) {
        // Memory methods
        tab(n, *fOut);
        tab(n, *fOut); *fOut << "static " << fKlassName << "* new" << fKlassName << "() {"
                            << " return (" << fKlassName  << "*)malloc(sizeof(" << fKlassName << ")); }";

        tab(n, *fOut); *fOut << "static void delete" << fKlassName << "(" << fKlassName << "* dsp) { free(dsp); }";

        tab(n, *fOut);
        tab(n, *fOut);
    }
    produceInfoFunctions(n, fKlassName, "dsp", false, false, &fCodeProducer);
        
    // Init
    // TODO
    //generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&fCodeProducer);
    
    tab(n, *fOut); *fOut << "static void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateInit(&fCodeProducer);
        generateResetUserInterface(&fCodeProducer);
        generateClear(&fCodeProducer);
    tab(n, *fOut); *fOut << "}";
 
    // Fill
    tab(n, *fOut);
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n, *fOut); *fOut << "static void fill" << fKlassName << "(" << fKlassName << subst("* dsp, int $0, int* output) {", counter);
    } else {
        tab(n, *fOut); *fOut << "static void fill" << fKlassName << "("  << fKlassName << subst("* dsp, int $0, $1* output) {", counter, ifloat());
    }
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "};" << endl;
}

void CCodeContainer::produceClass()
{
    int n = 0;
 
    tab(n, *fOut); 
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "extern \"C\" {" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut); 
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
      
    tab(n, *fOut); 
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS "<< fKlassName << endl;
    *fOut << "#endif" << endl;
    
    *fOut << "#ifdef __APPLE__ " << endl;
    *fOut << "#define exp10f __exp10f" << endl;
    *fOut << "#define exp10 __exp10" << endl;
    *fOut << "#endif" << endl;
    
    if (gGlobal->gLightMode) {
        tab(n, *fOut);
        *fOut << "#define max(a,b) ((a < b) ? b : a)\n";
        *fOut << "#define min(a,b) ((a < b) ? a : b)\n";
    }

    tab(n, *fOut); *fOut << "typedef struct {";

        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "} "<<  fKlassName << ";";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n, *fOut); *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
                tab(n+1, *fOut);
                fAllocateInstructions->accept(&fCodeProducer);
            tab(n, *fOut); *fOut << "}";
        }
        
        tab(n, *fOut);
        
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n, *fOut); *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
                tab(n+1, *fOut);
                fDestroyInstructions->accept(&fCodeProducer);
            tab(n, *fOut);  *fOut << "}";
            tab(n, *fOut);
            tab(n, *fOut);
        }
        
        *fOut << fKlassName << "* new" << fKlassName << "() { ";
            tab(n+1, *fOut); *fOut << fKlassName << "* dsp = (" << fKlassName  << "*)malloc(sizeof(" << fKlassName << "));";
            if (fAllocateInstructions->fCode.size() > 0) {
                tab(n+1, *fOut); *fOut << "allocate" << fKlassName << "(dsp);";
            }
            tab(n+1, *fOut); *fOut << "return dsp;";
        tab(n, *fOut); *fOut << "}";

        tab(n, *fOut);
        tab(n, *fOut); *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) { ";
            if (fDestroyInstructions->fCode.size() > 0) {
                tab(n+1, *fOut); *fOut << "destroy" << fKlassName << "(dsp);";
            }
            tab(n+1, *fOut); *fOut << "free(dsp);";
        tab(n, *fOut); *fOut << "}";

        // Print metadata declaration
        tab(n, *fOut);
        produceMetadata(n);
    }

    // Get sample rate method  (TODO : use generateGetSampleRate)
    tab(n, *fOut); *fOut << "int getSampleRate" << fKlassName << "(" << fKlassName << "* dsp) { return dsp->fSamplingFreq; }";
   
    tab(n, *fOut);
    tab(n, *fOut);
    produceInfoFunctions(n, fKlassName, "dsp", false, false, &fCodeProducer);

    // Inits
    
    // TODO
    /*
     CInstVisitor codeproducer1(fOut, "");
     codeproducer1.Tab(n+1);
     generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
     generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);
     */
    
    tab(n, *fOut); *fOut << "void classInit" << fKlassName << "(int samplingFreq) {";
        {
            tab(n+1, *fOut);
            // Local visitor here to avoid DSP object type wrong generation  
            CInstVisitor codeproducer(fOut, "");
            codeproducer.Tab(n+1);
            generateStaticInit(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void instanceResetUserInterface" << fKlassName << "(" << fKlassName << "* dsp) {";
        {
            tab(n+1, *fOut);
            // Local visitor here to avoid DSP object type wrong generation
            CInstVisitor codeproducer(fOut, "");
            codeproducer.Tab(n+1);
            generateResetUserInterface(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp) {";
        {
            tab(n+1, *fOut);
            // Local visitor here to avoid DSP object type wrong generation
            CInstVisitor codeproducer(fOut, "");
            codeproducer.Tab(n+1);
            generateClear(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";
    
  
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int samplingFreq) {";
        {
            tab(n+1, *fOut);
            // Local visitor here to avoid DSP object type wrong generation
            CInstVisitor codeproducer(fOut, "");
            codeproducer.Tab(n+1);
            generateInit(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";
   
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut); *fOut << "instanceConstants" << fKlassName << "(dsp, samplingFreq);";
        tab(n+1, *fOut); *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
        tab(n+1, *fOut); *fOut << "instanceClear" << fKlassName << "(dsp);";
    tab(n, *fOut); *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut); *fOut << "classInit" << fKlassName << "(samplingFreq);";
        tab(n+1, *fOut); *fOut << "instanceInit" << fKlassName << "(dsp, samplingFreq);";
    tab(n, *fOut); *fOut << "}";
    
    if (!gGlobal->gLightMode) {
        // User interface
        tab(n, *fOut);
        tab(n, *fOut); *fOut << "void buildUserInterface" << fKlassName << "(" << fKlassName << "* dsp, UIGlue* ui_interface) {";
            tab(n+1, *fOut);
            fCodeProducer.Tab(n+1);
            generateUserInterface(&fCodeProducer);
        tab(n, *fOut); *fOut << "}";
    }

    // Compute
    generateCompute(n);
    tab(n, *fOut);

    // Generate user interface macros if needed
	if (gGlobal->gUIMacroSwitch) {
		tab(n, *fOut); *fOut << "#ifdef FAUST_UIMACROS";
            tab(n+1, *fOut); *fOut << "#define FAUST_INPUTS " << fNumInputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_ACTIVES " << fNumActives;
            tab(n+1, *fOut); *fOut << "#define FAUST_PASSIVES " << fNumPassives;
			printlines(n+1, fUIMacro, *fOut);
		tab(n, *fOut); *fOut << "#endif";
        tab(n, *fOut);
	}
    
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
}

void CCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut); *fOut << "void metadata" << fKlassName << "(MetaGlue* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(tabs+1, *fOut); *fOut << "m->declare(m->metaInterface, \"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become "contributor"
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(tabs+1, *fOut); *fOut << "m->declare(m->metaInterface, \"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                    tab(tabs+1, *fOut); *fOut << "m->declare(m->metaInterface, \"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }
 
    tab(tabs, *fOut); *fOut << "}" << endl;
}

// Scalar
CScalarCodeContainer::CScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :CCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

CScalarCodeContainer::~CScalarCodeContainer()
{}

void CScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void compute" << fKlassName << "(" << fKlassName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates one single scalar loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        loop->accept(&fCodeProducer);
    
        // Currently for soundfile management
        generatePostComputeBlock(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// Vector
CVectorCodeContainer::CVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out)
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
    tab(n, *fOut); *fOut << "void compute" << fKlassName << "(" << fKlassName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates DSP loop
        fDAGBlock->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;
}

// OpenMP
COpenMPCodeContainer::COpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :OpenMPCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out)
{}

void COpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n);
    tab(n, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Compute declaration
    tab(n, *fOut); *fOut << "void compute" << fKlassName << "(" << fKlassName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
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
CWorkStealingCodeContainer::CWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :WSSCodeContainer(numInputs, numOutputs, "dsp"), CCodeContainer(name, numInputs, numOutputs, out)
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
    tab(n, *fOut); *fOut << "static void computeThread(" << fKlassName << "* dsp, int num_thread) {";
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generate it
        fThreadLoopBlock->accept(&fCodeProducer);

        tab(n, *fOut); *fOut << "}" << endl;

        // Compute "compute" declaration
        tab(n, *fOut); *fOut << "void compute" << fKlassName << "(" << fKlassName << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

    tab(n, *fOut); *fOut << "}" << endl;

    tab(n, *fOut); *fOut << "extern \"C\" void computeThreadExternal(void* dsp, int num_thread) {";
        tab(n+1, *fOut); *fOut << "computeThread((" << fKlassName << "*)dsp, num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}
