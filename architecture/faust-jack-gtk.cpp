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

#define LLVM 1

#ifdef LLVM
#include "faust/dsp/llvm-dsp.h"
#else
#include "faust/dsp/interpreter-dsp.h"
#endif

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

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

dsp* DSP;
dsp* DSP1;

std::list<GUI*> GUI::fGuiList;

int main(int argc, char *argv[])
{
	char	appname[256];
    char	filename[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");

#ifdef LLVM
    llvm_dsp_factory* factory = 0;
#else
    interpreter_dsp_factory* factory = 0;
#endif

    if (argc < 2) {
        printf("Usage: faust-jack-gtk args [file.dsp | file.bc]\n");
        exit(1);
    } else {
        
        int argc1 = 1;
        const char* argv1[argc1];
        argv1[0] = "-svg";
        std::string error_msg;
        
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
        */

        
    #ifdef LLVM
        factory = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "", error_msg, 0);
    #else
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], error_msg);
    #endif
        
        if (factory) {
            DSP = factory->createDSPInstance();
            assert(DSP);
         } else {
            printf("Cannot create factory : %s\n", error_msg.c_str());
            return 1;
        }
    }
    
    DSP->instanceInit(44100);
    //DSP->instanceClear();
  
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
    delete DSP;

#ifdef LLVM
    deleteDSPFactory(factory);
#else
    deleteInterpreterDSPFactory(factory);
#endif
  	return 0;
}

