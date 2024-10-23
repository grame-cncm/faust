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
     WIRE = 334,
     CUT = 335,
     ENDDEF = 336,
     VIRG = 337,
     LPAR = 338,
     RPAR = 339,
     LBRAQ = 340,
     RBRAQ = 341,
     LCROC = 342,
     RCROC = 343,
     WHERE = 344,
     DEF = 345,
     LAPPLY = 346,
     IMPORT = 347,
     COMPONENT = 348,
     LIBRARY = 349,
     ENVIRONMENT = 350,
     WAVEFORM = 351,
     ROUTE = 352,
     ENABLE = 353,
     CONTROL = 354,
     IPAR = 355,
     ISEQ = 356,
     ISUM = 357,
     IPROD = 358,
     INPUTS = 359,
     OUTPUTS = 360,
     STRING = 361,
     FSTRING = 362,
     IDENT = 363,
     EXTRA = 364,
     DECLARE = 365,
     CASE = 366,
     ARROW = 367,
     ASSERTBOUNDS = 368,
     LOWEST = 369,
     HIGHEST = 370,
     FLOATMODE = 371,
     DOUBLEMODE = 372,
     QUADMODE = 373,
     FIXEDPOINTMODE = 374,
     BDOC = 375,
     EDOC = 376,
     BEQN = 377,
     EEQN = 378,
     BDGM = 379,
     EDGM = 380,
     BLST = 381,
     ELST = 382,
     BMETADATA = 383,
     EMETADATA = 384,
     DOCCHAR = 385,
     NOTICE = 386,
     LISTING = 387,
     LSTTRUE = 388,
     LSTFALSE = 389,
     LSTDEPENDENCIES = 390,
     LSTMDOCTAGS = 391,
     LSTDISTRIBUTED = 392,
     LSTEQ = 393,
     LSTQ = 394
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
#define WIRE 334
#define CUT 335
#define ENDDEF 336
#define VIRG 337
#define LPAR 338
#define RPAR 339
#define LBRAQ 340
#define RBRAQ 341
#define LCROC 342
#define RCROC 343
#define WHERE 344
#define DEF 345
#define LAPPLY 346
#define IMPORT 347
#define COMPONENT 348
#define LIBRARY 349
#define ENVIRONMENT 350
#define WAVEFORM 351
#define ROUTE 352
#define ENABLE 353
#define CONTROL 354
#define IPAR 355
#define ISEQ 356
#define ISUM 357
#define IPROD 358
#define INPUTS 359
#define OUTPUTS 360
#define STRING 361
#define FSTRING 362
#define IDENT 363
#define EXTRA 364
#define DECLARE 365
#define CASE 366
#define ARROW 367
#define ASSERTBOUNDS 368
#define LOWEST 369
#define HIGHEST 370
#define FLOATMODE 371
#define DOUBLEMODE 372
#define QUADMODE 373
#define FIXEDPOINTMODE 374
#define BDOC 375
#define EDOC 376
#define BEQN 377
#define EEQN 378
#define BDGM 379
#define EDGM 380
#define BLST 381
#define ELST 382
#define BMETADATA 383
#define EMETADATA 384
#define DOCCHAR 385
#define NOTICE 386
#define LISTING 387
#define LSTTRUE 388
#define LSTFALSE 389
#define LSTDEPENDENCIES 390
#define LSTMDOCTAGS 391
#define LSTDISTRIBUTED 392
#define LSTEQ 393
#define LSTQ 394




/* Copy the first part of user declarations.  */
#line 5 "faustparser.y"


#include "global.hh"
#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
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

