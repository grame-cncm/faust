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
     FVARIABLE = 290,
     BUTTON = 291,
     CHECKBOX = 292,
     VSLIDER = 293,
     HSLIDER = 294,
     NENTRY = 295,
     VGROUP = 296,
     HGROUP = 297,
     TGROUP = 298,
     HBARGRAPH = 299,
     VBARGRAPH = 300,
     ATTACH = 301,
     ACOS = 302,
     ASIN = 303,
     ATAN = 304,
     ATAN2 = 305,
     COS = 306,
     SIN = 307,
     TAN = 308,
     EXP = 309,
     LOG = 310,
     LOG10 = 311,
     POW = 312,
     SQRT = 313,
     ABS = 314,
     MIN = 315,
     MAX = 316,
     FMOD = 317,
     REMAINDER = 318,
     FLOOR = 319,
     CEIL = 320,
     RINT = 321,
     RDTBL = 322,
     RWTBL = 323,
     SELECT2 = 324,
     SELECT3 = 325,
     INT = 326,
     FLOAT = 327,
     LAMBDA = 328,
     WIRE = 329,
     CUT = 330,
     ENDDEF = 331,
     VIRG = 332,
     LPAR = 333,
     RPAR = 334,
     LBRAQ = 335,
     RBRAQ = 336,
     DEF = 337,
     IMPORT = 338,
     COMPONENT = 339,
     IPAR = 340,
     ISEQ = 341,
     ISUM = 342,
     IPROD = 343,
     STRING = 344,
     FSTRING = 345,
     IDENT = 346,
     EXTRA = 347,
     DECLARE = 348,
     CASE = 349,
     ARROW = 350
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
#define FVARIABLE 290
#define BUTTON 291
#define CHECKBOX 292
#define VSLIDER 293
#define HSLIDER 294
#define NENTRY 295
#define VGROUP 296
#define HGROUP 297
#define TGROUP 298
#define HBARGRAPH 299
#define VBARGRAPH 300
#define ATTACH 301
#define ACOS 302
#define ASIN 303
#define ATAN 304
#define ATAN2 305
#define COS 306
#define SIN 307
#define TAN 308
#define EXP 309
#define LOG 310
#define LOG10 311
#define POW 312
#define SQRT 313
#define ABS 314
#define MIN 315
#define MAX 316
#define FMOD 317
#define REMAINDER 318
#define FLOOR 319
#define CEIL 320
#define RINT 321
#define RDTBL 322
#define RWTBL 323
#define SELECT2 324
#define SELECT3 325
#define INT 326
#define FLOAT 327
#define LAMBDA 328
#define WIRE 329
#define CUT 330
#define ENDDEF 331
#define VIRG 332
#define LPAR 333
#define RPAR 334
#define LBRAQ 335
#define RBRAQ 336
#define DEF 337
#define IMPORT 338
#define COMPONENT 339
#define IPAR 340
#define ISEQ 341
#define ISUM 342
#define IPROD 343
#define STRING 344
#define FSTRING 345
#define IDENT 346
#define EXTRA 347
#define DECLARE 348
#define CASE 349
#define ARROW 350




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
#line 58 "parser/faustparser.y"
{
	CTree* 	exp;
}
/* Line 187 of yacc.c.  */
#line 343 "parser/faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 356 "parser/faustparser.cpp"

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
#define YYLAST   525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNRULES -- Number of states.  */
#define YYNSTATES  348

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

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
      95
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
     256,   258,   260,   262,   264,   266,   268,   271,   275,   284,
     289,   291,   293,   295,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   338,   342,   346,   350,   354,   356,   358,   360,
     362,   364,   373,   382,   391,   400,   409,   417,   425,   430,
     435,   448,   461,   474,   481,   488,   495,   504,   513,   519,
     524,   526,   528,   532,   534,   537,   544,   546
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      97,     0,    -1,    98,    -1,    -1,    98,    99,    -1,   100,
      78,   107,    79,    82,   102,    76,    -1,   100,    82,   102,
      76,    -1,    83,    78,   110,    79,    76,    -1,    93,   106,
     109,    76,    -1,     1,    76,    -1,   105,    -1,   105,    -1,
     101,     7,   105,    -1,   102,     3,    80,    98,    81,    -1,
     102,     7,   102,    -1,   102,     6,   102,    -1,   102,     5,
     102,    -1,   102,     4,   102,    -1,   102,     8,   102,    -1,
     103,    -1,   103,    17,   103,    -1,   103,    16,   103,    -1,
     103,    24,   103,    -1,   103,    23,   103,    -1,   103,    22,
     103,    -1,   103,    25,   103,    -1,   103,    26,    -1,   103,
      27,   105,    -1,   103,    21,   103,    -1,   103,    15,   103,
      -1,   103,    20,   103,    -1,   103,    19,   103,    -1,   103,
      18,   103,    -1,   103,    14,   103,    -1,   103,    13,   103,
      -1,   103,    11,   103,    -1,   103,    10,   103,    -1,   103,
      12,   103,    -1,   103,     9,   103,    -1,   103,    78,   107,
      79,    -1,   104,    -1,    71,    -1,    72,    -1,    17,    71,
      -1,    17,    72,    -1,    16,    71,    -1,    16,    72,    -1,
      74,    -1,    75,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    17,    -1,    16,    -1,    24,    -1,    23,    -1,
      22,    -1,    25,    -1,    21,    -1,    15,    -1,    20,    -1,
      19,    -1,    18,    -1,    14,    -1,    13,    -1,    11,    -1,
      10,    -1,    12,    -1,     9,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,   105,    -1,    16,   105,
      -1,    78,   102,    79,    -1,    73,    78,   101,    79,    27,
      78,   102,    79,    -1,    94,    80,   132,    81,    -1,   116,
      -1,   117,    -1,   118,    -1,    84,    78,   110,    79,    -1,
     119,    -1,   120,    -1,   121,    -1,   122,    -1,   123,    -1,
     124,    -1,   125,    -1,   126,    -1,   127,    -1,   128,    -1,
     112,    -1,   113,    -1,   114,    -1,   115,    -1,    91,    -1,
      91,    -1,   108,    -1,   107,     7,   108,    -1,   108,     6,
     108,    -1,   108,     5,   108,    -1,   108,     4,   108,    -1,
     108,     8,   108,    -1,   103,    -1,    89,    -1,    89,    -1,
      89,    -1,    90,    -1,    85,    78,   105,     7,   108,     7,
     102,    79,    -1,    86,    78,   105,     7,   108,     7,   102,
      79,    -1,    87,    78,   105,     7,   108,     7,   102,    79,
      -1,    88,    78,   105,     7,   108,     7,   102,    79,    -1,
      33,    78,   129,     7,   111,     7,   109,    79,    -1,    34,
      78,   134,   106,     7,   111,    79,    -1,    35,    78,   134,
     106,     7,   111,    79,    -1,    36,    78,   109,    79,    -1,
      37,    78,   109,    79,    -1,    38,    78,   109,     7,   108,
       7,   108,     7,   108,     7,   108,    79,    -1,    39,    78,
     109,     7,   108,     7,   108,     7,   108,     7,   108,    79,
      -1,    40,    78,   109,     7,   108,     7,   108,     7,   108,
       7,   108,    79,    -1,    41,    78,   109,     7,   102,    79,
      -1,    42,    78,   109,     7,   102,    79,    -1,    43,    78,
     109,     7,   102,    79,    -1,    45,    78,   109,     7,   108,
       7,   108,    79,    -1,    44,    78,   109,     7,   108,     7,
     108,    79,    -1,   134,   130,    78,   131,    79,    -1,   134,
     130,    78,    79,    -1,    91,    -1,   134,    -1,   131,     7,
     134,    -1,   133,    -1,   132,   133,    -1,    78,   107,    79,
      95,   102,    76,    -1,    31,    -1,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   236,   236,   239,   240,   246,   247,   248,   249,   250,
     253,   256,   257,   260,   261,   262,   263,   264,   265,   266,
     269,   270,   271,   272,   273,   274,   275,   276,   278,   279,
     280,   282,   283,   285,   286,   287,   288,   289,   290,   292,
     294,   297,   298,   300,   301,   303,   304,   306,   307,   309,
     310,   312,   313,   315,   316,   317,   318,   319,   320,   322,
     323,   324,   326,   327,   329,   330,   331,   332,   333,   334,
     336,   338,   339,   340,   341,   342,   343,   344,   346,   347,
     348,   349,   350,   352,   353,   354,   356,   357,   359,   360,
     361,   364,   365,   367,   368,   370,   371,   373,   374,   377,
     379,   380,   381,   382,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   395,   396,   397,   398,   402,   405,
     410,   411,   414,   415,   416,   417,   418,   421,   424,   427,
     428,   433,   437,   441,   445,   452,   456,   459,   464,   467,
     470,   473,   476,   479,   482,   485,   489,   492,   497,   498,
     501,   504,   505,   508,   509,   512,   516,   517
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
  "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER", "HSLIDER",
  "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH", "VBARGRAPH",
  "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2", "COS", "SIN", "TAN", "EXP",
  "LOG", "LOG10", "POW", "SQRT", "ABS", "MIN", "MAX", "FMOD", "REMAINDER",
  "FLOOR", "CEIL", "RINT", "RDTBL", "RWTBL", "SELECT2", "SELECT3", "INT",
  "FLOAT", "LAMBDA", "WIRE", "CUT", "ENDDEF", "VIRG", "LPAR", "RPAR",
  "LBRAQ", "RBRAQ", "DEF", "IMPORT", "COMPONENT", "IPAR", "ISEQ", "ISUM",
  "IPROD", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "$accept", "program", "eqlist", "equation", "eqname", "params",
  "diagram", "expression", "primitive", "ident", "name", "arglist",
  "argument", "string", "uqstring", "fstring", "fpar", "fseq", "fsum",
  "fprod", "ffunction", "fconst", "fvariable", "button", "checkbox",
  "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
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
     345,   346,   347,   348,   349,   350
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    98,    98,    99,    99,    99,    99,    99,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   105,   106,
     107,   107,   108,   108,   108,   108,   108,   109,   110,   111,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   129,
     130,   131,   131,   132,   132,   133,   134,   134
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
       1,     1,     1,     1,     1,     1,     2,     3,     8,     4,
       1,     1,     1,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     8,     8,     8,     8,     8,     7,     7,     4,     4,
      12,    12,    12,     6,     6,     6,     8,     8,     5,     4,
       1,     1,     3,     1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   118,     0,     4,     0,
      10,     9,     0,   119,     0,     0,     0,   128,     0,   127,
       0,    69,    67,    66,    68,    65,    64,    60,    54,    53,
      63,    62,    61,    59,    57,    56,    55,    58,    49,    50,
      51,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      41,    42,     0,    47,    48,     0,     0,     0,     0,     0,
       0,     0,   126,    40,    95,     0,   120,   114,   115,   116,
     117,   100,   101,   102,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     0,    19,     0,     8,    45,    46,
      96,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,   156,   157,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,    97,     0,     0,     0,
       0,     0,     0,     0,   153,    38,    36,    35,    37,    34,
      33,    29,    21,    20,    32,    31,    30,    28,    24,    23,
      22,    25,    27,     0,   121,     0,   124,   123,   122,   125,
       3,    17,    16,    15,    14,    18,     0,   150,     0,     0,
       0,   138,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,    99,
     154,    39,     0,     0,   129,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,     0,     0,     0,     0,     5,    13,     0,   149,     0,
     151,     0,     0,     0,     0,     0,   143,   144,   145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   152,     0,     0,     0,   147,   146,
      98,   131,   132,   133,   134,   155,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,   141,   142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,   194,   114,    92,    93,    94,
      14,    95,    96,    20,    18,   266,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   180,   238,   289,   203,   204,   181
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
    -121,    34,     7,  -121,    10,    25,  -121,    -3,  -121,    88,
    -121,  -121,    21,  -121,    83,   282,   282,  -121,    48,  -121,
     106,  -121,  -121,  -121,  -121,  -121,  -121,  -121,   146,    82,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,   109,   115,   138,   143,   160,   170,   178,   184,
     185,   186,   190,   191,   192,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,   193,  -121,  -121,   282,   197,   198,   199,   204,
     206,   111,   397,  -121,  -121,    -6,   253,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,   207,   397,   202,  -121,  -121,  -121,
    -121,  -121,  -121,    36,    36,    36,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    33,    23,    21,    33,
      33,    33,    33,   230,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,  -121,    33,   282,   282,   167,   282,   282,   282,   282,
     229,   282,   282,   282,   282,   282,  -121,  -121,  -121,  -121,
     266,   219,    -3,    -3,   279,   280,   364,   365,   367,   368,
     398,   428,   443,   444,    -5,  -121,  -121,   285,   445,   447,
     448,   449,   282,    44,  -121,   422,   422,   422,   422,   422,
     422,    38,    38,    38,    45,    45,    45,    45,    45,    45,
      45,     6,  -121,    -4,   253,   282,    79,    79,   378,  -121,
    -121,    16,    16,   173,   383,  -121,   130,  -121,   381,   450,
     453,  -121,  -121,   282,   282,   282,   282,   282,   282,   282,
     282,    33,   434,  -121,   282,   282,   282,   282,     3,  -121,
    -121,  -121,   390,     8,  -121,  -121,   455,     4,   130,   130,
     200,   237,   247,    35,    41,    47,   421,   426,  -121,   386,
     463,   472,   477,   482,   370,  -121,  -121,    83,  -121,    18,
    -121,   394,   395,   282,   282,   282,  -121,  -121,  -121,   282,
     282,   282,   282,   282,   282,   282,   282,   417,    36,  -121,
    -121,  -121,   487,   497,   502,   107,   113,    73,   157,   171,
     195,   374,   396,  -121,  -121,   282,   282,   282,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,   507,   512,   517,   282,
     282,   282,   357,   379,   384,  -121,  -121,  -121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   267,  -121,  -121,  -121,   -79,   -16,  -121,     9,
      46,   -97,   -60,  -114,   360,   -22,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,   296,  -120
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     115,   164,   251,   164,   182,   183,   137,    -2,     4,     4,
     164,    10,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   173,   174,   175,   308,   170,   171,   172,   173,
     174,   175,   161,   162,     3,   178,   179,   120,   170,   171,
     172,   173,   174,   175,   170,   171,   172,   173,   174,   175,
     170,   171,   172,   173,   174,   175,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   223,   178,   179,   115,
     160,   161,   162,   165,   252,   261,   170,   171,   172,   173,
     174,   175,   284,   288,   163,   168,    11,   169,    13,   286,
       5,     5,   231,   232,   233,   234,   235,   309,     6,     6,
       7,     7,   196,    12,   224,   258,   226,   227,   228,   229,
      17,   166,   167,   168,   296,   169,   163,   166,   167,   168,
     297,   169,   202,   163,     6,   259,   298,   116,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   195,   262,   290,   198,   199,
     200,   201,   330,   121,   122,   115,   115,   115,   115,   115,
     170,   171,   172,   173,   174,   175,    15,   273,   274,   275,
      16,   222,    19,   307,   170,   171,   172,   173,   174,   175,
     174,   175,   117,   270,   271,   272,   328,   123,   324,   276,
     277,   143,   329,   124,   280,   281,   282,   283,   170,   171,
     172,   173,   174,   175,   166,   167,   168,   293,   169,   115,
     170,   171,   172,   173,   174,   175,   125,   118,   119,   264,
     265,   126,   317,   318,   319,   320,   321,   322,   239,   240,
     115,   115,   115,   312,   313,   314,   331,     6,   127,   315,
     316,   166,   167,   168,   294,   169,   291,   292,   128,   225,
     332,   166,   167,   168,   295,   169,   129,   166,   167,   168,
     278,   169,   130,   131,   132,   336,   337,   338,   133,   134,
     135,   136,    10,   236,   333,   138,   139,   140,   177,   342,
     343,   344,   141,   176,   142,   115,   115,   115,   115,   115,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   202,   230,
     237,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   241,   242,
      85,   166,   167,   168,   253,   169,    86,    87,    88,    89,
      90,   243,   244,     6,   245,   246,    91,   170,   171,   172,
     173,   174,   175,   166,   167,   168,   169,   169,   166,   167,
     168,   175,   169,   170,   171,   172,   173,   174,   175,   170,
     171,   172,   173,   174,   175,   247,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   166,   167,   168,   299,   169,
     166,   167,   168,   300,   169,   248,   345,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     249,   250,   254,   334,   255,   256,   257,   268,   346,   267,
     269,   279,   287,   347,   301,   306,   285,   166,   167,   168,
     302,   169,   335,   310,   311,   163,   166,   167,   168,   303,
     169,   166,   167,   168,   304,   169,   166,   167,   168,   305,
     169,   166,   167,   168,   325,   169,   323,   263,   197,   260,
     163,   166,   167,   168,   326,   169,   166,   167,   168,   327,
     169,   166,   167,   168,   339,   169,   166,   167,   168,   340,
     169,   166,   167,   168,   341,   169
};

