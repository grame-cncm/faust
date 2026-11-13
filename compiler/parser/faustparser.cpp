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
  YYSYMBOL_ONDEMAND = 98,                  /* ONDEMAND  */
  YYSYMBOL_UPSAMPLING = 99,                /* UPSAMPLING  */
  YYSYMBOL_DOWNSAMPLING = 100,             /* DOWNSAMPLING  */
  YYSYMBOL_ENABLE = 101,                   /* ENABLE  */
  YYSYMBOL_CONTROL = 102,                  /* CONTROL  */
  YYSYMBOL_IPAR = 103,                     /* IPAR  */
  YYSYMBOL_ISEQ = 104,                     /* ISEQ  */
  YYSYMBOL_ISUM = 105,                     /* ISUM  */
  YYSYMBOL_IPROD = 106,                    /* IPROD  */
  YYSYMBOL_INPUTS = 107,                   /* INPUTS  */
  YYSYMBOL_OUTPUTS = 108,                  /* OUTPUTS  */
  YYSYMBOL_STRING = 109,                   /* STRING  */
  YYSYMBOL_FSTRING = 110,                  /* FSTRING  */
  YYSYMBOL_IDENT = 111,                    /* IDENT  */
  YYSYMBOL_EXTRA = 112,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 113,                  /* DECLARE  */
  YYSYMBOL_CASE = 114,                     /* CASE  */
  YYSYMBOL_ARROW = 115,                    /* ARROW  */
  YYSYMBOL_ASSERTBOUNDS = 116,             /* ASSERTBOUNDS  */
  YYSYMBOL_LOWEST = 117,                   /* LOWEST  */
  YYSYMBOL_HIGHEST = 118,                  /* HIGHEST  */
  YYSYMBOL_FLOATMODE = 119,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 120,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 121,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 122,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 123,                     /* BDOC  */
  YYSYMBOL_EDOC = 124,                     /* EDOC  */
  YYSYMBOL_BEQN = 125,                     /* BEQN  */
  YYSYMBOL_EEQN = 126,                     /* EEQN  */
  YYSYMBOL_BDGM = 127,                     /* BDGM  */
  YYSYMBOL_EDGM = 128,                     /* EDGM  */
  YYSYMBOL_BLST = 129,                     /* BLST  */
  YYSYMBOL_ELST = 130,                     /* ELST  */
  YYSYMBOL_BMETADATA = 131,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 132,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 133,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 134,                   /* NOTICE  */
  YYSYMBOL_LISTING = 135,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 136,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 137,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 138,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 139,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 140,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 141,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 142,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 143,                 /* $accept  */
  YYSYMBOL_program = 144,                  /* program  */
  YYSYMBOL_stmtlist = 145,                 /* stmtlist  */
  YYSYMBOL_deflist = 146,                  /* deflist  */
  YYSYMBOL_variantlist = 147,              /* variantlist  */
  YYSYMBOL_variant = 148,                  /* variant  */
  YYSYMBOL_reclist = 149,                  /* reclist  */
  YYSYMBOL_vallist = 150,                  /* vallist  */
  YYSYMBOL_number = 151,                   /* number  */
  YYSYMBOL_statement = 152,                /* statement  */
  YYSYMBOL_doc = 153,                      /* doc  */
  YYSYMBOL_docelem = 154,                  /* docelem  */
  YYSYMBOL_doctxt = 155,                   /* doctxt  */
  YYSYMBOL_doceqn = 156,                   /* doceqn  */
  YYSYMBOL_docdgm = 157,                   /* docdgm  */
  YYSYMBOL_docntc = 158,                   /* docntc  */
  YYSYMBOL_doclst = 159,                   /* doclst  */
  YYSYMBOL_lstattrlist = 160,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 161,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 162,               /* lstattrval  */
  YYSYMBOL_docmtd = 163,                   /* docmtd  */
  YYSYMBOL_definition = 164,               /* definition  */
  YYSYMBOL_recinition = 165,               /* recinition  */
  YYSYMBOL_defname = 166,                  /* defname  */
  YYSYMBOL_recname = 167,                  /* recname  */
  YYSYMBOL_params = 168,                   /* params  */
  YYSYMBOL_modentry = 169,                 /* modentry  */
  YYSYMBOL_modlist = 170,                  /* modlist  */
  YYSYMBOL_expression = 171,               /* expression  */
  YYSYMBOL_infixexp = 172,                 /* infixexp  */
  YYSYMBOL_primitive = 173,                /* primitive  */
  YYSYMBOL_ident = 174,                    /* ident  */
  YYSYMBOL_name = 175,                     /* name  */
  YYSYMBOL_arglist = 176,                  /* arglist  */
  YYSYMBOL_argument = 177,                 /* argument  */
  YYSYMBOL_string = 178,                   /* string  */
  YYSYMBOL_uqstring = 179,                 /* uqstring  */
  YYSYMBOL_fstring = 180,                  /* fstring  */
  YYSYMBOL_fpar = 181,                     /* fpar  */
  YYSYMBOL_fseq = 182,                     /* fseq  */
  YYSYMBOL_fsum = 183,                     /* fsum  */
  YYSYMBOL_fprod = 184,                    /* fprod  */
  YYSYMBOL_finputs = 185,                  /* finputs  */
  YYSYMBOL_foutputs = 186,                 /* foutputs  */
  YYSYMBOL_ffunction = 187,                /* ffunction  */
  YYSYMBOL_fconst = 188,                   /* fconst  */
  YYSYMBOL_fvariable = 189,                /* fvariable  */
  YYSYMBOL_button = 190,                   /* button  */
  YYSYMBOL_checkbox = 191,                 /* checkbox  */
  YYSYMBOL_vslider = 192,                  /* vslider  */
  YYSYMBOL_hslider = 193,                  /* hslider  */
  YYSYMBOL_nentry = 194,                   /* nentry  */
  YYSYMBOL_vgroup = 195,                   /* vgroup  */
  YYSYMBOL_hgroup = 196,                   /* hgroup  */
  YYSYMBOL_tgroup = 197,                   /* tgroup  */
  YYSYMBOL_vbargraph = 198,                /* vbargraph  */
  YYSYMBOL_hbargraph = 199,                /* hbargraph  */
  YYSYMBOL_soundfile = 200,                /* soundfile  */
  YYSYMBOL_signature = 201,                /* signature  */
  YYSYMBOL_fun = 202,                      /* fun  */
  YYSYMBOL_typelist = 203,                 /* typelist  */
  YYSYMBOL_rulelist = 204,                 /* rulelist  */
  YYSYMBOL_rule = 205,                     /* rule  */
  YYSYMBOL_type = 206,                     /* type  */
  YYSYMBOL_argtype = 207                   /* argtype  */
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
#define YYLAST   829

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  143
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  242
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  523

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   397


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
     135,   136,   137,   138,   139,   140,   141,   142
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   362,   362,   365,   366,   369,   370,   373,   374,   377,
     378,   379,   380,   383,   384,   391,   392,   395,   396,   397,
     398,   399,   400,   403,   404,   405,   406,   407,   410,   411,
     414,   415,   416,   417,   418,   419,   422,   423,   426,   429,
     432,   435,   438,   439,   442,   443,   444,   447,   448,   451,
     454,   455,   456,   459,   460,   463,   466,   469,   470,   473,
     474,   477,   478,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   502,   503,   504,   506,   507,   509,   510,   511,   512,
     513,   514,   516,   517,   519,   522,   523,   525,   526,   528,
     529,   531,   532,   534,   535,   537,   538,   540,   541,   542,
     543,   544,   545,   547,   548,   549,   551,   552,   554,   555,
     556,   557,   558,   559,   561,   562,   563,   565,   566,   567,
     568,   569,   570,   571,   573,   574,   575,   576,   577,   578,
     580,   581,   582,   584,   585,   587,   588,   589,   590,   592,
     593,   595,   596,   598,   599,   600,   602,   603,   605,   606,
     612,   615,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   641,   642,   643,   644,   646,
     647,   650,   653,   656,   657,   660,   661,   662,   663,   664,
     667,   670,   673,   674,   679,   683,   687,   691,   695,   698,
     703,   707,   711,   716,   719,   722,   725,   728,   731,   734,
     737,   741,   744,   747,   754,   755,   756,   757,   759,   760,
     761,   762,   765,   768,   769,   772,   773,   776,   780,   781,
     784,   785,   786
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
  "ROUTE", "ONDEMAND", "UPSAMPLING", "DOWNSAMPLING", "ENABLE", "CONTROL",
  "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING",
  "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "ASSERTBOUNDS",
  "LOWEST", "HIGHEST", "FLOATMODE", "DOUBLEMODE", "QUADMODE",
  "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST",
  "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE", "LISTING",
  "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
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

