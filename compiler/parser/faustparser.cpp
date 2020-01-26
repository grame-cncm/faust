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

// A defintion is accepted if the prefixset is empty or if
// the current float precision is member of the prefix set
bool acceptdefinition(int prefixset)
{
	int precisions[] = {0, 1, 2, 4};
	return (prefixset==0) || (prefixset & precisions[gGlobal->gFloatSize]);
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


#line 145 "faustparser.cpp" /* yacc.c:337  */
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
#line 81 "faustparser.y" /* yacc.c:352  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;

#line 328 "faustparser.cpp" /* yacc.c:352  */
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
#define YYLAST   732

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  132
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  482

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
       0,   334,   334,   337,   338,   341,   342,   345,   346,   349,
     350,   351,   355,   356,   363,   364,   367,   368,   369,   370,
     371,   372,   376,   377,   378,   379,   380,   383,   384,   387,
     388,   389,   390,   391,   392,   395,   396,   399,   402,   405,
     408,   411,   412,   415,   416,   417,   420,   421,   424,   427,
     428,   429,   432,   433,   436,   439,   442,   443,   446,   447,
     448,   449,   450,   451,   452,   453,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   466,   467,   468,   470,   471,
     473,   474,   475,   476,   477,   478,   480,   481,   483,   486,
     487,   489,   490,   492,   493,   495,   496,   498,   499,   501,
     502,   504,   505,   506,   507,   508,   509,   511,   512,   513,
     515,   516,   518,   519,   520,   521,   522,   523,   525,   526,
     527,   530,   531,   532,   533,   534,   535,   536,   538,   539,
     540,   541,   542,   543,   545,   546,   547,   549,   550,   552,
     553,   554,   557,   558,   560,   561,   563,   564,   566,   567,
     570,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     592,   593,   594,   595,   597,   598,   603,   606,   611,   612,
     615,   616,   617,   618,   619,   622,   625,   628,   629,   634,
     638,   642,   646,   651,   654,   661,   665,   668,   673,   676,
     679,   682,   685,   688,   691,   694,   698,   701,   704,   711,
     712,   713,   715,   716,   717,   720,   723,   724,   727,   728,
     731,   735,   736
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

#define YYPACT_NINF -329

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-329)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -329,    98,   105,  -329,     8,   -60,    63,  -329,    55,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,    48,  -329,  -329,    11,
    -329,    20,   222,   411,   411,  -329,   132,  -329,   116,   195,
    -329,   411,   411,  -329,    55,  -329,  -329,   168,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,   -48,
      41,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,   233,   237,   249,   256,   270,
     275,   281,   300,   302,   308,   324,   325,   327,   328,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,   329,  -329,  -329,   411,
     337,   338,   223,   228,   359,  -329,  -329,   409,   410,   432,
     433,   435,   436,   243,   524,  -329,  -329,    13,   352,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,   360,
     524,   262,   305,  -329,    36,     9,   225,   320,  -329,  -329,
    -329,  -329,  -329,  -329,    99,    99,    99,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,   429,    45,
      11,    11,  -329,   272,   411,   429,   429,   429,   429,   411,
     411,   472,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
    -329,   429,   411,  -329,   411,   468,   411,   411,   411,   411,
     498,   511,   411,   411,   411,   411,   411,  -329,  -329,  -329,
    -329,  -329,  -329,   469,   470,   471,  -329,  -329,  -329,  -329,
     590,   499,    55,    55,   522,   525,   598,   600,   612,   614,
     615,   616,   623,   624,   626,    15,  -329,  -329,   553,   554,
     619,    80,   153,  -329,  -329,     2,  -329,   370,   696,   697,
     698,   699,    52,    67,   411,    47,  -329,   540,   540,   540,
     540,   540,   540,   552,   552,   552,   289,   289,   289,   289,
     289,   289,   289,   301,    72,  -329,    17,   622,   352,   411,
     352,   352,   129,  -329,  -329,  -329,   395,   395,   290,   260,
    -329,   578,   579,   580,   230,  -329,    69,   704,   705,  -329,
    -329,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     429,   684,  -329,  -329,  -329,  -329,  -329,  -329,  -329,   272,
    -329,   411,   411,   411,   411,   411,  -329,  -329,    61,  -329,
    -329,  -329,  -329,     0,   490,   631,    19,   224,   224,   224,
    -329,  -329,   708,   499,   183,   230,   230,   605,   610,   621,
      74,    85,   185,   633,   638,    25,  -329,   636,  -329,   643,
     648,   653,   658,   663,   611,  -329,  -329,  -329,   639,   429,
    -329,  -329,   634,  -329,  -329,   589,   591,   592,   116,   134,
    -329,    76,  -329,   642,   644,   411,   411,   411,  -329,  -329,
    -329,   411,   411,  -329,   411,   411,   411,   411,   411,   411,
     411,  -329,  -329,   411,  -329,  -329,  -329,   645,   499,   261,
      99,  -329,  -329,  -329,   668,   673,   678,    57,   257,   204,
     231,   238,   245,   252,   273,   516,   523,  -329,   647,  -329,
     113,  -329,   411,   411,   411,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,   291,  -329,   683,   688,   693,
    -329,   115,   411,   411,   411,  -329,   278,   298,   303,  -329,
    -329,  -329
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   176,     0,     9,
      10,    11,    27,     8,     4,    25,     0,    54,    51,     0,
     177,     0,    35,     0,     0,   186,     0,   185,     0,     0,
      26,     0,     0,    41,     0,    39,    28,    29,    30,    31,
      32,    33,    34,   112,   113,   116,   114,   115,   117,   101,
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
      65,     0,     0,    23,     0,     0,     0,     0,    36,    91,
      92,    93,    94,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    22,    24,
      37,    38,    40,     0,     0,     0,    42,    48,   221,   222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,   148,     0,     0,
       7,     0,     0,    16,    17,     0,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   218,    80,    81,    84,
      82,    83,    85,    66,    67,    76,    68,    69,    70,    75,
      77,    78,    79,    71,    72,    74,     0,     7,   179,     0,
     181,   182,   180,   183,     5,    12,    62,    63,    61,    60,
      64,     0,     0,     0,     0,   215,     0,     0,     0,   198,
     199,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   155,   156,    18,    19,    20,    21,     0,
     157,     0,     0,     0,     0,     0,   193,   194,     0,   150,
     219,    86,    87,     0,     0,     7,     0,     0,     0,     0,
     187,   188,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,    15,     0,
       0,     0,     0,     0,     0,     6,    49,    58,     0,     0,
      59,    13,     0,    46,    47,     0,     0,     0,     0,     0,
     212,     0,   216,     0,     0,     0,     0,     0,   203,   204,
     205,     0,     0,   208,     0,     0,     0,     0,     0,     0,
       0,    53,    55,     0,    43,    44,    45,     0,     0,     0,
       0,   209,   196,   197,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   195,     0,   213,
       0,   217,     0,     0,     0,   207,   206,   149,   158,   189,
     190,   191,   192,   220,    52,     0,   210,     0,     0,     0,
     214,     0,     0,     0,     0,   211,     0,     0,     0,   200,
     201,   202
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -329,  -329,   543,   425,  -230,  -329,  -329,  -329,   391,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,    29,
    -329,   378,  -329,  -329,  -329,  -329,    -3,   -24,  -329,    18,
     -10,  -166,  -181,   -26,   416,    32,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -298,  -328,  -329,
     457,  -160
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   297,     4,    13,   356,   265,   266,    14,
      22,    36,    37,    38,    39,    40,    41,   156,   236,   395,
      42,    15,   391,    16,   392,   255,   149,   124,   125,   126,
      21,   127,   128,    29,    26,   362,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   240,   316,   401,   275,
     276,   402
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     150,     5,   152,   267,   241,   242,   243,   150,   150,     5,
     339,    28,   220,   221,   222,   223,   224,   225,   226,    18,
     388,   214,    17,   330,   157,   214,   159,   160,   154,   155,
     216,   217,   218,   298,   219,   300,   301,   302,   303,   220,
     221,   222,   223,   224,   225,   226,   296,   389,   220,   221,
     222,   223,   224,   225,   226,   220,   221,   222,   223,   224,
     225,   226,   216,   217,   218,   399,   219,   353,   163,   214,
     220,   221,   222,   223,   224,   225,   226,   220,   221,   222,
     223,   224,   225,   226,   430,   150,   340,   363,   220,   221,
     222,   223,   224,   225,   226,   215,     6,   331,     3,   351,
     210,   450,   211,   390,     7,    -2,   179,   413,   348,     9,
      10,    11,     7,    25,     8,   161,   162,     9,    10,    11,
      12,   430,    27,   430,    20,   353,   231,   257,   274,    23,
     448,   349,   238,   239,   346,    24,   218,   471,   219,   455,
     367,   368,   369,   384,    19,     7,   373,   374,   375,   347,
     364,   230,   428,   212,   335,   336,   408,   213,   431,    20,
     379,   380,   381,   382,   383,   150,   150,   409,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   272,   273,   220,   221,
     222,   223,   224,   225,   226,   466,   256,   475,   150,   150,
     150,   150,   150,   268,   269,   270,   271,   220,   221,   222,
     223,   224,   225,   226,   151,   429,   238,   239,    27,   306,
     307,   308,   309,   310,   434,   435,   436,   337,   338,   295,
     437,   438,   317,   318,   220,   221,   222,   223,   224,   225,
     226,   220,   221,   222,   223,   224,   225,   226,   220,   221,
     222,   223,   224,   225,   226,   220,   221,   222,   223,   224,
     225,   226,   216,   217,   218,   400,   219,   410,   225,   226,
     451,   467,   468,   469,   153,   150,   220,   221,   222,   223,
     224,   225,   226,   216,   217,   218,   457,   219,   261,   262,
     158,   476,   477,   478,   238,   239,   354,   224,   225,   226,
     150,   150,   150,   216,   217,   218,   182,   219,   216,   217,
     218,   183,   219,   458,   164,   208,   209,   210,   165,   211,
     459,   370,   371,   372,   238,   239,   191,   460,   209,   210,
     166,   211,   360,   361,   461,    30,    31,   167,    32,   456,
      33,   228,    34,   449,   232,    35,   263,   264,   376,   393,
     394,   168,   233,   234,   235,   462,   169,   216,   217,   218,
     479,   219,   170,   220,   221,   222,   223,   224,   225,   226,
     212,    17,   427,   470,   213,   216,   217,   218,   341,   219,
     480,   171,   212,   172,   229,   481,   213,   396,   397,   173,
     150,   150,   150,   150,   150,   150,   150,   403,   404,   150,
     222,   223,   224,   225,   226,   174,   175,   422,   176,   177,
     178,   439,   440,   441,   442,   443,   444,   445,   180,   181,
     446,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   227,
     184,   237,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     185,   186,   109,   220,   221,   222,   223,   224,   225,   226,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   187,   188,     7,   189,   190,   123,   220,
     221,   222,   223,   224,   225,   226,   220,   221,   222,   223,
     224,   225,   226,     7,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   274,   211,   299,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   386,
     211,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   304,   211,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   305,   463,   258,   259,   314,   311,
     312,   313,   464,   315,   319,   212,   321,   320,   322,   213,
     216,   217,   218,   405,   219,   216,   217,   218,   406,   219,
     323,   212,   324,   325,   326,   213,   216,   217,   218,   407,
     219,   327,   328,   212,   329,   332,   333,   213,   216,   217,
     218,   411,   219,   216,   217,   218,   412,   219,   216,   217,
     218,   415,   219,   216,   217,   218,   416,   219,   216,   217,
     218,   417,   219,   216,   217,   218,   418,   219,   216,   217,
     218,   419,   219,   216,   217,   218,   452,   219,   216,   217,
     218,   453,   219,   216,   217,   218,   454,   219,   216,   217,
     218,   472,   219,   216,   217,   218,   473,   219,   216,   217,
     218,   474,   219,   334,   342,   343,   344,   345,   352,   357,
     358,   359,   365,   366,   377,   387,   398,   414,   421,   420,
     424,   423,   425,   426,   432,   260,   433,   447,   465,   355,
     378,   385,   350
};

