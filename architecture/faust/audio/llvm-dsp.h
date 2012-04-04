
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>

#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Analysis/LoopPass.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/PassNameParser.h>
#include <llvm/Support/PluginLoader.h>
#include <llvm/Support/system_error.h>
#include <llvm/Linker.h>
#ifdef LLVM_29
#include <llvm/Target/TargetSelect.h>
#endif
#ifdef LLVM_30
#include <llvm/Support/TargetSelect.h>
#endif
#include <llvm/Support/Host.h>

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "faust/gui/CUI.h"
#include "faust/libfaust.h"
#include "faust/audio/dsp.h"
#include "faust/misc.h"

using namespace std;
using namespace llvm;

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct llvm_dsp {};

typedef llvm_dsp* (* newDspFun) ();
typedef void (* deleteDspFun) (llvm_dsp* self);
typedef int (* getNumInputsFun) (llvm_dsp* self);
typedef int (* getNumOutputsFun) (llvm_dsp* self);
typedef void (* buildUserInterfaceFun) (llvm_dsp* self, UIGlue* ui);
typedef void (* initFun) (llvm_dsp* self, int freq);
typedef void (* classInitFun) (int freq);
typedef void (* instanceInitFun) (llvm_dsp* self, int freq);
typedef void (* computeFun) (llvm_dsp* self, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

#ifdef __cplusplus
}
#endif

void openTabBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openTabBox(label);
}

void openHorizontalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openHorizontalBox(label);
}

void openVerticalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openVerticalBox(label);
}

void closeBoxGlue(void* cpp_interface)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->closeBox();
}

void addButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addButton(label, zone);
}

void addCheckButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addCheckButton(label, zone);
}

void addVerticalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalSlider(label, zone, init, min, max, step);
}

void addHorizontalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalSlider(label, zone, init, min, max, step);
}

void addNumEntryGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumEntry(label, zone, init, min, max, step);
}

void addHorizontalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalBargraph(label, zone, min, max);
}

void addVerticalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalBargraph(label, zone, min, max);
}

void declareGlue(void* cpp_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->declare(zone, key, value);
}

class llvmdsp : public dsp {

  private:

        ExecutionEngine* fJIT;
        Module* fModule;
        FunctionPassManager* fManager;

        llvm_dsp* fDsp;
        newDspFun fNew;
        deleteDspFun fDelete;
        getNumInputsFun fGetNumInputs;
        getNumOutputsFun fGetNumOutputs;
        buildUserInterfaceFun fBuildUserInterface;
        initFun fInit;
        static classInitFun fClassInit;
        instanceInitFun fInstanceInit;
        computeFun fCompute;
        
        void* LoadOptimize(const std::string& function)
        {
            Function* fun_ptr = fModule->getFunction(function);
            fManager->run(*fun_ptr);
            return fJIT->getPointerToFunction(fun_ptr);
        }
        
        Module* LoadModule(const std::string filename)
        {
            LLVMContext &Context = getGlobalContext();
            std::string ErrorMessage;
            OwningPtr<MemoryBuffer> Buffer;
            if (error_code ec = MemoryBuffer::getFileOrSTDIN(filename, Buffer)) {
                ErrorMessage = ec.message();
            }
            Module *Result = 0;
            if (Buffer.get()) {
                return ParseBitcodeFile(Buffer.get(), Context, &ErrorMessage);
            }
        }

  public:
  
        llvmdsp(const std::string& pgm)
        {
            int argc = 3;
            const char* argv[3];
            argv[0] = "faust";
            argv[1] = "-lang";
            argv[2] = "llvm";
            
            fModule = compile_faust_llvm(argc, (char**)argv, pgm.c_str());
            if (fModule) {
                Init();
            } else {
                throw new std::bad_alloc;
            }
        }
  
        llvmdsp(int argc, char *argv[])
        {
            if (strstr(argv[1], ".bc")) {
                printf("Load module...\n");
                fModule = LoadModule(argv[1]);
            } else {
                printf("Compile module...\n");
                int argc1 = 4;
                const char* argv1[4];
                argv1[0] = "faust";
                argv1[1] = "-lang";
                argv1[2] = "llvm";
                argv1[3] = argv[1];
                fModule = compile_faust_llvm(argc1, (char**)argv1, NULL);
            }
            
            if (fModule) {
                Init();
            } else {
                throw new std::bad_alloc;
            }
        }

