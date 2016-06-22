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


#line 131 "parser/faustparser.cpp" /* yacc.c:339  */

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
#line 71 "parser/faustparser.y" /* yacc.c:355  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 303 "parser/faustparser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 320 "parser/faustparser.cpp" /* yacc.c:358  */

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
#define YYLAST   693

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  125
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  211
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  456

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
       0,   308,   308,   311,   312,   314,   315,   319,   320,   327,
     328,   331,   332,   333,   334,   335,   336,   340,   341,   342,
     343,   346,   347,   350,   351,   352,   353,   354,   355,   358,
     359,   362,   365,   368,   371,   374,   375,   378,   379,   380,
     383,   384,   387,   390,   391,   392,   395,   396,   399,   402,
     405,   406,   409,   410,   411,   412,   413,   414,   415,   416,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   429,
     430,   431,   433,   434,   436,   437,   438,   439,   440,   441,
     443,   444,   446,   449,   450,   452,   453,   455,   456,   458,
     459,   461,   462,   464,   465,   467,   468,   469,   470,   471,
     472,   474,   475,   476,   478,   479,   481,   482,   483,   484,
     485,   486,   488,   490,   491,   492,   493,   494,   495,   496,
     498,   499,   500,   501,   502,   503,   505,   506,   507,   509,
     510,   512,   513,   514,   517,   518,   520,   521,   523,   524,
     526,   527,   530,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     550,   551,   552,   553,   555,   556,   561,   564,   569,   570,
     573,   574,   575,   576,   577,   580,   583,   586,   587,   592,
     596,   600,   604,   609,   612,   619,   623,   626,   631,   634,
     637,   640,   643,   646,   649,   652,   656,   659,   666,   667,
     668,   670,   671,   672,   675,   678,   679,   682,   683,   686,
     690,   691
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
  "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "IPAR",
  "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING",
  "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "reclist", "vallist", "number", "statement",
  "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "definition",
  "recinition", "defname", "recname", "params", "expression", "infixexp",
  "primitive", "ident", "name", "arglist", "argument", "string",
  "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod", "finputs",
  "foutputs", "ffunction", "fconst", "fvariable", "button", "checkbox",
  "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
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
     375,   376,   377,   378,   379
};
# endif