static const yytype_uint16 yycheck[] =
{
      24,     1,    28,   184,   164,   165,   166,    31,    32,     1,
       8,    21,     3,     4,     5,     6,     7,     8,     9,    79,
       1,     8,     4,     8,    34,     8,    74,    75,    31,    32,
       5,     6,     7,   214,     9,   216,   217,   218,   219,     3,
       4,     5,     6,     7,     8,     9,   212,    28,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     5,     6,     7,   363,     9,   297,    50,     8,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     8,   109,    84,    18,     3,     4,
       5,     6,     7,     8,     9,    82,    88,    82,     0,    82,
      28,   429,    30,    84,   104,     0,   109,    82,   274,   109,
     110,   111,   104,   102,   106,    74,    75,   109,   110,   111,
     112,     8,   102,     8,   104,   355,   117,    82,    81,    81,
     428,    84,    33,    34,    82,    87,     7,   465,     9,    82,
     321,   322,   323,    82,    81,   104,   327,   328,   329,    82,
      81,   115,    18,    81,    74,    75,    82,    85,    82,   104,
     341,   342,   343,   344,   345,   189,   190,    82,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   189,   190,     3,     4,
       5,     6,     7,     8,     9,    82,   178,    82,   222,   223,
     224,   225,   226,   185,   186,   187,   188,     3,     4,     5,
       6,     7,     8,     9,    82,    81,    33,    34,   102,   222,
     223,   224,   225,   226,   405,   406,   407,    74,    75,   211,
     411,   412,   242,   243,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     5,     6,     7,    82,     9,    82,     8,     9,
     430,   452,   453,   454,    79,   299,     3,     4,     5,     6,
       7,     8,     9,     5,     6,     7,    82,     9,    16,    17,
     122,   472,   473,   474,    33,    34,   299,     7,     8,     9,
     324,   325,   326,     5,     6,     7,    83,     9,     5,     6,
       7,    83,     9,    82,    81,    26,    27,    28,    81,    30,
      82,   324,   325,   326,    33,    34,    83,    82,    27,    28,
      81,    30,   102,   103,    82,   113,   114,    81,   116,    82,
     118,    79,   120,    82,   119,   123,    74,    75,   330,   125,
     126,    81,   127,   128,   129,    82,    81,     5,     6,     7,
      82,     9,    81,     3,     4,     5,     6,     7,     8,     9,
      81,   353,   398,    82,    85,     5,     6,     7,     8,     9,
      82,    81,    81,    81,    79,    82,    85,   358,   359,    81,
     414,   415,   416,   417,   418,   419,   420,   365,   366,   423,
       5,     6,     7,     8,     9,    81,    81,   389,    81,    81,
      81,   414,   415,   416,   417,   418,   419,   420,    81,    81,
     423,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    79,
      81,   121,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      81,    81,    81,     3,     4,     5,     6,     7,     8,     9,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,    81,    81,   104,    81,    81,   107,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,   104,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    81,    30,    87,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    79,
      30,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    83,    30,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,    83,    79,   180,   181,     8,   130,
     130,   130,    79,   104,    82,    81,     8,    82,     8,    85,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
       8,    81,     8,     8,     8,    85,     5,     6,     7,     8,
       9,     8,     8,    81,     8,    82,    82,    85,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,    84,     8,     8,     8,     8,    86,   131,
     131,   131,     8,     8,    30,    84,     8,    81,    79,   108,
     131,    87,   131,   131,    82,   182,    82,    82,    81,   304,
     339,   353,   275
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   133,   134,     0,   136,     1,    88,   104,   106,   109,
     110,   111,   112,   137,   141,   153,   155,   161,    79,    81,
     104,   162,   142,    81,    87,   102,   166,   102,   162,   165,
     113,   114,   116,   118,   120,   123,   143,   144,   145,   146,
     147,   148,   152,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    81,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   107,   159,   160,   161,   163,   164,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   158,
     159,    82,   165,    79,   158,   158,   149,   162,   122,    74,
      75,    74,    75,   161,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,   158,
      81,    81,    83,    83,    81,    81,    81,    81,    81,    81,
      81,    83,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    30,    81,    85,     8,    82,     5,     6,     7,     9,
       3,     4,     5,     6,     7,     8,     9,    79,    79,    79,
     115,   117,   119,   127,   128,   129,   150,   121,    33,    34,
     188,   193,   193,   193,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   157,   161,    82,   166,   166,
     134,    16,    17,    74,    75,   139,   140,   164,   161,   161,
     161,   161,   158,   158,    81,   191,   192,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   161,   163,   135,   164,    87,
     164,   164,   164,   164,    83,    83,   158,   158,   158,   158,
     158,   130,   130,   130,     8,   104,   189,   162,   162,    82,
      82,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,    82,    82,    82,    84,    74,    75,    74,    75,     8,
      84,     8,     8,     8,     8,     8,    82,    82,   163,    84,
     192,    82,    86,   136,   158,   135,   138,   131,   131,   131,
     102,   103,   167,    18,    81,     8,     8,   164,   164,   164,
     158,   158,   158,   164,   164,   164,   161,    30,   140,   164,
     164,   164,   164,   164,    82,   153,    79,    84,     1,    28,
      84,   154,   156,   125,   126,   151,   151,   151,     8,   189,
      82,   190,   193,   167,   167,     8,     8,     8,    82,    82,
      82,     8,     8,    82,    81,     8,     8,     8,     8,     8,
     108,    79,   161,    87,   131,   131,   131,   165,    18,    81,
       8,    82,    82,    82,   164,   164,   164,   164,   164,   158,
     158,   158,   158,   158,   158,   158,   158,    82,   189,    82,
     190,   193,     8,     8,     8,    82,    82,    82,    82,    82,
      82,    82,    82,    79,    79,    81,    82,   164,   164,   164,
      82,   190,     8,     8,     8,    82,   164,   164,   164,    82,
      82,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   132,   133,   134,   134,   135,   135,   136,   136,   137,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   140,   141,   141,   141,   141,   141,   142,   142,   143,
     143,   143,   143,   143,   143,   144,   144,   145,   146,   147,
     148,   149,   149,   150,   150,   150,   151,   151,   152,   153,
     153,   153,   154,   154,   155,   156,   157,   157,   158,   158,
     158,   158,   158,   158,   158,   158,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   162,   163,   163,
     164,   164,   164,   164,   164,   165,   166,   167,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     188,   188,   188,   188,   188,   189,   190,   190,   191,   191,
     192,   193,   193
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     0,     2,     1,     3,     1,     1,     2,     2,
       2,     2,     5,     4,     5,     1,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     0,     2,     3,     3,     1,
       3,     0,     2,     5,     5,     5,     1,     1,     3,     7,
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
#line 334 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1828 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 337 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1834 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 338 "faustparser.y" /* yacc.c:1652  */
    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp); }
