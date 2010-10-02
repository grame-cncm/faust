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
using namespace std;

#include "opencl_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "function_builder.hh"

extern int gVectorLoopVariant;
extern bool gUIMacroSwitch;

extern map<Tree, set<Tree> > gMetaDataSet;

CodeContainer* OpenCLCodeContainer::createScalarContainer(const string& name) 
{ 
    return new OpenCLCodeContainer("", 0, 1, fOut, name);
}

void OpenCLCodeContainer::produceInternal()
{
    int n = 0;
    
    // Global declarations
    tab(n, *fOut); 
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }
    
    tab(n, *fOut); *fOut << "struct " << fPrefix << fStructName << " {";
    
        tab(n+1, *fOut); 
        tab(n+1, *fOut); 
        
        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);
            
            // Sort arrays to be at the begining
            fDeclarationInstructions->fCode.sort(sortFunction1);
            
            fDeclarationInstructions->accept(&fCodeProducer);
        }
            
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
            fInitInstructions->accept(&fCodeProducer);
        }
    tab(n, *fOut); *fOut << "}";
    
    // Fill
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << "fill" << fPrefix << "(" << fPrefix << fStructName << subst("* dsp, int count, $0* output) {", ifloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    
    if (fComputeBlockInstructions->fCode.size() > 0) {
        fComputeBlockInstructions->accept(&fCodeProducer);
    }
    
    ForLoopInst* loop = fCurLoop->getScalarLoop();
    loop->accept(&fCodeProducer);

    tab(n, *fOut); *fOut << "};\n" << endl;
}
        
void OpenCLCodeContainer::produceClass() 
{
    // Generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushGlobalDeclare(InstBuilder::genDeclareVarInst("fSamplingFreq", 
        InstBuilder::genBasicTyped(Typed::kInt), Address::kGlobal));
    pushFrontInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fSamplingFreq", Address::kGlobal), 
                                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("samplingFreq", Address::kFunArgs))));
    
    int n = 0;
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
     
     // Sub containers
    generateSubContainers();
    
    // Functions
    tab(n, *fOut); 
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }
    
    tab(n, *fOut); *fOut << "struct " << fPrefix << fStructName << " {";
    
        tab(n+1, *fOut); 
        tab(n+1, *fOut); 
        
        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);
            
            // Sort arrays to be at the begining
            fDeclarationInstructions->fCode.sort(sortFunction1);
            
            fDeclarationInstructions->accept(&fCodeProducer);
        }
            
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
            OpenCLInstVisitor codeproducer(fOut, "", "");
            codeproducer.Tab(n+1);
            fStaticInitInstructions->accept(&codeproducer);
        }
    tab(n, *fOut); *fOut << "}";

    tab(n, *fOut); 
    tab(n, *fOut); *fOut << "void " << fPrefix << "instanceInit(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        if (fInitInstructions->fCode.size() > 0) {
            tab(n+1, *fOut);
            fCodeProducer.Tab(n+1);
            fInitInstructions->accept(&fCodeProducer);
        }
    tab(n, *fOut); *fOut << "}";

    tab(n, *fOut); 
    tab(n, *fOut); *fOut << "void " << fPrefix << "init(" << fPrefix << fStructName << "* dsp, int samplingFreq) {";
        tab(n+1, *fOut); *fOut << fPrefix << "classInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << fPrefix << "instanceInit(dsp, samplingFreq);";
    tab(n, *fOut); *fOut << "}";
    
    // User interface
    tab(n, *fOut); 
    tab(n, *fOut); *fOut << "void " << fPrefix << "buildUserInterface(" << fPrefix << fStructName << "* dsp, UIGlue* interface) {";
        if (fUserInterfaceInstructions->fCode.size() > 0) {
            tab(n+1, *fOut);
            fCodeProducer.Tab(n+1);
            fUserInterfaceInstructions->accept(&fCodeProducer);
        }
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

void OpenCLCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "void " << fPrefix << "compute(" << fPrefix << fStructName << subst("* dsp, int count, $0** inputs, $0** outputs) {", xfloat());
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    
    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&fCodeProducer);
    
    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->getScalarLoop();
    loop->accept(&fCodeProducer);
    
    tab(n, *fOut); *fOut << "}" << endl;
}

