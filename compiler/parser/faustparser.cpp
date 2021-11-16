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


#line 138 "faustparser.cpp"

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
  YYSYMBOL_ONDEMAND = 102,                 /* ONDEMAND  */
  YYSYMBOL_STRING = 103,                   /* STRING  */
  YYSYMBOL_FSTRING = 104,                  /* FSTRING  */
  YYSYMBOL_IDENT = 105,                    /* IDENT  */
  YYSYMBOL_EXTRA = 106,                    /* EXTRA  */
  YYSYMBOL_DECLARE = 107,                  /* DECLARE  */
  YYSYMBOL_CASE = 108,                     /* CASE  */
  YYSYMBOL_ARROW = 109,                    /* ARROW  */
  YYSYMBOL_BDOC = 110,                     /* BDOC  */
  YYSYMBOL_EDOC = 111,                     /* EDOC  */
  YYSYMBOL_BEQN = 112,                     /* BEQN  */
  YYSYMBOL_EEQN = 113,                     /* EEQN  */
  YYSYMBOL_BDGM = 114,                     /* BDGM  */
  YYSYMBOL_EDGM = 115,                     /* EDGM  */
  YYSYMBOL_BLST = 116,                     /* BLST  */
  YYSYMBOL_ELST = 117,                     /* ELST  */
  YYSYMBOL_BMETADATA = 118,                /* BMETADATA  */
  YYSYMBOL_EMETADATA = 119,                /* EMETADATA  */
  YYSYMBOL_DOCCHAR = 120,                  /* DOCCHAR  */
  YYSYMBOL_NOTICE = 121,                   /* NOTICE  */
  YYSYMBOL_LISTING = 122,                  /* LISTING  */
  YYSYMBOL_LSTTRUE = 123,                  /* LSTTRUE  */
  YYSYMBOL_LSTFALSE = 124,                 /* LSTFALSE  */
  YYSYMBOL_LSTDEPENDENCIES = 125,          /* LSTDEPENDENCIES  */
  YYSYMBOL_LSTMDOCTAGS = 126,              /* LSTMDOCTAGS  */
  YYSYMBOL_LSTDISTRIBUTED = 127,           /* LSTDISTRIBUTED  */
  YYSYMBOL_LSTEQ = 128,                    /* LSTEQ  */
  YYSYMBOL_LSTQ = 129,                     /* LSTQ  */
  YYSYMBOL_YYACCEPT = 130,                 /* $accept  */
  YYSYMBOL_program = 131,                  /* program  */
  YYSYMBOL_stmtlist = 132,                 /* stmtlist  */
  YYSYMBOL_deflist = 133,                  /* deflist  */
  YYSYMBOL_reclist = 134,                  /* reclist  */
  YYSYMBOL_vallist = 135,                  /* vallist  */
  YYSYMBOL_number = 136,                   /* number  */
  YYSYMBOL_statement = 137,                /* statement  */
  YYSYMBOL_doc = 138,                      /* doc  */
  YYSYMBOL_docelem = 139,                  /* docelem  */
  YYSYMBOL_doctxt = 140,                   /* doctxt  */
  YYSYMBOL_doceqn = 141,                   /* doceqn  */
  YYSYMBOL_docdgm = 142,                   /* docdgm  */
  YYSYMBOL_docntc = 143,                   /* docntc  */
  YYSYMBOL_doclst = 144,                   /* doclst  */
  YYSYMBOL_lstattrlist = 145,              /* lstattrlist  */
  YYSYMBOL_lstattrdef = 146,               /* lstattrdef  */
  YYSYMBOL_lstattrval = 147,               /* lstattrval  */
  YYSYMBOL_docmtd = 148,                   /* docmtd  */
  YYSYMBOL_definition = 149,               /* definition  */
  YYSYMBOL_recinition = 150,               /* recinition  */
  YYSYMBOL_defname = 151,                  /* defname  */
  YYSYMBOL_recname = 152,                  /* recname  */
  YYSYMBOL_params = 153,                   /* params  */
  YYSYMBOL_expression = 154,               /* expression  */
  YYSYMBOL_infixexp = 155,                 /* infixexp  */
  YYSYMBOL_primitive = 156,                /* primitive  */
  YYSYMBOL_ident = 157,                    /* ident  */
  YYSYMBOL_name = 158,                     /* name  */
  YYSYMBOL_arglist = 159,                  /* arglist  */
  YYSYMBOL_argument = 160,                 /* argument  */
  YYSYMBOL_string = 161,                   /* string  */
  YYSYMBOL_uqstring = 162,                 /* uqstring  */
  YYSYMBOL_fstring = 163,                  /* fstring  */
  YYSYMBOL_fpar = 164,                     /* fpar  */
  YYSYMBOL_fseq = 165,                     /* fseq  */
  YYSYMBOL_fsum = 166,                     /* fsum  */
  YYSYMBOL_fprod = 167,                    /* fprod  */
  YYSYMBOL_finputs = 168,                  /* finputs  */
  YYSYMBOL_foutputs = 169,                 /* foutputs  */
  YYSYMBOL_fondemand = 170,                /* fondemand  */
  YYSYMBOL_ffunction = 171,                /* ffunction  */
  YYSYMBOL_fconst = 172,                   /* fconst  */
  YYSYMBOL_fvariable = 173,                /* fvariable  */
  YYSYMBOL_button = 174,                   /* button  */
  YYSYMBOL_checkbox = 175,                 /* checkbox  */
  YYSYMBOL_vslider = 176,                  /* vslider  */
  YYSYMBOL_hslider = 177,                  /* hslider  */
  YYSYMBOL_nentry = 178,                   /* nentry  */
  YYSYMBOL_vgroup = 179,                   /* vgroup  */
  YYSYMBOL_hgroup = 180,                   /* hgroup  */
  YYSYMBOL_tgroup = 181,                   /* tgroup  */
  YYSYMBOL_vbargraph = 182,                /* vbargraph  */
  YYSYMBOL_hbargraph = 183,                /* hbargraph  */
  YYSYMBOL_soundfile = 184,                /* soundfile  */
  YYSYMBOL_signature = 185,                /* signature  */
  YYSYMBOL_fun = 186,                      /* fun  */
  YYSYMBOL_typelist = 187,                 /* typelist  */
  YYSYMBOL_rulelist = 188,                 /* rulelist  */
  YYSYMBOL_rule = 189,                     /* rule  */
  YYSYMBOL_type = 190                      /* type  */
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
#define YYLAST   768

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  481

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   384


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
     125,   126,   127,   128,   129
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   319,   319,   322,   323,   325,   326,   330,   331,   338,
     339,   342,   343,   344,   345,   346,   347,   351,   352,   353,
     354,   355,   358,   359,   362,   363,   364,   365,   366,   367,
     370,   371,   374,   377,   380,   383,   386,   387,   390,   391,
     392,   395,   396,   399,   402,   403,   404,   407,   408,   411,
     414,   417,   418,   421,   422,   423,   424,   425,   426,   427,
     428,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     441,   442,   443,   445,   446,   448,   449,   450,   451,   452,
     453,   455,   456,   458,   461,   462,   464,   465,   467,   468,
     470,   471,   473,   474,   476,   477,   479,   480,   481,   482,
     483,   484,   486,   487,   488,   490,   491,   493,   494,   495,
     496,   497,   498,   500,   501,   502,   505,   506,   507,   508,
     509,   510,   511,   513,   514,   515,   516,   517,   518,   520,
     521,   522,   524,   525,   527,   528,   529,   532,   533,   535,
     536,   538,   539,   541,   542,   545,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   567,   568,   569,   570,   572,
     573,   574,   579,   582,   587,   588,   591,   592,   593,   594,
     595,   598,   601,   604,   605,   610,   614,   618,   622,   627,
     630,   633,   638,   642,   645,   650,   653,   656,   659,   662,
     665,   668,   671,   675,   678,   681,   688,   689,   690,   692,
     693,   694,   697,   700,   701,   704,   705,   708,   712,   713
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
  "IPROD", "INPUTS", "OUTPUTS", "ONDEMAND", "STRING", "FSTRING", "IDENT",
  "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC", "BEQN", "EEQN",
  "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR",
  "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "reclist", "vallist", "number", "statement",
  "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "definition",
  "recinition", "defname", "recname", "params", "expression", "infixexp",
  "primitive", "ident", "name", "arglist", "argument", "string",
  "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod", "finputs",
  "foutputs", "fondemand", "ffunction", "fconst", "fvariable", "button",
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384
};
#endif

