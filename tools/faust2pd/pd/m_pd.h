/* Copyright (c) 1997-1999 Miller Puckette.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

#ifndef __m_pd_h_

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
extern "C" {
#endif

#define PD_MAJOR_VERSION 0
#define PD_MINOR_VERSION 55
#define PD_BUGFIX_VERSION 0
#define PD_TEST_VERSION ""

/* compile-time version check:
   #if PD_VERSION_CODE < PD_VERSION(0, 56, 0)
      // put legacy code for Pd<<0.56 in here
   #endif
 */
#define PD_VERSION(major, minor, bugfix) \
    (((major) << 16) + ((minor) << 8) + ((bugfix) > 255 ? 255 : (bugfix)))
#define PD_VERSION_CODE PD_VERSION(PD_MAJOR_VERSION, PD_MINOR_VERSION, PD_BUGFIX_VERSION)

extern int pd_compatibilitylevel;   /* e.g., 43 for pd 0.43 compatibility */

/* old name for "MSW" flag -- we have to take it for the sake of many old
"nmakefiles" for externs, which will define NT and not MSW */
#if defined(NT) && !defined(MSW)
#define MSW
#endif

/* These pragmas are only used for MSVC, not MinGW or Cygwin <hans@at.or.at> */
#ifdef _MSC_VER
/* #pragma warning( disable : 4091 ) */
#pragma warning( disable : 4305 )  /* uncast const double to float */
#pragma warning( disable : 4244 )  /* uncast float/int conversion etc. */
#pragma warning( disable : 4101 )  /* unused automatic variables */
#endif /* _MSC_VER */

    /* the external storage class is "extern" in UNIX; in MSW it's ugly. */
#ifndef EXTERN
#ifdef _WIN32
#ifdef PD_INTERNAL
#define EXTERN __declspec(dllexport) extern
#else
#define EXTERN __declspec(dllimport) extern
#endif /* PD_INTERNAL */
#else
#define EXTERN extern
#endif /* _WIN32 */
#endif /* EXTERN */

    /* On most c compilers, you can just say "struct foo;" to declare a
    structure whose elements are defined elsewhere.  On very old MSVC versions,
    when compiling C (but not C++) code, you have to say "extern struct foo;".
    So we make a stupid macro: */
#if defined(_MSC_VER) && !defined(_LANGUAGE_C_PLUS_PLUS) \
    && !defined(__cplusplus) && (_MSC_VER < 1700)
#define EXTERN_STRUCT extern struct
#else
#define EXTERN_STRUCT struct
#endif


/* util for better inlining of static functions in headers */
#if defined(__cplusplus)
# define PD_INLINE inline
#else
# if (__STDC_VERSION__ >= 199901L)
#  define PD_INLINE static inline
# else
#  define PD_INLINE static
# endif
#endif


/* Define some attributes, specific to the compiler */
#if defined(__GNUC__)
#define ATTRIBUTE_FORMAT_PRINTF(a, b) __attribute__ ((format (printf, a, b)))
#else
#define ATTRIBUTE_FORMAT_PRINTF(a, b)
#endif

#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define PD_STATIC_ASSERT _Static_assert
#elif __cplusplus >= 201103L
#define PD_STATIC_ASSERT static_assert
#else
#define PD_STATIC_ASSERT(condition, message) /* no-op */
#endif

/* deprecation warning */
#ifndef PD_DEPRECATED
# ifdef __GNUC__
#  define PD_DEPRECATED __attribute__ ((deprecated))
# elif defined(_MSC_VER) && _MSC_VER >= 1300
#  define PD_DEPRECATED __declspec(deprecated)
# else
#  define PD_DEPRECATED
#  pragma message("PD_DEPRECATED not defined for this compiler")
# endif
#endif

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#include <stddef.h>     /* just for size_t -- how lame! */
#endif

#include <stddef.h> /* for size_t and offsetof */

/* Microsoft Visual Studio is not C99, but since VS2015 has included most C99 headers:
   https://docs.microsoft.com/en-us/previous-versions/hh409293(v=vs.140)#c-runtime-library
   These definitions recreate stdint.h types, but only in pre-2015 Visual Studio: */
#if defined(_MSC_VER) && _MSC_VER < 1900
typedef signed __int8     int8_t;
typedef signed __int16    int16_t;
typedef signed __int32    int32_t;
typedef signed __int64    int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
#else
# include <stdint.h>
#endif

/* for FILE, needed by sys_fopen() and sys_fclose() only */
#include <stdio.h>

#define MAXPDSTRING 1000        /* use this for anything you want */
#define MAXPDARG 5              /* max number of args we can typecheck today */

/* signed and unsigned integer types the size of a pointer:  */
#if !defined(PD_LONGINTTYPE)
#if defined(_WIN32) && defined(_WIN64)
#define PD_LONGINTTYPE long long
#else
#define PD_LONGINTTYPE long
#endif
#endif

#if !defined(PD_FLOATSIZE)
  /* normally, our floats (t_float, t_sample,...) are 32bit */
# define PD_FLOATSIZE 32
#endif

#if PD_FLOATSIZE == 32
# define PD_FLOATTYPE float
/* an unsigned int of the same size as FLOATTYPE: */
# define PD_FLOATUINTTYPE uint32_t

#elif PD_FLOATSIZE == 64
# define PD_FLOATTYPE double
# define PD_FLOATUINTTYPE uint64_t
#else
# error invalid FLOATSIZE: must be 32 or 64
#endif

typedef PD_LONGINTTYPE t_int;       /* pointer-size integer */
typedef PD_FLOATTYPE t_float;       /* a float type at most the same size */
typedef PD_FLOATTYPE t_floatarg;    /* float type for function calls */

typedef struct _symbol
{
    const char *s_name;
    struct _class **s_thing;
    struct _symbol *s_next;
} t_symbol;

EXTERN_STRUCT _array;
#define t_array struct _array       /* g_canvas.h */

