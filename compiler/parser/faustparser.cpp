/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

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
    IPAR = 346,
    ISEQ = 347,
    ISUM = 348,
    IPROD = 349,
    INPUTS = 350,
    OUTPUTS = 351,
    STRING = 352,
    FSTRING = 353,
    IDENT = 354,
    EXTRA = 355,
    DECLARE = 356,
    CASE = 357,
    ARROW = 358,
    BDOC = 359,
    EDOC = 360,
    BEQN = 361,
    EEQN = 362,
    BDGM = 363,
    EDGM = 364,
    BLST = 365,
    ELST = 366,
    BMETADATA = 367,
    EMETADATA = 368,
    DOCCHAR = 369,
    NOTICE = 370,
    LISTING = 371,
    LSTTRUE = 372,
    LSTFALSE = 373,
    LSTDEPENDENCIES = 374,
    LSTMDOCTAGS = 375,
    LSTDISTRIBUTED = 376,
    LSTEQ = 377,
    LSTQ = 378
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 78 "parser/faustparser.y" /* yacc.c:355  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 309 "parser/faustparser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 324 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYLAST   661

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  124
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  443

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

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
     115,   116,   117,   118,   119,   120,   121,   122,   123
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   310,   310,   313,   314,   316,   317,   324,   325,   328,
     329,   330,   331,   332,   333,   337,   338,   339,   340,   343,
     344,   347,   348,   349,   350,   351,   352,   355,   356,   359,
     362,   365,   368,   371,   372,   375,   376,   377,   380,   381,
     384,   387,   388,   389,   392,   395,   396,   399,   400,   401,
     402,   403,   404,   405,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   418,   419,   420,   422,   423,   425,   426,
     427,   428,   429,   430,   432,   433,   435,   438,   439,   441,
     442,   444,   445,   447,   448,   450,   451,   453,   454,   456,
     457,   458,   459,   460,   461,   463,   464,   465,   467,   468,
     470,   471,   472,   473,   474,   475,   477,   479,   480,   481,
     482,   483,   484,   485,   487,   488,   489,   490,   491,   492,
     494,   495,   496,   498,   499,   501,   502,   503,   506,   507,
     509,   510,   512,   513,   515,   516,   519,   521,   522,   523,
     524,   525,   526,   527,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   540,   541,   542,   543,   545,   546,
     551,   554,   559,   560,   563,   564,   565,   566,   567,   570,
     573,   576,   577,   582,   586,   590,   594,   599,   602,   609,
     613,   616,   621,   624,   627,   630,   633,   636,   639,   642,
     646,   649,   656,   657,   658,   660,   661,   662,   665,   668,
     669,   672,   673,   676,   680,   681
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
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "IPAR", "ISEQ",
  "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT",
  "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC", "BEQN", "EEQN",
  "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR",
  "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
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
     375,   376,   377,   378
};
# endif

#define YYPACT_NINF -319

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-319)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -319,    86,    20,  -319,    14,    32,  -319,     1,  -319,  -319,
    -319,    10,  -319,  -319,    46,  -319,   109,   218,   382,   382,
    -319,    52,  -319,   158,  -319,   382,   382,  -319,     1,  -319,
    -319,   150,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,   111,   170,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,   169,
     195,   200,   205,   206,   219,   225,   235,   243,   246,   248,
     250,   252,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,   255,
    -319,  -319,   382,   264,   265,   260,   269,   266,   275,   278,
     279,   281,   282,   290,   476,  -319,  -319,    19,   311,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,   332,   476,
     271,  -319,    11,     5,   -27,   238,  -319,  -319,  -319,  -319,
    -319,  -319,   165,   165,   165,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,   247,    27,    46,    46,  -319,
      81,   247,   247,   247,   247,   382,   382,   284,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,  -319,   247,   382,  -319,
     382,   277,   382,   382,   382,   382,   292,   382,   382,   382,
     382,   382,  -319,  -319,  -319,  -319,  -319,   288,   289,   337,
    -319,  -319,  -319,  -319,   365,   361,     1,     1,   388,   399,
     473,   475,   497,   505,   526,   527,   528,   540,    35,  -319,
    -319,   403,   446,     3,   145,   148,  -319,  -319,    16,  -319,
     547,   549,   550,   551,    33,    42,   382,    76,  -319,   498,
     498,   498,   498,   498,   498,   519,   519,   519,   270,   270,
     270,   270,   270,   270,   270,   276,   291,  -319,    36,    21,
     311,   382,   311,   311,    95,  -319,  -319,   371,   371,   283,
      67,  -319,   447,   448,   451,   153,  -319,    47,   568,   569,
    -319,  -319,   382,   382,   382,   382,   382,   382,   382,   382,
     247,   570,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
      81,  -319,   382,   382,   382,   382,  -319,  -319,    37,  -319,
    -319,  -319,  -319,   459,    28,   139,   139,   139,  -319,  -319,
     571,   361,    55,   153,   153,   376,   524,   545,    48,    54,
      64,   578,   583,  -319,   500,  -319,   588,   599,   604,   609,
     494,  -319,  -319,  -319,  -319,   477,   478,   525,   109,    73,
    -319,    56,  -319,   572,   573,   382,   382,   382,  -319,  -319,
    -319,   382,   382,   382,   382,   382,   382,   382,   382,  -319,
    -319,  -319,   574,   361,   175,   165,  -319,  -319,  -319,   614,
     619,   624,   125,   241,   134,   142,   220,   226,   233,   503,
    -319,   576,  -319,    71,  -319,   382,   382,   382,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,   183,  -319,   629,   634,
     639,  -319,   102,   382,   382,   382,  -319,   262,   267,   272,
    -319,  -319,  -319
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   160,     0,    19,     4,
      17,     0,    44,    43,     0,   161,     0,    27,     0,     0,
     170,     0,   169,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   100,   101,   104,
     102,   103,   105,    89,    90,    96,    91,    92,    93,    95,
      97,    98,    99,   117,    94,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,    77,    78,     0,
      83,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,    76,   132,     0,   162,   154,
     155,   156,   157,   158,   159,   137,   138,   139,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,    53,
       0,    16,     0,     0,     0,     0,    28,    79,    80,    81,
      82,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    15,    29,    30,    32,     0,     0,     0,
      34,    40,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
     134,     0,     0,     0,     0,     0,     9,    10,     0,     7,
       0,     0,     0,     0,     0,     0,     0,     0,   201,    68,
      69,    72,    70,    71,    73,    54,    55,    64,    56,    57,
      58,    63,    65,    66,    67,    59,    60,    62,     0,     0,
     163,     0,   165,   166,   164,   167,     5,    50,    51,    49,
      48,    52,     0,     0,     0,     0,   198,     0,     0,     0,
     182,   183,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,   141,   142,     6,    11,    12,    13,    14,
       0,   143,     0,     0,     0,     0,   177,   178,     0,   136,
     202,    74,    75,     0,     0,     0,     0,     0,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     8,     0,     0,     0,     0,
       0,    41,    47,    38,    39,     0,     0,     0,     0,     0,
     195,     0,   199,     0,     0,     0,     0,     0,   187,   188,
     189,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,     0,     0,     0,     0,   192,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,   196,     0,   200,     0,     0,     0,   191,   190,
     135,   173,   174,   175,   176,   203,     0,   193,     0,     0,
       0,   197,     0,     0,     0,     0,   194,     0,     0,     0,
     184,   185,   186
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -319,  -319,  -319,  -174,  -319,   329,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,   -76,  -319,   648,  -319,
    -319,     2,   -19,  -319,    22,   -23,  -133,  -123,   293,   405,
     -62,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -268,  -318,  -319,   394,  -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   243,   248,   249,     9,    17,    30,    31,
      32,    33,    34,    35,   144,   220,   365,    36,   315,    11,
     238,   138,   114,   115,   116,    16,   117,   118,    23,    21,
     340,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     224,   297,   371,   257,   258,   372
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     139,   225,   226,   227,     4,   145,   139,   139,   206,   207,
     208,   209,   210,   211,   206,   207,   208,   209,   210,   211,
      -2,     4,     4,   320,    12,   279,   200,   142,   143,     4,
     206,   207,   208,   209,   210,   211,   206,   207,   208,   209,
     210,   211,   310,   200,   200,   206,   207,   208,   209,   210,
     211,   206,   207,   208,   209,   210,   211,   206,   207,   208,
     209,   210,   211,   395,   341,   278,   151,   206,   207,   208,
     209,   210,   211,   369,   210,   211,   413,   280,   395,   282,
     283,   284,   285,   139,   216,   314,     3,   222,   223,    18,
     393,    13,   217,   218,   219,    19,   244,   245,   321,   201,
      15,   204,     6,   205,   166,   332,     5,   240,   432,   395,
     362,    14,   334,   326,   215,   311,   331,   360,   214,     6,
       6,     7,   327,   328,     8,   411,   342,     6,   378,   202,
     203,   204,   140,   205,   379,   370,   396,   206,   207,   208,
     209,   210,   211,    20,   380,   206,   207,   208,   209,   210,
     211,   427,   394,   246,   247,   256,   139,   139,   329,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   254,   255,   345,
     346,   347,   436,   147,   148,   351,   352,   239,   139,   139,
     139,   139,   139,   250,   251,   252,   253,   222,   223,   356,
     357,   358,   359,   298,   299,   418,    22,   222,   223,   287,
     288,   289,   290,   291,   420,   222,   223,   316,   317,   277,
     318,   319,   421,   206,   207,   208,   209,   210,   211,   206,
     207,   208,   209,   210,   211,   141,   206,   207,   208,   209,
     210,   211,   149,   150,   414,   202,   203,   204,   152,   205,
     338,   339,   399,   400,   401,   412,   363,   364,   402,   403,
     366,   367,   139,   431,   146,    12,   202,   203,   204,     6,
     205,   202,   203,   204,   153,   205,   202,   203,   204,   154,
     205,   373,   374,   333,   155,   156,   139,   139,   139,   209,
     210,   211,   428,   429,   430,   194,   195,   196,   157,   197,
     422,    12,   195,   196,   158,   197,   423,   348,   349,   350,
     437,   438,   439,   424,   159,   202,   203,   204,   196,   205,
     197,   419,   160,    24,    25,   161,    26,   162,    27,   163,
      28,   164,   353,    29,   165,   206,   207,   208,   209,   210,
     211,   169,   440,   167,   168,   171,     6,   441,   213,   198,
     170,   221,   442,   199,   172,   198,    12,   173,   174,   199,
     175,   176,   281,   256,   139,   139,   139,   139,   139,   139,
     198,   177,   295,   286,   199,   207,   208,   209,   210,   211,
     202,   203,   204,   375,   205,   404,   405,   406,   407,   408,
     409,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   212,
     292,   293,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   294,
     296,   102,   206,   207,   208,   209,   210,   211,   300,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   301,
     302,     6,   303,   312,   113,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   304,   197,   206,   207,   208,   209,
     210,   211,   305,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   313,   197,   202,   203,
     204,   376,   205,   306,   307,   308,   361,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   309,   197,   202,
     203,   204,   377,   205,   322,   198,   323,   324,   325,   199,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     335,   336,   241,   242,   337,   343,   344,   198,   368,   383,
     425,   199,   202,   203,   204,   381,   205,   202,   203,   204,
     382,   205,   202,   203,   204,   384,   205,   388,   198,   354,
     389,   390,   199,   202,   203,   204,   385,   205,   202,   203,
     204,   386,   205,   202,   203,   204,   387,   205,   202,   203,
     204,   415,   205,   202,   203,   204,   416,   205,   202,   203,
     204,   417,   205,   202,   203,   204,   433,   205,   202,   203,
     204,   434,   205,   202,   203,   204,   435,   205,   391,   355,
      10,   330,   397,   398,   410,   426,     0,     0,     0,     0,
       0,   392
};

static const yytype_int16 yycheck[] =
{
      19,   152,   153,   154,     1,    28,    25,    26,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       0,     1,     1,     7,     2,   199,     7,    25,    26,     1,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,     7,     7,     7,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,     3,     4,     5,
       6,     7,     8,     7,    17,   198,    44,     3,     4,     5,
       6,     7,     8,   341,     7,     8,   394,   200,     7,   202,
     203,   204,   205,   102,   111,    82,     0,    32,    33,    79,
      17,    77,   119,   120,   121,    85,    15,    16,    82,    80,
      99,     6,    99,     8,   102,    84,    86,    80,   426,     7,
      82,    79,   286,    80,   109,    80,    80,    80,   107,    99,
      99,   101,    80,   256,   104,   393,    79,    99,    80,     4,
       5,     6,    80,     8,    80,    80,    80,     3,     4,     5,
       6,     7,     8,    97,    80,     3,     4,     5,     6,     7,
       8,    80,    79,    72,    73,    79,   175,   176,    82,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   175,   176,   302,
     303,   304,    80,    72,    73,   308,   309,   165,   207,   208,
     209,   210,   211,   171,   172,   173,   174,    32,    33,   322,
     323,   324,   325,   226,   227,    80,    97,    32,    33,   207,
     208,   209,   210,   211,    80,    32,    33,    72,    73,   197,
      72,    73,    80,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,    77,     3,     4,     5,     6,
       7,     8,    72,    73,   395,     4,     5,     6,    79,     8,
      97,    98,   375,   376,   377,    80,   117,   118,   381,   382,
     336,   337,   281,    80,   114,   243,     4,     5,     6,    99,
       8,     4,     5,     6,    79,     8,     4,     5,     6,    79,
       8,   343,   344,   281,    79,    79,   305,   306,   307,     6,
       7,     8,   415,   416,   417,    25,    26,    27,    79,    29,
      80,   279,    26,    27,    79,    29,    80,   305,   306,   307,
     433,   434,   435,    80,    79,     4,     5,     6,    27,     8,
      29,    80,    79,   105,   106,    79,   108,    79,   110,    79,
     112,    79,   310,   115,    79,     3,     4,     5,     6,     7,
       8,    81,    80,    79,    79,    79,    99,    80,    77,    79,
      81,   113,    80,    83,    79,    79,   334,    79,    79,    83,
      79,    79,    85,    79,   383,   384,   385,   386,   387,   388,
      79,    81,     7,    81,    83,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,   383,   384,   385,   386,   387,
     388,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    77,
     122,   122,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   122,
      99,    79,     3,     4,     5,     6,     7,     8,    80,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    80,
       7,    99,     7,    80,   102,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,     7,    29,     3,     4,     5,     6,
       7,     8,     7,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    80,    29,     4,     5,
       6,     7,     8,     7,     7,     7,    77,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     7,    29,     4,
       5,     6,     7,     8,     7,    79,     7,     7,     7,    83,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     123,   123,   167,   168,   123,     7,     7,    79,     7,    79,
      77,    83,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,   103,    79,    29,
     123,   123,    83,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,   123,   320,
       2,   257,    80,    80,    80,    79,    -1,    -1,    -1,    -1,
      -1,   368
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   125,   126,     0,     1,    86,    99,   101,   104,   130,
     142,   143,   148,    77,    79,    99,   149,   131,    79,    85,
      97,   153,    97,   152,   105,   106,   108,   110,   112,   115,
     132,   133,   134,   135,   136,   137,   141,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   102,   146,   147,   148,   150,   151,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   145,   146,
      80,    77,   145,   145,   138,   149,   114,    72,    73,    72,
      73,   148,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,   145,    79,    79,    81,
      81,    79,    79,    79,    79,    79,    79,    81,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    29,    79,    83,
       7,    80,     4,     5,     6,     8,     3,     4,     5,     6,
       7,     8,    77,    77,   107,   109,   111,   119,   120,   121,
     139,   113,    32,    33,   174,   179,   179,   179,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   144,   148,
      80,   153,   153,   127,    15,    16,    72,    73,   128,   129,
     148,   148,   148,   148,   145,   145,    79,   177,   178,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   148,   150,   127,
     151,    85,   151,   151,   151,   151,    81,   145,   145,   145,
     145,   145,   122,   122,   122,     7,    99,   175,   149,   149,
      80,    80,     7,     7,     7,     7,     7,     7,     7,     7,
       7,    80,    80,    80,    82,   142,    72,    73,    72,    73,
       7,    82,     7,     7,     7,     7,    80,    80,   150,    82,
     178,    80,    84,   145,   127,   123,   123,   123,    97,    98,
     154,    17,    79,     7,     7,   151,   151,   151,   145,   145,
     145,   151,   151,   148,    29,   129,   151,   151,   151,   151,
      80,    77,    82,   117,   118,   140,   140,   140,     7,   175,
      80,   176,   179,   154,   154,     7,     7,     7,    80,    80,
      80,     7,     7,    79,     7,     7,     7,     7,   103,   123,
     123,   123,   152,    17,    79,     7,    80,    80,    80,   151,
     151,   151,   151,   151,   145,   145,   145,   145,   145,   145,
      80,   175,    80,   176,   179,     7,     7,     7,    80,    80,
      80,    80,    80,    80,    80,    77,    79,    80,   151,   151,
     151,    80,   176,     7,     7,     7,    80,   151,   151,   151,
      80,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   124,   125,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   129,   130,   130,   130,   130,   131,
     131,   132,   132,   132,   132,   132,   132,   133,   133,   134,
     135,   136,   137,   138,   138,   139,   139,   139,   140,   140,
     141,   142,   142,   142,   143,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     148,   149,   150,   150,   151,   151,   151,   151,   151,   152,
     153,   154,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   174,   174,   174,   174,   174,   175,   176,
     176,   177,   177,   178,   179,   179
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
       1,     1,     1,     2,     3,     8,     4,     1,     1,     1,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     8,     8,     8,     8,     4,     4,     8,
       7,     7,     4,     4,    12,    12,    12,     6,     6,     6,
       8,     8,     5,     7,     9,     4,     6,     8,     1,     1,
       3,     1,     2,     6,     1,     1
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
#line 310 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gResult = formatDefinitions((yyval.exp)); }
#line 1771 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 313 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1777 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 314 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1783 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 316 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1789 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 317 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1795 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 324 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1801 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 325 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1807 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 328 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1813 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 329 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1819 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 330 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1825 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 331 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1831 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 332 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1837 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 333 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1843 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 337 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1849 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 338 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = nil; }
#line 1855 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 339 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1861 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1867 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 343 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1873 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 344 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1879 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 347 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1885 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 348 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1891 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 349 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1897 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 350 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1903 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1909 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1915 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 355 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1921 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 356 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1927 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 359 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1933 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 362 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1939 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 365 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1945 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 368 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1951 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 371 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1957 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 372 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1963 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 375 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1969 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 376 "parser/faustparser.y" /* yacc.c:1646  */
    { gStripDocSwitch = (yyvsp[-1].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
#line 1975 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 377 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDistributedSwitch = (yyvsp[-1].b); }
#line 1981 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 380 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 1987 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 381 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 1993 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 384 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1999 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 387 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2005 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 388 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2011 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 389 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2017 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 392 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2023 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 395 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2029 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 396 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2035 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 399 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2041 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 400 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2047 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 401 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2053 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 402 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2059 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 403 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2065 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 404 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2071 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 405 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2077 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 408 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2083 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 409 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2089 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 410 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2095 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2101 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 412 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2107 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 413 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gPowPrim->box()); }
#line 2113 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 414 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2119 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 415 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2125 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 416 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2131 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 418 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2137 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 419 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2143 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2149 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 422 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2155 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 423 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2161 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 425 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2167 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 426 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2173 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 427 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2179 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 428 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2185 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 429 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2191 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2197 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 432 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2203 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 433 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2209 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 435 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2215 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 438 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2221 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 439 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2227 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 441 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2233 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 442 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2239 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 444 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2245 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 445 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2251 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 447 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2257 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 448 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2263 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 450 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2269 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 451 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2275 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 453 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2281 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 454 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2287 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 456 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2293 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 457 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2299 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2305 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 459 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2311 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 460 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2317 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2323 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 463 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2329 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 464 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2335 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 465 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2341 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 467 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2347 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 468 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2353 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 470 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2359 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 471 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2365 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 472 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2371 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 473 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2377 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2383 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 475 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2389 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 477 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2395 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 479 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAcosPrim->box(); }
#line 2401 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 480 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAsinPrim->box(); }
#line 2407 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 481 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtanPrim->box(); }
#line 2413 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 482 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtan2Prim->box(); }
#line 2419 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 483 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCosPrim->box(); }
#line 2425 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSinPrim->box(); }
#line 2431 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gTanPrim->box(); }
#line 2437 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 487 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gExpPrim->box(); }
#line 2443 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 488 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLogPrim->box(); }
#line 2449 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 489 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLog10Prim->box(); }
#line 2455 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2461 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 491 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2467 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSqrtPrim->box(); }
#line 2473 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAbsPrim->box(); }
#line 2479 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMinPrim->box(); }
#line 2485 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 496 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMaxPrim->box(); }
#line 2491 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 498 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFmodPrim->box(); }
#line 2497 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRemainderPrim->box(); }
#line 2503 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 501 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFloorPrim->box(); }
#line 2509 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 502 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCeilPrim->box(); }
#line 2515 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 503 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRintPrim->box(); }
#line 2521 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2527 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 507 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2533 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 509 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2539 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 510 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2545 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2551 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 513 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2557 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 515 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2563 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 517 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2569 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 519 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2575 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 521 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2581 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 522 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2587 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 523 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2593 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2599 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 525 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2605 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2611 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 527 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gWaveForm); gWaveForm.clear(); }
#line 2617 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 529 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2623 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2629 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 531 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2635 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2641 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 533 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2647 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 534 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2653 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2659 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 536 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2665 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 537 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2671 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 538 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2677 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 540 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2683 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 541 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2689 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 542 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2695 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 543 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2701 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2707 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2713 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 551 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2719 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 554 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2725 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 559 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2731 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 560 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2737 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 563 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2743 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 564 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2749 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 565 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2755 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 566 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2761 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 567 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2767 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 570 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2773 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 573 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2779 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 576 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2785 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 577 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2791 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 583 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2797 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 587 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2803 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 591 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2809 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 595 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2815 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 599 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2821 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 602 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2827 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 610 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2833 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 614 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2839 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 617 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2845 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 621 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2851 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 624 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2857 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 628 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2863 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 631 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2869 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 634 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2875 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 637 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2881 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 640 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2887 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 643 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2893 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 647 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2899 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 650 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2905 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 656 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2911 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 657 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2917 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 658 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2923 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 660 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2929 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 661 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2935 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 662 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2941 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 665 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2947 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 668 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2953 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 669 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2959 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 672 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2965 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 673 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 2971 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 677 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 2977 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 680 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 2983 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 681 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 2989 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 2993 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 684 "parser/faustparser.y" /* yacc.c:1906  */


