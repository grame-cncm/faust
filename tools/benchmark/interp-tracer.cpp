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

 ************************************************************************/

#include <libgen.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "faust/audio/dummy-audio.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/faustgtk.h"
#include "faust/misc.h"

using namespace std;

//----------------------------------------------------------------------------
// DSP control UI
//----------------------------------------------------------------------------

struct CheckControlUI : public MapUI {
    
    struct ZoneDesc {
        
        FAUSTFLOAT fInit;
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fStep;
        
        ZoneDesc(FAUSTFLOAT init,
                 FAUSTFLOAT min,
                 FAUSTFLOAT max,
                 FAUSTFLOAT step)
            :fInit(init), fMin(min), fMax(max), fStep(step)
        {}
    };
    
    vector<pair<FAUSTFLOAT*, ZoneDesc> > fControlZone;
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addButton(label, zone);
        addItem(zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0));
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addCheckButton(label, zone);
        addItem(zone, FAUSTFLOAT(1), FAUSTFLOAT(1), FAUSTFLOAT(1), FAUSTFLOAT(0));
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        addItem(zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        addItem(zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        addItem(zone, init, min, max, step);
    }
    
    void addItem(FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        fControlZone.push_back(make_pair(zone, ZoneDesc(init, min, max, step)));
    }

};

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    char name[256];
    char filename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    
    int trace_mode = lopt(argv, "-trace", 0);
    bool is_control = isopt(argv, "-control");
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || trace_mode < 0 || trace_mode > 5) {
        cout << "interp-trace -trace <1-5> -control [additional Faust options (-ftz xx)] foo.dsp" << endl;
        cout << "-control to activate min/max control check\n";
        cout << "-trace 1 to collect FP_SUBNORMAL only\n";
        cout << "-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN\n";
        cout << "-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO\n";
        cout << "-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, fails at first FP_INFINITE or FP_NAN\n";
        cout << "-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, continue after FP_INFINITE or FP_NAN\n";
        exit(EXIT_FAILURE);
    }
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-trace" || string(argv[i]) == "-control") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
        cout << argv[i] << " ";
    }
    cout << endl;
    
    argv1[argc1] = 0;  // NULL terminated argv
    
    cout << "Using interpreter backend" << endl;
    if (trace_mode > 0) {
        char mode[8]; sprintf(mode, "%d", trace_mode);
        setenv("FAUST_INTERP_TRACE", mode, 1);
    }
    
    string error_msg;
    // argc : without the filename (last element);
    dsp_factory* factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
    
    if (!factory) {
        cerr << "Cannot create factory : " << error_msg << endl;
        exit(EXIT_FAILURE);
    }
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "Cannot create instance "<< endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "getName " << factory->getName() << endl;
    
    dummyaudio audio(44100, 512, INT_MAX);
    if (!audio.init(filename, DSP)) {
        return 0;
    }
    
    GUI* interface = new GTKUI(filename, &argc, &argv);
    DSP->buildUserInterface(interface);
    
    if (is_control) {
        CheckControlUI ctl;
        DSP->buildUserInterface(&ctl);
        cout << "Check control min/max for " << ctl.fControlZone.size() << " controls" << endl;
        for (int index = 0; index < ctl.fControlZone.size(); index++) {
            cout << "------------------------------" << endl;
            cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
            FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
            FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
            FAUSTFLOAT init = ctl.fControlZone[index].second.fInit;
            // Test min
            cout << "Min: " << min << endl;
            *ctl.fControlZone[index].first = min;
            audio.render();
            *ctl.fControlZone[index].first = init; // reset to init
            // Test max
            cout << "Max: " << max << endl;
            *ctl.fControlZone[index].first = max;
            audio.render();
            *ctl.fControlZone[index].first = init; // reset to init
        }
        goto end;
    } else {
        audio.start();
    }
   
    interface->run();
    audio.stop();
    
end:
    
    delete DSP;
    delete interface;
    
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    return 0;
}