/* pointers to glist and array elements go through a "stub" which sticks
around after the glist or array is freed.  The stub itself is deleted when
both the glist/array is gone and the refcount is zero, ensuring that no
gpointers are pointing here. */

#define GP_NONE 0       /* the stub points nowhere (has been cut off) */
#define GP_GLIST 1      /* the stub points to a glist element */
#define GP_ARRAY 2      /* ... or array */

typedef struct _gstub
{
    union
    {
        struct _glist *gs_glist;    /* glist we're in */
        struct _array *gs_array;    /* array we're in */
    } gs_un;
    int gs_which;                   /* GP_GLIST/GP_ARRAY */
    int gs_refcount;                /* number of gpointers pointing here */
} t_gstub;

typedef struct _gpointer           /* pointer to a gobj in a glist */
{
    union
    {
        struct _scalar *gp_scalar;  /* scalar we're in (if glist) */
        union word *gp_w;           /* raw data (if array) */
    } gp_un;
    int gp_valid;                   /* number which must match gpointee */
    t_gstub *gp_stub;               /* stub which points to glist/array */
} t_gpointer;

typedef union word
{
    t_float w_float;
    t_symbol *w_symbol;
    t_gpointer *w_gpointer;
    t_array *w_array;
    struct _binbuf *w_binbuf;
    int w_index;
} t_word;

typedef enum
{
    A_NULL = 0,
    A_FLOAT,
    A_SYMBOL,
    A_POINTER,
    A_SEMI,
    A_COMMA,
    A_DEFFLOAT,
    A_DEFSYM,
    A_DOLLAR,
    A_DOLLSYM,
    A_GIMME,
    A_CANT
}  t_atomtype;

#define A_DEFSYMBOL A_DEFSYM    /* better name for this */

typedef struct _atom
{
    t_atomtype a_type;
    union word a_w;
} t_atom;

EXTERN_STRUCT _class;
#define t_class struct _class

EXTERN_STRUCT _outlet;
#define t_outlet struct _outlet

EXTERN_STRUCT _inlet;
#define t_inlet struct _inlet

EXTERN_STRUCT _binbuf;
#define t_binbuf struct _binbuf

EXTERN_STRUCT _clock;
#define t_clock struct _clock

EXTERN_STRUCT _outconnect;
#define t_outconnect struct _outconnect

EXTERN_STRUCT _glist;
#define t_glist struct _glist
#define t_canvas struct _glist  /* LATER lose this */

EXTERN_STRUCT _template;

typedef t_class *t_pd;      /* pure datum: nothing but a class pointer */

typedef struct _gobj        /* a graphical object */
{
    t_pd g_pd;              /* pure datum header (class) */
    struct _gobj *g_next;   /* next in list */
} t_gobj;

typedef struct _scalar      /* a graphical object holding data */
{
    t_gobj sc_gobj;         /* header for graphical object */
    t_symbol *sc_template;  /* template name (LATER replace with pointer) */
    t_word sc_vec[1];       /* indeterminate-length array of words */
} t_scalar;

typedef struct _text        /* patchable object - graphical, with text */
{
    t_gobj te_g;                /* header for graphical object */
    t_binbuf *te_binbuf;        /* holder for the text */
    t_outlet *te_outlet;        /* linked list of outlets */
    t_inlet *te_inlet;          /* linked list of inlets */
    short te_xpix;              /* x&y location (within the toplevel) */
    short te_ypix;
    short te_width;             /* requested width in chars, 0 if auto */
    unsigned int te_type:2;     /* from defs below */
} t_text;

#define T_TEXT 0        /* just a textual comment */
#define T_OBJECT 1      /* a MAX style patchable object */
#define T_MESSAGE 2     /* a MAX type message */
#define T_ATOM 3        /* a cell to display a number or symbol */

#define te_pd te_g.g_pd

   /* t_object is synonym for t_text (LATER unify them) */

typedef struct _text t_object;

#define ob_outlet te_outlet
#define ob_inlet te_inlet
#define ob_binbuf te_binbuf
#define ob_pd te_g.g_pd
#define ob_g te_g

typedef void (*t_method)(void);
typedef void *(*t_newmethod)(void);

/* in ARM 64 a varargs prototype generates a different function call sequence
from a fixed one, so in that special case we make a more restrictive
definition for t_gotfn.  This will break some code in the "chaos" package
in Pd extended.  (that code will run incorrectly anyhow so why not catch it
at compile time anyhow.) */
#if defined(__APPLE__) && defined(__aarch64__)
typedef void (*t_gotfn)(void *x);
#else
typedef void (*t_gotfn)(void *x, ...);
#endif

/* ---------------- pre-defined objects and symbols --------------*/
EXTERN t_pd pd_objectmaker;     /* factory for creating "object" boxes */
EXTERN t_pd pd_canvasmaker;     /* factory for creating canvases */

/* --------- prototypes from the central message system ----------- */
EXTERN void pd_typedmess(t_pd *x, t_symbol *s, int argc, t_atom *argv);
EXTERN void pd_forwardmess(t_pd *x, int argc, t_atom *argv);
EXTERN t_symbol *gensym(const char *s);
EXTERN t_gotfn getfn(const t_pd *x, t_symbol *s);
EXTERN t_gotfn zgetfn(const t_pd *x, t_symbol *s);
EXTERN void nullfn(void);
EXTERN void pd_vmess(t_pd *x, t_symbol *s, const char *fmt, ...);

/* the following macros are for sending non-type-checkable messages, i.e.,
using function lookup but circumventing type checking on arguments.  Only
use for internal messaging protected by A_CANT so that the message can't
be generated at patch level. */
#define mess0(x, s) ((*getfn((x), (s)))((x)))
typedef void (*t_gotfn1)(void *x, void *arg1);
#define mess1(x, s, a) ((*(t_gotfn1)getfn((x), (s)))((x), (a)))
typedef void (*t_gotfn2)(void *x, void *arg1, void *arg2);
#define mess2(x, s, a,b) ((*(t_gotfn2)getfn((x), (s)))((x), (a),(b)))
typedef void (*t_gotfn3)(void *x, void *arg1, void *arg2, void *arg3);
#define mess3(x, s, a,b,c) ((*(t_gotfn3)getfn((x), (s)))((x), (a),(b),(c)))
typedef void (*t_gotfn4)(void *x,
    void *arg1, void *arg2, void *arg3, void *arg4);
