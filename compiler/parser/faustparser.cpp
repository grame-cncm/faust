/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     INPUTS = 349,
     OUTPUTS = 350,
     STRING = 351,
     FSTRING = 352,
     IDENT = 353,
     EXTRA = 354,
     DECLARE = 355,
     CASE = 356,
     ARROW = 357,
     BDOC = 358,
     EDOC = 359,
     BEQN = 360,
     EEQN = 361,
     BDGM = 362,
     EDGM = 363,
     BLST = 364,
     ELST = 365,
     BMETADATA = 366,
     EMETADATA = 367,
     DOCCHAR = 368,
     NOTICE = 369,
     LISTING = 370,
     LSTTRUE = 371,
     LSTFALSE = 372,
     LSTDEPENDENCIES = 373,
     LSTMDOCTAGS = 374,
     LSTDISTRIBUTED = 375,
     LSTEQ = 376,
     LSTQ = 377
   };
#endif
/* Tokens.  */
#define WITH 258
#define MIX 259
#define SPLIT 260
#define SEQ 261
#define PAR 262
#define REC 263
#define NE 264
#define GE 265
#define GT 266
#define EQ 267
#define LE 268
#define LT 269
#define OR 270
#define SUB 271
#define ADD 272
#define RSH 273
#define LSH 274
#define XOR 275
#define AND 276
#define MOD 277
#define DIV 278
#define MUL 279
#define POWOP 280
#define FDELAY 281
#define DELAY1 282
#define DOT 283
#define APPL 284
#define MEM 285
#define PREFIX 286
#define INTCAST 287
#define FLOATCAST 288
#define FFUNCTION 289
#define FCONSTANT 290
#define FVARIABLE 291
#define BUTTON 292
#define CHECKBOX 293
#define VSLIDER 294
#define HSLIDER 295
#define NENTRY 296
#define VGROUP 297
#define HGROUP 298
#define TGROUP 299
#define HBARGRAPH 300
#define VBARGRAPH 301
#define ATTACH 302
#define ACOS 303
#define ASIN 304
#define ATAN 305
#define ATAN2 306
#define COS 307
#define SIN 308
#define TAN 309
#define EXP 310
#define LOG 311
#define LOG10 312
#define POWFUN 313
#define SQRT 314
#define ABS 315
#define MIN 316
#define MAX 317
#define FMOD 318
#define REMAINDER 319
#define FLOOR 320
#define CEIL 321
#define RINT 322
#define RDTBL 323
#define RWTBL 324
#define SELECT2 325
#define SELECT3 326
#define INT 327
#define FLOAT 328
#define LAMBDA 329
#define WIRE 330
#define CUT 331
#define ENDDEF 332
#define VIRG 333
#define LPAR 334
#define RPAR 335
#define LBRAQ 336
#define RBRAQ 337
#define LCROC 338
#define RCROC 339
#define DEF 340
#define IMPORT 341
#define COMPONENT 342
#define LIBRARY 343
#define ENVIRONMENT 344
#define IPAR 345
#define ISEQ 346
#define ISUM 347
#define IPROD 348
#define INPUTS 349
#define OUTPUTS 350
#define STRING 351
#define FSTRING 352
#define IDENT 353
#define EXTRA 354
#define DECLARE 355
#define CASE 356
#define ARROW 357
#define BDOC 358
#define EDOC 359
#define BEQN 360
#define EEQN 361
#define BDGM 362
#define EDGM 363
#define BLST 364
#define ELST 365
#define BMETADATA 366
#define EMETADATA 367
#define DOCCHAR 368
#define NOTICE 369
#define LISTING 370
#define LSTTRUE 371
#define LSTFALSE 372
#define LSTDEPENDENCIES 373
#define LSTMDOCTAGS 374
#define LSTDISTRIBUTED 375
#define LSTEQ 376
#define LSTQ 377




