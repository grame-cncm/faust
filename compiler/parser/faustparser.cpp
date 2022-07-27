/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
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


#line 162 "faustparser.cpp"

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
  YYSYMBOL_WHERE = 86,                     /* WHERE  */
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
  YYSYMBOL_ASSERTBOUNDS = 109,             /* ASSERTBOUNDS  */
  YYSYMBOL_LOWEST = 110,                   /* LOWEST  */
  YYSYMBOL_HIGHEST = 111,                  /* HIGHEST  */
  YYSYMBOL_FLOATMODE = 112,                /* FLOATMODE  */
  YYSYMBOL_DOUBLEMODE = 113,               /* DOUBLEMODE  */
  YYSYMBOL_QUADMODE = 114,                 /* QUADMODE  */
  YYSYMBOL_FIXEDPOINTMODE = 115,           /* FIXEDPOINTMODE  */
  YYSYMBOL_BDOC = 116,                     /* BDOC  */
  YYSYMBOL_EDOC = 117,                     /* EDOC  */
  YYSYMBOL_BEQN = 118,                     /* BEQN  */
  YYSYMBOL_EEQN = 119,                     /* EEQN  */
  YYSYMBOL_BDGM = 120,                     /* BDGM  */
  YYSYMBOL_EDGM = 121,                     /* EDGM  */
  YYSYMBOL_BLST = 122,                     /* BLST  */
  YYSYMBOL_ELST = 123,                     /* ELST  */
  YYSYMBOL_BMETADATA = 124,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 125,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 126,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 127,                   /* NOTICE  */
  YYSYMBOL_LISTING = 128,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 129,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 130,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 131,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 132,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 133,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 134,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 135,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 136,                 /* $accept  */
  YYSYMBOL_program = 137,                  /* program  */
  YYSYMBOL_stmtlist = 138,                 /* stmtlist  */
  YYSYMBOL_deflist = 139,                  /* deflist  */
  YYSYMBOL_variantlist = 140,              /* variantlist  */
  YYSYMBOL_variant = 141,                  /* variant  */
  YYSYMBOL_reclist = 142,                  /* reclist  */
  YYSYMBOL_vallist = 143,                  /* vallist  */
  YYSYMBOL_number = 144,                   /* number  */
  YYSYMBOL_statement = 145,                /* statement  */
  YYSYMBOL_doc = 146,                      /* doc  */
  YYSYMBOL_docelem = 147,                  /* docelem  */
  YYSYMBOL_doctxt = 148,                   /* doctxt  */
  YYSYMBOL_doceqn = 149,                   /* doceqn  */
  YYSYMBOL_docdgm = 150,                   /* docdgm  */
  YYSYMBOL_docntc = 151,                   /* docntc  */
  YYSYMBOL_doclst = 152,                   /* doclst  */
  YYSYMBOL_lstattrlist = 153,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 154,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 155,               /* lstattrval  */
  YYSYMBOL_docmtd = 156,                   /* docmtd  */
  YYSYMBOL_definition = 157,               /* definition  */
  YYSYMBOL_recinition = 158,               /* recinition  */
  YYSYMBOL_defname = 159,                  /* defname  */
  YYSYMBOL_recname = 160,                  /* recname  */
  YYSYMBOL_params = 161,                   /* params  */
  YYSYMBOL_expression = 162,               /* expression  */
  YYSYMBOL_infixexp = 163,                 /* infixexp  */
  YYSYMBOL_primitive = 164,                /* primitive  */
  YYSYMBOL_ident = 165,                    /* ident  */
  YYSYMBOL_name = 166,                     /* name  */
  YYSYMBOL_arglist = 167,                  /* arglist  */
  YYSYMBOL_argument = 168,                 /* argument  */
  YYSYMBOL_string = 169,                   /* string  */
  YYSYMBOL_uqstring = 170,                 /* uqstring  */
  YYSYMBOL_fstring = 171,                  /* fstring  */
  YYSYMBOL_fpar = 172,                     /* fpar  */
  YYSYMBOL_fseq = 173,                     /* fseq  */
  YYSYMBOL_fsum = 174,                     /* fsum  */
  YYSYMBOL_fprod = 175,                    /* fprod  */
  YYSYMBOL_finputs = 176,                  /* finputs  */
  YYSYMBOL_foutputs = 177,                 /* foutputs  */
  YYSYMBOL_ffunction = 178,                /* ffunction  */
  YYSYMBOL_fconst = 179,                   /* fconst  */
  YYSYMBOL_fvariable = 180,                /* fvariable  */
  YYSYMBOL_button = 181,                   /* button  */
  YYSYMBOL_checkbox = 182,                 /* checkbox  */
  YYSYMBOL_vslider = 183,                  /* vslider  */
  YYSYMBOL_hslider = 184,                  /* hslider  */
  YYSYMBOL_nentry = 185,                   /* nentry  */
  YYSYMBOL_vgroup = 186,                   /* vgroup  */
  YYSYMBOL_hgroup = 187,                   /* hgroup  */
  YYSYMBOL_tgroup = 188,                   /* tgroup  */
  YYSYMBOL_vbargraph = 189,                /* vbargraph  */
  YYSYMBOL_hbargraph = 190,                /* hbargraph  */
  YYSYMBOL_soundfile = 191,                /* soundfile  */
  YYSYMBOL_signature = 192,                /* signature  */
  YYSYMBOL_fun = 193,                      /* fun  */
  YYSYMBOL_typelist = 194,                 /* typelist  */
  YYSYMBOL_rulelist = 195,                 /* rulelist  */
  YYSYMBOL_rule = 196,                     /* rule  */
  YYSYMBOL_type = 197                      /* type  */
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
#define YYLAST   775

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  227
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  489

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   390


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
     135
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   345,   345,   348,   349,   352,   353,   356,   357,   360,
     361,   362,   363,   366,   367,   374,   375,   378,   379,   380,
     381,   382,   383,   386,   387,   388,   389,   390,   393,   394,
     397,   398,   399,   400,   401,   402,   405,   406,   409,   412,
     415,   418,   421,   422,   425,   426,   427,   430,   431,   434,
     437,   438,   439,   442,   443,   446,   449,   452,   453,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   477,   478,   479,
     481,   482,   484,   485,   486,   487,   488,   489,   491,   492,
     494,   497,   498,   500,   501,   503,   504,   506,   507,   509,
     510,   512,   513,   515,   516,   517,   518,   519,   520,   522,
     523,   524,   526,   527,   529,   530,   531,   532,   533,   534,
     536,   537,   538,   540,   541,   542,   543,   544,   545,   546,
     548,   549,   550,   551,   552,   553,   555,   556,   557,   559,
     560,   562,   563,   564,   566,   567,   569,   570,   572,   573,
     574,   576,   577,   579,   580,   583,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   605,   606,   607,   608,   610,
     611,   615,   618,   621,   622,   625,   626,   627,   628,   629,
     632,   635,   638,   639,   644,   648,   652,   656,   660,   663,
     668,   672,   676,   681,   684,   687,   690,   693,   696,   699,
     702,   706,   709,   712,   719,   720,   721,   723,   724,   725,
     728,   731,   732,   735,   736,   739,   743,   744
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
  "WITH", "LETREC", "WHERE", "DEF", "IMPORT", "COMPONENT", "LIBRARY",
  "ENVIRONMENT", "WAVEFORM", "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ",
  "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT",
  "EXTRA", "DECLARE", "CASE", "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST",
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

