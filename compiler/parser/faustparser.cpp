/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 5 "parser/faustparser.y"


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
extern vector<Tree> gDocVector;


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


/* Line 371 of yacc.c  */
#line 140 "parser/faustparser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WITH = 258,
     MIX = 259,
     SPLIT = 260,
     SEQ = 261,
     PAR = 262,
     REC = 263,
     NE = 264,
     GE = 265,
     GT = 266,
     EQ = 267,
     LE = 268,
     LT = 269,
     OR = 270,
     SUB = 271,
     ADD = 272,
     RSH = 273,
     LSH = 274,
     XOR = 275,
     AND = 276,
     MOD = 277,
     DIV = 278,
     MUL = 279,
     POWOP = 280,
     FDELAY = 281,
     DELAY1 = 282,
     DOT = 283,
     APPL = 284,
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


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 78 "parser/faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;


/* Line 387 of yacc.c  */
#line 320 "parser/faustparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 348 "parser/faustparser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   797

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNRULES -- Number of states.  */
#define YYNSTATES  454

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   384

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    13,    15,    19,
      21,    23,    26,    29,    32,    35,    41,    46,    48,    52,
      53,    56,    58,    60,    62,    64,    66,    68,    69,    72,
      76,    80,    82,    86,    87,    90,    96,   102,   108,   110,
     112,   116,   124,   129,   132,   134,   136,   140,   146,   150,
     154,   158,   162,   166,   168,   172,   176,   180,   184,   188,
     192,   196,   199,   203,   207,   211,   215,   219,   223,   227,
     231,   235,   239,   243,   247,   251,   256,   261,   263,   265,
     267,   270,   273,   276,   279,   281,   283,   285,   287,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   323,   325,   327,   329,
     331,   333,   335,   337,   339,   341,   343,   345,   347,   349,
     351,   353,   355,   357,   359,   361,   363,   365,   367,   369,
     371,   373,   375,   377,   379,   381,   383,   385,   387,   390,
     394,   396,   399,   403,   412,   417,   419,   421,   423,   428,
     433,   438,   443,   445,   447,   449,   451,   453,   455,   457,
     459,   461,   463,   465,   467,   469,   471,   473,   475,   477,
     479,   481,   485,   489,   493,   497,   501,   503,   505,   507,
     509,   511,   520,   529,   538,   547,   552,   557,   566,   574,
     582,   587,   592,   605,   618,   631,   638,   645,   652,   661,
     670,   676,   684,   694,   699,   706,   715,   717,   719,   723,
     725,   728,   735,   737
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     131,     0,    -1,   132,    -1,    -1,   132,   136,    -1,    -1,
     133,   148,    -1,   135,    -1,   134,     7,   135,    -1,    73,
      -1,    74,    -1,    17,    73,    -1,    17,    74,    -1,    16,
      73,    -1,    16,    74,    -1,    87,    80,   159,    81,    78,
      -1,   102,   155,   158,    78,    -1,   148,    -1,   110,   137,
     111,    -1,    -1,   137,   138,    -1,   139,    -1,   140,    -1,
     141,    -1,   142,    -1,   143,    -1,   147,    -1,    -1,   139,
     120,    -1,   112,   151,   113,    -1,   114,   151,   115,    -1,
     121,    -1,   116,   144,   117,    -1,    -1,   144,   145,    -1,
     125,   128,   129,   146,   129,    -1,   126,   128,   129,   146,
     129,    -1,   127,   128,   129,   146,   129,    -1,   123,    -1,
     124,    -1,   118,   155,   119,    -1,   149,    80,   156,    81,
      86,   151,    78,    -1,   149,    86,   151,    78,    -1,     1,
      78,    -1,   154,    -1,   154,    -1,   150,     7,   154,    -1,
     151,     3,    82,   133,    83,    -1,   151,     7,   151,    -1,
     151,     6,   151,    -1,   151,     5,   151,    -1,   151,     4,
     151,    -1,   151,     8,   151,    -1,   152,    -1,   152,    17,
     152,    -1,   152,    16,   152,    -1,   152,    24,   152,    -1,
     152,    23,   152,    -1,   152,    22,   152,    -1,   152,    25,
     152,    -1,   152,    26,   152,    -1,   152,    27,    -1,   152,
      28,   154,    -1,   152,    21,   152,    -1,   152,    15,   152,
      -1,   152,    20,   152,    -1,   152,    19,   152,    -1,   152,
      18,   152,    -1,   152,    14,   152,    -1,   152,    13,   152,
      -1,   152,    11,   152,    -1,   152,    10,   152,    -1,   152,
      12,   152,    -1,   152,     9,   152,    -1,   152,    30,   152,
      -1,   152,    80,   156,    81,    -1,   152,    84,   133,    85,
      -1,   153,    -1,    73,    -1,    74,    -1,    17,    73,    -1,
      17,    74,    -1,    16,    73,    -1,    16,    74,    -1,    76,
      -1,    77,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1,    17,    -1,    16,    -1,    24,    -1,    23,    -1,    22,
      -1,    26,    -1,    21,    -1,    15,    -1,    20,    -1,    19,
      -1,    18,    -1,    14,    -1,    13,    -1,    11,    -1,    10,
      -1,    12,    -1,     9,    -1,    48,    -1,    49,    -1,    50,
      -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,
      -1,    56,    -1,    57,    -1,    58,    -1,    25,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    72,    -1,   105,    -1,   106,
      -1,    30,    -1,   108,    -1,   109,    -1,    84,    85,    -1,
      84,   152,    85,    -1,   154,    -1,    16,   154,    -1,    80,
     151,    81,    -1,    75,    80,   150,    81,    28,    80,   151,
      81,    -1,   103,    82,   183,    83,    -1,   167,    -1,   168,
      -1,   169,    -1,    88,    80,   159,    81,    -1,    89,    80,
     159,    81,    -1,    90,    82,   133,    83,    -1,    91,    82,
     134,    83,    -1,   170,    -1,   171,    -1,   172,    -1,   173,
      -1,   174,    -1,   175,    -1,   176,    -1,   177,    -1,   178,
      -1,   179,    -1,   161,    -1,   162,    -1,   163,    -1,   164,
      -1,   165,    -1,   166,    -1,   100,    -1,   100,    -1,   157,
      -1,   156,     7,   157,    -1,   157,     6,   157,    -1,   157,
       5,   157,    -1,   157,     4,   157,    -1,   157,     8,   157,
      -1,   152,    -1,    98,    -1,    98,    -1,    98,    -1,    99,
      -1,    92,    80,   154,     7,   157,     7,   151,    81,    -1,
      93,    80,   154,     7,   157,     7,   151,    81,    -1,    94,
      80,   154,     7,   157,     7,   151,    81,    -1,    95,    80,
     154,     7,   157,     7,   151,    81,    -1,    96,    80,   151,
      81,    -1,    97,    80,   151,    81,    -1,    35,    80,   180,
       7,   160,     7,   158,    81,    -1,    36,    80,   185,   155,
       7,   160,    81,    -1,    37,    80,   185,   155,     7,   160,
      81,    -1,    38,    80,   159,    81,    -1,    39,    80,   159,
      81,    -1,    40,    80,   159,     7,   157,     7,   157,     7,
     157,     7,   157,    81,    -1,    41,    80,   159,     7,   157,
       7,   157,     7,   157,     7,   157,    81,    -1,    42,    80,
     159,     7,   157,     7,   157,     7,   157,     7,   157,    81,
      -1,    43,    80,   159,     7,   151,    81,    -1,    44,    80,
     159,     7,   151,    81,    -1,    45,    80,   159,     7,   151,
      81,    -1,    47,    80,   159,     7,   157,     7,   157,    81,
      -1,    46,    80,   159,     7,   157,     7,   157,    81,    -1,
     185,   181,    80,   182,    81,    -1,   185,   181,    15,   181,
      80,   182,    81,    -1,   185,   181,    15,   181,    15,   181,
      80,   182,    81,    -1,   185,   181,    80,    81,    -1,   185,
     181,    15,   181,    80,    81,    -1,   185,   181,    15,   181,
      15,   181,    80,    81,    -1,   100,    -1,   185,    -1,   182,
       7,   185,    -1,   184,    -1,   183,   184,    -1,    80,   156,
      81,   104,   151,    78,    -1,    33,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   320,   321,   323,   324,   331,   332,   335,
     336,   337,   338,   339,   340,   344,   345,   346,   347,   350,
     351,   354,   355,   356,   357,   358,   359,   362,   363,   366,
     369,   372,   375,   378,   379,   382,   383,   384,   387,   388,
     391,   394,   395,   396,   399,   402,   403,   406,   407,   408,
     409,   410,   411,   412,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   425,   426,   427,   429,   430,   432,   433,
     434,   435,   436,   437,   439,   441,   442,   444,   447,   448,
     450,   451,   453,   454,   456,   457,   459,   460,   462,   463,
     465,   466,   467,   468,   469,   470,   472,   473,   474,   476,
     477,   479,   480,   481,   482,   483,   484,   486,   488,   489,
     490,   491,   492,   493,   494,   496,   497,   498,   499,   500,
     501,   503,   504,   505,   507,   508,   510,   511,   512,   515,
     516,   518,   519,   521,   522,   523,   525,   526,   528,   529,
     531,   532,   534,   535,   538,   540,   541,   542,   543,   544,
     545,   546,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   559,   560,   561,   562,   564,   565,   570,   573,
     578,   579,   582,   583,   584,   585,   586,   589,   592,   595,
     596,   601,   605,   609,   613,   618,   621,   628,   632,   635,
     640,   643,   646,   649,   652,   655,   658,   661,   665,   668,
     675,   676,   677,   679,   680,   681,   684,   687,   688,   691,
     692,   695,   699,   700
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "MIX", "SPLIT", "SEQ", "PAR",
  "REC", "NE", "GE", "GT", "EQ", "LE", "LT", "OR", "SUB", "ADD", "RSH",
  "LSH", "XOR", "AND", "MOD", "DIV", "MUL", "POWOP", "FDELAY", "DELAY1",
  "DOT", "APPL", "HASH", "MEM", "PREFIX", "INTCAST", "FLOATCAST",
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
  "rule", "type", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   168,     0,    19,     4,
      17,     0,    44,    43,     0,   169,     0,    27,     0,     0,
     178,     0,   177,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   106,   104,   103,
     105,   102,   101,    97,    91,    90,   100,    99,    98,    96,
      94,    93,    92,   118,    95,   135,    86,    87,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,    78,    79,
       0,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   134,   136,   137,
     176,    77,   140,     0,   170,   162,   163,   164,   165,   166,
     167,   145,   146,   147,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     0,    53,     0,    16,     0,     0,
       0,     0,    28,    82,    83,   141,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    15,    29,    30,    32,     0,     0,     0,    34,
      40,   212,   213,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,   142,
     139,     0,     0,     0,     0,     0,     9,    10,     0,     7,
       0,     0,     0,     0,     0,     0,     0,     0,   209,    73,
      71,    70,    72,    69,    68,    64,    55,    54,    67,    66,
      65,    63,    58,    57,    56,    59,    60,    62,    74,     0,
       0,   171,     0,   174,   173,   172,   175,     5,    51,    50,
      49,    48,    52,     0,     0,     0,     0,   206,     0,     0,
       0,   190,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   149,   150,     6,    13,    14,    11,
      12,     0,   151,     0,     0,     0,     0,   185,   186,     0,
     144,   210,    75,    76,     0,     0,     0,     0,     0,   179,
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   253,   258,   259,     9,    17,    30,    31,
      32,    33,    34,    35,   150,   229,   376,    36,   326,    11,
     247,   144,   120,   121,   122,    16,   123,   124,    23,    21,
     351,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     233,   308,   382,   267,   268,   383
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -340
static const yytype_int16 yypact[] =
{
    -340,    26,     4,  -340,    15,   134,  -340,    27,  -340,  -340,
    -340,     3,  -340,  -340,   111,  -340,   125,   225,   494,   494,
    -340,    49,  -340,    67,  -340,   494,   494,  -340,    27,  -340,
    -340,   141,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,    50,    28,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     195,   209,   216,   224,   232,   251,   254,   255,   258,   260,
     262,   268,   273,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     276,  -340,  -340,   494,   393,   277,   287,   272,   299,   294,
     304,   305,   312,   313,   314,   301,  -340,  -340,  -340,  -340,
     617,  -340,  -340,    85,   571,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,   274,   617,   228,  -340,    12,     6,
     198,   352,  -340,  -340,  -340,  -340,  -340,  -340,    84,    84,
      84,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   295,    32,  -340,   595,   111,   111,  -340,   292,   295,
     295,   295,   295,   494,   494,   340,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,  -340,   295,   494,   494,  -340,   494,
     335,   494,   494,   494,   494,   390,   494,   494,   494,   494,
     494,  -340,  -340,  -340,  -340,  -340,   346,   347,   348,  -340,
    -340,  -340,  -340,   415,   379,    27,    27,   399,   410,   485,
     487,   488,   490,   493,   514,   515,   516,   108,  -340,  -340,
    -340,   491,   492,    20,   153,   170,  -340,  -340,    17,  -340,
     573,   574,   585,   586,    38,    45,   494,   162,  -340,   640,
     640,   640,   640,   640,   640,   663,   663,   663,   275,   275,
     275,   275,   275,   275,   275,   265,   302,  -340,   179,   109,
      22,   571,   494,   571,   571,   261,  -340,  -340,   356,   356,
     102,   303,  -340,   466,   467,   469,   218,  -340,   116,   594,
     639,  -340,  -340,   494,   494,   494,   494,   494,   494,   494,
     494,   295,   596,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,   292,  -340,   494,   494,   494,   494,  -340,  -340,   129,
    -340,  -340,  -340,  -340,   280,    29,   203,   203,   203,  -340,
    -340,   647,   379,    47,   218,   218,   365,   383,   721,    51,
      57,    65,   726,   731,  -340,   589,  -340,   744,   749,   754,
     759,   567,  -340,  -340,  -340,  -340,   543,   544,   545,   125,
     210,  -340,   130,  -340,   597,   611,   494,   494,   494,  -340,
    -340,  -340,   494,   494,   494,   494,   494,   494,   494,   494,
    -340,  -340,  -340,   613,   379,    61,    84,  -340,  -340,  -340,
     764,   769,   774,    82,   143,    71,   154,   226,   233,   247,
     645,  -340,   615,  -340,   136,  -340,   494,   494,   494,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,    63,  -340,   779,
     784,   789,  -340,   181,   494,   494,   494,  -340,   187,   252,
     266,  -340,  -340,  -340
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -340,  -340,  -340,  -186,  -340,   345,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,   -26,  -340,   675,  -340,
    -340,     2,   -19,  -340,    23,   -20,  -125,  -180,   317,   541,
      -4,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -305,  -339,  -340,   431,  -157
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     145,   234,   235,   236,    -2,     4,   145,   145,   151,   215,
     216,   217,   218,   219,   220,   215,   216,   217,   218,   219,
     220,     4,   290,     4,   331,    12,     3,   148,   149,   291,
       4,   293,   294,   295,   296,   215,   216,   217,   218,   219,
     220,   215,   216,   217,   218,   219,   220,   380,   215,   216,
     217,   218,   219,   220,   215,   216,   217,   218,   219,   220,
     215,   216,   217,   218,   219,   220,   424,   155,   215,   216,
     217,   218,   219,   220,   215,   216,   217,   218,   219,   220,
     231,   232,   289,    18,   145,   174,   211,   212,   213,    19,
     214,     5,   209,    13,   231,   232,   231,   232,   443,   422,
     332,   156,   157,   325,     6,   172,     7,   343,   218,   219,
     220,   345,   373,   249,     8,   321,   209,   231,   232,   337,
       6,   224,     6,   153,   154,   223,   338,    15,   381,     6,
     146,   352,   389,   356,   357,   358,   209,   406,   390,   362,
     363,   339,   423,   406,   442,   147,   391,   211,   212,   213,
       6,   214,   431,   367,   368,   369,   370,   215,   216,   217,
     218,   219,   220,   429,   145,   145,   210,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   264,   265,   288,   406,   322,
     342,   211,   212,   213,   248,   214,   353,   145,   145,   145,
     145,   145,   260,   261,   262,   263,   410,   411,   412,    20,
     371,   407,   413,   414,    14,   309,   310,   438,   298,   299,
     300,   301,   302,    22,   430,   404,   327,   328,   287,   215,
     216,   217,   218,   219,   220,   432,   215,   216,   217,   218,
     219,   220,   266,   329,   330,   340,   439,   440,   441,   425,
     215,   216,   217,   218,   219,   220,   211,   212,   213,   207,
     214,   152,   447,   208,   448,   449,   450,   213,   451,   214,
     211,   212,   213,   145,   214,   158,    12,   215,   216,   217,
     218,   219,   220,   215,   216,   217,   218,   219,   220,   159,
     405,   203,   204,   205,   344,   206,   160,   145,   145,   145,
     202,   203,   204,   205,   161,   206,   222,   433,   254,   255,
     219,   220,   162,    12,   434,   225,   349,   350,   359,   360,
     361,   377,   378,   226,   227,   228,   374,   375,   435,   204,
     205,   163,   206,   452,   164,   165,    24,    25,   166,    26,
     167,    27,   168,    28,   364,   207,    29,   453,   169,   208,
     384,   385,   221,   170,   177,   207,   171,   175,   372,   208,
     216,   217,   218,   219,   220,   256,   257,   176,    12,   211,
     212,   213,   386,   214,   179,   145,   145,   145,   145,   145,
     145,   178,   207,   185,   180,   181,   208,   211,   212,   213,
     387,   214,   182,   183,   184,     6,   415,   416,   417,   418,
     419,   420,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     266,   292,   306,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   230,   297,   103,   303,   304,   305,   104,   173,   307,
     311,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   312,   313,     6,   314,   315,   115,   316,   116,   117,
     317,   118,   119,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   318,   319,   320,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   323,   324,   103,   211,   212,   213,   104,   214,
     333,   334,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   335,   336,     6,   346,   347,   115,   348,   116,
     117,   354,   118,   119,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   365,   206,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   355,   206,   215,   216,
     217,   218,   219,   220,   379,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   394,
     206,   399,   400,   401,   402,   207,   366,    10,   408,   208,
     250,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   409,   206,   421,   437,   403,   207,   341,     0,
       0,   208,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,     0,     0,     0,     0,   251,   252,     0,     0,
     207,     0,     0,   436,   208,   211,   212,   213,   388,   214,
     211,   212,   213,   392,   214,   211,   212,   213,   393,   214,
       0,     0,     0,   207,     0,     0,     0,   208,   211,   212,
     213,   395,   214,   211,   212,   213,   396,   214,   211,   212,
     213,   397,   214,   211,   212,   213,   398,   214,   211,   212,
     213,   426,   214,   211,   212,   213,   427,   214,   211,   212,
     213,   428,   214,   211,   212,   213,   444,   214,   211,   212,
     213,   445,   214,   211,   212,   213,   446,   214
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-340)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      19,   158,   159,   160,     0,     1,    25,    26,    28,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,     1,   208,     1,     7,     2,     0,    25,    26,   209,
       1,   211,   212,   213,   214,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,   352,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,   405,    44,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
      33,    34,   207,    80,   103,   104,     4,     5,     6,    86,
       8,    87,     7,    78,    33,    34,    33,    34,   437,   404,
      83,    73,    74,    83,   100,   103,   102,    85,     6,     7,
       8,   297,    83,    81,   110,     7,     7,    33,    34,    81,
     100,   115,   100,    73,    74,   113,    81,   100,    81,   100,
      81,    15,    81,   313,   314,   315,     7,     7,    81,   319,
     320,   266,    81,     7,    81,    78,    81,     4,     5,     6,
     100,     8,    81,   333,   334,   335,   336,     3,     4,     5,
       6,     7,     8,    81,   183,   184,    81,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   183,   184,   206,     7,    81,
      81,     4,     5,     6,   171,     8,    80,   216,   217,   218,
     219,   220,   179,   180,   181,   182,   386,   387,   388,    98,
      81,    81,   392,   393,    80,   235,   236,    81,   216,   217,
     218,   219,   220,    98,    81,    15,    73,    74,   205,     3,
       4,     5,     6,     7,     8,    81,     3,     4,     5,     6,
       7,     8,    80,    73,    74,    83,   426,   427,   428,   406,
       3,     4,     5,     6,     7,     8,     4,     5,     6,    80,
       8,   120,    81,    84,   444,   445,   446,     6,    81,     8,
       4,     5,     6,   292,     8,    80,   253,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,    80,
      80,    26,    27,    28,   292,    30,    80,   316,   317,   318,
      25,    26,    27,    28,    80,    30,    78,    81,    16,    17,
       7,     8,    80,   290,    81,   117,    98,    99,   316,   317,
     318,   347,   348,   125,   126,   127,   123,   124,    81,    27,
      28,    80,    30,    81,    80,    80,   111,   112,    80,   114,
      80,   116,    80,   118,   321,    80,   121,    81,    80,    84,
     354,   355,    78,    80,    82,    80,    80,    80,    78,    84,
       4,     5,     6,     7,     8,    73,    74,    80,   345,     4,
       5,     6,     7,     8,    80,   394,   395,   396,   397,   398,
     399,    82,    80,    82,    80,    80,    84,     4,     5,     6,
       7,     8,    80,    80,    80,   100,   394,   395,   396,   397,
     398,   399,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      80,    86,     7,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,   119,    82,    80,   128,   128,   128,    84,    85,   100,
      81,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    81,     7,   100,     7,     7,   103,     7,   105,   106,
       7,   108,   109,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     7,     7,     7,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    81,    81,    80,     4,     5,     6,    84,     8,
       7,     7,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     7,     7,   100,   129,   129,   103,   129,   105,
     106,     7,   108,   109,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    28,    30,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     7,    30,     3,     4,
       5,     6,     7,     8,     7,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    80,
      30,   104,   129,   129,   129,    80,   331,     2,    81,    84,
      85,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    81,    30,    81,    80,   379,    80,   267,    -1,
      -1,    84,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,    -1,    -1,    -1,    -1,   175,   176,    -1,    -1,
      80,    -1,    -1,    78,    84,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    84,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8
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
     144,   155,   120,    73,    74,   154,    73,    74,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,   151,    85,   152,    80,    80,    82,    82,    80,
      80,    80,    80,    80,    80,    82,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    30,    80,    84,     7,
      81,     4,     5,     6,     8,     3,     4,     5,     6,     7,
       8,    78,    78,   113,   115,   117,   125,   126,   127,   145,
     119,    33,    34,   180,   185,   185,   185,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   150,   154,    81,
      85,   159,   159,   133,    16,    17,    73,    74,   134,   135,
     154,   154,   154,   154,   151,   151,    80,   183,   184,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   154,   152,   156,
     133,   157,    86,   157,   157,   157,   157,    82,   151,   151,
     151,   151,   151,   128,   128,   128,     7,   100,   181,   155,
     155,    81,    81,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    81,    81,    81,    83,   148,    73,    74,    73,
      74,     7,    83,     7,     7,     7,     7,    81,    81,   156,
      83,   184,    81,    85,   151,   133,   129,   129,   129,    98,
      99,   160,    15,    80,     7,     7,   157,   157,   157,   151,
     151,   151,   157,   157,   154,    28,   135,   157,   157,   157,
     157,    81,    78,    83,   123,   124,   146,   146,   146,     7,
     181,    81,   182,   185,   160,   160,     7,     7,     7,    81,
      81,    81,     7,     7,    80,     7,     7,     7,     7,   104,
     129,   129,   129,   158,    15,    80,     7,    81,    81,    81,
     157,   157,   157,   157,   157,   151,   151,   151,   151,   151,
     151,    81,   181,    81,   182,   185,     7,     7,     7,    81,
      81,    81,    81,    81,    81,    81,    78,    80,    81,   157,
     157,   157,    81,   182,     7,     7,     7,    81,   157,   157,
     157,    81,    81,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1787 of yacc.c  */
