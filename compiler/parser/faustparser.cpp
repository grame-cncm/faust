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
     LETREC = 259,
     MIX = 260,
     SPLIT = 261,
     SEQ = 262,
     PAR = 263,
     REC = 264,
     NE = 265,
     GE = 266,
     GT = 267,
     EQ = 268,
     LE = 269,
     LT = 270,
     OR = 271,
     SUB = 272,
     ADD = 273,
     RSH = 274,
     LSH = 275,
     XOR = 276,
     AND = 277,
     MOD = 278,
     DIV = 279,
     MUL = 280,
     POWOP = 281,
     FDELAY = 282,
     DELAY1 = 283,
     DOT = 284,
     MEM = 285,
     PREFIX = 286,
     INTCAST = 287,
     FLOATCAST = 288,
     NOTYPECAST = 289,
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
     WHERE = 342,
     DEF = 343,
     IMPORT = 344,
     COMPONENT = 345,
     LIBRARY = 346,
     ENVIRONMENT = 347,
     WAVEFORM = 348,
     ROUTE = 349,
     ENABLE = 350,
     CONTROL = 351,
     IPAR = 352,
     ISEQ = 353,
     ISUM = 354,
     IPROD = 355,
     INPUTS = 356,
     OUTPUTS = 357,
     STRING = 358,
     FSTRING = 359,
     IDENT = 360,
     EXTRA = 361,
     DECLARE = 362,
     CASE = 363,
     ARROW = 364,
     ASSERTBOUNDS = 365,
     LOWEST = 366,
     HIGHEST = 367,
     FLOATMODE = 368,
     DOUBLEMODE = 369,
     QUADMODE = 370,
     FIXEDPOINTMODE = 371,
     BDOC = 372,
     EDOC = 373,
     BEQN = 374,
     EEQN = 375,
     BDGM = 376,
     EDGM = 377,
     BLST = 378,
     ELST = 379,
     BMETADATA = 380,
     EMETADATA = 381,
     DOCCHAR = 382,
     NOTICE = 383,
     LISTING = 384,
     LSTTRUE = 385,
     LSTFALSE = 386,
     LSTDEPENDENCIES = 387,
     LSTMDOCTAGS = 388,
     LSTDISTRIBUTED = 389,
     LSTEQ = 390,
     LSTQ = 391
   };
#endif
/* Tokens.  */
#define WITH 258
#define LETREC 259
#define MIX 260
#define SPLIT 261
#define SEQ 262
#define PAR 263
#define REC 264
#define NE 265
#define GE 266
#define GT 267
#define EQ 268
#define LE 269
#define LT 270
#define OR 271
#define SUB 272
#define ADD 273
#define RSH 274
#define LSH 275
#define XOR 276
#define AND 277
#define MOD 278
#define DIV 279
#define MUL 280
#define POWOP 281
#define FDELAY 282
#define DELAY1 283
#define DOT 284
#define MEM 285
#define PREFIX 286
#define INTCAST 287
#define FLOATCAST 288
#define NOTYPECAST 289
#define FFUNCTION 290
#define FCONSTANT 291
#define FVARIABLE 292
#define BUTTON 293
#define CHECKBOX 294
#define VSLIDER 295
#define HSLIDER 296
#define NENTRY 297
#define VGROUP 298
#define HGROUP 299
#define TGROUP 300
#define HBARGRAPH 301
#define VBARGRAPH 302
#define SOUNDFILE 303
#define ATTACH 304
#define ACOS 305
#define ASIN 306
#define ATAN 307
#define ATAN2 308
#define COS 309
#define SIN 310
#define TAN 311
#define EXP 312
#define LOG 313
#define LOG10 314
#define POWFUN 315
#define SQRT 316
#define ABS 317
#define MIN 318
#define MAX 319
#define FMOD 320
#define REMAINDER 321
#define FLOOR 322
#define CEIL 323
#define RINT 324
#define RDTBL 325
#define RWTBL 326
#define SELECT2 327
#define SELECT3 328
#define INT 329
#define FLOAT 330
#define LAMBDA 331
#define WIRE 332
#define CUT 333
#define ENDDEF 334
#define VIRG 335
#define LPAR 336
#define RPAR 337
#define LBRAQ 338
#define RBRAQ 339
#define LCROC 340
#define RCROC 341
#define WHERE 342
#define DEF 343
#define IMPORT 344
#define COMPONENT 345
#define LIBRARY 346
#define ENVIRONMENT 347
#define WAVEFORM 348
#define ROUTE 349
#define ENABLE 350
#define CONTROL 351
#define IPAR 352
#define ISEQ 353
#define ISUM 354
#define IPROD 355
#define INPUTS 356
#define OUTPUTS 357
#define STRING 358
#define FSTRING 359
#define IDENT 360
#define EXTRA 361
#define DECLARE 362
#define CASE 363
#define ARROW 364
#define ASSERTBOUNDS 365
#define LOWEST 366
#define HIGHEST 367
#define FLOATMODE 368
#define DOUBLEMODE 369
#define QUADMODE 370
#define FIXEDPOINTMODE 371
#define BDOC 372
#define EDOC 373
#define BEQN 374
#define EEQN 375
#define BDGM 376
#define EDGM 377
#define BLST 378
#define ELST 379
#define BMETADATA 380
#define EMETADATA 381
#define DOCCHAR 382
#define NOTICE 383
#define LISTING 384
#define LSTTRUE 385
#define LSTFALSE 386
#define LSTDEPENDENCIES 387
#define LSTMDOCTAGS 388
#define LSTDISTRIBUTED 389
#define LSTEQ 390
#define LSTQ 391




/* Copy the first part of user declarations.  */
#line 5 "faustparser.y"


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