#define mess4(x, s, a,b,c,d) \
    ((*(t_gotfn4)getfn((x), (s)))((x), (a),(b),(c),(d)))
typedef void (*t_gotfn5)(void *x,
    void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);
#define mess5(x, s, a,b,c,d,e) \
    ((*(t_gotfn5)getfn((x), (s)))((x), (a),(b),(c),(d),(e)))

EXTERN void obj_list(t_object *x, t_symbol *s, int argc, t_atom *argv);
EXTERN t_pd *pd_newest(void);

/* --------------- memory management -------------------- */
EXTERN void *getbytes(size_t nbytes);
EXTERN void *getzbytes(size_t nbytes);
EXTERN void *copybytes(const void *src, size_t nbytes);
EXTERN void freebytes(void *x, size_t nbytes);
EXTERN void *resizebytes(void *x, size_t oldsize, size_t newsize);

/* -------------------- atoms ----------------------------- */

#define SETSEMI(atom) ((atom)->a_type = A_SEMI, (atom)->a_w.w_index = 0)
#define SETCOMMA(atom) ((atom)->a_type = A_COMMA, (atom)->a_w.w_index = 0)
#define SETPOINTER(atom, gp) ((atom)->a_type = A_POINTER, \
    (atom)->a_w.w_gpointer = (gp))
#define SETFLOAT(atom, f) ((atom)->a_type = A_FLOAT, (atom)->a_w.w_float = (f))
#define SETSYMBOL(atom, s) ((atom)->a_type = A_SYMBOL, \
    (atom)->a_w.w_symbol = (s))
#define SETDOLLAR(atom, n) ((atom)->a_type = A_DOLLAR, \
    (atom)->a_w.w_index = (n))
#define SETDOLLSYM(atom, s) ((atom)->a_type = A_DOLLSYM, \
    (atom)->a_w.w_symbol= (s))

EXTERN t_float atom_getfloat(const t_atom *a);
EXTERN t_int atom_getint(const t_atom *a);
EXTERN t_symbol *atom_getsymbol(const t_atom *a);
EXTERN t_symbol *atom_gensym(const t_atom *a);
EXTERN t_float atom_getfloatarg(int which, int argc, const t_atom *argv);
EXTERN t_int atom_getintarg(int which, int argc, const t_atom *argv);
EXTERN t_symbol *atom_getsymbolarg(int which, int argc, const t_atom *argv);

EXTERN void atom_string(const t_atom *a, char *buf, unsigned int bufsize);

/* ------------------  binbufs --------------- */

EXTERN t_binbuf *binbuf_new(void);
EXTERN void binbuf_free(t_binbuf *x);
EXTERN t_binbuf *binbuf_duplicate(const t_binbuf *y);

EXTERN void binbuf_text(t_binbuf *x, const char *text, size_t size);
EXTERN void binbuf_gettext(const t_binbuf *x, char **bufp, int *lengthp);
EXTERN void binbuf_clear(t_binbuf *x);
EXTERN void binbuf_add(t_binbuf *x, int argc, const t_atom *argv);
EXTERN void binbuf_addv(t_binbuf *x, const char *fmt, ...);
EXTERN void binbuf_addbinbuf(t_binbuf *x, const t_binbuf *y);
EXTERN void binbuf_addsemi(t_binbuf *x);
EXTERN void binbuf_restore(t_binbuf *x, int argc, const t_atom *argv);
EXTERN void binbuf_print(const t_binbuf *x);
EXTERN int binbuf_getnatom(const t_binbuf *x);
EXTERN t_atom *binbuf_getvec(const t_binbuf *x);
EXTERN int binbuf_resize(t_binbuf *x, int newsize);
EXTERN void binbuf_eval(const t_binbuf *x, t_pd *target, int argc, const t_atom *argv);
EXTERN int binbuf_read(t_binbuf *b, const char *filename, const char *dirname,
    int crflag);
EXTERN int binbuf_read_via_canvas(t_binbuf *b, const char *filename, const t_canvas *canvas,
    int crflag);
EXTERN int binbuf_read_via_path(t_binbuf *b, const char *filename, const char *dirname,
    int crflag);
EXTERN int binbuf_write(const t_binbuf *x, const char *filename, const char *dir,
    int crflag);
EXTERN void binbuf_evalfile(t_symbol *name, t_symbol *dir);
EXTERN t_symbol *binbuf_realizedollsym(t_symbol *s, int ac, const t_atom *av,
    int tonew);

/* ------------------  clocks --------------- */

EXTERN t_clock *clock_new(void *owner, t_method fn);
EXTERN void clock_set(t_clock *x, double systime);
EXTERN void clock_delay(t_clock *x, double delaytime);
EXTERN void clock_unset(t_clock *x);
EXTERN void clock_setunit(t_clock *x, double timeunit, int sampflag);
EXTERN double clock_getlogicaltime(void);
PD_DEPRECATED EXTERN double clock_getsystime(void); /* use clock_getlogicaltime() */
EXTERN double clock_gettimesince(double prevsystime);
EXTERN double clock_gettimesincewithunits(double prevsystime,
    double units, int sampflag);
EXTERN double clock_getsystimeafter(double delaytime);
EXTERN void clock_free(t_clock *x);

