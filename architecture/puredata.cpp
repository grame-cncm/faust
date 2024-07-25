/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
 Copyright (C) 2024 Christof Ressi <christof.ressi@gmx.at>
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as
 published by the Free Software Foundation; either version 2.1 of the
 License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, write to the Free
 Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/*
 Pd architecture file, written by Albert Graef <Dr.Graef@t-online.de>
 and Christof Ressi <christof.ressi@gmx.at>.
 This was derived from minimal.cpp included in the Faust distribution.
 Please note that this is to be compiled as a shared library, which is
 then loaded dynamically by Pd as an external.
 */

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/***************************************************************************
 Pd UI interface
 ***************************************************************************/

enum ui_elem_type_t {
    UI_BUTTON, UI_CHECK_BUTTON,
    UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
    UI_V_BARGRAPH, UI_H_BARGRAPH,
    UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
    ui_elem_type_t type;
    char *label;
    float *zone;
    float init, min, max, step;
};

class PdUI : public UI
{
public:
    const char *name;
    int nelems, level;
    ui_elem_t *elems;
    
    PdUI();
    PdUI(const char *nm, const char *s);
    virtual ~PdUI();
    
protected:
    std::string path;
    void add_elem(ui_elem_type_t type, const char *label = NULL);
    void add_elem(ui_elem_type_t type, const char *label, float *zone);
    void add_elem(ui_elem_type_t type, const char *label, float *zone,
                  float init, float min, float max, float step);
    void add_elem(ui_elem_type_t type, const char *label, float *zone,
                  float min, float max);
    
public:
    virtual void addButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
    virtual void openTabBox(const char* label);
    virtual void openHorizontalBox(const char* label);
    virtual void openVerticalBox(const char* label);
    virtual void closeBox();
    
    virtual void run();
};

static std::string mangle(const char *name, int level, const char *s)
{
    const char *s0 = s;
    std::string t = "";
    if (!s) return t;
    // Get rid of bogus "0x00" labels in recent Faust revisions. Also, for
    // backward compatibility with old Faust versions, make sure that default
    // toplevel groups and explicit toplevel groups with an empty label are
    // treated alike (these both return "0x00" labels in the latest Faust, but
    // would be treated inconsistently in earlier versions).
    if (!*s || strcmp(s, "0x00") == 0) {
        if (level == 0)
            // toplevel group with empty label, map to dsp name
            s = name;
        else
            // empty label
            s = "";
    }
    while (*s)
        if (isalnum(*s))
            t += *(s++);
        else {
            const char *s1 = s;
            while (*s && !isalnum(*s)) ++s;
            if (s1 != s0 && *s) t += "-";
        }
    return t;
}

static std::string normpath(std::string path)
{
    path = std::string("/")+path;
    int pos = path.find("//");
    while (pos >= 0) {
        path.erase(pos, 1);
        pos = path.find("//");
    }
    size_t len = path.length();
    if (len > 1 && path[len-1] == '/')
        path.erase(len-1, 1);
    return path;
}

static std::string pathcat(std::string path, std::string label)
{
    if (path.empty())
        return normpath(label);
    else if (label.empty())
        return normpath(path);
    else
        return normpath(path+"/"+label);
}

PdUI::PdUI()
{
    nelems = level = 0;
    elems = NULL;
    name = "";
    path = "";
}

PdUI::PdUI(const char *nm, const char *s)
{
    nelems = level = 0;
    elems = NULL;
    name = nm?nm:"";
    path = s?s:"";
}

PdUI::~PdUI()
{
    if (elems) {
        for (int i = 0; i < nelems; i++)
            if (elems[i].label)
                free(elems[i].label);
        free(elems);
    }
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label)
{
    ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
    if (elems1)
        elems = elems1;
    else
        return;
    std::string s = pathcat(path, mangle(name, level, label));
    elems[nelems].type = type;
    elems[nelems].label = strdup(s.c_str());
    elems[nelems].zone = NULL;
    elems[nelems].init = 0.0;
    elems[nelems].min = 0.0;
    elems[nelems].max = 0.0;
    elems[nelems].step = 0.0;
    nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
    ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
    if (elems1)
        elems = elems1;
    else
        return;
    std::string s = pathcat(path, mangle(name, level, label));
    elems[nelems].type = type;
    elems[nelems].label = strdup(s.c_str());
    elems[nelems].zone = zone;
    elems[nelems].init = 0.0;
    elems[nelems].min = 0.0;
    elems[nelems].max = 1.0;
    elems[nelems].step = 1.0;
    nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
                           float init, float min, float max, float step)
{
    ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
    if (elems1)
        elems = elems1;
    else
        return;
    std::string s = pathcat(path, mangle(name, level, label));
    elems[nelems].type = type;
    elems[nelems].label = strdup(s.c_str());
    elems[nelems].zone = zone;
    elems[nelems].init = init;
    elems[nelems].min = min;
    elems[nelems].max = max;
    elems[nelems].step = step;
    nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
                           float min, float max)
{
    ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
    if (elems1)
        elems = elems1;
    else
        return;
    std::string s = pathcat(path, mangle(name, level, label));
    elems[nelems].type = type;
    elems[nelems].label = strdup(s.c_str());
    elems[nelems].zone = zone;
    elems[nelems].init = 0.0;
    elems[nelems].min = min;
    elems[nelems].max = max;
    elems[nelems].step = 0.0;
    nelems++;
}

