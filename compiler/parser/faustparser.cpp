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
  YYSYMBOL_APPL = 27,                      /* APPL  */
  YYSYMBOL_MEM = 28,                       /* MEM  */
  YYSYMBOL_PREFIX = 29,                    /* PREFIX  */
  YYSYMBOL_INTCAST = 30,                   /* INTCAST  */
  YYSYMBOL_FLOATCAST = 31,                 /* FLOATCAST  */
  YYSYMBOL_FFUNCTION = 32,                 /* FFUNCTION  */
  YYSYMBOL_FCONSTANT = 33,                 /* FCONSTANT  */
  YYSYMBOL_FVARIABLE = 34,                 /* FVARIABLE  */
  YYSYMBOL_BUTTON = 35,                    /* BUTTON  */
  YYSYMBOL_CHECKBOX = 36,                  /* CHECKBOX  */
  YYSYMBOL_VSLIDER = 37,                   /* VSLIDER  */
  YYSYMBOL_HSLIDER = 38,                   /* HSLIDER  */
  YYSYMBOL_NENTRY = 39,                    /* NENTRY  */
  YYSYMBOL_VGROUP = 40,                    /* VGROUP  */
  YYSYMBOL_HGROUP = 41,                    /* HGROUP  */
  YYSYMBOL_TGROUP = 42,                    /* TGROUP  */
  YYSYMBOL_HBARGRAPH = 43,                 /* HBARGRAPH  */
  YYSYMBOL_VBARGRAPH = 44,                 /* VBARGRAPH  */
  YYSYMBOL_SOUNDFILE = 45,                 /* SOUNDFILE  */
  YYSYMBOL_ATTACH = 46,                    /* ATTACH  */
  YYSYMBOL_ACOS = 47,                      /* ACOS  */
  YYSYMBOL_ASIN = 48,                      /* ASIN  */
  YYSYMBOL_ATAN = 49,                      /* ATAN  */
  YYSYMBOL_ATAN2 = 50,                     /* ATAN2  */
  YYSYMBOL_COS = 51,                       /* COS  */
  YYSYMBOL_SIN = 52,                       /* SIN  */
  YYSYMBOL_TAN = 53,                       /* TAN  */
  YYSYMBOL_EXP = 54,                       /* EXP  */
  YYSYMBOL_LOG = 55,                       /* LOG  */
  YYSYMBOL_LOG10 = 56,                     /* LOG10  */
  YYSYMBOL_POWFUN = 57,                    /* POWFUN  */
  YYSYMBOL_SQRT = 58,                      /* SQRT  */
  YYSYMBOL_ABS = 59,                       /* ABS  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_MAX = 61,                       /* MAX  */
  YYSYMBOL_FMOD = 62,                      /* FMOD  */
  YYSYMBOL_REMAINDER = 63,                 /* REMAINDER  */
  YYSYMBOL_FLOOR = 64,                     /* FLOOR  */
  YYSYMBOL_CEIL = 65,                      /* CEIL  */
  YYSYMBOL_RINT = 66,                      /* RINT  */
  YYSYMBOL_RDTBL = 67,                     /* RDTBL  */
  YYSYMBOL_RWTBL = 68,                     /* RWTBL  */
  YYSYMBOL_SELECT2 = 69,                   /* SELECT2  */
  YYSYMBOL_SELECT3 = 70,                   /* SELECT3  */
  YYSYMBOL_INT = 71,                       /* INT  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_LAMBDA = 73,                    /* LAMBDA  */
  YYSYMBOL_DOT = 74,                       /* DOT  */
  YYSYMBOL_WIRE = 75,                      /* WIRE  */
  YYSYMBOL_CUT = 76,                       /* CUT  */
  YYSYMBOL_ENDDEF = 77,                    /* ENDDEF  */
  YYSYMBOL_VIRG = 78,                      /* VIRG  */
  YYSYMBOL_LPAR = 79,                      /* LPAR  */
  YYSYMBOL_RPAR = 80,                      /* RPAR  */
  YYSYMBOL_LBRAQ = 81,                     /* LBRAQ  */
  YYSYMBOL_RBRAQ = 82,                     /* RBRAQ  */
  YYSYMBOL_LCROC = 83,                     /* LCROC  */
  YYSYMBOL_RCROC = 84,                     /* RCROC  */
  YYSYMBOL_WITH = 85,                      /* WITH  */
  YYSYMBOL_LETREC = 86,                    /* LETREC  */
  YYSYMBOL_DEF = 87,                       /* DEF  */
  YYSYMBOL_IMPORT = 88,                    /* IMPORT  */
  YYSYMBOL_COMPONENT = 89,                 /* COMPONENT  */
  YYSYMBOL_LIBRARY = 90,                   /* LIBRARY  */
  YYSYMBOL_ENVIRONMENT = 91,               /* ENVIRONMENT  */
  YYSYMBOL_WAVEFORM = 92,                  /* WAVEFORM  */
  YYSYMBOL_ROUTE = 93,                     /* ROUTE  */
  YYSYMBOL_ENABLE = 94,                    /* ENABLE  */
  YYSYMBOL_CONTROL = 95,                   /* CONTROL  */
  YYSYMBOL_IPAR = 96,                      /* IPAR  */
  YYSYMBOL_ISEQ = 97,                      /* ISEQ  */
  YYSYMBOL_ISUM = 98,                      /* ISUM  */
  YYSYMBOL_IPROD = 99,                     /* IPROD  */
  YYSYMBOL_INPUTS = 100,                   /* INPUTS  */
  YYSYMBOL_OUTPUTS = 101,                  /* OUTPUTS  */
  YYSYMBOL_STRING = 102,                   /* STRING  */
  YYSYMBOL_FSTRING = 103,                  /* FSTRING  */
  YYSYMBOL_IDENT = 104,                    /* IDENT  */
  YYSYMBOL_EXTRA = 105,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 106,                  /* DECLARE  */
  YYSYMBOL_CASE = 107,                     /* CASE  */
  YYSYMBOL_ARROW = 108,                    /* ARROW  */
  YYSYMBOL_ISLT = 109,                     /* ISLT  */
  YYSYMBOL_ISGT = 110,                     /* ISGT  */
  YYSYMBOL_UPB = 111,                      /* UPB  */
  YYSYMBOL_LOB = 112,                      /* LOB  */
  YYSYMBOL_FLOATMODE = 113,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 114,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 115,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 116,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 117,                     /* BDOC  */
  YYSYMBOL_EDOC = 118,                     /* EDOC  */
  YYSYMBOL_BEQN = 119,                     /* BEQN  */
  YYSYMBOL_EEQN = 120,                     /* EEQN  */
  YYSYMBOL_BDGM = 121,                     /* BDGM  */
  YYSYMBOL_EDGM = 122,                     /* EDGM  */
  YYSYMBOL_BLST = 123,                     /* BLST  */
  YYSYMBOL_ELST = 124,                     /* ELST  */
  YYSYMBOL_BMETADATA = 125,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 126,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 127,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 128,                   /* NOTICE  */
  YYSYMBOL_LISTING = 129,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 130,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 131,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 132,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 133,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 134,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 135,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 136,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 137,                 /* $accept  */
  YYSYMBOL_program = 138,                  /* program  */
  YYSYMBOL_stmtlist = 139,                 /* stmtlist  */
  YYSYMBOL_deflist = 140,                  /* deflist  */
  YYSYMBOL_variantlist = 141,              /* variantlist  */
  YYSYMBOL_variant = 142,                  /* variant  */
  YYSYMBOL_reclist = 143,                  /* reclist  */
  YYSYMBOL_vallist = 144,                  /* vallist  */
  YYSYMBOL_number = 145,                   /* number  */
  YYSYMBOL_statement = 146,                /* statement  */
  YYSYMBOL_doc = 147,                      /* doc  */
  YYSYMBOL_docelem = 148,                  /* docelem  */
  YYSYMBOL_doctxt = 149,                   /* doctxt  */
  YYSYMBOL_doceqn = 150,                   /* doceqn  */
  YYSYMBOL_docdgm = 151,                   /* docdgm  */
  YYSYMBOL_docntc = 152,                   /* docntc  */
  YYSYMBOL_doclst = 153,                   /* doclst  */
  YYSYMBOL_lstattrlist = 154,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 155,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 156,               /* lstattrval  */
  YYSYMBOL_docmtd = 157,                   /* docmtd  */
  YYSYMBOL_definition = 158,               /* definition  */
  YYSYMBOL_recinition = 159,               /* recinition  */
  YYSYMBOL_defname = 160,                  /* defname  */
  YYSYMBOL_recname = 161,                  /* recname  */
  YYSYMBOL_params = 162,                   /* params  */
  YYSYMBOL_expression = 163,               /* expression  */
  YYSYMBOL_infixexp = 164,                 /* infixexp  */
  YYSYMBOL_primitive = 165,                /* primitive  */
  YYSYMBOL_ident = 166,                    /* ident  */
  YYSYMBOL_name = 167,                     /* name  */
  YYSYMBOL_arglist = 168,                  /* arglist  */
  YYSYMBOL_argument = 169,                 /* argument  */
  YYSYMBOL_string = 170,                   /* string  */
  YYSYMBOL_uqstring = 171,                 /* uqstring  */
  YYSYMBOL_fstring = 172,                  /* fstring  */
  YYSYMBOL_fpar = 173,                     /* fpar  */
  YYSYMBOL_fseq = 174,                     /* fseq  */
  YYSYMBOL_fsum = 175,                     /* fsum  */
  YYSYMBOL_fprod = 176,                    /* fprod  */
  YYSYMBOL_finputs = 177,                  /* finputs  */
  YYSYMBOL_foutputs = 178,                 /* foutputs  */
  YYSYMBOL_ffunction = 179,                /* ffunction  */
  YYSYMBOL_fconst = 180,                   /* fconst  */
  YYSYMBOL_fvariable = 181,                /* fvariable  */
  YYSYMBOL_button = 182,                   /* button  */
  YYSYMBOL_checkbox = 183,                 /* checkbox  */
  YYSYMBOL_vslider = 184,                  /* vslider  */
  YYSYMBOL_hslider = 185,                  /* hslider  */
  YYSYMBOL_nentry = 186,                   /* nentry  */
  YYSYMBOL_vgroup = 187,                   /* vgroup  */
  YYSYMBOL_hgroup = 188,                   /* hgroup  */
  YYSYMBOL_tgroup = 189,                   /* tgroup  */
  YYSYMBOL_vbargraph = 190,                /* vbargraph  */
  YYSYMBOL_hbargraph = 191,                /* hbargraph  */
  YYSYMBOL_soundfile = 192,                /* soundfile  */
  YYSYMBOL_signature = 193,                /* signature  */
  YYSYMBOL_fun = 194,                      /* fun  */
  YYSYMBOL_typelist = 195,                 /* typelist  */
  YYSYMBOL_rulelist = 196,                 /* rulelist  */
  YYSYMBOL_rule = 197,                     /* rule  */
  YYSYMBOL_type = 198                      /* type  */
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
#define YYLAST   748

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  137
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  223
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  483

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   391


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
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   340,   340,   343,   344,   347,   348,   351,   352,   355,
     356,   357,   358,   362,   363,   370,   371,   374,   375,   376,
     377,   378,   379,   383,   384,   385,   386,   387,   390,   391,
     394,   395,   396,   397,   398,   399,   402,   403,   406,   409,
     412,   415,   418,   419,   422,   423,   424,   427,   428,   431,
     434,   435,   436,   439,   440,   443,   446,   449,   450,   453,
     454,   455,   456,   457,   458,   459,   460,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   473,   474,   475,   477,
     478,   480,   481,   482,   483,   484,   485,   487,   488,   490,
     493,   494,   496,   497,   499,   500,   502,   503,   505,   506,
     508,   509,   511,   512,   513,   514,   515,   516,   518,   519,
     520,   522,   523,   525,   526,   527,   528,   529,   530,   532,
     533,   534,   537,   538,   539,   540,   541,   542,   543,   545,
     546,   547,   548,   549,   550,   552,   553,   554,   556,   557,
     559,   560,   561,   564,   565,   567,   568,   570,   571,   573,
     574,   577,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     597,   599,   600,   601,   602,   604,   605,   610,   613,   618,
     619,   622,   623,   624,   625,   626,   629,   632,   635,   636,
     641,   645,   649,   653,   658,   661,   668,   672,   675,   680,
     683,   686,   689,   692,   695,   698,   701,   705,   708,   711,
     718,   719,   720,   722,   723,   724,   727,   730,   731,   734,
     735,   738,   742,   743
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
  "DELAY1", "APPL", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "FFUNCTION",
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
  "DECLARE", "CASE", "ARROW", "ISLT", "ISGT", "UPB", "LOB", "FLOATMODE",
  "DOUBLEMODE", "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
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
     385,   386,   387,   388,   389,   390,   391
};
#endif

