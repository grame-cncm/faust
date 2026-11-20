/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public License
 as published by the Free Software Foundation; either version 2.1 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************
 ************************************************************************/

#ifdef WIN32
#pragma warning (disable: 4244 4800 4267)
#define _CRT_SECURE_NO_WARNINGS
#else
#include <Carbon/Carbon.h>
#endif

#include "faustgen_factory.h"
#include "faustgen_cache.h"
#include "faustgen~.h"

// The report clock's callback (defined with faustgen::report)
static void report_tick(faustgen* x);

using namespace std;

// globals
t_jrgba faustgen::gDefaultColor = {-1., -1., -1., -1.};

std::map<string, faustgen_factory*> faustgen_factory::gFactoryMap;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

namespace {

// GUI keeps a module-wide registry, whereas factories have independent
// locks. This lock serializes registry mutation with a global GUI refresh.
std::recursive_mutex gGUIRegistryMutex;
using RecursiveLock = std::lock_guard<std::recursive_mutex>;
using TryRecursiveLock = std::unique_lock<std::recursive_mutex>;

}

//====================
// Faust DSP Instance
//====================

// Allocate or reuse a factory for the named DSP group and track this instance
bool faustgen::allocate_factory(const string& effect_name)
{
    bool res = false;
    
    if (faustgen_factory::gFactoryMap.find(effect_name) != faustgen_factory::gFactoryMap.end()) {
        fDSPfactory = faustgen_factory::gFactoryMap[effect_name];
    } else {
        fDSPfactory = new faustgen_factory(effect_name);
        faustgen_factory::gFactoryMap[effect_name] = fDSPfactory;
        res = true;
    }
    
    fDSPfactory->add_instance(this);
    return res;
}

// Construct a faustgen~ object from a Max instantiation
faustgen::faustgen(t_symbol* sym, long ac, t_atom* argv)
{
    m_siginlets = 0;
    m_sigoutlets = 0;
    
    fDSP = nullptr;
    fMCDSP = nullptr;
    fDSPUI = nullptr;
    fMidiUI = nullptr;
    fOSCUI = nullptr;
    fSavedUI = nullptr;
    fDSPfactory = nullptr;
    fEditor = nullptr;
    fMute = false;
    fRNBOAttr = false;
    fReportPeriod = 0;
    fReportClock = clock_new((t_object*)this, (method)report_tick);
   
    // sym can be "faustgen~" or "mc.faustgen~"
    m_is_mc = (string(sym->s_name) == "mc.faustgen~");
    
    fMidiHandler.startMidi();
    
    // Allocate factory with a given "name"
    int i;
    t_atom* ap;
    bool res = false;
    
    for (i = 0, ap = argv; i < ac; i++, ap++) {
        if (atom_gettype(ap) == A_SYM) {
            // Check "@rnbo" attribute
            if (strcmp(atom_getsym(ap)->s_name, "@rnbo") == 0) {
                fRNBOAttr = true;
            // Check "@report <ms>" attribute
            } else if (strcmp(atom_getsym(ap)->s_name, "@report") == 0) {
                if (i + 1 < ac && (atom_gettype(ap + 1) == A_LONG || atom_gettype(ap + 1) == A_FLOAT)) {
                    fReportPeriod = std::max(0L, long(atom_getfloat(ap + 1)));
                    i++; ap++;
                }
            } else {
                res = allocate_factory(atom_getsym(ap)->s_name);
            }
        }
    }
    
    // Empty (= no name) faustgen~ will be internally separated as groups with different names
    if (!fDSPfactory) {
        string effect_name;
        effect_name = "faustgen_factory-" + to_string(faustgen_factory::gFaustCounter);
        res = allocate_factory(effect_name);
    }
    
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    if (gDefaultColor.red == -1.) {
        jbox_get_color(box, &gDefaultColor);
    }
    
    // Needed to script objects
    char name[64];
    snprintf(name, 64, "faustgen-%lld", (long long)this);
    jbox_set_varname(box, gensym(name));
    
    // Fetch the data inside the max patcher using the dictionary
    t_dictionary* d = 0;
    if ((d = (t_dictionary*)gensym("#D")->s_thing) && res) {
        fDSPfactory->getfromdictionary(d);
    }
    
    create_dsp(true);
    schedule_report();
}

// Called upon deleting the object inside the patcher
faustgen::~faustgen()
{
    // No report once the DSP is gone
    clock_unset(fReportClock);
    object_free(fReportClock);
    fReportClock = nullptr;
    
    // Stop audio work before removing the instance
    fDSPfactory->lock_audio();
    free_dsp();
    fDSPfactory->unlock_audio();
    
    if (fEditor) {
        object_free(fEditor);
        fEditor = nullptr;
    }
    
    fMidiHandler.stopMidi();
    
    // remove_instance may delete the factory, so do not touch fDSPfactory after this call
    fDSPfactory->remove_instance(this);
    fDSPfactory = nullptr;
}

