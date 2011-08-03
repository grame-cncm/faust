
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
#line 315 "parser/faustparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 327 "parser/faustparser.cpp"

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
#define YYLAST   746

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  125
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNRULES -- Number of states.  */
#define YYNSTATES  415

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   379

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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124
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
     345,   347,   349,   351,   353,   355,   357,   359,   361,   364,
     368,   370,   373,   377,   386,   391,   393,   395,   397,   402,
     407,   412,   414,   416,   418,   420,   422,   424,   426,   428,
     430,   432,   434,   436,   438,   440,   442,   444,   446,   450,
     454,   458,   462,   466,   468,   470,   472,   474,   476,   485,
     494,   503,   512,   521,   529,   537,   542,   547,   560,   573,
     586,   593,   600,   607,   616,   625,   631,   636,   638,   640,
     644,   646,   649,   656,   658
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     126,     0,    -1,   127,    -1,    -1,   127,   129,    -1,    -1,
     128,   141,    -1,    87,    80,   152,    81,    78,    -1,    99,
     148,   151,    78,    -1,   141,    -1,   105,   130,   106,    -1,
      -1,   130,   131,    -1,   132,    -1,   133,    -1,   134,    -1,
     135,    -1,   136,    -1,   140,    -1,    -1,   132,   115,    -1,
     107,   144,   108,    -1,   109,   144,   110,    -1,   116,    -1,
     111,   137,   112,    -1,    -1,   137,   138,    -1,   120,   123,
     124,   139,   124,    -1,   121,   123,   124,   139,   124,    -1,
     122,   123,   124,   139,   124,    -1,   118,    -1,   119,    -1,
     113,   148,   114,    -1,   142,    80,   149,    81,    86,   144,
      78,    -1,   142,    86,   144,    78,    -1,     1,    78,    -1,
     147,    -1,   147,    -1,   143,     7,   147,    -1,   144,     3,
      82,   128,    83,    -1,   144,     7,   144,    -1,   144,     6,
     144,    -1,   144,     5,   144,    -1,   144,     4,   144,    -1,
     144,     8,   144,    -1,   145,    -1,   145,    17,   145,    -1,
     145,    16,   145,    -1,   145,    24,   145,    -1,   145,    23,
     145,    -1,   145,    22,   145,    -1,   145,    25,   145,    -1,
     145,    26,   145,    -1,   145,    27,    -1,   145,    28,   147,
      -1,   145,    21,   145,    -1,   145,    15,   145,    -1,   145,
      20,   145,    -1,   145,    19,   145,    -1,   145,    18,   145,
      -1,   145,    14,   145,    -1,   145,    13,   145,    -1,   145,
      11,   145,    -1,   145,    10,   145,    -1,   145,    12,   145,
      -1,   145,     9,   145,    -1,   145,    30,   145,    -1,   145,
      80,   149,    81,    -1,   145,    84,   128,    85,    -1,   146,
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
      -1,    84,    85,    -1,    84,   145,    85,    -1,   147,    -1,
      16,   147,    -1,    80,   144,    81,    -1,    75,    80,   143,
      81,    28,    80,   144,    81,    -1,   100,    82,   174,    83,
      -1,   158,    -1,   159,    -1,   160,    -1,    88,    80,   152,
      81,    -1,    89,    80,   152,    81,    -1,    90,    82,   128,
      83,    -1,   161,    -1,   162,    -1,   163,    -1,   164,    -1,
     165,    -1,   166,    -1,   167,    -1,   168,    -1,   169,    -1,
     170,    -1,   154,    -1,   155,    -1,   156,    -1,   157,    -1,
      97,    -1,    97,    -1,   150,    -1,   149,     7,   150,    -1,
     150,     6,   150,    -1,   150,     5,   150,    -1,   150,     4,
     150,    -1,   150,     8,   150,    -1,   145,    -1,    95,    -1,
      95,    -1,    95,    -1,    96,    -1,    91,    80,   147,     7,
     150,     7,   144,    81,    -1,    92,    80,   147,     7,   150,
       7,   144,    81,    -1,    93,    80,   147,     7,   150,     7,
     144,    81,    -1,    94,    80,   147,     7,   150,     7,   144,
      81,    -1,    35,    80,   171,     7,   153,     7,   151,    81,
      -1,    36,    80,   176,   148,     7,   153,    81,    -1,    37,
      80,   176,   148,     7,   153,    81,    -1,    38,    80,   152,
      81,    -1,    39,    80,   152,    81,    -1,    40,    80,   152,
       7,   150,     7,   150,     7,   150,     7,   150,    81,    -1,
      41,    80,   152,     7,   150,     7,   150,     7,   150,     7,
     150,    81,    -1,    42,    80,   152,     7,   150,     7,   150,
       7,   150,     7,   150,    81,    -1,    43,    80,   152,     7,
     144,    81,    -1,    44,    80,   152,     7,   144,    81,    -1,
      45,    80,   152,     7,   144,    81,    -1,    47,    80,   152,
       7,   150,     7,   150,    81,    -1,    46,    80,   152,     7,
     150,     7,   150,    81,    -1,   176,   172,    80,   173,    81,
      -1,   176,   172,    80,    81,    -1,    97,    -1,   176,    -1,
     173,     7,   176,    -1,   175,    -1,   174,   175,    -1,    80,
     149,    81,   101,   144,    78,    -1,    33,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   306,   306,   309,   310,   312,   313,   316,   317,   318,
     319,   322,   323,   326,   327,   328,   329,   330,   331,   334,
     335,   338,   341,   344,   347,   350,   351,   354,   355,   356,
     359,   360,   363,   366,   367,   368,   371,   374,   375,   378,
     379,   380,   381,   382,   383,   384,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   397,   398,   399,   401,   402,
     404,   405,   406,   407,   408,   409,   411,   413,   414,   416,
     419,   420,   422,   423,   425,   426,   428,   429,   431,   432,
     434,   435,   437,   438,   439,   440,   441,   442,   444,   445,
     446,   448,   449,   451,   452,   453,   454,   455,   456,   458,
     460,   461,   462,   463,   464,   465,   466,   468,   469,   470,
     471,   472,   473,   475,   476,   477,   479,   480,   482,   483,
     484,   487,   488,   490,   491,   493,   494,   495,   496,   497,
     499,   500,   502,   503,   506,   508,   509,   510,   511,   512,
     513,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   526,   527,   528,   529,   533,   536,   541,   542,   545,
     546,   547,   548,   549,   552,   555,   558,   559,   564,   568,
     572,   576,   583,   587,   590,   595,   598,   601,   604,   607,
     610,   613,   616,   620,   623,   629,   630,   633,   636,   637,
     640,   641,   644,   648,   649
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
  "ARROW", "VECTORIZE", "SERIALIZE", "RATE", "BDOC", "EDOC", "BEQN",
  "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "statement", "doc", "docelem", "doctxt", "doceqn",
  "docdgm", "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval",
  "docmtd", "definition", "defname", "params", "expression", "infixexp",
  "primitive", "ident", "name", "arglist", "argument", "string",
  "uqstring", "fstring", "fpar", "fseq", "fsum", "fprod", "ffunction",
  "fconst", "fvariable", "button", "checkbox", "vslider", "hslider",
  "nentry", "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph",
  "signature", "fun", "typelist", "rulelist", "rule", "type", 0
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
     375,   376,   377,   378,   379
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   125,   126,   127,   127,   128,   128,   129,   129,   129,
     129,   130,   130,   131,   131,   131,   131,   131,   131,   132,
     132,   133,   134,   135,   136,   137,   137,   138,   138,   138,
     139,   139,   140,   141,   141,   141,   142,   143,   143,   144,
     144,   144,   144,   144,   144,   144,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   147,   148,   149,   149,   150,
     150,   150,   150,   150,   151,   152,   153,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   171,   172,   173,   173,
     174,   174,   175,   176,   176
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     2,     3,     8,     4,     1,     1,     1,     4,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     8,     8,
       8,     8,     8,     7,     7,     4,     4,    12,    12,    12,
       6,     6,     6,     8,     8,     5,     4,     1,     1,     3,
       1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   155,     0,    11,     4,
       9,     0,    36,    35,     0,   156,     0,    19,     0,     0,
     165,     0,   164,     0,    10,     0,     0,    25,     0,    23,
      12,    13,    14,    15,    16,    17,    18,    98,    96,    95,
      97,    94,    93,    89,    83,    82,    92,    91,    90,    88,
      86,    85,    84,   110,    87,   127,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,    70,    71,
       0,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   163,    69,   130,     0,   157,
     151,   152,   153,   154,   135,   136,   137,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,     0,    45,     0,
       8,     0,     0,     0,     0,    20,    74,    75,   131,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     7,    21,    22,    24,     0,     0,     0,    26,
      32,   193,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,   132,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     190,    65,    63,    62,    64,    61,    60,    56,    47,    46,
      59,    58,    57,    55,    50,    49,    48,    51,    52,    54,
      66,     0,     0,   158,     0,   161,   160,   159,   162,     5,
      43,    42,    41,    40,    44,     0,     0,     0,     0,   187,
       0,     0,     0,   175,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,     6,     0,
       0,     0,     0,     0,   134,   191,    67,    68,     0,     0,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,    33,    39,    30,    31,     0,     0,
       0,     0,   186,     0,   188,     0,     0,     0,     0,     0,
     180,   181,   182,     0,     0,     0,     0,     0,     0,     0,
       0,    27,    28,    29,     0,     0,   185,   173,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,   189,     0,     0,     0,   184,   183,   133,   168,   169,
     170,   171,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   178,   179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   243,     9,    17,    30,    31,    32,    33,
      34,    35,   143,   219,   348,    36,   308,    11,   237,   137,
     115,   116,   117,    16,   118,   119,    23,    21,   325,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   223,   290,   353,   249,
     250,   224
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -191
static const yytype_int16 yypact[] =
{
    -191,    57,     4,  -191,   -67,    63,  -191,    -9,  -191,  -191,
    -191,    34,  -191,  -191,     0,  -191,    12,   183,   445,   445,
    -191,    66,  -191,    74,  -191,   445,   445,  -191,    -9,  -191,
    -191,    -3,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,    13,    26,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
      96,   112,   119,   129,   143,   147,   153,   170,   179,   208,
     211,   213,   228,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
     229,  -191,  -191,   445,   350,   235,   241,   240,   245,   246,
     247,   255,   254,  -191,  -191,   562,  -191,  -191,    15,   312,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,   259,   562,    77,
    -191,    27,    11,    86,   111,  -191,  -191,  -191,  -191,  -191,
    -191,   150,   150,   150,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,    41,  -191,   540,     0,     0,
    -191,   215,   215,   215,   215,   258,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,  -191,   215,   445,   445,  -191,   445,
     237,   445,   445,   445,   445,   257,   445,   445,   445,   445,
     445,  -191,  -191,  -191,  -191,  -191,   205,   217,   218,  -191,
    -191,  -191,  -191,   337,   281,    -9,    -9,   264,   298,   421,
     422,   424,   425,   426,   429,   430,   438,    49,  -191,  -191,
    -191,   365,   367,     9,   442,   444,   465,   466,   445,   -41,
    -191,   578,   578,   578,   578,   578,   578,   591,   591,   591,
     601,   601,   601,   601,   601,   601,   601,   606,   230,  -191,
      31,    75,     8,   312,   445,   312,   312,   138,  -191,  -191,
     133,   133,    21,   197,  -191,   399,   400,   402,   136,  -191,
     394,   520,   521,  -191,  -191,   445,   445,   445,   445,   445,
     445,   445,   445,   215,   502,  -191,  -191,  -191,  -191,   445,
     445,   445,   445,    97,  -191,  -191,  -191,  -191,   265,    19,
     165,   165,   165,  -191,  -191,   524,    64,   136,   136,   270,
     326,   633,    47,    55,    61,   643,   648,  -191,   452,   659,
     672,   703,   708,   439,  -191,  -191,  -191,  -191,   417,   419,
     420,    12,  -191,   101,  -191,   488,   510,   445,   445,   445,
    -191,  -191,  -191,   445,   445,   445,   445,   445,   445,   445,
     445,  -191,  -191,  -191,   526,   150,  -191,  -191,  -191,   713,
     718,   723,    32,   121,    67,    73,   214,   232,   238,   299,
    -191,  -191,   445,   445,   445,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,   728,   733,   738,   445,   445,   445,   145,
     243,   248,  -191,  -191,  -191
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,  -191,  -190,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   -24,  -191,   544,  -191,  -191,   -13,
     -19,  -191,    39,   -25,  -154,  -178,   271,   537,   -27,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
     374,  -151
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     138,   225,   226,   144,    -2,     4,   138,   138,   272,     4,
       4,    13,   141,   142,   205,   206,   207,   208,   209,   210,
       4,   273,   199,   275,   276,   277,   278,   208,   209,   210,
     205,   206,   207,   208,   209,   210,   201,   202,   203,   248,
     204,    12,   314,   271,   205,   206,   207,   208,   209,   210,
     205,   206,   207,   208,   209,   210,   303,     3,   205,   206,
     207,   208,   209,   210,   205,   206,   207,   208,   209,   210,
     205,   206,   207,   208,   209,   210,   205,   206,   207,   208,
     209,   210,   199,   148,   138,   167,   146,   147,    15,   319,
     165,     5,   307,   317,   313,    20,   200,   221,   222,   149,
     150,     6,   345,     7,   199,     6,     6,    22,   375,     8,
       6,   197,   145,   395,    18,   198,     6,   329,   330,   331,
      19,   214,   239,   335,   336,   201,   202,   203,   360,   204,
     304,   339,   340,   341,   342,   213,   361,   206,   207,   208,
     209,   210,   362,    14,   203,   352,   204,   139,   397,   201,
     202,   203,   140,   204,   398,   212,   316,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   354,   151,   270,   343,   379,
     380,   381,   376,   221,   222,   382,   383,   138,   138,   138,
     138,   138,   152,   280,   281,   282,   283,   284,   215,   153,
     291,   292,   396,   238,   209,   210,   216,   217,   218,   154,
     244,   245,   246,   247,   403,   404,   405,   205,   206,   207,
     208,   209,   210,   155,   391,   220,   412,   156,   409,   410,
     411,   323,   324,   157,   269,   205,   206,   207,   208,   209,
     210,   205,   206,   207,   208,   209,   210,   201,   202,   203,
     158,   204,   201,   202,   203,   138,   204,   194,   195,   159,
     196,   318,   205,   206,   207,   208,   209,   210,   205,   206,
     207,   208,   209,   210,   201,   202,   203,   357,   204,   138,
     138,   138,    12,   346,   347,   332,   333,   334,   160,    24,
      25,   161,    26,   162,    27,   399,    28,   349,   350,    29,
     355,   356,   205,   206,   207,   208,   209,   210,   163,   164,
     197,    12,     6,   400,   198,   168,   201,   202,   203,   401,
     204,   169,   170,   274,   413,   171,   172,   173,   285,   414,
     201,   202,   203,   358,   204,   174,   175,   211,   248,   279,
     286,   287,   337,   344,   288,   293,   138,   138,   138,   138,
     138,   138,   384,   385,   386,   387,   388,   389,    12,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,   402,   289,   294,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   295,   296,
     103,   297,   298,   299,   104,   166,   300,   301,   105,   106,
     107,   108,   109,   110,   111,   302,   305,     6,   306,   309,
     112,   310,   113,   114,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   311,   312,   326,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   320,   321,   103,   322,   327,   328,   104,
     338,   351,   365,   105,   106,   107,   108,   109,   110,   111,
     370,   371,     6,   372,   373,   112,    10,   113,   114,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   377,
     196,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   378,   196,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   390,   196,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     197,   196,   374,   315,   198,   240,   192,   193,   194,   195,
       0,   196,   193,   194,   195,     0,   196,   201,   202,   203,
     359,   204,   197,     0,     0,     0,   198,   201,   202,   203,
     363,   204,   201,   202,   203,   364,   204,     0,   197,     0,
       0,     0,   198,   201,   202,   203,   366,   204,     0,     0,
       0,   197,     0,     0,     0,   198,   201,   202,   203,   367,
     204,   197,     0,     0,     0,   198,   197,     0,     0,     0,
     198,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,     0,     0,     0,     0,   241,   242,   201,   202,   203,
     368,   204,   201,   202,   203,   369,   204,   201,   202,   203,
     392,   204,   201,   202,   203,   393,   204,   201,   202,   203,
     394,   204,   201,   202,   203,   406,   204,   201,   202,   203,
     407,   204,   201,   202,   203,   408,   204
};

