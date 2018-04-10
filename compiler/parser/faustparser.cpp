/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 5 "faustparser.y" /* yacc.c:339  */


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
char replaceCR(char c)
{
	return (c!='\n') ? c : ' ';
}

Tree unquote(char* str)
{
	//-----------copy unquoted filename-------------
	char buf[512];
	int j=0;

	if (str[0] == '"') {
		//it is a quoted string, we remove the quotes
		for (int i=1; j<511 && str[i];) {
			buf[j++] = replaceCR(str[i++]);
		}
		// remove last quote
		if (j>0) buf[j-1] = 0;
	} else {
		for (int i=0; j<511 && str[i];) {
			buf[j++] = replaceCR(str[i++]);
		}
	}
	buf[j] = 0;

	return tree(buf);
	//----------------------------------------------
}


#line 131 "faustparser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "faustparser.hpp".  */
#ifndef YY_YY_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_FAUSTPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WITH = 258,
    LETREC = 259,
    SPLIT = 260,
    MIX = 261,
    SEQ = 262,
    PAR = 263,
    REC = 264,
    LT = 265,
    LE = 266,
    EQ = 267,
    GT = 268,
    GE = 269,
    NE = 270,
    ADD = 271,
    SUB = 272,
    OR = 273,
    MUL = 274,
    DIV = 275,
    MOD = 276,
    AND = 277,
    XOR = 278,
    LSH = 279,
    RSH = 280,
    POWOP = 281,
    FDELAY = 282,
    DELAY1 = 283,
    APPL = 284,
    DOT = 285,
    MEM = 286,
    PREFIX = 287,
    INTCAST = 288,
    FLOATCAST = 289,
    FFUNCTION = 290,
    FCONSTANT = 291,
    FVARIABLE = 292,
    BUTTON = 293,
    CHECKBOX = 294,
    VSLIDER = 295,
    HSLIDER = 296,
    NENTRY = 297,
    VGROUP = 298,
    HGROUP = 299,
    TGROUP = 300,
    HBARGRAPH = 301,
    VBARGRAPH = 302,
    SOUNDFILE = 303,
    ATTACH = 304,
    ACOS = 305,
    ASIN = 306,
    ATAN = 307,
    ATAN2 = 308,
    COS = 309,
    SIN = 310,
    TAN = 311,
    EXP = 312,
    LOG = 313,
    LOG10 = 314,
    POWFUN = 315,
    SQRT = 316,
    ABS = 317,
    MIN = 318,
    MAX = 319,
    FMOD = 320,
    REMAINDER = 321,
    FLOOR = 322,
    CEIL = 323,
    RINT = 324,
    RDTBL = 325,
    RWTBL = 326,
    SELECT2 = 327,
    SELECT3 = 328,
    INT = 329,
    FLOAT = 330,
    LAMBDA = 331,
    WIRE = 332,
    CUT = 333,
    ENDDEF = 334,
    VIRG = 335,
    LPAR = 336,
    RPAR = 337,
    LBRAQ = 338,
    RBRAQ = 339,
    LCROC = 340,
    RCROC = 341,
    DEF = 342,
    IMPORT = 343,
    COMPONENT = 344,
    LIBRARY = 345,
    ENVIRONMENT = 346,
    WAVEFORM = 347,
    ENABLE = 348,
    CONTROL = 349,
    IPAR = 350,
    ISEQ = 351,
    ISUM = 352,
    IPROD = 353,
    INPUTS = 354,
    OUTPUTS = 355,
    STRING = 356,
    FSTRING = 357,
    IDENT = 358,
    EXTRA = 359,
    DECLARE = 360,
    CASE = 361,
    ARROW = 362,
    BDOC = 363,
    EDOC = 364,
    BEQN = 365,
    EEQN = 366,
    BDGM = 367,
    EDGM = 368,
    BLST = 369,
    ELST = 370,
    BMETADATA = 371,
    EMETADATA = 372,
    DOCCHAR = 373,
    NOTICE = 374,
    LISTING = 375,
    LSTTRUE = 376,
    LSTFALSE = 377,
    LSTDEPENDENCIES = 378,
    LSTMDOCTAGS = 379,
    LSTDISTRIBUTED = 380,
    LSTEQ = 381,
    LSTQ = 382
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 71 "faustparser.y" /* yacc.c:355  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 306 "faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 323 "faustparser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   710

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  216
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  468

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   382

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
     125,   126,   127
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   314,   314,   317,   318,   320,   321,   325,   326,   333,
     334,   337,   338,   339,   340,   341,   342,   346,   347,   348,
     349,   350,   353,   354,   357,   358,   359,   360,   361,   362,
     365,   366,   369,   372,   375,   378,   381,   382,   385,   386,
     387,   390,   391,   394,   397,   398,   399,   402,   403,   406,
     409,   412,   413,   416,   417,   418,   419,   420,   421,   422,
     423,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     436,   437,   438,   440,   441,   443,   444,   445,   446,   447,
     448,   450,   451,   453,   456,   457,   459,   460,   462,   463,
     465,   466,   468,   469,   471,   472,   474,   475,   476,   477,
     478,   479,   481,   482,   483,   485,   486,   488,   489,   490,
     491,   492,   493,   495,   496,   497,   500,   501,   502,   503,
     504,   505,   506,   508,   509,   510,   511,   512,   513,   515,
     516,   517,   519,   520,   522,   523,   524,   527,   528,   530,
     531,   533,   534,   536,   537,   540,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   561,   562,   563,   564,   566,   567,
     572,   575,   580,   581,   584,   585,   586,   587,   588,   591,
     594,   597,   598,   603,   607,   611,   615,   620,   623,   630,
     634,   637,   642,   645,   648,   651,   654,   657,   660,   663,
     667,   670,   673,   680,   681,   682,   684,   685,   686,   689,
     692,   693,   696,   697,   700,   704,   705
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "LETREC", "SPLIT", "MIX", "SEQ",
  "PAR", "REC", "LT", "LE", "EQ", "GT", "GE", "NE", "ADD", "SUB", "OR",
  "MUL", "DIV", "MOD", "AND", "XOR", "LSH", "RSH", "POWOP", "FDELAY",
  "DELAY1", "APPL", "DOT", "MEM", "PREFIX", "INTCAST", "FLOATCAST",
  "FFUNCTION", "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER",
  "HSLIDER", "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH",
  "VBARGRAPH", "SOUNDFILE", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2",
  "COS", "SIN", "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS",
  "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL",
  "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT",
  "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC",
  "DEF", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM",
  "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS",
  "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST",
  "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE",
  "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ",
  "LSTQ", "$accept", "program", "stmtlist", "deflist", "reclist",
  "vallist", "number", "statement", "doc", "docelem", "doctxt", "doceqn",
  "docdgm", "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval",
  "docmtd", "definition", "recinition", "defname", "recname", "params",
  "expression", "infixexp", "primitive", "ident", "name", "arglist",
  "argument", "string", "uqstring", "fstring", "fpar", "fseq", "fsum",
  "fprod", "finputs", "foutputs", "ffunction", "fconst", "fvariable",
  "button", "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup",
  "tgroup", "vbargraph", "hbargraph", "soundfile", "signature", "fun",
  "typelist", "rulelist", "rule", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
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
     375,   376,   377,   378,   379,   380,   381,   382
};
# endif

#define YYPACT_NINF -315

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-315)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -315,    97,    45,  -315,   -55,    42,  -315,     5,  -315,  -315,
    -315,     9,  -315,  -315,    10,  -315,    33,   238,   404,   404,
    -315,    38,  -315,    41,    75,  -315,   404,   404,  -315,     5,
    -315,  -315,    95,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,    30,   119,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
     168,   187,   206,   208,   222,   236,   244,   249,   265,   268,
     270,   277,   302,   309,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,   310,  -315,  -315,   404,   319,   321,   180,   315,  -315,
    -315,   331,   351,   352,   353,   402,   403,   320,   516,  -315,
    -315,    39,   108,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,   332,   516,   276,   281,  -315,    27,     6,
     247,   389,  -315,  -315,  -315,  -315,  -315,  -315,   190,   190,
     190,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,   263,    34,    10,    10,  -315,   192,   263,   263,
     263,   263,   404,   404,   424,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,  -315,   263,   404,  -315,   404,   421,   404,
     404,   404,   404,   426,   442,   404,   404,   404,   404,   404,
    -315,  -315,  -315,  -315,  -315,  -315,   227,   419,   434,  -315,
    -315,  -315,  -315,   565,   487,     5,     5,   504,   509,   584,
     585,   587,   588,   590,   591,   592,   605,   606,    40,  -315,
    -315,   533,   540,     4,   186,   241,  -315,  -315,    18,  -315,
     615,   616,   618,   619,    46,    53,   404,    14,  -315,   531,
     531,   531,   531,   531,   531,   544,   544,   544,   283,   283,
     283,   283,   283,   283,   283,   278,   129,  -315,    61,    15,
     108,   404,   108,   108,   132,  -315,  -315,  -315,   388,   388,
     266,   334,  -315,   501,   563,   564,   272,  -315,    71,   684,
     685,  -315,  -315,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   263,   664,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,   192,  -315,   404,   404,   404,   404,  -315,  -315,    76,
    -315,  -315,  -315,  -315,  -315,   483,    26,    16,   254,   254,
     254,  -315,  -315,   687,   487,   182,   272,   272,   597,   602,
     612,    67,    74,   183,   625,   630,    58,  -315,   617,  -315,
     635,   640,   645,   650,   589,  -315,  -315,   620,   263,  -315,
    -315,   610,  -315,  -315,   573,   574,   575,    41,    81,  -315,
      78,  -315,   621,   622,   404,   404,   404,  -315,  -315,  -315,
     404,   404,  -315,   404,   404,   404,   404,   404,   404,  -315,
    -315,   404,  -315,  -315,  -315,   623,   487,   262,   190,  -315,
    -315,  -315,   655,   660,   665,   279,   285,   225,   232,   239,
     250,   274,   508,   515,  -315,   626,  -315,    79,  -315,   404,
     404,   404,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,   300,  -315,   670,   675,   680,  -315,    83,   404,   404,
     404,  -315,   295,   317,   322,  -315,  -315,  -315
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   170,     0,    22,     4,
      20,     0,    49,    46,     0,   171,     0,    30,     0,     0,
     180,     0,   179,     0,     0,    21,     0,     0,    36,     0,
      34,    23,    24,    25,    26,    27,    28,    29,   107,   108,
     111,   109,   110,   112,    96,    97,   103,    98,    99,   100,
     102,   104,   105,   106,   126,   101,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    84,
      85,     0,    90,    91,     0,     0,     0,     0,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,   178,    83,
     141,     0,   172,   164,   165,   166,   167,   168,   169,   146,
     147,   148,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,     0,    60,     0,     0,    18,     0,     0,
       0,     0,    31,    86,    87,    88,    89,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    17,    19,    32,    33,    35,     0,     0,     0,    37,
      43,   215,   216,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
     143,     0,     0,     0,     0,     0,    11,    12,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,   212,    75,
      76,    79,    77,    78,    80,    61,    62,    71,    63,    64,
      65,    70,    72,    73,    74,    66,    67,    69,     0,     0,
     173,     0,   175,   176,   174,   177,     5,     7,    57,    58,
      56,    55,    59,     0,     0,     0,     0,   209,     0,     0,
       0,   192,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   149,   150,   151,    13,    14,    15,
      16,     0,   152,     0,     0,     0,     0,   187,   188,     0,
     145,   213,    81,    82,     6,     0,     0,     0,     0,     0,
       0,   181,   182,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    52,     0,    10,
       0,     0,     0,     0,     0,    44,    53,     0,     0,    54,
       8,     0,    41,    42,     0,     0,     0,     0,     0,   206,
       0,   210,     0,     0,     0,     0,     0,   197,   198,   199,
       0,     0,   202,     0,     0,     0,     0,     0,     0,    48,
      50,     0,    38,    39,    40,     0,     0,     0,     0,   203,
     190,   191,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   189,     0,   207,     0,   211,     0,
       0,     0,   201,   200,   144,   183,   184,   185,   186,   214,
      47,     0,   204,     0,     0,     0,   208,     0,     0,     0,
       0,   205,     0,     0,     0,   194,   195,   196
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -315,  -315,   530,   412,  -315,  -315,   378,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,    29,  -315,  -195,
    -315,  -315,  -315,  -315,     2,   -19,  -315,    23,   -10,  -139,
    -189,   -22,   414,    24,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -261,  -314,  -315,   443,  -156
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   289,   347,   258,   259,     9,    17,    31,
      32,    33,    34,    35,    36,   150,   229,   384,    37,    10,
     380,    11,   381,   248,   143,   118,   119,   120,    16,   121,
     122,    24,    21,   353,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   233,   308,   390,   267,   268,   391
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     144,   146,   234,   235,   236,     4,    23,   144,   144,   213,
     214,   215,   216,   217,   218,   219,     4,   377,   290,   151,
     292,   293,   294,   295,    13,    12,   331,     4,   148,   149,
     213,   214,   215,   216,   217,   218,   219,   213,   214,   215,
     216,   217,   218,   219,   378,    -2,     4,   207,   322,   213,
     214,   215,   216,   217,   218,   219,   213,   214,   215,   216,
     217,   218,   219,   209,   210,   211,   288,   212,   157,   207,
     213,   214,   215,   216,   217,   218,   219,   213,   214,   215,
     216,   217,   218,   219,   207,   144,   418,   418,   326,   354,
      18,   418,     5,   388,   344,   266,    19,     3,   340,   416,
     379,   343,   332,   437,   153,   154,   173,     6,    15,     7,
     376,    20,     8,   209,   210,   211,   250,   212,     6,   224,
     145,   208,   323,    14,   358,   359,   360,   339,   337,     6,
     364,   365,   366,     5,    22,   338,    15,   457,   223,   211,
     402,   212,    22,   342,   370,   371,   372,   373,     6,   397,
       7,   344,   355,     8,   147,   435,   398,   203,   374,   204,
     419,   452,   417,   144,   144,   461,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   264,   265,   213,   214,   215,   216,
     217,   218,   219,   155,   156,   249,   144,   144,   144,   144,
     144,   260,   261,   262,   263,   422,   423,   424,   254,   255,
     205,   425,   426,   152,   206,   231,   232,   298,   299,   300,
     301,   302,     6,   231,   232,   309,   310,   287,   213,   214,
     215,   216,   217,   218,   219,   213,   214,   215,   216,   217,
     218,   219,   213,   214,   215,   216,   217,   218,   219,   158,
     453,   454,   455,   213,   214,   215,   216,   217,   218,   219,
     327,   328,   438,   176,   389,   399,   256,   257,   159,   462,
     463,   464,   144,   217,   218,   219,    12,   213,   214,   215,
     216,   217,   218,   219,   209,   210,   211,   160,   212,   161,
     209,   210,   211,   345,   212,   231,   232,   144,   144,   144,
     209,   210,   211,   162,   212,   202,   203,   444,   204,   201,
     202,   203,    12,   204,   445,   329,   330,   163,   361,   362,
     363,   446,   209,   210,   211,   164,   212,   209,   210,   211,
     165,   212,   447,   231,   232,   213,   214,   215,   216,   217,
     218,   219,   218,   219,   436,   367,   166,    25,    26,   167,
      27,   168,    28,   303,    29,   221,   448,    30,   169,   205,
     222,   442,   225,   206,   205,   415,     6,   443,   206,    12,
     226,   227,   228,   351,   352,   382,   383,   465,   385,   386,
     392,   393,   456,   170,   144,   144,   144,   144,   144,   144,
     171,   172,   144,   215,   216,   217,   218,   219,   177,   466,
     174,   410,   175,   184,   467,   427,   428,   429,   430,   431,
     432,   220,   178,   433,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   179,   180,   181,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   182,   183,   104,   213,   214,   215,   216,
     217,   218,   219,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   266,   230,     6,   291,   296,
     117,   213,   214,   215,   216,   217,   218,   219,   213,   214,
     215,   216,   217,   218,   219,   297,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   304,   204,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     305,   204,   375,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   306,   204,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   311,   449,   251,   252,
     307,   312,   313,   314,   450,   315,   316,   205,   317,   318,
     319,   206,   209,   210,   211,   394,   212,   209,   210,   211,
     395,   212,   205,   320,   321,   324,   206,   209,   210,   211,
     396,   212,   325,   333,   334,   205,   335,   336,   348,   206,
     209,   210,   211,   400,   212,   209,   210,   211,   401,   212,
     209,   210,   211,   404,   212,   209,   210,   211,   405,   212,
     209,   210,   211,   406,   212,   209,   210,   211,   407,   212,
     209,   210,   211,   439,   212,   209,   210,   211,   440,   212,
     209,   210,   211,   441,   212,   209,   210,   211,   458,   212,
     209,   210,   211,   459,   212,   209,   210,   211,   460,   212,
     349,   350,   356,   357,   368,   387,   408,   411,   403,   409,
     412,   413,   414,   420,   421,   434,   253,   451,   346,   369,
     341
};

static const yytype_uint16 yycheck[] =
{
      19,    23,   158,   159,   160,     1,    16,    26,    27,     3,
       4,     5,     6,     7,     8,     9,     1,     1,   207,    29,
     209,   210,   211,   212,    79,     2,     8,     1,    26,    27,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,    28,     0,     1,     8,     8,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,     5,     6,     7,   205,     9,    45,     8,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     8,   104,     8,     8,    84,    18,
      81,     8,    88,   354,   289,    81,    87,     0,    84,    18,
      84,    86,    84,   417,    74,    75,   104,   103,   103,   105,
      84,   101,   108,     5,     6,     7,    82,     9,   103,   113,
      82,    82,    82,    81,   313,   314,   315,   266,    82,   103,
     319,   320,   321,    88,   101,    82,   103,   451,   111,     7,
      82,     9,   101,    82,   333,   334,   335,   336,   103,    82,
     105,   346,    81,   108,    79,   416,    82,    28,    82,    30,
      82,    82,    81,   182,   183,    82,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   182,   183,     3,     4,     5,     6,
       7,     8,     9,    74,    75,   172,   215,   216,   217,   218,
     219,   178,   179,   180,   181,   394,   395,   396,    16,    17,
      81,   400,   401,   118,    85,    33,    34,   215,   216,   217,
     218,   219,   103,    33,    34,   235,   236,   204,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,    81,
     439,   440,   441,     3,     4,     5,     6,     7,     8,     9,
      74,    75,   418,    83,    82,    82,    74,    75,    81,   458,
     459,   460,   291,     7,     8,     9,   253,     3,     4,     5,
       6,     7,     8,     9,     5,     6,     7,    81,     9,    81,
       5,     6,     7,   291,     9,    33,    34,   316,   317,   318,
       5,     6,     7,    81,     9,    27,    28,    82,    30,    26,
      27,    28,   289,    30,    82,    74,    75,    81,   316,   317,
     318,    82,     5,     6,     7,    81,     9,     5,     6,     7,
      81,     9,    82,    33,    34,     3,     4,     5,     6,     7,
       8,     9,     8,     9,    82,   322,    81,   109,   110,    81,
     112,    81,   114,   126,   116,    79,    82,   119,    81,    81,
      79,    82,   115,    85,    81,   387,   103,    82,    85,   346,
     123,   124,   125,   101,   102,   121,   122,    82,   349,   350,
     356,   357,    82,    81,   403,   404,   405,   406,   407,   408,
      81,    81,   411,     5,     6,     7,     8,     9,    83,    82,
      81,   378,    81,    83,    82,   403,   404,   405,   406,   407,
     408,    79,    81,   411,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    81,    81,    81,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    81,    81,    81,     3,     4,     5,     6,
       7,     8,     9,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    81,   117,   103,    87,    83,
     106,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,    83,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,   126,    30,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
     126,    30,    79,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     8,    30,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,    82,    79,   174,   175,
     103,    82,     8,     8,    79,     8,     8,    81,     8,     8,
       8,    85,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,    81,     8,     8,    82,    85,     5,     6,     7,
       8,     9,    82,     8,     8,    81,     8,     8,   127,    85,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
     127,   127,     8,     8,    30,     8,   107,    87,    81,    79,
     127,   127,   127,    82,    82,    82,   176,    81,   296,   331,
     267
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   129,   130,     0,     1,    88,   103,   105,   108,   135,
     147,   149,   155,    79,    81,   103,   156,   136,    81,    87,
     101,   160,   101,   156,   159,   109,   110,   112,   114,   116,
     119,   137,   138,   139,   140,   141,   142,   146,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    81,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   106,   153,   154,
     155,   157,   158,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   152,   153,    82,   159,    79,   152,   152,
     143,   156,   118,    74,    75,    74,    75,   155,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,   152,    81,    81,    83,    83,    81,    81,
      81,    81,    81,    81,    83,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    81,    85,     8,    82,     5,
       6,     7,     9,     3,     4,     5,     6,     7,     8,     9,
      79,    79,    79,   111,   113,   115,   123,   124,   125,   144,
     117,    33,    34,   182,   187,   187,   187,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   151,   155,
      82,   160,   160,   130,    16,    17,    74,    75,   133,   134,
     155,   155,   155,   155,   152,   152,    81,   185,   186,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   155,   157,   131,
     158,    87,   158,   158,   158,   158,    83,    83,   152,   152,
     152,   152,   152,   126,   126,   126,     8,   103,   183,   156,
     156,    82,    82,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,    82,    82,    82,    84,    74,    75,    74,
      75,     8,    84,     8,     8,     8,     8,    82,    82,   157,
      84,   186,    82,    86,   147,   152,   131,   132,   127,   127,
     127,   101,   102,   161,    18,    81,     8,     8,   158,   158,
     158,   152,   152,   152,   158,   158,   158,   155,    30,   134,
     158,   158,   158,   158,    82,    79,    84,     1,    28,    84,
     148,   150,   121,   122,   145,   145,   145,     8,   183,    82,
     184,   187,   161,   161,     8,     8,     8,    82,    82,    82,
       8,     8,    82,    81,     8,     8,     8,     8,   107,    79,
     155,    87,   127,   127,   127,   159,    18,    81,     8,    82,
      82,    82,   158,   158,   158,   158,   158,   152,   152,   152,
     152,   152,   152,   152,    82,   183,    82,   184,   187,     8,
       8,     8,    82,    82,    82,    82,    82,    82,    82,    79,
      79,    81,    82,   158,   158,   158,    82,   184,     8,     8,
       8,    82,   158,   158,   158,    82,    82,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   128,   129,   130,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   134,   135,   135,   135,
     135,   135,   136,   136,   137,   137,   137,   137,   137,   137,
     138,   138,   139,   140,   141,   142,   143,   143,   144,   144,
     144,   145,   145,   146,   147,   147,   147,   148,   148,   149,
     150,   151,   151,   152,   152,   152,   152,   152,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   156,   157,   157,   158,   158,   158,   158,   158,   159,
     160,   161,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   182,   182,   182,   182,   182,   183,
     184,   184,   185,   185,   186,   187,   187
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       4,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     8,     8,     8,     8,     4,     4,     8,
       7,     7,     4,     4,    12,    12,    12,     6,     6,     6,
       8,     8,     6,     5,     7,     9,     4,     6,     8,     1,
       1,     3,     1,     2,     6,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 314 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1791 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 317 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1797 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 318 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1803 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 320 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1809 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 321 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1815 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 325 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1821 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 326 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1827 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 333 "faustparser.y" /* yacc.c:1646  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1833 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 334 "faustparser.y" /* yacc.c:1646  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1839 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 337 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1845 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 338 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1851 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 339 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1857 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 340 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1863 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 341 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1869 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 342 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1875 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 346 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1881 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 347 "faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1887 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 348 "faustparser.y" /* yacc.c:1646  */
    { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1893 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 349 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1899 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 350 "faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1905 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 353 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1911 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 354 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1917 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 357 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1923 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 358 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1929 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 359 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1935 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 360 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1941 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 361 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1947 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 362 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1953 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 365 "faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1959 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 366 "faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1965 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 369 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1971 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 372 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1977 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 375 "faustparser.y" /* yacc.c:1646  */
    { }
#line 1983 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 378 "faustparser.y" /* yacc.c:1646  */
    { }
#line 1989 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 381 "faustparser.y" /* yacc.c:1646  */
    { }
#line 1995 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 382 "faustparser.y" /* yacc.c:1646  */
    { }
#line 2001 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 385 "faustparser.y" /* yacc.c:1646  */
    { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2007 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 386 "faustparser.y" /* yacc.c:1646  */
    { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2013 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 387 "faustparser.y" /* yacc.c:1646  */
    { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2019 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 390 "faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 2025 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 391 "faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 2031 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 394 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2037 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 397 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2043 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 398 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2049 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 399 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2055 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 402 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2061 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 403 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2067 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 406 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2073 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 409 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2079 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 412 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2085 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 413 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2091 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 416 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2097 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 417 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2103 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 418 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2109 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 419 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2115 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 420 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2121 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 421 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2127 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 422 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2133 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 423 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2139 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 426 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2145 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 427 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2151 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 428 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2157 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 429 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2163 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 430 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2169 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2175 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 432 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2181 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 433 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2187 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 434 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2193 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 436 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2199 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 437 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2205 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 438 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2211 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 440 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2217 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 441 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2223 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 443 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2229 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 444 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2235 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 445 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2241 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 446 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2247 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 447 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2253 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 448 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2259 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 450 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2265 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 451 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2271 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 453 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2277 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 456 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2283 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 457 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2289 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 459 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2295 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 460 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2301 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 462 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2307 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 463 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2313 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 465 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2319 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 466 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2325 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 468 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2331 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 469 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2337 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 471 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2343 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 472 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2349 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 474 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2355 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 475 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2361 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 476 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2367 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 477 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2373 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 478 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2379 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 479 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2385 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 481 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2391 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 482 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2397 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 483 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2403 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 485 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2409 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 486 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2415 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 488 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2421 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 489 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2427 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 490 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2433 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 491 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2439 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 492 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2445 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 493 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2451 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 495 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2457 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 496 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2463 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 497 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2469 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 500 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2475 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 501 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2481 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 502 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2487 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 503 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2493 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 504 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2499 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 505 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2505 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 506 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2511 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 508 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2517 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 509 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2523 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 510 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2529 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 511 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2535 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 512 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2541 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 513 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2547 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 515 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2553 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 516 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2559 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 517 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2565 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 519 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2571 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 520 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2577 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 522 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2583 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 523 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2589 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 524 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2595 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 527 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2601 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 528 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2607 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 530 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2613 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 531 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2619 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 533 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2625 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 534 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2631 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 536 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2637 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 538 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2643 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 540 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2649 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 542 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2655 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 543 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2661 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 544 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2667 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 545 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2673 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 546 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2679 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 547 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2685 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 548 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2691 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 549 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2697 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 550 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2703 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 551 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2709 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 552 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2715 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 553 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2721 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 554 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2727 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 555 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2733 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 556 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2739 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 557 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2745 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 558 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2751 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 559 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2757 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 561 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2763 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 562 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2769 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 563 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2775 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 564 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2781 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 566 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2787 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 567 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2793 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 572 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2799 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 575 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2805 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 580 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2811 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 581 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2817 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 584 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2823 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 585 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2829 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 586 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2835 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 587 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2841 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 588 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2847 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 591 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2853 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 594 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2859 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 597 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2865 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 598 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2871 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 604 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2877 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 608 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2883 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 612 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2889 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 616 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2895 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 620 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2901 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 623 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2907 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 631 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2913 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 635 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2919 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 638 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2925 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 642 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2931 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 645 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2937 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 649 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2943 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 652 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2949 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 655 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2955 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 658 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2961 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 661 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2967 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 664 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2973 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 668 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2979 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 671 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2985 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 674 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2991 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 680 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2997 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 681 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3003 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 682 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3009 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 684 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3015 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 685 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3021 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 686 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3027 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 689 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 3033 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 692 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3039 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 693 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3045 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 696 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3051 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 697 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3057 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 701 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3063 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 704 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 3069 "faustparser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 705 "faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 3075 "faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3079 "faustparser.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 708 "faustparser.y" /* yacc.c:1906  */