/* ----------------- pure data ---------------- */
EXTERN t_pd *pd_new(t_class *cls);
EXTERN void pd_free(t_pd *x);
EXTERN void pd_bind(t_pd *x, t_symbol *s);
EXTERN void pd_unbind(t_pd *x, t_symbol *s);
EXTERN t_pd *pd_findbyclass(t_symbol *s, const t_class *c);
EXTERN void pd_pushsym(t_pd *x);
EXTERN void pd_popsym(t_pd *x);
EXTERN void pd_bang(t_pd *x);
EXTERN void pd_pointer(t_pd *x, t_gpointer *gp);
EXTERN void pd_float(t_pd *x, t_float f);
EXTERN void pd_symbol(t_pd *x, t_symbol *s);
EXTERN void pd_list(t_pd *x, t_symbol *s, int argc, t_atom *argv);
EXTERN void pd_anything(t_pd *x, t_symbol *s, int argc, t_atom *argv);
#define pd_class(x) (*(x))

/* ----------------- pointers ---------------- */
EXTERN void gpointer_init(t_gpointer *gp);
EXTERN void gpointer_copy(const t_gpointer *gpfrom, t_gpointer *gpto);
EXTERN void gpointer_unset(t_gpointer *gp);
EXTERN int gpointer_check(const t_gpointer *gp, int headok);

/* ----------------- patchable "objects" -------------- */
EXTERN t_inlet *inlet_new(t_object *owner, t_pd *dest, t_symbol *s1,
    t_symbol *s2);
EXTERN t_inlet *pointerinlet_new(t_object *owner, t_gpointer *gp);
EXTERN t_inlet *floatinlet_new(t_object *owner, t_float *fp);
EXTERN t_inlet *symbolinlet_new(t_object *owner, t_symbol **sp);
EXTERN t_inlet *signalinlet_new(t_object *owner, t_float f);
EXTERN void inlet_free(t_inlet *x);

EXTERN t_outlet *outlet_new(t_object *owner, t_symbol *s);
EXTERN void outlet_bang(t_outlet *x);
EXTERN void outlet_pointer(t_outlet *x, t_gpointer *gp);
EXTERN void outlet_float(t_outlet *x, t_float f);
EXTERN void outlet_symbol(t_outlet *x, t_symbol *s);
EXTERN void outlet_list(t_outlet *x, t_symbol *s, int argc, t_atom *argv);
EXTERN void outlet_anything(t_outlet *x, t_symbol *s, int argc, t_atom *argv);
EXTERN t_symbol *outlet_getsymbol(t_outlet *x);
EXTERN void outlet_free(t_outlet *x);
EXTERN t_object *pd_checkobject(t_pd *x);


/* -------------------- canvases -------------- */

EXTERN void glob_setfilename(void *dummy, t_symbol *name, t_symbol *dir);

EXTERN void canvas_setargs(int argc, const t_atom *argv);
EXTERN void canvas_getargs(int *argcp, t_atom **argvp);
EXTERN t_symbol *canvas_getcurrentdir(void);
EXTERN t_glist *canvas_getcurrent(void);
EXTERN void canvas_makefilename(const t_glist *c, const char *file,
    char *result, int resultsize);
EXTERN t_symbol *canvas_getdir(const t_glist *x);
EXTERN char sys_font[]; /* default typeface set in s_main.c */
EXTERN char sys_fontweight[]; /* default font weight set in s_main.c */
EXTERN int sys_hostfontsize(int fontsize, int zoom);
EXTERN int sys_zoomfontwidth(int fontsize, int zoom, int worstcase);
EXTERN int sys_zoomfontheight(int fontsize, int zoom, int worstcase);
EXTERN int sys_fontwidth(int fontsize);
EXTERN int sys_fontheight(int fontsize);
EXTERN void canvas_dataproperties(t_glist *x, t_scalar *sc, t_binbuf *b);
EXTERN int canvas_open(const t_canvas *x, const char *name, const char *ext,
    char *dirresult, char **nameresult, unsigned int size, int bin);
EXTERN t_float canvas_getsr(t_canvas *x);
EXTERN int canvas_getsignallength(t_canvas *x);

/* ---------------- widget behaviors ---------------------- */

EXTERN_STRUCT _widgetbehavior;
#define t_widgetbehavior struct _widgetbehavior

EXTERN_STRUCT _parentwidgetbehavior;
#define t_parentwidgetbehavior struct _parentwidgetbehavior
EXTERN const t_parentwidgetbehavior *pd_getparentwidget(t_pd *x);

/* -------------------- classes -------------- */

#define CLASS_DEFAULT 0         /* flags for new classes below */
#define CLASS_PD 1              /* non-canvasable (bare) pd such as an inlet */
#define CLASS_GOBJ 2            /* pd that can belong to a canvas */
#define CLASS_PATCHABLE 3       /* pd that also can have inlets and outlets */
#define CLASS_TYPEMASK 3

#define CLASS_NOINLET 8             /* suppress left inlet */
#define CLASS_MULTICHANNEL 0x10     /* can deal with multichannel sigs */
#define CLASS_NOPROMOTESIG 0x20     /* don't promote scalars to signals */
#define CLASS_NOPROMOTELEFT 0x40    /* not even the main (left) inlet */

/*
    Setting a tilde object's CLASS_MULTICHANNEL flag declares that it can
    deal with multichannel inputs.  In this case the channel counts of
    the inputs might not match; it's up to the dsp method to figure out what
    to do.  Also, the output signal vectors aren't allocated.  The output
    channel counts have to be specified by the object at DSP time.  If
    the object can't put itself on the DSP chain it then has to create
    outputs anyway and arrange to zero them.

    By default, if a tilde object's inputs are unconnected, Pd fills them
    in by adding scalar-to-vector conversions to the DSP chain as needed before
    calling the dsp method.  This behavior can be suppressed for the left
    (main) inlet by setting CLASS_NOPROMOTELEFT and for one or more non-main
    inlets by setting CLASS_NOPROMOTESIG.  Seeing this, the object can then
    opt to supply a faster routine; for example, "+" can do a vector-scalar
    add.  In any case, signal outputs are all vectors, and are allocated
    automatically unless the CLASS_MULTICHANNEL flag is also set.
*/

