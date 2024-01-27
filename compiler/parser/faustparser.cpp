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

/* Substitute the variable and function names.  */
#define yyparse FAUSTparse
#define yylex   FAUSTlex
#define yyerror FAUSTerror
#define yylval  FAUSTlval
#define yychar  FAUSTchar
#define yydebug FAUSTdebug
#define yynerrs FAUSTnerrs


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
     ROUND = 325,
     RDTBL = 326,
     RWTBL = 327,
     SELECT2 = 328,
     SELECT3 = 329,
     INT = 330,
     FLOAT = 331,
     MODULATE = 332,
     LAMBDA = 333,
     CASH = 334,
     HASH = 335,
     WIRE = 336,
     CUT = 337,
     ENDDEF = 338,
     VIRG = 339,
     LPAR = 340,
     RPAR = 341,
     LBRAQ = 342,
     RBRAQ = 343,
     LCROC = 344,
     RCROC = 345,
     WHERE = 346,
     DEF = 347,
     LAPPLY = 348,
     IMPORT = 349,
     COMPONENT = 350,
     LIBRARY = 351,
     ENVIRONMENT = 352,
     WAVEFORM = 353,
     ROUTE = 354,
     ENABLE = 355,
     CONTROL = 356,
     IPAR = 357,
     ISEQ = 358,
     ISUM = 359,
     IPROD = 360,
     INPUTS = 361,
     OUTPUTS = 362,
     STRING = 363,
     FSTRING = 364,
     IDENT = 365,
     EXTRA = 366,
     DECLARE = 367,
     CASE = 368,
     ARROW = 369,
     ASSERTBOUNDS = 370,
     LOWEST = 371,
     HIGHEST = 372,
     FLOATMODE = 373,
     DOUBLEMODE = 374,
     QUADMODE = 375,
     FIXEDPOINTMODE = 376,
     BDOC = 377,
     EDOC = 378,
     BEQN = 379,
     EEQN = 380,
     BDGM = 381,
     EDGM = 382,
     BLST = 383,
     ELST = 384,
     BMETADATA = 385,
     EMETADATA = 386,
     DOCCHAR = 387,
     NOTICE = 388,
     LISTING = 389,
     LSTTRUE = 390,
     LSTFALSE = 391,
     LSTDEPENDENCIES = 392,
     LSTMDOCTAGS = 393,
     LSTDISTRIBUTED = 394,
     LSTEQ = 395,
     LSTQ = 396
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
#define ROUND 325
#define RDTBL 326
#define RWTBL 327
#define SELECT2 328
#define SELECT3 329
#define INT 330
#define FLOAT 331
#define MODULATE 332
#define LAMBDA 333
#define CASH 334
#define HASH 335
#define WIRE 336
#define CUT 337
#define ENDDEF 338
#define VIRG 339
#define LPAR 340
#define RPAR 341
#define LBRAQ 342
#define RBRAQ 343
#define LCROC 344
#define RCROC 345
#define WHERE 346
#define DEF 347
#define LAPPLY 348
#define IMPORT 349
#define COMPONENT 350
#define LIBRARY 351
#define ENVIRONMENT 352
#define WAVEFORM 353
#define ROUTE 354
#define ENABLE 355
#define CONTROL 356
#define IPAR 357
#define ISEQ 358
#define ISUM 359
#define IPROD 360
#define INPUTS 361
#define OUTPUTS 362
#define STRING 363
#define FSTRING 364
#define IDENT 365
#define EXTRA 366
#define DECLARE 367
#define CASE 368
#define ARROW 369
#define ASSERTBOUNDS 370
#define LOWEST 371
#define HIGHEST 372
#define FLOATMODE 373
#define DOUBLEMODE 374
#define QUADMODE 375
#define FIXEDPOINTMODE 376
#define BDOC 377
#define EDOC 378
#define BEQN 379
#define EEQN 380
#define BDGM 381
#define EDGM 382
#define BLST 383
#define ELST 384
#define BMETADATA 385
#define EMETADATA 386
#define DOCCHAR 387
#define NOTICE 388
#define LISTING 389
#define LSTTRUE 390
#define LSTFALSE 391
#define LSTDEPENDENCIES 392
#define LSTMDOCTAGS 393
#define LSTDISTRIBUTED 394
#define LSTEQ 395
#define LSTQ 396




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
#define YYMAXDEPTH    100000
    
using namespace std;

extern char*        FAUSTtext;
extern const char*  FAUSTfilename;
extern int          FAUSTlineno;
extern int          FAUSTerr;

int FAUSTlex();

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
    CTree*     exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}