/* Copy the first part of user declarations.  */
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 78 "parser/faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
}
/* Line 193 of yacc.c.  */
#line 419 "parser/faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 432 "parser/faustparser.cpp"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   643

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  123
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  428

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   377

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
     115,   116,   117,   118,   119,   120,   121,   122
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
     425,   427,   429,   431,   433,   437,   441,   445,   449,   453,
     455,   457,   459,   461,   463,   472,   481,   490,   499,   504,
     509,   518,   526,   534,   539,   544,   557,   570,   583,   590,
     597,   604,   613,   622,   628,   636,   646,   651,   658,   667,
     669,   671,   675,   677,   680,   687,   689
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     124,     0,    -1,   125,    -1,    -1,   125,   127,    -1,    -1,
     126,   139,    -1,    86,    79,   150,    80,    77,    -1,   100,
     146,   149,    77,    -1,   139,    -1,   103,   128,   104,    -1,
      -1,   128,   129,    -1,   130,    -1,   131,    -1,   132,    -1,
     133,    -1,   134,    -1,   138,    -1,    -1,   130,   113,    -1,
     105,   142,   106,    -1,   107,   142,   108,    -1,   114,    -1,
     109,   135,   110,    -1,    -1,   135,   136,    -1,   118,   121,
     122,   137,   122,    -1,   119,   121,   122,   137,   122,    -1,
     120,   121,   122,   137,   122,    -1,   116,    -1,   117,    -1,
     111,   146,   112,    -1,   140,    79,   147,    80,    85,   142,
      77,    -1,   140,    85,   142,    77,    -1,     1,    77,    -1,
     145,    -1,   145,    -1,   141,     7,   145,    -1,   142,     3,
      81,   126,    82,    -1,   142,     7,   142,    -1,   142,     6,
     142,    -1,   142,     5,   142,    -1,   142,     4,   142,    -1,
     142,     8,   142,    -1,   143,    -1,   143,    17,   143,    -1,
     143,    16,   143,    -1,   143,    24,   143,    -1,   143,    23,
     143,    -1,   143,    22,   143,    -1,   143,    25,   143,    -1,
     143,    26,   143,    -1,   143,    27,    -1,   143,    28,   145,
      -1,   143,    21,   143,    -1,   143,    15,   143,    -1,   143,
      20,   143,    -1,   143,    19,   143,    -1,   143,    18,   143,
      -1,   143,    14,   143,    -1,   143,    13,   143,    -1,   143,
      11,   143,    -1,   143,    10,   143,    -1,   143,    12,   143,
      -1,   143,     9,   143,    -1,   143,    79,   147,    80,    -1,
     143,    83,   126,    84,    -1,   144,    -1,    72,    -1,    73,
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
      -1,   145,    -1,    16,   145,    -1,    79,   142,    80,    -1,
      74,    79,   141,    80,    28,    79,   142,    80,    -1,   101,
      81,   174,    82,    -1,   158,    -1,   159,    -1,   160,    -1,
      87,    79,   150,    80,    -1,    88,    79,   150,    80,    -1,
      89,    81,   126,    82,    -1,   161,    -1,   162,    -1,   163,
      -1,   164,    -1,   165,    -1,   166,    -1,   167,    -1,   168,
      -1,   169,    -1,   170,    -1,   152,    -1,   153,    -1,   154,
      -1,   155,    -1,   156,    -1,   157,    -1,    98,    -1,    98,
      -1,   148,    -1,   147,     7,   148,    -1,   148,     6,   148,
      -1,   148,     5,   148,    -1,   148,     4,   148,    -1,   148,
       8,   148,    -1,   143,    -1,    96,    -1,    96,    -1,    96,
      -1,    97,    -1,    90,    79,   145,     7,   148,     7,   142,
      80,    -1,    91,    79,   145,     7,   148,     7,   142,    80,
      -1,    92,    79,   145,     7,   148,     7,   142,    80,    -1,
      93,    79,   145,     7,   148,     7,   142,    80,    -1,    94,
      79,   142,    80,    -1,    95,    79,   142,    80,    -1,    34,
      79,   171,     7,   151,     7,   149,    80,    -1,    35,    79,
     176,   146,     7,   151,    80,    -1,    36,    79,   176,   146,
       7,   151,    80,    -1,    37,    79,   150,    80,    -1,    38,
      79,   150,    80,    -1,    39,    79,   150,     7,   148,     7,
     148,     7,   148,     7,   148,    80,    -1,    40,    79,   150,
       7,   148,     7,   148,     7,   148,     7,   148,    80,    -1,
      41,    79,   150,     7,   148,     7,   148,     7,   148,     7,
     148,    80,    -1,    42,    79,   150,     7,   142,    80,    -1,
      43,    79,   150,     7,   142,    80,    -1,    44,    79,   150,
       7,   142,    80,    -1,    46,    79,   150,     7,   148,     7,
     148,    80,    -1,    45,    79,   150,     7,   148,     7,   148,
      80,    -1,   176,   172,    79,   173,    80,    -1,   176,   172,
      15,   172,    79,   173,    80,    -1,   176,   172,    15,   172,
      15,   172,    79,   173,    80,    -1,   176,   172,    79,    80,
      -1,   176,   172,    15,   172,    79,    80,    -1,   176,   172,
      15,   172,    15,   172,    79,    80,    -1,    98,    -1,   176,
      -1,   173,     7,   176,    -1,   175,    -1,   174,   175,    -1,
      79,   147,    80,   102,   142,    77,    -1,    32,    -1,    33,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   307,   307,   310,   311,   313,   314,   317,   318,   319,
     320,   323,   324,   327,   328,   329,   330,   331,   332,   335,
     336,   339,   342,   345,   348,   351,   352,   355,   356,   357,
     360,   361,   364,   367,   368,   369,   372,   375,   376,   379,
     380,   381,   382,   383,   384,   385,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   398,   399,   400,   402,   403,
     405,   406,   407,   408,   409,   410,   412,   413,   415,   418,
     419,   421,   422,   424,   425,   427,   428,   430,   431,   433,
     434,   436,   437,   438,   439,   440,   441,   443,   444,   445,
     447,   448,   450,   451,   452,   453,   454,   455,   457,   459,
     460,   461,   462,   463,   464,   465,   467,   468,   469,   470,
     471,   472,   474,   475,   476,   478,   479,   481,   482,   483,
     486,   487,   489,   490,   492,   493,   495,   496,   499,   501,
     502,   503,   504,   505,   506,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   519,   520,   521,   522,   524,
     525,   530,   533,   538,   539,   542,   543,   544,   545,   546,
     549,   552,   555,   556,   561,   565,   569,   573,   578,   581,
     588,   592,   595,   600,   603,   606,   609,   612,   615,   618,
     621,   625,   628,   635,   636,   637,   639,   640,   641,   644,
     647,   648,   651,   652,   655,   659,   660
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
  "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE",
  "CASE", "ARROW", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST",
  "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE", "LISTING",
  "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm",
  "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "defname", "params", "expression", "infixexp", "primitive",
  "ident", "name", "arglist", "argument", "string", "uqstring", "fstring",
  "fpar", "fseq", "fsum", "fprod", "finputs", "foutputs", "ffunction",
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
     375,   376,   377
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   123,   124,   125,   125,   126,   126,   127,   127,   127,
     127,   128,   128,   129,   129,   129,   129,   129,   129,   130,
     130,   131,   132,   133,   134,   135,   135,   136,   136,   136,
     137,   137,   138,   139,   139,   139,   140,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   146,   147,   147,   148,   148,   148,   148,   148,
     149,   150,   151,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   171,   171,   171,   171,   171,   172,
     173,   173,   174,   174,   175,   176,   176
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       8,     7,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     5,     7,     9,     4,     6,     8,     1,
       1,     3,     1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   151,     0,    11,     4,
       9,     0,    36,    35,     0,   152,     0,    19,     0,     0,
     161,     0,   160,     0,    10,     0,     0,    25,     0,    23,
      12,    13,    14,    15,    16,    17,    18,    97,    95,    94,
      96,    93,    92,    88,    82,    81,    91,    90,    89,    87,
      85,    84,    83,   109,    86,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    69,    70,     0,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,    68,   124,     0,   153,   145,   146,
     147,   148,   149,   150,   129,   130,   131,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,     0,    45,     0,
       8,     0,     0,     0,     0,    20,    73,    74,   125,    71,
      72,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     7,    21,    22,    24,     0,     0,     0,    26,    32,
     195,   196,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     192,    65,    63,    62,    64,    61,    60,    56,    47,    46,
      59,    58,    57,    55,    50,    49,    48,    51,    52,    54,
       0,     0,   154,     0,   157,   156,   155,   158,     5,    43,
      42,    41,    40,    44,     0,     0,     0,     0,   189,     0,
       0,     0,   173,   174,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,   133,   134,     6,     0,     0,
       0,     0,   168,   169,     0,   128,   193,    66,    67,     0,
       0,     0,     0,     0,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,    33,    39,    30,    31,
       0,     0,     0,     0,     0,   186,     0,   190,     0,     0,
       0,     0,     0,   178,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,    29,     0,     0,     0,
       0,   183,   171,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   170,     0,   187,     0,   191,
       0,     0,     0,   182,   181,   127,   164,   165,   166,   167,
     194,     0,   184,     0,     0,     0,   188,     0,     0,     0,
       0,   185,     0,     0,     0,   175,   176,   177
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   241,     9,    17,    30,    31,    32,    33,
      34,    35,   143,   218,   350,    36,   307,    11,   236,   137,
     113,   114,   115,    16,   116,   117,    23,    21,   326,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   222,   289,
     356,   249,   250,   357
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -282
static const yytype_int16 yypact[] =
{
    -282,    51,    33,  -282,    -7,    13,  -282,   -13,  -282,  -282,
    -282,     8,  -282,  -282,    -2,  -282,    38,   226,   367,   367,
    -282,    57,  -282,   117,  -282,   367,   367,  -282,   -13,  -282,
    -282,    40,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,   108,    28,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,   106,
     137,   142,   144,   147,   155,   174,   188,   195,   249,   257,
     260,   262,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,   267,
    -282,  -282,   367,   374,   387,   111,   388,   432,   433,   434,
     435,   437,   132,   460,  -282,  -282,    23,   358,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,   278,   460,   225,
    -282,    18,     6,   224,   139,  -282,  -282,  -282,  -282,  -282,
    -282,   200,   200,   200,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,   250,    35,    -2,    -2,  -282,   250,
     250,   250,   250,   367,   367,   438,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   367,  -282,   250,   367,  -282,   367,   445,
     367,   367,   367,   367,   450,   367,   367,   367,   367,   367,
    -282,  -282,  -282,  -282,  -282,   397,   419,   420,  -282,  -282,
    -282,  -282,   535,   451,   -13,   -13,   470,   471,   545,   547,
     548,   549,   551,   552,   553,   555,    29,  -282,  -282,   483,
     484,     4,   614,   615,   616,   617,    41,    49,   367,   133,
    -282,   474,   474,   474,   474,   474,   474,   286,   286,   286,
     424,   424,   424,   424,   424,   424,   424,   482,   436,  -282,
      43,     7,   358,   367,   358,   358,    82,  -282,  -282,   289,
     289,   498,   269,  -282,   503,   504,   505,   271,  -282,    16,
     621,   622,  -282,  -282,   367,   367,   367,   367,   367,   367,
     367,   367,   250,   603,  -282,  -282,  -282,  -282,   367,   367,
     367,   367,  -282,  -282,    71,  -282,  -282,  -282,  -282,   284,
      34,   328,   328,   328,  -282,  -282,   623,   451,   170,   271,
     271,   312,   352,   530,    55,    61,    69,   540,   562,  -282,
     554,   567,   572,   577,   582,   532,  -282,  -282,  -282,  -282,
     510,   513,   514,    38,    17,  -282,    72,  -282,   557,   558,
     367,   367,   367,  -282,  -282,  -282,   367,   367,   367,   367,
     367,   367,   367,   367,  -282,  -282,  -282,   559,   451,   172,
     200,  -282,  -282,  -282,   587,   592,   597,    76,   102,   140,
     235,   241,   252,   258,   319,  -282,   561,  -282,   113,  -282,
     367,   367,   367,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,   192,  -282,   602,   607,   612,  -282,   115,   367,   367,
     367,  -282,   134,   223,   265,  -282,  -282,  -282
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -282,  -282,  -282,  -181,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,   125,  -282,   639,  -282,  -282,     2,
     -19,  -282,    27,   -24,  -159,  -183,   290,   366,    65,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -228,
    -281,  -282,   393,  -150
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     138,   223,   224,   225,   144,     4,   138,   138,     4,   204,
     205,   206,   207,   208,   209,   272,   271,   274,   275,   276,
     277,   204,   205,   206,   207,   208,   209,   141,   142,    12,
     198,   327,   378,    -2,     4,     4,   302,   270,   204,   205,
     206,   207,   208,   209,   204,   205,   206,   207,   208,   209,
     198,     3,   204,   205,   206,   207,   208,   209,   204,   205,
     206,   207,   208,   209,   204,   205,   206,   207,   208,   209,
      13,   148,   204,   205,   206,   207,   208,   209,   198,   380,
     200,   201,   202,   138,   203,    15,   306,    18,   202,   314,
     203,   318,    14,    19,    20,   328,   379,   320,   398,   354,
     149,   150,     6,   199,   165,     6,   200,   201,   202,   303,
     203,   331,   332,   333,   213,   238,   347,   337,   338,     5,
     380,   312,   380,   317,   212,   341,   342,   343,   344,   313,
     417,     6,     6,     7,    22,   363,     8,   139,   200,   201,
     202,   364,   203,   204,   205,   206,   207,   208,   209,   365,
     396,   345,   381,   145,   138,   138,   403,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   246,   247,   384,   385,   386,
     146,   147,   404,   387,   388,   151,   138,   138,   138,   138,
     138,   237,   168,   412,   140,   421,   242,   243,   244,   245,
     290,   291,   220,   221,   220,   221,     6,   279,   280,   281,
     282,   283,   248,   175,   425,   315,   152,   413,   414,   415,
     405,   153,   269,   154,   220,   221,   155,   200,   201,   202,
     399,   203,   220,   221,   156,   422,   423,   424,   204,   205,
     206,   207,   208,   209,   204,   205,   206,   207,   208,   209,
     355,   219,   397,   157,   138,   204,   205,   206,   207,   208,
     209,   204,   205,   206,   207,   208,   209,   158,    12,   200,
     201,   202,   416,   203,   159,   319,   208,   209,   138,   138,
     138,   204,   205,   206,   207,   208,   209,   204,   205,   206,
     207,   208,   209,   205,   206,   207,   208,   209,    12,   334,
     335,   336,   211,   426,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   406,   200,   201,   202,   360,
     203,   407,   204,   205,   206,   207,   208,   209,   160,   339,
      24,    25,   408,    26,   214,    27,   161,    28,   409,   162,
      29,   163,   215,   216,   217,   427,   164,    12,     6,   138,
     138,   138,   138,   138,   138,   210,   200,   201,   202,   361,
     203,   346,   200,   201,   202,   196,   203,   324,   325,   197,
     389,   390,   391,   392,   393,   394,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   358,   359,   410,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   348,   349,   102,   351,   352,   192,
     193,   194,   195,   166,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   194,   195,     6,   167,   169,   112,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   207,   208,   209,   197,   193,   194,
     195,   170,   171,   172,   173,   196,   174,   248,   284,   197,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     273,   278,   239,   240,   200,   201,   202,   362,   203,   196,
     285,   286,   287,   197,   200,   201,   202,   366,   203,   288,
     292,   293,   294,   196,   295,   296,   297,   197,   298,   299,
     300,   196,   301,   304,   305,   197,   200,   201,   202,   367,
     203,   200,   201,   202,   369,   203,   200,   201,   202,   370,
     203,   200,   201,   202,   371,   203,   200,   201,   202,   372,
     203,   200,   201,   202,   400,   203,   200,   201,   202,   401,
     203,   200,   201,   202,   402,   203,   200,   201,   202,   418,
     203,   200,   201,   202,   419,   203,   200,   201,   202,   420,
     203,   308,   309,   310,   311,   321,   322,   323,   329,   330,
     353,   340,   374,   368,   373,   375,   376,   382,   383,   395,
     411,    10,   316,   377
};

