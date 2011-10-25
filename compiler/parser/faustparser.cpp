
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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



/* Line 189 of yacc.c  */
#line 146 "parser/faustparser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
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
     IPAR = 346,
     ISEQ = 347,
     ISUM = 348,
     IPROD = 349,
     STRING = 350,
     FSTRING = 351,
     IDENT = 352,
     EXTRA = 353,
     DECLARE = 354,
     CASE = 355,
     ARROW = 356,
     VECTORIZE = 357,
     SERIALIZE = 358,
     RATE = 359,
     UPSAMPLE = 360,
     DOWNSAMPLE = 361,
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 78 "parser/faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;



/* Line 214 of yacc.c  */
#line 317 "parser/faustparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 329 "parser/faustparser.cpp"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   754

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  417

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

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
     125,   126
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    13,    19,    24,
      26,    30,    31,    34,    36,    38,    40,    42,    44,    46,
      47,    50,    54,    58,    60,    64,    65,    68,    74,    80,
      86,    88,    90,    94,   102,   107,   110,   112,   114,   118,
     124,   128,   132,   136,   140,   144,   146,   150,   154,   158,
     162,   166,   170,   174,   177,   181,   185,   189,   193,   197,
     201,   205,   209,   213,   217,   221,   225,   229,   234,   239,
     241,   243,   245,   248,   251,   254,   257,   259,   261,   263,
     265,   267,   269,   271,   273,   275,   277,   279,   281,   283,
     285,   287,   289,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   321,   323,
     325,   327,   329,   331,   333,   335,   337,   339,   341,   343,
     345,   347,   349,   351,   353,   355,   357,   359,   361,   363,
     365,   368,   372,   374,   377,   381,   390,   395,   397,   399,
     401,   406,   411,   416,   418,   420,   422,   424,   426,   428,
     430,   432,   434,   436,   438,   440,   442,   444,   446,   448,
     450,   454,   458,   462,   466,   470,   472,   474,   476,   478,
     480,   489,   498,   507,   516,   525,   533,   541,   546,   551,
     564,   577,   590,   597,   604,   611,   620,   629,   635,   640,
     642,   644,   648,   650,   653,   660,   662
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     128,     0,    -1,   129,    -1,    -1,   129,   131,    -1,    -1,
     130,   143,    -1,    87,    80,   154,    81,    78,    -1,    99,
     150,   153,    78,    -1,   143,    -1,   107,   132,   108,    -1,
      -1,   132,   133,    -1,   134,    -1,   135,    -1,   136,    -1,
     137,    -1,   138,    -1,   142,    -1,    -1,   134,   117,    -1,
     109,   146,   110,    -1,   111,   146,   112,    -1,   118,    -1,
     113,   139,   114,    -1,    -1,   139,   140,    -1,   122,   125,
     126,   141,   126,    -1,   123,   125,   126,   141,   126,    -1,
     124,   125,   126,   141,   126,    -1,   120,    -1,   121,    -1,
     115,   150,   116,    -1,   144,    80,   151,    81,    86,   146,
      78,    -1,   144,    86,   146,    78,    -1,     1,    78,    -1,
     149,    -1,   149,    -1,   145,     7,   149,    -1,   146,     3,
      82,   130,    83,    -1,   146,     7,   146,    -1,   146,     6,
     146,    -1,   146,     5,   146,    -1,   146,     4,   146,    -1,
     146,     8,   146,    -1,   147,    -1,   147,    17,   147,    -1,
     147,    16,   147,    -1,   147,    24,   147,    -1,   147,    23,
     147,    -1,   147,    22,   147,    -1,   147,    25,   147,    -1,
     147,    26,   147,    -1,   147,    27,    -1,   147,    28,   149,
      -1,   147,    21,   147,    -1,   147,    15,   147,    -1,   147,
      20,   147,    -1,   147,    19,   147,    -1,   147,    18,   147,
      -1,   147,    14,   147,    -1,   147,    13,   147,    -1,   147,
      11,   147,    -1,   147,    10,   147,    -1,   147,    12,   147,
      -1,   147,     9,   147,    -1,   147,    30,   147,    -1,   147,
      80,   151,    81,    -1,   147,    84,   130,    85,    -1,   148,
      -1,    73,    -1,    74,    -1,    17,    73,    -1,    17,    74,
      -1,    16,    73,    -1,    16,    74,    -1,    76,    -1,    77,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    17,
      -1,    16,    -1,    24,    -1,    23,    -1,    22,    -1,    26,
      -1,    21,    -1,    15,    -1,    20,    -1,    19,    -1,    18,
      -1,    14,    -1,    13,    -1,    11,    -1,    10,    -1,    12,
      -1,     9,    -1,    48,    -1,    49,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,
      -1,    57,    -1,    58,    -1,    25,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,
      -1,    71,    -1,    72,    -1,   102,    -1,   103,    -1,    30,
      -1,   105,    -1,   106,    -1,    84,    85,    -1,    84,   147,
      85,    -1,   149,    -1,    16,   149,    -1,    80,   146,    81,
      -1,    75,    80,   145,    81,    28,    80,   146,    81,    -1,
     100,    82,   176,    83,    -1,   160,    -1,   161,    -1,   162,
      -1,    88,    80,   154,    81,    -1,    89,    80,   154,    81,
      -1,    90,    82,   130,    83,    -1,   163,    -1,   164,    -1,
     165,    -1,   166,    -1,   167,    -1,   168,    -1,   169,    -1,
     170,    -1,   171,    -1,   172,    -1,   156,    -1,   157,    -1,
     158,    -1,   159,    -1,    97,    -1,    97,    -1,   152,    -1,
     151,     7,   152,    -1,   152,     6,   152,    -1,   152,     5,
     152,    -1,   152,     4,   152,    -1,   152,     8,   152,    -1,
     147,    -1,    95,    -1,    95,    -1,    95,    -1,    96,    -1,
      91,    80,   149,     7,   152,     7,   146,    81,    -1,    92,
      80,   149,     7,   152,     7,   146,    81,    -1,    93,    80,
     149,     7,   152,     7,   146,    81,    -1,    94,    80,   149,
       7,   152,     7,   146,    81,    -1,    35,    80,   173,     7,
     155,     7,   153,    81,    -1,    36,    80,   178,   150,     7,
     155,    81,    -1,    37,    80,   178,   150,     7,   155,    81,
      -1,    38,    80,   154,    81,    -1,    39,    80,   154,    81,
      -1,    40,    80,   154,     7,   152,     7,   152,     7,   152,
       7,   152,    81,    -1,    41,    80,   154,     7,   152,     7,
     152,     7,   152,     7,   152,    81,    -1,    42,    80,   154,
       7,   152,     7,   152,     7,   152,     7,   152,    81,    -1,
      43,    80,   154,     7,   146,    81,    -1,    44,    80,   154,
       7,   146,    81,    -1,    45,    80,   154,     7,   146,    81,
      -1,    47,    80,   154,     7,   152,     7,   152,    81,    -1,
      46,    80,   154,     7,   152,     7,   152,    81,    -1,   178,
     174,    80,   175,    81,    -1,   178,   174,    80,    81,    -1,
      97,    -1,   178,    -1,   175,     7,   178,    -1,   177,    -1,
     176,   177,    -1,    80,   151,    81,   101,   146,    78,    -1,
      33,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   308,   308,   311,   312,   314,   315,   318,   319,   320,
     321,   324,   325,   328,   329,   330,   331,   332,   333,   336,
     337,   340,   343,   346,   349,   352,   353,   356,   357,   358,
     361,   362,   365,   368,   369,   370,   373,   376,   377,   380,
     381,   382,   383,   384,   385,   386,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   399,   400,   401,   403,   404,
     406,   407,   408,   409,   410,   411,   413,   415,   416,   418,
     421,   422,   424,   425,   427,   428,   430,   431,   433,   434,
     436,   437,   439,   440,   441,   442,   443,   444,   446,   447,
     448,   450,   451,   453,   454,   455,   456,   457,   458,   460,
     462,   463,   464,   465,   466,   467,   468,   470,   471,   472,
     473,   474,   475,   477,   478,   479,   481,   482,   484,   485,
     486,   489,   490,   492,   493,   495,   496,   497,   499,   500,
     502,   503,   505,   506,   508,   509,   512,   514,   515,   516,
     517,   518,   519,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   532,   533,   534,   535,   539,   542,   547,
     548,   551,   552,   553,   554,   555,   558,   561,   564,   565,
     570,   574,   578,   582,   589,   593,   596,   601,   604,   607,
     610,   613,   616,   619,   622,   626,   629,   635,   636,   639,
     642,   643,   646,   647,   650,   654,   655
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "IPAR", "ISEQ", "ISUM",
  "IPROD", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "VECTORIZE", "SERIALIZE", "RATE", "UPSAMPLE", "DOWNSAMPLE",
  "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST",
  "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE",
  "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ",
  "LSTQ", "$accept", "program", "stmtlist", "deflist", "statement", "doc",
  "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "definition",
  "defname", "params", "expression", "infixexp", "primitive", "ident",
  "name", "arglist", "argument", "string", "uqstring", "fstring", "fpar",
  "fseq", "fsum", "fprod", "ffunction", "fconst", "fvariable", "button",
  "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
  "vbargraph", "hbargraph", "signature", "fun", "typelist", "rulelist",
  "rule", "type", 0
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
     375,   376,   377,   378,   379,   380,   381
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   127,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   132,   132,   133,   133,   133,   133,   133,   133,   134,
     134,   135,   136,   137,   138,   139,   139,   140,   140,   140,
     141,   141,   142,   143,   143,   143,   144,   145,   145,   146,
     146,   146,   146,   146,   146,   146,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   149,   150,   151,
     151,   152,   152,   152,   152,   152,   153,   154,   155,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   173,   174,
     175,   175,   176,   176,   177,   178,   178
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     5,     4,     1,
       3,     0,     2,     1,     1,     1,     1,     1,     1,     0,
       2,     3,     3,     1,     3,     0,     2,     5,     5,     5,
       1,     1,     3,     7,     4,     2,     1,     1,     3,     5,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     2,     3,     8,     4,     1,     1,     1,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       8,     8,     8,     8,     8,     7,     7,     4,     4,    12,
      12,    12,     6,     6,     6,     8,     8,     5,     4,     1,
       1,     3,     1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   157,     0,    11,     4,
       9,     0,    36,    35,     0,   158,     0,    19,     0,     0,
     167,     0,   166,     0,    10,     0,     0,    25,     0,    23,
      12,    13,    14,    15,    16,    17,    18,    98,    96,    95,
      97,    94,    93,    89,    83,    82,    92,    91,    90,    88,
      86,    85,    84,   110,    87,   127,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,    70,    71,
       0,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   128,   129,   165,    69,   132,
       0,   159,   153,   154,   155,   156,   137,   138,   139,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
      45,     0,     8,     0,     0,     0,     0,    20,    74,    75,
     133,    72,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     7,    21,    22,    24,     0,     0,
       0,    26,    32,   195,   196,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,   134,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   192,    65,    63,    62,    64,    61,    60,    56,
      47,    46,    59,    58,    57,    55,    50,    49,    48,    51,
      52,    54,    66,     0,     0,   160,     0,   163,   162,   161,
     164,     5,    43,    42,    41,    40,    44,     0,     0,     0,
       0,   189,     0,     0,     0,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   140,   141,   142,
       6,     0,     0,     0,     0,     0,   136,   193,    67,    68,
       0,     0,     0,     0,     0,   168,   169,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,    33,    39,    30,    31,
       0,     0,     0,     0,   188,     0,   190,     0,     0,     0,
       0,     0,   182,   183,   184,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    28,    29,     0,     0,   187,   175,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,   191,     0,     0,     0,   186,   185,   135,
     170,   171,   172,   173,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,   180,   181
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   245,     9,    17,    30,    31,    32,    33,
      34,    35,   145,   221,   350,    36,   310,    11,   239,   139,
     117,   118,   119,    16,   120,   121,    23,    21,   327,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   225,   292,   355,   251,
     252,   226
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -180
static const yytype_int16 yypact[] =
{
    -180,    24,     8,  -180,   -67,   -42,  -180,    -4,  -180,  -180,
    -180,   -43,  -180,  -180,     5,  -180,    29,   183,   450,   450,
    -180,    46,  -180,    54,  -180,   450,   450,  -180,    -4,  -180,
    -180,    26,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   -15,    44,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
      60,    98,   100,   114,   145,   155,   166,   171,   173,   179,
     200,   205,   206,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
     210,  -180,  -180,   450,   352,   213,   215,   217,   220,   222,
     223,   236,   235,  -180,  -180,  -180,  -180,   570,  -180,  -180,
      13,   306,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,   262,
     570,   240,  -180,    27,    11,    25,   207,  -180,  -180,  -180,
    -180,  -180,  -180,    97,    97,    97,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,   224,    41,  -180,   548,
       5,     5,  -180,   224,   224,   224,   224,   242,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,  -180,   224,   450,   450,
    -180,   450,   233,   450,   450,   450,   450,   257,   450,   450,
     450,   450,   450,  -180,  -180,  -180,  -180,  -180,   199,   218,
     255,  -180,  -180,  -180,  -180,   331,   245,    -4,    -4,   260,
     264,   340,   374,   423,   424,   426,   427,   428,   431,    15,
    -180,  -180,  -180,   358,   366,     4,   441,   443,   444,   446,
     450,   -44,  -180,   586,   586,   586,   586,   586,   586,   599,
     599,   599,   609,   609,   609,   609,   609,   609,   609,   614,
      61,  -180,    62,    22,     1,   306,   450,   306,   306,    91,
    -180,  -180,   203,   203,    73,   150,  -180,   330,   351,   353,
      89,  -180,   398,   521,   522,  -180,  -180,   450,   450,   450,
     450,   450,   450,   450,   450,   224,   503,  -180,  -180,  -180,
    -180,   450,   450,   450,   450,    33,  -180,  -180,  -180,  -180,
     268,     9,   107,   107,   107,  -180,  -180,   525,    23,    89,
      89,   322,   328,   641,    47,    57,    63,   651,   656,  -180,
     453,   667,   680,   711,   716,   434,  -180,  -180,  -180,  -180,
     410,   411,   419,    29,  -180,    35,  -180,   465,   467,   450,
     450,   450,  -180,  -180,  -180,   450,   450,   450,   450,   450,
     450,   450,   450,  -180,  -180,  -180,   468,    97,  -180,  -180,
    -180,   721,   726,   731,   198,   239,    69,   105,   148,   216,
     234,   301,  -180,  -180,   450,   450,   450,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,   736,   741,   746,   450,   450,
     450,   244,   250,   256,  -180,  -180,  -180
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,  -179,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   -90,  -180,   549,  -180,  -180,   -13,
     -19,  -180,    39,   -27,  -121,  -178,   201,   543,   -52,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
     326,  -151
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     140,   146,     4,   227,   228,     4,   140,   140,    -2,     4,
       4,    13,   143,   144,   207,   208,   209,   210,   211,   212,
     201,   274,   305,   275,     3,   277,   278,   279,   280,   201,
     207,   208,   209,   210,   211,   212,   250,    18,    14,   316,
     201,    12,   377,    19,   207,   208,   209,   210,   211,   212,
     207,   208,   209,   210,   211,   212,   223,   224,   148,   149,
     207,   208,   209,   210,   211,   212,   207,   208,   209,   210,
     211,   212,   207,   208,   209,   210,   211,   212,   273,   210,
     211,   212,     6,   150,   140,   169,   319,   309,   196,   197,
     167,   198,   347,    15,   202,     5,   306,   205,     6,   206,
      20,     6,   321,   318,   354,     6,     6,     7,   207,   208,
     209,   210,   211,   212,   345,     8,   378,   151,   152,   331,
     332,   333,   241,   216,    22,   337,   338,   141,   362,   315,
     223,   224,   142,   341,   342,   343,   344,   215,   363,   217,
     153,   199,   199,   147,   364,   200,   200,   218,   219,   220,
     399,   207,   208,   209,   210,   211,   212,   211,   212,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   356,   154,   272,
     155,   381,   382,   383,   325,   326,   400,   384,   385,   140,
     140,   140,   140,   140,   156,   282,   283,   284,   285,   286,
     293,   294,   203,   204,   205,   240,   206,   208,   209,   210,
     211,   212,   246,   247,   248,   249,   405,   406,   407,   207,
     208,   209,   210,   211,   212,   157,   393,   348,   349,   401,
     411,   412,   413,   351,   352,   158,   271,   207,   208,   209,
     210,   211,   212,   203,   204,   205,   159,   206,   203,   204,
     205,   160,   206,   161,   203,   204,   205,   140,   206,   162,
     203,   204,   205,   320,   206,   207,   208,   209,   210,   211,
     212,   207,   208,   209,   210,   211,   212,   357,   358,   397,
     163,   140,   140,   140,    12,   164,   165,   334,   335,   336,
     166,    24,    25,   170,    26,   171,    27,   402,    28,   172,
     173,    29,   174,   175,   207,   208,   209,   210,   211,   212,
     203,   204,   205,    12,   206,   403,   176,   177,   214,   276,
     398,     6,   250,   222,   287,   414,   203,   204,   205,   359,
     206,   415,   203,   204,   205,   360,   206,   416,   290,   281,
     213,   295,   291,   288,   339,   296,   346,   297,   140,   140,
     140,   140,   140,   140,   386,   387,   388,   389,   390,   391,
      12,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   404,
     289,   298,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     299,   300,   103,   301,   302,   303,   104,   168,   304,   307,
     105,   106,   107,   108,   109,   110,   111,   308,   311,     6,
     312,   313,   112,   314,   113,   114,   322,   115,   116,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,   323,   328,   324,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   329,   330,
     103,   340,   353,   367,   104,   372,   373,   374,   105,   106,
     107,   108,   109,   110,   111,   375,   379,     6,   380,   392,
     112,    10,   113,   114,   376,   115,   116,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   317,   198,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,     0,
     198,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,     0,   198,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   199,   198,
       0,     0,   200,   242,   194,   195,   196,   197,     0,   198,
     195,   196,   197,     0,   198,   203,   204,   205,   361,   206,
     199,     0,     0,     0,   200,   203,   204,   205,   365,   206,
     203,   204,   205,   366,   206,     0,   199,     0,     0,     0,
     200,   203,   204,   205,   368,   206,     0,     0,     0,   199,
       0,     0,     0,   200,   203,   204,   205,   369,   206,   199,
       0,     0,     0,   200,   199,     0,     0,     0,   200,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
       0,     0,     0,   243,   244,   203,   204,   205,   370,   206,
     203,   204,   205,   371,   206,   203,   204,   205,   394,   206,
     203,   204,   205,   395,   206,   203,   204,   205,   396,   206,
     203,   204,   205,   408,   206,   203,   204,   205,   409,   206,
     203,   204,   205,   410,   206
};

