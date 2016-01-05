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
#include "json_instructions.hh"

using namespace std;

/*
 ASM module description : 

     1) all variables have to be declared first, then functions, then export section.
     2) the DSP data structure fields are not generated. The structure size is computed instead, and memory allocation/deallocation is done
     outside of the module using emscripten (or 'self-made') memory functions.
     3) in compute, 'inputs/outputs' will point to audio buffers allocated outside of the module. Access on this buffers is generated 
     in an 'adhoc' manner...
     4) TypingVisitor is used to know value types :
        - 'funcalls' types are not known by TypingVisitor, so the CodeContainer::pushFunction adds kIntish, kFloatish or kDoublish
        and ASMJAVAScriptInstVisitor::visit(CastNumInst* inst) interprets kIntish, kFloatish or kDoublish
        - ASMJAVAScriptInstVisitor::visit(BinopInst* inst) adds the type of result
     5) MoveVariablesInFront1 and MoveVariablesInFront2 FIR ==> FIR passes are used to move variable declaration at the beginning of blocks.
     6) 'fmodf' and 'log10f' mathematical functions are manually generated. 
     7) 'buffer' argument is the actual emscripten (or 'self-made') memory buffer and will contain the DSP object structure and 'inputs/outputs' audio buffers.
     8) subcontainer generation :
        - tables (as type kStaticStruct) are treated as 'mydsp' fields
        - 'mydsp' classInit method is changed so that methods on subcontainers are rewritten as normal function calls
        - subcontainer are merged in the global container : fields, functions definition...
        - use of 'sig' variable name is translated in 'dsp'
        - subcontainer is not allocated/deallocated anymore
     9) pointers are actually integers, so are treated like this
     10) waveforms are also allocated in the DSP object heap. Array definition is not done in 'global' part but in 'inits' methods 
     (see InstructionsCompiler::declareWaveform()). Since 'in extention' array definition is not possible, the FIR code is first rewritten to 
     a list of 'store' instructions (MoveVariablesInFront2), then the actual code is generated.
 
*/

ASMJAVAScriptCodeContainer::ASMJAVAScriptCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
            :fOut(out), fObjPrefix("")
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    
    // Allocate one static visitor
    if (!gGlobal->gASMJSVisitor) {
        gGlobal->gASMJSVisitor = new ASMJAVAScriptInstVisitor(fOut);
    }
}

CodeContainer* ASMJAVAScriptCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new ASMJAVAScriptScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* ASMJAVAScriptCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
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
        //throw faustexception("Vector mode not supported for ASMJavaScript\n");
        container = new ASMJAVAScriptVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new ASMJAVAScriptScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
ASMJAVAScriptScalarCodeContainer::ASMJAVAScriptScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :ASMJAVAScriptCodeContainer(name, numInputs, numOutputs, out)
{
     fSubContainerType = sub_container_type;
}

ASMJAVAScriptScalarCodeContainer::~ASMJAVAScriptScalarCodeContainer()
{}

int ASMJAVAScriptCodeContainer::getStructSize() { return gGlobal->gASMJSVisitor->getStructSize(); }

void ASMJAVAScriptCodeContainer::produceInternal()
{
    int n = 0;
    
    // Global declarations
    tab(n, *fOut);
    gGlobal->gASMJSVisitor->Tab(n);
      
    // Fields : compute the structure size to use in 'new'
    gGlobal->gASMJSVisitor->Tab(n+1);
    generateDeclarations(gGlobal->gASMJSVisitor);
    
    // fKlassName used in method naming for subclasses
    
    // getNumInputs/getNumOutputs
    tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumInputs" << fKlassName << "(dsp) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumOutputs" << fKlassName << "(dsp) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    tab(n+1, *fOut);
    
    // Inits
    tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit" << fKlassName << "(dsp, samplingFreq) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
        tab(n+2, *fOut); gGlobal->gASMJSVisitor->Tab(n+2);
    
        // Moves all variables declaration at the beginning of the block
        MoveVariablesInFront2 mover1;
        BlockInst* block1 = mover1.getCode(fInitInstructions); 
        block1->accept(gGlobal->gASMJSVisitor);
    
    tab(n+1, *fOut); *fOut << "}";
    
    // Fill
    string counter = "count";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << "function fill" << fKlassName << subst("(dsp, $0, output) {", counter);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << counter << " = " << counter << " | 0;";
        tab(n+2, *fOut); *fOut << "output = output | 0;";
        tab(n+2, *fOut); gGlobal->gASMJSVisitor->Tab(n+2);
    
        // Generates one single scalar loop and put is the the block
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
        fComputeBlockInstructions->pushBackInst(loop);
        
        // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
        MoveVariablesInFront2 mover2;
        BlockInst* block2 = mover2.getCode(fComputeBlockInstructions); 
        block2->accept(gGlobal->gASMJSVisitor);
    tab(n+1, *fOut); *fOut << "}";
}

