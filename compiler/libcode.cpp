/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifdef WIN32
#pragma warning(disable : 4996 4146 4244)
#endif

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "Text.hh"
#include "compatibility.hh"
#include "dag_instructions_compiler.hh"
#include "description.hh"
#include "doc.hh"
#include "drawschema.hh"
#include "enrobage.hh"
#include "errormsg.hh"
#include "eval.hh"
#include "exception.hh"
#include "global.hh"
#include "instructions_compiler.hh"
#include "instructions_compiler1.hh"
#include "instructions_compiler_jax.hh"
#include "labels.hh"
#include "libfaust.h"
#include "normalform.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "propagate.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "timing.hh"

#ifdef C_BUILD
#include "c_code_container.hh"
#endif

#ifdef CODEBOX_BUILD
#include "codebox_code_container.hh"
#endif

#ifdef CPP_BUILD
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#endif

#ifdef CMAJOR_BUILD
#include "cmajor_code_container.hh"
#endif

#ifdef CSHARP_BUILD
#include "csharp_code_container.hh"
#endif

#ifdef DLANG_BUILD
#include "dlang_code_container.hh"
#endif

#ifdef FIR_BUILD
#include "fir_code_container.hh"
#endif

#if defined(INTERP_BUILD) || defined(INTERP_COMP_BUILD)
#include "interpreter_code_container.cpp"
#endif

#ifdef JAVA_BUILD
#include "java_code_container.hh"
#endif

#ifdef JAX_BUILD
#include "jax_code_container.hh"
#endif

#ifdef JULIA_BUILD
#include "julia_code_container.hh"
#endif

#ifdef JSFX_BUILD
#include "jsfx_code_container.hh"
#endif

#ifdef LLVM_BUILD
#include "clang_code_container.hh"
#include "llvm_code_container.hh"
#endif

#ifdef OCPP_BUILD
#include "compile_scal.hh"
#include "compile_sched.hh"
#include "compile_vect.hh"
#endif

#ifdef RUST_BUILD
#include "dag_instructions_compiler_rust.hh"
#include "rust_code_container.hh"
#endif

#ifdef TEMPLATE_BUILD
#include "template_code_container.hh"
#endif

#ifdef WASM_BUILD
#include "wasm_code_container.hh"
#include "wast_code_container.hh"
#endif

#ifdef VHDL_BUILD
#include "vhdl/vhdl_producer.hh"
#endif

using namespace std;

/****************************************************************
 Global context
 *****************************************************************/

// File handling
static unique_ptr<ifstream> gEnrobage;
static unique_ptr<ostream>  gHelpers;
static unique_ptr<ostream>  gDst;
static string               gOutpath;
static bool                 gUseCout = false;

// Old CPP compiler
#ifdef OCPP_BUILD
static Compiler* gOldComp = nullptr;
#endif

// FIR container
static InstructionsCompiler* gNewComp   = nullptr;
static CodeContainer*        gContainer = nullptr;

// Shared compilation context
global* gGlobal = nullptr;

string reorganizeCompilationOptions(int argc, const char* argv[]);

static void includeFile(const string& file, ostream& dst)
{
    unique_ptr<ifstream> file_include = openArchStream(file.c_str());
    if (file_include) {
        streamCopyUntilEnd(*file_include.get(), dst);
    }
}

static void injectCode(unique_ptr<ifstream>& enrobage, unique_ptr<ostream>& dst)
{
    // Check if this is a code injection
    if (gGlobal->gInjectFlag) {
        unique_ptr<ifstream> injcode;
        if (gGlobal->gArchFile == "") {
            stringstream error;
            error << "ERROR : no architecture file specified to inject \"" << gGlobal->gInjectFile
                  << "\"" << endl;
            throw faustexception(error.str());
        } else if (!(injcode = openArchStream(gGlobal->gInjectFile.c_str()))) {
            stringstream error;
            error << "ERROR : can't inject \"" << gGlobal->gInjectFile
                  << "\" external code file, file not found\n";
            throw faustexception(error.str());
        } else {
            streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeIntrinsic>>");
            streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeclass>>");
            streamCopyUntilEnd(*injcode.get(), *dst.get());
            streamCopyUntilEnd(*enrobage.get(), *dst.get());
            if (gUseCout) {
                cout << dynamic_cast<ostringstream*>(dst.get())->str();
            }
        }
        throw faustexception("");
    }
}