EXTERN t_class *class_new(t_symbol *name, t_newmethod newmethod,
    t_method freemethod, size_t size, int flags, t_atomtype arg1, ...);

EXTERN t_class *class_new64(t_symbol *name, t_newmethod newmethod,
    t_method freemethod, size_t size, int flags, t_atomtype arg1, ...);

EXTERN void class_free(t_class *c);

#ifdef PDINSTANCE
EXTERN t_class *class_getfirst(void);
#endif

EXTERN void class_addcreator(t_newmethod newmethod, t_symbol *s,
    t_atomtype type1, ...);
EXTERN void class_addmethod(t_class *c, t_method fn, t_symbol *sel,
    t_atomtype arg1, ...);
EXTERN void class_addbang(t_class *c, t_method fn);
EXTERN void class_addpointer(t_class *c, t_method fn);
EXTERN void class_doaddfloat(t_class *c, t_method fn);
EXTERN void class_addsymbol(t_class *c, t_method fn);
EXTERN void class_addlist(t_class *c, t_method fn);
EXTERN void class_addanything(t_class *c, t_method fn);
EXTERN void class_sethelpsymbol(t_class *c, t_symbol *s);
EXTERN void class_setwidget(t_class *c, const t_widgetbehavior *w);
EXTERN void class_setparentwidget(t_class *c, const t_parentwidgetbehavior *w);
EXTERN const char *class_getname(const t_class *c);
EXTERN const char *class_gethelpname(const t_class *c);
EXTERN const char *class_gethelpdir(const t_class *c);
EXTERN void class_setdrawcommand(t_class *c);
EXTERN int class_isdrawcommand(const t_class *c);
EXTERN void class_set_extern_dir(t_symbol *s);
EXTERN void class_domainsignalin(t_class *c, int onset);
#define CLASS_MAINSIGNALIN(c, type, field) \
    PD_STATIC_ASSERT(sizeof(((type *)NULL)->field) == sizeof(t_float), "field must be t_float!"); \
    class_domainsignalin(c, offsetof(type, field))

         /* prototype for functions to save Pd's to a binbuf */
typedef void (*t_savefn)(t_gobj *x, t_binbuf *b);
EXTERN void class_setsavefn(t_class *c, t_savefn f);
EXTERN t_savefn class_getsavefn(const t_class *c);
EXTERN void obj_saveformat(const t_object *x, t_binbuf *bb); /* add format to bb */

        /* prototype for functions to open properties dialogs */
typedef void (*t_propertiesfn)(t_gobj *x, struct _glist *glist);
EXTERN void class_setpropertiesfn(t_class *c, t_propertiesfn f);
EXTERN t_propertiesfn class_getpropertiesfn(const t_class *c);

typedef void (*t_classfreefn)(t_class *);
EXTERN void class_setfreefn(t_class *c, t_classfreefn fn);

#ifndef PD_CLASS_DEF
#define class_addbang(x, y) class_addbang((x), (t_method)(y))
#define class_addpointer(x, y) class_addpointer((x), (t_method)(y))
#define class_addfloat(x, y) class_doaddfloat((x), (t_method)(y))
#define class_addsymbol(x, y) class_addsymbol((x), (t_method)(y))
#define class_addlist(x, y) class_addlist((x), (t_method)(y))
#define class_addanything(x, y) class_addanything((x), (t_method)(y))
#endif

#if PD_FLOATSIZE == 64
# define class_new class_new64
#endif

/* ------------   printing --------------------------------- */

EXTERN void post(const char *fmt, ...);
EXTERN void startpost(const char *fmt, ...);
EXTERN void poststring(const char *s);
EXTERN void postfloat(t_floatarg f);
EXTERN void postatom(int argc, const t_atom *argv);
EXTERN void endpost(void);

EXTERN void bug(const char *fmt, ...) ATTRIBUTE_FORMAT_PRINTF(1, 2);
EXTERN void pd_error(const void *object, const char *fmt, ...) ATTRIBUTE_FORMAT_PRINTF(2, 3);

/* for logpost(); does *not* work with verbose()! */
typedef enum {
    PD_CRITICAL = 0,
    PD_ERROR,
    PD_NORMAL,
    PD_DEBUG,
    PD_VERBOSE
} t_loglevel;

EXTERN void logpost(const void *object, int level, const char *fmt, ...)
    ATTRIBUTE_FORMAT_PRINTF(3, 4);

PD_DEPRECATED EXTERN void verbose(int level, const char *fmt, ...) ATTRIBUTE_FORMAT_PRINTF(2, 3); /* avoid this: use logpost() instead */


/* ------------  system interface routines ------------------- */
EXTERN int sys_isabsolutepath(const char *dir);
EXTERN void sys_bashfilename(const char *from, char *to);
EXTERN void sys_unbashfilename(const char *from, char *to);
EXTERN int open_via_path(const char *dir, const char *name, const char *ext,
    char *dirresult, char **nameresult, unsigned int size, int bin);
EXTERN int sched_geteventno(void);
EXTERN double sys_getrealtime(void);
EXTERN int (*sys_idlehook)(void);   /* hook to add idle time computation */

/* Win32's open()/fopen() do not handle UTF-8 filenames so we need
 * these internal versions that handle UTF-8 filenames the same across
 * all platforms.  They are recommended for use in external
 * objectclasses as well so they work with Unicode filenames on Windows */
EXTERN int sys_open(const char *path, int oflag, ...);
EXTERN int sys_close(int fd);
EXTERN FILE *sys_fopen(const char *filename, const char *mode);
EXTERN int sys_fclose(FILE *stream);

/* ------------  threading ------------------- */
EXTERN void sys_lock(void);
EXTERN void sys_unlock(void);
EXTERN int sys_trylock(void);


/* --------------- signals ----------------------------------- */

typedef PD_FLOATTYPE t_sample;
typedef union _sampleint_union {
  t_sample f;
  PD_FLOATUINTTYPE i;
} t_sampleint_union;
#define MAXLOGSIG 32
#define MAXSIGSIZE (1 << MAXLOGSIG)

