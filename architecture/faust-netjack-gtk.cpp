/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#include <libgen.h>
#include "faust/gui/FUI.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/GTKUI.h"
#include "faust/misc.h"
#include "faust/audio/netjack-dsp.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

std::list<GUI*> GUI::fGuiList;

int main(int argc, char* argv[])
{
	char appname[256];
    char filename[256];
	char rcfilename[256];
    std::string error_msg;
	char* home = getenv("HOME");
    llvm_dsp* DSP = NULL;
    llvm_dsp_factory* factory;
    
    int inc_arg = 0;
    
    int	celt = lopt(argv, "--celt", -1);
    const char* master_ip = lopts(argv, "--a", DEFAULT_MULTICAST_IP);
    int master_port = lopt(argv, "--p", DEFAULT_PORT);
    
    if (isopt(argv, "--celt")) inc_arg += 2;
    if (isopt(argv, "--a")) inc_arg += 2;
    if (isopt(argv, "--p")) inc_arg += 2;
    
    if (argc < 2) {
        printf("Usage: faust-netjack-gtk args [file.dsp | file.bc]\n");
        exit(1);
    } else {
        factory = createDSPFactoryFromFile(argv[1], argc-2-inc_arg, (const char**)&argv[inc_arg+2], "", error_msg);
        DSP = factory->createDSPInstance();
        if (!DSP) {
            std::cerr << error_msg;
            std::cerr << "Cannot load .dsp or .bc file" << std::endl;
            exit(1);
        }
    }

	snprintf(appname, 256, "%s", basename(argv[0]));
    snprintf(filename, 256, "%s", basename(argv[argc-1]));
	snprintf(rcfilename, 256, "%s/.%s-%src", home, appname, argv[1]);

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

	netjackaudio audio(celt, master_ip, master_port, DEFAULT_MTU);
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
  	return 0;
}