void yyerror(char* msg) 
{
    std::stringstream error;
    error << FAUSTfilename << " : " << FAUSTlineno << " : ERROR : " << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
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

//----------------------------------------------------------
// unquote() : remove enclosing quotes and carriage return 
// characters from string. Returns a Tree 
//----------------------------------------------------------
inline char replaceCR(char c)
{
    return (c != '\n') ? c : ' ';
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
#line 103 "faustparser.y"
{
    CTreeBase*     exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}
/* Line 193 of yacc.c.  */
#line 488 "faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 501 "faustparser.cpp"

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
#define YYLAST   774

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  140
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  239
/* YYNRULES -- Number of states.  */
#define YYNSTATES  511

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   394

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
     135,   136,   137,   138,   139
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
     434,   436,   438,   440,   442,   444,   446,   448,   451,   455,
     464,   470,   475,   477,   479,   481,   486,   491,   496,   501,
     508,   517,   519,   521,   523,   525,   527,   529,   531,   533,
     535,   537,   539,   541,   543,   545,   547,   549,   551,   553,
     555,   557,   561,   565,   569,   573,   577,   579,   581,   583,
     585,   587,   596,   605,   614,   623,   628,   633,   642,   650,
     658,   663,   668,   681,   694,   707,   714,   721,   728,   737,
     746,   753,   759,   767,   777,   789,   794,   801,   810,   821,
     823,   825,   829,   831,   834,   841,   843,   845,   847,   849
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     141,     0,    -1,   142,    -1,    -1,   142,   144,   149,    -1,
      -1,   143,   144,   161,    -1,    -1,   144,   145,    -1,   116,
      -1,   117,    -1,   118,    -1,   119,    -1,    -1,   146,   162,
      -1,   148,    -1,   147,     8,   148,    -1,    75,    -1,    76,
      -1,    18,    75,    -1,    18,    76,    -1,    17,    75,    -1,
      17,    76,    -1,    92,    83,   176,    84,    81,    -1,   110,
     172,   175,    81,    -1,   110,   172,   172,   175,    81,    -1,
     161,    -1,   120,   150,   121,    -1,    -1,   150,   151,    -1,
     152,    -1,   153,    -1,   154,    -1,   155,    -1,   156,    -1,
     160,    -1,    -1,   152,   130,    -1,   122,   168,   123,    -1,
     124,   168,   125,    -1,   131,    -1,   126,   157,   127,    -1,
      -1,   157,   158,    -1,   135,   138,   139,   159,   139,    -1,
     136,   138,   139,   159,   139,    -1,   137,   138,   139,   159,
     139,    -1,   133,    -1,   134,    -1,   128,   172,   129,    -1,
     163,    83,   173,    84,    90,   168,    81,    -1,   163,    90,
     168,    81,    -1,     1,    81,    -1,   164,    90,   168,    81,
      -1,     1,    81,    -1,   171,    -1,    28,   171,    -1,   171,
      -1,   165,     8,   171,    -1,   176,    -1,   176,     7,   174,
      -1,   166,    -1,   167,     8,   166,    -1,   168,     3,    85,
     143,    86,    -1,   168,     4,    85,   146,    86,    -1,   168,
       4,    85,   146,    89,   143,    86,    -1,   168,     8,   168,
      -1,   168,     7,   168,    -1,   168,     6,   168,    -1,   168,
       5,   168,    -1,   168,     9,   168,    -1,   169,    -1,   169,
      18,   169,    -1,   169,    17,   169,    -1,   169,    25,   169,
      -1,   169,    24,   169,    -1,   169,    23,   169,    -1,   169,
      26,   169,    -1,   169,    27,   169,    -1,   169,    28,    -1,
     169,    29,   171,    -1,   169,    22,   169,    -1,   169,    16,
     169,    -1,   169,    21,   169,    -1,   169,    20,   169,    -1,
     169,    19,   169,    -1,   169,    15,   169,    -1,   169,    14,
     169,    -1,   169,    12,   169,    -1,   169,    11,   169,    -1,
     169,    13,   169,    -1,   169,    10,   169,    -1,   169,    83,
     173,    84,    -1,   169,    87,   143,    88,    -1,   170,    -1,
      75,    -1,    76,    -1,    18,    75,    -1,    18,    76,    -1,
      17,    75,    -1,    17,    76,    -1,    79,    -1,    80,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    18,    -1,
      17,    -1,    25,    -1,    24,    -1,    23,    -1,    27,    -1,
      22,    -1,    16,    -1,    21,    -1,    20,    -1,    19,    -1,
      15,    -1,    14,    -1,    12,    -1,    11,    -1,    13,    -1,
      10,    -1,    49,    -1,    98,    -1,    99,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    58,    -1,    59,    -1,    26,    -1,
      60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
     113,    -1,   114,    -1,   115,    -1,   171,    -1,    17,   171,
      -1,    83,   168,    84,    -1,    78,    83,   165,    84,    29,
      83,   168,    84,    -1,    87,   167,    91,   168,    88,    -1,
     111,    85,   201,    86,    -1,   184,    -1,   185,    -1,   186,
      -1,    93,    83,   176,    84,    -1,    94,    83,   176,    84,
      -1,    95,    85,   142,    86,    -1,    96,    85,   147,    86,
      -1,    97,    83,   174,     8,   174,    84,    -1,    97,    83,
     174,     8,   174,     8,   168,    84,    -1,   187,    -1,   188,
      -1,   189,    -1,   190,    -1,   191,    -1,   192,    -1,   193,
      -1,   194,    -1,   195,    -1,   196,    -1,   197,    -1,   178,
      -1,   179,    -1,   180,    -1,   181,    -1,   182,    -1,   183,
      -1,   108,    -1,   108,    -1,   174,    -1,   173,     8,   174,
      -1,   174,     7,   174,    -1,   174,     6,   174,    -1,   174,
       5,   174,    -1,   174,     9,   174,    -1,   169,    -1,   106,
      -1,   106,    -1,   106,    -1,   107,    -1,   100,    83,   171,
       8,   174,     8,   168,    84,    -1,   101,    83,   171,     8,
     174,     8,   168,    84,    -1,   102,    83,   171,     8,   174,
       8,   168,    84,    -1,   103,    83,   171,     8,   174,     8,
     168,    84,    -1,   104,    83,   168,    84,    -1,   105,    83,
     168,    84,    -1,    35,    83,   198,     8,   177,     8,   175,
      84,    -1,    36,    83,   203,   172,     8,   177,    84,    -1,
      37,    83,   203,   172,     8,   177,    84,    -1,    38,    83,
     176,    84,    -1,    39,    83,   176,    84,    -1,    40,    83,
     176,     8,   174,     8,   174,     8,   174,     8,   174,    84,
      -1,    41,    83,   176,     8,   174,     8,   174,     8,   174,
       8,   174,    84,    -1,    42,    83,   176,     8,   174,     8,
     174,     8,   174,     8,   174,    84,    -1,    43,    83,   176,
       8,   168,    84,    -1,    44,    83,   176,     8,   168,    84,
      -1,    45,    83,   176,     8,   168,    84,    -1,    47,    83,
     176,     8,   174,     8,   174,    84,    -1,    46,    83,   176,
       8,   174,     8,   174,    84,    -1,    48,    83,   176,     8,
     174,    84,    -1,   203,   199,    83,   200,    84,    -1,   203,
     199,    16,   199,    83,   200,    84,    -1,   203,   199,    16,
     199,    16,   199,    83,   200,    84,    -1,   203,   199,    16,
     199,    16,   199,    16,   199,    83,   200,    84,    -1,   203,
     199,    83,    84,    -1,   203,   199,    16,   199,    83,    84,
      -1,   203,   199,    16,   199,    16,   199,    83,    84,    -1,
     203,   199,    16,   199,    16,   199,    16,   199,    83,    84,
      -1,   108,    -1,   204,    -1,   200,     8,   204,    -1,   202,
      -1,   201,   202,    -1,    83,   173,    84,   112,   168,    81,
      -1,    32,    -1,    33,    -1,    32,    -1,    33,    -1,    34,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   359,   359,   362,   363,   366,   367,   370,   371,   374,
     375,   376,   377,   380,   381,   388,   389,   392,   393,   394,
     395,   396,   397,   400,   401,   402,   403,   404,   407,   408,
     411,   412,   413,   414,   415,   416,   419,   420,   423,   426,
     429,   432,   435,   436,   439,   440,   441,   444,   445,   448,
     451,   452,   453,   456,   457,   460,   463,   466,   467,   470,
     471,   474,   475,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   499,   500,   501,   503,   504,   506,   507,   508,   509,
     510,   511,   513,   514,   516,   519,   520,   522,   523,   525,
     526,   528,   529,   531,   532,   534,   535,   537,   538,   539,
     540,   541,   542,   544,   545,   546,   548,   549,   551,   552,
     553,   554,   555,   556,   558,   559,   560,   562,   563,   564,
     565,   566,   567,   568,   570,   571,   572,   573,   574,   575,
     577,   578,   579,   581,   582,   584,   585,   586,   587,   589,
     590,   592,   593,   595,   596,   597,   599,   600,   602,   603,
     609,   612,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   635,   636,   637,   638,   640,   641,   644,   647,
     650,   651,   654,   655,   656,   657,   658,   661,   664,   667,
     668,   673,   677,   681,   685,   689,   692,   697,   701,   705,
     710,   713,   716,   719,   722,   725,   728,   731,   735,   738,
     741,   748,   749,   750,   751,   753,   754,   755,   756,   759,
     762,   763,   766,   767,   770,   774,   775,   778,   779,   780
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
  "LAMBDA", "WIRE", "CUT", "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ",
  "RBRAQ", "LCROC", "RCROC", "WHERE", "DEF", "LAPPLY", "IMPORT",
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "ROUTE", "ENABLE",
  "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS", "OUTPUTS",
  "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE", "CASE", "ARROW",
  "ASSERTBOUNDS", "LOWEST", "HIGHEST", "FLOATMODE", "DOUBLEMODE",
  "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM",
  "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE",
  "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "variantlist", "variant", "reclist", "vallist", "number",
  "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm", "docntc",
  "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "modentry",
  "modlist", "expression", "infixexp", "primitive", "ident", "name",
  "arglist", "argument", "string", "uqstring", "fstring", "fpar", "fseq",
  "fsum", "fprod", "finputs", "foutputs", "ffunction", "fconst",
  "fvariable", "button", "checkbox", "vslider", "hslider", "nentry",
  "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph", "soundfile",
  "signature", "fun", "typelist", "rulelist", "rule", "type", "argtype", 0
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
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   140,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   145,   145,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   149,   149,   149,   149,   149,   150,   150,
     151,   151,   151,   151,   151,   151,   152,   152,   153,   154,
     155,   156,   157,   157,   158,   158,   158,   159,   159,   160,
     161,   161,   161,   162,   162,   163,   164,   165,   165,   166,
     166,   167,   167,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   171,   172,
     173,   173,   174,   174,   174,   174,   174,   175,   176,   177,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     200,   200,   201,   201,   202,   203,   203,   204,   204,   204
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
       1,     1,     1,     1,     1,     1,     1,     2,     3,     8,
       5,     4,     1,     1,     1,     4,     4,     4,     4,     6,
       8,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     8,     8,     8,     8,     4,     4,     8,     7,     7,
       4,     4,    12,    12,    12,     6,     6,     6,     8,     8,
       6,     5,     7,     9,    11,     4,     6,     8,    10,     1,
       1,     3,     1,     2,     6,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   188,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   189,     0,    36,     0,     0,   198,     0,   197,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   123,   121,   120,   122,   119,   118,
     114,   108,   107,   117,   116,   115,   113,   111,   110,   109,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,     0,     0,     0,     0,   153,   154,   155,
     196,    94,   156,     0,   190,   182,   183,   184,   185,   186,
     187,   162,   163,   164,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,     0,    71,     0,     0,    24,
       0,     0,     0,     0,    37,    99,   100,   157,    97,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    59,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    23,    25,    38,
      39,    41,     0,     0,     0,    43,    49,   235,   236,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,   158,     0,     0,     0,
       0,     0,     7,     0,     0,    17,    18,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,    91,
      89,    88,    90,    87,    86,    82,    73,    72,    85,    84,
      83,    81,    76,    75,    74,    77,    78,    80,     0,     7,
     191,     0,   194,   193,   192,   195,     5,    13,    69,    68,
      67,    66,    70,     0,     0,     0,     0,   229,     0,     0,
       0,   210,   211,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,    60,   165,   166,   167,
      21,    22,    19,    20,     0,   168,     0,     0,     0,     0,
       0,   205,   206,     0,   161,   233,    92,    93,     0,     0,
       7,     0,     0,     0,     0,   199,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,   160,    16,     0,     0,     0,     0,     0,
       0,     6,    50,    63,     0,     0,    64,     5,    14,     0,
      47,    48,     0,     0,     0,     0,     0,   237,   238,   239,
     225,     0,   230,     0,     0,     0,     0,     0,   215,   216,
     217,     0,     0,   220,     0,     0,   169,     0,     0,     0,
       0,     0,    54,    56,     7,     0,    44,    45,    46,     0,
       0,     0,     0,   221,   208,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
     207,     0,   226,     0,   231,     0,     0,     0,   219,   218,
     159,   170,   201,   202,   203,   204,   234,    53,     0,     0,
     222,     0,     0,     0,     0,   227,     0,     0,     0,     0,
       0,   223,     0,     0,     0,   228,     0,   212,   213,   214,
     224
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   309,   368,    14,   371,   277,   278,    15,
      23,    37,    38,    39,    40,    41,    42,   162,   245,   412,
      43,    16,   408,    17,   409,   264,   186,   187,   155,   130,
     131,   132,    22,   133,   134,    30,   188,   377,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   249,   328,
     421,   287,   288,   250,   422
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -374
static const yytype_int16 yypact[] =
{
    -374,   106,   109,  -374,     3,   -16,    31,  -374,    30,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,    64,  -374,  -374,
      21,  -374,   -82,   114,   432,   432,  -374,    74,  -374,    47,
      87,  -374,   432,   432,  -374,    30,  -374,  -374,    26,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,    41,   -21,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,    92,   113,   117,   119,
     151,   156,   161,   177,   248,   281,   287,   301,   303,   325,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,   328,  -374,
    -374,   432,    21,   336,   341,    63,   133,   346,  -374,  -374,
     349,   357,   377,   378,   426,   430,   250,  -374,  -374,  -374,
     586,  -374,  -374,    15,   621,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,   385,   586,    90,   277,  -374,
      27,     6,   269,   298,  -374,  -374,  -374,  -374,  -374,  -374,
     255,   255,   255,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,   271,    34,  -374,    10,   370,    21,
      21,  -374,    49,   432,   271,   271,   271,   271,   432,   432,
     431,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,  -374,
     271,   432,  -374,   432,   433,   432,   432,   432,   432,   436,
     437,   432,   432,   432,   432,   432,  -374,  -374,  -374,  -374,
    -374,  -374,   386,   400,   401,  -374,  -374,  -374,  -374,   533,
     434,    30,    30,   460,   474,   583,   584,   585,   623,   624,
     625,   627,   628,   629,    19,  -374,  -374,    21,   432,   432,
     479,   510,   552,   234,   293,  -374,  -374,    12,  -374,   581,
     632,   633,   634,   636,    55,    67,   432,   -61,  -374,   658,
     658,   658,   658,   658,   658,   639,   639,   639,   316,   316,
     316,   316,   316,   316,   316,   338,   197,  -374,    44,   568,
     621,   432,   621,   621,   103,  -374,  -374,  -374,   611,   611,
     208,   329,  -374,   531,   532,   579,   275,  -374,    69,   664,
     711,  -374,  -374,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   271,   691,  -374,    42,   621,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,    49,  -374,   432,   432,   432,   432,
     432,  -374,  -374,    45,  -374,  -374,  -374,  -374,    18,   562,
     635,    16,   264,   264,   264,  -374,  -374,   715,   434,   296,
     275,   275,   616,   640,   646,    75,   157,   262,   683,   688,
     252,  -374,   641,  -374,  -374,   135,   693,   698,   703,   708,
     613,  -374,  -374,  -374,   656,   271,  -374,  -374,  -374,   648,
    -374,  -374,   600,   601,   603,    47,    72,  -374,  -374,  -374,
    -374,    48,  -374,   659,   660,   432,   432,   432,  -374,  -374,
    -374,   432,   432,  -374,   432,   432,  -374,   432,   432,   432,
     432,   432,  -374,  -374,   680,   432,  -374,  -374,  -374,   684,
     434,   323,   260,  -374,  -374,  -374,   722,   727,   741,   276,
     299,   270,   294,   311,   318,   344,   545,   569,  -374,   576,
    -374,    84,  -374,    61,  -374,   432,   432,   432,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,   434,   339,
    -374,   746,   751,   756,   686,  -374,    86,   432,   432,   432,
     342,  -374,   511,   550,   555,  -374,    88,  -374,  -374,  -374,
    -374
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,  -374,   580,  -310,     0,  -374,  -374,  -374,   413,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,    65,
    -374,   402,  -374,  -374,  -374,  -374,   505,  -374,    -4,   -25,
    -374,    17,   -19,  -117,  -136,   -28,    73,    20,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -373,
    -343,  -374,   486,   246,   322
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     156,   158,     4,    29,     5,   416,   370,   156,   156,   229,
     230,   231,   232,   233,   234,   235,   163,   404,   267,     5,
     354,    18,   286,   223,    28,   364,    21,   342,   160,   161,
     229,   230,   231,   232,   233,   234,   235,   229,   230,   231,
     232,   233,   234,   235,   405,   229,   230,   231,   232,   233,
     234,   235,   223,   223,   168,   169,   452,   279,   229,   230,
     231,   232,   233,   234,   235,    19,   273,   274,   167,   452,
     229,   230,   231,   232,   233,   234,   235,   471,   229,   230,
     231,   232,   233,   234,   235,   378,   156,   310,   450,   312,
     313,   314,   315,    27,   452,     6,   452,   444,   355,   224,
     488,   268,   406,   343,   308,   407,     3,   185,   473,    -2,
     227,     7,   228,     8,    20,   494,   165,   166,   266,     9,
      10,    11,    12,    13,   275,   276,     7,    26,   366,   400,
     393,   240,   453,   346,     9,    10,    11,    12,    21,   361,
     225,   226,   227,   435,   228,   490,   496,    24,   191,     7,
     239,   362,   379,    28,    25,   451,   164,   506,   157,   428,
     229,   230,   231,   232,   233,   234,   235,   489,   159,   363,
     501,   237,   510,   156,   156,   170,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   284,   285,   171,   382,   383,   384,
     172,   265,   173,   388,   389,   390,   156,   156,   156,   156,
     156,   280,   281,   282,   283,   233,   234,   235,   192,   436,
     395,   396,   397,   398,   399,   219,   220,   318,   319,   320,
     321,   322,   329,   330,   174,    31,    32,   307,    33,   175,
      34,   429,    35,   156,   176,    36,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   225,   226,   227,
     177,   228,   270,   271,   345,   229,   230,   231,   232,   233,
     234,   235,     4,   229,   230,   231,   232,   233,   234,   235,
     221,   225,   226,   227,   222,   228,   156,   247,   248,   456,
     457,   458,   417,   418,   419,   459,   460,   229,   230,   231,
     232,   233,   234,   235,   225,   226,   227,   369,   228,   350,
     351,   156,   156,   156,   229,   230,   231,   232,   233,   234,
     235,   229,   230,   231,   232,   233,   234,   235,   417,   418,
     419,   178,   385,   386,   387,   200,   433,   234,   235,   491,
     492,   493,   217,   218,   219,   220,   430,   229,   230,   231,
     232,   233,   234,   235,   480,   417,   418,   419,   238,   391,
     478,   502,   503,   504,   179,   218,   219,   220,   352,   353,
     180,   417,   418,   419,   417,   418,   419,   269,   481,     7,
     420,   375,   376,   479,   181,    18,   182,   449,   229,   230,
     231,   232,   233,   234,   235,   482,   241,   410,   411,   221,
     423,   424,   483,   222,   242,   243,   244,   472,   183,   156,
     156,   184,   156,   156,   156,   156,   156,   251,   252,   189,
     156,   221,   443,   495,   190,   222,   505,   246,   484,   193,
     461,   462,   194,   463,   464,   465,   466,   467,   413,   414,
     195,   469,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     196,   197,    62,    63,    64,    65,   236,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   198,
     108,   109,   110,   199,   286,   111,   225,   226,   227,   112,
     228,   316,   317,   311,   323,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   324,   325,
       7,   326,   327,   126,   331,   127,   128,   129,   229,   230,
     231,   232,   233,   234,   235,   225,   226,   227,   332,   228,
     225,   226,   227,   347,   228,   229,   230,   231,   232,   233,
     234,   235,   229,   230,   231,   232,   233,   234,   235,   229,
     230,   231,   232,   233,   234,   235,   225,   226,   227,   356,
     228,   333,   334,   335,   348,   507,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   231,   232,   233,   234,
     235,   225,   226,   227,   425,   228,   225,   226,   227,   485,
     228,   336,   337,   338,   508,   339,   340,   341,   349,   509,
     357,   358,   359,   402,   360,   225,   226,   227,   426,   228,
     486,   225,   226,   227,   427,   228,   367,   487,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     372,   373,   380,   222,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   225,   226,
     227,   431,   228,   225,   226,   227,   432,   228,   225,   226,
     227,   437,   228,   225,   226,   227,   438,   228,   225,   226,
     227,   439,   228,   225,   226,   227,   440,   228,   374,   381,
     392,   403,   221,   415,   434,   441,   222,   225,   226,   227,
     475,   228,   225,   226,   227,   476,   228,   442,   445,   446,
     447,   221,   448,   454,   455,   222,   225,   226,   227,   477,
     228,   225,   226,   227,   497,   228,   225,   226,   227,   498,
     228,   225,   226,   227,   499,   228,   468,   394,   470,   500,
     401,   272,   344,   365,   474
};

static const yytype_uint16 yycheck[] =
{
      25,    29,     2,    22,     1,   378,   316,    32,    33,     3,
       4,     5,     6,     7,     8,     9,    35,     1,     8,     1,
       8,     4,    83,     8,   106,    86,   108,     8,    32,    33,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,    28,     3,     4,     5,     6,     7,
       8,     9,     8,     8,    75,    76,     8,   193,     3,     4,
       5,     6,     7,     8,     9,    81,    17,    18,    51,     8,
       3,     4,     5,     6,     7,     8,     9,   450,     3,     4,
       5,     6,     7,     8,     9,    16,   111,   223,    16,   225,
     226,   227,   228,    20,     8,    92,     8,   407,    86,    84,
      16,    91,    86,    84,   221,    89,     0,   111,   451,     0,
       7,   108,     9,   110,    83,   488,    75,    76,    84,   116,
     117,   118,   119,   120,    75,    76,   108,   106,    84,    84,
      88,   125,    84,   269,   116,   117,   118,   119,   108,    84,
       5,     6,     7,     8,     9,    84,   489,    83,    85,   108,
     123,    84,    83,   106,    90,    83,   130,   500,    84,    84,
       3,     4,     5,     6,     7,     8,     9,    83,    81,   286,
      84,    81,    84,   198,   199,    83,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   198,   199,    83,   333,   334,   335,
      83,   184,    83,   339,   340,   341,   231,   232,   233,   234,
     235,   194,   195,   196,   197,     7,     8,     9,    85,    84,
     356,   357,   358,   359,   360,    28,    29,   231,   232,   233,
     234,   235,   251,   252,    83,   121,   122,   220,   124,    83,
     126,    84,   128,   268,    83,   131,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     5,     6,     7,
      83,     9,   189,   190,   268,     3,     4,     5,     6,     7,
       8,     9,   272,     3,     4,     5,     6,     7,     8,     9,
      83,     5,     6,     7,    87,     9,   311,    32,    33,   425,
     426,   427,    32,    33,    34,   431,   432,     3,     4,     5,
       6,     7,     8,     9,     5,     6,     7,   311,     9,    75,
      76,   336,   337,   338,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,    32,    33,
      34,    83,   336,   337,   338,    85,    84,     8,     9,   475,
     476,   477,    26,    27,    28,    29,    84,     3,     4,     5,
       6,     7,     8,     9,    84,    32,    33,    34,    81,   342,
      84,   497,   498,   499,    83,    27,    28,    29,    75,    76,
      83,    32,    33,    34,    32,    33,    34,     7,    84,   108,
      84,   106,   107,    84,    83,   368,    83,   415,     3,     4,
       5,     6,     7,     8,     9,    84,   127,   133,   134,    83,
     380,   381,    84,    87,   135,   136,   137,    84,    83,   434,
     435,    83,   437,   438,   439,   440,   441,   171,   172,    83,
     445,    83,   405,    84,    83,    87,    84,   129,    84,    83,
     434,   435,    83,   437,   438,   439,   440,   441,   373,   374,
      83,   445,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      83,    83,    30,    31,    32,    33,    81,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    83,
      78,    79,    80,    83,    83,    83,     5,     6,     7,    87,
       9,    85,    85,    90,   138,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   138,   138,
     108,     8,   108,   111,    84,   113,   114,   115,     3,     4,
       5,     6,     7,     8,     9,     5,     6,     7,    84,     9,
       5,     6,     7,    84,     9,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,     3,
       4,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     8,     8,     8,    84,    84,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,    84,
       9,     8,     8,     8,    84,     8,     8,     8,    86,    84,
       8,     8,     8,    81,     8,     5,     6,     7,     8,     9,
      81,     5,     6,     7,     8,     9,    88,    81,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    83,
     139,   139,     8,    87,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,   139,     8,
      29,    86,    83,     8,    83,   112,    87,     5,     6,     7,
       8,     9,     5,     6,     7,     8,     9,    81,    90,   139,
     139,    83,   139,    84,    84,    87,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,    86,   354,    84,    83,
     368,   191,   267,   287,   452
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   141,   142,     0,   144,     1,    92,   108,   110,   116,
     117,   118,   119,   120,   145,   149,   161,   163,   171,    81,
      83,   108,   172,   150,    83,    90,   106,   176,   106,   172,
     175,   121,   122,   124,   126,   128,   131,   151,   152,   153,
     154,   155,   156,   160,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    78,    79,
      80,    83,    87,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   111,   113,   114,   115,
     169,   170,   171,   173,   174,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   168,   169,    84,   175,    81,
     168,   168,   157,   172,   130,    75,    76,   171,    75,    76,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,   168,   166,   167,   176,    83,
      83,    85,    85,    83,    83,    83,    83,    83,    83,    83,
      85,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    83,    87,     8,    84,     5,     6,     7,     9,     3,
       4,     5,     6,     7,     8,     9,    81,    81,    81,   123,
     125,   127,   135,   136,   137,   158,   129,    32,    33,   198,
     203,   203,   203,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   165,   171,    84,     8,    91,     7,
     176,   176,   142,    17,    18,    75,    76,   147,   148,   174,
     171,   171,   171,   171,   168,   168,    83,   201,   202,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   171,   173,   143,
     174,    90,   174,   174,   174,   174,    85,    85,   168,   168,
     168,   168,   168,   138,   138,   138,     8,   108,   199,   172,
     172,    84,    84,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,    84,   166,   168,   174,    84,    84,    86,
      75,    76,    75,    76,     8,    86,     8,     8,     8,     8,
       8,    84,    84,   173,    86,   202,    84,    88,   144,   168,
     143,   146,   139,   139,   139,   106,   107,   177,    16,    83,
       8,     8,   174,   174,   174,   168,   168,   168,   174,   174,
     174,   171,    29,    88,   148,   174,   174,   174,   174,   174,
      84,   161,    81,    86,     1,    28,    86,    89,   162,   164,
     133,   134,   159,   159,   159,     8,   199,    32,    33,    34,
      84,   200,   204,   177,   177,     8,     8,     8,    84,    84,
      84,     8,     8,    84,    83,     8,    84,     8,     8,     8,
       8,   112,    81,   171,   143,    90,   139,   139,   139,   175,
      16,    83,     8,    84,    84,    84,   174,   174,   174,   174,
     174,   168,   168,   168,   168,   168,   168,   168,    86,   168,
      84,   199,    84,   200,   204,     8,     8,     8,    84,    84,
      84,    84,    84,    84,    84,    84,    81,    81,    16,    83,
      84,   174,   174,   174,   199,    84,   200,     8,     8,     8,
      83,    84,   174,   174,   174,    84,   200,    84,    84,    84,
      84
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
#line 359 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 362 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 4:
#line 363 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp); ;}
    break;

  case 5:
#line 366 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 6:
#line 367 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp);;}
    break;

  case 7:
#line 370 "faustparser.y"
    { (yyval.numvariant) = 0; ;}
    break;

  case 8:
#line 371 "faustparser.y"
    { (yyval.numvariant) = (yyvsp[(1) - (2)].numvariant) | (yyvsp[(2) - (2)].numvariant);;}
    break;

  case 9:
#line 374 "faustparser.y"
    { (yyval.numvariant) = 1;;}
    break;

  case 10:
#line 375 "faustparser.y"
    { (yyval.numvariant) = 2;;}
    break;

  case 11:
#line 376 "faustparser.y"
    { (yyval.numvariant) = 4;;}
    break;

  case 12:
#line 377 "faustparser.y"
    { (yyval.numvariant) = 8;;}
    break;

  case 13:
#line 380 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 14:
#line 381 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 15:
#line 388 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 389 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); ;}
    break;

  case 17:
#line 392 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 18:
#line 393 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 19:
#line 394 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 20:
#line 395 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 21:
#line 396 "faustparser.y"
    { (yyval.exp) = boxInt(-str2int(FAUSTtext)); ;}
    break;

  case 22:
#line 397 "faustparser.y"
    { (yyval.exp) = boxReal(-atof(FAUSTtext)); ;}
    break;

  case 23:
#line 400 "faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 24:
#line 401 "faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 25:
#line 402 "faustparser.y"
    { declareDefinitionMetadata((yyvsp[(2) - (5)].exp),(yyvsp[(3) - (5)].exp),(yyvsp[(4) - (5)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 26:
#line 403 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 27:
#line 404 "faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 28:
#line 407 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 29:
#line 408 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 30:
#line 411 "faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 31:
#line 412 "faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 32:
#line 413 "faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 33:
#line 414 "faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 34:
#line 415 "faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 35:
#line 416 "faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 36:
#line 419 "faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 37:
#line 420 "faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(FAUSTtext)); ;}
    break;

  case 38:
#line 423 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 39:
#line 426 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 40:
#line 429 "faustparser.y"
    { ;}
    break;

  case 41:
#line 432 "faustparser.y"
    { ;}
    break;

  case 42:
#line 435 "faustparser.y"
    { ;}
    break;

  case 43:
#line 436 "faustparser.y"
    { ;}
    break;

  case 44:
#line 439 "faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 45:
#line 440 "faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; ;}
    break;

  case 46:
#line 441 "faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 47:
#line 444 "faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 48:
#line 445 "faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 49:
#line 448 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 50:
#line 451 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); setDefProp((yyvsp[(1) - (7)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 51:
#line 452 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp)));  setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 52:
#line 453 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 53:
#line 456 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 54:
#line 457 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 55:
#line 460 "faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); ;}
    break;

  case 56:
#line 463 "faustparser.y"
    { (yyval.exp)=(yyvsp[(2) - (2)].exp); ;}
    break;

  case 57:
#line 466 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 58:
#line 467 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 59:
#line 470 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 60:
#line 471 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 61:
#line 474 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 62:
#line 475 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 63:
#line 478 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 64:
#line 479 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp)), gGlobal->nil); ;}
    break;

  case 65:
#line 480 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (7)].exp),formatDefinitions((yyvsp[(4) - (7)].exp)),formatDefinitions((yyvsp[(6) - (7)].exp))); ;}
    break;

  case 66:
#line 481 "faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 67:
#line 482 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 68:
#line 483 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 69:
#line 484 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 70:
#line 485 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 71:
#line 486 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 72:
#line 489 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxAdd()); ;}
    break;

  case 73:
#line 490 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxSub()); ;}
    break;

  case 74:
#line 491 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxMul()); ;}
    break;

  case 75:
#line 492 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxDiv()); ;}
    break;

  case 76:
#line 493 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxRem()); ;}
    break;

  case 77:
#line 494 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPow()); ;}
    break;

  case 78:
#line 495 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxDelay()); ;}
    break;

  case 79:
#line 496 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxDelay1()); ;}
    break;

  case 80:
#line 497 "faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 81:
#line 499 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxAND()); ;}
    break;

  case 82:
#line 500 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxOR()); ;}
    break;

  case 83:
#line 501 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxXOR()); ;}
    break;

  case 84:
#line 503 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLeftShift()); ;}
    break;

  case 85:
#line 504 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxARightShift()); ;}
    break;

  case 86:
#line 506 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLT()); ;}
    break;

  case 87:
#line 507 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLE()); ;}
    break;

  case 88:
#line 508 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxGT()); ;}
    break;

  case 89:
#line 509 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxGE()); ;}
    break;

  case 90:
#line 510 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxEQ()); ;}
    break;

  case 91:
#line 511 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxNE()); ;}
    break;

  case 92:
#line 513 "faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 93:
#line 514 "faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 94:
#line 516 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 95:
#line 519 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 96:
#line 520 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 97:
#line 522 "faustparser.y"
    { (yyval.exp) = boxInt (str2int(FAUSTtext)); ;}
    break;

  case 98:
#line 523 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 99:
#line 525 "faustparser.y"
    { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); ;}
    break;

  case 100:
#line 526 "faustparser.y"
    { (yyval.exp) = boxReal( -atof(FAUSTtext) ); ;}
    break;

  case 101:
#line 528 "faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 102:
#line 529 "faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 103:
#line 531 "faustparser.y"
    { (yyval.exp) = boxDelay1(); ;}
    break;

  case 104:
#line 532 "faustparser.y"
    { (yyval.exp) = boxPrefix(); ;}
    break;

  case 105:
#line 534 "faustparser.y"
    { (yyval.exp) = boxIntCast(); ;}
    break;

  case 106:
#line 535 "faustparser.y"
    { (yyval.exp) = boxFloatCast(); ;}
    break;

  case 107:
#line 537 "faustparser.y"
    { (yyval.exp) = boxAdd(); ;}
    break;

  case 108:
#line 538 "faustparser.y"
    { (yyval.exp) = boxSub(); ;}
    break;

  case 109:
#line 539 "faustparser.y"
    { (yyval.exp) = boxMul(); ;}
    break;

  case 110:
#line 540 "faustparser.y"
    { (yyval.exp) = boxDiv(); ;}
    break;

  case 111:
#line 541 "faustparser.y"
    { (yyval.exp) = boxRem(); ;}
    break;

  case 112:
#line 542 "faustparser.y"
    { (yyval.exp) = boxDelay(); ;}
    break;

  case 113:
#line 544 "faustparser.y"
    { (yyval.exp) = boxAND(); ;}
    break;

  case 114:
#line 545 "faustparser.y"
    { (yyval.exp) = boxOR(); ;}
    break;

  case 115:
#line 546 "faustparser.y"
    { (yyval.exp) = boxXOR(); ;}
    break;

  case 116:
#line 548 "faustparser.y"
    { (yyval.exp) = boxLeftShift(); ;}
    break;

  case 117:
#line 549 "faustparser.y"
    { (yyval.exp) = boxARightShift(); ;}
    break;

  case 118:
#line 551 "faustparser.y"
    { (yyval.exp) = boxLT(); ;}
    break;

  case 119:
#line 552 "faustparser.y"
    { (yyval.exp) = boxLE(); ;}
    break;

  case 120:
#line 553 "faustparser.y"
    { (yyval.exp) = boxGT(); ;}
    break;

  case 121:
#line 554 "faustparser.y"
    { (yyval.exp) = boxGE(); ;}
    break;

  case 122:
#line 555 "faustparser.y"
    { (yyval.exp) = boxEQ(); ;}
    break;

  case 123:
#line 556 "faustparser.y"
    { (yyval.exp) = boxNE(); ;}
    break;

  case 124:
#line 558 "faustparser.y"
    { (yyval.exp) = boxAttach(); ;}
    break;

  case 125:
#line 559 "faustparser.y"
    { (yyval.exp) = boxEnable(); ;}
    break;

  case 126:
#line 560 "faustparser.y"
    { (yyval.exp) = boxControl(); ;}
    break;

  case 127:
#line 562 "faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); ;}
    break;

  case 128:
#line 563 "faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); ;}
    break;

  case 129:
#line 564 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); ;}
    break;

  case 130:
#line 565 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); ;}
    break;

  case 131:
#line 566 "faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); ;}
    break;

  case 132:
#line 567 "faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); ;}
    break;

  case 133:
#line 568 "faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); ;}
    break;

  case 134:
#line 570 "faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); ;}
    break;

  case 135:
#line 571 "faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); ;}
    break;

  case 136:
#line 572 "faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); ;}
    break;

  case 137:
#line 573 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 138:
#line 574 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 139:
#line 575 "faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); ;}
    break;

  case 140:
#line 577 "faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); ;}
    break;

  case 141:
#line 578 "faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); ;}
    break;

  case 142:
#line 579 "faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); ;}
    break;

  case 143:
#line 581 "faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); ;}
    break;

  case 144:
#line 582 "faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); ;}
    break;

  case 145:
#line 584 "faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); ;}
    break;

  case 146:
#line 585 "faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); ;}
    break;

  case 147:
#line 586 "faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); ;}
    break;

  case 148:
#line 587 "faustparser.y"
    { (yyval.exp) = gGlobal->gRoundPrim->box(); ;}
    break;

  case 149:
#line 589 "faustparser.y"
    { (yyval.exp) = boxReadOnlyTable(); ;}
    break;

  case 150:
#line 590 "faustparser.y"
    { (yyval.exp) = boxWriteReadTable(); ;}
    break;

  case 151:
#line 592 "faustparser.y"
    { (yyval.exp) = boxSelect2(); ;}
    break;

  case 152:
#line 593 "faustparser.y"
    { (yyval.exp) = boxSelect3(); ;}
    break;

  case 153:
#line 595 "faustparser.y"
    { (yyval.exp) = boxAssertBound(); ;}
    break;

  case 154:
#line 596 "faustparser.y"
    { (yyval.exp) = boxLowest(); ;}
    break;

  case 155:
#line 597 "faustparser.y"
    { (yyval.exp) = boxHighest(); ;}
    break;

  case 156:
#line 599 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); setUseProp((yyvsp[(1) - (1)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 157:
#line 600 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxSub()); ;}
    break;

  case 158:
#line 602 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 159:
#line 604 "faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 160:
#line 610 "faustparser.y"
    { (yyval.exp) = buildBoxModulation((yyvsp[(2) - (5)].exp),(yyvsp[(4) - (5)].exp)); ;}
    break;

  case 161:
#line 612 "faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 162:
#line 614 "faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 163:
#line 615 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 164:
#line 616 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 165:
#line 617 "faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 166:
#line 618 "faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 167:
#line 619 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 168:
#line 620 "faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); ;}
    break;

  case 169:
#line 621 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp), boxPar(boxInt(0),boxInt(0))); ;}
    break;

  case 170:
#line 622 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), (yyvsp[(7) - (8)].exp)); ;}
    break;

  case 171:
#line 623 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 172:
#line 624 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 173:
#line 625 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 174:
#line 626 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 175:
#line 627 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 176:
#line 628 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 177:
#line 629 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 178:
#line 630 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 179:
#line 631 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 180:
#line 632 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 181:
#line 633 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 182:
#line 635 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 183:
#line 636 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 184:
#line 637 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 185:
#line 638 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 186:
#line 640 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 187:
#line 641 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 188:
#line 644 "faustparser.y"
    { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 189:
#line 647 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 190:
#line 650 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 191:
#line 651 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 192:
#line 654 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 193:
#line 655 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 194:
#line 656 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 195:
#line 657 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 196:
#line 658 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 197:
#line 661 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 198:
#line 664 "faustparser.y"
    { (yyval.exp) = unquote(FAUSTtext); ;}
    break;

  case 199:
#line 667 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 200:
#line 668 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 201:
#line 674 "faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 202:
#line 678 "faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 203:
#line 682 "faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 204:
#line 686 "faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 205:
#line 689 "faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 206:
#line 692 "faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 207:
#line 698 "faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 208:
#line 702 "faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 209:
#line 706 "faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 210:
#line 710 "faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 211:
#line 713 "faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 212:
#line 717 "faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 213:
#line 720 "faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 214:
#line 723 "faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 215:
#line 726 "faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 216:
#line 729 "faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 217:
#line 732 "faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 218:
#line 736 "faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 219:
#line 739 "faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 220:
#line 742 "faustparser.y"
    { (yyval.exp) = boxSoundfile((yyvsp[(3) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 221:
#line 748 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp),cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil)))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 222:
#line 749 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil)))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 223:
#line 750 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp),cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil)))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 224:
#line 751 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (11)].exp),cons(cons((yyvsp[(2) - (11)].exp),cons((yyvsp[(4) - (11)].exp),cons((yyvsp[(6) - (11)].exp),cons((yyvsp[(8) - (11)].exp),gGlobal->nil)))), (yyvsp[(10) - (11)].exp))); ;}
    break;

  case 225:
#line 753 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 226:
#line 754 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp),cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 227:
#line 755 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp),cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 228:
#line 756 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (10)].exp),cons(cons((yyvsp[(2) - (10)].exp),cons((yyvsp[(4) - (10)].exp),cons((yyvsp[(6) - (10)].exp),cons((yyvsp[(8) - (10)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 229:
#line 759 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 230:
#line 762 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 231:
#line 763 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 232:
#line 766 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 233:
#line 767 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 234:
#line 771 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 235:
#line 774 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 236:
#line 775 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 237:
#line 778 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 238:
#line 779 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 239:
#line 780 "faustparser.y"
    { (yyval.exp) = tree(2); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3421 "faustparser.cpp"
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


#line 783 "faustparser.y"


