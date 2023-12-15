/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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
#pragma warning(disable : 4141 4244 4291 4146 4267 4275 4624 4800)
#endif

#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Text.hh"
#include "compatibility.hh"
#include "global.hh"
#include "libfaust.h"
#include "llvm_dynamic_dsp_aux.hh"
#include "rn_base64.h"
#include "lock_api.hh"

#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/ObjectCache.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormattedStream.h>
#if LLVM_VERSION_MAJOR >= 16
#include <llvm/TargetParser/Host.h>
#else
#include <llvm/Support/Host.h>
#endif
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/IPO.h>
#if LLVM_VERSION_MAJOR < 17
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#endif
#include <llvm/Transforms/IPO/AlwaysInliner.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Analysis/TargetLibraryInfo.h>
#include <llvm/Analysis/TargetTransformInfo.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>

#if LLVM_VERSION_MAJOR >= 17
#include <llvm/Analysis/LoopAnalysisManager.h>
#include <llvm/Analysis/CGSCCPassManager.h>
#include <llvm/Passes/PassBuilder.h>
#endif

// Disappears in LLVM 15
#if LLVM_VERSION_MAJOR >= 14
#include <llvm/MC/TargetRegistry.h>
#else
#include <llvm/Support/TargetRegistry.h>
#endif

#if LLVM_VERSION_MAJOR >= 10
#include <llvm/InitializePasses.h>
#include <llvm/Support/CodeGen.h>
#endif

using namespace llvm;
using namespace std;

#define dumpLLVM(val)                    \
    {                                    \
        string             res;          \
        raw_string_ostream out_str(res); \
        out_str << *val;                 \
        cout << out_str.str() << endl;   \
    }

static void splitTarget(const string& target, string& triple, string& cpu)
{
    size_t pos1 = target.find_first_of(':');
    triple      = target.substr(0, pos1);
    if (pos1 != string::npos) {
        cpu = target.substr(pos1 + 1);
    }
}

static string getParam(int argc, const char* argv[], const string& param, const string& def)
{
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == param) return argv[i + 1];
    }
    return def;
}

static Module* ParseBitcodeFile(MEMORY_BUFFER buffer, LLVMContext& context, string& error_msg)
{
    Expected<unique_ptr<Module>> module_or_err = parseBitcodeFile(buffer, context);
    if (error_code ec = errorToErrorCode(module_or_err.takeError())) {
        error_msg = "ERROR : failed to read bitcode\n";
        return nullptr;
    } else {
        return module_or_err.get().release();
    }
}

void llvm_dynamic_dsp_factory_aux::write(ostream* out, bool binary, bool small)
{
    string res;
    raw_string_ostream out_str(res);
    if (binary) {
#if LLVM_VERSION_MAJOR >= 8
        WriteBitcodeToFile(*fModule, out_str);
#else
        WriteBitcodeToFile(fModule, out_str);
#endif
    } else {
        out_str << *fModule;
    }
    *out << out_str.str();
}

// Bitcode
string llvm_dynamic_dsp_factory_aux::writeDSPFactoryToBitcode()
{
    string res;
    raw_string_ostream out(res);
#if LLVM_VERSION_MAJOR >= 8
    WriteBitcodeToFile(*fModule, out);
#else
    WriteBitcodeToFile(fModule, out);
#endif
    out.flush();
    return base64_encode(res);
}

bool llvm_dynamic_dsp_factory_aux::writeDSPFactoryToBitcodeFile(const string& bit_code_path)
{
    STREAM_ERROR err;
    raw_fd_ostream out(bit_code_path.c_str(), err, sysfs_binary_flag);
    if (err) {
        cerr << "ERROR : writeDSPFactoryToBitcodeFile could not open file : " << err.message();
        return false;
    }
#if LLVM_VERSION_MAJOR >= 8
    WriteBitcodeToFile(*fModule, out);
#else
    WriteBitcodeToFile(fModule, out);
#endif
    return true;
}

// IR
string llvm_dynamic_dsp_factory_aux::writeDSPFactoryToIR()
{
    string             res;
    raw_string_ostream out(res);
    PASS_MANAGER       PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
    return res;
}

bool llvm_dynamic_dsp_factory_aux::writeDSPFactoryToIRFile(const string& ir_code_path)
{
    STREAM_ERROR   err;
    raw_fd_ostream out(ir_code_path.c_str(), err, sysfs_binary_flag);
    if (err) {
        cerr << "ERROR : writeDSPFactoryToBitcodeFile could not open file : " << err.message();
        return false;
    }
    PASS_MANAGER PM;
    PM.add(llvmcreatePrintModulePass(out));
    PM.run(*fModule);
    out.flush();
    return true;
}