/* Line 193 of yacc.c.  */
#line 485 "faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 498 "faustparser.cpp"

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
#define YYLAST   778

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  243
/* YYNRULES -- Number of states.  */
#define YYNSTATES  517

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   396

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
     135,   136,   137,   138,   139,   140,   141
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
     177,   181,   183,   187,   193,   199,   207,   211,   215,   219,
     223,   227,   229,   233,   237,   241,   245,   249,   253,   257,
     260,   264,   268,   272,   276,   280,   284,   288,   292,   296,
     300,   304,   308,   313,   318,   320,   322,   324,   327,   330,
     333,   336,   338,   340,   342,   344,   346,   348,   350,   352,
     354,   356,   358,   360,   362,   364,   366,   368,   370,   372,
     374,   376,   378,   380,   382,   384,   386,   388,   390,   392,
     394,   396,   398,   400,   402,   404,   406,   408,   410,   412,
     414,   416,   418,   420,   422,   424,   426,   428,   430,   432,
     434,   436,   438,   440,   442,   444,   446,   448,   451,   454,
     457,   461,   470,   476,   481,   483,   485,   487,   492,   497,
     502,   507,   514,   523,   525,   527,   529,   531,   533,   535,
     537,   539,   541,   543,   545,   547,   549,   551,   553,   555,
     557,   559,   561,   563,   565,   567,   571,   575,   579,   583,
     587,   589,   591,   593,   595,   597,   606,   615,   624,   633,
     638,   643,   652,   660,   668,   673,   678,   691,   704,   717,
     724,   731,   738,   747,   756,   763,   769,   777,   787,   799,
     804,   811,   820,   831,   833,   835,   839,   841,   844,   851,
     853,   855,   857,   859
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     143,     0,    -1,   144,    -1,    -1,   144,   146,   151,    -1,
      -1,   145,   146,   163,    -1,    -1,   146,   147,    -1,   118,
      -1,   119,    -1,   120,    -1,   121,    -1,    -1,   148,   164,
      -1,   150,    -1,   149,     8,   150,    -1,    75,    -1,    76,
      -1,    18,    75,    -1,    18,    76,    -1,    17,    75,    -1,
      17,    76,    -1,    94,    85,   180,    86,    83,    -1,   112,
     176,   179,    83,    -1,   112,   176,   176,   179,    83,    -1,
     163,    -1,   122,   152,   123,    -1,    -1,   152,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     162,    -1,    -1,   154,   132,    -1,   124,   170,   125,    -1,
     126,   170,   127,    -1,   133,    -1,   128,   159,   129,    -1,
      -1,   159,   160,    -1,   137,   140,   141,   161,   141,    -1,
     138,   140,   141,   161,   141,    -1,   139,   140,   141,   161,
     141,    -1,   135,    -1,   136,    -1,   130,   176,   131,    -1,
     165,    85,   177,    86,    92,   170,    83,    -1,   165,    92,
     170,    83,    -1,     1,    83,    -1,   166,    92,   170,    83,
      -1,     1,    83,    -1,   173,    -1,    28,   173,    -1,   173,
      -1,   167,     8,   173,    -1,   180,    -1,   180,     7,   178,
      -1,   168,    -1,   169,     8,   168,    -1,   170,     3,    87,
     145,    88,    -1,   170,     4,    87,   148,    88,    -1,   170,
       4,    87,   148,    91,   145,    88,    -1,   170,     8,   170,
      -1,   170,     7,   170,    -1,   170,     6,   170,    -1,   170,
       5,   170,    -1,   170,     9,   170,    -1,   171,    -1,   171,
      18,   171,    -1,   171,    17,   171,    -1,   171,    25,   171,
      -1,   171,    24,   171,    -1,   171,    23,   171,    -1,   171,
      26,   171,    -1,   171,    27,   171,    -1,   171,    28,    -1,
     171,    29,   173,    -1,   171,    22,   171,    -1,   171,    16,
     171,    -1,   171,    21,   171,    -1,   171,    20,   171,    -1,
     171,    19,   171,    -1,   171,    15,   171,    -1,   171,    14,
     171,    -1,   171,    12,   171,    -1,   171,    11,   171,    -1,
     171,    13,   171,    -1,   171,    10,   171,    -1,   171,    85,
     177,    86,    -1,   171,    89,   145,    90,    -1,   172,    -1,
      75,    -1,    76,    -1,    18,    75,    -1,    18,    76,    -1,
      17,    75,    -1,    17,    76,    -1,    81,    -1,    82,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    18,    -1,
      17,    -1,    25,    -1,    24,    -1,    23,    -1,    27,    -1,
      22,    -1,    16,    -1,    21,    -1,    20,    -1,    19,    -1,
      15,    -1,    14,    -1,    12,    -1,    11,    -1,    13,    -1,
      10,    -1,    49,    -1,   100,    -1,   101,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    58,    -1,    59,    -1,    26,    -1,
      60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
     115,    -1,   116,    -1,   117,    -1,   173,    -1,    17,   173,
      -1,    79,   174,    -1,    80,   175,    -1,    85,   170,    86,
      -1,    78,    85,   167,    86,    29,    85,   170,    86,    -1,
      89,   169,    93,   170,    90,    -1,   113,    87,   205,    88,
      -1,   188,    -1,   189,    -1,   190,    -1,    95,    85,   180,
      86,    -1,    96,    85,   180,    86,    -1,    97,    87,   144,
      88,    -1,    98,    87,   149,    88,    -1,    99,    85,   178,
       8,   178,    86,    -1,    99,    85,   178,     8,   178,     8,
     170,    86,    -1,   191,    -1,   192,    -1,   193,    -1,   194,
      -1,   195,    -1,   196,    -1,   197,    -1,   198,    -1,   199,
      -1,   200,    -1,   201,    -1,   182,    -1,   183,    -1,   184,
      -1,   185,    -1,   186,    -1,   187,    -1,   110,    -1,   110,
      -1,   110,    -1,   110,    -1,   178,    -1,   177,     8,   178,
      -1,   178,     7,   178,    -1,   178,     6,   178,    -1,   178,
       5,   178,    -1,   178,     9,   178,    -1,   171,    -1,   108,
      -1,   108,    -1,   108,    -1,   109,    -1,   102,    85,   173,
       8,   178,     8,   170,    86,    -1,   103,    85,   173,     8,
     178,     8,   170,    86,    -1,   104,    85,   173,     8,   178,
       8,   170,    86,    -1,   105,    85,   173,     8,   178,     8,
     170,    86,    -1,   106,    85,   170,    86,    -1,   107,    85,
     170,    86,    -1,    35,    85,   202,     8,   181,     8,   179,
      86,    -1,    36,    85,   207,   176,     8,   181,    86,    -1,
      37,    85,   207,   176,     8,   181,    86,    -1,    38,    85,
     180,    86,    -1,    39,    85,   180,    86,    -1,    40,    85,
     180,     8,   178,     8,   178,     8,   178,     8,   178,    86,
      -1,    41,    85,   180,     8,   178,     8,   178,     8,   178,
       8,   178,    86,    -1,    42,    85,   180,     8,   178,     8,
     178,     8,   178,     8,   178,    86,    -1,    43,    85,   180,
       8,   170,    86,    -1,    44,    85,   180,     8,   170,    86,
      -1,    45,    85,   180,     8,   170,    86,    -1,    47,    85,
     180,     8,   178,     8,   178,    86,    -1,    46,    85,   180,
       8,   178,     8,   178,    86,    -1,    48,    85,   180,     8,
     178,    86,    -1,   207,   203,    85,   204,    86,    -1,   207,
     203,    16,   203,    85,   204,    86,    -1,   207,   203,    16,
     203,    16,   203,    85,   204,    86,    -1,   207,   203,    16,
     203,    16,   203,    16,   203,    85,   204,    86,    -1,   207,
     203,    85,    86,    -1,   207,   203,    16,   203,    85,    86,
      -1,   207,   203,    16,   203,    16,   203,    85,    86,    -1,
     207,   203,    16,   203,    16,   203,    16,   203,    85,    86,
      -1,   110,    -1,   208,    -1,   204,     8,   208,    -1,   206,
      -1,   205,   206,    -1,    85,   177,    86,   114,   170,    83,
      -1,    32,    -1,    33,    -1,    32,    -1,    33,    -1,    34,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   356,   356,   359,   360,   363,   364,   367,   368,   371,
     372,   373,   374,   377,   378,   385,   386,   389,   390,   391,
     392,   393,   394,   397,   398,   399,   400,   401,   404,   405,
     408,   409,   410,   411,   412,   413,   416,   417,   420,   423,
     426,   429,   432,   433,   436,   437,   438,   441,   442,   445,
     448,   449,   450,   453,   454,   457,   460,   463,   464,   467,
     468,   471,   472,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   496,   497,   498,   500,   501,   503,   504,   505,   506,
     507,   508,   510,   511,   513,   516,   517,   519,   520,   522,
     523,   525,   526,   528,   529,   531,   532,   534,   535,   536,
     537,   538,   539,   541,   542,   543,   545,   546,   548,   549,
     550,   551,   552,   553,   555,   556,   557,   559,   560,   561,
     562,   563,   564,   565,   567,   568,   569,   570,   571,   572,
     574,   575,   576,   578,   579,   581,   582,   583,   584,   586,
     587,   589,   590,   592,   593,   594,   596,   597,   598,   599,
     601,   602,   608,   611,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,   634,   635,   636,   637,   639,   640,
     644,   647,   650,   653,   656,   657,   660,   661,   662,   663,
     664,   667,   670,   673,   674,   679,   683,   687,   691,   695,
     698,   703,   707,   711,   716,   719,   722,   725,   728,   731,
     734,   737,   741,   744,   747,   754,   755,   756,   757,   759,
     760,   761,   762,   765,   768,   769,   772,   773,   776,   780,
     781,   784,   785,   786
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
  "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "ROUND",
  "RDTBL", "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "MODULATE",
  "LAMBDA", "CASH", "HASH", "WIRE", "CUT", "ENDDEF", "VIRG", "LPAR",
  "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC", "WHERE", "DEF", "LAPPLY",
  "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "ROUTE",
  "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS",
  "OUTPUTS", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE",
  "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST", "FLOATMODE", "DOUBLEMODE",
  "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM",
  "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE",
  "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "variantlist", "variant", "reclist", "vallist", "number",
  "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc",
  "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "modentry",
  "modlist", "expression", "infixexp", "primitive", "ident", "tap",
  "tapdef", "name", "arglist", "argument", "string", "uqstring", "fstring",
  "fpar", "fseq", "fsum", "fprod", "finputs", "foutputs", "ffunction",
  "fconst", "fvariable", "button", "checkbox", "vslider", "hslider",
  "nentry", "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph",
  "soundfile", "signature", "fun", "typelist", "rulelist", "rule", "type",
  "argtype", 0
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
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   142,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   147,   148,   148,   149,   149,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   151,   152,   152,
     153,   153,   153,   153,   153,   153,   154,   154,   155,   156,
     157,   158,   159,   159,   160,   160,   160,   161,   161,   162,
     163,   163,   163,   164,   164,   165,   166,   167,   167,   168,
     168,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     173,   174,   175,   176,   177,   177,   178,   178,   178,   178,
     178,   179,   180,   181,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   202,   202,   202,   202,
     202,   202,   202,   203,   204,   204,   205,   205,   206,   207,
     207,   208,   208,   208
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     3,     0,     2,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     2,
       2,     2,     2,     5,     4,     5,     1,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     3,
       1,     3,     0,     2,     5,     5,     5,     1,     1,     3,
       7,     4,     2,     4,     2,     1,     2,     1,     3,     1,
       3,     1,     3,     5,     5,     7,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     1,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       3,     8,     5,     4,     1,     1,     1,     4,     4,     4,
       4,     6,     8,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     8,     8,     8,     8,     4,
       4,     8,     7,     7,     4,     4,    12,    12,    12,     6,
       6,     6,     8,     8,     6,     5,     7,     9,    11,     4,
       6,     8,    10,     1,     1,     3,     1,     2,     6,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   190,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   193,     0,    36,     0,     0,   202,     0,   201,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   123,   121,   120,   122,   119,   118,
     114,   108,   107,   117,   116,   115,   113,   111,   110,   109,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
     125,   126,     0,     0,     0,     0,     0,     0,     0,   153,
     154,   155,   200,    94,   156,     0,   194,   184,   185,   186,
     187,   188,   189,   164,   165,   166,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     0,    71,     0,
       0,    24,     0,     0,     0,     0,    37,    99,   100,   157,
      97,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   191,   158,   192,
     159,     0,    61,     0,    59,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    23,    25,    38,    39,    41,     0,     0,
       0,    43,    49,   239,   240,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,   160,     0,     0,     0,     0,     0,     7,     0,
       0,    17,    18,     0,    15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,    91,    89,    88,    90,    87,
      86,    82,    73,    72,    85,    84,    83,    81,    76,    75,
      74,    77,    78,    80,     0,     7,   195,     0,   198,   197,
     196,   199,     5,    13,    69,    68,    67,    66,    70,     0,
       0,     0,     0,   233,     0,     0,     0,   214,   215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,    60,   167,   168,   169,    21,    22,    19,    20,
       0,   170,     0,     0,     0,     0,     0,   209,   210,     0,
     163,   237,    92,    93,     0,     0,     7,     0,     0,     0,
       0,   203,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,     0,   162,
      16,     0,     0,     0,     0,     0,     0,     6,    50,    63,
       0,     0,    64,     5,    14,     0,    47,    48,     0,     0,
       0,     0,     0,   241,   242,   243,   229,     0,   234,     0,
       0,     0,     0,     0,   219,   220,   221,     0,     0,   224,
       0,     0,   171,     0,     0,     0,     0,     0,    54,    56,
       7,     0,    44,    45,    46,     0,     0,     0,     0,   225,
     212,   213,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,     0,   211,     0,   230,     0,
     235,     0,     0,     0,   223,   222,   161,   172,   205,   206,
     207,   208,   238,    53,     0,     0,   226,     0,     0,     0,
       0,   231,     0,     0,     0,     0,     0,   227,     0,     0,
       0,   232,     0,   216,   217,   218,   228
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   315,   374,    14,   377,   283,   284,    15,
      23,    37,    38,    39,    40,    41,    42,   164,   251,   418,
      43,    16,   414,    17,   415,   270,   192,   193,   157,   132,
     133,   134,   188,   190,    22,   135,   136,    30,   194,   383,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     255,   334,   427,   293,   294,   256,   428
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -380
static const yytype_int16 yypact[] =
{
    -380,    10,    35,  -380,     2,   -34,    40,  -380,    29,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,   222,  -380,  -380,
      36,  -380,   288,   271,   438,   438,  -380,    33,  -380,    53,
      73,  -380,   438,   438,  -380,    29,  -380,  -380,    70,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,    32,   -50,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,   147,   163,   206,   315,
     332,   342,   347,   348,   349,   359,   360,   387,   430,   436,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,   437,   253,
     272,  -380,  -380,   438,    36,   439,   440,   266,   305,   441,
    -380,  -380,   461,   462,   464,   465,   467,   492,   379,  -380,
    -380,  -380,   568,  -380,  -380,    19,   325,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,   363,   568,    84,
     319,  -380,    39,     9,    20,   494,  -380,  -380,  -380,  -380,
    -380,  -380,    60,    60,    60,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,   516,  -380,  -380,  -380,
    -380,    55,  -380,    11,   158,    36,    36,  -380,    99,   438,
     516,   516,   516,   516,   438,   438,   542,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,  -380,   516,   438,  -380,   438,
     536,   438,   438,   438,   438,   548,   554,   438,   438,   438,
     438,   438,  -380,  -380,  -380,  -380,  -380,  -380,   500,   502,
     509,  -380,  -380,  -380,  -380,   643,   544,    29,    29,   566,
     569,   648,   655,   656,   657,   658,   660,   661,   662,   669,
      57,  -380,  -380,    36,   438,   438,   599,   601,   591,   101,
     233,  -380,  -380,    12,  -380,   260,   673,   680,   681,   682,
     201,   247,   438,   292,  -380,   582,   582,   582,   582,   582,
     582,   593,   593,   593,   323,   323,   323,   323,   323,   323,
     323,   346,   595,  -380,    59,   663,   325,   438,   325,   325,
     126,  -380,  -380,  -380,   523,   523,   398,   307,  -380,   611,
     613,   614,   228,  -380,     6,   748,   749,  -380,  -380,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   516,   729,
    -380,    48,   325,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
      99,  -380,   438,   438,   438,   438,   438,  -380,  -380,    76,
    -380,  -380,  -380,  -380,     8,   553,   671,    22,   243,   243,
     243,  -380,  -380,   752,   544,   295,   228,   228,   639,   653,
     667,   255,   268,   276,   687,   692,    64,  -380,   676,  -380,
    -380,    25,   697,   702,   707,   712,   649,  -380,  -380,  -380,
     679,   516,  -380,  -380,  -380,   672,  -380,  -380,   624,   625,
     626,    53,    21,  -380,  -380,  -380,  -380,    82,  -380,   683,
     684,   438,   438,   438,  -380,  -380,  -380,   438,   438,  -380,
     438,   438,  -380,   438,   438,   438,   438,   438,  -380,  -380,
     685,   438,  -380,  -380,  -380,   686,   544,   597,   377,  -380,
    -380,  -380,   717,   722,   727,    69,    74,   290,   297,   317,
     339,   352,   381,   560,  -380,   567,  -380,    78,  -380,    95,
    -380,   438,   438,   438,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,   544,   600,  -380,   732,   737,   742,
     689,  -380,   249,   438,   438,   438,   605,  -380,    80,    92,
     125,  -380,   278,  -380,  -380,  -380,  -380
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -380,  -380,   571,  -318,     0,  -380,  -380,  -380,   411,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,    34,
    -380,   401,  -380,  -380,  -380,  -380,   503,  -380,    -4,   -25,
    -380,    17,  -380,  -380,   -11,  -155,  -193,   -28,    46,    37,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -379,  -355,  -380,   484,   256,   320
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     158,   160,     4,     5,   376,   422,   285,   158,   158,     5,
       3,    29,   235,   236,   237,   238,   239,   240,   241,   273,
     360,    18,   384,   410,   165,   170,   171,   229,   162,   163,
     231,   232,   233,   441,   234,    -2,   316,   456,   318,   319,
     320,   321,   235,   236,   237,   238,   239,   240,   241,    19,
     411,   235,   236,   237,   238,   239,   240,   241,   235,   236,
     237,   238,   239,   240,   241,   348,    27,   229,   169,   231,
     232,   233,   314,   234,   231,   232,   233,   477,   234,   231,
     232,   233,   352,   234,   229,   231,   232,   233,   158,   234,
     458,   385,   253,   254,   494,   450,     6,   231,   232,   233,
     361,   234,   479,   458,   274,   230,   457,   167,   168,   191,
     412,   442,     7,   413,     8,   500,   279,   280,     7,   159,
       9,    10,    11,    12,    13,    20,     9,    10,    11,    12,
     231,   232,   233,   233,   234,   234,   246,   369,   399,    21,
     502,   272,     7,   349,    26,   372,   388,   389,   390,   247,
     439,   512,   394,   395,   396,   484,   161,   248,   249,   250,
     485,    28,   406,   495,   245,   275,   513,   243,   459,   401,
     402,   403,   404,   405,   281,   282,   356,   357,   514,   158,
     158,   496,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     290,   291,   166,   271,   235,   236,   237,   238,   239,   240,
     241,   515,   158,   158,   158,   158,   158,   286,   287,   288,
     289,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   172,   324,   325,   326,   327,   328,   462,   463,
     464,   276,   277,   313,   465,   466,   335,   336,   173,   158,
     235,   236,   237,   238,   239,   240,   241,   458,   235,   236,
     237,   238,   239,   240,   241,   231,   232,   233,   362,   234,
     351,   235,   236,   237,   238,   239,   240,   241,     4,   235,
     236,   237,   238,   239,   240,   241,   458,   367,   497,   498,
     499,   174,   158,   235,   236,   237,   238,   239,   240,   241,
     235,   236,   237,   238,   239,   240,   241,    24,   358,   359,
     508,   509,   510,   375,    25,   240,   241,   158,   158,   158,
     235,   236,   237,   238,   239,   240,   241,   423,   424,   425,
     231,   232,   233,   368,   234,   507,   381,   382,   391,   392,
     393,   434,   235,   236,   237,   238,   239,   240,   241,   223,
     224,   225,   226,   197,   435,   235,   236,   237,   238,   239,
     240,   241,   436,   187,   516,   397,   235,   236,   237,   238,
     239,   240,   241,   224,   225,   226,   486,   292,   416,   417,
     370,   426,   189,   487,   235,   236,   237,   238,   239,   240,
     241,    18,   198,   455,    31,    32,    28,    33,    21,    34,
     175,    35,   244,   488,    36,   239,   240,   241,   227,   423,
     424,   425,   228,   419,   420,   158,   158,   176,   158,   158,
     158,   158,   158,   429,   430,   489,   158,   177,   449,   257,
     258,   227,   178,   179,   180,   228,   467,   468,   490,   469,
     470,   471,   472,   473,   181,   182,   242,   475,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   206,   491,    62,    63,
      64,    65,   183,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   184,   108,   109,   110,   111,
     112,   185,   186,   113,   195,   196,   199,   114,   237,   238,
     239,   240,   241,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   200,   201,     7,   202,
     203,   128,   204,   129,   130,   131,   235,   236,   237,   238,
     239,   240,   241,   235,   236,   237,   238,   239,   240,   241,
     235,   236,   237,   238,   239,   240,   241,   205,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   225,   226,   252,     7,   292,   317,   423,
     424,   425,   423,   424,   425,   322,   408,   423,   424,   425,
     329,   323,   330,   492,   231,   232,   233,   431,   234,   331,
     493,   332,   337,   227,   333,   338,   339,   228,   231,   232,
     233,   432,   234,   340,   341,   342,   343,   227,   344,   345,
     346,   228,   231,   232,   233,   433,   234,   347,   227,   355,
     227,   363,   228,   478,   228,   353,   501,   354,   364,   365,
     366,   511,   231,   232,   233,   437,   234,   231,   232,   233,
     438,   234,   231,   232,   233,   443,   234,   231,   232,   233,
     444,   234,   231,   232,   233,   445,   234,   231,   232,   233,
     446,   234,   231,   232,   233,   481,   234,   231,   232,   233,
     482,   234,   231,   232,   233,   483,   234,   231,   232,   233,
     503,   234,   231,   232,   233,   504,   234,   231,   232,   233,
     505,   234,   378,   373,   379,   380,   386,   387,   398,   409,
     421,   440,   448,   447,   451,   452,   453,   454,   278,   460,
     461,   400,   476,   474,   506,   407,   350,   371,   480
};