static const yytype_uint16 yycheck[] =
{
      19,   151,   152,   153,    28,     1,    25,    26,     1,     3,
       4,     5,     6,     7,     8,   198,   197,   200,   201,   202,
     203,     3,     4,     5,     6,     7,     8,    25,    26,     2,
       7,    15,    15,     0,     1,     1,     7,   196,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       7,     0,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
      77,    44,     3,     4,     5,     6,     7,     8,     7,     7,
       4,     5,     6,   102,     8,    98,    82,    79,     6,   248,
       8,    84,    79,    85,    96,    79,    79,   278,   379,   327,
      72,    73,    98,    80,   102,    98,     4,     5,     6,    80,
       8,   294,   295,   296,   108,    80,    82,   300,   301,    86,
       7,    80,     7,    80,   106,   308,   309,   310,   311,    80,
     411,    98,    98,   100,    96,    80,   103,    80,     4,     5,
       6,    80,     8,     3,     4,     5,     6,     7,     8,    80,
     378,    80,    80,   113,   173,   174,    80,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   173,   174,   360,   361,   362,
      72,    73,    80,   366,   367,    79,   205,   206,   207,   208,
     209,   164,    81,    80,    77,    80,   169,   170,   171,   172,
     224,   225,    32,    33,    32,    33,    98,   205,   206,   207,
     208,   209,    79,    81,    80,    82,    79,   400,   401,   402,
      80,    79,   195,    79,    32,    33,    79,     4,     5,     6,
     380,     8,    32,    33,    79,   418,   419,   420,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
      80,   112,    80,    79,   273,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,    79,   241,     4,
       5,     6,    80,     8,    79,   273,     7,     8,   297,   298,
     299,     3,     4,     5,     6,     7,     8,     3,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,   271,   297,
     298,   299,    77,    80,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    80,     4,     5,     6,     7,
       8,    80,     3,     4,     5,     6,     7,     8,    79,   302,
     104,   105,    80,   107,   110,   109,    79,   111,    80,    79,
     114,    79,   118,   119,   120,    80,    79,   320,    98,   368,
     369,   370,   371,   372,   373,    77,     4,     5,     6,     7,
       8,    77,     4,     5,     6,    79,     8,    96,    97,    83,
     368,   369,   370,   371,   372,   373,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   329,   330,    77,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   116,   117,    79,   322,   323,    25,
      26,    27,    28,    79,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    27,    28,    98,    79,    79,   101,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    79,     6,     7,     8,    83,    26,    27,
      28,    79,    79,    79,    79,    79,    79,    79,   121,    83,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      85,    81,   166,   167,     4,     5,     6,     7,     8,    79,
     121,   121,     7,    83,     4,     5,     6,     7,     8,    98,
      80,    80,     7,    79,     7,     7,     7,    83,     7,     7,
       7,    79,     7,    80,    80,    83,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     7,     7,     7,     7,   122,   122,   122,     7,     7,
       7,    28,   122,    79,   102,   122,   122,    80,    80,    80,
      79,     2,   249,   353
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   124,   125,     0,     1,    86,    98,   100,   103,   127,
     139,   140,   145,    77,    79,    98,   146,   128,    79,    85,
      96,   150,    96,   149,   104,   105,   107,   109,   111,   114,
     129,   130,   131,   132,   133,   134,   138,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      94,    95,   101,   143,   144,   145,   147,   148,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   142,   143,    80,
      77,   142,   142,   135,   146,   113,    72,    73,   145,    72,
      73,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,   142,    79,    79,    81,    79,
      79,    79,    79,    79,    79,    81,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    79,    83,     7,    80,
       4,     5,     6,     8,     3,     4,     5,     6,     7,     8,
      77,    77,   106,   108,   110,   118,   119,   120,   136,   112,
      32,    33,   171,   176,   176,   176,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   141,   145,    80,   150,
     150,   126,   145,   145,   145,   145,   142,   142,    79,   174,
     175,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   145,
     147,   126,   148,    85,   148,   148,   148,   148,    81,   142,
     142,   142,   142,   142,   121,   121,   121,     7,    98,   172,
     146,   146,    80,    80,     7,     7,     7,     7,     7,     7,
       7,     7,     7,    80,    80,    80,    82,   139,     7,     7,
       7,     7,    80,    80,   147,    82,   175,    80,    84,   142,
     126,   122,   122,   122,    96,    97,   151,    15,    79,     7,
       7,   148,   148,   148,   142,   142,   142,   148,   148,   145,
      28,   148,   148,   148,   148,    80,    77,    82,   116,   117,
     137,   137,   137,     7,   172,    80,   173,   176,   151,   151,
       7,     7,     7,    80,    80,    80,     7,     7,    79,     7,
       7,     7,     7,   102,   122,   122,   122,   149,    15,    79,
       7,    80,    80,    80,   148,   148,   148,   148,   148,   142,
     142,   142,   142,   142,   142,    80,   172,    80,   173,   176,
       7,     7,     7,    80,    80,    80,    80,    80,    80,    80,
      77,    79,    80,   148,   148,   148,    80,   173,     7,     7,
       7,    80,   148,   148,   148,    80,    80,    80
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 307 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 310 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 4:
#line 311 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:
#line 313 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 6:
#line 314 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 7:
#line 317 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:
#line 318 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:
#line 319 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 10:
#line 320 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 11:
#line 323 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 12:
#line 324 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 13:
#line 327 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 14:
#line 328 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 15:
#line 329 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 330 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 17:
#line 331 "parser/faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 18:
#line 332 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 19:
#line 335 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 20:
#line 336 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); ;}
    break;

  case 21:
#line 339 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 22:
#line 342 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 23:
#line 345 "parser/faustparser.y"
    { ;}
    break;

  case 24:
#line 348 "parser/faustparser.y"
    { ;}
    break;

  case 25:
#line 351 "parser/faustparser.y"
    { ;}
    break;

  case 26:
#line 352 "parser/faustparser.y"
    { ;}
    break;

  case 27:
#line 355 "parser/faustparser.y"
    { gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 28:
#line 356 "parser/faustparser.y"
    { gStripDocSwitch = (yyvsp[(4) - (5)].b); gStripDocSwitch==true ? gStripDocSwitch=false : gStripDocSwitch=true; ;}
    break;

  case 29:
#line 357 "parser/faustparser.y"
    { gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 30:
#line 360 "parser/faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 31:
#line 361 "parser/faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 32:
#line 364 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 33:
#line 367 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 34:
#line 368 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 35:
#line 369 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; ;}
    break;

  case 36:
#line 372 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 37:
#line 375 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 38:
#line 376 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 39:
#line 379 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 40:
#line 380 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 41:
#line 381 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 42:
#line 382 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 43:
#line 383 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 44:
#line 384 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 45:
#line 385 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 46:
#line 388 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 47:
#line 389 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 48:
#line 390 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 49:
#line 391 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 50:
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 51:
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); ;}
    break;

  case 52:
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 53:
#line 395 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 54:
#line 396 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 55:
#line 398 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 56:
#line 399 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 57:
#line 400 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 58:
#line 402 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 59:
#line 403 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 60:
#line 405 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 61:
#line 406 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 62:
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 63:
#line 408 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 64:
#line 409 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 65:
#line 410 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 66:
#line 412 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 67:
#line 413 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 68:
#line 415 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 69:
#line 418 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); ;}
    break;

  case 70:
#line 419 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 71:
#line 421 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); ;}
    break;

  case 72:
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 73:
#line 424 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); ;}
    break;

  case 74:
#line 425 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); ;}
    break;

  case 75:
#line 427 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 76:
#line 428 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 77:
#line 430 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 78:
#line 431 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 79:
#line 433 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 80:
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 81:
#line 436 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 82:
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 83:
#line 438 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 84:
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 85:
#line 440 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 86:
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); ;}
    break;

  case 87:
