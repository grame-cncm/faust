/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "faustparser.y"


#include "global.hh"

#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
#include "signals.hh"
#include "errormsg.hh"
#include "sourcereader.hh"
#include "doc.hh"
#include "ppbox.hh"

#include <string>
#include <list>

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMAXDEPTH	100000
	
using namespace std;

extern char* 		yytext;
extern const char* 	yyfilename;
extern int 			yylineno;
extern int 			yyerr;

int yylex();

//----------------------------------------------------------
// unquote() : remove enclosing quotes and carriage return 
// characters from string. Returns a Tree 
//----------------------------------------------------------
inline char replaceCR(char c)
{
	return (c!='\n') ? c : ' ';
}

// A definition is accepted if the prefixset is empty or if
// the current float precision is member of the prefix set
bool acceptdefinition(int prefixset)
{
	int precisions[] = {0, 1, 2, 4, 8};
	return (prefixset==0) || (prefixset & precisions[gGlobal->gFloatSize]);
}

Tree unquote(char* str)
{
    size_t size = strlen(str) + 1;
    
    //-----------copy unquoted filename-------------
    char* buf = (char*)alloca(size);
    size_t j=0;

    if (str[0] == '"') {
        //it is a quoted string, we remove the quotes
        for (size_t i=1; j<size-1 && str[i];) {
            buf[j++] = replaceCR(str[i++]);
        }
        // remove last quote
        if (j>0) buf[j-1] = 0;
    } else {
        for (size_t i=0; j<size-1 && str[i];) {
            buf[j++] = replaceCR(str[i++]);
        }
    }
    buf[j] = 0;

    return tree(buf);
    //----------------------------------------------
}