// Fill the Max assist strings for inlets/outlets
void faustgen::assist(void* b, long msg, long a, char* dst)
{
    fDSPfactory->lock_audio();
    fDSPfactory->lock_ui();
    {
        if (m_is_mc) {
            if (msg == ASSIST_INLET) {
                snprintf(dst, 512, "(messages/multi-channel signal) : Audio Input %ld", (a+1));
            } else if (msg == ASSIST_OUTLET) {
                if (a == 0) {
                    snprintf(dst, 512, "(multi-channel signal) : Audio Output %ld", (a+1));
                } else if (a == 1) {
                    snprintf(dst, 512, "(list) : [path, cur|init, min, max]*");
                } else {
                    snprintf(dst, 512, "(int) : raw MIDI bytes*");
                }
            }
        } else {
            if (msg == ASSIST_INLET) {
                if (a == 0) {
                    if (fDSP->getNumInputs() == 0) {
                        snprintf(dst, 512, "(messages)");
                    } else {
                        snprintf(dst, 512, "(messages/signal) : Audio Input %ld", (a+1));
                    }
                } else if (a < fDSP->getNumInputs()) {
                    snprintf(dst, 512, "(signal) : Audio Input %ld", (a+1));
                }
            } else if (msg == ASSIST_OUTLET) {
                if (a < fDSP->getNumOutputs()) {
                    snprintf(dst, 512, "(signal) : Audio Output %ld", (a+1));
                } else if (a == fDSP->getNumOutputs()) {
                    snprintf(dst, 512, "(list) : [path, cur|init, min, max]*");
                } else {
                    snprintf(dst, 512, "(int) : raw MIDI bytes*");
                }
            }
        }
    }
    fDSPfactory->unlock_ui();
    fDSPfactory->unlock_audio();
}

// Release DSP, UI, MIDI, and OSC resources
void faustgen::free_dsp()
{
    // Keep the global GUI registry stable while its MIDI and OSC entries are
    // removed. Deleting an OSCUI also stops its process-wide OSC streams.
    RecursiveLock gui_lock(gGUIRegistryMutex);
    RecursiveLock osc_lock(oscfaust::OSCControler::globalMutex());

    // Save controller state
    if (fSavedUI) {
        fSavedUI->save();
        delete fSavedUI;
        fSavedUI = nullptr;
    }
    
    // The multichannel adapter borrows fDSP, so release it first.
    delete fMCDSP;
    fMCDSP = nullptr;

    // A polyphonic DSP keeps the MidiUI as its MIDI interface.  Destroy the
    // DSP while that interface is still alive so it can unregister itself.
    delete fDSP;
    fDSP = nullptr;

    delete fMidiUI;
    fMidiUI = nullptr;
    
    delete fOSCUI;
    fOSCUI = nullptr;
 
    delete fDSPUI;
    fDSPUI = nullptr;
}

// Parse a JSON string into a Max dictionary object
t_dictionary* faustgen::json_reader(const char* jsontext)
{
    t_dictionary* d = nullptr;
    t_max_err err;
    t_atom result[1];
    t_object* jsonreader = (t_object*)object_new(_sym_nobox, _sym_jsonreader);
    
    err = (t_max_err)object_method(jsonreader, _sym_parse, jsontext, result);
    if (!err) {
        t_object* ro = (t_object*)atom_getobj(result);
        if (ro) {
            if (object_classname_compare(ro, _sym_dictionary)) {
                d = (t_dictionary*)ro;
            } else {
                object_free(ro);
            }
        }
    }
    object_free(jsonreader);
    return d;
}