void PdUI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PdUI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PdUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PdUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PdUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PdUI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PdUI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PdUI::openTabBox(const char* label)
{
    if (!path.empty()) path += "/";
    path += mangle(name, level, label);
    level++;
}
void PdUI::openHorizontalBox(const char* label)
{
    if (!path.empty()) path += "/";
    path += mangle(name, level, label);
    level++;
}
void PdUI::openVerticalBox(const char* label)
{
    if (!path.empty()) path += "/";
    path += mangle(name, level, label);
    level++;
}
void PdUI::closeBox()
{
    int pos = path.rfind("/");
    if (pos < 0) pos = 0;
    path.erase(pos);
    level--;
}

void PdUI::run() {}

/******************************************************************************
 *******************************************************************************
 
 FAUST DSP
 
 *******************************************************************************
 *******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeclass>>

#include <stdio.h>
#include <string>
#include "m_pd.h"

// For some reason, the first inlet has always been
// reserved for messages, so the input signals (if any)
// would only start at the *second* inlet. This is not
// very idiomatic as the first inlet can be a signal inlet
// and still take messages. Also, the message outlet
// comes before the signal outlet(s), which isn't very
// idiomatic either.
// If NEWIO is 1, incoming messages go to the first signal
// inlet and the message outlet comes last;
// if NEWIO is 0, you get the old behavior.
//
// NOTE: NEWIO=1 is not compatible yet with the faust2pd
// program which generates the UI wrapper.
#ifndef NEWIO
#define NEWIO 0
#endif

// for dlsym() resp. GetProcAddress()
#ifdef _WIN32
# include <windows.h>
#else
# include <dlfcn.h>
#endif

#define sym(name) xsym(name)
#define xsym(name) #name
#define faust_setup(name) xfaust_setup(name)
#define xfaust_setup(name) name ## _tilde_setup(void)
#define classname(x) class_getname(*(t_pd *)x)

// time for "active" toggle xfades in secs
#define XFADE_TIME 0.1f

#ifdef CLASS_MULTICHANNEL
# define HAVE_MULTICHANNEL
#else
# pragma message("building without multi-channel support; requires Pd 0.54 or later")
# define CLASS_MULTICHANNEL 0
#endif

// function pointer to signal_setmultiout API function;
// NULL if the runtime Pd version has no multichannel support.
using t_signal_setmultiout = void (*)(t_signal **, int);
static t_signal_setmultiout g_signal_setmultiout;

static t_class *faust_class;

struct t_faust {
    t_object x_obj;
    mydsp *dsp;
    PdUI *ui;
    std::string *label;
    bool active;
    bool multi;
    int xfade;
    int n_xfade;
    int rate;
    int n_in;
    int n_out;
    t_sample **inputs;
    t_sample **outputs;
    t_sample **buf;
    t_sample *dummy;
    t_outlet *out;
    t_sample f;
};

static t_symbol *s_button, *s_checkbox, *s_vslider, *s_hslider, *s_nentry,
*s_vbargraph, *s_hbargraph;

static inline void zero_samples(int k, int n, t_sample **out)
{
    for (int i = 0; i < k; i++)
#ifdef __STDC_IEC_559__
        /* IEC 559 a.k.a. IEEE 754 floats can be initialized faster like this */
        memset(out[i], 0, n*sizeof(t_sample));
#else
    for (int j = 0; j < n; j++)
        out[i][j] = 0.0f;
#endif
}

static inline void copy_samples(int k, int n, t_sample **out, t_sample **in)
{
    for (int i = 0; i < k; i++)
        memcpy(out[i], in[i], n*sizeof(t_sample));
}

