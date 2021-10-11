/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

//#define FAUSTFLOAT double

#include "faust/gui/GTKUI.h"
#include "faust/gui/OSCUI.h"
#include "faust/gui/FUI.h"
#include "faust/misc.h"
#include "faust/dsp/proxy-osc-dsp.h"

using namespace std;

// Usage: faust-osc-controller /clarinet localhost -port 5001 -outport 5000 -xmit 1

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static string replaceChar(string str, char src, char dst)
{
    replace(str.begin(), str.end(), src, dst);
    return str;
}

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(rcfilename, 255, "%s/.%s%src", home, name, replaceChar(argv[1], '/', '_').c_str());
    
    if (isopt(argv, "-h") || isopt(argv, "-help")) {
        cout << "faust-osc-controller root [-ip <host_ip>] [-port <port>] [-outport <port>]" << endl;
        cout << "Set root to the OSC root name (like '/freeverb')\n";
        cout << "Use '-ip <host_ip>' to set the remote application IP address (default 'localhost')\n";
        cout << "Use '-port <port>' to set the OSC input port\n";
        cout << "Use '-outport <port>' to set the OSC output port\n";
        exit(EXIT_FAILURE);
    }
    
    const char* ip = lopts(argv, "-ip", "localhost");
    int in_port = lopt(argv, "-port", 5511);
    int out_port = lopt(argv, "-outport", 5510);    
    
    dsp* DSP = nullptr;
    try {
        DSP = new proxy_osc_dsp(ip, argv[1], in_port, out_port);
    } catch (...) {
        cerr << "Cannot allocate proxy_osc_dsp..." << endl;
        exit(EXIT_FAILURE);
    }
    
    // OSC controller
    OSCUI oscinterface(argv[1], argc, argv);
    DSP->buildUserInterface(&oscinterface);
    oscinterface.run();
    
    // UI
    GTKUI interface(argv[1], &argc, &argv);
    DSP->buildUserInterface(&interface);
    
    // State (after UI construction)
    FUI finterface;
    DSP->buildUserInterface(&finterface);
    finterface.recallState(rcfilename);
    
    interface.run();
    
    finterface.saveState(rcfilename);
    
    delete DSP;
    return 0;
}
