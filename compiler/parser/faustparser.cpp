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
    ENABLE = 346,
    CONTROL = 347,
    IPAR = 348,
    ISEQ = 349,
    ISUM = 350,
    IPROD = 351,
    INPUTS = 352,
    OUTPUTS = 353,
    STRING = 354,
    FSTRING = 355,
    IDENT = 356,
    EXTRA = 357,
    DECLARE = 358,
    CASE = 359,
    ARROW = 360,
    BDOC = 361,
    EDOC = 362,
    BEQN = 363,
    EEQN = 364,
    BDGM = 365,
    EDGM = 366,
    BLST = 367,
    ELST = 368,
    BMETADATA = 369,
    EMETADATA = 370,
    DOCCHAR = 371,
    NOTICE = 372,
    LISTING = 373,
    LSTTRUE = 374,
    LSTFALSE = 375,
    LSTDEPENDENCIES = 376,
    LSTMDOCTAGS = 377,
    LSTDISTRIBUTED = 378,
    LSTEQ = 379,
    LSTQ = 380
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

#line 311 "parser/faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 328 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYNTOKENS  126
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  207
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  445

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   380

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
     125
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   312,   312,   315,   316,   318,   319,   326,   327,   330,
     331,   332,   333,   334,   335,   339,   340,   341,   342,   345,
     346,   349,   350,   351,   352,   353,   354,   357,   358,   361,
     364,   367,   370,   373,   374,   377,   378,   379,   382,   383,
     386,   389,   390,   391,   394,   397,   398,   401,   402,   403,
     404,   405,   406,   407,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   420,   421,   422,   424,   425,   427,   428,
     429,   430,   431,   432,   434,   435,   437,   440,   441,   443,
     444,   446,   447,   449,   450,   452,   453,   455,   456,   458,
     459,   460,   461,   462,   463,   465,   466,   467,   469,   470,
     472,   473,   474,   475,   476,   477,   479,   480,   481,   484,
     485,   486,   487,   488,   489,   490,   492,   493,   494,   495,
     496,   497,   499,   500,   501,   503,   504,   506,   507,   508,
     511,   512,   514,   515,   517,   518,   520,   521,   524,   526,
     527,   528,   529,   530,   531,   532,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   545,   546,   547,   548,
     550,   551,   556,   559,   564,   565,   568,   569,   570,   571,
     572,   575,   578,   581,   582,   587,   591,   595,   599,   604,
     607,   614,   618,   621,   626,   629,   632,   635,   638,   641,
     644,   647,   651,   654,   661,   662,   663,   665,   666,   667,
     670,   673,   674,   677,   678,   681,   685,   686
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
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "ENABLE", "CONTROL",
  "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING",
  "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC",
  "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
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
     375,   376,   377,   378,   379,   380
};
# endif

