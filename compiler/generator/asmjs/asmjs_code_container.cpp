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
 ASM backend/module description: 

     1) all variables have to be declared first, then functions, then export section.
     2) the DSP data structure fields are not generated. The structure size is computed instead, and memory allocation/deallocation is done
     outside of the module using emscripten (or 'self-made') memory functions.
     3) in compute, 'inputs/outputs' will point to audio buffers allocated outside of the module. Access on this buffers is generated 
     in an 'adhoc' manner...
     4) TypingVisitor is used to know value types :
        - 'funcalls' types are not known by TypingVisitor, so the CodeContainer::pushFunction adds kInt32ish, kFloatish or kDoublish
        and ASMJAVAScriptInstVisitor::visit(CastInst* inst) interprets kInt32ish, kFloatish or kDoublish
        - ASMJAVAScriptInstVisitor::visit(BinopInst* inst) adds the type of result
     5) MoveVariablesInFront2 FIR ==> FIR passes are used to move variable declaration at the beginning of blocks.
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
     11) 'faustpower' function actually fallback to regular 'pow' (see powprim.h), otherwise incorrectly typed 'faustpower' is generated.
 
*/

dsp_factory_base* ASMJAVAScriptCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

ASMJAVAScriptCodeContainer::ASMJAVAScriptCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out):fOut(out)
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
  
    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for ASMJavaScript\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for ASMJavaScript\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for ASMJavaScript\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for ASMJavaScript\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for ASMJavaScript\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for ASMJavaScript\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for ASMJavaScript\n");
        //container = new ASMJAVAScriptVectorCodeContainer(name, numInputs, numOutputs, dst);
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
    tab(n+1, *fOut); *fOut << "function getNumInputs" << fKlassName << "(dsp) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << "function getNumOutputs" << fKlassName << "(dsp) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
    tab(n+1, *fOut); *fOut << "}";
    tab(n+1, *fOut);
    
    // Inits
    tab(n+1, *fOut); *fOut << "function instanceInit" << fKlassName << "(dsp, samplingFreq) {";
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
        tab(n+2, *fOut); gGlobal->gASMJSVisitor->Tab(n+2);
        generateASMBlock(fStaticInitInstructions);
        generateASMBlock(fInitInstructions);
        generateASMBlock(fResetUserInterfaceInstructions);
        generateASMBlock(fClearInstructions);
    tab(n+1, *fOut); *fOut << "}";
    
    // Fill
    string counter = "count";
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << "function fill" << fKlassName << subst("(dsp, $0, output) {", counter);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << counter << " = " << counter << " | 0;";
        tab(n+2, *fOut); *fOut << "output = output | 0;";
        tab(n+2, *fOut); gGlobal->gASMJSVisitor->Tab(n+2);
    
        // Generates one single scalar loop and put it in the block
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
        fComputeBlockInstructions->pushBackInst(loop);
        
        // Moves all variables declaration at the beginning of the block and possibly separate 'declaration' and 'store'
        MoveVariablesInFront2 mover;
        BlockInst* block = mover.getCode(fComputeBlockInstructions);
    
        // Force "output" access to be coherent with fSubContainerType (integer or real)
        gGlobal->gASMJSVisitor->setSubContainerType(fSubContainerType);
        block->accept(gGlobal->gASMJSVisitor);
    
        // Restore default...
        gGlobal->gASMJSVisitor->setSubContainerType(-1);
    
    tab(n+1, *fOut); *fOut << "}";
}

