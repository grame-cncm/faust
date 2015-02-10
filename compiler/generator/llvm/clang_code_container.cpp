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

#include "clang_code_container.hh"
#include "dag_instructions_compiler.hh"

#include <llvm/Support/raw_ostream.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/LLVMContext.h>

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticBuffer.h>

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

ClangCodeContainer::ClangCodeContainer(const string& name, int numInputs, int numOutputs)
{
    fResult = static_cast<LLVMResult*>(calloc(1, sizeof(LLVMResult)));
    fResult->fContext = new LLVMContext();
    
    fContainer = CPPCodeContainer::createContainer(name, "", numInputs, numOutputs, &fOut);
}

ClangCodeContainer::ClangCodeContainer(const string& name, int numInputs, int numOutputs, LLVMResult* result)
{}

ClangCodeContainer::~ClangCodeContainer()
{
    // fContainer is Garbageable
}

LLVMResult* ClangCodeContainer::produceModule(Tree signals, const string& filename)
{
    InstructionsCompiler* comp;

    if (gGlobal->gVectorSwitch) {
        comp = new DAGInstructionsCompiler(fContainer);
    } else {
        comp = new InstructionsCompiler(fContainer);
    }
    
    printf("ClangCodeContainer::produceModule\n");
    
    comp->compileMultiSignal(signals);
    fContainer->produceClass();
    
    cout << fOut.str();
    
    llvm::MemoryBuffer * buffer = llvm::MemoryBuffer::getMemBufferCopy(fOut.str(), "src");
    
    /*
    CompilerInstance CI;
	CI.createDiagnostics(0, NULL);
	Diagnostic & Diags = CI.getDiagnostics();	
	TextDiagnosticBuffer * client = new TextDiagnosticBuffer;
	Diags.setClient(client);
	CompilerInvocation::CreateFromArgs(CI.getInvocation(), NULL, NULL, Diags);
	
	LangOptions& lang = CI.getInvocation().getLangOpts();
	// The fateful line
	lang.CPlusPlus = options.CPlusPlus;
	lang.Bool = 1;
	lang.BCPLComment = 1;
	lang.RTTI = 0;
	lang.PICLevel = 1;
	lang.InlineVisibilityHidden = 1;
    
    CI.createSourceManager();
	CI.getSourceManager().createMainFileIDForMemBuffer(buffer);
	CI.createFileManager();
    
    // Create the target instance.
    CI.setTarget(TargetInfo::CreateTargetInfo(CI.getDiagnostics(), CI.getTargetOpts()));
    
    CI.createPreprocessor();
	Preprocessor &PP = CI.getPreprocessor();
    
    PP.getBuiltinInfo().InitializeBuiltins(PP.getIdentifierTable(), PP.getLangOptions().NoBuiltin);
    
    CI.createASTContext();
    
    CodeGenOptions CGO;
    CGO.CXAAtExit = 0;
    
    CodeGenerator* codegen = CreateLLVMCodeGen(Diags, "FaustModule", CGO, fResult->fContext);
    
    ParseAST(CI.getPreprocessor(),
			codegen,
			CI.getASTContext(),
			// PrintState= false,
			true,
			0);
	
	llvm::Module* module = codegen->ReleaseModule();

    module->dump();
    
    */
    
    if (filename != "") {
        std::string err;
        raw_fd_ostream out(filename.c_str(), err, sysfs_binary_flag);
        WriteBitcodeToFile(fResult->fModule, out);
    }
    
    LLVMResult* result = fResult;
    fResult = NULL; // Will be deallocated later on in the compilation chain...
    return result;

}

CodeContainer* ClangCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{}

CodeContainer* ClangCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    return new ClangCodeContainer(name, numInputs, numOutputs);
}
