/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include "llvm_dsp_aux.hh"
#include "../../architecture/faust/libfaust.h"

#include <stdio.h>

// For scheduler mode : this function is retrieved in the LLVM module and used in scheduler.cpp
typedef void (* computeThreadExternalFun) (llvm_dsp* dsp, int cur_thread);
computeThreadExternalFun gComputeThreadExternal = 0;

static int gLLVMInit = 0;
        
void* llvm_dsp_factory::LoadOptimize(const std::string& function)
{
    llvm::Function* fun_ptr = fModule->getFunction(function);
    if (fun_ptr) {
        return fJIT->getPointerToFunction(fun_ptr);
    } else {
        throw -1;
    }
}

static Module* LoadModule(const std::string filename)
{
    printf("Load module : %s \n", filename.c_str());
    SMDiagnostic err;
    Module* res = ParseIRFile(filename, err, getGlobalContext());
    if (!res) {
    #if defined(LLVM_31) 
        err.print("LoadModule", errs());
    #endif
    #if defined(LLVM_30) 
        err.Print("LoadModule", errs());
    #endif
    }
    return res;
}

Module* llvm_dsp_factory::CompileModule(int argc, const char *argv[], const char* library_path,  const char* draw_path, const char* input_name, const char* input, char* error_msg)
{
    printf("Compile module...\n");
    
    int argc1 = argc + 3;
    const char* argv1[argc1];
    argv1[0] = "faust";
    argv1[1] = "-lang";
    argv1[2] = "llvm";
    for (int i = 0; i < argc; i++) {
        argv1[i+3] = argv[i];
        if (strcmp(argv[i], "-sch") == 0) {
            fScheduler = true;
        }
    }
    
    fLibraryPath = string(library_path);
    return compile_faust_llvm(argc1, argv1, library_path, draw_path, input_name, input, error_msg);
}

// Bitcode
std::string llvm_dsp_factory::writeDSPFactoryToBitcode()
{
    std::string res;
    raw_string_ostream out(res);
    WriteBitcodeToFile(fModule, out);
    out.flush();
    return res;
}

void llvm_dsp_factory::writeDSPFactoryToBitcodeFile(const std::string& bit_code_path)
{
    std::string err;
    raw_fd_ostream out(bit_code_path.c_str(), err, raw_fd_ostream::F_Binary);
    WriteBitcodeToFile(fModule, out);
}

// IR
string llvm_dsp_factory::writeDSPFactoryToIR()
{
    std::string res;
    raw_string_ostream out(res);
    PassManager PM;
    PM.add(createPrintModulePass(&out));
    PM.run(*fModule);
    out.flush();
    return res;
}

void llvm_dsp_factory::writeDSPFactoryToIRFile(const std::string& ir_code_path)
{
    std::string err;
    raw_fd_ostream out(ir_code_path.c_str(), err, raw_fd_ostream::F_Binary);
    PassManager PM;
    PM.add(createPrintModulePass(&out));
    PM.run(*fModule);
    out.flush();
}

llvm_dsp_factory::llvm_dsp_factory(Module* module, const std::string& target, int opt_level)
{
    fOptLevel = opt_level;
    fTarget = target;
    Init();
    fModule = module;
}

llvm_dsp_factory::llvm_dsp_factory(int argc, const char *argv[], 
    const std::string& library_path,
    const std::string& draw_path, 
    const std::string& name,
    const std::string& input, 
    const std::string& target, 
    char* error_msg, int opt_level)
{
    fOptLevel = opt_level;
    fTarget = target;
    Init();
    fModule = CompileModule(argc, argv, library_path.c_str(), draw_path.c_str(), name.c_str(), input.c_str(), error_msg);
}

void llvm_dsp_factory::Init()
{
    fJIT = 0;
    fNew = 0;
    fDelete = 0;
    fGetNumInputs = 0;
    fGetNumOutputs = 0;
    fBuildUserInterface = 0;
    fInit = 0;
    fClassInit = 0;
    fInstanceInit = 0;
    fCompute = 0;
    fScheduler = false;
}

llvm_dsp_aux* llvm_dsp_factory::createDSPInstance()
{
    assert(fModule);
    assert(fJIT);
    return new llvm_dsp_aux(this, fNew());
}