void ASMJAVAScriptCodeContainer::produceClass()
{
    int n = 0;
  
    // Global declarations
    tab(n, *fOut);
    gGlobal->gASMJSVisitor->Tab(n);
    tab(n, *fOut); *fOut << "function " << fKlassName << "Module(global, foreign, buffer) {";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "'use asm';"; 
        tab(n+1, *fOut);
        
        // Memory access
        tab(n+1, *fOut); *fOut << "var HEAP32 = new global.Int32Array(buffer);";
        if (gGlobal->gFloatSize == 1) {
            tab(n+1, *fOut); *fOut << "var HEAPF = new global.Float32Array(buffer);";
        } else if (gGlobal->gFloatSize == 2) {
            tab(n+1, *fOut); *fOut << "var HEAPF = new global.Float64Array(buffer);";
        }
    
        // Always generated mathematical functions
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "var imul = foreign.imul;";
        tab(n+1, *fOut); *fOut << "var log = foreign.log;";
        tab(n+1, *fOut); *fOut << "var round = foreign.round;";
    
        // Global declarations (mathematical functions, global variables...)
        tab(n+1, *fOut);
        gGlobal->gASMJSVisitor->Tab(n+1);
           
        // Sub containers : before functions generation
        mergeSubContainers();
    
        // All mathematical functions (got from math library as variables) have to be first
        sortDeclareFunctions sorter(gGlobal->gASMJSVisitor->getMathLibTable());
        fGlobalDeclarationInstructions->fCode.sort(sorter);
        generateGlobalDeclarations(gGlobal->gASMJSVisitor);
          
        // Manually always generated mathematical functions
        tab(n+1, *fOut); *fOut << "function fmod" << isuffix() << "(x, y) { x = +x; y = +y; return +(x % y); }";
        tab(n+1, *fOut); *fOut << "function log10" << isuffix() << "(a) { a = +a; return +(+log(a) / +log(10.)); }";
        tab(n+1, *fOut); *fOut << "function remainder" << isuffix() << "(x, y) { x = +x; y = +y; return +(x - +round(x/y) * y); }";
    
        // Fields : compute the structure size to use in 'new'
        gGlobal->gASMJSVisitor->Tab(n+1);
        generateDeclarations(gGlobal->gASMJSVisitor);
    
        // After field declaration...
        generateSubContainers();
        
        // getNumInputs/getNumOutputs
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function getNumInputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumInputs << ";";
        tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function getNumOutputs(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return " << fNumOutputs << ";";
        tab(n+1, *fOut); *fOut << "}";
    
        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function classInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateASMBlock(DspRenamer().getCode(fStaticInitInstructions));
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function instanceConstants(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateASMBlock(DspRenamer().getCode(fInitInstructions));
            }
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function instanceResetUserInterface(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateASMBlock(DspRenamer().getCode(fResetUserInterfaceInstructions));
            }
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function instanceClear(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut);
            gGlobal->gASMJSVisitor->Tab(n+2);
            {
                // Rename 'sig' in 'dsp' and remove 'dsp' allocation
                generateASMBlock(DspRenamer().getCode(fClearInstructions));
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function init(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut); *fOut << "classInit(dsp, samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(dsp, samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function instanceInit(dsp, samplingFreq) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "samplingFreq = samplingFreq | 0;";
            tab(n+2, *fOut); *fOut << "instanceConstants(dsp, samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceResetUserInterface(dsp);";
            tab(n+2, *fOut); *fOut << "instanceClear(dsp);";
        tab(n+1, *fOut); *fOut << "}";
    
        // getSampleRate
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function getSampleRate(dsp) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "return HEAP32[dsp + " << gGlobal->gASMJSVisitor->getFieldOffset("fSamplingFreq") << " >> 2] | 0;";
        tab(n+1, *fOut); *fOut << "}";
 
        // setParamValue
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function setParamValue(dsp, offset, value) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "offset = offset | 0;";
            tab(n+2, *fOut); *fOut << "value = +value;";
            tab(n+2, *fOut); *fOut << "HEAPF[dsp + offset >> " << offStr << "] = value;";
        tab(n+1, *fOut); *fOut << "}";
    
        // getParamValue
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "function getParamValue(dsp, offset) {";
            tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
            tab(n+2, *fOut); *fOut << "offset = offset | 0;";
            tab(n+2, *fOut); *fOut << "return +(HEAPF[dsp + offset >> " << offStr << "]);";
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
        *fOut << "instanceConstants : instanceConstants, ";
        *fOut << "instanceResetUserInterface : instanceResetUserInterface, ";
        *fOut << "instanceClear : instanceClear, ";
        *fOut << "init : init, ";
        *fOut << "getSampleRate : getSampleRate, ";
        *fOut << "setParamValue : setParamValue, ";
        *fOut << "getParamValue : getParamValue, ";
        *fOut << "compute : compute";
        *fOut << " };";
   
    tab(n, *fOut); *fOut << "}" << endl;
    
    // User interface : prepare the JSON string...
    JSONInstVisitor json_visitor(fNumInputs, fNumOutputs);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);
     
    // Generate JSON and getSize
    tab(n, *fOut); *fOut << "function getSize" << fKlassName << "() {";
        tab(n+1, *fOut);
        *fOut << "return " << gGlobal->gASMJSVisitor->getStructSize() << ";";
        printlines(n+1, fUICode, *fOut);
    tab(n, *fOut); *fOut << "}";
    tab(n, *fOut);
    
    // Fields to path
    tab(n, *fOut); *fOut << "function getPathTable" << fKlassName << "() {";
        tab(n+1, *fOut); *fOut << "var pathTable = [];";
        map <string, string>::iterator it;
        map <string, pair<int, Typed::VarType> >& fieldTable = gGlobal->gASMJSVisitor->getFieldTable();
        for (it = json_visitor.fPathTable.begin(); it != json_visitor.fPathTable.end(); it++) {
            pair<int, Typed::VarType> tmp = fieldTable[(*it).first];
            tab(n+1, *fOut); *fOut << "pathTable[\"" << (*it).second << "\"] = " << tmp.first << ";"; 
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
    tab(n+1, *fOut); *fOut << subst("function compute(dsp, $0, inputs, outputs) {", fFullCount);
        tab(n+2, *fOut); *fOut << "dsp = dsp | 0;";
        tab(n+2, *fOut); *fOut << fFullCount << " = " << fFullCount << " | 0;";
        tab(n+2, *fOut); *fOut << "inputs = inputs | 0;";
        tab(n+2, *fOut); *fOut << "outputs = outputs | 0;";
        tab(n+2, *fOut);
        gGlobal->gASMJSVisitor->Tab(n+2);
        // Generates one single scalar loop and put is the the block
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        fComputeBlockInstructions->pushBackInst(loop);
        generateASMBlock(fComputeBlockInstructions);
    tab(n+1, *fOut); *fOut << "}";
}

// Vector
ASMJAVAScriptVectorCodeContainer::ASMJAVAScriptVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), ASMJAVAScriptCodeContainer(name, numInputs, numOutputs, out)
{
    // No array on stack, move all of them in struct
    gGlobal->gMachineMaxStackSize = -1;
}

ASMJAVAScriptVectorCodeContainer::~ASMJAVAScriptVectorCodeContainer()
{}

void ASMJAVAScriptVectorCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("function compute(dsp, $0, inputs, outputs) {", fFullCount);
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
