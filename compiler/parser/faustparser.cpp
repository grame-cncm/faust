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
    MEM = 285,
    PREFIX = 286,
    INTCAST = 287,
    FLOATCAST = 288,
    FFUNCTION = 289,
    FCONSTANT = 290,
    FVARIABLE = 291,
    BUTTON = 292,
    CHECKBOX = 293,
    VSLIDER = 294,
    HSLIDER = 295,
    NENTRY = 296,
    VGROUP = 297,
    HGROUP = 298,
    TGROUP = 299,
    HBARGRAPH = 300,
    VBARGRAPH = 301,
    ATTACH = 302,
    ACOS = 303,
    ASIN = 304,
    ATAN = 305,
    ATAN2 = 306,
    COS = 307,
    SIN = 308,
    TAN = 309,
    EXP = 310,
    LOG = 311,
    LOG10 = 312,
    POWFUN = 313,
    SQRT = 314,
    ABS = 315,
    MIN = 316,
    MAX = 317,
    FMOD = 318,
    REMAINDER = 319,
    FLOOR = 320,
    CEIL = 321,
    RINT = 322,
    RDTBL = 323,
    RWTBL = 324,
    SELECT2 = 325,
    SELECT3 = 326,
    INT = 327,
    FLOAT = 328,
    LAMBDA = 329,
    WIRE = 330,
    CUT = 331,
    ENDDEF = 332,
    VIRG = 333,
    LPAR = 334,
    RPAR = 335,
    LBRAQ = 336,
    RBRAQ = 337,
    LCROC = 338,
    RCROC = 339,
    DEF = 340,
    IMPORT = 341,
    COMPONENT = 342,
    LIBRARY = 343,
    ENVIRONMENT = 344,
    WAVEFORM = 345,
    MUTE = 346,
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
    BDOC = 360,
    EDOC = 361,
    BEQN = 362,
    EEQN = 363,
    BDGM = 364,
    EDGM = 365,
    BLST = 366,
    ELST = 367,
    BMETADATA = 368,
    EMETADATA = 369,
    DOCCHAR = 370,
    NOTICE = 371,
    LISTING = 372,
    LSTTRUE = 373,
    LSTFALSE = 374,
    LSTDEPENDENCIES = 375,
    LSTMDOCTAGS = 376,
    LSTDISTRIBUTED = 377,
    LSTEQ = 378,
    LSTQ = 379
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

#line 310 "parser/faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 327 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  125
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  206
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  444

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   379

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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   311,   311,   314,   315,   317,   318,   325,   326,   329,
     330,   331,   332,   333,   334,   338,   339,   340,   341,   344,
     345,   348,   349,   350,   351,   352,   353,   356,   357,   360,
     363,   366,   369,   372,   373,   376,   377,   378,   381,   382,
     385,   388,   389,   390,   393,   396,   397,   400,   401,   402,
     403,   404,   405,   406,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   419,   420,   421,   423,   424,   426,   427,
     428,   429,   430,   431,   433,   434,   436,   439,   440,   442,
     443,   445,   446,   448,   449,   451,   452,   454,   455,   457,
     458,   459,   460,   461,   462,   464,   465,   466,   468,   469,
     471,   472,   473,   474,   475,   476,   478,   479,   482,   483,
     484,   485,   486,   487,   488,   490,   491,   492,   493,   494,
     495,   497,   498,   499,   501,   502,   504,   505,   506,   509,
     510,   512,   513,   515,   516,   518,   519,   522,   524,   525,
     526,   527,   528,   529,   530,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   543,   544,   545,   546,   548,
     549,   554,   557,   562,   563,   566,   567,   568,   569,   570,
     573,   576,   579,   580,   585,   589,   593,   597,   602,   605,
     612,   616,   619,   624,   627,   630,   633,   636,   639,   642,
     645,   649,   652,   659,   660,   661,   663,   664,   665,   668,
     671,   672,   675,   676,   679,   683,   684
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
  "APPL", "DOT", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "FFUNCTION",
  "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER", "HSLIDER",
  "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH", "VBARGRAPH",
  "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN", "TAN", "EXP",
  "LOG", "LOG10", "POWFUN", "SQRT", "ABS", "MIN", "MAX", "FMOD",
  "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL", "SELECT2",
  "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT", "ENDDEF", "VIRG",
  "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC", "DEF", "IMPORT",
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "MUTE", "IPAR",
  "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING",
  "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "vallist", "number", "statement", "doc",
  "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "definition",
  "defname", "params", "expression", "infixexp", "primitive", "ident",
  "name", "arglist", "argument", "string", "uqstring", "fstring", "fpar",
  "fseq", "fsum", "fprod", "finputs", "foutputs", "ffunction", "fconst",
  "fvariable", "button", "checkbox", "vslider", "hslider", "nentry",
  "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph", "signature",
  "fun", "typelist", "rulelist", "rule", "type", YY_NULLPTR
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
     375,   376,   377,   378,   379
};
# endif