#line 443 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 88:
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 89:
#line 445 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 90:
#line 447 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 91:
#line 448 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); ;}
    break;

  case 92:
#line 450 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 93:
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 94:
#line 452 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 95:
#line 453 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 96:
#line 454 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 97:
#line 455 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 98:
#line 457 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 99:
#line 459 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 100:
#line 460 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 101:
#line 461 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 102:
#line 462 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 103:
#line 463 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); ;}
    break;

  case 104:
#line 464 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); ;}
    break;

  case 105:
#line 465 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); ;}
    break;

  case 106:
#line 467 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); ;}
    break;

  case 107:
#line 468 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); ;}
    break;

  case 108:
#line 469 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 109:
#line 470 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 110:
#line 471 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 111:
#line 472 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 112:
#line 474 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 113:
#line 475 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); ;}
    break;

  case 114:
#line 476 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 115:
#line 478 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 116:
#line 479 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 117:
#line 481 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 118:
#line 482 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 119:
#line 483 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); ;}
    break;

  case 120:
#line 486 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 121:
#line 487 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 122:
#line 489 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 123:
#line 490 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 124:
#line 492 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 125:
#line 493 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 126:
#line 495 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 127:
#line 497 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 128:
#line 499 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 129:
#line 501 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 130:
#line 502 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 131:
#line 503 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 132:
#line 504 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 133:
#line 505 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 134:
#line 506 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 135:
#line 508 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 136:
#line 509 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 137:
#line 510 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 138:
#line 511 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 139:
#line 512 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 140:
#line 513 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 141:
#line 514 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 142:
#line 515 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 143:
#line 516 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 144:
#line 517 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 145:
#line 519 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 146:
#line 520 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 147:
#line 521 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 148:
#line 522 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 149:
#line 524 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 150:
#line 525 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 151:
#line 530 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); ;}
    break;

  case 152:
