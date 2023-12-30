/************************************************************************
 FAUST Architecture File
 Copyright (C) 2012-2023 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
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

#include "faustgen~.h"

using namespace std;

// globals
t_jrgba faustgen::gDefaultColor = {-1., -1., -1., -1.};

std::map<string, faustgen_factory*> faustgen_factory::gFactoryMap;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

//====================
// Faust DSP Instance
//====================

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

faustgen::faustgen(t_symbol* sym, long ac, t_atom* argv)
{
    m_siginlets = 0;
    m_sigoutlets = 0;
    
    fDSP = nullptr;
    fDSPUI = nullptr;
    fMidiUI = nullptr;
    fOSCUI = nullptr;
    fSavedUI = nullptr;
    fDSPfactory = nullptr;
    fEditor = nullptr;
    fMute = false;
    
    int i;
    t_atom* ap;
    bool res = false;
    
    fMidiHandler.startMidi();
    
    // Allocate factory with a given "name"
    for (i = 0, ap = argv; i < ac; i++, ap++) {
        if (atom_gettype(ap) == A_SYM) {
            res = allocate_factory(atom_getsym(ap)->s_name);
            break;
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
}

// Called upon deleting the object inside the patcher
faustgen::~faustgen()
{
    free_dsp();
    
    if (fEditor) {
        object_free(fEditor);
        fEditor = nullptr;
    }
    
    fDSPfactory->remove_instance(this);    
    fMidiHandler.stopMidi();
}

void faustgen::assist(void* b, long msg, long a, char* dst)
{
    fDSPfactory->lock_audio();
    fDSPfactory->lock_ui();
    {
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
    fDSPfactory->unlock_ui();
    fDSPfactory->unlock_audio();
}

void faustgen::free_dsp()
{
    // Save controller state
    if (fSavedUI) {
        fSavedUI->save();
        delete fSavedUI;
        fSavedUI = nullptr;
    }
    
    delete fMidiUI;
    fMidiUI = nullptr;
    
    delete fOSCUI;
    fOSCUI = nullptr;
 
    delete fDSPUI;
    fDSPUI = nullptr;
    
    delete fDSP;
    fDSP = nullptr;
}

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
            
            av[0].a_type = A_FLOAT;
            av[0].a_w.w_float = off;
            anything(inlet, s, 1, av);
            
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
            
        } else {
            // Standard parameter name
            FAUSTFLOAT value = (av[0].a_type == A_LONG) ? FAUSTFLOAT(av[0].a_w.w_long) : FAUSTFLOAT(av[0].a_w.w_float);
            res = fDSPUI->setValue(name, value);
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
    }
        
    unlock:
        fDSPfactory->unlock_ui();
}

void faustgen::compileoptions(long inlet, t_symbol* s, long argc, t_atom* argv)
{
    fDSPfactory->compileoptions(inlet, s, argc, argv);
}

void faustgen::read(long inlet, t_symbol* s)
{
    fDSPfactory->read(inlet, s);
}

void faustgen::write(long inlet, t_symbol* s)
{
    fDSPfactory->write(inlet, s);
}

void faustgen::polyphony(long inlet, t_symbol* s, long ac, t_atom* av)
{
    fDSPfactory->lock_audio();
    fDSPfactory->lock_ui();
    {
        free_dsp();
        fDSP = fDSPfactory->create_dsp_instance(av[0].a_w.w_long);
        assert(fDSP);
        
        // Init all controller (UI, MIDI, Soundfile)
        init_controllers();
        
        // Prepare JSON
        fDSPfactory->make_json(fDSP);
        
        // Send JSON to JS script
        create_jsui();
        
        // Initialize at the system's sampling rate
        fDSP->init(sys_getsr());
    }
    fDSPfactory->unlock_ui();
    fDSPfactory->unlock_audio();
}

// Reset controllers to init value and send [path, init, min, max]
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

// osc 'IP inport outport xmit bundle'
void faustgen::osc(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac == 5) {
        fDSPfactory->lock_audio();
        fDSPfactory->lock_ui();
        {
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

void faustgen::midievent(long inlet, t_symbol* s, long ac, t_atom* av)
{
    if (ac > 0) {
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

void faustgen::librarypath(long inlet, t_symbol* s)
{
    fDSPfactory->librarypath(inlet, s);
}

// Called when saving the Max patcher, this function saves the necessary data inside the json file (faust sourcecode)
void faustgen::appendtodictionary(t_dictionary* d)
{
    fDSPfactory->appendtodictionary(d);
}

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

void faustgen::update_sourcecode()
{
    // Create a new DSP instance
    create_dsp(false);
    
    // faustgen~ state is modified...
    set_dirty();
    
    // Send a bang
    outlet_bang(m_control_outlet);
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
            fDSP->compute(vs, reinterpret_cast<FAUSTFLOAT**>(inputs), reinterpret_cast<FAUSTFLOAT**>(outputs));
            if (fOSCUI) fOSCUI->endBundle();
            // Use the right outlet to output messages
            dump_outputs();
            // Done for fMidiUI and fOSCUI
            GUI::updateAllGuis();
        }
        fDSPfactory->unlock_audio();
    }
}

inline void faustgen::init(double samplerate)
{
    fDSP->init(samplerate);
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

// Display the Faust module's parameters along with their standard values
void faustgen::display_dsp_params()
{
    fDSPUI->displayControls();
}

void faustgen::display_svg()
{
    fDSPfactory->display_svg();
}

void faustgen::display_documentation()
{
    fDSPfactory->display_documentation();
}

void faustgen::display_libraries()
{
    fDSPfactory->display_libraries();
}

void faustgen::hilight_on()
{
    t_jrgba color;
    jrgba_set(&color, 1.0, 0.0, 0.0, 1.0);
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    jbox_set_color(box, &color);
}

void faustgen::hilight_off()
{
    t_object* box;
    object_obex_lookup((t_object*)&m_ob, gensym("#B"), &box);
    jbox_set_color(box, &gDefaultColor);
}

void faustgen::hilight_error(const string& error)
{
    object_error_obtrusive((t_object*)&m_ob, (char*)error.c_str());
}

void faustgen::init_controllers()
{
    // Initialize User Interface (here connnection with controls)
    if (!fDSPUI) {
        fDSPUI = new mspUI();
        fDSP->buildUserInterface(fDSPUI);
    }
    
    // MIDI handling
    if (!fMidiUI) {
        fMidiUI = new MidiUI(&fMidiHandler);
        fDSP->buildUserInterface(fMidiUI);
    }
    
    // State handling
    if (!fSavedUI) {
        fSavedUI = new SaveLabelUI();
    }
    
    // Soundfile handling
    if (fDSPfactory->fSoundUI) {
        fDSP->buildUserInterface(fDSPfactory->fSoundUI);
    }
}

void faustgen::create_dsp(bool init)
{
    fDSPfactory->lock_audio();
    fDSPfactory->lock_ui();
    {
        fDSP = fDSPfactory->create_dsp_aux();
        assert(fDSP);
        
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
        
        // Send JSON to JS script
        create_jsui();
    }
    fDSPfactory->unlock_ui();
    fDSPfactory->unlock_audio();
}

void faustgen::set_dirty()
{
    t_object* mypatcher;
    object_obex_lookup(&m_ob, gensym("#P"), &mypatcher);
    jpatcher_set_dirty(mypatcher, 1);
}

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
                || (object_classname(obj) == gensym("adc~"))) {
                return (t_pxobject*)box;
            }
        }
    }
    
    return nullptr;
}

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
    
    // Keep all outputs to be notified in update_outputs
    fOutputTable.clear();
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        t_symbol* scriptingname = jbox_get_varname(obj); // scripting name
        // Keep control outputs
        if (scriptingname && fDSPUI->isOutputValue(scriptingname->s_name)) {
            fOutputTable[scriptingname->s_name].push_back(obj);
        }
    }
}

void faustgen::update_outputs()
{
    for (const auto& it1 : fOutputTable) {
        bool new_val = false;
        FAUSTFLOAT value = fDSPUI->getOutputValue(it1.first, new_val);
        if (new_val) {
            t_atom at_value;
            atom_setfloat(&at_value, value);
            for (const auto& it2 : it1.second) {
                object_method_typed(it2, gensym("float"), 1, &at_value, 0);
            }
        }
    }
}

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

void faustgen::mute(long inlet, long mute)
{
    fMute = mute;
}

extern "C" void ext_main(void* r)
{
#ifdef WIN32
    static bool done = false;
    if (done) return;
    done = true;
#endif
    
    common_symbols_init();
    
    // Creates an instance of Faustgen
    t_class * mclass = faustgen::makeMaxClass("faustgen~");
    post("faustgen~ v%s (sample = 64 bits code = %s)", FAUSTGEN_VERSION, getCodeSize());
    post("LLVM powered Faust embedded compiler v%s", getCLibFaustVersion());
    post("Copyright (c) 2012-2024 Grame");
    
    // Start 'libfaust' in multi-thread safe mode
    startMTDSPFactories();
    
    // Process all messages coming to the object using a custom method
    REGISTER_METHOD_GIMME(faustgen, anything);
    
    // Process the "compileoptions" message, to add optional compilation possibilities
    REGISTER_METHOD_GIMME(faustgen, compileoptions);
    
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

