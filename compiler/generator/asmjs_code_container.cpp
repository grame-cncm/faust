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

/*
void ASMJAVAScriptCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
 
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
        // fKlassName used in method naming for subclasses
        //produceInfoFunctions(n+1, fKlassName, false);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumInputs" << fKlassName << "(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
        tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumOutputs" << fKlassName << "(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
        tab(n+1, *fOut); *fOut << "}";
    
        // Inits
        tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit" << fKlassName << "(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut); fCodeProducer.Tab(n+2);
            //generateInit(&fCodeProducer);
            // Moves all variables declaration at the beginning of the block
            MoveVariablesInFront1 mover1;
            BlockInst* block1 = mover1.getCode(fInitInstructions); 
            block1->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function fill" << fKlassName << subst("(dsp, $0, output) {", counter);
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << counter << " = " << counter << " | 0;";
            tab(n+2, *fOut); *fOut << "output = output | 0;";
            tab(n+2, *fOut); fCodeProducer.Tab(n+2);
     
            // Generates one single scalar loop and put is the the block
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            fComputeBlockInstructions->pushBackInst(loop);
            
            // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
            MoveVariablesInFront2 mover2;
            BlockInst* block2 = mover2.getCode(fComputeBlockInstructions); 
            block2->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        // Exported functions (DSP only)
        tab(n+1, *fOut);
        *fOut << "return { ";
        *fOut << "getNumInputs" << fKlassName << ": " << "getNumInputs" << fKlassName << ", ";
        *fOut << "getNumOutputs"<< fKlassName << ": " << "getNumOutputs"<< fKlassName << ", ";
        *fOut << "instanceInit"<< fKlassName << ": " << "instanceInit"<< fKlassName << ", ";
        *fOut << "fill"<< fKlassName << ": " << "fill"<< fKlassName;
        *fOut << " };";
  
    tab(n, *fOut); *fOut << "}";
    
    // Generate JSON and getDSPSize
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function getDSPSize" <<  fKlassName << "() {";
    tab(n+1, *fOut);
    *fOut << "return " << fCodeProducer.getStructSize() << ";";
    printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
}
*/