#define YYPACT_NINF -299

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-299)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -299,    82,    25,  -299,    36,    30,  -299,    -7,  -299,  -299,
    -299,    10,  -299,  -299,    40,  -299,    89,   231,   384,   384,
    -299,    44,  -299,    69,  -299,   384,   384,  -299,    -7,  -299,
    -299,    86,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,   154,   193,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   183,
     208,   229,   239,   258,   268,   274,   285,   286,   293,   295,
     296,   297,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   304,
    -299,  -299,   384,   305,   306,   135,   161,  -299,  -299,   332,
     333,   334,   382,   383,   390,   214,   480,  -299,  -299,    34,
     320,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
     265,   480,   197,  -299,    13,     6,   233,   355,  -299,  -299,
    -299,  -299,  -299,  -299,   177,   177,   177,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,   243,    26,    40,
      40,  -299,    27,   243,   243,   243,   243,   384,   384,   404,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,  -299,   243,
     384,  -299,   384,   399,   384,   384,   384,   384,   405,   384,
     384,   384,   384,   384,  -299,  -299,  -299,  -299,  -299,   363,
     411,   423,  -299,  -299,  -299,  -299,   501,   422,    -7,    -7,
     468,   476,   550,   551,   553,   554,   555,   568,   569,   570,
      57,  -299,  -299,   504,   505,     4,   163,   184,  -299,  -299,
      15,  -299,   580,   581,   582,   634,    32,    43,   384,   220,
    -299,   495,   495,   495,   495,   495,   495,   507,   507,   507,
     294,   294,   294,   294,   294,   294,   294,   278,   257,  -299,
      58,     7,   320,   384,   320,   320,   235,  -299,  -299,   374,
     374,    95,   269,  -299,   517,   518,   519,   201,  -299,    68,
     638,   639,  -299,  -299,   384,   384,   384,   384,   384,   384,
     384,   384,   243,   618,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,    27,  -299,   384,   384,   384,   384,  -299,  -299,    77,
    -299,  -299,  -299,  -299,  -299,   275,    14,   210,   210,   210,
    -299,  -299,   641,   422,    12,   201,   201,   460,   547,   560,
      49,    55,    64,   565,   575,  -299,   571,  -299,   587,   592,
     597,   602,   544,  -299,  -299,  -299,  -299,   526,   527,   528,
      89,   108,  -299,    80,  -299,   574,   576,   384,   384,   384,
    -299,  -299,  -299,   384,   384,   384,   384,   384,   384,   384,
     384,  -299,  -299,  -299,   577,   422,    47,   177,  -299,  -299,
    -299,   607,   612,   617,   128,   137,    70,   148,   178,   226,
     242,   309,  -299,   579,  -299,   142,  -299,   384,   384,   384,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   174,  -299,
     622,   627,   632,  -299,   216,   384,   384,   384,  -299,   195,
     247,   255,  -299,  -299,  -299
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   162,     0,    19,     4,
      17,     0,    44,    43,     0,   163,     0,    27,     0,     0,
     172,     0,   171,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   100,   101,   104,
     102,   103,   105,    89,    90,    96,    91,    92,    93,    95,
      97,    98,    99,   119,    94,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    77,    78,     0,
      83,    84,     0,     0,     0,     0,     0,   107,   108,     0,
       0,     0,     0,     0,     0,     0,   170,    76,   134,     0,
     164,   156,   157,   158,   159,   160,   161,   139,   140,   141,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,    53,     0,    16,     0,     0,     0,     0,    28,    79,
      80,    81,    82,   135,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    15,    29,    30,    32,     0,
       0,     0,    34,    40,   206,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,   136,     0,     0,     0,     0,     0,     9,    10,
       0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
     203,    68,    69,    72,    70,    71,    73,    54,    55,    64,
      56,    57,    58,    63,    65,    66,    67,    59,    60,    62,
       0,     0,   165,     0,   167,   168,   166,   169,     5,    50,
      51,    49,    48,    52,     0,     0,     0,     0,   200,     0,
       0,     0,   184,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   142,   143,   144,    11,    12,    13,
      14,     0,   145,     0,     0,     0,     0,   179,   180,     0,
     138,   204,    74,    75,     6,     0,     0,     0,     0,     0,
     173,   174,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     8,     0,     0,
       0,     0,     0,    41,    47,    38,    39,     0,     0,     0,
       0,     0,   197,     0,   201,     0,     0,     0,     0,     0,
     189,   190,   191,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    37,     0,     0,     0,     0,   194,   182,
     183,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,     0,   198,     0,   202,     0,     0,     0,
     193,   192,   137,   175,   176,   177,   178,   205,     0,   195,
       0,     0,     0,   199,     0,     0,     0,     0,   196,     0,
       0,     0,   186,   187,   188
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -299,  -299,   484,   371,  -299,   339,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,    21,  -299,  -188,  -299,
    -299,     2,   -19,  -299,    22,   -24,  -177,   -86,   291,   380,
      17,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -255,  -298,  -299,   403,  -153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   281,   250,   251,     9,    17,    30,    31,
      32,    33,    34,    35,   146,   222,   367,    36,    10,    11,
     240,   140,   116,   117,   118,    16,   119,   120,    23,    21,
     342,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     226,   299,   373,   259,   260,   374
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     141,   227,   228,   229,   147,     4,   141,   141,     4,   208,
     209,   210,   211,   212,   213,     4,   208,   209,   210,   211,
     212,   213,   321,   280,    12,    -2,     4,   144,   145,   208,
     209,   210,   211,   212,   213,   208,   209,   210,   211,   212,
     213,   202,   246,   247,   224,   225,   208,   209,   210,   211,
     212,   213,   208,   209,   210,   211,   212,   213,   208,   209,
     210,   211,   212,   213,   312,   202,   153,   208,   209,   210,
     211,   212,   213,   208,   209,   210,   211,   212,   213,   224,
     225,   329,     3,   141,   202,   343,   316,   397,   371,    18,
       5,   333,   372,   334,    15,    19,   364,   322,   415,   248,
     249,   211,   212,   213,   168,     6,   242,     7,     6,    14,
       8,     5,   327,    13,   203,     6,   282,   217,   284,   285,
     286,   287,   216,   328,   142,   395,     6,   414,     7,   380,
     434,     8,   204,   205,   206,   381,   207,   313,   332,    20,
     413,   204,   205,   206,   382,   207,   143,   344,   334,   397,
     422,   208,   209,   210,   211,   212,   213,   362,   141,   141,
     398,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   256,
     257,   208,   209,   210,   211,   212,   213,   396,    22,   241,
     141,   141,   141,   141,   141,   252,   253,   254,   255,   204,
     205,   206,   148,   207,   300,   301,   224,   225,   420,   224,
     225,   289,   290,   291,   292,   293,   171,   421,   347,   348,
     349,   279,   429,   397,   353,   354,   149,   150,   423,   208,
     209,   210,   211,   212,   213,   317,   318,   358,   359,   360,
     361,   206,   172,   207,   416,   208,   209,   210,   211,   212,
     213,   204,   205,   206,   433,   207,   319,   320,   424,   204,
     205,   206,   154,   207,   141,   151,   152,    12,   208,   209,
     210,   211,   212,   213,   215,   442,   212,   213,   208,   209,
     210,   211,   212,   213,   198,   335,   199,   155,   141,   141,
     141,   401,   402,   403,     6,   179,   438,   404,   405,   258,
     340,   341,   330,    12,   197,   198,   425,   199,   156,   350,
     351,   352,   208,   209,   210,   211,   212,   213,   157,   196,
     197,   198,   426,   199,   204,   205,   206,   443,   207,   365,
     366,   430,   431,   432,   355,   444,   200,   158,    24,    25,
     201,    26,   214,    27,     6,    28,   218,   159,    29,   439,
     440,   441,   363,   160,   219,   220,   221,   200,    12,   368,
     369,   201,   375,   376,   161,   162,   141,   141,   141,   141,
     141,   141,   163,   200,   164,   165,   166,   201,   209,   210,
     211,   212,   213,   167,   169,   170,   427,   406,   407,   408,
     409,   410,   411,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   173,   174,   175,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   176,   177,   102,   204,   205,   206,   377,   207,   178,
     223,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   258,   283,     6,   288,   294,   115,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   297,   199,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   298,   199,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   295,   199,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   296,   302,   243,
     244,   204,   205,   206,   378,   207,   303,   304,   305,   200,
     306,   307,   308,   201,   204,   205,   206,   379,   207,   204,
     205,   206,   383,   207,   200,   309,   310,   311,   201,   204,
     205,   206,   384,   207,   314,   315,   200,   323,   324,   325,
     201,   204,   205,   206,   386,   207,   204,   205,   206,   387,
     207,   204,   205,   206,   388,   207,   204,   205,   206,   389,
     207,   204,   205,   206,   417,   207,   204,   205,   206,   418,
     207,   204,   205,   206,   419,   207,   204,   205,   206,   435,
     207,   204,   205,   206,   436,   207,   204,   205,   206,   437,
     207,   326,   337,   338,   339,   345,   346,   356,   370,   390,
     385,   391,   392,   393,   399,   245,   400,   412,   428,   336,
     357,   394,   331
};