static bool openOutfile()
{
    /*******************************************************************
     MANDATORY: use ostringstream which is indeed a subclass of ostream
     (otherwise subtle dynamic_cast related crash can occur...)
     *******************************************************************/

    bool res = false;

    if (gGlobal->gOutputFile == "string") {
        gDst = unique_ptr<ostream>(new ostringstream());
    } else if (gGlobal->gOutputFile == "binary") {
        gDst = unique_ptr<ostream>(new ostringstream(ostringstream::out | ostringstream::binary));
    } else if (gGlobal->gOutputFile != "") {
        gOutpath = (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile)
                                               : gGlobal->gOutputFile;
        unique_ptr<ofstream> fdst = unique_ptr<ofstream>(new ofstream(gOutpath.c_str()));
        if (!fdst->is_open()) {
            stringstream error;
            error << "ERROR : file '" << gOutpath << "' cannot be opened\n";
            throw faustexception(error.str());
        } else {
            gDst = std::move(fdst);
        }

    } else {
        // cout will be used
        gDst = unique_ptr<ostream>(new ostringstream());
        res  = true;
    }
    return res;
}

static bool openEnrobagefile()
{
    // Check for architecture file
    if (gGlobal->gArchFile != "") {
        if (!(gEnrobage = openArchStream(gGlobal->gArchFile.c_str()))) {
            stringstream error;
            error << "ERROR : can't open architecture file " << gGlobal->gArchFile << endl;
            throw faustexception(error.str());
        }
        return true;
    } else {
        return false;
    }
}

static void createHelperFile(const string& outpath)
{
    // Additional file with JS code
    if (gGlobal->gOutputFile == "binary") {
        // Nothing
    } else if (gGlobal->gOutputFile != "") {
        string outpath_json;
        bool   res = replaceExtension(outpath, ".json", outpath_json);
        if (res) {
            gHelpers = unique_ptr<ostream>(new ofstream(outpath_json.c_str()));
        } else {
            cerr << "WARNING : cannot generate helper JS file, outpath is incorrect : \"" << outpath
                 << "\"" << endl;
        }
    } else {
        gHelpers = unique_ptr<ostream>(new ostringstream());
    }
}

/****************************************************************
                                MAIN
*****************************************************************/

static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs)
{
    startTiming("evaluation");

    Tree process = evalprocess(expandedDefList);
    if (gGlobal->gErrorCount > 0) {
        stringstream error;
        error << "ERROR : total of " << gGlobal->gErrorCount << " errors during the compilation of "
              << gGlobal->gMasterDocument << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) {
        cout << "process = " << boxpp(process) << ";\n";
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(process) << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDrawPSSwitch) {
        drawSchema(process, subst("$0-ps", gGlobal->makeDrawPathNoExt()).c_str(), "ps");
    }

    if (gGlobal->gDrawSVGSwitch) {
        drawSchema(process, subst("$0-svg", gGlobal->makeDrawPathNoExt()).c_str(), "svg");
    }

    if (gGlobal->gDetailsSwitch) {
        cout << "process has " << inputs(numInputs) << ", and " << outputs(numOutputs) << endl;
    }

    endTiming("evaluation");

    if (gGlobal->gPrintPackageListSwitch){
        cout << "---------------------------\n";
        cout << "List of Package Dependencies :\n";
        cout << "---------------------------\n";
        
        // print the package used to evaluate process
        vector<string> packages = gGlobal->gReader.listPackages();

        for (size_t i = 0; i < packages.size(); i++) {
            cout << packages[i] << endl;
        }

        cout << "---------------------------\n";
        cout << endl;
    }

    if (gGlobal->gPrintFileListSwitch) {
        cout << "---------------------------\n";
        cout << "List of file dependencies :\n";
        cout << "---------------------------\n";
        // print the pathnames of the files used to evaluate process
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (size_t i = 0; i < pathnames.size(); i++) {
            cout << pathnames[i] << endl;
        }
        cout << "---------------------------\n";
        cout << endl;
    }

    return process;
}

static void compileCLLVM(Tree signals, int numInputs, int numOutputs)
{
#ifdef CLANG_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    gContainer = ClangCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }

    // To trigger 'sig.dot' generation
    gNewComp->prepare(signals);
#else
    throw faustexception("ERROR : -lang cllcm not supported since LLVM backend is not built\n");
#endif
}

static void compileLLVM(Tree signals, int numInputs, int numOutputs, bool generate)
{
#ifdef LLVM_BUILD
    gContainer = LLVMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

    // libc functions will be found by the LLVM linker, but not user defined ones...
    gGlobal->gAllowForeignFunction = false;
    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    gGlobal->gUseDefaultSound     = false;

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }

    if (generate) {
        gNewComp->compileMultiSignal(signals);
    } else {
        // To trigger 'sig.dot' generation
        gNewComp->prepare(signals);
    }
