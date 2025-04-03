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
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <assert.h>

#include "faust/audio/dummy-audio.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-bench.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/gui/meta.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/MapUI.h"
#include "faust/misc.h"

#define MEMORY_READER
#include "faust/gui/SoundUI.h"

using namespace std;

static MemoryReader* memory_reader = new MemoryReader();
static SoundUI* sound_ui = new SoundUI("", -1, memory_reader, (sizeof(FAUSTFLOAT) == sizeof(double)));

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << "item: " << list[i] << "\n";
    }
}

static void testProgram(const string& code, dsp* DSP)
{
    string error_msg;
    dsp_factory* factory = createInterpreterDSPFactoryFromString("FaustDSP", code, 0, nullptr, error_msg);
    assert(factory);
    dsp* tester = factory->createDSPInstance();
    assert(tester);
    dsp* combined = createDSPSplitter(tester, DSP, error_msg);
    if (combined) {
        cout << "----[" << code << "]----" << endl;
        dummyaudio_real<float> audio(44100, 16, INT_MAX, -1, false, true);
        if (!audio.init("dummy", combined)) {
            exit(EXIT_FAILURE);
        }
        for (int step = 0; step < 1000; step++) {
            audio.render();
        }
        delete combined;
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    } else {
        cerr << error_msg;
    }
}

//----------------------------------------------------------------------------
// DSP control UI
//----------------------------------------------------------------------------

struct CheckControlUI : public MapUI {
    
    bool fReset = true;
    string fName;
    struct ZoneDesc {
        
        string fLabel;
        FAUSTFLOAT fInit;
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fStep;
        
        ZoneDesc(const string& label,
                 FAUSTFLOAT init,
                 FAUSTFLOAT min,
                 FAUSTFLOAT max,
                 FAUSTFLOAT step)
        :fLabel(label), fInit(init), fMin(min), fMax(max), fStep(step)
        {}
    };
    
    CheckControlUI(const string& name = ""):fName(name)
    {}
    
    vector<pair<FAUSTFLOAT*, ZoneDesc> > fControlZone;
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addButton(label, zone);
        addItem(label, zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0));
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        MapUI::addCheckButton(label, zone);
        addItem(label, zone, FAUSTFLOAT(1), FAUSTFLOAT(1), FAUSTFLOAT(1), FAUSTFLOAT(0));
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        addItem(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        addItem(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        addItem(label, zone, init, min, max, step);
    }
    
    void addItem(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        // Reset to init
        if (fReset) *zone = init;
        addZoneLabel(label, zone);
        fControlZone.push_back(make_pair(zone, ZoneDesc(label, init, min, max, step)));
    }
    
    void display()
    {
        cout << "--------- Control state ---------"  << endl;
        ofstream out(fName + "rc");
        for (const auto& it : fPathZoneMap) {
            out << (std::to_string(*it.second) + " " + it.first + " \n");
            cout << ("Control : " + it.first + " = " + std::to_string(*it.second) + "\n");
        }
        out.close();
    }
    
};