#if LLVM_VERSION_MAJOR < 17
/// AddOptimizationPasses - This routine adds optimization passes
/// based on selected optimization level, OptLevel. This routine
/// duplicates llvm-gcc behaviour.
///
/// OptLevel - Optimization Level
static void AddOptimizationPasses(PassManagerBase& MPM, FUNCTION_PASS_MANAGER& FPM, unsigned OptLevel,
                                  unsigned SizeLevel)
{
    FPM.add(createVerifierPass());  // Verify that input is correct

    PassManagerBuilder Builder;
    Builder.OptLevel  = OptLevel;
    Builder.SizeLevel = SizeLevel;

    if (OptLevel > 1) {
        unsigned Threshold = 225;
        if (SizeLevel == 1) {  // -Os
            Threshold = 75;
        } else if (SizeLevel == 2) {  // -Oz
            Threshold = 25;
        }
        if (OptLevel > 2) {
            Threshold = 275;
        }
    #if LLVM_VERSION_MAJOR < 17
        Builder.Inliner = createFunctionInliningPass(Threshold);
    #endif
    } else {
        Builder.Inliner = createAlwaysInlinerLegacyPass();
    }

    Builder.DisableUnrollLoops = (OptLevel == 0);

    // Add auto-vectorization passes
    if (OptLevel > 3) {
        Builder.LoopVectorize = true;
        Builder.SLPVectorize  = true;
    }

    Builder.populateFunctionPassManager(FPM);
    Builder.populateModulePassManager(MPM);
}
#endif

bool llvm_dynamic_dsp_factory_aux::initJIT(string& error_msg)
{
    startTiming("initJIT");
    faustassert(fModule);

#ifdef LLVM_BUILD_UNIVERSAL
    // For multiple target support
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();
    InitializeAllAsmParsers();
#endif

    // For host target support
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // For ObjectCache to work...
    LLVMLinkInMCJIT();

    EngineBuilder builder((unique_ptr<Module>(fModule)));

    builder.setOptLevel(CodeGenOpt::Aggressive);
    builder.setEngineKind(EngineKind::JIT);

    string buider_error;
    builder.setErrorStr(&buider_error);
  
    string triple, cpu;
    splitTarget(fTarget, triple, cpu);
    fModule->setTargetTriple(triple);

    builder.setMCPU((cpu == "") ? sys::getHostCPUName() : StringRef(cpu));
    TargetOptions targetOptions;

    // -fastmath is activated at IR level, and has to be setup at JIT level also
    targetOptions.AllowFPOpFusion       = FPOpFusion::Fast;
    targetOptions.UnsafeFPMath          = true;
    targetOptions.NoInfsFPMath          = true;
    targetOptions.NoNaNsFPMath          = true;
    targetOptions.GuaranteedTailCallOpt = true;
    targetOptions.NoTrappingFPMath      = true;
    
#if LLVM_VERSION_MAJOR >= 9
    targetOptions.NoSignedZerosFPMath   = true;
#endif
    
#if LLVM_VERSION_MAJOR >= 11
    targetOptions.setFPDenormalMode(DenormalMode::getIEEE());
#else
    targetOptions.FPDenormalMode = FPDenormal::IEEE;
#endif
    
    targetOptions.GuaranteedTailCallOpt = true;
    
    string debug_var = (getenv("FAUST_DEBUG")) ? string(getenv("FAUST_DEBUG")) : "";
    if ((debug_var != "") && (debug_var.find("FAUST_LLVM3") != string::npos)) {
#if LLVM_VERSION_MAJOR < 12
        targetOptions.PrintMachineCode = true;
#endif
    }

    builder.setTargetOptions(targetOptions);
    TargetMachine* tm = builder.selectTarget();

    fJIT = builder.create(tm);
    if (!fJIT) {
        endTiming("initJIT");
        error_msg = "ERROR : cannot create LLVM JIT : " + buider_error + "\n";
        return false;
    }

    int optlevel = getOptlevel();

    if ((optlevel == -1) || (fOptLevel > optlevel)) {
        
#if LLVM_VERSION_MAJOR >= 17
        // See: https://llvm.org/docs/NewPassManager.html
        
        // Create the analysis managers.
        LoopAnalysisManager LAM;
        FunctionAnalysisManager FAM;
        CGSCCAnalysisManager CGAM;
        ModuleAnalysisManager MAM;
        
        // Create the new pass manager builder.
        // Take a look at the PassBuilder constructor parameters for more
        // customization, e.g. specifying a TargetMachine or various debugging
        // options.
        PassBuilder PB;
        
        // Register all the basic analyses with the managers.
        PB.registerModuleAnalyses(MAM);
        PB.registerCGSCCAnalyses(CGAM);
        PB.registerFunctionAnalyses(FAM);
        PB.registerLoopAnalyses(LAM);
        PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);
        
        // Create the pass manager.
        OptimizationLevel opt_table[] = {OptimizationLevel::O0, OptimizationLevel::O1, OptimizationLevel::O2, OptimizationLevel::O3};
        fOptLevel = std::min(fOptLevel, 3);
        ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(opt_table[fOptLevel]);
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
            dumpLLVM(fModule);
        }
        
        // Optimize the IR
        MPM.run(*fModule, MAM);
        
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
            dumpLLVM(fModule);
        }
