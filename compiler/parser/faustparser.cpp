/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         FAUSTparse
#define yylex           FAUSTlex
#define yyerror         FAUSTerror
#define yydebug         FAUSTdebug
#define yynerrs         FAUSTnerrs
#define yylval          FAUSTlval
#define yychar          FAUSTchar

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
#define YYMAXDEPTH    100000
    
using namespace std;

extern char*        FAUSTtext;
extern const char*  FAUSTfilename;
extern int          FAUSTlineno;
extern int          FAUSTerr;

int FAUSTlex();

//----------------------------------------------------------
// unquote() : remove enclosing quotes and carriage return 
// characters from string. Returns a Tree 
//----------------------------------------------------------
inline char replaceCR(char c)
{
    return (c!='\n') ? c : ' ';
}

//----------------------------------------------------------
// A definition is accepted if the prefixset is empty or if
// the current float precision is member of the prefix set
//----------------------------------------------------------
inline bool acceptdefinition(int prefixset)
{
    int precisions[] = {0, 1, 2, 4, 8};
    return (prefixset==0) || (prefixset & precisions[gGlobal->gFloatSize]);
}
    
//----------------------------------------------------------
// 'atoi' does not work correctly on Windows with MSVC on values
// greater than 2^31 (= 2147483648)
//----------------------------------------------------------
inline int str2int(const char* str)
{
    int result = 0;
    while (*str != 0) {
        result = result * 10 + *str - '0';
        str++;
    }
    return result;
}