// Called upon sending the object a message inside the max patcher
// Allows to set a value to the Faust module's parameter, or a list of values
void faustgen::anything(long inlet, t_symbol* s, long ac, t_atom* av)
{
    fDSPfactory->lock_ui();
    {
        bool res = false;
        string name = string((s)->s_name);
        
        // If no argument is there, consider it as a toggle message for a button
        if (ac == 0 && fDSPUI->isValue(name)) {
            
            FAUSTFLOAT off = FAUSTFLOAT(0.0);
            FAUSTFLOAT on = FAUSTFLOAT(1.0);
            fDSPUI->setValue(name, off);
            fDSPUI->setValue(name, on);
            
            // Safe toggle using a local atom (ac can be 0, so av may be nullptr)
            t_atom toggle_atom[1];
            toggle_atom[0].a_type = A_FLOAT;
            toggle_atom[0].a_w.w_float = off;
            anything(inlet, s, 1, toggle_atom);
            
            goto unlock;
            
        } else if (mspUI::checkDigit(name)) { // List of values
            
            int pos, ndigit = 0;
            for (pos = name.size() - 1; pos >= 0; pos--) {
                if (isdigit(name[pos]) || name[pos] == ' ') {
                    ndigit++;
                } else {
                    break;
                }
            }
            pos++;
            
            string prefix = name.substr(0, pos);
            string num_base = name.substr(pos);
            int num = atoi(num_base.c_str());
            
            int i;
            t_atom* ap;
            
            // Increment ap each time to get to the next atom
            for (i = 0, ap = av; i < ac; i++, ap++) {
                FAUSTFLOAT value;
                switch (atom_gettype(ap)) {
                    case A_LONG:
                        value = FAUSTFLOAT(ap[0].a_w.w_long);
                        break;
                    case A_FLOAT:
                        value = FAUSTFLOAT(ap[0].a_w.w_float);
                        break;
                    default:
                        post("Invalid argument in parameter setting");
                        goto unlock;
                }
                
                string num_val = to_string(num + i);
                stringstream param_name; param_name << prefix;
                for (int i = 0; i < ndigit - mspUI::countDigit(num_val); i++) {
                    param_name << ' ';
                }
                param_name << num_val;
                
                // Try special naming scheme for list of parameters
                res = fDSPUI->setValue(param_name.str(), value);
                
                // Otherwise try standard name
                if (!res) {
                    res = fDSPUI->setValue(name, value);
                }
                if (!res) {
                    post("Unknown parameter : %s", (s)->s_name);
                }
            }
            
        } else if (ac > 0) {
            // Standard parameter name
            FAUSTFLOAT value;
            if (atom_gettype(&av[0]) == A_LONG) {
                value = FAUSTFLOAT(av[0].a_w.w_long);
            } else if (atom_gettype(&av[0]) == A_FLOAT) {
                value = FAUSTFLOAT(av[0].a_w.w_float);
            } else {
                post("Invalid argument in parameter setting");
                goto unlock;
            }
            res = fDSPUI->setValue(name, value);
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        } else {
            post("No value provided for parameter : %s", (s)->s_name);
        }
    }
        
    unlock:
        fDSPfactory->unlock_ui();
}

// Forward compile options to the factory
void faustgen::compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv)
{
    fDSPfactory->compileoptions(inlet, s, argc, argv);
}

// Empty the disk cache of compiled code: the objects compile their source again when
// they are next compiled (the current DSPs are kept)
void faustgen::clearcache(long inlet, t_symbol* s, long argc, t_atom* argv)
{
    int removed = faustgen_cache::clear();
    post("Cache of compiled code '%s' cleared, %d entries removed", faustgen_cache::directory().c_str(), removed);
}

// Load Faust source code from disk
void faustgen::read(long inlet, t_symbol* s)
{
    fDSPfactory->read(inlet, s);
}

// Save Faust source code to disk
void faustgen::write(long inlet, t_symbol* s)
{
    fDSPfactory->write(inlet, s);
}

// Recreate the DSP with a requested number of voices
void faustgen::polyphony(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac < 1) {
        post("polyphony requires a long argument (voices)");
    } else {
        
        fDSPfactory->lock_audio();
        fDSPfactory->lock_ui();
        {
            free_dsp();
            fDSP = fDSPfactory->create_dsp_instance(av[0].a_w.w_long);
            assert(fDSP);
            fVoices = fDSPfactory->last_voices();
            
            // Init all controller (UI, MIDI, Soundfile)
            init_controllers();
            
            // Prepare JSON
            fDSPfactory->make_json(fDSP);
            
            // Initialize at the system's sampling rate
            fDSP->init(sys_getsr());
            
            // Polyphony changes the controls: all reported again
            fReported.clear();
        }
        fDSPfactory->unlock_ui();
        fDSPfactory->unlock_audio();
        
        // Mono and polyphonic voices are not the same wasm (internal or external memory)
        announce_dsp();
    }
}