static const yytype_int16 yycheck[] =
{
      19,    28,     1,   154,   155,     1,    25,    26,     0,     1,
       1,    78,    25,    26,     3,     4,     5,     6,     7,     8,
       7,   200,     7,   201,     0,   203,   204,   205,   206,     7,
       3,     4,     5,     6,     7,     8,    80,    80,    80,    83,
       7,     2,     7,    86,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,    33,    34,    73,    74,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,   199,     6,
       7,     8,    97,    44,   103,   104,    85,    83,    27,    28,
     103,    30,    83,    97,    81,    87,    81,     6,    97,     8,
      95,    97,   281,    81,    81,    97,    97,    99,     3,     4,
       5,     6,     7,     8,    81,   107,    81,    73,    74,   297,
     298,   299,    81,   112,    95,   303,   304,    81,    81,   250,
      33,    34,    78,   311,   312,   313,   314,   110,    81,   114,
      80,    80,    80,   117,    81,    84,    84,   122,   123,   124,
      81,     3,     4,     5,     6,     7,     8,     7,     8,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   328,    80,   198,
      80,   359,   360,   361,    95,    96,    81,   365,   366,   208,
     209,   210,   211,   212,    80,   208,   209,   210,   211,   212,
     227,   228,     4,     5,     6,   166,     8,     4,     5,     6,
       7,     8,   173,   174,   175,   176,   394,   395,   396,     3,
       4,     5,     6,     7,     8,    80,   377,   120,   121,    81,
     408,   409,   410,   323,   324,    80,   197,     3,     4,     5,
       6,     7,     8,     4,     5,     6,    80,     8,     4,     5,
       6,    80,     8,    80,     4,     5,     6,   276,     8,    80,
       4,     5,     6,   276,     8,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,   329,   330,    81,
      80,   300,   301,   302,   245,    80,    80,   300,   301,   302,
      80,   108,   109,    80,   111,    80,   113,    81,   115,    82,
      80,   118,    80,    80,     3,     4,     5,     6,     7,     8,
       4,     5,     6,   274,     8,    81,    80,    82,    78,    86,
      81,    97,    80,   116,   125,    81,     4,     5,     6,     7,
       8,    81,     4,     5,     6,     7,     8,    81,     7,    82,
      78,    81,    97,   125,   305,    81,    78,     7,   367,   368,
     369,   370,   371,   372,   367,   368,   369,   370,   371,   372,
     321,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    78,
     125,     7,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
       7,     7,    80,     7,     7,     7,    84,    85,     7,    81,
      88,    89,    90,    91,    92,    93,    94,    81,     7,    97,
       7,     7,   100,     7,   102,   103,   126,   105,   106,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,   126,    80,   126,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     7,     7,
      80,    28,     7,    80,    84,   101,   126,   126,    88,    89,
      90,    91,    92,    93,    94,   126,    81,    97,    81,    81,
     100,     2,   102,   103,   353,   105,   106,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,   251,    30,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    80,    30,
      -1,    -1,    84,    85,    25,    26,    27,    28,    -1,    30,
      26,    27,    28,    -1,    30,     4,     5,     6,     7,     8,
      80,    -1,    -1,    -1,    84,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    -1,    80,    -1,    -1,    -1,
      84,     4,     5,     6,     7,     8,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    84,     4,     5,     6,     7,     8,    80,
      -1,    -1,    -1,    84,    80,    -1,    -1,    -1,    84,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
      -1,    -1,    -1,   170,   171,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   128,   129,     0,     1,    87,    97,    99,   107,   131,
     143,   144,   149,    78,    80,    97,   150,   132,    80,    86,
      95,   154,    95,   153,   108,   109,   111,   113,   115,   118,
     133,   134,   135,   136,   137,   138,   142,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    84,    88,    89,    90,    91,    92,
      93,    94,   100,   102,   103,   105,   106,   147,   148,   149,
     151,   152,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   146,
     147,    81,    78,   146,   146,   139,   150,   117,    73,    74,
     149,    73,    74,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,   146,    85,   147,
      80,    80,    82,    80,    80,    80,    80,    82,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    30,    80,
      84,     7,    81,     4,     5,     6,     8,     3,     4,     5,
       6,     7,     8,    78,    78,   110,   112,   114,   122,   123,
     124,   140,   116,    33,    34,   173,   178,   178,   178,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   145,
     149,    81,    85,   154,   154,   130,   149,   149,   149,   149,
      80,   176,   177,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   149,   147,   151,   130,   152,    86,   152,   152,   152,
     152,    82,   146,   146,   146,   146,   146,   125,   125,   125,
       7,    97,   174,   150,   150,    81,    81,     7,     7,     7,
       7,     7,     7,     7,     7,     7,    81,    81,    81,    83,
     143,     7,     7,     7,     7,   151,    83,   177,    81,    85,
     146,   130,   126,   126,   126,    95,    96,   155,    80,     7,
       7,   152,   152,   152,   146,   146,   146,   152,   152,   149,
      28,   152,   152,   152,   152,    81,    78,    83,   120,   121,
     141,   141,   141,     7,    81,   175,   178,   155,   155,     7,
       7,     7,    81,    81,    81,     7,     7,    80,     7,     7,
       7,     7,   101,   126,   126,   126,   153,     7,    81,    81,
      81,   152,   152,   152,   152,   152,   146,   146,   146,   146,
     146,   146,    81,   178,     7,     7,     7,    81,    81,    81,
      81,    81,    81,    81,    78,   152,   152,   152,     7,     7,
       7,   152,   152,   152,    81,    81,    81
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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

/* Line 1455 of yacc.c  */
#line 308 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 311 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 312 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 314 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 315 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 318 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 319 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 320 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 321 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 324 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 325 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 328 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 329 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 330 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 331 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 332 "parser/faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 333 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 336 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 337 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 340 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 343 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 346 "parser/faustparser.y"
    { ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 349 "parser/faustparser.y"
    { ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 352 "parser/faustparser.y"
    { ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 353 "parser/faustparser.y"
    { ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 356 "parser/faustparser.y"
    { gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 357 "parser/faustparser.y"
    { gStripDocSwitch = (yyvsp[(4) - (5)].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 358 "parser/faustparser.y"
    { gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 361 "parser/faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 362 "parser/faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 365 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 368 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 369 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 370 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 373 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 376 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 377 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 380 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 381 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 382 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 383 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 384 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 385 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 386 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 389 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 390 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 391 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 395 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 396 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 397 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 399 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 400 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 401 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 403 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 404 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 406 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 408 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 409 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 410 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 411 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 413 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigConcat)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 415 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 416 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 418 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 421 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 424 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 425 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 427 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 428 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 430 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 431 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 433 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 436 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 440 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 442 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 443 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 446 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 447 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 448 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 450 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 453 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 454 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 455 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 456 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 457 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 458 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 460 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 462 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 463 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 464 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 465 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 466 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 467 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 468 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 470 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 471 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 472 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 473 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 474 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 475 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 477 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 478 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 479 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 481 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 482 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 484 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 485 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 486 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 489 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 490 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 492 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 493 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 495 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorize); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 496 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigSerialize); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 497 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigConcat); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 499 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigUpSample); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 500 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDownSample); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 502 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorAt); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 503 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxWire(),(yyvsp[(2) - (3)].exp)),boxPrim2(sigVectorAt)); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 505 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 506 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 508 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 510 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 512 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 514 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 515 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 516 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 517 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 518 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 519 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 521 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 522 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 523 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 524 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 525 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 526 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 527 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 528 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 529 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 530 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 532 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 533 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 534 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 535 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 539 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 542 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 547 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 548 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 551 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 552 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 553 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 554 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 555 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 558 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 561 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 564 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 565 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 571 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 575 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 579 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 583 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 590 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 594 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 597 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 601 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 604 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 608 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 611 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 614 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 617 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 620 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 623 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 627 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 630 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 635 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 636 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 639 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 642 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 643 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 646 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 647 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 651 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 654 "parser/faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 655 "parser/faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3345 "parser/faustparser.cpp"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 658 "parser/faustparser.y"