#define YYPACT_NINF (-418)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -418,    31,    50,  -418,    19,   -12,     4,  -418,   -15,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,   -11,  -418,  -418,
      -7,  -418,    54,   246,   418,   418,  -418,    34,  -418,    28,
      69,  -418,   418,   418,  -418,   -15,  -418,  -418,    72,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
     124,   -17,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,   140,   185,   193,   199,
     215,   222,   224,   237,   240,   252,   254,   265,   266,   270,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,   273,  -418,  -418,
     418,   274,   275,   277,   278,   281,  -418,  -418,   284,   287,
     289,   291,   293,   296,   301,  -418,  -418,  -418,   577,  -418,
    -418,    24,   316,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,    42,   577,   280,   308,  -418,    20,     7,
     -58,   258,  -418,  -418,  -418,  -418,  -418,  -418,    48,    48,
      48,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,   282,    65,    -7,    -7,  -418,    29,   418,   282,
     282,   282,   282,   418,   418,   323,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,  -418,   282,   418,  -418,   418,   298,
     418,   418,   418,   418,   418,   418,   418,   418,   418,  -418,
     322,   325,  -418,  -418,  -418,  -418,  -418,   269,   288,   290,
    -418,  -418,  -418,  -418,   400,   310,   -15,   -15,   328,   344,
     438,   485,   488,   489,   514,   515,   517,   518,   520,    33,
    -418,  -418,   456,   457,   461,   143,   158,  -418,  -418,     9,
    -418,   373,   537,   543,   544,   565,   205,   232,   418,   192,
    -418,   619,   619,   619,   619,   619,   619,   643,   643,   643,
     219,   219,   219,   219,   219,   219,   219,   260,   272,  -418,
      35,   471,   316,   418,   316,   316,   160,  -418,   386,   386,
     307,   103,  -418,  -418,  -418,   424,   437,   439,   138,  -418,
      18,   570,   571,  -418,  -418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   282,   507,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,    29,  -418,   418,   418,   418,   418,   418,
    -418,  -418,    57,  -418,  -418,  -418,  -418,    39,    53,   501,
      16,   122,   122,   122,  -418,  -418,   575,   310,    22,   138,
     138,   406,   558,   563,   243,   250,   262,   683,   699,    76,
    -418,   526,  -418,   704,   723,   728,   733,   738,   497,  -418,
    -418,  -418,   531,   282,  -418,  -418,  -418,   521,  -418,  -418,
     474,   475,   479,    28,    92,  -418,    78,  -418,   536,   538,
     418,   418,   418,  -418,  -418,  -418,   418,   418,  -418,   418,
     418,   418,   418,   418,   418,   418,  -418,  -418,   535,   418,
    -418,  -418,  -418,   542,   310,    32,    48,  -418,  -418,  -418,
     743,   748,   753,   112,   117,   276,   303,   494,   527,   534,
     541,   255,  -418,   499,  -418,   545,  -418,    80,  -418,   418,
     418,   418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,   163,  -418,   758,   763,   768,  -418,    87,   418,
     418,   418,  -418,   212,   548,   553,  -418,  -418,  -418
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   181,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   182,     0,    36,     0,     0,   191,     0,   190,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   114,   115,   118,   116,   117,   119,
     103,   104,   110,   105,   106,   107,   109,   111,   112,   113,
     133,   108,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,    91,    92,     0,    97,    98,
       0,     0,     0,     0,     0,     0,   121,   122,     0,     0,
       0,     0,     0,     0,     0,   148,   149,   150,   189,    90,
     151,     0,   183,   175,   176,   177,   178,   179,   180,   156,
     157,   158,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,    67,     0,     0,    24,     0,     0,
       0,     0,    37,    93,    94,    95,    96,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    23,    25,    38,    39,    41,     0,     0,     0,
      43,    49,   226,   227,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   153,     0,     0,     7,     0,     0,    17,    18,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     223,    82,    83,    86,    84,    85,    87,    68,    69,    78,
      70,    71,    72,    77,    79,    80,    81,    73,    74,    76,
       0,     7,   184,     0,   186,   187,   185,   188,    64,    65,
      63,    62,    66,     5,    13,     0,     0,     0,     0,   220,
       0,     0,     0,   203,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,   160,   161,    19,
      20,    21,    22,     0,   162,     0,     0,     0,     0,     0,
     198,   199,     0,   155,   224,    88,    89,     0,     0,     7,
       0,     0,     0,     0,   192,   193,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,     0,    16,     0,     0,     0,     0,     0,     0,     6,
      50,    59,     0,     0,    60,     5,    14,     0,    47,    48,
       0,     0,     0,     0,     0,   217,     0,   221,     0,     0,
       0,     0,     0,   208,   209,   210,     0,     0,   213,     0,
       0,     0,     0,     0,     0,     0,    54,    56,     7,     0,
      44,    45,    46,     0,     0,     0,     0,   214,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,     0,   200,     0,   218,     0,   222,     0,
       0,     0,   212,   211,   154,   163,   194,   195,   196,   197,
     225,    53,     0,   215,     0,     0,     0,   219,     0,     0,
       0,     0,   216,     0,     0,     0,   205,   206,   207
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -418,  -418,   436,  -297,     0,  -418,  -418,  -418,   285,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,   -75,
    -418,   267,  -418,  -418,  -418,  -418,    -4,   -25,  -418,    15,
     -13,  -184,  -185,   -28,   500,   -33,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -346,  -417,  -418,
     350,  -164
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   301,   357,    14,   360,   269,   270,    15,
      23,    37,    38,    39,    40,    41,    42,   160,   240,   400,
      43,    16,   396,    17,   397,   259,   153,   128,   129,   130,
      22,   131,   132,    30,    27,   366,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   244,   320,   406,   279,
     280,   407
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     154,   156,     4,   271,   245,   246,   247,   154,   154,    29,
     224,   225,   226,   227,   228,   343,   359,   392,   457,    18,
       5,   404,   161,   224,   225,   226,   227,   228,   158,   159,
     218,     3,   300,   302,   367,   304,   305,   306,   307,   334,
       5,   218,   393,   265,   266,   224,   225,   226,   227,   228,
      -2,   242,   243,   165,   166,   478,   224,   225,   226,   227,
     228,   242,   243,   218,    19,   236,   167,    24,   224,   225,
     226,   227,   228,   237,   238,   239,    25,   242,   243,   220,
     221,   222,    20,   223,   436,   154,   436,     7,   455,    21,
     344,   230,   231,   436,   352,    26,   368,   394,   428,   267,
     268,   405,   395,   219,   230,   231,   183,     6,   434,   227,
     228,   456,   335,   155,   355,   220,   221,   222,   229,   223,
     220,   221,   222,     7,   223,     8,   230,   231,   235,   390,
      28,     9,    10,    11,    12,    13,   388,   230,   231,   234,
     371,   372,   373,     7,   261,   157,   377,   378,   379,   230,
     231,     9,    10,    11,    12,   418,    28,   437,    21,   473,
     383,   384,   385,   386,   387,   222,   482,   223,   154,   154,
     435,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   276,
     277,   462,   242,   243,   163,   164,   463,   260,   162,   154,
     154,   154,   154,   154,   272,   273,   274,   275,   224,   225,
     226,   227,   228,   339,   340,   220,   221,   222,   168,   223,
     308,   309,   310,   311,   312,   440,   441,   442,   341,   342,
     299,   443,   444,   321,   322,   224,   225,   226,   227,   228,
     364,   365,   477,   212,   213,   214,   224,   225,   226,   227,
     228,   398,   399,   224,   225,   226,   227,   228,   224,   225,
     226,   227,   228,   169,     4,   224,   225,   226,   227,   228,
     278,   170,   458,   353,   474,   475,   476,   171,   154,   224,
     225,   226,   227,   228,   350,   213,   214,   401,   402,   230,
     231,   486,   215,   172,   483,   484,   485,   216,   214,   358,
     173,   217,   174,   154,   154,   154,   224,   225,   226,   227,
     228,   351,   226,   227,   228,   175,   230,   231,   176,   220,
     221,   222,   413,   223,   374,   375,   376,   230,   231,   414,
     177,   470,   178,   215,   230,   231,   408,   409,   216,   230,
     231,   415,   217,   179,   180,   215,   230,   231,   181,   380,
     216,   182,   184,   185,   217,   464,   232,   186,   187,   188,
     230,   231,   189,    31,    32,   190,    33,   191,    34,   192,
      35,   193,    18,    36,   194,   433,   220,   221,   222,   345,
     223,   195,   465,   241,   233,   303,     7,   230,   231,   224,
     225,   226,   227,   228,   154,   154,   154,   154,   154,   154,
     154,   278,   313,   315,   154,   314,   318,   323,   427,   220,
     221,   222,   410,   223,   319,   445,   446,   447,   448,   449,
     450,   451,   316,   324,   317,   453,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,   325,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   326,   108,   109,   327,   328,   110,   224,   225,   226,
     227,   228,   224,   225,   226,   227,   228,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     329,   330,     7,   331,   332,   124,   333,   125,   126,   127,
     224,   225,   226,   227,   228,   336,   337,   224,   225,   226,
     227,   228,   338,   346,   224,   225,   226,   227,   228,   347,
     348,   220,   221,   222,   356,   223,   220,   221,   222,   361,
     223,   220,   221,   222,   411,   223,   220,   221,   222,   412,
     223,   349,   362,   466,   363,   471,   369,   370,   230,   231,
     381,   403,   391,   230,   231,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   419,   425,   467,   426,   429,   430,
     431,   230,   231,   468,   432,   438,   452,   439,   230,   231,
     469,   454,   264,   472,   389,   230,   231,   487,   382,   354,
       0,     0,   488,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,     0,     0,     0,     0,
     215,     0,     0,     0,     0,   216,     0,     0,     0,   217,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
       0,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,     0,   262,   263,   220,   221,   222,   416,
     223,     0,   215,     0,     0,     0,     0,   216,     0,     0,
       0,   217,   220,   221,   222,   417,   223,   220,   221,   222,
     420,   223,     0,     0,     0,     0,   215,     0,     0,     0,
       0,   216,     0,     0,     0,   217,   220,   221,   222,   421,
     223,   220,   221,   222,   422,   223,   220,   221,   222,   423,
     223,   220,   221,   222,   424,   223,   220,   221,   222,   459,
     223,   220,   221,   222,   460,   223,   220,   221,   222,   461,
     223,   220,   221,   222,   479,   223,   220,   221,   222,   480,
     223,   220,   221,   222,   481,   223
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,   188,   168,   169,   170,    32,    33,    22,
       3,     4,     5,     6,     7,     6,   313,     1,   435,     4,
       1,   367,    35,     3,     4,     5,     6,     7,    32,    33,
       6,     0,   216,   218,    16,   220,   221,   222,   223,     6,
       1,     6,    26,    14,    15,     3,     4,     5,     6,     7,
       0,    29,    30,    70,    71,   472,     3,     4,     5,     6,
       7,    29,    30,     6,    76,   123,    51,    78,     3,     4,
       5,     6,     7,   131,   132,   133,    87,    29,    30,     3,
       4,     5,    78,     7,     6,   110,     6,   104,   434,   104,
      81,    84,    85,     6,   278,   102,    78,    81,   395,    70,
      71,    79,    86,    79,    84,    85,   110,    88,    16,     6,
       7,    79,    79,    79,    79,     3,     4,     5,    76,     7,
       3,     4,     5,   104,     7,   106,    84,    85,   121,    76,
     102,   112,   113,   114,   115,   116,    79,    84,    85,   119,
     325,   326,   327,   104,    79,    76,   331,   332,   333,    84,
      85,   112,   113,   114,   115,    79,   102,    79,   104,    79,
     345,   346,   347,   348,   349,     5,    79,     7,   193,   194,
      78,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   193,
     194,    79,    29,    30,    70,    71,    79,   182,   126,   224,
     225,   226,   227,   228,   189,   190,   191,   192,     3,     4,
       5,     6,     7,    70,    71,     3,     4,     5,    78,     7,
     224,   225,   226,   227,   228,   410,   411,   412,    70,    71,
     215,   416,   417,   246,   247,     3,     4,     5,     6,     7,
     102,   103,    79,    24,    25,    26,     3,     4,     5,     6,
       7,   129,   130,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    78,   264,     3,     4,     5,     6,     7,
      78,    78,   436,    81,   459,   460,   461,    78,   303,     3,
       4,     5,     6,     7,    79,    25,    26,   362,   363,    84,
      85,    79,    73,    78,   479,   480,   481,    78,    26,   303,
      78,    82,    78,   328,   329,   330,     3,     4,     5,     6,
       7,    79,     5,     6,     7,    78,    84,    85,    78,     3,
       4,     5,    79,     7,   328,   329,   330,    84,    85,    79,
      78,    76,    78,    73,    84,    85,   369,   370,    78,    84,
      85,    79,    82,    78,    78,    73,    84,    85,    78,   334,
      78,    78,    78,    78,    82,    79,    76,    80,    80,    78,
      84,    85,    78,   117,   118,    78,   120,    78,   122,    78,
     124,    78,   357,   127,    78,   403,     3,     4,     5,     6,
       7,    80,    79,   125,    76,    87,   104,    84,    85,     3,
       4,     5,     6,     7,   419,   420,   421,   422,   423,   424,
     425,    78,    80,   134,   429,    80,     6,    79,   393,     3,
       4,     5,     6,     7,   104,   419,   420,   421,   422,   423,
     424,   425,   134,    79,   134,   429,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     6,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,     6,    74,    75,     6,     6,    78,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       6,     6,   104,     6,     6,   107,     6,   109,   110,   111,
       3,     4,     5,     6,     7,    79,    79,     3,     4,     5,
       6,     7,    81,     6,     3,     4,     5,     6,     7,     6,
       6,     3,     4,     5,    83,     7,     3,     4,     5,   135,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     6,   135,    79,   135,    76,     6,     6,    84,    85,
      73,     6,    81,    84,    85,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    78,   108,    79,    76,    87,   135,
     135,    84,    85,    79,   135,    79,    81,    79,    84,    85,
      79,    79,   186,    78,   357,    84,    85,    79,   343,   279,
      -1,    -1,    79,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,    -1,    -1,   184,   185,     3,     4,     5,     6,
       7,    -1,    73,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   137,   138,     0,   140,     1,    88,   104,   106,   112,
     113,   114,   115,   116,   141,   145,   157,   159,   165,    76,
      78,   104,   166,   146,    78,    87,   102,   170,   102,   166,
     169,   117,   118,   120,   122,   124,   127,   147,   148,   149,
     150,   151,   152,   156,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    74,    75,
      78,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   107,   109,   110,   111,   163,   164,
     165,   167,   168,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   162,   163,    79,   169,    76,   162,   162,
     153,   166,   126,    70,    71,    70,    71,   165,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,   162,    78,    78,    80,    80,    78,    78,
      78,    78,    78,    78,    78,    80,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    73,    78,    82,     6,    79,
       3,     4,     5,     7,     3,     4,     5,     6,     7,    76,
      84,    85,    76,    76,   119,   121,   123,   131,   132,   133,
     154,   125,    29,    30,   192,   197,   197,   197,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   161,
     165,    79,   170,   170,   138,    14,    15,    70,    71,   143,
     144,   168,   165,   165,   165,   165,   162,   162,    78,   195,
     196,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   165,
     167,   139,   168,    87,   168,   168,   168,   168,   162,   162,
     162,   162,   162,    80,    80,   134,   134,   134,     6,   104,
     193,   166,   166,    79,    79,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,    79,    79,    79,    81,    70,
      71,    70,    71,     6,    81,     6,     6,     6,     6,     6,
      79,    79,   167,    81,   196,    79,    83,   140,   162,   139,
     142,   135,   135,   135,   102,   103,   171,    16,    78,     6,
       6,   168,   168,   168,   162,   162,   162,   168,   168,   168,
     165,    73,   144,   168,   168,   168,   168,   168,    79,   157,
      76,    81,     1,    26,    81,    86,   158,   160,   129,   130,
     155,   155,   155,     6,   193,    79,   194,   197,   171,   171,
       6,     6,     6,    79,    79,    79,     6,     6,    79,    78,
       6,     6,     6,     6,     6,   108,    76,   165,   139,    87,
     135,   135,   135,   169,    16,    78,     6,    79,    79,    79,
     168,   168,   168,   168,   168,   162,   162,   162,   162,   162,
     162,   162,    81,   162,    79,   193,    79,   194,   197,     6,
       6,     6,    79,    79,    79,    79,    79,    79,    79,    79,
      76,    76,    78,    79,   168,   168,   168,    79,   194,     6,
       6,     6,    79,   168,   168,   168,    79,    79,    79
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   141,   141,   142,   142,   143,   143,   144,   144,   144,
     144,   144,   144,   145,   145,   145,   145,   145,   146,   146,
     147,   147,   147,   147,   147,   147,   148,   148,   149,   150,
     151,   152,   153,   153,   154,   154,   154,   155,   155,   156,
     157,   157,   157,   158,   158,   159,   160,   161,   161,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   165,   166,   167,   167,   168,   168,   168,   168,   168,
     169,   170,   171,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   192,   192,   192,   192,   192,
     193,   194,   194,   195,   195,   196,   197,   197
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     2,
       2,     2,     2,     5,     4,     5,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     3,
       1,     3,     0,     2,     5,     5,     5,     1,     1,     3,
       7,     4,     2,     4,     2,     1,     2,     1,     3,     5,
       5,     7,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     8,     4,     1,     1,     1,     4,
       4,     4,     4,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       8,     7,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     6,     5,     7,     9,     4,     6,     8,
       1,     1,     3,     1,     2,     6,     1,     1
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
#line 345 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1749 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 348 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1755 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist variantlist statement  */
#line 349 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1761 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 352 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1767 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist variantlist definition  */
#line 353 "faustparser.y"
                                                                    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1773 "faustparser.cpp"
    break;

  case 7: /* variantlist: %empty  */
