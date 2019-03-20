/* A Bison parser, made by GNU Bison 3.2.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.2.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "faustparser.y" /* yacc.c:338  */


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


#line 136 "faustparser.cpp" /* yacc.c:338  */
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
    BDOC = 364,
    EDOC = 365,
    BEQN = 366,
    EEQN = 367,
    BDGM = 368,
    EDGM = 369,
    BLST = 370,
    ELST = 371,
    BMETADATA = 372,
    EMETADATA = 373,
    DOCCHAR = 374,
    NOTICE = 375,
    LISTING = 376,
    LSTTRUE = 377,
    LSTFALSE = 378,
    LSTDEPENDENCIES = 379,
    LSTMDOCTAGS = 380,
    LSTDISTRIBUTED = 381,
    LSTEQ = 382,
    LSTQ = 383
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 73 "faustparser.y" /* yacc.c:353  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 315 "faustparser.cpp" /* yacc.c:353  */
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
#define YYLAST   734

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  476

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   383

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
     125,   126,   127,   128
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   320,   321,   323,   324,   328,   329,   336,
     337,   340,   341,   342,   343,   344,   345,   349,   350,   351,
     352,   353,   356,   357,   360,   361,   362,   363,   364,   365,
     368,   369,   372,   375,   378,   381,   384,   385,   388,   389,
     390,   393,   394,   397,   400,   401,   402,   405,   406,   409,
     412,   415,   416,   419,   420,   421,   422,   423,   424,   425,
     426,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     439,   440,   441,   443,   444,   446,   447,   448,   449,   450,
     451,   453,   454,   456,   459,   460,   462,   463,   465,   466,
     468,   469,   471,   472,   474,   475,   477,   478,   479,   480,
     481,   482,   484,   485,   486,   488,   489,   491,   492,   493,
     494,   495,   496,   498,   499,   500,   503,   504,   505,   506,
     507,   508,   509,   511,   512,   513,   514,   515,   516,   518,
     519,   520,   522,   523,   525,   526,   527,   530,   531,   533,
     534,   536,   537,   539,   540,   543,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   565,   566,   567,   568,   570,
     571,   576,   579,   584,   585,   588,   589,   590,   591,   592,
     595,   598,   601,   602,   607,   611,   615,   619,   624,   627,
     634,   638,   641,   646,   649,   652,   655,   658,   661,   664,
     667,   671,   674,   677,   684,   685,   686,   688,   689,   690,
     693,   696,   697,   700,   701,   704,   708,   709
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
     375,   376,   377,   378,   379,   380,   381,   382,   383
};
# endif

