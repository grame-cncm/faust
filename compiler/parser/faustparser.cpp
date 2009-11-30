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
     DEF = 338,
     IMPORT = 339,
     COMPONENT = 340,
     LIBRARY = 341,
     ENVIRONMENT = 342,
     IPAR = 343,
     ISEQ = 344,
     ISUM = 345,
     IPROD = 346,
     STRING = 347,
     FSTRING = 348,
     IDENT = 349,
     EXTRA = 350,
     DECLARE = 351,
     CASE = 352,
     ARROW = 353,
     BDOC = 354,
     EDOC = 355,
     BEQN = 356,
     EEQN = 357,
     BDGM = 358,
     EDGM = 359,
     DOCCHAR = 360,
     NOTICE = 361,
     LISTING = 362
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
#define DEF 338
#define IMPORT 339
#define COMPONENT 340
#define LIBRARY 341
#define ENVIRONMENT 342
#define IPAR 343
#define ISEQ 344
#define ISUM 345
#define IPROD 346
#define STRING 347
#define FSTRING 348
#define IDENT 349
#define EXTRA 350
#define DECLARE 351
#define CASE 352
#define ARROW 353
#define BDOC 354
#define EDOC 355
#define BEQN 356
#define EEQN 357
#define BDGM 358
#define EDGM 359
#define DOCCHAR 360
#define NOTICE 361
#define LISTING 362




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

extern char* 		yytext;
extern const char* 	yyfilename;
extern int 			yylineno;
extern int 			yyerr;
extern Tree 		gResult;

