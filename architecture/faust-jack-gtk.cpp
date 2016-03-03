/************************************************************************
    FAUST Architecture File
	Copyright (C) 2010-2012 GRAME, Centre National de Creation Musicale
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

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.


 ************************************************************************
 ************************************************************************/
#include <libgen.h>
#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/faustgtk.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/jsonfaustui.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

struct MyMeta : public Meta
{
    virtual void declare(const char* key, const char* value)
    {
        printf("key = %s value = %s\n", key, value);
    }
};

extern "C" int compile_faust(int argc, const char* argv[], const char* library_path, const char* draw_path, const char* name, const char* input, char* error_msg);
extern "C" void* compile_faust_llvm(int argc, const char* argv[], const char* library_path, const char* draw_path, const char* name, const char* input, char* error_msg);

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

dsp* DSP;
std::list<GUI*> GUI::fGuiList;

int main(int argc, char *argv[])
{
	char	appname[256];
    char	filename[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");
    
    llvm_dsp_factory* factory3 = 0;
    llvm_dsp_factory* factory4 = 0;

    if (argc < 2) {
        printf("Usage: faust-jack-gtk args [file.dsp | file.bc]\n");
        exit(1);
    } else {
    
        /*
        int argc1 = 2;
        const char* argv1[argc1];
        argv1[0] = "faust";
        argv1[1] = "-svg";

        compile_faust(argc1, (char**)argv1, false, "", "in1", "process = +,+;", error_msg);
        compile_faust(argc1, (char**)argv1, false, "", "in2", "process = _,_;", error_msg);
        */
        
        /*
        try {
            
            int argc1 = 1;
            char* argv1[argc1];
            argv1[0] = "-svg";
            //DSP = new llvmdsp(argc1, argv1, "/Users/letz", "in1", "import(\"test.lib\"); process = TOTO;", error_msg);
            DSP = new llvmdsp(argc1, argv1, "", "in1", "process = +,+;", error_msg);
            //delete(DSP);
            //DSP = new llvmdsp(argc1, argv1, "in2", "process = +,+;", "/Users/letz", error_msg);
            //DSP = new llvmdsp(0, NULL, "in1", "process = +,+;", error_msg);
        }
        catch (...) {
            printf("Mauvais code source : %s", error_msg);
            DSP = new llvmdsp(0, NULL, "/Users/letz", "in1", "process = +,+;", error_msg);
        }
        */
        
        int argc1 = 1;
        const char* argv1[argc1];
        argv1[0] = "-svg";
        std::string error_msg1;
        
        /*
        llvm_dsp_factory* factory1 = createDSPFactory(argc1, argv1, "/Users/letz", "", "in1", "process = +,+", "", error_msg1);
        if (factory1) {
            llvm_dsp* imp1 = createDSPInstance(factory1);
            deleteDSPInstance(imp1);
            imp1 = createDSPInstance(factory1);
            deleteDSPInstance(imp1);
            printf("createInstance %x %s\n", imp1, error_msg1);
            DSP = createDSPInstance(factory1);
            deleteDSPInstance(DSP);
            deleteDSPFactory(factory1);
        } else {
            printf("Cannot create factory : %s", error_msg1);
        }
        
        char error_msg2[256];
        llvm_dsp_factory* factory2 = createDSPFactory(argc1, argv1, "/Users/letz", "", "in1", "process = +,+", "", error_msg1);
        if (factory2) {
            llvm_dsp* imp2 = createDSPInstance(factory2);
            deleteDSPInstance(imp2);
            llvm_dsp* imp21 = createDSPInstance(factory2);
            deleteDSPInstance(imp21);
            printf("createInstance %x %s\n", imp2, error_msg2);
            DSP = createDSPInstance(factory2);
            deleteDSPInstance(DSP);
            deleteDSPFactory(factory2);
        } else {
            printf("Cannot create factory : %s", error_msg2);
        }
        */
        
        /*
        char error_msg3[256];
        factory3 = createDSPFactory(argc - 1, (const char**)&argv[1], "", "", "", "", "", error_msg3, 3);
        //printf("createDSPFactory %x\n", factory3);
        if (factory3) {
            DSP = createDSPInstance(factory3);
            assert(DSP);
         } else {
            printf("Cannot create factory : %s\n", error_msg3);
            return 1;
        }
        
        MyMeta meta;
        httpdfaust::jsonfaustui json("", "", 0);
        DSP->buildUserInterface(&json);
        metadataDSPFactory(factory3, &json);
        metadataDSPFactory(factory3, &meta);
        printf("JSON %s\n", json.json());
        
        error_msg3[256];
        factory3 = createDSPFactory(argc - 1, (const char**)&argv[1], "", "", "", "", "", error_msg3, 3);
        //printf("createDSPFactory %x\n", factory3);
        if (factory3) {
            DSP = createDSPInstance(factory3);
            assert(DSP);
         } else {
            printf("Cannot create factory : %s\n", error_msg3);
            return 1;
        }
        
        meta;
        DSP->buildUserInterface(&json);
        metadataDSPFactory(factory3, &json);
        metadataDSPFactory(factory3, &meta);
        printf("JSON %s\n", json.json());
        */
        
        std::string error_msg3;
        //factory3 = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "i386-apple-darwin10.6.0-cortex-m3", error_msg3, 0);
        //factory3 = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "i386-apple-darwin10.6.0", error_msg3, -1);
        factory3 = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "", error_msg3, -1);
        
        printf("factory3 %p\n", factory3);
        
        ///deleteDSPFactory(factory3);
        //factory3 = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "", error_msg3, 3);
        //factory4 = createDSPFactoryFromString("titi", "process = +,+,+;", argc-2, (const char**)argv[argc-1], "", error_msg3, 4);
        //factory4 = createDSPFactoryFromString("toto", "process = +;", argc-2, (const char**)argv[argc-1], "", error_msg3, 4);
        
        /*
        for (int i = 0; i < 10; i++) {
            std::string machine_code = writeDSPFactoryToMachine(factory3);
            printf("writeDSPFactoryToMachine %d\n", i);
            factory3 = readDSPFactoryFromMachine(machine_code);
        }
        */
        
        /*
        for (int i = 0; i < 10; i++) {
            writeDSPFactoryToMachineFile(factory3, "/Users/letz/machinecode");
            printf("writeDSPFactoryToMachineFile %d\n", i);
            factory3 = readDSPFactoryFromMachineFile("/Users/letz/machinecode");
        }
        */
        
        if (factory3) {
            DSP = createDSPInstance(factory3);
            assert(DSP);
         } else {
            printf("Cannot create factory : %s\n", error_msg3.c_str());
            return 1;
        }
        
        /*
        if (factory4) {
            DSP = createDSPInstance(factory4);
            assert(DSP);
         } else {
            printf("Cannot create factory : %s\n", error_msg3.c_str());
            return 1;
        }
        */
       
        /*
        meta;
        DSP->buildUserInterface(&json);
        metadataDSPFactory(factory3, &json);
        metadataDSPFactory(factory3, &meta);
        printf("JSON %s\n", json.json());
        */
        
        //deleteDSPInstance(DSP);
        //deleteDSPFactory(factory3);
               
        /*
        printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
        DSP = new llvmdsp(1, NULL, "process = +,+;");
        printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
        delete DSP;
        DSP = new llvmdsp(1, NULL, "process = +;");
        printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
        delete DSP;
        DSP = new llvmdsp(1, NULL, "process = +,+,+,+;");
        printf("DSP in/out %d %d\n", DSP->getNumInputs(), DSP->getNumOutputs());
        */
        
    }
    
    
	
	snprintf(appname, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
	snprintf(rcfilename, 255, "%s/.%s-%src", home, appname, argv[1]);

	GUI* interface 	= new GTKUI(filename, &argc, &argv);
	FUI* finterface	= new FUI();
    
	DSP->buildUserInterface(interface);
	DSP->buildUserInterface(finterface);

#ifdef HTTPCTRL
	httpdUI* httpdinterface = new httpdUI(appname, argc, argv);
	DSP->buildUserInterface(httpdinterface);
#endif

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(filename, argc, argv);
	DSP->buildUserInterface(oscinterface);
#endif
  
	jackaudio audio;
    if (!audio.init(filename, DSP)) {
        return 0;
    }
	finterface->recallState(rcfilename);
	audio.start();
  
#ifdef HTTPCTRL
	httpdinterface->run();
#endif

#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();
    
    audio.stop();
    finterface->saveState(rcfilename);
    delete(interface);
    delete(finterface);
    //deleteDSPInstance(DSP);
    delete DSP;
    
    deleteDSPFactory(factory3);
    //deleteDSPFactory(factory4);
     
    //deleteAllDSPFactories();
  	return 0;
}

