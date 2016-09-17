/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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
#include <iostream>

#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/gui/faustgtk.h"
#include "faust/audio/jack-dsp.h"

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

std::list<GUI*> GUI::fGuiList;

int main(int argc, char *argv[])
{
   
    long is_llvm = isopt(argv, "-llvm");
    long is_interp = isopt(argv, "-interp");
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || (!is_llvm && !is_interp)) {
        std::cout << "dynamic-jack-gtk [-llvm] [-interp] <compiler-options> foo.dsp" << std::endl;
        exit(1);
    }
    
    dsp_factory* factory = 0;
    dsp* DSP = 0;
   
    std::string error_msg;
    if (is_llvm) {
        std::cout << "Using LLVM backend" << std::endl;
        factory = createDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], "", error_msg, -1);
    } else {
        std::cout << "Using interpreter backend"<< std::endl;
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc-2, (const char**)&argv[1], error_msg);
    }

    if (factory) {
        DSP = factory->createDSPInstance();
        assert(DSP);
    } else {
        std::cout << "Cannot create factory : " << error_msg << std::endl;
        exit(1);
    }

    char appname[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(appname, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, appname, filename);
 
    GUI* interface 	= new GTKUI(filename, &argc, &argv);
    FUI* finterface	= new FUI();

    DSP->buildUserInterface(interface);
    DSP->buildUserInterface(finterface);

#ifdef HTTPCTRL
    httpdUI* httpdinterface = new httpdUI(appname, DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
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
    delete interface;
    delete finterface;
    delete DSP;

    if (is_llvm) {
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
    } else {
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    }
    
    return 0;
}