#line 356 "faustparser.y"
                                                        { (yyval.numvariant) = 0; }
#line 1779 "faustparser.cpp"
    break;

  case 8: /* variantlist: variantlist variant  */
#line 357 "faustparser.y"
                                                                                { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1785 "faustparser.cpp"
    break;

  case 9: /* variant: FLOATMODE  */
#line 360 "faustparser.y"
                                                                                        { (yyval.numvariant) = 1;}
#line 1791 "faustparser.cpp"
    break;

  case 10: /* variant: DOUBLEMODE  */
#line 361 "faustparser.y"
                                                                                        { (yyval.numvariant) = 2;}
#line 1797 "faustparser.cpp"
    break;

  case 11: /* variant: QUADMODE  */
#line 362 "faustparser.y"
                                                                                                { (yyval.numvariant) = 4;}
#line 1803 "faustparser.cpp"
    break;

  case 12: /* variant: FIXEDPOINTMODE  */
#line 363 "faustparser.y"
                                                    { (yyval.numvariant) = 8;}
#line 1809 "faustparser.cpp"
    break;

  case 13: /* reclist: %empty  */
#line 366 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1815 "faustparser.cpp"
    break;

  case 14: /* reclist: reclist recinition  */
#line 367 "faustparser.y"
                                                        { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1821 "faustparser.cpp"
    break;

  case 15: /* vallist: number  */
#line 374 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1827 "faustparser.cpp"
    break;

  case 16: /* vallist: vallist PAR number  */
#line 375 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1833 "faustparser.cpp"
    break;

  case 17: /* number: INT  */
#line 378 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(str2int(yytext)); }
#line 1839 "faustparser.cpp"
    break;

  case 18: /* number: FLOAT  */
#line 379 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 1845 "faustparser.cpp"
    break;

  case 19: /* number: ADD INT  */
#line 380 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(str2int(yytext)); }
#line 1851 "faustparser.cpp"
    break;

  case 20: /* number: ADD FLOAT  */
#line 381 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 1857 "faustparser.cpp"
    break;

  case 21: /* number: SUB INT  */
#line 382 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(-str2int(yytext)); }
#line 1863 "faustparser.cpp"
    break;

  case 22: /* number: SUB FLOAT  */
#line 383 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(-atof(yytext)); }
#line 1869 "faustparser.cpp"
    break;

  case 23: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 386 "faustparser.y"
                                                                { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1875 "faustparser.cpp"
    break;

  case 24: /* statement: DECLARE name string ENDDEF  */
#line 387 "faustparser.y"
                                                                                { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1881 "faustparser.cpp"
    break;

  case 25: /* statement: DECLARE name name string ENDDEF  */
#line 388 "faustparser.y"
                                                                                { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1887 "faustparser.cpp"
    break;

  case 26: /* statement: definition  */
#line 389 "faustparser.y"
                                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 1893 "faustparser.cpp"
    break;

  case 27: /* statement: BDOC doc EDOC  */
#line 390 "faustparser.y"
                                                                                                { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1899 "faustparser.cpp"
    break;

  case 28: /* doc: %empty  */
#line 393 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; }
#line 1905 "faustparser.cpp"
    break;

  case 29: /* doc: doc docelem  */
#line 394 "faustparser.y"
                                                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1911 "faustparser.cpp"
    break;

  case 30: /* docelem: doctxt  */
#line 397 "faustparser.y"
                                                                                        { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1917 "faustparser.cpp"
    break;

  case 31: /* docelem: doceqn  */
#line 398 "faustparser.y"
                                                                                                        { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1923 "faustparser.cpp"
    break;

  case 32: /* docelem: docdgm  */
#line 399 "faustparser.y"
                                                                                                        { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1929 "faustparser.cpp"
    break;

  case 33: /* docelem: docntc  */
#line 400 "faustparser.y"
                                                                                                        { (yyval.exp) = docNtc(); }
#line 1935 "faustparser.cpp"
    break;

  case 34: /* docelem: doclst  */
#line 401 "faustparser.y"
                                                                                        { (yyval.exp) = docLst(); }
#line 1941 "faustparser.cpp"
    break;

  case 35: /* docelem: docmtd  */
#line 402 "faustparser.y"
                                                                                                        { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1947 "faustparser.cpp"
    break;

  case 36: /* doctxt: %empty  */
#line 405 "faustparser.y"
                                                                                { (yyval.cppstr) = new string(); }
#line 1953 "faustparser.cpp"
    break;

  case 37: /* doctxt: doctxt DOCCHAR  */
#line 406 "faustparser.y"
                                                                                                { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1959 "faustparser.cpp"
    break;

  case 38: /* doceqn: BEQN expression EEQN  */
#line 409 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1965 "faustparser.cpp"
    break;

  case 39: /* docdgm: BDGM expression EDGM  */
#line 412 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1971 "faustparser.cpp"
    break;

  case 40: /* docntc: NOTICE  */
#line 415 "faustparser.y"
                                                                                        { }
#line 1977 "faustparser.cpp"
    break;

  case 41: /* doclst: BLST lstattrlist ELST  */
#line 418 "faustparser.y"
                                                                        { }
#line 1983 "faustparser.cpp"
    break;

  case 42: /* lstattrlist: %empty  */
#line 421 "faustparser.y"
                                                                                        { }
#line 1989 "faustparser.cpp"
    break;

  case 43: /* lstattrlist: lstattrlist lstattrdef  */
#line 422 "faustparser.y"
                                                                                        { }
#line 1995 "faustparser.cpp"
    break;

  case 44: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 425 "faustparser.y"
                                                                        { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2001 "faustparser.cpp"
    break;

  case 45: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 426 "faustparser.y"
                                                                                        { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2007 "faustparser.cpp"
    break;

  case 46: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 427 "faustparser.y"
                                                                                        { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2013 "faustparser.cpp"
    break;

  case 47: /* lstattrval: LSTTRUE  */
#line 430 "faustparser.y"
                                                                                                { (yyval.b) = true; }
#line 2019 "faustparser.cpp"
    break;

  case 48: /* lstattrval: LSTFALSE  */
#line 431 "faustparser.y"
                                                                                                        { (yyval.b) = false; }
#line 2025 "faustparser.cpp"
    break;

  case 49: /* docmtd: BMETADATA name EMETADATA  */
#line 434 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2031 "faustparser.cpp"
    break;

  case 50: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 437 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2037 "faustparser.cpp"
    break;

  case 51: /* definition: defname DEF expression ENDDEF  */
#line 438 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2043 "faustparser.cpp"
    break;

  case 52: /* definition: error ENDDEF  */
#line 439 "faustparser.y"
                                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2049 "faustparser.cpp"
    break;

  case 53: /* recinition: recname DEF expression ENDDEF  */
#line 442 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2055 "faustparser.cpp"
    break;

  case 54: /* recinition: error ENDDEF  */
#line 443 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2061 "faustparser.cpp"
    break;

  case 55: /* defname: ident  */
#line 446 "faustparser.y"
                                                                                                { (yyval.exp)=(yyvsp[0].exp); }
#line 2067 "faustparser.cpp"
    break;

  case 56: /* recname: DELAY1 ident  */
#line 449 "faustparser.y"
                                                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2073 "faustparser.cpp"
    break;

  case 57: /* params: ident  */
#line 452 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2079 "faustparser.cpp"
    break;

  case 58: /* params: params PAR ident  */
#line 453 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2085 "faustparser.cpp"
    break;

  case 59: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 456 "faustparser.y"
                                                                { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2091 "faustparser.cpp"
    break;

  case 60: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 457 "faustparser.y"
                                                        { (yyval.exp) = boxWithRecDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp)), gGlobal->nil); }
#line 2097 "faustparser.cpp"
    break;

  case 61: /* expression: expression LETREC LBRAQ reclist WHERE deflist RBRAQ  */
#line 458 "faustparser.y"
                                                                        { (yyval.exp) = boxWithRecDef((yyvsp[-6].exp),formatDefinitions((yyvsp[-3].exp)),formatDefinitions((yyvsp[-1].exp))); }
#line 2103 "faustparser.cpp"
    break;

  case 62: /* expression: expression PAR expression  */
#line 459 "faustparser.y"
                                                                { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2109 "faustparser.cpp"
    break;

  case 63: /* expression: expression SEQ expression  */
#line 460 "faustparser.y"
                                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2115 "faustparser.cpp"
    break;

  case 64: /* expression: expression SPLIT expression  */
#line 461 "faustparser.y"
                                                                            { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2121 "faustparser.cpp"
    break;

  case 65: /* expression: expression MIX expression  */
#line 462 "faustparser.y"
                                                                                { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2127 "faustparser.cpp"
    break;

  case 66: /* expression: expression REC expression  */
#line 463 "faustparser.y"
                                                                                { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2133 "faustparser.cpp"
    break;

  case 67: /* expression: infixexp  */
#line 464 "faustparser.y"
                                                                                            { (yyval.exp) = (yyvsp[0].exp); }
#line 2139 "faustparser.cpp"
    break;

  case 68: /* infixexp: infixexp ADD infixexp  */
#line 467 "faustparser.y"
                                                        { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2145 "faustparser.cpp"
    break;

  case 69: /* infixexp: infixexp SUB infixexp  */
#line 468 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2151 "faustparser.cpp"
    break;

  case 70: /* infixexp: infixexp MUL infixexp  */
#line 469 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2157 "faustparser.cpp"
    break;

  case 71: /* infixexp: infixexp DIV infixexp  */
#line 470 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2163 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp MOD infixexp  */
#line 471 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2169 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp POWOP infixexp  */
#line 472 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2175 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp FDELAY infixexp  */
#line 473 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDelay)); }
#line 2181 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp DELAY1  */
#line 474 "faustparser.y"
                                                                        { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2187 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp DOT ident  */
#line 475 "faustparser.y"
                                                                { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2193 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp AND infixexp  */
#line 477 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2199 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp OR infixexp  */
#line 478 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2205 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp XOR infixexp  */
#line 479 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2211 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp LSH infixexp  */
#line 481 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2217 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp RSH infixexp  */
#line 482 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigARightShift)); }
#line 2223 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp LT infixexp  */
#line 484 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2229 "faustparser.cpp"
    break;

  case 83: /* infixexp: infixexp LE infixexp  */
#line 485 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2235 "faustparser.cpp"
    break;

  case 84: /* infixexp: infixexp GT infixexp  */
#line 486 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2241 "faustparser.cpp"
    break;

  case 85: /* infixexp: infixexp GE infixexp  */
#line 487 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2247 "faustparser.cpp"
    break;

  case 86: /* infixexp: infixexp EQ infixexp  */
#line 488 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2253 "faustparser.cpp"
    break;

  case 87: /* infixexp: infixexp NE infixexp  */
#line 489 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2259 "faustparser.cpp"
    break;

  case 88: /* infixexp: infixexp LPAR arglist RPAR  */
#line 491 "faustparser.y"
                                                                { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2265 "faustparser.cpp"
    break;

  case 89: /* infixexp: infixexp LCROC deflist RCROC  */
#line 492 "faustparser.y"
                                                                { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2271 "faustparser.cpp"
    break;

  case 90: /* infixexp: primitive  */
#line 494 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2277 "faustparser.cpp"
    break;

  case 91: /* primitive: INT  */
#line 497 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(str2int(yytext)); }
#line 2283 "faustparser.cpp"
    break;

  case 92: /* primitive: FLOAT  */
#line 498 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 2289 "faustparser.cpp"
    break;

  case 93: /* primitive: ADD INT  */
#line 500 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (str2int(yytext)); }
#line 2295 "faustparser.cpp"
    break;

  case 94: /* primitive: ADD FLOAT  */
#line 501 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 2301 "faustparser.cpp"
    break;

  case 95: /* primitive: SUB INT  */
#line 503 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -str2int(yytext) ); }
#line 2307 "faustparser.cpp"
    break;

  case 96: /* primitive: SUB FLOAT  */
#line 504 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2313 "faustparser.cpp"
    break;

  case 97: /* primitive: WIRE  */
#line 506 "faustparser.y"
                                                                                        { (yyval.exp) = boxWire(); }
#line 2319 "faustparser.cpp"
    break;

  case 98: /* primitive: CUT  */
#line 507 "faustparser.y"
                                                                                        { (yyval.exp) = boxCut(); }
#line 2325 "faustparser.cpp"
    break;

  case 99: /* primitive: MEM  */
#line 509 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2331 "faustparser.cpp"
    break;

  case 100: /* primitive: PREFIX  */
#line 510 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2337 "faustparser.cpp"
    break;

  case 101: /* primitive: INTCAST  */
#line 512 "faustparser.y"
                                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2343 "faustparser.cpp"
    break;

  case 102: /* primitive: FLOATCAST  */
#line 513 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2349 "faustparser.cpp"
    break;

  case 103: /* primitive: ADD  */
#line 515 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAdd); }
#line 2355 "faustparser.cpp"
    break;

  case 104: /* primitive: SUB  */
#line 516 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigSub); }
#line 2361 "faustparser.cpp"
    break;

  case 105: /* primitive: MUL  */
#line 517 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigMul); }
#line 2367 "faustparser.cpp"
    break;

  case 106: /* primitive: DIV  */
#line 518 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDiv); }
#line 2373 "faustparser.cpp"
    break;

  case 107: /* primitive: MOD  */
#line 519 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRem); }
#line 2379 "faustparser.cpp"
    break;

  case 108: /* primitive: FDELAY  */
#line 520 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDelay); }
#line 2385 "faustparser.cpp"
    break;

  case 109: /* primitive: AND  */
#line 522 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAND); }
#line 2391 "faustparser.cpp"
    break;

  case 110: /* primitive: OR  */
#line 523 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigOR); }
#line 2397 "faustparser.cpp"
    break;

  case 111: /* primitive: XOR  */
#line 524 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigXOR); }
#line 2403 "faustparser.cpp"
    break;

  case 112: /* primitive: LSH  */
#line 526 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2409 "faustparser.cpp"
    break;

  case 113: /* primitive: RSH  */
#line 527 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigARightShift); }
#line 2415 "faustparser.cpp"
    break;

  case 114: /* primitive: LT  */
#line 529 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLT); }
#line 2421 "faustparser.cpp"
    break;

  case 115: /* primitive: LE  */
#line 530 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLE); }
#line 2427 "faustparser.cpp"
    break;

  case 116: /* primitive: GT  */
#line 531 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGT); }
#line 2433 "faustparser.cpp"
    break;

  case 117: /* primitive: GE  */
#line 532 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGE); }
#line 2439 "faustparser.cpp"
    break;

  case 118: /* primitive: EQ  */
#line 533 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigEQ); }
#line 2445 "faustparser.cpp"
    break;

  case 119: /* primitive: NE  */
#line 534 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigNE); }
#line 2451 "faustparser.cpp"
    break;

  case 120: /* primitive: ATTACH  */
#line 536 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAttach); }
#line 2457 "faustparser.cpp"
    break;

  case 121: /* primitive: ENABLE  */
#line 537 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2463 "faustparser.cpp"
    break;

  case 122: /* primitive: CONTROL  */
#line 538 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2469 "faustparser.cpp"
    break;

  case 123: /* primitive: ACOS  */
#line 540 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2475 "faustparser.cpp"
    break;

  case 124: /* primitive: ASIN  */
#line 541 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2481 "faustparser.cpp"
    break;

  case 125: /* primitive: ATAN  */
#line 542 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2487 "faustparser.cpp"
    break;

  case 126: /* primitive: ATAN2  */
#line 543 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2493 "faustparser.cpp"
    break;

  case 127: /* primitive: COS  */
#line 544 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2499 "faustparser.cpp"
    break;

  case 128: /* primitive: SIN  */
#line 545 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2505 "faustparser.cpp"
    break;

  case 129: /* primitive: TAN  */
#line 546 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2511 "faustparser.cpp"
    break;

  case 130: /* primitive: EXP  */
#line 548 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2517 "faustparser.cpp"
    break;

  case 131: /* primitive: LOG  */
#line 549 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2523 "faustparser.cpp"
    break;

  case 132: /* primitive: LOG10  */
#line 550 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2529 "faustparser.cpp"
    break;

  case 133: /* primitive: POWOP  */
#line 551 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2535 "faustparser.cpp"
    break;

  case 134: /* primitive: POWFUN  */
#line 552 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2541 "faustparser.cpp"
    break;

  case 135: /* primitive: SQRT  */
#line 553 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2547 "faustparser.cpp"
    break;

  case 136: /* primitive: ABS  */
#line 555 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2553 "faustparser.cpp"
    break;

  case 137: /* primitive: MIN  */
#line 556 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2559 "faustparser.cpp"
    break;

  case 138: /* primitive: MAX  */
#line 557 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2565 "faustparser.cpp"
    break;

  case 139: /* primitive: FMOD  */
#line 559 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2571 "faustparser.cpp"
    break;

  case 140: /* primitive: REMAINDER  */
#line 560 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2577 "faustparser.cpp"
    break;

  case 141: /* primitive: FLOOR  */
#line 562 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2583 "faustparser.cpp"
    break;

  case 142: /* primitive: CEIL  */
#line 563 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2589 "faustparser.cpp"
    break;

  case 143: /* primitive: RINT  */
#line 564 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2595 "faustparser.cpp"
    break;

  case 144: /* primitive: RDTBL  */
#line 566 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2601 "faustparser.cpp"
    break;

  case 145: /* primitive: RWTBL  */
#line 567 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2607 "faustparser.cpp"
    break;

  case 146: /* primitive: SELECT2  */
#line 569 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2613 "faustparser.cpp"
    break;

  case 147: /* primitive: SELECT3  */
#line 570 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2619 "faustparser.cpp"
    break;

  case 148: /* primitive: ASSERTBOUNDS  */
#line 572 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim3(sigAssertBounds);}
#line 2625 "faustparser.cpp"
    break;

  case 149: /* primitive: LOWEST  */
#line 573 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigLowest);}
#line 2631 "faustparser.cpp"
    break;

  case 150: /* primitive: HIGHEST  */
#line 574 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigHighest);}
#line 2637 "faustparser.cpp"
    break;

  case 151: /* primitive: ident  */
#line 576 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2643 "faustparser.cpp"
    break;

  case 152: /* primitive: SUB ident  */
#line 577 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2649 "faustparser.cpp"
    break;

  case 153: /* primitive: LPAR expression RPAR  */
#line 579 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2655 "faustparser.cpp"
    break;

  case 154: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 581 "faustparser.y"
                                                                                                { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2661 "faustparser.cpp"
    break;

  case 155: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 583 "faustparser.y"
                                                                        { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2667 "faustparser.cpp"
    break;

  case 156: /* primitive: ffunction  */
#line 585 "faustparser.y"
                                                                                        { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2673 "faustparser.cpp"
    break;

  case 157: /* primitive: fconst  */
#line 586 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2679 "faustparser.cpp"
    break;

  case 158: /* primitive: fvariable  */
#line 587 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2685 "faustparser.cpp"
    break;

  case 159: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 588 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2691 "faustparser.cpp"
    break;

  case 160: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 589 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2697 "faustparser.cpp"
    break;

  case 161: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 590 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2703 "faustparser.cpp"
    break;

  case 162: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 591 "faustparser.y"
                                                { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2709 "faustparser.cpp"
    break;

  case 163: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 592 "faustparser.y"
                                                                                                { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2715 "faustparser.cpp"
    break;

  case 164: /* primitive: button  */
#line 593 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2721 "faustparser.cpp"
    break;

  case 165: /* primitive: checkbox  */
#line 594 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2727 "faustparser.cpp"
    break;

  case 166: /* primitive: vslider  */
#line 595 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2733 "faustparser.cpp"
    break;

  case 167: /* primitive: hslider  */
#line 596 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2739 "faustparser.cpp"
    break;

  case 168: /* primitive: nentry  */
#line 597 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2745 "faustparser.cpp"
    break;

  case 169: /* primitive: vgroup  */
#line 598 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2751 "faustparser.cpp"
    break;

  case 170: /* primitive: hgroup  */
#line 599 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2757 "faustparser.cpp"
    break;

  case 171: /* primitive: tgroup  */
#line 600 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2763 "faustparser.cpp"
    break;

  case 172: /* primitive: vbargraph  */
#line 601 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2769 "faustparser.cpp"
    break;

  case 173: /* primitive: hbargraph  */
#line 602 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2775 "faustparser.cpp"
    break;

  case 174: /* primitive: soundfile  */
#line 603 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2781 "faustparser.cpp"
    break;

  case 175: /* primitive: fpar  */
#line 605 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2787 "faustparser.cpp"
    break;

  case 176: /* primitive: fseq  */
#line 606 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2793 "faustparser.cpp"
    break;

  case 177: /* primitive: fsum  */
#line 607 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2799 "faustparser.cpp"
    break;

  case 178: /* primitive: fprod  */
#line 608 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2805 "faustparser.cpp"
    break;

  case 179: /* primitive: finputs  */
#line 610 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2811 "faustparser.cpp"
    break;

  case 180: /* primitive: foutputs  */
#line 611 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2817 "faustparser.cpp"
    break;

  case 181: /* ident: IDENT  */
#line 615 "faustparser.y"
                                                                                { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2823 "faustparser.cpp"
    break;

  case 182: /* name: IDENT  */
#line 618 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2829 "faustparser.cpp"
    break;

  case 183: /* arglist: argument  */
#line 621 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2835 "faustparser.cpp"
    break;

  case 184: /* arglist: arglist PAR argument  */
#line 622 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2841 "faustparser.cpp"
    break;

  case 185: /* argument: argument SEQ argument  */
#line 625 "faustparser.y"
                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2847 "faustparser.cpp"
    break;

  case 186: /* argument: argument SPLIT argument  */
#line 626 "faustparser.y"
                                                                        { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2853 "faustparser.cpp"
    break;

  case 187: /* argument: argument MIX argument  */
#line 627 "faustparser.y"
                                                                        { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2859 "faustparser.cpp"
    break;

  case 188: /* argument: argument REC argument  */
#line 628 "faustparser.y"
                                                                        { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2865 "faustparser.cpp"
    break;

  case 189: /* argument: infixexp  */
#line 629 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2871 "faustparser.cpp"
    break;

  case 190: /* string: STRING  */
#line 632 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2877 "faustparser.cpp"
    break;

  case 191: /* uqstring: STRING  */
#line 635 "faustparser.y"
                                                                                { (yyval.exp) = unquote(yytext); }
#line 2883 "faustparser.cpp"
    break;

  case 192: /* fstring: STRING  */
#line 638 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2889 "faustparser.cpp"
    break;

  case 193: /* fstring: FSTRING  */
#line 639 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2895 "faustparser.cpp"
    break;

  case 194: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 645 "faustparser.y"
                                                                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2901 "faustparser.cpp"
    break;

  case 195: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 649 "faustparser.y"
                                                                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2907 "faustparser.cpp"
    break;

  case 196: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 653 "faustparser.y"
                                                                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2913 "faustparser.cpp"
    break;

  case 197: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 657 "faustparser.y"
                                                                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2919 "faustparser.cpp"
    break;

  case 198: /* finputs: INPUTS LPAR expression RPAR  */
#line 660 "faustparser.y"
                                                      { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2925 "faustparser.cpp"
    break;

  case 199: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 663 "faustparser.y"
                                                       { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2931 "faustparser.cpp"
    break;

  case 200: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 669 "faustparser.y"
                                                                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2937 "faustparser.cpp"
    break;

  case 201: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 673 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2943 "faustparser.cpp"
    break;

  case 202: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 677 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2949 "faustparser.cpp"
    break;

  case 203: /* button: BUTTON LPAR uqstring RPAR  */
#line 681 "faustparser.y"
                                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2955 "faustparser.cpp"
    break;

  case 204: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 684 "faustparser.y"
                                                        { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2961 "faustparser.cpp"
    break;

  case 205: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 688 "faustparser.y"
                                                                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2967 "faustparser.cpp"
    break;

  case 206: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 691 "faustparser.y"
                                                                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2973 "faustparser.cpp"
    break;

  case 207: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 694 "faustparser.y"
                                                                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2979 "faustparser.cpp"
    break;

  case 208: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 697 "faustparser.y"
                                                                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2985 "faustparser.cpp"
    break;

  case 209: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 700 "faustparser.y"
                                                                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2991 "faustparser.cpp"
    break;

  case 210: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 703 "faustparser.y"
                                                                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2997 "faustparser.cpp"
    break;

  case 211: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 707 "faustparser.y"
                                                                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3003 "faustparser.cpp"
    break;

  case 212: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 710 "faustparser.y"
                                                                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3009 "faustparser.cpp"
    break;

  case 213: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 713 "faustparser.y"
                                                                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3015 "faustparser.cpp"
    break;

  case 214: /* signature: type fun LPAR typelist RPAR  */
#line 719 "faustparser.y"
                                                                    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3021 "faustparser.cpp"
    break;

  case 215: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 720 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3027 "faustparser.cpp"
    break;

  case 216: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 721 "faustparser.y"
                                                                { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3033 "faustparser.cpp"
    break;

  case 217: /* signature: type fun LPAR RPAR  */
#line 723 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3039 "faustparser.cpp"
    break;

  case 218: /* signature: type fun OR fun LPAR RPAR  */
#line 724 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3045 "faustparser.cpp"
    break;

  case 219: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 725 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3051 "faustparser.cpp"
    break;

  case 220: /* fun: IDENT  */
#line 728 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 3057 "faustparser.cpp"
    break;

  case 221: /* typelist: type  */
#line 731 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3063 "faustparser.cpp"
    break;

  case 222: /* typelist: typelist PAR type  */
#line 732 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3069 "faustparser.cpp"
    break;

  case 223: /* rulelist: rule  */
#line 735 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3075 "faustparser.cpp"
    break;

  case 224: /* rulelist: rulelist rule  */
#line 736 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3081 "faustparser.cpp"
    break;

  case 225: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 740 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3087 "faustparser.cpp"
    break;

  case 226: /* type: INTCAST  */
#line 743 "faustparser.y"
                                                        { (yyval.exp) = tree(0); }
#line 3093 "faustparser.cpp"
    break;

  case 227: /* type: FLOATCAST  */
#line 744 "faustparser.y"
                                                                                        { (yyval.exp) = tree(1); }
#line 3099 "faustparser.cpp"
    break;


#line 3103 "faustparser.cpp"

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

#line 747 "faustparser.y"

