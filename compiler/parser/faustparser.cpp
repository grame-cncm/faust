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
    ENABLE = 347,
    CONTROL = 348,
    IPAR = 349,
    ISEQ = 350,
    ISUM = 351,
    IPROD = 352,
    INPUTS = 353,
    OUTPUTS = 354,
    STRING = 355,
    FSTRING = 356,
    IDENT = 357,
    EXTRA = 358,
    DECLARE = 359,
    CASE = 360,
    ARROW = 361,
    BDOC = 362,
    EDOC = 363,
    BEQN = 364,
    EEQN = 365,
    BDGM = 366,
    EDGM = 367,
    BLST = 368,
    ELST = 369,
    BMETADATA = 370,
    EMETADATA = 371,
    DOCCHAR = 372,
    NOTICE = 373,
    LISTING = 374,
    LSTTRUE = 375,
    LSTFALSE = 376,
    LSTDEPENDENCIES = 377,
    LSTMDOCTAGS = 378,
    LSTDISTRIBUTED = 379,
    LSTEQ = 380,
    LSTQ = 381
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

#line 312 "parser/faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 329 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYLAST   695

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  458

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

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
     125,   126
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   320,   321,   323,   324,   328,   329,   336,
     337,   340,   341,   342,   343,   344,   345,   349,   350,   351,
     352,   355,   356,   359,   360,   361,   362,   363,   364,   367,
     368,   371,   374,   377,   380,   383,   384,   387,   388,   389,
     392,   393,   396,   399,   400,   401,   404,   405,   408,   411,
     414,   415,   418,   419,   420,   421,   422,   423,   424,   425,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   438,
     439,   440,   442,   443,   445,   446,   447,   448,   449,   450,
     452,   453,   455,   458,   459,   461,   462,   464,   465,   467,
     468,   470,   471,   473,   474,   476,   477,   478,   479,   480,
     481,   483,   484,   485,   487,   488,   490,   491,   492,   493,
     494,   495,   497,   498,   499,   502,   503,   504,   505,   506,
     507,   508,   510,   511,   512,   513,   514,   515,   517,   518,
     519,   521,   522,   524,   525,   526,   529,   530,   532,   533,
     535,   536,   538,   539,   542,   544,   545,   546,   547,   548,
     549,   550,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   563,   564,   565,   566,   568,   569,   574,   577,
     582,   583,   586,   587,   588,   589,   590,   593,   596,   599,
     600,   605,   609,   613,   617,   622,   625,   632,   636,   639,
     644,   647,   650,   653,   656,   659,   662,   665,   669,   672,
     679,   680,   681,   683,   684,   685,   688,   691,   692,   695,
     696,   699,   703,   704
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
  "VBARGRAPH", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN",
  "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS", "MIN", "MAX",
  "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL",
  "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT", "ENDDEF",
  "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC", "DEF",
  "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "ENABLE",
  "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS",
  "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW",
  "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST",
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
  "tgroup", "vbargraph", "hbargraph", "signature", "fun", "typelist",
  "rulelist", "rule", "type", YY_NULLPTR
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
     375,   376,   377,   378,   379,   380,   381
};
# endif