#define YYPACT_NINF -413

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-413)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -413,    10,    20,  -413,   -28,   -15,  -413,   -20,  -413,  -413,
    -413,     5,  -413,  -413,   -11,  -413,   170,   267,   410,   410,
    -413,    25,  -413,    -5,    24,  -413,   410,   410,  -413,   -20,
    -413,  -413,    78,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,    63,   160,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
     152,   213,   225,   230,   239,   243,   252,   262,   266,   271,
     287,   288,   291,   298,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,   300,  -413,  -413,   410,   302,   304,   235,   274,   305,
    -413,  -413,   307,   315,   316,   318,   319,   322,   326,   530,
    -413,  -413,    16,   126,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,   489,   530,   292,   339,  -413,    27,
       9,   179,   227,  -413,  -413,  -413,  -413,  -413,  -413,   183,
     183,   183,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,   297,    34,   -11,   -11,  -413,    72,   410,
     297,   297,   297,   297,   410,   410,   324,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,  -413,   297,   410,  -413,   410,
     351,   410,   410,   410,   410,   356,   357,   410,   410,   410,
     410,   410,  -413,  -413,  -413,  -413,  -413,  -413,   362,   363,
     385,  -413,  -413,  -413,  -413,   505,   411,   -20,   -20,   434,
     457,   551,   556,   558,   559,   574,   599,   601,   602,   604,
      18,  -413,  -413,   479,   531,    21,   191,   202,  -413,  -413,
      15,  -413,   146,   606,   609,   610,   611,    52,    67,   410,
     -32,  -413,   553,   553,   553,   553,   553,   553,   565,   565,
     565,   323,   323,   323,   323,   323,   323,   323,   535,   282,
    -413,    36,     8,   126,   410,   126,   126,   310,  -413,  -413,
    -413,   591,   591,   290,   328,  -413,   493,   509,   516,   236,
    -413,    30,   625,   637,  -413,  -413,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   297,   617,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,    72,  -413,   410,   410,   410,   410,
     410,  -413,  -413,    54,  -413,  -413,  -413,  -413,  -413,   515,
      44,    26,   237,   237,   237,  -413,  -413,   640,   411,    62,
     236,   236,   597,   634,   646,    74,   154,   186,   651,   656,
      58,  -413,   568,  -413,   661,   666,   671,   676,   681,   613,
    -413,  -413,   643,   297,  -413,  -413,   636,  -413,  -413,   596,
     598,   600,    -5,    32,  -413,    82,  -413,   645,   647,   410,
     410,   410,  -413,  -413,  -413,   410,   410,  -413,   410,   410,
     410,   410,   410,   410,   410,  -413,  -413,   410,  -413,  -413,
    -413,   648,   411,    68,   183,  -413,  -413,  -413,   686,   691,
     696,   136,   264,   204,   234,   246,   253,   276,   284,   522,
     529,  -413,   644,  -413,    85,  -413,   410,   410,   410,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,   181,
    -413,   701,   706,   711,  -413,   106,   410,   410,   410,  -413,
     320,   325,   335,  -413,  -413,  -413
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   171,     0,    22,     4,
      20,     0,    49,    46,     0,   172,     0,    30,     0,     0,
     181,     0,   180,     0,     0,    21,     0,     0,    36,     0,
      34,    23,    24,    25,    26,    27,    28,    29,   107,   108,
     111,   109,   110,   112,    96,    97,   103,    98,    99,   100,
     102,   104,   105,   106,   126,   101,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    84,
      85,     0,    90,    91,     0,     0,     0,     0,     0,     0,
     114,   115,     0,     0,     0,     0,     0,     0,     0,   179,
      83,   141,     0,   173,   165,   166,   167,   168,   169,   170,
     146,   147,   148,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,     0,    60,     0,     0,    18,     0,
       0,     0,     0,    31,    86,    87,    88,    89,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    17,    19,    32,    33,    35,     0,     0,
       0,    37,    43,   216,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,   143,     0,     0,     0,     0,     0,    11,    12,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   213,    75,    76,    79,    77,    78,    80,    61,    62,
      71,    63,    64,    65,    70,    72,    73,    74,    66,    67,
      69,     0,     0,   174,     0,   176,   177,   175,   178,     5,
       7,    57,    58,    56,    55,    59,     0,     0,     0,     0,
     210,     0,     0,     0,   193,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,   150,   151,
      13,    14,    15,    16,     0,   152,     0,     0,     0,     0,
       0,   188,   189,     0,   145,   214,    81,    82,     6,     0,
       0,     0,     0,     0,     0,   182,   183,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,    10,     0,     0,     0,     0,     0,     0,
      44,    53,     0,     0,    54,     8,     0,    41,    42,     0,
       0,     0,     0,     0,   207,     0,   211,     0,     0,     0,
       0,     0,   198,   199,   200,     0,     0,   203,     0,     0,
       0,     0,     0,     0,     0,    48,    50,     0,    38,    39,
      40,     0,     0,     0,     0,   204,   191,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,     0,   208,     0,   212,     0,     0,     0,   202,
     201,   144,   153,   184,   185,   186,   187,   215,    47,     0,
     205,     0,     0,     0,   209,     0,     0,     0,     0,   206,
       0,     0,     0,   195,   196,   197
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -413,  -413,   554,   433,  -413,  -413,   399,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,    11,  -413,  -246,
    -413,  -413,  -413,  -413,     2,   -19,  -413,    23,   -10,  -154,
     -92,   -22,   460,     1,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,  -413,
    -413,  -413,  -413,  -413,  -413,  -353,  -412,  -413,   464,  -157
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   292,   351,   260,   261,     9,    17,    31,
      32,    33,    34,    35,    36,   151,   231,   389,    37,    10,
     385,    11,   386,   250,   144,   119,   120,   121,    16,   122,
     123,    24,    21,   357,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   235,   311,   395,   270,   271,   396
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     145,   147,   236,   237,   238,   393,    23,   145,   145,     4,
       3,   444,   215,   216,   217,   218,   219,   220,   221,   152,
      -2,     4,     4,   334,   209,    12,   325,   382,   149,   150,
     215,   216,   217,   218,   219,   220,   221,   215,   216,   217,
     218,   219,   220,   221,   209,     4,   348,   465,   358,   269,
     422,    13,   344,   291,   383,   215,   216,   217,   218,   219,
     220,   221,   209,   211,   212,   213,    14,   214,   158,   442,
     215,   216,   217,   218,   219,   220,   221,   215,   216,   217,
     218,   219,   220,   221,    15,   145,    18,   262,   256,   257,
     424,    20,    19,   424,   347,   233,   234,    22,   210,   335,
     326,   233,   234,   148,   348,   329,   174,   146,     5,     5,
     384,   359,     6,   423,   424,   343,   252,   293,   346,   295,
     296,   297,   298,   226,     6,     6,     7,     7,   381,     8,
       8,   211,   212,   213,   341,   214,   379,   154,   155,   225,
     407,   211,   212,   213,   394,   214,   258,   259,     6,   342,
     443,   211,   212,   213,   336,   214,   402,   215,   216,   217,
     218,   219,   220,   221,   425,   145,   145,   460,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   267,   268,   469,   215,
     216,   217,   218,   219,   220,   221,   251,   153,   145,   145,
     145,   145,   145,   263,   264,   265,   266,   215,   216,   217,
     218,   219,   220,   221,   233,   234,   233,   234,   449,   301,
     302,   303,   304,   305,   362,   363,   364,   312,   313,   290,
     368,   369,   370,   159,   156,   157,   403,   215,   216,   217,
     218,   219,   220,   221,   374,   375,   376,   377,   378,   215,
     216,   217,   218,   219,   220,   221,   215,   216,   217,   218,
     219,   220,   221,   464,     6,   330,   331,   445,   404,   211,
     212,   213,    22,   214,    15,   145,   332,   333,    12,   215,
     216,   217,   218,   219,   220,   221,   451,   215,   216,   217,
     218,   219,   220,   221,   160,   227,   349,   219,   220,   221,
     145,   145,   145,   228,   229,   230,   161,   428,   429,   430,
     205,   162,   206,   431,   432,    12,   452,   213,   177,   214,
     163,   365,   366,   367,   164,   211,   212,   213,   453,   214,
     211,   212,   213,   165,   214,   454,   220,   221,   355,   356,
     211,   212,   213,   166,   214,   232,   450,   167,   371,   203,
     204,   205,   168,   206,   461,   462,   463,   178,   455,   387,
     388,   397,   398,   207,   390,   391,   456,   208,   169,   170,
     421,   223,   171,    12,   470,   471,   472,    25,    26,   172,
      27,   173,    28,   175,    29,   176,   179,    30,   180,   145,
     145,   145,   145,   145,   145,   145,   181,   182,   145,   183,
     184,     6,   473,   185,   207,   269,   416,   474,   208,   186,
     433,   434,   435,   436,   437,   438,   439,   475,   224,   440,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,   294,   299,
     300,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   306,
     307,   104,   215,   216,   217,   218,   219,   220,   221,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   308,   309,     6,   310,   314,   118,   215,   216,
     217,   218,   219,   220,   221,   215,   216,   217,   218,   219,
     220,   221,   215,   216,   217,   218,   219,   220,   221,   315,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   316,
     206,   327,   204,   205,   317,   206,   318,   319,   222,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   320,   206,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   380,   206,   217,   218,   219,   220,
     221,   457,   211,   212,   213,   399,   214,   321,   458,   322,
     323,   207,   324,   328,   337,   208,   207,   338,   339,   340,
     208,   352,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   360,   207,   253,   254,   353,   208,   211,
     212,   213,   400,   214,   354,   361,   207,   372,   392,   408,
     208,   211,   212,   213,   401,   214,   211,   212,   213,   405,
     214,   211,   212,   213,   406,   214,   211,   212,   213,   409,
     214,   211,   212,   213,   410,   214,   211,   212,   213,   411,
     214,   211,   212,   213,   412,   214,   211,   212,   213,   413,
     214,   211,   212,   213,   446,   214,   211,   212,   213,   447,
     214,   211,   212,   213,   448,   214,   211,   212,   213,   466,
     214,   211,   212,   213,   467,   214,   211,   212,   213,   468,
     214,   414,   415,   417,   418,   459,   419,   426,   420,   427,
     441,   255,   350,   373,   345
};

