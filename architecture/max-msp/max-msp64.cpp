/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN max-msp64.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2004-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 MAX MSP SDK : in order to compile a MaxMSP external with this
 architecture file you will need the official MaxMSP SDK from
 cycling'74. Please check the corresponding license.
 
 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#ifdef WIN32
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

// FAUSTFLOAT is setup by faust2max6

#ifndef DOWN_SAMPLING
#define DOWN_SAMPLING 0
#endif
#ifndef UP_SAMPLING
#define UP_SAMPLING 0
#endif
#ifndef FILTER_TYPE
#define FILTER_TYPE 0
#endif

#include "faust/gui/UI.h"
#include "faust/gui/SimpleParser.h"
#include "faust/gui/PathBuilder.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/dsp.h"
#include "faust/misc.h"
#include "faust/gui/SaveUI.h"

// Always included
#include "faust/gui/OSCUI.h"

#ifdef POLY2
#include "effect.h"
#endif

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

// For FAUST_CLASS_NAME to be defined
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)
#define FAUST_ADDSOUNDFILE(s,f)

using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/* Faust code wrapper ------- */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "jpatcher_api.h"
#include <string.h>
#include <stdint.h>

#define ASSIST_INLET 	1
#define ASSIST_OUTLET 	2

#define EXTERNAL_VERSION    "0.88"
#define STR_SIZE            512

#include "faust/gui/GUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/mspUI.h"
#include "faust/dsp/poly-dsp.h"

#ifdef MC_VERSION
// For older Max/MSP SDK versions
#ifndef Z_MC_INLETS
#define Z_MC_INLETS 32
#endif
#endif

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static t_class* faust_class;

/*--------------------------------------------------------------------------*/
static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

/*--------------------------------------------------------------------------*/
typedef struct faust
{
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    short m_where;
    bool m_mute;
    void** m_args;
    mspUI* m_dspUI;
    dsp* m_dsp;
#ifdef MC_VERSION
    dsp* m_mc_dsp;
#endif
    void* m_control_outlet;
    char* m_json;
    t_systhread_mutex m_mutex;    
    int m_Inputs;
    int m_Outputs;
    SaveUI* m_savedUI;
#ifdef MIDICTRL
    MidiUI* m_midiUI;
    max_midi* m_midiHandler;
    void* m_midi_outlet;
#endif
#ifdef SOUNDFILE
    SoundUI* m_soundInterface;
#endif
#ifdef OSCCTRL
    OSCUI* m_oscInterface;
#endif
} t_faust;

void faust_create_jsui(t_faust* x);
void faust_make_json(t_faust* x);

/*--------------------------------------------------------------------------*/
void faust_allocate(t_faust* x, int nvoices)
{
    // Delete old
    delete x->m_dsp;
    delete x->m_dspUI;
    x->m_dspUI = new mspUI();
    
    if (nvoices > 0) {
    #ifdef POST
        post("polyphonic DSP voices = %d", nvoices);
    #endif
        x->m_dsp = new mydsp_poly(new mydsp(), nvoices, true, true);
    #ifdef POLY2
        x->m_dsp = new dsp_sequencer(x->m_dsp, new effect());
    #endif
    } else {
    #ifdef POST
        post("monophonic DSP");
    #endif
        // Create a DS/US + Filter adapted DSP
        std::string error;
        x->m_dsp = createSRAdapter<FAUSTFLOAT>(new mydsp(), error, DOWN_SAMPLING, UP_SAMPLING, FILTER_TYPE);
    }
    
#ifdef MIDICTRL
    x->m_dsp->buildUserInterface(x->m_midiUI);
#endif
  
    // Possible sample adaptation
    if (sizeof(FAUSTFLOAT) == 4) {
        x->m_dsp = new dsp_sample_adapter<FAUSTFLOAT, double>(x->m_dsp);
    }
    
    x->m_Inputs = x->m_dsp->getNumInputs();
    x->m_Outputs = x->m_dsp->getNumOutputs();
    
    // Initialize at the system's sampling rate
    x->m_dsp->init(long(sys_getsr()));
    
    // Initialize User Interface (here connnection with controls)
    x->m_dsp->buildUserInterface(x->m_dspUI);
    
#ifdef SOUNDFILE
    x->m_dsp->buildUserInterface(x->m_soundInterface);
#endif
    
    // Prepare JSON
    faust_make_json(x);
    
    // Send JSON to JS script
    faust_create_jsui(x);
    
#ifdef OSCCTRL
    x->m_oscInterface = NULL;
#endif
    
    // Load old controller state
    x->m_dsp->buildUserInterface(x->m_savedUI);
}

