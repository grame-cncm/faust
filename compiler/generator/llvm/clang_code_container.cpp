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

#include "compatibility.hh"

#if CLANG_BUILD

#include "clang_code_container.hh"

#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Tool.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/FrontendDiagnostic.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>

#include <llvm/Support/Host.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <llvm/Bitcode/ReaderWriter.h>
#if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40)
#include <llvm/IR/Module.h>
#else
#include <llvm/Module.h>
#endif

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40)
#include <llvm/Support/FileSystem.h>
#define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
#define sysfs_binary_flag sys::fs::F_Binary
#else
#define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

using namespace std;
using namespace llvm;
using namespace clang;
using namespace clang::driver;

#include "CInterface_exp.h"
//#include "scheduler_exp.h"

// Helper functions
bool linkModules(Module* dst, Module* src, char* error_msg);
Module* loadModule(const string& module_name, llvm::LLVMContext* context);
Module* linkAllModules(llvm::LLVMContext* context, Module* dst, char* error);

#define FAUST_FILENAME "/var/tmp/FaustLLVM.c"

ClangCodeContainer::ClangCodeContainer(const string& name, int numInputs, int numOutputs)
{
    fOut = new ofstream(getTempName());
   
    if (gGlobal->gFloatSize == 2) {
        *fOut << "#define FAUSTFLOAT double" << "\n\n";
    }
    
    *fOut << ___architecture_faust_gui_CUI_h;
    //fOut << ___architecture_scheduler_cpp;
    *fOut << endl;
    *fOut << "#define max(a,b) ((a < b) ? b : a)" << endl;
    *fOut << "#define min(a,b) ((a < b) ? a : b)" << "\n\n";
    printHeader(*fOut);
  
    fContainer = CCodeContainer::createContainer(name, numInputs, numOutputs, fOut);
    
    if (gGlobal->gVectorSwitch) {
        fCompiler = new DAGInstructionsCompiler(fContainer);
    } else {
        fCompiler = new InstructionsCompiler(fContainer);
    }
    
    if (gGlobal->gPrintXMLSwitch) fCompiler->setDescription(new Description());
    if (gGlobal->gPrintDocSwitch) fCompiler->setDescription(new Description());
}

ClangCodeContainer::~ClangCodeContainer()
{
    delete fOut;
}

LLVMResult* ClangCodeContainer::produceModule(Tree signals, const string& filename)
{
    // Compile DSP and generate C code
    fCompiler->compileMultiSignal(signals);
    fContainer->produceClass();
    
#if defined(LLVM_34) || defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40)
    // Compile it with 'clang'
    IntrusiveRefCntPtr<DiagnosticOptions> DiagOpts = new DiagnosticOptions();
    TextDiagnosticPrinter* DiagClient = new TextDiagnosticPrinter(llvm::errs(), &*DiagOpts);
    
    IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
    DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagClient);
    Driver TheDriver("", llvm::sys::getProcessTriple(), "a.out", Diags);
    TheDriver.setTitle("clang interpreter");
    
    int argc = 2;
    const char* argv[argc + 1];
    argv[0] = "clang";
    argv[1] = getTempName();
    argv[argc] = 0;  // NULL terminated argv
    SmallVector<const char*, 16> Args(argv, argv + argc);
    Args.push_back("-fsyntax-only");
    //Args.push_back("-O3");
    Args.push_back("-ffast-math");
      
    list<string>::iterator it;
    for (it = gGlobal->gImportDirList.begin(); it != gGlobal->gImportDirList.end(); it++) {
        string path = "-I" + (*it);
        Args.push_back(strdup(path.c_str()));
    }
    
    OwningPtr<Compilation> C(TheDriver.BuildCompilation(Args));
    if (!C) {
        return NULL;
    }

    const driver::JobList &Jobs = C->getJobs();
    if (Jobs.size() != 1 || !isa<driver::Command>(*Jobs.begin())) {
        SmallString<256> Msg;
        llvm::raw_svector_ostream OS(Msg);
        Jobs.Print(OS, "; ", true);
        Diags.Report(diag::err_fe_expected_compiler_job) << OS.str();
        return NULL;
    }

    const driver::Command* Cmd = cast<driver::Command>(*Jobs.begin());
    if (llvm::StringRef(Cmd->getCreator().getName()) != "clang") {
        Diags.Report(diag::err_fe_expected_clang_command);
        return NULL;
    }

    // Initialize a compiler invocation object from the clang (-cc1) arguments.
    const driver::ArgStringList &CCArgs = Cmd->getArguments();
    OwningPtr<CompilerInvocation> CI(new CompilerInvocation);
    CompilerInvocation::CreateFromArgs(*CI, const_cast<const char**>(CCArgs.data()),
                                            const_cast<const char**>(CCArgs.data()) + CCArgs.size(), Diags);

    // Create a compiler instance to handle the actual work.
    CompilerInstance Clang;
    Clang.setInvocation(CI.take());

    // Create the compilers actual diagnostics engine.
    Clang.createDiagnostics();
    if (!Clang.hasDiagnostics()) {
        return NULL;
    }
    
    CompilerInvocation::setLangDefaults(Clang.getLangOpts(), IK_CXX, LangStandard::lang_unspecified);

    // Create and execute the frontend to generate an LLVM bitcode module.
    OwningPtr<CodeGenAction> Act(new EmitLLVMOnlyAction());
    if (!Clang.ExecuteAction(*Act)) {
        return NULL;
    }

    // Get the compiled LLVM module
    if (llvm::Module* Module = Act->takeModule()) {
        LLVMResult* result = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
        result->fModule = Module;
        result->fContext = Act->takeLLVMContext();
        
        // Link LLVM modules defined in 'ffunction'
        set<string> S;
        set<string>::iterator f;
        char error_msg[512];
        
        collectLibrary(S);
        if (S.size() > 0) {
            for (f = S.begin(); f != S.end(); f++) {
                string module_name = unquote(*f);
                if (endWith(module_name, ".bc") || endWith(module_name, ".ll")) {
                    Module* module = loadModule(module_name, result->fContext);
                    if (module) {
                        bool res = linkModules(result->fModule, module, error_msg);
                        if (!res) printf("Link LLVM modules %s\n", error_msg);
                    }
                }
            }
        }
        
        // Possibly link with additional LLVM modules
        char error[256];
        if (!linkAllModules(result->fContext, result->fModule, error)) {
            stringstream llvm_error;
            llvm_error << "ERROR : " << error << endl;
            throw faustexception(llvm_error.str());
        }
        
        // Keep source files pathnames
        result->fPathnameList = gGlobal->gReader.listSrcFiles();
        
        // Possibly output file
        if (filename != "") {
            std::string err;
            raw_fd_ostream out(filename.c_str(), err, sysfs_binary_flag);
            WriteBitcodeToFile(result->fModule, out);
        }
        
        return result;
    } else {
        return NULL;
    }
#else
    return NULL;
#endif
}

CodeContainer* ClangCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    return new ClangCodeContainer(name, numInputs, numOutputs);
}

#endif // CLANG_BUILD