static t_int *faust_perform(t_int *w)
{
    t_faust *x = (t_faust *)(w[1]);
    int n = (int)(w[2]);
    if (!x->dsp || !x->buf) return (w+3);
    AVOIDDENORMALS;
    if (x->xfade > 0) {
        float d = 1.0f/x->n_xfade, f = (x->xfade--)*d;
        d = d/n;
        x->dsp->compute(n, x->inputs, x->buf);
        if (x->active) {
            if (x->n_in == x->n_out) {
                /* xfade inputs -> buf */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++) {
                        x->outputs[i][j] = f*x->inputs[i][j]+(1.0f-f)*x->buf[i][j];
                    }
                }
            } else {
                /* xfade 0 -> buf */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++) {
                        x->outputs[i][j] = (1.0f-f)*x->buf[i][j];
                    }
                }
            }
        } else {
            if (x->n_in == x->n_out) {
                /* xfade buf -> inputs */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++) {
                        x->outputs[i][j] = f*x->buf[i][j]+(1.0f-f)*x->inputs[i][j];
                    }
                }
            } else {
                /* xfade buf -> 0 */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++) {
                        x->outputs[i][j] = f*x->buf[i][j];
                    }
                }
            }
        }
    } else if (x->active) {
        x->dsp->compute(n, x->inputs, x->buf);
        copy_samples(x->n_out, n, x->outputs, x->buf);
    } else if (x->n_in == x->n_out) {
        copy_samples(x->n_out, n, x->buf, x->inputs);
        copy_samples(x->n_out, n, x->outputs, x->buf);
    } else {
        zero_samples(x->n_out, n, x->outputs);
    }
    return (w+3);
}

static void faust_dsp(t_faust *x, t_signal **sp)
{
    int n = sp[0]->s_n, sr = (int)sp[0]->s_sr;
    if (sr != x->rate) {
        /* update sample rate */
        PdUI *ui = x->ui;
        float *z = NULL;
        if (ui->nelems > 0 &&
            (z = (float*)malloc(ui->nelems*sizeof(float)))) {
            /* save the current control values */
            for (int i = 0; i < ui->nelems; i++)
                if (ui->elems[i].zone)
                    z[i] = *ui->elems[i].zone;
        }
        /* set the proper sample rate; this requires reinitializing the dsp */
        x->rate = sr;
        x->dsp->init(sr);
        if (z) {
            /* restore previous control values */
            for (int i = 0; i < ui->nelems; i++)
                if (ui->elems[i].zone)
                    *ui->elems[i].zone = z[i];
            free(z);
        }
    }
    if (n > 0)
        x->n_xfade = (int)(x->rate*XFADE_TIME/n);

    if (x->multi && x->n_in > 0) {
        /* dummy buffer for missing input channels in multichannel mode */
        if (x->dummy)
            free(x->dummy);
        x->dummy = (t_sample*)malloc(n*sizeof(t_sample));
        memset(x->dummy, 0, n*sizeof(t_sample)); /* silence! */
    }

    if (x->buf != NULL) {
        /* temporary output buffers */
        for (int i = 0; i < x->n_out; i++) {
            if (x->buf[i])
                free(x->buf[i]);
            x->buf[i] = (t_sample*)malloc(n*sizeof(t_sample));
        }
    }

#ifdef HAVE_MULTICHANNEL
    /* NB: 's_nchans' only exists if PD_HAVE_MULTICHANNEL is defined */
    if (g_signal_setmultiout) {
        /* first set up output signals. NB: since this is a multi-channel
         * class, we need to call signal_setmultiout() on all outputs
         * - even in single-channel mode! */
        if (x->multi) {
            g_signal_setmultiout(&sp[1], x->n_out);
        } else {
            for (int i = 0; i < x->n_out; ++i) {
                g_signal_setmultiout(&sp[x->n_in+i], 1);
            }
        }
    }
    /* now we can store the input and output signals */
    if (x->multi) {
        for (int i = 0; i < x->n_in; i++) {
            if (i < sp[0]->s_nchans)
                x->inputs[i] = sp[0]->s_vec + (i*n);
            else
                x->inputs[i] = x->dummy;
        }
        for (int i = 0; i < x->n_out; i++)
            x->outputs[i] = sp[1]->s_vec + (i*n);
    } else
#endif
    {
        for (int i = 0; i < x->n_in; i++)
            x->inputs[i] = sp[i]->s_vec;
        for (int i = 0; i < x->n_out; i++)
            x->outputs[i] = sp[x->n_in+i]->s_vec;
    }

    dsp_add(faust_perform, 2, x, (t_int)n);
}