#else
        PASS_MANAGER          pm;
        FUNCTION_PASS_MANAGER fpm(fModule);

        // Code taken from opt.cpp
        TargetLibraryInfoImpl TLII(Triple(fModule->getTargetTriple()));
        pm.add(new TargetLibraryInfoWrapperPass(TLII));
        fModule->setDataLayout(fJIT->getDataLayout());

        // Add internal analysis passes from the target machine (mandatory for vectorization to work)
        // Code taken from opt.cpp
        pm.add(createTargetTransformInfoWrapperPass(tm->getTargetIRAnalysis()));

        if (fOptLevel > 0) {
            AddOptimizationPasses(pm, fpm, fOptLevel, 0);
        }

        if ((debug_var != "") && (debug_var.find("FAUST_LLVM1") != string::npos)) {
            dumpLLVM(fModule);
        }

        fpm.doInitialization();
        for (Module::iterator F = fModule->begin(), E = fModule->end(); F != E; ++F) {
            fpm.run(*F);
        }
        fpm.doFinalization();
        pm.add(createVerifierPass());

        if ((debug_var != "") && (debug_var.find("FAUST_LLVM4") != string::npos)) {
            // TODO
            // tm->addPassesToEmitFile(pm, fouts(), TargetMachine::CGFT_AssemblyFile, true);
        }

        // Now that we have all of the passes ready, run them.
        pm.run(*fModule);
        if ((debug_var != "") && (debug_var.find("FAUST_LLVM2") != string::npos)) {
            dumpLLVM(fModule);
        }
#endif
    }

    fObjectCache = new FaustObjectCache();
    fJIT->setObjectCache(fObjectCache);
    return initJITAux();
}

// Bitcode <==> string
static llvm_dsp_factory* readDSPFactoryFromBitcodeAux(MEMORY_BUFFER buffer, const string& target, string& error_msg,
                                                      int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;

    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        try {
            LLVMContext* context = new LLVMContext();
            Module*      module  = ParseBitcodeFile(buffer, *context, error_msg);
            if (!module) return nullptr;
            llvm_dynamic_dsp_factory_aux* factory_aux
                = new llvm_dynamic_dsp_factory_aux(sha_key, module, context, target, opt_level);
            if (factory_aux->initJIT(error_msg)) {
                llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
                llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                return factory;
            } else {
                delete factory_aux;
                return nullptr;
            }
        } catch (faustexception& e) {
            error_msg = e.what();
            return nullptr;
        }
    }
}

// Object code <==> file (taken from toy.cpp)
bool llvm_dynamic_dsp_factory_aux::writeDSPFactoryToObjectcodeFileAux(const string& object_code_path)
{
    auto TargetTriple = sys::getDefaultTargetTriple();
    fModule->setTargetTriple(TargetTriple);
    string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << "ERROR : " << Error;
        return false;
    }

    StringRef CPU = sys::getHostCPUName();
    string Features;
    TargetOptions opt;
#if LLVM_VERSION_MAJOR >= 16
    auto RM = optional<Reloc::Model>();
#else
    auto RM = Optional<Reloc::Model>();
#endif
    auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    fModule->setDataLayout(TheTargetMachine->createDataLayout());

    error_code EC;
    raw_fd_ostream  dest(object_code_path.c_str(), EC, sys::fs::OF_None);
    if (EC) {
        errs() << "ERROR : writeDSPFactoryToObjectcodeFile could not open file : " << EC.message();
        return false;
    }

    legacy::PassManager pass;
