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
     FDELAY = 280,
     DELAY1 = 281,
     DOT = 282,
     APPL = 283,
     MEM = 284,
     PREFIX = 285,
     INTCAST = 286,
     FLOATCAST = 287,
     FFUNCTION = 288,
     FCONSTANT = 289,
     BUTTON = 290,
     CHECKBOX = 291,
     VSLIDER = 292,
     HSLIDER = 293,
     NENTRY = 294,
     VGROUP = 295,
     HGROUP = 296,
     TGROUP = 297,
     HBARGRAPH = 298,
     VBARGRAPH = 299,
     ATTACH = 300,
     ACOS = 301,
     ASIN = 302,
     ATAN = 303,
     ATAN2 = 304,
     COS = 305,
     SIN = 306,
     TAN = 307,
     EXP = 308,
     LOG = 309,
     LOG10 = 310,
     POW = 311,
     SQRT = 312,
     ABS = 313,
     MIN = 314,
     MAX = 315,
     FMOD = 316,
     REMAINDER = 317,
     FLOOR = 318,
     CEIL = 319,
     RINT = 320,
     RDTBL = 321,
     RWTBL = 322,
     SELECT2 = 323,
     SELECT3 = 324,
     INT = 325,
     FLOAT = 326,
     LAMBDA = 327,
     WIRE = 328,
     CUT = 329,
     ENDDEF = 330,
     VIRG = 331,
     LPAR = 332,
     RPAR = 333,
     LBRAQ = 334,
     RBRAQ = 335,
     DEF = 336,
     IMPORT = 337,
     COMPONENT = 338,
     IPAR = 339,
     ISEQ = 340,
     ISUM = 341,
     IPROD = 342,
     STRING = 343,
     FSTRING = 344,
     IDENT = 345,
     EXTRA = 346,
     DECLARE = 347,
     NAMEPROP = 348,
     AUTHORPROP = 349,
     COPYRIGHTPROP = 350,
     VERSIONPROP = 351,
     LICENSEPROP = 352,
     CASE = 353,
     ARROW = 354
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
#define FDELAY 280
#define DELAY1 281
#define DOT 282
#define APPL 283
#define MEM 284
#define PREFIX 285
#define INTCAST 286
#define FLOATCAST 287
#define FFUNCTION 288
#define FCONSTANT 289
#define BUTTON 290
#define CHECKBOX 291
#define VSLIDER 292
#define HSLIDER 293
#define NENTRY 294
#define VGROUP 295
#define HGROUP 296
#define TGROUP 297
#define HBARGRAPH 298
#define VBARGRAPH 299
#define ATTACH 300
#define ACOS 301
#define ASIN 302
#define ATAN 303
#define ATAN2 304
#define COS 305
#define SIN 306
#define TAN 307
#define EXP 308
#define LOG 309
#define LOG10 310
#define POW 311
#define SQRT 312
#define ABS 313
#define MIN 314
#define MAX 315
#define FMOD 316
#define REMAINDER 317
#define FLOOR 318
#define CEIL 319
#define RINT 320
#define RDTBL 321
#define RWTBL 322
#define SELECT2 323
#define SELECT3 324
#define INT 325
#define FLOAT 326
#define LAMBDA 327
#define WIRE 328
#define CUT 329
#define ENDDEF 330
#define VIRG 331
#define LPAR 332
#define RPAR 333
#define LBRAQ 334
#define RBRAQ 335
#define DEF 336
#define IMPORT 337
#define COMPONENT 338
#define IPAR 339
#define ISEQ 340
#define ISUM 341
#define IPROD 342
#define STRING 343
#define FSTRING 344
#define IDENT 345
#define EXTRA 346
#define DECLARE 347
#define NAMEPROP 348
#define AUTHORPROP 349
#define COPYRIGHTPROP 350
#define VERSIONPROP 351
#define LICENSEPROP 352
#define CASE 353
#define ARROW 354




/* Copy the first part of user declarations.  */
#line 4 "parser/faustparser.y"


#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
#include "signals.hh"
#include "errormsg.hh"
#include "sourcereader.hh"

#include <string>
#include <list>

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMAXDEPTH	100000