#define YYPACT_NINF (-378)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -378,     9,    25,  -378,   -23,    31,  -378,   -13,  -378,  -378,
    -378,    18,  -378,  -378,    15,  -378,   -42,   290,   418,   418,
    -378,    51,  -378,    19,    35,  -378,   418,   418,  -378,   -13,
    -378,  -378,    -4,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,   148,    29,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
      78,    82,   134,   157,   202,   208,   210,   213,   221,   260,
     262,   267,   278,   281,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,   284,  -378,  -378,   418,   285,   287,    59,    64,   293,
    -378,  -378,   297,   306,   307,   308,   309,   312,   313,   242,
     574,  -378,  -378,    16,   376,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,    42,   574,   265,   316,
    -378,    13,     8,   228,   239,  -378,  -378,  -378,  -378,  -378,
    -378,   199,   199,   199,    15,    15,    15,    15,    15,    15,
      15,    15,    15,    15,    15,   245,    53,    15,    15,  -378,
     231,   418,   245,   245,   245,   245,   418,   418,   418,   326,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,  -378,   245,
     418,  -378,   418,   274,   418,   418,   418,   418,   418,   418,
     418,   418,   418,  -378,   328,   331,  -378,  -378,  -378,  -378,
    -378,   286,   295,   296,  -378,  -378,  -378,  -378,   401,   310,
     -13,   -13,   333,   365,   486,   489,   490,   497,   498,   499,
     500,   515,   516,    44,  -378,  -378,   444,   445,     1,   172,
     181,  -378,  -378,    21,  -378,   639,   526,   527,   533,   534,
      66,    73,   205,   418,   -47,  -378,   548,   548,   548,   548,
     548,   548,   615,   615,   615,   291,   291,   291,   291,   291,
     291,   291,   273,   299,  -378,    49,    20,   376,   418,   376,
     376,    83,  -378,   670,   670,   271,   253,  -378,  -378,  -378,
     422,   423,   427,   -29,  -378,    36,   552,   553,  -378,  -378,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   245,
     487,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   231,  -378,
     418,   418,   418,   418,   418,  -378,  -378,  -378,    56,  -378,
    -378,  -378,  -378,  -378,   211,    32,    27,   198,   198,   198,
    -378,  -378,   554,   310,    90,   -29,   -29,   675,   680,   696,
     234,   244,   251,   701,   706,    37,  -378,   522,  -378,   711,
     716,   721,   726,   731,   467,  -378,  -378,   501,   245,  -378,
    -378,   492,  -378,  -378,   448,   473,   474,    19,    68,  -378,
      75,  -378,   525,   528,   418,   418,   418,  -378,  -378,  -378,
     418,   418,  -378,   418,   418,   418,   418,   418,   418,   418,
    -378,  -378,   418,  -378,  -378,  -378,   532,   310,   162,   199,
    -378,  -378,  -378,   736,   741,   746,    61,   191,   258,   304,
     495,   524,   531,   538,   263,   543,  -378,   535,  -378,    76,
    -378,   418,   418,   418,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,   282,  -378,   751,   756,   761,  -378,
      80,   418,   418,   418,  -378,   279,   364,   550,  -378,  -378,
    -378
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   172,     0,    22,     4,
      20,     0,    49,    46,     0,   173,     0,    30,     0,     0,
     182,     0,   181,     0,     0,    21,     0,     0,    36,     0,
      34,    23,    24,    25,    26,    27,    28,    29,   107,   108,
     111,   109,   110,   112,    96,    97,   103,    98,    99,   100,
     102,   104,   105,   106,   126,   101,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    84,
      85,     0,    90,    91,     0,     0,     0,     0,     0,     0,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
     180,    83,   141,     0,   174,   165,   166,   167,   168,   169,
     170,   171,   146,   147,   148,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,    60,     0,     0,
      18,     0,     0,     0,     0,    31,    86,    87,    88,    89,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,    17,    19,    32,    33,
      35,     0,     0,     0,    37,    43,   218,   219,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,   143,     0,     0,     0,     0,
       0,    11,    12,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,    75,    76,    79,    77,
      78,    80,    61,    62,    71,    63,    64,    65,    70,    72,
      73,    74,    66,    67,    69,     0,     0,   175,     0,   177,
     178,   176,   179,    57,    58,    56,    55,    59,     5,     7,
       0,     0,     0,     0,   212,     0,     0,     0,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,    13,    14,    15,    16,     0,   152,
       0,     0,     0,     0,     0,   189,   190,   191,     0,   145,
     216,    81,    82,     6,     0,     0,     0,     0,     0,     0,
     183,   184,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,    10,     0,
       0,     0,     0,     0,     0,    44,    53,     0,     0,    54,
       8,     0,    41,    42,     0,     0,     0,     0,     0,   209,
       0,   213,     0,     0,     0,     0,     0,   200,   201,   202,
       0,     0,   205,     0,     0,     0,     0,     0,     0,     0,
      48,    50,     0,    38,    39,    40,     0,     0,     0,     0,
     206,   193,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,   210,     0,
     214,     0,     0,     0,   204,   203,   144,   153,   185,   186,
     187,   188,   217,    47,     0,   207,     0,     0,     0,   211,
       0,     0,     0,     0,   208,     0,     0,     0,   197,   198,
     199
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -378,  -378,   428,   298,  -378,  -378,   275,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,   -26,  -378,  -253,
    -378,  -378,  -378,  -378,     3,   -19,  -378,    22,    -6,  -119,
    -178,   -22,   494,   -31,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -332,  -377,  -378,   341,
    -157
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,   296,   356,   263,   264,     9,    17,    31,
      32,    33,    34,    35,    36,   153,   234,   394,    37,    10,
     390,    11,   391,   253,   146,   120,   121,   122,    16,   123,
     124,    24,    21,   362,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   238,   315,   400,   274,   275,
     401
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     147,   149,     4,   265,   239,   240,   241,   147,   147,     3,
      23,   218,   219,   220,   221,   222,   218,   219,   220,   221,
     222,     4,   212,   154,    12,    -2,     4,   338,   387,   151,
     152,   398,   273,     4,   297,   349,   299,   300,   301,   302,
     214,   215,   216,   353,   217,   218,   219,   220,   221,   222,
     329,   449,   363,   388,    13,   212,   218,   219,   220,   221,
     222,    22,   212,    15,   214,   215,   216,   160,   217,   218,
     219,   220,   221,   222,   360,   361,   218,   219,   220,   221,
     222,   429,   429,   333,   427,   147,   429,   470,   216,     5,
     217,   295,    15,   224,   225,   447,   213,    18,   224,   225,
     158,   159,   353,   339,   352,    19,     6,   176,     7,   389,
      14,     8,   150,     5,   386,   364,   155,   412,    20,   223,
     236,   237,    22,   229,   330,     6,   228,   224,   225,   351,
       6,   148,     7,   255,     6,     8,   384,     6,   224,   225,
     179,   454,   367,   368,   369,   180,   345,   428,   373,   374,
     375,   224,   225,   346,   348,   430,   465,   161,   224,   225,
     474,   162,   379,   380,   381,   382,   383,   147,   147,   147,
     399,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   270,
     271,   272,   236,   237,   214,   215,   216,   254,   217,   147,
     147,   147,   147,   147,   266,   267,   268,   269,   218,   219,
     220,   221,   222,   163,   218,   219,   220,   221,   222,   156,
     157,   303,   304,   305,   306,   307,   433,   434,   435,   236,
     237,   294,   436,   437,   316,   317,   164,   218,   219,   220,
     221,   222,   448,   334,   335,   259,   260,   218,   219,   220,
     221,   222,   336,   337,   218,   219,   220,   221,   222,   221,
     222,   218,   219,   220,   221,   222,   218,   219,   220,   221,
     222,   455,   450,   466,   467,   468,   220,   221,   222,   147,
      12,   165,   214,   215,   216,   347,   217,   166,   385,   167,
     224,   225,   168,   475,   476,   477,   224,   225,   207,   208,
     169,   354,   261,   262,   147,   147,   147,   218,   219,   220,
     221,   222,   236,   237,   407,   206,   207,   208,    12,   224,
     225,   392,   393,   189,   408,   208,   370,   371,   372,   224,
     225,   409,   395,   396,   402,   403,   224,   225,   456,   170,
     462,   171,   226,   224,   225,   230,   172,   209,   224,   225,
       6,   376,   210,   231,   232,   233,   211,   173,   235,   478,
     174,   298,   469,   175,   177,   209,   178,   214,   215,   216,
     210,   217,   181,   209,   211,   426,   182,    12,   210,   214,
     215,   216,   211,   217,   457,   183,   184,   185,   186,   224,
     225,   187,   188,   227,   147,   147,   147,   147,   147,   147,
     147,    25,    26,   147,    27,   273,    28,   313,    29,   308,
     421,    30,   309,   318,   310,   314,   438,   439,   440,   441,
     442,   443,   444,   311,   312,   445,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   479,   319,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   320,   102,   103,   321,   322,   104,   218,   219,
     220,   221,   222,   323,   324,   325,   326,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   327,   328,     6,   331,   332,   119,   218,   219,   220,
     221,   222,   341,   342,   218,   219,   220,   221,   222,   343,
     344,   218,   219,   220,   221,   222,   218,   219,   220,   221,
     222,   357,   358,   214,   215,   216,   359,   217,   365,   366,
     397,   377,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   458,   419,   423,   420,   422,
     224,   225,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   413,   424,   425,   459,   431,   355,   258,   432,   224,
     225,   460,   446,   378,   464,   350,   224,   225,   461,     0,
     463,     0,   209,   224,   225,     0,     0,   210,   224,   225,
     480,   211,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   214,   215,   216,   340,   217,     0,   209,     0,
       0,     0,     0,   210,     0,     0,     0,   211,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,     0,
       0,   256,   257,   218,   219,   220,   221,   222,   214,   215,
     216,   404,   217,   214,   215,   216,   405,   217,     0,   209,
       0,     0,     0,     0,   210,     0,     0,     0,   211,   214,
     215,   216,   406,   217,   214,   215,   216,   410,   217,   214,
     215,   216,   411,   217,   214,   215,   216,   414,   217,   214,
     215,   216,   415,   217,   214,   215,   216,   416,   217,   214,
     215,   216,   417,   217,   214,   215,   216,   418,   217,   214,
     215,   216,   451,   217,   214,   215,   216,   452,   217,   214,
     215,   216,   453,   217,   214,   215,   216,   471,   217,   214,
     215,   216,   472,   217,   214,   215,   216,   473,   217
};