typedef struct _signal
{
    union
    {
        int s_length;       /* number of items per channel */
        int s_n;            /* for source compatibility: pre-0.54 name */
    };
    t_sample *s_vec;        /* the samples, s_nchans vectors of s_length */
    t_float s_sr;           /* samples per second per channel */
    int s_nchans;           /* number of channels */
    int s_overlap;          /* number of times each sample appears */
    int s_refcount;         /* number of times signal is referenced */
    int s_isborrowed;       /* whether we're going to borrow our array */
    int s_isscalar;         /* scalar for an unconnected signal input */
    struct _signal *s_borrowedfrom;     /* signal to borrow it from */
    struct _signal *s_nextfree;         /* next in freelist */
    struct _signal *s_nextused;         /* next in used list */
    int s_nalloc;      /* allocated size of array in points */
} t_signal;

typedef t_int *(*t_perfroutine)(t_int *args);

EXTERN t_signal *signal_new(int length, int nchans, t_float sr,
    t_sample *scalarptr);
EXTERN void signal_setmultiout(t_signal **sig, int nchans);

EXTERN t_int *plus_perform(t_int *args);
EXTERN t_int *plus_perf8(t_int *args);
EXTERN t_int *zero_perform(t_int *args);
EXTERN t_int *zero_perf8(t_int *args);
EXTERN t_int *copy_perform(t_int *args);
EXTERN t_int *copy_perf8(t_int *args);
EXTERN t_int *scalarcopy_perform(t_int *args);
EXTERN t_int *scalarcopy_perf8(t_int *args);

EXTERN void dsp_add_plus(t_sample *in1, t_sample *in2, t_sample *out, int n);
EXTERN void dsp_add_copy(t_sample *in, t_sample *out, int n);
EXTERN void dsp_add_scalarcopy(t_float *in, t_sample *out, int n);
EXTERN void dsp_add_zero(t_sample *out, int n);

EXTERN int sys_getblksize(void);
EXTERN t_float sys_getsr(void);
EXTERN int sys_get_inchannels(void);
EXTERN int sys_get_outchannels(void);

EXTERN void dsp_add(t_perfroutine f, int n, ...);
EXTERN void dsp_addv(t_perfroutine f, int n, t_int *vec);
EXTERN void pd_fft(t_float *buf, int npoints, int inverse);
EXTERN int ilog2(int n);

EXTERN void mayer_fht(t_sample *fz, int n);
EXTERN void mayer_fft(int n, t_sample *real, t_sample *imag);
EXTERN void mayer_ifft(int n, t_sample *real, t_sample *imag);
EXTERN void mayer_realfft(int n, t_sample *real);
EXTERN void mayer_realifft(int n, t_sample *real);

EXTERN int canvas_suspend_dsp(void);
EXTERN void canvas_resume_dsp(int oldstate);
EXTERN void canvas_update_dsp(void);
EXTERN int canvas_dspstate;

/*   up/downsampling */
typedef struct _resample
{
  int method;       /* unused */

  int downsample; /* downsampling factor */
  int upsample;   /* upsampling factor */

  t_sample *s_vec;   /* here we hold the resampled data */
  int      s_n;

  t_sample *coeffs;  /* coefficients for filtering... */
  int      coefsize;

  t_sample *buffer;  /* buffer for filtering */
  int      bufsize;
} t_resample;

EXTERN void resample_init(t_resample *x);
EXTERN void resample_free(t_resample *x);

EXTERN void resample_dsp(t_resample *x, t_sample *in, int insize, t_sample *out, int outsize, int method);
EXTERN void resamplefrom_dsp(t_resample *x, t_sample *in, int insize, int outsize, int method);
EXTERN void resampleto_dsp(t_resample *x, t_sample *out, int insize, int outsize, int method);

/* ----------------------- utility functions for signals -------------- */
EXTERN t_float mtof(t_float);
EXTERN t_float ftom(t_float);
EXTERN t_float rmstodb(t_float);
EXTERN t_float powtodb(t_float);
EXTERN t_float dbtorms(t_float);
EXTERN t_float dbtopow(t_float);

EXTERN t_float q8_sqrt(t_float);
EXTERN t_float q8_rsqrt(t_float);
#ifndef N32
EXTERN t_float qsqrt(t_float);  /* old names kept for extern compatibility */
EXTERN t_float qrsqrt(t_float);
#endif

/* --------------------- data --------------------------------- */

    /* graphical arrays */
EXTERN_STRUCT _garray;
#define t_garray struct _garray

EXTERN t_class *garray_class;
PD_DEPRECATED EXTERN int garray_getfloatarray(t_garray *x, int *size, t_float **vec); /* use garray_getfloatwords() */
EXTERN int garray_getfloatwords(t_garray *x, int *size, t_word **vec);
EXTERN void garray_redraw(t_garray *x);
EXTERN int garray_npoints(t_garray *x);
EXTERN char *garray_vec(t_garray *x);
PD_DEPRECATED EXTERN void garray_resize(t_garray *x, t_floatarg f); /* use garray_resize_long() */
EXTERN void garray_resize_long(t_garray *x, long n);   /* better version */
EXTERN void garray_usedindsp(t_garray *x);
EXTERN void garray_setsaveit(t_garray *x, int saveit);
EXTERN t_glist *garray_getglist(t_garray *x);
EXTERN t_array *garray_getarray(t_garray *x);
EXTERN t_class *scalar_class;

EXTERN t_float *value_get(t_symbol *s);
EXTERN void value_release(t_symbol *s);
EXTERN int value_getfloat(t_symbol *s, t_float *f);
EXTERN int value_setfloat(t_symbol *s, t_float f);

/* ------- GUI interface - functions to send strings to TK --------- */
typedef void (*t_guicallbackfn)(t_gobj *client, t_glist *glist);

PD_DEPRECATED EXTERN void sys_vgui(const char *fmt, ...); /* avoid this: use pdgui_vmess() instead */
PD_DEPRECATED EXTERN void sys_gui(const char *s); /* avoid this: use pdgui_vmess() instead */