#define YYPACT_NINF -321

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-321)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -321,     4,    16,  -321,   -13,    37,  -321,   161,  -321,  -321,
    -321,   120,  -321,  -321,    54,  -321,   188,   457,   392,   392,
    -321,   214,  -321,   219,  -321,   392,   392,  -321,   161,  -321,
    -321,    20,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,    58,   270,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   234,
     238,   240,   252,   256,   262,   267,   277,   312,   340,   341,
     342,   390,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   391,
    -321,  -321,   392,   410,   411,   226,   230,   413,   414,   430,
     450,   462,   464,   243,   501,  -321,  -321,    39,   142,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,    35,   501,
     467,  -321,    26,     5,   228,   231,  -321,  -321,  -321,  -321,
    -321,  -321,    76,    76,    76,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,   255,    45,    54,    54,  -321,
     170,   255,   255,   255,   255,   392,   392,   466,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,  -321,   255,   392,  -321,
     392,   461,   392,   392,   392,   392,   477,   478,   392,   392,
     392,   392,   392,  -321,  -321,  -321,  -321,  -321,   442,   444,
     446,  -321,  -321,  -321,  -321,   564,   474,   161,   161,   494,
     495,   569,   571,   572,   574,   575,   576,   583,   584,    74,
    -321,  -321,   514,   515,    25,   254,   278,  -321,  -321,    28,
    -321,   586,   660,   661,   662,    52,    65,   392,    22,  -321,
      70,    70,    70,    70,    70,    70,   513,   513,   513,   274,
     274,   274,   274,   274,   274,   274,   303,   257,  -321,    77,
      14,   142,   392,   142,   142,   298,  -321,  -321,  -321,   355,
     355,   358,   370,  -321,   547,   548,   549,   283,  -321,    27,
     666,   667,  -321,  -321,   392,   392,   392,   392,   392,   392,
     392,   392,   255,   646,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,   170,  -321,   392,   392,   392,   392,  -321,  -321,   137,
    -321,  -321,  -321,  -321,  -321,   470,    36,    18,   266,   266,
     266,  -321,  -321,   669,   474,   288,   283,   283,   581,   593,
     598,    72,   176,   218,   603,   608,  -321,   599,  -321,   613,
     618,   623,   628,   577,  -321,  -321,   600,   255,  -321,  -321,
     594,  -321,  -321,   558,   559,   560,   188,   119,  -321,   201,
    -321,   604,   605,   392,   392,   392,  -321,  -321,  -321,   392,
     392,   392,   392,   392,   392,   392,   392,  -321,  -321,   392,
    -321,  -321,  -321,   606,   474,   290,    76,  -321,  -321,  -321,
     633,   638,   643,    57,   210,   225,   232,   245,   265,   272,
     493,   500,  -321,   609,  -321,   248,  -321,   392,   392,   392,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   305,
    -321,   648,   653,   658,  -321,   275,   392,   392,   392,  -321,
     253,   287,   310,  -321,  -321,  -321
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   166,     0,    21,     4,
      19,     0,    48,    45,     0,   167,     0,    29,     0,     0,
     176,     0,   175,     0,    20,     0,     0,    35,     0,    33,
      22,    23,    24,    25,    26,    27,    28,   106,   107,   110,
     108,   109,   111,    95,    96,   102,    97,    98,    99,   101,
     103,   104,   105,   123,   100,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,    83,    84,     0,
      89,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,    82,   138,     0,   168,   160,
     161,   162,   163,   164,   165,   143,   144,   145,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,     0,    59,
       0,    18,     0,     0,     0,     0,    30,    85,    86,    87,
      88,   139,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    17,    31,    32,    34,     0,     0,
       0,    36,    42,   210,   211,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,   140,     0,     0,     0,     0,     0,    11,    12,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,   207,
      74,    75,    78,    76,    77,    79,    60,    61,    70,    62,
      63,    64,    69,    71,    72,    73,    65,    66,    68,     0,
       0,   169,     0,   171,   172,   170,   173,     5,     7,    56,
      57,    55,    54,    58,     0,     0,     0,     0,   204,     0,
       0,     0,   188,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,   147,   148,    13,    14,    15,
      16,     0,   149,     0,     0,     0,     0,   183,   184,     0,
     142,   208,    80,    81,     6,     0,     0,     0,     0,     0,
       0,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,    10,     0,
       0,     0,     0,     0,    43,    52,     0,     0,    53,     8,
       0,    40,    41,     0,     0,     0,     0,     0,   201,     0,
     205,     0,     0,     0,     0,     0,   193,   194,   195,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    49,     0,
      37,    38,    39,     0,     0,     0,     0,   198,   186,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   185,     0,   202,     0,   206,     0,     0,     0,
     197,   196,   141,   179,   180,   181,   182,   209,    46,     0,
     199,     0,     0,     0,   203,     0,     0,     0,     0,   200,
       0,     0,     0,   190,   191,   192
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -321,  -321,   519,   403,  -321,  -321,   371,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,    49,  -321,   -38,
    -321,  -321,  -321,  -321,     2,   -19,  -321,    23,   -23,   -59,
    -182,   315,   394,    53,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -320,  -299,  -321,   435,  -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   280,   337,   249,   250,     9,    17,    30,
      31,    32,    33,    34,    35,   144,   221,   373,    36,    10,
     369,    11,   370,   239,   138,   114,   115,   116,    16,   117,
     118,    23,    21,   343,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   225,   299,   379,   258,   259,   380
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     139,   226,   227,   228,     3,   145,   139,   139,   206,   207,
     208,   209,   210,   211,   212,     4,    -2,     4,   281,   366,
     283,   284,   285,   286,   377,    12,     4,   142,   143,   206,
     207,   208,   209,   210,   211,   212,   321,     4,   206,   207,
     208,   209,   210,   211,   212,   344,   367,   200,   206,   207,
     208,   209,   210,   211,   212,   206,   207,   208,   209,   210,
     211,   212,   202,   203,   204,    13,   205,   151,   206,   207,
     208,   209,   210,   211,   212,   206,   207,   208,   209,   210,
     211,   212,   312,   139,   423,   200,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   333,
     197,   368,   257,     5,   166,   330,   425,   345,   316,   223,
     224,   322,     5,   213,     6,   216,     6,    14,     7,   365,
     201,     8,   348,   349,   350,     6,   241,     7,   354,   355,
       8,   147,   148,   327,   215,   146,     6,   404,   430,   279,
     445,   359,   360,   361,   362,   200,   328,   202,   203,   204,
     198,   205,    20,   386,   199,   313,   139,   139,   332,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   255,   256,   206,
     207,   208,   209,   210,   211,   212,   245,   246,   240,   139,
     139,   139,   139,   139,   251,   252,   253,   254,   329,   405,
      18,   410,   411,   412,   300,   301,    19,   413,   414,   406,
     289,   290,   291,   292,   293,   202,   203,   204,   363,   205,
     278,   206,   207,   208,   209,   210,   211,   212,   206,   207,
     208,   209,   210,   211,   212,   206,   207,   208,   209,   210,
     211,   212,   334,   247,   248,   441,   442,   443,   206,   207,
     208,   209,   210,   211,   212,   426,   406,   387,   202,   203,
     204,    15,   205,   139,   450,   451,   452,    12,   206,   207,
     208,   209,   210,   211,   212,   206,   207,   208,   209,   210,
     211,   212,   407,   406,   335,   196,    22,   197,   139,   139,
     139,   431,   202,   203,   204,   140,   205,   141,   334,   388,
     194,   195,   196,    12,   197,   204,   432,   205,   169,   351,
     352,   353,   170,   433,   152,   202,   203,   204,   153,   205,
     154,   223,   224,   223,   224,   177,   434,   317,   318,   440,
     195,   196,   155,   197,   453,   356,   156,   198,   223,   224,
     217,   199,   157,   149,   150,   222,   435,   158,   218,   219,
     220,   319,   320,   436,   198,     6,   449,   159,   199,    12,
     208,   209,   210,   211,   212,   210,   211,   212,   454,   378,
       6,   424,   139,   139,   139,   139,   139,   139,   211,   212,
     139,   341,   342,   198,   371,   372,   444,   199,   374,   375,
     398,   455,   160,   415,   416,   417,   418,   419,   420,   381,
     382,   421,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     161,   162,   163,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     164,   165,   102,   206,   207,   208,   209,   210,   211,   212,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     167,   168,     6,   171,   172,   113,   206,   207,   208,   209,
     210,   211,   212,   206,   207,   208,   209,   210,   211,   212,
     173,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     174,   197,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   175,   197,   176,   214,   257,   282,   364,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   287,
     288,   242,   243,    24,    25,   294,    26,   295,    27,   296,
      28,   437,   297,    29,   298,   302,   303,   304,   438,   305,
     306,   198,   307,   308,   309,   199,   202,   203,   204,   383,
     205,   310,   311,   198,   323,   314,   315,   199,   202,   203,
     204,   384,   205,   202,   203,   204,   385,   205,   202,   203,
     204,   389,   205,   202,   203,   204,   390,   205,   202,   203,
     204,   392,   205,   202,   203,   204,   393,   205,   202,   203,
     204,   394,   205,   202,   203,   204,   395,   205,   202,   203,
     204,   427,   205,   202,   203,   204,   428,   205,   202,   203,
     204,   429,   205,   202,   203,   204,   446,   205,   202,   203,
     204,   447,   205,   202,   203,   204,   448,   205,   324,   325,
     326,   338,   339,   340,   346,   347,   357,   376,   397,   391,
     399,   396,   400,   401,   402,   408,   409,   422,   244,   439,
     336,   403,   358,   331
};