static int pathcmp(const char *s, const char *t)
{
    int n = strlen(s), m = strlen(t);
    if (n == 0 || m == 0)
        return 0;
    else if (t[0] == '/')
        return strcmp(s, t);
    else if (n <= m || s[n-m-1] != '/')
        return strcmp(s+1, t);
    else
        return strcmp(s+n-m, t);
}

static void faust_any(t_faust *x, t_symbol *s, int argc, t_atom *argv)
{
    if (!x->dsp) return;
    PdUI *ui = x->ui;
    if (s == &s_bang) {
        for (int i = 0; i < ui->nelems; i++) {
            if (ui->elems[i].label && ui->elems[i].zone) {
                t_atom args[6];
                t_symbol *_s;
                switch (ui->elems[i].type) {
                    case UI_BUTTON:
                        _s = s_button;
                        break;
                    case UI_CHECK_BUTTON:
                        _s = s_checkbox;
                        break;
                    case UI_V_SLIDER:
                        _s = s_vslider;
                        break;
                    case UI_H_SLIDER:
                        _s = s_hslider;
                        break;
                    case UI_NUM_ENTRY:
                        _s = s_nentry;
                        break;
                    case UI_V_BARGRAPH:
                        _s = s_vbargraph;
                        break;
                    case UI_H_BARGRAPH:
                        _s = s_hbargraph;
                        break;
                    default:
                        continue;
                }
                SETSYMBOL(&args[0], gensym(ui->elems[i].label));
                SETFLOAT(&args[1], *ui->elems[i].zone);
                SETFLOAT(&args[2], ui->elems[i].init);
                SETFLOAT(&args[3], ui->elems[i].min);
                SETFLOAT(&args[4], ui->elems[i].max);
                SETFLOAT(&args[5], ui->elems[i].step);
                outlet_anything(x->out, _s, 6, args);
            }
        }
    } else {
        const char *label = s->s_name;
        int count = 0;
        for (int i = 0; i < ui->nelems; i++) {
            if (ui->elems[i].label &&
                pathcmp(ui->elems[i].label, label) == 0) {
                if (argc == 0) {
                    if (ui->elems[i].zone) {
                        t_atom arg;
                        SETFLOAT(&arg, *ui->elems[i].zone);
                        outlet_anything(x->out, gensym(ui->elems[i].label), 1, &arg);
                    }
                    ++count;
                } else if (argc == 1 && argv[0].a_type == A_FLOAT &&
                           ui->elems[i].zone) {
                    float f = atom_getfloat(argv);
                    *ui->elems[i].zone = f;
                    ++count;
                } else
                    pd_error(x, "[faust] %s: bad control argument: %s",
                             x->label->c_str(), label);
            }
        }
        if (count == 0 && strcmp(label, "active") == 0) {
            if (argc == 0) {
                t_atom arg;
                SETFLOAT(&arg, (float)x->active);
                outlet_anything(x->out, gensym((char*)"active"), 1, &arg);
            } else if (argc == 1 && argv[0].a_type == A_FLOAT) {
                float f = atom_getfloat(argv);
                x->active = f != 0;
                x->xfade = x->n_xfade;
            }
        }
    }
}

static void faust_free(t_faust *x)
{
    if (x->label) delete x->label;
    if (x->dsp) delete x->dsp;
    if (x->ui) delete x->ui;
    if (x->inputs) free(x->inputs);
    if (x->outputs) free(x->outputs);
    if (x->buf) {
        for (int i = 0; i < x->n_out; i++)
            if (x->buf[i]) free(x->buf[i]);
        free(x->buf);
    }
    if (x->dummy) free(x->dummy);
}

