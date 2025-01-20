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

void yyerror(char* msg) 
{
    std::stringstream error;
    error << FAUSTfilename << ":" << FAUSTlineno << " : ERROR : " << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
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

//----------------------------------------------------------
// unquote() : remove enclosing quotes and carriage return 
// characters from string. Returns a Tree 
//----------------------------------------------------------
inline char replaceCR(char c)
{
    return (c != '\n') ? c : ' ';
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


#line 176 "faustparser.cpp"

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
  YYSYMBOL_ONDEMAND = 106,                 /* ONDEMAND  */
  YYSYMBOL_STRING = 107,                   /* STRING  */
  YYSYMBOL_FSTRING = 108,                  /* FSTRING  */
  YYSYMBOL_IDENT = 109,                    /* IDENT  */
  YYSYMBOL_EXTRA = 110,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 111,                  /* DECLARE  */
  YYSYMBOL_CASE = 112,                     /* CASE  */
  YYSYMBOL_ARROW = 113,                    /* ARROW  */
  YYSYMBOL_ASSERTBOUNDS = 114,             /* ASSERTBOUNDS  */
  YYSYMBOL_LOWEST = 115,                   /* LOWEST  */
  YYSYMBOL_HIGHEST = 116,                  /* HIGHEST  */
  YYSYMBOL_FLOATMODE = 117,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 118,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 119,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 120,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 121,                     /* BDOC  */
  YYSYMBOL_EDOC = 122,                     /* EDOC  */
  YYSYMBOL_BEQN = 123,                     /* BEQN  */
  YYSYMBOL_EEQN = 124,                     /* EEQN  */
  YYSYMBOL_BDGM = 125,                     /* BDGM  */
  YYSYMBOL_EDGM = 126,                     /* EDGM  */
  YYSYMBOL_BLST = 127,                     /* BLST  */
  YYSYMBOL_ELST = 128,                     /* ELST  */
  YYSYMBOL_BMETADATA = 129,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 130,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 131,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 132,                   /* NOTICE  */
  YYSYMBOL_LISTING = 133,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 134,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 135,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 136,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 137,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 138,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 139,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 140,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 141,                 /* $accept  */
  YYSYMBOL_program = 142,                  /* program  */
  YYSYMBOL_stmtlist = 143,                 /* stmtlist  */
  YYSYMBOL_deflist = 144,                  /* deflist  */
  YYSYMBOL_variantlist = 145,              /* variantlist  */
  YYSYMBOL_variant = 146,                  /* variant  */
  YYSYMBOL_reclist = 147,                  /* reclist  */
  YYSYMBOL_vallist = 148,                  /* vallist  */
  YYSYMBOL_number = 149,                   /* number  */
  YYSYMBOL_statement = 150,                /* statement  */
  YYSYMBOL_doc = 151,                      /* doc  */
  YYSYMBOL_docelem = 152,                  /* docelem  */
  YYSYMBOL_doctxt = 153,                   /* doctxt  */
  YYSYMBOL_doceqn = 154,                   /* doceqn  */
  YYSYMBOL_docdgm = 155,                   /* docdgm  */
  YYSYMBOL_docntc = 156,                   /* docntc  */
  YYSYMBOL_doclst = 157,                   /* doclst  */
  YYSYMBOL_lstattrlist = 158,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 159,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 160,               /* lstattrval  */
  YYSYMBOL_docmtd = 161,                   /* docmtd  */
  YYSYMBOL_definition = 162,               /* definition  */
  YYSYMBOL_recinition = 163,               /* recinition  */
  YYSYMBOL_defname = 164,                  /* defname  */
  YYSYMBOL_recname = 165,                  /* recname  */
  YYSYMBOL_params = 166,                   /* params  */
  YYSYMBOL_modentry = 167,                 /* modentry  */
  YYSYMBOL_modlist = 168,                  /* modlist  */
  YYSYMBOL_expression = 169,               /* expression  */
  YYSYMBOL_infixexp = 170,                 /* infixexp  */
  YYSYMBOL_primitive = 171,                /* primitive  */
  YYSYMBOL_ident = 172,                    /* ident  */
  YYSYMBOL_name = 173,                     /* name  */
  YYSYMBOL_arglist = 174,                  /* arglist  */
  YYSYMBOL_argument = 175,                 /* argument  */
  YYSYMBOL_string = 176,                   /* string  */
  YYSYMBOL_uqstring = 177,                 /* uqstring  */
  YYSYMBOL_fstring = 178,                  /* fstring  */
  YYSYMBOL_fpar = 179,                     /* fpar  */
  YYSYMBOL_fseq = 180,                     /* fseq  */
  YYSYMBOL_fsum = 181,                     /* fsum  */
  YYSYMBOL_fprod = 182,                    /* fprod  */
  YYSYMBOL_finputs = 183,                  /* finputs  */
  YYSYMBOL_foutputs = 184,                 /* foutputs  */
  YYSYMBOL_fondemand = 185,                /* fondemand  */
  YYSYMBOL_ffunction = 186,                /* ffunction  */
  YYSYMBOL_fconst = 187,                   /* fconst  */
  YYSYMBOL_fvariable = 188,                /* fvariable  */
  YYSYMBOL_button = 189,                   /* button  */
  YYSYMBOL_checkbox = 190,                 /* checkbox  */
  YYSYMBOL_vslider = 191,                  /* vslider  */
  YYSYMBOL_hslider = 192,                  /* hslider  */
  YYSYMBOL_nentry = 193,                   /* nentry  */
  YYSYMBOL_vgroup = 194,                   /* vgroup  */
  YYSYMBOL_hgroup = 195,                   /* hgroup  */
  YYSYMBOL_tgroup = 196,                   /* tgroup  */
  YYSYMBOL_vbargraph = 197,                /* vbargraph  */
  YYSYMBOL_hbargraph = 198,                /* hbargraph  */
  YYSYMBOL_soundfile = 199,                /* soundfile  */
  YYSYMBOL_signature = 200,                /* signature  */
  YYSYMBOL_fun = 201,                      /* fun  */
  YYSYMBOL_typelist = 202,                 /* typelist  */
  YYSYMBOL_rulelist = 203,                 /* rulelist  */
  YYSYMBOL_rule = 204,                     /* rule  */
  YYSYMBOL_type = 205,                     /* type  */
  YYSYMBOL_argtype = 206                   /* argtype  */
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
#define YYLAST   801

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  141
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  241
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  516

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   395


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
     135,   136,   137,   138,   139,   140
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   361,   361,   364,   365,   368,   369,   372,   373,   376,
     377,   378,   379,   382,   383,   390,   391,   394,   395,   396,
     397,   398,   399,   402,   403,   404,   405,   406,   409,   410,
     413,   414,   415,   416,   417,   418,   421,   422,   425,   428,
     431,   434,   437,   438,   441,   442,   443,   446,   447,   450,
     453,   454,   455,   458,   459,   462,   465,   468,   469,   472,
     473,   476,   477,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   501,   502,   503,   505,   506,   508,   509,   510,   511,
     512,   513,   515,   516,   518,   521,   522,   524,   525,   527,
     528,   530,   531,   533,   534,   536,   537,   539,   540,   541,
     542,   543,   544,   546,   547,   548,   550,   551,   553,   554,
     555,   556,   557,   558,   560,   561,   562,   564,   565,   566,
     567,   568,   569,   570,   572,   573,   574,   575,   576,   577,
     579,   580,   581,   583,   584,   586,   587,   588,   589,   591,
     592,   594,   595,   597,   598,   599,   601,   602,   604,   605,
     611,   614,   616,   617,   618,   619,   620,   621,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   637,   638,   639,   640,   642,   643,   644,   647,
     650,   653,   654,   657,   658,   659,   660,   661,   664,   667,
     670,   671,   676,   680,   684,   688,   692,   695,   698,   703,
     707,   711,   716,   719,   722,   725,   728,   731,   734,   737,
     741,   744,   747,   754,   755,   756,   757,   759,   760,   761,
     762,   765,   768,   769,   772,   773,   776,   780,   781,   784,
     785,   786
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
  "OUTPUTS", "ONDEMAND", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE",
  "CASE", "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST", "FLOATMODE",
  "DOUBLEMODE", "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "variantlist", "variant", "reclist", "vallist",
  "number", "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm",
  "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "modentry",
  "modlist", "expression", "infixexp", "primitive", "ident", "name",
  "arglist", "argument", "string", "uqstring", "fstring", "fpar", "fseq",
  "fsum", "fprod", "finputs", "foutputs", "fondemand", "ffunction",
  "fconst", "fvariable", "button", "checkbox", "vslider", "hslider",
  "nentry", "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph",
  "soundfile", "signature", "fun", "typelist", "rulelist", "rule", "type",
  "argtype", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-381)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -381,    61,    74,  -381,    26,   -73,   -55,  -381,   -11,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,   -22,  -381,  -381,
      -4,  -381,    -8,   306,   440,   440,  -381,    52,  -381,     4,
      77,  -381,   440,   440,  -381,   -11,  -381,  -381,    28,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
     128,   278,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,    82,    89,    93,    97,
     125,   169,   186,   193,   215,   223,   229,   245,   271,   277,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,   282,  -381,
    -381,   440,    -4,   293,   307,   164,   211,   312,  -381,  -381,
     317,   335,   343,   349,   351,   363,   385,   257,  -381,  -381,
    -381,   604,  -381,  -381,    22,   599,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,    43,   604,   270,
     286,  -381,    18,     6,   268,   246,  -381,  -381,  -381,  -381,
    -381,  -381,   269,   269,   269,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,   276,    51,  -381,     9,
     417,    -4,    -4,  -381,   230,   440,   276,   276,   276,   276,
     440,   440,   440,   390,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,  -381,   276,   440,  -381,   440,   337,   440,   440,
     440,   440,   440,   440,   440,   440,   440,  -381,   431,   433,
    -381,  -381,  -381,  -381,  -381,   383,   384,   392,  -381,  -381,
    -381,  -381,   518,   423,   -11,   -11,   465,   466,   544,   545,
     547,   556,   557,   563,   570,   571,   595,    25,  -381,  -381,
      -4,   440,   440,   488,   525,   524,   295,   309,  -381,  -381,
      11,  -381,   404,   603,   631,   632,   633,    73,   161,   213,
     440,   -65,  -381,   676,   676,   676,   676,   676,   676,   686,
     686,   686,   299,   299,   299,   299,   299,   299,   299,   288,
      39,  -381,    32,   558,   599,   440,   599,   599,   166,  -381,
     593,   593,    83,   325,  -381,  -381,  -381,   500,   505,   507,
     253,  -381,    29,   645,   646,  -381,  -381,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   276,   577,  -381,    66,
     599,  -381,  -381,  -381,  -381,  -381,  -381,  -381,   230,  -381,
     440,   440,   440,   440,   440,  -381,  -381,  -381,    47,  -381,
    -381,  -381,  -381,    31,   218,   574,    13,   256,   256,   256,
    -381,  -381,   648,   423,   174,   253,   253,   628,   671,   710,
     248,   259,   266,   715,   720,    37,  -381,   579,  -381,  -381,
      30,   725,   730,   735,   740,   548,  -381,  -381,  -381,   586,
     276,  -381,  -381,  -381,   576,  -381,  -381,   529,   530,   531,
       4,    35,  -381,  -381,  -381,  -381,    54,  -381,   597,   600,
     440,   440,   440,  -381,  -381,  -381,   440,   440,  -381,   440,
     440,  -381,   440,   440,   440,   440,   440,  -381,  -381,   602,
     440,  -381,  -381,  -381,   601,   423,   313,   197,  -381,  -381,
    -381,   769,   774,   779,    59,    80,   315,   523,   554,   561,
     568,   575,   580,  -381,   585,  -381,    36,  -381,    75,  -381,
     440,   440,   440,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,   423,   341,  -381,   784,   789,   794,   606,
    -381,    76,   440,   440,   440,   564,  -381,   284,   304,   352,
    -381,    90,  -381,  -381,  -381,  -381
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   189,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   190,     0,    36,     0,     0,   199,     0,   198,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   118,   119,   122,   120,   121,   123,
     107,   108,   114,   109,   110,   111,   113,   115,   116,   117,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   154,
     155,   197,    94,   156,     0,   191,   182,   183,   184,   185,
     186,   187,   188,   162,   163,   164,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,     0,    71,     0,
       0,    24,     0,     0,     0,     0,    37,    97,    98,    99,
     100,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
      59,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,     0,     0,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
      23,    25,    38,    39,    41,     0,     0,     0,    43,    49,
     237,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,   158,
       0,     0,     0,     0,     0,     7,     0,     0,    17,    18,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,    86,    87,    90,    88,    89,    91,    72,
      73,    82,    74,    75,    76,    81,    83,    84,    85,    77,
      78,    80,     0,     7,   192,     0,   194,   195,   193,   196,
      68,    69,    67,    66,    70,     5,    13,     0,     0,     0,
       0,   231,     0,     0,     0,   212,   213,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
      60,   165,   166,   167,    19,    20,    21,    22,     0,   168,
       0,     0,     0,     0,     0,   206,   207,   208,     0,   161,
     235,    92,    93,     0,     0,     7,     0,     0,     0,     0,
     200,   201,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,     0,   160,    16,
       0,     0,     0,     0,     0,     0,     6,    50,    63,     0,
       0,    64,     5,    14,     0,    47,    48,     0,     0,     0,
       0,     0,   239,   240,   241,   227,     0,   232,     0,     0,
       0,     0,     0,   217,   218,   219,     0,     0,   222,     0,
       0,   169,     0,     0,     0,     0,     0,    54,    56,     7,
       0,    44,    45,    46,     0,     0,     0,     0,   223,   210,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,   209,     0,   228,     0,   233,
       0,     0,     0,   221,   220,   159,   170,   202,   203,   204,
     205,   236,    53,     0,     0,   224,     0,     0,     0,     0,
     229,     0,     0,     0,     0,     0,   225,     0,     0,     0,
     230,     0,   214,   215,   216,   226
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -381,  -381,   491,  -321,     0,  -381,  -381,  -381,   323,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,    34,
    -381,   375,  -381,  -381,  -381,  -381,   418,  -381,    -3,   -25,
    -381,    16,   -17,  -181,  -103,   -28,   101,    60,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -380,  -111,  -381,   458,   346,   294
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   313,   373,    14,   376,   280,   281,    15,
      23,    37,    38,    39,    40,    41,    42,   164,   248,   417,
      43,    16,   413,    17,   414,   267,   188,   189,   157,   131,
     132,   133,    22,   134,   135,    30,   190,   382,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   252,
     332,   426,   291,   292,   253,   427
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     158,   160,     4,   421,   375,    29,    19,   158,   158,   232,
     233,   234,   235,   236,   409,   270,   290,   358,   165,   369,
      18,   232,   233,   234,   235,   236,    20,     5,   226,   162,
     163,   346,     5,   228,   229,   230,   440,   231,   226,   410,
     228,   229,   230,   312,   231,   383,   232,   233,   234,   235,
     236,   455,   493,   226,   232,   233,   234,   235,   236,    24,
     457,     3,   228,   229,   230,   222,   231,   171,    25,   232,
     233,   234,   235,   236,    -2,   476,   232,   233,   234,   235,
     236,   457,   457,   228,   229,   230,   158,   231,   234,   235,
     236,   449,   282,   238,   239,   359,   457,   411,    21,    28,
     271,    21,   412,    26,   227,   238,   239,   347,   187,   368,
     384,    28,   441,   499,   371,   223,   456,   494,     6,   438,
     224,    27,   237,   314,   225,   316,   317,   318,   319,   405,
     238,   239,   243,   269,   159,     7,   458,     8,   238,   239,
       7,   483,   242,     9,    10,    11,    12,    13,     9,    10,
      11,    12,   398,   238,   239,   365,   161,   495,   506,   166,
     238,   239,   484,   172,   232,   233,   234,   235,   236,   350,
     173,   230,   515,   231,   174,   158,   158,   158,   175,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   287,   288,   289,
     167,   168,   268,   422,   423,   424,   176,   158,   158,   158,
     158,   158,   283,   284,   285,   286,   232,   233,   234,   235,
     236,   232,   233,   234,   235,   236,   422,   423,   424,   320,
     321,   322,   323,   324,   387,   388,   389,   333,   334,   311,
     393,   394,   395,   366,   276,   277,   158,   193,   238,   239,
     177,   232,   233,   234,   235,   236,   425,   400,   401,   402,
     403,   404,   232,   233,   234,   235,   236,   178,   349,   232,
     233,   234,   235,   236,   179,     4,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   228,   229,   230,
     158,   231,   273,   274,   194,   367,   180,   407,   250,   251,
     238,   239,   278,   279,   181,   238,   239,   228,   229,   230,
     182,   231,   374,   221,   222,   158,   158,   158,   232,   233,
     234,   235,   236,   220,   221,   222,   183,   461,   462,   463,
     433,   235,   236,   464,   465,   238,   239,   390,   391,   392,
     203,   434,   422,   423,   424,   478,   238,   239,   435,   240,
     169,   170,   184,   238,   239,   228,   229,   230,   185,   231,
     380,   381,   396,   186,   223,   241,   512,   354,   355,   224,
     422,   423,   424,   225,   191,   223,   249,   496,   497,   498,
     224,   356,   357,   501,   225,     7,   513,     7,   192,    18,
     415,   416,   454,   195,   511,   477,   244,   485,   196,   507,
     508,   509,   238,   239,   245,   246,   247,   228,   229,   230,
     360,   231,   418,   419,   158,   158,   197,   158,   158,   158,
     158,   158,   272,   500,   198,   158,   448,   315,    31,    32,
     199,    33,   200,    34,   514,    35,   466,   467,    36,   468,
     469,   470,   471,   472,   201,   428,   429,   474,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   202,    62,    63,    64,
      65,   290,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   325,   108,   326,   109,   110,   254,
     255,   111,   327,   328,   330,   112,   232,   233,   234,   235,
     236,   329,   331,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   335,   336,     7,
     337,   338,   127,   339,   128,   129,   130,   232,   233,   234,
     235,   236,   340,   341,   232,   233,   234,   235,   236,   342,
     351,   232,   233,   234,   235,   236,   343,   344,   232,   233,
     234,   235,   236,   232,   233,   234,   235,   236,   232,   233,
     234,   235,   236,   422,   423,   424,   232,   233,   234,   235,
     236,   345,   228,   229,   230,   486,   231,   352,   353,   361,
     238,   239,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   228,   229,   230,   430,   231,   487,   362,   363,   364,
     377,   238,   239,   488,   372,   378,   510,   379,   238,   239,
     489,   385,   386,   397,   420,   238,   239,   490,   408,   491,
     439,   446,   238,   239,   492,   447,   450,   238,   239,   451,
     452,   453,   238,   239,   228,   229,   230,   431,   231,   459,
     223,   399,   460,   475,   275,   224,   473,   505,   348,   225,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   228,   229,   230,   432,   231,   228,   229,
     230,   436,   231,   228,   229,   230,   437,   231,   228,   229,
     230,   442,   231,   228,   229,   230,   443,   231,   228,   229,
     230,   444,   231,   228,   229,   230,   445,   231,   406,   370,
       0,   479,   223,     0,     0,     0,     0,   224,     0,     0,
       0,   225,   223,     0,     0,     0,     0,   224,     0,     0,
       0,   225,   228,   229,   230,   480,   231,   228,   229,   230,
     481,   231,   228,   229,   230,   482,   231,   228,   229,   230,
     502,   231,   228,   229,   230,   503,   231,   228,   229,   230,
     504,   231
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,   383,   325,    22,    79,    32,    33,     3,
       4,     5,     6,     7,     1,     6,    81,     6,    35,    84,
       4,     3,     4,     5,     6,     7,    81,     1,     6,    32,
      33,     6,     1,     3,     4,     5,     6,     7,     6,    26,
       3,     4,     5,   224,     7,    16,     3,     4,     5,     6,
       7,    16,    16,     6,     3,     4,     5,     6,     7,    81,
       6,     0,     3,     4,     5,    26,     7,    51,    90,     3,
       4,     5,     6,     7,     0,   455,     3,     4,     5,     6,
       7,     6,     6,     3,     4,     5,   111,     7,     5,     6,
       7,   412,   195,    87,    88,    84,     6,    84,   109,   107,
      91,   109,    89,   107,    82,    87,    88,    82,   111,   290,
      81,   107,    82,   493,    82,    76,    81,    81,    92,    82,
      81,    20,    79,   226,    85,   228,   229,   230,   231,    82,
      87,    88,   126,    82,    82,   109,    82,   111,    87,    88,
     109,    82,   124,   117,   118,   119,   120,   121,   117,   118,
     119,   120,    86,    87,    88,    82,    79,    82,    82,   131,
      87,    88,    82,    81,     3,     4,     5,     6,     7,   272,
      81,     5,    82,     7,    81,   200,   201,   202,    81,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   200,   201,   202,
      72,    73,   186,    29,    30,    31,    81,   232,   233,   234,
     235,   236,   196,   197,   198,   199,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,    29,    30,    31,   232,
     233,   234,   235,   236,   337,   338,   339,   254,   255,   223,
     343,   344,   345,    82,    14,    15,   271,    83,    87,    88,
      81,     3,     4,     5,     6,     7,    82,   360,   361,   362,
     363,   364,     3,     4,     5,     6,     7,    81,   271,     3,
       4,     5,     6,     7,    81,   275,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     3,     4,     5,
     315,     7,   191,   192,    83,    82,    81,    79,    29,    30,
      87,    88,    72,    73,    81,    87,    88,     3,     4,     5,
      81,     7,   315,    25,    26,   340,   341,   342,     3,     4,
       5,     6,     7,    24,    25,    26,    81,   430,   431,   432,
      82,     6,     7,   436,   437,    87,    88,   340,   341,   342,
      83,    82,    29,    30,    31,   456,    87,    88,    82,    79,
      72,    73,    81,    87,    88,     3,     4,     5,    81,     7,
     107,   108,   346,    81,    76,    79,    82,    72,    73,    81,
      29,    30,    31,    85,    81,    76,   130,   480,   481,   482,
      81,    72,    73,   494,    85,   109,    82,   109,    81,   373,
     134,   135,   420,    81,   505,    82,   128,    82,    81,   502,
     503,   504,    87,    88,   136,   137,   138,     3,     4,     5,
       6,     7,   378,   379,   439,   440,    81,   442,   443,   444,
     445,   446,     5,    82,    81,   450,   410,    90,   122,   123,
      81,   125,    81,   127,    82,   129,   439,   440,   132,   442,
     443,   444,   445,   446,    81,   385,   386,   450,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    81,    27,    28,    29,
      30,    81,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    83,    75,    83,    77,    78,   173,
     174,    81,   139,   139,     6,    85,     3,     4,     5,     6,
       7,   139,   109,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    82,    82,   109,
       6,     6,   112,     6,   114,   115,   116,     3,     4,     5,
       6,     7,     6,     6,     3,     4,     5,     6,     7,     6,
      82,     3,     4,     5,     6,     7,     6,     6,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    29,    30,    31,     3,     4,     5,     6,
       7,     6,     3,     4,     5,    82,     7,    82,    84,     6,
      87,    88,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     3,     4,     5,     6,     7,    82,     6,     6,     6,
     140,    87,    88,    82,    86,   140,    82,   140,    87,    88,
      82,     6,     6,    76,     6,    87,    88,    82,    84,    79,
      81,   113,    87,    88,    79,    79,    90,    87,    88,   140,
     140,   140,    87,    88,     3,     4,     5,     6,     7,    82,
      76,   358,    82,    82,   193,    81,    84,    81,   270,    85,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,   373,   291,
      -1,   457,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   142,   143,     0,   145,     1,    92,   109,   111,   117,
     118,   119,   120,   121,   146,   150,   162,   164,   172,    79,
      81,   109,   173,   151,    81,    90,   107,   177,   107,   173,
     176,   122,   123,   125,   127,   129,   132,   152,   153,   154,
     155,   156,   157,   161,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    77,
      78,    81,    85,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   112,   114,   115,
     116,   170,   171,   172,   174,   175,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   169,   170,    82,
     176,    79,   169,   169,   158,   173,   131,    72,    73,    72,
      73,   172,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,   169,   167,   168,
     177,    81,    81,    83,    83,    81,    81,    81,    81,    81,
      81,    81,    81,    83,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    76,    81,    85,     6,    82,     3,     4,
       5,     7,     3,     4,     5,     6,     7,    79,    87,    88,
      79,    79,   124,   126,   128,   136,   137,   138,   159,   130,
      29,    30,   200,   205,   205,   205,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   166,   172,    82,
       6,    91,     5,   177,   177,   143,    14,    15,    72,    73,
     148,   149,   175,   172,   172,   172,   172,   169,   169,   169,
      81,   203,   204,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   172,   174,   144,   175,    90,   175,   175,   175,   175,
     169,   169,   169,   169,   169,    83,    83,   139,   139,   139,
       6,   109,   201,   173,   173,    82,    82,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,    82,   167,   169,
     175,    82,    82,    84,    72,    73,    72,    73,     6,    84,
       6,     6,     6,     6,     6,    82,    82,    82,   174,    84,
     204,    82,    86,   145,   169,   144,   147,   140,   140,   140,
     107,   108,   178,    16,    81,     6,     6,   175,   175,   175,
     169,   169,   169,   175,   175,   175,   172,    76,    86,   149,
     175,   175,   175,   175,   175,    82,   162,    79,    84,     1,
      26,    84,    89,   163,   165,   134,   135,   160,   160,   160,
       6,   201,    29,    30,    31,    82,   202,   206,   178,   178,
       6,     6,     6,    82,    82,    82,     6,     6,    82,    81,
       6,    82,     6,     6,     6,     6,   113,    79,   172,   144,
      90,   140,   140,   140,   176,    16,    81,     6,    82,    82,
      82,   175,   175,   175,   175,   175,   169,   169,   169,   169,
     169,   169,   169,    84,   169,    82,   201,    82,   202,   206,
       6,     6,     6,    82,    82,    82,    82,    82,    82,    82,
      82,    79,    79,    16,    81,    82,   175,   175,   175,   201,
      82,   202,     6,     6,     6,    81,    82,   175,   175,   175,
      82,   202,    82,    82,    82,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   141,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   146,   146,   147,   147,   148,   148,   149,   149,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   151,   151,
     152,   152,   152,   152,   152,   152,   153,   153,   154,   155,
     156,   157,   158,   158,   159,   159,   159,   160,   160,   161,
     162,   162,   162,   163,   163,   164,   165,   166,   166,   167,
     167,   168,   168,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   172,
     173,   174,   174,   175,   175,   175,   175,   175,   176,   177,
     178,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   200,   200,   200,   200,   200,   200,
     200,   201,   202,   202,   203,   203,   204,   205,   205,   206,
     206,   206
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
       1,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     8,     8,     8,     8,     4,     4,     4,     8,
       7,     7,     4,     4,    12,    12,    12,     6,     6,     6,
       8,     8,     6,     5,     7,     9,    11,     4,     6,     8,
      10,     1,     1,     3,     1,     2,     6,     1,     1,     1,
       1,     1
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
#line 361 "faustparser.y"
                                                    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1795 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 364 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1801 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 365 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1807 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 368 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1813 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 369 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1819 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 372 "faustparser.y"
                                                    { (yyval.numvariant) = 0; }
#line 1825 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 373 "faustparser.y"
                                                    { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1831 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 376 "faustparser.y"
                                                    { (yyval.numvariant) = 1;}
#line 1837 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 377 "faustparser.y"
                                                    { (yyval.numvariant) = 2;}
#line 1843 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 378 "faustparser.y"
                                                    { (yyval.numvariant) = 4;}
#line 1849 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 379 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1855 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 382 "faustparser.y"
                                                     { (yyval.exp) = gGlobal->nil; }
#line 1861 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 383 "faustparser.y"
                                                     { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1867 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 390 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1873 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 391 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1879 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 394 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1885 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 395 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1891 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 396 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1897 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 397 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1903 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 398 "faustparser.y"
                                                { (yyval.exp) = boxInt(-str2int(FAUSTtext)); }
#line 1909 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 399 "faustparser.y"
                                                { (yyval.exp) = boxReal(-atof(FAUSTtext)); }
#line 1915 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 402 "faustparser.y"
                                                             { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1921 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 403 "faustparser.y"
                                                             { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1927 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 404 "faustparser.y"
                                                             { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1933 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 405 "faustparser.y"
                                                             { (yyval.exp) = (yyvsp[0].exp); }
#line 1939 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 406 "faustparser.y"
                                                             { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1945 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 409 "faustparser.y"
                                                            { (yyval.exp) = gGlobal->nil; }
#line 1951 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 410 "faustparser.y"
                                                            { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1957 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 413 "faustparser.y"
                                                            { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1963 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 414 "faustparser.y"
                                                            { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1969 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 415 "faustparser.y"
                                                            { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1975 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 416 "faustparser.y"
                                                            { (yyval.exp) = docNtc(); }
#line 1981 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 417 "faustparser.y"
                                                            { (yyval.exp) = docLst(); }
#line 1987 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 418 "faustparser.y"
                                                            { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1993 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 421 "faustparser.y"
                                                           { (yyval.cppstr) = new string(); }
#line 1999 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 422 "faustparser.y"
                                                           { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(FAUSTtext)); }
#line 2005 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 425 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2011 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 428 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2017 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 431 "faustparser.y"
                                                        { }
#line 2023 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 434 "faustparser.y"
                                                        { }
#line 2029 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 437 "faustparser.y"
                                                        { }
#line 2035 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 438 "faustparser.y"
                                                        { }
#line 2041 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 441 "faustparser.y"
                                                                { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2047 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 442 "faustparser.y"
                                                                { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2053 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 443 "faustparser.y"
                                                                { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2059 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 446 "faustparser.y"
                                                         { (yyval.b) = true; }
#line 2065 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 447 "faustparser.y"
                                                          { (yyval.b) = false; }
#line 2071 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 450 "faustparser.y"
                                                          { (yyval.exp) = (yyvsp[-1].exp); }
#line 2077 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 453 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), FAUSTfilename, FAUSTlineno); }
#line 2083 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 454 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2089 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 455 "faustparser.y"
                                                                   { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2095 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 458 "faustparser.y"
                                                              { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2101 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 459 "faustparser.y"
                                                              { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2107 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 462 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2113 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 465 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2119 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 468 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2125 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 469 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2131 "faustparser.cpp"
    break;

  case 59: /* modentry: uqstring  */
#line 472 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2137 "faustparser.cpp"
    break;

  case 60: /* modentry: uqstring SEQ argument  */
#line 473 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2143 "faustparser.cpp"
    break;

  case 61: /* modlist: modentry  */
#line 476 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2149 "faustparser.cpp"
    break;

  case 62: /* modlist: modlist PAR modentry  */
#line 477 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2155 "faustparser.cpp"
    break;

  case 63: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 480 "faustparser.y"
                                                         { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2161 "faustparser.cpp"
    break;

  case 64: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 481 "faustparser.y"
                                                         { (yyval.exp) = boxWithRecDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp)), gGlobal->nil); }
#line 2167 "faustparser.cpp"
    break;

  case 65: /* expression: expression LETREC LBRAQ reclist WHERE deflist RBRAQ  */
#line 482 "faustparser.y"
                                                                         { (yyval.exp) = boxWithRecDef((yyvsp[-6].exp),formatDefinitions((yyvsp[-3].exp)),formatDefinitions((yyvsp[-1].exp))); }
#line 2173 "faustparser.cpp"
    break;

  case 66: /* expression: expression PAR expression  */
#line 483 "faustparser.y"
                                                         { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2179 "faustparser.cpp"
    break;

  case 67: /* expression: expression SEQ expression  */
#line 484 "faustparser.y"
                                                         { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2185 "faustparser.cpp"
    break;

  case 68: /* expression: expression SPLIT expression  */
#line 485 "faustparser.y"
                                                         { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2191 "faustparser.cpp"
    break;

  case 69: /* expression: expression MIX expression  */
#line 486 "faustparser.y"
                                                         { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2197 "faustparser.cpp"
    break;

  case 70: /* expression: expression REC expression  */
#line 487 "faustparser.y"
                                                         { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2203 "faustparser.cpp"
    break;

  case 71: /* expression: infixexp  */
#line 488 "faustparser.y"
                                                         { (yyval.exp) = (yyvsp[0].exp); }
#line 2209 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp ADD infixexp  */
#line 491 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxAdd()); }
#line 2215 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp SUB infixexp  */
#line 492 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxSub()); }
#line 2221 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp MUL infixexp  */
#line 493 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxMul()); }
#line 2227 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DIV infixexp  */
#line 494 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxDiv()); }
#line 2233 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp MOD infixexp  */
#line 495 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxRem()); }
#line 2239 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp POWOP infixexp  */
#line 496 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPow()); }
#line 2245 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp FDELAY infixexp  */
#line 497 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxDelay()); }
#line 2251 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp DELAY1  */
#line 498 "faustparser.y"
                                            { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxDelay1()); }
#line 2257 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp DOT ident  */
#line 499 "faustparser.y"
                                            { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2263 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp AND infixexp  */
#line 501 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxAND()); }
#line 2269 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp OR infixexp  */
#line 502 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxOR()); }
#line 2275 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp XOR infixexp  */
#line 503 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxXOR()); }
#line 2281 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp LSH infixexp  */
#line 505 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxLeftShift()); }
#line 2287 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp RSH infixexp  */
#line 506 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxARightShift()); }
#line 2293 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp LT infixexp  */
#line 508 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxLT()); }
#line 2299 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp LE infixexp  */
#line 509 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxLE()); }
#line 2305 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp GT infixexp  */
#line 510 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxGT()); }
#line 2311 "faustparser.cpp"
    break;

  case 89: /* infixexp: infixexp GE infixexp  */
#line 511 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxGE()); }
#line 2317 "faustparser.cpp"
    break;

  case 90: /* infixexp: infixexp EQ infixexp  */
#line 512 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxEQ()); }
#line 2323 "faustparser.cpp"
    break;

  case 91: /* infixexp: infixexp NE infixexp  */
#line 513 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxNE()); }
#line 2329 "faustparser.cpp"
    break;

  case 92: /* infixexp: infixexp LPAR arglist RPAR  */
#line 515 "faustparser.y"
                                                   { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2335 "faustparser.cpp"
    break;

  case 93: /* infixexp: infixexp LCROC deflist RCROC  */
#line 516 "faustparser.y"
                                                   { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2341 "faustparser.cpp"
    break;

  case 94: /* infixexp: primitive  */
#line 518 "faustparser.y"
                                                   { (yyval.exp) = (yyvsp[0].exp); }
#line 2347 "faustparser.cpp"
    break;

  case 95: /* primitive: INT  */
#line 521 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 2353 "faustparser.cpp"
    break;

  case 96: /* primitive: FLOAT  */
#line 522 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2359 "faustparser.cpp"
    break;

  case 97: /* primitive: ADD INT  */
#line 524 "faustparser.y"
                                                { (yyval.exp) = boxInt (str2int(FAUSTtext)); }
#line 2365 "faustparser.cpp"
    break;

  case 98: /* primitive: ADD FLOAT  */
#line 525 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2371 "faustparser.cpp"
    break;

  case 99: /* primitive: SUB INT  */
#line 527 "faustparser.y"
                                                { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); }
#line 2377 "faustparser.cpp"
    break;

  case 100: /* primitive: SUB FLOAT  */
#line 528 "faustparser.y"
                                                { (yyval.exp) = boxReal( -atof(FAUSTtext) ); }
#line 2383 "faustparser.cpp"
    break;

  case 101: /* primitive: WIRE  */
#line 530 "faustparser.y"
                                                { (yyval.exp) = boxWire(); }
#line 2389 "faustparser.cpp"
    break;

  case 102: /* primitive: CUT  */
#line 531 "faustparser.y"
                                                { (yyval.exp) = boxCut(); }
#line 2395 "faustparser.cpp"
    break;

  case 103: /* primitive: MEM  */
#line 533 "faustparser.y"
                                                { (yyval.exp) = boxDelay1(); }
#line 2401 "faustparser.cpp"
    break;

  case 104: /* primitive: PREFIX  */
#line 534 "faustparser.y"
                                                { (yyval.exp) = boxPrefix(); }
#line 2407 "faustparser.cpp"
    break;

  case 105: /* primitive: INTCAST  */
#line 536 "faustparser.y"
                                                { (yyval.exp) = boxIntCast(); }
#line 2413 "faustparser.cpp"
    break;

  case 106: /* primitive: FLOATCAST  */
#line 537 "faustparser.y"
                                                { (yyval.exp) = boxFloatCast(); }
#line 2419 "faustparser.cpp"
    break;

  case 107: /* primitive: ADD  */
#line 539 "faustparser.y"
                                                { (yyval.exp) = boxAdd(); }
#line 2425 "faustparser.cpp"
    break;

  case 108: /* primitive: SUB  */
#line 540 "faustparser.y"
                                                { (yyval.exp) = boxSub(); }
#line 2431 "faustparser.cpp"
    break;

  case 109: /* primitive: MUL  */
#line 541 "faustparser.y"
                                                { (yyval.exp) = boxMul(); }
#line 2437 "faustparser.cpp"
    break;

  case 110: /* primitive: DIV  */
#line 542 "faustparser.y"
                                                { (yyval.exp) = boxDiv(); }
#line 2443 "faustparser.cpp"
    break;

  case 111: /* primitive: MOD  */
#line 543 "faustparser.y"
                                                { (yyval.exp) = boxRem(); }
#line 2449 "faustparser.cpp"
    break;

  case 112: /* primitive: FDELAY  */
#line 544 "faustparser.y"
                                                { (yyval.exp) = boxDelay(); }
#line 2455 "faustparser.cpp"
    break;

  case 113: /* primitive: AND  */
#line 546 "faustparser.y"
                                                { (yyval.exp) = boxAND(); }
#line 2461 "faustparser.cpp"
    break;

  case 114: /* primitive: OR  */
#line 547 "faustparser.y"
                                                { (yyval.exp) = boxOR(); }
#line 2467 "faustparser.cpp"
    break;

  case 115: /* primitive: XOR  */
#line 548 "faustparser.y"
                                                { (yyval.exp) = boxXOR(); }
#line 2473 "faustparser.cpp"
    break;

  case 116: /* primitive: LSH  */
#line 550 "faustparser.y"
                                                { (yyval.exp) = boxLeftShift(); }
#line 2479 "faustparser.cpp"
    break;

  case 117: /* primitive: RSH  */
#line 551 "faustparser.y"
                                                { (yyval.exp) = boxARightShift(); }
#line 2485 "faustparser.cpp"
    break;

  case 118: /* primitive: LT  */
#line 553 "faustparser.y"
                                                { (yyval.exp) = boxLT(); }
#line 2491 "faustparser.cpp"
    break;

  case 119: /* primitive: LE  */
#line 554 "faustparser.y"
                                                { (yyval.exp) = boxLE(); }
#line 2497 "faustparser.cpp"
    break;

  case 120: /* primitive: GT  */
#line 555 "faustparser.y"
                                                { (yyval.exp) = boxGT(); }
#line 2503 "faustparser.cpp"
    break;

  case 121: /* primitive: GE  */
#line 556 "faustparser.y"
                                                { (yyval.exp) = boxGE(); }
#line 2509 "faustparser.cpp"
    break;

  case 122: /* primitive: EQ  */
#line 557 "faustparser.y"
                                                { (yyval.exp) = boxEQ(); }
#line 2515 "faustparser.cpp"
    break;

  case 123: /* primitive: NE  */
#line 558 "faustparser.y"
                                                { (yyval.exp) = boxNE(); }
#line 2521 "faustparser.cpp"
    break;

  case 124: /* primitive: ATTACH  */
#line 560 "faustparser.y"
                                                { (yyval.exp) = boxAttach(); }
#line 2527 "faustparser.cpp"
    break;

  case 125: /* primitive: ENABLE  */
#line 561 "faustparser.y"
                                                { (yyval.exp) = boxEnable(); }
#line 2533 "faustparser.cpp"
    break;

  case 126: /* primitive: CONTROL  */
#line 562 "faustparser.y"
                                                { (yyval.exp) = boxControl(); }
#line 2539 "faustparser.cpp"
    break;

  case 127: /* primitive: ACOS  */
#line 564 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2545 "faustparser.cpp"
    break;

  case 128: /* primitive: ASIN  */
#line 565 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2551 "faustparser.cpp"
    break;

  case 129: /* primitive: ATAN  */
#line 566 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2557 "faustparser.cpp"
    break;

  case 130: /* primitive: ATAN2  */
#line 567 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2563 "faustparser.cpp"
    break;

  case 131: /* primitive: COS  */
#line 568 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2569 "faustparser.cpp"
    break;

  case 132: /* primitive: SIN  */
#line 569 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2575 "faustparser.cpp"
    break;

  case 133: /* primitive: TAN  */
#line 570 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2581 "faustparser.cpp"
    break;

  case 134: /* primitive: EXP  */
#line 572 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2587 "faustparser.cpp"
    break;

  case 135: /* primitive: LOG  */
#line 573 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2593 "faustparser.cpp"
    break;

  case 136: /* primitive: LOG10  */
#line 574 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2599 "faustparser.cpp"
    break;

  case 137: /* primitive: POWOP  */
#line 575 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2605 "faustparser.cpp"
    break;

  case 138: /* primitive: POWFUN  */
#line 576 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2611 "faustparser.cpp"
    break;

  case 139: /* primitive: SQRT  */
#line 577 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2617 "faustparser.cpp"
    break;

  case 140: /* primitive: ABS  */
#line 579 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2623 "faustparser.cpp"
    break;

  case 141: /* primitive: MIN  */
#line 580 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2629 "faustparser.cpp"
    break;

  case 142: /* primitive: MAX  */
#line 581 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2635 "faustparser.cpp"
    break;

  case 143: /* primitive: FMOD  */
#line 583 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2641 "faustparser.cpp"
    break;

  case 144: /* primitive: REMAINDER  */
#line 584 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2647 "faustparser.cpp"
    break;

  case 145: /* primitive: FLOOR  */
#line 586 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2653 "faustparser.cpp"
    break;

  case 146: /* primitive: CEIL  */
#line 587 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2659 "faustparser.cpp"
    break;

  case 147: /* primitive: RINT  */
#line 588 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2665 "faustparser.cpp"
    break;

  case 148: /* primitive: ROUND  */
#line 589 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRoundPrim->box(); }
#line 2671 "faustparser.cpp"
    break;

  case 149: /* primitive: RDTBL  */
#line 591 "faustparser.y"
                                                 { (yyval.exp) = boxReadOnlyTable(); }
#line 2677 "faustparser.cpp"
    break;

  case 150: /* primitive: RWTBL  */
#line 592 "faustparser.y"
                                                 { (yyval.exp) = boxWriteReadTable(); }
#line 2683 "faustparser.cpp"
    break;

  case 151: /* primitive: SELECT2  */
#line 594 "faustparser.y"
                                                 { (yyval.exp) = boxSelect2(); }
#line 2689 "faustparser.cpp"
    break;

  case 152: /* primitive: SELECT3  */
#line 595 "faustparser.y"
                                                 { (yyval.exp) = boxSelect3(); }
#line 2695 "faustparser.cpp"
    break;

  case 153: /* primitive: ASSERTBOUNDS  */
#line 597 "faustparser.y"
                                                 { (yyval.exp) = boxAssertBound(); }
#line 2701 "faustparser.cpp"
    break;

  case 154: /* primitive: LOWEST  */
#line 598 "faustparser.y"
                                                 { (yyval.exp) = boxLowest(); }
#line 2707 "faustparser.cpp"
    break;

  case 155: /* primitive: HIGHEST  */
#line 599 "faustparser.y"
                                                 { (yyval.exp) = boxHighest(); }
#line 2713 "faustparser.cpp"
    break;

  case 156: /* primitive: ident  */
#line 601 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp); setUseProp((yyvsp[0].exp), FAUSTfilename, FAUSTlineno);}
#line 2719 "faustparser.cpp"
    break;

  case 157: /* primitive: SUB ident  */
#line 602 "faustparser.y"
                                                 { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxSub()); }
#line 2725 "faustparser.cpp"
    break;

  case 158: /* primitive: LPAR expression RPAR  */
#line 604 "faustparser.y"
                                                  { (yyval.exp) = (yyvsp[-1].exp); }
#line 2731 "faustparser.cpp"
    break;

  case 159: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 606 "faustparser.y"
                                                  { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2737 "faustparser.cpp"
    break;

  case 160: /* primitive: LCROC modlist LAPPLY expression RCROC  */
#line 612 "faustparser.y"
                                                  { (yyval.exp) = buildBoxModulation((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2743 "faustparser.cpp"
    break;

  case 161: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 614 "faustparser.y"
                                                { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2749 "faustparser.cpp"
    break;

  case 162: /* primitive: ffunction  */
#line 616 "faustparser.y"
                                                { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2755 "faustparser.cpp"
    break;

  case 163: /* primitive: fconst  */
#line 617 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2761 "faustparser.cpp"
    break;

  case 164: /* primitive: fvariable  */
#line 618 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2767 "faustparser.cpp"
    break;

  case 165: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 619 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2773 "faustparser.cpp"
    break;

  case 166: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 620 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2779 "faustparser.cpp"
    break;

  case 167: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 621 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2785 "faustparser.cpp"
    break;

  case 168: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 622 "faustparser.y"
                                                   { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2791 "faustparser.cpp"
    break;

  case 169: /* primitive: ROUTE LPAR argument PAR argument RPAR  */
#line 623 "faustparser.y"
                                                              { (yyval.exp) = boxRoute((yyvsp[-3].exp), (yyvsp[-1].exp), boxPar(boxInt(0),boxInt(0))); }
#line 2797 "faustparser.cpp"
    break;

  case 170: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 624 "faustparser.y"
                                                                             { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2803 "faustparser.cpp"
    break;

  case 171: /* primitive: button  */
#line 625 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2809 "faustparser.cpp"
    break;

  case 172: /* primitive: checkbox  */
#line 626 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2815 "faustparser.cpp"
    break;

  case 173: /* primitive: vslider  */
#line 627 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2821 "faustparser.cpp"
    break;

  case 174: /* primitive: hslider  */
#line 628 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2827 "faustparser.cpp"
    break;

  case 175: /* primitive: nentry  */
#line 629 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2833 "faustparser.cpp"
    break;

  case 176: /* primitive: vgroup  */
#line 630 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2839 "faustparser.cpp"
    break;

  case 177: /* primitive: hgroup  */
#line 631 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2845 "faustparser.cpp"
    break;

  case 178: /* primitive: tgroup  */
#line 632 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2851 "faustparser.cpp"
    break;

  case 179: /* primitive: vbargraph  */
#line 633 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2857 "faustparser.cpp"
    break;

  case 180: /* primitive: hbargraph  */
#line 634 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2863 "faustparser.cpp"
    break;

  case 181: /* primitive: soundfile  */
#line 635 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2869 "faustparser.cpp"
    break;

  case 182: /* primitive: fpar  */
#line 637 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2875 "faustparser.cpp"
    break;

  case 183: /* primitive: fseq  */
#line 638 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2881 "faustparser.cpp"
    break;

  case 184: /* primitive: fsum  */
#line 639 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2887 "faustparser.cpp"
    break;

  case 185: /* primitive: fprod  */
#line 640 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2893 "faustparser.cpp"
    break;

  case 186: /* primitive: finputs  */
#line 642 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2899 "faustparser.cpp"
    break;

  case 187: /* primitive: foutputs  */
#line 643 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2905 "faustparser.cpp"
    break;

  case 188: /* primitive: fondemand  */
#line 644 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2911 "faustparser.cpp"
    break;

  case 189: /* ident: IDENT  */
#line 647 "faustparser.y"
                                                { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2917 "faustparser.cpp"
    break;

  case 190: /* name: IDENT  */
#line 650 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2923 "faustparser.cpp"
    break;

  case 191: /* arglist: argument  */
#line 653 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2929 "faustparser.cpp"
    break;

  case 192: /* arglist: arglist PAR argument  */
#line 654 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2935 "faustparser.cpp"
    break;

  case 193: /* argument: argument SEQ argument  */
#line 657 "faustparser.y"
                                                 { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2941 "faustparser.cpp"
    break;

  case 194: /* argument: argument SPLIT argument  */
#line 658 "faustparser.y"
                                                 { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2947 "faustparser.cpp"
    break;

  case 195: /* argument: argument MIX argument  */
#line 659 "faustparser.y"
                                                 { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2953 "faustparser.cpp"
    break;

  case 196: /* argument: argument REC argument  */
#line 660 "faustparser.y"
                                                 { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2959 "faustparser.cpp"
    break;

  case 197: /* argument: infixexp  */
#line 661 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp); }
#line 2965 "faustparser.cpp"
    break;

  case 198: /* string: STRING  */
#line 664 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2971 "faustparser.cpp"
    break;

  case 199: /* uqstring: STRING  */
#line 667 "faustparser.y"
                                                 { (yyval.exp) = unquote(FAUSTtext); }
#line 2977 "faustparser.cpp"
    break;

  case 200: /* fstring: STRING  */
#line 670 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2983 "faustparser.cpp"
    break;

  case 201: /* fstring: FSTRING  */
#line 671 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2989 "faustparser.cpp"
    break;

  case 202: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 677 "faustparser.y"
                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2995 "faustparser.cpp"
    break;

  case 203: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 681 "faustparser.y"
                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3001 "faustparser.cpp"
    break;

  case 204: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 685 "faustparser.y"
                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3007 "faustparser.cpp"
    break;

  case 205: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 689 "faustparser.y"
                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3013 "faustparser.cpp"
    break;

  case 206: /* finputs: INPUTS LPAR expression RPAR  */
#line 692 "faustparser.y"
                                              { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 3019 "faustparser.cpp"
    break;

  case 207: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 695 "faustparser.y"
                                               { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 3025 "faustparser.cpp"
    break;

  case 208: /* fondemand: ONDEMAND LPAR expression RPAR  */
#line 698 "faustparser.y"
                                                { (yyval.exp) = boxOndemand((yyvsp[-1].exp)); }
#line 3031 "faustparser.cpp"
    break;

  case 209: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 704 "faustparser.y"
                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3037 "faustparser.cpp"
    break;

  case 210: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 708 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3043 "faustparser.cpp"
    break;

  case 211: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 712 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3049 "faustparser.cpp"
    break;

  case 212: /* button: BUTTON LPAR uqstring RPAR  */
#line 716 "faustparser.y"
                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3055 "faustparser.cpp"
    break;

  case 213: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 719 "faustparser.y"
                                                 { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3061 "faustparser.cpp"
    break;

  case 214: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 723 "faustparser.y"
                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3067 "faustparser.cpp"
    break;

  case 215: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 726 "faustparser.y"
                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3073 "faustparser.cpp"
    break;

  case 216: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 729 "faustparser.y"
                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3079 "faustparser.cpp"
    break;

  case 217: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 732 "faustparser.y"
                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3085 "faustparser.cpp"
    break;

  case 218: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 735 "faustparser.y"
                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3091 "faustparser.cpp"
    break;

  case 219: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 738 "faustparser.y"
                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3097 "faustparser.cpp"
    break;

  case 220: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 742 "faustparser.y"
                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3103 "faustparser.cpp"
    break;

  case 221: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 745 "faustparser.y"
                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3109 "faustparser.cpp"
    break;

  case 222: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 748 "faustparser.y"
                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3115 "faustparser.cpp"
    break;

  case 223: /* signature: type fun LPAR typelist RPAR  */
#line 754 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-4].exp),cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3121 "faustparser.cpp"
    break;

  case 224: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 755 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3127 "faustparser.cpp"
    break;

  case 225: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 756 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-8].exp),cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3133 "faustparser.cpp"
    break;

  case 226: /* signature: type fun OR fun OR fun OR fun LPAR typelist RPAR  */
#line 757 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-10].exp),cons(cons((yyvsp[-9].exp),cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3139 "faustparser.cpp"
    break;

  case 227: /* signature: type fun LPAR RPAR  */
#line 759 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3145 "faustparser.cpp"
    break;

  case 228: /* signature: type fun OR fun LPAR RPAR  */
#line 760 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-5].exp),cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3151 "faustparser.cpp"
    break;

  case 229: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 761 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-7].exp),cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3157 "faustparser.cpp"
    break;

  case 230: /* signature: type fun OR fun OR fun OR fun LPAR RPAR  */
#line 762 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-9].exp),cons(cons((yyvsp[-8].exp),cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3163 "faustparser.cpp"
    break;

  case 231: /* fun: IDENT  */
#line 765 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); }
#line 3169 "faustparser.cpp"
    break;

  case 232: /* typelist: argtype  */
#line 768 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3175 "faustparser.cpp"
    break;

  case 233: /* typelist: typelist PAR argtype  */
#line 769 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3181 "faustparser.cpp"
    break;

  case 234: /* rulelist: rule  */
#line 772 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3187 "faustparser.cpp"
    break;

  case 235: /* rulelist: rulelist rule  */
#line 773 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3193 "faustparser.cpp"
    break;

  case 236: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 777 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3199 "faustparser.cpp"
    break;

  case 237: /* type: INTCAST  */
#line 780 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3205 "faustparser.cpp"
    break;

  case 238: /* type: FLOATCAST  */
#line 781 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3211 "faustparser.cpp"
    break;

  case 239: /* argtype: INTCAST  */
#line 784 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3217 "faustparser.cpp"
    break;

  case 240: /* argtype: FLOATCAST  */
#line 785 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3223 "faustparser.cpp"
    break;

  case 241: /* argtype: NOTYPECAST  */
#line 786 "faustparser.y"
                                                { (yyval.exp) = tree(2); }
#line 3229 "faustparser.cpp"
    break;


#line 3233 "faustparser.cpp"

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

#line 789 "faustparser.y"