#define YYPACT_NINF -302

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-302)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -302,    65,    25,  -302,   -33,    29,  -302,   -15,  -302,  -302,
    -302,     3,  -302,  -302,   -17,  -302,    50,   231,   383,   383,
    -302,    43,  -302,   124,  -302,   383,   383,  -302,   -15,  -302,
    -302,   112,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,   189,   273,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,   156,
     164,   207,   219,   228,   241,   245,   255,   257,   275,   277,
     293,   295,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,   333,
    -302,  -302,   383,   381,   382,   262,   387,  -302,   390,   402,
     403,   405,   406,   427,   440,   478,  -302,  -302,    15,    97,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,   248,
     478,   181,  -302,    13,     6,   183,   186,  -302,  -302,  -302,
    -302,  -302,  -302,   232,   232,   232,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   433,    33,   -17,   -17,
    -302,    27,   433,   433,   433,   433,   383,   383,   466,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,  -302,   433,   383,
    -302,   383,   461,   383,   383,   383,   383,   473,   383,   383,
     383,   383,   383,  -302,  -302,  -302,  -302,  -302,   203,   432,
     435,  -302,  -302,  -302,  -302,   549,   460,   -15,   -15,   479,
     494,   566,   568,   575,   576,   578,   579,   580,   627,    16,
    -302,  -302,   555,   556,     7,   221,   280,  -302,  -302,    -2,
    -302,   630,   631,   632,   633,    42,    49,   383,     5,  -302,
     493,   493,   493,   493,   493,   493,   505,   505,   505,   292,
     292,   292,   292,   292,   292,   292,   256,   272,  -302,    44,
      14,    97,   383,    97,    97,    84,  -302,  -302,   354,   354,
     234,   321,  -302,   517,   518,   519,   265,  -302,    18,   637,
     638,  -302,  -302,   383,   383,   383,   383,   383,   383,   383,
     383,   433,   617,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
      27,  -302,   383,   383,   383,   383,  -302,  -302,    57,  -302,
    -302,  -302,  -302,  -302,   264,    28,   263,   263,   263,  -302,
    -302,   640,   460,   193,   265,   265,   372,   459,   545,    55,
      64,    70,   558,   563,  -302,   569,  -302,   573,   585,   590,
     595,   546,  -302,  -302,  -302,  -302,   525,   527,   528,    50,
     199,  -302,    79,  -302,   574,   577,   383,   383,   383,  -302,
    -302,  -302,   383,   383,   383,   383,   383,   383,   383,   383,
    -302,  -302,  -302,   581,   460,   243,   232,  -302,  -302,  -302,
     600,   605,   610,    26,   128,   135,   148,   177,   226,   242,
     308,  -302,   583,  -302,   179,  -302,   383,   383,   383,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,   247,  -302,   615,
     620,   625,  -302,   180,   383,   383,   383,  -302,   141,   194,
     201,  -302,  -302,  -302
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   161,     0,    19,     4,
      17,     0,    44,    43,     0,   162,     0,    27,     0,     0,
     171,     0,   170,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   100,   101,   104,
     102,   103,   105,    89,    90,    96,    91,    92,    93,    95,
      97,    98,    99,   118,    94,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,    77,    78,     0,
      83,    84,     0,     0,     0,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,   169,    76,   133,     0,   163,
     155,   156,   157,   158,   159,   160,   138,   139,   140,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     0,
      53,     0,    16,     0,     0,     0,     0,    28,    79,    80,
      81,    82,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    15,    29,    30,    32,     0,     0,
       0,    34,    40,   205,   206,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,   135,     0,     0,     0,     0,     0,     9,    10,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,   202,
      68,    69,    72,    70,    71,    73,    54,    55,    64,    56,
      57,    58,    63,    65,    66,    67,    59,    60,    62,     0,
       0,   164,     0,   166,   167,   165,   168,     5,    50,    51,
      49,    48,    52,     0,     0,     0,     0,   199,     0,     0,
       0,   183,   184,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,   142,   143,    11,    12,    13,    14,
       0,   144,     0,     0,     0,     0,   178,   179,     0,   137,
     203,    74,    75,     6,     0,     0,     0,     0,     0,   172,
     173,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     8,     0,     0,     0,
       0,     0,    41,    47,    38,    39,     0,     0,     0,     0,
       0,   196,     0,   200,     0,     0,     0,     0,     0,   188,
     189,   190,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,     0,     0,     0,   193,   181,   182,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,     0,   197,     0,   201,     0,     0,     0,   192,
     191,   136,   174,   175,   176,   177,   204,     0,   194,     0,
       0,     0,   198,     0,     0,     0,     0,   195,     0,     0,
       0,   185,   186,   187
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -302,  -302,   483,   368,  -302,   336,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,    46,  -302,   -58,  -302,
    -302,     2,   -19,  -302,    22,   -24,  -166,   -86,   289,   379,
      66,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,  -302,
    -302,  -263,  -301,  -302,   401,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   280,   249,   250,     9,    17,    30,    31,
      32,    33,    34,    35,   145,   221,   366,    36,    10,    11,
     239,   139,   115,   116,   117,    16,   118,   119,    23,    21,
     341,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     225,   298,   372,   258,   259,   373
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     140,   226,   227,   228,   146,   320,   140,   140,     4,   207,
     208,   209,   210,   211,   212,     4,   207,   208,   209,   210,
     211,   212,   201,   311,    12,    -2,     4,   143,   144,     4,
     203,   204,   205,   279,   206,   342,   207,   208,   209,   210,
     211,   212,   245,   246,    13,   207,   208,   209,   210,   211,
     212,   201,   207,   208,   209,   210,   211,   212,   207,   208,
     209,   210,   211,   212,   201,     3,   152,   207,   208,   209,
     210,   211,   212,   207,   208,   209,   210,   211,   212,   370,
     321,    20,    18,   140,   257,    15,   396,   329,    19,   315,
     205,   328,   206,     5,   414,   202,   312,   343,   332,   247,
     248,   203,   204,   205,   167,   206,   419,     6,    14,     7,
     363,     5,     8,   241,     6,   281,   216,   283,   284,   285,
     286,   215,   326,   141,   331,     6,   433,     7,     6,   327,
       8,   412,   203,   204,   205,   379,   206,   361,   207,   208,
     209,   210,   211,   212,   380,   203,   204,   205,    22,   206,
     381,   207,   208,   209,   210,   211,   212,   140,   140,   397,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   255,   256,
     207,   208,   209,   210,   211,   212,   396,   396,   240,   140,
     140,   140,   140,   140,   251,   252,   253,   254,   203,   204,
     205,   142,   206,   299,   300,   203,   204,   205,   420,   206,
     288,   289,   290,   291,   292,   421,   394,   346,   347,   348,
     278,   441,   333,   352,   353,   223,   224,   147,   422,   207,
     208,   209,   210,   211,   212,   153,   357,   358,   359,   360,
     210,   211,   212,   154,   415,   207,   208,   209,   210,   211,
     212,   207,   208,   209,   210,   211,   212,   423,   214,   428,
     437,   148,   149,   140,   223,   224,    12,   207,   208,   209,
     210,   211,   212,   371,   442,   223,   224,   333,   395,   223,
     224,   443,   196,   197,   334,   198,   155,   140,   140,   140,
     400,   401,   402,   316,   317,   217,   403,   404,   156,   197,
     222,   198,    12,   218,   219,   220,   424,   157,   349,   350,
     351,   207,   208,   209,   210,   211,   212,   195,   196,   197,
     158,   198,   425,   413,   159,   213,   293,   432,   211,   212,
     429,   430,   431,   354,   160,   199,   161,    24,    25,   200,
      26,   362,    27,   170,    28,   150,   151,    29,   438,   439,
     440,   199,   318,   319,   162,   200,   163,    12,   208,   209,
     210,   211,   212,   339,   340,   140,   140,   140,   140,   140,
     140,   199,   164,     6,   165,   200,   203,   204,   205,   376,
     206,   364,   365,   367,   368,   426,   405,   406,   407,   408,
     409,   410,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     374,   375,   166,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     168,   169,   102,   203,   204,   205,   377,   206,   171,   172,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   173,   174,     6,   175,   176,   114,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   177,   198,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   178,   198,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,     6,   198,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   257,   282,   242,   243,   203,
     204,   205,   378,   206,   287,   294,   296,   199,   295,   301,
     297,   200,   203,   204,   205,   382,   206,   203,   204,   205,
     383,   206,   199,   303,   302,   304,   200,   203,   204,   205,
     385,   206,   305,   306,   199,   307,   308,   309,   200,   203,
     204,   205,   386,   206,   203,   204,   205,   387,   206,   203,
     204,   205,   388,   206,   203,   204,   205,   416,   206,   203,
     204,   205,   417,   206,   203,   204,   205,   418,   206,   203,
     204,   205,   434,   206,   203,   204,   205,   435,   206,   203,
     204,   205,   436,   206,   310,   313,   314,   322,   323,   324,
     325,   336,   337,   338,   344,   345,   355,   369,   384,   390,
     389,   391,   392,   244,   398,   335,   356,   399,   393,   330,
       0,   411,   427
};