#if LLVM_VERSION_MAJOR >= 10
    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, CGFT_ObjectFile)) {
#elif LLVM_VERSION_MAJOR >= 8
    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, TargetMachine::CGFT_ObjectFile)) {
#else
    if (TheTargetMachine->addPassesToEmitFile(pass, dest, TargetMachine::CGFT_ObjectFile, true)) {
#endif
        errs() << "ERROR : writeDSPFactoryToObjectcodeFile : can't emit a file of this type";
        return false;
    }

    pass.run(*fModule);
    dest.flush();
    return true;
}

// Object code <==> file
bool llvm_dynamic_dsp_factory_aux::writeDSPFactoryToObjectcodeFile(const string& object_code_path,
                                                                   const string& target)
{
    if (target != "" && target != getTarget()) {
        // Recompilation is required
        string old_target = getTarget();
        if (crossCompile(target)) {
            bool res = writeDSPFactoryToObjectcodeFileAux(object_code_path);
            // Restore old target
            crossCompile(old_target);
            return res;
        } else {
            return false;
        }
    } else {
        return writeDSPFactoryToObjectcodeFileAux(object_code_path);
    }
}
        
// IR <==> string
static llvm_dsp_factory* readDSPFactoryFromIRAux(MEMORY_BUFFER buffer, const string& target, string& error_msg,
                                                 int opt_level)
{
    string sha_key = generateSHA1(MEMORY_BUFFER_GET(buffer).str());
    dsp_factory_table<SDsp_factory>::factory_iterator it;
    
    if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
        SDsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        try {
            char* tmp_local = setlocale(LC_ALL, NULL);
            if (tmp_local) {
                tmp_local = strdup(tmp_local);
            }
            setlocale(LC_ALL, "C");
            LLVMContext* context = new LLVMContext();
            SMDiagnostic err;
            // parseIR takes ownership of the given buffer, so don't delete it
            Module* module = parseIR(buffer, err, *context).release();
            if (!module) {
                error_msg = "ERROR : " + string(err.getMessage().data()) + "\n";
                return nullptr;
            }
            if (tmp_local) {
                setlocale(LC_ALL, tmp_local);
                free(tmp_local);
            }
            llvm_dynamic_dsp_factory_aux* factory_aux
                = new llvm_dynamic_dsp_factory_aux(sha_key, module, context, target, opt_level);
            if (factory_aux->initJIT(error_msg)) {
                llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
                llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
                factory->setSHAKey(sha_key);
                return factory;
            } else {
                delete factory_aux;
                return nullptr;
            }
        } catch (faustexception& e) {
            error_msg = e.what();
            return nullptr;
        }
    }
}

// Helper functions
ModulePTR loadSingleModule(const string filename, LLVMContext* context)
{
    SMDiagnostic err;
    ModulePTR module = parseIRFile(filename, err, *context);
    return module;
}

ModulePTR loadModule(const string& module_name, LLVMContext* context)
{
    // Try as a complete path
    if (ModulePTR module = loadSingleModule(module_name, context)) {
        return module;
    } else {
        // Otherwise use import directories
        for (size_t i = 0; i < gGlobal->gImportDirList.size(); i++) {
            string file_name = gGlobal->gImportDirList[i] + '/' + module_name;
            if (ModulePTR module1 = loadSingleModule(file_name, context)) {
                return module1;
            }
        }
        return nullptr;
    }
}

bool linkModules(Module* dst, ModulePTR src, string& error)
{
    bool res = false;
    if (Linker::linkModules(*dst, MovePTR(src))) {
        error = "cannot link module";
    } else {
        res = true;
    }
    return res;
}

Module* linkAllModules(LLVMContext* context, Module* dst, string& error)
{
    for (size_t i = 0; i < gGlobal->gLibraryList.size(); i++) {
        string    module_name = gGlobal->gLibraryList[i];
        ModulePTR src         = loadModule(module_name, context);
        if (!src) {
            error = "cannot load module : " + module_name;
            return nullptr;
        }
        if (!linkModules(dst, MovePTR(src), error)) {
            return nullptr;
        }
    }
    return dst;
}
        