EXTERN void sys_pretendguibytes(int n);
EXTERN void sys_queuegui(void *client, t_glist *glist, t_guicallbackfn f);
EXTERN void sys_unqueuegui(void *client);
    /* dialog window creation and destruction */
PD_DEPRECATED EXTERN void gfxstub_new(t_pd *owner, void *key, const char *cmd); /* avoid this: use pdgui_stub_vnew() instead */
PD_DEPRECATED EXTERN void gfxstub_deleteforkey(void *key); /* avoid this: use pdgui_stub_deleteforkey() instead */

/*
 * send a message to the GUI, with a simplified formatting syntax
 * <destination>: receiver on the GUI side (e.g. a Tcl/Tk 'proc')
 * <fmt>: string of format specifiers
 * <...>: values according to the format specifiers
 *
 * the <destination> can be a NULL pointer (in which case it is ignored)
 * the user of NULL as a <destination> is discouraged

 * depending on the format specifiers, one or more values are passed
 *    'f' : <double:value>        : a floating point number
 *    'i' : <int:value>           : an integer number
 *    's' : <const char*:value>   : a string
 *    'r' : <const char*:value>   : a raw string
 *    'x' : <void*:value>         : a generic pointer
 *    'o' : <t_object*:value>     : an graphical object
 *    '^' : <t_canvas*:value>     : a toplevel window (legacy)
 *    'c' : <t_canvas*:value>     : a canvas (on a window)
 *    'F' : <int:size> <const t_float*:values>: array of t_float's
 *    'S' : <int:size> <const char**:values>: array of strings
 *    'R' : <int:size> <const char**:values>: array of raw strings
 *    'a' : <int:size> <const t_atom*:values>: list of atoms
 *    'A' : <int:size> <const t_atom*:values>: array of atoms
 *    'w' : <int:size> <const t_word*:values>: list of floatwords
 *    'W' : <int:size> <const t_word*:values>: array of floatwords
 *    'm' : <t_symbol*s:recv> <int:argc> <t_atom*:argv>: a Pd message
 *    'p' : <int:size> <const char*:values>  : a pascal string (explicit size; not \0-terminated)
 *    'k' : <int:color>           : a color (or kolor, if you prefer)
 *    ' ' : none                  : ignored
 * the use of the specifiers 'x^' is discouraged
 * raw-strings ('rR') should only be used for constant, well-known strings
 */
EXTERN void pdgui_vmess(const char* destination, const char* fmt, ...);


/* improved dialog window creation
 * this will insert a first argument to <destination> based on <key>
 * which the GUI can then use to callback.
 * gfxstub_new() ensures that the given receiver will be available,
 * even if the <owner> has been removed in the meantime.
 * see pdgui_vmess() for a description of <fmt> and the varargs
 */

EXTERN void pdgui_stub_vnew(t_pd *owner, const char* destination, void *key, const char* fmt, ...);
EXTERN void pdgui_stub_deleteforkey(void *key);


extern t_class *glob_pdobject;  /* object to send "pd" messages */

/*-------------  Max 0.26 compatibility --------------------*/

/* the following reflects the new way classes are laid out, with the class
   pointing to the messlist and not vice versa. Externs shouldn't feel it. */
typedef t_class *t_externclass;

EXTERN void c_extern(t_externclass *cls, t_newmethod newroutine,
    t_method freeroutine, t_symbol *name, size_t size, int tiny, \
    t_atomtype arg1, ...);
EXTERN void c_addmess(t_method fn, t_symbol *sel, t_atomtype arg1, ...);

#define t_getbytes getbytes
#define t_freebytes freebytes
#define t_resizebytes resizebytes
#define typedmess pd_typedmess
#define vmess pd_vmess

/* A definition to help gui objects straddle 0.34-0.35 changes.  If this is
defined, there is a "te_xpix" field in objects, not a "te_xpos" as before: */

#define PD_USE_TE_XPIX

#if defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(__aarch64__)

/* a test for NANs and denormals.
   WARNING: PD_BADFLOAT(0) = 1 -- you can replace a 'BADFLOAT' by 0 but don't
just do nothing with it. */

#if PD_FLOATSIZE == 32

typedef union
{
    t_float f;
    unsigned int ui;
} t_bigorsmall32;

PD_INLINE int PD_BADFLOAT(t_float f)  /* malformed float */
{
    t_bigorsmall32 pun;
    pun.f = f;
    pun.ui &= 0x7f800000;
    return((pun.ui == 0) | (pun.ui == 0x7f800000));
}

PD_INLINE int PD_BIGORSMALL(t_float f)  /* exponent outside (-64,64) */
{
    t_bigorsmall32 pun;
    pun.f = f;
    return((pun.ui & 0x20000000) == ((pun.ui >> 1) & 0x20000000));
}

#elif PD_FLOATSIZE == 64

typedef union
{
    t_float f;
    unsigned int ui[2];
} t_bigorsmall64;

PD_INLINE int PD_BADFLOAT(t_float f)  /* malformed double */
{
    t_bigorsmall64 pun;
    pun.f = f;
    pun.ui[1] &= 0x7ff00000;
    return((pun.ui[1] == 0) | (pun.ui[1] == 0x7ff00000));
}

PD_INLINE int PD_BIGORSMALL(t_float f)  /* exponent outside (-512,512) */
{
    t_bigorsmall64 pun;
    pun.f = f;
    return((pun.ui[1] & 0x20000000) == ((pun.ui[1] >> 1) & 0x20000000));
}

#endif /* PD_FLOATSIZE */
#else /* not INTEL or ARM */
#define PD_BADFLOAT(f) 0
#define PD_BIGORSMALL(f) 0
#endif

    /* get major/minor/bugfix version numbers and version code at run time */