#define YYPACT_NINF -313

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-313)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -313,    82,    29,  -313,    12,    35,  -313,    -8,  -313,  -313,
    -313,   121,  -313,  -313,    -2,  -313,    27,   475,   394,   394,
    -313,    49,  -313,   122,  -313,   394,   394,  -313,    -8,  -313,
    -313,    87,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,   -28,   129,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,    55,
     138,   159,   181,   190,   205,   216,   220,   249,   256,   265,
     270,   279,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,   280,
    -313,  -313,   394,   282,   283,   241,   286,  -313,  -313,   284,
     290,   291,   292,   293,   301,   303,   505,  -313,  -313,     8,
     335,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
     311,   505,   142,  -313,    15,     5,   211,   215,  -313,  -313,
    -313,  -313,  -313,  -313,    69,    69,    69,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,   281,    31,    -2,
      -2,  -313,   194,   281,   281,   281,   281,   394,   394,   306,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,  -313,   281,
     394,  -313,   394,   302,   394,   394,   394,   394,   305,   308,
     394,   394,   394,   394,   394,  -313,  -313,  -313,  -313,  -313,
     266,   269,   276,  -313,  -313,  -313,  -313,   385,   320,    -8,
      -8,   321,   342,   416,   464,   465,   486,   487,   489,   490,
     506,    18,  -313,  -313,   453,   455,     4,   115,   135,  -313,
    -313,    24,  -313,   554,   566,   570,   571,    45,    53,   394,
     -17,  -313,   521,   521,   521,   521,   521,   521,   533,   533,
     533,   300,   300,   300,   300,   300,   300,   300,   271,   259,
    -313,    33,    16,   335,   394,   335,   335,   212,  -313,  -313,
    -313,   589,   589,   140,   219,  -313,   454,   461,   466,   153,
    -313,    25,   573,   583,  -313,  -313,   394,   394,   394,   394,
     394,   394,   394,   394,   281,   569,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,   194,  -313,   394,   394,   394,   394,  -313,
    -313,    39,  -313,  -313,  -313,  -313,  -313,   472,    30,    14,
     201,   201,   201,  -313,  -313,   592,   320,    76,   153,   153,
     601,   613,   618,    65,    72,   136,   623,   628,  -313,   522,
    -313,   633,   638,   643,   648,   498,  -313,  -313,   525,   281,
    -313,  -313,   526,  -313,  -313,   485,   488,   562,    27,    75,
    -313,    47,  -313,   534,   535,   394,   394,   394,  -313,  -313,
    -313,   394,   394,   394,   394,   394,   394,   394,   394,  -313,
    -313,   394,  -313,  -313,  -313,   608,   320,   207,    69,  -313,
    -313,  -313,   653,   658,   663,    79,   145,   178,   229,   243,
     268,   275,   497,   504,  -313,   610,  -313,    56,  -313,   394,
     394,   394,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,   273,  -313,   668,   673,   678,  -313,    57,   394,   394,
     394,  -313,   251,   257,   288,  -313,  -313,  -313
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   168,     0,    21,     4,
      19,     0,    48,    45,     0,   169,     0,    29,     0,     0,
     178,     0,   177,     0,    20,     0,     0,    35,     0,    33,
      22,    23,    24,    25,    26,    27,    28,   106,   107,   110,
     108,   109,   111,    95,    96,   102,    97,    98,    99,   101,
     103,   104,   105,   125,   100,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,    83,    84,     0,
      89,    90,     0,     0,     0,     0,     0,   113,   114,     0,
       0,     0,     0,     0,     0,     0,   176,    82,   140,     0,
     170,   162,   163,   164,   165,   166,   167,   145,   146,   147,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
       0,    59,     0,    18,     0,     0,     0,     0,    30,    85,
      86,    87,    88,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    17,    31,    32,    34,
       0,     0,     0,    36,    42,   212,   213,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,   142,     0,     0,     0,     0,     0,    11,
      12,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,   209,    74,    75,    78,    76,    77,    79,    60,    61,
      70,    62,    63,    64,    69,    71,    72,    73,    65,    66,
      68,     0,     0,   171,     0,   173,   174,   172,   175,     5,
       7,    56,    57,    55,    54,    58,     0,     0,     0,     0,
     206,     0,     0,     0,   190,   191,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,    13,
      14,    15,    16,     0,   151,     0,     0,     0,     0,   185,
     186,     0,   144,   210,    80,    81,     6,     0,     0,     0,
       0,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
      10,     0,     0,     0,     0,     0,    43,    52,     0,     0,
      53,     8,     0,    40,    41,     0,     0,     0,     0,     0,
     203,     0,   207,     0,     0,     0,     0,     0,   195,   196,
     197,     0,     0,     0,     0,     0,     0,     0,     0,    47,
      49,     0,    37,    38,    39,     0,     0,     0,     0,   200,
     188,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   187,     0,   204,     0,   208,     0,
       0,     0,   199,   198,   143,   181,   182,   183,   184,   211,
      46,     0,   201,     0,     0,     0,   205,     0,     0,     0,
       0,   202,     0,     0,     0,   192,   193,   194
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -313,  -313,   520,   403,  -313,  -313,   370,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,    11,  -313,  -238,
    -313,  -313,  -313,  -313,     2,   -19,  -313,    23,   -24,  -167,
     -83,   316,   407,     9,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -250,  -312,  -313,   435,  -153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   282,   339,   251,   252,     9,    17,    30,
      31,    32,    33,    34,    35,   146,   223,   375,    36,    10,
     371,    11,   372,   241,   140,   116,   117,   118,    16,   119,
     120,    23,    21,   345,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   227,   301,   381,   260,   261,   382
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     141,   228,   229,   230,   147,     4,   141,   141,   208,   209,
     210,   211,   212,   213,   214,   368,   202,     4,   208,   209,
     210,   211,   212,   213,   214,    12,   314,   144,   145,    -2,
       4,     4,   323,   281,   208,   209,   210,   211,   212,   213,
     214,   202,   369,   346,   336,   149,   150,   202,   208,   209,
     210,   211,   212,   213,   214,   408,   208,   209,   210,   211,
     212,   213,   214,   259,   408,   408,   332,   153,   208,   209,
     210,   211,   212,   213,   214,   208,   209,   210,   211,   212,
     213,   214,     3,   141,   204,   205,   206,   318,   207,   203,
      13,     5,   331,   406,    15,   427,   379,   370,    20,   315,
     336,   335,   225,   226,   168,   347,     6,   324,     7,   225,
     226,     8,   243,   367,   334,    14,     5,   218,     6,   283,
     365,   285,   286,   287,   288,   217,   329,    22,   409,   447,
     142,     6,     6,     7,   330,   154,     8,   442,   451,   208,
     209,   210,   211,   212,   213,   214,   388,   212,   213,   214,
     204,   205,   206,   389,   207,   407,   425,   380,   141,   141,
     432,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   257,
     258,   208,   209,   210,   211,   212,   213,   214,   319,   320,
     242,   141,   141,   141,   141,   141,   253,   254,   255,   256,
     143,    18,   151,   152,   148,   302,   303,    19,   321,   322,
     247,   248,   291,   292,   293,   294,   295,   390,   155,   206,
     216,   207,   280,   350,   351,   352,   433,   213,   214,   356,
     357,     6,   208,   209,   210,   211,   212,   213,   214,   156,
     225,   226,   361,   362,   363,   364,   208,   209,   210,   211,
     212,   213,   214,   343,   344,   428,   204,   205,   206,   434,
     207,   157,   204,   205,   206,   141,   207,   249,   250,    12,
     158,   208,   209,   210,   211,   212,   213,   214,   208,   209,
     210,   211,   212,   213,   214,   159,   337,   198,   426,   199,
     141,   141,   141,   204,   205,   206,   160,   207,   197,   198,
     161,   199,   412,   413,   414,    12,   225,   226,   415,   416,
     435,   353,   354,   355,   208,   209,   210,   211,   212,   213,
     214,   373,   374,   171,   436,   219,   196,   197,   198,   162,
     199,   224,   455,   220,   221,   222,   163,   358,   456,   200,
     204,   205,   206,   201,   207,   164,   443,   444,   445,   437,
     165,   200,   376,   377,   446,   201,   438,   383,   384,   166,
     167,    12,   169,   170,   173,   452,   453,   454,   172,   457,
     174,   175,   176,   177,   141,   141,   141,   141,   141,   141,
     200,   178,   141,     6,   201,   179,   259,   289,   284,   215,
     290,   296,   400,   299,   297,   417,   418,   419,   420,   421,
     422,   298,   304,   423,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   300,   305,   306,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   307,   308,   102,   208,   209,   210,   211,   212,
     213,   214,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   309,   310,     6,   311,   312,   115,
     208,   209,   210,   211,   212,   213,   214,   208,   209,   210,
     211,   212,   213,   214,   313,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   316,   199,   317,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     366,   199,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   325,   199,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   326,   439,   244,   245,   327,   328,
     340,   348,   440,    24,    25,   200,    26,   341,    27,   201,
      28,   349,   342,    29,   210,   211,   212,   213,   214,   359,
     378,   200,   393,   399,   398,   201,   204,   205,   206,   385,
     207,   402,   401,   200,   403,   410,   411,   201,   204,   205,
     206,   386,   207,   204,   205,   206,   387,   207,   204,   205,
     206,   391,   207,   204,   205,   206,   392,   207,   204,   205,
     206,   394,   207,   204,   205,   206,   395,   207,   204,   205,
     206,   396,   207,   204,   205,   206,   397,   207,   204,   205,
     206,   429,   207,   204,   205,   206,   430,   207,   204,   205,
     206,   431,   207,   204,   205,   206,   448,   207,   204,   205,
     206,   449,   207,   204,   205,   206,   450,   207,   404,   424,
     441,   246,   338,   360,   405,   333
};