void ASMJAVAScriptCodeContainer::produceInternal()
{
    int n = 0;
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    
    /*
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
    */
    
    /*
    // All mathematical functions (got from math library as variables) have to be first...
    sortDeclareFunctions sorter(fCodeProducer.getMathLibTable());
    fGlobalDeclarationInstructions->fCode.sort(sorter);
    generateGlobalDeclarations(&fCodeProducer);
     */
    
    /*
    // Always generated
    tab(n+1, *fOut); *fOut << "function fmodf(x, y) { x = +x; y = +y; return +(x % y); }";
    tab(n+1, *fOut); *fOut << "function log10f(a) { a = +a; return +(+log(a) / +log(10.)); }";
    */
    
    // Fields : compute the structure size to use in 'new'
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    generateDeclarations(&fCodeProducer);
    
    
    // getNumInputs/getNumOutputs
    tab(n+1, *fOut);
    // fKlassName used in method naming for subclasses
    //produceInfoFunctions(n+1, fKlassName, false);
    tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumInputs" << fKlassName << "(dsp) {";
    tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
    tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumOutputs" << fKlassName << "(dsp) {";
    tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
    tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    
    // Inits
    tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit" << fKlassName << "(dsp, samplingFreq) {";
    tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
    tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
    tab(n+2, *fOut); fCodeProducer.Tab(n+2);
    //generateInit(&fCodeProducer);
    // Moves all variables declaration at the beginning of the block
    MoveVariablesInFront1 mover1;
    BlockInst* block1 = mover1.getCode(fInitInstructions); 
    block1->accept(&fCodeProducer);
    tab(n+1, *fOut); *fOut << "}";
    
    // Fill
    string counter = "count";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << "function fill" << fKlassName << subst("(dsp, $0, output) {", counter);
    tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
    tab(n+2, *fOut); *fOut << counter << " = " << counter << " | 0;";
    tab(n+2, *fOut); *fOut << "output = output | 0;";
    tab(n+2, *fOut); fCodeProducer.Tab(n+2);
    
    // Generates one single scalar loop and put is the the block
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    fComputeBlockInstructions->pushBackInst(loop);
    
    // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
    MoveVariablesInFront2 mover2;
    BlockInst* block2 = mover2.getCode(fComputeBlockInstructions); 
    block2->accept(&fCodeProducer);
    tab(n+1, *fOut); *fOut << "}";
    
    /*
    // Exported functions (DSP only)
    tab(n+1, *fOut);
    *fOut << "return { ";
    *fOut << "getNumInputs" << fKlassName << ": " << "getNumInputs" << fKlassName << ", ";
    *fOut << "getNumOutputs"<< fKlassName << ": " << "getNumOutputs"<< fKlassName << ", ";
    *fOut << "instanceInit"<< fKlassName << ": " << "instanceInit"<< fKlassName << ", ";
    *fOut << "fill"<< fKlassName << ": " << "fill"<< fKlassName;
    *fOut << " };";
    
    tab(n, *fOut); *fOut << "}";
    
    // Generate JSON and getDSPSize
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function getDSPSize" <<  fKlassName << "() {";
    tab(n+1, *fOut);
    *fOut << "return " << fCodeProducer.getStructSize() << ";";
    printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
     
    */
}

void ASMJAVAScriptCodeContainer::produceClass()
{
    int n = 0;

    generateSR();

    // Libraries
    printLibrary(*fOut);
    
    // Sub containers
    //generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    
    // ASM module
    /*
        1) all variables have to be declared first, then functions, then export section.
        2) the DSP data structure fields are not generated. The structure size is computed instead, and memory allocation/deallocation is done
            outside of the module using emscripten memory functions.
        3) in compute, 'inputs/outputs' will point to audio buffers allocated outside of the module. Access on this buffers is generated 
            in an 'adhoc' manner...
        4) TypingVisitor is used to know value types :
            - 'funcalls' types are not known by TypingVisitor, so the CodeContainer::pushFunction adds kIntish, kFloatish or kDoublish
            and ASMJAVAScriptInstVisitor::visit(CastNumInst* inst) interprets kIntish, kFloatish or kDoublish
            - ASMJAVAScriptInstVisitor::visit(BinopInst* inst) add the type of result
        5) MoveVariablesInFront1 and MoveVariablesInFront3 FIR ==> FIR passes are used to move variable declaration at the beginning of blocks.
        6) 'fmodf' and 'log10f' mathematical functions are manually generated. 
        7) 'buffer" argument is the actual emscripten memory buffer and will contain the DSP object structure and 'inputs/outputs' audio buffers
        8) Table generation :
            - tables (as type kStaticStruct) are treated as 'mydsp' fields
            - 'mydsp' classInit mathode is change so that method on subcontainers are rewritter, as normal function call
        9) Pointers are actually integers, so are treated like this
        
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
    
        // Access for subcontainer externally defined methods
        tab(n+1, *fOut);
        tab(n+1, *fOut);
    
        /*
        // Remove variable declaration
        StaticInitRewriter rewriter;
        BlockInst* block0 = rewriter.getCode(fStaticInitInstructions);
         */
    
        /*
        // Generates functions calls as "access" to externally defined methods
        ForeignContainerWriter foreign(fOut, n+1);
        fStaticInitInstructions->accept(&foreign);
        fInitInstructions->accept(&foreign);
        */
    
        // Global declarations (mathematical functions, global variables...)
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
    
        /*
        // TODO with subcontainers
        tab(n+1, *fOut); *fOut << "var abs = global.Math.abs;";
        tab(n+1, *fOut); *fOut << "var absf = global.Math.abs;";
        tab(n+1, *fOut); *fOut << "var fabsf = global.Math.abs;";
        tab(n+1, *fOut); *fOut << "var acosf = global.Math.acos;";
        tab(n+1, *fOut); *fOut << "var asinf = global.Math.asin;";
        tab(n+1, *fOut); *fOut << "var atanf = global.Math.atan;";
        tab(n+1, *fOut); *fOut << "var atan2f = global.Math.atan2;";
        tab(n+1, *fOut); *fOut << "var ceilf = global.Math.ceil;";
        tab(n+1, *fOut); *fOut << "var cosf = global.Math.cos;";
        tab(n+1, *fOut); *fOut << "var expf = global.Math.exp;";
        tab(n+1, *fOut); *fOut << "var floorf = global.Math.floor;";
        tab(n+1, *fOut); *fOut << "var logf = global.Math.log;";
        tab(n+1, *fOut); *fOut << "var max = global.Math.max;";
        tab(n+1, *fOut); *fOut << "var min = global.Math.min;";
        tab(n+1, *fOut); *fOut << "var powf = global.Math.pow;";
        tab(n+1, *fOut); *fOut << "var sinf = global.Math.sin;";
        tab(n+1, *fOut); *fOut << "var sqrtf = global.Math.sqrt;";
        tab(n+1, *fOut); *fOut << "var tanf = global.Math.tan;";
         */
    
    
        // All mathematical functions (got from math library as variables) have to be first...
        sortDeclareFunctions sorter(fCodeProducer.getMathLibTable());
        fGlobalDeclarationInstructions->fCode.sort(sorter);
        generateGlobalDeclarations(&fCodeProducer);
    
        // Always generated
        tab(n+1, *fOut); *fOut << "function fmodf(x, y) { x = +x; y = +y; return +(x % y); }";
        tab(n+1, *fOut); *fOut << "function log10f(a) { a = +a; return +(+log(a) / +log(10.)); }";
    
    
        // Sub containers
        //generateSubContainers();
    
        // Generate subcontainers and allocate their data structure in DSP
        list<CodeContainer*>::const_iterator it1;
        int i = 0;
        for (it1 = fSubContainers.begin(); it1 != fSubContainers.end(); it1++, i++) {
            (*it1)->produceInternal();
            stringstream num; num << i;
            string signame = "sig" + num.str();
            // Variable type will be changed, so removed it from global table
            gGlobal->gVarTypeTable.erase(signame);
            pushDeclare(InstBuilder::genDecStructVar(signame, InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kInt), (*it1)->getStructSize()/4)));
        }
        
        // Fields : compute the structure size to use in 'new'
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);
        

        // getNumInputs/getNumOutputs
        tab(n+1, *fOut);
        //produceInfoFunctions(n+1, "", false);  // TODO
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
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            //generateStaticInit(&fCodeProducer);
        
            // Generates 'foreign' funcalls
            ContainerObjectRemover writer1(fCodeProducer.getFieldTable());
            BlockInst* block0 = writer1.getCode(fStaticInitInstructions);
            block0->accept(&fCodeProducer);
            /*
            block0 = writer.getCode(fPostStaticInitInstructions);
            block0->accept(&fCodeProducer);
            */
            
            
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            // Moves all variables declaration at the beginning of the block
            MoveVariablesInFront1 mover;
            BlockInst* block2 = mover.getCode(fInitInstructions); 
    
            //block2->accept(&fCodeProducer);
    
            /// 
            ContainerObjectRemover writer2(fCodeProducer.getFieldTable());
            BlockInst* block22 = writer2.getCode(block2);
            block22->accept(&fCodeProducer);
            
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
    
    // Generate getSubContainers
    tab(n, *fOut); *fOut << "function getSubContainers" <<  fKlassName << "() {";
    tab(n+1, *fOut);
    *fOut << "return " << getSubContainers() << ";";
    tab(n, *fOut); *fOut << "}";
    tab(n, *fOut);
    
    // Generate JSON and getDSPSize
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