// Reset controllers to init values and send [path, init, min, max]
void faustgen::init(long inlet, t_symbol* s, long ac, t_atom* av)
{
    // Reset internal state
    fSavedUI->reset();
    
    // Input controllers
    for (mspUI::iterator it = fDSPUI->begin2(); it != fDSPUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
    // Output controllers
    for (mspUI::iterator it = fDSPUI->begin4(); it != fDSPUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
}

// Emit current values for all input controls
void faustgen::dump_inputs()
{
    // Input controllers
    for (mspUI::iterator it = fDSPUI->begin2(); it != fDSPUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
}
// Emit current values for all output controls
void faustgen::dump_outputs()
{
    // Output controllers
    for (mspUI::iterator it = fDSPUI->begin4(); it != fDSPUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(m_control_outlet, 0, 4, myList);
    }
}

// Dump controllers as list of [path, cur, min, max]
void faustgen::dump(long inlet, t_symbol* s, long ac, t_atom* av)
{
    dump_inputs();
    dump_outputs();
}

// Send 'json <text>' on the control outlet: for a v8 or node.script object,
// which create_jsui does not reach (it only notifies js objects)
void faustgen::send_json()
{
    t_atom json;
    atom_setsym(&json, gensym(fDSPfactory->get_json()));
    outlet_anything(m_control_outlet, gensym("json"), 1, &json);
}

// Answer 'json' with the DSP's JSON on the control outlet
void faustgen::json(long inlet, t_symbol* s, long ac, t_atom* av)
{
    send_json();
}

// The report clock's callback, on the scheduler thread
static void report_tick(faustgen* x)
{
    x->report_changes();
}

// Start the report clock when 'report' is on, stop it otherwise
void faustgen::schedule_report()
{
    if (fReportPeriod > 0) {
        clock_fdelay(fReportClock, double(fReportPeriod));
    } else {
        clock_unset(fReportClock);
    }
}

// 'report <ms>': every ms, send on the control outlet the input controls
// whose value changed, whatever changed them (a message, MIDI, OSC, init,
// a preset), and the bargraphs that changed, instead of every bargraph at
// every audio block; as [path, cur, min, max], like 'dump'. A new DSP sends
// its JSON ('json <text>'), then all its controls. 'report 0' (the default)
// goes back to bargraphs at every block.
void faustgen::report(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac != 1 || (atom_gettype(&av[0]) != A_LONG && atom_gettype(&av[0]) != A_FLOAT)) {
        post("Should be : report <ms> (0 to stop)");
        return;
    }
    long period = std::max(0L, long(atom_getfloat(&av[0])));
    bool starting = (fReportPeriod == 0 && period > 0);
    fReportPeriod = period;
    if (starting) {
        // From the start: the JSON, then every control
        fDSPfactory->lock_ui();
        fReported.clear();
        fDSPfactory->unlock_ui();
        send_json();
    }
    schedule_report();
}

// Send the controls whose value changed since they were last sent
void faustgen::report_changes()
{
    struct Change { t_symbol* path; FAUSTFLOAT cur, min, max; };
    std::vector<Change> changes;
    
    // Collected under the lock, sent after it: what the outlet triggers
    // downstream may well come back to this object
    fDSPfactory->lock_ui();
    if (fDSPUI) {
        auto collect = [&](mspUI::iterator begin, mspUI::iterator end) {
            for (mspUI::iterator it = begin; it != end; it++) {
                FAUSTFLOAT cur = (*it).second->getValue();
                auto last = fReported.find((*it).first);
                bool same = (last != fReported.end())
                    && (last->second == cur || (std::isnan(last->second) && std::isnan(cur)));
                if (!same) {
                    fReported[(*it).first] = cur;
                    changes.push_back({gensym((*it).first.c_str()), cur,
                                       (*it).second->getMinValue(), (*it).second->getMaxValue()});
                }
            }
        };
        collect(fDSPUI->begin2(), fDSPUI->end2());
        collect(fDSPUI->begin4(), fDSPUI->end4());
    }
    fDSPfactory->unlock_ui();
    
    for (const Change& change : changes) {
        t_atom myList[4];
        atom_setsym(&myList[0], change.path);
        atom_setfloat(&myList[1], change.cur);
        atom_setfloat(&myList[2], change.min);
        atom_setfloat(&myList[3], change.max);
        outlet_list(m_control_outlet, 0, 4, myList);
    }
    
    schedule_report();
}

// Configure OSC destinations using 'IP inport outport xmit bundle'
void faustgen::osc(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac == 5) {
        
        // Validate argument types: host is symbol, others are longs
        if (atom_gettype(&av[0]) != A_SYM
            || atom_gettype(&av[1]) != A_LONG
            || atom_gettype(&av[2]) != A_LONG
            || atom_gettype(&av[3]) != A_LONG
            || atom_gettype(&av[4]) != A_LONG) {
            post("Should be : osc 'IP inport outport xmit(0|1|2) bundle(0|1)'");
            return;
        }
        
        fDSPfactory->lock_audio();
        fDSPfactory->lock_ui();
        {
            // OSCUI participates in GUI's process-wide registry and owns a
            // reference to process-wide OSC streams.
            RecursiveLock gui_lock(gGUIRegistryMutex);
            RecursiveLock osc_lock(oscfaust::OSCControler::globalMutex());

            delete fOSCUI;
            
            const char* argv1[32];
            int argc1 = 0;
            
            argv1[argc1++] = "Faust";
            
            argv1[argc1++]  = "-desthost";
            argv1[argc1++]  = atom_getsym(&av[0])->s_name;
            
            char inport[32];
            snprintf(inport, 32, "%ld", long(av[1].a_w.w_long));
            argv1[argc1++] = "-port";
            argv1[argc1++] = inport;
            
            char outport[32];
            snprintf(outport, 32, "%ld", long(av[2].a_w.w_long));
            argv1[argc1++] = "-outport";
            argv1[argc1++] = outport;
            
            char xmit[32];
            snprintf(xmit, 32, "%ld", long(av[3].a_w.w_long));
            argv1[argc1++] = "-xmit";
            argv1[argc1++] = xmit;
            
            char bundle[32];
            snprintf(bundle, 32, "%ld", long(av[4].a_w.w_long));
            argv1[argc1++] = "-bundle";
            argv1[argc1++] = bundle;
            
            fOSCUI = new OSCUI("Faust", argc1, (char**)argv1);
            fDSP->buildUserInterface(fOSCUI);
            fOSCUI->run();
            
            post(fOSCUI->getInfos().c_str());
        }
        fDSPfactory->unlock_ui();
        fDSPfactory->unlock_audio();
    } else {
        post("Should be : osc 'IP inport outport xmit(0|1|2) bundle(0|1)'");
    }
}

// Route raw MIDI bytes into the Faust MIDI handler
void faustgen::midievent(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if ((ac > 0) && (ac <= 3)) {
        for (int i = 0; i < ac; ++i) {
            if (atom_gettype(&av[i]) != A_LONG) {
                post("MIDI event bytes must be integers");
                return;
            }
        }
        int type = (int)av[0].a_w.w_long & 0xf0;
        int channel = (int)av[0].a_w.w_long & 0x0f;
        if (ac == 1) {
            fMidiHandler.handleSync(0.0, av[0].a_w.w_long);
        } else if (ac == 2) {
            fMidiHandler.handleData1(0.0, type, channel, av[1].a_w.w_long);
        } else if (ac == 3) {
            fMidiHandler.handleData2(0.0, type, channel, av[1].a_w.w_long, av[2].a_w.w_long);
        }
    }
}

// Add an extra Faust library path from a Max message
void faustgen::librarypath(long inlet, t_symbol* s)
{
    fDSPfactory->librarypath(inlet, s);
}

// Called when saving the Max patcher, this function saves the necessary data inside the json file (faust sourcecode)
void faustgen::appendtodictionary(t_dictionary* d)
{
    fDSPfactory->appendtodictionary(d);
}

// Restore state from a saved dictionary entry
void faustgen::getfromdictionary(t_dictionary* d)
{
    fDSPfactory->getfromdictionary(d);
}

// Called when the user double-clicks on the faustgen object inside the Max patcher
void faustgen::dblclick(long inlet)
{
    // Create a popup menu inside the Max patcher
    t_jpopupmenu* popup = jpopupmenu_create();
    jpopupmenu_additem(popup, 1, "Edit DSP code", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 2, "View DSP parameters", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 3, "View compile options", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 4, "View SVG diagram", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 5, "View Web documentation", NULL, 0, 0, NULL);
    jpopupmenu_additem(popup, 6, "View libraries", NULL, 0, 0, NULL);
    
    // Get mouse position
    int x,y;
    jmouse_getposition_global(&x, &y);
    t_pt coordinate;
    coordinate.x = x;
    coordinate.y = y;
    
    int choice = jpopupmenu_popup(popup, coordinate, 0);
    
    switch (choice) {
            
        case 1:
            // Open the text editor to allow the user to input Faust sourcecode
            display_dsp_source();
            break;
            
        case 2:
            // Display inside the max window the current values of the module's parameters, as well as their ranges
            display_dsp_params();
            break;
            
        case 3:
            // Display compiler options
            fDSPfactory->print_compile_options();
            break;
            
        case 4:
            // Open the SVG diagram file inside a web browser
            display_svg();
            break;
            
        case 5:
            // Open the documentation
            display_documentation();
            break;
            
        case 6:
            // Open the libraries
            display_libraries();
            break;
            
        default:
            break;
    }
    
    // Destroy the popup menu once this is done
    jpopupmenu_destroy(popup);
}

// Called when closing the text editor, calls for the creation of a new Faust module with the updated sourcecode
void faustgen::edclose(long inlet, char** source_code, long size)
{
    // Edclose "may" be called with an already deallocated object (like closing the patcher with a still opened editor)
    if (fDSP && fEditor) {
        fDSPfactory->update_sourcecode(size, *source_code);
        fEditor = nullptr;
    }
}

// Replace source code from RNBO codebox and rebuild DSP
void faustgen::update_sourcecode(const std::string& codebox)
{
    // Create a new DSP instance
    create_dsp(false);
    
    // faustgen~ state is modified...
    set_dirty();
    
    // Send a bang
    outlet_bang(m_control_outlet);
    
    // Set codebox code
    t_object *patcher, *box, *obj;
    object_obex_lookup(this, gensym("#P"), &patcher);
    
    // Loop through objects in the main patcher.
    if (fRNBOAttr && codebox != "") {
        bool subpatch_missing_reported = false;
        bool codebox_missing_reported = false;
        for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
            obj = jbox_get_object(box);
            if (obj && (object_classname(obj) == gensym("rnbo~"))) {
                // Found an rnbo~ object.
                t_patcher *subpatcher = NULL;
                long index = 0;
                subpatcher = (t_patcher*)object_subpatcher(obj, &index, NULL);
                if (subpatcher) {
                    t_box *sub_box = NULL;
                    // Loop through objects in the rnbo~ subpatcher.
                    for (sub_box = jpatcher_get_firstobject(subpatcher); sub_box; sub_box = jbox_get_nextobject(sub_box)) {
                        t_object *sub_obj = jbox_get_object(sub_box);
                        if (sub_obj && (object_classname(sub_obj) == gensym("codebox~"))) {
                            t_string* code = string_new(codebox.c_str());
                            object_method(sub_obj, gensym("setcode"), code);
                            object_free(code);
                        } else {
                            if (!codebox_missing_reported) {
                                post("rnbo~ does not have codebox~ inside");
                                codebox_missing_reported = true;
                            }
                        }
                    }
                } else {
                    if (!subpatch_missing_reported) {
                        post("rnbo~ does not have an accessible subpatcher");
                        subpatch_missing_reported = true;
                    }
                }
            }
        }
    }

}