#define YYPACT_NINF (-377)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -377,    43,    65,  -377,    19,    12,   -30,  -377,    34,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,    30,  -377,  -377,
      22,  -377,   -20,   230,   413,   413,  -377,    68,  -377,    56,
      87,  -377,   413,   413,  -377,    34,  -377,  -377,    40,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
     -13,   169,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,   113,   116,   143,   147,
     149,   154,   163,   195,   253,   254,   255,   256,   260,   261,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,   262,  -377,  -377,
     413,   263,   266,   212,   269,   275,  -377,  -377,   281,   282,
     286,   287,   288,   291,   301,   569,  -377,  -377,     3,   374,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
      41,   569,   190,   306,  -377,    35,     8,   144,   271,  -377,
    -377,  -377,  -377,  -377,  -377,   222,   222,   222,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,   280,
      57,    22,    22,  -377,   139,   413,   280,   280,   280,   280,
     413,   413,   308,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,  -377,   280,   413,  -377,   413,   302,   413,   413,   413,
     413,   413,   413,   413,   413,   413,  -377,   317,   337,  -377,
    -377,  -377,  -377,  -377,   284,   304,   305,  -377,  -377,  -377,
    -377,   382,   383,    34,    34,   410,   411,   492,   493,   494,
     495,   509,   510,   512,   513,   530,    11,  -377,  -377,   457,
     461,   464,   188,   214,  -377,  -377,    10,  -377,   369,   547,
     548,   549,   550,    64,    71,   413,    37,  -377,   543,   543,
     543,   543,   543,   543,   610,   610,   610,   273,   273,   273,
     273,   273,   273,   273,    31,   285,  -377,    16,   467,   374,
     413,   374,   374,    92,  -377,   397,   397,   303,   307,  -377,
    -377,  -377,   435,   436,   437,   213,  -377,     2,   568,   590,
    -377,  -377,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   280,   525,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
     139,  -377,   413,   413,   413,   413,   413,  -377,  -377,    18,
    -377,  -377,  -377,  -377,   130,   202,   515,     5,   189,   189,
     189,  -377,  -377,   595,   383,    42,   213,   213,   403,   634,
     665,   209,   232,   244,   670,   675,    48,  -377,   527,  -377,
     691,   696,   701,   706,   711,   499,  -377,  -377,  -377,   533,
     280,  -377,  -377,   524,  -377,  -377,   466,   476,   480,    56,
       9,  -377,    20,  -377,   538,   539,   413,   413,   413,  -377,
    -377,  -377,   413,   413,  -377,   413,   413,   413,   413,   413,
     413,   413,  -377,  -377,   413,  -377,  -377,  -377,   541,   383,
      49,   222,  -377,  -377,  -377,   716,   721,   726,   108,   186,
     251,   258,   277,   300,   490,   518,   523,   528,  -377,   544,
    -377,    21,  -377,   413,   413,   413,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,    72,  -377,   731,   736,
     741,  -377,    24,   413,   413,   413,  -377,   535,   540,   545,
    -377,  -377,  -377
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   177,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   178,     0,    36,     0,     0,   187,     0,   186,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   113,   114,   117,   115,   116,   118,
     102,   103,   109,   104,   105,   106,   108,   110,   111,   112,
     132,   107,    98,    99,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,    90,    91,     0,    96,    97,
       0,     0,     0,     0,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,     0,   185,    89,   147,     0,   179,
     171,   172,   173,   174,   175,   176,   152,   153,   154,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,    66,     0,     0,    24,     0,     0,     0,     0,    37,
      92,    93,    94,    95,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,     0,    23,
      25,    38,    39,    41,     0,     0,     0,    43,    49,   222,
     223,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,   149,     0,
       0,     7,     0,     0,    17,    18,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   219,    81,    82,
      85,    83,    84,    86,    67,    68,    77,    69,    70,    71,
      76,    78,    79,    80,    72,    73,    75,     0,     7,   180,
       0,   182,   183,   181,   184,    63,    64,    62,    61,    65,
       5,    13,     0,     0,     0,     0,   216,     0,     0,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,    19,    20,    21,    22,
       0,   158,     0,     0,     0,     0,     0,   194,   195,     0,
     151,   220,    87,    88,     0,     0,     7,     0,     0,     0,
       0,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,     0,    16,
       0,     0,     0,     0,     0,     0,     6,    50,    59,     0,
       0,    60,    14,     0,    47,    48,     0,     0,     0,     0,
       0,   213,     0,   217,     0,     0,     0,     0,     0,   204,
     205,   206,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,    54,    56,     0,    44,    45,    46,     0,     0,
       0,     0,   210,   197,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   196,     0,
     214,     0,   218,     0,     0,     0,   208,   207,   150,   159,
     190,   191,   192,   193,   221,    53,     0,   211,     0,     0,
       0,   215,     0,     0,     0,     0,   212,     0,     0,     0,
     201,   202,   203
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -377,  -377,   441,   332,  -248,  -377,  -377,  -377,   309,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,   -34,
    -377,   290,  -377,  -377,  -377,  -377,    -4,   -25,  -377,    15,
     -12,  -180,  -183,   -28,   485,   -39,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -343,  -376,  -377,
     370,  -162
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   298,     4,    14,   357,   266,   267,    15,
      23,    37,    38,    39,    40,    41,    42,   157,   237,   396,
      43,    16,   392,    17,   393,   256,   150,   125,   126,   127,
      22,   128,   129,    30,    27,   363,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   241,   317,   402,   276,
     277,   403
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     151,   153,   268,   242,   243,   244,   389,   151,   151,   215,
      29,   221,   222,   223,   224,   225,   340,   331,   364,    18,
       5,   400,   215,   158,   215,   429,   431,   431,   155,   156,
     431,   390,   299,   297,   301,   302,   303,   304,   221,   222,
     223,   224,   225,     3,   221,   222,   223,   224,   225,    20,
     354,   217,   218,   219,   451,   220,   210,   211,   160,   161,
     221,   222,   223,   224,   225,    -2,   164,   221,   222,   223,
     224,   225,   239,   240,   221,   222,   223,   224,   225,   239,
     240,   365,    28,   216,    21,   151,   449,   391,   430,    19,
     472,   332,   341,   227,   228,   349,   352,   219,   385,   220,
     432,   467,   239,   240,   476,   212,   180,     6,   354,    24,
     213,   217,   218,   219,   214,   220,   275,    25,   226,   350,
     227,   228,   401,     7,    26,     8,   227,   228,   414,   450,
     232,     5,     9,    10,    11,    12,    13,   258,    21,   368,
     369,   370,   227,   228,   347,   374,   375,   376,   152,   227,
     228,   348,   471,   262,   263,   231,   227,   228,    28,   380,
     381,   382,   383,   384,   154,   151,   151,   159,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   273,   274,   456,   217,
     218,   219,   165,   220,   257,   166,   151,   151,   151,   151,
     151,   269,   270,   271,   272,   221,   222,   223,   224,   225,
     264,   265,   221,   222,   223,   224,   225,   305,   306,   307,
     308,   309,   167,   435,   436,   437,   168,   296,   169,   438,
     439,   318,   319,   170,     7,   221,   222,   223,   224,   225,
     162,   163,   171,     9,    10,    11,    12,   221,   222,   223,
     224,   225,   239,   240,   221,   222,   223,   224,   225,   336,
     337,   221,   222,   223,   224,   225,   457,   229,   233,   452,
     468,   469,   470,     7,   172,   151,   234,   235,   236,   387,
     221,   222,   223,   224,   225,   338,   339,   227,   228,   409,
     477,   478,   479,   183,   227,   228,   355,   209,   210,   211,
     151,   151,   151,   221,   222,   223,   224,   225,   223,   224,
     225,   211,   410,   224,   225,   361,   362,   227,   228,   394,
     395,   371,   372,   373,   411,   397,   398,   404,   405,   227,
     228,   458,   173,   174,   175,   176,   227,   228,   459,   177,
     178,   179,   181,   227,   228,   182,   377,   212,    31,    32,
     184,    33,   213,    34,   185,    35,   214,   460,    36,   212,
     186,   187,   227,   228,   213,   188,   189,   190,   214,    18,
     191,   428,   217,   218,   219,   342,   220,   217,   218,   219,
     461,   220,   192,   230,     7,   227,   228,   275,   315,   300,
     151,   151,   151,   151,   151,   151,   151,   238,   310,   151,
     221,   222,   223,   224,   225,   423,   217,   218,   219,   406,
     220,   440,   441,   442,   443,   444,   445,   446,   311,   312,
     447,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   313,
     314,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   316,   108,   109,
     320,   321,   110,   221,   222,   223,   224,   225,   322,   323,
     324,   325,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   326,   327,     7,   328,   329,
     124,   221,   222,   223,   224,   225,   221,   222,   223,   224,
     225,   221,   222,   223,   224,   225,   330,   333,   217,   218,
     219,   334,   220,   217,   218,   219,   335,   220,   217,   218,
     219,   353,   220,   343,   344,   345,   346,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     462,   358,   359,   360,   366,   227,   228,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   367,   388,   463,   378,
     464,   399,   425,   227,   228,   465,   415,   421,   227,   228,
     422,   424,   426,   227,   228,   480,   427,   212,   433,   434,
     481,   448,   213,   466,   261,   482,   214,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   217,   218,   219,
     407,   220,   356,   212,   386,     0,   351,     0,   213,   379,
       0,     0,   214,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,     0,     0,   259,   260,   217,   218,
     219,   408,   220,   217,   218,   219,   412,   220,   217,   218,
     219,   413,   220,     0,   212,     0,     0,     0,     0,   213,
       0,     0,     0,   214,   217,   218,   219,   416,   220,   217,
     218,   219,   417,   220,   217,   218,   219,   418,   220,   217,
     218,   219,   419,   220,   217,   218,   219,   420,   220,   217,
     218,   219,   453,   220,   217,   218,   219,   454,   220,   217,
     218,   219,   455,   220,   217,   218,   219,   473,   220,   217,
     218,   219,   474,   220,   217,   218,   219,   475,   220
};