static const yytype_int16 yycheck[] =
{
      19,   153,   154,   155,    28,     7,    25,    26,     1,     3,
       4,     5,     6,     7,     8,     1,     3,     4,     5,     6,
       7,     8,     7,     7,     2,     0,     1,    25,    26,     1,
       4,     5,     6,   199,     8,    17,     3,     4,     5,     6,
       7,     8,    15,    16,    77,     3,     4,     5,     6,     7,
       8,     7,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     7,     0,    44,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,   342,
      82,    98,    79,   102,    79,   100,     7,    82,    85,    82,
       6,   257,     8,    86,   395,    80,    80,    79,    84,    72,
      73,     4,     5,     6,   102,     8,    80,   100,    79,   102,
      82,    86,   105,    80,   100,   201,   110,   203,   204,   205,
     206,   108,    80,    80,    80,   100,   427,   102,   100,    80,
     105,   394,     4,     5,     6,    80,     8,    80,     3,     4,
       5,     6,     7,     8,    80,     4,     5,     6,    98,     8,
      80,     3,     4,     5,     6,     7,     8,   176,   177,    80,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   176,   177,
       3,     4,     5,     6,     7,     8,     7,     7,   166,   208,
     209,   210,   211,   212,   172,   173,   174,   175,     4,     5,
       6,    77,     8,   227,   228,     4,     5,     6,    80,     8,
     208,   209,   210,   211,   212,    80,    17,   303,   304,   305,
     198,    80,   280,   309,   310,    32,    33,   115,    80,     3,
       4,     5,     6,     7,     8,    79,   322,   323,   324,   325,
       6,     7,     8,    79,   396,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,    80,    77,    80,
      80,    72,    73,   282,    32,    33,   244,     3,     4,     5,
       6,     7,     8,    80,    80,    32,    33,   335,    79,    32,
      33,    80,    26,    27,   282,    29,    79,   306,   307,   308,
     376,   377,   378,    72,    73,   112,   382,   383,    79,    27,
     114,    29,   280,   120,   121,   122,    80,    79,   306,   307,
     308,     3,     4,     5,     6,     7,     8,    25,    26,    27,
      79,    29,    80,    80,    79,    77,   123,    80,     7,     8,
     416,   417,   418,   311,    79,    79,    79,   106,   107,    83,
     109,    77,   111,    81,   113,    72,    73,   116,   434,   435,
     436,    79,    72,    73,    79,    83,    79,   335,     4,     5,
       6,     7,     8,    98,    99,   384,   385,   386,   387,   388,
     389,    79,    79,   100,    79,    83,     4,     5,     6,     7,
       8,   118,   119,   337,   338,    77,   384,   385,   386,   387,
     388,   389,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
     344,   345,    79,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      79,    79,    79,     4,     5,     6,     7,     8,    81,    79,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    79,    79,   100,    79,    79,   103,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    79,    29,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    81,    29,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,   100,    29,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    79,    85,   168,   169,     4,
       5,     6,     7,     8,    81,   123,     7,    79,   123,    80,
     100,    83,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,    79,     7,    80,     7,    83,     4,     5,     6,
       7,     8,     7,     7,    79,     7,     7,     7,    83,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     7,    80,    80,     7,     7,     7,
       7,   124,   124,   124,     7,     7,    29,     7,    79,   124,
     104,   124,   124,   170,    80,   287,   320,    80,   369,   258,
      -1,    80,    79
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   126,   127,     0,     1,    86,   100,   102,   105,   131,
     143,   144,   149,    77,    79,   100,   150,   132,    79,    85,
      98,   154,    98,   153,   106,   107,   109,   111,   113,   116,
     133,   134,   135,   136,   137,   138,   142,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   103,   147,   148,   149,   151,   152,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   146,
     147,    80,    77,   146,   146,   139,   150,   115,    72,    73,
      72,    73,   149,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,   146,    79,    79,
      81,    81,    79,    79,    79,    79,    79,    79,    81,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    29,    79,
      83,     7,    80,     4,     5,     6,     8,     3,     4,     5,
       6,     7,     8,    77,    77,   108,   110,   112,   120,   121,
     122,   140,   114,    32,    33,   175,   180,   180,   180,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   145,
     149,    80,   154,   154,   127,    15,    16,    72,    73,   129,
     130,   149,   149,   149,   149,   146,   146,    79,   178,   179,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   149,   151,
     128,   152,    85,   152,   152,   152,   152,    81,   146,   146,
     146,   146,   146,   123,   123,   123,     7,   100,   176,   150,
     150,    80,    80,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    80,    80,    80,    82,    72,    73,    72,    73,
       7,    82,     7,     7,     7,     7,    80,    80,   151,    82,
     179,    80,    84,   143,   146,   128,   124,   124,   124,    98,
      99,   155,    17,    79,     7,     7,   152,   152,   152,   146,
     146,   146,   152,   152,   149,    29,   130,   152,   152,   152,
     152,    80,    77,    82,   118,   119,   141,   141,   141,     7,
     176,    80,   177,   180,   155,   155,     7,     7,     7,    80,
      80,    80,     7,     7,    79,     7,     7,     7,     7,   104,
     124,   124,   124,   153,    17,    79,     7,    80,    80,    80,
     152,   152,   152,   152,   152,   146,   146,   146,   146,   146,
     146,    80,   176,    80,   177,   180,     7,     7,     7,    80,
      80,    80,    80,    80,    80,    80,    77,    79,    80,   152,
     152,   152,    80,   177,     7,     7,     7,    80,   152,   152,
     152,    80,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   125,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   130,   130,   130,   130,   131,   131,   131,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   135,
     136,   137,   138,   139,   139,   140,   140,   140,   141,   141,
     142,   143,   143,   143,   144,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   149,   150,   151,   151,   152,   152,   152,   152,   152,
     153,   154,   155,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   175,   175,   175,   175,   175,   176,
     177,   177,   178,   178,   179,   180,   180
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
       3,     3,     3,     3,     4,     4,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     8,     4,     1,     1,
       1,     4,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       8,     7,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     5,     7,     9,     4,     6,     8,     1,
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
#line 311 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gResult = formatDefinitions((yyval.exp)); }
#line 1774 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 314 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1780 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 315 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1786 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 317 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1792 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 318 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1798 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 325 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1804 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 326 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1810 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 329 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1816 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 330 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1822 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 331 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1828 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 332 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1834 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 333 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1840 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 334 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1846 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 338 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1852 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 339 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = nil; }
#line 1858 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1864 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 341 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1870 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 344 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1876 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 345 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1882 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 348 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1888 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 349 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1894 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 350 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1900 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1906 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1912 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 353 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1918 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 356 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1924 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 357 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1930 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 360 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1936 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 363 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1942 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 366 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1948 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 369 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1954 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 372 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1960 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 373 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1966 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 376 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1972 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 377 "parser/faustparser.y" /* yacc.c:1646  */
    { gStripDocSwitch = (yyvsp[-1].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
#line 1978 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 378 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDistributedSwitch = (yyvsp[-1].b); }
#line 1984 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 381 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 1990 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 382 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 1996 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 385 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2002 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 388 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2008 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 389 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2014 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 390 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2020 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 393 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2026 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 396 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2032 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 397 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2038 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 400 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2044 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 401 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2050 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 402 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2056 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 403 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2062 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 404 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2068 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 405 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2074 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 406 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2080 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 409 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2086 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 410 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2092 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2098 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 412 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2104 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 413 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2110 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 414 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gPowPrim->box()); }
#line 2116 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 415 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2122 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 416 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2128 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 417 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2134 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 419 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2140 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2146 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 421 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2152 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 423 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2158 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 424 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2164 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 426 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2170 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 427 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2176 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 428 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2182 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 429 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2188 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2194 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 431 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2200 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 433 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2206 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 434 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2212 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 436 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2218 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 439 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2224 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 440 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2230 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 442 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2236 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 443 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2242 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 445 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2248 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 446 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2254 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 448 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2260 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 449 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2266 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 451 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2272 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 452 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2278 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 454 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2284 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 455 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2290 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 457 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2296 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2302 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 459 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2308 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 460 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2314 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2320 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 462 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2326 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 464 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2332 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 465 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2338 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 466 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2344 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 468 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2350 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 469 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2356 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 471 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2362 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 472 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2368 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 473 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2374 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2380 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 475 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2386 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 476 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2392 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 478 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2398 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 479 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMute); }
#line 2404 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 482 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAcosPrim->box(); }
#line 2410 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 483 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAsinPrim->box(); }
#line 2416 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtanPrim->box(); }
#line 2422 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtan2Prim->box(); }
#line 2428 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 486 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCosPrim->box(); }
#line 2434 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 487 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSinPrim->box(); }
#line 2440 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 488 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gTanPrim->box(); }
#line 2446 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gExpPrim->box(); }
#line 2452 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 491 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLogPrim->box(); }
#line 2458 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLog10Prim->box(); }
#line 2464 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 493 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2470 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2476 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSqrtPrim->box(); }
#line 2482 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 497 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAbsPrim->box(); }
#line 2488 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 498 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMinPrim->box(); }
#line 2494 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMaxPrim->box(); }
#line 2500 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 501 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFmodPrim->box(); }
#line 2506 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 502 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRemainderPrim->box(); }
#line 2512 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 504 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFloorPrim->box(); }
#line 2518 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 505 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCeilPrim->box(); }
#line 2524 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRintPrim->box(); }
#line 2530 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 509 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2536 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 510 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2542 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2548 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 513 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2554 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 515 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2560 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 516 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2566 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 518 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2572 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 520 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2578 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 522 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2584 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2590 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 525 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2596 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2602 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 527 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2608 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 528 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2614 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 529 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2620 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gWaveForm); gWaveForm.clear(); }
#line 2626 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2632 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 533 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2638 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 534 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2644 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2650 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 536 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2656 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 537 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2662 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 538 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2668 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 539 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2674 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 540 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2680 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 541 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2686 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 543 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2692 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 544 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2698 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2704 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2710 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 548 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2716 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 549 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2722 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 554 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2728 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 557 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2734 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 562 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2740 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 563 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2746 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 566 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2752 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 567 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2758 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 568 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2764 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 569 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2770 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 570 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2776 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 573 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2782 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 576 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2788 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 579 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2794 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 580 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2800 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 586 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2806 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 590 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2812 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 594 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2818 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 598 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2824 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 602 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2830 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 605 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2836 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 613 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2842 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 617 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2848 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 620 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2854 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 624 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2860 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 627 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2866 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 631 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2872 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 634 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2878 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 637 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2884 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 640 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2890 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 643 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2896 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 646 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2902 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 650 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2908 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 653 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2914 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 659 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2920 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 660 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2926 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 661 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2932 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 663 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2938 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 664 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2944 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 665 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2950 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 668 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2956 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 671 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2962 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 672 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2968 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 675 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2974 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 676 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 2980 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 680 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 2986 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 683 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 2992 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 684 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 2998 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3002 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 687 "parser/faustparser.y" /* yacc.c:1906  */