#line 1840 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 341 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1846 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 342 "faustparser.y" /* yacc.c:1652  */
    { if (acceptdefinition((yyvsp[-1].numvariant))) (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-2].exp)); else (yyval.exp)=(yyvsp[-2].exp);}
#line 1852 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 345 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 0; }
#line 1858 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 346 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = (yyvsp[-1].numvariant) | (yyvsp[0].numvariant);}
#line 1864 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 349 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 1;}
#line 1870 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 350 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 2;}
#line 1876 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 351 "faustparser.y" /* yacc.c:1652  */
    { (yyval.numvariant) = 4;}
#line 1882 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 355 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1888 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 356 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1894 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 363 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1900 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 364 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1906 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 367 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1912 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 368 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1918 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 369 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1924 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 370 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1930 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 371 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1936 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 372 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1942 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 376 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1948 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 377 "faustparser.y" /* yacc.c:1652  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1954 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 378 "faustparser.y" /* yacc.c:1652  */
    { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1960 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 379 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1966 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 380 "faustparser.y" /* yacc.c:1652  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1972 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 383 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; }
#line 1978 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 384 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1984 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 387 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1990 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 388 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1996 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 389 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 2002 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 390 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docNtc(); }
#line 2008 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 391 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docLst(); }
#line 2014 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 392 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 2020 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 395 "faustparser.y" /* yacc.c:1652  */
    { (yyval.cppstr) = new string(); }
#line 2026 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 396 "faustparser.y" /* yacc.c:1652  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 2032 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 399 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2038 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 402 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2044 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 405 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2050 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 408 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2056 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 411 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2062 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 412 "faustparser.y" /* yacc.c:1652  */
    { }
#line 2068 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 415 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2074 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 416 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2080 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 417 "faustparser.y" /* yacc.c:1652  */
    { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2086 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 420 "faustparser.y" /* yacc.c:1652  */
    { (yyval.b) = true; }
#line 2092 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 421 "faustparser.y" /* yacc.c:1652  */
    { (yyval.b) = false; }
#line 2098 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 424 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2104 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 427 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2110 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 428 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2116 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 429 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2122 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 432 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2128 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 433 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2134 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 436 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2140 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 439 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2146 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 442 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2152 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 443 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2158 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 446 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2164 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 447 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2170 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 448 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2176 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 449 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2182 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 450 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2188 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 451 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2194 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 452 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2200 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 453 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2206 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 456 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2212 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 457 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2218 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 458 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2224 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 459 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2230 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 460 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2236 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 461 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2242 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 462 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2248 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 463 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2254 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 464 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2260 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 466 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2266 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 467 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2272 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 468 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2278 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 470 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2284 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 471 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2290 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 473 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2296 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 474 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2302 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 475 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2308 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 476 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2314 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 477 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2320 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 478 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2326 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 480 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2332 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 481 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2338 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 483 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2344 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 486 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2350 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 487 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2356 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 489 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2362 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 490 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2368 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 492 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2374 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 493 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2380 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 495 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWire(); }
#line 2386 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 496 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCut(); }
#line 2392 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 498 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2398 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 499 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2404 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 501 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2410 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 502 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2416 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 504 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2422 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 505 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2428 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 506 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2434 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 507 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2440 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 508 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2446 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 509 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2452 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 511 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2458 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 512 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2464 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 513 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2470 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 515 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2476 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 516 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2482 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 518 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2488 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 519 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2494 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 520 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2500 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 521 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2506 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 522 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2512 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 523 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2518 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 525 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2524 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 526 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2530 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 120:
#line 527 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2536 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 121:
#line 530 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2542 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 122:
#line 531 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2548 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 123:
#line 532 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2554 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 124:
#line 533 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2560 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 125:
#line 534 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2566 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 126:
#line 535 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2572 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 127:
#line 536 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2578 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 128:
#line 538 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2584 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 129:
#line 539 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2590 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 130:
#line 540 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2596 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 131:
#line 541 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2602 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 132:
#line 542 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2608 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 133:
#line 543 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2614 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 134:
#line 545 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2620 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 135:
#line 546 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2626 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 136:
#line 547 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2632 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 137:
#line 549 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2638 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 138:
#line 550 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2644 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 139:
#line 552 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2650 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 140:
#line 553 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2656 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 141:
#line 554 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2662 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 142:
#line 557 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2668 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 143:
#line 558 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2674 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 144:
#line 560 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2680 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 145:
#line 561 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2686 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 146:
#line 563 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2692 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 147:
#line 564 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2698 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 148:
#line 566 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2704 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 149:
#line 568 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2710 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 150:
#line 570 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2716 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 151:
#line 572 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2722 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 152:
#line 573 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2728 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 153:
#line 574 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2734 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 154:
#line 575 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2740 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 155:
#line 576 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2746 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 156:
#line 577 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2752 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 157:
#line 578 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2758 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 158:
#line 579 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2764 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 159:
#line 580 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2770 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 160:
#line 581 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2776 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 161:
#line 582 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2782 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 162:
#line 583 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2788 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 163:
#line 584 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2794 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 164:
#line 585 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2800 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 165:
#line 586 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2806 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 166:
#line 587 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2812 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 167:
#line 588 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2818 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 168:
#line 589 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2824 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 169:
#line 590 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2830 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 170:
#line 592 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2836 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 171:
#line 593 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2842 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 172:
#line 594 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2848 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 173:
#line 595 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2854 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 174:
#line 597 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2860 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 175:
#line 598 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2866 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 176:
#line 603 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2872 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 177:
#line 606 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2878 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 178:
#line 611 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2884 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 179:
#line 612 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2890 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 180:
#line 615 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2896 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 181:
#line 616 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2902 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 182:
#line 617 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2908 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 183:
#line 618 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2914 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 184:
#line 619 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2920 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 185:
#line 622 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2926 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 186:
#line 625 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = unquote(yytext); }
#line 2932 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 187:
#line 628 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2938 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 188:
#line 629 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 2944 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 189:
#line 635 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2950 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 190:
#line 639 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2956 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 191:
#line 643 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2962 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 192:
#line 647 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2968 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 193:
#line 651 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2974 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 194:
#line 654 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2980 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 195:
#line 662 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2986 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 196:
#line 666 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2992 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 197:
#line 669 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2998 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 198:
#line 673 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3004 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 199:
#line 676 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3010 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 200:
#line 680 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3016 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 201:
#line 683 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3022 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 202:
#line 686 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3028 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 203:
#line 689 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3034 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 204:
#line 692 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3040 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 205:
#line 695 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3046 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 206:
#line 699 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3052 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 207:
#line 702 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3058 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 208:
#line 705 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3064 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 209:
#line 711 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3070 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 210:
#line 712 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3076 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 211:
#line 713 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3082 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 212:
#line 715 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3088 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 213:
#line 716 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3094 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 214:
#line 717 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3100 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 215:
#line 720 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(yytext); }
#line 3106 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 216:
#line 723 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3112 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 217:
#line 724 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3118 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 218:
#line 727 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3124 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 219:
#line 728 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3130 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 220:
#line 732 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3136 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 221:
#line 735 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(0); }
#line 3142 "faustparser.cpp" /* yacc.c:1652  */
    break;

  case 222:
#line 736 "faustparser.y" /* yacc.c:1652  */
    { (yyval.exp) = tree(1); }
#line 3148 "faustparser.cpp" /* yacc.c:1652  */
    break;


#line 3152 "faustparser.cpp" /* yacc.c:1652  */
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
#line 739 "faustparser.y" /* yacc.c:1918  */