EXTERN unsigned int sys_getversion(int *major, int *minor, int *bugfix);
#ifndef PD_INTERNAL
/* ABI compat hack: do not use _sys_getversioncode() directly! */
PD_INLINE unsigned int _sys_getversioncode(int*major, int*minor, int*bugfix)
{
    int a, b, c;
    sys_getversion(major, minor, bugfix);
    sys_getversion(&a, &b, &c);
    return PD_VERSION(a, b, c);
}
#define sys_getversion _sys_getversioncode
#endif

    /* get a Pd API function pointer by name. Returns NULL if the function
    does not exist. For example, This allows to use recently introduced API
    functions while providing a fallback for older Pd versions. */
EXTERN t_method sys_getfunbyname(const char *name);

    /* get floatsize at run time */
EXTERN unsigned int sys_getfloatsize(void);

EXTERN_STRUCT _instancemidi;
#define t_instancemidi struct _instancemidi

EXTERN_STRUCT _instanceinter;
#define t_instanceinter struct _instanceinter

EXTERN_STRUCT _instancecanvas;
#define t_instancecanvas struct _instancecanvas

EXTERN_STRUCT _instanceugen;
#define t_instanceugen struct _instanceugen

EXTERN_STRUCT _instancestuff;
#define t_instancestuff struct _instancestuff

#ifndef PDTHREADS
#define PDTHREADS 1
#endif

struct _pdinstance
{
    double pd_systime;          /* global time in Pd ticks */
    t_clock *pd_clock_setlist;  /* list of set clocks */
    t_canvas *pd_canvaslist;    /* list of all root canvases */
    struct _template *pd_templatelist;  /* list of all templates */
    int pd_instanceno;          /* ordinal number of this instance */
    t_symbol **pd_symhash;      /* symbol table hash table */
    t_instancemidi *pd_midi;    /* private stuff for x_midi.c */
    t_instanceinter *pd_inter;  /* private stuff for s_inter.c */
    t_instanceugen *pd_ugen;    /* private stuff for d_ugen.c */
    t_instancecanvas *pd_gui;   /* semi-private stuff in g_canvas.h */
    t_instancestuff *pd_stuff;  /* semi-private stuff in s_stuff.h */
    t_pd *pd_newest;            /* most recently created object */
#ifdef PDINSTANCE
    t_symbol  pd_s_pointer;
    t_symbol  pd_s_float;
    t_symbol  pd_s_symbol;
    t_symbol  pd_s_bang;
    t_symbol  pd_s_list;
    t_symbol  pd_s_anything;
    t_symbol  pd_s_signal;
    t_symbol  pd_s__N;
    t_symbol  pd_s__X;
    t_symbol  pd_s_x;
    t_symbol  pd_s_y;
    t_symbol  pd_s_;
#endif
#if PDTHREADS
    int pd_islocked;
#endif
};
#define t_pdinstance struct _pdinstance
EXTERN t_pdinstance pd_maininstance;

/* m_pd.c */
#ifdef PDINSTANCE
EXTERN t_pdinstance *pdinstance_new(void);
EXTERN void pd_setinstance(t_pdinstance *x);
EXTERN t_pdinstance *pd_getinstance(void);
EXTERN void pdinstance_free(t_pdinstance *x);
#endif /* PDINSTANCE */

#if defined(PDTHREADS) && defined(PDINSTANCE)
#ifdef _MSC_VER
#define PERTHREAD __declspec(thread)
#else
#define PERTHREAD __thread
#endif /* _MSC_VER */
#else
#define PERTHREAD
#endif

#ifdef PDINSTANCE
#ifdef _WIN32
/* Windows does not allow exporting thread-local variables from DLLs,
so externals need to get 'pd_this' with an (implicit) function call.
Internally, we may directly access 'pd_this', but we must not export it! */
#ifdef PD_INTERNAL
extern PERTHREAD t_pdinstance *pd_this; /* not EXTERN! */
#else
#define pd_this pd_getinstance()
#endif /* PD_INTERNAL */
#else
EXTERN PERTHREAD t_pdinstance *pd_this;
#endif /* _WIN32 */
EXTERN t_pdinstance **pd_instances;
EXTERN int pd_ninstances;
#else
#define pd_this (&pd_maininstance)
#endif /* PDINSTANCE */

#ifdef PDINSTANCE
#define s_pointer   (pd_this->pd_s_pointer)
#define s_float     (pd_this->pd_s_float)
#define s_symbol    (pd_this->pd_s_symbol)
#define s_bang      (pd_this->pd_s_bang)
#define s_list      (pd_this->pd_s_list)
#define s_anything  (pd_this->pd_s_anything)
#define s_signal    (pd_this->pd_s_signal)
#define s__N        (pd_this->pd_s__N)
#define s__X        (pd_this->pd_s__X)
#define s_x         (pd_this->pd_s_x)
#define s_y         (pd_this->pd_s_y)
#define s_          (pd_this->pd_s_)
#else
EXTERN t_symbol s_pointer, s_float, s_symbol, s_bang, s_list, s_anything,
  s_signal, s__N, s__X, s_x, s_y, s_;
#endif

EXTERN t_canvas *pd_getcanvaslist(void);
EXTERN int pd_getdspstate(void);

/* x_text.c */
EXTERN t_binbuf *text_getbufbyname(t_symbol *s); /* get binbuf from text obj */
EXTERN void text_notifybyname(t_symbol *s);      /* notify it was modified */

/* g_undo.c */
/* store two message-sets to be sent to the object's <s> method for 'undo'ing
 * resp. 'redo'ing the current state of an object.
 * this creates an internal copy of the atom-lists (so the caller is responsible
 * for freeing any dynamically allocated data)
 * this is a no-op if called during 'undo' (resp. 'redo').
 */
EXTERN void pd_undo_set_objectstate(t_canvas*canvas, t_pd*x, t_symbol*s,
                                    int undo_argc, t_atom*undo_argv,
                                    int redo_argc, t_atom*redo_argv);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
}
#endif

#define __m_pd_h_
#endif /* __m_pd_h_ */