#else
    throw faustexception("ERROR : -lang llvm not supported since LLVM backend is not built\n");
#endif
}

static void compileInterp(Tree signals, int numInputs, int numOutputs)
{
#if defined(INTERP_BUILD) || defined(INTERP_COMP_BUILD)
    if (gGlobal->gFloatSize == 1) {
        gContainer = InterpreterCodeContainer<float>::createContainer(gGlobal->gClassName,
                                                                      numInputs, numOutputs);
    } else if (gGlobal->gFloatSize == 2) {
        gContainer = InterpreterCodeContainer<double>::createContainer(gGlobal->gClassName,
                                                                       numInputs, numOutputs);
    } else {
        throw faustexception("ERROR : -quad format not supported in Interp\n");
    }
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable
    // gGlobal->gComputeIOTA       = true;   // Ensure IOTA base fixed delays are computed once

    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer
    gGlobal->gUseDefaultSound = false;

    if (gGlobal->gVectorSwitch) {
        gGlobal->gRemoveVarAddress = true;
        gNewComp                   = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InterpreterInstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception(
        "ERROR : -lang interp not supported since Interpreter backend is not built\n");
#endif
}

static void compileFIR(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef FIR_BUILD
    gContainer =
        FIRCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out, true);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);

    } else if (gGlobal->gFloatSize == 4) {
        // Special compiler for -fx mode
        gNewComp = new InstructionsFXCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang fir not supported since FIR backend is not built\n");
#endif
}

static void compileC(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef C_BUILD
    gContainer = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else if (gGlobal->gFloatSize == 4) {
        // Special compiler for -fx mode
        gNewComp = new InstructionsFXCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang c not supported since C backend is not built\n");
#endif
}

static void compileCodebox(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CODEBOX_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable
    gGlobal->gExtControl           = true;   // Separated control

    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    // "one sample control" model by default;
    gGlobal->gOneSampleControl = true;
    gGlobal->gNeedManualPow = false;  // Standard pow function will be used in pow(x,y) when y in an

    gContainer =
        CodeboxCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
    gNewComp = new InstructionsCompiler(gContainer);

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception(
        "ERROR : -lang codebox not supported since Codebox backend is not built\n");
#endif
}

static void compileCPP(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CPP_BUILD
    gContainer = CPPCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName,
                                                   numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else if (gGlobal->gFloatSize == 4) {
        // Special compiler for -fx mode
        gNewComp = new InstructionsFXCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang cpp not supported since CPP backend is not built\n");
#endif
}

static void compileOCPP(Tree signals, int numInputs, int numOutputs)
{
#ifdef OCPP_BUILD
    if (gGlobal->gSchedulerSwitch) {
        gOldComp = new SchedulerCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs,
                                         numOutputs);
    } else if (gGlobal->gVectorSwitch) {
        gOldComp = new VectorCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs,
                                      numOutputs);
    } else {
        gOldComp = new ScalarCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs,
                                      numOutputs);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gOldComp->setDescription(new Description());
    }
    gOldComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang ocpp not supported since old CPP backend is not built\n");
#endif
}