extern char* 		yytext;
extern const char* 	yyfilename;
extern int 			yylineno;
extern int 			yyerr;
extern Tree 		gResult;

// extern list<string>	gNameProperty;
// extern list<string>	gAuthorProperty;
// extern list<string>	gCopyrightProperty;
// extern list<string>	gVersionProperty;
// extern list<string>	gLicenseProperty;

extern map<Tree, set<Tree> > gMetaDataSet;

int yylex();

Tree unquote(char* str)
{
	//-----------copy unquoted filename-------------
	char buf[512];
	int j=0;

	if (str[0] == '"') {
		//it is a quoted string, we remove the quotes
		for (int i=1; j<511 && str[i];) {
			buf[j++] = str[i++];
		}
		// remove last quote
		if (j>0) buf[j-1] = 0;
	} else {
		for (int i=0; j<511 && str[i];) {
			buf[j++] = str[i++];
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
#line 64 "parser/faustparser.y"
{
	CTree* 	exp;
}
/* Line 187 of yacc.c.  */
#line 357 "parser/faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 370 "parser/faustparser.cpp"

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
#define YYLAST   516

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNRULES -- Number of states.  */
#define YYNSTATES  339

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   354

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
      95,    96,    97,    98,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    17,    22,    28,    33,
      36,    38,    40,    44,    50,    54,    58,    62,    66,    70,
      72,    76,    80,    84,    88,    92,    96,    99,   103,   107,
     111,   115,   119,   123,   127,   131,   135,   139,   143,   147,
     152,   154,   156,   158,   161,   164,   167,   170,   172,   174,
     176,   178,   180,   182,   184,   186,   188,   190,   192,   194,
     196,   198,   200,   202,   204,   206,   208,   210,   212,   214,
     216,   218,   220,   222,   224,   226,   228,   230,   232,   234,
     236,   238,   240,   242,   244,   246,   248,   250,   252,   254,
     256,   258,   260,   262,   264,   266,   268,   272,   281,   286,
     288,   290,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   323,   325,   327,   329,
     333,   337,   341,   345,   349,   351,   353,   355,   357,   359,
     368,   377,   386,   395,   404,   412,   417,   422,   435,   448,
     461,   468,   475,   482,   491,   500,   506,   511,   513,   515,
     519,   521,   524,   531,   533
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     101,     0,    -1,   102,    -1,    -1,   102,   103,    -1,   104,
      77,   111,    78,    81,   106,    75,    -1,   104,    81,   106,
      75,    -1,    82,    77,   114,    78,    75,    -1,    92,   110,
     113,    75,    -1,     1,    75,    -1,   109,    -1,   109,    -1,
     105,     7,   109,    -1,   106,     3,    79,   102,    80,    -1,
     106,     7,   106,    -1,   106,     6,   106,    -1,   106,     5,
     106,    -1,   106,     4,   106,    -1,   106,     8,   106,    -1,
     107,    -1,   107,    17,   107,    -1,   107,    16,   107,    -1,
     107,    24,   107,    -1,   107,    23,   107,    -1,   107,    22,
     107,    -1,   107,    25,   107,    -1,   107,    26,    -1,   107,
      27,   109,    -1,   107,    21,   107,    -1,   107,    15,   107,
      -1,   107,    20,   107,    -1,   107,    19,   107,    -1,   107,
      18,   107,    -1,   107,    14,   107,    -1,   107,    13,   107,
      -1,   107,    11,   107,    -1,   107,    10,   107,    -1,   107,
      12,   107,    -1,   107,     9,   107,    -1,   107,    77,   111,
      78,    -1,   108,    -1,    70,    -1,    71,    -1,    17,    70,
      -1,    17,    71,    -1,    16,    70,    -1,    16,    71,    -1,
      73,    -1,    74,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    17,    -1,    16,    -1,    24,    -1,    23,    -1,
      22,    -1,    25,    -1,    21,    -1,    15,    -1,    20,    -1,
      19,    -1,    18,    -1,    14,    -1,    13,    -1,    11,    -1,
      10,    -1,    12,    -1,     9,    -1,    45,    -1,    46,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    68,    -1,    69,    -1,   109,    -1,    77,   106,
      78,    -1,    72,    77,   105,    78,    27,    77,   106,    78,
      -1,    98,    79,   135,    80,    -1,   120,    -1,   121,    -1,
      83,    77,   114,    78,    -1,   122,    -1,   123,    -1,   124,
      -1,   125,    -1,   126,    -1,   127,    -1,   128,    -1,   129,
      -1,   130,    -1,   131,    -1,   116,    -1,   117,    -1,   118,
      -1,   119,    -1,    90,    -1,    90,    -1,   112,    -1,   111,
       7,   112,    -1,   112,     6,   112,    -1,   112,     5,   112,
      -1,   112,     4,   112,    -1,   112,     8,   112,    -1,   107,
      -1,    88,    -1,    88,    -1,    88,    -1,    89,    -1,    84,
      77,   109,     7,   112,     7,   106,    78,    -1,    85,    77,
     109,     7,   112,     7,   106,    78,    -1,    86,    77,   109,
       7,   112,     7,   106,    78,    -1,    87,    77,   109,     7,
     112,     7,   106,    78,    -1,    33,    77,   132,     7,   115,
       7,   113,    78,    -1,    34,    77,   137,   110,     7,   115,
      78,    -1,    35,    77,   113,    78,    -1,    36,    77,   113,
      78,    -1,    37,    77,   113,     7,   112,     7,   112,     7,
     112,     7,   112,    78,    -1,    38,    77,   113,     7,   112,
       7,   112,     7,   112,     7,   112,    78,    -1,    39,    77,
     113,     7,   112,     7,   112,     7,   112,     7,   112,    78,
      -1,    40,    77,   113,     7,   106,    78,    -1,    41,    77,
     113,     7,   106,    78,    -1,    42,    77,   113,     7,   106,
      78,    -1,    44,    77,   113,     7,   112,     7,   112,    78,
      -1,    43,    77,   113,     7,   112,     7,   112,    78,    -1,
     137,   133,    77,   134,    78,    -1,   137,   133,    77,    78,
      -1,    90,    -1,   137,    -1,   134,     7,   137,    -1,   136,
      -1,   135,   136,    -1,    77,   111,    78,    99,   106,    75,
      -1,    31,    -1,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   246,   246,   249,   250,   256,   257,   258,   259,   260,
     263,   266,   267,   270,   271,   272,   273,   274,   275,   276,
     279,   280,   281,   282,   283,   284,   285,   286,   288,   289,
     290,   292,   293,   295,   296,   297,   298,   299,   300,   302,
     304,   307,   308,   310,   311,   313,   314,   316,   317,   319,
     320,   322,   323,   325,   326,   327,   328,   329,   330,   332,
     333,   334,   336,   337,   339,   340,   341,   342,   343,   344,
     346,   348,   349,   350,   351,   352,   353,   354,   356,   357,
     358,   359,   360,   362,   363,   364,   366,   367,   369,   370,
     371,   374,   375,   377,   378,   380,   382,   383,   386,   388,
     389,   390,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   403,   404,   405,   406,   410,   413,   418,   419,
     422,   423,   424,   425,   426,   429,   432,   435,   436,   441,
     445,   449,   453,   460,   464,   469,   472,   475,   478,   481,
     484,   487,   490,   494,   497,   502,   503,   506,   509,   510,
     513,   514,   517,   521,   522
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "MIX", "SPLIT", "SEQ", "PAR",
  "REC", "NE", "GE", "GT", "EQ", "LE", "LT", "OR", "SUB", "ADD", "RSH",
  "LSH", "XOR", "AND", "MOD", "DIV", "MUL", "FDELAY", "DELAY1", "DOT",
  "APPL", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "FFUNCTION",
  "FCONSTANT", "BUTTON", "CHECKBOX", "VSLIDER", "HSLIDER", "NENTRY",
  "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH", "VBARGRAPH", "ATTACH", "ACOS",
  "ASIN", "ATAN", "ATAN2", "COS", "SIN", "TAN", "EXP", "LOG", "LOG10",
  "POW", "SQRT", "ABS", "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL",
  "RINT", "RDTBL", "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA",
  "WIRE", "CUT", "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "DEF",
  "IMPORT", "COMPONENT", "IPAR", "ISEQ", "ISUM", "IPROD", "STRING",
  "FSTRING", "IDENT", "EXTRA", "DECLARE", "NAMEPROP", "AUTHORPROP",
  "COPYRIGHTPROP", "VERSIONPROP", "LICENSEPROP", "CASE", "ARROW",
  "$accept", "program", "eqlist", "equation", "eqname", "params",
  "diagram", "expression", "primitive", "ident", "name", "arglist",
  "argument", "string", "uqstring", "fstring", "fpar", "fseq", "fsum",
  "fprod", "ffunction", "fconst", "button", "checkbox", "vslider",
  "hslider", "nentry", "vgroup", "hgroup", "tgroup", "vbargraph",
  "hbargraph", "signature", "fun", "typelist", "rulelist", "rule", "type", 0
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   102,   102,   103,   103,   103,   103,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   110,   111,   111,
     112,   112,   112,   112,   112,   113,   114,   115,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   132,   133,   134,   134,
     135,   135,   136,   137,   137
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     7,     4,     5,     4,     2,
       1,     1,     3,     5,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     8,     4,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     8,
       8,     8,     8,     8,     7,     4,     4,    12,    12,    12,
       6,     6,     6,     8,     8,     5,     4,     1,     1,     3,
       1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   116,     0,     4,     0,
      10,     9,     0,   117,     0,     0,     0,   126,     0,   125,
       0,    69,    67,    66,    68,    65,    64,    60,    54,    53,
      63,    62,    61,    59,    57,    56,    55,    58,    49,    50,
      51,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    41,
      42,     0,    47,    48,     0,     0,     0,     0,     0,     0,
       0,   124,    40,    95,     0,   118,   112,   113,   114,   115,
      99,   100,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,    19,     0,     8,    45,    46,    43,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     7,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    96,     0,     0,     0,     0,     0,     0,     0,   150,
      38,    36,    35,    37,    34,    33,    29,    21,    20,    32,
      31,    30,    28,    24,    23,    22,    25,    27,     0,   119,
       0,   122,   121,   120,   123,     3,    17,    16,    15,    14,
      18,     0,   147,     0,     0,   135,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
       0,     0,     0,    98,   151,    39,     0,     0,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     5,    13,
       0,   146,     0,   148,     0,     0,     0,     0,   140,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   145,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   149,     0,     0,     0,   144,
     143,    97,   129,   130,   131,   132,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   138,   139
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,   189,   112,    91,    92,    93,
      14,    94,    95,    20,    18,   260,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   176,   233,   282,   198,   199,   177
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
    -119,     7,     4,  -119,   -73,    11,  -119,    93,  -119,   -10,
    -119,  -119,    96,  -119,    99,   274,   274,  -119,    44,  -119,
      35,  -119,  -119,  -119,  -119,  -119,  -119,  -119,    -1,    95,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,   123,   137,   144,   145,   146,   155,   175,   176,
     178,   179,   180,   190,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,   193,  -119,  -119,   274,   194,   199,   223,   224,   225,
     109,   387,  -119,  -119,    -6,    79,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,    48,   387,   170,  -119,  -119,  -119,  -119,  -119,
     118,   118,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   140,    20,    96,   140,   140,   140,   140,   272,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,  -119,   140,   274,
     274,   187,   274,   274,   274,   274,   271,   274,   274,   274,
     274,   274,  -119,  -119,  -119,  -119,   355,   265,    93,   285,
     293,   388,   418,   439,   441,   442,   443,   444,   446,     1,
    -119,  -119,   298,   447,   455,   456,   463,   274,    41,  -119,
     412,   412,   412,   412,   412,   412,   397,   397,   397,     5,
       5,     5,     5,     5,     5,     5,    32,  -119,     2,    79,
     274,    91,    91,   373,  -119,  -119,   205,   205,   161,   464,
    -119,    89,  -119,   394,   466,  -119,  -119,   274,   274,   274,
     274,   274,   274,   274,   274,   140,   458,  -119,   274,   274,
     274,   274,     3,  -119,  -119,  -119,   380,    21,  -119,  -119,
     479,    34,    89,    56,   202,   231,    30,    36,    42,   236,
     243,  -119,   410,   257,   437,   452,   461,   389,  -119,  -119,
      99,  -119,    22,  -119,   432,   274,   274,   274,  -119,  -119,
    -119,   274,   274,   274,   274,   274,   274,   274,   274,   433,
     118,  -119,  -119,   471,   476,   486,   111,   197,    70,   153,
     168,   191,   362,   386,  -119,  -119,   274,   274,   274,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,   491,   496,   501,
     274,   274,   274,   348,   369,   374,  -119,  -119,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,   287,  -119,  -119,  -119,   -78,   -16,  -119,     9,
     335,  -102,   -58,  -110,   381,   252,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,   318,  -118
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     113,   160,    11,   178,    -2,     4,   133,     3,   245,   160,
     160,    10,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,     4,   166,   167,   168,   169,   170,   171,   300,
     156,   157,   158,   166,   167,   168,   169,   170,   171,   166,
     167,   168,   169,   170,   171,   166,   167,   168,   169,   170,
     171,   166,   167,   168,   169,   170,   171,   218,   157,   158,
     162,   163,   164,   285,   165,   174,   175,    15,   113,   116,
     117,    16,   161,   166,   167,   168,   169,   170,   171,   246,
     255,   277,   159,   162,   163,   164,     5,   165,    12,   226,
     227,   228,   229,   230,     6,   252,     7,   164,   191,   165,
     301,   279,   219,     5,   221,   222,   223,   224,   288,   159,
     115,     6,   281,     7,   289,   162,   163,   164,   197,   165,
     290,   253,   114,   172,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   190,   256,   283,   193,   194,   195,   196,   321,   174,
     175,   113,   113,   113,   113,   113,   166,   167,   168,   169,
     170,   171,   266,   267,   268,   118,   119,   217,   170,   171,
     299,   166,   167,   168,   169,   170,   171,   258,   259,   263,
     264,   265,   315,    13,    17,   269,   270,    19,   139,   319,
     273,   274,   275,   276,   166,   167,   168,   169,   170,   171,
     120,   162,   163,   164,   113,   165,   162,   163,   164,   286,
     165,   169,   170,   171,   121,   308,   309,   310,   311,   312,
     313,   122,   123,   124,   113,   113,   113,   303,   304,   305,
       6,   322,   125,   306,   307,   162,   163,   164,   287,   165,
     162,   163,   164,   291,   165,   173,   323,   162,   163,   164,
     292,   165,   126,   127,   271,   128,   129,   130,   327,   328,
     329,   162,   163,   164,   294,   165,    10,   131,   220,   324,
     132,   134,   333,   334,   335,   320,   135,   113,   113,   113,
     113,   113,   113,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
     136,   137,   138,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   197,
     225,    84,   162,   163,   164,   232,   165,    85,    86,    87,
      88,    89,   231,   235,     6,   166,   167,   168,   169,   170,
     171,   236,    90,   162,   163,   164,   247,   165,   162,   163,
     164,   165,   165,   166,   167,   168,   169,   170,   171,   166,
     167,   168,   169,   170,   171,   237,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   238,   336,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     325,   162,   163,   164,   295,   165,   239,   337,   240,   241,
     242,   243,   338,   244,   248,   278,   162,   163,   164,   296,
     165,   326,   249,   250,   159,   162,   163,   164,   297,   165,
     251,   261,   171,   262,   159,   162,   163,   164,   316,   165,
     162,   163,   164,   317,   165,   272,   280,   293,   298,   159,
     162,   163,   164,   318,   165,   162,   163,   164,   330,   165,
     162,   163,   164,   331,   165,   162,   163,   164,   332,   165,
     302,   314,   257,   234,   284,   192,   254
};

static const yytype_uint16 yycheck[] =
{
      16,     7,    75,   121,     0,     1,    84,     0,     7,     7,
       7,     2,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,     1,     3,     4,     5,     6,     7,     8,     7,
      25,    26,    27,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,   159,    26,    27,
       4,     5,     6,     7,     8,    31,    32,    77,    84,    70,
      71,    81,    78,     3,     4,     5,     6,     7,     8,    78,
      78,    78,    77,     4,     5,     6,    82,     8,    77,   167,
     168,   169,   170,   171,    90,   197,    92,     6,    78,     8,
      78,    80,   160,    82,   162,   163,   164,   165,    78,    77,
      75,    90,    78,    92,    78,     4,     5,     6,    77,     8,
      78,    80,    78,    75,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   132,   220,   261,   135,   136,   137,   138,    78,    31,
      32,   167,   168,   169,   170,   171,     3,     4,     5,     6,
       7,     8,   240,   241,   242,    70,    71,   158,     7,     8,
     280,     3,     4,     5,     6,     7,     8,    88,    89,   237,
     238,   239,   300,    90,    88,   243,   244,    88,    79,    78,
     248,   249,   250,   251,     3,     4,     5,     6,     7,     8,
      77,     4,     5,     6,   220,     8,     4,     5,     6,     7,
       8,     6,     7,     8,    77,   293,   294,   295,   296,   297,
     298,    77,    77,    77,   240,   241,   242,   285,   286,   287,
      90,    78,    77,   291,   292,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    75,    78,     4,     5,     6,
       7,     8,    77,    77,   245,    77,    77,    77,   316,   317,
     318,     4,     5,     6,     7,     8,   257,    77,    81,    78,
      77,    77,   330,   331,   332,    78,    77,   293,   294,   295,
     296,   297,   298,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      77,    77,    77,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    77,
      79,    77,     4,     5,     6,    90,     8,    83,    84,    85,
      86,    87,     7,    78,    90,     3,     4,     5,     6,     7,
       8,    78,    98,     4,     5,     6,    78,     8,     4,     5,
       6,     8,     8,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     7,    78,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      78,     4,     5,     6,     7,     8,     7,    78,     7,     7,
       7,     7,    78,     7,     7,    75,     4,     5,     6,     7,
       8,    75,     7,     7,    77,     4,     5,     6,     7,     8,
       7,    77,     8,     7,    77,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    27,     7,    77,    99,    77,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
      78,    78,   225,   178,   262,   134,   198
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   101,   102,     0,     1,    82,    90,    92,   103,   104,
     109,    75,    77,    90,   110,    77,    81,    88,   114,    88,
     113,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    77,    83,    84,    85,    86,    87,
      98,   107,   108,   109,   111,   112,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   106,   107,    78,    75,    70,    71,    70,    71,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,   106,    77,    77,    77,    77,    77,    79,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    77,
       7,    78,     4,     5,     6,     8,     3,     4,     5,     6,
       7,     8,    75,    75,    31,    32,   132,   137,   137,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   105,
     109,    78,   114,   109,   109,   109,   109,    77,   135,   136,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   109,   111,   112,
      81,   112,   112,   112,   112,    79,   106,   106,   106,   106,
     106,     7,    90,   133,   110,    78,    78,     7,     7,     7,
       7,     7,     7,     7,     7,     7,    78,    78,     7,     7,
       7,     7,   111,    80,   136,    78,   106,   102,    88,    89,
     115,    77,     7,   112,   112,   112,   106,   106,   106,   112,
     112,   109,    27,   112,   112,   112,   112,    78,    75,    80,
       7,    78,   134,   137,   115,     7,     7,     7,    78,    78,
      78,     7,     7,    77,     7,     7,     7,     7,    99,   113,
       7,    78,    78,   112,   112,   112,   112,   112,   106,   106,
     106,   106,   106,   106,    78,   137,     7,     7,     7,    78,
      78,    78,    78,    78,    78,    78,    75,   112,   112,   112,
       7,     7,     7,   112,   112,   112,    78,    78,    78
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
#line 246 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 249 "parser/faustparser.y"
    {(yyval.exp) = nil; ;}
    break;

  case 4:
#line 250 "parser/faustparser.y"
    {(yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:
#line 256 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 6:
#line 257 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 7:
#line 258 "parser/faustparser.y"
    {(yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:
#line 259 "parser/faustparser.y"
    {gMetaDataSet[(yyvsp[(2) - (4)].exp)].insert((yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:
#line 260 "parser/faustparser.y"
    {(yyval.exp) = nil; yyerr++;;}
    break;

  case 10:
#line 263 "parser/faustparser.y"
    {(yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 11:
#line 266 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 12:
#line 267 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 13:
#line 270 "parser/faustparser.y"
    {(yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 14:
#line 271 "parser/faustparser.y"
    {(yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 15:
#line 272 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 16:
#line 273 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 17:
#line 274 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 18:
#line 275 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 19:
#line 276 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 20:
#line 279 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 21:
#line 280 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 22:
#line 281 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 23:
#line 282 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 24:
#line 283 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 25:
#line 284 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 26:
#line 285 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 27:
#line 286 "parser/faustparser.y"
    {(yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 28:
#line 288 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 29:
#line 289 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 30:
#line 290 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 31:
#line 292 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 32:
#line 293 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 33:
#line 295 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 34:
#line 296 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 35:
#line 297 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 36:
#line 298 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 37:
#line 299 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 38:
#line 300 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 39:
#line 302 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 40:
#line 304 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 41:
#line 307 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 42:
#line 308 "parser/faustparser.y"
    {(yyval.exp) = boxReal(float(atof(yytext)));;}
    break;

  case 43:
#line 310 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 44:
#line 311 "parser/faustparser.y"
    {(yyval.exp) = boxReal(float(atof(yytext)));;}
    break;

  case 45:
#line 313 "parser/faustparser.y"
    {(yyval.exp) = boxInt(0 - atoi(yytext));;}
    break;

  case 46:
#line 314 "parser/faustparser.y"
    {(yyval.exp) = boxReal(0.0f - float(atof(yytext)));;}
    break;

  case 47:
#line 316 "parser/faustparser.y"
    {(yyval.exp) = boxWire();;}
    break;

  case 48:
#line 317 "parser/faustparser.y"
    {(yyval.exp) = boxCut();;}
    break;

  case 49:
#line 319 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigDelay1);;}
    break;

  case 50:
#line 320 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigPrefix);;}
    break;

  case 51:
#line 322 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigIntCast);;}
    break;

  case 52:
#line 323 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigFloatCast);;}
    break;

  case 53:
#line 325 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAdd);;}
    break;

  case 54:
#line 326 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigSub);;}
    break;

  case 55:
#line 327 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigMul);;}
    break;

  case 56:
#line 328 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigDiv);;}
    break;

  case 57:
#line 329 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRem);;}
    break;

  case 58:
#line 330 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigFixDelay);;}
    break;

  case 59:
#line 332 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAND);;}
    break;

  case 60:
#line 333 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigOR);;}
    break;

  case 61:
#line 334 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigXOR);;}
    break;

  case 62:
#line 336 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLeftShift);;}
    break;

  case 63:
#line 337 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRightShift);;}
    break;

  case 64:
#line 339 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLT);;}
    break;

  case 65:
#line 340 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLE);;}
    break;

  case 66:
#line 341 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGT);;}
    break;

  case 67:
#line 342 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGE);;}
    break;

  case 68:
#line 343 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigEQ);;}
    break;

  case 69:
#line 344 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigNE);;}
    break;

  case 70:
#line 346 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAttach);;}
    break;

  case 71:
#line 348 "parser/faustparser.y"
    {(yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 72:
#line 349 "parser/faustparser.y"
    {(yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 73:
#line 350 "parser/faustparser.y"
    {(yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 74:
#line 351 "parser/faustparser.y"
    {(yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 75:
#line 352 "parser/faustparser.y"
    {(yyval.exp) = gCosPrim->box(); ;}
    break;

  case 76:
#line 353 "parser/faustparser.y"
    {(yyval.exp) = gSinPrim->box(); ;}
    break;

  case 77:
#line 354 "parser/faustparser.y"
    {(yyval.exp) = gTanPrim->box(); ;}
    break;

  case 78:
#line 356 "parser/faustparser.y"
    {(yyval.exp) = gExpPrim->box(); ;}
    break;

  case 79:
#line 357 "parser/faustparser.y"
    {(yyval.exp) = gLogPrim->box(); ;}
    break;

  case 80:
#line 358 "parser/faustparser.y"
    {(yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 81:
#line 359 "parser/faustparser.y"
    {(yyval.exp) = gPowPrim->box(); ;}
    break;

  case 82:
#line 360 "parser/faustparser.y"
    {(yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 83:
#line 362 "parser/faustparser.y"
    {(yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 84:
#line 363 "parser/faustparser.y"
    {(yyval.exp) = gMinPrim->box(); ;}
    break;

  case 85:
#line 364 "parser/faustparser.y"
    {(yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 86:
#line 366 "parser/faustparser.y"
    {(yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 87:
#line 367 "parser/faustparser.y"
    {(yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 88:
#line 369 "parser/faustparser.y"
    {(yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 89:
#line 370 "parser/faustparser.y"
    {(yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 90:
#line 371 "parser/faustparser.y"
    {(yyval.exp) = gRintPrim->box(); ;}
    break;

  case 91:
#line 374 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigReadOnlyTable);;}
    break;

  case 92:
#line 375 "parser/faustparser.y"
    {(yyval.exp) = boxPrim5(sigWriteReadTable);;}
    break;

  case 93:
#line 377 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigSelect2);;}
    break;

  case 94:
#line 378 "parser/faustparser.y"
    {(yyval.exp) = boxPrim4(sigSelect3);;}
    break;

  case 95:
#line 380 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 96:
#line 382 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(2) - (3)].exp);;}
    break;

  case 97:
#line 384 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 98:
#line 386 "parser/faustparser.y"
    {(yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp)));;}
    break;

  case 99:
#line 388 "parser/faustparser.y"
    {(yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 100:
#line 389 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 101:
#line 390 "parser/faustparser.y"
    {(yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 102:
#line 392 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 103:
#line 393 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 104:
#line 394 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 105:
#line 395 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 106:
#line 396 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 107:
#line 397 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 108:
#line 398 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 109:
#line 399 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 110:
#line 400 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 111:
#line 401 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 112:
#line 403 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 113:
#line 404 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 114:
#line 405 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 115:
#line 406 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 116:
#line 410 "parser/faustparser.y"
    {(yyval.exp) = boxIdent(yytext);;}
    break;

  case 117:
#line 413 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 118:
#line 418 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 119:
#line 419 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 120:
#line 422 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 121:
#line 423 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 122:
#line 424 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 123:
#line 425 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 124:
#line 426 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 125:
#line 429 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 126:
#line 432 "parser/faustparser.y"
    {(yyval.exp) = unquote(yytext); ;}
    break;

  case 127:
#line 435 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 128:
#line 436 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 129:
#line 442 "parser/faustparser.y"
    {(yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 130:
#line 446 "parser/faustparser.y"
    {(yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 131:
#line 450 "parser/faustparser.y"
    {(yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 132:
#line 454 "parser/faustparser.y"
    {(yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 133:
#line 461 "parser/faustparser.y"
    {(yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 134:
#line 465 "parser/faustparser.y"
    {(yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp));;}
    break;

  case 135:
#line 469 "parser/faustparser.y"
    {(yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 136:
#line 472 "parser/faustparser.y"
    {(yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 137:
#line 476 "parser/faustparser.y"
    {(yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 138:
#line 479 "parser/faustparser.y"
    {(yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 139:
#line 482 "parser/faustparser.y"
    {(yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 140:
#line 485 "parser/faustparser.y"
    {(yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 141:
#line 488 "parser/faustparser.y"
    {(yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 142:
#line 491 "parser/faustparser.y"
    {(yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 143:
#line 495 "parser/faustparser.y"
    {(yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 144:
#line 498 "parser/faustparser.y"
    {(yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 145:
#line 502 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 146:
#line 503 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); ;}
    break;

  case 147:
#line 506 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 148:
#line 509 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 149:
#line 510 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 150:
#line 513 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 151:
#line 514 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 152:
#line 518 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 153:
#line 521 "parser/faustparser.y"
    {(yyval.exp) = tree(0); ;}
    break;

  case 154:
#line 522 "parser/faustparser.y"
    {(yyval.exp) = tree(1); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2670 "parser/faustparser.cpp"
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


#line 525 "parser/faustparser.y"