int main(int argc, char* argv[])
{
    char name[256];
    char filename[256];
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    
    int trace_mode = lopt(argv, "-trace", 0);
    bool is_input = isopt(argv, "-input");
    bool is_output = isopt(argv, "-output");
    bool is_control = isopt(argv, "-control");
    int time_out = lopt(argv, "-timeout", 10);
    
    if (isopt(argv, "-h") || isopt(argv, "-help") || trace_mode < 0 || trace_mode > 6) {
        cout << "interp-tracer [-trace <1-6>] [-control] [-output] [-noui] [-timeout <num>] [additional Faust options (-ftz xx)] foo.dsp" << endl;
        cout << "-control to activate min/max control check then setting all controllers (inside their range) in a random way\n";
        cout << "-input to test effects with various test signals (impulse, noise)\n";
        cout << "-output to display output samples\n";
        cout << "-timeout <num> to stop the application after a given timeout in seconds (default = 10s)\n";
        cout << "-trace 1 to collect FP_SUBNORMAL only\n";
        cout << "-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN\n";
        cout << "-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW and NEGATIVE_BITSHIFT\n";
        cout << "-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW, NEGATIVE_BITSHIFT and LOAD/STORE errors, fails at first FP_INFINITE, FP_NAN, CAST_INT_OVERFLOW or LOAD/STORE errors\n";
        cout << "-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW, NEGATIVE_BITSHIFT and LOAD/STORE errors, continue after FP_INFINITE, FP_NAN or CAST_INT_OVERFLOW, fails after LOAD/STORE errors\n";
        cout << "-trace 6 to only check LOAD/STORE errors and exit\n";
        exit(EXIT_FAILURE);
    }
    
    cout << "Filename: " << argv[argc-1] << endl;
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    int argc1 = 0;
    const char* argv1[64];
    
    cout << "Compiled with additional options : ";
    for (int i = 1; i < argc-1; i++) {
        if (string(argv[i]) == "-control"
            || string(argv[i]) == "-noui"
            || string(argv[i]) == "-input"
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
        char mode[8]; snprintf(mode, sizeof(mode), "%d", trace_mode);
        setenv("FAUST_INTERP_TRACE", mode, 1);
    }
    
    if (is_output > 0) {
        char mode[8]; snprintf(mode, sizeof(mode), "%d", is_output);
        setenv("FAUST_INTERP_OUTPUT", mode, 1);
    }
    
    dsp_factory* factory = nullptr;
    dsp* DSP = nullptr;
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
        dummyaudio_base* audio = nullptr;
        
        if (isopt(argv, "-double")) {
            audio = new dummyaudio_real<double>(44100, 16, INT_MAX, -1, false, trace_mode == 4);
        } else {
            audio = new dummyaudio_real<float>(44100, 16, INT_MAX, -1, false, trace_mode == 4);
        }
        if (!audio->init(filename, DSP)) {
            exit(EXIT_FAILURE);
        }
        
        // Soundfile setting
        DSP->buildUserInterface(sound_ui);
        
        if (is_control) {
            
            // Check by setting each control to min, the max, then reset to init before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control min/max for " << ctl.fControlZone.size() << " controls" << endl;
                for (size_t index = 0; index < ctl.fControlZone.size(); index++) {
                    cout << "------------------------------" << endl;
                    cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    FAUSTFLOAT init = ctl.fControlZone[index].second.fInit;
                    // Test min
                    cout << "Min: " << min << endl;
                    *ctl.fControlZone[index].first = min;
                    audio->render();
                    *ctl.fControlZone[index].first = init; // reset to init
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    audio->render();
                    *ctl.fControlZone[index].first = init; // reset to init
                }
            }
            
            // Check by setting each control to max, then min, then keeping to min before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control min/max successively keeping min for " << ctl.fControlZone.size() << " controls" << endl;
                for (size_t index = 0; index < ctl.fControlZone.size(); index++) {
                    cout << "------------------------------" << endl;
                    cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    audio->render();
                    // Test min
                    cout << "Min: " << min << endl;
                    *ctl.fControlZone[index].first = min;
                    audio->render();
                }
            }
            
            // Check by setting each control to min, then max, then keeping to max before going to next one
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control min/max successively, keeping max for " << ctl.fControlZone.size() << " controls" << endl;
                for (size_t index = 0; index < ctl.fControlZone.size(); index++) {
                    cout << "------------------------------" << endl;
                    cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    // Test min
                    cout << "Min: " << min << endl;
                    *ctl.fControlZone[index].first = min;
                    audio->render();
                    // Test max
                    cout << "Max: " << max << endl;
                    *ctl.fControlZone[index].first = max;
                    audio->render();
                }
            }
            
            // Check by setting each control to zero if contained in the [min..max] range
            {
                CheckControlUI ctl;
                DSP->buildUserInterface(&ctl);
                
                cout << "------------------------------" << endl;
                cout << "Check control to zero if contained in the [min..max] range" << endl;
                for (size_t index = 0; index < ctl.fControlZone.size(); index++) {
                    FAUSTFLOAT min = ctl.fControlZone[index].second.fMin;
                    FAUSTFLOAT max = ctl.fControlZone[index].second.fMax;
                    if (min < 0 && max > 0) {
                        cout << "------------------------------" << endl;
                        cout << "Control: " << ctl.getParamAddress(ctl.fControlZone[index].first) << endl;
                        // Test zero
                        *ctl.fControlZone[index].first = 0;
                        audio->render();
                    }
                }
            }
            
            // Generate random values for controllers
            DSP->buildUserInterface(&random);
            cout << "------------------------------" << endl;
            cout << "Use RandomControlUI" << endl;
            for (int step = 0; step < 10; step++) {
                cout << "Set random controllers, step: " << step <<  " until: " << 10 << endl;
                random.update();
                audio->render();
            }
            
            goto end;
            
        } else if (is_input) {
            
            // Test with impulse and noise
            cout << "------------------------------" << endl;
            cout << "-------- Test impulse --------" << endl;
            testProgram("process = 1-1';", DSP->clone());
            cout << "------------------------------" << endl;
            cout << "-------- Test noise ----------" << endl;
            testProgram("import(\"stdfaust.lib\"); process = no.noise;", DSP->clone());
            
            goto end;
            
        } else {
            audio->start();
        }
        
        cout << "Use Ctrl-c to Quit" << endl;
        usleep(time_out * 1e6);
        
        audio->stop();
        delete audio;
        
    } catch (...) {
        cout << endl;
        random.display();
        string fn = string(filename);
        CheckControlUI ctl(fn.substr(0, fn.length()-4));
        ctl.fReset = false;
        DSP->buildUserInterface(&ctl);
        ctl.display();
    }
    
end:
    
    delete DSP;
    printList(factory->getWarningMessages());
    deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    return 0;
}