// Process the signal data with the Faust module
inline void faustgen::perform(int vs, t_sample** inputs, long numins, t_sample** outputs, long numouts)
{
    // Clear outputs
    for (int chan = 0; chan < numouts; chan++) {
        memset(outputs[chan], 0, sizeof(t_sample) * vs);
    }
    
    // Possibly compute DSP
    if (!fMute && fDSPfactory->try_lock_audio()) {
        // Has to be tested again when the lock has been taken...
        if (fDSP) {
            if (m_is_mc) {
                // Not RT but simpler: adapt channel layout at first cycle or when the connected layout changes
                if (!fMCDSP || (fMCDSP && ((numins != fMCDSP->getNumInputs() || numouts != fMCDSP->getNumOutputs())))) {
                    delete fMCDSP;
                    fMCDSP = new dsp_adapter(fDSP, numins, fDSP->getNumOutputs(), 4096, false);
                    std::cout << "new dsp_adapter " << numins << " " << fDSP->getNumOutputs() << std::endl;
                }
                fMCDSP->compute(vs, reinterpret_cast<FAUSTFLOAT**>(inputs), reinterpret_cast<FAUSTFLOAT**>(outputs));
            } else {
                fDSP->compute(vs, reinterpret_cast<FAUSTFLOAT**>(inputs), reinterpret_cast<FAUSTFLOAT**>(outputs));
            }
            // Use the right outlet to output messages: at every block, unless
            // 'report' sends only the bargraphs that changed, from its clock
            if (fReportPeriod == 0) {
                dump_outputs();
            }
            // Done for fMidiUI and fOSCUI
            // Do not ever block the audio callback. A concurrent UI/OSC
            // reconfiguration simply defers this refresh to a later block.
            TryRecursiveLock gui_lock(gGUIRegistryMutex, std::try_to_lock);
            if (gui_lock.owns_lock()) {
                TryRecursiveLock osc_lock(oscfaust::OSCControler::globalMutex(), std::try_to_lock);
                if (osc_lock.owns_lock()) {
                    GUI::updateAllGuis();
                }
            }
        }
        fDSPfactory->unlock_audio();
    }
}