static const yytype_int16 yycheck[] =
{
      25,    29,   185,   165,   166,   167,     1,    32,    33,     6,
      22,     3,     4,     5,     6,     7,     6,     6,    16,     4,
       1,   364,     6,    35,     6,    16,     6,     6,    32,    33,
       6,    26,   215,   213,   217,   218,   219,   220,     3,     4,
       5,     6,     7,     0,     3,     4,     5,     6,     7,    79,
     298,     3,     4,     5,   430,     7,    25,    26,    71,    72,
       3,     4,     5,     6,     7,     0,    51,     3,     4,     5,
       6,     7,    30,    31,     3,     4,     5,     6,     7,    30,
      31,    79,   102,    80,   104,   110,   429,    82,    79,    77,
     466,    80,    82,    85,    86,   275,    80,     5,    80,     7,
      80,    80,    30,    31,    80,    74,   110,    88,   356,    79,
      79,     3,     4,     5,    83,     7,    79,    87,    77,    82,
      85,    86,    80,   104,   102,   106,    85,    86,    80,    80,
     122,     1,   113,   114,   115,   116,   117,    80,   104,   322,
     323,   324,    85,    86,    80,   328,   329,   330,    80,    85,
      86,    80,    80,    14,    15,   120,    85,    86,   102,   342,
     343,   344,   345,   346,    77,   190,   191,   127,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   190,   191,    80,     3,
       4,     5,    79,     7,   179,    79,   221,   222,   223,   224,
     225,   186,   187,   188,   189,     3,     4,     5,     6,     7,
      71,    72,     3,     4,     5,     6,     7,   221,   222,   223,
     224,   225,    79,   406,   407,   408,    79,   212,    79,   412,
     413,   243,   244,    79,   104,     3,     4,     5,     6,     7,
      71,    72,    79,   113,   114,   115,   116,     3,     4,     5,
       6,     7,    30,    31,     3,     4,     5,     6,     7,    71,
      72,     3,     4,     5,     6,     7,    80,    77,   124,   431,
     453,   454,   455,   104,    79,   300,   132,   133,   134,    77,
       3,     4,     5,     6,     7,    71,    72,    85,    86,    80,
     473,   474,   475,    81,    85,    86,   300,    24,    25,    26,
     325,   326,   327,     3,     4,     5,     6,     7,     5,     6,
       7,    26,    80,     6,     7,   102,   103,    85,    86,   130,
     131,   325,   326,   327,    80,   359,   360,   366,   367,    85,
      86,    80,    79,    79,    79,    79,    85,    86,    80,    79,
      79,    79,    79,    85,    86,    79,   331,    74,   118,   119,
      81,   121,    79,   123,    79,   125,    83,    80,   128,    74,
      79,    79,    85,    86,    79,    79,    79,    79,    83,   354,
      79,   399,     3,     4,     5,     6,     7,     3,     4,     5,
      80,     7,    81,    77,   104,    85,    86,    79,     6,    87,
     415,   416,   417,   418,   419,   420,   421,   126,    81,   424,
       3,     4,     5,     6,     7,   390,     3,     4,     5,     6,
       7,   415,   416,   417,   418,   419,   420,   421,    81,   135,
     424,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,   135,
     135,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   104,    75,    76,
      80,    80,    79,     3,     4,     5,     6,     7,     6,     6,
       6,     6,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     6,     6,   104,     6,     6,
     107,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     6,    80,     3,     4,
       5,    80,     7,     3,     4,     5,    82,     7,     3,     4,
       5,    84,     7,     6,     6,     6,     6,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      80,   136,   136,   136,     6,    85,    86,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     6,    82,    80,    74,
      77,     6,   136,    85,    86,    77,    79,   108,    85,    86,
      77,    87,   136,    85,    86,    80,   136,    74,    80,    80,
      80,    80,    79,    79,   183,    80,    83,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,   310,    74,   354,    -1,   276,    -1,    79,   340,
      -1,    -1,    83,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,    -1,    -1,   181,   182,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    -1,    74,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    83,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   138,   139,     0,   141,     1,    88,   104,   106,   113,
     114,   115,   116,   117,   142,   146,   158,   160,   166,    77,
      79,   104,   167,   147,    79,    87,   102,   171,   102,   167,
     170,   118,   119,   121,   123,   125,   128,   148,   149,   150,
     151,   152,   153,   157,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    76,
      79,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   107,   164,   165,   166,   168,   169,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     163,   164,    80,   170,    77,   163,   163,   154,   167,   127,
      71,    72,    71,    72,   166,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
     163,    79,    79,    81,    81,    79,    79,    79,    79,    79,
      79,    79,    81,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    74,    79,    83,     6,    80,     3,     4,     5,
       7,     3,     4,     5,     6,     7,    77,    85,    86,    77,
      77,   120,   122,   124,   132,   133,   134,   155,   126,    30,
      31,   193,   198,   198,   198,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   162,   166,    80,   171,
     171,   139,    14,    15,    71,    72,   144,   145,   169,   166,
     166,   166,   166,   163,   163,    79,   196,   197,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   166,   168,   140,   169,
      87,   169,   169,   169,   169,   163,   163,   163,   163,   163,
      81,    81,   135,   135,   135,     6,   104,   194,   167,   167,
      80,    80,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,    80,    80,    80,    82,    71,    72,    71,    72,
       6,    82,     6,     6,     6,     6,     6,    80,    80,   168,
      82,   197,    80,    84,   141,   163,   140,   143,   136,   136,
     136,   102,   103,   172,    16,    79,     6,     6,   169,   169,
     169,   163,   163,   163,   169,   169,   169,   166,    74,   145,
     169,   169,   169,   169,   169,    80,   158,    77,    82,     1,
      26,    82,   159,   161,   130,   131,   156,   156,   156,     6,
     194,    80,   195,   198,   172,   172,     6,     6,     6,    80,
      80,    80,     6,     6,    80,    79,     6,     6,     6,     6,
       6,   108,    77,   166,    87,   136,   136,   136,   170,    16,
      79,     6,    80,    80,    80,   169,   169,   169,   169,   169,
     163,   163,   163,   163,   163,   163,   163,   163,    80,   194,
      80,   195,   198,     6,     6,     6,    80,    80,    80,    80,
      80,    80,    80,    80,    77,    77,    79,    80,   169,   169,
     169,    80,   195,     6,     6,     6,    80,   169,   169,   169,
      80,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   137,   138,   139,   139,   140,   140,   141,   141,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     145,   145,   145,   146,   146,   146,   146,   146,   147,   147,
     148,   148,   148,   148,   148,   148,   149,   149,   150,   151,
     152,   153,   154,   154,   155,   155,   155,   156,   156,   157,
     158,   158,   158,   159,   159,   160,   161,   162,   162,   163,
     163,   163,   163,   163,   163,   163,   163,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   166,   167,   168,
     168,   169,   169,   169,   169,   169,   170,   171,   172,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   193,   193,   193,   193,   193,   194,   195,   195,   196,
     196,   197,   198,   198
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       8,     4,     1,     1,     1,     4,     4,     4,     4,     8,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       8,     8,     8,     8,     4,     4,     8,     7,     7,     4,
       4,    12,    12,    12,     6,     6,     6,     8,     8,     6,
       5,     7,     9,     4,     6,     8,     1,     1,     3,     1,
       2,     6,     1,     1
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
#line 340 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1748 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 343 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1754 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 344 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1760 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 347 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1766 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 348 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1772 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 351 "faustparser.y"
                                                        { (yyval.numvariant) = 0; }
#line 1778 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 352 "faustparser.y"
                                                                                { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1784 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 355 "faustparser.y"
                                                                                        { (yyval.numvariant) = 1;}
#line 1790 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 356 "faustparser.y"
                                                                                        { (yyval.numvariant) = 2;}
#line 1796 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 357 "faustparser.y"
                                                                                                { (yyval.numvariant) = 4;}
#line 1802 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 358 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1808 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 362 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1814 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 363 "faustparser.y"
                                                        { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1820 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 370 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1826 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 371 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1832 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 374 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1838 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 375 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 1844 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 376 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1850 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 377 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 1856 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 378 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1862 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 379 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1868 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 383 "faustparser.y"
                                                                { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1874 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 384 "faustparser.y"
                                                                                { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1880 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 385 "faustparser.y"
                                                                                { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1886 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 386 "faustparser.y"
                                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 1892 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 387 "faustparser.y"
                                                                                                { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1898 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 390 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; }
#line 1904 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 391 "faustparser.y"
                                                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1910 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 394 "faustparser.y"
                                                                                        { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1916 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 395 "faustparser.y"
                                                                                                        { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1922 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 396 "faustparser.y"
                                                                                                        { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1928 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 397 "faustparser.y"
                                                                                                        { (yyval.exp) = docNtc(); }
#line 1934 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 398 "faustparser.y"
                                                                                        { (yyval.exp) = docLst(); }
#line 1940 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 399 "faustparser.y"
                                                                                                        { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1946 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 402 "faustparser.y"
                                                                                { (yyval.cppstr) = new string(); }
#line 1952 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 403 "faustparser.y"
                                                                                                { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1958 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 406 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1964 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 409 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1970 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 412 "faustparser.y"
                                                                                        { }
#line 1976 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 415 "faustparser.y"
                                                                        { }
#line 1982 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 418 "faustparser.y"
                                                                                        { }
#line 1988 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 419 "faustparser.y"
                                                                                        { }
#line 1994 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 422 "faustparser.y"
                                                                        { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2000 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 423 "faustparser.y"
                                                                                        { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2006 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 424 "faustparser.y"
                                                                                        { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2012 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 427 "faustparser.y"
                                                                                                { (yyval.b) = true; }
#line 2018 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 428 "faustparser.y"
                                                                                                        { (yyval.b) = false; }
#line 2024 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 431 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2030 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 434 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2036 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 435 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2042 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 436 "faustparser.y"
                                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2048 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 439 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2054 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 440 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2060 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 443 "faustparser.y"
                                                                                                { (yyval.exp)=(yyvsp[0].exp); }
#line 2066 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 446 "faustparser.y"
                                                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2072 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 449 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2078 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 450 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2084 "faustparser.cpp"
    break;

  case 59: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 453 "faustparser.y"
                                                                { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2090 "faustparser.cpp"
    break;

  case 60: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 454 "faustparser.y"
                                                        { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2096 "faustparser.cpp"
    break;

  case 61: /* expression: expression PAR expression  */
#line 455 "faustparser.y"
                                                                { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2102 "faustparser.cpp"
    break;

  case 62: /* expression: expression SEQ expression  */
#line 456 "faustparser.y"
                                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2108 "faustparser.cpp"
    break;

  case 63: /* expression: expression SPLIT expression  */
#line 457 "faustparser.y"
                                                                            { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2114 "faustparser.cpp"
    break;

  case 64: /* expression: expression MIX expression  */
#line 458 "faustparser.y"
                                                                                { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2120 "faustparser.cpp"
    break;

  case 65: /* expression: expression REC expression  */
#line 459 "faustparser.y"
                                                                                { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2126 "faustparser.cpp"
    break;

  case 66: /* expression: infixexp  */
#line 460 "faustparser.y"
                                                                                            { (yyval.exp) = (yyvsp[0].exp); }
#line 2132 "faustparser.cpp"
    break;

  case 67: /* infixexp: infixexp ADD infixexp  */
#line 463 "faustparser.y"
                                                        { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2138 "faustparser.cpp"
    break;

  case 68: /* infixexp: infixexp SUB infixexp  */
#line 464 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2144 "faustparser.cpp"
    break;

  case 69: /* infixexp: infixexp MUL infixexp  */
#line 465 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2150 "faustparser.cpp"
    break;

  case 70: /* infixexp: infixexp DIV infixexp  */
#line 466 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2156 "faustparser.cpp"
    break;

  case 71: /* infixexp: infixexp MOD infixexp  */
#line 467 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2162 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp POWOP infixexp  */
#line 468 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2168 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp FDELAY infixexp  */
#line 469 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2174 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp DELAY1  */
#line 470 "faustparser.y"
                                                                        { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2180 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DOT ident  */
#line 471 "faustparser.y"
                                                                { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2186 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp AND infixexp  */
#line 473 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2192 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp OR infixexp  */
#line 474 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2198 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp XOR infixexp  */
#line 475 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2204 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp LSH infixexp  */
#line 477 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2210 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp RSH infixexp  */
#line 478 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2216 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp LT infixexp  */
#line 480 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2222 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp LE infixexp  */
#line 481 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2228 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp GT infixexp  */
#line 482 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2234 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp GE infixexp  */
#line 483 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2240 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp EQ infixexp  */
#line 484 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2246 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp NE infixexp  */
#line 485 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2252 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp LPAR arglist RPAR  */
#line 487 "faustparser.y"
                                                                                { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2258 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp LCROC deflist RCROC  */
#line 488 "faustparser.y"
                                                                                { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2264 "faustparser.cpp"
    break;

  case 89: /* infixexp: primitive  */
#line 490 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2270 "faustparser.cpp"
    break;

  case 90: /* primitive: INT  */
#line 493 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2276 "faustparser.cpp"
    break;

  case 91: /* primitive: FLOAT  */
#line 494 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 2282 "faustparser.cpp"
    break;

  case 92: /* primitive: ADD INT  */
#line 496 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2288 "faustparser.cpp"
    break;

  case 93: /* primitive: ADD FLOAT  */
#line 497 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 2294 "faustparser.cpp"
    break;

  case 94: /* primitive: SUB INT  */
#line 499 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2300 "faustparser.cpp"
    break;

  case 95: /* primitive: SUB FLOAT  */
#line 500 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2306 "faustparser.cpp"
    break;

  case 96: /* primitive: WIRE  */
#line 502 "faustparser.y"
                                                                                        { (yyval.exp) = boxWire(); }
#line 2312 "faustparser.cpp"
    break;

  case 97: /* primitive: CUT  */
#line 503 "faustparser.y"
                                                                                        { (yyval.exp) = boxCut(); }
#line 2318 "faustparser.cpp"
    break;

  case 98: /* primitive: MEM  */
#line 505 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2324 "faustparser.cpp"
    break;

  case 99: /* primitive: PREFIX  */
#line 506 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2330 "faustparser.cpp"
    break;

  case 100: /* primitive: INTCAST  */
#line 508 "faustparser.y"
                                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2336 "faustparser.cpp"
    break;

  case 101: /* primitive: FLOATCAST  */
#line 509 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2342 "faustparser.cpp"
    break;

  case 102: /* primitive: ADD  */
#line 511 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAdd); }
#line 2348 "faustparser.cpp"
    break;

  case 103: /* primitive: SUB  */
#line 512 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigSub); }
#line 2354 "faustparser.cpp"
    break;

  case 104: /* primitive: MUL  */
#line 513 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigMul); }
#line 2360 "faustparser.cpp"
    break;

  case 105: /* primitive: DIV  */
#line 514 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDiv); }
#line 2366 "faustparser.cpp"
    break;

  case 106: /* primitive: MOD  */
#line 515 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRem); }
#line 2372 "faustparser.cpp"
    break;

  case 107: /* primitive: FDELAY  */
#line 516 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2378 "faustparser.cpp"
    break;

  case 108: /* primitive: AND  */
#line 518 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAND); }
#line 2384 "faustparser.cpp"
    break;

  case 109: /* primitive: OR  */
#line 519 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigOR); }
#line 2390 "faustparser.cpp"
    break;

  case 110: /* primitive: XOR  */
#line 520 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigXOR); }
#line 2396 "faustparser.cpp"
    break;

  case 111: /* primitive: LSH  */
#line 522 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2402 "faustparser.cpp"
    break;

  case 112: /* primitive: RSH  */
#line 523 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2408 "faustparser.cpp"
    break;

  case 113: /* primitive: LT  */
#line 525 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLT); }
#line 2414 "faustparser.cpp"
    break;

  case 114: /* primitive: LE  */
#line 526 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLE); }
#line 2420 "faustparser.cpp"
    break;

  case 115: /* primitive: GT  */
#line 527 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGT); }
#line 2426 "faustparser.cpp"
    break;

  case 116: /* primitive: GE  */
#line 528 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGE); }
#line 2432 "faustparser.cpp"
    break;

  case 117: /* primitive: EQ  */
#line 529 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigEQ); }
#line 2438 "faustparser.cpp"
    break;

  case 118: /* primitive: NE  */
#line 530 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigNE); }
#line 2444 "faustparser.cpp"
    break;

  case 119: /* primitive: ATTACH  */
#line 532 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAttach); }
#line 2450 "faustparser.cpp"
    break;

  case 120: /* primitive: ENABLE  */
#line 533 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2456 "faustparser.cpp"
    break;

  case 121: /* primitive: CONTROL  */
#line 534 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2462 "faustparser.cpp"
    break;

  case 122: /* primitive: ACOS  */
#line 537 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2468 "faustparser.cpp"
    break;

  case 123: /* primitive: ASIN  */
#line 538 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2474 "faustparser.cpp"
    break;

  case 124: /* primitive: ATAN  */
#line 539 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2480 "faustparser.cpp"
    break;

  case 125: /* primitive: ATAN2  */
#line 540 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2486 "faustparser.cpp"
    break;

  case 126: /* primitive: COS  */
#line 541 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2492 "faustparser.cpp"
    break;

  case 127: /* primitive: SIN  */
#line 542 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2498 "faustparser.cpp"
    break;

  case 128: /* primitive: TAN  */
#line 543 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2504 "faustparser.cpp"
    break;

  case 129: /* primitive: EXP  */
#line 545 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2510 "faustparser.cpp"
    break;

  case 130: /* primitive: LOG  */
#line 546 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2516 "faustparser.cpp"
    break;

  case 131: /* primitive: LOG10  */
#line 547 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2522 "faustparser.cpp"
    break;

  case 132: /* primitive: POWOP  */
#line 548 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2528 "faustparser.cpp"
    break;

  case 133: /* primitive: POWFUN  */
#line 549 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2534 "faustparser.cpp"
    break;

  case 134: /* primitive: SQRT  */
#line 550 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2540 "faustparser.cpp"
    break;

  case 135: /* primitive: ABS  */
#line 552 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2546 "faustparser.cpp"
    break;

  case 136: /* primitive: MIN  */
#line 553 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2552 "faustparser.cpp"
    break;

  case 137: /* primitive: MAX  */
#line 554 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2558 "faustparser.cpp"
    break;

  case 138: /* primitive: FMOD  */
#line 556 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2564 "faustparser.cpp"
    break;

  case 139: /* primitive: REMAINDER  */
#line 557 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2570 "faustparser.cpp"
    break;

  case 140: /* primitive: FLOOR  */
#line 559 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2576 "faustparser.cpp"
    break;

  case 141: /* primitive: CEIL  */
#line 560 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2582 "faustparser.cpp"
    break;

  case 142: /* primitive: RINT  */
#line 561 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2588 "faustparser.cpp"
    break;

  case 143: /* primitive: RDTBL  */
#line 564 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2594 "faustparser.cpp"
    break;

  case 144: /* primitive: RWTBL  */
#line 565 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2600 "faustparser.cpp"
    break;

  case 145: /* primitive: SELECT2  */
#line 567 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2606 "faustparser.cpp"
    break;

  case 146: /* primitive: SELECT3  */
#line 568 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2612 "faustparser.cpp"
    break;

  case 147: /* primitive: ident  */
#line 570 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2618 "faustparser.cpp"
    break;

  case 148: /* primitive: SUB ident  */
#line 571 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2624 "faustparser.cpp"
    break;

  case 149: /* primitive: LPAR expression RPAR  */
#line 573 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2630 "faustparser.cpp"
    break;

  case 150: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 575 "faustparser.y"
                                                                                                { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2636 "faustparser.cpp"
    break;

  case 151: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 577 "faustparser.y"
                                                                        { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2642 "faustparser.cpp"
    break;

  case 152: /* primitive: ffunction  */
#line 579 "faustparser.y"
                                                                                        { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2648 "faustparser.cpp"
    break;

  case 153: /* primitive: fconst  */
#line 580 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2654 "faustparser.cpp"
    break;

  case 154: /* primitive: fvariable  */
#line 581 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2660 "faustparser.cpp"
    break;

  case 155: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 582 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2666 "faustparser.cpp"
    break;

  case 156: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 583 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2672 "faustparser.cpp"
    break;

  case 157: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 584 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2678 "faustparser.cpp"
    break;

  case 158: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 585 "faustparser.y"
                                                { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2684 "faustparser.cpp"
    break;

  case 159: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 586 "faustparser.y"
                                                                                                { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2690 "faustparser.cpp"
    break;

  case 160: /* primitive: button  */
#line 587 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2696 "faustparser.cpp"
    break;

  case 161: /* primitive: checkbox  */
#line 588 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2702 "faustparser.cpp"
    break;

  case 162: /* primitive: vslider  */
#line 589 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2708 "faustparser.cpp"
    break;

  case 163: /* primitive: hslider  */
#line 590 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2714 "faustparser.cpp"
    break;

  case 164: /* primitive: nentry  */
#line 591 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2720 "faustparser.cpp"
    break;

  case 165: /* primitive: vgroup  */
#line 592 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2726 "faustparser.cpp"
    break;

  case 166: /* primitive: hgroup  */
#line 593 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2732 "faustparser.cpp"
    break;

  case 167: /* primitive: tgroup  */
#line 594 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2738 "faustparser.cpp"
    break;

  case 168: /* primitive: vbargraph  */
#line 595 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2744 "faustparser.cpp"
    break;

  case 169: /* primitive: hbargraph  */
#line 596 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2750 "faustparser.cpp"
    break;

  case 170: /* primitive: soundfile  */
#line 597 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2756 "faustparser.cpp"
    break;

  case 171: /* primitive: fpar  */
#line 599 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2762 "faustparser.cpp"
    break;

  case 172: /* primitive: fseq  */
#line 600 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2768 "faustparser.cpp"
    break;

  case 173: /* primitive: fsum  */
#line 601 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2774 "faustparser.cpp"
    break;

  case 174: /* primitive: fprod  */
#line 602 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2780 "faustparser.cpp"
    break;

  case 175: /* primitive: finputs  */
#line 604 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2786 "faustparser.cpp"
    break;

  case 176: /* primitive: foutputs  */
#line 605 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2792 "faustparser.cpp"
    break;

  case 177: /* ident: IDENT  */
#line 610 "faustparser.y"
                                                                                { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2798 "faustparser.cpp"
    break;

  case 178: /* name: IDENT  */
#line 613 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2804 "faustparser.cpp"
    break;

  case 179: /* arglist: argument  */
#line 618 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2810 "faustparser.cpp"
    break;

  case 180: /* arglist: arglist PAR argument  */
#line 619 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2816 "faustparser.cpp"
    break;

  case 181: /* argument: argument SEQ argument  */
#line 622 "faustparser.y"
                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2822 "faustparser.cpp"
    break;

  case 182: /* argument: argument SPLIT argument  */
#line 623 "faustparser.y"
                                                                        { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2828 "faustparser.cpp"
    break;

  case 183: /* argument: argument MIX argument  */
#line 624 "faustparser.y"
                                                                        { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2834 "faustparser.cpp"
    break;

  case 184: /* argument: argument REC argument  */
#line 625 "faustparser.y"
                                                                        { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2840 "faustparser.cpp"
    break;

  case 185: /* argument: infixexp  */
#line 626 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2846 "faustparser.cpp"
    break;

  case 186: /* string: STRING  */
#line 629 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2852 "faustparser.cpp"
    break;

  case 187: /* uqstring: STRING  */
#line 632 "faustparser.y"
                                                                                { (yyval.exp) = unquote(yytext); }
#line 2858 "faustparser.cpp"
    break;

  case 188: /* fstring: STRING  */
#line 635 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2864 "faustparser.cpp"
    break;

  case 189: /* fstring: FSTRING  */
#line 636 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2870 "faustparser.cpp"
    break;

  case 190: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 642 "faustparser.y"
                                                                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2876 "faustparser.cpp"
    break;

  case 191: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 646 "faustparser.y"
                                                                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2882 "faustparser.cpp"
    break;

  case 192: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 650 "faustparser.y"
                                                                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2888 "faustparser.cpp"
    break;

  case 193: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 654 "faustparser.y"
                                                                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2894 "faustparser.cpp"
    break;

  case 194: /* finputs: INPUTS LPAR expression RPAR  */
#line 658 "faustparser.y"
                                                      { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2900 "faustparser.cpp"
    break;

  case 195: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 661 "faustparser.y"
                                                       { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2906 "faustparser.cpp"
    break;

  case 196: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 669 "faustparser.y"
                                                                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2912 "faustparser.cpp"
    break;

  case 197: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 673 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2918 "faustparser.cpp"
    break;

  case 198: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 676 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2924 "faustparser.cpp"
    break;

  case 199: /* button: BUTTON LPAR uqstring RPAR  */
#line 680 "faustparser.y"
                                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2930 "faustparser.cpp"
    break;

  case 200: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 683 "faustparser.y"
                                                                { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2936 "faustparser.cpp"
    break;

  case 201: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 687 "faustparser.y"
                                                                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2942 "faustparser.cpp"
    break;

  case 202: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 690 "faustparser.y"
                                                                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2948 "faustparser.cpp"
    break;

  case 203: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 693 "faustparser.y"
                                                                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2954 "faustparser.cpp"
    break;

  case 204: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 696 "faustparser.y"
                                                                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2960 "faustparser.cpp"
    break;

  case 205: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 699 "faustparser.y"
                                                                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2966 "faustparser.cpp"
    break;

  case 206: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 702 "faustparser.y"
                                                                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2972 "faustparser.cpp"
    break;

  case 207: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 706 "faustparser.y"
                                                                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2978 "faustparser.cpp"
    break;

  case 208: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 709 "faustparser.y"
                                                                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2984 "faustparser.cpp"
    break;

  case 209: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 712 "faustparser.y"
                                                                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2990 "faustparser.cpp"
    break;

  case 210: /* signature: type fun LPAR typelist RPAR  */
#line 718 "faustparser.y"
                                                                    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2996 "faustparser.cpp"
    break;

  case 211: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 719 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3002 "faustparser.cpp"
    break;

  case 212: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 720 "faustparser.y"
                                                                { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3008 "faustparser.cpp"
    break;

  case 213: /* signature: type fun LPAR RPAR  */
#line 722 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3014 "faustparser.cpp"
    break;

  case 214: /* signature: type fun OR fun LPAR RPAR  */
#line 723 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3020 "faustparser.cpp"
    break;

  case 215: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 724 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3026 "faustparser.cpp"
    break;

  case 216: /* fun: IDENT  */
#line 727 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 3032 "faustparser.cpp"
    break;

  case 217: /* typelist: type  */
#line 730 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3038 "faustparser.cpp"
    break;

  case 218: /* typelist: typelist PAR type  */
#line 731 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3044 "faustparser.cpp"
    break;

  case 219: /* rulelist: rule  */
#line 734 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3050 "faustparser.cpp"
    break;

  case 220: /* rulelist: rulelist rule  */
#line 735 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3056 "faustparser.cpp"
    break;

  case 221: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 739 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3062 "faustparser.cpp"
    break;

  case 222: /* type: INTCAST  */
#line 742 "faustparser.y"
                                                        { (yyval.exp) = tree(0); }
#line 3068 "faustparser.cpp"
    break;

  case 223: /* type: FLOATCAST  */
#line 743 "faustparser.y"
                                                                                        { (yyval.exp) = tree(1); }
#line 3074 "faustparser.cpp"
    break;


#line 3078 "faustparser.cpp"

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

#line 746 "faustparser.y"