bool llvm_dsp_factory::initJIT()
{
    // First check is Faust compilation succeeded... (valid LLVM module)
    if (!fModule) {
        return false;
    }
    
    if (gLLVMInit++ == 0) {
        //printf("InitializeNativeTarget\n");
        InitializeNativeTarget();
    }
    if (fTarget != "") {
         fModule->setTargetTriple(fTarget);
    } else {
    #if defined(LLVM_31)
        fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
    #else
        fModule->setTargetTriple(llvm::sys::getHostTriple());
    #endif
    }

    std::string err;
    EngineBuilder builder(fModule);
    builder.setOptLevel(CodeGenOpt::Aggressive);
    builder.setEngineKind(EngineKind::JIT);
    builder.setUseMCJIT(true);
    builder.setMCPU(llvm::sys::getHostCPUName());
    /*
    SmallVector<std::string, 4> attrs;
    attrs.push_back("sse");
    attrs.push_back("sse2");
    attrs.push_back("sse3");
    attrs.push_back("enable-unsafe-fp-math");
    builder.setMAttrs(attrs);
    */
    fJIT = builder.create();
    assert(fJIT);
    
    // Run static constructors.
    fJIT->runStaticConstructorsDestructors(false);
    
    fJIT->DisableLazyCompilation(true);
    fModule->setDataLayout(fJIT->getTargetData()->getStringRepresentation());
    //fModule->dump();

    // Set up the optimizer pipeline. Start with registering info about how the
    // target lays out data structures.
    PassManager pm;
    pm.add(new TargetData(*fJIT->getTargetData()));
    
    FunctionPassManager fpm(fModule);
    fpm.add(new TargetData(*fJIT->getTargetData()));
    
    // Link with "scheduler" code
    if (fScheduler) {
        Module* scheduler = LoadModule(fLibraryPath + "scheduler.ll");
        if (scheduler) {
            //scheduler->dump();
            if (Linker::LinkModules(fModule, scheduler, Linker::DestroySource, &err)) {
                printf("Cannot link scheduler module : %s\n", err.c_str());
            }
            delete scheduler;
        } else {
            printf("File scheduler.ll not found...\n");
        }
    }
    
    // Taken from LLVM Opt.cpp
    PassManagerBuilder Builder;
    Builder.OptLevel = fOptLevel;

    if (fOptLevel > 1) {
        unsigned threshold = 225;
        if (fOptLevel > 2)
            threshold = 275;
        Builder.Inliner = createFunctionInliningPass(threshold);
    } else {
        Builder.Inliner = createAlwaysInlinerPass();
    }
      
    Builder.DisableUnrollLoops = (fOptLevel == 0);
    Builder.populateFunctionPassManager(fpm);
    Builder.populateModulePassManager(pm);
    
    pm.run(*fModule);
    
    fModule->dump();
    
    try {
        fNew = (newDspFun)LoadOptimize("new_mydsp");
        fDelete = (deleteDspFun)LoadOptimize("delete_mydsp");
        fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs_mydsp");
        fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs_mydsp");
        fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface_mydsp");
        fInit = (initFun)LoadOptimize("init_mydsp");
        fClassInit = (classInitFun)LoadOptimize("classInit_mydsp");
        fInstanceInit = (instanceInitFun)LoadOptimize("instanceInit_mydsp");
        fCompute = (computeFun)LoadOptimize("compute_mydsp");
        // FIXME : what happens if loaded from bitcode or IR ?
        if (fScheduler) {
            gComputeThreadExternal = (computeThreadExternalFun)LoadOptimize("computeThreadExternal");
        }
        return true;
    } catch (...) {
        // Module does not contain the Faust entry points...
        return false;
    }
}

llvm_dsp_factory::~llvm_dsp_factory()
{
    if (fJIT) {
        fJIT->runStaticConstructorsDestructors(true);
        // fModule is kept and deleted by fJIT
        delete fJIT;
    }
    
    if (--gLLVMInit == 0) {
        //TODO
        //printf("llvm_shutdown\n");
        //llvm_shutdown();
    }
}

std::string llvm_dsp_factory::BuildJSON(llvm_dsp_imp* dsp)
{
    stringstream dst;
    UIGlue glue;
    JSONUI json(&dst);
    buildUIGlue(&glue, &json);
    fBuildUserInterface(dsp, &glue);
    json.finish();
    return dst.str();
}

// -- widget's layouts

static void tab(int n, ostream& fout)
{
    fout << '\n';
    while (n--) fout << '\t';
}

void JSONUI::openGroup(const char* group, const char* label)
{
    fTab++;
    tab(fTab, *fOut); *fOut << "\"" << group << "\":" << "\"" << label << "\"" << "[";
    fNewGroup = true;
    fTab++; 
}

void JSONUI::openTabBox(const char* label)
{
    openGroup("tablegroup", label);
}

void JSONUI::openHorizontalBox(const char* label)
{
    openGroup("horizontalgroup", label);
}
void JSONUI::openVerticalBox(const char* label)
{
    openGroup("verticalgroup", label);
}

void JSONUI::closeBox()
{
    fTab--;
    tab(fTab, *fOut); *fOut << "]" << endl;
    fTab--;
}

// -- active widgets