#line 146 "faustparser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "faustparser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SPLIT = 3,                      /* SPLIT  */
  YYSYMBOL_MIX = 4,                        /* MIX  */
  YYSYMBOL_SEQ = 5,                        /* SEQ  */
  YYSYMBOL_PAR = 6,                        /* PAR  */
  YYSYMBOL_REC = 7,                        /* REC  */
  YYSYMBOL_LT = 8,                         /* LT  */
  YYSYMBOL_LE = 9,                         /* LE  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_GT = 11,                        /* GT  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_NE = 13,                        /* NE  */
  YYSYMBOL_ADD = 14,                       /* ADD  */
  YYSYMBOL_SUB = 15,                       /* SUB  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_MUL = 17,                       /* MUL  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_XOR = 21,                       /* XOR  */
  YYSYMBOL_LSH = 22,                       /* LSH  */
  YYSYMBOL_RSH = 23,                       /* RSH  */
  YYSYMBOL_POWOP = 24,                     /* POWOP  */
  YYSYMBOL_FDELAY = 25,                    /* FDELAY  */
  YYSYMBOL_DELAY1 = 26,                    /* DELAY1  */
  YYSYMBOL_MEM = 27,                       /* MEM  */
  YYSYMBOL_PREFIX = 28,                    /* PREFIX  */
  YYSYMBOL_INTCAST = 29,                   /* INTCAST  */
  YYSYMBOL_FLOATCAST = 30,                 /* FLOATCAST  */
  YYSYMBOL_FFUNCTION = 31,                 /* FFUNCTION  */
  YYSYMBOL_FCONSTANT = 32,                 /* FCONSTANT  */
  YYSYMBOL_FVARIABLE = 33,                 /* FVARIABLE  */
  YYSYMBOL_BUTTON = 34,                    /* BUTTON  */
  YYSYMBOL_CHECKBOX = 35,                  /* CHECKBOX  */
  YYSYMBOL_VSLIDER = 36,                   /* VSLIDER  */
  YYSYMBOL_HSLIDER = 37,                   /* HSLIDER  */
  YYSYMBOL_NENTRY = 38,                    /* NENTRY  */
  YYSYMBOL_VGROUP = 39,                    /* VGROUP  */
  YYSYMBOL_HGROUP = 40,                    /* HGROUP  */
  YYSYMBOL_TGROUP = 41,                    /* TGROUP  */
  YYSYMBOL_HBARGRAPH = 42,                 /* HBARGRAPH  */
  YYSYMBOL_VBARGRAPH = 43,                 /* VBARGRAPH  */
  YYSYMBOL_SOUNDFILE = 44,                 /* SOUNDFILE  */
  YYSYMBOL_ATTACH = 45,                    /* ATTACH  */
  YYSYMBOL_ACOS = 46,                      /* ACOS  */
  YYSYMBOL_ASIN = 47,                      /* ASIN  */
  YYSYMBOL_ATAN = 48,                      /* ATAN  */
  YYSYMBOL_ATAN2 = 49,                     /* ATAN2  */
  YYSYMBOL_COS = 50,                       /* COS  */
  YYSYMBOL_SIN = 51,                       /* SIN  */
  YYSYMBOL_TAN = 52,                       /* TAN  */
  YYSYMBOL_EXP = 53,                       /* EXP  */
  YYSYMBOL_LOG = 54,                       /* LOG  */
  YYSYMBOL_LOG10 = 55,                     /* LOG10  */
  YYSYMBOL_POWFUN = 56,                    /* POWFUN  */
  YYSYMBOL_SQRT = 57,                      /* SQRT  */
  YYSYMBOL_ABS = 58,                       /* ABS  */
  YYSYMBOL_MIN = 59,                       /* MIN  */
  YYSYMBOL_MAX = 60,                       /* MAX  */
  YYSYMBOL_FMOD = 61,                      /* FMOD  */
  YYSYMBOL_REMAINDER = 62,                 /* REMAINDER  */
  YYSYMBOL_FLOOR = 63,                     /* FLOOR  */
  YYSYMBOL_CEIL = 64,                      /* CEIL  */
  YYSYMBOL_RINT = 65,                      /* RINT  */
  YYSYMBOL_RDTBL = 66,                     /* RDTBL  */
  YYSYMBOL_RWTBL = 67,                     /* RWTBL  */
  YYSYMBOL_SELECT2 = 68,                   /* SELECT2  */
  YYSYMBOL_SELECT3 = 69,                   /* SELECT3  */
  YYSYMBOL_INT = 70,                       /* INT  */
  YYSYMBOL_FLOAT = 71,                     /* FLOAT  */
  YYSYMBOL_LAMBDA = 72,                    /* LAMBDA  */
  YYSYMBOL_DOT = 73,                       /* DOT  */
  YYSYMBOL_WIRE = 74,                      /* WIRE  */
  YYSYMBOL_CUT = 75,                       /* CUT  */
  YYSYMBOL_ENDDEF = 76,                    /* ENDDEF  */
  YYSYMBOL_VIRG = 77,                      /* VIRG  */
  YYSYMBOL_LPAR = 78,                      /* LPAR  */
  YYSYMBOL_RPAR = 79,                      /* RPAR  */
  YYSYMBOL_LBRAQ = 80,                     /* LBRAQ  */
  YYSYMBOL_RBRAQ = 81,                     /* RBRAQ  */
  YYSYMBOL_LCROC = 82,                     /* LCROC  */
  YYSYMBOL_RCROC = 83,                     /* RCROC  */
  YYSYMBOL_WITH = 84,                      /* WITH  */
  YYSYMBOL_LETREC = 85,                    /* LETREC  */
  YYSYMBOL_DEF = 86,                       /* DEF  */
  YYSYMBOL_IMPORT = 87,                    /* IMPORT  */
  YYSYMBOL_COMPONENT = 88,                 /* COMPONENT  */
  YYSYMBOL_LIBRARY = 89,                   /* LIBRARY  */
  YYSYMBOL_ENVIRONMENT = 90,               /* ENVIRONMENT  */
  YYSYMBOL_WAVEFORM = 91,                  /* WAVEFORM  */
  YYSYMBOL_ROUTE = 92,                     /* ROUTE  */
  YYSYMBOL_ENABLE = 93,                    /* ENABLE  */
  YYSYMBOL_CONTROL = 94,                   /* CONTROL  */
  YYSYMBOL_IPAR = 95,                      /* IPAR  */
  YYSYMBOL_ISEQ = 96,                      /* ISEQ  */
  YYSYMBOL_ISUM = 97,                      /* ISUM  */
  YYSYMBOL_IPROD = 98,                     /* IPROD  */
  YYSYMBOL_INPUTS = 99,                    /* INPUTS  */
  YYSYMBOL_OUTPUTS = 100,                  /* OUTPUTS  */
  YYSYMBOL_STRING = 101,                   /* STRING  */
  YYSYMBOL_FSTRING = 102,                  /* FSTRING  */
  YYSYMBOL_IDENT = 103,                    /* IDENT  */
  YYSYMBOL_EXTRA = 104,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 105,                  /* DECLARE  */
  YYSYMBOL_CASE = 106,                     /* CASE  */
  YYSYMBOL_ARROW = 107,                    /* ARROW  */
  YYSYMBOL_ASSERTBOUNDS = 108,             /* ASSERTBOUNDS  */
  YYSYMBOL_LOWEST = 109,                   /* LOWEST  */
  YYSYMBOL_HIGHEST = 110,                  /* HIGHEST  */
  YYSYMBOL_FLOATMODE = 111,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 112,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 113,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 114,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 115,                     /* BDOC  */
  YYSYMBOL_EDOC = 116,                     /* EDOC  */
  YYSYMBOL_BEQN = 117,                     /* BEQN  */
  YYSYMBOL_EEQN = 118,                     /* EEQN  */
  YYSYMBOL_BDGM = 119,                     /* BDGM  */
  YYSYMBOL_EDGM = 120,                     /* EDGM  */
  YYSYMBOL_BLST = 121,                     /* BLST  */
  YYSYMBOL_ELST = 122,                     /* ELST  */
  YYSYMBOL_BMETADATA = 123,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 124,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 125,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 126,                   /* NOTICE  */
  YYSYMBOL_LISTING = 127,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 128,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 129,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 130,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 131,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 132,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 133,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 134,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 135,                 /* $accept  */
  YYSYMBOL_program = 136,                  /* program  */
  YYSYMBOL_stmtlist = 137,                 /* stmtlist  */
  YYSYMBOL_deflist = 138,                  /* deflist  */
  YYSYMBOL_variantlist = 139,              /* variantlist  */
  YYSYMBOL_variant = 140,                  /* variant  */
  YYSYMBOL_reclist = 141,                  /* reclist  */
  YYSYMBOL_vallist = 142,                  /* vallist  */
  YYSYMBOL_number = 143,                   /* number  */
  YYSYMBOL_statement = 144,                /* statement  */
  YYSYMBOL_doc = 145,                      /* doc  */
  YYSYMBOL_docelem = 146,                  /* docelem  */
  YYSYMBOL_doctxt = 147,                   /* doctxt  */
  YYSYMBOL_doceqn = 148,                   /* doceqn  */
  YYSYMBOL_docdgm = 149,                   /* docdgm  */
  YYSYMBOL_docntc = 150,                   /* docntc  */
  YYSYMBOL_doclst = 151,                   /* doclst  */
  YYSYMBOL_lstattrlist = 152,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 153,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 154,               /* lstattrval  */
  YYSYMBOL_docmtd = 155,                   /* docmtd  */
  YYSYMBOL_definition = 156,               /* definition  */
  YYSYMBOL_recinition = 157,               /* recinition  */
  YYSYMBOL_defname = 158,                  /* defname  */
  YYSYMBOL_recname = 159,                  /* recname  */
  YYSYMBOL_params = 160,                   /* params  */
  YYSYMBOL_expression = 161,               /* expression  */
  YYSYMBOL_infixexp = 162,                 /* infixexp  */
  YYSYMBOL_primitive = 163,                /* primitive  */
  YYSYMBOL_ident = 164,                    /* ident  */
  YYSYMBOL_name = 165,                     /* name  */
  YYSYMBOL_arglist = 166,                  /* arglist  */
  YYSYMBOL_argument = 167,                 /* argument  */
  YYSYMBOL_string = 168,                   /* string  */
  YYSYMBOL_uqstring = 169,                 /* uqstring  */
  YYSYMBOL_fstring = 170,                  /* fstring  */
  YYSYMBOL_fpar = 171,                     /* fpar  */
  YYSYMBOL_fseq = 172,                     /* fseq  */
  YYSYMBOL_fsum = 173,                     /* fsum  */
  YYSYMBOL_fprod = 174,                    /* fprod  */
  YYSYMBOL_finputs = 175,                  /* finputs  */
  YYSYMBOL_foutputs = 176,                 /* foutputs  */
  YYSYMBOL_ffunction = 177,                /* ffunction  */
  YYSYMBOL_fconst = 178,                   /* fconst  */
  YYSYMBOL_fvariable = 179,                /* fvariable  */
  YYSYMBOL_button = 180,                   /* button  */
  YYSYMBOL_checkbox = 181,                 /* checkbox  */
  YYSYMBOL_vslider = 182,                  /* vslider  */
  YYSYMBOL_hslider = 183,                  /* hslider  */
  YYSYMBOL_nentry = 184,                   /* nentry  */
  YYSYMBOL_vgroup = 185,                   /* vgroup  */
  YYSYMBOL_hgroup = 186,                   /* hgroup  */
  YYSYMBOL_tgroup = 187,                   /* tgroup  */
  YYSYMBOL_vbargraph = 188,                /* vbargraph  */
  YYSYMBOL_hbargraph = 189,                /* hbargraph  */
  YYSYMBOL_soundfile = 190,                /* soundfile  */
  YYSYMBOL_signature = 191,                /* signature  */
  YYSYMBOL_fun = 192,                      /* fun  */
  YYSYMBOL_typelist = 193,                 /* typelist  */
  YYSYMBOL_rulelist = 194,                 /* rulelist  */
  YYSYMBOL_rule = 195,                     /* rule  */
  YYSYMBOL_type = 196                      /* type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   747

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  226
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  486

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   389


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   341,   341,   344,   345,   348,   349,   352,   353,   356,
     357,   358,   359,   363,   364,   371,   372,   375,   376,   377,
     378,   379,   380,   384,   385,   386,   387,   388,   391,   392,
     395,   396,   397,   398,   399,   400,   403,   404,   407,   410,
     413,   416,   419,   420,   423,   424,   425,   428,   429,   432,
     435,   436,   437,   440,   441,   444,   447,   450,   451,   454,
     455,   456,   457,   458,   459,   460,   461,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   474,   475,   476,   478,
     479,   481,   482,   483,   484,   485,   486,   488,   489,   491,
     494,   495,   497,   498,   500,   501,   503,   504,   506,   507,
     509,   510,   512,   513,   514,   515,   516,   517,   519,   520,
     521,   523,   524,   526,   527,   528,   529,   530,   531,   533,
     534,   535,   538,   539,   540,   541,   542,   543,   544,   546,
     547,   548,   549,   550,   551,   553,   554,   555,   557,   558,
     560,   561,   562,   565,   566,   568,   569,   571,   572,   573,
     575,   576,   578,   579,   582,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   604,   605,   606,   607,   609,   610,
     615,   618,   623,   624,   627,   628,   629,   630,   631,   634,
     637,   640,   641,   646,   650,   654,   658,   663,   666,   673,
     677,   680,   685,   688,   691,   694,   697,   700,   703,   706,
     710,   713,   716,   723,   724,   725,   727,   728,   729,   732,
     735,   736,   739,   740,   743,   747,   748
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SPLIT", "MIX", "SEQ",
  "PAR", "REC", "LT", "LE", "EQ", "GT", "GE", "NE", "ADD", "SUB", "OR",
  "MUL", "DIV", "MOD", "AND", "XOR", "LSH", "RSH", "POWOP", "FDELAY",
  "DELAY1", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "FFUNCTION",
  "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER", "HSLIDER",
  "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH", "VBARGRAPH",
  "SOUNDFILE", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN",
  "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS", "MIN", "MAX",
  "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL",
  "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "DOT", "WIRE", "CUT",
  "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC",
  "WITH", "LETREC", "DEF", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT",
  "WAVEFORM", "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM",
  "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA",
  "DECLARE", "CASE", "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST",
  "FLOATMODE", "DOUBLEMODE", "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC",
  "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "variantlist", "variant", "reclist", "vallist",
  "number", "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm",
  "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "expression",
  "infixexp", "primitive", "ident", "name", "arglist", "argument",
  "string", "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod",
  "finputs", "foutputs", "ffunction", "fconst", "fvariable", "button",
  "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
  "vbargraph", "hbargraph", "soundfile", "signature", "fun", "typelist",
  "rulelist", "rule", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389
};
#endif

#define YYPACT_NINF (-429)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -429,    33,    40,  -429,     2,   -21,   -14,  -429,   -11,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,   -18,  -429,  -429,
       8,  -429,   184,   260,   416,   416,  -429,    55,  -429,    11,
      43,  -429,   416,   416,  -429,   -11,  -429,  -429,    19,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
       4,   174,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,    92,   120,   180,   181,
     198,   217,   224,   233,   234,   240,   252,   259,   261,   265,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,   266,  -429,  -429,
     416,   273,   274,    75,   115,   278,  -429,  -429,   280,   284,
     285,   287,   293,   297,   241,  -429,  -429,  -429,   570,  -429,
    -429,    12,   642,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,    42,   570,   237,   264,  -429,    17,    10,
     201,   254,  -429,  -429,  -429,  -429,  -429,  -429,    58,    58,
      58,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,   256,    66,     8,     8,  -429,    83,   416,   256,
     256,   256,   256,   416,   416,   302,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,  -429,   256,   416,  -429,   416,   298,
     416,   416,   416,   416,   416,   416,   416,   416,   416,  -429,
     305,   309,  -429,  -429,  -429,  -429,  -429,   258,   267,   268,
    -429,  -429,  -429,  -429,   384,   289,   -11,   -11,   342,   343,
     483,   486,   487,   494,   495,   496,   497,   511,   512,    24,
    -429,  -429,   441,   442,   456,    96,   121,  -429,  -429,     0,
    -429,   400,   517,   532,   548,   549,    73,   205,   416,   -16,
    -429,   544,   544,   544,   544,   544,   544,   610,   610,   610,
     291,   291,   291,   291,   291,   291,   291,   275,   272,  -429,
      29,   459,   642,   416,   642,   642,   281,  -429,   406,   406,
     228,    93,  -429,  -429,  -429,   413,   418,   422,   112,  -429,
      26,   551,   566,  -429,  -429,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   256,   500,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,    83,  -429,   416,   416,   416,   416,   416,
    -429,  -429,    50,  -429,  -429,  -429,  -429,    25,    47,   493,
       1,   100,   100,   100,  -429,  -429,   569,   289,    14,   112,
     112,   594,   634,   665,   212,   235,   243,   670,   675,    54,
    -429,   526,  -429,   690,   695,   700,   705,   710,   499,  -429,
    -429,  -429,   531,   256,  -429,  -429,   516,  -429,  -429,   476,
     477,   478,    11,    68,  -429,    61,  -429,   537,   539,   416,
     416,   416,  -429,  -429,  -429,   416,   416,  -429,   416,   416,
     416,   416,   416,   416,   416,  -429,  -429,   416,  -429,  -429,
    -429,   540,   289,    81,    58,  -429,  -429,  -429,   715,   720,
     725,   117,   363,   250,   257,   276,   303,   492,   524,   262,
     529,  -429,   543,  -429,    77,  -429,   416,   416,   416,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,   164,
    -429,   730,   735,   740,  -429,    80,   416,   416,   416,  -429,
     536,   541,   546,  -429,  -429,  -429
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   180,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   181,     0,    36,     0,     0,   190,     0,   189,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   113,   114,   117,   115,   116,   118,
     102,   103,   109,   104,   105,   106,   108,   110,   111,   112,
     132,   107,    98,    99,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,    90,    91,     0,    96,    97,
       0,     0,     0,     0,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   188,    89,
     150,     0,   182,   174,   175,   176,   177,   178,   179,   155,
     156,   157,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,    66,     0,     0,    24,     0,     0,
       0,     0,    37,    92,    93,    94,    95,   151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    23,    25,    38,    39,    41,     0,     0,     0,
      43,    49,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   152,     0,     0,     7,     0,     0,    17,    18,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     222,    81,    82,    85,    83,    84,    86,    67,    68,    77,
      69,    70,    71,    76,    78,    79,    80,    72,    73,    75,
       0,     7,   183,     0,   185,   186,   184,   187,    63,    64,
      62,    61,    65,     5,    13,     0,     0,     0,     0,   219,
       0,     0,     0,   202,   203,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,   159,   160,    19,
      20,    21,    22,     0,   161,     0,     0,     0,     0,     0,
     197,   198,     0,   154,   223,    87,    88,     0,     0,     7,
       0,     0,     0,     0,   191,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,     0,    16,     0,     0,     0,     0,     0,     0,     6,
      50,    59,     0,     0,    60,    14,     0,    47,    48,     0,
       0,     0,     0,     0,   216,     0,   220,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,   212,     0,     0,
       0,     0,     0,     0,     0,    54,    56,     0,    44,    45,
      46,     0,     0,     0,     0,   213,   200,   201,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   199,     0,   217,     0,   221,     0,     0,     0,   211,
     210,   153,   162,   193,   194,   195,   196,   224,    53,     0,
     214,     0,     0,     0,   218,     0,     0,     0,     0,   215,
       0,     0,     0,   204,   205,   206
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -429,  -429,   437,   311,  -269,  -429,  -429,  -429,   299,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -111,
    -429,   294,  -429,  -429,  -429,  -429,    -4,   -25,  -429,    15,
     -10,  -153,  -184,   -28,   482,   -99,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,  -429,
    -429,  -429,  -429,  -429,  -429,  -429,  -429,  -336,  -428,  -429,
     365,  -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   301,     4,    14,   360,   269,   270,    15,
      23,    37,    38,    39,    40,    41,    42,   160,   240,   399,
      43,    16,   395,    17,   396,   259,   153,   128,   129,   130,
      22,   131,   132,    30,    27,   366,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   244,   320,   405,   279,
     280,   406
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     154,   156,   392,     5,   271,   454,   343,   154,   154,   245,
     246,   247,    29,   224,   225,   226,   227,   228,   218,    18,
     224,   225,   226,   227,   228,   161,     5,   393,   158,   159,
     334,   403,   357,     3,   302,   218,   304,   305,   306,   307,
      -2,   475,   367,   242,   243,   224,   225,   226,   227,   228,
     224,   225,   226,   227,   228,    19,   218,   220,   221,   222,
      24,   223,   278,   300,    20,   353,   167,   434,    25,   224,
     225,   226,   227,   228,   163,   164,   224,   225,   226,   227,
     228,   344,   394,   434,   432,   154,   434,   242,   243,     6,
     357,   219,    21,   404,   230,   231,   452,   265,   266,   227,
     228,   230,   231,   335,   368,     7,   183,     8,   355,    26,
     242,   243,    28,     9,    10,    11,    12,    13,   229,   157,
     220,   221,   222,   390,   223,   352,   230,   231,     7,   388,
     235,   230,   231,   417,   155,   234,     9,    10,    11,    12,
     435,   371,   372,   373,   162,   261,   433,   377,   378,   379,
     230,   231,   350,   267,   268,   186,   470,   230,   231,   479,
     453,   383,   384,   385,   386,   387,   339,   340,   154,   154,
     168,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   276,
     277,   341,   342,   242,   243,   187,   459,   260,   169,   154,
     154,   154,   154,   154,   272,   273,   274,   275,   224,   225,
     226,   227,   228,   364,   365,   224,   225,   226,   227,   228,
     308,   309,   310,   311,   312,   438,   439,   440,   397,   398,
     299,   441,   442,   226,   227,   228,   321,   322,   224,   225,
     226,   227,   228,   474,   165,   166,   224,   225,   226,   227,
     228,   400,   401,   224,   225,   226,   227,   228,   170,   171,
     224,   225,   226,   227,   228,   224,   225,   226,   227,   228,
     407,   408,   471,   472,   473,   455,   172,     7,   154,   224,
     225,   226,   227,   228,   351,    28,   222,    21,   223,   230,
     231,   412,   480,   481,   482,   173,   230,   231,   214,   358,
     213,   214,   174,   154,   154,   154,   224,   225,   226,   227,
     228,   175,   176,   232,   413,   212,   213,   214,   177,   230,
     231,   195,   414,   236,   374,   375,   376,   230,   231,   461,
     178,   237,   238,   239,   230,   231,   462,   179,   467,   180,
     233,   230,   231,   181,   182,   215,   230,   231,   215,   380,
     216,   184,   185,   216,   217,   463,   188,   217,   189,     7,
     230,   231,   190,   191,   215,   192,   220,   221,   222,   216,
     223,   193,    18,   217,   431,   194,    31,    32,   241,    33,
     278,    34,   464,    35,   303,   313,    36,   230,   231,   314,
     318,   315,   319,   154,   154,   154,   154,   154,   154,   154,
     316,   317,   154,   220,   221,   222,   345,   223,   426,   224,
     225,   226,   227,   228,   443,   444,   445,   446,   447,   448,
     449,   323,   324,   450,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,   460,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   325,
     108,   109,   326,   327,   110,   224,   225,   226,   227,   228,
     328,   329,   330,   331,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   332,   333,     7,
     336,   337,   124,   346,   125,   126,   127,   224,   225,   226,
     227,   228,   224,   225,   226,   227,   228,   338,   347,   220,
     221,   222,   356,   223,   220,   221,   222,   361,   223,   220,
     221,   222,   362,   223,   348,   349,   363,   369,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   465,   370,   381,   391,   402,   230,   231,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   220,   221,   222,
     409,   223,   427,   466,   418,   468,   424,   425,   230,   231,
     428,   429,   430,   230,   231,   483,   436,   215,   437,   451,
     484,   469,   216,   264,   359,   485,   217,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   220,   221,   222,
     410,   223,   382,   215,   354,   220,   221,   222,   216,   223,
       0,   389,   217,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,     0,   262,   263,   220,   221,
     222,   411,   223,   220,   221,   222,   415,   223,   220,   221,
     222,   416,   223,   215,     0,     0,     0,     0,   216,     0,
       0,     0,   217,   220,   221,   222,   419,   223,   220,   221,
     222,   420,   223,   220,   221,   222,   421,   223,   220,   221,
     222,   422,   223,   220,   221,   222,   423,   223,   220,   221,
     222,   456,   223,   220,   221,   222,   457,   223,   220,   221,
     222,   458,   223,   220,   221,   222,   476,   223,   220,   221,
     222,   477,   223,   220,   221,   222,   478,   223
};

static const yytype_int16 yycheck[] =
{
      25,    29,     1,     1,   188,   433,     6,    32,    33,   168,
     169,   170,    22,     3,     4,     5,     6,     7,     6,     4,
       3,     4,     5,     6,     7,    35,     1,    26,    32,    33,
       6,   367,   301,     0,   218,     6,   220,   221,   222,   223,
       0,   469,    16,    29,    30,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,    76,     6,     3,     4,     5,
      78,     7,    78,   216,    78,    81,    51,     6,    86,     3,
       4,     5,     6,     7,    70,    71,     3,     4,     5,     6,
       7,    81,    81,     6,    16,   110,     6,    29,    30,    87,
     359,    79,   103,    79,    84,    85,   432,    14,    15,     6,
       7,    84,    85,    79,    78,   103,   110,   105,    79,   101,
      29,    30,   101,   111,   112,   113,   114,   115,    76,    76,
       3,     4,     5,    76,     7,   278,    84,    85,   103,    79,
     120,    84,    85,    79,    79,   118,   111,   112,   113,   114,
      79,   325,   326,   327,   125,    79,    78,   331,   332,   333,
      84,    85,    79,    70,    71,    80,    79,    84,    85,    79,
      79,   345,   346,   347,   348,   349,    70,    71,   193,   194,
      78,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   193,
     194,    70,    71,    29,    30,    80,    79,   182,    78,   224,
     225,   226,   227,   228,   189,   190,   191,   192,     3,     4,
       5,     6,     7,   101,   102,     3,     4,     5,     6,     7,
     224,   225,   226,   227,   228,   409,   410,   411,   128,   129,
     215,   415,   416,     5,     6,     7,   246,   247,     3,     4,
       5,     6,     7,    79,    70,    71,     3,     4,     5,     6,
       7,   362,   363,     3,     4,     5,     6,     7,    78,    78,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
     369,   370,   456,   457,   458,   434,    78,   103,   303,     3,
       4,     5,     6,     7,    79,   101,     5,   103,     7,    84,
      85,    79,   476,   477,   478,    78,    84,    85,    26,   303,
      25,    26,    78,   328,   329,   330,     3,     4,     5,     6,
       7,    78,    78,    76,    79,    24,    25,    26,    78,    84,
      85,    80,    79,   122,   328,   329,   330,    84,    85,    79,
      78,   130,   131,   132,    84,    85,    79,    78,    76,    78,
      76,    84,    85,    78,    78,    73,    84,    85,    73,   334,
      78,    78,    78,    78,    82,    79,    78,    82,    78,   103,
      84,    85,    78,    78,    73,    78,     3,     4,     5,    78,
       7,    78,   357,    82,   402,    78,   116,   117,   124,   119,
      78,   121,    79,   123,    86,    80,   126,    84,    85,    80,
       6,   133,   103,   418,   419,   420,   421,   422,   423,   424,
     133,   133,   427,     3,     4,     5,     6,     7,   393,     3,
       4,     5,     6,     7,   418,   419,   420,   421,   422,   423,
     424,    79,    79,   427,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    79,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,     6,
      74,    75,     6,     6,    78,     3,     4,     5,     6,     7,
       6,     6,     6,     6,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     6,     6,   103,
      79,    79,   106,     6,   108,   109,   110,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,    81,     6,     3,
       4,     5,    83,     7,     3,     4,     5,   134,     7,     3,
       4,     5,   134,     7,     6,     6,   134,     6,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    79,     6,    73,    81,     6,    84,    85,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,    86,    79,    78,    76,   107,    76,    84,    85,
     134,   134,   134,    84,    85,    79,    79,    73,    79,    79,
      79,    78,    78,   186,   313,    79,    82,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,   343,    73,   279,     3,     4,     5,    78,     7,
      -1,   357,    82,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,    -1,    -1,   184,   185,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    73,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   136,   137,     0,   139,     1,    87,   103,   105,   111,
     112,   113,   114,   115,   140,   144,   156,   158,   164,    76,
      78,   103,   165,   145,    78,    86,   101,   169,   101,   165,
     168,   116,   117,   119,   121,   123,   126,   146,   147,   148,
     149,   150,   151,   155,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    74,    75,
      78,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   106,   108,   109,   110,   162,   163,
     164,   166,   167,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   161,   162,    79,   168,    76,   161,   161,
     152,   165,   125,    70,    71,    70,    71,   164,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,   161,    78,    78,    80,    80,    78,    78,
      78,    78,    78,    78,    78,    80,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    73,    78,    82,     6,    79,
       3,     4,     5,     7,     3,     4,     5,     6,     7,    76,
      84,    85,    76,    76,   118,   120,   122,   130,   131,   132,
     153,   124,    29,    30,   191,   196,   196,   196,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   160,
     164,    79,   169,   169,   137,    14,    15,    70,    71,   142,
     143,   167,   164,   164,   164,   164,   161,   161,    78,   194,
     195,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   164,
     166,   138,   167,    86,   167,   167,   167,   167,   161,   161,
     161,   161,   161,    80,    80,   133,   133,   133,     6,   103,
     192,   165,   165,    79,    79,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,    79,    79,    79,    81,    70,
      71,    70,    71,     6,    81,     6,     6,     6,     6,     6,
      79,    79,   166,    81,   195,    79,    83,   139,   161,   138,
     141,   134,   134,   134,   101,   102,   170,    16,    78,     6,
       6,   167,   167,   167,   161,   161,   161,   167,   167,   167,
     164,    73,   143,   167,   167,   167,   167,   167,    79,   156,
      76,    81,     1,    26,    81,   157,   159,   128,   129,   154,
     154,   154,     6,   192,    79,   193,   196,   170,   170,     6,
       6,     6,    79,    79,    79,     6,     6,    79,    78,     6,
       6,     6,     6,     6,   107,    76,   164,    86,   134,   134,
     134,   168,    16,    78,     6,    79,    79,    79,   167,   167,
     167,   167,   167,   161,   161,   161,   161,   161,   161,   161,
     161,    79,   192,    79,   193,   196,     6,     6,     6,    79,
      79,    79,    79,    79,    79,    79,    79,    76,    76,    78,
      79,   167,   167,   167,    79,   193,     6,     6,     6,    79,
     167,   167,   167,    79,    79,    79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   140,   141,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   145,   145,
     146,   146,   146,   146,   146,   146,   147,   147,   148,   149,
     150,   151,   152,   152,   153,   153,   153,   154,   154,   155,
     156,   156,   156,   157,   157,   158,   159,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     164,   165,   166,   166,   167,   167,   167,   167,   167,   168,
     169,   170,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   191,   191,   191,   191,   191,   192,
     193,   193,   194,   194,   195,   196,   196
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     2,
       2,     2,     2,     5,     4,     5,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     3,
       1,     3,     0,     2,     5,     5,     5,     1,     1,     3,
       7,     4,     2,     4,     2,     1,     2,     1,     3,     5,
       5,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     8,     4,     1,     1,     1,     4,     4,
       4,     4,     8,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     8,     8,     8,     8,     4,     4,     8,
       7,     7,     4,     4,    12,    12,    12,     6,     6,     6,
       8,     8,     6,     5,     7,     9,     4,     6,     8,     1,
       1,     3,     1,     2,     6,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmtlist  */