void ASMJAVAScriptCodeContainer::produceClass()
{
    int n = 0;
   
    generateSR();

    // Libraries
    printLibrary(*fOut);
 
    // Global declarations
    tab(n, *fOut);
    gGlobal->gASMJSVisitor->Tab(n);
    tab(n, *fOut); *fOut << "function " << fKlassName << "Module(global, foreign, buffer) {";
    
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
        gGlobal->gASMJSVisitor->Tab(n+1);
           
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first...
        sortDeclareFunctions sorter(gGlobal->gASMJSVisitor->getMathLibTable());
        fGlobalDeclarationInstructions->fCode.sort(sorter);
        generateGlobalDeclarations(gGlobal->gASMJSVisitor);
          
        // Manually and always generated
        tab(n+1, *fOut); *fOut << "function fmodf(x, y) { x = +x; y = +y; return +(x % y); }";
        tab(n+1, *fOut); *fOut << "function log10f(a) { a = +a; return +(+log(a) / +log(10.)); }";
           
        // Fields : compute the structure size to use in 'new'
        gGlobal->gASMJSVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gASMJSVisitor);
    
        // After field declaration...
        generateSubContainers();
        
        // getNumInputs/getNumOutputs
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumInputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
        tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getNumOutputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
        tab(n+1, *fOut); *fOut << "}";
    
        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function classInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            // Replace use of "sig" in use of "dsp"
            DspRenamer renamer1;
            BlockInst* block0 = renamer1.getCode(fStaticInitInstructions);
            block0->accept(gGlobal->gASMJSVisitor);
               
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function instanceInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            // Replace use of "sig" in use of "dsp"
            DspRenamer renamer2;
            BlockInst* block2 = renamer2.getCode(fInitInstructions);
            // Moves all variables declaration at the beginning of the block
            MoveVariablesInFront2 mover1;
            BlockInst* block3 = mover1.getCode(block2); 
            block3->accept(gGlobal->gASMJSVisitor);
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
            tab(n+2, *fOut); *fOut << "HEAPF32[dsp + offset >> 2] = value;"; 
        tab(n+1, *fOut); *fOut << "}";
    
        // getValue
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << fObjPrefix << "function getValue(dsp, offset) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "offset = offset | 0;";
            tab(n+2, *fOut); *fOut << "return +HEAPF32[dsp + offset >> 2];";
        tab(n+1, *fOut); *fOut << "}";
    
        // Compute
        generateCompute(n);

        // Possibly generate separated functions
        gGlobal->gASMJSVisitor->Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(gGlobal->gASMJSVisitor);
    
        // Exported functions (DSP only)
        tab(n+1, *fOut);
        *fOut << "return { ";
        *fOut << "getNumInputs : getNumInputs, ";
        *fOut << "getNumOutputs : getNumOutputs, ";
        *fOut << "classInit : classInit, ";
        *fOut << "instanceInit : instanceInit, ";
        *fOut << "init : init, ";
        *fOut << "setValue : setValue, ";
        *fOut << "getValue : getValue, ";
        *fOut << "compute : compute";
        *fOut << " };";
   
    tab(n, *fOut); *fOut << "}" << endl;
    
    // User interface : prepare the JSON string...
    JSONInstVisitor json_visitor(fNumInputs, fNumOutputs);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);
     
    // Generate JSON and getDSPSize
    tab(n, *fOut); *fOut << "function getSize" << fKlassName << "() {";
    tab(n+1, *fOut);
    *fOut << "return " << gGlobal->gASMJSVisitor->getStructSize() << ";";
    printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
    tab(n, *fOut);
    
    // Fields to path
    tab(n, *fOut); *fOut << "function getPathTable" << fKlassName << "() {";
    tab(n+1, *fOut); *fOut << fObjPrefix << "var pathTable = [];"; 
    map <string, string>::iterator it;
    map <string, pair<int, Typed::VarType> >& fieldTable = gGlobal->gASMJSVisitor->getFieldTable();
    for (it = json_visitor.fPathTable.begin(); it != json_visitor.fPathTable.end(); it++) {
        pair<int, Typed::VarType> tmp = fieldTable[(*it).first];
        tab(n+1, *fOut); *fOut << fObjPrefix << "pathTable[\"" << (*it).second << "\"] = " << tmp.first << ";"; 
    }
    tab(n+1, *fOut); *fOut << "return pathTable;"; 
    tab(n, *fOut); *fOut << "}";
    
    // Generate JSON 
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "function getJSON" << fKlassName << "() {";
        tab(n+1, *fOut);
        *fOut << "return \""; *fOut << json_visitor.JSON(true); *fOut << "\";";
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

void ASMJAVAScriptScalarCodeContainer::generateCompute(int n)
{
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << subst("function compute(dsp, $0, inputs, outputs) {", fFullCount);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << fFullCount << " = " << fFullCount << " | 0;";
        tab(n+2, *fOut); *fOut << "inputs = inputs | 0;";
        tab(n+2, *fOut); *fOut << "outputs = outputs | 0;";
        tab(n+2, *fOut);
        gGlobal->gASMJSVisitor->Tab(n+2);
    
        // Generates one single scalar loop and put is the the block
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        fComputeBlockInstructions->pushBackInst(loop);
    
        // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
        MoveVariablesInFront2 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions); 
        block->accept(gGlobal->gASMJSVisitor);
           
    tab(n+1, *fOut); *fOut << "}";
}

// Vector
ASMJAVAScriptVectorCodeContainer::ASMJAVAScriptVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), ASMJAVAScriptCodeContainer(name, numInputs, numOutputs, out)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = 0;
}

ASMJAVAScriptVectorCodeContainer::~ASMJAVAScriptVectorCodeContainer()
{}

void ASMJAVAScriptVectorCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << fObjPrefix << subst("function compute(dsp, $0, inputs, outputs) {", fFullCount);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << fFullCount << " = " << fFullCount << " | 0;";
        tab(n+2, *fOut); *fOut << "inputs = inputs | 0;";
        tab(n+2, *fOut); *fOut << "outputs = outputs | 0;";
        tab(n+2, *fOut);
    gGlobal->gASMJSVisitor->Tab(n+2);
    
    // Generates local variables declaration and setup
    generateComputeBlock(gGlobal->gASMJSVisitor);
    
    // Generates DSP loop
    fDAGBlock->accept(gGlobal->gASMJSVisitor);
    
    tab(n+1, *fOut); *fOut << "}";
}
