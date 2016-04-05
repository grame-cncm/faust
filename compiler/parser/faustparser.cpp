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
#line 5 "parser/faustparser.y" /* yacc.c:339  */


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
extern Tree 		gResult;
extern bool         gStripDocSwitch;
extern bool         gLstDependenciesSwitch;
extern bool         gLstDistributedSwitch;
extern bool        	gLstMdocTagsSwitch;

extern map<Tree, set<Tree> > gMetaDataSet;
extern vector<Tree>          gDocVector;
extern tvec                  gWaveForm; 

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


#line 138 "parser/faustparser.cpp" /* yacc.c:339  */

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
#ifndef YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
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
    SPLIT = 259,
    MIX = 260,
    SEQ = 261,
    PAR = 262,
    REC = 263,
    LT = 264,
    LE = 265,
    EQ = 266,
    GT = 267,
    GE = 268,
    NE = 269,
    ADD = 270,
    SUB = 271,
    OR = 272,
    MUL = 273,
    DIV = 274,
    MOD = 275,
    AND = 276,
    XOR = 277,
    LSH = 278,
    RSH = 279,
    POWOP = 280,
    FDELAY = 281,
    DELAY1 = 282,
    APPL = 283,
    DOT = 284,
    HASH = 285,
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
    ATTACH = 303,
    ACOS = 304,
    ASIN = 305,
    ATAN = 306,
    ATAN2 = 307,
    COS = 308,
    SIN = 309,
    TAN = 310,
    EXP = 311,
    LOG = 312,
    LOG10 = 313,
    POWFUN = 314,
    SQRT = 315,
    ABS = 316,
    MIN = 317,
    MAX = 318,
    FMOD = 319,
    REMAINDER = 320,
    FLOOR = 321,
    CEIL = 322,
    RINT = 323,
    RDTBL = 324,
    RWTBL = 325,
    SELECT2 = 326,
    SELECT3 = 327,
    INT = 328,
    FLOAT = 329,
    LAMBDA = 330,
    WIRE = 331,
    CUT = 332,
    ENDDEF = 333,
    VIRG = 334,
    LPAR = 335,
    RPAR = 336,
    LBRAQ = 337,
    RBRAQ = 338,
    LCROC = 339,
    RCROC = 340,
    DEF = 341,
    IMPORT = 342,
    COMPONENT = 343,
    LIBRARY = 344,
    ENVIRONMENT = 345,
    WAVEFORM = 346,
    IPAR = 347,
    ISEQ = 348,
    ISUM = 349,
    IPROD = 350,
    INPUTS = 351,
    OUTPUTS = 352,
    STRING = 353,
    FSTRING = 354,
    IDENT = 355,
    EXTRA = 356,
    DECLARE = 357,
    CASE = 358,
    ARROW = 359,
    VECTORIZE = 360,
    SERIALIZE = 361,
    RATE = 362,
    UPSAMPLE = 363,
    DOWNSAMPLE = 364,
    BDOC = 365,
    EDOC = 366,
    BEQN = 367,
    EEQN = 368,
    BDGM = 369,
    EDGM = 370,
    BLST = 371,
    ELST = 372,
    BMETADATA = 373,
    EMETADATA = 374,
    DOCCHAR = 375,
    NOTICE = 376,
    LISTING = 377,
    LSTTRUE = 378,
    LSTFALSE = 379,
    LSTDEPENDENCIES = 380,
    LSTMDOCTAGS = 381,
    LSTDISTRIBUTED = 382,
    LSTEQ = 383,
    LSTQ = 384
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 78 "parser/faustparser.y" /* yacc.c:355  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 315 "parser/faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 332 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYLAST   786

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  454

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   384

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
     125,   126,   127,   128,   129
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   318,   318,   321,   322,   324,   325,   332,   333,   336,
     337,   338,   339,   340,   341,   345,   346,   347,   348,   351,
     352,   355,   356,   357,   358,   359,   360,   363,   364,   367,
     370,   373,   376,   379,   380,   383,   384,   385,   388,   389,
     392,   395,   396,   397,   400,   403,   404,   407,   408,   409,
     410,   411,   412,   413,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   426,   427,   428,   430,   431,   433,   434,
     435,   436,   437,   438,   440,   442,   443,   445,   448,   449,
     451,   452,   454,   455,   457,   458,   460,   461,   463,   464,
     466,   467,   468,   469,   470,   471,   473,   474,   475,   477,
     478,   480,   481,   482,   483,   484,   485,   487,   489,   490,
     491,   492,   493,   494,   495,   497,   498,   499,   500,   501,
     502,   504,   505,   506,   508,   509,   511,   512,   513,   516,
     517,   519,   520,   522,   523,   524,   526,   527,   529,   530,
     532,   533,   535,   536,   539,   541,   542,   543,   544,   545,
     546,   547,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   560,   561,   562,   563,   565,   566,   571,   574,
     579,   580,   583,   584,   585,   586,   587,   590,   593,   596,
     597,   602,   606,   610,   614,   619,   622,   629,   633,   636,
     641,   644,   647,   650,   653,   656,   659,   662,   666,   669,
     676,   677,   678,   680,   681,   682,   685,   688,   689,   692,
     693,   696,   700,   701
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "SPLIT", "MIX", "SEQ", "PAR",
  "REC", "LT", "LE", "EQ", "GT", "GE", "NE", "ADD", "SUB", "OR", "MUL",
  "DIV", "MOD", "AND", "XOR", "LSH", "RSH", "POWOP", "FDELAY", "DELAY1",
  "APPL", "DOT", "HASH", "MEM", "PREFIX", "INTCAST", "FLOATCAST",
  "FFUNCTION", "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER",
  "HSLIDER", "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH",
  "VBARGRAPH", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN",
  "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS", "MIN", "MAX",
  "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL",
  "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT", "ENDDEF",
  "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC", "DEF",
  "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "IPAR",
  "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING",
  "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "VECTORIZE", "SERIALIZE",
  "RATE", "UPSAMPLE", "DOWNSAMPLE", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM",
  "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE",
  "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "vallist", "number", "statement", "doc", "docelem", "doctxt",
  "doceqn", "docdgm", "docntc", "doclst", "lstattrlist", "lstattrdef",
  "lstattrval", "docmtd", "definition", "defname", "params", "expression",
  "infixexp", "primitive", "ident", "name", "arglist", "argument",
  "string", "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod",
  "finputs", "foutputs", "ffunction", "fconst", "fvariable", "button",
  "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
  "vbargraph", "hbargraph", "signature", "fun", "typelist", "rulelist",
  "rule", "type", YY_NULLPTR
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384
};
# endif

#define YYPACT_NINF -340

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-340)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -340,   102,     4,  -340,    35,    47,  -340,    90,  -340,  -340,
    -340,   209,  -340,  -340,   113,  -340,   116,   249,   494,   494,
    -340,   128,  -340,   145,  -340,   494,   494,  -340,    90,  -340,
    -340,   147,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,     1,   171,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     213,   223,   230,   237,   251,   284,   289,   306,   307,   314,
     315,   340,   342,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     391,  -340,  -340,   494,   393,   392,   394,   224,   254,   395,
     396,   399,   400,   411,   412,   413,  -340,  -340,  -340,  -340,
     617,  -340,  -340,    45,   385,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,   274,   617,   416,  -340,    12,     6,
     -17,   378,  -340,  -340,  -340,  -340,  -340,  -340,   257,   257,
     257,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   421,    37,  -340,   595,   113,   113,  -340,   259,   421,
     421,   421,   421,   494,   494,   420,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,  -340,   421,   494,   494,  -340,   494,
     436,   494,   494,   494,   494,   441,   494,   494,   494,   494,
     494,  -340,  -340,  -340,  -340,  -340,   444,   445,   447,  -340,
    -340,  -340,  -340,   569,   477,    90,    90,   498,   499,   574,
     585,   586,   588,   589,   591,   594,   616,    69,  -340,  -340,
    -340,   564,   580,    20,   242,   256,  -340,  -340,    28,  -340,
     657,   671,   684,   685,    43,    50,   494,    62,  -340,   633,
     633,   633,   633,   633,   633,   647,   647,   647,   275,   275,
     275,   275,   275,   275,   275,   282,   308,  -340,   212,    85,
      38,   385,   494,   385,   385,   185,  -340,  -340,   317,   317,
     219,   319,  -340,   565,   570,   571,   255,  -340,    21,   686,
     691,  -340,  -340,   494,   494,   494,   494,   494,   494,   494,
     494,   421,   683,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     259,  -340,   494,   494,   494,   494,  -340,  -340,   129,  -340,
    -340,  -340,  -340,  -340,   280,    29,   248,   248,   248,  -340,
    -340,   707,   477,    60,   255,   255,   335,   377,   698,    56,
      65,    75,   703,   714,  -340,   635,  -340,   728,   733,   738,
     743,   612,  -340,  -340,  -340,  -340,   596,   597,   599,   116,
      48,  -340,   136,  -340,   642,   643,   494,   494,   494,  -340,
    -340,  -340,   494,   494,   494,   494,   494,   494,   494,   494,
    -340,  -340,  -340,   648,   477,    63,   257,  -340,  -340,  -340,
     748,   753,   758,    18,    82,   154,   226,   233,   247,   253,
     343,  -340,   650,  -340,   181,  -340,   494,   494,   494,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,   162,  -340,   763,
     768,   773,  -340,   182,   494,   494,   494,  -340,   111,   143,
     264,  -340,  -340,  -340
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   168,     0,    19,     4,
      17,     0,    44,    43,     0,   169,     0,    27,     0,     0,
     178,     0,   177,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   101,   102,   105,
     103,   104,   106,    90,    91,    97,    92,    93,    94,    96,
      98,    99,   100,   118,    95,   135,    86,    87,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,    78,    79,
       0,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   134,   136,   137,
     176,    77,   140,     0,   170,   162,   163,   164,   165,   166,
     167,   145,   146,   147,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     0,    53,     0,    16,     0,     0,
       0,     0,    28,    80,    81,    82,    83,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,     0,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    15,    29,    30,    32,     0,     0,     0,    34,
      40,   212,   213,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,   142,
     139,     0,     0,     0,     0,     0,     9,    10,     0,     7,
       0,     0,     0,     0,     0,     0,     0,     0,   209,    68,
      69,    72,    70,    71,    73,    54,    55,    64,    56,    57,
      58,    63,    65,    66,    67,    59,    60,    62,    74,     0,
       0,   171,     0,   173,   174,   172,   175,     5,    50,    51,
      49,    48,    52,     0,     0,     0,     0,   206,     0,     0,
       0,   190,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   149,   150,    11,    12,    13,    14,
       0,   151,     0,     0,     0,     0,   185,   186,     0,   144,
     210,    75,    76,     6,     0,     0,     0,     0,     0,   179,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     8,     0,     0,     0,
       0,     0,    41,    47,    38,    39,     0,     0,     0,     0,
       0,   203,     0,   207,     0,     0,     0,     0,     0,   195,
     196,   197,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,     0,     0,     0,   200,   188,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,   204,     0,   208,     0,     0,     0,   199,
     198,   143,   181,   182,   183,   184,   211,     0,   201,     0,
       0,     0,   205,     0,     0,     0,     0,   202,     0,     0,
       0,   192,   193,   194
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -340,  -340,   605,   486,  -340,   454,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,     9,  -340,  -213,  -340,
    -340,     2,   -19,  -340,    23,   -20,  -171,  -180,   406,   520,
      19,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -315,  -339,  -340,   519,  -157
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   290,   258,   259,     9,    17,    30,    31,
      32,    33,    34,    35,   150,   229,   376,    36,    10,    11,
     247,   144,   120,   121,   122,    16,   123,   124,    23,    21,
     351,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     233,   308,   382,   267,   268,   383
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     145,   234,   235,   236,    -2,     4,   145,   145,   151,   215,
     216,   217,   218,   219,   220,   215,   216,   217,   218,   219,
     220,     4,   211,   212,   213,    12,   214,   148,   149,   291,
       4,   293,   294,   295,   296,   330,   289,   380,   352,     4,
     215,   216,   217,   218,   219,   220,   215,   216,   217,   218,
     219,   220,   209,   215,   216,   217,   218,   219,   220,   215,
     216,   217,   218,   219,   220,   404,   424,   157,   215,   216,
     217,   218,   219,   220,   153,   154,   321,   343,   215,   216,
     217,   218,   219,   220,   145,   174,   211,   212,   213,   422,
     214,     5,   209,   231,   232,   338,   231,   232,   443,   429,
     225,   353,     3,   325,     6,   172,     7,     5,   226,   227,
     228,   331,   373,    13,     8,   211,   212,   213,   249,   214,
       6,   224,     7,   342,   336,   223,   210,    14,   405,     6,
       8,   337,   343,   356,   357,   358,   209,   389,     6,   362,
     363,   381,   266,   406,   423,   339,   390,   211,   212,   213,
     322,   214,   367,   368,   369,   370,   391,   215,   216,   217,
     218,   219,   220,   430,   145,   145,   341,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   264,   265,   288,   406,   406,
      15,   213,   451,   214,   248,   231,   232,   145,   145,   145,
     145,   145,   260,   261,   262,   263,   410,   411,   412,   146,
     371,    20,   413,   414,    22,   309,   310,   407,   298,   299,
     300,   301,   302,   147,   452,   218,   219,   220,   287,   215,
     216,   217,   218,   219,   220,   431,   215,   216,   217,   218,
     219,   220,   206,   442,   155,   156,   439,   440,   441,   425,
     215,   216,   217,   218,   219,   220,   215,   216,   217,   218,
     219,   220,   438,   447,   448,   449,   450,   152,   211,   212,
     213,     6,   214,   145,   254,   255,    12,   215,   216,   217,
     218,   219,   220,   215,   216,   217,   218,   219,   220,    18,
     231,   232,   207,   158,   344,    19,   208,   145,   145,   145,
     202,   203,   204,   159,   205,   206,   177,   432,   203,   204,
     160,   205,   206,    12,   433,   326,   327,   161,   359,   360,
     361,   216,   217,   218,   219,   220,   219,   220,   434,   328,
     329,   162,   256,   257,   435,   204,   178,   205,   206,   211,
     212,   213,   386,   214,   364,   453,   215,   216,   217,   218,
     219,   220,   221,   349,   350,   207,   377,   378,   372,   208,
      24,    25,   207,    26,   163,    27,   208,    28,    12,   164,
      29,   374,   375,   384,   385,   145,   145,   145,   145,   145,
     145,   211,   212,   213,   387,   214,   165,   166,   207,   211,
     212,   213,   208,   214,   167,   168,   415,   416,   417,   418,
     419,   420,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     169,   436,   170,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   171,   175,   103,   176,   179,   180,   104,   173,   181,
     182,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   183,   184,     6,   222,   185,   115,   230,   116,   117,
     266,   118,   119,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,     6,   292,   297,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   303,   304,   103,   305,   306,   307,   104,   311,
     312,   313,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   314,   315,     6,   316,   317,   115,   318,   116,
     117,   319,   118,   119,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   320,   205,   206,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   323,   205,   206,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   324,   205,   206,   332,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   207,   205,   206,   333,   208,
     250,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   334,   335,   354,   346,   251,   252,   207,   355,   347,
     348,   208,   211,   212,   213,   388,   214,   211,   212,   213,
     392,   214,   365,   207,   379,   394,   399,   208,   211,   212,
     213,   393,   214,   408,   409,   400,   401,   207,   402,   421,
     437,   208,   211,   212,   213,   395,   214,   211,   212,   213,
     396,   214,   211,   212,   213,   397,   214,   211,   212,   213,
     398,   214,   211,   212,   213,   426,   214,   211,   212,   213,
     427,   214,   211,   212,   213,   428,   214,   211,   212,   213,
     444,   214,   211,   212,   213,   445,   214,   211,   212,   213,
     446,   214,   253,   345,   366,   403,   340
};

static const yytype_uint16 yycheck[] =
{
      19,   158,   159,   160,     0,     1,    25,    26,    28,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,     1,     4,     5,     6,     2,     8,    25,    26,   209,
       1,   211,   212,   213,   214,     7,   207,   352,    17,     1,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,     7,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,    17,   405,    44,     3,     4,
       5,     6,     7,     8,    73,    74,     7,   290,     3,     4,
       5,     6,     7,     8,   103,   104,     4,     5,     6,   404,
       8,    87,     7,    33,    34,   266,    33,    34,   437,    81,
     117,    80,     0,    83,   100,   103,   102,    87,   125,   126,
     127,    83,    83,    78,   110,     4,     5,     6,    81,     8,
     100,   115,   102,    85,    81,   113,    81,    80,    80,   100,
     110,    81,   345,   313,   314,   315,     7,    81,   100,   319,
     320,    81,    80,     7,    81,    83,    81,     4,     5,     6,
      81,     8,   332,   333,   334,   335,    81,     3,     4,     5,
       6,     7,     8,    81,   183,   184,    81,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   183,   184,   206,     7,     7,
     100,     6,    81,     8,   171,    33,    34,   216,   217,   218,
     219,   220,   179,   180,   181,   182,   386,   387,   388,    81,
      81,    98,   392,   393,    98,   235,   236,    81,   216,   217,
     218,   219,   220,    78,    81,     6,     7,     8,   205,     3,
       4,     5,     6,     7,     8,    81,     3,     4,     5,     6,
       7,     8,    30,    81,    73,    74,   426,   427,   428,   406,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,    81,    81,   444,   445,   446,   120,     4,     5,
       6,   100,     8,   292,    15,    16,   253,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,    80,
      33,    34,    80,    80,   292,    86,    84,   316,   317,   318,
      25,    26,    27,    80,    29,    30,    82,    81,    26,    27,
      80,    29,    30,   290,    81,    73,    74,    80,   316,   317,
     318,     4,     5,     6,     7,     8,     7,     8,    81,    73,
      74,    80,    73,    74,    81,    27,    82,    29,    30,     4,
       5,     6,     7,     8,   321,    81,     3,     4,     5,     6,
       7,     8,    78,    98,    99,    80,   347,   348,    78,    84,
     111,   112,    80,   114,    80,   116,    84,   118,   345,    80,
     121,   123,   124,   354,   355,   394,   395,   396,   397,   398,
     399,     4,     5,     6,     7,     8,    80,    80,    80,     4,
       5,     6,    84,     8,    80,    80,   394,   395,   396,   397,
     398,   399,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      80,    78,    80,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    80,    80,    80,    80,    80,    80,    84,    85,    80,
      80,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    80,    80,   100,    78,    82,   103,   119,   105,   106,
      80,   108,   109,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   100,    86,    82,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,   128,   128,    80,   128,     7,   100,    84,    81,
      81,     7,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     7,     7,   100,     7,     7,   103,     7,   105,
     106,     7,   108,   109,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     7,    29,    30,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    81,    29,    30,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    81,    29,    30,     7,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    80,    29,    30,     7,    84,
      85,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,     7,     7,     7,   129,   175,   176,    80,     7,   129,
     129,    84,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,    29,    80,     7,    80,   104,    84,     4,     5,
       6,     7,     8,    81,    81,   129,   129,    80,   129,    81,
      80,    84,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,   177,   297,   330,   379,   267
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   131,   132,     0,     1,    87,   100,   102,   110,   136,
     148,   149,   154,    78,    80,   100,   155,   137,    80,    86,
      98,   159,    98,   158,   111,   112,   114,   116,   118,   121,
     138,   139,   140,   141,   142,   143,   147,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    84,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   103,   105,   106,   108,   109,
     152,   153,   154,   156,   157,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   151,   152,    81,    78,   151,   151,
     144,   155,   120,    73,    74,    73,    74,   154,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,   151,    85,   152,    80,    80,    82,    82,    80,
      80,    80,    80,    80,    80,    82,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    29,    30,    80,    84,     7,
      81,     4,     5,     6,     8,     3,     4,     5,     6,     7,
       8,    78,    78,   113,   115,   117,   125,   126,   127,   145,
     119,    33,    34,   180,   185,   185,   185,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   150,   154,    81,
      85,   159,   159,   132,    15,    16,    73,    74,   134,   135,
     154,   154,   154,   154,   151,   151,    80,   183,   184,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   154,   152,   156,
     133,   157,    86,   157,   157,   157,   157,    82,   151,   151,
     151,   151,   151,   128,   128,   128,     7,   100,   181,   155,
     155,    81,    81,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    81,    81,    81,    83,    73,    74,    73,    74,
       7,    83,     7,     7,     7,     7,    81,    81,   156,    83,
     184,    81,    85,   148,   151,   133,   129,   129,   129,    98,
      99,   160,    17,    80,     7,     7,   157,   157,   157,   151,
     151,   151,   157,   157,   154,    29,   135,   157,   157,   157,
     157,    81,    78,    83,   123,   124,   146,   146,   146,     7,
     181,    81,   182,   185,   160,   160,     7,     7,     7,    81,
      81,    81,     7,     7,    80,     7,     7,     7,     7,   104,
     129,   129,   129,   158,    17,    80,     7,    81,    81,    81,
     157,   157,   157,   157,   157,   151,   151,   151,   151,   151,
     151,    81,   181,    81,   182,   185,     7,     7,     7,    81,
      81,    81,    81,    81,    81,    81,    78,    80,    81,   157,
     157,   157,    81,   182,     7,     7,     7,    81,   157,   157,
     157,    81,    81,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   130,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   137,
     137,   138,   138,   138,   138,   138,   138,   139,   139,   140,
     141,   142,   143,   144,   144,   145,   145,   145,   146,   146,
     147,   148,   148,   148,   149,   150,   150,   151,   151,   151,
     151,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   155,
     156,   156,   157,   157,   157,   157,   157,   158,   159,   160,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   180,   180,   180,   180,   180,   181,   182,   182,   183,
     183,   184,   185,   185
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     1,     3,     1,
       1,     2,     2,     2,     2,     5,     4,     1,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     0,     2,     3,
       3,     1,     3,     0,     2,     5,     5,     5,     1,     1,
       3,     7,     4,     2,     1,     1,     3,     5,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     1,     1,     1,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     2,     3,     8,     4,     1,     1,     1,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     8,     8,     8,     8,     4,     4,     8,     7,     7,
       4,     4,    12,    12,    12,     6,     6,     6,     8,     8,
       5,     7,     9,     4,     6,     8,     1,     1,     3,     1,
       2,     6,     1,     1
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
#line 318 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gResult = formatDefinitions((yyval.exp)); }
#line 1811 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 321 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1817 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 322 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1823 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 324 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1829 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 325 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1835 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 332 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1841 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 333 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1847 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 336 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1853 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 337 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1859 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 338 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1865 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 339 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1871 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1877 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 341 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1883 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 345 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1889 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 346 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = nil; }
#line 1895 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 347 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1901 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 348 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1907 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1913 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1919 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 355 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1925 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 356 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1931 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 357 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1937 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 358 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1943 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 359 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1949 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 360 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1955 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 363 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1961 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 364 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1967 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 367 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1973 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 370 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1979 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 373 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1985 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 376 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1991 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 379 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1997 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 380 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 2003 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 383 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2009 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 384 "parser/faustparser.y" /* yacc.c:1646  */
    { gStripDocSwitch = (yyvsp[-1].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
#line 2015 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 385 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2021 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 388 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 2027 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 389 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 2033 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 392 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2039 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 395 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2045 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 396 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2051 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 397 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2057 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 400 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2063 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 403 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2069 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 404 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2075 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 407 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2081 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 408 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2087 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 409 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2093 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 410 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2099 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2105 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 412 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2111 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 413 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2117 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 416 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2123 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 417 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2129 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 418 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2135 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 419 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2141 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2147 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 421 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gPowPrim->box()); }
#line 2153 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 422 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2159 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 423 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2165 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 424 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2171 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 426 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2177 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 427 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2183 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 428 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2189 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2195 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 431 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2201 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 433 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2207 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 434 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2213 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 435 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2219 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 436 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2225 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 437 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2231 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 438 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2237 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 440 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigConcat)); }
#line 2243 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 442 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2249 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 443 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2255 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 445 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2261 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 448 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2267 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 449 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2273 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 451 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2279 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 452 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2285 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 454 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2291 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 455 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2297 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 457 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2303 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2309 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 460 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2315 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2321 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 463 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2327 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 464 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2333 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 466 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2339 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 467 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2345 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 468 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2351 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 469 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2357 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 470 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2363 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 471 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2369 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 473 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2375 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2381 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 475 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2387 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 477 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2393 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 478 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2399 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 480 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2405 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 481 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2411 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 482 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2417 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 483 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2423 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2429 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2435 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 487 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2441 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 489 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAcosPrim->box(); }
#line 2447 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAsinPrim->box(); }
#line 2453 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 491 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtanPrim->box(); }
#line 2459 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtan2Prim->box(); }
#line 2465 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 493 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCosPrim->box(); }
#line 2471 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSinPrim->box(); }
#line 2477 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gTanPrim->box(); }
#line 2483 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 497 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gExpPrim->box(); }
#line 2489 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 498 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLogPrim->box(); }
#line 2495 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLog10Prim->box(); }
#line 2501 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 500 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2507 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 501 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2513 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 502 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSqrtPrim->box(); }
#line 2519 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 504 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAbsPrim->box(); }
#line 2525 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 505 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMinPrim->box(); }
#line 2531 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMaxPrim->box(); }
#line 2537 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 508 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFmodPrim->box(); }
#line 2543 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 509 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRemainderPrim->box(); }
#line 2549 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 511 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFloorPrim->box(); }
#line 2555 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCeilPrim->box(); }
#line 2561 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 513 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRintPrim->box(); }
#line 2567 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 516 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2573 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 517 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2579 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 519 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2585 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 520 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2591 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 522 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigVectorize); }
#line 2597 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 523 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigSerialize); }
#line 2603 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigConcat); }
#line 2609 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigUpSample); }
#line 2615 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 527 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDownSample); }
#line 2621 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 529 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigVectorAt); }
#line 2627 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxWire(),(yyvsp[-1].exp)),boxPrim2(sigVectorAt)); }
#line 2633 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2639 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 533 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2645 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2651 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 537 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2657 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 539 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2663 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 541 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2669 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 542 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2675 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 543 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2681 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 544 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2687 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2693 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2699 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 547 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gWaveForm); gWaveForm.clear(); }
#line 2705 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 549 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2711 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 550 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2717 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 551 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2723 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 552 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2729 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 553 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2735 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 554 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2741 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 555 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2747 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 556 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2753 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 557 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2759 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 558 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2765 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 560 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2771 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 561 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2777 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 562 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2783 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 563 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2789 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 565 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2795 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 566 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2801 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 571 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2807 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 574 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2813 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 579 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2819 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 580 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2825 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 583 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2831 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 584 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2837 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 585 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2843 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 586 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2849 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 587 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2855 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 590 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2861 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 593 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2867 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 596 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2873 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 597 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2879 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 603 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2885 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 607 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2891 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 611 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2897 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 615 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2903 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 619 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2909 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 622 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2915 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 630 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2921 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 634 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2927 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 637 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2933 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 641 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2939 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 644 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2945 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 648 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2951 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 651 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2957 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 654 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2963 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 657 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2969 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 660 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2975 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 663 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2981 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 667 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2987 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 670 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2993 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 676 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2999 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 677 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 3005 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 678 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 3011 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 680 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 3017 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 681 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 3023 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 682 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 3029 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 685 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 3035 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 688 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 3041 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 689 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3047 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 692 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 3053 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 693 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3059 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 697 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3065 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 700 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 3071 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 701 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 3077 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3081 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 704 "parser/faustparser.y" /* yacc.c:1906  */