static void compileRust(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef RUST_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    gContainer =
        RustCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        // Required to not alias mutable buffers
        gGlobal->gRemoveVarAddress = true;
        gNewComp                   = new DAGInstructionsCompilerRust(gContainer);
    } else {
        gNewComp = new InstructionsCompiler1(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang rust not supported since Rust backend is not built\n");
#endif
}

static void compileJava(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JAVA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gContainer = JAVACodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName,
                                                    numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang java not supported since JAVA backend is not built\n");
#endif
}

static void compileJulia(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JULIA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gContainer =
        JuliaCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler1(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang julia not supported since Julia backend is not built\n");
#endif
}

static void compileJSFX(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JSFX_BUILD
    // Backend configuration
    gGlobal->gAllowForeignFunction = true;
    gGlobal->gNeedManualPow        = false;
    gGlobal->gFAUSTFLOAT2Internal  = true;
    // JSFX actually uses the in "inplace" model
    gGlobal->gInPlace = true;
    gContainer =
        JSFXCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang temp not supported since JSFX backend is not built\n");
#endif
}

static void compileJAX(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JAX_BUILD
    gGlobal->gAllowForeignFunction =
        true;  // foreign functions are supported (we use jax.random.PRNG for example)
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer
    gGlobal->gFAUSTFLOAT2Internal = true;
    gContainer = JAXCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompilerJAX(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang jax not supported since JAX backend is not built\n");
#endif
}

static void compileTemplate(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef TEMPLATE_BUILD
    // Backend configuration
    gGlobal->gAllowForeignFunction = true;
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer
    gGlobal->gFAUSTFLOAT2Internal = true;
    gContainer =
        TemplateCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang temp not supported since Template backend is not built\n");
#endif
}

static void compileCSharp(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CSHARP_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gContainer = CSharpCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName,
                                                      numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang csharp not supported since CSharp backend is not built\n");
#endif
}

static void compileCmajor(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CMAJOR_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable
    gGlobal->gBool2Int   = true;  // Cast bool binary operations (comparison operations) to int
    gGlobal->gExtControl = true;  // Separated control

    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    // "one sample control" model by default;
    gGlobal->gOneSampleControl = true;
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer

    gContainer =
        CmajorCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang cmajor not supported since Cmajor backend is not built\n");
#endif
}

static void compileWAST(Tree signals, int numInputs, int numOutputs, ostream* out,
                        const string& outpath)
{
#ifdef WASM_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable

    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    // the 'i' variable used in the scalar loop moves by bytes instead of frames
    gGlobal->gLoopVarInBytes = true;
    gGlobal->gWaveformInDSP  = true;  // waveform are allocated in the DSP and not as global data
    gGlobal->gMachinePtrSize = 4;     // WASM is currently 32 bits
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer
    // gGlobal->gHasTeeLocal = true;       // combined store/load
    gGlobal->gUseDefaultSound = false;

    // This speedup (freeverb for instance) ==> to be done at signal level
    // gGlobal->gComputeIOTA = true;     // Ensure IOTA base fixed delays are computed once

    gContainer = WASTCodeContainer::createContainer(
        gGlobal->gClassName, numInputs, numOutputs, out,
        ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wast-i")));
    createHelperFile(outpath);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang wast not supported since WAST backend is not built\n");
#endif
}

static void compileWASM(Tree signals, int numInputs, int numOutputs, ostream* out,
                        const string& outpath)
{
#ifdef WASM_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable

    // FIR is generated with internal real instead of FAUSTFLOAT (see IB::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    // the 'i' variable used in the scalar loop moves by bytes instead of frames
    gGlobal->gLoopVarInBytes = true;
    gGlobal->gWaveformInDSP  = true;  // waveform are allocated in the DSP and not as global data
    gGlobal->gMachinePtrSize = 4;     // WASM is currently 32 bits
    gGlobal->gNeedManualPow =
        false;  // Standard pow function will be used in pow(x,y) when y in an integer
    // gGlobal->gHasTeeLocal = true;        // combined store/load
    gGlobal->gUseDefaultSound = false;

    // This speedup (freeverb for instance) ==> to be done at signal level
    // gGlobal->gComputeIOTA = true;     // Ensure IOTA base fixed delays are computed once

    gContainer = WASMCodeContainer::createContainer(
        gGlobal->gClassName, numInputs, numOutputs, out,
        ((gGlobal->gOutputLang == "wasm") || (gGlobal->gOutputLang == "wasm-i")));
    createHelperFile(outpath);

    if (gGlobal->gVectorSwitch) {
        gGlobal->gRemoveVarAddress = true;
        gNewComp                   = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang wasm not supported since WASM backend is not built\n");
#endif
}

static void compileDlang(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef DLANG_BUILD
    gContainer = DLangCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName,
                                                     numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        gNewComp = new DAGInstructionsCompiler(gContainer);
    } else {
        gNewComp = new InstructionsCompiler(gContainer);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) {
        gNewComp->setDescription(new Description());
    }
    gNewComp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang dlang not supported since D backend is not built\n");
#endif
}

static void compileVhdl(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef VHDL_BUILD
    signals                = simplifyToNormalForm(signals);
    VhdlProducer vhdl_prod = VhdlProducer(signals, gGlobal->gClassName, numInputs, numOutputs);
    vhdl_prod.optimize();
    if (gGlobal->gVHDLTrace) {
        std::ofstream dot_output("vhdl_graph.dot");
        vhdl_prod.exportGraph(dot_output);
        dot_output.close();
    }
    vhdl_prod.generate(*out);
    if (gUseCout) {
        cout << dynamic_cast<ostringstream*>(out)->str();
    }
#else
    throw faustexception("ERROR : -lang vhdl not supported since VHDL backend is not built\n");
#endif
}

static void generateCodeAux1(unique_ptr<ostream>& helpers, unique_ptr<ifstream>& enrobage,
                             unique_ptr<ostream>& dst)
{
    if (openEnrobagefile()) {
        if (gGlobal->gNamespace != "" && gGlobal->gOutputLang == "cpp") {
            *dst.get() << "namespace " << gGlobal->gNamespace << " {" << endl;
        }
#ifdef DLANG_BUILD
        else if (gGlobal->gOutputLang == "dlang") {
            DLangCodeContainer::printDRecipeComment(*dst.get(), gContainer->getClassName());
            DLangCodeContainer::printDModuleStmt(*dst.get(), gContainer->getClassName());
        }
#endif

        gContainer->printHeader();

        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeIntrinsic>>");
        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeclass>>");

        if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) {
            includeFile("thread.h", *dst.get());
        }

        gContainer->printFloatDef();
        gContainer->produceClass();

        streamCopyUntilEnd(*enrobage.get(), *dst.get());

        if (gGlobal->gSchedulerSwitch) {
            includeFile("scheduler.cpp", *dst.get());
        }

        gContainer->printFooter();

        // Generate factory
        gGlobal->gDSPFactory = gContainer->produceFactory();

        if (gGlobal->gOutputFile == "string") {
            gGlobal->gDSPFactory->write(dst.get(), false, false);
        } else if (gGlobal->gOutputFile == "binary") {
            gGlobal->gDSPFactory->write(dst.get(), true, false);
        } else if (gGlobal->gOutputFile != "") {
            // Binary mode for LLVM backend if output different of 'cout'
            gGlobal->gDSPFactory->write(dst.get(), true, false);
        } else {
            gGlobal->gDSPFactory->write(&cout, false, false);
        }

        if (gGlobal->gNamespace != "" && gGlobal->gOutputLang == "cpp") {
            *dst.get() << "} // namespace " << gGlobal->gNamespace << endl;
        }

    } else {
        gContainer->printHeader();
        gContainer->printFloatDef();
        gContainer->produceClass();
        gContainer->printFooter();

        // Generate factory
        gGlobal->gDSPFactory = gContainer->produceFactory();

        if (gGlobal->gOutputFile == "string") {
            gGlobal->gDSPFactory->write(dst.get(), false, false);
            if (helpers) {
                gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
            }
        } else if (gGlobal->gOutputFile == "binary") {
            gGlobal->gDSPFactory->write(dst.get(), true, false);
            if (helpers) {
                gGlobal->gDSPFactory->writeHelper(helpers.get(), true, false);
            }
        } else if (gGlobal->gOutputFile != "") {
            // Binary mode for LLVM backend if output different of 'cout'
            gGlobal->gDSPFactory->write(dst.get(), true, false);
            if (helpers) {
                gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
            }
        } else {
            gGlobal->gDSPFactory->write(&cout, false, false);
            if (helpers) {
                gGlobal->gDSPFactory->writeHelper(&cout, false, false);
            }
        }
    }
}

#ifdef OCPP_BUILD

static void printHeader(ostream& dst)
{
    // defines the metadata we want to print as comments at the begin of in the C++ file
    set<Tree> selectedKeys;
    selectedKeys.insert(tree("name"));
    selectedKeys.insert(tree("author"));
    selectedKeys.insert(tree("copyright"));
    selectedKeys.insert(tree("license"));
    selectedKeys.insert(tree("version"));

    dst << "//----------------------------------------------------------" << endl;
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (selectedKeys.count(i.first)) {
            dst << "// " << *(i.first);
            const char* sep = ": ";
            for (const auto& j : i.second) {
                dst << sep << *j;
                sep = ", ";
            }
            dst << endl;
        }
    }

    dst << "//" << endl;
    dst << "// Code generated with Faust " << FAUSTVERSION << " (https://faust.grame.fr)" << endl;
    dst << "//----------------------------------------------------------" << endl << endl;
}

static void generateCodeAux2(unique_ptr<ifstream>& enrobage, unique_ptr<ostream>& dst)
{
    printHeader(*dst);
    gOldComp->getClass()->printLibrary(*dst.get());
    gOldComp->getClass()->printIncludeFile(*dst.get());
    gOldComp->getClass()->printAdditionalCode(*dst.get());

    if (gGlobal->gArchFile != "") {
        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeIntrinsic>>");

        if (gGlobal->gSchedulerSwitch) {
            unique_ptr<ifstream> scheduler_include = openArchStream("old-scheduler.cpp");
            if (scheduler_include) {
                streamCopyUntilEnd(*scheduler_include, *dst.get());
            } else {
                throw("ERROR : can't include \"old-scheduler.cpp\", file not found>\n");
            }
        }

        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeclass>>");
        printfloatdef(*dst.get());
        gOldComp->getClass()->println(0, *dst.get());
        streamCopyUntilEnd(*enrobage.get(), *dst.get());

    } else {
        printfloatdef(*dst.get());
        gOldComp->getClass()->println(0, *dst.get());
    }

    /****************************************************************
     9 - generate the task graph file in dot format
     *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
        gOldComp->getClass()->printGraphDotFormat(dotfile);
    }

    if (gGlobal->gOutputFile == "") {
        cout << dynamic_cast<ostringstream*>(dst.get())->str();
    }
}

#endif

static void generateCode(Tree signals, int numInputs, int numOutputs, bool generate)
{
    startTiming("generateCode");

    /****************************************************************
     * create gContainer
     ****************************************************************/

    if (gGlobal->gOutputLang == "cllvm") {
        compileCLLVM(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "llvm") {
        compileLLVM(signals, numInputs, numOutputs, generate);
    } else if (gGlobal->gOutputLang == "interp") {
        compileInterp(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "fir") {
        compileFIR(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "c") {
        compileC(signals, numInputs, numOutputs, gDst.get());
    } else if (startWith(gGlobal->gOutputLang, "codebox")) {
        compileCodebox(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "cpp") {
        compileCPP(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "ocpp") {
        compileOCPP(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "rust") {
        compileRust(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "java") {
        compileJava(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "jax") {
        compileJAX(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "temp") {
        compileTemplate(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "julia") {
        compileJulia(signals, numInputs, numOutputs, gDst.get());
    } else if (startWith(gGlobal->gOutputLang, "jsfx")) {
        compileJSFX(signals, numInputs, numOutputs, gDst.get());
    } else if (gGlobal->gOutputLang == "csharp") {
        compileCSharp(signals, numInputs, numOutputs, gDst.get());
    } else if (startWith(gGlobal->gOutputLang, "cmajor")) {
        compileCmajor(signals, numInputs, numOutputs, gDst.get());
    } else if (startWith(gGlobal->gOutputLang, "wast")) {
        compileWAST(signals, numInputs, numOutputs, gDst.get(), gOutpath);
    } else if (startWith(gGlobal->gOutputLang, "wasm")) {
        compileWASM(signals, numInputs, numOutputs, gDst.get(), gOutpath);
    } else if (startWith(gGlobal->gOutputLang, "dlang")) {
        compileDlang(signals, numInputs, numOutputs, gDst.get());
    } else if (startWith(gGlobal->gOutputLang, "vhdl")) {
        compileVhdl(signals, numInputs, numOutputs, gDst.get());
        // VHDL does not create a compiler, code is already generated here.
        return;
    } else {
        stringstream error;
        error << "ERROR : cannot find backend for "
              << "\"" << gGlobal->gOutputLang << "\"" << endl;
        throw faustexception(error.str());
    }

    /****************************************************************
     * generate output file
     ****************************************************************/

    if (gNewComp) {
        generateCodeAux1(gHelpers, gEnrobage, gDst);
    }
#ifdef OCPP_BUILD
    else if (gOldComp) {
        generateCodeAux2(gEnrobage, gDst);
    }
#endif
    else {
        faustassert(false);
    }

    endTiming("generateCode");
}

static void generateOutputFiles()
{
    /****************************************************************
     1 - generate XML description (if required)
    *****************************************************************/

    if (gGlobal->gPrintXMLSwitch) {
        if (gNewComp) {
            faustassert(gNewComp->getDescription());
            gNewComp->getDescription()->printXML(gContainer->inputs(), gContainer->outputs());
        }
#ifdef OCPP_BUILD
        else if (gOldComp) {
            faustassert(gOldComp->getDescription());
            gOldComp->getDescription()->printXML(gOldComp->getClass()->inputs(),
                                                 gOldComp->getClass()->outputs());
        }
#endif
        else {
            faustassert(false);
        }
    }

    /****************************************************************
     2 - generate documentation from Faust comments (if required)
    *****************************************************************/

    if (gGlobal->gPrintDocSwitch && gGlobal->gLatexDocSwitch) {
        printDoc(subst("$0-mdoc", gGlobal->makeDrawPathNoExt()).c_str(), "tex", FAUSTVERSION);
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
        if (gNewComp) {
            gContainer->printGraphDotFormat(dotfile);
        }
#ifdef OCPP_BUILD
        else if (gOldComp) {
            gOldComp->getClass()->printGraphDotFormat(dotfile);
        }
#endif
        else {
            faustassert(false);
        }
    }
}

static void expandDSPInternalAux(Tree process_tree, int argc, const char* argv[], ostream& out)
{
    // Encode compilation options as a 'declare' : has to be located first in the string
    out << "declare version \"" << FAUSTVERSION << "\";" << endl;
    out << COMPILATION_OPTIONS << reorganizeCompilationOptions(argc, argv) << ';' << endl;

    // Encode all libraries paths as 'declare'
    vector<string> pathnames = gGlobal->gReader.listSrcFiles();
    // Remove DSP filename
    pathnames.erase(pathnames.begin());
    int i = 0;
    for (const auto& it : pathnames) {
        out << "declare library_path" << to_string(i++) << " \"" << it << "\";" << endl;
    }

    gGlobal->printDeclareHeader(out);
    boxppShared(process_tree, out);
}

static void* expandDSPInternal(void* arg)
{
    try {
        CallContext* context     = static_cast<CallContext*>(arg);
        string       name_app    = context->fNameApp;
        string       dsp_content = context->fDSPContent;
        int          argc        = context->fArgc;
        const char** argv        = context->fArgv;

        /****************************************************************
         1 - process command line
        *****************************************************************/
        gGlobal->reset();
        gGlobal->initDirectories(argc, argv);
        gGlobal->processCmdline(argc, argv);

        /****************************************************************
         2 - parse source files
        *****************************************************************/
        if (dsp_content != "") {
            gGlobal->gInputString = dsp_content;
            gGlobal->gInputFiles.push_back(name_app);
        }
        gGlobal->initDocumentNames();

        gGlobal->parseSourceFiles();

        /****************************************************************
         3 - evaluate 'process' definition
        *****************************************************************/
        int  numInputs;
        int  numOutputs;
        Tree processTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);

        stringstream out;
        expandDSPInternalAux(processTree, argc, argv, out);
        context->fRes = out.str();
        return nullptr;

    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

static void* evaluateBlockDiagram2(void* arg)
{
    CallContext* context = static_cast<CallContext*>(arg);
    try {
        context->fTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, context->fNumInputs,
                                              context->fNumOutputs);
        return nullptr;
    } catch (faustexception& e) {
        context->fTree         = nullptr;
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

LIBFAUST_API Tree DSPToBoxes(const string& name_app, const string& dsp_content, int argc,
                             const char* argv[], int* inputs, int* outputs, string& error_msg)
{
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv

    /****************************************************************
     1 - process command line
     *****************************************************************/
    gGlobal->reset();
    gGlobal->initDirectories(argc1, argv1);
    gGlobal->processCmdline(argc1, argv1);

    faust_alarm(gGlobal->gTimeout);

    /****************************************************************
     2 - parse source files
     *****************************************************************/
    if (dsp_content.c_str()) {
        gGlobal->gInputString = dsp_content;
        gGlobal->gInputFiles.push_back(name_app);
    }
    gGlobal->initDocumentNames();

    try {
        gGlobal->parseSourceFiles();
        error_msg = "";
    } catch (faustexception& e) {
        error_msg = e.what();
        return nullptr;
    }

    /****************************************************************
     3 - evaluate 'process' definition
     *****************************************************************/
    CallContext context;
    callFun(evaluateBlockDiagram2, &context);
    if (context.fTree) {
        *inputs  = context.fNumInputs;
        *outputs = context.fNumOutputs;
        return context.fTree;
    } else {
        return nullptr;
    }
}

static void* createFactoryAux1(void* arg)
{
    try {
        CallContext* context     = static_cast<CallContext*>(arg);
        string       name_app    = context->fNameApp;
        string       dsp_content = context->fDSPContent;
        int          argc        = context->fArgc;
        const char** argv        = context->fArgv;
        bool         generate    = context->fGenerate;

        /****************************************************************
         1 - process command line
        *****************************************************************/
        gGlobal->reset();
        gGlobal->initDirectories(argc, argv);
        gGlobal->processCmdline(argc, argv);
        gGlobal->printDirectories();

        faust_alarm(gGlobal->gTimeout);

        // Open output file
        gUseCout = openOutfile();
        // Open enrobage file
        openEnrobagefile();

        /****************************************************************
         1.5 - Check and open some input files
        *****************************************************************/
        // Check for injected code (before checking for architectures)
        injectCode(gEnrobage, gDst);

        /****************************************************************
         2 - parse source files
        *****************************************************************/
        if (dsp_content != "") {
            gGlobal->gInputString = dsp_content;
            gGlobal->gInputFiles.push_back(name_app);
        }
        gGlobal->initDocumentNames();

        gGlobal->parseSourceFiles();

        /****************************************************************
         3 - evaluate 'process' definition
        *****************************************************************/
        int  numInputs;
        int  numOutputs;
        Tree processTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);
        if (numOutputs == 0) {
            throw faustexception("ERROR : the Faust program has no output signal\n");
        }

        /****************************************************************
         3.1 - possibly expand the DSP and return
         *****************************************************************/
        if (gGlobal->gExportDSP) {
            ofstream out(gOutpath.c_str());
            expandDSPInternalAux(processTree, argc, argv, out);
            return nullptr;
        }

        /****************************************************************
         4 - compute output signals of 'process'
        *****************************************************************/
        startTiming("propagation");

        Tree lsignals = boxPropagateSig(gGlobal->nil, processTree, makeSigInputList(numInputs));

        if (gGlobal->gDetailsSwitch) {
            cout << "output signals are : " << endl;
            printSignal(lsignals, stdout);
            cout << endl << ppsig(lsignals) << endl;
            cout << "\n\n";
        }

        endTiming("propagation");

        /*************************************************************************
        5 - preparation of the signal tree and translate output signals
        **************************************************************************/
        generateCode(lsignals, numInputs, numOutputs, generate);

        /****************************************************************
         6 - generate xml description, documentation or dot files
        *****************************************************************/
        generateOutputFiles();

        return nullptr;

    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

static void* createFactoryAux2(void* arg)
{
    // Keep the maximum index of inputs signals
    struct MaxInputsCounter : public SignalVisitor {
        int fMaxInputs = 0;

        MaxInputsCounter(Tree L)
        {
            // L is in normal form
            visitRoot(L);
        }

        void visit(Tree sig)
        {
            int input;
            if (isSigInput(sig, &input)) {
                fMaxInputs = std::max(fMaxInputs, input + 1);
            } else {
                SignalVisitor::visit(sig);
            }
        }
    };

    try {
        CallContext* context  = static_cast<CallContext*>(arg);
        string       name_app = context->fNameApp;
        Tree         signals1 = context->fTree;
        int          argc     = context->fArgc;
        const char** argv     = context->fArgv;
        bool         generate = context->fGenerate;

        Tree             signals2 = simplifyToNormalForm(signals1);
        MaxInputsCounter counter(signals2);
        int              numInputs  = counter.fMaxInputs;
        int              numOutputs = context->fNumOutputs;

        /****************************************************************
         1 - process command line
         *****************************************************************/
        gGlobal->reset();
        gGlobal->initDirectories(argc, argv);
        gGlobal->processCmdline(argc, argv);

        gGlobal->initDocumentNames();

        // Open output file
        openOutfile();

        /*************************************************************************
         5 - preparation of the signal tree and translate output signals
         **************************************************************************/
        gGlobal->gMetaDataSet[tree("name")].insert(tree(quote(name_app)));
        generateCode(signals2, numInputs, numOutputs, generate);

        return nullptr;

    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

// ============
// Backend API
// ============

dsp_factory_base* createFactory(const string& name_app, const string& dsp_content, int argc,
                                const char* argv[], string& error_msg, bool generate)
{
    gGlobal = nullptr;
    global::allocate();

    // Threaded call
    CallContext context;
    context.fNameApp    = name_app;
    context.fDSPContent = dsp_content;
    context.fArgc       = argc;
    context.fArgv       = argv;
    context.fGenerate   = generate;
    callFun(createFactoryAux1, &context);
    dsp_factory_base* factory = gGlobal->gDSPFactory;
    error_msg                 = gGlobal->gErrorMessage;

    global::destroy();
    return factory;
}

dsp_factory_base* createFactory(const string& name_app, tvec signals, int argc, const char* argv[],
                                string& error_msg)
{
    Tree outputs = listConvert(signals);
    // Threaded call
    CallContext context;
    context.fNameApp    = name_app;
    context.fTree       = outputs;
    context.fArgc       = argc;
    context.fArgv       = argv;
    context.fNumOutputs = signals.size();
    context.fGenerate   = true;
    callFun(createFactoryAux2, &context);
    error_msg = gGlobal->gErrorMessage;
    return gGlobal->gDSPFactory;
}

string expandDSP(const string& name_app, const string& dsp_content, int argc, const char* argv[],
                 string& sha_key, string& error_msg)
{
    gGlobal = nullptr;
    global::allocate();

    // Threaded call
    CallContext context;
    context.fNameApp    = name_app;
    context.fDSPContent = dsp_content;
    context.fArgc       = argc;
    context.fArgv       = argv;
    callFun(expandDSPInternal, &context);
    string res = context.fRes;
    sha_key    = generateSHA1(res);
    error_msg  = gGlobal->gErrorMessage;

    global::destroy();
    return res;
}