static const yytype_int16 yycheck[] =
{
      19,    23,     1,   181,   161,   162,   163,    26,    27,     0,
      16,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     1,     6,    29,     2,     0,     1,     6,     1,    26,
      27,   363,    79,     1,   212,    82,   214,   215,   216,   217,
       3,     4,     5,   296,     7,     3,     4,     5,     6,     7,
       6,   428,    16,    26,    77,     6,     3,     4,     5,     6,
       7,   103,     6,   105,     3,     4,     5,    45,     7,     3,
       4,     5,     6,     7,   103,   104,     3,     4,     5,     6,
       7,     6,     6,    82,    16,   104,     6,   464,     5,    88,
       7,   210,   105,    85,    86,   427,    80,    79,    85,    86,
      71,    72,   355,    82,    84,    87,   105,   104,   107,    82,
      79,   110,    77,    88,    82,    79,   120,    80,   103,    77,
      30,    31,   103,   115,    80,   105,   113,    85,    86,    80,
     105,    80,   107,    80,   105,   110,    80,   105,    85,    86,
      81,    80,   320,   321,   322,    81,    80,    79,   326,   327,
     328,    85,    86,    80,   273,    80,    80,    79,    85,    86,
      80,    79,   340,   341,   342,   343,   344,   186,   187,   188,
      80,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   186,
     187,   188,    30,    31,     3,     4,     5,   175,     7,   218,
     219,   220,   221,   222,   182,   183,   184,   185,     3,     4,
       5,     6,     7,    79,     3,     4,     5,     6,     7,    71,
      72,   218,   219,   220,   221,   222,   404,   405,   406,    30,
      31,   209,   410,   411,   240,   241,    79,     3,     4,     5,
       6,     7,    80,    71,    72,    14,    15,     3,     4,     5,
       6,     7,    71,    72,     3,     4,     5,     6,     7,     6,
       7,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,    80,   429,   451,   452,   453,     5,     6,     7,   298,
     258,    79,     3,     4,     5,    80,     7,    79,    77,    79,
      85,    86,    79,   471,   472,   473,    85,    86,    25,    26,
      79,   298,    71,    72,   323,   324,   325,     3,     4,     5,
       6,     7,    30,    31,    80,    24,    25,    26,   296,    85,
      86,   123,   124,    81,    80,    26,   323,   324,   325,    85,
      86,    80,   358,   359,   365,   366,    85,    86,    80,    79,
      77,    79,    77,    85,    86,   117,    79,    74,    85,    86,
     105,   329,    79,   125,   126,   127,    83,    79,   119,    80,
      79,    87,    80,    79,    79,    74,    79,     3,     4,     5,
      79,     7,    79,    74,    83,   397,    79,   355,    79,     3,
       4,     5,    83,     7,    80,    79,    79,    79,    79,    85,
      86,    79,    79,    77,   413,   414,   415,   416,   417,   418,
     419,   111,   112,   422,   114,    79,   116,     6,   118,    81,
     388,   121,    81,    80,   128,   105,   413,   414,   415,   416,
     417,   418,   419,   128,   128,   422,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    80,    80,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     6,    75,    76,     6,     6,    79,     3,     4,
       5,     6,     7,     6,     6,     6,     6,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,     6,     6,   105,    80,    80,   108,     3,     4,     5,
       6,     7,     6,     6,     3,     4,     5,     6,     7,     6,
       6,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,   129,   129,     3,     4,     5,   129,     7,     6,     6,
       6,    74,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    80,   109,   129,    77,    87,
      85,    86,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    79,   129,   129,    80,    80,   308,   179,    80,    85,
      86,    80,    80,   338,    79,   274,    85,    86,    80,    -1,
      77,    -1,    74,    85,    86,    -1,    -1,    79,    85,    86,
      80,    83,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     3,     4,     5,     6,     7,    -1,    74,    -1,
      -1,    -1,    -1,    79,    -1,    -1,    -1,    83,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,    -1,
      -1,   177,   178,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    -1,    74,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
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
       0,   131,   132,     0,     1,    88,   105,   107,   110,   137,
     149,   151,   157,    77,    79,   105,   158,   138,    79,    87,
     103,   162,   103,   158,   161,   111,   112,   114,   116,   118,
     121,   139,   140,   141,   142,   143,   144,   148,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    75,    76,    79,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   108,
     155,   156,   157,   159,   160,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   154,   155,    80,   161,
      77,   154,   154,   145,   158,   120,    71,    72,    71,    72,
     157,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,   154,    79,    79,    81,
      81,    79,    79,    79,    79,    79,    79,    79,    79,    81,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    74,
      79,    83,     6,    80,     3,     4,     5,     7,     3,     4,
       5,     6,     7,    77,    85,    86,    77,    77,   113,   115,
     117,   125,   126,   127,   146,   119,    30,    31,   185,   190,
     190,   190,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   153,   157,    80,   162,   162,   132,    14,
      15,    71,    72,   135,   136,   160,   157,   157,   157,   157,
     154,   154,   154,    79,   188,   189,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   157,   159,   133,   160,    87,   160,
     160,   160,   160,   154,   154,   154,   154,   154,    81,    81,
     128,   128,   128,     6,   105,   186,   158,   158,    80,    80,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
      80,    80,    80,    82,    71,    72,    71,    72,     6,    82,
       6,     6,     6,     6,     6,    80,    80,    80,   159,    82,
     189,    80,    84,   149,   154,   133,   134,   129,   129,   129,
     103,   104,   163,    16,    79,     6,     6,   160,   160,   160,
     154,   154,   154,   160,   160,   160,   157,    74,   136,   160,
     160,   160,   160,   160,    80,    77,    82,     1,    26,    82,
     150,   152,   123,   124,   147,   147,   147,     6,   186,    80,
     187,   190,   163,   163,     6,     6,     6,    80,    80,    80,
       6,     6,    80,    79,     6,     6,     6,     6,     6,   109,
      77,   157,    87,   129,   129,   129,   161,    16,    79,     6,
      80,    80,    80,   160,   160,   160,   160,   160,   154,   154,
     154,   154,   154,   154,   154,   154,    80,   186,    80,   187,
     190,     6,     6,     6,    80,    80,    80,    80,    80,    80,
      80,    80,    77,    77,    79,    80,   160,   160,   160,    80,
     187,     6,     6,     6,    80,   160,   160,   160,    80,    80,
      80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   130,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   137,
     137,   137,   138,   138,   139,   139,   139,   139,   139,   139,
     140,   140,   141,   142,   143,   144,   145,   145,   146,   146,
     146,   147,   147,   148,   149,   149,   149,   150,   150,   151,
     152,   153,   153,   154,   154,   154,   154,   154,   154,   154,
     154,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   157,   158,   159,   159,   160,   160,   160,   160,
     160,   161,   162,   163,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   185,   185,   185,
     185,   185,   186,   187,   187,   188,   188,   189,   190,   190
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     0,     2,     1,
       3,     1,     1,     2,     2,     2,     2,     5,     4,     5,
       1,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       0,     2,     3,     3,     1,     3,     0,     2,     5,     5,
       5,     1,     1,     3,     7,     4,     2,     4,     2,     1,
       2,     1,     3,     5,     5,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     4,     1,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     8,     4,     1,     1,     1,     4,
       4,     4,     4,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     8,     8,     8,     8,     4,
       4,     4,     8,     7,     7,     4,     4,    12,    12,    12,
       6,     6,     6,     8,     8,     6,     5,     7,     9,     4,
       6,     8,     1,     1,     3,     1,     2,     6,     1,     1
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
#line 319 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1730 "faustparser.cpp"
    break;

  case 3: /* stmtlist: %empty  */
#line 322 "faustparser.y"
                                                { (yyval.exp) = gGlobal->nil; }
#line 1736 "faustparser.cpp"
    break;

  case 4: /* stmtlist: stmtlist statement  */
#line 323 "faustparser.y"
                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1742 "faustparser.cpp"
    break;

  case 5: /* deflist: %empty  */
#line 325 "faustparser.y"
                                                { (yyval.exp) = gGlobal->nil; }
#line 1748 "faustparser.cpp"
    break;

  case 6: /* deflist: deflist definition  */
#line 326 "faustparser.y"
                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1754 "faustparser.cpp"
    break;

  case 7: /* reclist: %empty  */
#line 330 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1760 "faustparser.cpp"
    break;

  case 8: /* reclist: reclist recinition  */
#line 331 "faustparser.y"
                                                        { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1766 "faustparser.cpp"
    break;

  case 9: /* vallist: number  */
#line 338 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1772 "faustparser.cpp"
    break;

  case 10: /* vallist: vallist PAR number  */
#line 339 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1778 "faustparser.cpp"
    break;

  case 11: /* number: INT  */
#line 342 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1784 "faustparser.cpp"
    break;

  case 12: /* number: FLOAT  */
#line 343 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 1790 "faustparser.cpp"
    break;

  case 13: /* number: ADD INT  */
#line 344 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1796 "faustparser.cpp"
    break;

  case 14: /* number: ADD FLOAT  */
#line 345 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 1802 "faustparser.cpp"
    break;

  case 15: /* number: SUB INT  */
#line 346 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1808 "faustparser.cpp"
    break;

  case 16: /* number: SUB FLOAT  */
#line 347 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1814 "faustparser.cpp"
    break;

  case 17: /* statement: IMPORT LPAR uqstring RPAR ENDDEF  */
#line 351 "faustparser.y"
                                                                { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1820 "faustparser.cpp"
    break;

  case 18: /* statement: DECLARE name string ENDDEF  */
#line 352 "faustparser.y"
                                                                                { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1826 "faustparser.cpp"
    break;

  case 19: /* statement: DECLARE name name string ENDDEF  */
#line 353 "faustparser.y"
                                                                                { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1832 "faustparser.cpp"
    break;

  case 20: /* statement: definition  */
#line 354 "faustparser.y"
                                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 1838 "faustparser.cpp"
    break;

  case 21: /* statement: BDOC doc EDOC  */
#line 355 "faustparser.y"
                                                                                                { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1844 "faustparser.cpp"
    break;

  case 22: /* doc: %empty  */
#line 358 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; }
#line 1850 "faustparser.cpp"
    break;

  case 23: /* doc: doc docelem  */
#line 359 "faustparser.y"
                                                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1856 "faustparser.cpp"
    break;

  case 24: /* docelem: doctxt  */
#line 362 "faustparser.y"
                                                                                        { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1862 "faustparser.cpp"
    break;

  case 25: /* docelem: doceqn  */
#line 363 "faustparser.y"
                                                                                                        { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1868 "faustparser.cpp"
    break;

  case 26: /* docelem: docdgm  */
#line 364 "faustparser.y"
                                                                                                        { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1874 "faustparser.cpp"
    break;

  case 27: /* docelem: docntc  */
#line 365 "faustparser.y"
                                                                                                        { (yyval.exp) = docNtc(); }
#line 1880 "faustparser.cpp"
    break;

  case 28: /* docelem: doclst  */
#line 366 "faustparser.y"
                                                                                        { (yyval.exp) = docLst(); }
#line 1886 "faustparser.cpp"
    break;

  case 29: /* docelem: docmtd  */
#line 367 "faustparser.y"
                                                                                                        { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1892 "faustparser.cpp"
    break;

  case 30: /* doctxt: %empty  */
#line 370 "faustparser.y"
                                                                                { (yyval.cppstr) = new string(); }
#line 1898 "faustparser.cpp"
    break;

  case 31: /* doctxt: doctxt DOCCHAR  */
#line 371 "faustparser.y"
                                                                                                { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1904 "faustparser.cpp"
    break;

  case 32: /* doceqn: BEQN expression EEQN  */
#line 374 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1910 "faustparser.cpp"
    break;

  case 33: /* docdgm: BDGM expression EDGM  */
#line 377 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1916 "faustparser.cpp"
    break;

  case 34: /* docntc: NOTICE  */
#line 380 "faustparser.y"
                                                                                        { }
#line 1922 "faustparser.cpp"
    break;

  case 35: /* doclst: BLST lstattrlist ELST  */
#line 383 "faustparser.y"
                                                                        { }
#line 1928 "faustparser.cpp"
    break;

  case 36: /* lstattrlist: %empty  */
#line 386 "faustparser.y"
                                                                                        { }
#line 1934 "faustparser.cpp"
    break;

  case 37: /* lstattrlist: lstattrlist lstattrdef  */
#line 387 "faustparser.y"
                                                                                        { }
#line 1940 "faustparser.cpp"
    break;

  case 38: /* lstattrdef: LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ  */
#line 390 "faustparser.y"
                                                                        { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1946 "faustparser.cpp"
    break;

  case 39: /* lstattrdef: LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ  */
#line 391 "faustparser.y"
                                                                                        { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 1952 "faustparser.cpp"
    break;

  case 40: /* lstattrdef: LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ  */
#line 392 "faustparser.y"
                                                                                        { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 1958 "faustparser.cpp"
    break;

  case 41: /* lstattrval: LSTTRUE  */
#line 395 "faustparser.y"
                                                                                                { (yyval.b) = true; }
#line 1964 "faustparser.cpp"
    break;

  case 42: /* lstattrval: LSTFALSE  */
#line 396 "faustparser.y"
                                                                                                        { (yyval.b) = false; }
#line 1970 "faustparser.cpp"
    break;

  case 43: /* docmtd: BMETADATA name EMETADATA  */
#line 399 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 1976 "faustparser.cpp"
    break;

  case 44: /* definition: defname LPAR arglist RPAR DEF expression ENDDEF  */
#line 402 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 1982 "faustparser.cpp"
    break;

  case 45: /* definition: defname DEF expression ENDDEF  */
#line 403 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 1988 "faustparser.cpp"
    break;

  case 46: /* definition: error ENDDEF  */
#line 404 "faustparser.y"
                                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 1994 "faustparser.cpp"
    break;

  case 47: /* recinition: recname DEF expression ENDDEF  */
#line 407 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2000 "faustparser.cpp"
    break;

  case 48: /* recinition: error ENDDEF  */
#line 408 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2006 "faustparser.cpp"
    break;

  case 49: /* defname: ident  */
#line 411 "faustparser.y"
                                                                                                { (yyval.exp)=(yyvsp[0].exp); }
#line 2012 "faustparser.cpp"
    break;

  case 50: /* recname: DELAY1 ident  */
#line 414 "faustparser.y"
                                                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2018 "faustparser.cpp"
    break;

  case 51: /* params: ident  */
#line 417 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2024 "faustparser.cpp"
    break;

  case 52: /* params: params PAR ident  */
#line 418 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2030 "faustparser.cpp"
    break;

  case 53: /* expression: expression WITH LBRAQ deflist RBRAQ  */
#line 421 "faustparser.y"
                                                                { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2036 "faustparser.cpp"
    break;

  case 54: /* expression: expression LETREC LBRAQ reclist RBRAQ  */
#line 422 "faustparser.y"
                                                        { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2042 "faustparser.cpp"
    break;

  case 55: /* expression: expression PAR expression  */
#line 423 "faustparser.y"
                                                                { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2048 "faustparser.cpp"
    break;

  case 56: /* expression: expression SEQ expression  */
#line 424 "faustparser.y"
                                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2054 "faustparser.cpp"
    break;

  case 57: /* expression: expression SPLIT expression  */
#line 425 "faustparser.y"
                                                                            { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2060 "faustparser.cpp"
    break;

  case 58: /* expression: expression MIX expression  */
#line 426 "faustparser.y"
                                                                                { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2066 "faustparser.cpp"
    break;

  case 59: /* expression: expression REC expression  */
#line 427 "faustparser.y"
                                                                                { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2072 "faustparser.cpp"
    break;

  case 60: /* expression: infixexp  */
#line 428 "faustparser.y"
                                                                                            { (yyval.exp) = (yyvsp[0].exp); }
#line 2078 "faustparser.cpp"
    break;

  case 61: /* infixexp: infixexp ADD infixexp  */
#line 431 "faustparser.y"
                                                        { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2084 "faustparser.cpp"
    break;

  case 62: /* infixexp: infixexp SUB infixexp  */
#line 432 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2090 "faustparser.cpp"
    break;

  case 63: /* infixexp: infixexp MUL infixexp  */
#line 433 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2096 "faustparser.cpp"
    break;

  case 64: /* infixexp: infixexp DIV infixexp  */
#line 434 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2102 "faustparser.cpp"
    break;

  case 65: /* infixexp: infixexp MOD infixexp  */
#line 435 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2108 "faustparser.cpp"
    break;

  case 66: /* infixexp: infixexp POWOP infixexp  */
#line 436 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2114 "faustparser.cpp"
    break;

  case 67: /* infixexp: infixexp FDELAY infixexp  */
#line 437 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxDelay()); }
#line 2120 "faustparser.cpp"
    break;

  case 68: /* infixexp: infixexp DELAY1  */
#line 438 "faustparser.y"
                                                                        { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxMem()); }
#line 2126 "faustparser.cpp"
    break;

  case 69: /* infixexp: infixexp DOT ident  */
#line 439 "faustparser.y"
                                                                { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2132 "faustparser.cpp"
    break;

  case 70: /* infixexp: infixexp AND infixexp  */
#line 441 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2138 "faustparser.cpp"
    break;

  case 71: /* infixexp: infixexp OR infixexp  */
#line 442 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2144 "faustparser.cpp"
    break;

  case 72: /* infixexp: infixexp XOR infixexp  */
#line 443 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2150 "faustparser.cpp"
    break;

  case 73: /* infixexp: infixexp LSH infixexp  */
#line 445 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2156 "faustparser.cpp"
    break;

  case 74: /* infixexp: infixexp RSH infixexp  */
#line 446 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2162 "faustparser.cpp"
    break;

  case 75: /* infixexp: infixexp LT infixexp  */
#line 448 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2168 "faustparser.cpp"
    break;

  case 76: /* infixexp: infixexp LE infixexp  */
#line 449 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2174 "faustparser.cpp"
    break;

  case 77: /* infixexp: infixexp GT infixexp  */
#line 450 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2180 "faustparser.cpp"
    break;

  case 78: /* infixexp: infixexp GE infixexp  */
#line 451 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2186 "faustparser.cpp"
    break;

  case 79: /* infixexp: infixexp EQ infixexp  */
#line 452 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2192 "faustparser.cpp"
    break;

  case 80: /* infixexp: infixexp NE infixexp  */
#line 453 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2198 "faustparser.cpp"
    break;

  case 81: /* infixexp: infixexp LPAR arglist RPAR  */
#line 455 "faustparser.y"
                                                                                { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2204 "faustparser.cpp"
    break;

  case 82: /* infixexp: infixexp LCROC deflist RCROC  */
#line 456 "faustparser.y"
                                                                                { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2210 "faustparser.cpp"
    break;

  case 83: /* infixexp: primitive  */
#line 458 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2216 "faustparser.cpp"
    break;

  case 84: /* primitive: INT  */
#line 461 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2222 "faustparser.cpp"
    break;

  case 85: /* primitive: FLOAT  */
#line 462 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 2228 "faustparser.cpp"
    break;

  case 86: /* primitive: ADD INT  */
#line 464 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2234 "faustparser.cpp"
    break;

  case 87: /* primitive: ADD FLOAT  */
#line 465 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 2240 "faustparser.cpp"
    break;

  case 88: /* primitive: SUB INT  */
#line 467 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2246 "faustparser.cpp"
    break;

  case 89: /* primitive: SUB FLOAT  */
#line 468 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2252 "faustparser.cpp"
    break;

  case 90: /* primitive: WIRE  */
#line 470 "faustparser.y"
                                                                                        { (yyval.exp) = boxWire(); }
#line 2258 "faustparser.cpp"
    break;

  case 91: /* primitive: CUT  */
#line 471 "faustparser.y"
                                                                                        { (yyval.exp) = boxCut(); }
#line 2264 "faustparser.cpp"
    break;

  case 92: /* primitive: MEM  */
#line 473 "faustparser.y"
                                                                                        { (yyval.exp) = boxMem(); }
#line 2270 "faustparser.cpp"
    break;

  case 93: /* primitive: PREFIX  */
#line 474 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2276 "faustparser.cpp"
    break;

  case 94: /* primitive: INTCAST  */
#line 476 "faustparser.y"
                                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2282 "faustparser.cpp"
    break;

  case 95: /* primitive: FLOATCAST  */
#line 477 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2288 "faustparser.cpp"
    break;

  case 96: /* primitive: ADD  */
#line 479 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAdd); }
#line 2294 "faustparser.cpp"
    break;

  case 97: /* primitive: SUB  */
#line 480 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigSub); }
#line 2300 "faustparser.cpp"
    break;

  case 98: /* primitive: MUL  */
#line 481 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigMul); }
#line 2306 "faustparser.cpp"
    break;

  case 99: /* primitive: DIV  */
#line 482 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDiv); }
#line 2312 "faustparser.cpp"
    break;

  case 100: /* primitive: MOD  */
#line 483 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRem); }
#line 2318 "faustparser.cpp"
    break;

  case 101: /* primitive: FDELAY  */
#line 484 "faustparser.y"
                                                                                        { (yyval.exp) = boxDelay(); }
#line 2324 "faustparser.cpp"
    break;

  case 102: /* primitive: AND  */
#line 486 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAND); }
#line 2330 "faustparser.cpp"
    break;

  case 103: /* primitive: OR  */
#line 487 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigOR); }
#line 2336 "faustparser.cpp"
    break;

  case 104: /* primitive: XOR  */
#line 488 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigXOR); }
#line 2342 "faustparser.cpp"
    break;

  case 105: /* primitive: LSH  */
#line 490 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2348 "faustparser.cpp"
    break;

  case 106: /* primitive: RSH  */
#line 491 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2354 "faustparser.cpp"
    break;

  case 107: /* primitive: LT  */
#line 493 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLT); }
#line 2360 "faustparser.cpp"
    break;

  case 108: /* primitive: LE  */
#line 494 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLE); }
#line 2366 "faustparser.cpp"
    break;

  case 109: /* primitive: GT  */
#line 495 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGT); }
#line 2372 "faustparser.cpp"
    break;

  case 110: /* primitive: GE  */
#line 496 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGE); }
#line 2378 "faustparser.cpp"
    break;

  case 111: /* primitive: EQ  */
#line 497 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigEQ); }
#line 2384 "faustparser.cpp"
    break;

  case 112: /* primitive: NE  */
#line 498 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigNE); }
#line 2390 "faustparser.cpp"
    break;

  case 113: /* primitive: ATTACH  */
#line 500 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAttach); }
#line 2396 "faustparser.cpp"
    break;

  case 114: /* primitive: ENABLE  */
#line 501 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2402 "faustparser.cpp"
    break;

  case 115: /* primitive: CONTROL  */
#line 502 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2408 "faustparser.cpp"
    break;

  case 116: /* primitive: ACOS  */
#line 505 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2414 "faustparser.cpp"
    break;

  case 117: /* primitive: ASIN  */
#line 506 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2420 "faustparser.cpp"
    break;

  case 118: /* primitive: ATAN  */
#line 507 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2426 "faustparser.cpp"
    break;

  case 119: /* primitive: ATAN2  */
#line 508 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2432 "faustparser.cpp"
    break;

  case 120: /* primitive: COS  */
#line 509 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2438 "faustparser.cpp"
    break;

  case 121: /* primitive: SIN  */
#line 510 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2444 "faustparser.cpp"
    break;

  case 122: /* primitive: TAN  */
#line 511 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2450 "faustparser.cpp"
    break;

  case 123: /* primitive: EXP  */
#line 513 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2456 "faustparser.cpp"
    break;

  case 124: /* primitive: LOG  */
#line 514 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2462 "faustparser.cpp"
    break;

  case 125: /* primitive: LOG10  */
#line 515 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2468 "faustparser.cpp"
    break;

  case 126: /* primitive: POWOP  */
#line 516 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2474 "faustparser.cpp"
    break;

  case 127: /* primitive: POWFUN  */
#line 517 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2480 "faustparser.cpp"
    break;

  case 128: /* primitive: SQRT  */
#line 518 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2486 "faustparser.cpp"
    break;

  case 129: /* primitive: ABS  */
#line 520 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2492 "faustparser.cpp"
    break;

  case 130: /* primitive: MIN  */
#line 521 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2498 "faustparser.cpp"
    break;

  case 131: /* primitive: MAX  */
#line 522 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2504 "faustparser.cpp"
    break;

  case 132: /* primitive: FMOD  */
#line 524 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2510 "faustparser.cpp"
    break;

  case 133: /* primitive: REMAINDER  */
#line 525 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2516 "faustparser.cpp"
    break;

  case 134: /* primitive: FLOOR  */
#line 527 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2522 "faustparser.cpp"
    break;

  case 135: /* primitive: CEIL  */
#line 528 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2528 "faustparser.cpp"
    break;

  case 136: /* primitive: RINT  */
#line 529 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2534 "faustparser.cpp"
    break;

  case 137: /* primitive: RDTBL  */
#line 532 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2540 "faustparser.cpp"
    break;

  case 138: /* primitive: RWTBL  */
#line 533 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2546 "faustparser.cpp"
    break;

  case 139: /* primitive: SELECT2  */
#line 535 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2552 "faustparser.cpp"
    break;

  case 140: /* primitive: SELECT3  */
#line 536 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2558 "faustparser.cpp"
    break;

  case 141: /* primitive: ident  */
#line 538 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2564 "faustparser.cpp"
    break;

  case 142: /* primitive: SUB ident  */
#line 539 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2570 "faustparser.cpp"
    break;

  case 143: /* primitive: LPAR expression RPAR  */
#line 541 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2576 "faustparser.cpp"
    break;

  case 144: /* primitive: LAMBDA LPAR params RPAR DOT LPAR expression RPAR  */
#line 543 "faustparser.y"
                                                                                                { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2582 "faustparser.cpp"
    break;

  case 145: /* primitive: CASE LBRAQ rulelist RBRAQ  */
#line 545 "faustparser.y"
                                                                        { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2588 "faustparser.cpp"
    break;

  case 146: /* primitive: ffunction  */
#line 547 "faustparser.y"
                                                                                        { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2594 "faustparser.cpp"
    break;

  case 147: /* primitive: fconst  */
#line 548 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2600 "faustparser.cpp"
    break;

  case 148: /* primitive: fvariable  */
#line 549 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2606 "faustparser.cpp"
    break;

  case 149: /* primitive: COMPONENT LPAR uqstring RPAR  */
#line 550 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2612 "faustparser.cpp"
    break;

  case 150: /* primitive: LIBRARY LPAR uqstring RPAR  */
#line 551 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2618 "faustparser.cpp"
    break;

  case 151: /* primitive: ENVIRONMENT LBRAQ stmtlist RBRAQ  */
#line 552 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2624 "faustparser.cpp"
    break;

  case 152: /* primitive: WAVEFORM LBRAQ vallist RBRAQ  */
#line 553 "faustparser.y"
                                                { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2630 "faustparser.cpp"
    break;

  case 153: /* primitive: ROUTE LPAR argument PAR argument PAR expression RPAR  */
#line 554 "faustparser.y"
                                                                                                { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2636 "faustparser.cpp"
    break;

  case 154: /* primitive: button  */
#line 555 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2642 "faustparser.cpp"
    break;

  case 155: /* primitive: checkbox  */
#line 556 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2648 "faustparser.cpp"
    break;

  case 156: /* primitive: vslider  */
#line 557 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2654 "faustparser.cpp"
    break;

  case 157: /* primitive: hslider  */
#line 558 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2660 "faustparser.cpp"
    break;

  case 158: /* primitive: nentry  */
#line 559 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2666 "faustparser.cpp"
    break;

  case 159: /* primitive: vgroup  */
#line 560 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2672 "faustparser.cpp"
    break;

  case 160: /* primitive: hgroup  */
#line 561 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2678 "faustparser.cpp"
    break;

  case 161: /* primitive: tgroup  */
#line 562 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2684 "faustparser.cpp"
    break;

  case 162: /* primitive: vbargraph  */
#line 563 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2690 "faustparser.cpp"
    break;

  case 163: /* primitive: hbargraph  */
#line 564 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2696 "faustparser.cpp"
    break;

  case 164: /* primitive: soundfile  */
#line 565 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2702 "faustparser.cpp"
    break;

  case 165: /* primitive: fpar  */
#line 567 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2708 "faustparser.cpp"
    break;

  case 166: /* primitive: fseq  */
#line 568 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2714 "faustparser.cpp"
    break;

  case 167: /* primitive: fsum  */
#line 569 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2720 "faustparser.cpp"
    break;

  case 168: /* primitive: fprod  */
#line 570 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2726 "faustparser.cpp"
    break;

  case 169: /* primitive: finputs  */
#line 572 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2732 "faustparser.cpp"
    break;

  case 170: /* primitive: foutputs  */
#line 573 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2738 "faustparser.cpp"
    break;

  case 171: /* primitive: fondemand  */
#line 574 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2744 "faustparser.cpp"
    break;

  case 172: /* ident: IDENT  */
#line 579 "faustparser.y"
                                                                                { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2750 "faustparser.cpp"
    break;

  case 173: /* name: IDENT  */
#line 582 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2756 "faustparser.cpp"
    break;

  case 174: /* arglist: argument  */
#line 587 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2762 "faustparser.cpp"
    break;

  case 175: /* arglist: arglist PAR argument  */
#line 588 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2768 "faustparser.cpp"
    break;

  case 176: /* argument: argument SEQ argument  */
#line 591 "faustparser.y"
                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2774 "faustparser.cpp"
    break;

  case 177: /* argument: argument SPLIT argument  */
#line 592 "faustparser.y"
                                                                        { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2780 "faustparser.cpp"
    break;

  case 178: /* argument: argument MIX argument  */
#line 593 "faustparser.y"
                                                                        { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2786 "faustparser.cpp"
    break;

  case 179: /* argument: argument REC argument  */
#line 594 "faustparser.y"
                                                                        { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2792 "faustparser.cpp"
    break;

  case 180: /* argument: infixexp  */
#line 595 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2798 "faustparser.cpp"
    break;

  case 181: /* string: STRING  */
#line 598 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2804 "faustparser.cpp"
    break;

  case 182: /* uqstring: STRING  */
#line 601 "faustparser.y"
                                                                                { (yyval.exp) = unquote(yytext); }
#line 2810 "faustparser.cpp"
    break;

  case 183: /* fstring: STRING  */
#line 604 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2816 "faustparser.cpp"
    break;

  case 184: /* fstring: FSTRING  */
#line 605 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2822 "faustparser.cpp"
    break;

  case 185: /* fpar: IPAR LPAR ident PAR argument PAR expression RPAR  */
#line 611 "faustparser.y"
                                                                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2828 "faustparser.cpp"
    break;

  case 186: /* fseq: ISEQ LPAR ident PAR argument PAR expression RPAR  */
#line 615 "faustparser.y"
                                                                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2834 "faustparser.cpp"
    break;

  case 187: /* fsum: ISUM LPAR ident PAR argument PAR expression RPAR  */
#line 619 "faustparser.y"
                                                                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2840 "faustparser.cpp"
    break;

  case 188: /* fprod: IPROD LPAR ident PAR argument PAR expression RPAR  */
#line 623 "faustparser.y"
                                                                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2846 "faustparser.cpp"
    break;

  case 189: /* finputs: INPUTS LPAR expression RPAR  */
#line 627 "faustparser.y"
                                                      { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2852 "faustparser.cpp"
    break;

  case 190: /* foutputs: OUTPUTS LPAR expression RPAR  */
#line 630 "faustparser.y"
                                                       { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2858 "faustparser.cpp"
    break;

  case 191: /* fondemand: ONDEMAND LPAR expression RPAR  */
#line 633 "faustparser.y"
                                                { (yyval.exp) = boxOndemand((yyvsp[-1].exp)); }
#line 2864 "faustparser.cpp"
    break;

  case 192: /* ffunction: FFUNCTION LPAR signature PAR fstring PAR string RPAR  */
#line 639 "faustparser.y"
                                                                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2870 "faustparser.cpp"
    break;

  case 193: /* fconst: FCONSTANT LPAR type name PAR fstring RPAR  */
#line 643 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2876 "faustparser.cpp"
    break;

  case 194: /* fvariable: FVARIABLE LPAR type name PAR fstring RPAR  */
#line 646 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2882 "faustparser.cpp"
    break;

  case 195: /* button: BUTTON LPAR uqstring RPAR  */
#line 650 "faustparser.y"
                                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2888 "faustparser.cpp"
    break;

  case 196: /* checkbox: CHECKBOX LPAR uqstring RPAR  */
#line 653 "faustparser.y"
                                                                { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2894 "faustparser.cpp"
    break;

  case 197: /* vslider: VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 657 "faustparser.y"
                                                                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2900 "faustparser.cpp"
    break;

  case 198: /* hslider: HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 660 "faustparser.y"
                                                                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2906 "faustparser.cpp"
    break;

  case 199: /* nentry: NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR  */
#line 663 "faustparser.y"
                                                                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2912 "faustparser.cpp"
    break;

  case 200: /* vgroup: VGROUP LPAR uqstring PAR expression RPAR  */
#line 666 "faustparser.y"
                                                                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2918 "faustparser.cpp"
    break;

  case 201: /* hgroup: HGROUP LPAR uqstring PAR expression RPAR  */
#line 669 "faustparser.y"
                                                                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2924 "faustparser.cpp"
    break;

  case 202: /* tgroup: TGROUP LPAR uqstring PAR expression RPAR  */
#line 672 "faustparser.y"
                                                                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2930 "faustparser.cpp"
    break;

  case 203: /* vbargraph: VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 676 "faustparser.y"
                                                                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2936 "faustparser.cpp"
    break;

  case 204: /* hbargraph: HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR  */
#line 679 "faustparser.y"
                                                                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2942 "faustparser.cpp"
    break;

  case 205: /* soundfile: SOUNDFILE LPAR uqstring PAR argument RPAR  */
#line 682 "faustparser.y"
                                                                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2948 "faustparser.cpp"
    break;

  case 206: /* signature: type fun LPAR typelist RPAR  */
#line 688 "faustparser.y"
                                                                    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2954 "faustparser.cpp"
    break;

  case 207: /* signature: type fun OR fun LPAR typelist RPAR  */
#line 689 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2960 "faustparser.cpp"
    break;

  case 208: /* signature: type fun OR fun OR fun LPAR typelist RPAR  */
#line 690 "faustparser.y"
                                                                { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2966 "faustparser.cpp"
    break;

  case 209: /* signature: type fun LPAR RPAR  */
#line 692 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2972 "faustparser.cpp"
    break;

  case 210: /* signature: type fun OR fun LPAR RPAR  */
#line 693 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2978 "faustparser.cpp"
    break;

  case 211: /* signature: type fun OR fun OR fun LPAR RPAR  */
#line 694 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2984 "faustparser.cpp"
    break;

  case 212: /* fun: IDENT  */
#line 697 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2990 "faustparser.cpp"
    break;

  case 213: /* typelist: type  */
#line 700 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2996 "faustparser.cpp"
    break;

  case 214: /* typelist: typelist PAR type  */
#line 701 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3002 "faustparser.cpp"
    break;

  case 215: /* rulelist: rule  */
#line 704 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3008 "faustparser.cpp"
    break;

  case 216: /* rulelist: rulelist rule  */
#line 705 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3014 "faustparser.cpp"
    break;

  case 217: /* rule: LPAR arglist RPAR ARROW expression ENDDEF  */
#line 709 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3020 "faustparser.cpp"
    break;

  case 218: /* type: INTCAST  */
#line 712 "faustparser.y"
                                                        { (yyval.exp) = tree(0); }
#line 3026 "faustparser.cpp"
    break;

  case 219: /* type: FLOATCAST  */
#line 713 "faustparser.y"
                                                                                        { (yyval.exp) = tree(1); }
#line 3032 "faustparser.cpp"
    break;


#line 3036 "faustparser.cpp"

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

#line 716 "faustparser.y"


