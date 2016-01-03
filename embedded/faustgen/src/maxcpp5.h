/*

Max 6 C++ Architecture
Based on the architecture created by Graham Wakefield
Modified to include dynamic creation of inlets and outlets, as well as support for Max6 by Martin Di Rollo
 
-- licence --
maxcpp is distributed under the permissive BSD-like MIT licence:

Copyright (c) 2009 Graham Wakefield

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef MAXMSP_CPP_6_H
#define MAXMSP_CPP_6_H

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "commonsyms.h"
#include "z_dsp.h"

#include <new>
#include <iostream>

#define MAX_CPP_VERSION	0.006
#define MAX_CPP_MAX_DSP_SIGNALS (512) // max. no. signal ins/outs

// for A_NOTHING methods (e.g. bang):
#define REGISTER_METHOD(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,						\
            (method)CLASS::MaxMethod<&CLASS::METHOD>::call,	\
            #METHOD,										\
            0);	

// for A_CANT methods (dblclick):
#define REGISTER_METHOD_CANT(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,							\
            (method)CLASS::MaxMethodCant<&CLASS::METHOD>::call,	\
            #METHOD,    \
            A_CANT,     \
            0);	

// for A_CANT methods (edclose):
#define REGISTER_METHOD_EDCLOSE(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodEdClose<&CLASS::METHOD>::call,	\
            #METHOD,    \
            A_CANT,     \
            0);	

// for A_CANT methods (faust_assist):
#define REGISTER_METHOD_ASSIST(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodAssist<&CLASS::METHOD>::call,	\
            #METHOD,    \
            A_CANT,     \
            0);	

// for A_CANT methods (jsave)
#define REGISTER_METHOD_JSAVE(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodJsave<&CLASS::METHOD>::call,	\
            #METHOD,    \
            A_CANT,     \
            0);	

// for A_GIMME methods (t_symbol * s, long argc, void * argv):
#define REGISTER_METHOD_GIMME(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodGimme<&CLASS::METHOD>::call,	\
            #METHOD,												\
            A_GIMME,												\
            0);	

// for A_DEFSYM methods (t_symbol *s) (par ex, read) :
#define REGISTER_METHOD_DEFSYM(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodDefSym<&CLASS::METHOD>::call,	\
            #METHOD,												\
            A_DEFSYM,												\
            0);	

// for A_FLOAT methods (double v):
#define REGISTER_METHOD_FLOAT(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,								\
            (method)CLASS::MaxMethodFloat<&CLASS::METHOD>::call,	\
            #METHOD,												\
            A_FLOAT,												\
            0);	
	
// for A_INT methods (long v):
#define REGISTER_METHOD_LONG(CLASS, METHOD)	class_addmethod(	\
            (t_class *)CLASS::m_class,							\
            (method)CLASS::MaxMethodLong<&CLASS::METHOD>::call,	\
            #METHOD,											\
            A_LONG,												\
            0);	
	
// A purely static base class for Max and MSP objects:
template <typename T>
class MaxCppBase {
public:	
	static t_class * m_class;
	
	// template functors to forward Max messages to class methods:
	
	typedef void (T::*maxmethodgimme)(long inlet, t_symbol * s, long ac, t_atom * av);
	template<maxmethodgimme F>
	struct MaxMethodGimme {
		static void call(T * x, t_symbol * s, long ac, t_atom * av) { ((x)->*F)(proxy_getinlet((t_object *)x), s, ac, av); }
	};
	
	typedef void (T::*maxmethod)(long inlet);
	template<maxmethod F>
	struct MaxMethod {
		static void call(T * x) { ((x)->*F)(proxy_getinlet((t_object *)x)); }
	};
    
    //A_CANT pour dblclick
    typedef void (T::*maxmethodcant)(long inlet);
	template<maxmethodcant F>
	struct MaxMethodCant {
		static void call(T * x) { ((x)->*F)(proxy_getinlet((t_object *)x)); }
	};
    
    //A_CANT pour paint
    typedef void (T::*maxmethodpaint)(long inlet, char** text, long size);
	template<maxmethodpaint F>
	struct MaxMethodPaint {
		static void call(T * x, t_object *view) { ((x)->*F)(proxy_getinlet((t_object *)x), view); }
	};
    
    //A_CANT pour drag
    typedef long (T::*maxmethoddrag)(t_object *drag, t_object *view);
	template<maxmethoddrag F>
	struct MaxMethodDrag {
		static long call(T * x, t_object *drag, t_object *view) { return ((x)->*F)(drag, view); }
	};

    //A_CANT pour edclose et edsave
    typedef void (T::*maxmethodedclose)(long inlet, char** text, long size);
	template<maxmethodedclose F>
	struct MaxMethodEdClose {
		static void call(T * x, char** text, long size) { ((x)->*F)(proxy_getinlet((t_object *)x), text, size); }
	};
    
    //A_CANT pour assist
    typedef void (T::*maxmethodassist)(void *b, long msg, long a, char *dst);
	template<maxmethodassist F>
	struct MaxMethodAssist {
		static void call(T * x, void *b, long msg, long a, char *dst) { ((x)->*F)(b, msg, a, dst); }
	};
    
    //A_CANT pour jsave
    typedef void (T::*maxmethodjsave)(t_dictionary *d);
	template<maxmethodjsave F>
	struct MaxMethodJsave {
		static void call(T * x, t_dictionary *d) { ((x)->*F)(d); }
	};
    
    //proxy_getinlet((t_object *)x), 
	
	typedef void (T::*maxmethodlong)(long inlet, long v);
	template<maxmethodlong F>
	struct MaxMethodLong {
		static void call(T * x, long v) { ((x)->*F)(proxy_getinlet((t_object *)x), v); }
	};
    
    //Template que j'ai rajoute pour pouvoir faire A_DEFSYM(t_symbol *s)
	typedef void (T::*maxmethoddefsym)(long inlet, t_symbol *s);
	template<maxmethoddefsym F>
	struct MaxMethodDefSym {
		static void call(T * x, t_symbol *s) { ((x)->*F)(proxy_getinlet((t_object *)x), s); }
	};  
	
	typedef void (T::*maxmethodfloat)(long inlet, double v);
	template<maxmethodfloat F>
	struct MaxMethodFloat {
		static void call(T * x, double v) { ((x)->*F)(proxy_getinlet((t_object *)x), v); }
	};
};

// Inherit from this one for non-audio objects
template <typename T>
class MaxCpp5 : public MaxCppBase<T> {
public:
	t_object m_ob;
	int m_outlets, m_inlets;
	void **	m_outlet;
	void **	m_inletproxy;
	long m_whichinlet;
	
	static t_class * makeMaxClass(const char * name);
	static void * create(t_symbol * sym, long ac, t_atom * av);
	static void destroy(t_object * x);
	
	void setupIO(unsigned int numinlets, unsigned int numoutlets);
    
	// C++ operator overload to treat MaxCpp5 objects as t_objects
	operator t_object & () { return m_ob; }
};

// Inherit from this one for audio objects
template <typename T>
class MspCpp5 : public MaxCppBase<T> {

public:
    
    typedef void (T::*maxmethodperform)(int vs, t_sample ** inputs, long numins, t_sample ** outputs, long numouts);
    typedef void (T::*maxmethodinit)(double samplerate);

    t_pxobject m_ob;
    unsigned int m_siginlets, m_sigoutlets;
    maxmethodperform m_perform;
    maxmethodinit m_init;
    double m_samplerate;
    
    MspCpp5():m_siginlets(0), m_sigoutlets(0)
    {}
	
	static t_class * makeMaxClass(const char * name);
	static void * create(t_symbol * sym, long ac, t_atom * av);
	static void destroy(t_object * x);
    
    void out_anything(t_symbol *s, short ac, t_atom *av);
   
	void setupIO(maxmethodperform meth, maxmethodinit init, unsigned int siginlets, unsigned int sigoutlets, bool initialize);
	
    // 32 bits
	static void internal_dsp_32(MspCpp5<T> * x, t_signal **sp, short *count);
    static t_int * internal_perform_32(t_int *);
    
    // 64 bits
    static void internal_dsp_64(MspCpp5<T> * x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
    static void internal_perform_64(MspCpp5<T> * x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
	
	// stub function in case the user doesn't supply one
	void dsp() {}
		
	struct PerformData {
		T * x;
		int vs;
	     
        t_sample * inputs[MAX_CPP_MAX_DSP_SIGNALS];
		t_sample * outputs[MAX_CPP_MAX_DSP_SIGNALS];
	};
};

// Note: only include this file once to prevent linker errors!
template<typename T> t_class * MaxCppBase<T>::m_class = 0;

template<typename T> t_class * MaxCpp5<T>::makeMaxClass(const char * name) {
	common_symbols_init();
	MaxCppBase<T>::m_class = class_new((char *)name, (method)MaxCpp5<T>::create, (method)MaxCpp5<T>::destroy, sizeof(T), 0L, A_GIMME, 0);   
	class_register(CLASS_BOX, MaxCppBase<T>::m_class);
	return MaxCppBase<T>::m_class;
}

template<typename T> void * MaxCpp5<T>::create(t_symbol * sym, long ac, t_atom * av) {
	void * x = object_alloc(MaxCppBase<T>::m_class);
	new(x) T(sym, ac, av);
    return (T *)x; 
}

template<typename T> void MaxCpp5<T>::destroy(t_object * x) {
	T * t = (T *)x;
	t->~T();
	// free outlets:
	sysmem_freeptr(t->m_outlet);
	sysmem_freeptr(t->m_inletproxy);
}


template<typename T> void MaxCpp5<T>::setupIO(unsigned int numinlets, unsigned int numoutlets) {
	if (numinlets > 0) {
		m_inlets = (long)numinlets - 1;
		m_inletproxy = (void **)sysmem_newptr(sizeof(void *) * m_inlets);
		for (long i = 1; i <= m_inlets; i++) {
			m_inletproxy[i] = proxy_new(this, i, &this->m_whichinlet); // generic outlet
        }
	}
	
	m_outlets = (long)numoutlets;
	m_outlet = (void **)sysmem_newptr(sizeof(void *) * m_outlets);
	for (long i = 0; i < m_outlets; i++) {
		m_outlet[m_outlets - i - 1] = outlet_new(this, NULL); // generic outlet
    }
}

template<typename T> t_class * MspCpp5<T>::makeMaxClass(const char * name) {
	common_symbols_init();
	MaxCppBase<T>::m_class = class_new((char *)name, (method)MspCpp5<T>::create, (method)MspCpp5<T>::destroy, sizeof(T), 0L, A_GIMME, 0);   
	class_dspinit(MaxCppBase<T>::m_class);
    
#ifdef MSP64    
    // 64 bits
  	class_addmethod(MaxCppBase<T>::m_class, (method)MspCpp5<T>::internal_dsp_64, "dsp64", A_CANT, 0);
#else
    // 32 bits
    class_addmethod(MaxCppBase<T>::m_class, (method)MspCpp5<T>::internal_dsp_32, "dsp", A_CANT, 0);
#endif

	class_register(CLASS_BOX, MaxCppBase<T>::m_class);
	return MaxCppBase<T>::m_class;
}

template<typename T> void * MspCpp5<T>::create(t_symbol * sym, long ac, t_atom * av) {
	void * x = object_alloc(MaxCppBase<T>::m_class);
	new(x) T(sym, ac, av);
    return (T *)x; 
}

template<typename T> void MspCpp5<T>::destroy(t_object * x) {
	dsp_free((t_pxobject *)x);
	T * t = (T *)x;
	t->~T();
}

template<typename T> void MspCpp5<T>::out_anything(t_symbol *s, short ac, t_atom *av) {
	outlet_anything(outlet_nth((t_object*)this, m_sigoutlets), s, ac, av);
}

template<typename T> void MspCpp5<T>::setupIO(maxmethodperform meth, maxmethodinit init, unsigned int siginlets, unsigned int sigoutlets, bool initialize) {
    m_perform = meth;
    m_init = init;
    
    if (siginlets > MAX_CPP_MAX_DSP_SIGNALS) {
        post("Error : siginlets %d > MAX_CPP_MAX_DSP_SIGNALS", siginlets);
    }
    
    if (sigoutlets > MAX_CPP_MAX_DSP_SIGNALS) {
        post("Error : sigoutlets %d > MAX_CPP_MAX_DSP_SIGNALS", sigoutlets);
    }
    
    siginlets = MIN(siginlets, MAX_CPP_MAX_DSP_SIGNALS);
    sigoutlets = MIN(sigoutlets, MAX_CPP_MAX_DSP_SIGNALS);
    
    if (initialize) {
        dsp_setup((t_pxobject*)this, siginlets);
    }
    
    // detect inlet/outlet count change
	if ((m_siginlets != siginlets) || (m_sigoutlets != sigoutlets)) {
   
        t_object* b = NULL;
        
        // start the transaction with our box
        object_obex_lookup(this, _sym_pound_B, (t_object **)&b);
        object_method(b, gensym("dynlet_begin"));

        // update our inlets (exported from z_dsp.h for dynamic inlet support)
        dsp_resize((t_pxobject*)this, siginlets);
        m_siginlets = siginlets;
      
        if (sigoutlets > m_sigoutlets) {
            for (unsigned int i = m_sigoutlets; i < sigoutlets; i++) {
                outlet_append((t_object*)this, NULL, gensym("signal"));
            }
            
            // Additional output
            // outlet_append((t_object*)this, NULL, NULL);
        } else if (sigoutlets < m_sigoutlets) {
            for (unsigned int i = m_sigoutlets; i > sigoutlets && i > 0; i--) {
                outlet_delete(outlet_nth((t_object*)this, i-1));
            }
        }
     
        // end the transaction
        m_sigoutlets = sigoutlets;
        object_method(b, gensym("dynlet_end"));
        
        // Invalidate DSP chain
        dspchain_setbroken(dspchain_fromobject((t_object *)this));
    }
 
	// prevent recycling of inputs for outputs
	m_ob.z_misc = Z_NO_INPLACE;
}

template<typename T> void MspCpp5<T>::internal_dsp_32(MspCpp5<T> * x, t_signal **sp, short *count) {
	int i = 0;
	int s = 0;
	PerformData pdata;
	pdata.x = (T *)x;	
	pdata.vs = sp[i]->s_n;
	for (i = 0; i < x->m_siginlets; i++, s++) {
		pdata.inputs[i] = sp[s]->s_vec;
	}
	for (i = 0; i < x->m_sigoutlets; i++, s++) {
		pdata.outputs[i] = sp[s]->s_vec;
	}
    
	dsp_addv(MspCpp5<T>::internal_perform_32, sizeof(PerformData)/sizeof(t_int), (void **)&pdata);
	pdata.x->dsp();
}

template<typename T> void MspCpp5<T>::internal_dsp_64(MspCpp5<T> * x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
    T* self = (T*)x;	
    if (samplerate != self->m_samplerate) {
        ((self)->*(self->m_init))(samplerate);
        self->m_samplerate = samplerate;
    }
    object_method(dsp64, gensym("dsp_add64"), x, MspCpp5<T>::internal_perform_64, 0, NULL);
}

template<typename T> t_int * MspCpp5<T>::internal_perform_32(t_int * w) {
	PerformData * pdata = (PerformData *)(w+1);
	MspCpp5<T> * x = pdata->x;
	T* self = pdata->x;
	if (!x->m_ob.z_disabled) {
		// forward this to the user dsp routine:
        AVOIDDENORMALS;
		((self)->*(self->m_perform))(pdata->vs, pdata->inputs, pdata->outputs);
	}
	return w + sizeof(PerformData)/sizeof(t_int) + 1;
}

template<typename T> void MspCpp5<T>::internal_perform_64(MspCpp5<T> * x, t_object *dsp64, double **ins, long numins, 
    double **outs, long numouts, long sampleframes, long flags, void *userparam) {
    T* self = (T*)x;	
    AVOIDDENORMALS;
    ((self)->*(self->m_perform))(sampleframes, ins, numins, outs, numouts);
}

#endif //MAXMSP_CPP_6_H