static const yytype_uint16 yycheck[] =
{
      25,    29,     2,     1,   322,   384,   199,    32,    33,     1,
       0,    22,     3,     4,     5,     6,     7,     8,     9,     8,
       8,     4,    16,     1,    35,    75,    76,     8,    32,    33,
       5,     6,     7,     8,     9,     0,   229,    16,   231,   232,
     233,   234,     3,     4,     5,     6,     7,     8,     9,    83,
      28,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,     8,    20,     8,    51,     5,
       6,     7,   227,     9,     5,     6,     7,   456,     9,     5,
       6,     7,   275,     9,     8,     5,     6,     7,   113,     9,
       8,    85,    32,    33,    16,   413,    94,     5,     6,     7,
      88,     9,   457,     8,    93,    86,    85,    75,    76,   113,
      88,    86,   110,    91,   112,   494,    17,    18,   110,    86,
     118,   119,   120,   121,   122,    85,   118,   119,   120,   121,
       5,     6,     7,     7,     9,     9,   127,   292,    90,   110,
     495,    86,   110,    86,   108,    86,   339,   340,   341,   129,
      86,   506,   345,   346,   347,    86,    83,   137,   138,   139,
      86,   108,    86,    85,   125,     7,    86,    83,    86,   362,
     363,   364,   365,   366,    75,    76,    75,    76,    86,   204,
     205,    86,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     204,   205,   132,   186,     3,     4,     5,     6,     7,     8,
       9,    86,   237,   238,   239,   240,   241,   200,   201,   202,
     203,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,    85,   237,   238,   239,   240,   241,   431,   432,
     433,   195,   196,   226,   437,   438,   257,   258,    85,   274,
       3,     4,     5,     6,     7,     8,     9,     8,     3,     4,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
     274,     3,     4,     5,     6,     7,     8,     9,   278,     3,
       4,     5,     6,     7,     8,     9,     8,    86,   481,   482,
     483,    85,   317,     3,     4,     5,     6,     7,     8,     9,
       3,     4,     5,     6,     7,     8,     9,    85,    75,    76,
     503,   504,   505,   317,    92,     8,     9,   342,   343,   344,
       3,     4,     5,     6,     7,     8,     9,    32,    33,    34,
       5,     6,     7,    86,     9,    86,   108,   109,   342,   343,
     344,    86,     3,     4,     5,     6,     7,     8,     9,    26,
      27,    28,    29,    87,    86,     3,     4,     5,     6,     7,
       8,     9,    86,   110,    86,   348,     3,     4,     5,     6,
       7,     8,     9,    27,    28,    29,    86,    85,   135,   136,
      88,    86,   110,    86,     3,     4,     5,     6,     7,     8,
       9,   374,    87,   421,   123,   124,   108,   126,   110,   128,
      85,   130,    83,    86,   133,     7,     8,     9,    85,    32,
      33,    34,    89,   379,   380,   440,   441,    85,   443,   444,
     445,   446,   447,   386,   387,    86,   451,    85,   411,   173,
     174,    85,    85,    85,    85,    89,   440,   441,    86,   443,
     444,   445,   446,   447,    85,    85,    83,   451,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    87,    86,    30,    31,
      32,    33,    85,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    85,    78,    79,    80,    81,
      82,    85,    85,    85,    85,    85,    85,    89,     5,     6,
       7,     8,     9,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    85,    85,   110,    85,
      85,   113,    85,   115,   116,   117,     3,     4,     5,     6,
       7,     8,     9,     3,     4,     5,     6,     7,     8,     9,
       3,     4,     5,     6,     7,     8,     9,    85,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    28,    29,   131,   110,    85,    92,    32,
      33,    34,    32,    33,    34,    87,    83,    32,    33,    34,
     140,    87,   140,    83,     5,     6,     7,     8,     9,   140,
      83,     8,    86,    85,   110,    86,     8,    89,     5,     6,
       7,     8,     9,     8,     8,     8,     8,    85,     8,     8,
       8,    89,     5,     6,     7,     8,     9,     8,    85,    88,
      85,     8,    89,    86,    89,    86,    86,    86,     8,     8,
       8,    86,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9,   141,    90,   141,   141,     8,     8,    29,    88,
       8,    85,    83,   114,    92,   141,   141,   141,   197,    86,
      86,   360,    86,    88,    85,   374,   273,   293,   458
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   143,   144,     0,   146,     1,    94,   110,   112,   118,
     119,   120,   121,   122,   147,   151,   163,   165,   173,    83,
      85,   110,   176,   152,    85,    92,   108,   180,   108,   176,
     179,   123,   124,   126,   128,   130,   133,   153,   154,   155,
     156,   157,   158,   162,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    78,    79,
      80,    81,    82,    85,    89,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   113,   115,
     116,   117,   171,   172,   173,   177,   178,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   170,   171,    86,
     179,    83,   170,   170,   159,   176,   132,    75,    76,   173,
      75,    76,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,   110,   174,   110,
     175,   170,   168,   169,   180,    85,    85,    87,    87,    85,
      85,    85,    85,    85,    85,    85,    87,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    85,    89,     8,
      86,     5,     6,     7,     9,     3,     4,     5,     6,     7,
       8,     9,    83,    83,    83,   125,   127,   129,   137,   138,
     139,   160,   131,    32,    33,   202,   207,   207,   207,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     167,   173,    86,     8,    93,     7,   180,   180,   144,    17,
      18,    75,    76,   149,   150,   178,   173,   173,   173,   173,
     170,   170,    85,   205,   206,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   173,   177,   145,   178,    92,   178,   178,
     178,   178,    87,    87,   170,   170,   170,   170,   170,   140,
     140,   140,     8,   110,   203,   176,   176,    86,    86,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,    86,
     168,   170,   178,    86,    86,    88,    75,    76,    75,    76,
       8,    88,     8,     8,     8,     8,     8,    86,    86,   177,
      88,   206,    86,    90,   146,   170,   145,   148,   141,   141,
     141,   108,   109,   181,    16,    85,     8,     8,   178,   178,
     178,   170,   170,   170,   178,   178,   178,   173,    29,    90,
     150,   178,   178,   178,   178,   178,    86,   163,    83,    88,
       1,    28,    88,    91,   164,   166,   135,   136,   161,   161,
     161,     8,   203,    32,    33,    34,    86,   204,   208,   181,
     181,     8,     8,     8,    86,    86,    86,     8,     8,    86,
      85,     8,    86,     8,     8,     8,     8,   114,    83,   173,
     145,    92,   141,   141,   141,   179,    16,    85,     8,    86,
      86,    86,   178,   178,   178,   178,   178,   170,   170,   170,
     170,   170,   170,   170,    88,   170,    86,   203,    86,   204,
     208,     8,     8,     8,    86,    86,    86,    86,    86,    86,
      86,    86,    83,    83,    16,    85,    86,   178,   178,   178,
     203,    86,   204,     8,     8,     8,    85,    86,   178,   178,
     178,    86,   204,    86,    86,    86,    86
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
#line 356 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 359 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 4:
#line 360 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp); ;}
    break;

  case 5:
#line 363 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 6:
#line 364 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp);;}
    break;

  case 7:
#line 367 "faustparser.y"
    { (yyval.numvariant) = 0; ;}
    break;

  case 8:
#line 368 "faustparser.y"
    { (yyval.numvariant) = (yyvsp[(1) - (2)].numvariant) | (yyvsp[(2) - (2)].numvariant);;}
    break;

  case 9:
#line 371 "faustparser.y"
    { (yyval.numvariant) = 1;;}
    break;

  case 10:
#line 372 "faustparser.y"
    { (yyval.numvariant) = 2;;}
    break;

  case 11:
#line 373 "faustparser.y"
    { (yyval.numvariant) = 4;;}
    break;

  case 12:
#line 374 "faustparser.y"
    { (yyval.numvariant) = 8;;}
    break;

  case 13:
#line 377 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 14:
#line 378 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 15:
#line 385 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 386 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); ;}
    break;

  case 17:
#line 389 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 18:
#line 390 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 19:
#line 391 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 20:
#line 392 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 21:
#line 393 "faustparser.y"
    { (yyval.exp) = boxInt(-str2int(FAUSTtext)); ;}
    break;

  case 22:
#line 394 "faustparser.y"
    { (yyval.exp) = boxReal(-atof(FAUSTtext)); ;}
    break;

  case 23:
#line 397 "faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 24:
#line 398 "faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 25:
#line 399 "faustparser.y"
    { declareDefinitionMetadata((yyvsp[(2) - (5)].exp),(yyvsp[(3) - (5)].exp),(yyvsp[(4) - (5)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 26:
#line 400 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 27:
#line 401 "faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 28:
#line 404 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 29:
#line 405 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 30:
#line 408 "faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 31:
#line 409 "faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 32:
#line 410 "faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 33:
#line 411 "faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 34:
#line 412 "faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 35:
#line 413 "faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 36:
#line 416 "faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 37:
#line 417 "faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(FAUSTtext)); ;}
    break;

  case 38:
#line 420 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 39:
#line 423 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 40:
#line 426 "faustparser.y"
    { ;}
    break;

  case 41:
#line 429 "faustparser.y"
    { ;}
    break;

  case 42:
#line 432 "faustparser.y"
    { ;}
    break;

  case 43:
#line 433 "faustparser.y"
    { ;}
    break;

  case 44:
#line 436 "faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 45:
#line 437 "faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; ;}
    break;

  case 46:
#line 438 "faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 47:
#line 441 "faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 48:
#line 442 "faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 49:
#line 445 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 50:
#line 448 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); setDefProp((yyvsp[(1) - (7)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 51:
#line 449 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp)));  setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 52:
#line 450 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 53:
#line 453 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 54:
#line 454 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 55:
#line 457 "faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); ;}
    break;

  case 56:
#line 460 "faustparser.y"
    { (yyval.exp)=(yyvsp[(2) - (2)].exp); ;}
    break;

  case 57:
#line 463 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 58:
#line 464 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 59:
#line 467 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 60:
#line 468 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 61:
#line 471 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 62:
#line 472 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 63:
#line 475 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 64:
#line 476 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp)), gGlobal->nil); ;}
    break;

  case 65:
#line 477 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (7)].exp),formatDefinitions((yyvsp[(4) - (7)].exp)),formatDefinitions((yyvsp[(6) - (7)].exp))); ;}
    break;

  case 66:
#line 478 "faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 67:
#line 479 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 68:
#line 480 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 69:
#line 481 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 70:
#line 482 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 71:
#line 483 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 72:
#line 486 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 73:
#line 487 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 74:
#line 488 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 75:
#line 489 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 76:
#line 490 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 77:
#line 491 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gGlobal->gPowPrim->box()); ;}
    break;

  case 78:
#line 492 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDelay)); ;}
    break;

  case 79:
#line 493 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 80:
#line 494 "faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 81:
#line 496 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 82:
#line 497 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 83:
#line 498 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 84:
#line 500 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 85:
#line 501 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigARightShift)); ;}
    break;

  case 86:
#line 503 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 87:
#line 504 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 88:
#line 505 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 89:
#line 506 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 90:
#line 507 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 91:
#line 508 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 92:
#line 510 "faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 93:
#line 511 "faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 94:
#line 513 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 95:
#line 516 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 96:
#line 517 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 97:
#line 519 "faustparser.y"
    { (yyval.exp) = boxInt (str2int(FAUSTtext)); ;}
    break;

  case 98:
#line 520 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 99:
#line 522 "faustparser.y"
    { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); ;}
    break;

  case 100:
#line 523 "faustparser.y"
    { (yyval.exp) = boxReal( -atof(FAUSTtext) ); ;}
    break;

  case 101:
#line 525 "faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 102:
#line 526 "faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 103:
#line 528 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 104:
#line 529 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 105:
#line 531 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 106:
#line 532 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 107:
#line 534 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 108:
#line 535 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 109:
#line 536 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 110:
#line 537 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 111:
#line 538 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 112:
#line 539 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDelay); ;}
    break;

  case 113:
#line 541 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 114:
#line 542 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 115:
#line 543 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 116:
#line 545 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 117:
#line 546 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigARightShift); ;}
    break;

  case 118:
#line 548 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 119:
#line 549 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 120:
#line 550 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 121:
#line 551 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 122:
#line 552 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 123:
#line 553 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 124:
#line 555 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 125:
#line 556 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEnable); ;}
    break;

  case 126:
#line 557 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigControl); ;}
    break;

  case 127:
#line 559 "faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); ;}
    break;

  case 128:
#line 560 "faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); ;}
    break;

  case 129:
#line 561 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); ;}
    break;

  case 130:
#line 562 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); ;}
    break;

  case 131:
#line 563 "faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); ;}
    break;

  case 132:
#line 564 "faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); ;}
    break;

  case 133:
#line 565 "faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); ;}
    break;

  case 134:
#line 567 "faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); ;}
    break;

  case 135:
#line 568 "faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); ;}
    break;

  case 136:
#line 569 "faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); ;}
    break;

  case 137:
#line 570 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 138:
#line 571 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 139:
#line 572 "faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); ;}
    break;

  case 140:
#line 574 "faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); ;}
    break;

  case 141:
#line 575 "faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); ;}
    break;

  case 142:
#line 576 "faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); ;}
    break;

  case 143:
#line 578 "faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); ;}
    break;

  case 144:
#line 579 "faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); ;}
    break;

  case 145:
#line 581 "faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); ;}
    break;

  case 146:
#line 582 "faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); ;}
    break;

  case 147:
#line 583 "faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); ;}
    break;

  case 148:
#line 584 "faustparser.y"
    { (yyval.exp) = gGlobal->gRoundPrim->box(); ;}
    break;

  case 149:
#line 586 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 150:
#line 587 "faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 151:
#line 589 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 152:
#line 590 "faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 153:
#line 592 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigAssertBounds);;}
    break;

  case 154:
#line 593 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigLowest);;}
    break;

  case 155:
#line 594 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigHighest);;}
    break;

  case 156:
#line 596 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);  setUseProp((yyvsp[(1) - (1)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 157:
#line 597 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 158:
#line 598 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp);  setUseProp((yyvsp[(2) - (2)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 159:
#line 599 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp);  setUseProp((yyvsp[(2) - (2)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 160:
#line 601 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 161:
#line 603 "faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 162:
#line 609 "faustparser.y"
    { (yyval.exp) = buildBoxModulation((yyvsp[(2) - (5)].exp),(yyvsp[(4) - (5)].exp)); ;}
    break;

  case 163:
#line 611 "faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 164:
#line 613 "faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 165:
#line 614 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 166:
#line 615 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 167:
#line 616 "faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 168:
#line 617 "faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 169:
#line 618 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 170:
#line 619 "faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); ;}
    break;

  case 171:
#line 620 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp), boxPar(boxInt(0),boxInt(0))); ;}
    break;

  case 172:
#line 621 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), (yyvsp[(7) - (8)].exp)); ;}
    break;

  case 173:
#line 622 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 174:
#line 623 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 175:
#line 624 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 176:
#line 625 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 177:
#line 626 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 178:
#line 627 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 179:
#line 628 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 180:
#line 629 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 181:
#line 630 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 182:
#line 631 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 183:
#line 632 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 184:
#line 634 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 185:
#line 635 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 186:
#line 636 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 187:
#line 637 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 188:
#line 639 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 189:
#line 640 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 190:
#line 644 "faustparser.y"
    { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 191:
#line 647 "faustparser.y"
    { (yyval.exp) = boxTap(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 192:
#line 650 "faustparser.y"
    { (yyval.exp) = boxTapDef(boxTap(FAUSTtext)); setDefProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 193:
#line 653 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 194:
#line 656 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 195:
#line 657 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 196:
#line 660 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 197:
#line 661 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 198:
#line 662 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 199:
#line 663 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 200:
#line 664 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 201:
#line 667 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 202:
#line 670 "faustparser.y"
    { (yyval.exp) = unquote(FAUSTtext); ;}
    break;

  case 203:
#line 673 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 204:
#line 674 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 205:
#line 680 "faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 206:
#line 684 "faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 207:
#line 688 "faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 208:
#line 692 "faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 209:
#line 695 "faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 210:
#line 698 "faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 211:
#line 704 "faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 212:
#line 708 "faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 213:
#line 712 "faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 214:
#line 716 "faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 215:
#line 719 "faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 216:
#line 723 "faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 217:
#line 726 "faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 218:
#line 729 "faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 219:
#line 732 "faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 220:
#line 735 "faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 221:
#line 738 "faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 222:
#line 742 "faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 223:
#line 745 "faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 224:
#line 748 "faustparser.y"
    { (yyval.exp) = boxSoundfile((yyvsp[(3) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 225:
#line 754 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp),cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil)))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 226:
#line 755 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil)))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 227:
#line 756 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp),cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil)))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 228:
#line 757 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (11)].exp),cons(cons((yyvsp[(2) - (11)].exp),cons((yyvsp[(4) - (11)].exp),cons((yyvsp[(6) - (11)].exp),cons((yyvsp[(8) - (11)].exp),gGlobal->nil)))), (yyvsp[(10) - (11)].exp))); ;}
    break;

  case 229:
#line 759 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 230:
#line 760 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp),cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 231:
#line 761 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp),cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 232:
#line 762 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (10)].exp),cons(cons((yyvsp[(2) - (10)].exp),cons((yyvsp[(4) - (10)].exp),cons((yyvsp[(6) - (10)].exp),cons((yyvsp[(8) - (10)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 233:
#line 765 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 234:
#line 768 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 235:
#line 769 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 236:
#line 772 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 237:
#line 773 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 238:
#line 777 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 239:
#line 780 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 240:
#line 781 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 241:
#line 784 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 242:
#line 785 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 243:
#line 786 "faustparser.y"
    { (yyval.exp) = tree(2); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3445 "faustparser.cpp"
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


#line 789 "faustparser.y"