#define YYPACT_NINF (-385)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -385,    24,    51,  -385,     4,   -21,    20,  -385,   -27,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,   -31,  -385,  -385,
     -14,  -385,   -24,   314,   453,   453,  -385,    26,  -385,    48,
      33,  -385,   453,   453,  -385,   -27,  -385,  -385,    70,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
     203,   -59,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,    90,   128,   134,   145,
     185,   215,   238,   266,   288,   291,   312,   317,   333,   337,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   339,  -385,
    -385,   453,   -14,   342,   350,   228,   298,   352,   359,   363,
     378,  -385,  -385,   403,   446,   448,   454,   455,   456,   301,
    -385,  -385,  -385,   617,  -385,  -385,    25,   370,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,    34,   617,
     372,   465,  -385,    23,    12,   164,   297,  -385,  -385,  -385,
    -385,  -385,  -385,    47,    47,    47,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   434,    50,  -385,
      14,   557,   -14,   -14,  -385,   133,   453,   453,   453,   453,
     434,   434,   434,   434,   453,   453,   482,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,  -385,   434,   453,  -385,   453,
     475,   453,   453,   453,   453,   453,   453,   453,   453,   453,
    -385,   483,   485,  -385,  -385,  -385,  -385,  -385,   436,   437,
     443,  -385,  -385,  -385,  -385,   579,   480,   -27,   -27,   510,
     516,   593,   599,   600,   611,   613,   614,   615,   616,   643,
      27,  -385,  -385,   -14,   453,   453,   528,   533,   566,   212,
     242,  -385,  -385,     5,  -385,   641,    57,   218,   225,   646,
     647,   648,   649,   250,   276,   453,   -15,  -385,   689,   689,
     689,   689,   689,   689,   699,   699,   699,   361,   361,   361,
     361,   361,   361,   361,   334,   307,  -385,    36,   573,   370,
     453,   370,   370,   303,  -385,   723,   723,   263,   329,  -385,
    -385,  -385,   518,   519,   520,   247,  -385,    -6,   660,   661,
    -385,  -385,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   434,   592,  -385,    42,   370,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,   133,  -385,   453,  -385,  -385,  -385,   453,
     453,   453,   453,  -385,  -385,    37,  -385,  -385,  -385,  -385,
      31,    67,   585,     8,   280,   280,   280,  -385,  -385,   667,
     480,   234,   247,   247,   728,   733,   738,   283,   321,   348,
     743,   748,    99,  -385,   594,  -385,  -385,    76,   753,   782,
     787,   792,   559,  -385,  -385,  -385,   601,   434,  -385,  -385,
    -385,   586,  -385,  -385,   539,   540,   541,    48,     7,  -385,
    -385,  -385,  -385,    38,  -385,   605,   606,   453,   453,   453,
    -385,  -385,  -385,   453,   453,  -385,   453,   453,  -385,   453,
     453,   453,   453,   453,  -385,  -385,   608,   453,  -385,  -385,
    -385,   607,   480,   262,   300,  -385,  -385,  -385,   797,   802,
     807,   294,   375,   536,   569,   576,   583,   590,   597,   230,
    -385,   255,  -385,    75,  -385,    59,  -385,   453,   453,   453,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
     480,   365,  -385,   812,   817,   822,   618,  -385,    61,   453,
     453,   453,   376,  -385,   397,   604,   609,  -385,    88,  -385,
    -385,  -385,  -385
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   191,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   192,     0,    36,     0,     0,   201,     0,   200,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   118,   119,   122,   120,   121,   123,
     107,   108,   114,   109,   110,   111,   113,   115,   116,   117,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,   199,    94,   156,     0,   193,   185,   186,
     187,   188,   189,   190,   162,   163,   164,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,     0,    71,
       0,     0,    24,     0,     0,     0,     0,    37,    97,    98,
      99,   100,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,    59,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,    23,    25,    38,    39,    41,     0,     0,
       0,    43,    49,   238,   239,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,   158,     0,     0,     0,     0,     0,     7,     0,
       0,    17,    18,     0,    15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   235,    86,    87,
      90,    88,    89,    91,    72,    73,    82,    74,    75,    76,
      81,    83,    84,    85,    77,    78,    80,     0,     7,   194,
       0,   196,   197,   195,   198,    68,    69,    67,    66,    70,
       5,    13,     0,     0,     0,     0,   232,     0,     0,     0,
     213,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,    60,   165,   166,   167,    19,
      20,    21,    22,     0,   168,     0,   171,   172,   173,     0,
       0,     0,     0,   208,   209,     0,   161,   236,    92,    93,
       0,     0,     7,     0,     0,     0,     0,   202,   203,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,   160,    16,     0,     0,     0,
       0,     0,     0,     6,    50,    63,     0,     0,    64,     5,
      14,     0,    47,    48,     0,     0,     0,     0,     0,   240,
     241,   242,   228,     0,   233,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   223,     0,     0,   169,     0,
       0,     0,     0,     0,    54,    56,     7,     0,    44,    45,
      46,     0,     0,     0,     0,   224,   211,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,   210,     0,   229,     0,   234,     0,     0,     0,
     222,   221,   159,   170,   204,   205,   206,   207,   237,    53,
       0,     0,   225,     0,     0,     0,     0,   230,     0,     0,
       0,     0,     0,   226,     0,     0,     0,   231,     0,   215,
     216,   217,   227
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -385,  -385,   496,  -326,     0,  -385,  -385,  -385,   331,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   -19,
    -385,   315,  -385,  -385,  -385,  -385,   423,  -385,     3,   -25,
    -385,    17,   -10,  -205,   -98,   -28,   -17,   140,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -384,
    -285,  -385,   401,   187,   236
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   318,   380,    14,   383,   283,   284,    15,
      23,    37,    38,    39,    40,    41,    42,   165,   251,   424,
      43,    16,   420,    17,   421,   270,   189,   190,   158,   133,
     134,   135,    22,   136,   137,    30,   191,   389,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   255,   337,
     433,   296,   297,   256,   434
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     159,   161,     4,    27,   382,     5,   428,   159,   159,   416,
     390,   363,    29,   170,   171,   235,   236,   237,   238,   239,
     273,    18,   317,   462,     3,   166,   235,   236,   237,   238,
     239,   229,     5,   351,   417,   163,   164,   235,   236,   237,
     238,   239,   229,   229,   464,   235,   236,   237,   238,   239,
      24,    -2,     7,   235,   236,   237,   238,   239,    19,    25,
     235,   236,   237,   238,   239,   464,   295,   464,   172,   376,
     235,   236,   237,   238,   239,   391,   253,   254,   483,   231,
     232,   233,   447,   234,    21,    28,   159,    21,   463,   364,
     375,   500,   418,   456,   464,    26,     6,   419,   285,   241,
     242,    20,   231,   232,   233,   274,   234,   230,   160,   352,
     241,   242,   162,   240,   188,     7,   506,     8,   378,   412,
     465,   241,   242,     9,    10,    11,    12,    13,   405,   241,
     242,   319,   272,   321,   322,   323,   324,   241,   242,   366,
     246,   502,     7,   513,   241,   242,   414,   279,   280,   245,
       9,    10,    11,    12,   241,   242,   501,    28,   448,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     522,   173,   159,   159,   159,   276,   277,   355,   485,   159,
     159,   445,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     286,   287,   288,   167,   271,   281,   282,   293,   294,   174,
     159,   159,   159,   159,   159,   175,   508,   289,   290,   291,
     292,   235,   236,   237,   238,   239,   176,   518,   235,   236,
     237,   238,   239,   235,   236,   237,   238,   239,   325,   326,
     327,   328,   329,   316,   394,   395,   396,   338,   339,   159,
     400,   401,   402,   235,   236,   237,   238,   239,   235,   236,
     237,   238,   239,   429,   430,   431,   177,   407,   237,   238,
     239,   408,   409,   410,   411,   168,   169,   354,     4,   235,
     236,   237,   238,   239,   359,   360,   235,   236,   237,   238,
     239,   429,   430,   431,   247,   159,   178,   231,   232,   233,
     367,   234,   248,   249,   250,   241,   242,   368,   233,   498,
     234,   194,   241,   242,   361,   362,   432,   241,   242,   179,
     159,   159,   159,   381,   235,   236,   237,   238,   239,   429,
     430,   431,   373,   225,   499,   238,   239,   241,   242,   468,
     469,   470,   241,   242,   484,   471,   472,   180,   397,   398,
     399,   235,   236,   237,   238,   239,   387,   388,   374,   224,
     225,   257,   258,   241,   242,   440,   425,   426,   403,   181,
     241,   242,   182,   231,   232,   233,   490,   234,   231,   232,
     233,   195,   234,   226,   206,   223,   224,   225,   227,   503,
     504,   505,   228,   183,   429,   430,   431,    18,   184,   461,
     231,   232,   233,   441,   234,   429,   430,   431,   241,   242,
     226,   514,   515,   516,   185,   227,   422,   423,   186,   228,
     187,   159,   159,   192,   159,   159,   159,   159,   159,   252,
     442,   193,   159,   196,   455,   241,   242,   226,    31,    32,
     197,    33,   227,    34,   198,    35,   228,   507,    36,   473,
     474,   243,   475,   476,   477,   478,   479,   491,   517,   199,
     481,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   519,
      62,    63,    64,    65,   200,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   201,   108,   202,
     109,   110,   435,   436,   111,   203,   204,   205,   112,   235,
     236,   237,   238,   239,   244,     7,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   275,   295,     7,   320,   330,   129,   331,   130,
     131,   132,   235,   236,   237,   238,   239,   332,   333,   235,
     236,   237,   238,   239,   334,   335,   235,   236,   237,   238,
     239,   336,   340,   235,   236,   237,   238,   239,   341,   342,
     235,   236,   237,   238,   239,   343,   344,   231,   232,   233,
     356,   234,   231,   232,   233,   357,   234,   345,   492,   346,
     347,   348,   349,   241,   242,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   231,   232,   233,   365,   234,   350,
     358,   493,   369,   370,   371,   372,   241,   242,   494,   379,
     384,   385,   386,   241,   242,   495,   392,   393,   404,   415,
     241,   242,   496,   427,   453,   446,   457,   241,   242,   497,
     454,   458,   459,   460,   241,   242,   520,   466,   467,   482,
     278,   521,   480,   226,   406,   413,   353,   377,   227,   512,
     486,     0,   228,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   235,   236,   237,   238,
     239,   231,   232,   233,   437,   234,   231,   232,   233,   438,
     234,   231,   232,   233,   439,   234,   231,   232,   233,   443,
     234,   231,   232,   233,   444,   234,   231,   232,   233,   449,
     234,     0,     0,     0,     0,   226,     0,     0,     0,     0,
     227,     0,     0,     0,   228,   226,     0,     0,     0,     0,
     227,     0,     0,     0,   228,   231,   232,   233,   450,   234,
     231,   232,   233,   451,   234,   231,   232,   233,   452,   234,
     231,   232,   233,   487,   234,   231,   232,   233,   488,   234,
     231,   232,   233,   489,   234,   231,   232,   233,   509,   234,
     231,   232,   233,   510,   234,   231,   232,   233,   511,   234
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,    20,   330,     1,   390,    32,    33,     1,
      16,     6,    22,    72,    73,     3,     4,     5,     6,     7,
       6,     4,   227,    16,     0,    35,     3,     4,     5,     6,
       7,     6,     1,     6,    26,    32,    33,     3,     4,     5,
       6,     7,     6,     6,     6,     3,     4,     5,     6,     7,
      81,     0,   111,     3,     4,     5,     6,     7,    79,    90,
       3,     4,     5,     6,     7,     6,    81,     6,    51,    84,
       3,     4,     5,     6,     7,    81,    29,    30,   462,     3,
       4,     5,     6,     7,   111,   109,   111,   111,    81,    84,
     295,    16,    84,   419,     6,   109,    92,    89,   196,    87,
      88,    81,     3,     4,     5,    91,     7,    82,    82,    82,
      87,    88,    79,    79,   111,   111,   500,   113,    82,    82,
      82,    87,    88,   119,   120,   121,   122,   123,    86,    87,
      88,   229,    82,   231,   232,   233,   234,    87,    88,    82,
     128,    82,   111,    82,    87,    88,    79,    14,    15,   126,
     119,   120,   121,   122,    87,    88,    81,   109,    82,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
      82,    81,   197,   198,   199,   192,   193,   275,   463,   204,
     205,    82,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     197,   198,   199,   133,   187,    72,    73,   204,   205,    81,
     235,   236,   237,   238,   239,    81,   501,   200,   201,   202,
     203,     3,     4,     5,     6,     7,    81,   512,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,   235,   236,
     237,   238,   239,   226,   342,   343,   344,   257,   258,   274,
     348,   349,   350,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    29,    30,    31,    81,   365,     5,     6,
       7,   369,   370,   371,   372,    72,    73,   274,   278,     3,
       4,     5,     6,     7,    72,    73,     3,     4,     5,     6,
       7,    29,    30,    31,   130,   320,    81,     3,     4,     5,
      82,     7,   138,   139,   140,    87,    88,    82,     5,    79,
       7,    83,    87,    88,    72,    73,    82,    87,    88,    81,
     345,   346,   347,   320,     3,     4,     5,     6,     7,    29,
      30,    31,    82,    26,    79,     6,     7,    87,    88,   437,
     438,   439,    87,    88,    82,   443,   444,    81,   345,   346,
     347,     3,     4,     5,     6,     7,   109,   110,    82,    25,
      26,   174,   175,    87,    88,    82,   385,   386,   351,    81,
      87,    88,    81,     3,     4,     5,    82,     7,     3,     4,
       5,    83,     7,    76,    83,    24,    25,    26,    81,   487,
     488,   489,    85,    81,    29,    30,    31,   380,    81,   427,
       3,     4,     5,    82,     7,    29,    30,    31,    87,    88,
      76,   509,   510,   511,    81,    81,   136,   137,    81,    85,
      81,   446,   447,    81,   449,   450,   451,   452,   453,   132,
      82,    81,   457,    81,   417,    87,    88,    76,   124,   125,
      81,   127,    81,   129,    81,   131,    85,    82,   134,   446,
     447,    79,   449,   450,   451,   452,   453,    82,    82,    81,
     457,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    82,
      27,    28,    29,    30,    81,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    81,    75,    81,
      77,    78,   392,   393,    81,    81,    81,    81,    85,     3,
       4,     5,     6,     7,    79,   111,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,     5,    81,   111,    90,    83,   114,    83,   116,
     117,   118,     3,     4,     5,     6,     7,   141,   141,     3,
       4,     5,     6,     7,   141,     6,     3,     4,     5,     6,
       7,   111,    82,     3,     4,     5,     6,     7,    82,     6,
       3,     4,     5,     6,     7,     6,     6,     3,     4,     5,
      82,     7,     3,     4,     5,    82,     7,     6,    82,     6,
       6,     6,     6,    87,    88,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     3,     4,     5,     6,     7,     6,
      84,    82,     6,     6,     6,     6,    87,    88,    82,    86,
     142,   142,   142,    87,    88,    82,     6,     6,    76,    84,
      87,    88,    82,     6,   115,    81,    90,    87,    88,    82,
      79,   142,   142,   142,    87,    88,    82,    82,    82,    82,
     194,    82,    84,    76,   363,   380,   273,   296,    81,    81,
     464,    -1,    85,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    76,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   144,   145,     0,   147,     1,    92,   111,   113,   119,
     120,   121,   122,   123,   148,   152,   164,   166,   174,    79,
      81,   111,   175,   153,    81,    90,   109,   179,   109,   175,
     178,   124,   125,   127,   129,   131,   134,   154,   155,   156,
     157,   158,   159,   163,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    77,
      78,    81,    85,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   114,
     116,   117,   118,   172,   173,   174,   176,   177,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   171,   172,
      82,   178,    79,   171,   171,   160,   175,   133,    72,    73,
      72,    73,   174,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,   171,   169,
     170,   179,    81,    81,    83,    83,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    83,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    76,    81,    85,     6,
      82,     3,     4,     5,     7,     3,     4,     5,     6,     7,
      79,    87,    88,    79,    79,   126,   128,   130,   138,   139,
     140,   161,   132,    29,    30,   201,   206,   206,   206,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     168,   174,    82,     6,    91,     5,   179,   179,   145,    14,
      15,    72,    73,   150,   151,   177,   171,   171,   171,   174,
     174,   174,   174,   171,   171,    81,   204,   205,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   174,   176,   146,   177,
      90,   177,   177,   177,   177,   171,   171,   171,   171,   171,
      83,    83,   141,   141,   141,     6,   111,   202,   175,   175,
      82,    82,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,    82,   169,   171,   177,    82,    82,    84,    72,
      73,    72,    73,     6,    84,     6,    82,    82,    82,     6,
       6,     6,     6,    82,    82,   176,    84,   205,    82,    86,
     147,   171,   146,   149,   142,   142,   142,   109,   110,   180,
      16,    81,     6,     6,   177,   177,   177,   171,   171,   171,
     177,   177,   177,   174,    76,    86,   151,   177,   177,   177,
     177,   177,    82,   164,    79,    84,     1,    26,    84,    89,
     165,   167,   136,   137,   162,   162,   162,     6,   202,    29,
      30,    31,    82,   203,   207,   180,   180,     6,     6,     6,
      82,    82,    82,     6,     6,    82,    81,     6,    82,     6,
       6,     6,     6,   115,    79,   174,   146,    90,   142,   142,
     142,   178,    16,    81,     6,    82,    82,    82,   177,   177,
     177,   177,   177,   171,   171,   171,   171,   171,   171,   171,
      84,   171,    82,   202,    82,   203,   207,     6,     6,     6,
      82,    82,    82,    82,    82,    82,    82,    82,    79,    79,
      16,    81,    82,   177,   177,   177,   202,    82,   203,     6,
       6,     6,    81,    82,   177,   177,   177,    82,   203,    82,
      82,    82,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   143,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   148,   148,   149,   149,   150,   150,   151,   151,   151,
     151,   151,   151,   152,   152,   152,   152,   152,   153,   153,
     154,   154,   154,   154,   154,   154,   155,   155,   156,   157,
     158,   159,   160,   160,   161,   161,   161,   162,   162,   163,
     164,   164,   164,   165,   165,   166,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   174,   175,   176,   176,   177,   177,   177,   177,   177,
     178,   179,   180,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   201,   201,   201,   201,   201,
     201,   201,   202,   203,   203,   204,   204,   205,   206,   206,
     207,   207,   207
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
       8,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       8,     7,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     6,     5,     7,     9,    11,     4,     6,
       8,    10,     1,     1,     3,     1,     2,     6,     1,     1,
       1,     1,     1
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
#line 362 "faustparser.y"
                                                    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1803 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 365 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1809 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 366 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1815 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 369 "faustparser.y"
                                                    { (yyval.exp) = gGlobal->nil; }
