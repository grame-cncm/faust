/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#include <libgen.h>

#include <iostream>
#include <string>

#include "faust/dsp/nam_faust_dsp.h"
#include "faust/audio/jack-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/meta.h"
#include "faust/misc.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static string get_option_value(int argc, char* argv[], const string& key)
{
    for (int i = 1; i < argc - 1; ++i) {
        if (string(argv[i]) == key) {
            return argv[i + 1];
        }
    }
    return "";
}

int main(int argc, char* argv[])
{
    bool use_double = isopt(argv, "-double");

    string model_path = get_option_value(argc, argv, "-model");
    if (model_path.empty() && argc > 1) {
        model_path = argv[argc - 1];
        if (!model_path.empty() && model_path[0] == '-') {
            model_path.clear();
        }
    }

    if (isopt(argv, "-h") || isopt(argv, "-help") || model_path.empty()) {
        cout << "nam-jack-gtk [-double] -model <model.nam>" << endl;
        cout << "or: nam-jack-gtk [-double] <model.nam>" << endl;
        return EXIT_FAILURE;
    }

    char filename[256];
    snprintf(filename, 255, "%s", basename(const_cast<char*>(model_path.c_str())));

    jackaudio audio;
    auto* nam_dsp = new nam::faust::NAMFaustDSP(model_path);
    dsp*  DSP = nam_dsp;

    if (use_double) {
#ifdef NAM_SAMPLE_FLOAT
        std::cerr << "-double is not available: NAM is compiled in float mode." << std::endl;
        delete nam_dsp;
        return EXIT_FAILURE;
#else
        DSP = new dsp_sample_adapter<double, float>(nam_dsp);
#endif
    }

    GUI* interface = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(interface);

    if (!audio.init(filename, DSP)) {
        delete DSP;
        delete interface;
        return EXIT_FAILURE;
    }

    if (!nam_dsp->isLoaded()) {
        std::cerr << "Failed to load NAM model: " << nam_dsp->lastError() << std::endl;
        delete DSP;
        delete interface;
        return EXIT_FAILURE;
    }

    audio.start();
    interface->run();
    audio.stop();

    delete DSP;
    delete interface;

    return 0;
}