#line 317 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 320 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 321 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 323 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 324 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 331 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 332 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 335 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 336 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 337 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 338 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 339 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 340 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 344 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 345 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 346 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 347 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 350 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 351 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 354 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 355 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 356 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 357 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 358 "parser/faustparser.y"
    { (yyval.exp) = docLst(); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 359 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 362 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 363 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 366 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 369 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 372 "parser/faustparser.y"
    { }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 375 "parser/faustparser.y"
    { }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 378 "parser/faustparser.y"
    { }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 379 "parser/faustparser.y"
    { }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 382 "parser/faustparser.y"
    { gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 383 "parser/faustparser.y"
    { gStripDocSwitch = (yyvsp[(4) - (5)].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 384 "parser/faustparser.y"
    { gLstDistributedSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 387 "parser/faustparser.y"
    { (yyval.b) = true; }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 388 "parser/faustparser.y"
    { (yyval.b) = false; }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 391 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 394 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 395 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 396 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 399 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 402 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 403 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 406 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 408 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 409 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 410 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 411 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 412 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 415 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 416 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 417 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 418 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 419 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 420 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 421 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 423 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 425 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 426 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 427 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 429 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 430 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 432 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 433 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 435 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 436 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigConcat)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 441 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 442 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 444 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 447 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 448 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 450 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 453 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 454 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 456 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 457 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 459 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 460 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 462 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 463 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 465 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 466 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 467 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 468 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 469 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 470 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 472 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 473 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 474 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 476 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 477 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 479 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 480 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 481 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 482 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 483 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 484 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 486 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 488 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 489 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 490 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 491 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 492 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 493 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 494 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 496 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 497 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 498 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 499 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 500 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 501 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 503 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 504 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 505 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 507 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 508 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 510 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 511 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 512 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 515 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 516 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 518 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 519 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 521 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorize); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 522 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigSerialize); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 523 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigConcat); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 525 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigUpSample); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 526 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDownSample); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 528 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorAt); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 529 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxWire(),(yyvsp[(2) - (3)].exp)),boxPrim2(sigVectorAt)); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 531 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 532 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 534 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 536 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 538 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 540 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 541 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 542 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 543 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 544 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 545 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 546 "parser/faustparser.y"
    { (yyval.exp) = boxWaveform(reverse((yyvsp[(3) - (4)].exp))); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 548 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 549 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 550 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 551 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 552 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 553 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 554 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 555 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 556 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 557 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 559 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 560 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 561 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 562 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 564 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 565 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 570 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 573 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 578 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 579 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 582 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 583 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 584 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 585 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 586 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 589 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 592 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 595 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 596 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 602 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 606 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 610 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 614 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 618 "parser/faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 621 "parser/faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 629 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 633 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 636 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 640 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 643 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 647 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 650 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 653 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 656 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 659 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 662 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 666 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 669 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 675 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),nil))), (yyvsp[(4) - (5)].exp))); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 676 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp), cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),nil))), (yyvsp[(6) - (7)].exp))); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 677 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp), cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),nil))), (yyvsp[(8) - (9)].exp))); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 679 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),nil))), nil)); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 680 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp), cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),nil))), nil)); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 681 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp), cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),nil))), nil)); }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 684 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 687 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 688 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 691 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 692 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 696 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 699 "parser/faustparser.y"
    { (yyval.exp) = tree(0); }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 700 "parser/faustparser.y"
    { (yyval.exp) = tree(1); }
    break;


/* Line 1787 of yacc.c  */
#line 3305 "parser/faustparser.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 703 "parser/faustparser.y"