static const yytype_uint16 yycheck[] =
{
      16,     7,     7,     7,   124,   125,    85,     0,     1,     1,
       7,     2,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,     6,     7,     8,     7,     3,     4,     5,     6,
       7,     8,    26,    27,     0,    31,    32,    28,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,   163,    31,    32,    85,
      25,    26,    27,    79,    79,    79,     3,     4,     5,     6,
       7,     8,    79,    79,    78,     6,    76,     8,    91,    81,
      83,    83,   171,   172,   173,   174,   175,    79,    91,    91,
      93,    93,    79,    78,   164,   202,   166,   167,   168,   169,
      89,     4,     5,     6,    79,     8,    78,     4,     5,     6,
      79,     8,    78,    78,    91,    81,    79,    79,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   136,   225,   267,   139,   140,
     141,   142,    79,    71,    72,   171,   172,   173,   174,   175,
       3,     4,     5,     6,     7,     8,    78,   246,   247,   248,
      82,   162,    89,   287,     3,     4,     5,     6,     7,     8,
       7,     8,    76,   243,   244,   245,    79,    78,   308,   249,
     250,    80,    79,    78,   254,   255,   256,   257,     3,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,   225,
       3,     4,     5,     6,     7,     8,    78,    71,    72,    89,
      90,    78,   301,   302,   303,   304,   305,   306,   182,   183,
     246,   247,   248,   293,   294,   295,    79,    91,    78,   299,
     300,     4,     5,     6,     7,     8,   268,   269,    78,    82,
      79,     4,     5,     6,     7,     8,    78,     4,     5,     6,
     251,     8,    78,    78,    78,   325,   326,   327,    78,    78,
      78,    78,   263,     7,    79,    78,    78,    78,    76,   339,
     340,   341,    78,    76,    78,   301,   302,   303,   304,   305,
     306,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    78,    80,
      91,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    79,    79,
      78,     4,     5,     6,    79,     8,    84,    85,    86,    87,
      88,     7,     7,    91,     7,     7,    94,     3,     4,     5,
       6,     7,     8,     4,     5,     6,     8,     8,     4,     5,
       6,     8,     8,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     7,    79,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       7,     7,     7,    79,     7,     7,     7,     7,    79,    78,
       7,    27,     7,    79,    78,    95,    76,     4,     5,     6,
       7,     8,    76,    79,    79,    78,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,    79,   230,   138,   203,
      78,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    97,    98,     0,     1,    83,    91,    93,    99,   100,
     105,    76,    78,    91,   106,    78,    82,    89,   110,    89,
     109,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    78,    84,    85,    86,    87,
      88,    94,   103,   104,   105,   107,   108,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   102,   103,    79,    76,    71,    72,
     105,    71,    72,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,   102,    78,    78,
      78,    78,    78,    80,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    78,     7,    79,     4,     5,     6,     8,
       3,     4,     5,     6,     7,     8,    76,    76,    31,    32,
     129,   134,   134,   134,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   101,   105,    79,   110,   105,   105,
     105,   105,    78,   132,   133,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   105,   107,   108,    82,   108,   108,   108,   108,
      80,   102,   102,   102,   102,   102,     7,    91,   130,   106,
     106,    79,    79,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    79,    79,     7,     7,     7,     7,   107,    81,
     133,    79,   102,    98,    89,    90,   111,    78,     7,     7,
     108,   108,   108,   102,   102,   102,   108,   108,   105,    27,
     108,   108,   108,   108,    79,    76,    81,     7,    79,   131,
     134,   111,   111,     7,     7,     7,    79,    79,    79,     7,
       7,    78,     7,     7,     7,     7,    95,   109,     7,    79,
      79,    79,   108,   108,   108,   108,   108,   102,   102,   102,
     102,   102,   102,    79,   134,     7,     7,     7,    79,    79,
      79,    79,    79,    79,    79,    76,   108,   108,   108,     7,
       7,     7,   108,   108,   108,    79,    79,    79
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
#line 236 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 239 "parser/faustparser.y"
    {(yyval.exp) = nil; ;}
    break;

  case 4:
#line 240 "parser/faustparser.y"
    {(yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:
#line 246 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 6:
#line 247 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 7:
#line 248 "parser/faustparser.y"
    {(yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:
#line 249 "parser/faustparser.y"
    {gMetaDataSet[(yyvsp[(2) - (4)].exp)].insert((yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:
#line 250 "parser/faustparser.y"
    {(yyval.exp) = nil; yyerr++;;}
    break;

  case 10:
#line 253 "parser/faustparser.y"
    {(yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 11:
#line 256 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 12:
#line 257 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 13:
#line 260 "parser/faustparser.y"
    {(yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 14:
#line 261 "parser/faustparser.y"
    {(yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 15:
#line 262 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 16:
#line 263 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 17:
#line 264 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 18:
#line 265 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 19:
#line 266 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 20:
#line 269 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 21:
#line 270 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 22:
#line 271 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 23:
#line 272 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 24:
#line 273 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 25:
#line 274 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 26:
#line 275 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 27:
#line 276 "parser/faustparser.y"
    {(yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 28:
#line 278 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 29:
#line 279 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 30:
#line 280 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 31:
#line 282 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 32:
#line 283 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 33:
#line 285 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 34:
#line 286 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 35:
#line 287 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 36:
#line 288 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 37:
#line 289 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 38:
#line 290 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 39:
#line 292 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 40:
#line 294 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 41:
#line 297 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 42:
#line 298 "parser/faustparser.y"
    {(yyval.exp) = boxReal(float(atof(yytext)));;}
    break;

  case 43:
#line 300 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 44:
#line 301 "parser/faustparser.y"
    {(yyval.exp) = boxReal(float(atof(yytext)));;}
    break;

  case 45:
#line 303 "parser/faustparser.y"
    {(yyval.exp) = boxInt(0 - atoi(yytext));;}
    break;

  case 46:
#line 304 "parser/faustparser.y"
    {(yyval.exp) = boxReal(0.0f - float(atof(yytext)));;}
    break;

  case 47:
#line 306 "parser/faustparser.y"
    {(yyval.exp) = boxWire();;}
    break;

  case 48:
#line 307 "parser/faustparser.y"
    {(yyval.exp) = boxCut();;}
    break;

  case 49:
#line 309 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigDelay1);;}
    break;

  case 50:
#line 310 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigPrefix);;}
    break;

  case 51:
#line 312 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigIntCast);;}
    break;

  case 52:
#line 313 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigFloatCast);;}
    break;

  case 53:
#line 315 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAdd);;}
    break;

  case 54:
#line 316 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigSub);;}
    break;

  case 55:
#line 317 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigMul);;}
    break;

  case 56:
#line 318 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigDiv);;}
    break;

  case 57:
#line 319 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRem);;}
    break;

  case 58:
#line 320 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigFixDelay);;}
    break;

  case 59:
#line 322 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAND);;}
    break;

  case 60:
#line 323 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigOR);;}
    break;

  case 61:
#line 324 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigXOR);;}
    break;

  case 62:
#line 326 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLeftShift);;}
    break;

  case 63:
#line 327 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRightShift);;}
    break;

  case 64:
#line 329 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLT);;}
    break;

  case 65:
#line 330 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLE);;}
    break;

  case 66:
#line 331 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGT);;}
    break;

  case 67:
#line 332 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGE);;}
    break;

  case 68:
#line 333 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigEQ);;}
    break;

  case 69:
#line 334 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigNE);;}
    break;

  case 70:
#line 336 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAttach);;}
    break;

  case 71:
#line 338 "parser/faustparser.y"
    {(yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 72:
#line 339 "parser/faustparser.y"
    {(yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 73:
#line 340 "parser/faustparser.y"
    {(yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 74:
#line 341 "parser/faustparser.y"
    {(yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 75:
#line 342 "parser/faustparser.y"
    {(yyval.exp) = gCosPrim->box(); ;}
    break;

  case 76:
#line 343 "parser/faustparser.y"
    {(yyval.exp) = gSinPrim->box(); ;}
    break;

  case 77:
#line 344 "parser/faustparser.y"
    {(yyval.exp) = gTanPrim->box(); ;}
    break;

  case 78:
#line 346 "parser/faustparser.y"
    {(yyval.exp) = gExpPrim->box(); ;}
    break;

  case 79:
#line 347 "parser/faustparser.y"
    {(yyval.exp) = gLogPrim->box(); ;}
    break;

  case 80:
#line 348 "parser/faustparser.y"
    {(yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 81:
#line 349 "parser/faustparser.y"
    {(yyval.exp) = gPowPrim->box(); ;}
    break;

  case 82:
#line 350 "parser/faustparser.y"
    {(yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 83:
#line 352 "parser/faustparser.y"
    {(yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 84:
#line 353 "parser/faustparser.y"
    {(yyval.exp) = gMinPrim->box(); ;}
    break;

  case 85:
#line 354 "parser/faustparser.y"
    {(yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 86:
#line 356 "parser/faustparser.y"
    {(yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 87:
#line 357 "parser/faustparser.y"
    {(yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 88:
#line 359 "parser/faustparser.y"
    {(yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 89:
#line 360 "parser/faustparser.y"
    {(yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 90:
#line 361 "parser/faustparser.y"
    {(yyval.exp) = gRintPrim->box(); ;}
    break;

  case 91:
#line 364 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigReadOnlyTable);;}
    break;

  case 92:
#line 365 "parser/faustparser.y"
    {(yyval.exp) = boxPrim5(sigWriteReadTable);;}
    break;

  case 93:
#line 367 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigSelect2);;}
    break;

  case 94:
#line 368 "parser/faustparser.y"
    {(yyval.exp) = boxPrim4(sigSelect3);;}
    break;

  case 95:
#line 370 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 96:
#line 371 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub));;}
    break;

  case 97:
#line 373 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(2) - (3)].exp);;}
    break;

  case 98:
#line 375 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 99:
#line 377 "parser/faustparser.y"
    {(yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp)));;}
    break;

  case 100:
#line 379 "parser/faustparser.y"
    {(yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 101:
#line 380 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 102:
#line 381 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 103:
#line 382 "parser/faustparser.y"
    {(yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 104:
#line 384 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 105:
#line 385 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 106:
#line 386 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 107:
#line 387 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 108:
#line 388 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 109:
#line 389 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 110:
#line 390 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 111:
#line 391 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 112:
#line 392 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 113:
#line 393 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 114:
#line 395 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 115:
#line 396 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 116:
#line 397 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 117:
#line 398 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 118:
#line 402 "parser/faustparser.y"
    {(yyval.exp) = boxIdent(yytext);;}
    break;

  case 119:
#line 405 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 120:
#line 410 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 121:
#line 411 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 122:
#line 414 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 123:
#line 415 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 124:
#line 416 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 125:
#line 417 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp));;}
    break;

  case 126:
#line 418 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 127:
#line 421 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 128:
#line 424 "parser/faustparser.y"
    {(yyval.exp) = unquote(yytext); ;}
    break;

  case 129:
#line 427 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 130:
#line 428 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 131:
#line 434 "parser/faustparser.y"
    {(yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 132:
#line 438 "parser/faustparser.y"
    {(yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 133:
#line 442 "parser/faustparser.y"
    {(yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 134:
#line 446 "parser/faustparser.y"
    {(yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 135:
#line 453 "parser/faustparser.y"
    {(yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp));;}
    break;

  case 136:
#line 457 "parser/faustparser.y"
    {(yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp));;}
    break;

  case 137:
#line 460 "parser/faustparser.y"
    {(yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp));;}
    break;

  case 138:
#line 464 "parser/faustparser.y"
    {(yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 139:
#line 467 "parser/faustparser.y"
    {(yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 140:
#line 471 "parser/faustparser.y"
    {(yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 141:
#line 474 "parser/faustparser.y"
    {(yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 142:
#line 477 "parser/faustparser.y"
    {(yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 143:
#line 480 "parser/faustparser.y"
    {(yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 144:
#line 483 "parser/faustparser.y"
    {(yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 145:
#line 486 "parser/faustparser.y"
    {(yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 146:
#line 490 "parser/faustparser.y"
    {(yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 147:
#line 493 "parser/faustparser.y"
    {(yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 148:
#line 497 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 149:
#line 498 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); ;}
    break;

  case 150:
#line 501 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 151:
#line 504 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 152:
#line 505 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 153:
#line 508 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 154:
#line 509 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 155:
#line 513 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 156:
#line 516 "parser/faustparser.y"
    {(yyval.exp) = tree(0); ;}
    break;

  case 157:
#line 517 "parser/faustparser.y"
    {(yyval.exp) = tree(1); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2677 "parser/faustparser.cpp"
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


#line 520 "parser/faustparser.y"