#line 341 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1745 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 344 "faustparser.y"
                                                          { (yyval.exp) = gGlobal->nil; }
#line 1751 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 345 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1757 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 348 "faustparser.y"
                                                          { (yyval.exp) = gGlobal->nil; }
#line 1763 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 349 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1769 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 352 "faustparser.y"
                                                          { (yyval.numvariant) = 0; }
#line 1775 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 353 "faustparser.y"
                                                                                { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1781 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 356 "faustparser.y"
                                                                                        { (yyval.numvariant) = 1;}
#line 1787 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 357 "faustparser.y"
                                                                                        { (yyval.numvariant) = 2;}
#line 1793 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 358 "faustparser.y"
                                                                                                { (yyval.numvariant) = 4;}
#line 1799 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 359 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1805 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 363 "faustparser.y"
                                                          { (yyval.exp) = gGlobal->nil; }
#line 1811 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 364 "faustparser.y"
                                                        { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1817 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 371 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1823 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 372 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1829 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 375 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1835 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 376 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 1841 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 377 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1847 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 378 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 1853 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 379 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1859 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 380 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1865 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 384 "faustparser.y"
                                                                { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1871 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 385 "faustparser.y"
                                                                                { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1877 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 386 "faustparser.y"
                                                                                { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1883 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 387 "faustparser.y"
                                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 1889 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 388 "faustparser.y"
                                                                                                { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1895 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 391 "faustparser.y"
                                                                                  { (yyval.exp) = gGlobal->nil; }
#line 1901 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 392 "faustparser.y"
                                                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1907 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 395 "faustparser.y"
                                                                                        { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1913 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 396 "faustparser.y"
                                                                                                        { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1919 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 397 "faustparser.y"
                                                                                                        { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1925 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 398 "faustparser.y"
                                                                                                        { (yyval.exp) = docNtc(); }
#line 1931 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 399 "faustparser.y"
                                                                                        { (yyval.exp) = docLst(); }
#line 1937 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 400 "faustparser.y"
                                                                                                        { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1943 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 403 "faustparser.y"
                                                                                  { (yyval.cppstr) = new string(); }
#line 1949 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 404 "faustparser.y"
                                                                                                { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1955 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 407 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1961 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 410 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1967 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 413 "faustparser.y"
                                                                                        { }
#line 1973 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 416 "faustparser.y"
                                                                        { }
#line 1979 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 419 "faustparser.y"
                                                                                          { }
#line 1985 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 420 "faustparser.y"
                                                                                        { }
#line 1991 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 423 "faustparser.y"
                                                                        { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1997 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 424 "faustparser.y"
                                                                                        { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2003 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 425 "faustparser.y"
                                                                                        { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2009 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 428 "faustparser.y"
                                                                                                { (yyval.b) = true; }
#line 2015 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 429 "faustparser.y"
                                                                                                        { (yyval.b) = false; }
#line 2021 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 432 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2027 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 435 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2033 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 436 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2039 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 437 "faustparser.y"
                                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2045 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 440 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2051 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 441 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2057 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 444 "faustparser.y"
                                                                                                { (yyval.exp)=(yyvsp[0].exp); }
#line 2063 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 447 "faustparser.y"
                                                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2069 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 450 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2075 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 451 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2081 "faustparser.cpp"
    break;

  case 59: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 454 "faustparser.y"
                                                                { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2087 "faustparser.cpp"
    break;

  case 60: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 455 "faustparser.y"
                                                        { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2093 "faustparser.cpp"
    break;

  case 61: /* expression: expression PAR expression  */
#line 456 "faustparser.y"
                                                                { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2099 "faustparser.cpp"
    break;

  case 62: /* expression: expression SEQ expression  */
#line 457 "faustparser.y"
                                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2105 "faustparser.cpp"
    break;

  case 63: /* expression: expression SPLIT expression  */
#line 458 "faustparser.y"
                                                                            { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2111 "faustparser.cpp"
    break;

  case 64: /* expression: expression MIX expression  */
#line 459 "faustparser.y"
                                                                                { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2117 "faustparser.cpp"
    break;

  case 65: /* expression: expression REC expression  */
#line 460 "faustparser.y"
                                                                                { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2123 "faustparser.cpp"
    break;

  case 66: /* expression: infixexp  */
#line 461 "faustparser.y"
                                                                                            { (yyval.exp) = (yyvsp[0].exp); }
#line 2129 "faustparser.cpp"
    break;

  case 67: /* infixexp: infixexp ADD infixexp  */
#line 464 "faustparser.y"
                                                        { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2135 "faustparser.cpp"
    break;

  case 68: /* infixexp: infixexp SUB infixexp  */
#line 465 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2141 "faustparser.cpp"
    break;

  case 69: /* infixexp: infixexp MUL infixexp  */
#line 466 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2147 "faustparser.cpp"
    break;

  case 70: /* infixexp: infixexp DIV infixexp  */
#line 467 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2153 "faustparser.cpp"
    break;

  case 71: /* infixexp: infixexp MOD infixexp  */
#line 468 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2159 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp POWOP infixexp  */
#line 469 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2165 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp FDELAY infixexp  */
#line 470 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2171 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp DELAY1  */
#line 471 "faustparser.y"
                                                                        { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2177 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DOT ident  */
#line 472 "faustparser.y"
                                                                { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2183 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp AND infixexp  */
#line 474 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2189 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp OR infixexp  */
#line 475 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2195 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp XOR infixexp  */
#line 476 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2201 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp LSH infixexp  */
#line 478 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2207 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp RSH infixexp  */
#line 479 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2213 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp LT infixexp  */
#line 481 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2219 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp LE infixexp  */
#line 482 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2225 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp GT infixexp  */
#line 483 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2231 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp GE infixexp  */
#line 484 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2237 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp EQ infixexp  */
#line 485 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2243 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp NE infixexp  */
#line 486 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2249 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp LPAR arglist RPAR  */
#line 488 "faustparser.y"
                                                                { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2255 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp LCROC deflist RCROC  */
#line 489 "faustparser.y"
                                                                { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2261 "faustparser.cpp"
    break;

  case 89: /* infixexp: primitive  */
#line 491 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2267 "faustparser.cpp"
    break;

  case 90: /* primitive: INT  */
#line 494 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2273 "faustparser.cpp"
    break;

  case 91: /* primitive: FLOAT  */
#line 495 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 2279 "faustparser.cpp"
    break;

  case 92: /* primitive: ADD INT  */
#line 497 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2285 "faustparser.cpp"
    break;

  case 93: /* primitive: ADD FLOAT  */
#line 498 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 2291 "faustparser.cpp"
    break;

  case 94: /* primitive: SUB INT  */
#line 500 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2297 "faustparser.cpp"
    break;

  case 95: /* primitive: SUB FLOAT  */
#line 501 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2303 "faustparser.cpp"
    break;

  case 96: /* primitive: WIRE  */
#line 503 "faustparser.y"
                                                                                        { (yyval.exp) = boxWire(); }
#line 2309 "faustparser.cpp"
    break;

  case 97: /* primitive: CUT  */
#line 504 "faustparser.y"
                                                                                        { (yyval.exp) = boxCut(); }
#line 2315 "faustparser.cpp"
    break;

  case 98: /* primitive: MEM  */
#line 506 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2321 "faustparser.cpp"
    break;

  case 99: /* primitive: PREFIX  */
#line 507 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2327 "faustparser.cpp"
    break;

  case 100: /* primitive: INTCAST  */
#line 509 "faustparser.y"
                                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2333 "faustparser.cpp"
    break;

  case 101: /* primitive: FLOATCAST  */
#line 510 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2339 "faustparser.cpp"
    break;

  case 102: /* primitive: ADD  */
#line 512 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAdd); }
#line 2345 "faustparser.cpp"
    break;

  case 103: /* primitive: SUB  */
#line 513 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigSub); }
#line 2351 "faustparser.cpp"
    break;

  case 104: /* primitive: MUL  */
#line 514 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigMul); }
#line 2357 "faustparser.cpp"
    break;

  case 105: /* primitive: DIV  */
#line 515 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDiv); }
#line 2363 "faustparser.cpp"
    break;

  case 106: /* primitive: MOD  */
#line 516 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRem); }
#line 2369 "faustparser.cpp"
    break;

  case 107: /* primitive: FDELAY  */
#line 517 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2375 "faustparser.cpp"
    break;

  case 108: /* primitive: AND  */
#line 519 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAND); }
#line 2381 "faustparser.cpp"
    break;

  case 109: /* primitive: OR  */
#line 520 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigOR); }
#line 2387 "faustparser.cpp"
    break;

  case 110: /* primitive: XOR  */
#line 521 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigXOR); }
#line 2393 "faustparser.cpp"
    break;

  case 111: /* primitive: LSH  */
#line 523 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2399 "faustparser.cpp"
    break;

  case 112: /* primitive: RSH  */
#line 524 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2405 "faustparser.cpp"
    break;

  case 113: /* primitive: LT  */
#line 526 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLT); }
#line 2411 "faustparser.cpp"
    break;

  case 114: /* primitive: LE  */
#line 527 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLE); }
#line 2417 "faustparser.cpp"
    break;

  case 115: /* primitive: GT  */
#line 528 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGT); }
#line 2423 "faustparser.cpp"
    break;

  case 116: /* primitive: GE  */
#line 529 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGE); }
#line 2429 "faustparser.cpp"
    break;

  case 117: /* primitive: EQ  */
#line 530 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigEQ); }
#line 2435 "faustparser.cpp"
    break;

  case 118: /* primitive: NE  */
#line 531 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigNE); }
#line 2441 "faustparser.cpp"
    break;

  case 119: /* primitive: ATTACH  */
#line 533 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAttach); }
#line 2447 "faustparser.cpp"
    break;

  case 120: /* primitive: ENABLE  */
#line 534 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2453 "faustparser.cpp"
    break;

  case 121: /* primitive: CONTROL  */
#line 535 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2459 "faustparser.cpp"
    break;

  case 122: /* primitive: ACOS  */
#line 538 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2465 "faustparser.cpp"
    break;

  case 123: /* primitive: ASIN  */
#line 539 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2471 "faustparser.cpp"
    break;

  case 124: /* primitive: ATAN  */
#line 540 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2477 "faustparser.cpp"
    break;

  case 125: /* primitive: ATAN2  */
#line 541 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2483 "faustparser.cpp"
    break;

  case 126: /* primitive: COS  */
#line 542 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2489 "faustparser.cpp"
    break;

  case 127: /* primitive: SIN  */
#line 543 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2495 "faustparser.cpp"
    break;

  case 128: /* primitive: TAN  */
#line 544 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2501 "faustparser.cpp"
    break;

  case 129: /* primitive: EXP  */
#line 546 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2507 "faustparser.cpp"
    break;

  case 130: /* primitive: LOG  */
#line 547 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2513 "faustparser.cpp"
    break;

  case 131: /* primitive: LOG10  */
#line 548 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2519 "faustparser.cpp"
    break;

  case 132: /* primitive: POWOP  */
#line 549 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2525 "faustparser.cpp"
    break;

  case 133: /* primitive: POWFUN  */
#line 550 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2531 "faustparser.cpp"
    break;

  case 134: /* primitive: SQRT  */
#line 551 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2537 "faustparser.cpp"
    break;

  case 135: /* primitive: ABS  */
#line 553 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2543 "faustparser.cpp"
    break;

  case 136: /* primitive: MIN  */
#line 554 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2549 "faustparser.cpp"
    break;

  case 137: /* primitive: MAX  */
#line 555 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2555 "faustparser.cpp"
    break;

  case 138: /* primitive: FMOD  */
#line 557 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2561 "faustparser.cpp"
    break;

  case 139: /* primitive: REMAINDER  */
#line 558 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2567 "faustparser.cpp"
    break;

  case 140: /* primitive: FLOOR  */
#line 560 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2573 "faustparser.cpp"
    break;

  case 141: /* primitive: CEIL  */
#line 561 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2579 "faustparser.cpp"
    break;

  case 142: /* primitive: RINT  */
#line 562 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2585 "faustparser.cpp"
    break;

  case 143: /* primitive: RDTBL  */
#line 565 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2591 "faustparser.cpp"
    break;

  case 144: /* primitive: RWTBL  */
#line 566 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2597 "faustparser.cpp"
    break;

  case 145: /* primitive: SELECT2  */
#line 568 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2603 "faustparser.cpp"
    break;

  case 146: /* primitive: SELECT3  */
#line 569 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2609 "faustparser.cpp"
    break;

  case 147: /* primitive: ASSERTBOUNDS  */
#line 571 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim3(sigAssertBounds);}
#line 2615 "faustparser.cpp"
    break;

  case 148: /* primitive: LOWEST  */
#line 572 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigLowest);}
#line 2621 "faustparser.cpp"
    break;

  case 149: /* primitive: HIGHEST  */
#line 573 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigHighest);}
#line 2627 "faustparser.cpp"
    break;

  case 150: /* primitive: ident  */
#line 575 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2633 "faustparser.cpp"
    break;

  case 151: /* primitive: SUB ident  */
#line 576 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2639 "faustparser.cpp"
    break;

  case 152: /* primitive: LPAR expression RPAR  */
#line 578 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2645 "faustparser.cpp"
    break;

  case 153: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 580 "faustparser.y"
                                                                                                { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2651 "faustparser.cpp"
    break;

  case 154: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 582 "faustparser.y"
                                                                        { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2657 "faustparser.cpp"
    break;

  case 155: /* primitive: ffunction  */
#line 584 "faustparser.y"
                                                                                        { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2663 "faustparser.cpp"
    break;

  case 156: /* primitive: fconst  */
#line 585 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2669 "faustparser.cpp"
    break;

  case 157: /* primitive: fvariable  */
#line 586 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2675 "faustparser.cpp"
    break;

  case 158: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 587 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2681 "faustparser.cpp"
    break;

  case 159: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 588 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2687 "faustparser.cpp"
    break;

  case 160: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 589 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2693 "faustparser.cpp"
    break;

  case 161: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 590 "faustparser.y"
                                                { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2699 "faustparser.cpp"
    break;

  case 162: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 591 "faustparser.y"
                                                                                                { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2705 "faustparser.cpp"
    break;

  case 163: /* primitive: button  */
#line 592 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2711 "faustparser.cpp"
    break;

  case 164: /* primitive: checkbox  */
#line 593 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2717 "faustparser.cpp"
    break;

  case 165: /* primitive: vslider  */
#line 594 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2723 "faustparser.cpp"
    break;

  case 166: /* primitive: hslider  */
#line 595 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2729 "faustparser.cpp"
    break;

  case 167: /* primitive: nentry  */
#line 596 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2735 "faustparser.cpp"
    break;

  case 168: /* primitive: vgroup  */
#line 597 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2741 "faustparser.cpp"
    break;

  case 169: /* primitive: hgroup  */
#line 598 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2747 "faustparser.cpp"
    break;

  case 170: /* primitive: tgroup  */
#line 599 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2753 "faustparser.cpp"
    break;

  case 171: /* primitive: vbargraph  */
#line 600 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2759 "faustparser.cpp"
    break;

  case 172: /* primitive: hbargraph  */
#line 601 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2765 "faustparser.cpp"
    break;

  case 173: /* primitive: soundfile  */
#line 602 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2771 "faustparser.cpp"
    break;

  case 174: /* primitive: fpar  */
#line 604 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2777 "faustparser.cpp"
    break;

  case 175: /* primitive: fseq  */
#line 605 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2783 "faustparser.cpp"
    break;

  case 176: /* primitive: fsum  */
#line 606 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2789 "faustparser.cpp"
    break;

  case 177: /* primitive: fprod  */
#line 607 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2795 "faustparser.cpp"
    break;

  case 178: /* primitive: finputs  */
#line 609 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2801 "faustparser.cpp"
    break;

  case 179: /* primitive: foutputs  */
#line 610 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2807 "faustparser.cpp"
    break;

  case 180: /* ident: IDENT  */
#line 615 "faustparser.y"
                                                                                { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2813 "faustparser.cpp"
    break;

  case 181: /* name: IDENT  */
#line 618 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2819 "faustparser.cpp"
    break;

  case 182: /* arglist: argument  */
#line 623 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2825 "faustparser.cpp"
    break;

  case 183: /* arglist: arglist PAR argument  */
#line 624 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2831 "faustparser.cpp"
    break;

  case 184: /* argument: argument SEQ argument  */
#line 627 "faustparser.y"
                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2837 "faustparser.cpp"
    break;

  case 185: /* argument: argument SPLIT argument  */
#line 628 "faustparser.y"
                                                                        { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2843 "faustparser.cpp"
    break;

  case 186: /* argument: argument MIX argument  */
#line 629 "faustparser.y"
                                                                        { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2849 "faustparser.cpp"
    break;

  case 187: /* argument: argument REC argument  */
#line 630 "faustparser.y"
                                                                        { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2855 "faustparser.cpp"
    break;

  case 188: /* argument: infixexp  */
#line 631 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2861 "faustparser.cpp"
    break;

  case 189: /* string: STRING  */
#line 634 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2867 "faustparser.cpp"
    break;

  case 190: /* uqstring: STRING  */
#line 637 "faustparser.y"
                                                                                { (yyval.exp) = unquote(yytext); }
#line 2873 "faustparser.cpp"
    break;

  case 191: /* fstring: STRING  */
#line 640 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2879 "faustparser.cpp"
    break;

  case 192: /* fstring: FSTRING  */
#line 641 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2885 "faustparser.cpp"
    break;

  case 193: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 647 "faustparser.y"
                                                                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2891 "faustparser.cpp"
    break;

  case 194: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 651 "faustparser.y"
                                                                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2897 "faustparser.cpp"
    break;

  case 195: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 655 "faustparser.y"
                                                                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2903 "faustparser.cpp"
    break;

  case 196: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 659 "faustparser.y"
                                                                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2909 "faustparser.cpp"
    break;

  case 197: /* finputs: INPUTS LPAR expression RPAR  */
#line 663 "faustparser.y"
                                                      { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2915 "faustparser.cpp"
    break;

  case 198: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 666 "faustparser.y"
                                                       { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2921 "faustparser.cpp"
    break;

  case 199: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 674 "faustparser.y"
                                                                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2927 "faustparser.cpp"
    break;

  case 200: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 678 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2933 "faustparser.cpp"
    break;

  case 201: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 681 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2939 "faustparser.cpp"
    break;

  case 202: /* button: BUTTON LPAR uqstring RPAR  */
#line 685 "faustparser.y"
                                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2945 "faustparser.cpp"
    break;

  case 203: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 688 "faustparser.y"
                                                                { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2951 "faustparser.cpp"
    break;

  case 204: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 692 "faustparser.y"
                                                                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2957 "faustparser.cpp"
    break;

  case 205: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 695 "faustparser.y"
                                                                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2963 "faustparser.cpp"
    break;

  case 206: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 698 "faustparser.y"
                                                                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2969 "faustparser.cpp"
    break;

  case 207: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 701 "faustparser.y"
                                                                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2975 "faustparser.cpp"
    break;

  case 208: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 704 "faustparser.y"
                                                                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2981 "faustparser.cpp"
    break;

  case 209: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 707 "faustparser.y"
                                                                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2987 "faustparser.cpp"
    break;

  case 210: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 711 "faustparser.y"
                                                                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2993 "faustparser.cpp"
    break;

  case 211: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 714 "faustparser.y"
                                                                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2999 "faustparser.cpp"
    break;

  case 212: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 717 "faustparser.y"
                                                                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3005 "faustparser.cpp"
    break;

  case 213: /* signature: type fun LPAR typelist RPAR  */
#line 723 "faustparser.y"
                                                                    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3011 "faustparser.cpp"
    break;

  case 214: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 724 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3017 "faustparser.cpp"
    break;

  case 215: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 725 "faustparser.y"
                                                                { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3023 "faustparser.cpp"
    break;

  case 216: /* signature: type fun LPAR RPAR  */
#line 727 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3029 "faustparser.cpp"
    break;

  case 217: /* signature: type fun OR fun LPAR RPAR  */
#line 728 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3035 "faustparser.cpp"
    break;

  case 218: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 729 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3041 "faustparser.cpp"
    break;

  case 219: /* fun: IDENT  */
#line 732 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 3047 "faustparser.cpp"
    break;

  case 220: /* typelist: type  */
#line 735 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3053 "faustparser.cpp"
    break;

  case 221: /* typelist: typelist PAR type  */
#line 736 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3059 "faustparser.cpp"
    break;

  case 222: /* rulelist: rule  */
#line 739 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3065 "faustparser.cpp"
    break;

  case 223: /* rulelist: rulelist rule  */
#line 740 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3071 "faustparser.cpp"
    break;

  case 224: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 744 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3077 "faustparser.cpp"
    break;

  case 225: /* type: INTCAST  */
#line 747 "faustparser.y"
                                                        { (yyval.exp) = tree(0); }
#line 3083 "faustparser.cpp"
    break;

  case 226: /* type: FLOATCAST  */
#line 748 "faustparser.y"
                                                                                        { (yyval.exp) = tree(1); }
#line 3089 "faustparser.cpp"
    break;


#line 3093 "faustparser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 751 "faustparser.y"