// Public C++ API
LIBFAUST_API llvm_dsp_factory* createDSPFactoryFromFile(const string& filename, int argc, const char* argv[],
                                                  const string& target, string& error_msg, int opt_level)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");
    
    if (pos != string::npos) {
        return createDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, target, error_msg,
                                          opt_level);
    } else {
        error_msg = "ERROR : file extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

LIBFAUST_API llvm_dsp_factory* createDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc,
                                                       const char* argv[], const string& target, string& error_msg,
                                                       int opt_level)
{
    LOCK_API
    string expanded_dsp_content, sha_key;
   
    if ((expanded_dsp_content = sha1FromDSP(name_app, dsp_content, argc, argv, sha_key)) == "") {
        return nullptr;
    } else {
        
        dsp_factory_table<SDsp_factory>::factory_iterator it;
        if (llvm_dsp_factory_aux::gLLVMFactoryTable.getFactory(sha_key, it)) {
            SDsp_factory sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            try {
                int         argc1 = 0;
                const char* argv1[64];
                argv1[argc1++] = "faust";
                argv1[argc1++] = "-lang";
                argv1[argc1++] = "llvm";
                argv1[argc1++] = "-o";
                argv1[argc1++] = "string";
                // Copy arguments
                for (int i = 0; i < argc; i++) {
                    argv1[argc1++] = argv[i];
                }
                argv1[argc1] = nullptr;  // NULL terminated argv
                
                llvm_dynamic_dsp_factory_aux* factory_aux
                    = static_cast<llvm_dynamic_dsp_factory_aux*>(createFactory(name_app,
                                                                            dsp_content,
                                                                            argc1, argv1,
                                                                            error_msg,
                                                                            true));
                if (factory_aux && factory_aux->initJIT(error_msg)) {
                    factory_aux->setTarget(target);
                    factory_aux->setOptlevel(opt_level);
                    factory_aux->setClassName(getParam(argc, argv, "-cn", "mydsp"));
                    factory_aux->setName(name_app);
                    llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
                    llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
                    factory->setSHAKey(sha_key);
                    factory->setDSPCode(expanded_dsp_content);
                    return factory;
                } else {
                    delete factory_aux;
                    return nullptr;
                }
            } catch (faustexception& e) {
                error_msg = e.what();
                return nullptr;
            }
        }
    }
}
        
LIBFAUST_API llvm_dsp_factory* createDSPFactoryFromSignals(const string& name_app, tvec signals,
                                                        int argc, const char* argv[],
                                                        const string& target,
                                                        string& error_msg,
                                                        int opt_level)
{
    LOCK_API
    try {
        int         argc1 = 0;
        const char* argv1[64];
        argv1[argc1++] = "faust";
        argv1[argc1++] = "-lang";
        argv1[argc1++] = "llvm";
        argv1[argc1++] = "-o";
        argv1[argc1++] = "string";
        // Copy arguments
        for (int i = 0; i < argc; i++) {
            argv1[argc1++] = argv[i];
        }
        argv1[argc1] = nullptr;  // NULL terminated argv
        
        llvm_dynamic_dsp_factory_aux* factory_aux
            = static_cast<llvm_dynamic_dsp_factory_aux*>(createFactory(name_app, signals, argc1, argv1, error_msg));
        if (factory_aux && factory_aux->initJIT(error_msg)) {
            factory_aux->setTarget(target);
            factory_aux->setOptlevel(opt_level);
            factory_aux->setClassName(getParam(argc, argv, "-cn", "mydsp"));
            factory_aux->setName(name_app);
            llvm_dsp_factory* factory = new llvm_dsp_factory(factory_aux);
            llvm_dsp_factory_aux::gLLVMFactoryTable.setFactory(factory);
            return factory;
        } else {
            delete factory_aux;
            return nullptr;
        }
    } catch (faustexception& e) {
        error_msg = e.what();
        return nullptr;
    }
}
        
LIBFAUST_API llvm_dsp_factory* createDSPFactoryFromBoxes(const string& name_app, Tree box,
                                                      int argc, const char* argv[],
                                                      const string& target,
                                                      string& error_msg,
                                                      int opt_level)
{
    LOCK_API
    try {
        tvec signals = boxesToSignalsAux(box);
        return createDSPFactoryFromSignals(name_app, signals, argc, argv, target, error_msg, opt_level);
    } catch (faustexception& e) {
        error_msg = e.Message();
        return nullptr;
    }
}

LIBFAUST_API llvm_dsp_factory* readDSPFactoryFromBitcode(const string& bit_code, const string& target, string& error_msg,
                                                      int opt_level)
{
    LOCK_API
    return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_CREATE(StringRef(base64_decode(bit_code))), target, error_msg,
                                        opt_level);
}