// Initialize DSP at host sample rate while preserving saved state
inline void faustgen::init(double samplerate)
{
    std::cout << "faustgen::init\n";
    
    // Save internal state
    fSavedUI->save();
    
    // Init with defaults
    fDSP->init(samplerate);
    
    // Load internal state
    fSavedUI->load();
}

// Display source code
void faustgen::display_dsp_source()
{
    if (fEditor) {
        // Editor already open, set it to to foreground
        object_attr_setchar(fEditor, gensym("visible"), 1);
    } else {
        // Create a text editor object
        fEditor = (t_object*)object_new(CLASS_NOBOX, gensym("jed"), this, 0);
        
        // Set the text inside the text editor to be fSourceCode
        object_method(fEditor, gensym("settext"), fDSPfactory->get_sourcecode(), gensym("utf-8"));
        object_attr_setchar(fEditor, gensym("scratch"), 1);
        char name[256];
        snprintf(name, 256, "DSP code : %s", fDSPfactory->get_name().c_str());
        object_attr_setsym(fEditor, gensym("title"), gensym(name));
    }
}

// Display the Faust dsp parameters along with their standard values
void faustgen::display_dsp_params()
{
    fDSPUI->displayControls();
}

// Display the Faust dsp SVG
void faustgen::display_svg()
{
    fDSPfactory->display_svg();
}

// Display the Faust documentation
void faustgen::display_documentation()
{
    fDSPfactory->display_documentation();
}

// Display the Faust libraries
void faustgen::display_libraries()
{
    fDSPfactory->display_libraries();
}