extern map<Tree, set<Tree> > gMetaDataSet;
extern vector<Tree> gDocVector;
static string doctxtString = "";


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
	char* str;
}
/* Line 187 of yacc.c.  */
#line 373 "parser/faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 386 "parser/faustparser.cpp"

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
#define YYLAST   569

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  379

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

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
     105,   106,   107
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    13,    19,    24,
      26,    30,    31,    34,    36,    38,    40,    42,    44,    48,
      52,    53,    56,    58,    60,    68,    73,    76,    78,    80,
      84,    90,    94,    98,   102,   106,   110,   112,   116,   120,
     124,   128,   132,   136,   140,   143,   147,   151,   155,   159,
     163,   167,   171,   175,   179,   183,   187,   191,   196,   198,
     200,   202,   205,   208,   211,   214,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   234,   236,   238,   240,   242,
     244,   246,   248,   250,   252,   254,   256,   258,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   317,   321,   330,   335,
     337,   339,   341,   346,   351,   356,   358,   360,   362,   364,
     366,   368,   370,   372,   374,   376,   378,   380,   382,   384,
     386,   388,   390,   394,   398,   402,   406,   410,   412,   414,
     416,   418,   420,   429,   438,   447,   456,   465,   473,   481,
     486,   491,   504,   517,   530,   537,   544,   551,   560,   569,
     575,   580,   582,   584,   588,   590,   593,   600,   602
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     109,     0,    -1,   110,    -1,    -1,   110,   112,    -1,    -1,
     111,   120,    -1,    84,    79,   131,    80,    77,    -1,    96,
     127,   130,    77,    -1,   120,    -1,    99,   113,   100,    -1,
      -1,   113,   114,    -1,   117,    -1,   115,    -1,   116,    -1,
     118,    -1,   119,    -1,   101,   123,   102,    -1,   103,   123,
     104,    -1,    -1,   117,   105,    -1,   106,    -1,   107,    -1,
     121,    79,   128,    80,    83,   123,    77,    -1,   121,    83,
     123,    77,    -1,     1,    77,    -1,   126,    -1,   126,    -1,
     122,     7,   126,    -1,   123,     3,    81,   111,    82,    -1,
     123,     7,   123,    -1,   123,     6,   123,    -1,   123,     5,
     123,    -1,   123,     4,   123,    -1,   123,     8,   123,    -1,
     124,    -1,   124,    17,   124,    -1,   124,    16,   124,    -1,
     124,    24,   124,    -1,   124,    23,   124,    -1,   124,    22,
     124,    -1,   124,    25,   124,    -1,   124,    26,   124,    -1,
     124,    27,    -1,   124,    28,   126,    -1,   124,    21,   124,
      -1,   124,    15,   124,    -1,   124,    20,   124,    -1,   124,
      19,   124,    -1,   124,    18,   124,    -1,   124,    14,   124,
      -1,   124,    13,   124,    -1,   124,    11,   124,    -1,   124,
      10,   124,    -1,   124,    12,   124,    -1,   124,     9,   124,
      -1,   124,    79,   128,    80,    -1,   125,    -1,    72,    -1,
      73,    -1,    17,    72,    -1,    17,    73,    -1,    16,    72,
      -1,    16,    73,    -1,    75,    -1,    76,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    17,    -1,    16,    -1,
      24,    -1,    23,    -1,    22,    -1,    26,    -1,    21,    -1,
      15,    -1,    20,    -1,    19,    -1,    18,    -1,    14,    -1,
      13,    -1,    11,    -1,    10,    -1,    12,    -1,     9,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    25,    -1,    58,    -1,    59,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,   126,    -1,    16,   126,    -1,    79,   123,    80,
      -1,    74,    79,   122,    80,    28,    79,   123,    80,    -1,
      97,    81,   153,    82,    -1,   137,    -1,   138,    -1,   139,
      -1,    85,    79,   131,    80,    -1,    86,    79,   131,    80,
      -1,    87,    81,   111,    82,    -1,   140,    -1,   141,    -1,
     142,    -1,   143,    -1,   144,    -1,   145,    -1,   146,    -1,
     147,    -1,   148,    -1,   149,    -1,   133,    -1,   134,    -1,
     135,    -1,   136,    -1,    94,    -1,    94,    -1,   129,    -1,
     128,     7,   129,    -1,   129,     6,   129,    -1,   129,     5,
     129,    -1,   129,     4,   129,    -1,   129,     8,   129,    -1,
     124,    -1,    92,    -1,    92,    -1,    92,    -1,    93,    -1,
      88,    79,   126,     7,   129,     7,   123,    80,    -1,    89,
      79,   126,     7,   129,     7,   123,    80,    -1,    90,    79,
     126,     7,   129,     7,   123,    80,    -1,    91,    79,   126,
       7,   129,     7,   123,    80,    -1,    34,    79,   150,     7,
     132,     7,   130,    80,    -1,    35,    79,   155,   127,     7,
     132,    80,    -1,    36,    79,   155,   127,     7,   132,    80,
      -1,    37,    79,   131,    80,    -1,    38,    79,   131,    80,
      -1,    39,    79,   131,     7,   129,     7,   129,     7,   129,
       7,   129,    80,    -1,    40,    79,   131,     7,   129,     7,
     129,     7,   129,     7,   129,    80,    -1,    41,    79,   131,
       7,   129,     7,   129,     7,   129,     7,   129,    80,    -1,
      42,    79,   131,     7,   123,    80,    -1,    43,    79,   131,
       7,   123,    80,    -1,    44,    79,   131,     7,   123,    80,
      -1,    46,    79,   131,     7,   129,     7,   129,    80,    -1,
      45,    79,   130,     7,   129,     7,   129,    80,    -1,   155,
     151,    79,   152,    80,    -1,   155,   151,    79,    80,    -1,
      94,    -1,   155,    -1,   152,     7,   155,    -1,   154,    -1,
     153,   154,    -1,    79,   128,    80,    98,   123,    77,    -1,
      32,    -1,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   265,   265,   268,   269,   271,   272,   275,   276,   277,
     278,   281,   282,   285,   286,   287,   288,   289,   292,   295,
     298,   299,   302,   305,   308,   309,   310,   313,   316,   317,
     320,   321,   322,   323,   324,   325,   326,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   339,   340,   341,   343,
     344,   346,   347,   348,   349,   350,   351,   353,   355,   358,
     359,   361,   362,   364,   365,   367,   368,   370,   371,   373,
     374,   376,   377,   378,   379,   380,   381,   383,   384,   385,
     387,   388,   390,   391,   392,   393,   394,   395,   397,   399,
     400,   401,   402,   403,   404,   405,   407,   408,   409,   410,
     411,   412,   414,   415,   416,   418,   419,   421,   422,   423,
     426,   427,   429,   430,   432,   433,   435,   436,   439,   441,
     442,   443,   444,   445,   446,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   459,   460,   461,   462,   466,
     469,   474,   475,   478,   479,   480,   481,   482,   485,   488,
     491,   492,   497,   501,   505,   509,   516,   520,   523,   528,
     531,   534,   537,   540,   543,   546,   549,   553,   556,   562,
     563,   566,   569,   570,   573,   574,   577,   581,   582
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
  "LPAR", "RPAR", "LBRAQ", "RBRAQ", "DEF", "IMPORT", "COMPONENT",
  "LIBRARY", "ENVIRONMENT", "IPAR", "ISEQ", "ISUM", "IPROD", "STRING",
  "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC",
  "BEQN", "EEQN", "BDGM", "EDGM", "DOCCHAR", "NOTICE", "LISTING",
  "$accept", "program", "stmtlist", "deflist", "statement", "doc",
  "docelem", "doceqn", "docdgm", "doctxt", "docntc", "doclst",
  "definition", "defname", "params", "expression", "infixexp", "primitive",
  "ident", "name", "arglist", "argument", "string", "uqstring", "fstring",
  "fpar", "fseq", "fsum", "fprod", "ffunction", "fconst", "fvariable",
  "button", "checkbox", "vslider", "hslider", "nentry", "vgroup", "hgroup",
  "tgroup", "vbargraph", "hbargraph", "signature", "fun", "typelist",
  "rulelist", "rule", "type", 0
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
     355,   356,   357,   358,   359,   360,   361,   362
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   110,   110,   111,   111,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   115,   116,
     117,   117,   118,   119,   120,   120,   120,   121,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   126,
     127,   128,   128,   129,   129,   129,   129,   129,   130,   131,
     132,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     150,   151,   152,   152,   153,   153,   154,   155,   155
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     5,     4,     1,
       3,     0,     2,     1,     1,     1,     1,     1,     3,     3,
       0,     2,     1,     1,     7,     4,     2,     1,     1,     3,
       5,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     1,     1,
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   139,     0,    11,     4,
       9,     0,    27,    26,     0,   140,     0,    20,     0,     0,
     149,     0,   148,     0,    10,     0,     0,    22,    23,    12,
      14,    15,    13,    16,    17,    87,    85,    84,    86,    83,
      82,    78,    72,    71,    81,    80,    79,    77,    75,    74,
      73,    99,    76,    67,    68,    69,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    59,    60,     0,    65,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147,
      58,   114,     0,   141,   135,   136,   137,   138,   119,   120,
     121,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,    36,     0,     8,     0,     0,    21,    63,    64,
     115,    61,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       7,    18,    19,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,    56,    54,    53,    55,    52,    51,    47,    38,
      37,    50,    49,    48,    46,    41,    40,    39,    42,    43,
      45,     0,   142,     0,   145,   144,   143,   146,     5,    34,
      33,    32,    31,    35,     0,   171,     0,     0,     0,   159,
     160,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,   124,     6,     0,     0,     0,     0,     0,
     118,   175,    57,     0,     0,   150,   151,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,    24,    30,     0,   170,
       0,   172,     0,     0,     0,     0,     0,   164,   165,   166,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     169,   157,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,   173,     0,     0,     0,   168,
     167,   117,   152,   153,   154,   155,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   161,   162,   163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   224,     9,    17,    29,    30,    31,    32,
      33,    34,   284,    11,   219,   131,   109,   110,   111,    16,
     112,   113,    23,    21,   297,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   205,   266,   320,   230,   231,   206
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -153
static const yytype_int16 yypact[] =
{
    -153,    48,     4,  -153,    -2,     1,  -153,    10,  -153,  -153,
    -153,    36,  -153,  -153,    22,  -153,    39,   178,   316,   316,
    -153,    65,  -153,    92,  -153,   316,   316,  -153,  -153,  -153,
    -153,  -153,    23,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,   164,   -64,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   101,   109,   114,
     146,   148,   152,   156,   167,   168,   169,   172,   173,   174,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   175,  -153,  -153,
     316,   180,   201,   117,   203,   204,   215,   221,   179,   418,
    -153,  -153,     3,   291,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,   266,   418,   209,  -153,    19,    13,  -153,  -153,  -153,
    -153,  -153,  -153,    57,    57,    57,    22,    22,    22,    22,
      22,    22,    22,    22,    39,    22,   198,    25,    22,    22,
    -153,   198,   198,   198,   198,   222,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,  -153,   198,   316,   316,   219,   316,
     316,   316,   316,   229,   316,   316,   316,   316,   316,  -153,
    -153,  -153,  -153,  -153,  -153,   304,   250,    10,    10,   232,
     265,   386,   387,   401,   402,   404,   405,   419,   473,    27,
    -153,  -153,   403,   406,     0,   475,   480,   488,   489,   316,
      20,  -153,   432,   432,   432,   432,   432,   432,   443,   443,
     443,    51,    51,    51,    51,    51,    51,    51,   116,    58,
    -153,    40,   291,   316,   181,   181,   500,  -153,  -153,   132,
     132,   193,   501,  -153,   110,  -153,   431,   551,   552,  -153,
    -153,   316,   316,   316,   316,   316,   316,   316,   316,   198,
     532,  -153,  -153,  -153,  -153,   316,   316,   316,   316,    94,
    -153,  -153,  -153,   411,     2,  -153,  -153,   554,    17,   110,
     110,   260,   301,   392,    32,    38,    49,   485,   494,  -153,
     483,   499,   508,   513,   519,   465,  -153,  -153,    39,  -153,
     106,  -153,   484,   486,   316,   316,   316,  -153,  -153,  -153,
     316,   316,   316,   316,   316,   316,   316,   316,   487,    57,
    -153,  -153,  -153,   524,   529,   534,    66,    87,    55,    61,
     119,   207,   213,   417,  -153,  -153,   316,   316,   316,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   539,   544,   549,
     316,   316,   316,   128,   218,   224,  -153,  -153,  -153
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -153,   307,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,   566,  -153,  -153,   -13,   -19,  -153,     9,    31,
    -113,   -81,  -152,   326,   -58,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,   339,  -130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     132,     4,   217,     4,    -2,     4,   132,   132,   141,   142,
     187,    12,   135,   136,   207,   208,   193,   194,   195,   196,
     197,   198,   193,   194,   195,   196,   197,   198,   193,   194,
     195,   196,   197,   198,   279,   193,   194,   195,   196,   197,
     198,   193,   194,   195,   196,   197,   198,   187,     3,   203,
     204,   140,   193,   194,   195,   196,   197,   198,   193,   194,
     195,   196,   197,   198,   193,   194,   195,   196,   197,   198,
     189,   190,   191,   251,   192,    13,   182,   183,   184,   185,
      14,   132,   283,   188,   317,   184,   185,   157,     5,   203,
     204,   189,   190,   191,     6,   192,     6,   319,     6,   229,
       7,   187,   290,     8,    15,   221,   252,   280,   254,   255,
     256,   257,   327,   339,    20,    18,   289,   202,   328,    19,
     292,   201,   193,   194,   195,   196,   197,   198,   137,   329,
     186,    22,   189,   190,   191,   361,   192,   186,   196,   197,
     198,   362,   183,   184,   185,   133,   359,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   220,   338,   360,   321,   134,
     225,   226,   227,   228,   315,   132,   132,   132,   132,   132,
     143,   259,   260,   261,   262,   263,   340,   191,   144,   192,
     301,   302,   303,   145,   250,   186,   307,   308,   160,   363,
     197,   198,   295,   296,   311,   312,   313,   314,   376,   355,
     193,   194,   195,   196,   197,   198,   193,   194,   195,   196,
     197,   198,   189,   190,   191,   146,   192,   147,   189,   190,
     191,   148,   192,    12,   132,   149,   138,   139,   267,   268,
     293,   322,   323,   343,   344,   345,   150,   151,   152,   346,
     347,   153,   154,   155,   156,   132,   132,   132,     6,   158,
     165,   304,   305,   306,   189,   190,   191,   324,   192,   193,
     194,   195,   196,   197,   198,   367,   368,   369,    24,    25,
     159,    26,   161,   162,    27,    28,   200,   364,   309,   373,
     374,   375,     6,   365,   163,   189,   190,   191,   377,   192,
     164,   229,   253,    12,   378,   189,   190,   191,   325,   192,
     258,   264,   269,   132,   132,   132,   132,   132,   132,   348,
     349,   350,   351,   352,   353,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   199,   265,   270,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   271,   272,   100,   189,   190,   191,   326,
     192,   101,   102,   103,   104,   105,   106,   107,   273,   274,
       6,   275,   276,   108,   193,   194,   195,   196,   197,   198,
     193,   194,   195,   196,   197,   198,   277,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   209,   210,   211,   212,   213,   214,   215,   216,
     278,   218,   285,   281,   222,   223,   282,   286,   316,   189,
     190,   191,   330,   192,   366,   287,   288,   186,   189,   190,
     191,   331,   192,   189,   190,   191,   333,   192,   192,   198,
     298,   186,   189,   190,   191,   334,   192,   189,   190,   191,
     335,   192,   186,   189,   190,   191,   336,   192,   189,   190,
     191,   356,   192,   189,   190,   191,   357,   192,   189,   190,
     191,   358,   192,   189,   190,   191,   370,   192,   189,   190,
     191,   371,   192,   189,   190,   191,   372,   192,   299,   300,
     310,   318,   332,   337,   341,   294,   342,   354,    10,   291
};

