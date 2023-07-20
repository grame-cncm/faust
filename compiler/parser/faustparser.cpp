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
     LAMBDA = 332,
     WIRE = 333,
     CUT = 334,
     ENDDEF = 335,
     VIRG = 336,
     LPAR = 337,
     RPAR = 338,
     LBRAQ = 339,
     RBRAQ = 340,
     LCROC = 341,
     RCROC = 342,
     WHERE = 343,
     DEF = 344,
     IMPORT = 345,
     COMPONENT = 346,
     LIBRARY = 347,
     ENVIRONMENT = 348,
     WAVEFORM = 349,
     ROUTE = 350,
     ENABLE = 351,
     CONTROL = 352,
     IPAR = 353,
     ISEQ = 354,
     ISUM = 355,
     IPROD = 356,
     INPUTS = 357,
     OUTPUTS = 358,
     STRING = 359,
     FSTRING = 360,
     IDENT = 361,
     EXTRA = 362,
     DECLARE = 363,
     CASE = 364,
     ARROW = 365,
     ASSERTBOUNDS = 366,
     LOWEST = 367,
     HIGHEST = 368,
     FLOATMODE = 369,
     DOUBLEMODE = 370,
     QUADMODE = 371,
     FIXEDPOINTMODE = 372,
     BDOC = 373,
     EDOC = 374,
     BEQN = 375,
     EEQN = 376,
     BDGM = 377,
     EDGM = 378,
     BLST = 379,
     ELST = 380,
     BMETADATA = 381,
     EMETADATA = 382,
     DOCCHAR = 383,
     NOTICE = 384,
     LISTING = 385,
     LSTTRUE = 386,
     LSTFALSE = 387,
     LSTDEPENDENCIES = 388,
     LSTMDOCTAGS = 389,
     LSTDISTRIBUTED = 390,
     LSTEQ = 391,
     LSTQ = 392
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
#define LAMBDA 332
#define WIRE 333
#define CUT 334
#define ENDDEF 335
#define VIRG 336
#define LPAR 337
#define RPAR 338
#define LBRAQ 339
#define RBRAQ 340
#define LCROC 341
#define RCROC 342
#define WHERE 343
#define DEF 344
#define IMPORT 345
#define COMPONENT 346
#define LIBRARY 347
#define ENVIRONMENT 348
#define WAVEFORM 349
#define ROUTE 350
#define ENABLE 351
#define CONTROL 352
#define IPAR 353
#define ISEQ 354
#define ISUM 355
#define IPROD 356
#define INPUTS 357
#define OUTPUTS 358
#define STRING 359
#define FSTRING 360
#define IDENT 361
#define EXTRA 362
#define DECLARE 363
#define CASE 364
#define ARROW 365
#define ASSERTBOUNDS 366
#define LOWEST 367
#define HIGHEST 368
#define FLOATMODE 369
#define DOUBLEMODE 370
#define QUADMODE 371
#define FIXEDPOINTMODE 372
#define BDOC 373
#define EDOC 374
#define BEQN 375
#define EEQN 376
#define BDGM 377
#define EDGM 378
#define BLST 379
#define ELST 380
#define BMETADATA 381
#define EMETADATA 382
#define DOCCHAR 383
#define NOTICE 384
#define LISTING 385
#define LSTTRUE 386
#define LSTFALSE 387
#define LSTDEPENDENCIES 388
#define LSTMDOCTAGS 389
#define LSTDISTRIBUTED 390
#define LSTEQ 391
#define LSTQ 392




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
#line 477 "faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 490 "faustparser.cpp"

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
#define YYLAST   758

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNRULES -- Number of states.  */
#define YYNSTATES  500

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   392

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
     135,   136,   137
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
     430,   432,   434,   436,   439,   443,   452,   457,   459,   461,
     463,   468,   473,   478,   483,   490,   499,   501,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   523,   525,
     527,   529,   531,   533,   535,   537,   539,   543,   547,   551,
     555,   559,   561,   563,   565,   567,   569,   578,   587,   596,
     605,   610,   615,   624,   632,   640,   645,   650,   663,   676,
     689,   696,   703,   710,   719,   728,   735,   741,   749,   759,
     771,   776,   783,   792,   803,   805,   807,   811,   813,   816,
     823,   825,   827,   829,   831
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     139,     0,    -1,   140,    -1,    -1,   140,   142,   147,    -1,
      -1,   141,   142,   159,    -1,    -1,   142,   143,    -1,   114,
      -1,   115,    -1,   116,    -1,   117,    -1,    -1,   144,   160,
      -1,   146,    -1,   145,     8,   146,    -1,    75,    -1,    76,
      -1,    18,    75,    -1,    18,    76,    -1,    17,    75,    -1,
      17,    76,    -1,    90,    82,   172,    83,    80,    -1,   108,
     168,   171,    80,    -1,   108,   168,   168,   171,    80,    -1,
     159,    -1,   118,   148,   119,    -1,    -1,   148,   149,    -1,
     150,    -1,   151,    -1,   152,    -1,   153,    -1,   154,    -1,
     158,    -1,    -1,   150,   128,    -1,   120,   164,   121,    -1,
     122,   164,   123,    -1,   129,    -1,   124,   155,   125,    -1,
      -1,   155,   156,    -1,   133,   136,   137,   157,   137,    -1,
     134,   136,   137,   157,   137,    -1,   135,   136,   137,   157,
     137,    -1,   131,    -1,   132,    -1,   126,   168,   127,    -1,
     161,    82,   169,    83,    89,   164,    80,    -1,   161,    89,
     164,    80,    -1,     1,    80,    -1,   162,    89,   164,    80,
      -1,     1,    80,    -1,   167,    -1,    28,   167,    -1,   167,
      -1,   163,     8,   167,    -1,   164,     3,    84,   141,    85,
      -1,   164,     4,    84,   144,    85,    -1,   164,     4,    84,
     144,    88,   141,    85,    -1,   164,     8,   164,    -1,   164,
       7,   164,    -1,   164,     6,   164,    -1,   164,     5,   164,
      -1,   164,     9,   164,    -1,   165,    -1,   165,    18,   165,
      -1,   165,    17,   165,    -1,   165,    25,   165,    -1,   165,
      24,   165,    -1,   165,    23,   165,    -1,   165,    26,   165,
      -1,   165,    27,   165,    -1,   165,    28,    -1,   165,    29,
     167,    -1,   165,    22,   165,    -1,   165,    16,   165,    -1,
     165,    21,   165,    -1,   165,    20,   165,    -1,   165,    19,
     165,    -1,   165,    15,   165,    -1,   165,    14,   165,    -1,
     165,    12,   165,    -1,   165,    11,   165,    -1,   165,    13,
     165,    -1,   165,    10,   165,    -1,   165,    82,   169,    83,
      -1,   165,    86,   141,    87,    -1,   166,    -1,    75,    -1,
      76,    -1,    18,    75,    -1,    18,    76,    -1,    17,    75,
      -1,    17,    76,    -1,    78,    -1,    79,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    18,    -1,    17,    -1,
      25,    -1,    24,    -1,    23,    -1,    27,    -1,    22,    -1,
      16,    -1,    21,    -1,    20,    -1,    19,    -1,    15,    -1,
      14,    -1,    12,    -1,    11,    -1,    13,    -1,    10,    -1,
      49,    -1,    96,    -1,    97,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    26,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,    72,    -1,    73,    -1,    74,    -1,   111,    -1,
     112,    -1,   113,    -1,   167,    -1,    17,   167,    -1,    82,
     164,    83,    -1,    77,    82,   163,    83,    29,    82,   164,
      83,    -1,   109,    84,   197,    85,    -1,   180,    -1,   181,
      -1,   182,    -1,    91,    82,   172,    83,    -1,    92,    82,
     172,    83,    -1,    93,    84,   140,    85,    -1,    94,    84,
     145,    85,    -1,    95,    82,   170,     8,   170,    83,    -1,
      95,    82,   170,     8,   170,     8,   164,    83,    -1,   183,
      -1,   184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,
      -1,   189,    -1,   190,    -1,   191,    -1,   192,    -1,   193,
      -1,   174,    -1,   175,    -1,   176,    -1,   177,    -1,   178,
      -1,   179,    -1,   106,    -1,   106,    -1,   170,    -1,   169,
       8,   170,    -1,   170,     7,   170,    -1,   170,     6,   170,
      -1,   170,     5,   170,    -1,   170,     9,   170,    -1,   165,
      -1,   104,    -1,   104,    -1,   104,    -1,   105,    -1,    98,
      82,   167,     8,   170,     8,   164,    83,    -1,    99,    82,
     167,     8,   170,     8,   164,    83,    -1,   100,    82,   167,
       8,   170,     8,   164,    83,    -1,   101,    82,   167,     8,
     170,     8,   164,    83,    -1,   102,    82,   164,    83,    -1,
     103,    82,   164,    83,    -1,    35,    82,   194,     8,   173,
       8,   171,    83,    -1,    36,    82,   199,   168,     8,   173,
      83,    -1,    37,    82,   199,   168,     8,   173,    83,    -1,
      38,    82,   172,    83,    -1,    39,    82,   172,    83,    -1,
      40,    82,   172,     8,   170,     8,   170,     8,   170,     8,
     170,    83,    -1,    41,    82,   172,     8,   170,     8,   170,
       8,   170,     8,   170,    83,    -1,    42,    82,   172,     8,
     170,     8,   170,     8,   170,     8,   170,    83,    -1,    43,
      82,   172,     8,   164,    83,    -1,    44,    82,   172,     8,
     164,    83,    -1,    45,    82,   172,     8,   164,    83,    -1,
      47,    82,   172,     8,   170,     8,   170,    83,    -1,    46,
      82,   172,     8,   170,     8,   170,    83,    -1,    48,    82,
     172,     8,   170,    83,    -1,   199,   195,    82,   196,    83,
      -1,   199,   195,    16,   195,    82,   196,    83,    -1,   199,
     195,    16,   195,    16,   195,    82,   196,    83,    -1,   199,
     195,    16,   195,    16,   195,    16,   195,    82,   196,    83,
      -1,   199,   195,    82,    83,    -1,   199,   195,    16,   195,
      82,    83,    -1,   199,   195,    16,   195,    16,   195,    82,
      83,    -1,   199,   195,    16,   195,    16,   195,    16,   195,
      82,    83,    -1,   106,    -1,   200,    -1,   196,     8,   200,
      -1,   198,    -1,   197,   198,    -1,    82,   169,    83,   110,
     164,    80,    -1,    32,    -1,    33,    -1,    32,    -1,    33,
      -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   348,   348,   351,   352,   355,   356,   359,   360,   363,
     364,   365,   366,   369,   370,   377,   378,   381,   382,   383,
     384,   385,   386,   389,   390,   391,   392,   393,   396,   397,
     400,   401,   402,   403,   404,   405,   408,   409,   412,   415,
     418,   421,   424,   425,   428,   429,   430,   433,   434,   437,
     440,   441,   442,   445,   446,   449,   452,   455,   456,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   480,   481,   482,
     484,   485,   487,   488,   489,   490,   491,   492,   494,   495,
     497,   500,   501,   503,   504,   506,   507,   509,   510,   512,
     513,   515,   516,   518,   519,   520,   521,   522,   523,   525,
     526,   527,   529,   530,   532,   533,   534,   535,   536,   537,
     539,   540,   541,   543,   544,   545,   546,   547,   548,   549,
     551,   552,   553,   554,   555,   556,   558,   559,   560,   562,
     563,   565,   566,   567,   568,   570,   571,   573,   574,   576,
     577,   578,   580,   581,   583,   584,   587,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   610,   611,   612,
     613,   615,   616,   620,   623,   626,   627,   630,   631,   632,
     633,   634,   637,   640,   643,   644,   649,   653,   657,   661,
     665,   668,   673,   677,   681,   686,   689,   692,   695,   698,
     701,   704,   707,   711,   714,   717,   724,   725,   726,   727,
     729,   730,   731,   732,   735,   738,   739,   742,   743,   746,
     750,   751,   754,   755,   756
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
  "RDTBL", "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE",
  "CUT", "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC",
  "RCROC", "WHERE", "DEF", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT",
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
     385,   386,   387,   388,   389,   390,   391,   392
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   138,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   146,   146,
     146,   146,   146,   147,   147,   147,   147,   147,   148,   148,
     149,   149,   149,   149,   149,   149,   150,   150,   151,   152,
     153,   154,   155,   155,   156,   156,   156,   157,   157,   158,
     159,   159,   159,   160,   160,   161,   162,   163,   163,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   167,   168,   169,   169,   170,   170,   170,
     170,   170,   171,   172,   173,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   194,   194,   194,
     194,   194,   194,   194,   195,   196,   196,   197,   197,   198,
     199,   199,   200,   200,   200
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
       1,     1,     1,     2,     3,     8,     4,     1,     1,     1,
       4,     4,     4,     4,     6,     8,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     8,     8,     8,     8,
       4,     4,     8,     7,     7,     4,     4,    12,    12,    12,
       6,     6,     6,     8,     8,     6,     5,     7,     9,    11,
       4,     6,     8,    10,     1,     1,     3,     1,     2,     6,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   183,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   184,     0,    36,     0,     0,   193,     0,   192,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   119,   117,   116,   118,   115,   114,
     110,   104,   103,   113,   112,   111,   109,   107,   106,   105,
     133,   108,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,    91,    92,     0,    97,
      98,     0,     0,     0,     0,     0,     0,   121,   122,     0,
       0,     0,     0,     0,     0,     0,   149,   150,   151,   191,
      90,   152,     0,   185,   177,   178,   179,   180,   181,   182,
     157,   158,   159,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,     0,    67,     0,     0,    24,     0,
       0,     0,     0,    37,    95,    96,   153,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    23,    25,    38,    39,    41,     0,     0,
       0,    43,    49,   230,   231,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,   154,     0,     0,     7,     0,     0,    17,    18,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   227,    87,    85,    84,    86,    83,    82,    78,    69,
      68,    81,    80,    79,    77,    72,    71,    70,    73,    74,
      76,     0,     7,   186,     0,   189,   188,   187,   190,     5,
      13,    65,    64,    63,    62,    66,     0,     0,     0,     0,
     224,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,   161,   162,
      21,    22,    19,    20,     0,   163,     0,     0,     0,     0,
       0,   200,   201,     0,   156,   228,    88,    89,     0,     0,
       7,     0,     0,     0,     0,   194,   195,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,    16,     0,     0,     0,     0,     0,     0,
       6,    50,    59,     0,     0,    60,     5,    14,     0,    47,
      48,     0,     0,     0,     0,     0,   232,   233,   234,   220,
       0,   225,     0,     0,     0,     0,     0,   210,   211,   212,
       0,     0,   215,     0,     0,   164,     0,     0,     0,     0,
       0,    54,    56,     7,     0,    44,    45,    46,     0,     0,
       0,     0,   216,   203,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,   202,
       0,   221,     0,   226,     0,     0,     0,   214,   213,   155,
     165,   196,   197,   198,   199,   229,    53,     0,     0,   217,
       0,     0,     0,     0,   222,     0,     0,     0,     0,     0,
     218,     0,     0,     0,   223,     0,   207,   208,   209,   219
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   302,   358,    14,   361,   270,   271,    15,
      23,    37,    38,    39,    40,    41,    42,   161,   241,   401,
      43,    16,   397,    17,   398,   260,   154,   129,   130,   131,
      22,   132,   133,    30,    27,   367,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   245,   321,   410,   280,
     281,   246,   411
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -365
static const yytype_int16 yypact[] =
{
    -365,     5,    20,  -365,     2,   -36,   -10,  -365,   -18,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,    63,  -365,  -365,
      31,  -365,   -19,   484,   421,   421,  -365,    26,  -365,    35,
     158,  -365,   421,   421,  -365,   -18,  -365,  -365,   119,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,     8,    79,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,   181,   187,   205,   217,
     242,   252,   279,   283,   292,   295,   315,   339,   345,   346,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,   347,  -365,
    -365,   421,   367,   368,   253,   267,   419,  -365,  -365,   420,
     429,   443,   444,   446,   447,   465,  -365,  -365,  -365,   540,
    -365,  -365,    66,   364,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,   375,   540,   195,   240,  -365,    27,
       6,     3,   218,  -365,  -365,  -365,  -365,  -365,  -365,   186,
     186,   186,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,   241,    44,    31,    31,  -365,   260,   421,
     241,   241,   241,   241,   421,   421,   449,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,  -365,   241,   421,  -365,   421,
     513,   421,   421,   421,   421,   521,   523,   421,   421,   421,
     421,   421,  -365,  -365,  -365,  -365,  -365,  -365,   473,   475,
     485,  -365,  -365,  -365,  -365,   612,   517,   -18,   -18,   541,
     542,   624,   626,   627,   628,   635,   636,   637,   638,   641,
      81,  -365,  -365,   568,   581,   580,   146,   239,  -365,  -365,
      14,  -365,   323,   720,   721,   722,   723,    51,    58,   421,
      68,  -365,   566,   566,   566,   566,   566,   566,   551,   551,
     551,   314,   314,   314,   314,   314,   314,   314,   326,   328,
    -365,    82,   645,   364,   421,   364,   364,    89,  -365,  -365,
    -365,   386,   386,   159,   341,  -365,   596,   597,   598,   254,
    -365,    24,   728,   729,  -365,  -365,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   241,   709,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,   260,  -365,   421,   421,   421,   421,
     421,  -365,  -365,   191,  -365,  -365,  -365,  -365,    16,   501,
     654,    15,   275,   275,   275,  -365,  -365,   732,   517,   256,
     254,   254,   609,   622,   633,    73,   154,   189,   663,   668,
      32,  -365,   659,  -365,    18,   673,   678,   683,   688,   632,
    -365,  -365,  -365,   664,   241,  -365,  -365,  -365,   656,  -365,
    -365,   606,   610,   611,    35,    29,  -365,  -365,  -365,  -365,
     193,  -365,   666,   667,   421,   421,   421,  -365,  -365,  -365,
     421,   421,  -365,   421,   421,  -365,   421,   421,   421,   421,
     421,  -365,  -365,   661,   421,  -365,  -365,  -365,   669,   517,
     330,   269,  -365,  -365,  -365,   693,   698,   703,    64,    88,
     208,   236,   250,   277,   289,   304,   532,  -365,   539,  -365,
      30,  -365,   238,  -365,   421,   421,   421,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,   517,   564,  -365,
     708,   713,   718,   671,  -365,   263,   421,   421,   421,   567,
    -365,   137,   255,   261,  -365,   265,  -365,  -365,  -365,  -365
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -365,  -365,   569,  -291,     0,  -365,  -365,  -365,   407,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,    22,
    -365,   396,  -365,  -365,  -365,  -365,    -4,   -25,  -365,    17,
     -16,  -175,   -98,   -28,   481,    45,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,  -365,
    -365,  -365,  -365,  -365,  -365,  -365,  -365,  -364,  -338,  -365,
     477,   247,   317
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     155,   157,     4,     5,   405,     3,    29,   155,   155,   225,
     226,   227,   228,   229,   230,   231,   393,     5,   360,   162,
      -2,    18,   344,   221,   222,   223,   424,   224,   159,   160,
     225,   226,   227,   228,   229,   230,   231,   221,   222,   223,
     368,   224,   301,   394,    19,   439,   477,   225,   226,   227,
     228,   229,   230,   231,   225,   226,   227,   228,   229,   230,
     231,   225,   226,   227,   228,   229,   230,   231,   166,   221,
     222,   223,    20,   224,   219,   460,   225,   226,   227,   228,
     229,   230,   231,   164,   165,    28,   155,    21,    21,   335,
     219,   272,     6,   221,   222,   223,   223,   224,   224,   345,
     395,   425,   462,   396,   353,   433,   369,   184,     7,   156,
       8,   440,   478,   483,     7,   422,     9,    10,    11,    12,
      13,   303,     7,   305,   306,   307,   308,   262,   237,   236,
       9,    10,    11,    12,   351,    26,   238,   239,   240,    28,
     485,   352,   221,   222,   223,    24,   224,   467,   235,   220,
     279,   495,    25,   354,   167,   168,   417,   225,   226,   227,
     228,   229,   230,   231,   336,   356,   229,   230,   231,   155,
     155,   468,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     277,   278,   225,   226,   227,   228,   229,   230,   231,   219,
     261,   441,   155,   155,   155,   155,   155,   273,   274,   275,
     276,   225,   226,   227,   228,   229,   230,   231,   243,   244,
     496,   340,   341,   311,   312,   313,   314,   315,   372,   373,
     374,   322,   323,   300,   378,   379,   380,   418,   158,   225,
     226,   227,   228,   229,   230,   231,   441,   163,   384,   385,
     386,   387,   388,   225,   226,   227,   228,   229,   230,   231,
     221,   222,   223,   169,   224,     4,   221,   222,   223,   170,
     224,   441,   419,   441,   389,   233,   442,   266,   267,   155,
     225,   226,   227,   228,   229,   230,   231,   171,   406,   407,
     408,   469,   225,   226,   227,   228,   229,   230,   231,   172,
     359,   406,   407,   408,   155,   155,   155,   225,   226,   227,
     228,   229,   230,   231,   342,   343,   445,   446,   447,   470,
     234,   479,   448,   449,   173,   375,   376,   377,   221,   222,
     223,   346,   224,   471,   174,   268,   269,   187,   497,   409,
     213,   214,   215,   216,   498,   242,   490,     7,   499,   230,
     231,   188,   381,   214,   215,   216,   215,   216,   365,   366,
     472,   175,   406,   407,   408,   176,   480,   481,   482,   221,
     222,   223,   473,   224,   177,    18,   438,   178,   225,   226,
     227,   228,   229,   230,   231,   402,   403,   474,   491,   492,
     493,   227,   228,   229,   230,   231,   217,   179,   155,   155,
     218,   155,   155,   155,   155,   155,   399,   400,   217,   155,
     217,   432,   218,   461,   218,   412,   413,   247,   248,   450,
     451,   180,   452,   453,   454,   455,   456,   181,   182,   183,
     458,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   185,
     186,    62,    63,    64,    65,   232,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   189,   190,   111,   225,   226,   227,   228,   229,   230,
     231,   191,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   192,   193,     7,   194,   195,
     125,   279,   126,   127,   128,   225,   226,   227,   228,   229,
     230,   231,   225,   226,   227,   228,   229,   230,   231,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   391,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   406,   407,   408,   406,
     407,   408,   304,    31,    32,   309,    33,   310,    34,   316,
      35,   317,   475,    36,   221,   222,   223,   414,   224,   476,
     319,   318,   217,   320,   324,   325,   218,   221,   222,   223,
     415,   224,   326,   217,   327,   328,   329,   218,   221,   222,
     223,   416,   224,   330,   331,   332,   333,   484,   217,   334,
     494,   337,   218,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   338,   339,   263,   264,   221,   222,
     223,   420,   224,   221,   222,   223,   421,   224,   221,   222,
     223,   426,   224,   221,   222,   223,   427,   224,   221,   222,
     223,   428,   224,   221,   222,   223,   429,   224,   221,   222,
     223,   464,   224,   221,   222,   223,   465,   224,   221,   222,
     223,   466,   224,   221,   222,   223,   486,   224,   221,   222,
     223,   487,   224,   221,   222,   223,   488,   224,   347,   348,
     349,   350,   357,   362,   363,   364,   370,   371,   382,   392,
     404,   423,   430,   435,   431,   434,   457,   436,   437,   443,
     444,   383,   459,   489,   390,     0,   265,   355,   463
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,     1,   368,     0,    22,    32,    33,     3,
       4,     5,     6,     7,     8,     9,     1,     1,   309,    35,
       0,     4,     8,     5,     6,     7,     8,     9,    32,    33,
       3,     4,     5,     6,     7,     8,     9,     5,     6,     7,
      16,     9,   217,    28,    80,    16,    16,     3,     4,     5,
       6,     7,     8,     9,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,    51,     5,
       6,     7,    82,     9,     8,   439,     3,     4,     5,     6,
       7,     8,     9,    75,    76,   104,   111,   106,   106,     8,
       8,   189,    90,     5,     6,     7,     7,     9,     9,    85,
      85,    83,   440,    88,   279,   396,    82,   111,   106,    83,
     108,    82,    82,   477,   106,    83,   114,   115,   116,   117,
     118,   219,   106,   221,   222,   223,   224,    83,   125,   123,
     114,   115,   116,   117,    83,   104,   133,   134,   135,   104,
     478,    83,     5,     6,     7,    82,     9,    83,   121,    83,
      82,   489,    89,    85,    75,    76,    83,     3,     4,     5,
       6,     7,     8,     9,    83,    83,     7,     8,     9,   194,
     195,    83,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     194,   195,     3,     4,     5,     6,     7,     8,     9,     8,
     183,     8,   227,   228,   229,   230,   231,   190,   191,   192,
     193,     3,     4,     5,     6,     7,     8,     9,    32,    33,
      83,    75,    76,   227,   228,   229,   230,   231,   326,   327,
     328,   247,   248,   216,   332,   333,   334,    83,    80,     3,
       4,     5,     6,     7,     8,     9,     8,   128,   346,   347,
     348,   349,   350,     3,     4,     5,     6,     7,     8,     9,
       5,     6,     7,    82,     9,   265,     5,     6,     7,    82,
       9,     8,    83,     8,    83,    80,    83,    17,    18,   304,
       3,     4,     5,     6,     7,     8,     9,    82,    32,    33,
      34,    83,     3,     4,     5,     6,     7,     8,     9,    82,
     304,    32,    33,    34,   329,   330,   331,     3,     4,     5,
       6,     7,     8,     9,    75,    76,   414,   415,   416,    83,
      80,    83,   420,   421,    82,   329,   330,   331,     5,     6,
       7,     8,     9,    83,    82,    75,    76,    84,    83,    83,
      26,    27,    28,    29,    83,   127,    83,   106,    83,     8,
       9,    84,   335,    27,    28,    29,    28,    29,   104,   105,
      83,    82,    32,    33,    34,    82,   464,   465,   466,     5,
       6,     7,    83,     9,    82,   358,   404,    82,     3,     4,
       5,     6,     7,     8,     9,   363,   364,    83,   486,   487,
     488,     5,     6,     7,     8,     9,    82,    82,   423,   424,
      86,   426,   427,   428,   429,   430,   131,   132,    82,   434,
      82,   394,    86,    83,    86,   370,   371,   170,   171,   423,
     424,    82,   426,   427,   428,   429,   430,    82,    82,    82,
     434,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    82,
      82,    30,    31,    32,    33,    80,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    82,    82,    82,     3,     4,     5,     6,     7,     8,
       9,    82,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    82,    82,   106,    82,    82,
     109,    82,   111,   112,   113,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,    84,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    80,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    32,    33,    34,    32,
      33,    34,    89,   119,   120,    84,   122,    84,   124,   136,
     126,   136,    80,   129,     5,     6,     7,     8,     9,    80,
       8,   136,    82,   106,    83,    83,    86,     5,     6,     7,
       8,     9,     8,    82,     8,     8,     8,    86,     5,     6,
       7,     8,     9,     8,     8,     8,     8,    83,    82,     8,
      83,    83,    86,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,    83,    85,   185,   186,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     8,     8,
       8,     8,    87,   137,   137,   137,     8,     8,    29,    85,
       8,    82,   110,   137,    80,    89,    85,   137,   137,    83,
      83,   344,    83,    82,   358,    -1,   187,   280,   441
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   139,   140,     0,   142,     1,    90,   106,   108,   114,
     115,   116,   117,   118,   143,   147,   159,   161,   167,    80,
      82,   106,   168,   148,    82,    89,   104,   172,   104,   168,
     171,   119,   120,   122,   124,   126,   129,   149,   150,   151,
     152,   153,   154,   158,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    82,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   109,   111,   112,   113,   165,
     166,   167,   169,   170,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   164,   165,    83,   171,    80,   164,
     164,   155,   168,   128,    75,    76,   167,    75,    76,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,   164,    82,    82,    84,    84,    82,
      82,    82,    82,    82,    82,    82,    84,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    82,    86,     8,
      83,     5,     6,     7,     9,     3,     4,     5,     6,     7,
       8,     9,    80,    80,    80,   121,   123,   125,   133,   134,
     135,   156,   127,    32,    33,   194,   199,   199,   199,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     163,   167,    83,   172,   172,   140,    17,    18,    75,    76,
     145,   146,   170,   167,   167,   167,   167,   164,   164,    82,
     197,   198,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     167,   169,   141,   170,    89,   170,   170,   170,   170,    84,
      84,   164,   164,   164,   164,   164,   136,   136,   136,     8,
     106,   195,   168,   168,    83,    83,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,    83,    83,    83,    85,
      75,    76,    75,    76,     8,    85,     8,     8,     8,     8,
       8,    83,    83,   169,    85,   198,    83,    87,   142,   164,
     141,   144,   137,   137,   137,   104,   105,   173,    16,    82,
       8,     8,   170,   170,   170,   164,   164,   164,   170,   170,
     170,   167,    29,   146,   170,   170,   170,   170,   170,    83,
     159,    80,    85,     1,    28,    85,    88,   160,   162,   131,
     132,   157,   157,   157,     8,   195,    32,    33,    34,    83,
     196,   200,   173,   173,     8,     8,     8,    83,    83,    83,
       8,     8,    83,    82,     8,    83,     8,     8,     8,     8,
     110,    80,   167,   141,    89,   137,   137,   137,   171,    16,
      82,     8,    83,    83,    83,   170,   170,   170,   170,   170,
     164,   164,   164,   164,   164,   164,   164,    85,   164,    83,
     195,    83,   196,   200,     8,     8,     8,    83,    83,    83,
      83,    83,    83,    83,    83,    80,    80,    16,    82,    83,
     170,   170,   170,   195,    83,   196,     8,     8,     8,    82,
      83,   170,   170,   170,    83,   196,    83,    83,    83,    83
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
#line 348 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 351 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 4:
#line 352 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp); ;}
    break;

  case 5:
#line 355 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 6:
#line 356 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp);;}
    break;

  case 7:
#line 359 "faustparser.y"
    { (yyval.numvariant) = 0; ;}
    break;

  case 8:
#line 360 "faustparser.y"
    { (yyval.numvariant) = (yyvsp[(1) - (2)].numvariant) | (yyvsp[(2) - (2)].numvariant);;}
    break;

  case 9:
#line 363 "faustparser.y"
    { (yyval.numvariant) = 1;;}
    break;

  case 10:
#line 364 "faustparser.y"
    { (yyval.numvariant) = 2;;}
    break;

  case 11:
#line 365 "faustparser.y"
    { (yyval.numvariant) = 4;;}
    break;

  case 12:
#line 366 "faustparser.y"
    { (yyval.numvariant) = 8;;}
    break;

  case 13:
#line 369 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 14:
#line 370 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 15:
#line 377 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 378 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); ;}
    break;

  case 17:
#line 381 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 18:
#line 382 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 19:
#line 383 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 20:
#line 384 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 21:
#line 385 "faustparser.y"
    { (yyval.exp) = boxInt(-str2int(FAUSTtext)); ;}
    break;

  case 22:
#line 386 "faustparser.y"
    { (yyval.exp) = boxReal(-atof(FAUSTtext)); ;}
    break;

  case 23:
#line 389 "faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 24:
#line 390 "faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 25:
#line 391 "faustparser.y"
    { declareDefinitionMetadata((yyvsp[(2) - (5)].exp),(yyvsp[(3) - (5)].exp),(yyvsp[(4) - (5)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 26:
#line 392 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 27:
#line 393 "faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 28:
#line 396 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 29:
#line 397 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 30:
#line 400 "faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 31:
#line 401 "faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 32:
#line 402 "faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 33:
#line 403 "faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 34:
#line 404 "faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 35:
#line 405 "faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 36:
#line 408 "faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 37:
#line 409 "faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(FAUSTtext)); ;}
    break;

  case 38:
#line 412 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 39:
#line 415 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 40:
#line 418 "faustparser.y"
    { ;}
    break;

  case 41:
#line 421 "faustparser.y"
    { ;}
    break;

  case 42:
#line 424 "faustparser.y"
    { ;}
    break;

  case 43:
#line 425 "faustparser.y"
    { ;}
    break;

  case 44:
#line 428 "faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 45:
#line 429 "faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; ;}
    break;

  case 46:
#line 430 "faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 47:
#line 433 "faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 48:
#line 434 "faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 49:
#line 437 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 50:
#line 440 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); setDefProp((yyvsp[(1) - (7)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 51:
#line 441 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp)));  setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 52:
#line 442 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 53:
#line 445 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 54:
#line 446 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 55:
#line 449 "faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); ;}
    break;

  case 56:
#line 452 "faustparser.y"
    { (yyval.exp)=(yyvsp[(2) - (2)].exp); ;}
    break;

  case 57:
#line 455 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 58:
#line 456 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 59:
#line 459 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 60:
#line 460 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp)), gGlobal->nil); ;}
    break;

  case 61:
#line 461 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (7)].exp),formatDefinitions((yyvsp[(4) - (7)].exp)),formatDefinitions((yyvsp[(6) - (7)].exp))); ;}
    break;

  case 62:
#line 462 "faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 63:
#line 463 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 64:
#line 464 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 65:
#line 465 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 66:
#line 466 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 67:
#line 467 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 68:
#line 470 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 69:
#line 471 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 70:
#line 472 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); ;}
    break;

  case 71:
#line 473 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 72:
#line 474 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); ;}
    break;

  case 73:
#line 475 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gGlobal->gPowPrim->box()); ;}
    break;

  case 74:
#line 476 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDelay)); ;}
    break;

  case 75:
#line 477 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 76:
#line 478 "faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 77:
#line 480 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); ;}
    break;

  case 78:
#line 481 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); ;}
    break;

  case 79:
#line 482 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 80:
#line 484 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 81:
#line 485 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigARightShift)); ;}
    break;

  case 82:
#line 487 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); ;}
    break;

  case 83:
#line 488 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); ;}
    break;

  case 84:
#line 489 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); ;}
    break;

  case 85:
#line 490 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); ;}
    break;

  case 86:
#line 491 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 87:
#line 492 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); ;}
    break;

  case 88:
#line 494 "faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 89:
#line 495 "faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 90:
#line 497 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 91:
#line 500 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 92:
#line 501 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 93:
#line 503 "faustparser.y"
    { (yyval.exp) = boxInt (str2int(FAUSTtext)); ;}
    break;

  case 94:
#line 504 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 95:
#line 506 "faustparser.y"
    { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); ;}
    break;

  case 96:
#line 507 "faustparser.y"
    { (yyval.exp) = boxReal( -atof(FAUSTtext) ); ;}
    break;

  case 97:
#line 509 "faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 98:
#line 510 "faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 99:
#line 512 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); ;}
    break;

  case 100:
#line 513 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); ;}
    break;

  case 101:
#line 515 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); ;}
    break;

  case 102:
#line 516 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); ;}
    break;

  case 103:
#line 518 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); ;}
    break;

  case 104:
#line 519 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); ;}
    break;

  case 105:
#line 520 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); ;}
    break;

  case 106:
#line 521 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); ;}
    break;

  case 107:
#line 522 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); ;}
    break;

  case 108:
#line 523 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigDelay); ;}
    break;

  case 109:
#line 525 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); ;}
    break;

  case 110:
#line 526 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); ;}
    break;

  case 111:
#line 527 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); ;}
    break;

  case 112:
#line 529 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); ;}
    break;

  case 113:
#line 530 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigARightShift); ;}
    break;

  case 114:
#line 532 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); ;}
    break;

  case 115:
#line 533 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); ;}
    break;

  case 116:
#line 534 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); ;}
    break;

  case 117:
#line 535 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); ;}
    break;

  case 118:
#line 536 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); ;}
    break;

  case 119:
#line 537 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); ;}
    break;

  case 120:
#line 539 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); ;}
    break;

  case 121:
#line 540 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigEnable); ;}
    break;

  case 122:
#line 541 "faustparser.y"
    { (yyval.exp) = boxPrim2(sigControl); ;}
    break;

  case 123:
#line 543 "faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); ;}
    break;

  case 124:
#line 544 "faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); ;}
    break;

  case 125:
#line 545 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); ;}
    break;

  case 126:
#line 546 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); ;}
    break;

  case 127:
#line 547 "faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); ;}
    break;

  case 128:
#line 548 "faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); ;}
    break;

  case 129:
#line 549 "faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); ;}
    break;

  case 130:
#line 551 "faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); ;}
    break;

  case 131:
#line 552 "faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); ;}
    break;

  case 132:
#line 553 "faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); ;}
    break;

  case 133:
#line 554 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 134:
#line 555 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 135:
#line 556 "faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); ;}
    break;

  case 136:
#line 558 "faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); ;}
    break;

  case 137:
#line 559 "faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); ;}
    break;

  case 138:
#line 560 "faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); ;}
    break;

  case 139:
#line 562 "faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); ;}
    break;

  case 140:
#line 563 "faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); ;}
    break;

  case 141:
#line 565 "faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); ;}
    break;

  case 142:
#line 566 "faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); ;}
    break;

  case 143:
#line 567 "faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); ;}
    break;

  case 144:
#line 568 "faustparser.y"
    { (yyval.exp) = gGlobal->gRoundPrim->box(); ;}
    break;

  case 145:
#line 570 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); ;}
    break;

  case 146:
#line 571 "faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); ;}
    break;

  case 147:
#line 573 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); ;}
    break;

  case 148:
#line 574 "faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); ;}
    break;

  case 149:
#line 576 "faustparser.y"
    { (yyval.exp) = boxPrim3(sigAssertBounds);;}
    break;

  case 150:
#line 577 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigLowest);;}
    break;

  case 151:
#line 578 "faustparser.y"
    { (yyval.exp) = boxPrim1(sigHighest);;}
    break;

  case 152:
#line 580 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);  setUseProp((yyvsp[(1) - (1)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 153:
#line 581 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); ;}
    break;

  case 154:
#line 583 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 155:
#line 585 "faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 156:
#line 587 "faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 157:
#line 589 "faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 158:
#line 590 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 159:
#line 591 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 160:
#line 592 "faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 161:
#line 593 "faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 162:
#line 594 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 163:
#line 595 "faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); ;}
    break;

  case 164:
#line 596 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp), boxPar(boxInt(0),boxInt(0))); ;}
    break;

  case 165:
#line 597 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), (yyvsp[(7) - (8)].exp)); ;}
    break;

  case 166:
#line 598 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 167:
#line 599 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 168:
#line 600 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 169:
#line 601 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 170:
#line 602 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 171:
#line 603 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 172:
#line 604 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 173:
#line 605 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 174:
#line 606 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 175:
#line 607 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 176:
#line 608 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 177:
#line 610 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 178:
#line 611 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 179:
#line 612 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 180:
#line 613 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 181:
#line 615 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 182:
#line 616 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 183:
#line 620 "faustparser.y"
    { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 184:
#line 623 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 185:
#line 626 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 186:
#line 627 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 187:
#line 630 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 188:
#line 631 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 189:
#line 632 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 190:
#line 633 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 191:
#line 634 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 192:
#line 637 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 193:
#line 640 "faustparser.y"
    { (yyval.exp) = unquote(FAUSTtext); ;}
    break;

  case 194:
#line 643 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 195:
#line 644 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 196:
#line 650 "faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 197:
#line 654 "faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 198:
#line 658 "faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 199:
#line 662 "faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 200:
#line 665 "faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 201:
#line 668 "faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 202:
#line 674 "faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 203:
#line 678 "faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 204:
#line 682 "faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 205:
#line 686 "faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 206:
#line 689 "faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 207:
#line 693 "faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 208:
#line 696 "faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 209:
#line 699 "faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 210:
#line 702 "faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 211:
#line 705 "faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 212:
#line 708 "faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 213:
#line 712 "faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 214:
#line 715 "faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 215:
#line 718 "faustparser.y"
    { (yyval.exp) = boxSoundfile((yyvsp[(3) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 216:
#line 724 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp),cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil)))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 217:
#line 725 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil)))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 218:
#line 726 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp),cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil)))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 219:
#line 727 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (11)].exp),cons(cons((yyvsp[(2) - (11)].exp),cons((yyvsp[(4) - (11)].exp),cons((yyvsp[(6) - (11)].exp),cons((yyvsp[(8) - (11)].exp),gGlobal->nil)))), (yyvsp[(10) - (11)].exp))); ;}
    break;

  case 220:
#line 729 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 221:
#line 730 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp),cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 222:
#line 731 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp),cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 223:
#line 732 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (10)].exp),cons(cons((yyvsp[(2) - (10)].exp),cons((yyvsp[(4) - (10)].exp),cons((yyvsp[(6) - (10)].exp),cons((yyvsp[(8) - (10)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 224:
#line 735 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 225:
#line 738 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 226:
#line 739 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 227:
#line 742 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 228:
#line 743 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 229:
#line 747 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 230:
#line 750 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 231:
#line 751 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 232:
#line 754 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 233:
#line 755 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 234:
#line 756 "faustparser.y"
    { (yyval.exp) = tree(2); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3372 "faustparser.cpp"
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


#line 759 "faustparser.y"


