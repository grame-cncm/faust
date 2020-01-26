/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "faustparser.y" /* yacc.c:337  */


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


#line 137 "faustparser.cpp" /* yacc.c:337  */
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
    ROUTE = 348,
    ENABLE = 349,
    CONTROL = 350,
    IPAR = 351,
    ISEQ = 352,
    ISUM = 353,
    IPROD = 354,
    INPUTS = 355,
    OUTPUTS = 356,
    STRING = 357,
    FSTRING = 358,
    IDENT = 359,
    EXTRA = 360,
    DECLARE = 361,
    CASE = 362,
    ARROW = 363,
    FLOATMODE = 364,
    DOUBLEMODE = 365,
    QUADMODE = 366,
    BDOC = 367,
    EDOC = 368,
    BEQN = 369,
    EEQN = 370,
    BDGM = 371,
    EDGM = 372,
    BLST = 373,
    ELST = 374,
    BMETADATA = 375,
    EMETADATA = 376,
    DOCCHAR = 377,
    NOTICE = 378,
    LISTING = 379,
    LSTTRUE = 380,
    LSTFALSE = 381,
    LSTDEPENDENCIES = 382,
    LSTMDOCTAGS = 383,
    LSTDISTRIBUTED = 384,
    LSTEQ = 385,
    LSTQ = 386
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 73 "faustparser.y" /* yacc.c:352  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;

#line 320 "faustparser.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   759

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  132
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  483

#define YYUNDEFTOK  2
#define YYMAXUTOK   386

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
     125,   126,   127,   128,   129,   130,   131
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   325,   325,   328,   329,   330,   332,   333,   334,   338,
     339,   346,   347,   350,   351,   352,   353,   354,   355,   359,
     360,   361,   362,   363,   366,   367,   370,   371,   372,   373,
     374,   375,   378,   379,   382,   385,   388,   391,   394,   395,
     398,   399,   400,   403,   404,   407,   410,   411,   412,   415,
     416,   417,   420,   421,   424,   427,   430,   431,   434,   435,
     436,   437,   438,   439,   440,   441,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   454,   455,   456,   458,   459,
     461,   462,   463,   464,   465,   466,   468,   469,   471,   474,
     475,   477,   478,   480,   481,   483,   484,   486,   487,   489,
     490,   492,   493,   494,   495,   496,   497,   499,   500,   501,
     503,   504,   506,   507,   508,   509,   510,   511,   513,   514,
     515,   518,   519,   520,   521,   522,   523,   524,   526,   527,
     528,   529,   530,   531,   533,   534,   535,   537,   538,   540,
     541,   542,   545,   546,   548,   549,   551,   552,   554,   555,
     558,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     580,   581,   582,   583,   585,   586,   591,   594,   599,   600,
     603,   604,   605,   606,   607,   610,   613,   616,   617,   622,
     626,   630,   634,   639,   642,   649,   653,   656,   661,   664,
     667,   670,   673,   676,   679,   682,   686,   689,   692,   699,
     700,   701,   703,   704,   705,   708,   711,   712,   715,   716,
     719,   723,   724
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
  "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS",
  "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "FLOATMODE", "DOUBLEMODE", "QUADMODE", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "reclist", "vallist", "number", "statement",
  "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "variant",
  "definition", "recinition", "defname", "recname", "params", "expression",
  "infixexp", "primitive", "ident", "name", "arglist", "argument",
  "string", "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod",
  "finputs", "foutputs", "ffunction", "fconst", "fvariable", "button",
  "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
  "vbargraph", "hbargraph", "soundfile", "signature", "fun", "typelist",
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386
};
# endif

#define YYPACT_NINF -401

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-401)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -401,    67,    22,  -401,   -23,    16,  -401,    47,  -401,  -401,
    -401,  -401,  -401,    17,  -401,    15,  -401,  -401,    55,  -401,
      93,   263,  -401,   412,   412,  -401,    82,  -401,   167,    25,
    -401,   412,   412,  -401,    47,  -401,  -401,    91,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,   114,
     -17,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,   147,   193,   196,   217,   264,
     268,   270,   289,   292,   294,   297,   299,   303,   304,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,   307,  -401,  -401,   412,
     308,   309,   315,   316,   321,  -401,  -401,   328,   329,   330,
     339,   360,   361,   408,   539,  -401,  -401,     1,   398,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,   517,
     539,   413,   439,  -401,    35,     8,   228,   427,  -401,  -401,
    -401,  -401,  -401,  -401,   175,   175,   175,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,   466,    56,
      55,    55,  -401,   278,   412,   466,   466,   466,   466,   412,
     412,   490,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
    -401,   466,   412,  -401,   412,   500,   412,   412,   412,   412,
     511,   512,   412,   412,   412,   412,   412,  -401,  -401,  -401,
    -401,  -401,  -401,   472,   479,   481,  -401,  -401,  -401,  -401,
     610,   515,    47,    47,   540,   541,   613,   627,   629,   630,
     632,   633,   634,   647,   648,    45,  -401,  -401,   602,   603,
       5,   215,   242,  -401,  -401,    11,  -401,   584,   678,   680,
     681,   682,    66,    73,   412,   -33,  -401,   558,   558,   558,
     558,   558,   558,   606,   606,   606,   126,   126,   126,   126,
     126,   126,   126,   487,   269,  -401,    76,    26,   398,   412,
     398,   398,   205,  -401,  -401,  -401,   592,   592,    92,   310,
    -401,   608,   609,   611,   235,  -401,    32,   729,   730,  -401,
    -401,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     466,   711,  -401,  -401,  -401,  -401,  -401,  -401,  -401,   278,
    -401,   412,   412,   412,   412,   412,  -401,  -401,   110,  -401,
    -401,  -401,  -401,    20,  -401,   524,   106,    24,   214,   214,
     214,  -401,  -401,   735,   515,    21,   235,   235,   599,   607,
     654,   231,   238,   245,   659,   664,    40,  -401,   663,  -401,
     669,   674,   687,   692,   697,   637,  -401,  -401,  -401,   667,
     466,  -401,  -401,   660,  -401,  -401,   617,   618,   619,   167,
      68,  -401,   111,  -401,   670,   671,   412,   412,   412,  -401,
    -401,  -401,   412,   412,  -401,   412,   412,   412,   412,   412,
     412,   412,  -401,  -401,   412,  -401,  -401,  -401,   672,   515,
     109,   175,  -401,  -401,  -401,   702,   707,   712,    85,   305,
     252,   259,   276,   300,   358,   491,   531,   538,  -401,   675,
    -401,   112,  -401,   412,   412,   412,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,   254,  -401,   717,   722,
     727,  -401,   136,   412,   412,   412,  -401,   319,   324,   337,
    -401,  -401,  -401
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   176,     0,    46,    47,
      48,    24,     5,     0,    22,     0,    54,    51,     0,   177,
       0,    32,     4,     0,     0,   186,     0,   185,     0,     0,
      23,     0,     0,    38,     0,    36,    25,    26,    27,    28,
      29,    30,    31,   112,   113,   116,   114,   115,   117,   101,
     102,   108,   103,   104,   105,   107,   109,   110,   111,   131,
     106,    97,    98,    99,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,    89,    90,     0,    95,    96,     0,
       0,     0,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,   184,    88,   146,     0,   178,   170,
     171,   172,   173,   174,   175,   151,   152,   153,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,     0,
      65,     0,     0,    20,     0,     0,     0,     0,    33,    91,
      92,    93,    94,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    19,    21,
      34,    35,    37,     0,     0,     0,    39,    45,   221,   222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,   148,     0,     0,
       0,     0,     0,    13,    14,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   218,    80,    81,    84,
      82,    83,    85,    66,    67,    76,    68,    69,    70,    75,
      77,    78,    79,    71,    72,    74,     0,     0,   179,     0,
     181,   182,   180,   183,     6,     9,    62,    63,    61,    60,
      64,     0,     0,     0,     0,   215,     0,     0,     0,   198,
     199,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   155,   156,    15,    16,    17,    18,     0,
     157,     0,     0,     0,     0,     0,   193,   194,     0,   150,
     219,    86,    87,     0,     8,     0,     0,     0,     0,     0,
       0,   187,   188,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,     0,    12,
       0,     0,     0,     0,     0,     0,     7,    49,    58,     0,
       0,    59,    10,     0,    43,    44,     0,     0,     0,     0,
       0,   212,     0,   216,     0,     0,     0,     0,     0,   203,
     204,   205,     0,     0,   208,     0,     0,     0,     0,     0,
       0,     0,    53,    55,     0,    40,    41,    42,     0,     0,
       0,     0,   209,   196,   197,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   195,     0,
     213,     0,   217,     0,     0,     0,   207,   206,   149,   158,
     189,   190,   191,   192,   220,    52,     0,   210,     0,     0,
       0,   214,     0,     0,     0,     0,   211,     0,     0,     0,
     200,   201,   202
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -401,  -401,   569,   451,  -401,  -401,   418,   745,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,     0,  -401,   -70,
     -21,  -401,  -401,  -401,  -401,    -3,   -24,  -401,    18,   -10,
    -186,  -182,   -27,   477,     2,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,  -401,
    -401,  -401,  -401,  -401,  -401,  -401,  -331,  -400,  -401,   484,
    -161
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   297,   357,   265,   266,    12,    21,    36,
      37,    38,    39,    40,    41,   156,   236,   396,    42,    13,
      14,   392,    15,   393,   255,   149,   124,   125,   126,    20,
     127,   128,    29,    26,   363,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   240,   316,   402,   275,   276,
     403
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     150,   152,   267,   241,   242,   243,     4,   150,   150,   214,
      28,   220,   221,   222,   223,   224,   225,   226,     4,   339,
      16,     4,    -2,     4,   157,   389,   296,     4,   154,   155,
     451,    16,   298,   400,   300,   301,   302,   303,   220,   221,
     222,   223,   224,   225,   226,   216,   217,   218,   274,   219,
     364,   349,   390,   330,   238,   239,    17,   161,   162,   220,
     221,   222,   223,   224,   225,   226,   472,     3,   163,   220,
     221,   222,   223,   224,   225,   226,   220,   221,   222,   223,
     224,   225,   226,   215,   214,   150,   429,     6,   348,   334,
     216,   217,   218,     5,   219,   340,    23,    18,   449,   224,
     225,   226,    24,   401,   153,     5,   179,     4,   391,     6,
       5,     7,   352,   365,     8,     9,    10,    11,   214,   431,
     431,     6,   414,     7,     6,   231,     6,   331,     7,    11,
       6,     8,     9,    10,    11,     8,     9,    10,   257,   368,
     369,   370,   238,   239,   431,   374,   375,   376,   346,   430,
     230,    19,   208,   209,   210,   347,   211,    25,   351,   380,
     381,   382,   383,   384,   151,   150,   150,   456,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   272,   273,   159,   160,
     388,   450,   385,   432,   467,    27,   256,    19,   150,   150,
     150,   150,   150,   268,   269,   270,   271,   212,   238,   239,
       6,   213,   218,   158,   219,     8,     9,    10,   476,   306,
     307,   308,   309,   310,   435,   436,   437,   353,   164,   295,
     438,   439,   317,   318,   220,   221,   222,   223,   224,   225,
     226,   220,   221,   222,   223,   224,   225,   226,   220,   221,
     222,   223,   224,   225,   226,   220,   221,   222,   223,   224,
     225,   226,   220,   221,   222,   223,   224,   225,   226,    27,
     452,   468,   469,   470,   165,   150,   354,   166,    16,   220,
     221,   222,   223,   224,   225,   226,   353,   238,   239,   335,
     336,   477,   478,   479,   261,   262,   355,   210,   167,   211,
     150,   150,   150,   220,   221,   222,   223,   224,   225,   226,
     216,   217,   218,   409,   219,    16,   337,   338,   225,   226,
     410,   371,   372,   373,   216,   217,   218,   411,   219,   216,
     217,   218,   386,   219,   458,   354,   471,   361,   362,   394,
     395,   459,   216,   217,   218,   168,   219,   232,   377,   169,
     212,   170,   263,   264,   213,   233,   234,   235,   460,   397,
     398,   220,   221,   222,   223,   224,   225,   226,   404,   405,
     171,    16,   428,   172,    16,   173,    30,    31,   174,    32,
     175,    33,   461,    34,   176,   177,    35,   457,   178,   180,
     181,   150,   150,   150,   150,   150,   150,   150,   182,   183,
     150,   480,   184,   216,   217,   218,   481,   219,   423,   185,
     186,   187,   440,   441,   442,   443,   444,   445,   446,   482,
     188,   447,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     462,   189,   190,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   191,   228,   109,   220,   221,   222,   223,   224,   225,
     226,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   209,   210,     6,   211,   229,   123,
     220,   221,   222,   223,   224,   225,   226,   220,   221,   222,
     223,   224,   225,   226,   220,   221,   222,   223,   224,   225,
     226,   220,   221,   222,   223,   224,   225,   226,   237,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   212,   211,
       6,   274,   213,   463,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   299,   211,   216,
     217,   218,   341,   219,   304,   305,   227,   222,   223,   224,
     225,   226,   311,   387,   216,   217,   218,   406,   219,   312,
     464,   313,   216,   217,   218,   407,   219,   465,   314,   315,
     212,   321,   319,   320,   213,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   322,   211,   323,   324,   212,
     325,   326,   327,   213,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   328,   329,   258,   259,   216,
     217,   218,   408,   219,   216,   217,   218,   412,   219,   216,
     217,   218,   413,   219,   216,   217,   218,   416,   219,   216,
     217,   218,   417,   219,   332,   333,   342,   212,   343,   344,
     345,   213,   216,   217,   218,   418,   219,   216,   217,   218,
     419,   219,   216,   217,   218,   420,   219,   216,   217,   218,
     453,   219,   216,   217,   218,   454,   219,   216,   217,   218,
     455,   219,   216,   217,   218,   473,   219,   216,   217,   218,
     474,   219,   216,   217,   218,   475,   219,   366,   367,   358,
     359,   378,   360,   399,   415,   421,   422,   424,   425,   426,
     427,   260,   433,   434,   448,   356,   466,   379,    22,   350
};

static const yytype_uint16 yycheck[] =
{
      24,    28,   184,   164,   165,   166,     1,    31,    32,     8,
      20,     3,     4,     5,     6,     7,     8,     9,     1,     8,
       2,     1,     0,     1,    34,     1,   212,     1,    31,    32,
     430,    13,   214,   364,   216,   217,   218,   219,     3,     4,
       5,     6,     7,     8,     9,     5,     6,     7,    81,     9,
      18,    84,    28,     8,    33,    34,    79,    74,    75,     3,
       4,     5,     6,     7,     8,     9,   466,     0,    50,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,    82,     8,   109,    18,   104,   274,    84,
       5,     6,     7,    88,     9,    84,    81,    81,   429,     7,
       8,     9,    87,    82,    79,    88,   109,     1,    84,   104,
      88,   106,    86,    81,   109,   110,   111,   112,     8,     8,
       8,   104,    82,   106,   104,   117,   104,    82,   106,   112,
     104,   109,   110,   111,   112,   109,   110,   111,    82,   321,
     322,   323,    33,    34,     8,   327,   328,   329,    82,    81,
     115,   104,    26,    27,    28,    82,    30,   102,    82,   341,
     342,   343,   344,   345,    82,   189,   190,    82,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   189,   190,    74,    75,
      84,    82,    82,    82,    82,   102,   178,   104,   222,   223,
     224,   225,   226,   185,   186,   187,   188,    81,    33,    34,
     104,    85,     7,   122,     9,   109,   110,   111,    82,   222,
     223,   224,   225,   226,   406,   407,   408,   297,    81,   211,
     412,   413,   242,   243,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,   102,
     431,   453,   454,   455,    81,   299,   297,    81,   260,     3,
       4,     5,     6,     7,     8,     9,   356,    33,    34,    74,
      75,   473,   474,   475,    16,    17,   299,    28,    81,    30,
     324,   325,   326,     3,     4,     5,     6,     7,     8,     9,
       5,     6,     7,    82,     9,   297,    74,    75,     8,     9,
      82,   324,   325,   326,     5,     6,     7,    82,     9,     5,
       6,     7,   353,     9,    82,   356,    82,   102,   103,   125,
     126,    82,     5,     6,     7,    81,     9,   119,   330,    81,
      81,    81,    74,    75,    85,   127,   128,   129,    82,   359,
     360,     3,     4,     5,     6,     7,     8,     9,   366,   367,
      81,   353,   399,    81,   356,    81,   113,   114,    81,   116,
      81,   118,    82,   120,    81,    81,   123,    82,    81,    81,
      81,   415,   416,   417,   418,   419,   420,   421,    83,    83,
     424,    82,    81,     5,     6,     7,    82,     9,   390,    81,
      81,    81,   415,   416,   417,   418,   419,   420,   421,    82,
      81,   424,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      82,    81,    81,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    83,    79,    81,     3,     4,     5,     6,     7,     8,
       9,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,    27,    28,   104,    30,    79,   107,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,   121,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    81,    30,
     104,    81,    85,    82,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    87,    30,     5,
       6,     7,     8,     9,    83,    83,    79,     5,     6,     7,
       8,     9,   130,    79,     5,     6,     7,     8,     9,   130,
      79,   130,     5,     6,     7,     8,     9,    79,     8,   104,
      81,     8,    82,    82,    85,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     8,    30,     8,     8,    81,
       8,     8,     8,    85,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,     8,     8,   180,   181,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     5,
       6,     7,     8,     9,    82,    82,     8,    81,     8,     8,
       8,    85,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     8,     8,   131,
     131,    30,   131,     8,    81,   108,    79,    87,   131,   131,
     131,   182,    82,    82,    82,   304,    81,   339,    13,   275
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   133,   134,     0,     1,    88,   104,   106,   109,   110,
     111,   112,   139,   151,   152,   154,   160,    79,    81,   104,
     161,   140,   139,    81,    87,   102,   165,   102,   161,   164,
     113,   114,   116,   118,   120,   123,   141,   142,   143,   144,
     145,   146,   150,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    81,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   107,   158,   159,   160,   162,   163,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   157,
     158,    82,   164,    79,   157,   157,   147,   161,   122,    74,
      75,    74,    75,   160,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,   157,
      81,    81,    83,    83,    81,    81,    81,    81,    81,    81,
      81,    83,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    30,    81,    85,     8,    82,     5,     6,     7,     9,
       3,     4,     5,     6,     7,     8,     9,    79,    79,    79,
     115,   117,   119,   127,   128,   129,   148,   121,    33,    34,
     187,   192,   192,   192,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   156,   160,    82,   165,   165,
     134,    16,    17,    74,    75,   137,   138,   163,   160,   160,
     160,   160,   157,   157,    81,   190,   191,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   160,   162,   135,   163,    87,
     163,   163,   163,   163,    83,    83,   157,   157,   157,   157,
     157,   130,   130,   130,     8,   104,   188,   161,   161,    82,
      82,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,    82,    82,    82,    84,    74,    75,    74,    75,     8,
      84,     8,     8,     8,     8,     8,    82,    82,   162,    84,
     191,    82,    86,   151,   152,   157,   135,   136,   131,   131,
     131,   102,   103,   166,    18,    81,     8,     8,   163,   163,
     163,   157,   157,   157,   163,   163,   163,   160,    30,   138,
     163,   163,   163,   163,   163,    82,   152,    79,    84,     1,
      28,    84,   153,   155,   125,   126,   149,   149,   149,     8,
     188,    82,   189,   192,   166,   166,     8,     8,     8,    82,
      82,    82,     8,     8,    82,    81,     8,     8,     8,     8,
       8,   108,    79,   160,    87,   131,   131,   131,   164,    18,
      81,     8,    82,    82,    82,   163,   163,   163,   163,   163,
     157,   157,   157,   157,   157,   157,   157,   157,    82,   188,
      82,   189,   192,     8,     8,     8,    82,    82,    82,    82,
      82,    82,    82,    82,    79,    79,    81,    82,   163,   163,
     163,    82,   189,     8,     8,     8,    82,   163,   163,   163,
      82,    82,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   132,   133,   134,   134,   134,   135,   135,   135,   136,
     136,   137,   137,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   139,   139,   140,   140,   141,   141,   141,   141,
     141,   141,   142,   142,   143,   144,   145,   146,   147,   147,
     148,   148,   148,   149,   149,   150,   151,   151,   151,   152,
     152,   152,   153,   153,   154,   155,   156,   156,   157,   157,
     157,   157,   157,   157,   157,   157,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   160,   161,   162,   162,
     163,   163,   163,   163,   163,   164,   165,   166,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     187,   187,   187,   187,   187,   188,   189,   189,   190,   190,
     191,   192,   192
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     2,     0,     3,     2,     0,
       2,     1,     3,     1,     1,     2,     2,     2,     2,     5,
       4,     5,     1,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     0,     2,     3,     3,     1,     3,     0,     2,
       5,     5,     5,     1,     1,     3,     1,     1,     1,     7,
       4,     2,     4,     2,     1,     2,     1,     3,     5,     5,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     4,     1,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     8,
       4,     1,     1,     1,     4,     4,     4,     4,     8,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     8,
       8,     8,     8,     4,     4,     8,     7,     7,     4,     4,
      12,    12,    12,     6,     6,     6,     8,     8,     6,     5,
       7,     9,     4,     6,     8,     1,     1,     3,     1,     2,
       6,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
        case 2:
#line 325 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1824 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 328 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1830 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 329 "faustparser.y" /* yacc.c:1652  */
    { if ((yyvsp[-1].numvariant)==gGlobal->gFloatSize) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1836 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 330 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1842 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 332 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1848 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 333 "faustparser.y" /* yacc.c:1652  */
    { if ((yyvsp[-1].numvariant)==gGlobal->gFloatSize) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1854 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 334 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1860 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 338 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1866 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 339 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1872 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 346 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1878 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 347 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1884 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 350 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1890 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 351 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1896 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 352 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1902 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 353 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1908 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 354 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1914 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 355 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1920 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 359 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1926 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 360 "faustparser.y" /* yacc.c:1652  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1932 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 361 "faustparser.y" /* yacc.c:1652  */
    { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1938 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 362 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1944 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 363 "faustparser.y" /* yacc.c:1652  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1950 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 366 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1956 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 367 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1962 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 370 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1968 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 371 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1974 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 372 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1980 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 373 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docNtc(); }
#line 1986 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 374 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docLst(); }
#line 1992 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 375 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1998 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 378 "faustparser.y" /* yacc.c:1652  */
    { (yyval.cppstr) = new string(); }
#line 2004 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 379 "faustparser.y" /* yacc.c:1652  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 2010 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 382 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2016 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 385 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2022 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 388 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2028 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 391 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2034 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 394 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2040 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 395 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2046 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 398 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2052 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 399 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2058 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 400 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2064 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 403 "faustparser.y" /* yacc.c:1652  */
    { (yyval.b) = true; }
#line 2070 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 404 "faustparser.y" /* yacc.c:1652  */
    { (yyval.b) = false; }
#line 2076 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 407 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2082 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 410 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 1;}
#line 2088 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 411 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 2;}
#line 2094 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 412 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 3;}
#line 2100 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 415 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2106 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 416 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2112 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 417 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2118 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 420 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2124 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 421 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2130 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 424 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2136 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 427 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2142 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 430 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2148 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 431 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2154 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 434 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2160 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 435 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2166 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 436 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2172 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 437 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2178 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 438 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2184 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 439 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2190 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 440 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2196 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 441 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2202 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 444 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2208 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 445 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2214 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 446 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2220 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 447 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2226 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 448 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2232 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 449 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2238 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 450 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2244 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 451 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2250 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 452 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2256 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 454 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2262 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 455 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2268 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 456 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2274 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 458 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2280 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 459 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2286 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 461 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2292 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 462 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2298 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 463 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2304 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 464 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2310 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 465 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2316 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 466 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2322 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 468 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2328 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 469 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2334 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 471 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2340 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 474 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2346 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 475 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2352 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 477 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2358 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 478 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2364 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 480 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2370 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 481 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2376 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 483 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWire(); }
#line 2382 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 484 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCut(); }
#line 2388 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 486 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2394 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 487 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2400 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 489 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2406 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 490 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2412 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 492 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2418 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 493 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2424 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 494 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2430 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 495 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2436 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 496 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2442 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 497 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2448 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 499 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2454 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 500 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2460 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 501 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2466 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 503 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2472 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 504 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2478 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 506 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2484 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 507 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2490 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 508 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2496 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 509 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2502 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 510 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2508 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 511 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2514 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 513 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2520 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 514 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2526 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 120:
#line 515 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2532 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 121:
#line 518 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2538 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 122:
#line 519 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2544 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 123:
#line 520 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2550 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 124:
#line 521 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2556 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 125:
#line 522 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2562 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 126:
#line 523 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2568 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 127:
#line 524 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2574 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 128:
#line 526 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2580 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 129:
#line 527 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2586 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 130:
#line 528 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2592 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 131:
#line 529 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2598 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 132:
#line 530 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2604 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 133:
#line 531 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2610 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 134:
#line 533 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2616 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 135:
#line 534 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2622 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 136:
#line 535 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2628 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 137:
#line 537 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2634 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 138:
#line 538 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2640 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 139:
#line 540 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2646 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 140:
#line 541 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2652 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 141:
#line 542 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2658 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 142:
#line 545 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2664 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 143:
#line 546 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2670 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 144:
#line 548 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2676 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 145:
#line 549 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2682 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 146:
#line 551 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2688 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 147:
#line 552 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2694 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 148:
#line 554 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2700 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 149:
#line 556 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2706 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 150:
#line 558 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2712 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 151:
#line 560 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2718 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 152:
#line 561 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2724 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 153:
#line 562 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2730 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 154:
#line 563 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2736 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 155:
#line 564 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2742 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 156:
#line 565 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2748 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 157:
#line 566 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2754 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 158:
#line 567 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2760 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 159:
#line 568 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2766 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 160:
#line 569 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2772 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 161:
#line 570 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2778 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 162:
#line 571 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2784 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 163:
#line 572 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2790 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 164:
#line 573 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2796 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 165:
#line 574 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2802 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 166:
#line 575 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2808 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 167:
#line 576 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2814 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 168:
#line 577 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2820 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 169:
#line 578 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2826 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 170:
#line 580 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2832 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 171:
#line 581 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2838 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 172:
#line 582 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2844 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 173:
#line 583 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2850 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 174:
#line 585 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2856 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 175:
#line 586 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2862 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 176:
#line 591 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2868 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 177:
#line 594 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2874 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 178:
#line 599 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2880 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 179:
#line 600 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2886 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 180:
#line 603 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2892 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 181:
#line 604 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2898 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 182:
#line 605 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2904 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 183:
#line 606 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2910 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 184:
#line 607 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2916 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 185:
#line 610 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2922 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 186:
#line 613 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = unquote(yytext); }
#line 2928 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 187:
#line 616 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2934 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 188:
#line 617 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2940 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 189:
#line 623 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2946 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 190:
#line 627 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2952 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 191:
#line 631 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2958 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 192:
#line 635 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2964 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 193:
#line 639 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2970 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 194:
#line 642 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2976 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 195:
#line 650 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2982 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 196:
#line 654 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2988 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 197:
#line 657 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2994 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 198:
#line 661 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3000 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 199:
#line 664 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3006 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 200:
#line 668 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3012 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 201:
#line 671 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3018 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 202:
#line 674 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3024 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 203:
#line 677 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3030 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 204:
#line 680 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3036 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 205:
#line 683 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3042 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 206:
#line 687 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3048 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 207:
#line 690 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3054 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 208:
#line 693 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3060 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 209:
#line 699 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3066 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 210:
#line 700 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3072 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 211:
#line 701 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3078 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 212:
#line 703 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3084 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 213:
#line 704 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3090 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 214:
#line 705 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3096 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 215:
#line 708 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 3102 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 216:
#line 711 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3108 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 217:
#line 712 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3114 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 218:
#line 715 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3120 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 219:
#line 716 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3126 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 220:
#line 720 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3132 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 221:
#line 723 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(0); }
#line 3138 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 222:
#line 724 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(1); }
#line 3144 "faustparser.cpp" /* yacc.c:1652  */
    break;


#line 3148 "faustparser.cpp" /* yacc.c:1652  */
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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 727 "faustparser.y" /* yacc.c:1918  */


