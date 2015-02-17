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

#if LLVM_BUILD

#include "clang_code_container.hh"

#include <llvm/Support/raw_ostream.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/LLVMContext.h>

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticBuffer.h>

#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Tool.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/FrontendDiagnostic.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>

#include <llvm/ADT/OwningPtr.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#if defined(LLVM_35)
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

ClangCodeContainer::ClangCodeContainer(const string& name, int numInputs, int numOutputs)
    :fOut("/var/tmp/FaustLLVM.c")
{
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fContext = new LLVMContext();
    
    fOut << "#include </usr/local/include/faust/gui/CUI.h>" << "\n\n";
    
    fOut << "#define max(a,b) ((a < b) ? b : a)" << endl;
    fOut << "#define min(a,b) ((a < b) ? a : b)" << "\n\n";
    
    printheader(fOut);
       
    fContainer = CCodeContainer::createContainer(name, numInputs, numOutputs, &fOut);
    
    if (gGlobal->gVectorSwitch) {
        fCompiler = new DAGInstructionsCompiler(fContainer);
    } else {
        fCompiler = new InstructionsCompiler(fContainer);
    }
    
    if (gGlobal->gPrintXMLSwitch) fCompiler->setDescription(new Description());
    if (gGlobal->gPrintDocSwitch) fCompiler->setDescription(new Description());
}

ClangCodeContainer::~ClangCodeContainer()
{}

LLVMResult* ClangCodeContainer::produceModule(Tree signals, const string& filename)
{
    fCompiler->compileMultiSignal(signals);
    fContainer->produceClass();
    
    int argc = 2;
    const char* argv[2];
    argv[1] = "/var/tmp/FaustLLVM.c";
    
    IntrusiveRefCntPtr<DiagnosticOptions> DiagOpts = new DiagnosticOptions();
    TextDiagnosticPrinter* DiagClient = new TextDiagnosticPrinter(llvm::errs(), &*DiagOpts);

    IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
    DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagClient);
    Driver TheDriver("", llvm::sys::getProcessTriple(), "a.out", Diags);
    TheDriver.setTitle("clang interpreter");

    // FIXME: This is a hack to try to force the driver to do something we can
    // recognize. We need to extend the driver library to support this use model
    // (basically, exactly one input, and the operation mode is hard wired).
    SmallVector<const char*, 16> Args(argv, argv + argc);
    Args.push_back("-fsyntax-only");
    //Args.push_back("-O3");
    //Args.push_back("-ffast-math");
    //Args.push_back("-fslp-vectorize");
    //Args.push_back("-fslp-vectorize-aggressive");
    OwningPtr<Compilation> C(TheDriver.BuildCompilation(Args));
    if (!C) {
        return NULL;
    }

    // FIXME: This is copied from ASTUnit.cpp; simplify and eliminate.

    // We expect to get back exactly one command job, if we didn't something
    // failed. Extract that job from the compilation.
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

    // Create and execute the frontend to generate an LLVM bitcode module.
    OwningPtr<CodeGenAction> Act(new EmitLLVMOnlyAction(fResult->fContext));
    if (!Clang.ExecuteAction(*Act)) {
        return NULL;
    }

    if (llvm::Module* Module = Act->takeModule()) {
        fResult->fModule = Module;
    }
  
    if (filename != "") {
        std::string err;
        raw_fd_ostream out(filename.c_str(), err, sysfs_binary_flag);
        WriteBitcodeToFile(fResult->fModule, out);
    }
    
    LLVMResult* result = fResult;
    fResult = NULL; // Will be deallocated later on in the compilation chain...
    return result;
}

CodeContainer* ClangCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    return new ClangCodeContainer(name, numInputs, numOutputs);
}

#endif // LLVM_BUILD