LIBFAUST_API string writeDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToBitcode() : "";
}

// Bitcode <==> file
LIBFAUST_API llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const string& bit_code_path, const string& target,
                                                          string& error_msg, int opt_level)
{
    LOCK_API
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(bit_code_path);
    if (error_code ec = buffer.getError()) {
        error_msg = "ERROR : " + ec.message() + "\n";
        return nullptr;
    } else {
        return readDSPFactoryFromBitcodeAux(MEMORY_BUFFER_GET_REF(buffer), target, error_msg, opt_level);
    }
}

LIBFAUST_API bool writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const string& bit_code_path)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToBitcodeFile(bit_code_path) : false;
}

LIBFAUST_API llvm_dsp_factory* readDSPFactoryFromIR(const string& ir_code, const string& target, string& error_msg,
                                              int opt_level)
{
    LOCK_API
    return readDSPFactoryFromIRAux(MEMORY_BUFFER_CREATE(StringRef(ir_code)), target, error_msg, opt_level);
}

LIBFAUST_API string writeDSPFactoryToIR(llvm_dsp_factory* factory)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToIR() : "";
}

// IR <==> file
LIBFAUST_API llvm_dsp_factory* readDSPFactoryFromIRFile(const string& ir_code_path, const string& target, string& error_msg,
                                                     int opt_level)
{
    LOCK_API
    ErrorOr<OwningPtr<MemoryBuffer>> buffer = MemoryBuffer::getFileOrSTDIN(ir_code_path);
    if (error_code ec = buffer.getError()) {
        error_msg = "ERROR : " + ec.message() + "\n";
        return nullptr;
    } else {
        return readDSPFactoryFromIRAux(MEMORY_BUFFER_GET_REF(buffer), target, error_msg, opt_level);
    }
}

LIBFAUST_API bool writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const string& ir_code_path)
{
    LOCK_API
    return (factory) ? factory->writeDSPFactoryToIRFile(ir_code_path) : false;
}

// Public C interface : lock management is done by called C++ API
#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromFile(const char* filename, int argc, const char* argv[],
                                                      const char* target, char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = createDSPFactoryFromFile(filename, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc,
                                                        const char* argv[], const char* target, char* error_msg,
                                                        int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory =
        createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}
    
LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromSignals(const char* name_app, Signal* signals_aux,
                                                         int argc, const char* argv[],
                                                         const char* target,
                                                         char* error_msg,
                                                         int opt_level)
{
    string error_msg_aux;
    tvec signals;
    int i = 0;
    while (signals_aux[i]) { signals.push_back(signals_aux[i]); i++; }
    llvm_dsp_factory* factory =
        createDSPFactoryFromSignals(name_app, signals, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API llvm_dsp_factory* createCDSPFactoryFromBoxes(const char* name_app,
                                                       Tree box,
                                                       int argc, const char* argv[],
                                                       const char* target,
                                                       char* error_msg,
                                                       int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory =
        createDSPFactoryFromBoxes(name_app, box, argc, argv, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromBitcode(const char* bit_code, const char* target, char* error_msg,
                                                       int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromBitcode(bit_code, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API char* writeCDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(writeDSPFactoryToBitcode(factory).c_str()) : nullptr;
}

LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromBitcodeFile(const char* bit_code_path, const char* target, char* error_msg,
                                                           int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromBitcodeFile(bit_code_path, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API bool writeCDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const char* bit_code_path)
{
    return writeDSPFactoryToBitcodeFile(factory, bit_code_path);
}

LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromIR(const char* ir_code, const char* target, char* error_msg, int opt_level)
{
    string error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromIR(ir_code, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API char* writeCDSPFactoryToIR(llvm_dsp_factory* factory)
{
    return (factory) ? strdup(writeDSPFactoryToIR(factory).c_str()) : nullptr;
}

LIBFAUST_API llvm_dsp_factory* readCDSPFactoryFromIRFile(const char* ir_code_path, const char* target, char* error_msg,
                                                   int opt_level)
{
    string            error_msg_aux;
    llvm_dsp_factory* factory = readDSPFactoryFromIRFile(ir_code_path, target, error_msg_aux, opt_level);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return factory;
}

LIBFAUST_API bool writeCDSPFactoryToIRFile(llvm_dsp_factory* factory, const char* ir_code_path)
{
    return writeDSPFactoryToIRFile(factory, ir_code_path);
}

#ifdef __cplusplus
}
#endif