#line 1821 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 370 "faustparser.y"
                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1827 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 373 "faustparser.y"
                                                    { (yyval.numvariant) = 0; }
#line 1833 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 374 "faustparser.y"
                                                    { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1839 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 377 "faustparser.y"
                                                    { (yyval.numvariant) = 1;}
#line 1845 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 378 "faustparser.y"
                                                    { (yyval.numvariant) = 2;}
#line 1851 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 379 "faustparser.y"
                                                    { (yyval.numvariant) = 4;}
#line 1857 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 380 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1863 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 383 "faustparser.y"
                                                     { (yyval.exp) = gGlobal->nil; }
#line 1869 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 384 "faustparser.y"
                                                     { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1875 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 391 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1881 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 392 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1887 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 395 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1893 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 396 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1899 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 397 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 1905 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 398 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 1911 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 399 "faustparser.y"
                                                { (yyval.exp) = boxInt(-str2int(FAUSTtext)); }
#line 1917 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 400 "faustparser.y"
                                                { (yyval.exp) = boxReal(-atof(FAUSTtext)); }
#line 1923 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 403 "faustparser.y"
                                                             { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1929 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 404 "faustparser.y"
                                                             { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1935 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 405 "faustparser.y"
                                                             { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1941 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 406 "faustparser.y"
                                                             { (yyval.exp) = (yyvsp[0].exp); }
#line 1947 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 407 "faustparser.y"
                                                             { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1953 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 410 "faustparser.y"
                                                            { (yyval.exp) = gGlobal->nil; }
#line 1959 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 411 "faustparser.y"
                                                            { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1965 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 414 "faustparser.y"
                                                            { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1971 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 415 "faustparser.y"
                                                            { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1977 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 416 "faustparser.y"
                                                            { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1983 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 417 "faustparser.y"
                                                            { (yyval.exp) = docNtc(); }
#line 1989 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 418 "faustparser.y"
                                                            { (yyval.exp) = docLst(); }
#line 1995 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 419 "faustparser.y"
                                                            { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 2001 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 422 "faustparser.y"
                                                           { (yyval.cppstr) = new string(); }
#line 2007 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 423 "faustparser.y"
                                                           { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(FAUSTtext)); }
#line 2013 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 426 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2019 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 429 "faustparser.y"
                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2025 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 432 "faustparser.y"
                                                        { }
#line 2031 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 435 "faustparser.y"
                                                        { }
#line 2037 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 438 "faustparser.y"
                                                        { }
#line 2043 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 439 "faustparser.y"
                                                        { }
#line 2049 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 442 "faustparser.y"
                                                                { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2055 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 443 "faustparser.y"
                                                                { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2061 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 444 "faustparser.y"
                                                                { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2067 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 447 "faustparser.y"
                                                         { (yyval.b) = true; }
#line 2073 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 448 "faustparser.y"
                                                          { (yyval.b) = false; }
#line 2079 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 451 "faustparser.y"
                                                          { (yyval.exp) = (yyvsp[-1].exp); }
#line 2085 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 454 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), FAUSTfilename, FAUSTlineno); }
#line 2091 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 455 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2097 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 456 "faustparser.y"
                                                                   { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2103 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 459 "faustparser.y"
                                                              { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), FAUSTfilename, FAUSTlineno); }
#line 2109 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 460 "faustparser.y"
                                                              { (yyval.exp) = gGlobal->nil; FAUSTerr++; }
#line 2115 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 463 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2121 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 466 "faustparser.y"
                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2127 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 469 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2133 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 470 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2139 "faustparser.cpp"
    break;

  case 59: /* modentry: uqstring  */
#line 473 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2145 "faustparser.cpp"
    break;

  case 60: /* modentry: uqstring SEQ argument  */
#line 474 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2151 "faustparser.cpp"
    break;

  case 61: /* modlist: modentry  */
#line 477 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2157 "faustparser.cpp"
    break;

  case 62: /* modlist: modlist PAR modentry  */
#line 478 "faustparser.y"
                                                          { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2163 "faustparser.cpp"
    break;

  case 63: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 481 "faustparser.y"
                                                         { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2169 "faustparser.cpp"
    break;

  case 64: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 482 "faustparser.y"
                                                         { (yyval.exp) = boxWithRecDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp)), gGlobal->nil); }
#line 2175 "faustparser.cpp"
    break;

  case 65: /* expression: expression LETREC LBRAQ reclist WHERE deflist RBRAQ  */
#line 483 "faustparser.y"
                                                                         { Tree r = formatDefinitions((yyvsp[-3].exp)); Tree d = formatDefinitions((yyvsp[-1].exp)); (yyval.exp) = boxWithRecDef((yyvsp[-6].exp), r, d); }
#line 2181 "faustparser.cpp"
    break;

  case 66: /* expression: expression PAR expression  */
#line 484 "faustparser.y"
                                                         { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2187 "faustparser.cpp"
    break;

  case 67: /* expression: expression SEQ expression  */
#line 485 "faustparser.y"
                                                         { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2193 "faustparser.cpp"
    break;

  case 68: /* expression: expression SPLIT expression  */
#line 486 "faustparser.y"
                                                         { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2199 "faustparser.cpp"
    break;

  case 69: /* expression: expression MIX expression  */
#line 487 "faustparser.y"
                                                         { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2205 "faustparser.cpp"
    break;

  case 70: /* expression: expression REC expression  */
#line 488 "faustparser.y"
                                                         { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2211 "faustparser.cpp"
    break;

  case 71: /* expression: infixexp  */
#line 489 "faustparser.y"
                                                         { (yyval.exp) = (yyvsp[0].exp); }
#line 2217 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp ADD infixexp  */
#line 492 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxAdd()); }
#line 2223 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp SUB infixexp  */
#line 493 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxSub()); }
#line 2229 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp MUL infixexp  */
#line 494 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxMul()); }
#line 2235 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DIV infixexp  */
#line 495 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxDiv()); }
#line 2241 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp MOD infixexp  */
#line 496 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxRem()); }
#line 2247 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp POWOP infixexp  */
#line 497 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxPow()); }
#line 2253 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp FDELAY infixexp  */
#line 498 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxDelay()); }
#line 2259 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp DELAY1  */
#line 499 "faustparser.y"
                                            { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxDelay1()); }
#line 2265 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp DOT ident  */
#line 500 "faustparser.y"
                                            { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2271 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp AND infixexp  */
#line 502 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxAND()); }
#line 2277 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp OR infixexp  */
#line 503 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxOR()); }
#line 2283 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp XOR infixexp  */
#line 504 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxXOR()); }
#line 2289 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp LSH infixexp  */
#line 506 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxLeftShift()); }
#line 2295 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp RSH infixexp  */
#line 507 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxARightShift()); }
#line 2301 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp LT infixexp  */
#line 509 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxLT()); }
#line 2307 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp LE infixexp  */
#line 510 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxLE()); }
#line 2313 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp GT infixexp  */
#line 511 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxGT()); }
#line 2319 "faustparser.cpp"
    break;

  case 89: /* infixexp: infixexp GE infixexp  */
#line 512 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxGE()); }
#line 2325 "faustparser.cpp"
    break;

  case 90: /* infixexp: infixexp EQ infixexp  */
#line 513 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxEQ()); }
#line 2331 "faustparser.cpp"
    break;

  case 91: /* infixexp: infixexp NE infixexp  */
#line 514 "faustparser.y"
                                            { Tree p = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxNE()); }
#line 2337 "faustparser.cpp"
    break;

  case 92: /* infixexp: infixexp LPAR arglist RPAR  */
#line 516 "faustparser.y"
                                                   { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2343 "faustparser.cpp"
    break;

  case 93: /* infixexp: infixexp LCROC deflist RCROC  */
#line 517 "faustparser.y"
                                                   { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2349 "faustparser.cpp"
    break;

  case 94: /* infixexp: primitive  */
#line 519 "faustparser.y"
                                                   { (yyval.exp) = (yyvsp[0].exp); }
#line 2355 "faustparser.cpp"
    break;

  case 95: /* primitive: INT  */
#line 522 "faustparser.y"
                                                { (yyval.exp) = boxInt(str2int(FAUSTtext)); }
#line 2361 "faustparser.cpp"
    break;

  case 96: /* primitive: FLOAT  */
#line 523 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2367 "faustparser.cpp"
    break;

  case 97: /* primitive: ADD INT  */
#line 525 "faustparser.y"
                                                { (yyval.exp) = boxInt (str2int(FAUSTtext)); }
#line 2373 "faustparser.cpp"
    break;

  case 98: /* primitive: ADD FLOAT  */
#line 526 "faustparser.y"
                                                { (yyval.exp) = boxReal(atof(FAUSTtext)); }
#line 2379 "faustparser.cpp"
    break;

  case 99: /* primitive: SUB INT  */
#line 528 "faustparser.y"
                                                { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); }
#line 2385 "faustparser.cpp"
    break;

  case 100: /* primitive: SUB FLOAT  */
#line 529 "faustparser.y"
                                                { (yyval.exp) = boxReal( -atof(FAUSTtext) ); }
#line 2391 "faustparser.cpp"
    break;

  case 101: /* primitive: WIRE  */
#line 531 "faustparser.y"
                                                { (yyval.exp) = boxWire(); }
#line 2397 "faustparser.cpp"
    break;

  case 102: /* primitive: CUT  */
#line 532 "faustparser.y"
                                                { (yyval.exp) = boxCut(); }
#line 2403 "faustparser.cpp"
    break;

  case 103: /* primitive: MEM  */
#line 534 "faustparser.y"
                                                { (yyval.exp) = boxDelay1(); }
#line 2409 "faustparser.cpp"
    break;

  case 104: /* primitive: PREFIX  */
#line 535 "faustparser.y"
                                                { (yyval.exp) = boxPrefix(); }
#line 2415 "faustparser.cpp"
    break;

  case 105: /* primitive: INTCAST  */
#line 537 "faustparser.y"
                                                { (yyval.exp) = boxIntCast(); }
#line 2421 "faustparser.cpp"
    break;

  case 106: /* primitive: FLOATCAST  */
#line 538 "faustparser.y"
                                                { (yyval.exp) = boxFloatCast(); }
#line 2427 "faustparser.cpp"
    break;

  case 107: /* primitive: ADD  */
#line 540 "faustparser.y"
                                                { (yyval.exp) = boxAdd(); }
#line 2433 "faustparser.cpp"
    break;

  case 108: /* primitive: SUB  */
#line 541 "faustparser.y"
                                                { (yyval.exp) = boxSub(); }
#line 2439 "faustparser.cpp"
    break;

  case 109: /* primitive: MUL  */
#line 542 "faustparser.y"
                                                { (yyval.exp) = boxMul(); }
#line 2445 "faustparser.cpp"
    break;

  case 110: /* primitive: DIV  */
#line 543 "faustparser.y"
                                                { (yyval.exp) = boxDiv(); }
#line 2451 "faustparser.cpp"
    break;

  case 111: /* primitive: MOD  */
#line 544 "faustparser.y"
                                                { (yyval.exp) = boxRem(); }
#line 2457 "faustparser.cpp"
    break;

  case 112: /* primitive: FDELAY  */
#line 545 "faustparser.y"
                                                { (yyval.exp) = boxDelay(); }
#line 2463 "faustparser.cpp"
    break;

  case 113: /* primitive: AND  */
#line 547 "faustparser.y"
                                                { (yyval.exp) = boxAND(); }
#line 2469 "faustparser.cpp"
    break;

  case 114: /* primitive: OR  */
#line 548 "faustparser.y"
                                                { (yyval.exp) = boxOR(); }
#line 2475 "faustparser.cpp"
    break;

  case 115: /* primitive: XOR  */
#line 549 "faustparser.y"
                                                { (yyval.exp) = boxXOR(); }
#line 2481 "faustparser.cpp"
    break;

  case 116: /* primitive: LSH  */
#line 551 "faustparser.y"
                                                { (yyval.exp) = boxLeftShift(); }
#line 2487 "faustparser.cpp"
    break;

  case 117: /* primitive: RSH  */
#line 552 "faustparser.y"
                                                { (yyval.exp) = boxARightShift(); }
#line 2493 "faustparser.cpp"
    break;

  case 118: /* primitive: LT  */
#line 554 "faustparser.y"
                                                { (yyval.exp) = boxLT(); }
#line 2499 "faustparser.cpp"
    break;

  case 119: /* primitive: LE  */
#line 555 "faustparser.y"
                                                { (yyval.exp) = boxLE(); }
#line 2505 "faustparser.cpp"
    break;

  case 120: /* primitive: GT  */
#line 556 "faustparser.y"
                                                { (yyval.exp) = boxGT(); }
#line 2511 "faustparser.cpp"
    break;

  case 121: /* primitive: GE  */
#line 557 "faustparser.y"
                                                { (yyval.exp) = boxGE(); }
#line 2517 "faustparser.cpp"
    break;

  case 122: /* primitive: EQ  */
#line 558 "faustparser.y"
                                                { (yyval.exp) = boxEQ(); }
#line 2523 "faustparser.cpp"
    break;

  case 123: /* primitive: NE  */
#line 559 "faustparser.y"
                                                { (yyval.exp) = boxNE(); }
#line 2529 "faustparser.cpp"
    break;

  case 124: /* primitive: ATTACH  */
#line 561 "faustparser.y"
                                                { (yyval.exp) = boxAttach(); }
#line 2535 "faustparser.cpp"
    break;

  case 125: /* primitive: ENABLE  */
#line 562 "faustparser.y"
                                                { (yyval.exp) = boxEnable(); }
#line 2541 "faustparser.cpp"
    break;

  case 126: /* primitive: CONTROL  */
#line 563 "faustparser.y"
                                                { (yyval.exp) = boxControl(); }
#line 2547 "faustparser.cpp"
    break;

  case 127: /* primitive: ACOS  */
#line 565 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2553 "faustparser.cpp"
    break;

  case 128: /* primitive: ASIN  */
#line 566 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2559 "faustparser.cpp"
    break;

  case 129: /* primitive: ATAN  */
#line 567 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2565 "faustparser.cpp"
    break;

  case 130: /* primitive: ATAN2  */
#line 568 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2571 "faustparser.cpp"
    break;

  case 131: /* primitive: COS  */
#line 569 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2577 "faustparser.cpp"
    break;

  case 132: /* primitive: SIN  */
#line 570 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2583 "faustparser.cpp"
    break;

  case 133: /* primitive: TAN  */
#line 571 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2589 "faustparser.cpp"
    break;

  case 134: /* primitive: EXP  */
#line 573 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2595 "faustparser.cpp"
    break;

  case 135: /* primitive: LOG  */
#line 574 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2601 "faustparser.cpp"
    break;

  case 136: /* primitive: LOG10  */
#line 575 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2607 "faustparser.cpp"
    break;

  case 137: /* primitive: POWOP  */
#line 576 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2613 "faustparser.cpp"
    break;

  case 138: /* primitive: POWFUN  */
#line 577 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2619 "faustparser.cpp"
    break;

  case 139: /* primitive: SQRT  */
#line 578 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2625 "faustparser.cpp"
    break;

  case 140: /* primitive: ABS  */
#line 580 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2631 "faustparser.cpp"
    break;

  case 141: /* primitive: MIN  */
#line 581 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2637 "faustparser.cpp"
    break;

  case 142: /* primitive: MAX  */
#line 582 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2643 "faustparser.cpp"
    break;

  case 143: /* primitive: FMOD  */
#line 584 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2649 "faustparser.cpp"
    break;

  case 144: /* primitive: REMAINDER  */
#line 585 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2655 "faustparser.cpp"
    break;

  case 145: /* primitive: FLOOR  */
#line 587 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2661 "faustparser.cpp"
    break;

  case 146: /* primitive: CEIL  */
#line 588 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2667 "faustparser.cpp"
    break;

  case 147: /* primitive: RINT  */
#line 589 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2673 "faustparser.cpp"
    break;

  case 148: /* primitive: ROUND  */
#line 590 "faustparser.y"
                                                 { (yyval.exp) = gGlobal->gRoundPrim->box(); }
#line 2679 "faustparser.cpp"
    break;

  case 149: /* primitive: RDTBL  */
#line 592 "faustparser.y"
                                                 { (yyval.exp) = boxReadOnlyTable(); }
#line 2685 "faustparser.cpp"
    break;

  case 150: /* primitive: RWTBL  */
#line 593 "faustparser.y"
                                                 { (yyval.exp) = boxWriteReadTable(); }
#line 2691 "faustparser.cpp"
    break;

  case 151: /* primitive: SELECT2  */
#line 595 "faustparser.y"
                                                 { (yyval.exp) = boxSelect2(); }
#line 2697 "faustparser.cpp"
    break;

  case 152: /* primitive: SELECT3  */
#line 596 "faustparser.y"
                                                 { (yyval.exp) = boxSelect3(); }
#line 2703 "faustparser.cpp"
    break;

  case 153: /* primitive: ASSERTBOUNDS  */
#line 598 "faustparser.y"
                                                 { (yyval.exp) = boxAssertBound(); }
#line 2709 "faustparser.cpp"
    break;

  case 154: /* primitive: LOWEST  */
#line 599 "faustparser.y"
                                                 { (yyval.exp) = boxLowest(); }
#line 2715 "faustparser.cpp"
    break;

  case 155: /* primitive: HIGHEST  */
#line 600 "faustparser.y"
                                                 { (yyval.exp) = boxHighest(); }
#line 2721 "faustparser.cpp"
    break;

  case 156: /* primitive: ident  */
#line 602 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp); setUseProp((yyvsp[0].exp), FAUSTfilename, FAUSTlineno);}
#line 2727 "faustparser.cpp"
    break;

  case 157: /* primitive: SUB ident  */
#line 603 "faustparser.y"
                                                 { Tree z = boxInt(0); Tree p = boxPar(z,(yyvsp[0].exp)); (yyval.exp) = boxSeq(p, boxSub()); }
#line 2733 "faustparser.cpp"
    break;

  case 158: /* primitive: LPAR expression RPAR  */
#line 605 "faustparser.y"
                                                  { (yyval.exp) = (yyvsp[-1].exp); }
#line 2739 "faustparser.cpp"
    break;

  case 159: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 607 "faustparser.y"
                                                  { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2745 "faustparser.cpp"
    break;

  case 160: /* primitive: LCROC modlist LAPPLY expression RCROC  */
#line 613 "faustparser.y"
                                                  { (yyval.exp) = buildBoxModulation((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2751 "faustparser.cpp"
    break;

  case 161: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 615 "faustparser.y"
                                                { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2757 "faustparser.cpp"
    break;

  case 162: /* primitive: ffunction  */
#line 617 "faustparser.y"
                                                { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2763 "faustparser.cpp"
    break;

  case 163: /* primitive: fconst  */
#line 618 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2769 "faustparser.cpp"
    break;

  case 164: /* primitive: fvariable  */
#line 619 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2775 "faustparser.cpp"
    break;

  case 165: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 620 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2781 "faustparser.cpp"
    break;

  case 166: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 621 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2787 "faustparser.cpp"
    break;

  case 167: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 622 "faustparser.y"
                                                   { Tree e = boxEnvironment(); Tree d = formatDefinitions((yyvsp[-1].exp)); (yyval.exp) = boxWithLocalDef(e, d); }
#line 2793 "faustparser.cpp"
    break;

  case 168: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 623 "faustparser.y"
                                                   { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2799 "faustparser.cpp"
    break;

  case 169: /* primitive: ROUTE LPAR argument PAR argument RPAR  */
#line 624 "faustparser.y"
                                                              { Tree z = boxInt(0); Tree p = boxPar(z,z); (yyval.exp) = boxRoute((yyvsp[-3].exp), (yyvsp[-1].exp), p); }
#line 2805 "faustparser.cpp"
    break;

  case 170: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 625 "faustparser.y"
                                                                             { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2811 "faustparser.cpp"
    break;

  case 171: /* primitive: ONDEMAND LPAR expression RPAR  */
#line 626 "faustparser.y"
                                                     { (yyval.exp) = boxOndemand((yyvsp[-1].exp)); }
#line 2817 "faustparser.cpp"
    break;

  case 172: /* primitive: UPSAMPLING LPAR expression RPAR  */
#line 627 "faustparser.y"
                                                     { (yyval.exp) = boxUpsampling((yyvsp[-1].exp)); }
#line 2823 "faustparser.cpp"
    break;

  case 173: /* primitive: DOWNSAMPLING LPAR expression RPAR  */
#line 628 "faustparser.y"
                                                     { (yyval.exp) = boxDownsampling((yyvsp[-1].exp)); }
#line 2829 "faustparser.cpp"
    break;

  case 174: /* primitive: button  */
#line 629 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2835 "faustparser.cpp"
    break;

  case 175: /* primitive: checkbox  */
#line 630 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2841 "faustparser.cpp"
    break;

  case 176: /* primitive: vslider  */
#line 631 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2847 "faustparser.cpp"
    break;

  case 177: /* primitive: hslider  */
#line 632 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2853 "faustparser.cpp"
    break;

  case 178: /* primitive: nentry  */
#line 633 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2859 "faustparser.cpp"
    break;

  case 179: /* primitive: vgroup  */
#line 634 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2865 "faustparser.cpp"
    break;

  case 180: /* primitive: hgroup  */
#line 635 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2871 "faustparser.cpp"
    break;

  case 181: /* primitive: tgroup  */
#line 636 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2877 "faustparser.cpp"
    break;

  case 182: /* primitive: vbargraph  */
#line 637 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2883 "faustparser.cpp"
    break;

  case 183: /* primitive: hbargraph  */
#line 638 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2889 "faustparser.cpp"
    break;

  case 184: /* primitive: soundfile  */
#line 639 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2895 "faustparser.cpp"
    break;

  case 185: /* primitive: fpar  */
#line 641 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2901 "faustparser.cpp"
    break;

  case 186: /* primitive: fseq  */
#line 642 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2907 "faustparser.cpp"
    break;

  case 187: /* primitive: fsum  */
#line 643 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2913 "faustparser.cpp"
    break;

  case 188: /* primitive: fprod  */
#line 644 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2919 "faustparser.cpp"
    break;

  case 189: /* primitive: finputs  */
#line 646 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2925 "faustparser.cpp"
    break;

  case 190: /* primitive: foutputs  */
#line 647 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2931 "faustparser.cpp"
    break;

  case 191: /* ident: IDENT  */
#line 650 "faustparser.y"
                                                { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2937 "faustparser.cpp"
    break;

  case 192: /* name: IDENT  */
#line 653 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  }
#line 2943 "faustparser.cpp"
    break;

  case 193: /* arglist: argument  */
#line 656 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2949 "faustparser.cpp"
    break;

  case 194: /* arglist: arglist PAR argument  */
#line 657 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2955 "faustparser.cpp"
    break;

  case 195: /* argument: argument SEQ argument  */
#line 660 "faustparser.y"
                                                 { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2961 "faustparser.cpp"
    break;

  case 196: /* argument: argument SPLIT argument  */
#line 661 "faustparser.y"
                                                 { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2967 "faustparser.cpp"
    break;

  case 197: /* argument: argument MIX argument  */
#line 662 "faustparser.y"
                                                 { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2973 "faustparser.cpp"
    break;

  case 198: /* argument: argument REC argument  */
#line 663 "faustparser.y"
                                                 { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2979 "faustparser.cpp"
    break;

  case 199: /* argument: infixexp  */
#line 664 "faustparser.y"
                                                 { (yyval.exp) = (yyvsp[0].exp); }
#line 2985 "faustparser.cpp"
    break;

  case 200: /* string: STRING  */
#line 667 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 2991 "faustparser.cpp"
    break;

  case 201: /* uqstring: STRING  */
#line 670 "faustparser.y"
                                                 { (yyval.exp) = unquote(FAUSTtext); }
#line 2997 "faustparser.cpp"
    break;

  case 202: /* fstring: STRING  */
#line 673 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 3003 "faustparser.cpp"
    break;

  case 203: /* fstring: FSTRING  */
#line 674 "faustparser.y"
                                                 { (yyval.exp) = tree(FAUSTtext); }
#line 3009 "faustparser.cpp"
    break;

  case 204: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 680 "faustparser.y"
                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3015 "faustparser.cpp"
    break;

  case 205: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 684 "faustparser.y"
                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3021 "faustparser.cpp"
    break;

  case 206: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 688 "faustparser.y"
                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3027 "faustparser.cpp"
    break;

  case 207: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 692 "faustparser.y"
                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3033 "faustparser.cpp"
    break;

  case 208: /* finputs: INPUTS LPAR expression RPAR  */
#line 695 "faustparser.y"
                                              { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 3039 "faustparser.cpp"
    break;

  case 209: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 698 "faustparser.y"
                                               { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 3045 "faustparser.cpp"
    break;

  case 210: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 704 "faustparser.y"
                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3051 "faustparser.cpp"
    break;

  case 211: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 708 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3057 "faustparser.cpp"
    break;

  case 212: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 712 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3063 "faustparser.cpp"
    break;

  case 213: /* button: BUTTON LPAR uqstring RPAR  */
#line 716 "faustparser.y"
                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3069 "faustparser.cpp"
    break;

  case 214: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 719 "faustparser.y"
                                                 { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3075 "faustparser.cpp"
    break;

  case 215: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 723 "faustparser.y"
                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3081 "faustparser.cpp"
    break;

  case 216: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 726 "faustparser.y"
                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3087 "faustparser.cpp"
    break;

  case 217: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 729 "faustparser.y"
                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3093 "faustparser.cpp"
    break;

  case 218: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 732 "faustparser.y"
                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3099 "faustparser.cpp"
    break;

  case 219: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 735 "faustparser.y"
                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3105 "faustparser.cpp"
    break;

  case 220: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 738 "faustparser.y"
                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3111 "faustparser.cpp"
    break;

  case 221: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 742 "faustparser.y"
                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3117 "faustparser.cpp"
    break;

  case 222: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 745 "faustparser.y"
                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3123 "faustparser.cpp"
    break;

  case 223: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 748 "faustparser.y"
                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3129 "faustparser.cpp"
    break;

  case 224: /* signature: type fun LPAR typelist RPAR  */
#line 754 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-4].exp),cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3135 "faustparser.cpp"
    break;

  case 225: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 755 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-6].exp),cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3141 "faustparser.cpp"
    break;

  case 226: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 756 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-8].exp),cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3147 "faustparser.cpp"
    break;

  case 227: /* signature: type fun OR fun OR fun OR fun LPAR typelist RPAR  */
#line 757 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-10].exp),cons(cons((yyvsp[-9].exp),cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil)))), (yyvsp[-1].exp))); }
#line 3153 "faustparser.cpp"
    break;

  case 228: /* signature: type fun LPAR RPAR  */
#line 759 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-3].exp),cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3159 "faustparser.cpp"
    break;

  case 229: /* signature: type fun OR fun LPAR RPAR  */
#line 760 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-5].exp),cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3165 "faustparser.cpp"
    break;

  case 230: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 761 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-7].exp),cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3171 "faustparser.cpp"
    break;

  case 231: /* signature: type fun OR fun OR fun OR fun LPAR RPAR  */
#line 762 "faustparser.y"
                                                                   { (yyval.exp) = cons((yyvsp[-9].exp),cons(cons((yyvsp[-8].exp),cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil)))), gGlobal->nil)); }
#line 3177 "faustparser.cpp"
    break;

  case 232: /* fun: IDENT  */
#line 765 "faustparser.y"
                                                { (yyval.exp) = tree(FAUSTtext); }
#line 3183 "faustparser.cpp"
    break;

  case 233: /* typelist: argtype  */
#line 768 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3189 "faustparser.cpp"
    break;

  case 234: /* typelist: typelist PAR argtype  */
#line 769 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3195 "faustparser.cpp"
    break;

  case 235: /* rulelist: rule  */
#line 772 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3201 "faustparser.cpp"
    break;

  case 236: /* rulelist: rulelist rule  */
#line 773 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3207 "faustparser.cpp"
    break;

  case 237: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 777 "faustparser.y"
                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3213 "faustparser.cpp"
    break;

  case 238: /* type: INTCAST  */
#line 780 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3219 "faustparser.cpp"
    break;

  case 239: /* type: FLOATCAST  */
#line 781 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3225 "faustparser.cpp"
    break;

  case 240: /* argtype: INTCAST  */
#line 784 "faustparser.y"
                                                { (yyval.exp) = tree(0); }
#line 3231 "faustparser.cpp"
    break;

  case 241: /* argtype: FLOATCAST  */
#line 785 "faustparser.y"
                                                { (yyval.exp) = tree(1); }
#line 3237 "faustparser.cpp"
    break;

  case 242: /* argtype: NOTYPECAST  */
#line 786 "faustparser.y"
                                                { (yyval.exp) = tree(2); }
#line 3243 "faustparser.cpp"
    break;


#line 3247 "faustparser.cpp"

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