// Report a compilation error in Max
void faustgen::hilight_error(const string& error)
{
    object_error_obtrusive((t_object*)&m_ob, (char*)error.c_str());
}

// Build control, MIDI, soundfile, and state UIs for the DSP
void faustgen::init_controllers()
{
    // MidiUI is registered in GUI::fGuiList. Its replacement must not race
    // with GUI::updateAllGuis() in another faustgen~ audio callback.
    RecursiveLock gui_lock(gGUIRegistryMutex);

    // Initialize User Interface (here connnection with controls)
    delete fDSPUI;
    fDSPUI = new mspUI();
    fDSP->buildUserInterface(fDSPUI);
    
    // MIDI handling
    delete fMidiUI;
    fMidiUI = new MidiUI(&fMidiHandler);
    fDSP->buildUserInterface(fMidiUI);
    
    // State handling
    delete fSavedUI;
    fSavedUI = new SaveLabelUI();
    
    // Soundfile handling
    if (fDSPfactory->fSoundUI) {
        fDSP->buildUserInterface(fDSPfactory->fSoundUI);
    }
}

// Create and initialize a new DSP instance, wiring up audio and UI
void faustgen::create_dsp(bool init)
{
    fDSPfactory->lock_audio();
    fDSPfactory->lock_ui();
    {
        fDSP = fDSPfactory->create_dsp_aux();
        assert(fDSP);
        fVoices = fDSPfactory->last_voices();
        
        // Init all controllers (UI, MIDI, Soundfile)
        init_controllers();
        
        // Initialize at the system's sampling rate
        fDSP->init(sys_getsr());
        
        // Setup MAX audio IO
        bool dspstate = false;
        
        if ((m_siginlets != fDSP->getNumInputs()) || (m_sigoutlets != fDSP->getNumOutputs())) {
            // Number of ins/outs have changed... possibly stop IO
            dspstate = sys_getdspobjdspstate((t_object*)&m_ob);
            if (dspstate) {
                dsp_status("stop");
            }
        }
        
        setupIO(&faustgen::perform, &faustgen::init, fDSP->getNumInputs(), fDSP->getNumOutputs(), init);
        
        // Setup m_midi_outlet MIDI output handler
        fMidiHandler.m_midi_outlet = m_midi_outlet;
        
        // Load old controller state
        fDSP->buildUserInterface(fSavedUI);
        
        // Possibly restart IO
        if (dspstate) {
            dsp_status("start");
        }
        
        // A new DSP: every control is reported again, after its JSON
        fReported.clear();
    }
    fDSPfactory->unlock_ui();
    fDSPfactory->unlock_audio();
    
    // Outside the locks: the wasm compilation must not hold the audio back
    announce_dsp();
}

// A new DSP: its wasm for the phones first (when 'wasm' is set), then its JSON, to the
// js objects and, with 'report', on the control outlet. In that order, so that whoever
// hears of the new JSON finds the wasm that goes with it.
void faustgen::announce_dsp()
{
    export_wasm();
    create_jsui();
    if (fReportPeriod > 0) {
        send_json();
    }
}

// Write the DSP compiled to wasm in fWasmFolder, if set
void faustgen::export_wasm()
{
    if (fWasmFolder.empty()) {
        return;
    }
    string error;
    bool poly = fVoices > 0;
    if (fDSPfactory->write_wasm(fWasmFolder, poly, error)) {
        post("DSP compiled to wasm in %s%s", fWasmFolder.c_str(), poly ? " (polyphonic voice)" : "");
    } else {
        post("DSP not compiled to wasm: %s", error.c_str());
    }
}

// 'wasm <folder>': from now on, write each DSP compiled to wasm in folder, as faustwasm
// runs it on a phone (dsp-module.wasm and dsp-meta.json), starting with the current one;
// 'wasm' alone stops
void faustgen::wasm(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac == 0) {
        fWasmFolder.clear();
        return;
    }
    if (ac != 1 || atom_gettype(&av[0]) != A_SYM) {
        post("Should be : wasm <folder> (or wasm alone to stop)");
        return;
    }
    fWasmFolder = atom_getsym(&av[0])->s_name;
    // Without a trailing separator, which write_wasm adds
    while (fWasmFolder.size() > 1 && fWasmFolder.back() == '/') {
        fWasmFolder.pop_back();
    }
    export_wasm();
}

// Mark the patcher dirty so Max saves updated state
void faustgen::set_dirty()
{
    t_object* mypatcher;
    object_obex_lookup(&m_ob, gensym("#P"), &mypatcher);
    jpatcher_set_dirty(mypatcher, 1);
}