static const yytype_uint16 yycheck[] =
{
      19,     1,   154,     1,     0,     1,    25,    26,    72,    73,
       7,     2,    25,    26,   144,   145,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     7,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,     7,     0,    32,
      33,    42,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       4,     5,     6,   186,     8,    77,    25,    26,    27,    28,
      79,   100,    82,    80,    82,    27,    28,   100,    84,    32,
      33,     4,     5,     6,    94,     8,    94,    80,    94,    79,
      96,     7,    82,    99,    94,    80,   187,    80,   189,   190,
     191,   192,    80,     7,    92,    79,   229,   104,    80,    83,
      80,   102,     3,     4,     5,     6,     7,     8,   105,    80,
      79,    92,     4,     5,     6,    80,     8,    79,     6,     7,
       8,    80,    26,    27,    28,    80,    80,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   156,   318,    80,   298,    77,
     161,   162,   163,   164,    80,   194,   195,   196,   197,   198,
      79,   194,   195,   196,   197,   198,    80,     6,    79,     8,
     271,   272,   273,    79,   185,    79,   277,   278,    81,    80,
       7,     8,    92,    93,   285,   286,   287,   288,    80,   339,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,     4,     5,     6,    79,     8,    79,     4,     5,
       6,    79,     8,   224,   253,    79,    72,    73,   207,   208,
     253,   299,   300,   324,   325,   326,    79,    79,    79,   330,
     331,    79,    79,    79,    79,   274,   275,   276,    94,    79,
      81,   274,   275,   276,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,   356,   357,   358,   100,   101,
      79,   103,    79,    79,   106,   107,    77,    80,   279,   370,
     371,   372,    94,    80,    79,     4,     5,     6,    80,     8,
      79,    79,    83,   294,    80,     4,     5,     6,     7,     8,
      81,     7,    80,   332,   333,   334,   335,   336,   337,   332,
     333,   334,   335,   336,   337,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    77,    94,    80,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     7,     7,    79,     4,     5,     6,     7,
       8,    85,    86,    87,    88,    89,    90,    91,     7,     7,
      94,     7,     7,    97,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,     7,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,   146,   147,   148,   149,   150,   151,   152,   153,
       7,   155,     7,    80,   158,   159,    80,     7,    77,     4,
       5,     6,     7,     8,    77,     7,     7,    79,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     8,     8,
      79,    79,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,    79,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     7,     7,
      28,     7,    79,    98,    80,   258,    80,    80,     2,   230
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   109,   110,     0,     1,    84,    94,    96,    99,   112,
     120,   121,   126,    77,    79,    94,   127,   113,    79,    83,
      92,   131,    92,   130,   100,   101,   103,   106,   107,   114,
     115,   116,   117,   118,   119,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      79,    85,    86,    87,    88,    89,    90,    91,    97,   124,
     125,   126,   128,   129,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   123,   124,    80,    77,   123,   123,   105,    72,    73,
     126,    72,    73,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,   123,    79,    79,
      81,    79,    79,    79,    79,    81,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    79,     7,    80,     4,
       5,     6,     8,     3,     4,     5,     6,     7,     8,    77,
      77,   102,   104,    32,    33,   150,   155,   155,   155,   131,
     131,   131,   131,   131,   131,   131,   131,   130,   131,   122,
     126,    80,   131,   131,   111,   126,   126,   126,   126,    79,
     153,   154,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     126,   128,   129,    83,   129,   129,   129,   129,    81,   123,
     123,   123,   123,   123,     7,    94,   151,   127,   127,    80,
      80,     7,     7,     7,     7,     7,     7,     7,     7,     7,
      80,    80,    80,    82,   120,     7,     7,     7,     7,   128,
      82,   154,    80,   123,   111,    92,    93,   132,    79,     7,
       7,   129,   129,   129,   123,   123,   123,   129,   129,   126,
      28,   129,   129,   129,   129,    80,    77,    82,     7,    80,
     152,   155,   132,   132,     7,     7,     7,    80,    80,    80,
       7,     7,    79,     7,     7,     7,     7,    98,   130,     7,
      80,    80,    80,   129,   129,   129,   129,   129,   123,   123,
     123,   123,   123,   123,    80,   155,     7,     7,     7,    80,
      80,    80,    80,    80,    80,    80,    77,   129,   129,   129,
       7,     7,     7,   129,   129,   129,    80,    80,    80
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
#line 265 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 268 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 4:
#line 269 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 5:
#line 271 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 6:
#line 272 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 7:
#line 275 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 8:
#line 276 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = nil; ;}
    break;

  case 9:
#line 277 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 10:
#line 278 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = nil; cout << "Yacc : doc : " << *(yyvsp[(2) - (3)].exp) << endl ; doctxtString = "";  ;}
    break;

  case 11:
#line 281 "parser/faustparser.y"
    { (yyval.exp) = nil; ;}
    break;

  case 12:
#line 282 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 13:
#line 285 "parser/faustparser.y"
    { (yyval.exp) = docTxt(doctxtString.c_str()); ;}
    break;

  case 14:
#line 286 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 15:
#line 287 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 288 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 17:
#line 289 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 18:
#line 292 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); doctxtString = ""; ;}
    break;

  case 19:
#line 295 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); doctxtString = ""; ;}
    break;

  case 20:
#line 298 "parser/faustparser.y"
    { ;}
    break;

  case 21:
#line 299 "parser/faustparser.y"
    { (doctxtString += yytext); ;}
    break;

  case 22:
#line 302 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 23:
#line 305 "parser/faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 24:
#line 308 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); ;}
    break;

  case 25:
#line 309 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(nil,(yyvsp[(3) - (4)].exp))); ;}
    break;

  case 26:
#line 310 "parser/faustparser.y"
    { (yyval.exp) = nil; yyerr++; ;}
    break;

  case 27:
#line 313 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); ;}
    break;

  case 28:
#line 316 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 29:
#line 317 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 30:
#line 320 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 31:
#line 321 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 32:
#line 322 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 33:
#line 323 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 34:
#line 324 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 35:
#line 325 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 36:
#line 326 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 37:
#line 329 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 38:
#line 330 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 39:
#line 331 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 40:
#line 332 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 41:
#line 333 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 42:
#line 334 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gPowPrim->box()); ;}
    break;

  case 43:
#line 335 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 44:
#line 336 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 45:
#line 337 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 46:
#line 339 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 47:
#line 340 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 48:
#line 341 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 49:
#line 343 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 50:
#line 344 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 51:
#line 346 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 52:
#line 347 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 53:
#line 348 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 54:
#line 349 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 55:
#line 350 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 56:
#line 351 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 57:
#line 353 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 58:
#line 355 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 59:
#line 358 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); ;}
    break;

  case 60:
#line 359 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 61:
#line 361 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); ;}
    break;

  case 62:
#line 362 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 63:
#line 364 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); ;}
    break;

  case 64:
#line 365 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); ;}
    break;

  case 65:
#line 367 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 66:
#line 368 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 67:
#line 370 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 68:
#line 371 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 69:
#line 373 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 70:
#line 374 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 71:
#line 376 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 72:
#line 377 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 73:
#line 378 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 74:
#line 379 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 75:
#line 380 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 76:
#line 381 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); ;}
    break;

  case 77:
#line 383 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 78:
#line 384 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 79:
#line 385 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 80:
#line 387 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 81:
#line 388 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); ;}
    break;

  case 82:
#line 390 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 83:
#line 391 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 84:
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 85:
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 86:
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 87:
#line 395 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 88:
#line 397 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 89:
#line 399 "parser/faustparser.y"
    { (yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 90:
#line 400 "parser/faustparser.y"
    { (yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 91:
#line 401 "parser/faustparser.y"
    { (yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 92:
#line 402 "parser/faustparser.y"
    { (yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 93:
#line 403 "parser/faustparser.y"
    { (yyval.exp) = gCosPrim->box(); ;}
    break;

  case 94:
#line 404 "parser/faustparser.y"
    { (yyval.exp) = gSinPrim->box(); ;}
    break;

  case 95:
#line 405 "parser/faustparser.y"
    { (yyval.exp) = gTanPrim->box(); ;}
    break;

  case 96:
#line 407 "parser/faustparser.y"
    { (yyval.exp) = gExpPrim->box(); ;}
    break;

  case 97:
#line 408 "parser/faustparser.y"
    { (yyval.exp) = gLogPrim->box(); ;}
    break;

  case 98:
#line 409 "parser/faustparser.y"
    { (yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 99:
#line 410 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 100:
#line 411 "parser/faustparser.y"
    { (yyval.exp) = gPowPrim->box(); ;}
    break;

  case 101:
#line 412 "parser/faustparser.y"
    { (yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 102:
#line 414 "parser/faustparser.y"
    { (yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 103:
#line 415 "parser/faustparser.y"
    { (yyval.exp) = gMinPrim->box(); ;}
    break;

  case 104:
#line 416 "parser/faustparser.y"
    { (yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 105:
#line 418 "parser/faustparser.y"
    { (yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 106:
#line 419 "parser/faustparser.y"
    { (yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 107:
#line 421 "parser/faustparser.y"
    { (yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 108:
#line 422 "parser/faustparser.y"
    { (yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 109:
#line 423 "parser/faustparser.y"
    { (yyval.exp) = gRintPrim->box(); ;}
    break;

  case 110:
#line 426 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 111:
#line 427 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 112:
#line 429 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 113:
#line 430 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 114:
#line 432 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 115:
#line 433 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 116:
#line 435 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 117:
#line 437 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 118:
#line 439 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 119:
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 120:
#line 442 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 121:
#line 443 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 122:
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 123:
#line 445 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 124:
#line 446 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 125:
#line 448 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 126:
#line 449 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 127:
#line 450 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 128:
#line 451 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 129:
#line 452 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 130:
#line 453 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 131:
#line 454 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 132:
#line 455 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 133:
#line 456 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 134:
#line 457 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 135:
#line 459 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 136:
#line 460 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 137:
#line 461 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 138:
#line 462 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 139:
#line 466 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); ;}
    break;

  case 140:
#line 469 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 141:
#line 474 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 142:
#line 475 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 143:
#line 478 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 144:
#line 479 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 145:
#line 480 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 146:
#line 481 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 147:
#line 482 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 148:
#line 485 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 149:
#line 488 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); ;}
    break;

  case 150:
#line 491 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 151:
#line 492 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 152:
#line 498 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 153:
#line 502 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 154:
#line 506 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 155:
#line 510 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 156:
#line 517 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 157:
#line 521 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 158:
#line 524 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 159:
#line 528 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 160:
#line 531 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 161:
#line 535 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 162:
#line 538 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 163:
#line 541 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 164:
#line 544 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 165:
#line 547 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 166:
#line 550 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 167:
#line 554 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 168:
#line 557 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 169:
#line 562 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons((yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 170:
#line 563 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons((yyvsp[(2) - (4)].exp), nil)); ;}
    break;

  case 171:
#line 566 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 172:
#line 569 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 173:
#line 570 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 174:
#line 573 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),nil); ;}
    break;

  case 175:
#line 574 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 176:
#line 578 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 177:
#line 581 "parser/faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 178:
#line 582 "parser/faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2850 "parser/faustparser.cpp"
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


#line 585 "parser/faustparser.y"