//----------------------------------------------------------
// A definition is accepted if the prefixset is empty or if
// the current float precision is member of the prefix set
//----------------------------------------------------------
inline bool acceptdefinition(int prefixset)
{
	int precisions[] = {0, 1, 2, 4, 8};
	return (prefixset==0) || (prefixset & precisions[gGlobal->gFloatSize]);
}
    
//----------------------------------------------------------
// 'atoi' does not work correctly on Windows with MSVC on values
// greater than 2^31 (= 2147483648)
//----------------------------------------------------------
inline int str2int(const char* str)
{
    int result = 0;
    while (*str != 0) {
        result = result * 10 + *str - '0';
        str++;
    }
    return result;
}

inline Tree unquote(char* str)
{
    size_t size = strlen(str) + 1;
    
    //-----------copy unquoted filename-------------
    char* buf = (char*)alloca(size);
    size_t j=0;

    if (str[0] == '"') {
        // it is a quoted string, we remove the quotes
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
#line 96 "faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;
}
/* Line 193 of yacc.c.  */
#line 467 "faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 480 "faustparser.cpp"

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
#define YYLAST   747

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  137
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  231
/* YYNRULES -- Number of states.  */
#define YYNSTATES  493

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   391

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
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,    10,    11,    15,    16,    19,
      21,    23,    25,    27,    28,    31,    33,    37,    39,    41,
      44,    47,    50,    53,    59,    64,    70,    72,    76,    77,
      80,    82,    84,    86,    88,    90,    92,    93,    96,   100,
     104,   106,   110,   111,   114,   120,   126,   132,   134,   136,
     140,   148,   153,   156,   161,   164,   166,   169,   171,   175,
     181,   187,   195,   199,   203,   207,   211,   215,   217,   221,
     225,   229,   233,   237,   241,   245,   248,   252,   256,   260,
     264,   268,   272,   276,   280,   284,   288,   292,   296,   301,
     306,   308,   310,   312,   315,   318,   321,   324,   326,   328,
     330,   332,   334,   336,   338,   340,   342,   344,   346,   348,
     350,   352,   354,   356,   358,   360,   362,   364,   366,   368,
     370,   372,   374,   376,   378,   380,   382,   384,   386,   388,
     390,   392,   394,   396,   398,   400,   402,   404,   406,   408,
     410,   412,   414,   416,   418,   420,   422,   424,   426,   428,
     430,   432,   434,   437,   441,   450,   455,   457,   459,   461,
     466,   471,   476,   481,   488,   497,   499,   501,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   523,   525,
     527,   529,   531,   533,   535,   537,   541,   545,   549,   553,
     557,   559,   561,   563,   565,   567,   576,   585,   594,   603,
     608,   613,   622,   630,   638,   643,   648,   661,   674,   687,
     694,   701,   708,   717,   726,   733,   739,   747,   757,   762,
     769,   778,   780,   782,   786,   788,   791,   798,   800,   802,
     804,   806
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     138,     0,    -1,   139,    -1,    -1,   139,   141,   146,    -1,
      -1,   140,   141,   158,    -1,    -1,   141,   142,    -1,   113,
      -1,   114,    -1,   115,    -1,   116,    -1,    -1,   143,   159,
      -1,   145,    -1,   144,     8,   145,    -1,    74,    -1,    75,
      -1,    18,    74,    -1,    18,    75,    -1,    17,    74,    -1,
      17,    75,    -1,    89,    81,   171,    82,    79,    -1,   107,
     167,   170,    79,    -1,   107,   167,   167,   170,    79,    -1,
     158,    -1,   117,   147,   118,    -1,    -1,   147,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     157,    -1,    -1,   149,   127,    -1,   119,   163,   120,    -1,
     121,   163,   122,    -1,   128,    -1,   123,   154,   124,    -1,
      -1,   154,   155,    -1,   132,   135,   136,   156,   136,    -1,
     133,   135,   136,   156,   136,    -1,   134,   135,   136,   156,
     136,    -1,   130,    -1,   131,    -1,   125,   167,   126,    -1,
     160,    81,   168,    82,    88,   163,    79,    -1,   160,    88,
     163,    79,    -1,     1,    79,    -1,   161,    88,   163,    79,
      -1,     1,    79,    -1,   166,    -1,    28,   166,    -1,   166,
      -1,   162,     8,   166,    -1,   163,     3,    83,   140,    84,
      -1,   163,     4,    83,   143,    84,    -1,   163,     4,    83,
     143,    87,   140,    84,    -1,   163,     8,   163,    -1,   163,
       7,   163,    -1,   163,     6,   163,    -1,   163,     5,   163,
      -1,   163,     9,   163,    -1,   164,    -1,   164,    18,   164,
      -1,   164,    17,   164,    -1,   164,    25,   164,    -1,   164,
      24,   164,    -1,   164,    23,   164,    -1,   164,    26,   164,
      -1,   164,    27,   164,    -1,   164,    28,    -1,   164,    29,
     166,    -1,   164,    22,   164,    -1,   164,    16,   164,    -1,
     164,    21,   164,    -1,   164,    20,   164,    -1,   164,    19,
     164,    -1,   164,    15,   164,    -1,   164,    14,   164,    -1,
     164,    12,   164,    -1,   164,    11,   164,    -1,   164,    13,
     164,    -1,   164,    10,   164,    -1,   164,    81,   168,    82,
      -1,   164,    85,   140,    86,    -1,   165,    -1,    74,    -1,
      75,    -1,    18,    74,    -1,    18,    75,    -1,    17,    74,
      -1,    17,    75,    -1,    77,    -1,    78,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    18,    -1,    17,    -1,
      25,    -1,    24,    -1,    23,    -1,    27,    -1,    22,    -1,
      16,    -1,    21,    -1,    20,    -1,    19,    -1,    15,    -1,
      14,    -1,    12,    -1,    11,    -1,    13,    -1,    10,    -1,
      49,    -1,    95,    -1,    96,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    26,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,    72,    -1,    73,    -1,   110,    -1,   111,    -1,
     112,    -1,   166,    -1,    17,   166,    -1,    81,   163,    82,
      -1,    76,    81,   162,    82,    29,    81,   163,    82,    -1,
     108,    83,   196,    84,    -1,   179,    -1,   180,    -1,   181,
      -1,    90,    81,   171,    82,    -1,    91,    81,   171,    82,
      -1,    92,    83,   139,    84,    -1,    93,    83,   144,    84,
      -1,    94,    81,   169,     8,   169,    82,    -1,    94,    81,
     169,     8,   169,     8,   163,    82,    -1,   182,    -1,   183,
      -1,   184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,
      -1,   189,    -1,   190,    -1,   191,    -1,   192,    -1,   173,
      -1,   174,    -1,   175,    -1,   176,    -1,   177,    -1,   178,
      -1,   105,    -1,   105,    -1,   169,    -1,   168,     8,   169,
      -1,   169,     7,   169,    -1,   169,     6,   169,    -1,   169,
       5,   169,    -1,   169,     9,   169,    -1,   164,    -1,   103,
      -1,   103,    -1,   103,    -1,   104,    -1,    97,    81,   166,
       8,   169,     8,   163,    82,    -1,    98,    81,   166,     8,
     169,     8,   163,    82,    -1,    99,    81,   166,     8,   169,
       8,   163,    82,    -1,   100,    81,   166,     8,   169,     8,
     163,    82,    -1,   101,    81,   163,    82,    -1,   102,    81,
     163,    82,    -1,    35,    81,   193,     8,   172,     8,   170,
      82,    -1,    36,    81,   198,   167,     8,   172,    82,    -1,
      37,    81,   198,   167,     8,   172,    82,    -1,    38,    81,
     171,    82,    -1,    39,    81,   171,    82,    -1,    40,    81,
     171,     8,   169,     8,   169,     8,   169,     8,   169,    82,
      -1,    41,    81,   171,     8,   169,     8,   169,     8,   169,
       8,   169,    82,    -1,    42,    81,   171,     8,   169,     8,
     169,     8,   169,     8,   169,    82,    -1,    43,    81,   171,
       8,   163,    82,    -1,    44,    81,   171,     8,   163,    82,
      -1,    45,    81,   171,     8,   163,    82,    -1,    47,    81,
     171,     8,   169,     8,   169,    82,    -1,    46,    81,   171,
       8,   169,     8,   169,    82,    -1,    48,    81,   171,     8,
     169,    82,    -1,   198,   194,    81,   195,    82,    -1,   198,
     194,    16,   194,    81,   195,    82,    -1,   198,   194,    16,
     194,    16,   194,    81,   195,    82,    -1,   198,   194,    81,
      82,    -1,   198,   194,    16,   194,    81,    82,    -1,   198,
     194,    16,   194,    16,   194,    81,    82,    -1,   105,    -1,
     199,    -1,   195,     8,   199,    -1,   197,    -1,   196,   197,
      -1,    81,   168,    82,   109,   163,    79,    -1,    32,    -1,
      33,    -1,    32,    -1,    33,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   347,   347,   350,   351,   354,   355,   358,   359,   362,
     363,   364,   365,   368,   369,   376,   377,   380,   381,   382,
     383,   384,   385,   388,   389,   390,   391,   392,   395,   396,
     399,   400,   401,   402,   403,   404,   407,   408,   411,   414,
     417,   420,   423,   424,   427,   428,   429,   432,   433,   436,
     439,   440,   441,   444,   445,   448,   451,   454,   455,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   479,   480,   481,
     483,   484,   486,   487,   488,   489,   490,   491,   493,   494,
     496,   499,   500,   502,   503,   505,   506,   508,   509,   511,
     512,   514,   515,   517,   518,   519,   520,   521,   522,   524,
     525,   526,   528,   529,   531,   532,   533,   534,   535,   536,
     538,   539,   540,   542,   543,   544,   545,   546,   547,   548,
     550,   551,   552,   553,   554,   555,   557,   558,   559,   561,
     562,   564,   565,   566,   568,   569,   571,   572,   574,   575,
     576,   578,   579,   581,   582,   585,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   608,   609,   610,   611,
     613,   614,   618,   621,   624,   625,   628,   629,   630,   631,
     632,   635,   638,   641,   642,   647,   651,   655,   659,   663,
     666,   671,   675,   679,   684,   687,   690,   693,   696,   699,
     702,   705,   709,   712,   715,   722,   723,   724,   726,   727,
     728,   731,   734,   735,   738,   739,   742,   746,   747,   750,
     751,   752
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "LETREC", "MIX", "SPLIT", "SEQ",
  "PAR", "REC", "NE", "GE", "GT", "EQ", "LE", "LT", "OR", "SUB", "ADD",
  "RSH", "LSH", "XOR", "AND", "MOD", "DIV", "MUL", "POWOP", "FDELAY",
  "DELAY1", "DOT", "MEM", "PREFIX", "INTCAST", "FLOATCAST", "NOTYPECAST",
  "FFUNCTION", "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER",
  "HSLIDER", "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH",
  "VBARGRAPH", "SOUNDFILE", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2",
  "COS", "SIN", "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS",
  "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL",
  "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT",
  "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC",
  "WHERE", "DEF", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT",
  "WAVEFORM", "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM",
  "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA",
  "DECLARE", "CASE", "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST",
  "FLOATMODE", "DOUBLEMODE", "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC",
  "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
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
  "rulelist", "rule", "type", "argtype", 0
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   137,   138,   139,   139,   140,   140,   141,   141,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     145,   145,   145,   146,   146,   146,   146,   146,   147,   147,
     148,   148,   148,   148,   148,   148,   149,   149,   150,   151,
     152,   153,   154,   154,   155,   155,   155,   156,   156,   157,
     158,   158,   158,   159,   159,   160,   161,   162,   162,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   166,   167,   168,   168,   169,   169,   169,   169,
     169,   170,   171,   172,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   193,   193,   193,   193,
     193,   194,   195,   195,   196,   196,   197,   198,   198,   199,
     199,   199
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     2,
       2,     2,     2,     5,     4,     5,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     3,
       1,     3,     0,     2,     5,     5,     5,     1,     1,     3,
       7,     4,     2,     4,     2,     1,     2,     1,     3,     5,
       5,     7,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     8,     4,     1,     1,     1,     4,
       4,     4,     4,     6,     8,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     8,     8,     8,     8,     4,
       4,     8,     7,     7,     4,     4,    12,    12,    12,     6,
       6,     6,     8,     8,     6,     5,     7,     9,     4,     6,
       8,     1,     1,     3,     1,     2,     6,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   182,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   183,     0,    36,     0,     0,   192,     0,   191,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   119,   117,   116,   118,   115,   114,
     110,   104,   103,   113,   112,   111,   109,   107,   106,   105,
     133,   108,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,    91,    92,     0,    97,    98,
       0,     0,     0,     0,     0,     0,   121,   122,     0,     0,
       0,     0,     0,     0,     0,   148,   149,   150,   190,    90,
     151,     0,   184,   176,   177,   178,   179,   180,   181,   156,
     157,   158,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,    67,     0,     0,    24,     0,     0,
       0,     0,    37,    95,    96,   152,    93,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    23,    25,    38,    39,    41,     0,     0,     0,
      43,    49,   227,   228,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   153,     0,     0,     7,     0,     0,    17,    18,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     224,    87,    85,    84,    86,    83,    82,    78,    69,    68,
      81,    80,    79,    77,    72,    71,    70,    73,    74,    76,
       0,     7,   185,     0,   188,   187,   186,   189,     5,    13,
      65,    64,    63,    62,    66,     0,     0,     0,     0,   221,
       0,     0,     0,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,   160,   161,    21,
      22,    19,    20,     0,   162,     0,     0,     0,     0,     0,
     199,   200,     0,   155,   225,    88,    89,     0,     0,     7,
       0,     0,     0,     0,   193,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,     0,    16,     0,     0,     0,     0,     0,     0,     6,
      50,    59,     0,     0,    60,     5,    14,     0,    47,    48,
       0,     0,     0,     0,     0,   229,   230,   231,   218,     0,
     222,     0,     0,     0,     0,     0,   209,   210,   211,     0,
       0,   214,     0,     0,   163,     0,     0,     0,     0,     0,
      54,    56,     7,     0,    44,    45,    46,     0,     0,     0,
       0,   215,   202,   203,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,   201,     0,
     219,     0,   223,     0,     0,     0,   213,   212,   154,   164,
     195,   196,   197,   198,   226,    53,     0,   216,     0,     0,
       0,   220,     0,     0,     0,     0,   217,     0,     0,     0,
     206,   207,   208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   301,   357,    14,   360,   269,   270,    15,
      23,    37,    38,    39,    40,    41,    42,   160,   240,   400,
      43,    16,   396,    17,   397,   259,   153,   128,   129,   130,
      22,   131,   132,    30,    27,   366,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   244,   320,   409,   279,
     280,   245,   410
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -394
static const yytype_int16 yypact[] =
{
    -394,     4,    98,  -394,     2,    25,    46,  -394,    39,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,    20,  -394,  -394,
      95,  -394,   -61,   492,   420,   420,  -394,    67,  -394,   134,
      75,  -394,   420,   420,  -394,    39,  -394,  -394,   135,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,    60,    92,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,   187,   232,   242,   262,
     278,   300,   302,   318,   328,   336,   347,   373,   418,   428,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,   442,  -394,  -394,
     420,   443,   445,   309,   313,   446,  -394,  -394,   448,   459,
     494,   495,   496,   520,   337,  -394,  -394,  -394,   531,  -394,
    -394,   138,   355,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,   289,   531,   270,   421,  -394,    27,     6,
     -21,   476,  -394,  -394,  -394,  -394,  -394,  -394,   297,   297,
     297,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,   500,    44,    95,    95,  -394,   315,   420,   500,
     500,   500,   500,   420,   420,   525,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,  -394,   500,   420,  -394,   420,   519,
     420,   420,   420,   420,   535,   536,   420,   420,   420,   420,
     420,  -394,  -394,  -394,  -394,  -394,  -394,   473,   479,   493,
    -394,  -394,  -394,  -394,   619,   524,    39,    39,   561,   562,
     634,   698,   699,   700,   701,   702,   703,   704,   705,   156,
    -394,  -394,   632,   633,   635,   226,   266,  -394,  -394,    12,
    -394,   364,   708,   709,   710,   712,    51,    58,   420,    72,
    -394,   545,   545,   545,   545,   545,   545,   560,   560,   560,
     326,   326,   326,   326,   326,   326,   326,   310,   299,  -394,
     209,   636,   355,   420,   355,   355,   212,  -394,  -394,  -394,
     407,   407,   130,   339,  -394,   585,   587,   588,   231,  -394,
      24,   717,   718,  -394,  -394,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   500,   706,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,   315,  -394,   420,   420,   420,   420,   420,
    -394,  -394,   238,  -394,  -394,  -394,  -394,    16,   303,   643,
      15,   275,   275,   275,  -394,  -394,   720,   524,    54,   231,
     231,   616,   626,   631,    66,    73,   154,   641,   646,    32,
    -394,   648,  -394,    18,   651,   656,   661,   666,   621,  -394,
    -394,  -394,   652,   500,  -394,  -394,  -394,   644,  -394,  -394,
     597,   598,   600,   134,    29,  -394,  -394,  -394,  -394,   294,
    -394,   655,   657,   420,   420,   420,  -394,  -394,  -394,   420,
     420,  -394,   420,   420,  -394,   420,   420,   420,   420,   420,
    -394,  -394,   654,   420,  -394,  -394,  -394,   658,   524,   118,
     345,  -394,  -394,  -394,   671,   676,   681,    88,   136,   188,
     207,   236,   249,   268,   276,   499,  -394,   530,  -394,   660,
    -394,   306,  -394,   420,   420,   420,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,   312,  -394,   686,   691,
     696,  -394,   311,   420,   420,   420,  -394,   254,   260,   281,
    -394,  -394,  -394
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -394,  -394,   556,  -303,     0,  -394,  -394,  -394,   400,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,    -6,
    -394,   387,  -394,  -394,  -394,  -394,    -4,   -25,  -394,    17,
     -16,  -194,   -98,   -28,   419,    57,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -349,  -393,  -394,
     466,   279,   307
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     154,   156,     4,     5,     3,   359,    29,   154,   154,   224,
     225,   226,   227,   228,   229,   230,   392,     5,   404,   161,
     343,    18,   300,   220,   221,   222,   423,   223,   158,   159,
     224,   225,   226,   227,   228,   229,   230,   220,   221,   222,
     367,   223,    28,   393,    21,   438,   461,   224,   225,   226,
     227,   228,   229,   230,   224,   225,   226,   227,   228,   229,
     230,   224,   225,   226,   227,   228,   229,   230,   165,   224,
     225,   226,   227,   228,   229,   230,   224,   225,   226,   227,
     228,   229,   230,   482,   352,   154,   405,   406,   407,   459,
     271,     6,   432,   220,   221,   222,   344,   223,    -2,   394,
     424,    24,   395,   236,    19,   368,   183,     7,    25,     8,
     439,   237,   238,   239,   421,     9,    10,    11,    12,    13,
     302,     7,   304,   305,   306,   307,   261,    20,   235,     9,
      10,    11,    12,   350,   163,   164,   408,   228,   229,   230,
     351,   220,   221,   222,    21,   223,   218,   234,   416,   155,
     405,   406,   407,   278,   157,   417,   353,   224,   225,   226,
     227,   228,   229,   230,   334,     7,   166,   167,   154,   154,
     466,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   276,
     277,   224,   225,   226,   227,   228,   229,   230,    26,   260,
     460,   154,   154,   154,   154,   154,   272,   273,   274,   275,
     224,   225,   226,   227,   228,   229,   230,   218,   467,   222,
     219,   223,   310,   311,   312,   313,   314,   371,   372,   373,
     321,   322,   299,   377,   378,   379,   418,    28,   335,   224,
     225,   226,   227,   228,   229,   230,   218,   383,   384,   385,
     386,   387,   224,   225,   226,   227,   228,   229,   230,   220,
     221,   222,   162,   223,     4,   220,   221,   222,   168,   223,
     468,   224,   225,   226,   227,   228,   229,   230,   154,   224,
     225,   226,   227,   228,   229,   230,   220,   221,   222,   469,
     223,   355,   224,   225,   226,   227,   228,   229,   230,   358,
     339,   340,   440,   154,   154,   154,   224,   225,   226,   227,
     228,   229,   230,   169,   440,   444,   445,   446,   470,   440,
     388,   447,   448,   170,   374,   375,   376,   214,   215,   242,
     243,   471,   265,   266,   364,   365,   490,   213,   214,   215,
     341,   342,   491,   171,   405,   406,   407,   229,   230,   232,
     472,   380,   212,   213,   214,   215,   401,   402,   473,   172,
     220,   221,   222,   492,   223,   478,   479,   480,   231,   220,
     221,   222,   345,   223,    18,   437,   441,   405,   406,   407,
     216,   173,   390,   174,   217,   487,   488,   489,   477,   267,
     268,   216,   186,   486,   481,   217,   187,   154,   154,   175,
     154,   154,   154,   154,   154,   398,   399,   216,   154,   176,
     431,   217,   226,   227,   228,   229,   230,   177,   449,   450,
     195,   451,   452,   453,   454,   455,   411,   412,   178,   457,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   246,   247,
      62,    63,    64,    65,   179,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   180,
     233,   110,   224,   225,   226,   227,   228,   229,   230,   181,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   182,   184,     7,   185,   188,   124,   189,
     125,   126,   127,   224,   225,   226,   227,   228,   229,   230,
     190,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   191,   192,   193,   474,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   194,   241,   262,   263,     7,   278,   303,   315,   475,
      31,    32,   216,    33,   316,    34,   217,    35,   308,   309,
      36,   220,   221,   222,   413,   223,   216,   318,   317,   319,
     217,   220,   221,   222,   414,   223,   220,   221,   222,   415,
     223,   216,   325,   323,   324,   217,   220,   221,   222,   419,
     223,   220,   221,   222,   420,   223,   220,   221,   222,   425,
     223,   220,   221,   222,   426,   223,   220,   221,   222,   427,
     223,   220,   221,   222,   428,   223,   220,   221,   222,   463,
     223,   220,   221,   222,   464,   223,   220,   221,   222,   465,
     223,   220,   221,   222,   483,   223,   220,   221,   222,   484,
     223,   220,   221,   222,   485,   223,   326,   327,   328,   329,
     330,   331,   332,   333,   336,   337,   346,   347,   348,   338,
     349,   361,   356,   362,   363,   369,   370,   391,   403,   422,
     429,   430,   433,   434,   435,   381,   436,   442,   456,   443,
     458,   476,   264,   382,   389,   354,     0,   462
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,     1,     0,   308,    22,    32,    33,     3,
       4,     5,     6,     7,     8,     9,     1,     1,   367,    35,
       8,     4,   216,     5,     6,     7,     8,     9,    32,    33,
       3,     4,     5,     6,     7,     8,     9,     5,     6,     7,
      16,     9,   103,    28,   105,    16,   439,     3,     4,     5,
       6,     7,     8,     9,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,    51,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,   476,   278,   110,    32,    33,    34,   438,
     188,    89,   395,     5,     6,     7,    84,     9,     0,    84,
      82,    81,    87,   124,    79,    81,   110,   105,    88,   107,
      81,   132,   133,   134,    82,   113,   114,   115,   116,   117,
     218,   105,   220,   221,   222,   223,    82,    81,   122,   113,
     114,   115,   116,    82,    74,    75,    82,     7,     8,     9,
      82,     5,     6,     7,   105,     9,     8,   120,    82,    82,
      32,    33,    34,    81,    79,    82,    84,     3,     4,     5,
       6,     7,     8,     9,     8,   105,    74,    75,   193,   194,
      82,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   193,
     194,     3,     4,     5,     6,     7,     8,     9,   103,   182,
      82,   226,   227,   228,   229,   230,   189,   190,   191,   192,
       3,     4,     5,     6,     7,     8,     9,     8,    82,     7,
      82,     9,   226,   227,   228,   229,   230,   325,   326,   327,
     246,   247,   215,   331,   332,   333,    82,   103,    82,     3,
       4,     5,     6,     7,     8,     9,     8,   345,   346,   347,
     348,   349,     3,     4,     5,     6,     7,     8,     9,     5,
       6,     7,   127,     9,   264,     5,     6,     7,    81,     9,
      82,     3,     4,     5,     6,     7,     8,     9,   303,     3,
       4,     5,     6,     7,     8,     9,     5,     6,     7,    82,
       9,    82,     3,     4,     5,     6,     7,     8,     9,   303,
      74,    75,     8,   328,   329,   330,     3,     4,     5,     6,
       7,     8,     9,    81,     8,   413,   414,   415,    82,     8,
      82,   419,   420,    81,   328,   329,   330,    28,    29,    32,
      33,    82,    17,    18,   103,   104,    82,    27,    28,    29,
      74,    75,    82,    81,    32,    33,    34,     8,     9,    79,
      82,   334,    26,    27,    28,    29,   362,   363,    82,    81,
       5,     6,     7,    82,     9,   463,   464,   465,    79,     5,
       6,     7,     8,     9,   357,   403,    82,    32,    33,    34,
      81,    81,    79,    81,    85,   483,   484,   485,    82,    74,
      75,    81,    83,    82,    82,    85,    83,   422,   423,    81,
     425,   426,   427,   428,   429,   130,   131,    81,   433,    81,
     393,    85,     5,     6,     7,     8,     9,    81,   422,   423,
      83,   425,   426,   427,   428,   429,   369,   370,    81,   433,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,   169,   170,
      30,    31,    32,    33,    81,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    81,
      79,    81,     3,     4,     5,     6,     7,     8,     9,    81,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    81,    81,   105,    81,    81,   108,    81,
     110,   111,   112,     3,     4,     5,     6,     7,     8,     9,
      81,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    81,    81,    81,    79,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,    81,   126,   184,   185,   105,    81,    88,   135,    79,
     118,   119,    81,   121,   135,   123,    85,   125,    83,    83,
     128,     5,     6,     7,     8,     9,    81,     8,   135,   105,
      85,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,    81,     8,    82,    82,    85,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     8,     8,     8,     8,
       8,     8,     8,     8,    82,    82,     8,     8,     8,    84,
       8,   136,    86,   136,   136,     8,     8,    84,     8,    81,
     109,    79,    88,   136,   136,    29,   136,    82,    84,    82,
      82,    81,   186,   343,   357,   279,    -1,   440
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   138,   139,     0,   141,     1,    89,   105,   107,   113,
     114,   115,   116,   117,   142,   146,   158,   160,   166,    79,
      81,   105,   167,   147,    81,    88,   103,   171,   103,   167,
     170,   118,   119,   121,   123,   125,   128,   148,   149,   150,
     151,   152,   153,   157,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      81,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   108,   110,   111,   112,   164,   165,
     166,   168,   169,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   163,   164,    82,   170,    79,   163,   163,
     154,   167,   127,    74,    75,   166,    74,    75,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,   163,    81,    81,    83,    83,    81,    81,
      81,    81,    81,    81,    81,    83,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    81,    85,     8,    82,
       5,     6,     7,     9,     3,     4,     5,     6,     7,     8,
       9,    79,    79,    79,   120,   122,   124,   132,   133,   134,
     155,   126,    32,    33,   193,   198,   198,   198,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   162,
     166,    82,   171,   171,   139,    17,    18,    74,    75,   144,
     145,   169,   166,   166,   166,   166,   163,   163,    81,   196,
     197,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   166,
     168,   140,   169,    88,   169,   169,   169,   169,    83,    83,
     163,   163,   163,   163,   163,   135,   135,   135,     8,   105,
     194,   167,   167,    82,    82,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,    82,    82,    82,    84,    74,
      75,    74,    75,     8,    84,     8,     8,     8,     8,     8,
      82,    82,   168,    84,   197,    82,    86,   141,   163,   140,
     143,   136,   136,   136,   103,   104,   172,    16,    81,     8,
       8,   169,   169,   169,   163,   163,   163,   169,   169,   169,
     166,    29,   145,   169,   169,   169,   169,   169,    82,   158,
      79,    84,     1,    28,    84,    87,   159,   161,   130,   131,
     156,   156,   156,     8,   194,    32,    33,    34,    82,   195,
     199,   172,   172,     8,     8,     8,    82,    82,    82,     8,
       8,    82,    81,     8,    82,     8,     8,     8,     8,   109,
      79,   166,   140,    88,   136,   136,   136,   170,    16,    81,
       8,    82,    82,    82,   169,   169,   169,   169,   169,   163,
     163,   163,   163,   163,   163,   163,    84,   163,    82,   194,
      82,   195,   199,     8,     8,     8,    82,    82,    82,    82,
      82,    82,    82,    82,    79,    79,    81,    82,   169,   169,
     169,    82,   195,     8,     8,     8,    82,   169,   169,   169,
      82,    82,    82
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
#line 347 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 350 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 4:
#line 351 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp); ;}
    break;

  case 5:
#line 354 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 6:
#line 355 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp);;}
    break;

  case 7:
#line 358 "faustparser.y"
    { (yyval.numvariant) = 0; ;}
    break;

  case 8:
#line 359 "faustparser.y"
    { (yyval.numvariant) = (yyvsp[(1) - (2)].numvariant) | (yyvsp[(2) - (2)].numvariant);;}
    break;

  case 9:
#line 362 "faustparser.y"
    { (yyval.numvariant) = 1;;}
    break;

  case 10:
#line 363 "faustparser.y"
    { (yyval.numvariant) = 2;;}
    break;

  case 11:
#line 364 "faustparser.y"
    { (yyval.numvariant) = 4;;}
    break;

  case 12:
#line 365 "faustparser.y"
    { (yyval.numvariant) = 8;;}
    break;

  case 13:
#line 368 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 14:
#line 369 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 15:
#line 376 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 377 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); ;}
    break;

  case 17:
#line 380 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(yytext)); ;}
    break;

  case 18:
#line 381 "faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 19:
#line 382 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(yytext)); ;}
    break;

  case 20:
#line 383 "faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 21:
#line 384 "faustparser.y"
    { (yyval.exp) = boxInt(-str2int(yytext)); ;}
    break;

  case 22:
#line 385 "faustparser.y"
    { (yyval.exp) = boxReal(-atof(yytext)); ;}
    break;

  case 23:
#line 388 "faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 24:
#line 389 "faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 25:
#line 390 "faustparser.y"
    { declareDefinitionMetadata((yyvsp[(2) - (5)].exp),(yyvsp[(3) - (5)].exp),(yyvsp[(4) - (5)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 26:
#line 391 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 27:
#line 392 "faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 28:
#line 395 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 29:
#line 396 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 30:
#line 399 "faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 31:
#line 400 "faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 32:
#line 401 "faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 33:
#line 402 "faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 34:
#line 403 "faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 35:
#line 404 "faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 36:
#line 407 "faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 37:
#line 408 "faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); ;}
    break;

  case 38:
#line 411 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 39:
#line 414 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 40:
#line 417 "faustparser.y"
    { ;}
    break;

  case 41:
#line 420 "faustparser.y"
    { ;}
    break;

  case 42:
#line 423 "faustparser.y"
    { ;}
    break;

  case 43:
#line 424 "faustparser.y"
    { ;}
    break;

  case 44:
#line 427 "faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 45:
#line 428 "faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; ;}
    break;

  case 46:
#line 429 "faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 47:
#line 432 "faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 48:
#line 433 "faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 49:
#line 436 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 50:
#line 439 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); setDefProp((yyvsp[(1) - (7)].exp), yyfilename, yylineno); ;}
    break;

  case 51:
#line 440 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp)));  setDefProp((yyvsp[(1) - (4)].exp), yyfilename, yylineno); ;}
    break;

  case 52:
#line 441 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; yyerr++; ;}
    break;

  case 53:
#line 444 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); setDefProp((yyvsp[(1) - (4)].exp), yyfilename, yylineno); ;}
    break;

  case 54:
#line 445 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; yyerr++; ;}
    break;

  case 55:
#line 448 "faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); ;}
    break;

  case 56:
#line 451 "faustparser.y"
    { (yyval.exp)=(yyvsp[(2) - (2)].exp); ;}
    break;

  case 57:
#line 454 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 58:
#line 455 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 59:
#line 458 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 60:
#line 459 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp)), gGlobal->nil); ;}
    break;

  case 61:
#line 460 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (7)].exp),formatDefinitions((yyvsp[(4) - (7)].exp)),formatDefinitions((yyvsp[(6) - (7)].exp))); ;}
    break;

  case 62:
#line 461 "faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 63:
#line 462 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 64:
#line 463 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 65:
#line 464 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 66:
#line 465 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 67:
#line 466 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 68:
#line 469 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 69:
#line 470 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 70:
#line 471 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 71:
#line 472 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 72:
#line 473 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 73:
#line 474 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gGlobal->gPowPrim->box()); ;}
    break;

  case 74:
#line 475 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDelay)); ;}
    break;

  case 75:
#line 476 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 76:
#line 477 "faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 77:
#line 479 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 78:
#line 480 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 79:
#line 481 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 80:
#line 483 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 81:
#line 484 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigARightShift)); ;}
    break;

  case 82:
#line 486 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 83:
#line 487 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 84:
#line 488 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 85:
#line 489 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 86:
#line 490 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 87:
#line 491 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 88:
#line 493 "faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 89:
#line 494 "faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 90:
#line 496 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 91:
#line 499 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(yytext)); ;}
    break;

  case 92:
#line 500 "faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 93:
#line 502 "faustparser.y"
    { (yyval.exp) = boxInt (str2int(yytext)); ;}
    break;

  case 94:
#line 503 "faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); ;}
    break;

  case 95:
#line 505 "faustparser.y"
    { (yyval.exp) = boxInt ( -str2int(yytext) ); ;}
    break;

  case 96:
#line 506 "faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); ;}
    break;

  case 97:
#line 508 "faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 98:
#line 509 "faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 99:
#line 511 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 100:
#line 512 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 101:
#line 514 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 102:
#line 515 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 103:
#line 517 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 104:
#line 518 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 105:
#line 519 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 106:
#line 520 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 107:
#line 521 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 108:
#line 522 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDelay); ;}
    break;

  case 109:
#line 524 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 110:
#line 525 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 111:
#line 526 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 112:
#line 528 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 113:
#line 529 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigARightShift); ;}
    break;

  case 114:
#line 531 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 115:
#line 532 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 116:
#line 533 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 117:
#line 534 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 118:
#line 535 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 119:
#line 536 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 120:
#line 538 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 121:
#line 539 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEnable); ;}
    break;

  case 122:
#line 540 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigControl); ;}
    break;

  case 123:
#line 542 "faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); ;}
    break;

  case 124:
#line 543 "faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); ;}
    break;

  case 125:
#line 544 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); ;}
    break;

  case 126:
#line 545 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); ;}
    break;

  case 127:
#line 546 "faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); ;}
    break;

  case 128:
#line 547 "faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); ;}
    break;

  case 129:
#line 548 "faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); ;}
    break;

  case 130:
#line 550 "faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); ;}
    break;

  case 131:
#line 551 "faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); ;}
    break;

  case 132:
#line 552 "faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); ;}
    break;

  case 133:
#line 553 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 134:
#line 554 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 135:
#line 555 "faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); ;}
    break;

  case 136:
#line 557 "faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); ;}
    break;

  case 137:
#line 558 "faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); ;}
    break;

  case 138:
#line 559 "faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); ;}
    break;

  case 139:
#line 561 "faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); ;}
    break;

  case 140:
#line 562 "faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); ;}
    break;

  case 141:
#line 564 "faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); ;}
    break;

  case 142:
#line 565 "faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); ;}
    break;

  case 143:
#line 566 "faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); ;}
    break;

  case 144:
#line 568 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 145:
#line 569 "faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 146:
#line 571 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 147:
#line 572 "faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 148:
#line 574 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigAssertBounds);;}
    break;

  case 149:
#line 575 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigLowest);;}
    break;

  case 150:
#line 576 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigHighest);;}
    break;

  case 151:
#line 578 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);  setUseProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno);;}
    break;

  case 152:
#line 579 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 153:
#line 581 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 154:
#line 583 "faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 155:
#line 585 "faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 156:
#line 587 "faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 157:
#line 588 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 158:
#line 589 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 159:
#line 590 "faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 160:
#line 591 "faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 161:
#line 592 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 162:
#line 593 "faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); ;}
    break;

  case 163:
#line 594 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp), boxPar(boxInt(0),boxInt(0))); ;}
    break;

  case 164:
#line 595 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), (yyvsp[(7) - (8)].exp)); ;}
    break;

  case 165:
#line 596 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 166:
#line 597 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 167:
#line 598 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 168:
#line 599 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 169:
#line 600 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 170:
#line 601 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 171:
#line 602 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 172:
#line 603 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 173:
#line 604 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 174:
#line 605 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 175:
#line 606 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 176:
#line 608 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 177:
#line 609 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 178:
#line 610 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 179:
#line 611 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 180:
#line 613 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 181:
#line 614 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 182:
#line 618 "faustparser.y"
    { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  ;}
    break;

  case 183:
#line 621 "faustparser.y"
    { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  ;}
    break;

  case 184:
#line 624 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 185:
#line 625 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 186:
#line 628 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 187:
#line 629 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 188:
#line 630 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 189:
#line 631 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 190:
#line 632 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 191:
#line 635 "faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 192:
#line 638 "faustparser.y"
    { (yyval.exp) = unquote(yytext); ;}
    break;

  case 193:
#line 641 "faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 194:
#line 642 "faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 195:
#line 648 "faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 196:
#line 652 "faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 197:
#line 656 "faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 198:
#line 660 "faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 199:
#line 663 "faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 200:
#line 666 "faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 201:
#line 672 "faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 202:
#line 676 "faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 203:
#line 680 "faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 204:
#line 684 "faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 205:
#line 687 "faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 206:
#line 691 "faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 207:
#line 694 "faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 208:
#line 697 "faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 209:
#line 700 "faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 210:
#line 703 "faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 211:
#line 706 "faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 212:
#line 710 "faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 213:
#line 713 "faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 214:
#line 716 "faustparser.y"
    { (yyval.exp) = boxSoundfile((yyvsp[(3) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 215:
#line 722 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 216:
#line 723 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp), cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 217:
#line 724 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp), cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 218:
#line 726 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil))), gGlobal->nil)); ;}
    break;

  case 219:
#line 727 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp), cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil))), gGlobal->nil)); ;}
    break;

  case 220:
#line 728 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp), cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil))), gGlobal->nil)); ;}
    break;

  case 221:
#line 731 "faustparser.y"
    { (yyval.exp) = tree(yytext); ;}
    break;

  case 222:
#line 734 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 223:
#line 735 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 224:
#line 738 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 225:
#line 739 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 226:
#line 743 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 227:
#line 746 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 228:
#line 747 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 229:
#line 750 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 230:
#line 751 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 231:
#line 752 "faustparser.y"
    { (yyval.exp) = tree(2); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3342 "faustparser.cpp"
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


#line 755 "faustparser.y"