#line 533 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 153:
#line 538 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 154:
#line 539 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 155:
#line 542 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 156:
#line 543 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 157:
#line 544 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 158:
#line 545 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 159:
#line 546 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 160:
#line 549 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 161:
#line 552 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); ;}
    break;

  case 162:
#line 555 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 163:
#line 556 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 164:
#line 562 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 165:
#line 566 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 166:
#line 570 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 167:
#line 574 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 168:
#line 578 "parser/faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 169:
#line 581 "parser/faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 170:
#line 589 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 171:
#line 593 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 172:
#line 596 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 173:
#line 600 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 174:
#line 603 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 175:
#line 607 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 176:
#line 610 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 177:
#line 613 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 178:
#line 616 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 179:
#line 619 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 180:
#line 622 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 181:
#line 626 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 182:
#line 629 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 183:
#line 635 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),nil))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 184:
#line 636 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp), cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),nil))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 185:
#line 637 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp), cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),nil))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 186:
#line 639 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),nil))), nil)); ;}
    break;

  case 187:
#line 640 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp), cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),nil))), nil)); ;}
    break;

  case 188:
#line 641 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp), cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),nil))), nil)); ;}
    break;

  case 189:
#line 644 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 190:
#line 647 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 191:
#line 648 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 192:
#line 651 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 193:
#line 652 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 194:
#line 656 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 195:
#line 659 "parser/faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 196:
#line 660 "parser/faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3042 "parser/faustparser.cpp"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 663 "parser/faustparser.y"