static const yytype_int16 yycheck[] =
{
      19,   152,   153,    28,     0,     1,    25,    26,   198,     1,
       1,    78,    25,    26,     3,     4,     5,     6,     7,     8,
       1,   199,     7,   201,   202,   203,   204,     6,     7,     8,
       3,     4,     5,     6,     7,     8,     4,     5,     6,    80,
       8,     2,    83,   197,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,     7,     0,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,     7,    44,   103,   104,    73,    74,    97,   279,
     103,    87,    83,    85,   248,    95,    81,    33,    34,    73,
      74,    97,    83,    99,     7,    97,    97,    95,     7,   105,
      97,    80,   115,    81,    80,    84,    97,   295,   296,   297,
      86,   110,    81,   301,   302,     4,     5,     6,    81,     8,
      81,   309,   310,   311,   312,   108,    81,     4,     5,     6,
       7,     8,    81,    80,     6,    81,     8,    81,    81,     4,
       5,     6,    78,     8,    81,    78,    81,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   326,    80,   196,    81,   357,
     358,   359,    81,    33,    34,   363,   364,   206,   207,   208,
     209,   210,    80,   206,   207,   208,   209,   210,   112,    80,
     225,   226,    81,   164,     7,     8,   120,   121,   122,    80,
     171,   172,   173,   174,   392,   393,   394,     3,     4,     5,
       6,     7,     8,    80,   375,   114,    81,    80,   406,   407,
     408,    95,    96,    80,   195,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,     4,     5,     6,
      80,     8,     4,     5,     6,   274,     8,    27,    28,    80,
      30,   274,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,   298,
     299,   300,   243,   118,   119,   298,   299,   300,    80,   106,
     107,    80,   109,    80,   111,    81,   113,   321,   322,   116,
     327,   328,     3,     4,     5,     6,     7,     8,    80,    80,
      80,   272,    97,    81,    84,    80,     4,     5,     6,    81,
       8,    80,    82,    86,    81,    80,    80,    80,   123,    81,
       4,     5,     6,     7,     8,    80,    82,    78,    80,    82,
     123,   123,   303,    78,     7,    81,   365,   366,   367,   368,
     369,   370,   365,   366,   367,   368,   369,   370,   319,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    78,    97,    81,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     7,     7,
      80,     7,     7,     7,    84,    85,     7,     7,    88,    89,
      90,    91,    92,    93,    94,     7,    81,    97,    81,     7,
     100,     7,   102,   103,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     7,     7,    80,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   124,   124,    80,   124,     7,     7,    84,
      28,     7,    80,    88,    89,    90,    91,    92,    93,    94,
     101,   124,    97,   124,   124,   100,     2,   102,   103,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    81,
      30,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    81,    30,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    81,    30,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      80,    30,   351,   249,    84,    85,    25,    26,    27,    28,
      -1,    30,    26,    27,    28,    -1,    30,     4,     5,     6,
       7,     8,    80,    -1,    -1,    -1,    84,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,    -1,    80,    -1,
      -1,    -1,    84,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    84,     4,     5,     6,     7,
       8,    80,    -1,    -1,    -1,    84,    80,    -1,    -1,    -1,
      84,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,    -1,    -1,    -1,    -1,   168,   169,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   126,   127,     0,     1,    87,    97,    99,   105,   129,
     141,   142,   147,    78,    80,    97,   148,   130,    80,    86,
      95,   152,    95,   151,   106,   107,   109,   111,   113,   116,
     131,   132,   133,   134,   135,   136,   140,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    84,    88,    89,    90,    91,    92,
      93,    94,   100,   102,   103,   145,   146,   147,   149,   150,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   144,   145,    81,
      78,   144,   144,   137,   148,   115,    73,    74,   147,    73,
      74,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,   144,    85,   145,    80,    80,
      82,    80,    80,    80,    80,    82,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    30,    80,    84,     7,
      81,     4,     5,     6,     8,     3,     4,     5,     6,     7,
       8,    78,    78,   108,   110,   112,   120,   121,   122,   138,
     114,    33,    34,   171,   176,   176,   176,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   143,   147,    81,
      85,   152,   152,   128,   147,   147,   147,   147,    80,   174,
     175,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   147,
     145,   149,   128,   150,    86,   150,   150,   150,   150,    82,
     144,   144,   144,   144,   144,   123,   123,   123,     7,    97,
     172,   148,   148,    81,    81,     7,     7,     7,     7,     7,
       7,     7,     7,     7,    81,    81,    81,    83,   141,     7,
       7,     7,     7,   149,    83,   175,    81,    85,   144,   128,
     124,   124,   124,    95,    96,   153,    80,     7,     7,   150,
     150,   150,   144,   144,   144,   150,   150,   147,    28,   150,
     150,   150,   150,    81,    78,    83,   118,   119,   139,   139,
     139,     7,    81,   173,   176,   153,   153,     7,     7,     7,
      81,    81,    81,     7,     7,    80,     7,     7,     7,     7,
     101,   124,   124,   124,   151,     7,    81,    81,    81,   150,
     150,   150,   150,   150,   144,   144,   144,   144,   144,   144,
      81,   176,     7,     7,     7,    81,    81,    81,    81,    81,
      81,    81,    78,   150,   150,   150,     7,     7,     7,   150,
     150,   150,    81,    81,    81
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
#line 306 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 309 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 310 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 312 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 313 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 316 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 317 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 318 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 319 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 322 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 323 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 326 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 327 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 328 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 329 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 330 "parser/faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 331 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 334 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 335 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 338 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 341 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 344 "parser/faustparser.y"
    { ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 347 "parser/faustparser.y"
    { ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 350 "parser/faustparser.y"
    { ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 351 "parser/faustparser.y"
    { ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 354 "parser/faustparser.y"
    { gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 355 "parser/faustparser.y"
    { gStripDocSwitch = (yyvsp[(4) - (5)].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 356 "parser/faustparser.y"
    { gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 359 "parser/faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 360 "parser/faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 363 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 366 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 367 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 368 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 371 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 374 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 375 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 378 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 379 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 380 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 381 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 382 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 383 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 384 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 387 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 388 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 389 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 390 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 391 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 395 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 397 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 398 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 399 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 401 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 402 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 404 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 405 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 406 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 408 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 409 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 411 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigConcat)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 413 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 414 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 416 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 419 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 420 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 423 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 425 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 426 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 428 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 429 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 431 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 432 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 435 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 438 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 440 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 442 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 445 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 446 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 448 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 449 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 452 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 453 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 454 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 455 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 456 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 458 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 460 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 461 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 462 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 463 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 464 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 465 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 466 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 468 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 469 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 470 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 471 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 472 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 473 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 475 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 476 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 477 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 479 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 480 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 482 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 483 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 484 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 487 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 488 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 490 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 491 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 493 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorize); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 494 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigSerialize); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 495 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigConcat); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 496 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigVectorAt); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 497 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxWire(),(yyvsp[(2) - (3)].exp)),boxPrim2(sigVectorAt)); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 499 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 500 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 502 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 504 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 506 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 508 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 509 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 510 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 511 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 512 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 513 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 515 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 516 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 517 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 518 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 519 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 520 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 521 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 522 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 523 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 524 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 526 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 527 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 528 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 529 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 533 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 536 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 541 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 542 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 545 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 546 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 547 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 548 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 549 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 552 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 555 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 558 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 559 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 565 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 569 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 573 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 577 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 584 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 588 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 591 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 595 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 598 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 602 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 605 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 608 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 611 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 614 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 617 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 621 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 624 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 629 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 630 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 633 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 636 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 637 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 640 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 641 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 645 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 648 "parser/faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 649 "parser/faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3324 "parser/faustparser.cpp"
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
#line 652 "parser/faustparser.y"