inline Tree unquote(char* str)
{
    size_t size = strlen(str) + 1;
    
    //-----------copy unquoted filename-------------
    char* buf = (char*)alloca(size);
    size_t j=0;

    if (str[0] == '"') {
        // it is a quoted string, we remove the quotes
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


#line 169 "faustparser.cpp"

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
  YYSYMBOL_NOTYPECAST = 31,                /* NOTYPECAST  */
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
  YYSYMBOL_ROUND = 67,                     /* ROUND  */
  YYSYMBOL_RDTBL = 68,                     /* RDTBL  */
  YYSYMBOL_RWTBL = 69,                     /* RWTBL  */
  YYSYMBOL_SELECT2 = 70,                   /* SELECT2  */
  YYSYMBOL_SELECT3 = 71,                   /* SELECT3  */
  YYSYMBOL_INT = 72,                       /* INT  */
  YYSYMBOL_FLOAT = 73,                     /* FLOAT  */
  YYSYMBOL_MODULATE = 74,                  /* MODULATE  */
  YYSYMBOL_LAMBDA = 75,                    /* LAMBDA  */
  YYSYMBOL_DOT = 76,                       /* DOT  */
  YYSYMBOL_WIRE = 77,                      /* WIRE  */
  YYSYMBOL_CUT = 78,                       /* CUT  */
  YYSYMBOL_ENDDEF = 79,                    /* ENDDEF  */
  YYSYMBOL_VIRG = 80,                      /* VIRG  */
  YYSYMBOL_LPAR = 81,                      /* LPAR  */
  YYSYMBOL_RPAR = 82,                      /* RPAR  */
  YYSYMBOL_LBRAQ = 83,                     /* LBRAQ  */
  YYSYMBOL_RBRAQ = 84,                     /* RBRAQ  */
  YYSYMBOL_LCROC = 85,                     /* LCROC  */
  YYSYMBOL_RCROC = 86,                     /* RCROC  */
  YYSYMBOL_WITH = 87,                      /* WITH  */
  YYSYMBOL_LETREC = 88,                    /* LETREC  */
  YYSYMBOL_WHERE = 89,                     /* WHERE  */
  YYSYMBOL_DEF = 90,                       /* DEF  */
  YYSYMBOL_LAPPLY = 91,                    /* LAPPLY  */
  YYSYMBOL_IMPORT = 92,                    /* IMPORT  */
  YYSYMBOL_COMPONENT = 93,                 /* COMPONENT  */
  YYSYMBOL_LIBRARY = 94,                   /* LIBRARY  */
  YYSYMBOL_ENVIRONMENT = 95,               /* ENVIRONMENT  */
  YYSYMBOL_WAVEFORM = 96,                  /* WAVEFORM  */
  YYSYMBOL_ROUTE = 97,                     /* ROUTE  */
  YYSYMBOL_ENABLE = 98,                    /* ENABLE  */
  YYSYMBOL_CONTROL = 99,                   /* CONTROL  */
  YYSYMBOL_IPAR = 100,                     /* IPAR  */
  YYSYMBOL_ISEQ = 101,                     /* ISEQ  */
  YYSYMBOL_ISUM = 102,                     /* ISUM  */
  YYSYMBOL_IPROD = 103,                    /* IPROD  */
  YYSYMBOL_INPUTS = 104,                   /* INPUTS  */
  YYSYMBOL_OUTPUTS = 105,                  /* OUTPUTS  */
  YYSYMBOL_STRING = 106,                   /* STRING  */
  YYSYMBOL_FSTRING = 107,                  /* FSTRING  */
  YYSYMBOL_IDENT = 108,                    /* IDENT  */
  YYSYMBOL_EXTRA = 109,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 110,                  /* DECLARE  */
  YYSYMBOL_CASE = 111,                     /* CASE  */
  YYSYMBOL_ARROW = 112,                    /* ARROW  */
  YYSYMBOL_ASSERTBOUNDS = 113,             /* ASSERTBOUNDS  */
  YYSYMBOL_LOWEST = 114,                   /* LOWEST  */
  YYSYMBOL_HIGHEST = 115,                  /* HIGHEST  */
  YYSYMBOL_FLOATMODE = 116,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 117,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 118,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 119,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 120,                     /* BDOC  */
  YYSYMBOL_EDOC = 121,                     /* EDOC  */
  YYSYMBOL_BEQN = 122,                     /* BEQN  */
  YYSYMBOL_EEQN = 123,                     /* EEQN  */
  YYSYMBOL_BDGM = 124,                     /* BDGM  */
  YYSYMBOL_EDGM = 125,                     /* EDGM  */
  YYSYMBOL_BLST = 126,                     /* BLST  */
  YYSYMBOL_ELST = 127,                     /* ELST  */
  YYSYMBOL_BMETADATA = 128,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 129,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 130,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 131,                   /* NOTICE  */
  YYSYMBOL_LISTING = 132,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 133,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 134,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 135,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 136,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 137,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 138,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 139,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 140,                 /* $accept  */
  YYSYMBOL_program = 141,                  /* program  */
  YYSYMBOL_stmtlist = 142,                 /* stmtlist  */
  YYSYMBOL_deflist = 143,                  /* deflist  */
  YYSYMBOL_variantlist = 144,              /* variantlist  */
  YYSYMBOL_variant = 145,                  /* variant  */
  YYSYMBOL_reclist = 146,                  /* reclist  */
  YYSYMBOL_vallist = 147,                  /* vallist  */
  YYSYMBOL_number = 148,                   /* number  */
  YYSYMBOL_statement = 149,                /* statement  */
  YYSYMBOL_doc = 150,                      /* doc  */
  YYSYMBOL_docelem = 151,                  /* docelem  */
  YYSYMBOL_doctxt = 152,                   /* doctxt  */
  YYSYMBOL_doceqn = 153,                   /* doceqn  */
  YYSYMBOL_docdgm = 154,                   /* docdgm  */
  YYSYMBOL_docntc = 155,                   /* docntc  */
  YYSYMBOL_doclst = 156,                   /* doclst  */
  YYSYMBOL_lstattrlist = 157,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 158,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 159,               /* lstattrval  */
  YYSYMBOL_docmtd = 160,                   /* docmtd  */
  YYSYMBOL_definition = 161,               /* definition  */
  YYSYMBOL_recinition = 162,               /* recinition  */
  YYSYMBOL_defname = 163,                  /* defname  */
  YYSYMBOL_recname = 164,                  /* recname  */
  YYSYMBOL_params = 165,                   /* params  */
  YYSYMBOL_modentry = 166,                 /* modentry  */
  YYSYMBOL_modlist = 167,                  /* modlist  */
  YYSYMBOL_expression = 168,               /* expression  */
  YYSYMBOL_infixexp = 169,                 /* infixexp  */
  YYSYMBOL_primitive = 170,                /* primitive  */
  YYSYMBOL_ident = 171,                    /* ident  */
  YYSYMBOL_name = 172,                     /* name  */
  YYSYMBOL_arglist = 173,                  /* arglist  */
  YYSYMBOL_argument = 174,                 /* argument  */
  YYSYMBOL_string = 175,                   /* string  */
  YYSYMBOL_uqstring = 176,                 /* uqstring  */
  YYSYMBOL_fstring = 177,                  /* fstring  */
  YYSYMBOL_fpar = 178,                     /* fpar  */
  YYSYMBOL_fseq = 179,                     /* fseq  */
  YYSYMBOL_fsum = 180,                     /* fsum  */
  YYSYMBOL_fprod = 181,                    /* fprod  */
  YYSYMBOL_finputs = 182,                  /* finputs  */
  YYSYMBOL_foutputs = 183,                 /* foutputs  */
  YYSYMBOL_ffunction = 184,                /* ffunction  */
  YYSYMBOL_fconst = 185,                   /* fconst  */
  YYSYMBOL_fvariable = 186,                /* fvariable  */
  YYSYMBOL_button = 187,                   /* button  */
  YYSYMBOL_checkbox = 188,                 /* checkbox  */
  YYSYMBOL_vslider = 189,                  /* vslider  */
  YYSYMBOL_hslider = 190,                  /* hslider  */
  YYSYMBOL_nentry = 191,                   /* nentry  */
  YYSYMBOL_vgroup = 192,                   /* vgroup  */
  YYSYMBOL_hgroup = 193,                   /* hgroup  */
  YYSYMBOL_tgroup = 194,                   /* tgroup  */
  YYSYMBOL_vbargraph = 195,                /* vbargraph  */
  YYSYMBOL_hbargraph = 196,                /* hbargraph  */
  YYSYMBOL_soundfile = 197,                /* soundfile  */
  YYSYMBOL_signature = 198,                /* signature  */
  YYSYMBOL_fun = 199,                      /* fun  */
  YYSYMBOL_typelist = 200,                 /* typelist  */
  YYSYMBOL_rulelist = 201,                 /* rulelist  */
  YYSYMBOL_rule = 202,                     /* rule  */
  YYSYMBOL_type = 203,                     /* type  */
  YYSYMBOL_argtype = 204                   /* argtype  */
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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYLAST   800

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  140
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  239
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  511

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   394


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
     135,   136,   137,   138,   139
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   352,   352,   355,   356,   359,   360,   363,   364,   367,
     368,   369,   370,   373,   374,   381,   382,   385,   386,   387,
     388,   389,   390,   393,   394,   395,   396,   397,   400,   401,
     404,   405,   406,   407,   408,   409,   412,   413,   416,   419,
     422,   425,   428,   429,   432,   433,   434,   437,   438,   441,
     444,   445,   446,   449,   450,   453,   456,   459,   460,   463,
     464,   467,   468,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   492,   493,   494,   496,   497,   499,   500,   501,   502,
     503,   504,   506,   507,   509,   512,   513,   515,   516,   518,
     519,   521,   522,   524,   525,   527,   528,   530,   531,   532,
     533,   534,   535,   537,   538,   539,   541,   542,   544,   545,
     546,   547,   548,   549,   551,   552,   553,   555,   556,   557,
     558,   559,   560,   561,   563,   564,   565,   566,   567,   568,
     570,   571,   572,   574,   575,   577,   578,   579,   580,   582,
     583,   585,   586,   588,   589,   590,   592,   593,   595,   596,
     602,   605,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   628,   629,   630,   631,   633,   634,   638,   641,
     644,   645,   648,   649,   650,   651,   652,   655,   658,   661,
     662,   667,   671,   675,   679,   683,   686,   691,   695,   699,
     704,   707,   710,   713,   716,   719,   722,   725,   729,   732,
     735,   742,   743,   744,   745,   747,   748,   749,   750,   753,
     756,   757,   760,   761,   764,   768,   769,   772,   773,   774
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
  "DELAY1", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "NOTYPECAST",
  "FFUNCTION", "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER",
  "HSLIDER", "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH",
  "VBARGRAPH", "SOUNDFILE", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2",
  "COS", "SIN", "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS",
  "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "ROUND",
  "RDTBL", "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "MODULATE",
  "LAMBDA", "DOT", "WIRE", "CUT", "ENDDEF", "VIRG", "LPAR", "RPAR",
  "LBRAQ", "RBRAQ", "LCROC", "RCROC", "WITH", "LETREC", "WHERE", "DEF",
  "LAPPLY", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM",
  "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS",
  "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST", "FLOATMODE", "DOUBLEMODE",
  "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM",
  "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE",
  "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "variantlist", "variant", "reclist", "vallist", "number",
  "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc",
  "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "modentry",
  "modlist", "expression", "infixexp", "primitive", "ident", "name",
  "arglist", "argument", "string", "uqstring", "fstring", "fpar", "fseq",
  "fsum", "fprod", "finputs", "foutputs", "ffunction", "fconst",
  "fvariable", "button", "checkbox", "vslider", "hslider", "nentry",
  "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph", "soundfile",
  "signature", "fun", "typelist", "rulelist", "rule", "type", "argtype", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-379)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -379,    42,    66,  -379,    26,   -73,   -55,  -379,   -78,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,     8,  -379,  -379,
     -32,  -379,   -48,   280,   434,   434,  -379,     5,  -379,    24,
      54,  -379,   434,   434,  -379,   -78,  -379,  -379,    45,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
     178,   292,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,   118,   128,   143,   149,
     161,   164,   184,   190,   207,   213,   225,   241,   250,   281,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,   302,  -379,
    -379,   434,   -32,   313,   322,    71,   157,   324,  -379,  -379,
     326,   338,   348,   358,   359,   379,   288,  -379,  -379,  -379,
     598,  -379,  -379,    10,   593,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,    40,   598,   169,   386,  -379,
      18,     6,   173,    27,  -379,  -379,  -379,  -379,  -379,  -379,
     255,   255,   255,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   400,    50,  -379,     9,   505,   -32,
     -32,  -379,    37,   434,   400,   400,   400,   400,   434,   434,
     432,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,  -379,
     400,   434,  -379,   434,   424,   434,   434,   434,   434,   434,
     434,   434,   434,   434,  -379,   433,   435,  -379,  -379,  -379,
    -379,  -379,   387,   388,   402,  -379,  -379,  -379,  -379,   511,
     436,   -78,   -78,   459,   461,   540,   549,   550,   556,   557,
     573,   574,   595,   596,    32,  -379,  -379,   -32,   434,   434,
     502,   507,   510,   219,   276,  -379,  -379,    11,  -379,   216,
     597,   619,   620,   621,    73,   159,   434,     4,  -379,   670,
     670,   670,   670,   670,   670,   680,   680,   680,   271,   271,
     271,   271,   271,   271,   271,    23,   261,  -379,    34,   542,
     593,   434,   593,   593,    96,  -379,   363,   363,   196,   329,
    -379,  -379,  -379,   491,   492,   493,   275,  -379,     3,   627,
     631,  -379,  -379,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   400,   562,  -379,    65,   593,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,    37,  -379,   434,   434,   434,   434,
     434,  -379,  -379,    35,  -379,  -379,  -379,  -379,    31,   165,
     555,    13,   257,   257,   257,  -379,  -379,   634,   436,   167,
     275,   275,   419,   704,   709,   211,   256,   263,   714,   719,
      58,  -379,   563,  -379,  -379,    30,   724,   729,   734,   763,
     534,  -379,  -379,  -379,   568,   400,  -379,  -379,  -379,   565,
    -379,  -379,   512,   513,   518,    24,    15,  -379,  -379,  -379,
    -379,    53,  -379,   579,   580,   434,   434,   434,  -379,  -379,
    -379,   434,   434,  -379,   434,   434,  -379,   434,   434,   434,
     434,   434,  -379,  -379,   572,   434,  -379,  -379,  -379,   581,
     436,   290,   347,  -379,  -379,  -379,   768,   773,   778,   350,
     356,   298,   311,   517,   547,   554,   561,   566,  -379,   571,
    -379,    48,  -379,    75,  -379,   434,   434,   434,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,   436,   297,
    -379,   783,   788,   793,   585,  -379,    76,   434,   434,   434,
     310,  -379,   578,   583,   588,  -379,    77,  -379,  -379,  -379,
    -379
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   188,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   189,     0,    36,     0,     0,   198,     0,   197,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   118,   119,   122,   120,   121,   123,
     107,   108,   114,   109,   110,   111,   113,   115,   116,   117,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,     0,     0,     0,     0,   153,   154,   155,
     196,    94,   156,     0,   190,   182,   183,   184,   185,   186,
     187,   162,   163,   164,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,    71,     0,     0,    24,
       0,     0,     0,     0,    37,    97,    98,    99,   100,   157,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    59,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,    23,    25,    38,
      39,    41,     0,     0,     0,    43,    49,   235,   236,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,   158,     0,     0,     0,
       0,     0,     7,     0,     0,    17,    18,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,    86,
      87,    90,    88,    89,    91,    72,    73,    82,    74,    75,
      76,    81,    83,    84,    85,    77,    78,    80,     0,     7,
     191,     0,   193,   194,   192,   195,    68,    69,    67,    66,
      70,     5,    13,     0,     0,     0,     0,   229,     0,     0,
       0,   210,   211,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,    60,   165,   166,   167,
      19,    20,    21,    22,     0,   168,     0,     0,     0,     0,
       0,   205,   206,     0,   161,   233,    92,    93,     0,     0,
       7,     0,     0,     0,     0,   199,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,   160,    16,     0,     0,     0,     0,     0,
       0,     6,    50,    63,     0,     0,    64,     5,    14,     0,
      47,    48,     0,     0,     0,     0,     0,   237,   238,   239,
     225,     0,   230,     0,     0,     0,     0,     0,   215,   216,
     217,     0,     0,   220,     0,     0,   169,     0,     0,     0,
       0,     0,    54,    56,     7,     0,    44,    45,    46,     0,
       0,     0,     0,   221,   208,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
     207,     0,   226,     0,   231,     0,     0,     0,   219,   218,
     159,   170,   201,   202,   203,   204,   234,    53,     0,     0,
     222,     0,     0,     0,     0,   227,     0,     0,     0,     0,
       0,   223,     0,     0,     0,   228,     0,   212,   213,   214,
     224
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -379,  -379,   473,  -317,     0,  -379,  -379,  -379,   314,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,    44,
    -379,   299,  -379,  -379,  -379,  -379,   404,  -379,    -4,   -25,
    -379,    16,   -17,  -171,  -102,   -28,   100,    47,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -375,
    -378,  -379,   382,   217,   220
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   309,   368,    14,   371,   277,   278,    15,
      23,    37,    38,    39,    40,    41,    42,   162,   245,   412,
      43,    16,   408,    17,   409,   264,   186,   187,   155,   130,
     131,   132,    22,   133,   134,    30,   188,   377,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   249,   328,
     421,   287,   288,   250,   422
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     156,   158,     4,   416,   370,    29,    19,   156,   156,   229,
     230,   231,   232,   233,   404,   267,   223,   354,   163,   378,
      18,   229,   230,   231,   232,   233,    20,     5,   160,   161,
      21,   450,     5,   225,   226,   227,   435,   228,   342,   405,
     223,   223,     3,   229,   230,   231,   232,   233,   218,   219,
     308,   273,   274,   229,   230,   231,   232,   233,    28,   452,
      21,   225,   226,   227,   488,   228,    -2,   169,   229,   230,
     231,   232,   233,   473,    26,   471,   229,   230,   231,   232,
     233,   452,   452,   452,   379,   286,   156,   157,   364,    24,
     444,   279,   224,   235,   236,   355,   451,   406,    25,   220,
     268,   227,   407,   228,   221,   235,   236,   185,   222,   275,
     276,   496,   436,   494,   343,   363,   366,   400,     6,   234,
      27,   310,   506,   312,   313,   314,   315,   235,   236,   489,
      28,   240,   266,   159,     7,   453,     8,   235,   236,     7,
     433,   239,     9,    10,    11,    12,    13,     9,    10,    11,
      12,   393,   235,   236,   191,   361,   246,   490,   501,   510,
     235,   236,   229,   230,   231,   232,   233,   346,   229,   230,
     231,   232,   233,   156,   156,   164,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   284,   285,   417,   418,   419,   170,
     265,   231,   232,   233,   156,   156,   156,   156,   156,   171,
     280,   281,   282,   283,   229,   230,   231,   232,   233,   225,
     226,   227,   356,   228,   172,   316,   317,   318,   319,   320,
     173,   382,   383,   384,   329,   330,   307,   388,   389,   390,
     192,   362,   174,   156,   402,   175,   235,   236,   237,   420,
     165,   166,   235,   236,   395,   396,   397,   398,   399,   229,
     230,   231,   232,   233,   345,   176,   229,   230,   231,   232,
     233,   177,     4,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   247,   248,   156,   219,   178,   270,
     271,   350,   351,   428,   179,   217,   218,   219,   235,   236,
     241,   229,   230,   231,   232,   233,   180,   369,   242,   243,
     244,   156,   156,   156,   229,   230,   231,   232,   233,   417,
     418,   419,   181,   456,   457,   458,   417,   418,   419,   459,
     460,   182,   385,   386,   387,   232,   233,   220,   429,   417,
     418,   419,   221,   235,   236,   430,   222,   220,   352,   353,
     235,   236,   221,   225,   226,   227,   222,   228,   391,   225,
     226,   227,   183,   228,   167,   168,   229,   230,   231,   232,
     233,   200,   472,   491,   492,   493,   417,   418,   419,   495,
     480,   375,   376,   184,    18,   235,   236,   449,   251,   252,
     410,   411,   505,   481,   189,   502,   503,   504,   235,   236,
       7,    31,    32,   190,    33,   193,    34,   194,    35,   156,
     156,    36,   156,   156,   156,   156,   156,   413,   414,   195,
     156,   443,   225,   226,   227,   425,   228,   423,   424,   196,
     461,   462,   478,   463,   464,   465,   466,   467,   479,   197,
     198,   469,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     199,    62,    63,    64,    65,   238,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     7,   108,
     269,   109,   110,   286,   311,   111,   321,   326,   322,   112,
     229,   230,   231,   232,   233,   323,   324,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     325,   331,     7,   332,   327,   126,   333,   127,   128,   129,
     229,   230,   231,   232,   233,   334,   335,   229,   230,   231,
     232,   233,   336,   337,   229,   230,   231,   232,   233,   229,
     230,   231,   232,   233,   229,   230,   231,   232,   233,   338,
     339,   225,   226,   227,   347,   228,   225,   226,   227,   348,
     228,   225,   226,   227,   349,   228,   225,   226,   227,   482,
     228,   340,   341,   357,   235,   236,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   358,   359,   360,   367,   483,
     372,   373,   374,   380,   235,   236,   484,   381,   392,   403,
     415,   235,   236,   485,   434,   486,   441,   442,   235,   236,
     487,   446,   447,   235,   236,   445,   468,   448,   235,   236,
     507,   454,   455,   470,   272,   508,   500,   401,   394,   365,
     509,   344,   474,     0,   220,     0,     0,     0,     0,   221,
       0,     0,     0,   222,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   225,   226,   227,
     426,   228,   225,   226,   227,   427,   228,   225,   226,   227,
     431,   228,   225,   226,   227,   432,   228,   225,   226,   227,
     437,   228,   225,   226,   227,   438,   228,   225,   226,   227,
     439,   228,     0,     0,     0,     0,   220,     0,     0,     0,
       0,   221,     0,     0,     0,   222,   220,     0,     0,     0,
       0,   221,     0,     0,     0,   222,   225,   226,   227,   440,
     228,   225,   226,   227,   475,   228,   225,   226,   227,   476,
     228,   225,   226,   227,   477,   228,   225,   226,   227,   497,
     228,   225,   226,   227,   498,   228,   225,   226,   227,   499,
     228
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,   378,   321,    22,    79,    32,    33,     3,
       4,     5,     6,     7,     1,     6,     6,     6,    35,    16,
       4,     3,     4,     5,     6,     7,    81,     1,    32,    33,
     108,    16,     1,     3,     4,     5,     6,     7,     6,    26,
       6,     6,     0,     3,     4,     5,     6,     7,    25,    26,
     221,    14,    15,     3,     4,     5,     6,     7,   106,     6,
     108,     3,     4,     5,    16,     7,     0,    51,     3,     4,
       5,     6,     7,   451,   106,   450,     3,     4,     5,     6,
       7,     6,     6,     6,    81,    81,   111,    82,    84,    81,
     407,   193,    82,    87,    88,    84,    81,    84,    90,    76,
      91,     5,    89,     7,    81,    87,    88,   111,    85,    72,
      73,   489,    82,   488,    82,   286,    82,    82,    92,    79,
      20,   223,   500,   225,   226,   227,   228,    87,    88,    81,
     106,   125,    82,    79,   108,    82,   110,    87,    88,   108,
      82,   123,   116,   117,   118,   119,   120,   116,   117,   118,
     119,    86,    87,    88,    83,    82,   129,    82,    82,    82,
      87,    88,     3,     4,     5,     6,     7,   269,     3,     4,
       5,     6,     7,   198,   199,   130,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   198,   199,    29,    30,    31,    81,
     184,     5,     6,     7,   229,   230,   231,   232,   233,    81,
     194,   195,   196,   197,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,    81,   229,   230,   231,   232,   233,
      81,   333,   334,   335,   251,   252,   220,   339,   340,   341,
      83,    82,    81,   268,    79,    81,    87,    88,    79,    82,
      72,    73,    87,    88,   356,   357,   358,   359,   360,     3,
       4,     5,     6,     7,   268,    81,     3,     4,     5,     6,
       7,    81,   272,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,    29,    30,   311,    26,    81,   189,
     190,    72,    73,    82,    81,    24,    25,    26,    87,    88,
     127,     3,     4,     5,     6,     7,    81,   311,   135,   136,
     137,   336,   337,   338,     3,     4,     5,     6,     7,    29,
      30,    31,    81,   425,   426,   427,    29,    30,    31,   431,
     432,    81,   336,   337,   338,     6,     7,    76,    82,    29,
      30,    31,    81,    87,    88,    82,    85,    76,    72,    73,
      87,    88,    81,     3,     4,     5,    85,     7,   342,     3,
       4,     5,    81,     7,    72,    73,     3,     4,     5,     6,
       7,    83,    82,   475,   476,   477,    29,    30,    31,    82,
      82,   106,   107,    81,   368,    87,    88,   415,   171,   172,
     133,   134,    82,    82,    81,   497,   498,   499,    87,    88,
     108,   121,   122,    81,   124,    81,   126,    81,   128,   434,
     435,   131,   437,   438,   439,   440,   441,   373,   374,    81,
     445,   405,     3,     4,     5,     6,     7,   380,   381,    81,
     434,   435,    82,   437,   438,   439,   440,   441,    82,    81,
      81,   445,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      81,    27,    28,    29,    30,    79,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,   108,    75,
       5,    77,    78,    81,    90,    81,    83,     6,    83,    85,
       3,     4,     5,     6,     7,   138,   138,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     138,    82,   108,    82,   108,   111,     6,   113,   114,   115,
       3,     4,     5,     6,     7,     6,     6,     3,     4,     5,
       6,     7,     6,     6,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     6,
       6,     3,     4,     5,    82,     7,     3,     4,     5,    82,
       7,     3,     4,     5,    84,     7,     3,     4,     5,    82,
       7,     6,     6,     6,    87,    88,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     6,     6,     6,    86,    82,
     139,   139,   139,     6,    87,    88,    82,     6,    76,    84,
       6,    87,    88,    82,    81,    79,   112,    79,    87,    88,
      79,   139,   139,    87,    88,    90,    84,   139,    87,    88,
      82,    82,    82,    82,   191,    82,    81,   368,   354,   287,
      82,   267,   452,    -1,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   141,   142,     0,   144,     1,    92,   108,   110,   116,
     117,   118,   119,   120,   145,   149,   161,   163,   171,    79,
      81,   108,   172,   150,    81,    90,   106,   176,   106,   172,
     175,   121,   122,   124,   126,   128,   131,   151,   152,   153,
     154,   155,   156,   160,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    77,
      78,    81,    85,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   111,   113,   114,   115,
     169,   170,   171,   173,   174,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   168,   169,    82,   175,    79,
     168,   168,   157,   172,   130,    72,    73,    72,    73,   171,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,   168,   166,   167,   176,    81,
      81,    83,    83,    81,    81,    81,    81,    81,    81,    81,
      83,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      76,    81,    85,     6,    82,     3,     4,     5,     7,     3,
       4,     5,     6,     7,    79,    87,    88,    79,    79,   123,
     125,   127,   135,   136,   137,   158,   129,    29,    30,   198,
     203,   203,   203,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   165,   171,    82,     6,    91,     5,
     176,   176,   142,    14,    15,    72,    73,   147,   148,   174,
     171,   171,   171,   171,   168,   168,    81,   201,   202,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   171,   173,   143,
     174,    90,   174,   174,   174,   174,   168,   168,   168,   168,
     168,    83,    83,   138,   138,   138,     6,   108,   199,   172,
     172,    82,    82,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,    82,   166,   168,   174,    82,    82,    84,
      72,    73,    72,    73,     6,    84,     6,     6,     6,     6,
       6,    82,    82,   173,    84,   202,    82,    86,   144,   168,
     143,   146,   139,   139,   139,   106,   107,   177,    16,    81,
       6,     6,   174,   174,   174,   168,   168,   168,   174,   174,
     174,   171,    76,    86,   148,   174,   174,   174,   174,   174,
      82,   161,    79,    84,     1,    26,    84,    89,   162,   164,
     133,   134,   159,   159,   159,     6,   199,    29,    30,    31,
      82,   200,   204,   177,   177,     6,     6,     6,    82,    82,
      82,     6,     6,    82,    81,     6,    82,     6,     6,     6,
       6,   112,    79,   171,   143,    90,   139,   139,   139,   175,
      16,    81,     6,    82,    82,    82,   174,   174,   174,   174,
     174,   168,   168,   168,   168,   168,   168,   168,    84,   168,
      82,   199,    82,   200,   204,     6,     6,     6,    82,    82,
      82,    82,    82,    82,    82,    82,    79,    79,    16,    81,
      82,   174,   174,   174,   199,    82,   200,     6,     6,     6,
      81,    82,   174,   174,   174,    82,   200,    82,    82,    82,
      82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   140,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   145,   145,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   149,   149,   149,   149,   149,   150,   150,
     151,   151,   151,   151,   151,   151,   152,   152,   153,   154,
     155,   156,   157,   157,   158,   158,   158,   159,   159,   160,
     161,   161,   161,   162,   162,   163,   164,   165,   165,   166,
     166,   167,   167,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   171,   172,
     173,   173,   174,   174,   174,   174,   174,   175,   176,   177,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     200,   200,   201,   201,   202,   203,   203,   204,   204,   204
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     2,
       2,     2,     2,     5,     4,     5,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     3,
       1,     3,     0,     2,     5,     5,     5,     1,     1,     3,
       7,     4,     2,     4,     2,     1,     2,     1,     3,     1,
       3,     1,     3,     5,     5,     7,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     1,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     8,
       5,     4,     1,     1,     1,     4,     4,     4,     4,     6,
       8,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     8,     8,     8,     8,     4,     4,     8,     7,     7,
       4,     4,    12,    12,    12,     6,     6,     6,     8,     8,
       6,     5,     7,     9,    11,     4,     6,     8,    10,     1,
       1,     3,     1,     2,     6,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
#line 352 "faustparser.y"
                                                    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1782 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 355 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1788 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 356 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1794 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 359 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1800 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 360 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1806 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 363 "faustparser.y"
                                                    { (yyval.numvariant) = 0; }
#line 1812 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 364 "faustparser.y"
                                                    { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1818 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 367 "faustparser.y"
                                                    { (yyval.numvariant) = 1;}
#line 1824 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 368 "faustparser.y"
                                                    { (yyval.numvariant) = 2;}
#line 1830 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 369 "faustparser.y"
                                                    { (yyval.numvariant) = 4;}
#line 1836 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 370 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1842 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 373 "faustparser.y"
                                                     { (yyval.exp) = gGlobal->nil; }
#line 1848 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 374 "faustparser.y"
                                                     { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1854 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 381 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1860 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 382 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1866 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 385 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1872 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 386 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1878 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 387 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1884 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 388 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1890 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 389 "faustparser.y"
                                                { (yyval.exp) = boxInt(-str2int(FAUSTtext)); }
#line 1896 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 390 "faustparser.y"
                                                { (yyval.exp) = boxReal(-atof(FAUSTtext)); }
#line 1902 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 393 "faustparser.y"
                                                             { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1908 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 394 "faustparser.y"
                                                             { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1914 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 395 "faustparser.y"
                                                             { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1920 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 396 "faustparser.y"
                                                             { (yyval.exp) = (yyvsp[0].exp); }
#line 1926 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 397 "faustparser.y"
                                                             { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1932 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 400 "faustparser.y"
                                                            { (yyval.exp) = gGlobal->nil; }
#line 1938 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 401 "faustparser.y"
                                                            { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1944 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 404 "faustparser.y"
                                                            { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1950 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 405 "faustparser.y"
                                                            { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1956 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 406 "faustparser.y"
                                                            { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1962 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 407 "faustparser.y"
                                                            { (yyval.exp) = docNtc(); }
#line 1968 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 408 "faustparser.y"
                                                            { (yyval.exp) = docLst(); }
#line 1974 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 409 "faustparser.y"
                                                            { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1980 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 412 "faustparser.y"
                                                           { (yyval.cppstr) = new string(); }
#line 1986 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 413 "faustparser.y"
                                                           { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(FAUSTtext)); }
#line 1992 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 416 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 1998 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 419 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2004 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 422 "faustparser.y"
                                                        { }
#line 2010 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 425 "faustparser.y"
                                                        { }
#line 2016 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 428 "faustparser.y"
                                                        { }
#line 2022 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 429 "faustparser.y"
                                                        { }
#line 2028 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 432 "faustparser.y"
                                                                { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2034 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 433 "faustparser.y"
                                                                { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2040 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 434 "faustparser.y"
                                                                { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2046 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 437 "faustparser.y"
                                                         { (yyval.b) = true; }
#line 2052 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 438 "faustparser.y"
                                                          { (yyval.b) = false; }
#line 2058 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 441 "faustparser.y"
                                                          { (yyval.exp) = (yyvsp[-1].exp); }
#line 2064 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 444 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), FAUSTfilename, FAUSTlineno); }
#line 2070 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 445 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2076 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 446 "faustparser.y"
                                                                   { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2082 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 449 "faustparser.y"
                                                              { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2088 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 450 "faustparser.y"
                                                              { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2094 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 453 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2100 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 456 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2106 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 459 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2112 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 460 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2118 "faustparser.cpp"
    break;

  case 59: /* modentry: uqstring  */
#line 463 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2124 "faustparser.cpp"
    break;

  case 60: /* modentry: uqstring SEQ argument  */
#line 464 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2130 "faustparser.cpp"
    break;

  case 61: /* modlist: modentry  */
#line 467 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2136 "faustparser.cpp"
    break;

  case 62: /* modlist: modlist PAR modentry  */
#line 468 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2142 "faustparser.cpp"
    break;

  case 63: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 471 "faustparser.y"
                                                         { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2148 "faustparser.cpp"
    break;

  case 64: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 472 "faustparser.y"
                                                         { (yyval.exp) = boxWithRecDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp)), gGlobal->nil); }
#line 2154 "faustparser.cpp"
    break;

  case 65: /* expression: expression LETREC LBRAQ reclist WHERE deflist RBRAQ  */
#line 473 "faustparser.y"
                                                                         { (yyval.exp) = boxWithRecDef((yyvsp[-6].exp),formatDefinitions((yyvsp[-3].exp)),formatDefinitions((yyvsp[-1].exp))); }
#line 2160 "faustparser.cpp"
    break;

  case 66: /* expression: expression PAR expression  */
#line 474 "faustparser.y"
                                                         { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2166 "faustparser.cpp"
    break;

  case 67: /* expression: expression SEQ expression  */
#line 475 "faustparser.y"
                                                         { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2172 "faustparser.cpp"
    break;

  case 68: /* expression: expression SPLIT expression  */
#line 476 "faustparser.y"
                                                         { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2178 "faustparser.cpp"
    break;

  case 69: /* expression: expression MIX expression  */
#line 477 "faustparser.y"
                                                         { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2184 "faustparser.cpp"
    break;

  case 70: /* expression: expression REC expression  */
#line 478 "faustparser.y"
                                                         { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2190 "faustparser.cpp"
    break;

  case 71: /* expression: infixexp  */
#line 479 "faustparser.y"
                                                         { (yyval.exp) = (yyvsp[0].exp); }
#line 2196 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp ADD infixexp  */
#line 482 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2202 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp SUB infixexp  */
#line 483 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2208 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp MUL infixexp  */
#line 484 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2214 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DIV infixexp  */
#line 485 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2220 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp MOD infixexp  */
#line 486 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2226 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp POWOP infixexp  */
#line 487 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2232 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp FDELAY infixexp  */
#line 488 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDelay)); }
#line 2238 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp DELAY1  */
#line 489 "faustparser.y"
                                            { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2244 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp DOT ident  */
#line 490 "faustparser.y"
                                            { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2250 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp AND infixexp  */
#line 492 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2256 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp OR infixexp  */
#line 493 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2262 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp XOR infixexp  */
#line 494 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2268 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp LSH infixexp  */
#line 496 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2274 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp RSH infixexp  */
#line 497 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigARightShift)); }
#line 2280 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp LT infixexp  */
#line 499 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2286 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp LE infixexp  */
#line 500 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2292 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp GT infixexp  */
#line 501 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2298 "faustparser.cpp"
    break;

  case 89: /* infixexp: infixexp GE infixexp  */
#line 502 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2304 "faustparser.cpp"
    break;

  case 90: /* infixexp: infixexp EQ infixexp  */
#line 503 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2310 "faustparser.cpp"
    break;

  case 91: /* infixexp: infixexp NE infixexp  */
#line 504 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2316 "faustparser.cpp"
    break;

  case 92: /* infixexp: infixexp LPAR arglist RPAR  */
#line 506 "faustparser.y"
                                                   { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2322 "faustparser.cpp"
    break;

  case 93: /* infixexp: infixexp LCROC deflist RCROC  */
#line 507 "faustparser.y"
                                                   { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2328 "faustparser.cpp"
    break;

  case 94: /* infixexp: primitive  */
#line 509 "faustparser.y"
                                                   { (yyval.exp) = (yyvsp[0].exp); }
#line 2334 "faustparser.cpp"
    break;

  case 95: /* primitive: INT  */
#line 512 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 2340 "faustparser.cpp"
    break;

  case 96: /* primitive: FLOAT  */
#line 513 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2346 "faustparser.cpp"
    break;

  case 97: /* primitive: ADD INT  */
#line 515 "faustparser.y"
                                                { (yyval.exp) = boxInt (str2int(FAUSTtext)); }
#line 2352 "faustparser.cpp"
    break;

  case 98: /* primitive: ADD FLOAT  */
#line 516 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2358 "faustparser.cpp"
    break;

  case 99: /* primitive: SUB INT  */
#line 518 "faustparser.y"
                                                { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); }
#line 2364 "faustparser.cpp"
    break;

  case 100: /* primitive: SUB FLOAT  */
#line 519 "faustparser.y"
                                                { (yyval.exp) = boxReal( -atof(FAUSTtext) ); }
#line 2370 "faustparser.cpp"
    break;

  case 101: /* primitive: WIRE  */
#line 521 "faustparser.y"
                                                { (yyval.exp) = boxWire(); }
#line 2376 "faustparser.cpp"
    break;

  case 102: /* primitive: CUT  */
#line 522 "faustparser.y"
                                                { (yyval.exp) = boxCut(); }
#line 2382 "faustparser.cpp"
    break;

  case 103: /* primitive: MEM  */
#line 524 "faustparser.y"
                                                { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2388 "faustparser.cpp"
    break;

  case 104: /* primitive: PREFIX  */
#line 525 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2394 "faustparser.cpp"
    break;

  case 105: /* primitive: INTCAST  */
#line 527 "faustparser.y"
                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2400 "faustparser.cpp"
    break;

  case 106: /* primitive: FLOATCAST  */
#line 528 "faustparser.y"
                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2406 "faustparser.cpp"
    break;

  case 107: /* primitive: ADD  */
#line 530 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigAdd); }
#line 2412 "faustparser.cpp"
    break;

  case 108: /* primitive: SUB  */
#line 531 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigSub); }
#line 2418 "faustparser.cpp"
    break;

  case 109: /* primitive: MUL  */
#line 532 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigMul); }
#line 2424 "faustparser.cpp"
    break;

  case 110: /* primitive: DIV  */
#line 533 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigDiv); }
#line 2430 "faustparser.cpp"
    break;

  case 111: /* primitive: MOD  */
#line 534 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigRem); }
#line 2436 "faustparser.cpp"
    break;

  case 112: /* primitive: FDELAY  */
#line 535 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigDelay); }
#line 2442 "faustparser.cpp"
    break;

  case 113: /* primitive: AND  */
#line 537 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigAND); }
#line 2448 "faustparser.cpp"
    break;

  case 114: /* primitive: OR  */
#line 538 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigOR); }
#line 2454 "faustparser.cpp"
    break;

  case 115: /* primitive: XOR  */
#line 539 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigXOR); }
#line 2460 "faustparser.cpp"
    break;

  case 116: /* primitive: LSH  */
#line 541 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2466 "faustparser.cpp"
    break;

  case 117: /* primitive: RSH  */
#line 542 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigARightShift); }
#line 2472 "faustparser.cpp"
    break;

  case 118: /* primitive: LT  */
#line 544 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigLT); }
#line 2478 "faustparser.cpp"
    break;

  case 119: /* primitive: LE  */
#line 545 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigLE); }
#line 2484 "faustparser.cpp"
    break;

  case 120: /* primitive: GT  */
#line 546 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigGT); }
#line 2490 "faustparser.cpp"
    break;

  case 121: /* primitive: GE  */
#line 547 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigGE); }
#line 2496 "faustparser.cpp"
    break;

  case 122: /* primitive: EQ  */
#line 548 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEQ); }
#line 2502 "faustparser.cpp"
    break;

  case 123: /* primitive: NE  */
#line 549 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigNE); }
#line 2508 "faustparser.cpp"
    break;

  case 124: /* primitive: ATTACH  */
#line 551 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigAttach); }
#line 2514 "faustparser.cpp"
    break;

  case 125: /* primitive: ENABLE  */
#line 552 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2520 "faustparser.cpp"
    break;

  case 126: /* primitive: CONTROL  */
#line 553 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2526 "faustparser.cpp"
    break;

  case 127: /* primitive: ACOS  */
#line 555 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2532 "faustparser.cpp"
    break;

  case 128: /* primitive: ASIN  */
#line 556 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2538 "faustparser.cpp"
    break;

  case 129: /* primitive: ATAN  */
#line 557 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2544 "faustparser.cpp"
    break;

  case 130: /* primitive: ATAN2  */
#line 558 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2550 "faustparser.cpp"
    break;

  case 131: /* primitive: COS  */
#line 559 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2556 "faustparser.cpp"
    break;

  case 132: /* primitive: SIN  */
#line 560 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2562 "faustparser.cpp"
    break;

  case 133: /* primitive: TAN  */
#line 561 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2568 "faustparser.cpp"
    break;

  case 134: /* primitive: EXP  */
#line 563 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2574 "faustparser.cpp"
    break;

  case 135: /* primitive: LOG  */
#line 564 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2580 "faustparser.cpp"
    break;

  case 136: /* primitive: LOG10  */
#line 565 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2586 "faustparser.cpp"
    break;

  case 137: /* primitive: POWOP  */
#line 566 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2592 "faustparser.cpp"
    break;

  case 138: /* primitive: POWFUN  */
#line 567 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2598 "faustparser.cpp"
    break;

  case 139: /* primitive: SQRT  */
#line 568 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2604 "faustparser.cpp"
    break;

  case 140: /* primitive: ABS  */
#line 570 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2610 "faustparser.cpp"
    break;

  case 141: /* primitive: MIN  */
#line 571 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2616 "faustparser.cpp"
    break;

  case 142: /* primitive: MAX  */
#line 572 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2622 "faustparser.cpp"
    break;

  case 143: /* primitive: FMOD  */
#line 574 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2628 "faustparser.cpp"
    break;

  case 144: /* primitive: REMAINDER  */
#line 575 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2634 "faustparser.cpp"
    break;

  case 145: /* primitive: FLOOR  */
#line 577 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2640 "faustparser.cpp"
    break;

  case 146: /* primitive: CEIL  */
#line 578 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2646 "faustparser.cpp"
    break;

  case 147: /* primitive: RINT  */
#line 579 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2652 "faustparser.cpp"
    break;

  case 148: /* primitive: ROUND  */
#line 580 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRoundPrim->box(); }
#line 2658 "faustparser.cpp"
    break;

  case 149: /* primitive: RDTBL  */
#line 582 "faustparser.y"
                                                 { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2664 "faustparser.cpp"
    break;

  case 150: /* primitive: RWTBL  */
#line 583 "faustparser.y"
                                                 { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2670 "faustparser.cpp"
    break;

  case 151: /* primitive: SELECT2  */
#line 585 "faustparser.y"
                                                 { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2676 "faustparser.cpp"
    break;

  case 152: /* primitive: SELECT3  */
#line 586 "faustparser.y"
                                                 { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2682 "faustparser.cpp"
    break;

  case 153: /* primitive: ASSERTBOUNDS  */
#line 588 "faustparser.y"
                                                 { (yyval.exp) = boxPrim3(sigAssertBounds);}
#line 2688 "faustparser.cpp"
    break;

  case 154: /* primitive: LOWEST  */
#line 589 "faustparser.y"
                                                 { (yyval.exp) = boxPrim1(sigLowest);}
#line 2694 "faustparser.cpp"
    break;

  case 155: /* primitive: HIGHEST  */
#line 590 "faustparser.y"
                                                 { (yyval.exp) = boxPrim1(sigHighest);}
#line 2700 "faustparser.cpp"
    break;

  case 156: /* primitive: ident  */
#line 592 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), FAUSTfilename, FAUSTlineno);}
#line 2706 "faustparser.cpp"
    break;

  case 157: /* primitive: SUB ident  */
#line 593 "faustparser.y"
                                                 { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2712 "faustparser.cpp"
    break;

  case 158: /* primitive: LPAR expression RPAR  */
#line 595 "faustparser.y"
                                                  { (yyval.exp) = (yyvsp[-1].exp); }
#line 2718 "faustparser.cpp"
    break;

  case 159: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 597 "faustparser.y"
                                                  { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2724 "faustparser.cpp"
    break;

  case 160: /* primitive: LCROC modlist LAPPLY expression RCROC  */
#line 603 "faustparser.y"
                                                  { (yyval.exp) = buildBoxModulation((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2730 "faustparser.cpp"
    break;

  case 161: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 605 "faustparser.y"
                                                { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2736 "faustparser.cpp"
    break;

  case 162: /* primitive: ffunction  */
#line 607 "faustparser.y"
                                                { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2742 "faustparser.cpp"
    break;

  case 163: /* primitive: fconst  */
#line 608 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2748 "faustparser.cpp"
    break;

  case 164: /* primitive: fvariable  */
#line 609 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2754 "faustparser.cpp"
    break;

  case 165: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 610 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2760 "faustparser.cpp"
    break;

  case 166: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 611 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2766 "faustparser.cpp"
    break;

  case 167: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 612 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2772 "faustparser.cpp"
    break;

  case 168: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 613 "faustparser.y"
                                                   { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2778 "faustparser.cpp"
    break;

  case 169: /* primitive: ROUTE LPAR argument PAR argument RPAR  */
#line 614 "faustparser.y"
                                                              { (yyval.exp) = boxRoute((yyvsp[-3].exp), (yyvsp[-1].exp), boxPar(boxInt(0),boxInt(0))); }
#line 2784 "faustparser.cpp"
    break;

  case 170: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 615 "faustparser.y"
                                                                             { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2790 "faustparser.cpp"
    break;

  case 171: /* primitive: button  */
#line 616 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2796 "faustparser.cpp"
    break;

  case 172: /* primitive: checkbox  */
#line 617 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2802 "faustparser.cpp"
    break;

  case 173: /* primitive: vslider  */
#line 618 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2808 "faustparser.cpp"
    break;

  case 174: /* primitive: hslider  */
#line 619 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2814 "faustparser.cpp"
    break;

  case 175: /* primitive: nentry  */
#line 620 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2820 "faustparser.cpp"
    break;

  case 176: /* primitive: vgroup  */
#line 621 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2826 "faustparser.cpp"
    break;

  case 177: /* primitive: hgroup  */
#line 622 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2832 "faustparser.cpp"
    break;

  case 178: /* primitive: tgroup  */
#line 623 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2838 "faustparser.cpp"
    break;

  case 179: /* primitive: vbargraph  */
#line 624 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2844 "faustparser.cpp"
    break;

  case 180: /* primitive: hbargraph  */
#line 625 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2850 "faustparser.cpp"
    break;

  case 181: /* primitive: soundfile  */
#line 626 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2856 "faustparser.cpp"
    break;

  case 182: /* primitive: fpar  */
#line 628 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2862 "faustparser.cpp"
    break;

  case 183: /* primitive: fseq  */
#line 629 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2868 "faustparser.cpp"
    break;

  case 184: /* primitive: fsum  */
#line 630 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2874 "faustparser.cpp"
    break;

  case 185: /* primitive: fprod  */
#line 631 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2880 "faustparser.cpp"
    break;

  case 186: /* primitive: finputs  */
#line 633 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2886 "faustparser.cpp"
    break;

  case 187: /* primitive: foutputs  */
#line 634 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2892 "faustparser.cpp"
    break;

  case 188: /* ident: IDENT  */
#line 638 "faustparser.y"
                                                { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2898 "faustparser.cpp"
    break;

  case 189: /* name: IDENT  */
#line 641 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2904 "faustparser.cpp"
    break;

  case 190: /* arglist: argument  */
#line 644 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2910 "faustparser.cpp"
    break;

  case 191: /* arglist: arglist PAR argument  */
#line 645 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2916 "faustparser.cpp"
    break;

  case 192: /* argument: argument SEQ argument  */
#line 648 "faustparser.y"
                                                 { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2922 "faustparser.cpp"
    break;

  case 193: /* argument: argument SPLIT argument  */
#line 649 "faustparser.y"
                                                 { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2928 "faustparser.cpp"
    break;

  case 194: /* argument: argument MIX argument  */
#line 650 "faustparser.y"
                                                 { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2934 "faustparser.cpp"
    break;

  case 195: /* argument: argument REC argument  */
#line 651 "faustparser.y"
                                                 { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2940 "faustparser.cpp"
    break;

  case 196: /* argument: infixexp  */
#line 652 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp); }
#line 2946 "faustparser.cpp"
    break;

  case 197: /* string: STRING  */
#line 655 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2952 "faustparser.cpp"
    break;

  case 198: /* uqstring: STRING  */
#line 658 "faustparser.y"
                                                 { (yyval.exp) = unquote(FAUSTtext); }
#line 2958 "faustparser.cpp"
    break;

  case 199: /* fstring: STRING  */
#line 661 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2964 "faustparser.cpp"
    break;

  case 200: /* fstring: FSTRING  */
#line 662 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2970 "faustparser.cpp"
    break;

  case 201: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 668 "faustparser.y"
                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2976 "faustparser.cpp"
    break;

  case 202: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 672 "faustparser.y"
                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2982 "faustparser.cpp"
    break;

  case 203: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 676 "faustparser.y"
                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2988 "faustparser.cpp"
    break;

  case 204: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 680 "faustparser.y"
                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2994 "faustparser.cpp"
    break;

  case 205: /* finputs: INPUTS LPAR expression RPAR  */
#line 683 "faustparser.y"
                                              { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 3000 "faustparser.cpp"
    break;

  case 206: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 686 "faustparser.y"
                                               { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 3006 "faustparser.cpp"
    break;

  case 207: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 692 "faustparser.y"
                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3012 "faustparser.cpp"
    break;

  case 208: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 696 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3018 "faustparser.cpp"
    break;

  case 209: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 700 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3024 "faustparser.cpp"
    break;

  case 210: /* button: BUTTON LPAR uqstring RPAR  */
#line 704 "faustparser.y"
                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3030 "faustparser.cpp"
    break;

  case 211: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 707 "faustparser.y"
                                                 { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3036 "faustparser.cpp"
    break;

  case 212: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 711 "faustparser.y"
                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3042 "faustparser.cpp"
    break;

  case 213: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 714 "faustparser.y"
                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3048 "faustparser.cpp"
    break;

  case 214: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 717 "faustparser.y"
                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3054 "faustparser.cpp"
    break;

  case 215: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 720 "faustparser.y"
                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3060 "faustparser.cpp"
    break;

  case 216: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 723 "faustparser.y"
                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3066 "faustparser.cpp"
    break;

  case 217: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 726 "faustparser.y"
                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3072 "faustparser.cpp"
    break;

  case 218: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 730 "faustparser.y"
                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3078 "faustparser.cpp"
    break;

  case 219: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 733 "faustparser.y"
                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3084 "faustparser.cpp"
    break;

  case 220: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 736 "faustparser.y"
                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3090 "faustparser.cpp"
    break;

  case 221: /* signature: type fun LPAR typelist RPAR  */
#line 742 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-4].exp),cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3096 "faustparser.cpp"
    break;

  case 222: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 743 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3102 "faustparser.cpp"
    break;

  case 223: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 744 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-8].exp),cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3108 "faustparser.cpp"
    break;

  case 224: /* signature: type fun OR fun OR fun OR fun LPAR typelist RPAR  */
#line 745 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-10].exp),cons(cons((yyvsp[-9].exp),cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3114 "faustparser.cpp"
    break;

  case 225: /* signature: type fun LPAR RPAR  */
#line 747 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3120 "faustparser.cpp"
    break;

  case 226: /* signature: type fun OR fun LPAR RPAR  */
#line 748 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-5].exp),cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3126 "faustparser.cpp"
    break;

  case 227: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 749 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-7].exp),cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3132 "faustparser.cpp"
    break;

  case 228: /* signature: type fun OR fun OR fun OR fun LPAR RPAR  */
#line 750 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-9].exp),cons(cons((yyvsp[-8].exp),cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3138 "faustparser.cpp"
    break;

  case 229: /* fun: IDENT  */
#line 753 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); }
#line 3144 "faustparser.cpp"
    break;

  case 230: /* typelist: argtype  */
#line 756 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3150 "faustparser.cpp"
    break;

  case 231: /* typelist: typelist PAR argtype  */
#line 757 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3156 "faustparser.cpp"
    break;

  case 232: /* rulelist: rule  */
#line 760 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3162 "faustparser.cpp"
    break;

  case 233: /* rulelist: rulelist rule  */
#line 761 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3168 "faustparser.cpp"
    break;

  case 234: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 765 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3174 "faustparser.cpp"
    break;

  case 235: /* type: INTCAST  */
#line 768 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3180 "faustparser.cpp"
    break;

  case 236: /* type: FLOATCAST  */
#line 769 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3186 "faustparser.cpp"
    break;

  case 237: /* argtype: INTCAST  */
#line 772 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3192 "faustparser.cpp"
    break;

  case 238: /* argtype: FLOATCAST  */
#line 773 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3198 "faustparser.cpp"
    break;

  case 239: /* argtype: NOTYPECAST  */
#line 774 "faustparser.y"
                                                { (yyval.exp) = tree(2); }
#line 3204 "faustparser.cpp"
    break;


#line 3208 "faustparser.cpp"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 777 "faustparser.y"

