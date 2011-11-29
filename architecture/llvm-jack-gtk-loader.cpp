/* link with  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <sys/wait.h>
#include <list>
#include <vector>

#include <iostream>
#include <fstream>

#include <libgen.h>
#include <jack/jack.h>

#include <iostream>
#include <fstream>
#include <ostream>

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

using namespace std;

#include "gui/FUI.h"
#include "misc.h"
#include "gui/faustgtk.h"
#include "audio/jack-dsp.h"

#ifdef OSCCTRL
#include "gui/OSCUI.h"
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
//#define IS_DOUBLE 1
#endif

#ifdef __APPLE__
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#endif

#ifndef UInt64
typedef long long unsigned int UInt64;
typedef unsigned int UInt32;
#endif

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

UInt64 DSP_rdtsc(void)
{
	union {
		UInt32 i32[2];
		UInt64 i64;
	} count;

	__asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
     return count.i64;
}

#define LOCK "lock ; "

char CAS1(volatile void* addr, volatile int value, int newvalue)
{
    register char ret;
    __asm__ __volatile__ (
						  "# CAS \n\t"
						  LOCK "cmpxchg %2, (%1) \n\t"
						  "sete %0               \n\t"
						  : "=a" (ret)
						  : "c" (addr), "d" (newvalue), "a" (value)
                          : "memory"
						  );
    return ret;
}

int atomic_xadd(volatile int* atomic, int val)
{
    register int result;
    __asm__ __volatile__ ("# atomic_xadd \n\t"
                          LOCK "xaddl %0,%1 \n\t"
                          : "=r" (result), "=m" (*atomic)
                          : "0" (val), "m" (*atomic));
    return result;
}

// -- layout groups

typedef void (* openFrameBoxFun) (void* interface, const char* label);
typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addToggleButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive display widgets

typedef void (* addNumDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, int precision);
typedef void (* addTextDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

typedef void (* declareFun) (void* interface, FAUSTFLOAT* zone, const char* key, const char* value);

struct UIGlue {

    void* uiInterface;

    openFrameBoxFun openFrameBox;
    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addToggleButtonFun addToggleButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addNumDisplayFun addNumDisplay;
    addTextDisplayFun addTextDisplay;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    declareFun declare;

};

typedef struct llvm_dsp {};

llvm_dsp* new_mydsp();
void delete_mydsp(llvm_dsp*);

int getNumInputs_mydsp(llvm_dsp*);
int getNumOutputs_mydsp(llvm_dsp*);

void init_mydsp(llvm_dsp*, int);
void classInit_mydsp(int);
void instanceInit_mydsp(llvm_dsp*, int);
void buildUserInterface_mydsp(llvm_dsp*, UIGlue*);
void compute_mydsp(llvm_dsp*, int, FAUSTFLOAT**, FAUSTFLOAT**);

typedef llvm_dsp* (* newDspFun) ();
typedef void (* deleteDspFun) (llvm_dsp* self);
typedef int (* getNumInputsFun) (llvm_dsp* self);
typedef int (* getNumOutputsFun) (llvm_dsp* self);
typedef void (* buildUserInterfaceFun) (llvm_dsp* self, UIGlue* ui);
typedef void (* initFun) (llvm_dsp* self, int freq);
typedef void (* classInitFun) (int freq);
typedef void (* instanceInitFun) (llvm_dsp* self, int freq);
typedef void (* computeFun) (llvm_dsp* self, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);

void openFrameBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openFrameBox(label);
}

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

void addToggleButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addToggleButton(label, zone);
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

void addNumDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, int precision)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumDisplay(label, zone, precision);
}

void addTextDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addTextDisplay(label, zone, names, min, max);
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

#ifdef __cplusplus
}
#endif

using namespace llvm;

static Module* LoadModule(std::string Filename)
{
    LLVMContext &Context = getGlobalContext();

    /*
    std::string ErrorMessage;
    std::auto_ptr<MemoryBuffer> Buffer(
                   MemoryBuffer::getFileOrSTDIN(Filename, &ErrorMessage));
 	return (Buffer.get()) ? ParseBitcodeFile(Buffer.get(), Context, &ErrorMessage) : 0;
    */

    std::string ErrorMessage;
    OwningPtr<MemoryBuffer> Buffer;
    if (error_code ec = MemoryBuffer::getFileOrSTDIN(Filename, Buffer))
        ErrorMessage = ec.message();
    Module *Result = 0;
    if (Buffer.get())
        return ParseBitcodeFile(Buffer.get(), Context, &ErrorMessage);
}

class LLVMLoader : public dsp {

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

  public:

	LLVMLoader(const std::string& name)
	{
        InitializeNativeTarget();
		fModule = LoadModule(name);
        fModule->setTargetTriple(llvm::sys::getHostTriple());

     	if (fModule) {
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
		} else {
			 throw new std::bad_alloc;
		}
	}

    void* LoadOptimize(const string& function)
    {
        Function* fun_ptr = fModule->getFunction(function);
        fManager->run(*fun_ptr);
        return fJIT->getPointerToFunction(fun_ptr);
    }

	virtual ~LLVMLoader()
	{
		fDelete(fDsp);
		delete fJIT;
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
        glue.openFrameBox = openFrameBoxGlue;
        glue.openTabBox = openTabBoxGlue;
        glue.openHorizontalBox = openHorizontalBoxGlue;
        glue.openVerticalBox = openVerticalBoxGlue;
        glue.closeBox = closeBoxGlue;
        glue.addButton = addButtonGlue;
        glue.addToggleButton = addToggleButtonGlue;
        glue.addCheckButton = addCheckButtonGlue;
        glue.addVerticalSlider = addVerticalSliderGlue;
        glue.addHorizontalSlider = addHorizontalSliderGlue;
        glue.addNumEntry = addNumEntryGlue;
        glue.addNumDisplay = addNumDisplayGlue;
        glue.addTextDisplay = addTextDisplayGlue;
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

LLVMLoader* DSP;

classInitFun LLVMLoader::fClassInit;

list<GUI*> GUI::fGuiList;

int main(int argc, char *argv[])
{
	char	appname[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");

    try {
		if (argc < 2) {
			printf("Usage: llvm-jack-gtk-loader [file.bc]\n");
			exit(1);
		} else {
			DSP = new LLVMLoader(argv[1]);
        }
	} catch (...) {
		printf("Cannot load LLVM bytecode file\n");
		exit(1);
	}

	snprintf(appname, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%s-%src", home, appname, argv[1]);

	GUI* interface 	= new GTKUI (appname, &argc, &argv);
	FUI* finterface	= new FUI();

	DSP->buildUserInterface(interface);
	DSP->buildUserInterface(finterface);

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(appname, argc, argv);
	DSP->buildUserInterface(oscinterface);
#endif

	jackaudio audio;
	audio.init(appname, DSP);
	finterface->recallState(rcfilename);
	audio.start();

#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();

	audio.stop();
	finterface->saveState(rcfilename);
  	return 0;
}