static void *faust_new(t_symbol *s, int argc, t_atom *argv)
{
    t_faust *x = (t_faust*)pd_new(faust_class);
    int sr = -1;
    t_symbol *id = NULL;
    x->active = true;
    x->multi = false;
    // flags
    while (argc && (argv->a_type == A_SYMBOL)) {
        const char *flag = argv->a_w.w_symbol->s_name;
        if (*flag == '-') {
            if (!strcmp(flag, "-m")) {
                x->multi = true;
                argc--; argv++;
            } else {
                pd_error(x, "%s: ignore unknown flag '%s",
                    classname(x), flag);
            }
            argc--; argv++;
        } else break;
    }
    // sr|id
    // NB: we keep this code for backwards compatibility.
    // 'sr' doesn't really do anything because faust_dsp() will
    // always update the DSP to the actual samplerate.
    for (int i = 0; i < argc; i++) {
        if (argv[i].a_type == A_FLOAT)
            sr = (int)argv[i].a_w.w_float;
        else if (argv[i].a_type == A_SYMBOL)
            id = argv[i].a_w.w_symbol;
    }
    if (sr <= 0) sr = 44100;
    x->rate = sr;
    x->xfade = 0;
    x->n_xfade = (int)(sr*XFADE_TIME/64);
    x->inputs = x->outputs = x->buf = NULL;
    x->dummy = NULL;
    x->label = new std::string(sym(mydsp) "~");
    x->dsp = new mydsp();
    x->ui = new PdUI(sym(mydsp), id?id->s_name:NULL);
    if (id) {
        *x->label += " ";
        *x->label += id->s_name;
    }
    x->n_in = x->dsp->getNumInputs();
    x->n_out = x->dsp->getNumOutputs();
    assert((x->n_in + x->n_out) > 0); /* there must be at least one signal */
    if (x->n_in > 0)
        x->inputs = (t_sample**)malloc(x->n_in*sizeof(t_sample*));
    if (x->n_out > 0) {
        x->outputs = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
        x->buf = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
        for (int i = 0; i < x->n_out; i++)
            x->buf[i] = NULL;
    }
    x->dsp->init(sr);
    x->dsp->buildUserInterface(x->ui);
#if !NEWIO
    /* the message outlet comes first! */
    x->out = outlet_new(&x->x_obj, 0);
#endif
    if (x->multi) {
        /* only create a single (multi-channel) signal inlet and outlet;
         * NB: if NEWIO is 1, we already have a signal inlet! */
    #if !NEWIO
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    #endif
        outlet_new(&x->x_obj, &s_signal);
    } else {
    #if NEWIO
        /* we already have a signal inlet */
        for (int i = 1; i < x->n_in; i++)
    #else
        for (int i = 0; i < x->n_in; i++)
    #endif
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->n_out; i++)
            outlet_new(&x->x_obj, &s_signal);
    }
#if NEWIO
    /* the message outlet comes last! */
    x->out = outlet_new(&x->x_obj, 0);
#endif
    return (void *)x;
}

extern "C" void faust_setup(mydsp)
{
#ifdef HAVE_MULTICHANNEL
    // runtime check for multichannel support:
#ifdef _WIN32
    // get a handle to the module containing the Pd API functions.
    // NB: GetModuleHandle("pd.dll") does not cover all cases.
    HMODULE module;
    int moduleflags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                      GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
    if (GetModuleHandleEx(moduleflags, (LPCSTR)&pd_typedmess, &module)) {
        g_signal_setmultiout = (t_signal_setmultiout)(void *)GetProcAddress(
            module, "signal_setmultiout");
    }
#else
    // search recursively, starting from the main program
    g_signal_setmultiout = (t_signal_setmultiout)dlsym(
        dlopen(nullptr, RTLD_NOW), "signal_setmultiout");
#endif
#endif // HAVE_MULTICHANNEL

    t_symbol *s = gensym(sym(mydsp) "~");
    int classflags = g_signal_setmultiout ? CLASS_MULTICHANNEL : 0;
    faust_class = class_new(s, (t_newmethod)faust_new, (t_method)faust_free,
        sizeof(t_faust), classflags, A_GIMME, A_NULL);
    class_addmethod(faust_class, (t_method)faust_dsp, gensym((char*)"dsp"), A_NULL);
#if NEWIO
    /* the first inlet is a signal inlet */
    CLASS_MAINSIGNALIN(faust_class, t_faust, f);
#endif
    class_addanything(faust_class, faust_any);
    s_button = gensym((char*)"button");
    s_checkbox = gensym((char*)"checkbox");
    s_vslider = gensym((char*)"vslider");
    s_hslider = gensym((char*)"hslider");
    s_nentry = gensym((char*)"nentry");
    s_vbargraph = gensym((char*)"vbargraph");
    s_hbargraph = gensym((char*)"hbargraph");
    /* force initialization of mydsp */
    mydsp dsp;
    /* give some indication that we're loaded and ready to go */
    post("[faust] %s: %d inputs, %d outputs", sym(mydsp) "~",
         dsp.getNumInputs(), dsp.getNumOutputs());
}