static const yytype_uint16 yycheck[] =
{
      19,   154,   155,   156,    28,     1,    25,    26,     3,     4,
       5,     6,     7,     8,     9,     1,     8,     1,     3,     4,
       5,     6,     7,     8,     9,     2,     8,    25,    26,     0,
       1,     1,     8,   200,     3,     4,     5,     6,     7,     8,
       9,     8,    28,    18,   282,    73,    74,     8,     3,     4,
       5,     6,     7,     8,     9,     8,     3,     4,     5,     6,
       7,     8,     9,    80,     8,     8,    83,    44,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     0,   102,     5,     6,     7,    83,     9,    81,
      78,    87,   259,    18,   102,   407,   346,    83,   100,    81,
     338,    85,    33,    34,   102,    80,   102,    83,   104,    33,
      34,   107,    81,    83,    81,    80,    87,   112,   102,   202,
      81,   204,   205,   206,   207,   110,    81,   100,    81,   441,
      81,   102,   102,   104,    81,    80,   107,    81,    81,     3,
       4,     5,     6,     7,     8,     9,    81,     7,     8,     9,
       5,     6,     7,    81,     9,    80,   406,    81,   177,   178,
      81,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   177,
     178,     3,     4,     5,     6,     7,     8,     9,    73,    74,
     167,   210,   211,   212,   213,   214,   173,   174,   175,   176,
      78,    80,    73,    74,   117,   229,   230,    86,    73,    74,
      16,    17,   210,   211,   212,   213,   214,    81,    80,     7,
      78,     9,   199,   306,   307,   308,    81,     8,     9,   312,
     313,   102,     3,     4,     5,     6,     7,     8,     9,    80,
      33,    34,   325,   326,   327,   328,     3,     4,     5,     6,
       7,     8,     9,   100,   101,   408,     5,     6,     7,    81,
       9,    80,     5,     6,     7,   284,     9,    73,    74,   246,
      80,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,    80,   284,    28,    81,    30,
     309,   310,   311,     5,     6,     7,    80,     9,    27,    28,
      80,    30,   385,   386,   387,   282,    33,    34,   391,   392,
      81,   309,   310,   311,     3,     4,     5,     6,     7,     8,
       9,   120,   121,    82,    81,   114,    26,    27,    28,    80,
      30,   116,    81,   122,   123,   124,    80,   314,    81,    80,
       5,     6,     7,    84,     9,    80,   429,   430,   431,    81,
      80,    80,   341,   342,    81,    84,    81,   348,   349,    80,
      80,   338,    80,    80,    80,   448,   449,   450,    82,    81,
      80,    80,    80,    80,   393,   394,   395,   396,   397,   398,
      80,    80,   401,   102,    84,    82,    80,    82,    86,    78,
      82,   125,   369,     8,   125,   393,   394,   395,   396,   397,
     398,   125,    81,   401,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   102,    81,     8,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,     8,     8,    80,     3,     4,     5,     6,     7,
       8,     9,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,     8,     8,   102,     8,     8,   105,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    81,    30,    81,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      78,    30,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     8,    30,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     8,    78,   169,   170,     8,     8,
     126,     8,    78,   108,   109,    80,   111,   126,   113,    84,
     115,     8,   126,   118,     5,     6,     7,     8,     9,    30,
       8,    80,    80,    78,   106,    84,     5,     6,     7,     8,
       9,   126,    86,    80,   126,    81,    81,    84,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,   126,    81,
      80,   171,   289,   323,   378,   260
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   128,   129,     0,     1,    87,   102,   104,   107,   134,
     146,   148,   154,    78,    80,   102,   155,   135,    80,    86,
     100,   159,   100,   158,   108,   109,   111,   113,   115,   118,
     136,   137,   138,   139,   140,   141,   145,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    80,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   105,   152,   153,   154,   156,
     157,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     151,   152,    81,    78,   151,   151,   142,   155,   117,    73,
      74,    73,    74,   154,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,   151,    80,
      80,    82,    82,    80,    80,    80,    80,    80,    80,    82,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    30,
      80,    84,     8,    81,     5,     6,     7,     9,     3,     4,
       5,     6,     7,     8,     9,    78,    78,   110,   112,   114,
     122,   123,   124,   143,   116,    33,    34,   180,   185,   185,
     185,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   150,   154,    81,   159,   159,   129,    16,    17,    73,
      74,   132,   133,   154,   154,   154,   154,   151,   151,    80,
     183,   184,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     154,   156,   130,   157,    86,   157,   157,   157,   157,    82,
      82,   151,   151,   151,   151,   151,   125,   125,   125,     8,
     102,   181,   155,   155,    81,    81,     8,     8,     8,     8,
       8,     8,     8,     8,     8,    81,    81,    81,    83,    73,
      74,    73,    74,     8,    83,     8,     8,     8,     8,    81,
      81,   156,    83,   184,    81,    85,   146,   151,   130,   131,
     126,   126,   126,   100,   101,   160,    18,    80,     8,     8,
     157,   157,   157,   151,   151,   151,   157,   157,   154,    30,
     133,   157,   157,   157,   157,    81,    78,    83,     1,    28,
      83,   147,   149,   120,   121,   144,   144,   144,     8,   181,
      81,   182,   185,   160,   160,     8,     8,     8,    81,    81,
      81,     8,     8,    80,     8,     8,     8,     8,   106,    78,
     154,    86,   126,   126,   126,   158,    18,    80,     8,    81,
      81,    81,   157,   157,   157,   157,   157,   151,   151,   151,
     151,   151,   151,   151,    81,   181,    81,   182,   185,     8,
       8,     8,    81,    81,    81,    81,    81,    81,    81,    78,
      78,    80,    81,   157,   157,   157,    81,   182,     8,     8,
       8,    81,   157,   157,   157,    81,    81,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   127,   128,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   135,   135,   136,   136,   136,   136,   136,   136,   137,
     137,   138,   139,   140,   141,   142,   142,   143,   143,   143,
     144,   144,   145,   146,   146,   146,   147,   147,   148,   149,
     150,   150,   151,   151,   151,   151,   151,   151,   151,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   153,   153,   153,   153,   153,   153,
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
       0,     2,     1,     0,     2,     0,     2,     0,     2,     1,
       3,     1,     1,     2,     2,     2,     2,     5,     4,     1,
       3,     0,     2,     1,     1,     1,     1,     1,     1,     0,
       2,     3,     3,     1,     3,     0,     2,     5,     5,     5,
       1,     1,     3,     7,     4,     2,     4,     2,     1,     2,
       1,     3,     5,     5,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     4,     1,     1,     1,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
#line 317 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gResult = formatDefinitions((yyval.exp)); }
#line 1790 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 320 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1796 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 321 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1802 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 323 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1808 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 324 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1814 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 328 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1820 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 329 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1826 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 336 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1832 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 337 "parser/faustparser.y" /* yacc.c:1646  */
    { gWaveForm.push_back((yyvsp[0].exp)); }
#line 1838 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1844 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 341 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1850 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 342 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1856 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 343 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1862 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 344 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1868 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 345 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1874 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 349 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1880 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 350 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = nil; }
#line 1886 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1892 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1898 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 355 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; }
#line 1904 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 356 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1910 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 359 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1916 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 360 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1922 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 361 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1928 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 362 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1934 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 363 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1940 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 364 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1946 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 367 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1952 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 368 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1958 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 371 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1964 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 374 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1970 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 377 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1976 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 380 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1982 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 383 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1988 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 384 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1994 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 387 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2000 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 388 "parser/faustparser.y" /* yacc.c:1646  */
    { gStripDocSwitch = (yyvsp[-1].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
#line 2006 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 389 "parser/faustparser.y" /* yacc.c:1646  */
    { gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2012 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 392 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 2018 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 393 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 2024 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 396 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2030 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 399 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2036 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 400 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2042 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 401 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2048 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 404 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(nil,(yyvsp[-1].exp))); }
#line 2054 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 405 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = nil; yyerr++; }
#line 2060 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 408 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2066 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2072 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 414 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2078 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 415 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2084 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 418 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2090 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 419 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2096 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2102 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 421 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2108 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 422 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2114 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 423 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2120 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 424 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2126 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 425 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2132 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 428 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2138 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 429 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2144 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2150 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 431 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2156 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 432 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2162 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 433 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gPowPrim->box()); }
#line 2168 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 434 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2174 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 435 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2180 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 436 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2186 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 438 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2192 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 439 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2198 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 440 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2204 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 442 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2210 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 443 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2216 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 445 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2222 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 446 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2228 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 447 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2234 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 448 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2240 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 449 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2246 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 450 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2252 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 452 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2258 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 453 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2264 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 455 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2270 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2276 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 459 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2282 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2288 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 462 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2294 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 464 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2300 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 465 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2306 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 467 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2312 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 468 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2318 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 470 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2324 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 471 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2330 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 473 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2336 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2342 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 476 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2348 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 477 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2354 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 478 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2360 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 479 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2366 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 480 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2372 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 481 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2378 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 483 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2384 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2390 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2396 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 487 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2402 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 488 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2408 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2414 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 491 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2420 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2426 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 493 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2432 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2438 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2444 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 497 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2450 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 498 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2456 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2462 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 502 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAcosPrim->box(); }
#line 2468 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 503 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAsinPrim->box(); }
#line 2474 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 504 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtanPrim->box(); }
#line 2480 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 505 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAtan2Prim->box(); }
#line 2486 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCosPrim->box(); }
#line 2492 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 507 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSinPrim->box(); }
#line 2498 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 508 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gTanPrim->box(); }
#line 2504 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 510 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gExpPrim->box(); }
#line 2510 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 511 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLogPrim->box(); }
#line 2516 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gLog10Prim->box(); }
#line 2522 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 513 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2528 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 514 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gPowPrim->box(); }
#line 2534 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 515 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gSqrtPrim->box(); }
#line 2540 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 517 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gAbsPrim->box(); }
#line 2546 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 518 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMinPrim->box(); }
#line 2552 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 519 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gMaxPrim->box(); }
#line 2558 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 521 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFmodPrim->box(); }
#line 2564 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 522 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRemainderPrim->box(); }
#line 2570 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gFloorPrim->box(); }
#line 2576 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 525 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gCeilPrim->box(); }
#line 2582 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gRintPrim->box(); }
#line 2588 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 529 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2594 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2600 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2606 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 533 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2612 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2618 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 536 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2624 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 538 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2630 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 540 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2636 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 542 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2642 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 544 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2648 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2654 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2660 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 547 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2666 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 548 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2672 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 549 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2678 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 550 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gWaveForm); gWaveForm.clear(); }
#line 2684 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 552 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2690 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 553 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2696 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 554 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2702 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 555 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2708 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 556 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2714 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 557 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2720 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 558 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2726 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 559 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2732 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 560 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2738 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 561 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2744 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 563 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2750 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 564 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2756 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 565 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2762 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 566 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2768 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 568 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2774 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 569 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2780 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 574 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2786 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 577 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2792 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 582 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 2798 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 583 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2804 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 586 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2810 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 587 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2816 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 588 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2822 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 589 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2828 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 590 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2834 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 593 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2840 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 596 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2846 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 599 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2852 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 600 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2858 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 606 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2864 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 610 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2870 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 614 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2876 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 618 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2882 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 622 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2888 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 625 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2894 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 633 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2900 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 637 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2906 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 640 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2912 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 644 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2918 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 647 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2924 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 651 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2930 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 654 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2936 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 657 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2942 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 660 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2948 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 663 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2954 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 666 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2960 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 670 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2966 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 673 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2972 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 679 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2978 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 680 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2984 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 681 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),nil))), (yyvsp[-1].exp))); }
#line 2990 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 683 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 2996 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 684 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 3002 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 685 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),nil))), nil)); }
#line 3008 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 688 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 3014 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 691 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 3020 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 692 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3026 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 695 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),nil); }
#line 3032 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 696 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3038 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 700 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3044 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 703 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 3050 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 704 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 3056 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3060 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 707 "parser/faustparser.y" /* yacc.c:1906  */