        void Init()
        {
            InitializeNativeTarget();
            fModule->setTargetTriple(llvm::sys::getHostTriple());

            std::string ErrorMessage;

            EngineBuilder builder(fModule);
            /*
            builder.setMArch(MArch);
            builder.setMCPU(MCPU);
            builder.setMAttrs(MAttrs);
            builder.setErrorStr(&ErrorMsg);
            builder.setEngineKind(ForceInterpreter
                                    ? EngineKind::Interpreter
                                    : EngineKind::JIT);
            */
            builder.setOptLevel(CodeGenOpt::Aggressive);
            fJIT = builder.create();

            //fJIT = EngineBuilder(fModule).create();
            assert(fJIT);
            fJIT->DisableLazyCompilation(true);
            fModule->setDataLayout(fJIT->getTargetData()->getStringRepresentation());
            //module->dump();

            FunctionPassManager OurFPM(fModule);
            // Set up the optimizer pipeline.  Start with registering info about how the
            // target lays out data structures.
            OurFPM.add(new TargetData(*fJIT->getTargetData()));
            // Do simple "peephole" optimizations and bit-twiddling optzns.
            OurFPM.add(createInstructionCombiningPass());
            // Reassociate expressions.
            OurFPM.add(createReassociatePass());
            // Eliminate Common SubExpressions.
            OurFPM.add(createGVNPass());
            // Simplify the control flow graph (deleting unreachable blocks, etc).
            OurFPM.add(createCFGSimplificationPass());

            OurFPM.doInitialization();
            fManager = &OurFPM;

            fNew = (newDspFun)LoadOptimize("new_mydsp");
            fDelete = (deleteDspFun)LoadOptimize("delete_mydsp");
            fGetNumInputs = (getNumInputsFun)LoadOptimize("getNumInputs_mydsp");
            fGetNumOutputs = (getNumOutputsFun)LoadOptimize("getNumOutputs_mydsp");
            fBuildUserInterface = (buildUserInterfaceFun)LoadOptimize("buildUserInterface_mydsp");
            fInit = (initFun)LoadOptimize("init_mydsp");
            fClassInit = (classInitFun)LoadOptimize("classInit_mydsp");
            fInstanceInit = (instanceInitFun)LoadOptimize("instanceInit_mydsp");
            fCompute = (computeFun)LoadOptimize("compute_mydsp");
            fDsp = fNew();
        }

        virtual ~llvmdsp()
        {
            fDelete(fDsp);
            delete fJIT;
            delete fModule;
        }

        virtual int getNumInputs()
        {
            return fGetNumInputs(fDsp);
        }
        virtual int getNumOutputs()
        {
            return fGetNumOutputs(fDsp);
        }

        static void classInit(int samplingFreq)
        {
            fClassInit(samplingFreq);
        }

        virtual void instanceInit(int samplingFreq)
        {
            fInstanceInit(fDsp, samplingFreq);
        }

        virtual void init(int samplingFreq)
        {
            fInit(fDsp, samplingFreq);
        }

        virtual void buildUserInterface(UI* interface)
        {
            UIGlue glue;
            glue.uiInterface = interface;
            glue.openTabBox = openTabBoxGlue;
            glue.openHorizontalBox = openHorizontalBoxGlue;
            glue.openVerticalBox = openVerticalBoxGlue;
            glue.closeBox = closeBoxGlue;
            glue.addButton = addButtonGlue;
            glue.addCheckButton = addCheckButtonGlue;
            glue.addVerticalSlider = addVerticalSliderGlue;
            glue.addHorizontalSlider = addHorizontalSliderGlue;
            glue.addNumEntry = addNumEntryGlue;
            glue.addHorizontalBargraph = addHorizontalBargraphGlue;
            glue.addVerticalBargraph = addVerticalBargraphGlue;
            glue.declare = declareGlue;
            fBuildUserInterface(fDsp, &glue);
        }

        virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            AVOIDDENORMALS;
            fCompute(fDsp, count, input, output);
        }
};