/*--------------------------------------------------------------------------*/
void faust_anything(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    bool res = false;
    string name = string((s)->s_name);
    
    // If no argument is there, consider it as a toggle message for a button
    if (ac == 0 && obj->m_dspUI->isValue(name)) {
        
        FAUSTFLOAT off = FAUSTFLOAT(0.0);
        FAUSTFLOAT on = FAUSTFLOAT(1.0);
        obj->m_dspUI->setValue(name, off);
        obj->m_dspUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_anything(obj, s, 1, av);
        
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
                    return;         
            }
            
            string num_val = to_string(num + i);
            stringstream param_name; param_name << prefix;
            for (int i = 0; i < ndigit - mspUI::countDigit(num_val); i++) {
                param_name << ' ';
            }
            param_name << num_val;
              
            // Try special naming scheme for list of parameters
            res = obj->m_dspUI->setValue(param_name.str(), value);
            
            // Otherwise try standard name
            if (!res) {
                res = obj->m_dspUI->setValue(name, value);
            }
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
        
    } else {
        // Standard parameter name
        FAUSTFLOAT value = (av[0].a_type == A_LONG) ? FAUSTFLOAT(av[0].a_w.w_long) : FAUSTFLOAT(av[0].a_w.w_float);
        res = obj->m_dspUI->setValue(name, value);
        if (!res) {
            post("Unknown parameter : %s", (s)->s_name);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_polyphony(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    if (systhread_mutex_lock(x->m_mutex) == MAX_ERR_NONE) {
        faust_allocate(x, av[0].a_w.w_long);
        systhread_mutex_unlock(x->m_mutex);
    } else {
        post("Mutex lock cannot be taken...");
    }
}

/*--------------------------------------------------------------------------*/
#ifdef MIDICTRL
void faust_midievent(t_faust* x, t_symbol* s, short ac, t_atom* av) 
{
    if (ac > 0) {
        int type = (int)av[0].a_w.w_long & 0xf0;
        int channel = (int)av[0].a_w.w_long & 0x0f;
                
        if (ac == 1) {
            x->m_midiHandler->handleSync(0.0, av[0].a_w.w_long);
        } else if (ac == 2) {
            x->m_midiHandler->handleData1(0.0, type, channel, av[1].a_w.w_long);
        } else if (ac == 3) {
            x->m_midiHandler->handleData2(0.0, type, channel, av[1].a_w.w_long, av[2].a_w.w_long);
        }
    }
}
#endif

/*--------------------------------------------------------------------------*/
void faust_create_jsui(t_faust* x)
{
    t_object *patcher, *box, *obj;
    object_obex_lookup((t_object*)x, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(x->m_json));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_make_json(t_faust* x)
{
    // Prepare JSON
    if (x->m_json) free(x->m_json);
    JSONUI builder(x->m_dsp->getNumInputs(), x->m_dsp->getNumOutputs());
    x->m_dsp->metadata(&builder);
    x->m_dsp->buildUserInterface(&builder);
    x->m_json = strdup(builder.JSON().c_str());
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    bool midi_sync = false;
    bool midi = false;
    int nvoices = 0;
    t_faust* x = (t_faust*)object_alloc(faust_class);
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi, midi_sync, nvoices);
#ifdef SOUNDFILE
    Max_Meta3 meta3;
    tmp_dsp->metadata(&meta3);
    string bundle_path_str = SoundUI::getBinaryPathFrom(meta3.fName);
    if (bundle_path_str == "") {
        post("Bundle_path '%s' cannot be found!", meta3.fName.c_str());
    }
    x->m_soundInterface = new SoundUI(bundle_path_str, -1, nullptr, sizeof(FAUSTFLOAT) == 8);
#endif
    delete tmp_dsp;
    
    x->m_savedUI = new SaveLabelUI();
    // allocation is done in faust_allocate
    x->m_dspUI = NULL;
    x->m_dsp = NULL;
#ifdef MC_VERSION
    x->m_mc_dsp = NULL;
#endif
    x->m_json = NULL;
    x->m_mute = false;
    x->m_control_outlet = outlet_new((t_pxobject*)x, (char*)"list");
    
#ifdef MIDICTRL
    x->m_midi_outlet = outlet_new((t_pxobject*)x, NULL);
    x->m_midiHandler = new max_midi(x->m_midi_outlet);
    x->m_midiUI = new MidiUI(x->m_midiHandler);
#endif
    
    faust_allocate(x, nvoices);
   
    if (systhread_mutex_new(&x->m_mutex, SYSTHREAD_MUTEX_NORMAL) != MAX_ERR_NONE) {
        post("Cannot allocate mutex...");
    }
    
    int num_input;
    if (x->m_dspUI->isMulti()) {
        num_input = x->m_dsp->getNumInputs() + 1;
    } else {
        num_input = x->m_dsp->getNumInputs();
    }
    
    x->m_args = (void**)calloc((num_input + x->m_dsp->getNumOutputs()) + 2, sizeof(void*));
   
#ifdef MC_VERSION
    dsp_setup((t_pxobject *)x, 1);
    outlet_new((t_pxobject*)x, (char*)"multichannelsignal");
    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE | Z_MC_INLETS; // To assure input and output buffers are actually different
#else
    /* Multi in */
    dsp_setup((t_pxobject*)x, num_input);
    /* Multi out */
    for (int i = 0; i < x->m_dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }
    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
#endif
     
    // Display controls
#ifdef POST
    x->m_dspUI->displayControls();
#endif
    
    // Get attributes values
    attr_args_process(x, ac, av);
    return x;
}

#ifdef OSCCTRL
// osc 'IP inport outport xmit bundle'
/*--------------------------------------------------------------------------*/
void faust_osc(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    if (ac == 5) {
        if (systhread_mutex_lock(x->m_mutex) == MAX_ERR_NONE) {
            
            delete x->m_oscInterface;
            
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
            
            x->m_oscInterface = new OSCUI("Faust", argc1, (char**)argv1);
            x->m_dsp->buildUserInterface(x->m_oscInterface);
            x->m_oscInterface->run();

            post(x->m_oscInterface->getInfos().c_str());

            systhread_mutex_unlock(x->m_mutex);
        } else {
            post("Mutex lock cannot be taken...");
        }
    } else {
        post("Should be : osc 'IP inport outport xmit(0|1|2) bundle(0|1)'");
    }
}
#endif

/*--------------------------------------------------------------------------*/
// Reset controllers to init value and send [path, init, min, max]
void faust_init(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    // Reset internal state
    x->m_savedUI->reset();
    
    // Input controllers
    for (mspUI::iterator it = x->m_dspUI->begin2(); it != x->m_dspUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
    // Output controllers
    for (mspUI::iterator it = x->m_dspUI->begin4(); it != x->m_dspUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getInitValue());    // init value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
 }

/*--------------------------------------------------------------------------*/
void faust_dump_inputs(t_faust* x)
{
    // Input controllers
    for (mspUI::iterator it = x->m_dspUI->begin2(); it != x->m_dspUI->end2(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
}

/*--------------------------------------------------------------------------*/
void faust_dump_outputs(t_faust* x)
{
    // Output controllers
    for (mspUI::iterator it = x->m_dspUI->begin4(); it != x->m_dspUI->end4(); it++) {
        t_atom myList[4];
        atom_setsym(&myList[0], gensym((*it).first.c_str()));
        atom_setfloat(&myList[1], (*it).second->getValue());    // cur value
        atom_setfloat(&myList[2], (*it).second->getMinValue());
        atom_setfloat(&myList[3], (*it).second->getMaxValue());
        outlet_list(x->m_control_outlet, 0, 4, myList);
    }
}

/*--------------------------------------------------------------------------*/
// Dump controllers as list of [path, cur, min, max]
void faust_dump(t_faust* x, t_symbol* s, short ac, t_atom* av)
{
    faust_dump_inputs(x);
    faust_dump_outputs(x);
}

/*--------------------------------------------------------------------------*/
void faust_dblclick(t_faust* x, long inlet)
{
    x->m_dspUI->displayControls();
}

/*--------------------------------------------------------------------------*/
//11/13/2015 : faust_assist is actually called at each click in the patcher, so we now use 'faust_dblclick' to display the parameters...
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
{
#ifdef MC_VERSION
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
#else
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->m_dsp->getNumInputs() == 0) {
                snprintf(dst, 512, "(messages)");
            } else {
                snprintf(dst, 512, "(messages/signal) : Audio Input %ld", (a+1));
            }
        } else if (a < x->m_dsp->getNumInputs()) {
            snprintf(dst, 512, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        if (a < x->m_dsp->getNumOutputs()) {
            snprintf(dst, 512, "(signal) : Audio Output %ld", (a+1));
        } else if (a == x->m_dsp->getNumOutputs()) {
            snprintf(dst, 512, "(list) : [path, cur|init, min, max]*");
        } else {
            snprintf(dst, 512, "(int) : raw MIDI bytes*");
        }
    }
#endif
}

/*--------------------------------------------------------------------------*/
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
#ifdef MC_VERSION
long faust_multichanneloutputs(t_faust* x, long outletindex)
{
    return (outletindex == 0) ? x->m_Outputs : 0;
}
#endif

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
    dsp_free((t_pxobject*)x);
    delete x->m_dsp;
    delete x->m_dspUI;
    delete x->m_savedUI;
    if (x->m_args) free(x->m_args);
    if (x->m_json) free(x->m_json);
    systhread_mutex_free(x->m_mutex);
#ifdef MIDICTRL
    // m_midiUI *must* be deleted before m_midiHandler
    delete x->m_midiUI;
    delete x->m_midiHandler;
#endif
#ifdef SOUNDFILE
    delete x->m_soundInterface;
#endif
#ifdef OSCCTRL
    delete x->m_oscInterface;
#endif
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust* x, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam)
{
    AVOIDDENORMALS;

    if (!x->m_mute && systhread_mutex_trylock(x->m_mutex) == MAX_ERR_NONE) {
        if (x->m_dsp) {
            if (x->m_dspUI->isMulti()) {
                x->m_dspUI->setMultiValues(reinterpret_cast<FAUSTFLOAT*>(ins[0]), sampleframes);
            #ifdef MC_VERSION
                x->m_mc_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(++ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            #else
                x->m_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(++ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            #endif
            } else {
            #ifdef MC_VERSION
                x->m_mc_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            #else
                x->m_dsp->compute(sampleframes, reinterpret_cast<FAUSTFLOAT**>(ins), reinterpret_cast<FAUSTFLOAT**>(outs));
            #endif
            }
            // Use the right outlet to output messages
            faust_dump_outputs(x);
        }
    #if defined(MIDICTRL) || defined(OSCCTRL)
        GUI::updateAllGuis();
    #endif
        systhread_mutex_unlock(x->m_mutex);
    } else {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
             memset(outs[i], 0, sizeof(double) * sampleframes);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust* x, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags)
{
#ifdef MC_VERSION
    // We need to know the real number of inputs to adapt faust_perform64
    intptr_t inputs = (intptr_t)object_method(dsp64, gensym("getnuminputchannels"), x, 0);
    delete x->m_mc_dsp;
    // x->m_mc_dsp will not delete the x->m_dsp object
    x->m_mc_dsp = new dsp_adapter(x->m_dsp, inputs, x->m_Outputs, maxvectorsize, false);
#endif
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
t_max_err faust_attr_set(t_faust* x, t_object* attr, long ac, t_atom* av)
{
    if (ac && av) {
        t_symbol* attrname = (t_symbol*)object_method(attr, gensym("getname"));
        // Redirect on the generic message handling method
        faust_anything(x, attrname, ac, av);
    }
    return MAX_ERR_NONE;
}

/*--------------------------------------------------------------------------*/
#ifdef _WIN32
extern "C" int main(void)
#else
void ext_main(void* r)
#endif
{
    string file_name = string(FAUST_FILE_NAME);
    // Remove ".dsp" ending
    string class_name = file_name.erase(file_name.size()-4) + "~";
    t_class* c = class_new(class_name.c_str(), (method)faust_new, (method)faust_free, sizeof(t_faust), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)faust_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)faust_polyphony, "polyphony", A_GIMME, 0);
#ifdef OSCCTRL
    class_addmethod(c, (method)faust_osc, "osc", A_GIMME, 0);
#endif
    class_addmethod(c, (method)faust_init, "init", A_GIMME, 0);
    class_addmethod(c, (method)faust_dump, "dump", A_GIMME, 0);
#ifdef MIDICTRL
    class_addmethod(c, (method)faust_midievent, "midievent", A_GIMME, 0);
#endif
    class_addmethod(c, (method)faust_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)faust_dblclick, "dblclick", A_CANT, 0);
    class_addmethod(c, (method)faust_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)faust_mute, "mute", A_GIMME, 0);
#ifdef MC_VERSION
    class_addmethod(c, (method)faust_multichanneloutputs, "multichanneloutputs", A_CANT, 0);
#endif
    
    dsp* tmp_dsp = new mydsp();
    mspUI tmp_UI;
    tmp_dsp->buildUserInterface(&tmp_UI);
    
    // Setup attributes
    if (sizeof(FAUSTFLOAT) == 4) {
        for (mspUI::iterator it = tmp_UI.begin1(); it != tmp_UI.end1(); it++) {
            CLASS_ATTR_FLOAT(c, (*it).first.c_str(), 0, t_faust, m_ob);
            CLASS_ATTR_ACCESSORS(c, (*it).first.c_str(), NULL, (method)faust_attr_set);
        }
    } else {
        for (mspUI::iterator it = tmp_UI.begin1(); it != tmp_UI.end1(); it++) {
            CLASS_ATTR_DOUBLE(c, (*it).first.c_str(), 0, t_faust, m_ob);
            CLASS_ATTR_ACCESSORS(c, (*it).first.c_str(), NULL, (method)faust_attr_set);
        }
    }
    
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    faust_class = c;
#ifdef POST
    post((char*)"Faust DSP object v%s (sample = %s bits code = %s)", EXTERNAL_VERSION, ((sizeof(FAUSTFLOAT) == 4) ? "32" : "64"), getCodeSize());
    post((char*)"Copyright (c) 2012-2024 Grame");
#endif
    Max_Meta1 meta1;
    tmp_dsp->metadata(&meta1);
    if (meta1.fCount > 0) {
    #ifdef POST
        Max_Meta2 meta2;
        post("------------------------------");
        tmp_dsp->metadata(&meta2);
        post("------------------------------");
    #endif
    }
    delete(tmp_dsp);
#ifdef _WIN32
    return 0;
#endif
}

/******************* END max-msp64.cpp ****************/

