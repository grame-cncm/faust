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

#include "asmjs_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"

using namespace std;

ASMJAVAScriptInstVisitor* ASMJAVAScriptInstVisitor::fGlobalVisitor = 0;

CodeContainer* ASMJAVAScriptCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new ASMJAVAScriptScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* ASMJAVAScriptCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for ASMJavaScript\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for ASMJavaScript\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("OpenMP : OpenMP not supported for ASMJavaScript\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("Scheduler mode not supported for ASMJavaScript\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("Vector mode not supported for ASMJavaScript\n");
    } else {
        container = new ASMJAVAScriptScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
ASMJAVAScriptScalarCodeContainer::ASMJAVAScriptScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :ASMJAVAScriptCodeContainer(name, super, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

ASMJAVAScriptScalarCodeContainer::~ASMJAVAScriptScalarCodeContainer()
{}

void ASMJAVAScriptCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "function " << fKlassName << "() {";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "'use asm';"; 
        
        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
        
        tab(n+1, *fOut);
        tab(n+1, *fOut);
        // fKlassName used in method naming for subclasses
        produceInfoFunctions(n+1, fKlassName, false);
    
        // Inits
        tab(n+1, *fOut); *fOut << fObjPrefix << "instanceInit" << fKlassName << " = function(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "fill" << fKlassName << " = function" << subst("(dsp, $0, output) {", counter);
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); fCodeProducer.Tab(n+2);
            generateComputeBlock(&fCodeProducer);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

    tab(n, *fOut); *fOut << "}" << endl;
    
    // Memory methods (as globals)
    tab(n, *fOut); *fOut << "new" << fKlassName << " = function() {"
                        << "return new "<< fKlassName << "()"
                        << "; }";

    tab(n, *fOut);
}

// Mathematical fucntion are declared as variables, they have to be generated before any other function (like 'faustpower')
struct sortDeclareFunctions
{
    map <string, string> fMathLibTable;
    
    sortDeclareFunctions(const map <string, string>& table) : fMathLibTable(table)
    {}
    
    bool operator()(StatementInst* a, StatementInst* b)
    { 
        DeclareFunInst* inst1 = dynamic_cast<DeclareFunInst*>(a);
        DeclareFunInst* inst2 = dynamic_cast<DeclareFunInst*>(b);
        
        if (inst1) {
            if (inst2) {
                if (fMathLibTable.find(inst1->fName) != fMathLibTable.end()) {
                    if (fMathLibTable.find(inst2->fName) != fMathLibTable.end()) {
                        return inst1->fName < inst2->fName;
                    } else {
                        return true;
                    }
                } 
            }
        }
        return false;
    }
};

void ASMJAVAScriptCodeContainer::produceClass()
{
    int n = 0;

    generateSR();

    // Libraries
    printLibrary(*fOut);
    
    // Sub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    
    // ASM module
    /*
        All variables have to be declared fierst, then functions, then export section.
     
    */
    tab(n, *fOut); *fOut << "function " << fKlassName << "Factory(global, foreign, buffer) {";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "'use asm';"; 
        tab(n+1, *fOut);
        
        // Memory access
        tab(n+1, *fOut); *fOut << "var HEAP32 = new global.Int32Array(buffer);"; 
        tab(n+1, *fOut); *fOut << "var HEAPF32 = new global.Float32Array(buffer);"; 
    
        // Always generated
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "var imul = global.Math.imul;";
        tab(n+1, *fOut); *fOut << "var log = global.Math.log;";
    
        // Global declarations (mathematical functions, global variables...)
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
    
        // All mathematical functions (got from math library as variables) have to be first...
        sortDeclareFunctions sorter(fCodeProducer.getMathLibTable());
        fGlobalDeclarationInstructions->fCode.sort(sorter);
        generateGlobalDeclarations(&fCodeProducer);
    
        // Always generated
        tab(n+1, *fOut); *fOut << "function fmodf(x, y) { x = +x; y = +y; return +(x % y); }";
        tab(n+1, *fOut); *fOut << "function log10f(a) { a = +a; return +(+log(a) / +log(10.)); }";
    
        // Fields : compute the structure size to use in 'new'
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
    
        // getNumInputs/getNumOutputs
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumInputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumOutputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
        tab(n+1, *fOut); *fOut << "}";

        // Inits
        tab(n+1, *fOut); *fOut << fObjPrefix << "function classInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            // Moves all variables declaration at the beginning of the block
            MoveVariablesInFront1 mover;
            BlockInst* block = mover.getCode(fInitInstructions); 
            block->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function init(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut); *fOut << fObjPrefix << "classInit(dsp, samplingFreq);";
            tab(n+2, *fOut); *fOut << fObjPrefix << "instanceInit(dsp, samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
    
        // setValue
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function setValue(dsp, offset, value) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "offset = offset | 0;";
            tab(n+2, *fOut); *fOut << "value = +value;";
            tab(n+2, *fOut);*fOut << "HEAPF32[dsp + offset >> 2] = value;"; 
        tab(n+1, *fOut); *fOut << "}";
    
        // getValue
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getValue(dsp, offset) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "offset = offset | 0;";
            tab(n+2, *fOut);*fOut << "return +HEAPF32[dsp + offset >> 2];";
        tab(n+1, *fOut); *fOut << "}";
    
        // Compute
        generateCompute(n);

        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(&fCodeProducer);
    
        // Exported functions (DSP only)
        tab(n+1, *fOut);
        *fOut << "return { ";
        *fOut << "getNumInputs" << ": " << "getNumInputs" << ", ";
        *fOut << "getNumOutputs" << ": " << "getNumOutputs" << ", ";
        *fOut << "classInit" << ": " << "classInit" << ", ";
        *fOut << "instanceInit" << ": " << "instanceInit" << ", ";
        *fOut << "init" << ": " << "init" << ", ";
        *fOut << "setValue" << ": " << "setValue" << ", ";
        *fOut << "getValue" << ": " << "getValue" << ", ";
        *fOut << "compute" << ": " << "compute";
        *fOut << " };";
   
    tab(n, *fOut); *fOut << "}" << endl;
    
    // User interface : prepare the JSON string...
    generateUserInterface(&fCodeProducer);
    
    // Generate JSON 
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function getDSPSize" <<  fKlassName << "() {";
    tab(n+1, *fOut);
    *fOut << "return " << fCodeProducer.getStructSize() << ";";
    printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
    tab(n, *fOut);
    
    // Fields to path
    tab(n, *fOut); *fOut << "function getPathTable" << fKlassName << "() {";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << "var pathTable = {};"; 
    map <string, string>::iterator it;
    map <string, string>& pathTable = fCodeProducer.getPathTable();
    map <string, pair<int, Typed::VarType> >& fieldTable = fCodeProducer.getFieldTable();
    for (it = pathTable.begin(); it != pathTable.end(); it++) {
        pair<int, Typed::VarType> tmp = fieldTable[(*it).first];
        tab(n+1, *fOut); *fOut << fObjPrefix << "pathTable[\"" << (*it).second << "\"] = " << tmp.first << ";"; 
    }
    tab(n+1, *fOut); *fOut << "return pathTable;"; 
    tab(n, *fOut); *fOut << "}";
    
    // Generate JSON 
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function getJSON" <<  fKlassName << "() {";
        tab(n+1, *fOut);
        *fOut << "return \""; *fOut << fCodeProducer.getJSON(true); *fOut << "\";";
        printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
    
    // Metadata declaration
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function metadata" << fKlassName << "(m) {";
    for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(n+1, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(n+1, *fOut); *fOut << "m.declare(\"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                    tab(n+1, *fOut); *fOut << "m.declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }
    
    tab(n, *fOut); *fOut << "}" << endl << endl;
 }

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void ASMJAVAScriptCodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{
    // Input/Output method
    fCodeProducer.Tab(tabs);
    generateGetInputs(subst("getNumInputs$0", classname), false, isvirtual)->accept(&fCodeProducer);
    generateGetOutputs(subst("getNumOutputs$0", classname), false, isvirtual)->accept(&fCodeProducer);
}

void ASMJAVAScriptScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << subst("function compute(dsp, $0, inputs, outputs) {", fFullCount);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << fFullCount << " = " << fFullCount << " | 0;";
        tab(n+2, *fOut); *fOut << "inputs = inputs | 0;";
        tab(n+2, *fOut); *fOut << "outputs = outputs | 0;";
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
    
        // Generates one single scalar loop and put is the the block
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        fComputeBlockInstructions->pushBackInst(loop);
    
        // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
        MoveVariablesInFront2 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions); 
        block->accept(&fCodeProducer);
           
    tab(n+1, *fOut); *fOut << "}";
}
