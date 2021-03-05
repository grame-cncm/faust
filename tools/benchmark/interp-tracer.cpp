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
#include <unistd.h>

#include "faust/audio/dummy-audio.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/gui/meta.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/GTKUI.h"
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
        // Reset to init
        *zone = init;
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
    bool is_output = isopt(argv, "-output");
    bool is_control = isopt(argv, "-control");
    bool is_noui = isopt(argv, "-noui");
    int time_out = lopt(argv, "-timeout", 10);
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || trace_mode < 0 || trace_mode > 7) {
        cout << "interp-tracer [-trace <1-7>] [-control] [-output] [-noui] [-timeout <num>] [additional Faust options (-ftz xx)] foo.dsp" << endl;
        cout << "-control to activate min/max control check then setting all controllers (inside their range) in a random way\n";
        cout << "-output to display output samples\n";
        cout << "-noui to start the application without UI\n";
        cout << "-timeout <num> when used in -noui mode, to stop the application after a given timeout in seconds (default = 10s)\n";
        cout << "-trace 1 to collect FP_SUBNORMAL only\n";
        cout << "-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN\n";
        cout << "-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and CAST_INT_OVERFLOW\n";
        cout << "-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW and LOAD/STORE errors, fails at first FP_INFINITE, FP_NAN or LOAD/STORE errors\n";
        cout << "-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW and LOAD/STORE errors, continue after FP_INFINITE, FP_NAN or LOAD/STORE errors\n";
        cout << "-trace 6 to only check LOAD/STORE errors and continue\n";
        cout << "-trace 7 to only check LOAD/STORE errors and exit\n";
        exit(EXIT_FAILURE);
    }
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-control"
            || string(argv[i]) == "-noui"
            || string(argv[i]) == "-output") {
            continue;
        } else if (string(argv[i]) == "-trace" || string(argv[i]) == "-timeout") {
            i++;
            continue;
        }
        argv1[argc1++] = argv[i];
        cout << argv[i] << " ";
    }
    cout << endl;
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    cout << "Using interpreter backend" << endl;
    if (trace_mode > 0) {
        char mode[8]; sprintf(mode, "%d", trace_mode);
        setenv("FAUST_INTERP_TRACE", mode, 1);
    }
    
    if (is_output > 0) {
        char mode[8]; sprintf(mode, "%d", is_output);
        setenv("FAUST_INTERP_OUTPUT", mode, 1);
    }
    
    dsp_factory* factory = nullptr;
    dsp* DSP = nullptr;
    GUI* interface = nullptr;
    RandomControlUI random;
    
    try {
        
        string error_msg;
        // argc : without the filename (last element)
        factory = createInterpreterDSPFactoryFromFile(argv[argc-1], argc1, argv1, error_msg);
        
        if (!factory) {
            cerr << error_msg;
            exit(EXIT_FAILURE);
        }
        
        DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance " << endl;
            exit(EXIT_FAILURE);
        }
        
        if (isopt(argv, "-double")) {
            cout << "Running in double..." << endl;
        }
        
        cout << "getName " << factory->getName() << endl;
        dummyaudio_real<float>* dummy_driver_float = nullptr;
        dummyaudio_real<double>* dummy_driver_double = nullptr;
        
        if (isopt(argv, "-double")) {
            dummy_driver_double = new dummyaudio_real<double>(44100, 16, INT_MAX);
        } else {
            dummy_driver_float = new dummyaudio_real<float>(44100, 16, INT_MAX);
        }
        
        if (dummy_driver_float) {
            if (!dummy_driver_float->init(filename, DSP)) {
                exit(EXIT_FAILURE);
            }
        } else {
            if (!dummy_driver_double->init(filename, DSP)) {
                exit(EXIT_FAILURE);
            }
        }
        
        if (!is_noui) {
            interface = new GTKUI(filename, &argc, &argv);
            DSP->buildUserInterface(interface);
        }
        
        if (is_control) {
            
            // Check by setting each control to min, the max, then reset to init before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
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
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                    *ctl.fControlZone[index].first = init; // reset to init
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                    *ctl.fControlZone[index].first = init; // reset to init
                }
            }
            
            // Check by setting each control to max, then min, then keeping to min before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control min/max successively keeping min for " << ctl.fControlZone.size() << " controls" << endl;
                for (int index = 0; index < ctl.fControlZone.size(); index++) {
                    cout << "------------------------------" << endl;
                    cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    FAUSTFLOAT init = ctl.fControlZone[index].second.fInit;
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                    // Test min
                    cout << "Min: " << min << endl;
                    *ctl.fControlZone[index].first = min;
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                }
            }
            
            // Check by setting each control to min, then max, then keeping to max before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control min/max successively, keeping max for " << ctl.fControlZone.size() << " controls" << endl;
                for (int index = 0; index < ctl.fControlZone.size(); index++) {
                    cout << "------------------------------" << endl;
                    cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    FAUSTFLOAT init = ctl.fControlZone[index].second.fInit;
                    // Test min
                    cout << "Min: " << min << endl;
                    *ctl.fControlZone[index].first = min;
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    if (dummy_driver_float) {
                        dummy_driver_float->render();
                    } else {
                        dummy_driver_double->render();
                    }
                }
            }
            
            // Generate random values for controllers
            DSP->buildUserInterface(&random);
            cout << "------------------------------" << endl;
            cout << "Use RandomControlUI" << endl;
            for (int step = 0; step < 1000; step++) {
                cout << "Set random controllers, step: " << step <<  " until: " << 1000 << endl;
                random.update();
                if (dummy_driver_float) {
                    dummy_driver_float->render();
                } else {
                    dummy_driver_double->render();
                }
            }
            
            goto end;
            
        } else {
            if (dummy_driver_float) {
                dummy_driver_float->start();
            } else {
                dummy_driver_double->start();
            }
        }
        
        if (!is_noui) {
            interface->run();
        } else {
            cout << "Use Ctrl-c to Quit" << endl;
            usleep(time_out * 1e6);
        }
        
        if (dummy_driver_float) {
            dummy_driver_float->stop();
        } else {
            dummy_driver_double->stop();
        }
        
        delete dummy_driver_float;
        delete dummy_driver_double;
        
    } catch (...) {
        cout << endl;
        random.display();
    }
    
end:
    
    delete DSP;
    delete interface;
    
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    return 0;
}