// Search the adc/dac object in the patcher.
t_pxobject* faustgen::check_dac()
{
    t_object *patcher, *box, *obj;
    object_obex_lookup(this, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        if (obj) {
            if ((object_classname(obj) == gensym("dac~"))
                || (object_classname(obj) == gensym("ezdac~"))
                || (object_classname(obj) == gensym("ezadc~"))
                || (object_classname(obj) == gensym("adc~"))
                || (object_classname(obj) == gensym("mc.dac~"))
                || (object_classname(obj) == gensym("mc.ezdac~"))
                || (object_classname(obj) == gensym("mc.ezadc~"))
                || (object_classname(obj) == gensym("mc.adc~"))) {
                return (t_pxobject*)box;
            }
        }
    }
    
    return nullptr;
}

// Notify any js objects in the patcher with the current JSON UI
void faustgen::create_jsui()
{
    t_object *patcher, *box, *obj;
    object_obex_lookup(this, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(fDSPfactory->get_json()));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
        }
    }
}
/**
 * Allows to start/stop the ADC/DAC in the patcher.
 *
 * mess : "start" or "stop" message
 */

/*
void faustgen::dsp_status(const char* mess)
{
    t_pxobject* dac = nullptr;
    if ((dac = check_dac())) {
        t_atom msg[1];
        atom_setsym(msg, gensym(mess));
        object_method_typed(dac, gensym("message"), 1, msg, 0);
    } else { // Global
        object_method(gensym("dsp")->s_thing, gensym(mess));
    }
}
*/

// Start or stop the global DSP chain in Max
void faustgen::dsp_status(const char* mess)
{
    object_method(gensym("dsp")->s_thing, gensym(mess));
}

/**
 * Set the object mute state.
 *
 * mute : 0|1
 */
void faustgen::mute(long inlet, long mute)
{
    fMute = mute;
}

/**
 * Called to get the number of outputs.
 *
 * outletindex : the outlet index starting from 0
 */
long faustgen::multichanneloutputs(long outletindex)
{
    if (m_is_mc) {
        std::cout << "faustgen::multichanneloutputs MC " << outletindex << std::endl;
        return (outletindex == 0) ? fDSP->getNumOutputs() : 0;
    } else {
        std::cout << "faustgen::multichanneloutputs DEFAULT " << outletindex << std::endl;
        return 1;
    }
}

// Max entry point registering the faustgen classes and methods
extern "C" void ext_main(void* r)
{
#ifdef WIN32
    static bool done = false;
    if (done) return;
    done = true;
#endif
    
    common_symbols_init();
    
    // Creates as class for Faustgen
    faustgen::makeMaxClass("faustgen~");
    
    // Creates as class for multi-channels Faustgen
    faustgen::makeMaxClass("mc.faustgen~");
    
    post("faustgen~/mc.faustgen~ v%s (sample = 64 bits code = %s)", FAUSTGEN_VERSION, getCodeSize());
    post("LLVM powered Faust embedded compiler v%s", getCLibFaustVersion());
    post("Copyright (c) 2012-2026 Grame");
    
    // Start 'libfaust' in multi-thread safe mode
    startMTDSPFactories();
    
    // Process all messages coming to the object using a custom method
    REGISTER_METHOD_GIMME(faustgen, anything);
    
    // Process the "compileoptions" message, to add optional compilation possibilities
    REGISTER_METHOD_GIMME(faustgen, compileoptions);
    
    // Process the "clearcache" message, to empty the disk cache of compiled code
    REGISTER_METHOD_GIMME(faustgen, clearcache);

    // Process the "midievent" message
    REGISTER_METHOD_GIMME(faustgen, midievent);
    
    // Process the "polyphony" message
    REGISTER_METHOD_GIMME(faustgen, polyphony);
    
    // Process the "init" message
    REGISTER_METHOD_GIMME(faustgen, init);
    
    // Process the "dump" message
    REGISTER_METHOD_GIMME(faustgen, dump);
    
    // Process the "osc" message
    REGISTER_METHOD_GIMME(faustgen, osc);
    
    // Register inside Max the faustgen::json method
    REGISTER_METHOD_GIMME(faustgen, json);
    
    // Register inside Max the faustgen::report method
    REGISTER_METHOD_GIMME(faustgen, report);
    
    // Register inside Max the faustgen::wasm method
    REGISTER_METHOD_GIMME(faustgen, wasm);
    
    // Process the "multichanneloutputs" message
    REGISTER_METHOD_MULTICHANNELOUPUTS(faustgen, multichanneloutputs);
    
    // Register inside Max the necessary methods
    REGISTER_METHOD_DEFSYM(faustgen, read);
    REGISTER_METHOD_DEFSYM(faustgen, write);
    REGISTER_METHOD_DEFSYM(faustgen, librarypath);
    REGISTER_METHOD_LONG(faustgen, mute);
    REGISTER_METHOD_CANT(faustgen, dblclick);
    REGISTER_METHOD_ASSIST(faustgen, assist);
    REGISTER_METHOD_EDCLOSE(faustgen, edclose);
    REGISTER_METHOD_JSAVE(faustgen, appendtodictionary);
}