void JSONUI::addGenericButton(const char* button, const char* label, FAUSTFLOAT* zone)
{
    tab(fTab, *fOut); 
    string beg = (fNewGroup) ? "{ " : ",{ ";
    fNewGroup = false;
    *fOut << beg << "\"type\":" << "\"" << button << "\",";
    tab(fTab, *fOut); *fOut << "\"label\":" << "\"" << label << "\"";
    tab(fTab, *fOut); *fOut << "}";
}

void JSONUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    addGenericButton("button", label, zone);
}
void JSONUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    addGenericButton("checkbutton", label, zone);
}
void JSONUI::addGenericSlider(const char* slider, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    tab(fTab, *fOut);
    string beg = (fNewGroup) ? "{ " : ",{ ";
    fNewGroup = false;
    *fOut << beg << "\"type\":" << "\"" << slider << "\",";
    tab(fTab, *fOut); *fOut << "\"label\":" << "\"" << label << "\",";
    tab(fTab, *fOut); *fOut << "\"init\":" << float(init) << ",";
    tab(fTab, *fOut); *fOut << "\"min\":" << float(min) << ",";
    tab(fTab, *fOut); *fOut << "\"max\":" << float(max) << ",";
    tab(fTab, *fOut); *fOut << "\"step\":" << float(step);
    tab(fTab, *fOut); *fOut << "}";
}
 
void JSONUI::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    addGenericSlider("vecticalslider", label, zone, init, min, max, step);
}
void JSONUI::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    addGenericSlider("horizontalslider", label, zone, init, min, max, step);
}
void JSONUI::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    addGenericSlider("numentry", label, zone, init, min, max, step);
}

// -- passive widgets

void JSONUI::addGenericBargraph(const char* bargraph, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    tab(fTab, *fOut); 
    string beg = (fNewGroup) ? "{ " : ",{ ";
    fNewGroup = false;
    *fOut << beg << "\"type\":" << "\"" << bargraph << "\",";
    tab(fTab, *fOut); *fOut << "\"label\":" << "\"" << label << "\",";
    tab(fTab, *fOut); *fOut << "\"min\":" << float(min) << ",";
    tab(fTab, *fOut); *fOut << "\"max\":" << float(max) << ",";
    tab(fTab, *fOut); *fOut << "}";
}

void JSONUI::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    addGenericBargraph("horizontalbargraph", label, zone, min, max);
}
void JSONUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    addGenericBargraph("verticalbargraph", label, zone, min, max);
}

// -- metadata declarations

void JSONUI::declare(FAUSTFLOAT* zone, const char* key, const char* val) 
{}
        
// Instance 

llvm_dsp_aux::llvm_dsp_aux(llvm_dsp_factory* factory, llvm_dsp_imp* dsp)
    :fDSPFactory(factory), fDSP(dsp)
{
    assert(fDSPFactory);
    assert(fDSP);
}
        
llvm_dsp_aux::~llvm_dsp_aux()
{   
    if (fDSP) {
        fDSPFactory->fDelete(fDSP);
    }
}

int llvm_dsp_aux::getNumInputs()
{
    return fDSPFactory->fGetNumInputs(fDSP);
}
int llvm_dsp_aux::getNumOutputs()
{
    return fDSPFactory->fGetNumOutputs(fDSP);
}

void llvm_dsp_aux::classInit(int samplingFreq)
{
    fDSPFactory->fClassInit(samplingFreq);
}

void llvm_dsp_aux::instanceInit(int samplingFreq)
{
    fDSPFactory->fInstanceInit(fDSP, samplingFreq);
}

void llvm_dsp_aux::init(int samplingFreq)
{
    fDSPFactory->fInit(fDSP, samplingFreq);
}

void llvm_dsp_aux::buildUserInterface(UI* interface)
{
    UIGlue glue;
    buildUIGlue(&glue, interface);
    fDSPFactory->fBuildUserInterface(fDSP, &glue);
}

std::string llvm_dsp_aux::buildJSON()
{
    return  fDSPFactory->BuildJSON(fDSP);
}

void llvm_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    AVOIDDENORMALS;
    fDSPFactory->fCompute(fDSP, count, input, output);
}

static llvm_dsp_factory* CheckDSPFactory(llvm_dsp_factory* factory)
{
    if (factory->initJIT()) {
        return factory;
    } else {
        delete factory;
        return 0;
    }
}

// Public API

EXPORT llvm_dsp_factory* createDSPFactory(int argc, const char *argv[], 
    const std::string& library_path, const std::string& draw_path, const std::string& name, 
    const std::string& input, const std::string& target, 
    char* error_msg, int opt_level)
{
    return CheckDSPFactory(new llvm_dsp_factory(argc, argv, library_path, draw_path, name, input, target, error_msg, opt_level));
}
    