static const yytype_uint16 yycheck[] =
{
      19,    23,   159,   160,   161,   358,    16,    26,    27,     1,
       0,   423,     3,     4,     5,     6,     7,     8,     9,    29,
       0,     1,     1,     8,     8,     2,     8,     1,    26,    27,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     8,     1,   292,   459,    18,    81,
      18,    79,    84,   207,    28,     3,     4,     5,     6,     7,
       8,     9,     8,     5,     6,     7,    81,     9,    45,   422,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,   104,   104,    81,   179,    16,    17,
       8,   102,    87,     8,    86,    33,    34,   102,    82,    84,
      82,    33,    34,    79,   350,    84,   104,    82,    88,    88,
      84,    81,   104,    81,     8,   269,    82,   209,    82,   211,
     212,   213,   214,   114,   104,   104,   106,   106,    84,   109,
     109,     5,     6,     7,    82,     9,    82,    74,    75,   112,
      82,     5,     6,     7,    82,     9,    74,    75,   104,    82,
      82,     5,     6,     7,     8,     9,    82,     3,     4,     5,
       6,     7,     8,     9,    82,   184,   185,    82,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   184,   185,    82,     3,
       4,     5,     6,     7,     8,     9,   173,   119,   217,   218,
     219,   220,   221,   180,   181,   182,   183,     3,     4,     5,
       6,     7,     8,     9,    33,    34,    33,    34,    82,   217,
     218,   219,   220,   221,   316,   317,   318,   237,   238,   206,
     322,   323,   324,    81,    74,    75,    82,     3,     4,     5,
       6,     7,     8,     9,   336,   337,   338,   339,   340,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,    82,   104,    74,    75,   424,    82,     5,
       6,     7,   102,     9,   104,   294,    74,    75,   255,     3,
       4,     5,     6,     7,     8,     9,    82,     3,     4,     5,
       6,     7,     8,     9,    81,   116,   294,     7,     8,     9,
     319,   320,   321,   124,   125,   126,    81,   399,   400,   401,
      28,    81,    30,   405,   406,   292,    82,     7,    83,     9,
      81,   319,   320,   321,    81,     5,     6,     7,    82,     9,
       5,     6,     7,    81,     9,    82,     8,     9,   102,   103,
       5,     6,     7,    81,     9,   118,    82,    81,   325,    26,
      27,    28,    81,    30,   446,   447,   448,    83,    82,   122,
     123,   360,   361,    81,   353,   354,    82,    85,    81,    81,
     392,    79,    81,   350,   466,   467,   468,   110,   111,    81,
     113,    81,   115,    81,   117,    81,    81,   120,    81,   408,
     409,   410,   411,   412,   413,   414,    81,    81,   417,    81,
      81,   104,    82,    81,    81,    81,   383,    82,    85,    83,
     408,   409,   410,   411,   412,   413,   414,    82,    79,   417,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    87,    83,
      83,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   127,
     127,    81,     3,     4,     5,     6,     7,     8,     9,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   127,     8,   104,   104,    82,   107,     3,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,    82,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     8,
      30,    82,    27,    28,     8,    30,     8,     8,    79,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     8,    30,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    79,    30,     5,     6,     7,     8,
       9,    79,     5,     6,     7,     8,     9,     8,    79,     8,
       8,    81,     8,    82,     8,    85,    81,     8,     8,     8,
      85,   128,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     8,    81,   175,   176,   128,    85,     5,
       6,     7,     8,     9,   128,     8,    81,    30,     8,    81,
      85,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,   108,    79,    87,   128,    81,   128,    82,   128,    82,
      82,   177,   299,   334,   270
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   130,   131,     0,     1,    88,   104,   106,   109,   136,
     148,   150,   156,    79,    81,   104,   157,   137,    81,    87,
     102,   161,   102,   157,   160,   110,   111,   113,   115,   117,
     120,   138,   139,   140,   141,   142,   143,   147,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    81,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   107,   154,
     155,   156,   158,   159,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   153,   154,    82,   160,    79,   153,
     153,   144,   157,   119,    74,    75,    74,    75,   156,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,   153,    81,    81,    83,    83,    81,
      81,    81,    81,    81,    81,    81,    83,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    30,    81,    85,     8,
      82,     5,     6,     7,     9,     3,     4,     5,     6,     7,
       8,     9,    79,    79,    79,   112,   114,   116,   124,   125,
     126,   145,   118,    33,    34,   183,   188,   188,   188,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     152,   156,    82,   161,   161,   131,    16,    17,    74,    75,
     134,   135,   159,   156,   156,   156,   156,   153,   153,    81,
     186,   187,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     156,   158,   132,   159,    87,   159,   159,   159,   159,    83,
      83,   153,   153,   153,   153,   153,   127,   127,   127,     8,
     104,   184,   157,   157,    82,    82,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,    82,    82,    82,    84,
      74,    75,    74,    75,     8,    84,     8,     8,     8,     8,
       8,    82,    82,   158,    84,   187,    82,    86,   148,   153,
     132,   133,   128,   128,   128,   102,   103,   162,    18,    81,
       8,     8,   159,   159,   159,   153,   153,   153,   159,   159,
     159,   156,    30,   135,   159,   159,   159,   159,   159,    82,
      79,    84,     1,    28,    84,   149,   151,   122,   123,   146,
     146,   146,     8,   184,    82,   185,   188,   162,   162,     8,
       8,     8,    82,    82,    82,     8,     8,    82,    81,     8,
       8,     8,     8,     8,   108,    79,   156,    87,   128,   128,
     128,   160,    18,    81,     8,    82,    82,    82,   159,   159,
     159,   159,   159,   153,   153,   153,   153,   153,   153,   153,
     153,    82,   184,    82,   185,   188,     8,     8,     8,    82,
      82,    82,    82,    82,    82,    82,    82,    79,    79,    81,
      82,   159,   159,   159,    82,   185,     8,     8,     8,    82,
     159,   159,   159,    82,    82,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   129,   130,   131,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   135,   135,   135,   135,   136,   136,   136,
     136,   136,   137,   137,   138,   138,   138,   138,   138,   138,
     139,   139,   140,   141,   142,   143,   144,   144,   145,   145,
     145,   146,   146,   147,   148,   148,   148,   149,   149,   150,
     151,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   156,   157,   158,   158,   159,   159,   159,   159,   159,
     160,   161,   162,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   183,   183,   183,   183,   183,
     184,   185,   185,   186,   186,   187,   188,   188
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
       4,     4,     4,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       8,     7,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     6,     5,     7,     9,     4,     6,     8,
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
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

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
                  (unsigned long) yystacksize));

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
#line 317 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1796 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 3:
#line 320 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; }
#line 1802 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 4:
#line 321 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1808 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 5:
#line 323 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; }
#line 1814 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 6:
#line 324 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1820 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 7:
#line 328 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; }
#line 1826 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 8:
#line 329 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1832 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 9:
#line 336 "faustparser.y" /* yacc.c:1645  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1838 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 10:
#line 337 "faustparser.y" /* yacc.c:1645  */
    { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1844 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 11:
#line 340 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1850 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 12:
#line 341 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1856 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 13:
#line 342 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1862 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 14:
#line 343 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 1868 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 15:
#line 344 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1874 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 16:
#line 345 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1880 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 17:
#line 349 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1886 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 18:
#line 350 "faustparser.y" /* yacc.c:1645  */
    { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1892 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 19:
#line 351 "faustparser.y" /* yacc.c:1645  */
    { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 1898 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 20:
#line 352 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1904 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 21:
#line 353 "faustparser.y" /* yacc.c:1645  */
    { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 1910 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 22:
#line 356 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; }
#line 1916 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 23:
#line 357 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1922 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 24:
#line 360 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 1928 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 25:
#line 361 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 1934 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 26:
#line 362 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 1940 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 27:
#line 363 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docNtc(); }
#line 1946 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 28:
#line 364 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docLst(); }
#line 1952 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 29:
#line 365 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 1958 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 30:
#line 368 "faustparser.y" /* yacc.c:1645  */
    { (yyval.cppstr) = new string(); }
#line 1964 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 31:
#line 369 "faustparser.y" /* yacc.c:1645  */
    { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 1970 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 32:
#line 372 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1976 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 33:
#line 375 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1982 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 34:
#line 378 "faustparser.y" /* yacc.c:1645  */
    { }
#line 1988 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 35:
#line 381 "faustparser.y" /* yacc.c:1645  */
    { }
#line 1994 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 36:
#line 384 "faustparser.y" /* yacc.c:1645  */
    { }
#line 2000 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 37:
#line 385 "faustparser.y" /* yacc.c:1645  */
    { }
#line 2006 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 38:
#line 388 "faustparser.y" /* yacc.c:1645  */
    { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2012 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 39:
#line 389 "faustparser.y" /* yacc.c:1645  */
    { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2018 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 40:
#line 390 "faustparser.y" /* yacc.c:1645  */
    { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2024 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 41:
#line 393 "faustparser.y" /* yacc.c:1645  */
    { (yyval.b) = true; }
#line 2030 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 42:
#line 394 "faustparser.y" /* yacc.c:1645  */
    { (yyval.b) = false; }
#line 2036 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 43:
#line 397 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2042 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 44:
#line 400 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2048 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 45:
#line 401 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2054 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 46:
#line 402 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2060 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 47:
#line 405 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2066 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 48:
#line 406 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2072 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 49:
#line 409 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2078 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 50:
#line 412 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp)=(yyvsp[0].exp); }
#line 2084 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 51:
#line 415 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2090 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 52:
#line 416 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2096 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 53:
#line 419 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2102 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 54:
#line 420 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2108 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 55:
#line 421 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2114 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 56:
#line 422 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2120 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 57:
#line 423 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2126 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 58:
#line 424 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2132 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 59:
#line 425 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2138 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 60:
#line 426 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2144 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 61:
#line 429 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2150 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 62:
#line 430 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2156 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 63:
#line 431 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2162 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 64:
#line 432 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2168 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 65:
#line 433 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2174 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 66:
#line 434 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2180 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 67:
#line 435 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2186 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 68:
#line 436 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2192 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 69:
#line 437 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2198 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 70:
#line 439 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2204 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 71:
#line 440 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2210 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 72:
#line 441 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2216 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 73:
#line 443 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2222 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 74:
#line 444 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2228 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 75:
#line 446 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2234 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 76:
#line 447 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2240 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 77:
#line 448 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2246 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 78:
#line 449 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2252 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 79:
#line 450 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2258 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 80:
#line 451 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2264 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 81:
#line 453 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2270 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 82:
#line 454 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2276 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 83:
#line 456 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2282 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 84:
#line 459 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2288 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 85:
#line 460 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2294 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 86:
#line 462 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2300 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 87:
#line 463 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal(atof(yytext)); }
#line 2306 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 88:
#line 465 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2312 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 89:
#line 466 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2318 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 90:
#line 468 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxWire(); }
#line 2324 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 91:
#line 469 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxCut(); }
#line 2330 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 92:
#line 471 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2336 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 93:
#line 472 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2342 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 94:
#line 474 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2348 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 95:
#line 475 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2354 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 96:
#line 477 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigAdd); }
#line 2360 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 97:
#line 478 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigSub); }
#line 2366 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 98:
#line 479 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigMul); }
#line 2372 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 99:
#line 480 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigDiv); }
#line 2378 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 100:
#line 481 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigRem); }
#line 2384 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 101:
#line 482 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2390 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 102:
#line 484 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigAND); }
#line 2396 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 103:
#line 485 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigOR); }
#line 2402 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 104:
#line 486 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigXOR); }
#line 2408 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 105:
#line 488 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2414 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 106:
#line 489 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2420 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 107:
#line 491 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigLT); }
#line 2426 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 108:
#line 492 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigLE); }
#line 2432 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 109:
#line 493 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigGT); }
#line 2438 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 110:
#line 494 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigGE); }
#line 2444 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 111:
#line 495 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigEQ); }
#line 2450 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 112:
#line 496 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigNE); }
#line 2456 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 113:
#line 498 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigAttach); }
#line 2462 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 114:
#line 499 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigEnable); }
#line 2468 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 115:
#line 500 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim2(sigControl); }
#line 2474 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 116:
#line 503 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2480 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 117:
#line 504 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2486 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 118:
#line 505 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2492 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 119:
#line 506 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2498 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 120:
#line 507 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2504 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 121:
#line 508 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2510 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 122:
#line 509 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2516 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 123:
#line 511 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2522 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 124:
#line 512 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2528 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 125:
#line 513 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2534 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 126:
#line 514 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2540 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 127:
#line 515 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2546 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 128:
#line 516 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2552 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 129:
#line 518 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2558 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 130:
#line 519 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2564 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 131:
#line 520 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2570 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 132:
#line 522 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2576 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 133:
#line 523 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2582 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 134:
#line 525 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2588 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 135:
#line 526 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2594 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 136:
#line 527 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2600 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 137:
#line 530 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2606 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 138:
#line 531 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2612 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 139:
#line 533 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2618 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 140:
#line 534 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2624 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 141:
#line 536 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2630 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 142:
#line 537 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2636 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 143:
#line 539 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 2642 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 144:
#line 541 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2648 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 145:
#line 543 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2654 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 146:
#line 545 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2660 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 147:
#line 546 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2666 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 148:
#line 547 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2672 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 149:
#line 548 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2678 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 150:
#line 549 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2684 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 151:
#line 550 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2690 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 152:
#line 551 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2696 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 153:
#line 552 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2702 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 154:
#line 553 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2708 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 155:
#line 554 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2714 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 156:
#line 555 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2720 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 157:
#line 556 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2726 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 158:
#line 557 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2732 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 159:
#line 558 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2738 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 160:
#line 559 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2744 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 161:
#line 560 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2750 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 162:
#line 561 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2756 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 163:
#line 562 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2762 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 164:
#line 563 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2768 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 165:
#line 565 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2774 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 166:
#line 566 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2780 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 167:
#line 567 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2786 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 168:
#line 568 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2792 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 169:
#line 570 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2798 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 170:
#line 571 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2804 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 171:
#line 576 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2810 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 172:
#line 579 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2816 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 173:
#line 584 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2822 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 174:
#line 585 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2828 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 175:
#line 588 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2834 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 176:
#line 589 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2840 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 177:
#line 590 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2846 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 178:
#line 591 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2852 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 179:
#line 592 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2858 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 180:
#line 595 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(yytext); }
#line 2864 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 181:
#line 598 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = unquote(yytext); }
#line 2870 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 182:
#line 601 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(yytext); }
#line 2876 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 183:
#line 602 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(yytext); }
#line 2882 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 184:
#line 608 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2888 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 185:
#line 612 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2894 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 186:
#line 616 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2900 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 187:
#line 620 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2906 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 188:
#line 624 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 2912 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 189:
#line 627 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 2918 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 190:
#line 635 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2924 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 191:
#line 639 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2930 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 192:
#line 642 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2936 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 193:
#line 646 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 2942 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 194:
#line 649 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 2948 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 195:
#line 653 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2954 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 196:
#line 656 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2960 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 197:
#line 659 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2966 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 198:
#line 662 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2972 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 199:
#line 665 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2978 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 200:
#line 668 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2984 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 201:
#line 672 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2990 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 202:
#line 675 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2996 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 203:
#line 678 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3002 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 204:
#line 684 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3008 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 205:
#line 685 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3014 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 206:
#line 686 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3020 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 207:
#line 688 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3026 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 208:
#line 689 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3032 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 209:
#line 690 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3038 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 210:
#line 693 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(yytext); }
#line 3044 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 211:
#line 696 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3050 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 212:
#line 697 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3056 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 213:
#line 700 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3062 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 214:
#line 701 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3068 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 215:
#line 705 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3074 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 216:
#line 708 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(0); }
#line 3080 "faustparser.cpp" /* yacc.c:1645  */
    break;

  case 217:
#line 709 "faustparser.y" /* yacc.c:1645  */
    { (yyval.exp) = tree(1); }
#line 3086 "faustparser.cpp" /* yacc.c:1645  */
    break;


#line 3090 "faustparser.cpp" /* yacc.c:1645  */
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
#line 712 "faustparser.y" /* yacc.c:1903  */