static const yytype_uint16 yycheck[] =
{
      19,   152,   153,   154,     0,    28,    25,    26,     3,     4,
       5,     6,     7,     8,     9,     1,     0,     1,   200,     1,
     202,   203,   204,   205,   344,     2,     1,    25,    26,     3,
       4,     5,     6,     7,     8,     9,     8,     1,     3,     4,
       5,     6,     7,     8,     9,    18,    28,     8,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     5,     6,     7,    78,     9,    44,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     8,   102,   404,     8,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    85,
      30,    83,    80,    87,   102,    83,   405,    80,    83,    33,
      34,    83,    87,    78,   100,   110,   100,    80,   102,    83,
      81,   105,   304,   305,   306,   100,    81,   102,   310,   311,
     105,    73,    74,    81,   108,   115,   100,    18,    81,   198,
     439,   323,   324,   325,   326,     8,    81,     5,     6,     7,
      80,     9,    98,    81,    84,    81,   175,   176,    81,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   175,   176,     3,
       4,     5,     6,     7,     8,     9,    16,    17,   165,   208,
     209,   210,   211,   212,   171,   172,   173,   174,   257,    80,
      80,   383,   384,   385,   227,   228,    86,   389,   390,     8,
     208,   209,   210,   211,   212,     5,     6,     7,    81,     9,
     197,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,   280,    73,    74,   427,   428,   429,     3,     4,
       5,     6,     7,     8,     9,   406,     8,    81,     5,     6,
       7,   100,     9,   282,   446,   447,   448,   244,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,    81,     8,   282,    28,    98,    30,   307,   308,
     309,    81,     5,     6,     7,    81,     9,    78,   336,    81,
      26,    27,    28,   280,    30,     7,    81,     9,    82,   307,
     308,   309,    82,    81,    80,     5,     6,     7,    80,     9,
      80,    33,    34,    33,    34,    82,    81,    73,    74,    81,
      27,    28,    80,    30,    81,   312,    80,    80,    33,    34,
     112,    84,    80,    73,    74,   114,    81,    80,   120,   121,
     122,    73,    74,    81,    80,   100,    81,    80,    84,   336,
       5,     6,     7,     8,     9,     7,     8,     9,    81,    81,
     100,    81,   391,   392,   393,   394,   395,   396,     8,     9,
     399,    98,    99,    80,   118,   119,    81,    84,   339,   340,
     367,    81,    80,   391,   392,   393,   394,   395,   396,   346,
     347,   399,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      80,    80,    80,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      80,    80,    80,     3,     4,     5,     6,     7,     8,     9,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      80,    80,   100,    80,    80,   103,     3,     4,     5,     6,
       7,     8,     9,     3,     4,     5,     6,     7,     8,     9,
      80,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      80,    30,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    80,    30,    80,    78,    80,    86,    78,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,    82,
      82,   167,   168,   106,   107,   123,   109,   123,   111,   123,
     113,    78,     8,   116,   100,    81,    81,     8,    78,     8,
       8,    80,     8,     8,     8,    84,     5,     6,     7,     8,
       9,     8,     8,    80,     8,    81,    81,    84,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     8,     8,
       8,   124,   124,   124,     8,     8,    30,     8,    78,    80,
      86,   104,   124,   124,   124,    81,    81,    81,   169,    80,
     287,   376,   321,   258
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   126,   127,     0,     1,    87,   100,   102,   105,   132,
     144,   146,   152,    78,    80,   100,   153,   133,    80,    86,
      98,   157,    98,   156,   106,   107,   109,   111,   113,   116,
     134,   135,   136,   137,   138,   139,   143,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    80,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   103,   150,   151,   152,   154,   155,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   149,   150,
      81,    78,   149,   149,   140,   153,   115,    73,    74,    73,
      74,   152,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,   149,    80,    80,    82,
      82,    80,    80,    80,    80,    80,    80,    82,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    30,    80,    84,
       8,    81,     5,     6,     7,     9,     3,     4,     5,     6,
       7,     8,     9,    78,    78,   108,   110,   112,   120,   121,
     122,   141,   114,    33,    34,   178,   183,   183,   183,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   148,
     152,    81,   157,   157,   127,    16,    17,    73,    74,   130,
     131,   152,   152,   152,   152,   149,   149,    80,   181,   182,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   152,   154,
     128,   155,    86,   155,   155,   155,   155,    82,    82,   149,
     149,   149,   149,   149,   123,   123,   123,     8,   100,   179,
     153,   153,    81,    81,     8,     8,     8,     8,     8,     8,
       8,     8,     8,    81,    81,    81,    83,    73,    74,    73,
      74,     8,    83,     8,     8,     8,     8,    81,    81,   154,
      83,   182,    81,    85,   144,   149,   128,   129,   124,   124,
     124,    98,    99,   158,    18,    80,     8,     8,   155,   155,
     155,   149,   149,   149,   155,   155,   152,    30,   131,   155,
     155,   155,   155,    81,    78,    83,     1,    28,    83,   145,
     147,   118,   119,   142,   142,   142,     8,   179,    81,   180,
     183,   158,   158,     8,     8,     8,    81,    81,    81,     8,
       8,    80,     8,     8,     8,     8,   104,    78,   152,    86,
     124,   124,   124,   156,    18,    80,     8,    81,    81,    81,
     155,   155,   155,   155,   155,   149,   149,   149,   149,   149,
     149,   149,    81,   179,    81,   180,   183,     8,     8,     8,
      81,    81,    81,    81,    81,    81,    81,    78,    78,    80,
      81,   155,   155,   155,    81,   180,     8,     8,     8,    81,
     155,   155,   155,    81,    81,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   125,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   131,   132,   132,   132,
     132,   133,   133,   134,   134,   134,   134,   134,   134,   135,
     135,   136,   137,   138,   139,   140,   140,   141,   141,   141,
     142,   142,   143,   144,   144,   144,   145,   145,   146,   147,
     148,   148,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   152,   153,   154,   154,
     155,   155,   155,   155,   155,   156,   157,   158,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   178,
     178,   178,   178,   178,   179,   180,   180,   181,   181,   182,
     183,   183
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     8,     4,     1,     1,     1,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     8,
       8,     8,     8,     4,     4,     8,     7,     7,     4,     4,
      12,    12,    12,     6,     6,     6,     8,     8,     5,     7,
       9,     4,     6,     8,     1,     1,     3,     1,     2,     6,
       1,     1
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
#line 308 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1780 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 311 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1786 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 312 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1792 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 314 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1798 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 315 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1804 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 319 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1810 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 320 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1816 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 327 "parser/faustparser.y" /* yacc.c:1646  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1822 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 328 "parser/faustparser.y" /* yacc.c:1646  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1828 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 331 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1834 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 332 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1840 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 333 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1846 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 334 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1852 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 335 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1858 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 336 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1864 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 340 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1870 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 341 "parser/faustparser.y" /* yacc.c:1646  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1876 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 342 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1882 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 343 "parser/faustparser.y" /* yacc.c:1646  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1888 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 346 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; }
#line 1894 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 347 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1900 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 350 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1906 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 351 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1912 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 352 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1918 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 353 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docNtc(); }
#line 1924 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 354 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docLst(); }
#line 1930 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 355 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1936 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 358 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = new string(); }
#line 1942 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 359 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1948 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 362 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1954 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 365 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1960 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 368 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1966 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 371 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1972 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 374 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1978 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 375 "parser/faustparser.y" /* yacc.c:1646  */
    { }
#line 1984 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 378 "parser/faustparser.y" /* yacc.c:1646  */
    { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 1990 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 379 "parser/faustparser.y" /* yacc.c:1646  */
    { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 1996 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 380 "parser/faustparser.y" /* yacc.c:1646  */
    { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2002 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 383 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = true; }
#line 2008 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 384 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.b) = false; }
#line 2014 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 387 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2020 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 390 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); }
#line 2026 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 391 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); }
#line 2032 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 392 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2038 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 395 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); }
#line 2044 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 396 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2050 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 399 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2056 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 402 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); }
#line 2062 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 405 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2068 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 406 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2074 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 409 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2080 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 410 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2086 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 411 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2092 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 412 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2098 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 413 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2104 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 414 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2110 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 415 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2116 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 416 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2122 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 419 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2128 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 420 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2134 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 421 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2140 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 422 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2146 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 423 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2152 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 424 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2158 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 425 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2164 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 426 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2170 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 427 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2176 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 429 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2182 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 430 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2188 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 431 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2194 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 433 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2200 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 434 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2206 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 436 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2212 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 437 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2218 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 438 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2224 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 439 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2230 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 440 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2236 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 441 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2242 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 443 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2248 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 444 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2254 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 446 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2260 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 449 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2266 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 450 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2272 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 452 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2278 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 453 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2284 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 455 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2290 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 456 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2296 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 458 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWire(); }
#line 2302 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 459 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCut(); }
#line 2308 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 461 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2314 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 462 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2320 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 464 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2326 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 465 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2332 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 467 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2338 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 468 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2344 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 469 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2350 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 470 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2356 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 471 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2362 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 472 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2368 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 474 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2374 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 475 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2380 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 476 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2386 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 478 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2392 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 479 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2398 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 481 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2404 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 482 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2410 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 483 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2416 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 484 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2422 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 485 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2428 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 486 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2434 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 488 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2440 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 490 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2446 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 491 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2452 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 492 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2458 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 493 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2464 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 494 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2470 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 495 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2476 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 496 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2482 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 498 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2488 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 499 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2494 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 500 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2500 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 501 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2506 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 502 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2512 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 503 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2518 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 505 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2524 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 506 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2530 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 507 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2536 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 509 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2542 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 510 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2548 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 512 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2554 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 513 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2560 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 514 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2566 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 517 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2572 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 518 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2578 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 520 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2584 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 521 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2590 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 523 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2596 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 524 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2602 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 526 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2608 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 528 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2614 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 530 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2620 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 532 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2626 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 533 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2632 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 534 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2638 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 535 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2644 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 536 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2650 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 537 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2656 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 538 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2662 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 539 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2668 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 540 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2674 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 541 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2680 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 542 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2686 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 543 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2692 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 544 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2698 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 545 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2704 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 546 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2710 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 547 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2716 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 548 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2722 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 550 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2728 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 551 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2734 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 552 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2740 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 553 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2746 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 555 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2752 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 556 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2758 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 561 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIdent(yytext); }
#line 2764 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 564 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2770 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 569 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2776 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 570 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2782 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 573 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2788 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 574 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2794 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 575 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2800 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 576 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2806 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 577 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2812 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 580 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2818 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 583 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = unquote(yytext); }
#line 2824 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 586 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2830 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 587 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2836 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 593 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2842 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 597 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2848 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 601 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2854 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 605 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2860 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 609 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2866 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 612 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2872 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 620 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2878 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 624 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2884 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 627 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2890 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 631 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2896 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 634 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2902 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 638 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2908 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 641 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2914 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 644 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2920 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 647 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2926 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 650 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2932 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 653 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2938 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 657 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2944 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 660 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2950 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 666 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2956 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 667 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2962 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 668 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 2968 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 670 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2974 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 671 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2980 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 672 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 2986 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 675 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(yytext); }
#line 2992 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 678 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2998 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 679 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3004 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 682 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3010 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 683 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3016 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 687 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3022 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 690 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(0); }
#line 3028 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 691 "parser/faustparser.y" /* yacc.c:1646  */
    { (yyval.exp) = tree(1); }
#line 3034 "parser/faustparser.cpp" /* yacc.c:1646  */
    break;


#line 3038 "parser/faustparser.cpp" /* yacc.c:1646  */
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
#line 694 "parser/faustparser.y" /* yacc.c:1906  */