// Bitcode <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcode(const std::string& bit_code, const std::string& target, int opt_level)
{
    string error_msg;
    MemoryBuffer* buffer = MemoryBuffer::getMemBuffer(StringRef(bit_code));
    Module* module = ParseBitcodeFile(buffer, getGlobalContext(), &error_msg);
    delete buffer;
    
    if (module) {
        return CheckDSPFactory(new llvm_dsp_factory(module, target, opt_level));
    } else {
        printf("readDSPFactoryFromBitcode failed : %s\n", error_msg.c_str());
        return 0;
    }
}

EXPORT std::string writeDSPFactoryToBitcode(llvm_dsp_factory* factory)
{
    return factory->writeDSPFactoryToBitcode();
}

// Bitcode <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level)
{
    OwningPtr<MemoryBuffer> buffer;
    if (error_code ec = MemoryBuffer::getFileOrSTDIN(bit_code_path.c_str(), buffer)) {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", ec.message().c_str());
        return 0;
    }
  
    std::string error_msg;
    Module* module = ParseBitcodeFile(buffer.get(), getGlobalContext(), &error_msg);
    
    if (module) {
        return CheckDSPFactory(new llvm_dsp_factory(module, target, opt_level));
    } else {
        printf("readDSPFactoryFromBitcodeFile failed : %s\n", error_msg.c_str());
        return 0;
    }
}

EXPORT void writeDSPFactoryToBitcodeFile(llvm_dsp_factory* factory, const std::string& bit_code_path)
{
    factory->writeDSPFactoryToBitcodeFile(bit_code_path);
}

// IR <==> string
EXPORT llvm_dsp_factory* readDSPFactoryFromIR(const std::string& ir_code, const std::string& target, int opt_level)
{
    SMDiagnostic err;
    MemoryBuffer* buffer = MemoryBuffer::getMemBuffer(StringRef(ir_code));
    Module* module = ParseIR(buffer, err, getGlobalContext()); // ParseIR takes ownership of the given buffer, so don't delete it
    
    if (module) {
        return CheckDSPFactory(new llvm_dsp_factory(module, target, opt_level));
    } else {
    #if defined(LLVM_31) 
        err.print("readDSPFactoryFromIR failed :", errs());
    #endif
    #if defined(LLVM_30) 
        err.Print("readDSPFactoryFromIR failed :", errs());
    #endif
        return 0;
    }
}

EXPORT std::string writeDSPFactoryToIR(llvm_dsp_factory* factory)
{
    return factory->writeDSPFactoryToIR();
}

// IR <==> file
EXPORT llvm_dsp_factory* readDSPFactoryFromIRFile(const std::string& ir_code_path, const std::string& target, int opt_level)
{
    SMDiagnostic err;
    Module* module = ParseIRFile(ir_code_path, err, getGlobalContext());
    
    if (module) {
        return CheckDSPFactory(new llvm_dsp_factory(module, target, opt_level));
    } else {
    #if defined(LLVM_31) 
        err.print("readDSPFactoryFromIR failed :", errs());
    #endif
    #if defined(LLVM_30) 
        err.Print("readDSPFactoryFromIR failed :", errs());
    #endif
        return 0;
    }
}

EXPORT void writeDSPFactoryToIRFile(llvm_dsp_factory* factory, const std::string& ir_code_path)
{
    factory->writeDSPFactoryToIRFile(ir_code_path);
}

// Instance

EXPORT llvm_dsp* createDSPInstance(llvm_dsp_factory* factory)
{
    return reinterpret_cast<llvm_dsp*>(factory->createDSPInstance());
}

EXPORT void deleteDSPFactory(llvm_dsp_factory* factory) { delete factory; }

EXPORT void deleteDSPInstance(llvm_dsp* dsp) 
{
    delete dsp; 
}

EXPORT int llvm_dsp::getNumInputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumInputs();
}

int EXPORT llvm_dsp::getNumOutputs()
{
    return reinterpret_cast<llvm_dsp_aux*>(this)->getNumOutputs();
}

EXPORT void llvm_dsp::classInit(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->classInit(samplingFreq);
}

EXPORT void llvm_dsp::instanceInit(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->instanceInit(samplingFreq);
}

EXPORT void llvm_dsp::init(int samplingFreq)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->init(samplingFreq);
}

EXPORT void llvm_dsp::buildUserInterface(UI* interface)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->buildUserInterface(interface);
}

EXPORT void llvm_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    reinterpret_cast<llvm_dsp_aux*>(this)->compute(count, input, output);
}

EXPORT std::string llvm_dsp::buildJSON()   
{ 
    return reinterpret_cast<llvm_dsp_aux*>(this)->buildJSON();
}
