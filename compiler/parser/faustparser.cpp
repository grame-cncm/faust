/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

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

/* Line 268 of yacc.c  */
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



/* Line 268 of yacc.c  */
#line 144 "parser/faustparser.cpp"

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
     IPAR = 345,
     ISEQ = 346,
     ISUM = 347,
     IPROD = 348,
     STRING = 349,
     FSTRING = 350,
     IDENT = 351,
     EXTRA = 352,
     DECLARE = 353,
     CASE = 354,
     ARROW = 355,
     BDOC = 356,
     EDOC = 357,
     BEQN = 358,
     EEQN = 359,
     BDGM = 360,
     EDGM = 361,
     BLST = 362,
     ELST = 363,
     BMETADATA = 364,
     EMETADATA = 365,
     DOCCHAR = 366,
     NOTICE = 367,
     LISTING = 368,
     LSTTRUE = 369,
     LSTFALSE = 370,
     LSTDEPENDENCIES = 371,
     LSTMDOCTAGS = 372,
     LSTDISTRIBUTED = 373,
     LSTEQ = 374,
     LSTQ = 375
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 78 "parser/faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;



/* Line 293 of yacc.c  */
#line 309 "parser/faustparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 321 "parser/faustparser.cpp"

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   603

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  121
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  188
/* YYNRULES -- Number of states.  */
#define YYNSTATES  406

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   375

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
     115,   116,   117,   118,   119,   120
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
     201,   205,   209,   213,   217,   221,   225,   230,   235,   237,
     239,   241,   244,   247,   250,   253,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   356,   360,   369,   374,
     376,   378,   380,   385,   390,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
     425,   427,   429,   433,   437,   441,   445,   449,   451,   453,
     455,   457,   459,   468,   477,   486,   495,   504,   512,   520,
     525,   530,   543,   556,   569,   576,   583,   590,   599,   608,
     614,   619,   621,   623,   627,   629,   632,   639,   641
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     122,     0,    -1,   123,    -1,    -1,   123,   125,    -1,    -1,
     124,   137,    -1,    86,    79,   148,    80,    77,    -1,    98,
     144,   147,    77,    -1,   137,    -1,   101,   126,   102,    -1,
      -1,   126,   127,    -1,   128,    -1,   129,    -1,   130,    -1,
     131,    -1,   132,    -1,   136,    -1,    -1,   128,   111,    -1,
     103,   140,   104,    -1,   105,   140,   106,    -1,   112,    -1,
     107,   133,   108,    -1,    -1,   133,   134,    -1,   116,   119,
     120,   135,   120,    -1,   117,   119,   120,   135,   120,    -1,
     118,   119,   120,   135,   120,    -1,   114,    -1,   115,    -1,
     109,   144,   110,    -1,   138,    79,   145,    80,    85,   140,
      77,    -1,   138,    85,   140,    77,    -1,     1,    77,    -1,
     143,    -1,   143,    -1,   139,     7,   143,    -1,   140,     3,
      81,   124,    82,    -1,   140,     7,   140,    -1,   140,     6,
     140,    -1,   140,     5,   140,    -1,   140,     4,   140,    -1,
     140,     8,   140,    -1,   141,    -1,   141,    17,   141,    -1,
     141,    16,   141,    -1,   141,    24,   141,    -1,   141,    23,
     141,    -1,   141,    22,   141,    -1,   141,    25,   141,    -1,
     141,    26,   141,    -1,   141,    27,    -1,   141,    28,   143,
      -1,   141,    21,   141,    -1,   141,    15,   141,    -1,   141,
      20,   141,    -1,   141,    19,   141,    -1,   141,    18,   141,
      -1,   141,    14,   141,    -1,   141,    13,   141,    -1,   141,
      11,   141,    -1,   141,    10,   141,    -1,   141,    12,   141,
      -1,   141,     9,   141,    -1,   141,    79,   145,    80,    -1,
     141,    83,   124,    84,    -1,   142,    -1,    72,    -1,    73,
      -1,    17,    72,    -1,    17,    73,    -1,    16,    72,    -1,
      16,    73,    -1,    75,    -1,    76,    -1,    30,    -1,    31,
      -1,    32,    -1,    33,    -1,    17,    -1,    16,    -1,    24,
      -1,    23,    -1,    22,    -1,    26,    -1,    21,    -1,    15,
      -1,    20,    -1,    19,    -1,    18,    -1,    14,    -1,    13,
      -1,    11,    -1,    10,    -1,    12,    -1,     9,    -1,    47,
      -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,
      -1,    25,    -1,    58,    -1,    59,    -1,    60,    -1,    61,
      -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,
      -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,    71,
      -1,   143,    -1,    16,   143,    -1,    79,   140,    80,    -1,
      74,    79,   139,    80,    28,    79,   140,    80,    -1,    99,
      81,   170,    82,    -1,   154,    -1,   155,    -1,   156,    -1,
      87,    79,   148,    80,    -1,    88,    79,   148,    80,    -1,
      89,    81,   124,    82,    -1,   157,    -1,   158,    -1,   159,
      -1,   160,    -1,   161,    -1,   162,    -1,   163,    -1,   164,
      -1,   165,    -1,   166,    -1,   150,    -1,   151,    -1,   152,
      -1,   153,    -1,    96,    -1,    96,    -1,   146,    -1,   145,
       7,   146,    -1,   146,     6,   146,    -1,   146,     5,   146,
      -1,   146,     4,   146,    -1,   146,     8,   146,    -1,   141,
      -1,    94,    -1,    94,    -1,    94,    -1,    95,    -1,    90,
      79,   143,     7,   146,     7,   140,    80,    -1,    91,    79,
     143,     7,   146,     7,   140,    80,    -1,    92,    79,   143,
       7,   146,     7,   140,    80,    -1,    93,    79,   143,     7,
     146,     7,   140,    80,    -1,    34,    79,   167,     7,   149,
       7,   147,    80,    -1,    35,    79,   172,   144,     7,   149,
      80,    -1,    36,    79,   172,   144,     7,   149,    80,    -1,
      37,    79,   148,    80,    -1,    38,    79,   148,    80,    -1,
      39,    79,   148,     7,   146,     7,   146,     7,   146,     7,
     146,    80,    -1,    40,    79,   148,     7,   146,     7,   146,
       7,   146,     7,   146,    80,    -1,    41,    79,   148,     7,
     146,     7,   146,     7,   146,     7,   146,    80,    -1,    42,
      79,   148,     7,   140,    80,    -1,    43,    79,   148,     7,
     140,    80,    -1,    44,    79,   148,     7,   140,    80,    -1,
      46,    79,   148,     7,   146,     7,   146,    80,    -1,    45,
      79,   148,     7,   146,     7,   146,    80,    -1,   172,   168,
      79,   169,    80,    -1,   172,   168,    79,    80,    -1,    96,
      -1,   172,    -1,   169,     7,   172,    -1,   171,    -1,   170,
     171,    -1,    79,   145,    80,   100,   140,    77,    -1,    32,
      -1,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   301,   301,   304,   305,   307,   308,   311,   312,   313,
     314,   317,   318,   321,   322,   323,   324,   325,   326,   329,
     330,   333,   336,   339,   342,   345,   346,   349,   350,   351,
     354,   355,   358,   361,   362,   363,   366,   369,   370,   373,
     374,   375,   376,   377,   378,   379,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   392,   393,   394,   396,   397,
     399,   400,   401,   402,   403,   404,   406,   407,   409,   412,
     413,   415,   416,   418,   419,   421,   422,   424,   425,   427,
     428,   430,   431,   432,   433,   434,   435,   437,   438,   439,
     441,   442,   444,   445,   446,   447,   448,   449,   451,   453,
     454,   455,   456,   457,   458,   459,   461,   462,   463,   464,
     465,   466,   468,   469,   470,   472,   473,   475,   476,   477,
     480,   481,   483,   484,   486,   487,   489,   490,   493,   495,
     496,   497,   498,   499,   500,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   513,   514,   515,   516,   520,
     523,   528,   529,   532,   533,   534,   535,   536,   539,   542,
     545,   546,   551,   555,   559,   563,   570,   574,   577,   582,
     585,   588,   591,   594,   597,   600,   603,   607,   610,   616,
     617,   620,   623,   624,   627,   628,   631,   635,   636
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
  "DOT", "APPL", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "FFUNCTION",
  "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER", "HSLIDER",
  "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH", "VBARGRAPH",
  "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN", "TAN", "EXP",
  "LOG", "LOG10", "POWFUN", "SQRT", "ABS", "MIN", "MAX", "FMOD",
  "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL", "SELECT2",
  "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT", "ENDDEF", "VIRG",
  "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC", "DEF", "IMPORT",
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "IPAR", "ISEQ", "ISUM", "IPROD",
  "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW",
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
     375
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   121,   122,   123,   123,   124,   124,   125,   125,   125,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   128,
     128,   129,   130,   131,   132,   133,   133,   134,   134,   134,
     135,   135,   136,   137,   137,   137,   138,   139,   139,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   143,
     144,   145,   145,   146,   146,   146,   146,   146,   147,   148,
     149,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     167,   168,   169,   169,   170,   170,   171,   172,   172
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
       3,     3,     3,     3,     3,     3,     4,     4,     1,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     8,     4,     1,
       1,     1,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     8,     8,     8,     8,     8,     7,     7,     4,
       4,    12,    12,    12,     6,     6,     6,     8,     8,     5,
       4,     1,     1,     3,     1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   149,     0,    11,     4,
       9,     0,    36,    35,     0,   150,     0,    19,     0,     0,
     159,     0,   158,     0,    10,     0,     0,    25,     0,    23,
      12,    13,    14,    15,    16,    17,    18,    97,    95,    94,
      96,    93,    92,    88,    82,    81,    91,    90,    89,    87,
      85,    84,    83,   109,    86,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    69,    70,     0,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,    68,   124,     0,   151,   145,   146,   147,   148,
     129,   130,   131,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,    45,     0,     8,     0,     0,     0,
       0,    20,    73,    74,   125,    71,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     7,    21,    22,    24,     0,
       0,     0,    26,    32,   187,   188,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   184,    65,    63,    62,    64,    61,    60,    56,
      47,    46,    59,    58,    57,    55,    50,    49,    48,    51,
      52,    54,     0,     0,   152,     0,   155,   154,   153,   156,
       5,    43,    42,    41,    40,    44,     0,     0,     0,     0,
     181,     0,     0,     0,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,   133,   134,     6,
       0,     0,     0,     0,     0,   128,   185,    66,    67,     0,
       0,     0,     0,     0,   160,   161,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,     0,     0,     0,    33,    39,    30,    31,     0,
       0,     0,     0,   180,     0,   182,     0,     0,     0,     0,
       0,   174,   175,   176,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    28,    29,     0,     0,   179,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   183,     0,     0,     0,   178,   177,   127,   162,
     163,   164,   165,   186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   172,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   235,     9,    17,    30,    31,    32,    33,
      34,    35,   139,   212,   339,    36,   299,    11,   230,   133,
     111,   112,   113,    16,   114,   115,    23,    21,   316,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   216,   281,   344,   241,
     242,   217
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -189
static const yytype_int16 yypact[] =
{
    -189,    36,     8,  -189,   -66,   -25,  -189,    -9,  -189,  -189,
    -189,    13,  -189,  -189,    -4,  -189,     3,   178,   342,   342,
    -189,    30,  -189,    60,  -189,   342,   342,  -189,    -9,  -189,
    -189,    31,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,    23,   -29,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,   172,
     183,   195,   200,   203,   205,   210,   212,   214,   220,   226,
     248,   249,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,   252,
    -189,  -189,   342,   253,   254,   118,   257,   270,   292,   340,
     225,   440,  -189,  -189,    19,   296,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,    25,   440,   241,  -189,    17,    11,    61,
     219,  -189,  -189,  -189,  -189,  -189,  -189,   101,   101,   101,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
     273,    43,    -4,    -4,  -189,   273,   273,   273,   273,   341,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,  -189,   273,
     342,  -189,   342,   343,   342,   342,   342,   342,   344,   342,
     342,   342,   342,   342,  -189,  -189,  -189,  -189,  -189,   308,
     317,   320,  -189,  -189,  -189,  -189,   430,   349,    -9,    -9,
     360,   367,   441,   487,   488,   489,   490,   507,   508,   509,
      27,  -189,  -189,   437,   442,     4,   513,   514,   522,   523,
     342,     6,  -189,   454,   454,   454,   454,   454,   454,   465,
     465,   465,   190,   190,   190,   190,   190,   190,   190,    41,
     209,  -189,    38,     9,   296,   342,   296,   296,    95,  -189,
    -189,   260,   260,   133,   120,  -189,   411,   412,   414,   107,
    -189,   456,   529,   536,  -189,  -189,   342,   342,   342,   342,
     342,   342,   342,   342,   273,   517,  -189,  -189,  -189,  -189,
     342,   342,   342,   342,    45,  -189,  -189,  -189,  -189,    73,
      26,    89,    89,    89,  -189,  -189,   539,   116,   107,   107,
     318,   495,   500,    52,    58,    67,   505,   520,  -189,   468,
     534,   545,   550,   555,   494,  -189,  -189,  -189,  -189,   475,
     476,   477,     3,  -189,    46,  -189,   518,   519,   342,   342,
     342,  -189,  -189,  -189,   342,   342,   342,   342,   342,   342,
     342,   342,  -189,  -189,  -189,   521,   101,  -189,  -189,  -189,
     560,   565,   570,   239,   255,   168,   206,   217,   227,   250,
     108,  -189,  -189,   342,   342,   342,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   575,   580,   585,   342,   342,   342,
     290,   418,   438,  -189,  -189,  -189
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,  -188,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   -74,  -189,   598,  -189,  -189,   -13,
     -19,  -189,    40,   -24,  -149,  -157,   261,   158,   -69,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
     361,  -147
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     134,   218,   219,   263,   140,     4,   134,   134,    -2,     4,
       4,    13,   137,   138,   198,   199,   200,   201,   202,   203,
     198,   199,   200,   201,   202,   203,   192,     4,   198,   199,
     200,   201,   202,   203,   294,   264,     3,   266,   267,   268,
     269,   262,    12,   145,   146,   192,   198,   199,   200,   201,
     202,   203,   192,   366,    14,   198,   199,   200,   201,   202,
     203,   198,   199,   200,   201,   202,   203,   187,   188,   189,
     198,   199,   200,   201,   202,   203,   198,   199,   200,   201,
     202,   203,   310,   134,   144,   240,   298,    15,   305,   161,
      20,   304,    18,   308,     5,   142,   143,    22,    19,   193,
       6,   196,   204,   197,     6,     6,     7,   295,   336,     8,
     135,   198,   199,   200,   201,   202,   203,   207,   307,     6,
     190,   206,     6,   232,   191,   334,   367,   202,   203,   320,
     321,   322,   351,   214,   215,   326,   327,   136,   352,   201,
     202,   203,   141,   330,   331,   332,   333,   353,   214,   215,
     335,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   208,
     345,   198,   199,   200,   201,   202,   203,   209,   210,   211,
     134,   134,   134,   134,   134,   393,   271,   272,   273,   274,
     275,   370,   371,   372,   282,   283,   343,   373,   374,   164,
     231,   314,   315,   337,   338,   236,   237,   238,   239,   198,
     199,   200,   201,   202,   203,   186,   187,   188,   189,   382,
     198,   199,   200,   201,   202,   203,   394,   395,   396,   261,
     198,   199,   200,   201,   202,   203,   188,   189,   340,   341,
     400,   401,   402,   194,   195,   196,   134,   197,   388,   346,
     347,   147,   309,   198,   199,   200,   201,   202,   203,   194,
     195,   196,   148,   197,   199,   200,   201,   202,   203,   190,
     134,   134,   134,   191,   149,    12,   323,   324,   325,   150,
      24,    25,   151,    26,   152,    27,   389,    28,   190,   153,
      29,   154,   191,   155,   194,   195,   196,   390,   197,   156,
     194,   195,   196,    12,   197,   157,   169,   391,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   205,   386,
     233,   234,   194,   195,   196,   348,   197,   158,   159,   213,
     392,   160,   162,   163,   328,   387,   165,   134,   134,   134,
     134,   134,   134,   375,   376,   377,   378,   379,   380,   166,
      12,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     6,
     403,   167,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   168,
     240,   102,   194,   195,   196,   270,   197,   276,   265,   103,
     104,   105,   106,   107,   108,   109,   277,   279,     6,   278,
     284,   110,   194,   195,   196,   280,   197,   285,   286,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   287,   288,   289,   290,   404,   194,
     195,   196,   349,   197,   194,   195,   196,   350,   197,   194,
     195,   196,   354,   197,   291,   292,   293,   296,   405,   190,
     300,   301,   297,   191,   194,   195,   196,   355,   197,   302,
     303,   311,   312,   190,   313,   317,   318,   191,   194,   195,
     196,   357,   197,   319,   190,   329,   342,   356,   191,   194,
     195,   196,   358,   197,   194,   195,   196,   359,   197,   194,
     195,   196,   360,   197,   194,   195,   196,   383,   197,   194,
     195,   196,   384,   197,   194,   195,   196,   385,   197,   194,
     195,   196,   397,   197,   194,   195,   196,   398,   197,   194,
     195,   196,   399,   197,   361,   362,   363,   364,   368,   369,
      10,   381,   306,   365
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-189))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint16 yycheck[] =
{
      19,   148,   149,   191,    28,     1,    25,    26,     0,     1,
       1,    77,    25,    26,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,     7,     1,     3,     4,
       5,     6,     7,     8,     7,   192,     0,   194,   195,   196,
     197,   190,     2,    72,    73,     7,     3,     4,     5,     6,
       7,     8,     7,     7,    79,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,    26,    27,    28,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,   270,   102,    44,    79,    82,    96,    82,   102,
      94,   240,    79,    84,    86,    72,    73,    94,    85,    80,
      96,     6,    77,     8,    96,    96,    98,    80,    82,   101,
      80,     3,     4,     5,     6,     7,     8,   106,    80,    96,
      79,   104,    96,    80,    83,    80,    80,     7,     8,   286,
     287,   288,    80,    32,    33,   292,   293,    77,    80,     6,
       7,     8,   111,   300,   301,   302,   303,    80,    32,    33,
      77,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   108,
     317,     3,     4,     5,     6,     7,     8,   116,   117,   118,
     199,   200,   201,   202,   203,    77,   199,   200,   201,   202,
     203,   348,   349,   350,   218,   219,    80,   354,   355,    81,
     160,    94,    95,   114,   115,   165,   166,   167,   168,     3,
       4,     5,     6,     7,     8,    25,    26,    27,    28,   366,
       3,     4,     5,     6,     7,     8,   383,   384,   385,   189,
       3,     4,     5,     6,     7,     8,    27,    28,   312,   313,
     397,   398,   399,     4,     5,     6,   265,     8,    80,   318,
     319,    79,   265,     3,     4,     5,     6,     7,     8,     4,
       5,     6,    79,     8,     4,     5,     6,     7,     8,    79,
     289,   290,   291,    83,    79,   235,   289,   290,   291,    79,
     102,   103,    79,   105,    79,   107,    80,   109,    79,    79,
     112,    79,    83,    79,     4,     5,     6,    80,     8,    79,
       4,     5,     6,   263,     8,    79,    81,    80,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,    77,    80,
     162,   163,     4,     5,     6,     7,     8,    79,    79,   110,
      80,    79,    79,    79,   294,    80,    79,   356,   357,   358,
     359,   360,   361,   356,   357,   358,   359,   360,   361,    79,
     310,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    96,
      80,    79,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    79,
      79,    79,     4,     5,     6,    81,     8,   119,    85,    87,
      88,    89,    90,    91,    92,    93,   119,     7,    96,   119,
      80,    99,     4,     5,     6,    96,     8,    80,     7,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     7,     7,     7,     7,    80,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     7,     7,     7,    80,    80,    79,
       7,     7,    80,    83,     4,     5,     6,     7,     8,     7,
       7,   120,   120,    79,   120,    79,     7,    83,     4,     5,
       6,     7,     8,     7,    79,    28,     7,    79,    83,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,   100,   120,   120,   120,    80,    80,
       2,    80,   241,   342
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   122,   123,     0,     1,    86,    96,    98,   101,   125,
     137,   138,   143,    77,    79,    96,   144,   126,    79,    85,
      94,   148,    94,   147,   102,   103,   105,   107,   109,   112,
     127,   128,   129,   130,   131,   132,   136,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      99,   141,   142,   143,   145,   146,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   140,   141,    80,    77,   140,   140,   133,
     144,   111,    72,    73,   143,    72,    73,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,   140,    79,    79,    81,    79,    79,    79,    79,    81,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      79,    83,     7,    80,     4,     5,     6,     8,     3,     4,
       5,     6,     7,     8,    77,    77,   104,   106,   108,   116,
     117,   118,   134,   110,    32,    33,   167,   172,   172,   172,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     139,   143,    80,   148,   148,   124,   143,   143,   143,   143,
      79,   170,   171,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   143,   145,   124,   146,    85,   146,   146,   146,   146,
      81,   140,   140,   140,   140,   140,   119,   119,   119,     7,
      96,   168,   144,   144,    80,    80,     7,     7,     7,     7,
       7,     7,     7,     7,     7,    80,    80,    80,    82,   137,
       7,     7,     7,     7,   145,    82,   171,    80,    84,   140,
     124,   120,   120,   120,    94,    95,   149,    79,     7,     7,
     146,   146,   146,   140,   140,   140,   146,   146,   143,    28,
     146,   146,   146,   146,    80,    77,    82,   114,   115,   135,
     135,   135,     7,    80,   169,   172,   149,   149,     7,     7,
       7,    80,    80,    80,     7,     7,    79,     7,     7,     7,
       7,   100,   120,   120,   120,   147,     7,    80,    80,    80,
     146,   146,   146,   146,   146,   140,   140,   140,   140,   140,
     140,    80,   172,     7,     7,     7,    80,    80,    80,    80,
      80,    80,    80,    77,   146,   146,   146,     7,     7,     7,
     146,   146,   146,    80,    80,    80
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/* Line 1806 of yacc.c  */
#line 301 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 304 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 305 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 307 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 308 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 311 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 312 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 313 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 314 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 317 "parser/faustparser.y"
    { (yyval.exp) = nil; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 318 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 321 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 322 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 323 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 324 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 325 "parser/faustparser.y"
    { (yyval.exp) = docLst(); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 326 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 329 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 330 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 333 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 336 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 339 "parser/faustparser.y"
    { }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 342 "parser/faustparser.y"
    { }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 345 "parser/faustparser.y"
    { }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 346 "parser/faustparser.y"
    { }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 349 "parser/faustparser.y"
    { gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 350 "parser/faustparser.y"
    { gStripDocSwitch = (yyvsp[(4) - (5)].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 351 "parser/faustparser.y"
    { gLstDistributedSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 354 "parser/faustparser.y"
    { (yyval.b) = true; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 355 "parser/faustparser.y"
    { (yyval.b) = false; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 358 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 361 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 362 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 363 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 366 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 369 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 370 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 373 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 374 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 375 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 376 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 377 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 378 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 379 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 382 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 383 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 384 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 385 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 386 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 387 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 388 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 389 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 390 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 396 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 397 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 399 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 400 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 401 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 402 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 403 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 404 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 406 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 409 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 412 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 413 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 415 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 416 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 418 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 419 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 421 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 424 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 425 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 427 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 428 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 430 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 431 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 432 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 433 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 435 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 438 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 442 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 445 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 446 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 447 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 448 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 449 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 453 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 454 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 455 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 456 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 457 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 458 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 459 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 461 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 462 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 463 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 464 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 465 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 466 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 468 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 469 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 470 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 472 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 473 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 475 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 476 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 477 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 480 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 481 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 483 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 484 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 486 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 487 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 489 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 491 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 493 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 495 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 496 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 497 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 498 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 499 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 500 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 502 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 503 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 504 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 505 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 506 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 507 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 508 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 509 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 510 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 511 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 513 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 514 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 515 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 516 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 520 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 523 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 528 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 529 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 532 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 533 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 534 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 535 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 536 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 539 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 542 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 545 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 546 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 552 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 556 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 560 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 564 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 571 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 575 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 578 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 582 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 585 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 589 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 592 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 595 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 598 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 601 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 604 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 608 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 611 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 616 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 617 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 620 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 623 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 624 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 627 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 628 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 632 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 635 "parser/faustparser.y"
    { (yyval.exp) = tree(0); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 636 "parser/faustparser.y"
    { (yyval.exp) = tree(1); }
    break;



/* Line 1806 of yacc.c  */
#line 3272 "parser/faustparser.cpp"
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



/* Line 2067 of yacc.c  */
#line 639 "parser/faustparser.y"