static const yytype_uint16 yycheck[] =
{
      19,   154,   155,   156,    28,     1,    25,    26,     1,     3,
       4,     5,     6,     7,     8,     1,     3,     4,     5,     6,
       7,     8,     7,   200,     2,     0,     1,    25,    26,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,     7,    15,    16,    32,    33,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     7,     7,    44,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,    32,
      33,   258,     0,   102,     7,    17,    82,     7,   343,    79,
      86,    84,    80,   281,   101,    85,    82,    82,   396,    72,
      73,     6,     7,     8,   102,   101,    80,   103,   101,    79,
     106,    86,    80,    77,    80,   101,   202,   111,   204,   205,
     206,   207,   109,    80,    80,    17,   101,    80,   103,    80,
     428,   106,     4,     5,     6,    80,     8,    80,    80,    99,
     395,     4,     5,     6,    80,     8,    77,    79,   336,     7,
      80,     3,     4,     5,     6,     7,     8,    80,   177,   178,
      80,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   177,
     178,     3,     4,     5,     6,     7,     8,    79,    99,   167,
     209,   210,   211,   212,   213,   173,   174,   175,   176,     4,
       5,     6,   116,     8,   228,   229,    32,    33,    80,    32,
      33,   209,   210,   211,   212,   213,    81,    80,   304,   305,
     306,   199,    80,     7,   310,   311,    72,    73,    80,     3,
       4,     5,     6,     7,     8,    72,    73,   323,   324,   325,
     326,     6,    81,     8,   397,     3,     4,     5,     6,     7,
       8,     4,     5,     6,    80,     8,    72,    73,    80,     4,
       5,     6,    79,     8,   283,    72,    73,   245,     3,     4,
       5,     6,     7,     8,    77,    80,     7,     8,     3,     4,
       5,     6,     7,     8,    27,   283,    29,    79,   307,   308,
     309,   377,   378,   379,   101,    81,    80,   383,   384,    79,
      99,   100,    82,   281,    26,    27,    80,    29,    79,   307,
     308,   309,     3,     4,     5,     6,     7,     8,    79,    25,
      26,    27,    80,    29,     4,     5,     6,    80,     8,   119,
     120,   417,   418,   419,   312,    80,    79,    79,   107,   108,
      83,   110,    77,   112,   101,   114,   113,    79,   117,   435,
     436,   437,    77,    79,   121,   122,   123,    79,   336,   338,
     339,    83,   345,   346,    79,    79,   385,   386,   387,   388,
     389,   390,    79,    79,    79,    79,    79,    83,     4,     5,
       6,     7,     8,    79,    79,    79,    77,   385,   386,   387,
     388,   389,   390,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    79,    79,    79,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    79,    79,    79,     4,     5,     6,     7,     8,    79,
     115,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    79,    85,   101,    81,   124,   104,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     7,    29,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,   101,    29,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   124,    29,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   124,    80,   169,
     170,     4,     5,     6,     7,     8,    80,     7,     7,    79,
       7,     7,     7,    83,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,    79,     7,     7,     7,    83,     4,
       5,     6,     7,     8,    80,    80,    79,     7,     7,     7,
      83,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     7,   125,   125,   125,     7,     7,    29,     7,   105,
      79,   125,   125,   125,    80,   171,    80,    80,    79,   288,
     321,   370,   259
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   127,   128,     0,     1,    86,   101,   103,   106,   132,
     144,   145,   150,    77,    79,   101,   151,   133,    79,    85,
      99,   155,    99,   154,   107,   108,   110,   112,   114,   117,
     134,   135,   136,   137,   138,   139,   143,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   104,   148,   149,   150,   152,
     153,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     147,   148,    80,    77,   147,   147,   140,   151,   116,    72,
      73,    72,    73,   150,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,   147,    79,
      79,    81,    81,    79,    79,    79,    79,    79,    79,    81,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    29,
      79,    83,     7,    80,     4,     5,     6,     8,     3,     4,
       5,     6,     7,     8,    77,    77,   109,   111,   113,   121,
     122,   123,   141,   115,    32,    33,   176,   181,   181,   181,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     146,   150,    80,   155,   155,   128,    15,    16,    72,    73,
     130,   131,   150,   150,   150,   150,   147,   147,    79,   179,
     180,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   150,
     152,   129,   153,    85,   153,   153,   153,   153,    81,   147,
     147,   147,   147,   147,   124,   124,   124,     7,   101,   177,
     151,   151,    80,    80,     7,     7,     7,     7,     7,     7,
       7,     7,     7,    80,    80,    80,    82,    72,    73,    72,
      73,     7,    82,     7,     7,     7,     7,    80,    80,   152,
      82,   180,    80,    84,   144,   147,   129,   125,   125,   125,
      99,   100,   156,    17,    79,     7,     7,   153,   153,   153,
     147,   147,   147,   153,   153,   150,    29,   131,   153,   153,
     153,   153,    80,    77,    82,   119,   120,   142,   142,   142,
       7,   177,    80,   178,   181,   156,   156,     7,     7,     7,
      80,    80,    80,     7,     7,    79,     7,     7,     7,     7,
     105,   125,   125,   125,   154,    17,    79,     7,    80,    80,
      80,   153,   153,   153,   153,   153,   147,   147,   147,   147,
     147,   147,    80,   177,    80,   178,   181,     7,     7,     7,
      80,    80,    80,    80,    80,    80,    80,    77,    79,    80,
     153,   153,   153,    80,   178,     7,     7,     7,    80,   153,
     153,   153,    80,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   126,   127,   128,   128,   129,   129,   130,   130,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   134,   135,   135,   136,
     137,   138,   139,   140,   140,   141,   141,   141,   142,   142,
     143,   144,   144,   144,   145,   146,   146,   147,   147,   147,
     147,   147,   147,   147,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150,   151,   152,   152,   153,   153,   153,   153,
     153,   154,   155,   156,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   176,   176,   176,   176,   176,
     177,   178,   178,   179,   179,   180,   181,   181
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
       1,     1,     1,     1,     1,     2,     3,     8,     4,     1,
       1,     1,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     8,     8,     8,     8,     4,
       4,     8,     7,     7,     4,     4,    12,    12,    12,     6,
       6,     6,     8,     8,     5,     7,     9,     4,     6,     8,
       1,     1,     3,     1,     2,     6,     1,     1
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
#line 312 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gResult = formatDefinitions((yyval.exp)); }
#line 1776 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 315 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1782 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 316 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1788 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 318 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1794 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 319 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1800 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 326 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1806 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 327 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1812 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 330 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1818 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 331 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1824 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 332 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1830 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 333 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1836 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 334 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1842 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 335 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1848 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 339 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1854 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = nil; }
#line 1860 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 341 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1866 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 342 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1872 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 345 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1878 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 346 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1884 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 349 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1890 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 350 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1896 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1902 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1908 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 353 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1914 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 354 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1920 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 357 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1926 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 358 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1932 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 361 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1938 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 364 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1944 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 367 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1950 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 370 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1956 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 373 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1962 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 374 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1968 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 377 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1974 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 378 "parser/faustparser.y" /* yacc.c:1646  */
    { gStripDocSwitch = (yyvsp[-1].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
#line 1980 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 379 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDistributedSwitch = (yyvsp[-1].b); }
#line 1986 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 382 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 1992 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 383 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 1998 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 386 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2004 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 389 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2010 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 390 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2016 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 391 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2022 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 394 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2028 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 397 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2034 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 398 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2040 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 401 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2046 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 402 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2052 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 403 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2058 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 404 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2064 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 405 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2070 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 406 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2076 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 407 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2082 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 410 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2088 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2094 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 412 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2100 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 413 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2106 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 414 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2112 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 415 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gPowPrim->box()); }
#line 2118 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 416 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2124 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 417 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2130 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 418 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2136 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2142 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 421 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2148 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 422 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2154 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 424 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2160 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 425 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2166 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 427 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2172 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 428 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2178 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 429 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2184 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2190 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 431 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2196 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 432 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2202 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 434 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2208 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 435 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2214 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 437 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2220 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 440 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2226 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 441 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2232 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 443 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2238 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 444 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2244 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 446 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2250 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 447 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2256 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 449 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2262 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 450 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2268 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 452 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2274 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 453 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2280 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 455 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2286 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 456 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2292 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2298 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 459 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2304 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 460 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2310 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2316 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 462 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2322 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 463 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2328 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 465 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2334 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 466 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2340 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 467 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2346 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 469 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2352 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 470 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2358 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 472 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2364 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 473 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2370 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2376 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 475 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2382 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 476 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2388 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 477 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2394 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 479 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2400 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 480 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2406 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 481 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2412 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAcosPrim->box(); }
#line 2418 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAsinPrim->box(); }
#line 2424 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 486 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtanPrim->box(); }
#line 2430 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 487 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtan2Prim->box(); }
#line 2436 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 488 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCosPrim->box(); }
#line 2442 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 489 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSinPrim->box(); }
#line 2448 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gTanPrim->box(); }
#line 2454 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gExpPrim->box(); }
#line 2460 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 493 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLogPrim->box(); }
#line 2466 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLog10Prim->box(); }
#line 2472 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2478 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 496 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2484 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 497 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSqrtPrim->box(); }
#line 2490 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAbsPrim->box(); }
#line 2496 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 500 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMinPrim->box(); }
#line 2502 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 501 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMaxPrim->box(); }
#line 2508 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 503 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFmodPrim->box(); }
#line 2514 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 504 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRemainderPrim->box(); }
#line 2520 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFloorPrim->box(); }
#line 2526 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 507 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCeilPrim->box(); }
#line 2532 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 508 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRintPrim->box(); }
#line 2538 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 511 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2544 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2550 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 514 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2556 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 515 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2562 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 517 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2568 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 518 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2574 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 520 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2580 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 522 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2586 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2592 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2598 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 527 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2604 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 528 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2610 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 529 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2616 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2622 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 531 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2628 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gWaveForm); gWaveForm.clear(); }
#line 2634 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 534 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2640 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2646 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 536 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2652 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 537 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2658 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 538 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2664 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 539 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2670 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 540 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2676 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 541 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2682 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 542 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2688 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 543 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2694 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2700 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2706 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 547 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2712 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 548 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2718 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 550 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2724 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 551 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2730 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 556 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2736 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 559 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2742 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 564 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2748 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 565 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2754 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 568 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2760 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 569 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2766 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 570 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2772 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 571 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2778 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 572 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2784 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 575 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2790 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 578 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2796 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 581 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2802 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 582 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2808 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 588 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2814 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 592 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2820 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 596 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2826 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 600 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2832 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 604 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2838 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 607 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2844 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 615 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2850 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 619 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2856 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 622 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2862 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 626 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2868 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 629 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2874 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 633 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2880 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 636 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2886 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 639 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2892 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 642 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2898 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 645 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2904 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 648 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2910 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 652 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2916 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 655 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2922 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 661 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2928 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 662 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2934 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 663 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2940 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 665 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2946 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 666 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2952 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 667 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2958 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 670 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2964 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 673 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2970 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 674 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2976 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 677 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2982 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 678 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 2988 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 682 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 2994 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 685 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 3000 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 686 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 3006 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3010 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 689 "parser/faustparser.y" /* yacc.c:1906  */


